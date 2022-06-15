// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "Sample05Actor.h"
#include "SpiceTypes.h"
#include "Spice.h"
#include "SampleUtilities.h"
#include "Sample05TelemetryActor.h"
#include "SpiceOrbits.h"

using MaxQSamples::Log;
using namespace MaxQ::Constants;

/* THIS SAMPLE IS IN PROGRESS */

/* ****************************************************************************
*  This tutorial is only an interim version.
*  ***************************************************************************/


//-----------------------------------------------------------------------------
// Sample05
// Kepler Orbits, TLE's, and more...
//-----------------------------------------------------------------------------
ASample05Actor::ASample05Actor()
{
    SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));

    USampleUtilities::GetDefaultBasicKernels(BasicKernels);

    // We need to add geophysical.ker to get physical constants of Earth needed
    // to propagate TLEs.
    BasicKernels.Add(TEXT("NonAssetData/naif/kernels/Generic/PCK/geophysical.ker"));

    TelemetryObjectId = TEXT("GROUP=STATIONS");

    OriginNaifName = Name_EARTH;
    OriginReferenceFrame = Name_J2000;
    SunNaifName = Name_SUN;
    DistanceScale = 25.0;
    SolarSystemState.TimeScale = 1.0;

    PrimaryActorTick.bCanEverTick = true;
}


//-----------------------------------------------------------------------------
// Name: BeginPlay
// Desc: Calls each of the sample/demo methods once when play begins
//-----------------------------------------------------------------------------
void ASample05Actor::BeginPlay()
{
    Super::BeginPlay();

    Log(FString::Printf(TEXT("PluginInfo: %s"), *MaxQSamples::MaxQPluginInfo()), FColor::Purple);
    Log(TEXT("Sample05: Initialization and kernel data"), FColor::Blue);
    Log(TEXT("** Please see Sample05Actor in Scene 'Sample05' folder for button controls (details panel) **"), FColor::Yellow);
    Log(TEXT("** Please see Sample05Actor.cpp for more info **"), FColor::Blue);
    Log(TEXT("** This tutorial is only an interim version! **"), FColor::Red);

    // init_all:  clears kernel memory and any error state.
    USpice::init_all();

    // Don't tick unless we have the kernels required to update the solar system
    bool EnableTick = USampleUtilities::LoadKernelList(TEXT("Basic"), BasicKernels);
    if (EnableTick)
    {
        // Individual examples
        conics();
        oscelt();
        TLEs();

        InitAnimation();

        // Get telemetry from server and create objects in orbit
        RequestTelemetryByHttp();
    }
    PrimaryActorTick.SetTickFunctionEnable(EnableTick);
}



//-----------------------------------------------------------------------------
// Name: Tick
// Desc: 
//-----------------------------------------------------------------------------
void ASample05Actor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    SolarSystemState.CurrentTime += DeltaSeconds * SolarSystemState.TimeScale;

    bool success = true;
    success &= MaxQSamples::UpdateBodyPositions(OriginNaifName, OriginReferenceFrame, DistanceScale, SolarSystemState);
    success &= MaxQSamples::UpdateBodyOrientations(OriginReferenceFrame, SolarSystemState);
    success &= MaxQSamples::UpdateSunDirection(OriginNaifName, OriginReferenceFrame, SolarSystemState.CurrentTime, SunNaifName, SunDirectionalLight);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Time Scale: %f x"), SolarSystemState.TimeScale.AsSeconds()));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Display Time: %s"), *SolarSystemState.CurrentTime.ToString()));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Origin Reference Frame: %s"), *OriginReferenceFrame.ToString()));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Origin Observer Naif Name: %s"), *OriginNaifName.ToString()));
    }

    if (!success)
    {
        // Restart time...
        Restart();
    }
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: conics
// Desc:
// Very simple example of orbital "propagation" with kepler orbital elements.
// "Propagating" an orbit just means predicting its future location.     
//-----------------------------------------------------------------------------

