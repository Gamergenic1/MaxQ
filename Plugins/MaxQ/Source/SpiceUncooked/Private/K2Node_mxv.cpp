// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "K2Node_mxv.h"
#include "K2Utilities.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "ToolMenu.h"
#include "K2Node_CallFunction.h"
#include "SpiceK2.h"
#include "SpicePlatformDefs.h"


#define LOCTEXT_NAMESPACE "K2Node_mxv"

const TArray<FK2MxVOp> UK2Node_mxv::SupportedOperations
{
    FK2MxVOp{ "mxv dimensionless vector", FName(USpiceK2::mxv_vector), FK2Type::SRotationMatrix(), FK2Type::SDimensionlessVector() },
    FK2MxVOp{ "mxv distance vector",  USpiceK2::mxv_vector, FK2Type::SRotationMatrix(), FK2Conversion::SDistanceVectorToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSDistanceVector() },
    FK2MxVOp{ "mxv velocity vector",  USpiceK2::mxv_vector, FK2Type::SRotationMatrix(), FK2Conversion::SVelocityVectorToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSVelocityVector() },
    FK2MxVOp{ "mxv angular velocity",  USpiceK2::mxv_vector, FK2Type::SRotationMatrix(), FK2Conversion::SAngularVelocityToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSAngularVelocity() },
    FK2MxVOp{ "mxv dimensionless state",  USpiceK2::mxv_state_vector, FK2Type::SStateTransform(), FK2Type::SDimensionlessStateVector() },
    FK2MxVOp{ "mxv state vector",  USpiceK2::mxv_state_vector, FK2Type::SStateTransform(), FK2Conversion::SStateVectorToSDimensionlessStateVector(), FK2Conversion::SDimensionlessStateVectorToSStateVector() }
};

const FName UK2Node_mxv::vin{ VIN };
const FName UK2Node_mxv::m{ M };
const FName UK2Node_mxv::vout{ VOUT };

UK2Node_mxv::UK2Node_mxv(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
#if WITH_EDITOR
    for (const auto& op : SupportedOperations)
    {
        // make sure required conversions exist...
        if (!op.InnerToOuterConversion.ConversionName.IsNone())
        {
            check(USpiceK2::StaticClass()->FindFunctionByName(op.InnerToOuterConversion.ConversionName));
        }
        if (!op.OuterToInnerConversion.ConversionName.IsNone())
        {
            check(USpiceK2::StaticClass()->FindFunctionByName(op.OuterToInnerConversion.ConversionName));
        }
        if (!op.K2NodeName.IsNone())
        {
            check(USpiceK2::StaticClass()->FindFunctionByName(op.K2NodeName));
        }
    }
#endif

    CurrentOperation = FK2MxVOp();
}



void UK2Node_mxv::AllocateDefaultPins()
{
    Super::AllocateDefaultPins();

    const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

    auto InputPin{ CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, vin) };
    InputPin->PinToolTip = TEXT("Input Vector");

    auto MatrixPin{ CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, m) };
    MatrixPin->PinToolTip = TEXT("Multiplication Matrix (SRotationMatrix or SStateTransform)");

    auto OutputPin{ CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, vout) };
    OutputPin->PinToolTip = TEXT("Product (m * v)");

    // The module is 'uncooked' and thus only compiles with editor data, but still...
#if WITH_EDITORONLY_DATA
    InputPin->PinFriendlyName = LOCTEXT("v", "v");
    MatrixPin->PinFriendlyName = LOCTEXT("m", "m");
    OutputPin->PinFriendlyName = LOCTEXT("v_out", "vout");
#endif

    if (!CurrentOperation.ShortName.IsNone())
    {
        SetPinType(InputPin, CurrentOperation.OuterType, TEXT("Input vector"));
        SetPinType(MatrixPin, CurrentOperation.MatrixType, TEXT("Multiplication Matrix"));
        SetPinType(OutputPin, CurrentOperation.OuterType, TEXT("Product (m * vin)"));
    }
}


