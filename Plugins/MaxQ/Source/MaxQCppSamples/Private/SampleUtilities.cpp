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

using namespace MaxQ::Data;
using namespace MaxQ::Core;
using namespace MaxQ::Constants;
using namespace MaxQ::Math;


namespace MaxQSamples
{
    const FString PluginName = TEXT("MaxQ");

    //-----------------------------------------------------------------------------
    // Name: MaxQPluginInfo
    // Desc:
    // Report the sample's file system location, so the user can find the plugin's
    // files if needed (to see documentation, kernels, etc)
    // Exposed to Blueprints & the Blueprint samples also use this, because
    // it's not implementable in Blueprints alone without a Third Party plugin.
    //-----------------------------------------------------------------------------
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


    //-----------------------------------------------------------------------------
    // Name: AbsolutifyMaxQPath
    // Desc:
    // 'furnsh' accepts directories relative to the content folder OR absolute
    // paths.
    // To run the samples, we need to know exactly where the plugin is installed.
    // This turns plugin-relative paths into absolute paths.  It's only needed for
    // the sample kernels.
    // Non-temporary variable (path-by-reference) version.
    //-----------------------------------------------------------------------------
    FString AbsolutifyMaxQPathForWriting(const FString& path)
    {
#if WITH_EDITOR
        FString pluginFilePath = FPaths::Combine(IPluginManager::Get().FindPlugin(*PluginName)->GetContentDir(), path);
        IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
        return PlatformFile.ConvertToAbsolutePathForExternalAppForRead(*pluginFilePath);
#else
        return path;
#endif
    }


    //-----------------------------------------------------------------------------
    // Name: AbsolutifyMaxQPath
    // Desc:
    // 'furnsh' accepts directories relative to the content folder OR absolute
    // paths.
    // To run the samples, we need to know exactly where the plugin is installed.
    // This turns plugin-relative paths into absolute paths.  It's only needed for
    // the sample kernels.
    // Non-temporary variable (path-by-reference) version.
    //-----------------------------------------------------------------------------
    void AbsolutifyMaxQPath(FString& path)
    {
#if WITH_EDITOR
        AbsolutifyMaxQPathForWriting(path);
        FString PluginFilePath = AbsolutifyMaxQPathForWriting(path);

        if (FPaths::FileExists(PluginFilePath) || FPaths::DirectoryExists(PluginFilePath))
        {
            path = PluginFilePath;
        }
#endif
    }

    //-----------------------------------------------------------------------------
    // Name: MaxQPathAbsolutified
    // Desc:
    // Same as AbsolutifyMaxQPath, but returns the path via a temporary.
    // (Programming convenience, by technically less flexible since it forces the
    // instantiation of a return value and copy the value upon return.)
    //-----------------------------------------------------------------------------
    FString MaxQPathAbsolutified(const FString& path)
    {
        FString AbsolutePath = path;
        AbsolutifyMaxQPath(AbsolutePath);
        return AbsolutePath;
    }

    //-----------------------------------------------------------------------------
    // Name: MaxQPathsAbsolutified
    // Desc:
    // Same as MaxQPathAbsolutified above, but for a whole array of paths.
    //-----------------------------------------------------------------------------
    TArray<FString> MaxQPathsAbsolutified(const TArray<FString>& paths)
    {
        TArray<FString> AbsolutePaths;

        for (auto path : paths)
        {
            AbsolutePaths.Add(MaxQPathAbsolutified(path));
        }

        return AbsolutePaths;
    }

