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

using MaxQSamples::Log;


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
    Log(TEXT("** Please see Sample05Actor.cpp for more info **"), FColor::Blue);
    Log(TEXT("** This tutorial is only an interim version! **"), FColor::Red);

    // init_all:  clears kernel memory and any error state.
    USpice::init_all();

    if (USampleUtilities::LoadKernelList(TEXT("Basic"), BasicKernels))
    {
        conics();
        oscelt();
        TLEs();
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
    FSMassConstant GM;
    FString NaifNameOfMass = TEXT("EARTH");
    USpice::bodvrd_mass(ResultCode, ErrorMessage, GM, NaifNameOfMass, TEXT("GM"));

    Log(FString::Printf(TEXT("conics Mass Constant of EARTH = %s"), *USpiceTypes::Conv_SMassConstantToString(GM)), ResultCode);

    // We'll also need Earth's Radius, since the orbital elements below express Rp in altitude, not radius.
    FSDistanceVector Radii;
    if (ResultCode == ES_ResultCode::Success)
    {
        USpice::bodvrd_distance_vector(ResultCode, ErrorMessage, Radii, NaifNameOfMass, TEXT("RADII"));
        Log(FString::Printf(TEXT("conics Radii of EARTH = %s"), *USpiceTypes::Conv_SDistanceVectorToString(Radii)), ResultCode);
    }

    if (ResultCode == ES_ResultCode::Success)
    {
        // From:
        // https://www.heavens-above.com/orbit.aspx?satid=20580
        const FSDistance alt  = FSDistance::FromKm(533);
        const double e      = 0.0002312;
        const FSAngle i     = FSAngle::FromDegrees(28.4689);
        const FSAngle node  = FSAngle::FromDegrees(225.34227);
        const FSAngle arg   = FSAngle::FromDegrees(306.2587);
        const FSAngle M     = FSAngle::FromDegrees(222.7137);
        const FSEphemerisTime epoch = USpiceTypes::Conv_StringToSEpheremisTime(TEXT("08 June 2022 22:05:53"));

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

        Log(FString::Printf(TEXT("Hubble Space Telescope State Vector (from Kepler Orbit) = %s"), *USpiceTypes::Conv_SStateVectorToString(state)), ResultCode);
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
    FString targ = TEXT("EARTH");

    // Where do we want it relative to? (Solar System Barycenter)
    FString obs = TEXT("SSB");

    // What reference frame (coordinate system orientation)?
    // Ecliptic Plane
    FString ref = TEXT("ECLIPJ2000");

    // Call SPICE, get the position in rectangular coordinates...
    USpice::spkezr(ResultCode, ErrorMessage, et, state, lt, targ, obs, ref);

    Log(FString::Printf(TEXT("oscelt EARTH's State Vector (ECLIP2000 Frame) = %s"), *USpiceTypes::Conv_SStateVectorToString(state)), ResultCode);

    FSMassConstant GM;
    if (ResultCode == ES_ResultCode::Success)
    {
        // We're ignoring the effects of all other bodies on the earth, only the sun
        // So, we want the mass of the Sun itself, even though we're getting the
        // orbital params relative to the Solar System Barycenter, as if the sun was there.
        FString NaifNameOfMass = TEXT("SUN");
        USpice::bodvrd_mass(ResultCode, ErrorMessage, GM, NaifNameOfMass, TEXT("GM"));

        Log(FString::Printf(TEXT("oscelt Mass of SUN = %s"), *USpiceTypes::Conv_SMassConstantToString(GM)), ResultCode);
    }

    FSConicElements ConicElements;
    if (ResultCode == ES_ResultCode::Success)
    {
        // Now, deduce the orbital elements!
        USpice::oscelt(ResultCode, ErrorMessage, state, et, GM, ConicElements);

        Log(FString::Printf(TEXT("oscelt EARTH's Orbital/Conic/Keplerian Elements (ECLIP2000 Frame) = %s"), *USpiceTypes::Conv_SConicElementsToString(ConicElements)), ResultCode);
    }
}



// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: TLEs
// Desc:
// Simple example of Propagating an orbit by TLE
//-----------------------------------------------------------------------------

void ASample05Actor::TLEs()
{
    // A random TLE from:
    // https://www.n2yo.com/satellite/?s=20580
    FString TLE_1 = TEXT("1 20580U 90037B   22159.92075888  .00001332  00000-0  67903-4 0  9998");
    FString TLE_2 = TEXT("2 20580  28.4689 225.3422 0002312 306.2587 222.7137 15.10552549564920");


    Log(TEXT("2 20580  28.4689 225.3422 0002312 306.2587 222.7137 15.10552549564920"), FColor::White);
    Log(TEXT("1 20580U 90037B   22159.92075888  .00001332  00000-0  67903-4 0  9998"), FColor::White);
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

        USpice::evsgp4(ResultCode, ErrorMessage, state, et, GeophysicalConstants, TwoLineElements);

        Log(FString::Printf(TEXT("TLEs Hubble Space Telescope's State Vector (TEME Frame) = %s"), *USpiceTypes::Conv_SStateVectorToString(state)), ResultCode);
    }

    if (ResultCode != ES_ResultCode::Success)
    {
        Log(FString::Printf(TEXT("TLEs Error calling SPICE: %s"), *ErrorMessage), ResultCode);
    }
}

