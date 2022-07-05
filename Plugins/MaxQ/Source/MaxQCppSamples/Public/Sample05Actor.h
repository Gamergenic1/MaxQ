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
//
// Kepler orbits are paramatized by geometric properties.
// * Semi-Major axis (or equivalent, such as "perifocal" distance)
// * Elliptical Eccentricity
// * 3 DOF Orientation angles (or equivalents)
//     * Inclination
//     * Argument of Periapsis
//     * Longitude of Ascending Node
// * Epoch (time)
// * Mean Anomaly at Epoch (or alternative, such as True Anomaly)
//
// Kepler orbits are simple to compute but inaccurate.  They're still good for
// visualizing and orbit once you have a feel for the parameters.
//
// Kepler orbit data is useful when dealing with small bodies, like
// asteroids and comets.  Orbital Elements for nearly any asteroid/comet
// Known to humans is available from NASA/JPL's Solar System Dynamics group:
// https://ssd.jpl.nasa.gov/
//
// "Two Line" Element (TLE) data originated from NORAD tracking telemetry.
// It remains valid for a brief time (a few days)
// It's more commonly used at least with anything orbiting Earth.
// Various orbit "propagators" have been used.  SPICE will use "sgp4" here.
//
// TLE data from Satellite Catalog (SatCat) REST APIs such as space-track.org.
// For an example of querying this data from Unreal Engine, see:
// https://gamedevtricks.com/post/call-satcat-rest-api-from-ue-http/
// https://stupidrockettricks.com/post/call-satcat-rest-api-from-ue-http/
// https://github.com/gamergenic/ASATDebrisVisualization
// (Kepler/Conic orbit data is available as well, of course.)


class ASample05TelemetryActor;

UCLASS(Blueprintable, HideCategories = (Transform, Rendering, Replication, Collision, HLOD, Input, Actor, Advanced, Cooking))
class MAXQCPPSAMPLES_API ASample05Actor : public AActor
{
    GENERATED_BODY()

public:

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    TArray<FString> BasicKernels;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FSamplesSolarSystemState SolarSystemState;
        
    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FString TelemetryObjectId;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    TSubclassOf<ASample05TelemetryActor> TelemetryObjectClass;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FName OriginNaifName;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FName OriginReferenceFrame;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FName SunNaifName;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    TWeakObjectPtr<AActor> SunDirectionalLight;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    double DistanceScale;

    UPROPERTY(EditInstanceOnly, Transient, Category = "MaxQ|Samples")
    FSTLEGeophysicalConstants EarthConstants;

    // Note: 'GM' is perhaps a bad name, for as there's a MaxQ::Constants::GM, among other reasons.
    UPROPERTY(EditInstanceOnly, Transient, Category = "MaxQ|Samples")
    FSMassConstant gm;

public:
    ASample05Actor();

    void BeginPlay() override;
    void Tick(float DeltaSeconds) override;
    void InitAnimation();


    // This is what you came for...
    void conics();
    void oscelt();
    void TLEs();
    void RequestTelemetryByHttp();

private:
    UFUNCTION()
    void ProcessTelemetryResponseAsTLE(bool Success, const FString& ObjectId, const FString& Telemetry);

    void AddTelemetryObject(const FString& ObjectId, const FString& ObjectName, const FSTwoLineElements& Elements);

    // This is what you came for...
    UFUNCTION(BlueprintCallable, Category = "MaxQ|Samples")
    bool PropagateTLE(const FSTwoLineElements& TLEs, FSStateVector& StateVector);

    UFUNCTION(BlueprintCallable, Category = "MaxQ|Samples")
    bool TransformPosition(const FSDistanceVector& RHSPosition, FVector& UEVector);

    UFUNCTION(BlueprintCallable, Category = "MaxQ|Samples")
    bool ComputeConic(const FSStateVector& StateVector, FSEllipse& OrbitalConicc, bool& bIsHyperbolic);

    UFUNCTION(BlueprintCallable, Category = "MaxQ|Samples")
    void RenderDebugOrbit(const FSEllipse& OrbitalConicc, bool bIsHyperbolic, const FColor& Color, float Thickness);

    UFUNCTION(BlueprintCallable, Category = "MaxQ|Samples")
    bool EvaluateOrbitalElements(const FSConicElements& KeplerianElements, FSStateVector& StateVector);

    UFUNCTION(BlueprintCallable, Category = "MaxQ|Samples")
    bool GetOrbitalElements(const FSStateVector& StateVector, FSConicElements& KeplerianElements);

    UFUNCTION(BlueprintCallable, Category = "MaxQ|Samples")
    bool GetConicFromKepler(const FSConicElements& KeplerianElements, FSEllipse& OrbitalConicc, bool& bIsHyperbolic);




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
};