    //-----------------------------------------------------------------------------
    // Name: InitBodyScales
    // Desc:
    // Generalized scale (size) initialization for meshes in a group of solar
    // system bodies.
    // This keeps boilerplate scenario stuff out of the samples, so each sample
    // can more readily highlight the interesting parts.
    //-----------------------------------------------------------------------------
    bool InitBodyScales(float BodyScale, const FSamplesSolarSystemState& SolarSystemState)
    {
        ES_ResultCode ResultCode = ES_ResultCode::Success;
        FString ErrorMessage = "";

        for (const auto& [BodyNaifName, BodyActor] : SolarSystemState.SolarSystemBodyMap)
        {
            FString NaifName = BodyNaifName.ToString();
            AActor* Actor = BodyActor.Get();

            if (Actor)
            {
                auto Radii = Bodvrd<FSDistanceVector>(NaifName, TEXT("RADII"), &ResultCode, &ErrorMessage);

                if (ResultCode == ES_ResultCode::Success)
                {
                    // Get the dimensions of the static mesh at the root...  (ringed planets have multiple meshes)
                    UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(Actor->GetRootComponent());

                    if (SM && SM->GetStaticMesh())
                    {
                        FBoxSphereBounds Bounds = SM->GetStaticMesh()->GetBounds();

                        // ** Swizzle is the correct way to get an FVector from FSDistanceVector etc **
                        FVector ScenegraphRadii = Radii.AsKilometers().Swizzle();

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


    //-----------------------------------------------------------------------------
    // Name: UpdateBodyPositions
    // Desc:
    // Generalized positioning of solar system bodies.
    // This keeps boilerplate scenario stuff out of the samples.
    //-----------------------------------------------------------------------------
    bool UpdateBodyPositions(const FName& OriginNaifName, const FName& OriginReferenceFrame, float DistanceScale, const FSamplesSolarSystemState& SolarSystemState)
    {
        FSDistanceVector r;
        FSEphemerisPeriod lt;

        ES_ResultCode ResultCode;
        FString ErrorMessage;

        // When do we want it?   (time: now)
        FSEphemerisTime et = SolarSystemState.CurrentTime;

        bool result = true;
        for (const auto& [BodyNaifName, BodyActor] : SolarSystemState.SolarSystemBodyMap)
        {
            AActor* Actor = BodyActor.Get();

            if (Actor)
            {
                // Targ = NaifName = Map Key
                FString targ = BodyNaifName.ToString();

                // Call SPICE, get the position in rectangular coordinates...
                USpice::spkpos(ResultCode, ErrorMessage, et, r, lt, targ, OriginNaifName.ToString(), OriginReferenceFrame.ToString());

                result &= (ResultCode == ES_ResultCode::Success);

                if (result)
                {
                    // IMPORTANT NOTE:
                    // Positional data (vectors, quaternions, should only be exchanged through USpiceTypes::Conf_*
                    // SPICE coordinate systems are Right-Handed, and Unreal Engine is Left-Handed.
                    // The USpiceTypes conversions understand this, and how to convert.
                    FVector BodyLocation = r.Swizzle();

                    // Scale and set the body location
                    BodyLocation /= DistanceScale;
                    Actor->SetActorLocation(BodyLocation);
                }
            }
        }

        return result;
    }

    //-----------------------------------------------------------------------------
    // Name: UpdateBodyOrientations
    // Desc:
    // Generalized orienatation updates of solar system bodies.
    // This keeps boilerplate scenario stuff out of the samples.
    //-----------------------------------------------------------------------------
    bool UpdateBodyOrientations(const FName& OriginReferenceFrame, const FSamplesSolarSystemState& SolarSystemState)
    {
        ES_ResultCode ResultCode;
        FString ErrorMessage;

        // When do we want it?   (time: now)
        FSEphemerisTime et = SolarSystemState.CurrentTime;

        bool result = true;
        for (const auto& [BodyNaifName, BodyActor] : SolarSystemState.SolarSystemBodyMap)
        {
            // The rotation matrix that will be the delta from the inertial frame
            // of the origin and the body frame of earth/moon
            FSRotationMatrix m;

            // Body Frame (IAU_EARTH, IAU_MOON, etc)
            FString BodyFrame = TEXT("IAU_") + BodyNaifName.ToString();

            // Get the rotation matrix from the body frame, to the observer's frame (coord system origin)
            // So, to position the body from the perspective of a camera from the observer's frame,
            // we need to rotate it by this rotation, right?  Right.
            USpice::pxform(ResultCode, ErrorMessage, m, et, BodyFrame, OriginReferenceFrame.ToString());

            result &= (ResultCode == ES_ResultCode::Success);

            AActor* Actor = BodyActor.Get();
            if (Actor && result)
            {
                // Convert the Rotation Matrix into a SPICE Quaternion
                auto q = M2q(m, &ResultCode);

                // (m2q can't fail unless 'm' isn't a rotation matrix... But if pxform succeeded, it will be)
                result &= (ResultCode == ES_ResultCode::Success);

                // Now, convert the SPICE Quaternion into an Unreal Engine Quaternion
                if (result)
                {
                    // IMPORTANT NOTE:
                    // Positional data (vectors, quaternions, should only be exchanged through USpiceTypes::Conf_*
                    // SPICE coordinate systems are Right-Handed, and Unreal Engine is Left-Handed.
                    // The USpiceTypes conversions understand this, and how to convert.
                    FQuat BodyOrientation = q.Swizzle();

                    // Set the actor to the new orientation
                    Actor->SetActorRotation(BodyOrientation);
                }
            }
        }

        return result;
    }


    //-----------------------------------------------------------------------------
    // Name: UpdateSunDirection
    // Desc:
    // Generalized directional light (sun) directional updates.
    // This keeps boilerplate scenario stuff out of the samples.
    //-----------------------------------------------------------------------------
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
            FSDistance DistanceToSun;

            auto DirectionToSun = MaxQ::Math::Unorm(DistanceToSun, r);
            FVector LightDirection = -DirectionToSun.Swizzle();

            AActor* SunActor = SunDirectionalLight.Get();
            if (SunActor)
            {
                SunActor->SetActorRotation(LightDirection.Rotation());
            }
        }

        return result;
    }


    //-----------------------------------------------------------------------------
    // Name: Log
    // Desc:
    // Common handling of result logging.
    // Keeps samples less verbose, more focused on features.
    // (Caller-provided color)
    //-----------------------------------------------------------------------------
    void Log(const FString& LogString, const FColor& Color, float DisplayTime)
    {
        UE_LOG(LogMaxQSamples, Log, TEXT("%s"), *LogString);
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, DisplayTime, Color, LogString);
        }
    }



    //-----------------------------------------------------------------------------
    // Name: Log
    // Desc:
    // Common handling of result logging.
    // (Color inferred from bSuccessCode)
    //-----------------------------------------------------------------------------
    void Log(const FString& LogString, bool bSuccessCode, float DisplayTime)
    {
        if (bSuccessCode)
        {
            UE_LOG(LogMaxQSamples, Log, TEXT("%s"), *LogString);
        }
        else
        {
            UE_LOG(LogMaxQSamples, Error, TEXT("%s"), *LogString);
        }

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, DisplayTime, bSuccessCode ? FColor::Green : FColor::Red, LogString);
        }
    }


    //-----------------------------------------------------------------------------
    // Name: Log
    // Desc:
    // Common handling of result logging.
    // (Color inferred from ResultCode)
    //-----------------------------------------------------------------------------
    void Log(const FString& LogString, ES_ResultCode ResultCode, float DisplayTime)
    {
        Log(LogString, ResultCode == ES_ResultCode::Success, DisplayTime);
    }
}


