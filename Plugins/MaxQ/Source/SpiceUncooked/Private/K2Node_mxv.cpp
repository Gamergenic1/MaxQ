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


#include "K2Node_mxv.h"
#include "K2Utilities.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "ToolMenu.h"
#include "K2Node_CallFunction.h"
#include "SpiceK2.h"
#include "SpicePlatformDefs.h"


#define LOCTEXT_NAMESPACE "K2Node_mxv"

const FName UK2Node_mxv::vin{ VIN };
const FName UK2Node_mxv::m{ M };
const FName UK2Node_mxv::vout{ VOUT };


UK2Node_mxv::UK2Node_mxv(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
#if WITH_EDITOR
    for (const auto& op : GetSupportedOperations())
    {
        op.CheckClass(USpiceK2::StaticClass());
    }
#endif

    CurrentOperation = OperationType();
}



void UK2Node_mxv::AllocateDefaultPins()
{
    Super::AllocateDefaultPins();

    const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

    auto InputPin{ CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, vin) };
    InputPin->PinToolTip = VIN_tip;

    auto MatrixPin{ CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, m) };
    MatrixPin->PinToolTip = FString::Printf(TEXT("%s (SRotationMatrix or SStateTransform)"), M_tip);

    auto OutputPin{ CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, vout) };
    OutputPin->PinToolTip = VOUT_tip;

    // The module is 'uncooked' and thus only compiles with editor data, but still...
#if WITH_EDITORONLY_DATA
    InputPin->PinFriendlyName = LOCTEXT("v", "v");
    MatrixPin->PinFriendlyName = LOCTEXT("m", "m");
    OutputPin->PinFriendlyName = LOCTEXT("v_out", "vout");
#endif

    if (!CurrentOperation.ShortName.IsNone())
    {
        SetPinType(this, InputPin, CurrentOperation.OuterType, VIN_tip);
        SetPinType(this, MatrixPin, CurrentOperation.MatrixType, M_tip);
        SetPinType(this, OutputPin, CurrentOperation.OuterType, VOUT_tip);
    }
}


bool UK2Node_mxv::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const
{
    // handles split pins
    if(IsExactPair(MyPin, OtherPin)) return false;

    if (!CurrentOperation.ShortName.IsNone())
    {
        if (MyPin->PinName == vin || MyPin->PinName == vout)
        {
            return !CurrentOperation.OuterType.Matches(OtherPin->PinType);
        }
        else if (MyPin->PinName == m)
        {
            return !CurrentOperation.MatrixType.Matches(OtherPin->PinType);
        }
    }

    const auto Ops = GetSupportedOperations();

    if (MyPin->PinName == vin || MyPin->PinName == vout)
    {
        for (const auto& Op : Ops)
        {
            if (Op.OuterType.Matches(OtherPin->PinType)) return false;
        }
    }
    else if (MyPin->PinName == m)
    {
        for (const auto& Op : Ops)
        {
            if (Op.MatrixType.Matches(OtherPin->PinType)) return false;
        }
    }

    OutReason = TEXT("Pin connection type not supported");
    return true;
}


void UK2Node_mxv::NodeConnectionListChanged()
{
    Super::NodeConnectionListChanged();

    auto InputPin = FindPinChecked(vin);
    auto MatrixPin = FindPinChecked(m);
    auto OutputPin = FindPinChecked(vout);

    CurrentOperation = OperationType();
    for (const auto& Op : GetSupportedOperations())
    {
        if (Op.IsUniquelyDetermined(InputPin, MatrixPin, OutputPin))
        {
            CurrentOperation = Op;
            break;
        }
    }

    bool NodeIsGeneric = CurrentOperation.ShortName.IsNone();

    if (NodeIsGeneric)
    {
        SetPinTypeToWildcard(this, InputPin, VIN_tip);
        SetPinTypeToWildcard(this, MatrixPin, FString::Printf(TEXT("%s (SRotationMatrix or SStateTransform)"), M_tip));
        SetPinTypeToWildcard(this, OutputPin, TEXT("Product (m * vin)"));
    }
    else
    {
        SetPinType(this, InputPin, CurrentOperation.OuterType, VIN_tip);
        SetPinType(this, MatrixPin, CurrentOperation.MatrixType, M_tip);
        SetPinType(this, OutputPin, CurrentOperation.OuterType, TEXT("Product (m * vin)"));
    }
}


