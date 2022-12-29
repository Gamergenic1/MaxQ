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
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GetTelemetryFromServer.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTelemetryCallback_AsyncExecutionCompleted, const FString&, ObjectId, const FString&, Telemetry);


UCLASS()
class MAXQCPPSAMPLES_API UGetTelemetryFromServer_AsyncExecution : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    // Execute the actual load
    virtual void Activate() override;

    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", Category = "MaxQSamples", WorldContext = "WorldContextObject"))
    static UGetTelemetryFromServer_AsyncExecution* IssueTelemetryRequest(UObject* WorldContextObject, FString ObjectId, FString Format);

    UPROPERTY(BlueprintAssignable)
    FTelemetryCallback_AsyncExecutionCompleted OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FTelemetryCallback_AsyncExecutionCompleted OnError;

    // Args from IssueTelemetryRequest (to be used by Activate)
    FString ObjectIdArg;
    FString FormatArg;
};