void ASample05Actor::conics()
{
    ES_ResultCode ResultCode;
    FString ErrorMessage;

    // We'll need Earth's mass for propagating orbits via conics and oscelt
    FString NaifNameOfMass = EARTH;
    USpice::bodvrd_mass(ResultCode, ErrorMessage, GM, NaifNameOfMass, MaxQ::Constants::GM);

    Log(FString::Printf(TEXT("conics Mass Constant of EARTH = %s"), *GM.ToString()), ResultCode);

    // We'll also need Earth's Radius, since the orbital elements below express Rp in altitude, not radius.
    FSDistanceVector Radii;
    if (ResultCode == ES_ResultCode::Success)
    {
        USpice::bodvrd_distance_vector(ResultCode, ErrorMessage, Radii, NaifNameOfMass, RADII);
        Log(FString::Printf(TEXT("conics Radii of EARTH = %s"), *Radii.ToString()), ResultCode);
    }

    // for a random orbit specified by classic kepler orbital elements,
    // get a state vector for a given time.
    if (ResultCode == ES_ResultCode::Success)
    {
        // A random orbit.
        // From:
        // https://www.heavens-above.com/orbit.aspx?satid=20580
        const FSDistance alt  = FSDistance::FromKilometers(533);
        const double e      = 0.0002312;
        const FSAngle i     = FSAngle::FromDegrees(28.4689);
        const FSAngle node  = FSAngle::FromDegrees(225.34227);
        const FSAngle arg   = FSAngle::FromDegrees(306.2587);
        const FSAngle M     = FSAngle::FromDegrees(222.7137);
        const FSEphemerisTime epoch = FSEphemerisTime::FromString(TEXT("08 June 2022 22:05:53"));

        FSConicElements OrbitalElements;
        OrbitalElements.PerifocalDistance = alt + Radii.x;
        OrbitalElements.Eccentricity = e;
        OrbitalElements.Inclination = i;
        OrbitalElements.LongitudeOfAscendingNode = node;
        OrbitalElements.ArgumentOfPeriapse = arg;
        OrbitalElements.MeanAnomalyAtEpoch = M;
        OrbitalElements.Epoch = epoch;
        OrbitalElements.GravitationalParameter = GM;

        FSEphemerisTime et;
        USpice::et_now(et);

        FSStateVector state;

        // Get a state vector from the orbital elements!
        USpice::conics(ResultCode, ErrorMessage, OrbitalElements, et, state);

        Log(FString::Printf(TEXT("Hubble Space Telescope State Vector (from Kepler Orbit) = %s"), *state.ToString()), ResultCode);
    }
}



// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: oscelt
// Desc:
// Simple example of deducing orbital elements from a state vector.
// "State Vector" just means a Position and Velocity relative to whatever
// mass the object is orbiting.
//-----------------------------------------------------------------------------

void ASample05Actor::oscelt()
{
    // We'll get Earth's current state vector, then get orbital params for it.
    FSStateVector state;
    FSEphemerisPeriod lt;

    ES_ResultCode ResultCode;
    FString ErrorMessage;

    // When do we want it?   (time: now)
    FSEphemerisTime et;
    USpice::et_now(et);

    // What do we want?  (Earth's position)
    FString targ = EARTH;

    // Where do we want it relative to? (Solar System Barycenter)
    FString obs = SSB;

    // What reference frame (coordinate system orientation)?
    // Ecliptic Plane
    FString ref = ECLIPJ2000;

    // Call SPICE, get the position in rectangular coordinates...
    USpice::spkezr(ResultCode, ErrorMessage, et, state, lt, targ, obs, ref);

    Log(FString::Printf(TEXT("oscelt EARTH's State Vector (ECLIP2000 Frame) = %s"), *state.ToString()), ResultCode);

    // We need the mass of whatever we're orbiting to get the orbital elements
    // from a state vector ('oscelt').  In this case we're orbiting the sun.
    FSMassConstant SUN_GM;
    if (ResultCode == ES_ResultCode::Success)
    {
        // We're ignoring the effects of all other bodies on the earth, only the sun
        // So, we want the mass of the Sun itself, even though we're getting the
        // orbital params relative to the Solar System Barycenter, as if the sun was there.
        FString NaifNameOfMass = SUN;
        USpice::bodvrd_mass(ResultCode, ErrorMessage, SUN_GM, NaifNameOfMass, MaxQ::Constants::GM);

        Log(FString::Printf(TEXT("oscelt Mass of SUN = %s"), *SUN_GM.ToString()), ResultCode);
    }

    FSConicElements ConicElements;
    if (ResultCode == ES_ResultCode::Success)
    {
        // Now, deduce the orbital elements!
        USpice::oscelt(ResultCode, ErrorMessage, state, et, SUN_GM, ConicElements);

        Log(FString::Printf(TEXT("oscelt EARTH's Orbital/Conic/Keplerian Elements (ECLIP2000 Frame) = %s"), *ConicElements.ToString()), ResultCode);
    }
}



// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: TLEs
// Desc:
// Simple example of Propagating an orbit by NORAD TLE telemetry
//-----------------------------------------------------------------------------

void ASample05Actor::TLEs()
{
    // If you're new to "Two-Line Elements", see:
    // https://en.wikipedia.org/wiki/Two-line_element_set
    // 
    // A random TLE from:
    // https://www.n2yo.com/satellite/?s=20580
    // (It's the Hubble Space Telescope).
    FString TLE_1 = TEXT("1 20580U 90037B   22159.92075888  .00001332  00000-0  67903-4 0  9998");
    FString TLE_2 = TEXT("2 20580  28.4689 225.3422 0002312 306.2587 222.7137 15.10552549564920");


    Log(*TLE_2, FColor::White);
    Log(*TLE_1, FColor::White);
    Log(TEXT("TLEs Using TLE data for Hubble Space telescope"), FColor::White);

    FSStateVector state;
    FSEphemerisPeriod lt;

    ES_ResultCode ResultCode;
    FString ErrorMessage;

    // When do we want it?   (time: now)
    FSEphemerisTime et;
    USpice::et_now(et);

    // First, we ask SPICE to kindly parse the TLE strings...
    FSTwoLineElements TwoLineElements;
    USpice::getelm(ResultCode, ErrorMessage, et, TwoLineElements, TLE_1, TLE_2);

    // Now, we can propagate the orbit...
    if (ResultCode == ES_ResultCode::Success)
    {
        // getgeophs requires geophysical.ker or equivalent kernel to be loaded...
        FSTLEGeophysicalConstants GeophysicalConstants;
        USpice::getgeophs(GeophysicalConstants, TEXT("EARTH"));

        // 'evsgp4' propagates TLE's.
        // See:
        // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/evsgp4_c.html
        USpice::evsgp4(ResultCode, ErrorMessage, state, et, GeophysicalConstants, TwoLineElements);

        Log(FString::Printf(TEXT("TLEs Hubble Space Telescope's State Vector (TEME Frame) = %s"), *state.ToString()), ResultCode);
    }

    if (ResultCode != ES_ResultCode::Success)
    {
        Log(FString::Printf(TEXT("TLEs Error calling SPICE: %s"), *ErrorMessage), ResultCode);
    }
}

// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: InitAnimation
// Desc: Scale the earth, etc.
//-----------------------------------------------------------------------------

void ASample05Actor::InitAnimation()
{
    USampleUtilities::InitializeTime(SolarSystemState);
    MaxQSamples::InitBodyScales(DistanceScale, SolarSystemState);
    USpice::getgeophs(EarthConstants, TEXT("EARTH"));
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: RequestTelemetryByHttp
// Desc:
// Send a telemetry data request to Celestrak
//-----------------------------------------------------------------------------

void ASample05Actor::RequestTelemetryByHttp()
{
    Log(TEXT("RequestTelemetryByHttp sending telemetry request to server by http"));

    // Uses the Http module to send request by http
    FTelemetryCallback Callback;
    Callback.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(ASample05Actor, ProcessTelemetryResponseAsTLE));
    USampleUtilities::GetTelemetryFromServer(Callback, TelemetryObjectId, TEXT("TLE"));
}



// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: ProcessTelemetryResponseAsTLE
// Desc:
// Process the server response, assuming it's a group of TLE data
//-----------------------------------------------------------------------------

