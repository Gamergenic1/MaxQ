// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "Sample06Actor.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Spice.h"

using MaxQSamples::Log;
using namespace MaxQ::Constants;


//-----------------------------------------------------------------------------
// Sample06
// Setting orientations with PCK Kernels, Reference Frames, and more
//-----------------------------------------------------------------------------
ASample06Actor::ASample06Actor()
{
    SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
    PrimaryActorTick.bCanEverTick = true;

    GetDefaultTrappistKernels(TrappistSystemKernels);

    SolarSystemState.TimeScale = 10000.0;

    BodyScale = 50.0;
    DistanceScale = 200.0;

    OriginNaifName = "TRAPPIST_1_BARYCENTER";
    OriginReferenceFrame = "GALACTIC";

    // Sun is needed to determine light direction
    SunNaifName = "TRAPPIST_1";

    PlanetFocusName = "TRAPPIST_1E";

    RelativePathToSPKFileToWrite = TEXT("NonAssetData/MaxQ/kernels/TRAPPIST-1/MaxQ-TRAPPIST_1-orbits.bsp");
    RelativePathToSPKFileToRead = RelativePathToSPKFileToWrite;

    CommentsToWrite.Emplace(TEXT("Created by MaxQ Spaceflight Toolkit for Unreal Engine."));
    CommentsToWrite.Emplace(TEXT("This file should not be used for any purpose other"));
    CommentsToWrite.Emplace(TEXT("that testing MaxQ."));

    OrbitalElements = GetTrappist1OrbitalElements();
}


//-----------------------------------------------------------------------------
// Name: BeginPlay
// Desc: Calls each of the sample/demo methods once when play begins
//-----------------------------------------------------------------------------
void ASample06Actor::BeginPlay()
{
    Super::BeginPlay();

    Log(FString::Printf(TEXT("PluginInfo: %s"), *MaxQSamples::MaxQPluginInfo()), FColor::Purple);
    Log(TEXT("Sample06: Authoring new bodies - TRAPPIST-1 System"), FColor::Blue);
    Log(TEXT("** Please see Sample04Actor.cpp for more info **"), FColor::Blue);
    Log(TEXT("See Sample06Actor (scene instance) Details Panel for time/obs/ref control buttons."), FColor::Blue);

    // init_all:  clears kernel memory and any error state.
    USpice::init_all();

    // Don't tick unless we have the kernels required to update the solar system
    bool EnableTick = USampleUtilities::LoadKernelList(TEXT("TRAPPIST System"), TrappistSystemKernels);
    if (EnableTick)
    {
        InitializeSolarSystem();
    }

    FString ReadFilePath = MaxQSamples::MaxQPathAbsolutified(RelativePathToSPKFileToRead);

    if (!ReadFilePath.IsEmpty() && FPaths::ValidatePath(ReadFilePath))
    {
        if (!FPaths::FileExists(ReadFilePath))
        {
            GenerateTrappistSPKKernel();
        }
    }

    ES_ResultCode ResultCode;
    FString ErrorMessage;
    USpice::furnsh(ResultCode, ErrorMessage, ReadFilePath);
    Log(FString::Printf(TEXT("furnsh: %s"), *MaxQSamples::MaxQPluginInfo()), ResultCode);


    PrimaryActorTick.SetTickFunctionEnable(EnableTick);
}


//-----------------------------------------------------------------------------
// Name: Tick
// Desc: 
//-----------------------------------------------------------------------------
void ASample06Actor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateSolarSystem(DeltaTime);
}



// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: InitializeSolarSystem
// Desc: Scale the Earth & Moon.
//-----------------------------------------------------------------------------

void ASample06Actor::InitializeSolarSystem()
{
    USampleUtilities::InitializeTime(SolarSystemState);
    MaxQSamples::InitBodyScales(BodyScale, SolarSystemState);
}



// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: UpdateSolarSystem
// Desc: Position and rotate the Earth and Moon.  Orient the directional light.
//-----------------------------------------------------------------------------

void ASample06Actor::UpdateSolarSystem(float DeltaTime)
{
    SolarSystemState.CurrentTime += DeltaTime * SolarSystemState.TimeScale;

    bool success = true;
    //success &= MaxQSamples::UpdateSunDirection(OriginNaifName, OriginReferenceFrame, SolarSystemState.CurrentTime, SunNaifName, SunDirectionalLight);
    success &= MaxQSamples::UpdateBodyPositions(OriginNaifName, OriginReferenceFrame, DistanceScale, SolarSystemState);
    success &= MaxQSamples::UpdateBodyOrientations(OriginReferenceFrame, SolarSystemState);

    if (!success)
    {
        // Restart time...
        Restart();
    }

    if (GEngine)
    {
        double UE_Units_Per_KM = 100 * 1000.;
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Time Scale: %f x"), SolarSystemState.TimeScale.AsSeconds()));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Scale PLANETS/MOON : 1/%d"), (int)(BodyScale * UE_Units_Per_KM)));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Scale Solar System Distances : 1/%d"), (int)(DistanceScale * UE_Units_Per_KM)));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Display Time: %s"), *SolarSystemState.CurrentTime.ToString()));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Origin Reference Frame: %s"), *OriginReferenceFrame.ToString()));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Origin Observer Naif Name: %s"), *OriginNaifName.ToString()));
    }
}