bool UK2Node_mxv::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const
{
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

    if (MyPin->PinName == vin || MyPin->PinName == vout)
    {
        for (const auto& Op : SupportedOperations)
        {
            if (Op.OuterType.Matches(OtherPin->PinType)) return false;
        }
    }
    else if (MyPin->PinName == m)
    {
        for (const auto& Op : SupportedOperations)
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

    CurrentOperation = FK2MxVOp();
    for (const auto& Op : SupportedOperations)
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
        SetPinTypeToWildcard(InputPin, TEXT("Input vector"));
        SetPinTypeToWildcard(MatrixPin, TEXT("Multiplication Matrix (SRotationMatrix or SStateTransform)"));
        SetPinTypeToWildcard(OutputPin, TEXT("Product (m * vin)"));
    }
    else
    {
        SetPinType(InputPin, CurrentOperation.OuterType, TEXT("Input vector"));
        SetPinType(MatrixPin, CurrentOperation.MatrixType, TEXT("Multiplication Matrix"));
        SetPinType(OutputPin, CurrentOperation.OuterType, TEXT("Product (m * vin)"));
    }
}

void UK2Node_mxv::SetPinType(UEdGraphPin* Pin, const FK2Type& type, const FString& ToolTip)
{
    SetPinType(Pin, type.Category, type.SubCategoryObject, type.Container, FString::Printf(TEXT("%s (%s)"), *ToolTip, *type.TypeName.ToString()));
}

void UK2Node_mxv::SetPinTypeToWildcard(UEdGraphPin* Pin, const FString& ToolTip)
{
    SetPinType(Pin, UEdGraphSchema_K2::PC_Wildcard, nullptr, EPinContainerType::None, ToolTip);
}

bool UK2Node_mxv::SetPinType(UEdGraphPin* Pin, FName Category, TWeakObjectPtr<UScriptStruct> SubCategoryObject, EPinContainerType Container, const FString& ToolTip)
{
    bool bUpdatePin = Pin->PinType.PinCategory != Category;
    bUpdatePin |= Pin->PinType.PinSubCategoryObject != SubCategoryObject;
    bUpdatePin |= Pin->PinType.ContainerType != Container;

    if (bUpdatePin)
    {
        Pin->PinType.PinCategory = Category;
        Pin->PinType.PinSubCategoryObject = SubCategoryObject;
        Pin->PinType.ContainerType = Container;
        Pin->PinToolTip = ToolTip;

        PinTypeChanged(Pin);
    }

    return bUpdatePin;
}


void UK2Node_mxv::PinTypeChanged(UEdGraphPin* Pin)
{
    Super::PinTypeChanged(Pin);

    // Notify any connections that this pin changed... which gives them the
    // opportunity to adapt, themselves...
    for (auto Connection : Pin->LinkedTo)
    {
        if (auto MathGeneric = Cast<IK2Node_MathGenericInterface>(Connection->GetOwningNode()))
        {
            MathGeneric->NotifyConnectionChanged(Connection, Pin);
        }
    }

    const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
    K2Schema->ForceVisualizationCacheClear();
}


void UK2Node_mxv::NotifyConnectionChanged(UEdGraphPin* Pin, UEdGraphPin* Connection)
{
    auto& PinType = Pin->PinType;
    auto& ConnectedPinType = Connection->PinType;

    // Only consider flipping if this type is a wildcard, but the other one isn't...
    if (PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard && ConnectedPinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard)
    {
        NodeConnectionListChanged();
    }
}


bool UK2Node_mxv::CheckForErrors(FKismetCompilerContext& CompilerContext, FK2MxVOp& Operation)
{
    auto InputPin = FindPinChecked(vin);
    auto MatrixPin = FindPinChecked(m);
    auto OutputPin = FindPinChecked(vout);

    for (const auto& Op : SupportedOperations)
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

    FK2MxVOp Operation;
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
    for (const FK2MxVOp& Op : SupportedOperations)
    {
        Tooltip = Tooltip.Join(bIsFirstItem ? ListStart : ListSItemeparator, Tooltip, Op.OuterType.GetDisplayNameText());
        bIsFirstItem = false;
    }

    return Tooltip;
}

#undef LOCTEXT_NAMESPACE