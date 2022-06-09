// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "SampleUtilities.h"
#include "Sample05Actor.generated.h"


//-----------------------------------------------------------------------------
// Sample05
// Kepler Orbits, TLE's, and more...
//-----------------------------------------------------------------------------

/* THIS SAMPLE IS IN PROGRESS */

/* ****************************************************************************
*  This tutorial is only an interim version.
*  ***************************************************************************/

// Kepler orbits are paramatized by geometric properties.
// * Semi-Major axis (or equivalent, such as "perifocal" distance)
// * Elliptical Eccentricity
// * 3 DOF Orientation angles (or equivalents)
//     * Inclination
//     * Argument of Periapsis
//     * Longitude of Ascending Node
// * Epoch (time)
// * Mean Anomaly at Epoch (or alternative, such as True Anomaly)
//
// Kepler orbits are simple to compute but inaccurate.  They're still good for
// visualizing and orbit once you have a feel for the parameters.
//
// Kepler orbit data is useful when dealing with small bodies, like
// asteroids and comets.  Orbital Elements for nearly any asteroid/comet
// Known to humans is available from NASA/JPL's Solar System Dynamics group:
// https://ssd.jpl.nasa.gov/


// "Two Line" Element (TLE) data originated from NORAD tracking telemetry.
// It remains valid for a brief time (a few days)
// It's more commonly used at least with anything orbiting Earth.
// Various orbit "propagators" have been used.  SPICE will use "sgp4" here.

// TLE data from Satellite Catalog (SatCat) REST APIs such as space-track.org.
// For an example of querying this data from Unreal Engine, see:
// https://gamedevtricks.com/post/call-satcat-rest-api-from-ue-http/
// https://stupidrockettricks.com/post/call-satcat-rest-api-from-ue-http/
// https://github.com/gamergenic/ASATDebrisVisualization
// (Kepler/Conic orbit data is available as well, of course.)


UCLASS()
class MAXQCPPSAMPLES_API ASample05Actor : public AActor
{
    GENERATED_BODY()

public:

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    TArray<FString> BasicKernels;


public:
    ASample05Actor();

    void BeginPlay() override;

    void conics();
    void oscelt();
    void TLEs();
};


