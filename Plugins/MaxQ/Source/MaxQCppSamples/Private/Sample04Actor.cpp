// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "Sample04Actor.h"
#include "Spice.h"

using MaxQSamples::Log;
using namespace MaxQ::Data;
using namespace MaxQ::Core;
using namespace MaxQ::Constants;
using namespace MaxQ::Math;



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
    OriginNaifName = Name_EMB;
    // This is the UE coordinate system orientation relative to SPICE
    OriginReferenceFrame = Name_ECLIPJ2000;

    // Sun is needed to determine light direction
    SunNaifName = Name_SUN;
    
    PlanetFocusName = Name_EARTH;
    
    // In Spice "Satellite" = Natural Satellite, like MOON.
    SatelliteName = Name_MOON;

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
        FSEphemerisTime et;
        USpice::et_now(et);
        sxform(et);
        sxform_xf2rav(et);
        GetUERotationAndAngularVelocity(et, OriginReferenceFrame, Name_MOON);

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
    GetUERotationAndAngularVelocity(SolarSystemState.CurrentTime, OriginReferenceFrame, Name_EARTH, true);
}



// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: pxform
// Desc:
// Compute a body's orientation
//-----------------------------------------------------------------------------

void ASample04Actor::pxform()
{
    ES_ResultCode ResultCode;
    FString ErrorMessage;

    // Body Frame (IAU_EARTH, IAU_MOON, etc)
    FString BodyFrame = IAU_VENUS;

    FSEphemerisTime et;
    USpice::et_now(et);

    // Note:  It can take a some effort to wrap your mind around how this works,
    // and that's "normal".
    // 
    // In the call below:
    // "From" frame:  The planet's "fixed" (body) frame that rotates
    // "To" frame: The frame we're watching in (observer's reference frame)
    //
    // We seek the orientation of the body (fixed frame) in the observer frame
    // (So we can set the rotation of a planet mesh appropriately).

    // How to think of this?
    // 
    // SO... from a distance, you need:
    // pxform
    //      FROM: Planet body frame (IAU_<planet>)
    //      TO:  Observer reference frame (here, ECLIPJ2000, aligned with the ecliptic plane)
    // ... And set the result to be the planet's physical rotation wrt the ref frame.

    // This may be helpful, or maybe not:
    // https://github.com/Gamergenic1/MaxQ/blob/main/ExternalTests/MaxQ/Spice/USpice/sxform.cpp

    FString From = BodyFrame;
    FString To = OriginReferenceFrame.ToString();

    // Get the rotation matrix from the origin's frame to the Body frame.
    FSRotationMatrix m;
    USpice::pxform(ResultCode, ErrorMessage, m, et, From, To);

    Log(FString::Printf(TEXT("pxform: pxform transformation FROM %s TO %s"), *From, *To), ResultCode);

    // We can get a quaternion... which can be used to set an actor rotation.
    FSQuaternion q;
    USpice::m2q(ResultCode, ErrorMessage, m, q);
    Log(FString::Printf(TEXT("pxform: m2q gives rotation quaternion as %s"), *q.ToString()), ResultCode, 60.f);
}

// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: sxform
// Desc:
// Demonstrates sxform, getting the angular state transformation from one frame
// to another.
// The State Transformation Matrix can be used to transform a state vector
// from one observer's coordinate system to another.
// In this case, we want to see the Earth...
// For a camera pointing at earth, move the observer position out to an
// inertial frame (ECLIPJ2000, for instance).
// And, for a state vector stationary in earth's frame... what is the new
// state vector in the inertial frame?
//-----------------------------------------------------------------------------

