// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "Sample03Actor.h"
#include "Components/SceneComponent.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "Spice.h"
#include "SpiceK2.h"
#include "SampleUtilities.h"

using MaxQSamples::Log;

//-----------------------------------------------------------------------------
// Sample03
// Basic positions and state vectors (Spice SPK)
//-----------------------------------------------------------------------------
ASample03Actor::ASample03Actor()
{
    SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
    PrimaryActorTick.bCanEverTick = true;

    USampleUtilities::GetDefaultBasicKernels(BasicKernels);
    USampleUtilities::GetDefaultItrf93Kernels(Itrf93Kernels);
    USampleUtilities::GetDefaultInsightMissionKernels(InsightMissionKernels);
    RelativePathToOuterPlanetSPKFixups = TEXT("NonAssetData/MaxQ/kernels/SPK/outer_planets.bsp");

    BodyScale = 1000.0;
    DistanceScale = 473586.957802;

    // This is the coordinate system center relative to SPICE
    // (SSB = "Solar System Barycenter")
    OriginNaifName = FName("SSB");
    // This is the UE coordinate system orientation relative to SPICE
    OriginReferenceFrame = FName("ECLIPJ2000");
}



//-----------------------------------------------------------------------------
// Name: BeginPlay
// Desc: Calls each of the sample/demo methods once when play begins
//-----------------------------------------------------------------------------
void ASample03Actor::BeginPlay()
{
    Super::BeginPlay();

    Log(FString::Printf(TEXT("PluginInfo: %s"), *MaxQSamples::MaxQPluginInfo()), FColor::Purple);
    Log(TEXT("Sample03: Basic positions and state vectors (Spice SPK)"), FColor::Blue);
    Log(TEXT("** Please see Sample03Actor.cpp for more info **"), FColor::Blue);
    Log(TEXT("See Sample03Actor (scene instance) Details Panel for time control buttons."), FColor::Blue);


    // init_all:  clears kernel memory and any error state.
    USpice::init_all();

    bool EnableTick;
    if (EnableTick = USampleUtilities::LoadKernelList(TEXT("Basic"), BasicKernels))
    {
        // Use 'spkpos' to find a position in ECI Frame (Earth-Centered, Inertial)
        spkpos_inertial();

        if (USampleUtilities::LoadKernelList(TEXT("Itrf93"), Itrf93Kernels))
        {
            // Use 'spkpos' to find a position in ECEF Frame (Earth-Centered, Earth-Fixed)
            spkpos_fixed();

            // Use 'spkezr_inertial' to find a state vector in an inertial frame
            // State vector = Position + Velocity
            spkezr_inertial();

            // Use 'spkezr_fixed' finding a state vector relative to a body's fixed frame
            spkezr_fixed();

            if (USampleUtilities::LoadKernelList(TEXT("Insight Mission"), InsightMissionKernels))
            {
                // Earth DSS-14 antenna <-> Mars Insight Lander
                // --------------------------------------------
                // Light takes a while to travel between Mars and Earth.  To receive a message
                // from Mars we need to know what the apparent location is (factoring time travel).
                // To transmit a message to mars we need to know what the future location will be
                // by the time our message gets there...

                // Direction to aim DSS-14 to receive message from INSIGHT landing site
                azlcpo(ES_AberrationCorrectionWithTransmissions::LT_S);
                // Direction to aim DSS-14 to transmit message to INSIGHT landing site
                azlcpo(ES_AberrationCorrectionWithTransmissions::XLT_S);
            }
        }

        InitializeSolarSystem(SolarSystemState);
    }

    PrimaryActorTick.SetTickFunctionEnable(EnableTick);
}


//-----------------------------------------------------------------------------
// Name: Tick
// Desc: 
//-----------------------------------------------------------------------------
void ASample03Actor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateSolarSystem(SolarSystemState, DeltaTime);
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: spkpos_inertial
// Desc:
// spkpos returns a position (computed from SPK kernel data).
// Where is the Sun, relative to Earth? (Right Ascension/Declination angles)
//-----------------------------------------------------------------------------
/*
* Additional Info: spkpos SPICE documentation
* https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkpos_c.html
*/

