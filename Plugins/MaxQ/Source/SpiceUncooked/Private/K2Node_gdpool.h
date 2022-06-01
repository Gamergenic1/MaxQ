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
#include "K2OperationNOutput.h"
#include "K2Node_OperationNOutput.h"
#include "K2Node_gdpool.generated.h"

#pragma once

UCLASS(BlueprintType, Blueprintable)
class SPICEUNCOOKED_API UK2Node_gdpool : public UK2Node_OperationNOutput
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
    static FK2OperationNOutput WildcardOp();
    static FK2OperationNOutput DoubleOp();
    static FK2OperationNOutput RealOp();
    static FK2OperationNOutput ArrayDoubleOp();
    static FK2OperationNOutput ArrayRealOp();
    static FK2OperationNOutput SDimensionlessVectorOp();
    static FK2OperationNOutput SMassConstantOp();
    static FK2OperationNOutput SDistanceOp();
    static FK2OperationNOutput SDegreesOp();
    static FK2OperationNOutput SDistanceVectorOp();
    static FK2OperationNOutput SVelocityVectorOp();
    static FK2OperationNOutput SDistanceX();
    static FK2OperationNOutput SDistanceY();
    static FK2OperationNOutput SDistanceZ();
};


