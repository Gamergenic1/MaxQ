// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "SampleUtilities.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Spice.h"

#if WITH_EDITOR
#include "Interfaces/IPluginManager.h"
#endif

class AActor;

DEFINE_LOG_CATEGORY(LogMaxQSamples);

namespace MaxQSamples
{
    const FString PluginName = TEXT("MaxQ");

    FString MaxQPluginInfo()
    {
        FString Info = PluginName;

    #if WITH_EDITOR
        FString pluginFilePath = FPaths::Combine(IPluginManager::Get().FindPlugin(*PluginName)->GetBaseDir(), TEXT("Documentation"));
        IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
        FString AbsolutePluginFilePath = PlatformFile.ConvertToAbsolutePathForExternalAppForRead(*pluginFilePath);

        Info = FString::Printf(TEXT("%s (Documentation:%s)"), *IPluginManager::Get().FindPlugin(*PluginName)->GetFriendlyName(), *AbsolutePluginFilePath);
    #endif

        return Info;
    }

    void AbsolutifyMaxQPath(FString& path)
    {
#if WITH_EDITOR
        FString pluginFilePath = FPaths::Combine(IPluginManager::Get().FindPlugin(*PluginName)->GetContentDir(), path);
        IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
        FString PluginFilePath = PlatformFile.ConvertToAbsolutePathForExternalAppForRead(*pluginFilePath);

        if (FPaths::FileExists(PluginFilePath) || FPaths::DirectoryExists(PluginFilePath))
        {
            path = PluginFilePath;
        }
#endif
    }

    FString MaxQPathAbsolutified(const FString& path)
    {
        FString AbsolutePath = path;
        AbsolutifyMaxQPath(AbsolutePath);
        return AbsolutePath;
    }

    TArray<FString> MaxQPathsAbsolutified(const TArray<FString>& paths)
    {
        TArray<FString> AbsolutePaths;

        for (auto path : paths)
        {
            AbsolutePaths.Add(MaxQPathAbsolutified(path));
        }

        return AbsolutePaths;
    }

    bool InitBodyScales(float BodyScale, const FSamplesSolarSystemState& SolarSystemState)
    {
        ES_ResultCode ResultCode = ES_ResultCode::Success;
        FString ErrorMessage = "";

        for (auto BodyPair : SolarSystemState.SolarSystemBodyMap)
        {
            FString NaifName = BodyPair.Key.ToString();
            AActor* Actor = BodyPair.Value.Get();

            if (Actor)
            {
                FSDistanceVector Radii;
                USpice::bodvrd_distance_vector(ResultCode, ErrorMessage, Radii, NaifName, TEXT("RADII"));

                if (ResultCode == ES_ResultCode::Success)
                {
                    // Get the dimensions of the static mesh at the root...  (ringed planets have multiple meshes)
                    UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(Actor->GetRootComponent());

                    if (SM && SM->GetStaticMesh())
                    {
                        FBoxSphereBounds Bounds = SM->GetStaticMesh()->GetBounds();

                        // ** Swizzle is the correct way to get an FVector from FSDistanceVector etc **
                        FVector ScenegraphRadii = USpiceTypes::Swizzle(Radii.AsKilometers());

                        // Swizzle does no scaling, so our values are in kilometers
                        // Normally one scenegraph unit = one centimeter, but let's scale it all down
                        ScenegraphRadii /= BodyScale;

                        FVector ScenegraphDiameter = ScenegraphRadii;

                        // Finally, set the actor's scale based on the actual size and the mesh dimensions
                        Actor->SetActorScale3D(ScenegraphDiameter / Bounds.BoxExtent);
                    }
                    else
                    {
                        Log(FString::Printf(TEXT("InitializeSolarSystem could not find static mesh for %s"), *NaifName), FColor::Red);
                    }
                }
            }
        }

        return ResultCode == ES_ResultCode::Success;
    }

