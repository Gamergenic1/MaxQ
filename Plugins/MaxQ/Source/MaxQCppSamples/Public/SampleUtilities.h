// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "SpiceTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "SampleUtilities.generated.h"


//-----------------------------------------------------------------------------
// SampleUtilities
// Common code used by MaxQ C++ Samples
//-----------------------------------------------------------------------------

MAXQCPPSAMPLES_API DECLARE_LOG_CATEGORY_EXTERN(LogMaxQSamples, Log, All);



//-----------------------------------------------------------------------------
// FSolarSystemState
// Track the state of a small demo animated solar system
//-----------------------------------------------------------------------------

USTRUCT(BlueprintType)
struct MAXQCPPSAMPLES_API FSamplesSolarSystemState
{
    GENERATED_BODY();

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    bool InitializeTimeToNow;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FString InitialTime;

    UPROPERTY(Transient)
    FSEphemerisTime CurrentTime;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    FSEphemerisPeriod TimeScale;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    TMap<FName, TWeakObjectPtr<AActor> > SolarSystemBodyMap;

    FSamplesSolarSystemState()
    {
        InitializeTimeToNow = true;
        InitialTime = TEXT("25 DEC 2021 12:00:00");
        TimeScale = FSEphemerisPeriod::FromSeconds(10000000.0);
    }
};


//-----------------------------------------------------------------------------
// FCelestrakTLERequest
// Ask Celestrak for TLE Data
//-----------------------------------------------------------------------------
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FTelemetryCallback, bool, Success, const FString&, ObjectId, const FString&, Telemetry);
DECLARE_DYNAMIC_DELEGATE_OneParam(FPositionUpdate, const FVector&, Position);
DECLARE_DYNAMIC_DELEGATE_OneParam(FVisibilityUpdate, bool, bIsVisible);
DECLARE_DELEGATE_RetVal_ThreeParams(bool, FComputeConic, const FSStateVector&, FSEllipse&, bool&);
DECLARE_DELEGATE_FourParams(FRenderDebugOrbit, const FSEllipse&, bool, const FColor&, float);
DECLARE_DELEGATE_RetVal_TwoParams(bool, FTLEGetStateVectorCallback, const FSTwoLineElements&, FSStateVector&);
DECLARE_DELEGATE_RetVal_TwoParams(bool, FXformPositionCallback, const FSDistanceVector&, FVector&);
DECLARE_DELEGATE_RetVal_TwoParams(bool, FEvaluateOrbitalElements, const FSConicElements&, FSStateVector&);
DECLARE_DELEGATE_RetVal_TwoParams(bool, FGetOrbitalElements, const FSStateVector&, FSConicElements&);
DECLARE_DELEGATE_RetVal_ThreeParams(bool, FGetConicFromKepler, const FSConicElements&, FSEllipse&, bool&);


UCLASS(Category="MaxQSamples")
class MAXQCPPSAMPLES_API USampleUtilities : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "MaxQSamples", meta = (DevelopmentOnly))
    static void GetMaxQPluginInfo(FString& Info);

    UFUNCTION(BlueprintPure, Category = "MaxQSamples", meta = (DevelopmentOnly))
    static void GetMaxQPathAbsolutified(const FString& path, FString& AbsolutePath);

    UFUNCTION(BlueprintPure, Category = "MaxQSamples", meta = (DevelopmentOnly))
    static void GetMaxQPathsAbsolutified(const TArray<FString>& paths, TArray<FString>& AbsolutePaths);

    UFUNCTION(BlueprintPure, Category = "MaxQSamples", meta = (DevelopmentOnly))
    static void GetDefaultBasicKernels(TArray<FString>& BasicKernels);

    UFUNCTION(BlueprintPure, Category = "MaxQSamples", meta = (DevelopmentOnly))
    static void GetDefaultItrf93Kernels(TArray<FString>& Itrf93Kernels);

    UFUNCTION(BlueprintPure, Category = "MaxQSamples", meta = (DevelopmentOnly))
    static void GetDefaultInsightMissionKernels(TArray<FString>& InsightMissionKernels);

    UFUNCTION(BlueprintPure, Category = "MaxQSamples", meta = (DevelopmentOnly))
    static bool LoadKernelList(const FString& ListName, const TArray<FString>& KernelFiles);

    UFUNCTION(BlueprintCallable, Category = "MaxQSamples", meta = (DevelopmentOnly))
    static void InitializeTime(FSamplesSolarSystemState& SolarSystemState, bool SetInitialTime = true);

    UFUNCTION(BlueprintCallable, Category = "MaxQSamples", meta = (DevelopmentOnly))
    static void GetTelemetryFromServer(FTelemetryCallback Callback, FString ObjectId = TEXT("CATNR=25544"), FString Format = TEXT("TLE"));
};

namespace MaxQSamples
{
    void Log(const FString& LogString, const FColor& Color = FColor::White, float DisplayTime = 60.f);
    void Log(const FString& LogString, ES_ResultCode ResultCode, float DisplayTime = 60.f);
    FString MaxQPluginInfo();
    FString MaxQPathAbsolutified(const FString& path);
    TArray<FString> MaxQPathsAbsolutified(const TArray<FString>& paths);

    // Common solar system posing stuff, so each sample can focus on a particular thing without
    // Reimplementing all this stuff to reduce the noise.
    bool InitBodyScales(float BodyScale, const FSamplesSolarSystemState& SolarSystemState);
    bool UpdateBodyPositions(const FName& OriginNaifName, const FName& OriginReferenceFrame, float DistanceScale, const FSamplesSolarSystemState& SolarSystemState);
    bool UpdateBodyOrientations(const FName& OriginReferenceFrame, const FSamplesSolarSystemState& SolarSystemState);
    bool UpdateSunDirection(const FName& OriginNaifName, const FName& OriginReferenceFrame, const FSEphemerisTime& et, const FName& SunNaifName, const TWeakObjectPtr<AActor>& SunDirectionalLight);
}