void ASample03Actor::spkpos_inertial()
{
    // We're going to compute the sun's (apparent) position as of: now :).
    // Outputs:
    FSDistance Range;
    FSAngle RightAscension;
    FSAngle Declination;

    // Intermediate outputs:
    // r: sun's position relative to earth
    // lt: the light travel time from sun to earth
    FSDistanceVector r;
    FSEphemerisPeriod lt;

    ES_ResultCode ResultCode;
    FString ErrorMessage;

    // When do we want it?   (time: now)
    FSEphemerisTime et;
    USpice::et_now(et);

    // What do we want?  (SUN's position)
    FString targ = TEXT("SUN");

    // Where do we want it relative to? (EARTH's position)
    FString obs = TEXT("EARTH");

    // What reference frame (coordinate system orientation)?
    // J2000 (also known as EME 2000, and is actually ICRF)
    FString ref = TEXT("J2000");

    // "Converged Newtonian" light time correction.
    // This means our result won't be where the sun actually *IS* right now...
    // ...It will be where the sun *APPEARS* to be... In otherwords, where it was when
    // the light arriving here now left the sun.  'lt' time ago.
    ES_AberrationCorrectionWithNewtonians abscorr = ES_AberrationCorrectionWithNewtonians::CN;

    // Call SPICE, get the position in rectangular coordinates...
    USpice::spkpos(ResultCode, ErrorMessage, et, r, lt, targ, obs, ref, abscorr);


    // Rectangular coordinates are not intuitive!   Distant Astronomical Objects are usually tracked by Right Ascension & Declination.
    // Here we convert rectangular ECEF coordinates to RA/Dec
    USpice::recrad(r, Range, RightAscension, Declination);

    double au = 0.;
    if (ResultCode == ES_ResultCode::Success)
    {

        // Kilometers are less interesting than a more geometrically relevant measure, like AU... So, convert kilometers to AU...
        USpice::convrt(ResultCode, ErrorMessage, Range.AsKilometers(), ES_Units::KILOMETERS, ES_Units::AU, au);
    }

    // We can format RA/Dec to look all pretty like so
    FString PrettyRADec = USpiceTypes::FormatRADec(RightAscension, Declination);

    Log(FString::Printf(TEXT("Sun:  Right Ascension/Declination = %s, Range = %f AU, Light Travel Time %f seconds"), *PrettyRADec, au, lt.AsSeconds()), ResultCode);
}



// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: spkpos_fixed
// Desc:
// Find high precision geodetic & geographic lat/lon coordinates for DSS-14
//-----------------------------------------------------------------------------