    bool UpdateBodyPositions(const FName& OriginNaifName, const FName& OriginReferenceFrame, float DistanceScale, const FSamplesSolarSystemState& SolarSystemState)
    {
        FSDistanceVector r;
        FSEphemerisPeriod lt;

        ES_ResultCode ResultCode;
        FString ErrorMessage;

        // When do we want it?   (time: now)
        FSEphemerisTime et = SolarSystemState.CurrentTime;

        bool result = true;
        for (auto BodyPair : SolarSystemState.SolarSystemBodyMap)
        {
            AActor* Actor = BodyPair.Value.Get();

            if (Actor)
            {
                // Targ = NaifName = Map Key
                FString targ = BodyPair.Key.ToString();

                // Call SPICE, get the position in rectangular coordinates...
                USpice::spkpos(ResultCode, ErrorMessage, et, r, lt, targ, OriginNaifName.ToString(), OriginReferenceFrame.ToString());

                result &= (ResultCode == ES_ResultCode::Success);

                if (result)
                {
                    // IMPORTANT NOTE:
                    // Positional data (vectors, quaternions, should only be exchanged through USpiceTypes::Conf_*
                    // SPICE coordinate systems are Right-Handed, and Unreal Engine is Left-Handed.
                    // The USpiceTypes conversions understand this, and how to convert.
                    FVector BodyLocation = USpiceTypes::Swizzle(r);

                    // Scale and set the body location
                    BodyLocation /= DistanceScale;
                    Actor->SetActorLocation(BodyLocation);
                }
            }
        }

        return result;
    }

    bool UpdateBodyOrientations(const FName& OriginReferenceFrame, const FSamplesSolarSystemState& SolarSystemState)
    {
        ES_ResultCode ResultCode;
        FString ErrorMessage;

        // When do we want it?   (time: now)
        FSEphemerisTime et = SolarSystemState.CurrentTime;

        bool result = true;
        for (auto BodyPair : SolarSystemState.SolarSystemBodyMap)
        {
            // The rotation matrix that will be the delta from the inertial frame
            // of the origin and the body frame of earth/moon
            FSRotationMatrix m;

            // Body Frame (IAU_EARTH, IAU_MOON, etc)
            FString BodyFrame = TEXT("IAU_") + BodyPair.Key.ToString();

            // Get the rotation matrix from the orign's frame to the Body frame.
            USpice::pxform(ResultCode, ErrorMessage, m, et, BodyFrame, OriginReferenceFrame.ToString());

            result &= (ResultCode == ES_ResultCode::Success);

            AActor* Actor = BodyPair.Value.Get();
            if (Actor && result)
            {
                // Convert the Rotation Matrix into a SPICE Quaternion
                FSQuaternion q;
                USpice::m2q(ResultCode, ErrorMessage, m, q);

                // (m2q can't fail unless 'm' isn't a rotation matrix... But if pxform succeeded, it will be)
                result &= (ResultCode == ES_ResultCode::Success);

                // Now, convert the SPICE Quaternion into an Unreal Engine Quaternion
                if (result)
                {
                    // IMPORTANT NOTE:
                    // Positional data (vectors, quaternions, should only be exchanged through USpiceTypes::Conf_*
                    // SPICE coordinate systems are Right-Handed, and Unreal Engine is Left-Handed.
                    // The USpiceTypes conversions understand this, and how to convert.
                    FQuat BodyOrientation = USpiceTypes::Swazzle(q);

                    Actor->SetActorRotation(BodyOrientation);
                }
            }
        }

        return result;
    }

    bool UpdateSunDirection(const FName& OriginNaifName, const FName& OriginReferenceFrame, const FSEphemerisTime& et, const FName& SunNaifName, const TWeakObjectPtr<AActor>& SunDirectionalLight)
    {
        FSDistanceVector r;
        FSEphemerisPeriod lt;

        ES_ResultCode ResultCode;
        FString ErrorMessage;

        // Call SPICE, get the position in rectangular coordinates...
        USpice::spkpos(ResultCode, ErrorMessage, et, r, lt, SunNaifName.ToString(), OriginNaifName.ToString(), OriginReferenceFrame.ToString());

        bool result = (ResultCode == ES_ResultCode::Success);

        if (result)
        {
            // We assume we want to point the sun at the origin...
            FSDimensionlessVector DirectionToSun;
            FSDistance DistanceToSun;

            USpice::unorm_distance(r, DirectionToSun, DistanceToSun);

            FVector LightDirection = -USpiceTypes::Swizzle(DirectionToSun);

            AActor* SunActor = SunDirectionalLight.Get();

            if (SunActor)
            {
                SunActor->SetActorRotation(LightDirection.Rotation());
            }
        }

        return result;
    }