void ASample05Actor::ProcessTelemetryResponseAsTLE(bool Success, const FString& ObjectId, const FString& Telemetry)
{
    // Oh, hi!
    // We got an object from the server... and it's TLE lines.
    Log(TEXT("ProcessTelemetryResponseAsTLE Telemetry response received from server"));
    Log(FString::Printf(TEXT("ProcessTelemetryResponseAsTLE Telemetry : %s"), *(Telemetry.Left(750) + TEXT("..."))), Success ? FColor::Green : FColor::Red, 15.f);

    TArray<FString> TLEArray;
    if (Success && (0 == (Telemetry.ParseIntoArrayLines(TLEArray, true) % 3)))
    {
        ES_ResultCode ResultCode;
        FString ErrorMessage;

        FSEphemerisTime et;
        FSTwoLineElements elems;

        for(int i = 0; i < TLEArray.Num(); i += 3)
        {
            // 'getelm' parses TLE strings into a useable form.  So, process the strings
            // from the server.
            USpice::getelm(ResultCode, ErrorMessage, et, elems, TLEArray[i + 1], TLEArray[i + 2]);

            // If the object's TLEs parsed successfully, create an actor for it.
            if (ResultCode == ES_ResultCode::Success)
            {
                AddTelemetryObject(ObjectId, TLEArray[i + 0].TrimStartAndEnd(), elems);
            }
            else
            {
                Log(FString::Printf(TEXT("ProcessTelemetryResponse getelem Spice Error %s"), *ErrorMessage), ResultCode);
            }

            // Dump a few object names to the log.
            if (i < 10)
            {
                Log(FString::Printf(TEXT("** Please also see %s in Scene 'In Orbit' folder for button controls (details panel) **"), *(TLEArray[i].TrimStartAndEnd())), FColor::Orange);
            }
        }
    }
    else
    {
        Log(TEXT("ProcessTelemetryResponseAsTLE TLE Response is nonsense (expected 3 lines including obj name line)"), FColor::Red);
    }
}



// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: 
// Desc:
//-----------------------------------------------------------------------------

void ASample05Actor::AddTelemetryObject(const FString& ObjectId, const FString& ObjectName, const FSTwoLineElements& Elements)
{
    check(IsInGameThread());

    if(TelemetryObjectClass)
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.ObjectFlags |= RF_Transient;

        ASample05TelemetryActor* TelemetryObject = Cast<ASample05TelemetryActor>(GetWorld()->SpawnActor(TelemetryObjectClass, NULL, NULL, SpawnParameters));

        if (TelemetryObject != nullptr)
        {
            TelemetryObject->SetActorLabel(ObjectName);
            TelemetryObject->SetFolderPath("In Orbit");

            // There's several ways this could have been done, obviously.
            // Is this the best?
            // Hey, there's no right or wrong solutions, only solutions optimized to different criteria.
            TelemetryObject->PropagateByTLEs.BindUObject(this, &ASample05Actor::PropagateTLE);
            TelemetryObject->XformPositionCallback.BindUObject(this, &ASample05Actor::TransformPosition);

            TelemetryObject->ComputeConic.BindUObject(this, &ASample05Actor::ComputeConic);
            TelemetryObject->RenderDebugOrbit.BindUObject(this, &ASample05Actor::RenderDebugOrbit);
            TelemetryObject->PropagateByKeplerianElements.BindUObject(this, &ASample05Actor::EvaluateOrbitalElements);
            TelemetryObject->GetOrbitalElements.BindUObject(this, &ASample05Actor::GetOrbitalElements);
            TelemetryObject->GetConicFromKepler.BindUObject(this, &ASample05Actor::GetConicFromKepler);

            // By default only render debug orbits for ISS-related objects
            bool bShouldRenderOrbit = ObjectName.StartsWith(TEXT("ISS"));

            TelemetryObject->Init(ObjectId, ObjectName, Elements, bShouldRenderOrbit);
        }
    }
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: PropagateTLE
// Desc:
// ...how to propagate TLE telemetry to an orbital state vector.
//-----------------------------------------------------------------------------

