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

    BodyScale = 100.0;
    DistanceScale = 100.0;

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
    bool EnableTick;
    if (EnableTick = USampleUtilities::LoadKernelList(TEXT("Basic"), BasicKernels))
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
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage = "";

    USampleUtilities::InitializeTime(SolarSystemState);

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

                    FVector ScenegraphDiameter = 2 * ScenegraphRadii;

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
    success &= UpdateSunDirection();
    success &= UpdateBodyPositions();
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
// Name: UpdateSunDirection
// Desc: Aim the sun's directional light
//-----------------------------------------------------------------------------

bool ASample04Actor::UpdateSunDirection()
{
    FSDistanceVector r;
    FSEphemerisPeriod lt;

    ES_ResultCode ResultCode;
    FString ErrorMessage;

    // When do we want it?   (time: now)
    FSEphemerisTime et = SolarSystemState.CurrentTime;

    // Call SPICE, get the position in rectangular coordinates...
    USpice::spkpos(ResultCode, ErrorMessage, et, r, lt, SunNaifName.ToString(), OriginNaifName.ToString(), OriginReferenceFrame.ToString());

    bool result = (ResultCode == ES_ResultCode::Success);

    if (result)
    {
        // We assume we want to point the sun at the origin...
        FSDimensionlessVector DirectionToSun;
        FSDistance DistanceToSun;

        USpice::unorm_distance(r, DirectionToSun, DistanceToSun);

        FVector LightDirection = -USpiceTypes::Conv_SDimensionlessToVector(DirectionToSun);

        AActor* SunActor = SunDirectionalLight.Get();

        if (SunActor)
        {
            SunActor->SetActorRotation(LightDirection.Rotation());
        }
    }

    return result;
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: UpdateBodyPositions
// Desc: Position and rotate the Earth and Moon
//-----------------------------------------------------------------------------

bool ASample04Actor::UpdateBodyPositions()
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
                FVector BodyLocation = USpiceTypes::Conv_SDistanceVectorToVector(r);

                // Scale and set the body location
                BodyLocation /= DistanceScale;
                Actor->SetActorLocation(BodyLocation);

                if (GEngine)
                {
                    GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("%s r=: %s kilometers"), *BodyPair.Key.ToString(), *USpiceTypes::Conv_SDistanceToString(r.Magnitude())));
                }
            }
        }
    }

    return result;
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: UpdateBodyOrientations
// Desc: This is what you came for
//-----------------------------------------------------------------------------

bool ASample04Actor::UpdateBodyOrientations()
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