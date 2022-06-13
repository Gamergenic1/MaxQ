// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SampleUtilities.h"
#include "SampleNametagWidget.generated.h"



UCLASS(Category="MaxQSamples")
class MAXQCPPSAMPLES_API USampleNametagWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintImplementableEvent)
    void Init(const FString& NewObjectName, FPositionUpdate& NewPositionUpdate, FVisibilityUpdate& VisibilityUpdate);
};
