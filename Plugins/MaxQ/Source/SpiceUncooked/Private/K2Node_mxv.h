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
#include "K2Type.h"
#include "K2Node_CallFunction.h"
#include "Chaos/Vector.h"
#include "SpiceTypes.h"
#include "K2Node_MathGenericInterface.h"
#include "K2Conversion.h"
#include "K2Node_mxv.generated.h"

#pragma once

#define LOCTEXT_NAMESPACE "K2Node_mxv"


USTRUCT()
struct FK2MxVOp
{
    typedef FK2MxVOp OperationType;

    GENERATED_BODY()

    UPROPERTY() FName ShortName;
    UPROPERTY() FName K2NodeName;
    UPROPERTY() FK2Type MatrixType;
    UPROPERTY() FK2Type OuterType;
    UPROPERTY() FK2Type InnerType;
    UPROPERTY() FK2Conversion InnerToOuterConversion;
    UPROPERTY() FK2Conversion OuterToInnerConversion;

    FK2MxVOp()
    {
        ShortName = FName();
        K2NodeName = FName();
        MatrixType = FK2Type();
        OuterType = FK2Type();
        InnerType = FK2Type();
        InnerToOuterConversion = FK2Conversion();
        OuterToInnerConversion = FK2Conversion();
    }

    FK2MxVOp(FName _name, FName _k2NodeName, const FK2Type& _matrix, const FK2Type& _final)
    {
        ShortName = _name;
        K2NodeName = _k2NodeName;
        MatrixType = _matrix;
        OuterType = _final;
        InnerType = _final;
        InnerToOuterConversion = FK2Conversion();
        OuterToInnerConversion = FK2Conversion();
    }

    FK2MxVOp(FName _name, FName _k2NodeName, const FK2Type& _matrix, const FK2Conversion& _OuterToInnerConversion, const FK2Conversion& _InnerToOuterConversion)
    {
        ShortName = _name;
        K2NodeName = _k2NodeName;
        MatrixType = _matrix;
        OuterType = _OuterToInnerConversion.In;
        InnerType = _OuterToInnerConversion.Out;
        OuterToInnerConversion = _OuterToInnerConversion;
        InnerToOuterConversion = _InnerToOuterConversion;

        check(_InnerToOuterConversion.In == InnerType);
        check(_InnerToOuterConversion.Out == OuterType);
    }

    FK2MxVOp(const OperationType& other)
    {
        ShortName = other.ShortName;
        K2NodeName = other.K2NodeName;
        MatrixType = other.MatrixType;
        OuterType = other.OuterType;
        InnerType = other.InnerType;
        OuterToInnerConversion = other.OuterToInnerConversion;
        InnerToOuterConversion = other.InnerToOuterConversion;
    }

    FK2MxVOp& operator= (const OperationType& other)
    {
        // self-assignment guard
        if (this == &other)
            return *this;

        // do the copy
        ShortName = other.ShortName;
        K2NodeName = other.K2NodeName;
        MatrixType = other.MatrixType;
        OuterType = other.OuterType;
        InnerType = other.InnerType;
        OuterToInnerConversion = other.OuterToInnerConversion;
        InnerToOuterConversion = other.InnerToOuterConversion;

        // return the existing object so we can chain this operator
        return *this;
    }


    bool operator== (const OperationType& other) const
    {
        // self equality
        if (this == &other)
            return true;

        bool bEqual = ShortName.IsEqual(other.ShortName);

#if WITH_EDITOR
        if (bEqual)
        {
            check(K2NodeName.IsEqual(other.K2NodeName));
            check(MatrixType == other.MatrixType);
            check(OuterType == other.OuterType);
            check(InnerType == other.InnerType);
            check(OuterToInnerConversion == other.OuterToInnerConversion);
            check(InnerToOuterConversion == other.InnerToOuterConversion);
        }
#endif

        return bEqual;
    }

