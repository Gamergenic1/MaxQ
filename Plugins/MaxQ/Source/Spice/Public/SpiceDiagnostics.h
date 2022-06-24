// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpicePlatformDefs.h"
#include "SpiceDiagnostics.generated.h"

SPICE_API DECLARE_LOG_CATEGORY_EXTERN(LogSpiceDiagnostics, Log, All);


UCLASS(Category = "MaxQ|Diagnostics")
class SPICE_API USpiceDiagnostics : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable,
        Category = "MaxQ|Diagnostics",
        meta = (
            Keywords = "UTILITY",
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Summarize SPK file",
            ToolTip = "Summarize an SPK file (coverages, etc)", 
            DevelopmentOnly
            ))
    static void DumpSpkSummary(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        FString& LogString,
        const FString& relativeLskPath = TEXT("NonAssetData/naif/kernels/Generic/LSK/naif0012.tls"),
        const FString& relativeSpkPath = TEXT("NonAssetData/naif/kernels/Generic/SPK/planets/de440s.bsp")
    );

    UFUNCTION(BlueprintCallable,
        Category = "MaxQ|Diagnostics",
        meta = (
            Keywords = "UTILITY",
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Summarize Binary PCK file",
            ToolTip = "Summarize Binary PCK file (coverages, etc)", 
            DevelopmentOnly
            ))
    static void DumpPckSummary(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        FString& LogString,
        const FString& relativeLskPath = TEXT("NonAssetData/naif/kernels/Generic/LSK/naif0012.tls"),
        const FString& relativePckPath = TEXT("NonAssetData/naif/kernels/Generic/PCK/earth_200101_990628_predict.bpc")
    );
    
    UFUNCTION(BlueprintCallable,
        Category = "MaxQ|Diagnostics",
        meta = (
            Keywords = "UTILITY",
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Summarize CK file",
            ToolTip = "Summarize a CK Kernel file coverage (spacecraft & instrument rotation/orientation coverages, etc)", 
            DevelopmentOnly
            ))
    static void DumpCkSummary(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        FString& LogString,
        const FString& relativeLskPath = TEXT("NonAssetData/naif/kernels/Generic/LSK/naif0012.tls"),
        const FString& relativeSclkPath = TEXT("NonAssetData/naif/kernels/INSIGHT/SCLK/NSY_SCLKSCET.00023.tsc"),
        const FString& relativeCkPath = TEXT("NonAssetData/naif/kernels/INSIGHT/CK/insight_ida_pot_210801_211218_v1.bc")
    );
};
