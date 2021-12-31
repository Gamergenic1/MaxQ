// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

#pragma once

#include "CoreMinimal.h"
#include "SpiceTypes.h"
#include "Spice.h"
#include "SpiceOrbits.generated.h"


UCLASS(BlueprintType, Blueprintable)
class SPICE_API USpiceOrbits : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    USpiceOrbits();

public:
    /// <summary>Converts a distance to a double (kilometers)</summary>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Orbits",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ToolTip = "Evaluates an orbit, while transforming frames if needed"
            ))
    static void EvaluateOrbit(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        FSStateVector& state,
        const FSEphemerisTime& et,
        const FSConicElements& orbit,
        const FString& orbitReferenceFrame = "ECLIPJ2000",
        const FString& observerReferenceFrame = "ECLIPJ2000"
    );


    /// <summary>Converts a distance to a double (kilometers)</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Orbits",
        meta = (
            ToolTip = "Computes an ellipse from Conic elements"
            ))
    static void ComputeConic(
        FSEllipse& ellipse,
        bool& isHyperbolic,
        const FSEphemerisTime& et,
        const FSConicElements& orbit,
        const FString& orbitReferenceFrame = "ECLIPJ2000",
        const FString& observerReferenceFrame = "ECLIPJ2000"
    );

    /// <summary>Renders an ellipse in debug lines</summary>
    // For staic orbits this better than rendering orbits, slightly, because
    // you can cache the ellipse and forget about it.
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Debug|Orbits", 
        meta = (
            DevelopmentOnly,
            ToolTip = "Renders an ellipse in debug lines",
            AdvancedDisplay = "color, thickness"
            ))
    static void RenderDebugConic(
        const AActor* actor,
        const FSEllipse& conic,
        bool isHyperbolic,
        const FTransform& localTransform,
        const FColor& color = FColor::White,
        float thickness = 10.f
        );

    /// <summary>Renders an orbit in debug lines</summary>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Debug|Orbits",
        meta = (
            AutoCreateRefTerm = "et",
            DevelopmentOnly,
            ToolTip = "Renders an orbit in debug lines",
            AdvancedDisplay = "color, thickness"
            ))
    static void RenderDebugOrbit(
        const AActor* actor,
        const FTransform& localTransform,
        const FSEphemerisTime& et,
        const FSConicElements& orbit,
        const FString& orbitReferenceFrame = "ECLIPJ2000",
        const FString& observerReferenceFrame = "ECLIPJ2000",
        const FColor& color = FColor::White,
        float thickness = 10.f
    );

private:
   static  void RenderDebugEllipse(const UWorld* world, const FSEllipse& ellipse, const FTransform& localTransform, const FColor& color = FColor::White, float thickness = 10.f);
   static  void RenderDebugHyperbola(const UWorld* world, const FSEllipse& ellipse, const FTransform& localTransform, const FColor& color = FColor::White, float thickness = 10.f);
};
