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
};

namespace MaxQSamples
{
    void Log(const FString& LogString, const FColor& Color = FColor::White);
    void Log(const FString& LogString, ES_ResultCode ResultCode);
    FString MaxQPluginInfo();
    FString MaxQPathAbsolutified(const FString& path);
    TArray<FString> MaxQPathsAbsolutified(const TArray<FString>& paths);
}