bool ASample05Actor::PropagateTLE(const FSTwoLineElements& TLEs, FSStateVector& StateVector)
{
    ES_ResultCode ResultCode;
    FString ErrorMessage;

    // Given "Two-Line" Elements, compute a state vector
    USpice::evsgp4(ResultCode, ErrorMessage, StateVector, SolarSystemState.CurrentTime, EarthConstants, TLEs);

    return ResultCode == ES_ResultCode::Success;
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: TransformPosition
// Desc:
// Swizzle and scale a vector from RHS SPICE coords to LHS UE coords.
//-----------------------------------------------------------------------------

bool ASample05Actor::TransformPosition(const FSDistanceVector& RHSPosition, FVector& UEVector)
{
    // Simple transform.
    UEVector = USpiceTypes::Swizzle(RHSPosition);

    UEVector /= DistanceScale;

    return true;
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: ComputeConic
// Desc: Compute an ellipse or hyperbola from a state vector
//-----------------------------------------------------------------------------

bool ASample05Actor::ComputeConic(const FSStateVector& StateVector, FSEllipse& OrbitalConic, bool& bIsHyperbolic)
{
    FSConicElements KeplerianElements;
    bool result = GetOrbitalElements(StateVector, KeplerianElements);
    if (result)
    {
        GetConicFromKepler(KeplerianElements, OrbitalConic, bIsHyperbolic);
    }

    return result;
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: RenderDebugOrbit
// Desc:
// Given an ellipse/hyperbola, render it with debug lines.
//-----------------------------------------------------------------------------

void ASample05Actor::RenderDebugOrbit(const FSEllipse& OrbitalConic, bool bIsHyperbolic, const FColor& Color, float Thickness)
{
    USpiceOrbits::RenderDebugConic(this, OrbitalConic, bIsHyperbolic, FTransform(FScaleMatrix(1./DistanceScale)), Color, Thickness);
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: EvaluateOrbitalElements
// Desc:
// Propagate an orbit by kepler orbital elements.
// E.g. get a state vector for a given time.
// Reminder: A "state vector" is a position and velocity at a point in orbit.
//-----------------------------------------------------------------------------

bool ASample05Actor::EvaluateOrbitalElements(const FSConicElements& KeplerianElements, FSStateVector& StateVector)
{
    ES_ResultCode ResultCode;
    FString ErrorMessage;

    USpice::conics(ResultCode, ErrorMessage, KeplerianElements, SolarSystemState.CurrentTime, StateVector);

    return ResultCode == ES_ResultCode::Success;
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: GetOrbitalElements
// Desc:
// Given a state vector, compute the keplerian orbital elements.
// This is what 'oscelt' is for!
//-----------------------------------------------------------------------------

bool ASample05Actor::GetOrbitalElements(const FSStateVector& StateVector, FSConicElements& KeplerianElements)
{
    ES_ResultCode ResultCode;
    FString ErrorMessage;

    // Given a state vector, compute the orbital elements
    USpice::oscelt(ResultCode, ErrorMessage, StateVector, SolarSystemState.CurrentTime, GM, KeplerianElements);

    return ResultCode == ES_ResultCode::Success;
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: GetConicFromKepler
// Desc:
// Desc: Compute an ellipse or hyperbola from classical orbital elements.
//-----------------------------------------------------------------------------

bool ASample05Actor::GetConicFromKepler(const FSConicElements& KeplerianElements, FSEllipse& OrbitalConic, bool& bIsHyperbolic)
{
    USpiceOrbits::ComputeConic(OrbitalConic, bIsHyperbolic, SolarSystemState.CurrentTime, KeplerianElements, J2000, OriginReferenceFrame.ToString());
    return true;
}

//-----------------------------------------------------------------------------



void ASample05Actor::VeryFastSpeed()
{
    NormalSpeed();
    FasterSpeed();
    FasterSpeed();
}

void ASample05Actor::FasterSpeed()
{
    SolarSystemState.TimeScale *= 10.;
}

void ASample05Actor::SlowerSpeed()
{
    SolarSystemState.TimeScale *= 0.1;
}

void ASample05Actor::NormalSpeed()
{
    SolarSystemState.TimeScale = 1;
}

void ASample05Actor::GoToNow()
{
    USpice::et_now(SolarSystemState.CurrentTime);
    NormalSpeed();
}

void ASample05Actor::Restart()
{
    USampleUtilities::InitializeTime(SolarSystemState, false);
}