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


#include "K2Node_hat.h"
#include "K2Utilities.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "ToolMenu.h"
#include "K2Node_CallFunction.h"
#include "SpiceK2.h"
#include "SpicePlatformDefs.h"
#include "K2SingleInputOp.h"
//#include "EdGraphSchema_K2.h"
//#include "KismetCompiler.h"


#define LOCTEXT_NAMESPACE "K2Node_hat"


UK2Node_hat::UK2Node_hat(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
#if WITH_EDITOR
    for (const auto& op : GetSupportedOperations())
    {
        op.CheckClass(USpiceK2::StaticClass());
    }
#endif
}



void UK2Node_hat::AllocateDefaultPins()
{
    Super::AllocateDefaultPins();

    const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

    auto InputPin{ CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, FName("vin")) };
    InputPin->PinToolTip = TEXT("Input Vector");

    auto OutputPin{ CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Struct, FName("vout")) };
    OutputPin->PinToolTip = TEXT("Output Vector (SDimensionlessVector)");
    OutputPin->PinType.PinSubCategoryObject = FSDimensionlessVector::StaticStruct();
    OutputPin->PinType.ContainerType = EPinContainerType::None;

    // The module is 'uncooked' and thus only compiles with editor data, but still...
#if WITH_EDITORONLY_DATA
    InputPin->PinFriendlyName = LOCTEXT("v", "v");
    OutputPin->PinFriendlyName = LOCTEXT("v_unit", "v-hat");
#endif

    if (!OperandType.Category.IsNone() && OperandType.Category != UEdGraphSchema_K2::PC_Wildcard)
    {
        SetPinType(this, InputPin, OperandType);
    }
}


void UK2Node_hat::ReconstructNode()
{
    Super::ReconstructNode();
}

void UK2Node_hat::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
    Super::ReallocatePinsDuringReconstruction(OldPins);
}

bool UK2Node_hat::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const
{
    const auto& MyPinType = MyPin->PinType;
    const auto& OtherPinType = OtherPin->PinType;

    if (MyPin->Direction == EEdGraphPinDirection::EGPD_Output)
    {
        if(OtherPinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard) return false;

        if (!FK2Type::SDimensionlessVector().Matches(OtherPinType))
        {
            OutReason = TEXT("Result must match SDimensionlessVector");
            return true;
        }

        return false;
    }

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


void UK2Node_hat::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
    Super::NotifyPinConnectionListChanged(Pin);
}

void UK2Node_hat::NodeConnectionListChanged()
{
    Super::NodeConnectionListChanged();

    auto InputPin = FindPinChecked(FName("vin"), EGPD_Input);

    bool NodeIsGeneric = true;

    FEdGraphPinType FoundType;

    for (UEdGraphPin* ConnectedPin : InputPin->LinkedTo)
    {
        const auto& ConnectedPinType = ConnectedPin->PinType;

        if (ConnectedPinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard)
        {
            NodeIsGeneric = false;
            FoundType = ConnectedPinType;
            break;
        }
    }

    if (NodeIsGeneric)
    {
        SetPinTypeToWildcard(this, InputPin);
        OperandType = FK2Type::Wildcard();
    }
    else
    {
        // Find what supported operand type is connected...
        for (const auto& op : GetSupportedTypes())
        {
            if (op.Is(FoundType))
            {
                OperandType = op;
                SetPinType(this, InputPin, OperandType);
                break;
            }
        }
    }
}

void UK2Node_hat::PinTypeChanged(UEdGraphPin* Pin)
{
    Super::PinTypeChanged(Pin);

    const auto& PinType { Pin->PinType };
    if (Pin->Direction == EEdGraphPinDirection::EGPD_Output) return;


    // Update the tooltip
    Pin->PinToolTip = TEXT("Input vector");
    for (const auto& Type : GetSupportedTypes())
    {
        if (Type.Is(PinType))
        {
            Pin->PinToolTip = FString::Printf(TEXT("Input Vector (%s)"), *(Type.GetDisplayNameString()));
            break;
        }
    }
}


bool UK2Node_hat::CheckForErrors(FKismetCompilerContext& CompilerContext, OperationType& Operation)
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


FSlateIcon UK2Node_hat::GetIconAndTint(FLinearColor& OutColor) const
{
    OutColor = FColor::Emerald;
    return FSlateIcon("EditorStyle", "Kismet.AllClasses.FunctionIcon");
}

FLinearColor UK2Node_hat::GetNodeTitleColor() const
{
    return NodeBackgroundColor;
}


void UK2Node_hat::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
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

    auto InternalIn = InternalNode->FindPinChecked(FName(USpiceK2::vhat_in));
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


    MovePinLinksOrCopyDefaults(CompilerContext, OutputPin, InternalOut);

    BreakAllNodeLinks();
}

void UK2Node_hat::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    RegisterAction(ActionRegistrar, GetClass());
}

FText UK2Node_hat::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    constexpr bool bUseShortNameForTitle{ false };

    switch (TitleType)
    {
    case ENodeTitleType::FullTitle:
        /** The full title, may be multiple lines. */
        return LOCTEXT("ListViewTitle", "vhat");
    case ENodeTitleType::MenuTitle:
        /** Menu Title for context menus to be displayed in context menus referencing the node. */
        return LOCTEXT("MenuTitle", "vhat - Unit vector");
    case ENodeTitleType::ListView:
        /** More concise, single line title. */
        return LOCTEXT("ListViewTitle", "vhat - Unit vector");
    }

    return LOCTEXT("ShortTitle", "vhat");
}

FText UK2Node_hat::GetMenuCategory() const
{
    return LOCTEXT("Category", "MaxQ|Math|Vector");
}


FText UK2Node_hat::GetKeywords() const
{
    return LOCTEXT("Keywords", "VECTOR, UNIT, HAT, NORMAL");
}


FText UK2Node_hat::GetTooltipText() const
{
    FText Tooltip = LOCTEXT("Tooltip", "Compute unit vector from a MaxQ vector Type. E.g., return v-hat (by value).  Support limited wildcards in a single action.");

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


const TArray<FK2Type>& UK2Node_hat::GetSupportedTypes() const
{
    static const TArray<FK2Type> SupportedTypes
    {
        OperationType::GetTypesFromOperations(GetSupportedOperations())
    };

    return SupportedTypes;
}

const TArray<UK2Node_hat::OperationType>& UK2Node_hat::GetSupportedOperations() const
{
    static const TArray<OperationType> SupportedOperations
    {
        OperationType{ "vhat dimensionless vector", USpiceK2::vhat_vector, FK2Type::SDimensionlessVector() },
        OperationType{ "vhat distance vector",  USpiceK2::vhat_vector, FK2Conversion::SDistanceVectorToSDimensionlessVector() },
        OperationType{ "vhat velocity vector",  USpiceK2::vhat_vector, FK2Conversion::SVelocityVectorToSDimensionlessVector() },
        OperationType{ "vhat angular velocity",  USpiceK2::vhat_vector, FK2Conversion::SAngularVelocityToSDimensionlessVector() }
    };

    return SupportedOperations;
}

#undef LOCTEXT_NAMESPACE