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


#include "K2Node_minus.h"
#include "K2Utilities.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "ToolMenu.h"
#include "K2Node_CallFunction.h"
#include "SpiceK2.h"
#include "SpicePlatformDefs.h"
#include "K2SingleOutputOp.h"
//#include "EdGraphSchema_K2.h"
//#include "KismetCompiler.h"


#define LOCTEXT_NAMESPACE "K2Node_minus"


UK2Node_minus::UK2Node_minus(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
#if WITH_EDITOR
    for (const auto& op : GetSupportedOperations())
    {
        op.CheckClass(USpiceK2::StaticClass());
    }
#endif
}



void UK2Node_minus::AllocateDefaultPins()
{
    Super::AllocateDefaultPins();

    const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

    auto InputPin{ CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, FName("vin")) };
    InputPin->PinToolTip = TEXT("Input Vector");

    auto OutputPin{ CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, FName("vout")) };
    OutputPin->PinToolTip = TEXT("Output Vector");

    // The module is 'uncooked' and thus only compiles with editor data, but still...
#if WITH_EDITORONLY_DATA
    InputPin->PinFriendlyName = LOCTEXT("v", "v");
    OutputPin->PinFriendlyName = LOCTEXT("v_negated", "-v");
#endif

    if (!OperandType.Category.IsNone() && OperandType.Category != UEdGraphSchema_K2::PC_Wildcard)
    {
        SetPinType(this, InputPin, OperandType);
        SetPinType(this, OutputPin, OperandType);
    }
}


void UK2Node_minus::ReconstructNode()
{
    Super::ReconstructNode();
}

void UK2Node_minus::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
    Super::ReallocatePinsDuringReconstruction(OldPins);
}

bool UK2Node_minus::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const
{
    const auto& MyPinType = MyPin->PinType;
    const auto& OtherPinType = OtherPin->PinType;

    bool FixedType = !OperandType.Category.IsNone() && OperandType.Category != UEdGraphSchema_K2::PC_Wildcard;

    if (FixedType)
    {
        if (OperandType.Matches(OtherPinType)) return false;
        if (OtherPinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard) return false;

        OutReason = TEXT("Pin type must match exactly");
        return true; 
    }

    // !FixedType (Wildcard)
    if (MyPinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard)
    {
        if(OtherPinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard) return false;
        
        const auto& SupportedTypes = GetSupportedTypes();
        for (int i = 0; i < SupportedTypes.Num(); ++i)
        {
            const auto& k2type = SupportedTypes[i];

            if (k2type.Matches(OtherPinType))
            {
                return false;
            }
        }
    }

    OutReason = TEXT("Pin connection type not supported");
    return true;
}


void UK2Node_minus::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
    Super::NotifyPinConnectionListChanged(Pin);
}

void UK2Node_minus::NodeConnectionListChanged()
{
    Super::NodeConnectionListChanged();

    bool NodeIsGeneric = true;

    FEdGraphPinType FoundType;

    for (auto& Pin : Pins)
    {
        for (UEdGraphPin* ConnectedPin : Pin->LinkedTo)
        {
            const auto& ConnectedPinType = ConnectedPin->PinType;

            if (ConnectedPinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard)
            {
                NodeIsGeneric = false;
                FoundType = ConnectedPinType;
                break;
            }
        }
    }

    auto InputPin = FindPinChecked(FName("vin"), EEdGraphPinDirection::EGPD_Input);
    auto OutputPin = FindPinChecked(FName("vout"), EEdGraphPinDirection::EGPD_Output);

    if (NodeIsGeneric)
    {
        SetPinTypeToWildcard(this, InputPin);
        SetPinTypeToWildcard(this, OutputPin);
    }
    else
    {
        // Find what supported operand type is connected...
        bool bFoundTheType = false;
        for (const auto& op : GetSupportedTypes())
        {
            if (op.Is(FoundType))
            {
                OperandType = op;
                SetPinType(this, InputPin, OperandType);
                SetPinType(this, OutputPin, OperandType);
                break;
            }
        }
    }
}

void UK2Node_minus::PinTypeChanged(UEdGraphPin* Pin)
{
    Super::PinTypeChanged(Pin);

    const auto& PinType { Pin->PinType };

    // Update the tooltip
    for (const auto& Type : GetSupportedTypes())
    {
        if (Type.Is(PinType))
        {
            Pin->PinToolTip = FString::Printf(TEXT("Packed Vector (%s)"), *(Type.GetDisplayNameString()));
            break;
        }
    }

    ThisPinTypeChanged(Pin);
}


bool UK2Node_minus::CheckForErrors(FKismetCompilerContext& CompilerContext, OperationType& Operation)
{
    for (const auto& op : GetSupportedOperations())
    {
        if (op.OuterType == OperandType)
        {
            Operation = op;
            return false;
        }
    }

    CompilerContext.MessageLog.Error(*LOCTEXT("Error", "Node @@ had an operand type error.").ToString(), this);
    return true;
}


