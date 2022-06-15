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
#include "SampleNametagWidget.h"
#include "Sample05TelemetryActor.generated.h"

class UStaticMeshComponent;

// This actor represents an object who's state was obtained
// by the celestrak server... It updates its location
// ("propagates" its orbit) to a given time and displays a position.
// The orbit is updated from "Two-Line Elements" NORAD
// type telemetry data.
// Also, it renders a debug orbit, which is computed from it's
// current state.
UCLASS(BlueprintType)
class MAXQCPPSAMPLES_API ASample05TelemetryActor : public AActor
{
    GENERATED_BODY()

public:

    UPROPERTY(EditDefaultsOnly, Category = "MaxQ|Samples")
    TObjectPtr<UStaticMeshComponent> MeshComponent;

    UPROPERTY(EditDefaultsOnly, Category = "MaxQ|Samples")
    TSubclassOf<USampleNametagWidget> NametagWidgetClass;

    UPROPERTY(EditAnywhere, Category = "MaxQ|Samples")
    double VelocityBumpFraction;

    UPROPERTY(EditInstanceOnly, Transient, Category = "MaxQ|Samples")
    TWeakObjectPtr<USampleNametagWidget> NametagWidgetInstance;

    UPROPERTY(EditInstanceOnly, Transient, Category = "MaxQ|Samples")
    FString ObjectId;

    UPROPERTY(EditInstanceOnly, Transient, Category = "MaxQ|Samples")
    FString ObjectName;

    UPROPERTY(EditInstanceOnly, Transient, Category = "MaxQ|Samples")
    FSTwoLineElements TLElements;

    UPROPERTY(EditInstanceOnly, Transient, Category = "MaxQ|Samples")
    FSTLEGeophysicalConstants GeophysicalConstants;

    UPROPERTY(EditInstanceOnly, Transient, Category = "MaxQ|Samples")
    bool PropagateStateByTLEs = true;

    UPROPERTY(EditInstanceOnly, Transient, Category = "MaxQ|Samples")
    FSConicElements KeplerianElements;

    UPROPERTY()
    FPositionUpdate PositionUpdate;

    UPROPERTY()
    FVisibilityUpdate VisibilityUpdate;

    FTLEGetStateVectorCallback PropagateByTLEs;
    FXformPositionCallback XformPositionCallback;
    FComputeConic ComputeConic;
    FRenderDebugOrbit RenderDebugOrbit;
    FEvaluateOrbitalElements PropagateByKeplerianElements;
    FGetOrbitalElements GetOrbitalElements;
    FGetConicFromKepler GetConicFromKepler;

    bool bWasVisible = false;
    bool bShouldRenderOrbit;

    FSEllipse OrbitalConic;
    bool bIsHyperbolic;

public:
    ASample05TelemetryActor();

    void BeginPlay() override;
    void Init(const FString& NewObjectId, const FString& NewObjectName, const FSTwoLineElements& NewTLEs, bool bNewShouldRenderOrbit);
    void Tick(float DeltaSeconds) override;
    void PropagateTLE();
    void PropagateKepler();

    void GoKeplerian();
    void BumpVelocity(const FSVelocityVector& Direction);

    UFUNCTION(CallInEditor, Category = "Editor")
    void BumpPrograde();

    UFUNCTION(CallInEditor, Category = "Editor")
    void BumpRetrograde();

    UFUNCTION(CallInEditor, Category = "Editor")
    void BumpRadial();

    UFUNCTION(CallInEditor, Category = "Editor")
    void BumpAntiRadial();

    UFUNCTION(CallInEditor, Category = "Editor")
    void BumpNormal();

    UFUNCTION(CallInEditor, Category = "Editor")
    void BumpAntiNormal();
};


