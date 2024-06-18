// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "SpiceConstants.h"
#include "SpiceTypes.h"
#include "SampleUtilities.h"
#include "GameFramework/Actor.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "Sample06Actor.generated.h"

class AActor;

//-----------------------------------------------------------------------------
// Sample06
// Authoring new planets, etc
//-----------------------------------------------------------------------------

UCLASS(Blueprintable, HideCategories=(Transform, Rendering, Replication, Collision, HLOD, Input, Actor, Advanced, Cooking))
class MAXQCPPSAMPLES_API ASample06Actor : public AActor
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = "MaxQ|Samples")
    TArray<FString> TrappistSystemKernels;

    UPROPERTY(EditAnywhere, Category = "MaxQ|Samples")
    FSamplesSolarSystemState SolarSystemState;

    UPROPERTY(EditAnywhere, Category = "MaxQ|Samples")
    double BodyScale;

    UPROPERTY(EditAnywhere, Category = "MaxQ|Samples")
    double DistanceScale;

    UPROPERTY(EditAnywhere, Category = "MaxQ|Samples")
    FName OriginNaifName;

    UPROPERTY(EditAnywhere, Category = "MaxQ|Samples")
    FName OriginReferenceFrame;

    UPROPERTY(EditAnywhere, Category = "MaxQ|Samples")
    FName SunNaifName;

    UPROPERTY(EditAnywhere, Category = "MaxQ|Samples")
    FName PlanetFocusName;

    UPROPERTY(EditAnywhere, Category = "MaxQ|Samples")
    TMap<FString, FSConicElements> OrbitalElements;

    UPROPERTY(EditAnywhere, Category = "MaxQ|Samples")
    bool UpdateSpkFile = false;

    UPROPERTY(EditAnywhere, Category = "MaxQ|Samples")
    FString RelativePathToSPKFile;

    UPROPERTY(EditAnywhere, Category = "MaxQ|Samples")
    TArray<FString> CommentsToWrite;

    UPROPERTY(EditAnywhere, Category = "MaxQ|Samples")
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
    void TRAPPIST_1_SSB();

    UFUNCTION(CallInEditor, Category = "Editor")
    void _1B();

    UFUNCTION(CallInEditor, Category = "Editor")
    void _1C();

    UFUNCTION(CallInEditor, Category = "Editor")
    void _1D();

    UFUNCTION(CallInEditor, Category = "Editor")
    void _1E();

    UFUNCTION(CallInEditor, Category = "Editor")
    void _1F();

    UFUNCTION(CallInEditor, Category = "Editor")
    void _1G();

    UFUNCTION(CallInEditor, Category = "Editor")
    void _1H();


    UFUNCTION(CallInEditor, Category = "Editor")
        void IAU_1();

    UFUNCTION(CallInEditor, Category = "Editor")
        void IAU_1B();

    UFUNCTION(CallInEditor, Category = "Editor")
        void IAU_1C();

    UFUNCTION(CallInEditor, Category = "Editor")
        void IAU_1D();

    UFUNCTION(CallInEditor, Category = "Editor")
        void IAU_1E();

    UFUNCTION(CallInEditor, Category = "Editor")
        void IAU_1F();

    UFUNCTION(CallInEditor, Category = "Editor")
        void IAU_1G();

    UFUNCTION(CallInEditor, Category = "Editor")
        void IAU_1H();

    UFUNCTION(CallInEditor, Category = "Editor")
    void TRAPPIST_ECLIPTIC();

    UFUNCTION(CallInEditor, Category = "Editor")
    void ECLIPTIC_POLE();

    UFUNCTION(CallInEditor, Category = "Editor")
    void View_From_EARTH();

    UFUNCTION(BlueprintNativeEvent, Category = "Editor")
    void ResetYawPitch();


private:
    // The pawn camera yaw pitch roll means if the reference frame is re-set it won't actually
    // be aligned, unless the pawn camera resets its yaw pitch roll as well
    static const TMap<FString, FSConicElements>& GetTrappist1OrbitalElements();
};