void ASample03Actor::spkpos_fixed()
{
    FSDistanceVector r;
    FSEphemerisPeriod lt;

    ES_ResultCode ResultCode;
    FString ErrorMessage;

    // When do we want it?   (time: now)
    FSEphemerisTime et;
    USpice::et_now(et);

    // DSS 14 is a 70-meter antenna operated by JPL @ Goldstone Deep Space 
    // Communications Complex (Near Barstow, California)
    // It's Naif Name is DSS-14
    // https://www.nasa.gov/directorates/heo/scan/services/networks/deep_space_network/complexes/70-meter
    FString targ = TEXT("DSS-14");

    // Let's get the Latitude, Longitude, and Altitude of  
    FString obs = TEXT("EARTH");

    // ITRF is an Earth-Centered Earth-Fixed "fixed" reference frame that rotates with the earth.
    // Fixed-body (rotating) frames are usually IAU_* (IAU_MOON, IAU_EARTH, IAU_MARS, etc...)
    FString ref = TEXT("ITRF93");

    ES_AberrationCorrectionWithNewtonians abscorr = ES_AberrationCorrectionWithNewtonians::None;

    // Call SPICE, get the position in rectangular coordinates...
    USpice::spkpos(ResultCode, ErrorMessage, et, r, lt, targ, obs, ref, abscorr);

    // What reference spheroid should we use?
    // We could look up Re/Rp from bodvrd, but ITRF93 is based on GRS 80, which is defined by set values.
    // https://en.wikipedia.org/wiki/Geodetic_Reference_System_1980

    const double GRS80_f_inverse = 298.257222100882711243;
    const double GRS80_b = 6356752.314140347;  // meters

    const double GRS80_f = 1. / GRS80_f_inverse;
    const double GRS80_a = GRS80_b / (1. - GRS80_f);
        
    FSDistance Re = FSDistance::FromMeters(GRS80_a);

    // First, the geographic coordinates
    FSPlanetographicVector GeographicPosition;
    USpice::recpgr(ResultCode, ErrorMessage, r, Re, GeographicPosition, TEXT("EARTH"), GRS80_f);

    Log(FString::Printf(TEXT("DSS-14 Geographic Lon/Lat/Alt = %s"), *USpiceTypes::Conv_SPlanetographicVectorToString(GeographicPosition)), ResultCode);
    Log(FString::Printf(TEXT("DSS-14 Geographic Lon/Lat = %s"), *USpiceTypes::FormatLonLat(GeographicPosition.lonlat, TEXT(", "), ES_AngleFormat::DMS)), ResultCode);


    // Now, the geodetic coordinates
    FSGeodeticVector GeodeticPosition;
    USpice::recgeo(r, Re, GeodeticPosition, GRS80_f);

    Log(FString::Printf(TEXT("DSS-14 Geodetic Lon/Lat/Alt = %s"), *USpiceTypes::Conv_SGeodeticVectorToString(GeodeticPosition)), ResultCode);
    Log(FString::Printf(TEXT("DSS-14 Geodetic Lon/Lat = %s"), *USpiceTypes::FormatLonLat(GeodeticPosition.lonlat, TEXT(", "), ES_AngleFormat::DMS)), ResultCode);

    Log(TEXT("Note that in SPICE Longitude preceeds Latitude; MaxQ remains consistent with SPICE"));
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: spkezr_inertial
// Desc: What direction is Mercury?  How fast is it moving?
//-----------------------------------------------------------------------------
/*
* Additional Info: spkezr SPICE documentation
* https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkezr_c.html
*/

void ASample03Actor::spkezr_inertial()
{
    // Let's figure out what direction the sun is shining on the earth with spkezr
    FSStateVector state;
    FSEphemerisPeriod lt;

    ES_ResultCode ResultCode;
    FString ErrorMessage;

    // When do we want it?   (time: now)
    FSEphemerisTime et;
    USpice::et_now(et);

    // Where's planet Mercury right now?
    FString targ = TEXT("MERCURY");

    // SSB = Solar System Barycenter, the point around which the planets, sun, move.
    FString obs = TEXT("SSB");

    // Reference Frame for results (Coordinate System orientation only)
    // ECLIPJ2000 is aligned with the Solar System's Ecliptic Plane...
    // ...The plane the planets orbit in (roughly)
    FString ref = TEXT("ECLIPJ2000");

    // Don't worry about light travel time (abscorr = None)
    ES_AberrationCorrectionWithNewtonians abscorr = ES_AberrationCorrectionWithNewtonians::None;

    // Call SPICE, get the state vector in rectangular coordinates...
    USpice::spkezr(ResultCode, ErrorMessage, et, state, lt, targ, obs, ref, abscorr);

    Log(FString::Printf(TEXT("Mercury State Vector = %s"), *USpiceTypes::Conv_SStateVectorToString(state)), ResultCode);
}




// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: spkezr_fixed
// Desc: What direction is the sun wrt Moon's surface?
//-----------------------------------------------------------------------------
/*
* In addition to the SPICE functionality demonstrated here, also see:
* https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkcpo_c.html
* https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkcvo_c.html
* https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkcpt_c.html
* https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkcvt_c.html
*
* The "Constant Position" and "Constant Velocity" observer/target
* actions are important for things that may not be covered in SPK kernels
*
* Examples:
* spaceship moving in real-time in unreal engine via UE physics
* your home
* etc
*/

void ASample03Actor::spkezr_fixed()
{
    // Let's figure out what direction the sun is shining on the earth with spkezr
    FSStateVector state;
    FSEphemerisPeriod lt;

    ES_ResultCode ResultCode;
    FString ErrorMessage;

    // When do we want it?   (time: now)
    FSEphemerisTime et;
    USpice::et_now(et);

    // Where's that sun right now?
    FString targ = TEXT("SUN");

    // Position relative to Moon's center  
    FString obs = TEXT("MOON");

    // Returned in Moon's Fixed Frame (IAU_* = body-fixed, rotates with surface)
    // We could determine the phase of the moon from the results...
    FString ref = TEXT("IAU_MOON");

    // Don't worry about light travel time (abscorr = None)
    ES_AberrationCorrectionWithNewtonians abscorr = ES_AberrationCorrectionWithNewtonians::None;

    // Call SPICE, get the state vector in rectangular coordinates...
    USpice::spkezr(ResultCode, ErrorMessage, et, state, lt, targ, obs, ref, abscorr);

    Log(FString::Printf(TEXT("Sun's State Vector in Moon's Fixed Frame = %s"), *USpiceTypes::Conv_SStateVectorToString(state)), ResultCode);

    FSDistanceVector MoonRadii;
    USpice::bodvrd_distance_vector(ResultCode, ErrorMessage, MoonRadii, TEXT("MOON"));

    FSDistance Re = MoonRadii.x, Rp = MoonRadii.z;
    Log(FString::Printf(TEXT("Moon's Equatorial Radius=%s km, Polar Radius=%s km"), *USpiceTypes::Conv_SDistanceToString(Re), *USpiceTypes::Conv_SDistanceToString(Rp)), ResultCode);

    FSGeodeticVector GeodeticPosition;
    USpice::recgeo(state.r, MoonRadii.x, GeodeticPosition, (Re-Rp)/Re);

    Log(FString::Printf(TEXT("Sun's Geodetic Position in Moon's Fixed Frame = %s"), *USpiceTypes::Conv_SGeodeticVectorToString(GeodeticPosition)), ResultCode);

    // In Frame IAU_Moon, The Sun's Longitude 180 = New Moon, 90 = First Quarter, 0 = Full Moon.
    FString MoonPhaseString;
    int MoonPhase = FMath::RoundToInt(8. * USpiceTypes::normalize180to180(GeodeticPosition.lonlat.longitude.AsDegrees()) / 360.);
    switch (MoonPhase)
    {
    case -3:
        MoonPhaseString = TEXT("Waning Crescent");
        break;
    case -2:
        MoonPhaseString = TEXT("Last Quarter");
        break;
    case -1:
        MoonPhaseString = TEXT("Waning Gibbous");
        break;
    case 0:
        MoonPhaseString = TEXT("Full Moon");
        break;
    case 1:
        MoonPhaseString = TEXT("Waxing Gibbous");
        break;
    case 2:
        MoonPhaseString = TEXT("First Quarter");
        break;
    case 3:
        MoonPhaseString = TEXT("Waxing Crescent");
        break;
    default:
        MoonPhaseString = TEXT("New Moon");
        break;
    }

    Log(FString::Printf(TEXT("Moon's Phase= %s"), *MoonPhaseString), ResultCode);
}



// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: azlcpo
// Desc: What direction do we aim an antenna to communicate with Mars?
//-----------------------------------------------------------------------------
/*
* Additional info: azlcpo SPICE documentation:
* https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/azlcpo_c.html
*/

void ASample03Actor::azlcpo(ES_AberrationCorrectionWithTransmissions abcorr)
{
    FString CaseName = USpiceTypes::toString(abcorr);
    switch (abcorr)
    {
    case ES_AberrationCorrectionWithTransmissions::LT_S:
        CaseName = TEXT("reception (receive messages from this direction)");
        break;
    case ES_AberrationCorrectionWithTransmissions::XLT_S:
        CaseName = TEXT("transmission (direction to transmit a message)");
        break;
    }

    ES_ResultCode ResultCode;
    FString ErrorMessage;
    // State Vector in Range/Azimuth/Elevation (output)
    FSDimensionlessStateVector azlsta;
    // Light Travel Time (output)
    FSEphemerisPeriod lt;
    
    // et = 'now'
    FSEphemerisTime et;
    USpice::et_now(et);

    // azl-'cpo' means a Constant Position Offset.
    // This is valuable when we don't have an SPK id / SPK data for
    // the location (on earth).  We could set it relative to a fixed point on earth (IAU_EARTH or ITRF frame),
    // fixed point on IAU_MOON, IAU_MARS, etc...
    // But in this case we DO have SPK position data, under Naif Id "DSS-14".
    const FSDistanceVector obspos = FSDistanceVector();
    const FString obsctr = FString("DSS-14");

    // Reference Frame != Naif Id
    // Get the position in the DSS-14 'Topocentric' frame.  This frame was defined in the FK/stations/earth_topo_...
    // kernel with Z = "up" (towards sky), Azimuth (Direction, 0 = north), and Elevation (Angle above/below surface)
    const FString obsref = FString("DSS-14_TOPO");

    // What do we want the direction of?  The Insight Mission Landing Site is well defined in data.
    const FString target = FString("INSIGHT_LANDING_SITE");
    
    // Measure Azimuth Clockwise
    bool azccw = false;

    // Measure Elevation Positive when Z is positive
    bool elplsz = true;

    // (Only ELLIPSOID is supported)
    ES_LocalZenithMethod method = ES_LocalZenithMethod::ELLIPSOID;

    USpice::azlcpo(ResultCode, ErrorMessage, azlsta, lt, et, obspos, obsctr, obsref, target, azccw, elplsz, abcorr, method);

    // The result is in an FSDimensionlessStateVector, which is a catch-all when we don't have a set data type result
    // (There is no Range/Azimuth/Elevation state vector defined, which is a valid MaxQ enhancement request)

    // azlsta.r = Range/Azimuth/Elevation
    FSDistance range = FSDistance(azlsta.r.x);
    FSAngle az = FSAngle(azlsta.r.y);
    FSAngle el = FSAngle(azlsta.r.z);

    // azlsta.dr = Derivatives of azlsta.r
    FSSpeed speed = FSSpeed(azlsta.dr.x);
    FSAngularRate daz = FSAngularRate(azlsta.dr.y);
    FSAngularRate del = FSAngularRate(azlsta.dr.z);


    // Print Range/Az/El km/deg (0,-360]/deg (-180,180]
    // Compare with:
    // https://www.heavens-above.com/PlanetSummary.aspx?lat=35.4259&lng=-116.8897&loc=Mars+DSS-14&alt=0&tz=PST
    Log(FString::Printf(TEXT("To Insight Mars Landing Site From DSS-14 %s: Range=%s km; Azimuth=%s; Elevation=%s"), *CaseName , *USpiceTypes::Conv_SDistanceToString(range), *USpiceTypes::FormatAngle(az, ES_AngleFormat::DD_360), *USpiceTypes::FormatAngle(el, ES_AngleFormat::DD_180)), ResultCode);
    Log(FString::Printf(TEXT("To Insight Mars Landing Site From DSS-14 %s: dRange=%f km/s; dAzimuth=%f deg/sec; dElevation=%f deg/sec"), *CaseName, speed.AsKilometersPerSecond(), daz.AsDegreesPerSecond(), del.AsDegreesPerSecond()), ResultCode);
    Log(FString::Printf(TEXT("To Insight Mars Landing Site From DSS-14 %s light travel time= %f sec"), *CaseName, USpiceTypes::Conv_SEphemerisPeriodToDouble(lt)), ResultCode);
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: Initialize Solar System Animation
// Desc: 
//-----------------------------------------------------------------------------

void ASample03Actor::InitializeSolarSystem(FSamplesSolarSystemState& State)
{
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage = "";

    FString AbsPathToOuterPlanetSPKFixups = MaxQSamples::MaxQPathAbsolutified(RelativePathToOuterPlanetSPKFixups);
    USpice::furnsh(ResultCode, ErrorMessage, AbsPathToOuterPlanetSPKFixups);
    Log(FString::Printf(TEXT("InitializeSolarSystem loaded kernel file %s"), *AbsPathToOuterPlanetSPKFixups), ResultCode);

    USampleUtilities::InitializeTime(State);

    AActor* Actor = nullptr;
    FString ActorName;

    // Iterate over all actors in the scene
    for (TActorIterator<AActor> ActorIterator(GetWorld()); ActorIterator; ++ActorIterator)
    {
        Actor = *ActorIterator;

        // Drill down on all celestial bodies
        if (Actor && Actor != this && Actor->ActorHasTag("BODY"))
        {
            // Use the actor name to get radii info from the kernel pool
            Actor->GetName(ActorName);

            ActorName.RemoveFromStart(TEXT("BP_"));

            int32 TrailingIndex;
            if (ActorName.FindChar('_', TrailingIndex))
            {
                ActorName.RemoveAt(TrailingIndex, ActorName.Len() - TrailingIndex);
            }

            FSDistanceVector Radii;
            USpice::bodvrd_distance_vector(ResultCode, ErrorMessage, Radii, ActorName, TEXT("RADII"));

            if (ResultCode == ES_ResultCode::Success)
            {
                // Get the dimensions of the static mesh at the root...  (ringed planets have multiple meshes)
                UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(Actor->GetRootComponent());

                if (SM && SM->GetStaticMesh())
                {
                    // Don't scale the sun, or it's impossible to see Mercury etc without them ending up inside the sun.
                    if(ActorName != FString("SUN"))
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

                    SolarSystemState.SolarSystemBodyMap.Add(FName(ActorName), Actor);
                }
                else
                {
                    Log(FString::Printf(TEXT("InitializeSolarSystem could not find static mesh for %s"), *ActorName), FColor::Red);
                }
            }
            else
            {
                Log(FString::Printf(TEXT("InitializeSolarSystem kernel pool RADII failed for %s"), *ActorName), FColor::Red);
            }
        }
    }
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: Update Solar System Animation
// Desc: 
//-----------------------------------------------------------------------------

void ASample03Actor::UpdateSolarSystem(FSamplesSolarSystemState& State, float DeltaTime)
{
    SolarSystemState.CurrentTime += DeltaTime * SolarSystemState.TimeScale;

    // Intermediate outputs:
    // r: sun's position relative to earth
    // lt: the light travel time from sun to earth
    FSDistanceVector r;
    FSEphemerisPeriod lt;

    ES_ResultCode ResultCode;
    FString ErrorMessage;

    // When do we want it?   (time: now)
    FSEphemerisTime et = SolarSystemState.CurrentTime;

    // Where do we want it relative to?
    // SSB = Solar System Barycenter, the point the sun and planets mutually orbit
    // ECLIPJ2000 = Inertial (non-rotating) reference frame alighned with Ecliptic (the plane of Earth's orbit)
    FString obs = OriginNaifName.ToString();
    FString ref = OriginReferenceFrame.ToString();

    // "Converged Newtonian" light time correction.
    // This means our result won't be where the sun actually *IS* right now...
    // ...It will be where the sun *APPEARS* to be... In otherwords, where it was when
    // the light arriving here now left the sun.  'lt' time ago.
    ES_AberrationCorrectionWithNewtonians abscorr = ES_AberrationCorrectionWithNewtonians::CN;

    for (auto BodyPair : SolarSystemState.SolarSystemBodyMap)
    {
        AActor* Actor = BodyPair.Value.Get();

        if (Actor)
        {
            // Targ = NaifName = Map Key
            FString targ = BodyPair.Key.ToString();

            // Call SPICE, get the position in rectangular coordinates...
            USpice::spkpos(ResultCode, ErrorMessage, et, r, lt, targ, obs, ref, abscorr);

            if (ResultCode == ES_ResultCode::Success)
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
            else
            {
                // If the call failed, there's insufficient SPK data for this time, so reset the clock.
                Restart();

                // Slow the timescale down each time it repeats...
                SlowerSpeed();
            }
        }
    }

    if (GEngine)
    {
        double UE_Units_Per_KM = 100 * 1000.;
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Scale SUN : 1/%f"), UE_Units_Per_KM));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Scale PLANETS/MOON : 1/%f"), BodyScale * UE_Units_Per_KM));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Scale Solar System Distances : 1/%f"), DistanceScale * UE_Units_Per_KM));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Display Time: %s"), *USpiceTypes::Conv_SEpheremisTimeToString(SolarSystemState.CurrentTime)));
    }
}

void ASample03Actor::VeryFastSpeed()
{
    NormalSpeed();
    FasterSpeed();
    FasterSpeed();
    FasterSpeed();
    FasterSpeed();
    FasterSpeed();
    FasterSpeed();
    FasterSpeed();
}

void ASample03Actor::FasterSpeed()
{
    SolarSystemState.TimeScale *= 10.;
}

void ASample03Actor::SlowerSpeed()
{
    SolarSystemState.TimeScale *= 0.1;
}

void ASample03Actor::NormalSpeed()
{
    SolarSystemState.TimeScale = 1;
}

void ASample03Actor::GoToNow()
{
    USpice::et_now(SolarSystemState.CurrentTime);
    NormalSpeed();
}

void ASample03Actor::Restart()
{
    USampleUtilities::InitializeTime(SolarSystemState, false);
}