FSlateIcon UK2Node_minus::GetIconAndTint(FLinearColor& OutColor) const
{
    OutColor = FColor::Emerald;
    return FSlateIcon("EditorStyle", "Kismet.AllClasses.FunctionIcon");
}

FLinearColor UK2Node_minus::GetNodeTitleColor() const
{
    return NodeBackgroundColor;
}


void UK2Node_minus::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
    Super::ExpandNode(CompilerContext, SourceGraph);

    auto Schema = Cast< UEdGraphSchema_K2 >(GetSchema());

    OperationType Operation;

    if (CheckForErrors(CompilerContext, Operation))
    {
        BreakAllNodeLinks();
        return;
    }

    UEdGraphPin* InputPin{ FindPinChecked(TEXT("vin"), EEdGraphPinDirection::EGPD_Input) };
    UEdGraphPin* OutputPin{ FindPinChecked(TEXT("vout"), EEdGraphPinDirection::EGPD_Output) };

    auto InternalNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
    InternalNode->FunctionReference.SetExternalMember(Operation.K2NodeName, USpiceK2::StaticClass());
    InternalNode->AllocateDefaultPins();
    CompilerContext.MessageLog.NotifyIntermediateObjectCreation(InternalNode, this);

    auto InternalIn = InternalNode->FindPinChecked(FName(USpiceK2::vminus_in));
    auto InternalOut = InternalNode->GetReturnValuePin();

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

    BreakAllNodeLinks();
}

void UK2Node_minus::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    RegisterAction(ActionRegistrar, GetClass());
}

FText UK2Node_minus::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    constexpr bool bUseShortNameForTitle{ true };

    switch (TitleType)
    {
    case ENodeTitleType::FullTitle:
        /** The full title, may be multiple lines. */
        if (!bUseShortNameForTitle && !OperandType.TypeName.IsNone())
        {
            return FText::FromString(FString::Printf(TEXT("vminus %s"), *OperandType.TypeName.ToString()));
        }
        return LOCTEXT("ListViewTitle", "vminus");
    case ENodeTitleType::MenuTitle:
        /** Menu Title for context menus to be displayed in context menus referencing the node. */
        return LOCTEXT("MenuTitle", "vminus - Negate vector");
    case ENodeTitleType::ListView:
        /** More concise, single line title. */
        return LOCTEXT("ListViewTitle", "vminus - Negate vector");
    }

    return LOCTEXT("ShortTitle", "vminus");
}



FText UK2Node_minus::GetMenuCategory() const
{
    return LOCTEXT("Category", "MaxQ|Math|Vector");
}


FText UK2Node_minus::GetKeywords() const
{
    return LOCTEXT("Keywords", "VECTOR, NEGATE, NEGATION, NEGATIVE, INVERSE");
}


FText UK2Node_minus::GetTooltipText() const
{
    FText Tooltip = LOCTEXT("Tooltip", "Negate a MaxQ vector Type. E.g., return -V (by value).  Support limited wildcards in a single action.");

    FText ListStart = LOCTEXT("ListStart", ":\n");
    FText ListSItemeparator = LOCTEXT("ListItemSeparator", ",\n");
    bool bIsFirstItem = true;
    for (const FK2Type& Type : GetSupportedTypes())
    {
        Tooltip = Tooltip.Join(bIsFirstItem ? ListStart : ListSItemeparator, Tooltip, Type.GetDisplayNameText());
        bIsFirstItem = false;
    }

    return Tooltip;
}

const TArray<FK2Type>& UK2Node_minus::GetSupportedTypes() const
{
    static const TArray<FK2Type> SupportedTypes
    {
        OperationType::GetTypesFromOperations(GetSupportedOperations())
    };

    return SupportedTypes;
}

const TArray<UK2Node_minus::OperationType>& UK2Node_minus::GetSupportedOperations() const
{
    static const TArray<OperationType> SupportedOperations
    {
        OperationType{ "vminus dimensionless vector", USpiceK2::vminus_vector, FK2Type::SDimensionlessVector() },
        OperationType{ "vminus distance vector",  USpiceK2::vminus_vector, FK2Conversion::SDistanceVectorToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSDistanceVector() },
        OperationType{ "vminus velocity vector",  USpiceK2::vminus_vector, FK2Conversion::SVelocityVectorToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSVelocityVector() },
        OperationType{ "vminus angular velocity",  USpiceK2::vminus_vector, FK2Conversion::SAngularVelocityToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSAngularVelocity() },
        OperationType{ "vminus dimensionless state vector",  USpiceK2::vminus_state_vector, FK2Type::SDimensionlessStateVector() },
        OperationType{ "vminus state vector", USpiceK2::vminus_state_vector, FK2Conversion::SStateVectorToSDimensionlessStateVector(), FK2Conversion::SDimensionlessStateVectorToSStateVector() }
    };

    return SupportedOperations;
}

#undef LOCTEXT_NAMESPACE
