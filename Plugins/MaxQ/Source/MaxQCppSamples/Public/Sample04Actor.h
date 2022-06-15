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
#include "Sample04Actor.generated.h"

class AActor;

//-----------------------------------------------------------------------------
// Sample04
// Setting orientations with PCK Kernels, Reference Frames, and more
//-----------------------------------------------------------------------------

UCLASS()
class MAXQCPPSAMPLES_API ASample04Actor : public AActor
{
    GENERATED_BODY()

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    TArray<FString> BasicKernels;

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
    FName SatelliteName;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    TWeakObjectPtr<AActor> SunDirectionalLight;

public:
    ASample04Actor();

    void BeginPlay() override;
    void Tick(float DeltaSeconds) override;

    void pxform();
    void sxform(const FSEphemerisTime& et);
    void sxform_xf2rav(const FSEphemerisTime& et);
    void GetUERotationAndAngularVelocity(const FSEphemerisTime& et, const FName& ReferenceFrame, const FName& BodyName, bool DontLog = false);

    void InitializeSolarSystem();
    void UpdateSolarSystem(float DeltaTime);

    // This is what you came for!.
    bool UpdateBodyOrientations();


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
    void EMB() { OriginNaifName = MaxQ::Constants::Name_EMB; }

    UFUNCTION(CallInEditor, Category = "Editor")
    void Earth() { OriginNaifName = MaxQ::Constants::Name_EARTH; }

    UFUNCTION(CallInEditor, Category = "Editor")
    void Moon() { OriginNaifName = MaxQ::Constants::Name_MOON; }

    UFUNCTION(CallInEditor, Category = "Editor")
    void J2000() { OriginReferenceFrame = MaxQ::Constants::Name_J2000; }

    UFUNCTION(CallInEditor, Category = "Editor")
    void EclipJ2000() { OriginReferenceFrame = MaxQ::Constants::Name_ECLIPJ2000; }

    UFUNCTION(CallInEditor, Category = "Editor")
    void IAU_EARTH() { OriginReferenceFrame = MaxQ::Constants::Name_IAU_EARTH; }

    UFUNCTION(CallInEditor, Category = "Editor")
    void IAU_MOON() { OriginReferenceFrame = MaxQ::Constants::Name_IAU_MOON; }
};