void UK2Node_mxv::PinTypeChanged(UEdGraphPin* Pin)
{
    Super::PinTypeChanged(Pin);

    ThisPinTypeChanged(Pin);
}


bool UK2Node_mxv::CheckForErrors(FKismetCompilerContext& CompilerContext, OperationType& Operation)
{
    auto InputPin = FindPinChecked(vin);
    auto MatrixPin = FindPinChecked(m);
    auto OutputPin = FindPinChecked(vout);

    for (const auto& Op : GetSupportedOperations())
    {
        if (Op.Is(InputPin, MatrixPin, OutputPin))
        {
            Operation = Op;
            return false;
        }
    }

    CompilerContext.MessageLog.Error(*LOCTEXT("Error", "Node @@ had an operand type error.").ToString(), this);
    return true;
}


void UK2Node_mxv::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
    Super::ExpandNode(CompilerContext, SourceGraph);

    auto Schema = Cast< UEdGraphSchema_K2 >(GetSchema());

    OperationType Operation;
    if (CheckForErrors(CompilerContext, Operation))
    {
        BreakAllNodeLinks();
        return;
    }

    UEdGraphPin* InputPin{ FindPinChecked(vin, EEdGraphPinDirection::EGPD_Input) };
    UEdGraphPin* MatrixPin{ FindPinChecked(m, EEdGraphPinDirection::EGPD_Input) };
    UEdGraphPin* OutputPin{ FindPinChecked(vout, EEdGraphPinDirection::EGPD_Output) };

    auto InternalNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
    InternalNode->FunctionReference.SetExternalMember(Operation.K2NodeName, USpiceK2::StaticClass());
    InternalNode->AllocateDefaultPins();
    CompilerContext.MessageLog.NotifyIntermediateObjectCreation(InternalNode, this);

    auto InternalIn = InternalNode->FindPinChecked(FName(USpiceK2::mxv_vin));

    if (!Operation.OuterToInnerConversion.ConversionName.IsNone())
    {
        auto ConversionNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);

        ConversionNode->FunctionReference.SetExternalMember(Operation.OuterToInnerConversion.ConversionName, USpiceK2::StaticClass());
        ConversionNode->AllocateDefaultPins();
        CompilerContext.MessageLog.NotifyIntermediateObjectCreation(ConversionNode, this);

        auto ConversionValueInput = ConversionNode->FindPinChecked(FName(USpiceK2::conv_input), EEdGraphPinDirection::EGPD_Input);
        auto ConversionOut = ConversionNode->GetReturnValuePin();

        MovePinLinksOrCopyDefaults(CompilerContext, InputPin, ConversionValueInput);
        Schema->TryCreateConnection(ConversionOut, InternalIn);
    }
    else
    {
        MovePinLinksOrCopyDefaults(CompilerContext, InputPin, InternalIn);
    }

    auto InternalOut = InternalNode->GetReturnValuePin();

    if (!Operation.InnerToOuterConversion.ConversionName.IsNone())
    {
        auto ConversionNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);

        ConversionNode->FunctionReference.SetExternalMember(Operation.InnerToOuterConversion.ConversionName, USpiceK2::StaticClass());
        ConversionNode->AllocateDefaultPins();
        CompilerContext.MessageLog.NotifyIntermediateObjectCreation(ConversionNode, this);

        auto ConversionValueInput = ConversionNode->FindPinChecked(FName(USpiceK2::conv_input), EEdGraphPinDirection::EGPD_Input);
        auto ConversionOut = ConversionNode->GetReturnValuePin();

        Schema->TryCreateConnection(InternalOut, ConversionValueInput);
        MovePinLinksOrCopyDefaults(CompilerContext, OutputPin, ConversionOut);
    }
    else
    {
        MovePinLinksOrCopyDefaults(CompilerContext, OutputPin, InternalOut);
    }

    auto InternalMatrix = InternalNode->FindPinChecked(FName(USpiceK2::mxv_m));
    MovePinLinksOrCopyDefaults(CompilerContext, MatrixPin, InternalMatrix);


    BreakAllNodeLinks();
}

