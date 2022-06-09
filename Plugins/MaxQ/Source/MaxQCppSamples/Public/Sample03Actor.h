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
#include "SampleUtilities.h"
#include "Sample03Actor.generated.h"


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
    FSamplesSolarSystemState SolarSystemState;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    double BodyScale;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    double DistanceScale;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples", Meta=(Tooltip="Center of all coordiantes are relative to in UE Space"))
    FName OriginNaifName;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples", Meta = (Tooltip = "Reference Frame orientation all coordiantes are relative to in UE Space"))
    FName OriginReferenceFrame;


public:
    ASample03Actor();
    void BeginPlay() override;
    void Tick(float DeltaTime) override;

    void spkpos_inertial();
    void spkpos_fixed();
    void spkezr_inertial();
    void spkezr_fixed();
    void azlcpo(ES_AberrationCorrectionWithTransmissions abcorr);

    void InitializeSolarSystem(FSamplesSolarSystemState& State);
    void UpdateSolarSystem(FSamplesSolarSystemState& State, float DeltaTime);


    // Buttons for the Details Panel
    UFUNCTION(CallInEditor, Category = "Editor")
    void VeryFastSpeed();

    UFUNCTION(CallInEditor, Category = "Editor")
    void FasterSpeed();

    UFUNCTION(CallInEditor, Category = "Editor")
    void SlowerSpeed();

    UFUNCTION(CallInEditor, Category = "Editor")
    void NormalSpeed();

    UFUNCTION(CallInEditor, Category = "Editor")
    void GoToNow();

    UFUNCTION(CallInEditor, Category = "Editor")
    void Restart();
};


