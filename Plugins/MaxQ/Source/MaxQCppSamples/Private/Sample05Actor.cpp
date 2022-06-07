// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "Sample05Actor.h"
#include "SampleUtilities.h"

using MaxQSamples::Log;

//-----------------------------------------------------------------------------
// Sample05
// Kepler Orbits, TLE's, and more...
//-----------------------------------------------------------------------------
ASample05Actor::ASample05Actor()
{
    SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
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

}
