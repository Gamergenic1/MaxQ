// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "SpiceTypes.h"
#include "SampleUtilities.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "Sample06Actor.generated.h"

class AActor;

//-----------------------------------------------------------------------------
// Sample06
// Authoring new planets, etc
//-----------------------------------------------------------------------------

UCLASS()
class MAXQCPPSAMPLES_API ASample06Actor : public AActor
{
    GENERATED_BODY()

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    TArray<FString> TrappistSystemKernels;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FSamplesSolarSystemState SolarSystemState;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    double BodyScale;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    double DistanceScale;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FName OriginNaifName;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FName OriginReferenceFrame;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FName SunNaifName;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FName PlanetFocusName;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    TMap<FString, FSConicElements> OrbitalElements;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FString RelativePathToSPKFileToRead;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FString RelativePathToSPKFileToWrite;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    TArray<FString> CommentsToWrite;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    TWeakObjectPtr<AActor> SunDirectionalLight;

public:
    ASample06Actor();

    void BeginPlay() override;
    void Tick(float DeltaSeconds) override;

    void InitializeSolarSystem();
    void UpdateSolarSystem(float DeltaTime);


    //-----------------------------------------------------------------------------
    // The list of custom-make kernels for the Trappist-1 system
    //-----------------------------------------------------------------------------
    UFUNCTION(BlueprintPure, Category = "MaxQSamples", meta = (DevelopmentOnly))
    static void GetDefaultTrappistKernels(TArray<FString>& TrappistSystemKernelsArray);

    //-----------------------------------------------------------------------------
    // Generates the system binary SPK (ephemeris position) file.
    //-----------------------------------------------------------------------------
    UFUNCTION(CallInEditor, Category = "Editor")
    void GenerateTrappistSPKKernel();


    //-----------------------------------------------------------------------------
    // Button controls for the Details Panel
    //-----------------------------------------------------------------------------

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

    UFUNCTION(CallInEditor, Category = "Editor")
    void SSB() { OriginNaifName = "TRAPPIST_1_BARYCENTER"; }

    UFUNCTION(CallInEditor, Category = "Editor")
    void _1B() { OriginNaifName = "TRAPPIST_1B"; }

    UFUNCTION(CallInEditor, Category = "Editor")
    void _1C() { OriginNaifName = "TRAPPIST_1D"; }

    UFUNCTION(CallInEditor, Category = "Editor")
    void _1D() { OriginNaifName = "TRAPPIST_1D"; }

    UFUNCTION(CallInEditor, Category = "Editor")
    void _1E() { OriginNaifName = "TRAPPIST_1E"; }

    UFUNCTION(CallInEditor, Category = "Editor")
    void _1F() { OriginNaifName = "TRAPPIST_1F"; }

    UFUNCTION(CallInEditor, Category = "Editor")
    void _1G() { OriginNaifName = "TRAPPIST_1G"; }


    UFUNCTION(CallInEditor, Category = "Editor")
        void IAU_1() { OriginReferenceFrame = "IAU_TRAPPIST_1"; }

    UFUNCTION(CallInEditor, Category = "Editor")
        void IAU_1B() { OriginReferenceFrame = "IAU_TRAPPIST_1B"; }

    UFUNCTION(CallInEditor, Category = "Editor")
        void IAU_1C() { OriginReferenceFrame = "IAU_TRAPPIST_1C"; }

    UFUNCTION(CallInEditor, Category = "Editor")
        void IAU_1D() { OriginReferenceFrame = "IAU_TRAPPIST_1D"; }

    UFUNCTION(CallInEditor, Category = "Editor")
        void IAU_1E() { OriginReferenceFrame = "IAU_TRAPPIST_1E"; }

    UFUNCTION(CallInEditor, Category = "Editor")
        void IAU_1F() { OriginReferenceFrame = "IAU_TRAPPIST_1F"; }

    UFUNCTION(CallInEditor, Category = "Editor")
        void IAU_1G() { OriginReferenceFrame = "IAU_TRAPPIST_1G"; }

    UFUNCTION(CallInEditor, Category = "Editor")
        void GALACTIC() { OriginReferenceFrame = "GALACTIC"; }

    UFUNCTION(CallInEditor, Category = "Editor")
    void J2000() { OriginReferenceFrame = MaxQ::Constants::Name_J2000; }

    UFUNCTION(CallInEditor, Category = "Editor")
    void EclipJ2000() { OriginReferenceFrame = MaxQ::Constants::Name_ECLIPJ2000; }

private:
    static const TMap<FString, FSConicElements>& GetTrappist1OrbitalElements();
};