void ASample04Actor::sxform(const FSEphemerisTime& et)
{
    ES_ResultCode ResultCode;
    FString ErrorMessage;

    // Body "Fixed" Frame (IAU_EARTH, IAU_MOON, etc)
    FString BodyFrame = MaxQ::Constants::IAU_EARTH;

    // As with pxform,
    // FROM:  Body Frame
    // TO:  Observer's frame
    FString From = BodyFrame;
    FString To = OriginReferenceFrame.ToString();

    // Get the state vector transformation from the body frame to the observer's frame.
    FSStateTransform StateTransform;
    USpice::sxform(ResultCode, ErrorMessage, StateTransform, et, From, To);

    // We can transform an arbitrary state vector...
    FSStateVector StateInEarthsFixedFrame(FSDistanceVector(6700,0,0), FSVelocityVector());
    FSStateVector StateInObserverFrame = StateTransform * StateInEarthsFixedFrame;

    // Print the results
    Log(FString::Printf(TEXT("sxform: random state in Earth's Fixed Frame=%s"), *StateInEarthsFixedFrame.ToString()));
    Log(FString::Printf(TEXT("sxform: random state in Observer Frame=%s"), *StateInObserverFrame.ToString()));
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: sxform_xf2rav
// Desc:
// Get the angular state transformation, as a rotation and angular velocity
//-----------------------------------------------------------------------------

void ASample04Actor::sxform_xf2rav(const FSEphemerisTime& et)
{
    ES_ResultCode ResultCode;
    FString ErrorMessage;

    // Body "Fixed" Frame (IAU_EARTH, IAU_MOON, etc)
    FString BodyFrame = MaxQ::Constants::IAU_EARTH;

    // This is difficult to explain.  But,... study this a bit:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/xf2rav_c.html
    // 
    /*
        av          is the angular velocity of the transformation.
                    In other words, if `p' is the position of a fixed
                    point in FRAME2, then from the point of view of
                    FRAME1, `p' rotates (in a right handed sense) about
                    an axis parallel to `av'. Moreover the rate of rotation
                    in radians per unit time is given by the length of
                    `av'.

                    More formally, the velocity `v' of `p' in FRAME1 is
                    given by
                                        T
                        v  = av x ( rot  * p )

                    The components of `av' are given relative to FRAME1.
    */
    // Angular velocity is the A.V. of frame2, from frame1, relative to frame1.
    // 
    // Oh, snap.
    // That means if we do as above, we'll have the A.V. of the inertial frame
    // in the body frame, with respect to the body frame.
    // That is not what we want!!  Strike that!  Reverse it!
    // 
    // So, we're going to get the transform oppositely and save the Angular
    // velocity vector.
    // 
    // Then, we're going to make up for it by inverting the rotation matrix
    // that we get, so we can get proper orientation as before.
    // In the case of rotation, two "wrongs" do make "right"!
    // (Note the opposite order, compared to above!)
    FString From = OriginReferenceFrame.ToString();
    FString To = BodyFrame;

    // Get the state transform from the inertial frame to the body frame.
    FSStateTransform StateTransform;
    USpice::sxform(ResultCode, ErrorMessage, StateTransform, et, From, To);

    // Separate the state transform into a rotation matrix and an angular velocity.
    FSRotationMatrix rotationMatrix;
    FSAngularVelocity angularVelocity;
    USpice::xf2rav(StateTransform, rotationMatrix, angularVelocity);

    // Cool. cool.  cool.  The angular velocity is exactly as we want it.
    // It's the angular velocity of earth, in the observer's frame, with respect to
    // the observer's frame (ECLIPJ2000).

    // We have to invert the rotation matrix to get the equivalent rotation as before...
    USpice::xpose(rotationMatrix, rotationMatrix);

    // We can get the rotation as a quaternion...
    FSQuaternion q;
    USpice::m2q(ResultCode, ErrorMessage, rotationMatrix, q);
    Log(FString::Printf(TEXT("sxform_xf2rav: q=%s, av=%s"), *q.ToString(), *angularVelocity.ToString()), FColor::Orange, 0.f);

    // At this point, we could swizzle the rotation to the UE coordinate system and place a mesh.
    // And, we could swizzle the angular velocity vector, and set it to the Physics angular velocity,
    // If we were about to start up some UE physics on whatever it is.
    // see:
    // UPrimitiveComponent::SetPhysicsAngularVelocity
    // This will be important later when we have spacecraft flying around doing UE physics and
    // we need to reorient the coordinate system differently around a planet etc.
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: GetUERotationAndAngularVelocity
// Desc:
// Get the angular state transformation,as a rotation and angular velocity.
// Transform them into an Unreal Engine quaternion and vector.
//-----------------------------------------------------------------------------

void ASample04Actor::GetUERotationAndAngularVelocity(const FSEphemerisTime& et, const FName& ReferenceFrame, const FName& BodyName, bool DontLog)
{
    // (Re) demonstrate how to get a rotation and angular velocity of the fixed
    // frame with respect to the observer's frame.
#pragma region ComputeRHSRotation
    // Same drill as sxform_sf2rav
    ES_ResultCode ResultCode;
    FString ErrorMessage;

    FString BodyFrame = TEXT("IAU_") + BodyName.ToString();
    FString From = ReferenceFrame.ToString();
    FString To = BodyFrame;

    // Get the state transform from the observer's frame to the body frame...
    FSStateTransform StateTransform;
    USpice::sxform(ResultCode, ErrorMessage, StateTransform, et, From, To);

    // Get the rotation and angular velocity from the state transform
    FSRotationMatrix rotationMatrix;
    FSAngularVelocity angularVelocity;
    FSQuaternion q;

    if (ResultCode == ES_ResultCode::Success)
    {
        USpice::xf2rav(StateTransform, rotationMatrix, angularVelocity);

        // We have to invert the rotation matrix... again
        USpice::xpose(rotationMatrix, rotationMatrix);

        // We can get a quaternion... again
        USpice::m2q(ResultCode, ErrorMessage, rotationMatrix, q);
    }
#pragma endregion ComputeRHSRotation

    // Demonstrate how to decompose the rotation matrix into:
    // North Pole:
    //    Right Ascension
    //    Declination
    // Prime Meridian
    //    Rotation around north pole
#pragma region NorthPoleAndPrimeMeridian
    if (ResultCode == ES_ResultCode::Success)
    {
        // Get the north pole Right-Ascension and Declination, and the prime meridian rotation around it
        // (just for kicks)
        // See:
        // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/frames.html#Example%20of%20an%20Euler%20Frame
        /*
        The 3x3 transformation matrix M defined by the angles is

           M = [angle_1]   [angle_2]   [angle_3]
                        3           1           3
        Vectors are mapped from the J2000 base frame to the IAU_MARS frame via left multiplication by M.
        The relationship of these Euler angles to RA/Dec/PM for the J2000-to-IAU Mars body-fixed transformation is as follows:

           angle_1 is        PM  * (radians/degree)
           angle_2 is pi/2 - Dec * (radians/degree)
           angle_3 is pi/2 + RA  * (radians/degree)
        Since when we define the IAU_MARS_EULER frame we're defining the *inverse* of the above transformation, the angles for our Euler frame definition are reversed and the signs negated:
           angle_1 is -pi/2 - RA  * (radians/degree)
           angle_2 is -pi/2 + Dec * (radians/degree)
           angle_3 is       - PM  * (radians/degree)
        */
        // (But, swap angle1 and angle3 as the order was given opposite of how m2eul works)

        FSEulerAngles eulers;
        USpice::m2eul(ResultCode, ErrorMessage, eulers, rotationMatrix, ES_Axis::Z, ES_Axis::X, ES_Axis::Z);

        FSAngle PM = -eulers.angle1;
        FSAngle Dec = FSAngle::halfpi + eulers.angle2;
        FSAngle RA = -eulers.angle3 - FSAngle::halfpi;

        PM = FSAngle::FromRadians(USpiceTypes::normalizeZeroToTwoPi(PM.AsRadians()));

        if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Orange, *FString::Printf(TEXT("North Pole RADec: %s; Prime Meridian Rotation: %s (Frame: %s)"), *USpiceTypes::FormatRADec(RA, Dec), *PM.ToString(), *ReferenceFrame.ToString()));
    }
#pragma endregion NorthPoleAndPrimeMeridian

    // Demonstrate how to "swizzle" the rotation and angular velocity
    // From:  MaxQ/SPICE Right-Handed Coordinate System (RHS)
    // To:  Unreal Engine Left-handed Coordinate System (LHS)
#pragma region SwizzleToUnrealEngineLHSCoords
    // Now, we can "Swizzle" the result into UE coordinates.

    // Normalize the angular velocity so it's not just an itsy bitsy teeny tiny number
    FQuat UnrealEngineRotation = q.Swizzle();
    FVector UnrealEngineAngularVelocity = angularVelocity.Swizzle();
    double AVMagnitude = UnrealEngineAngularVelocity.Length();
    UnrealEngineAngularVelocity.Normalize(0.);

    // Convert the quaternion into something more intuitive, like an axis/angle
    FVector RotationAxis;
    double RotationAngle;
    UnrealEngineRotation.ToAxisAndAngle(RotationAxis, RotationAngle);
    FString UERotation = FString::Printf(TEXT("{%f (%s)"), RotationAngle, *RotationAxis.ToString());

    // Either log only to the screen or log to screen+log.
    if (DontLog && GEngine)
    {
        double UE_Units_Per_KM = 100 * 1000.;
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("GetUERotationAndAngularVelocity: Unreal Engine (LHS coords) q=%s, av={%f, (%s)}"), *UERotation, AVMagnitude, *UnrealEngineAngularVelocity.ToString()));
    }
    else
    {
        Log(FString::Printf(TEXT("GetUERotationAndAngularVelocity: Unreal Engine Rotation/Angular-Velocity q=%s, av={%f, (%s)}"), *UERotation, AVMagnitude, *UnrealEngineAngularVelocity.ToString()), ResultCode);
    }
