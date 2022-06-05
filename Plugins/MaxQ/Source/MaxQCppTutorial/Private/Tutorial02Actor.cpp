// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "Tutorial02Actor.h"
#include "Components/SceneComponent.h"
#include "Engine/Engine.h"
#include "Spice.h"
#include "SpiceK2.h"
#include "TutorialUtilities.h"

using MaxQTutorial::Log;

//-----------------------------------------------------------------------------
// Tutorial02
// Time manipulation
//-----------------------------------------------------------------------------
/*
 * Additional Info:  Documentation
 *
 * Plugin documentation is available in the plugin's directory
 *      /Documentation
 *          /naif - Helpful documentation on SPICE
 */
 /* Additional Info: Files Kernels (SPICE API)
 * LSK kernels
        Leap seconds, for time keeping
        https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/Tutorials/pdf/individual_docs/16_lsk_and_sclk.pdf
 * PCK kernels
        Planet orientations, kernel pool data, etc
        https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/pck.html
        https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/Tutorials/pdf/individual_docs/19_pck.pdf
        https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/kernel.html
*  Time
*       https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/time.html
*       https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/Tutorials/pdf/individual_docs/15_time.pdf
*/
ATutorial02Actor::ATutorial02Actor()
{
    SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
    PrimaryActorTick.bCanEverTick = true;

    // This is a "Leap Seconds" kernel
    // (it is a text file, open it up and take a look if you wish...)
    // It contains data on leap seconds that have been declared, which is necessary
    // for highly precise time keeping.
    RequiredKernels.Add(TEXT("NonAssetData/naif/kernels/Generic/LSK/naif0012.tls"));

    // This is a PCK kernel... Which contains data about planet orientations, etc
    // Again, another text file.
    RequiredKernels.Add(TEXT("NonAssetData/naif/kernels/Generic/PCK/pck00010.tpc"));

    // This is a Spacecraft Clock kernel, for the NASA Insight lander on mars
    InsightSCLKKernel = TEXT("NonAssetData/naif/kernels/INSIGHT/SCLK/NSY_SCLKSCET.00023.tsc");

    // This is a Mission FK Kernel, containing Naif ID codes and Reference
    // Frames for the Insight lander and sub-assemblies
    InsightMissionFKKernel = TEXT("NonAssetData/naif/kernels/INSIGHT/FK/insight_v05.tf");
}