//-----------------------------------------------------------------------------
// Name: DeleteFileIfExists
// Desc: Deletes a kernel file so we can regenerate it.
//       Avoids requiring the blueprint file utils plugin...
//-----------------------------------------------------------------------------
void USampleUtilities::DeleteFileIfExists(const FString& Path)
{
    FString FilePath = MaxQSamples::AbsolutifyMaxQPathForWriting(Path);

    if (!FilePath.IsEmpty() && FPaths::ValidatePath(FilePath))
    {
        if (FPaths::FileExists(FilePath))
        {
            MaxQSamples::Log(FString::Printf(TEXT("File Exists, deleting %s"), *FilePath), FColor::Yellow);
            IFileManager& FileManager = IFileManager::Get(); FileManager.Delete(*FilePath);
        }
    }
}

//-----------------------------------------------------------------------------
// Name: GetMaxQPluginInfo
// Desc: Support for Blueprint samples.
//-----------------------------------------------------------------------------
void USampleUtilities::GetMaxQPluginInfo(FString& Info)
{
    Info = MaxQSamples::MaxQPluginInfo();
}


void USampleUtilities::AbsolutifyMaxQPathForWriting(const FString& path, FString& AbsolutePath)
{
    AbsolutePath = MaxQSamples::AbsolutifyMaxQPathForWriting(path);
}

//-----------------------------------------------------------------------------
// Name: GetMaxQPathAbsolutified
// Desc: Support for Blueprint samples.
//-----------------------------------------------------------------------------
void USampleUtilities::GetMaxQPathAbsolutified(const FString& path, FString& AbsolutePath)
{
    AbsolutePath = MaxQSamples::MaxQPathAbsolutified(path);
}


