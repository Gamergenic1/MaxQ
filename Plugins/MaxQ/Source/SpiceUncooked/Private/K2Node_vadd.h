// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "K2Node_NInOneOut.h"
#include "K2Node_vadd.generated.h"

#pragma once

UCLASS(BlueprintType, Blueprintable)
class SPICEUNCOOKED_API UK2Node_vadd : public UK2Node_NInOneOut
{
    GENERATED_BODY()

    UK2Node_vadd();

public:
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
    virtual FText GetMenuCategory() const override;
    virtual FText GetKeywords() const override;
    virtual FText GetTooltipText() const override;
};