//-----------------------------------------------------------------------------
// Name: BeginPlay
// Desc: Calls each of the tutorial/demo methods once when play begins
//-----------------------------------------------------------------------------
void ATutorial02Actor::BeginPlay()
{
    Super::BeginPlay();

    Log(FString::Printf(TEXT("PluginInfo: %s"), *MaxQTutorial::MaxQPluginInfo()), FColor::Purple);
    Log(TEXT("Tutorial02: Time manipulation"), FColor::Blue);
    Log(TEXT("** Please see Tutorial02Actor.cpp for more info **"), FColor::Blue);

    InitializeSpice();

    J2000();

    J2020();

    Now();

    Insight();
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: InitializeSpice
// Desc: Demonstrate how to initialize the SPICE module
//-----------------------------------------------------------------------------

void ATutorial02Actor::InitializeSpice()
{
    // init_all:  clears kernel memory and any error state.
    USpice::init_all();

    // SPICE return values
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage = "";

    // furnsh_list will load the list of relative paths as kernel files
    USpice::furnsh_list(ResultCode, ErrorMessage, MaxQTutorial::MaxQPathsAbsolutified(RequiredKernels));

    Log(TEXT("InitializeSpice loaded kernel file"), ResultCode);
}



// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: J2000
// Desc: Print the J2000 Epoch
//-----------------------------------------------------------------------------

void ATutorial02Actor::J2000()
{
    // An "epoch" is a point in time.
    // The time-line commonly used in SPICE is Barycentric Dynamical Time (TDB).
    // TDB is also called "Ephemeris Time" (ET).
    // The MaxQ FSEphemerisTime structure is used to track ET's.
    // The J2000 (1 Jan 2000, 11:58:55.816 UTC) is a commonly used epoch.
    // Often et is tracked as "seconds past J2000"
    FSEphemerisTime et = FSEphemerisTime::J2000;

    // Get a string representation of J2000
    // Also, see: USpice::et2utc, USpice::etcal, USpice::timout
    FString EpochString = USpiceTypes::Conv_SEpheremisTimeToString(et);

    Log(FString::Printf( TEXT("J2000 was: %s"), *EpochString));

    // Add a period of one day to et...
    et += FSEphemerisPeriod::Day;
    Log(FString::Printf(TEXT("One day after J2000 was: %s"), *USpiceTypes::Conv_SEpheremisTimeToString(et)));
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: J2020
// Desc:
// Print (J2020 - J2000) in seconds
// There were intervening "leap seconds" between j2000 and j2020, so the number
// should not be evenly divisible by minutes.
//-----------------------------------------------------------------------------
/*
* Additional Info:
  According to the LSK kernel we loaded, there were 5 leap seconds in the
  interval.
 
naif0012.tls:
        33, @2006 - JAN - 1
        34, @2009 - JAN - 1
        35, @2012 - JUL - 1
        36, @2015 - JUL - 1
        37, @2017 - JAN - 1
*/

void ATutorial02Actor::J2020()
{
    // Load j2000 with the et value correlating to J2000.
    FSEphemerisTime j2000 = FSEphemerisTime::J2000;

    // Create & Load a loose equivalent for J2020 epoch
    // Also, see USpice::utc2et, USpice::str2et, USpice::tparse
    FSEphemerisTime j2020 = USpiceTypes::Conv_StringToSEpheremisTime(TEXT("1 JAN 2020 11:58:55.816 UTC"));

    // FSEphemerisPeriod can store an interval between two epochs
    FSEphemerisPeriod delta = j2020 - j2000;

    // The period can be converted into a double as seconds
    double seconds = delta.AsSeconds();

    // Dividing two FSEphemerisPeriod values gives a double.
    // The period of one day is value FSEphemerisPeriod::Day
    int days = FMath::FloorToInt64( delta / FSEphemerisPeriod::Day);    
    
    // The delta between the actual period, and the period for 'days' should be
    // the number of leap seconds.
    double LeapSeconds = seconds - days * FSEphemerisPeriod::Day.AsSeconds();

    // We should see "5" seconds.
    Log(FString::Printf(TEXT("J2020-J2000 = %.6f seconds (%d days + %.6f seconds)"), seconds, days, LeapSeconds));
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: Now
// Desc: Demonstrate getting the current Ephemeris Time
//-----------------------------------------------------------------------------

void ATutorial02Actor::Now()
{
    // Load j2000 with the et value correlating to J2000.
    FSEphemerisTime et; 
    USpice::et_now(et);

    FString EpochString;

    // Demonstrate a number of ways to format time strings...
    USpice::etcal(et, EpochString);
    Log(FString::Printf(TEXT("Now (CAL): %s Cal"), *EpochString));

    ES_ResultCode ResultCode;
    FString ErrorMessage;

    USpice::et2utc(ResultCode, ErrorMessage, et, ES_UTCTimeFormat::ISOCalendar, EpochString);
    Log(FString::Printf(TEXT("Now ISOCalendar: %s"), *EpochString), ResultCode);

    USpice::et2utc(ResultCode, ErrorMessage, et, ES_UTCTimeFormat::ISODayOfYear, EpochString);
    Log(FString::Printf(TEXT("Now ISODayOfYear: %s"), *EpochString), ResultCode);

    USpice::et2utc(ResultCode, ErrorMessage, et, ES_UTCTimeFormat::Calendar, EpochString);
    Log(FString::Printf(TEXT("Now Calendar: %s"), *EpochString), ResultCode);

    USpice::et2utc(ResultCode, ErrorMessage, et, ES_UTCTimeFormat::DayOfYear, EpochString, 4);
    Log(FString::Printf(TEXT("Now DayOfYear: %s"), *EpochString), ResultCode);

    USpice::et2utc(ResultCode, ErrorMessage, et, ES_UTCTimeFormat::JulianDate, EpochString, 4);
    Log(FString::Printf(TEXT("Now JulianDate: %s"), *EpochString), ResultCode);

    USpice::timout(ResultCode, ErrorMessage, EpochString, et, TEXT("MON DD, YYYY  HR:MN:SC.#### (TDB) ::TDB"));
    Log(FString::Printf(TEXT("Now TDB: %s"), *EpochString), ResultCode);
}



// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: Insight
// Desc: Demonstrate Spacecraft clock time conversion
//-----------------------------------------------------------------------------

void ATutorial02Actor::Insight()
{
    ES_ResultCode ResultCode;
    FString ErrorMessage;

    // The FK Kernel defines reference frames of instruments, etc for the Insight mission
    // It also defines the Spacecraft ID, which we can get for "Insight"
    USpice::furnsh(ResultCode, ErrorMessage, MaxQTutorial::MaxQPathAbsolutified(InsightMissionFKKernel));
    Log(FString::Printf(TEXT("Insight loaded Insight Mission FK kernel %s"), *InsightMissionFKKernel), ResultCode);

    // With the FK loaded, we can look up the spacecraft Id (it's -189)
    int SpacecraftId = 0;  // -189;
    ES_FoundCode FoundCode;
    USpice::bodn2c(FoundCode, SpacecraftId, TEXT("INSIGHT"));
    Log(FString::Printf(TEXT("Insight found Insight Spacecraft ID %d"), SpacecraftId), FoundCode == ES_FoundCode::Found ? FColor::Green : FColor::Red);

    // Note, the LSK file refers to leap seconds kernel insight.tls, but the
    // current file is equivalent to naif0012.tls, which we've loaded already.

    // The SCLK Kernel allows us to convert times between ET/UTC and the Spacecraft's clock
    USpice::furnsh(ResultCode, ErrorMessage, MaxQTutorial::MaxQPathAbsolutified(InsightSCLKKernel));
    Log(FString::Printf(TEXT("Insight loaded Insight Mars Lander SCLK kernel %s"), *InsightSCLKKernel), ResultCode);

    FSEphemerisTime et;
    USpice::et_now(et);

    // Convert the current time to a spacecraft clock string...
    FString SpacecraftClock;
    USpice::sce2s(ResultCode, ErrorMessage, SpacecraftId, et, SpacecraftClock);
    Log(FString::Printf(TEXT("Insight Spacecraft clock: %s"), *SpacecraftClock), ResultCode);

    // Convert the current time to a current tick of Insight's clock
    double IntegralTicks;
    USpice::sce2t(ResultCode, ErrorMessage, SpacecraftId, et, IntegralTicks);
    Log(FString::Printf(TEXT("Insight Spacecraft clock Integral Ticks: %f"), IntegralTicks), ResultCode);

    // Sometimes you need an imaginary fractional tick for animation/lerp of
    // orientation or something... Even though the spacecraft clock increments
    // increments as discrete integer ticks
    double FractionalTicks;
    USpice::sce2c(ResultCode, ErrorMessage, SpacecraftId, et, FractionalTicks);
    Log(FString::Printf(TEXT("Insight Spacecraft clock Fractional Ticks: %f"), FractionalTicks), ResultCode);
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: Tick
// Desc: Update the current epoch and Insight spacecraft clock live
//-----------------------------------------------------------------------------

void ATutorial02Actor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    ES_ResultCode ResultCode;
    FString ErrorMessage;
    FSEphemerisTime et;
    USpice::et_now(et);

    // Update current epoch (live)
    FString EpochString;
    USpice::et2utc(ResultCode, ErrorMessage, et, ES_UTCTimeFormat::Calendar, EpochString);
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 0.0f, ResultCode == ES_ResultCode::Success ? FColor::Green : FColor::Red, FString::Printf(TEXT("Epoch (now): %s"), *EpochString));
    }

    int SpacecraftId = -189;

    // Update Insight spacecraft clock (live)
    FString SpacecraftClock;
    USpice::sce2s(ResultCode, ErrorMessage, SpacecraftId, et, SpacecraftClock);
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 0.0f, ResultCode == ES_ResultCode::Success ? FColor::Green : FColor::Red, FString::Printf(TEXT("Insight Spacecraft clock: %s"), *SpacecraftClock));
    }
}
