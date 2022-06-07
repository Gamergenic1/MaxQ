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
};

namespace MaxQSamples
{
    void Log(const FString& LogString, const FColor& Color = FColor::White);
    void Log(const FString& LogString, ES_ResultCode ResultCode);
    FString MaxQPluginInfo();
    FString MaxQPathAbsolutified(const FString& path);
    TArray<FString> MaxQPathsAbsolutified(const TArray<FString>& paths);
}



