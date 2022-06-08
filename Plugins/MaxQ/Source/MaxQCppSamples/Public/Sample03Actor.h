// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpiceTypes.h"
#include "Sample03Actor.generated.h"




//-----------------------------------------------------------------------------
// FSolarSystemState
// Track the state of a small demo animated solar system
//-----------------------------------------------------------------------------

USTRUCT()
struct MAXQCPPSAMPLES_API FSolarSystemState
{
    GENERATED_BODY();

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    bool InitializeTimeToNow;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FSEphemerisTime InitialTime;

    UPROPERTY(Transient)
    FSEphemerisTime CurrentTime;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FSEphemerisPeriod TimeScale;

    UPROPERTY(Transient)
    TMap<FName,TWeakObjectPtr<AActor> > SolarSystemBodyMap;
};


//-----------------------------------------------------------------------------
// Sample03
// Basic positions and state vectors (Spice SPK)
//-----------------------------------------------------------------------------

UCLASS()
class MAXQCPPSAMPLES_API ASample03Actor : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    TArray<FString> BasicKernels;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    TArray<FString> Itrf93Kernels;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    TArray<FString> InsightMissionKernels;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FString RelativePathToOuterPlanetSPKFixups;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FSolarSystemState SolarSystemState;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    double BodyScale;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    double DistanceScale;


public:
    ASample03Actor();
    void BeginPlay() override;
    void Tick(float DeltaTime) override;

    void spkpos_inertial();
    void spkpos_fixed();
    void spkezr_inertial();
    void spkezr_fixed();
    void azlcpo(ES_AberrationCorrectionWithTransmissions abcorr);

    void InitializeSolarSystem(FSolarSystemState& State);
    void UpdateSolarSystem(FSolarSystemState& State, float DeltaTime);

    UFUNCTION(CallInEditor)
    void FastSpeed();

    UFUNCTION(CallInEditor)
    void NormalSpeed();

    UFUNCTION(CallInEditor)
    void GoToNow();
};


