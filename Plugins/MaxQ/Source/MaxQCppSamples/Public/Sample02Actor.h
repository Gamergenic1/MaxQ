// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sample02Actor.generated.h"


//-----------------------------------------------------------------------------
// Sample02
// Time manipulation
//-----------------------------------------------------------------------------

UCLASS(HideCategories = (Transform, Rendering, Replication, Collision, HLOD, Input, Actor, Advanced, Cooking))
class MAXQCPPSAMPLES_API ASample02Actor : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    TArray<FString> RequiredKernels;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FString InsightSCLKKernel;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FString InsightMissionFKKernel;


public:
    ASample02Actor();
    void BeginPlay() override;
    void Tick(float DeltaTime) override;

    void InitializeSpice();

    void J2000();
    void J2020();
    void Now();
    void Insight();
};