    void Log(const FString& LogString, const FColor& Color, float DisplayTime)
    {
        UE_LOG(LogMaxQSamples, Log, TEXT("%s"), *LogString);
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, DisplayTime, Color, LogString);
        }
    }

    void Log(const FString& LogString, ES_ResultCode ResultCode)
    {
        if (ResultCode == ES_ResultCode::Success)
        {
            UE_LOG(LogMaxQSamples, Log, TEXT("%s"), *LogString);
        }
        else
        {
            UE_LOG(LogMaxQSamples, Error, TEXT("%s"), *LogString);
        }

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 60.0f, ResultCode == ES_ResultCode::Success ? FColor::Green : FColor::Red, LogString);
        }
    }
}


void USampleUtilities::GetMaxQPluginInfo(FString& Info)
{
    Info = MaxQSamples::MaxQPluginInfo();
}

void USampleUtilities::GetMaxQPathAbsolutified(const FString& path, FString& AbsolutePath)
{
    AbsolutePath = MaxQSamples::MaxQPathAbsolutified(path);
}

void USampleUtilities::GetMaxQPathsAbsolutified(const TArray<FString>& paths, TArray<FString>& AbsolutePaths)
{
    AbsolutePaths = MaxQSamples::MaxQPathsAbsolutified(paths);
}

bool USampleUtilities::LoadKernelList(const FString& ListName, const TArray<FString>& KernelFiles)
{
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage = "";

    USpice::furnsh_list(ResultCode, ErrorMessage, MaxQSamples::MaxQPathsAbsolutified(KernelFiles));

    MaxQSamples::Log(FString::Printf(TEXT("Loaded %s Kernel files"), *ListName), ResultCode);
    if (ResultCode != ES_ResultCode::Success)
    {
        MaxQSamples::Log(FString::Printf(TEXT("Error: %s"), *ErrorMessage), FColor::Red);
    }

    return ResultCode == ES_ResultCode::Success;
}

void USampleUtilities::InitializeTime(FSamplesSolarSystemState& SolarSystemState, bool SetInitialTime)
{
    if (SolarSystemState.InitializeTimeToNow)
    {
        USpice::et_now(SolarSystemState.CurrentTime);
        if(SetInitialTime) SolarSystemState.InitialTime = SolarSystemState.CurrentTime.ToString();
    }
    else
    {
        SolarSystemState.CurrentTime = FSEphemerisTime::FromString(SolarSystemState.InitialTime);
    }
}

void USampleUtilities::GetDefaultBasicKernels(TArray<FString>& BasicKernels)
{
    BasicKernels.Empty();

    // This is a "Leap Seconds" kernel
    BasicKernels.Add(TEXT("NonAssetData/naif/kernels/Generic/LSK/naif0012.tls"));

    // This is a PCK kernel... Which contains data about planet orientations, etc
    BasicKernels.Add(TEXT("NonAssetData/naif/kernels/Generic/PCK/pck00010.tpc"));

    // This mass kernel matches what was used to generate de431, not de440...
    // ...which we load below...  But that's okay here
    BasicKernels.Add(TEXT("NonAssetData/naif/kernels/Generic/PCK/gm_de431.tpc"));

    // SPK Kernel, which is a trimmed down subset of de440 (32mb, instead of 114m)
    // (GitHub balks at anything over 100mb).
    BasicKernels.Add(TEXT("NonAssetData/naif/kernels/Generic/SPK/planets/de440s.bsp"));
}