    bool IsCompatibleWithConnectionsTo(const UEdGraphPin* Input, const UEdGraphPin* Matrix, const UEdGraphPin* Output) const
    {
        bool bIsOkay = true;

        if (Input->LinkedTo.Num() > 0)
        {
            bIsOkay &= OuterType.Matches(Input->LinkedTo[0]->PinType);
        }

        if (Matrix->LinkedTo.Num() > 0)
        {
            bIsOkay &= MatrixType.Matches(Matrix->LinkedTo[0]->PinType);
        }

        if (Output->LinkedTo.Num() > 0)
        {
            bIsOkay &= OuterType.Matches(Output->LinkedTo[0]->PinType);
        }

        return bIsOkay;
    }

    bool IsUniquelyDetermined(const UEdGraphPin* Input, const UEdGraphPin* Matrix, const UEdGraphPin* Output) const
    {
        if (IsCompatibleWithConnectionsTo(Input, Matrix, Output))
        {
            if (Input->LinkedTo.Num() > 0)
            {
                if(OuterType.Is(Input->LinkedTo[0]->PinType)) return true;
            }

            if (Output->LinkedTo.Num() > 0)
            {
                if(OuterType.Is(Output->LinkedTo[0]->PinType)) return true;
            }
        }

        return false;
    }

    bool Is(const UEdGraphPin* Input, const UEdGraphPin* Matrix, const UEdGraphPin* Output) const
    {
        if (IsCompatibleWithConnectionsTo(Input, Matrix, Output))
        {
            bool bEqual = true;

            bEqual &= Input->LinkedTo.Num() > 0 && OuterType.Is(Input->LinkedTo[0]->PinType);
            bEqual &= Output->LinkedTo.Num() > 0 && OuterType.Is(Output->LinkedTo[0]->PinType);
            bEqual &= Matrix->LinkedTo.Num() > 0 && MatrixType.Is(Matrix->LinkedTo[0]->PinType);

            return bEqual;
        }

        return false;
    }

#if WITH_EDITOR
    void CheckClass(UClass* Class) const
    {
        // make sure required conversions exist...
        if (!InnerToOuterConversion.ConversionName.IsNone())
        {
            check(Class->FindFunctionByName(InnerToOuterConversion.ConversionName));
        }
        if (!OuterToInnerConversion.ConversionName.IsNone())
        {
            check(Class->FindFunctionByName(OuterToInnerConversion.ConversionName));
        }
        if (!K2NodeName.IsNone())
        {
            check(Class->FindFunctionByName(K2NodeName));
        }
    }
#endif
};



UCLASS(BlueprintType, Blueprintable)
class SPICEUNCOOKED_API UK2Node_mxv : public UK2Node, public IK2Node_MathGenericInterface
{
    GENERATED_UCLASS_BODY()

    static constexpr ANSICHAR VIN[] = "vin";
    static constexpr ANSICHAR M[]  = "m";
    static constexpr ANSICHAR VOUT[] = "vout";

    static constexpr TCHAR VIN_tip[] = TEXT("Input vector");
    static constexpr TCHAR M_tip[] = TEXT("Multiplication Matrix");
    static constexpr TCHAR VOUT_tip[] = TEXT("Product (m * vin)");

    static const FName vin;
    static const FName m;
    static const FName vout;

public:
    UPROPERTY()
    FK2MxVOp CurrentOperation;

    typedef FK2MxVOp OperationType;

public:

    // UEdGraphNode interface
    virtual void AllocateDefaultPins() override;
    virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;
    virtual FLinearColor GetNodeTitleColor() const override;

    virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const  override;
    virtual void PinTypeChanged(UEdGraphPin* Pin) override;
    virtual bool IsNodePure() const override { return true; }
    virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
    virtual void NodeConnectionListChanged() override;
    // End of UEdGraphNode interface

    // UK2Node interface
    virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
    virtual FText GetMenuCategory() const override;
    virtual FText GetKeywords() const override;
    virtual FText GetTooltipText() const override;
    // end of UK2Node interface

    bool CheckForErrors(FKismetCompilerContext& CompilerContext, OperationType& Operation);
    void CreateInputPin();
    void AllocateInputPin(FName& PinName);

    void RefreshOperation();

    virtual const TArray<OperationType>& GetSupportedOperations() const;
};


#undef LOCTEXT_NAMESPACE
