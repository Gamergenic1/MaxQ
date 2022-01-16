// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "SpiceTypes.h"
#include "K2Type.h"
#include "K2Conversion.h"
#include "K2OperationNOutput.h"
#include "K2Node_OperationNOutput.generated.h"

#pragma once

// This is a K2Node that emits two child nodes:
// 1 operation
// 2 conversion to wildcard type
UCLASS(BlueprintType, Blueprintable)
class SPICEUNCOOKED_API UK2Node_OperationNOutput : public UK2Node
{
    GENERATED_BODY()

private:
    const FName value_Field = FName(TEXT("Value"));
    const FName success_Field = FName(TEXT("Success"));
    const FName error_Field = FName(TEXT("Error"));
    const FName selector_Field = FName(TEXT("Select"));
    const FName errorMessage_Field = FName(TEXT("ErrorMessage"));

    bool CheckForErrors(FKismetCompilerContext& CompilerContext);
    bool MatchMe(FK2OperationNOutput& operation, FEdGraphPinType CompilerContext, EK2_ComponentSelector selector) const;

protected:
    TMap<FName, FK2OperationNOutput> OperationsMap;

public:

    UPROPERTY()
    FK2OperationNOutput CurrentOperation;
        
public:

    UK2Node_OperationNOutput();
    bool IsNodeSafeToIgnore() const;

    virtual void AllocateDefaultPins();
    virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph);
    bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const;
    bool IsOutputCompatible(const UEdGraphPin* ThePin, EK2_ComponentSelector selector) const;
    void NotifyPinConnectionListChanged(UEdGraphPin* Pin);
    void PreloadRequiredAssets();

    UEdGraphPin* selectorPin() const { return FindPin(selector_Field); }
    UEdGraphPin* successPin() const { return FindPinChecked(success_Field); }
    UEdGraphPin* errorPin() const { return FindPinChecked(error_Field); }
    UEdGraphPin* errorMessagePin() const { return FindPinChecked(errorMessage_Field); }
    UEdGraphPin* returnValuePin() const { return FindPinChecked(value_Field); }
    UEdGraphPin* getReturnValuePin(class UK2Node_CallFunction* other) const;

protected:
    virtual void ExpandOperationNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UK2Node* operationNode) {}

    EK2_ComponentSelector selectorPinValue() const;
};


