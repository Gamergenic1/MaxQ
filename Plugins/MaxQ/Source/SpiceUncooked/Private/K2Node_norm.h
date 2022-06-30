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
#include "Chaos/Vector.h"
#include "SpiceTypes.h"
#include "K2Node_AddPinInterface.h"
#include "K2Node_MathGenericInterface.h"
#include "K2Conversion.h"
#include "K2Node_norm.generated.h"

#pragma once

#define LOCTEXT_NAMESPACE "K2Node_norm"


USTRUCT()
struct FK2VnormOp
{
    GENERATED_BODY()

    UPROPERTY() FName ShortName;
    UPROPERTY() FName K2NodeName;
    UPROPERTY() FK2Type InputVectorType;
    UPROPERTY() FK2Type OutputScalarType;
    UPROPERTY() FK2Conversion InputToVectorConversion;
    UPROPERTY() FK2Conversion ScalarToOutputConversion;

    FK2VnormOp()
    {
        ShortName = FName();
        K2NodeName = FName("vnorm_vector_K2");
        InputVectorType = FK2Type();
        OutputScalarType = FK2Type();
        InputToVectorConversion = FK2Conversion();
        ScalarToOutputConversion = FK2Conversion();
    }

    FK2VnormOp(FName _name, FName _K2NodeName, const FK2Type& _vectortype, const FK2Type& _scalartype)
    {
        ShortName = _name;
        K2NodeName = _K2NodeName;
        InputVectorType = _vectortype;
        OutputScalarType = _scalartype;
        InputToVectorConversion = FK2Conversion();
        ScalarToOutputConversion = FK2Conversion();
    }

    FK2VnormOp(FName _name, FName _K2NodeName, const FK2Conversion& _InputToVectorConversion, const FK2Conversion& _ScalarToOutputConversion)
    {
        ShortName = _name;
        K2NodeName = _K2NodeName;
        InputVectorType = _InputToVectorConversion.In;
        OutputScalarType = _ScalarToOutputConversion.Out;
        InputToVectorConversion = _InputToVectorConversion;
        ScalarToOutputConversion = _ScalarToOutputConversion;
    }

    FK2VnormOp(const FK2VnormOp& other)
    {
        ShortName = other.ShortName;
        K2NodeName = other.K2NodeName;
        InputVectorType = other.InputVectorType;
        OutputScalarType = other.OutputScalarType;
        InputToVectorConversion = other.InputToVectorConversion;
        ScalarToOutputConversion = other.ScalarToOutputConversion;
    }

    FK2VnormOp& operator= (const FK2VnormOp& other)
    {
        // self-assignment guard
        if (this == &other)
            return *this;

        // do the copy
        ShortName = other.ShortName;
        K2NodeName = other.K2NodeName;
        InputVectorType = other.InputVectorType;
        OutputScalarType = other.OutputScalarType;
        InputToVectorConversion = other.InputToVectorConversion;
        ScalarToOutputConversion = other.ScalarToOutputConversion;

        // return the existing object so we can chain this operator
        return *this;
    }


    bool operator== (const FK2VnormOp & other) const
    {
        // self equality
        if (this == &other)
            return true;

        bool bEqual = ShortName.IsEqual(other.ShortName);

#if WITH_EDITOR
        if (bEqual)
        {
            check(K2NodeName.IsEqual(other.K2NodeName));
            check(InputVectorType == other.InputVectorType);
            check(OutputScalarType == other.OutputScalarType);
            check(InputToVectorConversion == other.InputToVectorConversion);
            check(ScalarToOutputConversion == other.ScalarToOutputConversion);
        }
#endif

        return bEqual;
    }
};



UCLASS(BlueprintType, Blueprintable)
class SPICEUNCOOKED_API UK2Node_norm : public UK2Node, public IK2Node_MathGenericInterface
{
    GENERATED_UCLASS_BODY()

public:

    // UEdGraphNode interface
    virtual void AllocateDefaultPins() override;
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

    bool CheckForErrors(FKismetCompilerContext& CompilerContext, FK2VnormOp& Operation);
    void CreateInputPin();
    void AllocateInputPin(FName& PinName);

    static const TArray<FK2VnormOp> SupportedOperations;

    UPROPERTY()
    FK2VnormOp CurrentOperation;

    void RefreshOperation();
};



#undef LOCTEXT_NAMESPACE