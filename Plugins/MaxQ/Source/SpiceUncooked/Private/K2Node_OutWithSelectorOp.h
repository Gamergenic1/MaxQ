// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceUncooked
// K2 Node Compilation
// See comments in Spice/SpiceK2.h.
//------------------------------------------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "SpiceTypes.h"
#include "K2Type.h"
#include "K2Conversion.h"
#include "K2SingleOutputOpWithComponentFilter.h"
#include "K2Node_MathGenericInterface.h"
#include "K2Node_OutWithSelectorOp.generated.h"

#pragma once

// This is a K2Node that emits two child nodes:
// 1 operation
// 2 conversion to wildcard type
UCLASS(Abstract)
class SPICEUNCOOKED_API UK2Node_OutWithSelectorOp : public UK2Node, public IK2Node_MathGenericInterface
{
    GENERATED_UCLASS_BODY()

public:
    UPROPERTY()
    FK2SingleOutputOpWithComponentFilter CurrentOperation;

    typedef FK2SingleOutputOpWithComponentFilter OperationType;

private:
    const FName returnValue_PinName = FName(TEXT("Value"));
    const FName successExec_PinName = FName(TEXT("Success"));
    const FName errorExec_PinName = FName(TEXT("Error"));
    const FName selector_PinName = FName(TEXT("Select"));
    const FName errorMessage_PinName = FName(TEXT("ErrorMessage"));

    bool CheckForErrors(FKismetCompilerContext& CompilerContext);
    bool MatchMe(OperationType& operation, FEdGraphPinType CompilerContext, EK2_ComponentSelector selector) const;

public:

    bool IsNodeSafeToIgnore() const override;

    virtual void AllocateDefaultPins();
    virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)  override;
    bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const  override;
    void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;
    void PreloadRequiredAssets() override;
    FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
    virtual FLinearColor GetNodeTitleColor() const override;

    UEdGraphPin* selectorPin() const { return FindPin(selector_PinName); }
    UEdGraphPin* successPin() const { return FindPinChecked(successExec_PinName); }
    UEdGraphPin* errorPin() const { return FindPinChecked(errorExec_PinName); }
    UEdGraphPin* errorMessagePin() const { return FindPinChecked(errorMessage_PinName); }
    UEdGraphPin* returnValuePin() const { return FindPinChecked(returnValue_PinName); }

    // IK2Node_MathGenericInterface
    virtual void NotifyConnectionChanged(UEdGraphPin* Pin, UEdGraphPin* Connection);
    // end of IK2Node_MathGenericInterface


protected:
    virtual void ExpandOperationNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UK2Node* operationNode) {}
    virtual bool IsOutputCompatible(const UEdGraphPin* ThePin, EK2_ComponentSelector selector) const;

    EK2_ComponentSelector selectorPinValue() const;

    virtual const TMap<FName, OperationType>& GetOperationsMap() const { static TMap<FName, OperationType> dummy; return dummy; }
    virtual const OperationType& GetWildcardOp() const { static const OperationType dummy; return dummy; }
};