#pragma endregion SwizzleToUnrealEngineLHSCoords
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
// Desc:
// This is what you came for
// Demonstrate orienting the earth and moon at a given time.
//-----------------------------------------------------------------------------

bool ASample04Actor::UpdateBodyOrientations()
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

        // Get the rotation matrix from the origin's frame to the Body frame.
        USpice::pxform(ResultCode, ErrorMessage, m, et, BodyFrame, OriginReferenceFrame.ToString());

        result &= (ResultCode == ES_ResultCode::Success);

        AActor* Actor = BodyActor.Get();
        if (Actor && result)
        {
            // Convert the Rotation Matrix into a SPICE Quaternion
            FSQuaternion q;
            USpice::m2q(ResultCode, ErrorMessage, m, q);

            if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("UpdateBodyOrientations (%s): m2q gives rotation quaternion as %s"), *BodyFrame, *q.ToString()));

            // (m2q can't fail unless 'm' isn't a rotation matrix... But if pxform succeeded, it will be)
            result &= (ResultCode == ES_ResultCode::Success);

            // Now, convert the SPICE Quaternion into an Unreal Engine Quaternion
            if(result)
            {
                // IMPORTANT NOTE:
                // Positional data (vectors, quaternions, should only be exchanged through USpiceTypes::Conf_*
                // SPICE coordinate systems are Right-Handed, and Unreal Engine is Left-Handed.
                // The USpiceTypes conversions understand this, and how to convert.
                FQuat BodyOrientation = q.Swizzle();

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