//-----------------------------------------------------------------------------
// Name: GetMaxQPathsAbsolutified
// Desc: Support for Blueprint samples.
//-----------------------------------------------------------------------------
void USampleUtilities::GetMaxQPathsAbsolutified(const TArray<FString>& paths, TArray<FString>& AbsolutePaths)
{
    AbsolutePaths = MaxQSamples::MaxQPathsAbsolutified(paths);
}


//-----------------------------------------------------------------------------
// Name: LoadKernelList
// Desc: Commonized loading of kernel file lists.  Keeps samples less verbose.
//-----------------------------------------------------------------------------
bool USampleUtilities::LoadKernelList(const FString& ListName, const TArray<FString>& KernelFiles)
{
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage = "";

    // Call MaxQ/Spice to load the list of kernels.
    Furnsh(MaxQSamples::MaxQPathsAbsolutified(KernelFiles), &ResultCode, &ErrorMessage);

    MaxQSamples::Log(FString::Printf(TEXT("Loaded %s Kernel files"), *ListName), ResultCode);
    if (ResultCode != ES_ResultCode::Success)
    {
        MaxQSamples::Log(FString::Printf(TEXT("Error: %s"), *ErrorMessage), FColor::Red);
    }

    return ResultCode == ES_ResultCode::Success;
}


//-----------------------------------------------------------------------------
// Name: InitializeTime
// Desc:
// Generalized handling of time initialization.
// (Really belongs with InitBodyScales, UpdateBodyPositions,
// UpdateBodyOrientations, and UpdateSunDirection.)
// #TODO Refactor per comment
//-----------------------------------------------------------------------------
void USampleUtilities::InitializeTime(FSamplesSolarSystemState& SolarSystemState, bool SetInitialTime)
{
    // Initialize the time, from either the current time, or the InitialiTime string.
    if (SolarSystemState.InitializeTimeToNow)
    {
        SolarSystemState.CurrentTime = Now();
        // We may want to record the actual initial time, that way we could rewind to the
        // exact same time later.
        if(SetInitialTime) SolarSystemState.InitialTime = SolarSystemState.CurrentTime.ToString();
    }
    else
    {
        SolarSystemState.CurrentTime = FSEphemerisTime::FromString(SolarSystemState.InitialTime);
    }
}



//-----------------------------------------------------------------------------
// Name: GetDefaultBasicKernels
// Desc:
// Load a list with basic kernels common to samples...
// Leap-seconds, solar system PCK/masses/default-SPK.
//-----------------------------------------------------------------------------
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


//-----------------------------------------------------------------------------
// Name: GetDefaultItrf93Kernels
// Desc:
// Load a list with basic kernels common to high-precision Earth ITRF93 cases
//-----------------------------------------------------------------------------
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



//-----------------------------------------------------------------------------
// Name: GetDefaultInsightMissionKernels
// Desc:
// Load a list with basic kernels common to an actual spaceflight mission.
// 
//-----------------------------------------------------------------------------
void USampleUtilities::GetDefaultInsightMissionKernels(TArray<FString>& InsightMissionKernels)
{
    InsightMissionKernels.Empty();

    // Specifies the relative orientations and relations of spacecraft's parts/instruments/etc
    InsightMissionKernels.Add(TEXT("NonAssetData/naif/kernels/INSIGHT/FK/insight_v05.tf"));
    
    // One SPK kernel of mission data (spacecraft positions, mission landing sight, etc)
    InsightMissionKernels.Add(TEXT("NonAssetData/naif/kernels/INSIGHT/SPK/insight_ls_ops181206_iau2000_v1.bsp"));
    
    // The specific SPK kernel used for mars & its natural satellites while planning/analyzing the mission
    InsightMissionKernels.Add(TEXT("NonAssetData/naif/kernels/INSIGHT/SPK/mar097s.bsp"));

    // This SPK kernel provides the relative position offsets of structures on the spacecraft
    InsightMissionKernels.Add(TEXT("NonAssetData/naif/kernels/INSIGHT/SPK/insight_struct_v01.bsp"));
}


/* DEPRECATED */
// telemetry will use the celestrak server.
#define CELESTRAK_URL_BASE "https://celestrak.com"

