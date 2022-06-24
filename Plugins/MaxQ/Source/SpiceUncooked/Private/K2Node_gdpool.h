// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "SpiceTypes.h"
#include "K2Type.h"
#include "K2Conversion.h"
#include "K2SingleOutputOpWithComponentFilter.h"
#include "K2Node_OutWithSelectorOp.h"
#include "K2Node_gdpool.generated.h"

#pragma once

UCLASS(BlueprintType, Blueprintable)
class SPICEUNCOOKED_API UK2Node_gdpool : public UK2Node_OutWithSelectorOp
{
    GENERATED_BODY()

public:

    UPROPERTY() FString item_Value;
    UPROPERTY() FString start_Value;

public:
    UK2Node_gdpool();

    void AllocateDefaultPins();
    void NotifyPinConnectionListChanged(UEdGraphPin* Pin);
    FText GetNodeTitle(ENodeTitleType::Type TitleType) const;
    FText GetMenuCategory() const;
    FText GetKeywords() const;
    FText GetTooltipText() const;
    void ReconstructNode();
    void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const;

protected:
    void ExpandOperationNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UK2Node* operationNode);

private:
    const FName item_Field = FName(TEXT("name"));
    const FName item_DefaultValue = FName(TEXT("BODY514_NUT_PREC_RA"));

    UEdGraphPin* itemPin() const { return FindPinChecked(item_Field); }

    const FName start_Field = FName(TEXT("start"));
    const int start_DefaultValue = 0;

    UEdGraphPin* startPin() const { return FindPinChecked(start_Field); }

private:
    static const FK2SingleOutputOpWithComponentFilter& WildcardOp();
    static const FK2SingleOutputOpWithComponentFilter& DoubleOp();
    static const FK2SingleOutputOpWithComponentFilter& RealOp();
    static const FK2SingleOutputOpWithComponentFilter& ArrayDoubleOp();
    static const FK2SingleOutputOpWithComponentFilter& ArrayRealOp();
    static const FK2SingleOutputOpWithComponentFilter& SDimensionlessVectorOp();
    static const FK2SingleOutputOpWithComponentFilter& SMassConstantOp();
    static const FK2SingleOutputOpWithComponentFilter& SDistanceOp();
    static const FK2SingleOutputOpWithComponentFilter& SDegreesOp();
    static const FK2SingleOutputOpWithComponentFilter& SDistanceVectorOp();
    static const FK2SingleOutputOpWithComponentFilter& SVelocityVectorOp();
    static const FK2SingleOutputOpWithComponentFilter& SDistanceX();
    static const FK2SingleOutputOpWithComponentFilter& SDistanceY();
    static const FK2SingleOutputOpWithComponentFilter& SDistanceZ();
};