void USampleUtilities::GetDefaultItrf93Kernels(TArray<FString>& Itrf93Kernels)
{
    Itrf93Kernels.Empty();

    // A "binary earth" PCK is a high precision measurement or prediction of the Earth's orientation
    // This kernel is predictive and a "low precision" version (it's still 14mb, so...)
    Itrf93Kernels.Add(TEXT("NonAssetData/naif/kernels/Generic/PCK/earth_200101_990628_predict.bpc"));

    // We need this FK kernel to establish the "ITRF" reference frame, which is affixed to earth.
    // The data in the PCK file above is relative to ITRF, so we need it.
    Itrf93Kernels.Add(TEXT("NonAssetData/naif/kernels/Generic/PCK/earth_fixed.tf"));

    // This text file FK kernel establishes earth-fixed topocentric ROTATION offsets for 
    // Deep Space Space stations (antennas for communicating with deep space).
    // It defines reference frames only (rotation orientation), as rotation offsets, which are "class 4" FK frames.
    // More into: https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/frames.html
    // It also established the Naif Id codes for the stations, like so:
    // NAIF_BODY_NAME += 'DSS-14'
    // NAIF_BODY_CODE += 399014
    // More info: https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/naif_ids.html
    Itrf93Kernels.Add(TEXT("NonAssetData/naif/kernels/Generic/FK/stations/earth_topo_201023.tf"));

    // This binary SPK kernel is where the fixed POSITION offsets for the DSN stations come from.
    Itrf93Kernels.Add(TEXT("NonAssetData/naif/kernels/Generic/SPK/stations/earthstns_itrf93_201023.bsp"));
}

void USampleUtilities::GetDefaultInsightMissionKernels(TArray<FString>& InsightMissionKernels)
{
    InsightMissionKernels.Empty();

    InsightMissionKernels.Add(TEXT("NonAssetData/naif/kernels/INSIGHT/FK/insight_v05.tf"));
    InsightMissionKernels.Add(TEXT("NonAssetData/naif/kernels/INSIGHT/SPK/insight_ls_ops181206_iau2000_v1.bsp"));
    InsightMissionKernels.Add(TEXT("NonAssetData/naif/kernels/INSIGHT/SPK/mar097s.bsp"));
    InsightMissionKernels.Add(TEXT("NonAssetData/naif/kernels/INSIGHT/SPK/insight_struct_v01.bsp"));
}


#define LIVE_URL_BASE "https://celestrak.com"

void USampleUtilities::GetTelemetryFromServer(FTelemetryCallback Callback, FString ObjectId, FString Format)
{
    // Example URLs
    // https://celestrak.com/NORAD/elements/gp.php?CATNR=25544&FORMAT=TLE
    // https://celestrak.com/NORAD/elements/gp.php?GROUP=STATIONS&FORMAT=TLE
    // https://celestrak.com/NORAD/elements/gp.php?NAME=MICROSAT-R&FORMAT=JSON
    // https://celestrak.com/NORAD/elements/gp.php?INTDES=2020-025&FORMAT=JSON-PRETTY
    FString uriBase = LIVE_URL_BASE;
    FString uriQuery = uriBase + TEXT("/NORAD/elements/gp.php?") + ObjectId + TEXT("&FORMAT") + Format;

    FHttpModule& httpModule = FHttpModule::Get();

    // Create an http request
    // The request will execute asynchronously, and call us back on the Lambda below
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> pRequest = httpModule.CreateRequest();

    FString RequestContent;

    pRequest->SetVerb(TEXT("GET"));
    pRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));

    pRequest->SetURL(uriQuery);

    pRequest->OnProcessRequestComplete().BindLambda(
        [ObjectId, Callback](
            FHttpRequestPtr pRequest,
            FHttpResponsePtr pResponse,
            bool connectedSuccessfully) mutable {

                // Validate http called us back on the Game Thread...
                check(IsInGameThread());

                if (connectedSuccessfully) {
                    UE_LOG(LogTemp, Log, TEXT("Space-Track response: %s"), *(pResponse->GetContentAsString().Left(64)));

                    if (Callback.IsBound())
                    {
                        Callback.Execute(true, ObjectId, pResponse->GetContentAsString());
                        Callback.Unbind();
                    }
                }
                else {
                    FString Mistake;

                    switch (pRequest->GetStatus()) {
                    case EHttpRequestStatus::Failed_ConnectionError:
                        Mistake = TEXT("Connection failed.");
                    default:
                        Mistake = TEXT("Request failed.");
                    }

                    UE_LOG(LogTemp, Error, TEXT("GetTelemetryFromServer Error: %s"), *Mistake);

                    if (Callback.IsBound())
                    {
                        Callback.Execute(false, ObjectId, Mistake);
                        Callback.Unbind();
                    }
                }
        });

    UE_LOG(LogTemp, Log, TEXT("request: %s; content:%s"), *uriBase, *uriQuery);

    pRequest->ProcessRequest();
}