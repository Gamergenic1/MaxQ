// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "Sample04Actor.h"
#include "SpiceTypes.h"
#include "Spice.h"

using MaxQSamples::Log;

//-----------------------------------------------------------------------------
// Sample04
// Setting orientations with PCK Kernels, Reference Frames, and more
//-----------------------------------------------------------------------------
ASample04Actor::ASample04Actor()
{
    SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
    PrimaryActorTick.bCanEverTick = true;

    USampleUtilities::GetDefaultBasicKernels(BasicKernels);

    SolarSystemState.TimeScale = 10000.0;

    BodyScale = 50.0;
    DistanceScale = 200.0;

    // This is the coordinate system center relative to SPICE
    // (EMB = "Earth-Moon Barycenter")
    OriginNaifName = FName("EMB");
    // This is the UE coordinate system orientation relative to SPICE
    OriginReferenceFrame = FName("ECLIPJ2000");

    // Sun is needed to determine light direction
    SunNaifName = FName("SUN");
    
    PlanetFocusName = FName("EARTH");
    
    // In Spice "Satellite" = Natural Satellite, like MOON.
    SatelliteName = FName("MOON");

    // Note that SolarSystemBodyMap will be serialized with Moon and Earth
    // (In this case they won't be dynamically discovered).

    // The sun is handled separately, since it's just for directional light orientation
}


//-----------------------------------------------------------------------------
// Name: BeginPlay
// Desc: Calls each of the sample/demo methods once when play begins
//-----------------------------------------------------------------------------
void ASample04Actor::BeginPlay()
{
    Super::BeginPlay();

    Log(FString::Printf(TEXT("PluginInfo: %s"), *MaxQSamples::MaxQPluginInfo()), FColor::Purple);
    Log(TEXT("Sample04: Setting orientations with PCK Kernels, Reference Frames, and more"), FColor::Blue);
    Log(TEXT("** Please see Sample04Actor.cpp for more info **"), FColor::Blue);
    Log(TEXT("See Sample04Actor (scene instance) Details Panel for time/obs/ref control buttons."), FColor::Blue);

    // init_all:  clears kernel memory and any error state.
    USpice::init_all();

    // Don't tick unless we have the kernels required to update the solar system
    bool EnableTick = USampleUtilities::LoadKernelList(TEXT("Basic"), BasicKernels);
    if (EnableTick)
    {
        InitializeSolarSystem();
    }

    PrimaryActorTick.SetTickFunctionEnable(EnableTick);
}


//-----------------------------------------------------------------------------
// Name: Tick
// Desc: 
//-----------------------------------------------------------------------------
void ASample04Actor::Tick(float DeltaTime)
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

void ASample04Actor::InitializeSolarSystem()
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

void ASample04Actor::UpdateSolarSystem(float DeltaTime)
{
    SolarSystemState.CurrentTime += DeltaTime * SolarSystemState.TimeScale;

    bool success = true;
    success &= MaxQSamples::UpdateSunDirection(OriginNaifName, OriginReferenceFrame, SolarSystemState.CurrentTime, SunNaifName, SunDirectionalLight);
    success &= MaxQSamples::UpdateBodyPositions(OriginNaifName, OriginReferenceFrame, DistanceScale, SolarSystemState);
    success &= UpdateBodyOrientations();

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
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Display Time: %s"), *USpiceTypes::Conv_SEpheremisTimeToString(SolarSystemState.CurrentTime)));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Origin Reference Frame: %s"), *OriginReferenceFrame.ToString()));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Origin Observer Naif Name: %s"), *OriginNaifName.ToString()));
    }
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: UpdateBodyOrientations
// Desc: This is what you came for
//-----------------------------------------------------------------------------

bool ASample04Actor::UpdateBodyOrientations()
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
            if(result)
            {
                // IMPORTANT NOTE:
                // Positional data (vectors, quaternions, should only be exchanged through USpiceTypes::Conf_*
                // SPICE coordinate systems are Right-Handed, and Unreal Engine is Left-Handed.
                // The USpiceTypes conversions understand this, and how to convert.
                FQuat BodyOrientation = USpiceTypes::Conv_SQuaternionToQuat(q);

                Actor->SetActorRotation(BodyOrientation);
            }
        }
    }

    return result;
}



//-----------------------------------------------------------------------------



void ASample04Actor::VeryFastSpeed()
{
    NormalSpeed();
    FasterSpeed();
    FasterSpeed();
    FasterSpeed();
    FasterSpeed();
    FasterSpeed();
}

void ASample04Actor::FasterSpeed()
{
    SolarSystemState.TimeScale *= 10.;
}

void ASample04Actor::SlowerSpeed()
{
    SolarSystemState.TimeScale *= 0.1;
}

void ASample04Actor::NormalSpeed()
{
    SolarSystemState.TimeScale = 1;
}

void ASample04Actor::GoToNow()
{
    USpice::et_now(SolarSystemState.CurrentTime);
    NormalSpeed();
}

void ASample04Actor::Restart()
{
    USampleUtilities::InitializeTime(SolarSystemState, false);
}