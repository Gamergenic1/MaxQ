// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"
#include "K2Type.h"
#include "K2Node_CallFunction.h"
#include "SpiceTypes.h"
#include "K2Node_AddPinInterface.h"
#include "Chaos/Vector.h"
#include "K2Node_MathGenericInterface.h"
#include "K2PassThroughOp.h"
#include "K2Node_minus.generated.h"

#pragma once

#define LOCTEXT_NAMESPACE "K2Node_minus"

UCLASS(BlueprintType, Blueprintable)
class SPICEUNCOOKED_API UK2Node_minus : public UK2Node, public IK2Node_MathGenericInterface
{
    GENERATED_UCLASS_BODY()

public:

    // UObject interface
    virtual void Serialize(FArchive& Ar) override;
    virtual void PostLoad() override;
    virtual void PostPasteNode() override;
    // End of UObject interface

    // UEdGraphNode interface
    virtual void AllocateDefaultPins() override;
    virtual bool IsActionFilteredOut(FBlueprintActionFilter const& Filter) override;
    virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
    virtual FLinearColor GetNodeTitleColor() const override;
    virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;

    virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const  override;
    virtual void NotifyPinConnectionListChanged(UEdGraphPin* Pin) override;
    virtual void NodeConnectionListChanged() override;
    virtual void PinTypeChanged(UEdGraphPin* Pin) override;
    virtual bool IsNodePure() const override { return true; }
    virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph);
    virtual void ReconstructNode() override;
    // End of UEdGraphNode interface

    // UK2Node interface
    virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
    virtual FText GetMenuCategory() const override;
    virtual FText GetKeywords() const override;
    virtual FText GetTooltipText() const override;
    // end of UK2Node interface

    // IK2Node_MathGenericInterface
    virtual void NotifyConnectionChanged(UEdGraphPin* Pin, UEdGraphPin* Connection);
    // end of IK2Node_MathGenericInterface

    bool CheckForErrors(FKismetCompilerContext& CompilerContext, FK2PassThroughOp& Operation);
    void CreateInputPin();
    void AllocateInputPin(FName& PinName);

    TArray<FK2Type> SupportedTypes;
    TArray<FK2PassThroughOp> SupportedOperations;
    FName OutputPinName;

    UPROPERTY()
    FK2Type OperandType;

    UPROPERTY()
    TArray<double> DefaultValues;


    TArray<FString> PinLabels;

    void RefreshOperand();
};


#undef LOCTEXT_NAMESPACE