//-----------------------------------------------------------------------------
// Name: GetDefaultTrappistKernels
// Desc:
// Load a list with basic kernels common to an actual spaceflight mission.
// 
//-----------------------------------------------------------------------------
void ASample06Actor::GetDefaultTrappistKernels(TArray<FString>& TrappistSystemKernelsArray)
{
    TrappistSystemKernelsArray.Empty();

    // New hand-created text kernel for Trappist system.
    // Created in a text editor.
    // This is a frames kernel, which establishes the structure of the system planet names, ID's etc
    TrappistSystemKernelsArray.Add(TEXT("NonAssetData/MaxQ/kernels/TRAPPIST-1/MaxQ-TRAPPIST_1-fk.tf"));

    // Also created in a text editor.
    // This is a PCK kernel file, which contains information about the orientation and rotation
    // of the planets.   It also contains the Mass Constant for each.
    TrappistSystemKernelsArray.Add(TEXT("NonAssetData/MaxQ/kernels/TRAPPIST-1/MaxQ-TRAPPIST_1-pck.tpc"));

    // This is a binary SPK kernel file (ephemeris position).
    // This SPK affixes the star to the system barycenter, and all planets to their own
    // subsystem barycenter (TRAPPIST_1B -> TRAPPIST_1B_BARYCENTER, etc.)
    // It was created with the NAIF 'Pinpoint' utility, which exists for this purpose.
    //
    // See:
    // https://naif.jpl.nasa.gov/pub/naif/utilities/PC_Linux_64bit/pinpoint.ug
    //
    // Pinpoint can be downloaded here (Windows version, MacOS and Linux are available too):
    // https://naif.jpl.nasa.gov/naif/utilities_PC_Windows_64bit.html
    //
    // The file used to generate the SPK:
    // \MaxQ\Content\NonAssetData\MaxQ\site_defs\trappist-1-barycenters.defs
    // (See notes in the .defs file, open it with a text editor.)
    TrappistSystemKernelsArray.Add(TEXT("NonAssetData/MaxQ/kernels/TRAPPIST-1/MaxQ-TRAPPIST_1-barycenters.bsp"));

    // The same leap seconds file we always use... No need to make a new one for this.
    // (although, we could.)
    TrappistSystemKernelsArray.Add(TEXT("NonAssetData/naif/kernels/Generic/LSK/naif0012.tls"));
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: GenerateTrappistSPKKernel
// Desc: Generate an SPK file for the planet positions...
//-----------------------------------------------------------------------------

void ASample06Actor::GenerateTrappistSPKKernel()
{
    FString WriteFilePath = MaxQSamples::AbsolutifyMaxQPathForWriting(RelativePathToSPKFileToWrite);

    if (!WriteFilePath.IsEmpty() && FPaths::ValidatePath(WriteFilePath))
    {
        if (FPaths::FileExists(WriteFilePath))
        {
            MaxQSamples::Log(FString::Printf(TEXT("File Exists, deleting %s"), *WriteFilePath), FColor::Yellow);
            IFileManager& FileManager = IFileManager::Get(); FileManager.Delete(*WriteFilePath);
        }

        // Initialize SPICE, load relevant kernels
        USpice::init_all();
        if (!USampleUtilities::LoadKernelList(TEXT("TRAPPIST System"), TrappistSystemKernels))
        {
            MaxQSamples::Log(TEXT("Kernel load failed"), FColor::Red);
            return;
        }

        ES_ResultCode ResultCode;
        FString ErrorMessage;
        int Handle{ 0 };
        USpice::spkopn(ResultCode, ErrorMessage, WriteFilePath, FPaths::GetCleanFilename(WriteFilePath), CommentsToWrite.Num() * 128, Handle);

        MaxQSamples::Log(FString::Printf(TEXT("spkopn file %s"), *WriteFilePath, ResultCode));

        if (ResultCode == ES_ResultCode::Success)
        {
            USpice::dafac(ResultCode, ErrorMessage, Handle, CommentsToWrite);
            MaxQSamples::Log(FString::Printf(TEXT("dafac result: %s"), ErrorMessage.IsEmpty() ? TEXT("OK") : *ErrorMessage, ResultCode));
        }

        FSEphemerisTime Start;
        USpice::et_now(Start);
        FSEphemerisTime Stop = Start + 30 * FSEphemerisPeriod::OneDay;

        ES_FoundCode FoundCode;
        int Center = 0;
        USpice::bods2c(FoundCode, Center, TEXT("TRAPPIST_1"));

        if (FoundCode != ES_FoundCode::Found)
        {
            MaxQSamples::Log(TEXT("Could not look up TRAPPIST_1"), FColor::Red);
            ResultCode = ES_ResultCode::Error;
        }

        if (ResultCode == ES_ResultCode::Success)
        {
            for (const auto& [BodyName, ConicElements] : OrbitalElements)
            {
                int Body = 0;
                USpice::bods2c(FoundCode, Body, BodyName);
                if (FoundCode != ES_FoundCode::Found)
                {
                    MaxQSamples::Log(FString::Printf(TEXT("Could not look up %s"), *BodyName), FColor::Red);
                    ResultCode = ES_ResultCode::Error;
                }

                FString segid;
                TArray<FSPKType5Observation> States{};

                for (int i = 0; i < 30; ++i)
                {
                    FSPKType5Observation Observation;
                    Observation.et = Start + i * FSEphemerisPeriod::OneDay;
                    USpice::conics(ResultCode, ErrorMessage, ConicElements, Observation.et, Observation.state);
                    if (ResultCode == ES_ResultCode::Success)
                    {
                        States.Add(Observation);
                    }
                    else
                    {
                        break;
                    }
                }

                if (ResultCode == ES_ResultCode::Success)
                {
                    USpice::spkw05(ResultCode, ErrorMessage, Handle, Body, Center, MaxQ::Constants::GALACTIC, Start, Stop, TEXT("TEST SEGMENT"), ConicElements.GravitationalParameter, States);
                }
            }

            USpice::spkcls(ResultCode, ErrorMessage, Handle);

            if (ResultCode != ES_ResultCode::Success)
            {
                MaxQSamples::Log(FString::Printf(TEXT("spkcls file %s"), *WriteFilePath, ResultCode));
            }
        }
    }
}


//-----------------------------------------------------------------------------



void ASample06Actor::VeryFastSpeed()
{
    NormalSpeed();
    FasterSpeed();
    FasterSpeed();
    FasterSpeed();
    FasterSpeed();
    FasterSpeed();
}

void ASample06Actor::FasterSpeed()
{
    SolarSystemState.TimeScale *= 10.;
}

void ASample06Actor::SlowerSpeed()
{
    SolarSystemState.TimeScale *= 0.1;
}

void ASample06Actor::NormalSpeed()
{
    SolarSystemState.TimeScale = 1;
}

void ASample06Actor::GoToNow()
{
    USpice::et_now(SolarSystemState.CurrentTime);
    NormalSpeed();
}

void ASample06Actor::Restart()
{
    USampleUtilities::InitializeTime(SolarSystemState, false);
}


namespace MaxQCppSamples::Data
{
    //-----------------------------------------------------------------------------
    // Hardcoded TRAPPIST-1 System Data
    //-----------------------------------------------------------------------------

    // Values for e, sma, i obtained from:
    // https://en.wikipedia.org/wiki/TRAPPIST-1
    constexpr auto TRAPPIST_1_GM = 1.19175771158E+10;
    constexpr auto TRAPPIST_1B_e = 0.00622;
    constexpr auto TRAPPIST_1C_e = 0.00654;
    constexpr auto TRAPPIST_1D_e = 0.00837;
    constexpr auto TRAPPIST_1E_e = 0.00510;
    constexpr auto TRAPPIST_1F_e = 0.01007;
    constexpr auto TRAPPIST_1G_e = 0.00208;
    constexpr auto TRAPPIST_1H_e = 0.00567;

    // We could (should?) load the kernel files & get the value from there...
    static const FSMassConstant Trappist1GM {TRAPPIST_1_GM};

    constexpr double sma2rp(double e, double sma)
    {
        constexpr auto au2km = 1.495978707E8;
        return (1. - e) * sma * au2km;
    }

    static const TMap<FString, FSConicElements> Trappist1OrbitalElements
    {
        TMap<FString,FSConicElements>::ElementType
        {
            TEXT("TRAPPIST_1B"),
            FSConicElements
            {
                sma2rp(TRAPPIST_1B_e, 0.01154), // PerifocalDistance
                TRAPPIST_1B_e,                  // Eccentricity
                FSAngle::FromDegrees(89.728),   // Inclination
                FSAngle::FromDegrees(0),        // LongitudeOfAscendingNode
                FSAngle::FromDegrees(0),        // ArgumentOfPeriapse
                FSAngle::FromDegrees(0),        // MeanAnomalyAtEpoch
                FSEphemerisTime::J2000,         // Epoch
                Trappist1GM                     // GravitationalParameter
            }
        },
        TMap<FString,FSConicElements>::ElementType
        {
            TEXT("TRAPPIST_1C"),
            FSConicElements
            {
                sma2rp(TRAPPIST_1C_e, 0.01580), // PerifocalDistance
                TRAPPIST_1C_e,                  // Eccentricity
                FSAngle::FromDegrees(89.778),   // Inclination
                FSAngle::FromDegrees(0),        // LongitudeOfAscendingNode
                FSAngle::FromDegrees(0),        // ArgumentOfPeriapse
                FSAngle::FromDegrees(0),        // MeanAnomalyAtEpoch
                FSEphemerisTime::J2000,         // Epoch
                Trappist1GM                     // GravitationalParameter
            }
        },
        TMap<FString,FSConicElements>::ElementType
        {
            TEXT("TRAPPIST_1D"),
            FSConicElements
            {
                sma2rp(TRAPPIST_1D_e, 0.02227), // PerifocalDistance
                TRAPPIST_1D_e,                  // Eccentricity
                FSAngle::FromDegrees(89.896),   // Inclination
                FSAngle::FromDegrees(0),        // LongitudeOfAscendingNode
                FSAngle::FromDegrees(0),        // ArgumentOfPeriapse
                FSAngle::FromDegrees(0),        // MeanAnomalyAtEpoch
                FSEphemerisTime::J2000,         // Epoch
                Trappist1GM                     // GravitationalParameter
            }
        },
        TMap<FString,FSConicElements>::ElementType
        {
            TEXT("TRAPPIST_1E"),
            FSConicElements
            {
                sma2rp(TRAPPIST_1E_e, 0.02925), // PerifocalDistance
                TRAPPIST_1E_e,                  // Eccentricity
                FSAngle::FromDegrees(89.793),   // Inclination
                FSAngle::FromDegrees(0),        // LongitudeOfAscendingNode
                FSAngle::FromDegrees(0),        // ArgumentOfPeriapse
                FSAngle::FromDegrees(0),        // MeanAnomalyAtEpoch
                FSEphemerisTime::J2000,         // Epoch
                Trappist1GM                     // GravitationalParameter
            }
        },
        TMap<FString,FSConicElements>::ElementType
        {
            TEXT("TRAPPIST_1F"),
            FSConicElements
            {
                sma2rp(TRAPPIST_1F_e, 0.03849), // PerifocalDistance
                TRAPPIST_1F_e,                  // Eccentricity
                FSAngle::FromDegrees(89.740),   // Inclination
                FSAngle::FromDegrees(0),        // LongitudeOfAscendingNode
                FSAngle::FromDegrees(0),        // ArgumentOfPeriapse
                FSAngle::FromDegrees(0),        // MeanAnomalyAtEpoch
                FSEphemerisTime::J2000,         // Epoch
                Trappist1GM                     // GravitationalParameter
            }
        },
        TMap<FString,FSConicElements>::ElementType
        {
            TEXT("TRAPPIST_1G"),
            FSConicElements
            {
                sma2rp(TRAPPIST_1G_e, 0.04683), // PerifocalDistance
                TRAPPIST_1G_e,                  // Eccentricity
                FSAngle::FromDegrees(89.742),   // Inclination
                FSAngle::FromDegrees(0),        // LongitudeOfAscendingNode
                FSAngle::FromDegrees(0),        // ArgumentOfPeriapse
                FSAngle::FromDegrees(0),        // MeanAnomalyAtEpoch
                FSEphemerisTime::J2000,         // Epoch
                Trappist1GM                     // GravitationalParameter
            }
        },
        TMap<FString,FSConicElements>::ElementType
        {
            TEXT("TRAPPIST_1H"),
            FSConicElements
            {
                sma2rp(TRAPPIST_1H_e, 0.06189), // PerifocalDistance
                TRAPPIST_1H_e,                  // Eccentricity
                FSAngle::FromDegrees(89.805),   // Inclination
                FSAngle::FromDegrees(0),        // LongitudeOfAscendingNode
                FSAngle::FromDegrees(0),        // ArgumentOfPeriapse
                FSAngle::FromDegrees(0),        // MeanAnomalyAtEpoch
                FSEphemerisTime::J2000,         // Epoch
                Trappist1GM                     // GravitationalParameter
            }
        }
    };
}

const TMap<FString, FSConicElements>& ASample06Actor::GetTrappist1OrbitalElements()
{
    return MaxQCppSamples::Data::Trappist1OrbitalElements;
}