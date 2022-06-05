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
#include "TutorialUtilities.generated.h"


//-----------------------------------------------------------------------------
// TutorialUtilities
// Common code used by MaxQ C++ Tutorials
//-----------------------------------------------------------------------------

MAXQCPPTUTORIAL_API DECLARE_LOG_CATEGORY_EXTERN(LogMaxQTutorials, Log, All);

UCLASS(Category="MaxQTutorials")
class MAXQCPPTUTORIAL_API UTutorialUtilities : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "MaxQTutorials", meta = (DevelopmentOnly))
    static void GetMaxQPluginInfo(FString& Info);

    UFUNCTION(BlueprintPure, Category = "MaxQTutorials", meta = (DevelopmentOnly))
    static void GetMaxQPathAbsolutified(const FString& path, FString& AbsolutePath);

    UFUNCTION(BlueprintPure, Category = "MaxQTutorials", meta = (DevelopmentOnly))
    static void GetMaxQPathsAbsolutified(const TArray<FString>& paths, TArray<FString>& AbsolutePaths);
};

namespace MaxQTutorial
{
    void Log(const FString& LogString, const FColor& Color = FColor::White);
    void Log(const FString& LogString, ES_ResultCode ResultCode);
    FString MaxQPluginInfo();
    FString MaxQPathAbsolutified(const FString& path);
    TArray<FString> MaxQPathsAbsolutified(const TArray<FString>& paths);
}



