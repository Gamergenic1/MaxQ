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

UCLASS()
class MAXQCPPSAMPLES_API ASample05Actor : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FSamplesSolarSystemState SolarSystemState;

public:
    ASample05Actor();

    void BeginPlay() override;
};