FSlateIcon UK2Node_mxv::GetIconAndTint(FLinearColor& OutColor) const
{
    OutColor = FColor::Emerald;
    return FSlateIcon("EditorStyle", "Kismet.AllClasses.FunctionIcon");
}


FLinearColor UK2Node_mxv::GetNodeTitleColor() const
{
    return NodeBackgroundColor;
}

void UK2Node_mxv::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    RegisterAction(ActionRegistrar, GetClass());
}

FText UK2Node_mxv::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    constexpr bool bUseShortNameForTitle{ true };

    switch (TitleType)
    {
    case ENodeTitleType::FullTitle:
        /** The full title, may be multiple lines. */
        return LOCTEXT("ListViewTitle", "mxv");
    case ENodeTitleType::MenuTitle:
        /** Menu Title for context menus to be displayed in context menus referencing the node. */
        return LOCTEXT("MenuTitle", "mxv - Matrix * Vector");
    case ENodeTitleType::ListView:
        /** More concise, single line title. */
        return LOCTEXT("ListViewTitle", "mxv - Matrix * Vector");
    }

    return LOCTEXT("ShortTitle", "mxv");
}

FText UK2Node_mxv::GetMenuCategory() const
{
    return LOCTEXT("Category", "MaxQ|Math");
}


FText UK2Node_mxv::GetKeywords() const
{
    return LOCTEXT("Keywords", "MATRIX, VECTOR, MULTIPLICATION");
}


FText UK2Node_mxv::GetTooltipText() const
{
    FText Tooltip = LOCTEXT("Tooltip", "Compute the product of a matrix and vector.  Support limited wildcards in a single action.");

    FText ListStart = LOCTEXT("ListStart", ":\n");
    FText ListSItemeparator = LOCTEXT("ListItemSeparator", ",\n");
    bool bIsFirstItem = true;
    for (const auto& Op : GetSupportedOperations())
    {
        Tooltip = Tooltip.Join(bIsFirstItem ? ListStart : ListSItemeparator, Tooltip, Op.OuterType.GetDisplayNameText());
        bIsFirstItem = false;
    }

    return Tooltip;
}

const TArray<UK2Node_mxv::OperationType>& UK2Node_mxv::GetSupportedOperations() const
{
    static const TArray<OperationType> SupportedOperations
    {
        OperationType{ "mxv dimensionless vector", FName(USpiceK2::mxv_vector), FK2Type::SRotationMatrix(), FK2Type::SDimensionlessVector() },
        OperationType{ "mxv distance vector",  USpiceK2::mxv_vector, FK2Type::SRotationMatrix(), FK2Conversion::SDistanceVectorToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSDistanceVector() },
        OperationType{ "mxv velocity vector",  USpiceK2::mxv_vector, FK2Type::SRotationMatrix(), FK2Conversion::SVelocityVectorToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSVelocityVector() },
        OperationType{ "mxv angular velocity",  USpiceK2::mxv_vector, FK2Type::SRotationMatrix(), FK2Conversion::SAngularVelocityToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSAngularVelocity() },
        OperationType{ "mxv dimensionless state",  USpiceK2::mxv_state_vector, FK2Type::SStateTransform(), FK2Type::SDimensionlessStateVector() },
        OperationType{ "mxv state vector",  USpiceK2::mxv_state_vector, FK2Type::SStateTransform(), FK2Conversion::SStateVectorToSDimensionlessStateVector(), FK2Conversion::SDimensionlessStateVectorToSStateVector() }
    };

    return SupportedOperations;
}

#undef LOCTEXT_NAMESPACE