//-----------------------------------------------------------------------------
// Name: GetTelemetryFromServer
// Desc:
// Fetch telemetry data from a SatCat (satellite catalog).
// It's tied to a specific server (celestrak) so it doesn't become an overly
// generalized "swiss army knife" used for more than intended.
// Exposed to Blueprints & the Blueprint samples also use this, because
// it's not implementable in Blueprints alone without a Third Party plugin.
//-----------------------------------------------------------------------------
void USampleUtilities::GetTelemetryFromServer(FTelemetryCallback Callback, FString ObjectId, FString Format)
{
    // Example URLs
    // https://celestrak.com/NORAD/elements/gp.php?CATNR=25544&FORMAT=TLE
    // https://celestrak.com/NORAD/elements/gp.php?GROUP=STATIONS&FORMAT=TLE
    // https://celestrak.com/NORAD/elements/gp.php?NAME=MICROSAT-R&FORMAT=JSON
    // https://celestrak.com/NORAD/elements/gp.php?INTDES=2020-025&FORMAT=JSON-PRETTY
    FString uriBase = CELESTRAK_URL_BASE;
    FString uriQuery = uriBase + TEXT("/NORAD/elements/gp.php?") + ObjectId + TEXT("&FORMAT") + Format;

    // Requires inclusion of Http module.
    // (MaxQCppSamples.Build.cs: PrivateDependencyModuleNames.Add("HTTP");)
    FHttpModule& httpModule = FHttpModule::Get();

    // Create an http request
    // The request will execute asynchronously, and call us back on the Lambda below
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> pRequest = httpModule.CreateRequest();

    FString RequestContent;

    // Set up the Http calls (GET vs POST et al, content type, URL).
    pRequest->SetVerb(TEXT("GET"));
    pRequest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));

    pRequest->SetURL(uriQuery);

    // Binds a "Lambda" callback.
    // The lambda does not execute immediately.  Rather, the function we're in
    // exits, and when the HTTP response is received the lambda will be called back.
    // (The lambda in turn will execute a callback delegate so the caller can handle the data.)
    pRequest->OnProcessRequestComplete().BindLambda(
        // This is a capture list.
        // It is necessary because the function executes & returns immediately, yet
        // the lambda needs access to some of the local variables that went out of scope.
        // The callback preserves the local variables so the Lambda has access to them.
        // The 'this' pointer for the object could be preserved here, but we don't need it
        // and this is a static function anyways (no 'this' pointer to save.)
        [ObjectId, Callback](
            // Parameters the caller (http module) send into the callback.
            FHttpRequestPtr pRequest,
            FHttpResponsePtr pResponse,
            bool connectedSuccessfully) mutable {

                // Validate http called us back on the Game Thread...
                check(IsInGameThread());

                // Was the callback successful?
                if (connectedSuccessfully) {
                    // Yes!  Log it...
                    UE_LOG(LogTemp, Log, TEXT("Space-Track response: %s"), *(pResponse->GetContentAsString().Left(64)));

                    // ...and send the data to the user
                    if (Callback.IsBound())
                    {
                        Callback.Execute(true, ObjectId, pResponse->GetContentAsString());
                    }
                }
                else {
                    // No.  Mistakes were made.
                    FString Mistake;

                    switch (pRequest->GetStatus()) {
                    case EHttpRequestStatus::Failed_ConnectionError:
                        Mistake = TEXT("Connection failed.");
                    default:
                        Mistake = TEXT("Request failed.");
                    }

                    /*
                    Now on Kindle Prime:
                        Strings Of Failure, or Bits of Redemption?
                        How I learned to overcome my mistakes through the power of TCHAR Logs
                        By SamplesUtility.cpp
                    */
                    UE_LOG(LogTemp, Error, TEXT("GetTelemetryFromServer Error: %s"), *Mistake);

                    // Confess the mistake but of course don't divulge any details to anyone.
                    if (Callback.IsBound())
                    {
                        Callback.Execute(false, ObjectId, Mistake);
                    }
                }
                Callback.Unbind();
        });

    UE_LOG(LogTemp, Log, TEXT("request: %s; content:%s"), *uriBase, *uriQuery);

    pRequest->ProcessRequest();
}

#undef CELESTRAK_URL_BASE
/* /DEPRECATED */