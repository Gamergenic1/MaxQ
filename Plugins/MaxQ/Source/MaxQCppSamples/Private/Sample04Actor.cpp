// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "Sample04Actor.h"
#include "SampleUtilities.h"

using MaxQSamples::Log;

//-----------------------------------------------------------------------------
// Sample04
// Setting orientations with PCK Kernels, Reference Frames, and more
//-----------------------------------------------------------------------------
ASample04Actor::ASample04Actor()
{
    SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
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
}


