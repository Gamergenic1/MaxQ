// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tutorial02Actor.generated.h"


//-----------------------------------------------------------------------------
// Tutorial02
// Time manipulation
//-----------------------------------------------------------------------------

UCLASS()
class MAXQCPPTUTORIAL_API ATutorial02Actor : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Tutorials")
    TArray<FString> RequiredKernels;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Tutorials")
    FString InsightSCLKKernel;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Tutorials")
    FString InsightMissionFKKernel;


public:
    ATutorial02Actor();
    void BeginPlay() override;
    void Tick(float DeltaTime) override;

    void InitializeSpice();

    void J2000();
    void J2020();
    void Now();
    void Insight();
};


