// Copyright 2021 Gamergenic.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this
// software and associated documentation files (the "Software"), to deal in the Software
// without restriction, including without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "SpiceTypes.h"
#include "K2Node_bodvrd.generated.h"

#pragma once

UCLASS(BlueprintType, Blueprintable)
class SPICEUNCOOKED_API UK2Node_bodvrd : public UK2Node
{
    GENERATED_BODY()

private:
    const FName bodynm_Field = FName(TEXT("bodynm"));
    const FName item_Field = FName(TEXT("item"));
    const FName value_Field = FName(TEXT("Value"));
    const FName success_Field = FName(TEXT("Success"));
    const FName error_Field = FName(TEXT("Error"));
    const FName errorMessage_Field = FName(TEXT("ErrorMessage"));

    const FName bodynm_DefaultValue = FName(TEXT("EARTH"));
    const FName item_DefaultValue = FName(TEXT("RADII"));

private:
    bool CheckForErrors(FKismetCompilerContext& CompilerContext);

public:

    UPROPERTY() FString bodynm_Value;
    UPROPERTY() FString item_Value;
    UPROPERTY() FString value_Value;

    UPROPERTY()
    TObjectPtr<UScriptStruct> StructType;

    UK2Node_bodvrd();

public:

    bool IsNodeSafeToIgnore() const;
    void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const;
    FText GetMenuCategory() const;
    FText GetNodeTitle(ENodeTitleType::Type TitleType) const;
    FText GetTooltipText() const;
    FText GetKeywords() const;
    
    void AllocateDefaultPins();
    void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph);
    bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const;
    bool IsOutputCompatible(const UEdGraphPin* ThePin) const;

    UEdGraphPin* bodynmPin() const { return FindPinChecked(bodynm_Field); }
    UEdGraphPin* itemPin() const { return FindPinChecked(item_Field); }
    UEdGraphPin* successPin() const { return FindPinChecked(success_Field); }
    UEdGraphPin* errorPin() const { return FindPinChecked(error_Field); }
    UEdGraphPin* errorMessagePin() const { return FindPinChecked(errorMessage_Field); }
    UEdGraphPin* returnValuePin() const { return FindPinChecked(value_Field); }
    UEdGraphPin* getReturnValuePin(class UK2Node_CallFunction* other) const;
};


