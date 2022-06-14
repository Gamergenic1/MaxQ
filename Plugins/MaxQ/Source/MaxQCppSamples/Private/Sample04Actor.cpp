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
        pxform();
        sxform();
        sxform_xf2rav();
        GetUERotationAndAngularVelocity(OriginReferenceFrame, "MOON");

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
// Name: pxform
// Desc:
// Demonstrates pxform, getting the rotation from one frame to another
//-----------------------------------------------------------------------------

void ASample04Actor::pxform()
{
    ES_ResultCode ResultCode;
    FString ErrorMessage;

    // Body Frame (IAU_EARTH, IAU_MOON, etc)
    FString BodyFrame = TEXT("IAU_VENUS");

    // Note:  It can take a some effort to wrap your mind around how this works,
    // and that's "normal".   If you have some experience with 3D graphics it's
    // actually a bit harder, because SPICE is conceptually opposite.  (In 3D
    // graphics we usually think of transformations as moving an object from
    // one coordinate system to another, in SPICE transformations change the
    // coordinate system (camera's perspective) of a stationary object.)

    // In the call below:
    // "From" frame:  Our reference frame (inertial, non-rotating)
    // "To" frame: The planet's "fixed" (body) frame that rotates
    // We seek the orientation of the body (fixed frame) in the reference frame
    // (So we can set the rotation of a planet mesh appropriately).
    
    // How to think of this?
    // You have the planet's 3D model, all the vertices are in local space.
    // To render the planet, or to take a picture, the camera has to be in local space.
    // If you want the picture (or render) to be from any other location, you have
    // to take that camera and move it here for the picture or render, and then it
    // will be correct from that camera's perspective.
    // So... if you want to see the planet oriented correction from a distance
    // you have to move the camera "FROM" that local "TO" the planet's body/fixed frame,
    // and then render it.  So, the planet needs that rotation before rendering.
    // SO... from a distance, you need:
    // pxform
    //      FROM: Reference Frame (inertial)
    //      TO:  Planet body frame (IAU_<planet>)
    // ... And set the result to be the planet's physical rotation wrt the ref frame.

    // This may be helpful, or maybe not:
    // https://github.com/Gamergenic1/MaxQ/blob/main/ExternalTests/MaxQ/Spice/USpice/sxform.cpp

    FString From = OriginReferenceFrame.ToString();
    FString To = BodyFrame;
    FSEphemerisTime et;
    USpice::et_now(et);

    // Get the rotation matrix from the origin's frame to the Body frame.
    FSRotationMatrix m;
    USpice::pxform(ResultCode, ErrorMessage, m, et, From, To);

    Log(FString::Printf(TEXT("pxform: pxform transformation FROM %s TO %s"), *From, *To), ResultCode);

    // We have a rotation matrix, but that's not super interesting to view raw.
    Log(FString::Printf(TEXT("pxform: m2q gives rotation matrix as %s"), *m.ToString()), ResultCode);


    // We can get a quaternion...
    FSQuaternion q;
    USpice::m2q(ResultCode, ErrorMessage, m, q);
    Log(FString::Printf(TEXT("pxform: m2q gives rotation quaternion as %s"), *q.ToString()), ResultCode);
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: sxform
// Demonstrates pxform, getting the angular state transformation from one frame
// to another.
//-----------------------------------------------------------------------------

void ASample04Actor::sxform()
{

}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: sxform_xf2rav
// Desc:
// Get the angular state transformation,as a rotation and angular velocity
//-----------------------------------------------------------------------------

void ASample04Actor::sxform_xf2rav()
{

}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: GetUERotationAndAngularVelocity
// Desc:
//  Get the angular state transformation,as a rotation and angular velocity.
//  Transform them into an Unreal Engine quaternion and vector.
//-----------------------------------------------------------------------------

void ASample04Actor::GetUERotationAndAngularVelocity(const FName& ReferenceFrame, const FName& BodyName)
{

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
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Display Time: %s"), *SolarSystemState.CurrentTime.ToString()));
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

        // Get the rotation matrix from the origin's frame to the Body frame.
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
                FQuat BodyOrientation = USpiceTypes::Swazzle(q);

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