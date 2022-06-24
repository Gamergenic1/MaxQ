// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "K2Node_upack.h"
#include "K2Utilities.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "ToolMenu.h"
#include "K2Node_CallFunction.h"
#include "SpiceK2.h"
#include "SpicePlatformDefs.h"
#include "K2SingleInputOp.h"
//#include "EdGraphSchema_K2.h"
//#include "KismetCompiler.h"


#define LOCTEXT_NAMESPACE "K2Node_upack"


UK2Node_upack::UK2Node_upack(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SupportedOperations.Add(FK2SingleInputOp{ "vupack dimensionless vector", USpiceK2::vupack_vector, FK2Type::SDimensionlessVector() });
    SupportedOperations.Add(FK2SingleInputOp{ "vupack distance vector", USpiceK2::vupack_vector, FK2Conversion::SDistanceVectorToSDimensionlessVector() });
    SupportedOperations.Add(FK2SingleInputOp{ "vupack velocity vector", USpiceK2::vupack_vector, FK2Conversion::SVelocityVectorToSDimensionlessVector() });
    SupportedOperations.Add(FK2SingleInputOp{ "vupack angular velocity", USpiceK2::vupack_vector, FK2Conversion::SAngularVelocityToSDimensionlessVector() });
    SupportedOperations.Add(FK2SingleInputOp{ "vupack dimensionless state vector", USpiceK2::vupack_state_vector, FK2Type::SDimensionlessStateVector() });
    SupportedOperations.Add(FK2SingleInputOp{ "vupack state vector", USpiceK2::vupack_state_vector, FK2Conversion::SStateVectorToSDimensionlessStateVector() });

    for (const auto& op : SupportedOperations)
    {
        SupportedTypes.Add(op.OuterType);

#if WITH_EDITOR
        // Ensure the specified actions actually exist!
        if (!op.OuterToInnerConversion.ConversionName.IsNone())
        {
            check(USpiceK2::StaticClass()->FindFunctionByName(op.OuterToInnerConversion.ConversionName));
        }
        if (!op.K2NodeName.IsNone())
        {
            check(USpiceK2::StaticClass()->FindFunctionByName(op.K2NodeName));
        }
#endif
    }

    InputPinName = "Vec";
}



void UK2Node_upack::AllocateDefaultPins()
{
    Super::AllocateDefaultPins();

    const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

    for (int i = 0; i < USpiceK2::vupack_outputs_n; ++i)
    {
        const auto& PinName = USpiceK2::vupack_outputs[i];
        auto Pin { CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Real, FName(PinName)) };
        Pin->PinToolTip = TEXT("double precision input scalar");
    }

    auto PinCategory = UEdGraphSchema_K2::PC_Wildcard;
    if (!OperandType.Category.IsNone() && OperandType.Category != UEdGraphSchema_K2::PC_Wildcard)
    {
        PinCategory = OperandType.Category;
    }

    auto InputPin = CreatePin(EGPD_Input, PinCategory, CreateUniquePinName(InputPinName));
    if (!OperandType.Category.IsNone() && OperandType.Category != UEdGraphSchema_K2::PC_Wildcard)
    {
        InputPin->PinType.PinSubCategoryObject = OperandType.SubCategoryObject;
        InputPin->PinType.ContainerType = OperandType.Container;
    }

    InputPin->PinToolTip = TEXT("vector value");

    RefreshOperand();
}


void UK2Node_upack::ReconstructNode()
{
    Super::ReconstructNode();
}

void UK2Node_upack::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
    Super::ReallocatePinsDuringReconstruction(OldPins);
}

bool UK2Node_upack::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const
{
    const auto& MyPinType = MyPin->PinType;
    const auto& OtherPinType = OtherPin->PinType;

    if (MyPin->Direction == EEdGraphPinDirection::EGPD_Output)
    {
        bool ConnectionOkay = OtherPinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard || OtherPinType.PinCategory == UEdGraphSchema_K2::PC_Double || OtherPinType.PinCategory == UEdGraphSchema_K2::PC_Real;

        if (!ConnectionOkay)
        {
            OutReason = TEXT("Output must be real");
        }
        return !ConnectionOkay;
    }

    bool FixedType = !OperandType.Category.IsNone() && OperandType.Category != UEdGraphSchema_K2::PC_Wildcard;

    if (FixedType && MyPin->Direction == EEdGraphPinDirection::EGPD_Input)
    {
        if (OperandType.Matches(OtherPinType)) return false;
        if (OtherPinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard) return false;

        OutReason = TEXT("Pin type must match exactly");
        return true; 
    }

    if (MyPinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard)
    {
        if(OtherPinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard) return false;
        
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


void UK2Node_upack::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
    Super::NotifyPinConnectionListChanged(Pin);
}

void UK2Node_upack::NodeConnectionListChanged()
{
    Super::NodeConnectionListChanged();

    bool NodeIsGeneric = true;
    bool bOperandChanged = false;
    FEdGraphPinType FoundType;

    // Determine if there are any connected pins that aren't wildcards.
    // And, if so, what type is it connected to?
    UEdGraphPin** ppInputPin = Pins.FindByPredicate([](const UEdGraphPin* Pin) -> bool
    {
        return Pin->Direction == EEdGraphPinDirection::EGPD_Input;
    });

    if (!ppInputPin)
    {
        return;
    }

    UEdGraphPin* InputPin{ *ppInputPin };

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
        // Switch non-wildcard pin to wildcards.
        auto& PinType = InputPin->PinType;

        bool bUpdatePin = PinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard;
        bUpdatePin |= PinType.PinSubCategoryObject != nullptr;
        bUpdatePin |= PinType.ContainerType != EPinContainerType::None;

        bOperandChanged = !(OperandType == FK2Type::Wildcard());
        OperandType = FK2Type::Wildcard();

        if (bUpdatePin)
        {
            PinType.PinCategory = UEdGraphSchema_K2::PC_Wildcard;
            PinType.PinSubCategoryObject = nullptr;
            PinType.ContainerType = EPinContainerType::None;

            PinTypeChanged(InputPin);
        }
    }
    else
    {
        // Find what supported operand type is connected...
        for (const auto& op : SupportedTypes)
        {
            if (op.Is(FoundType))
            {
                bOperandChanged = !(OperandType == op);
                OperandType = op;
                break;
            }
        }

        // Flip a generic pin to this type...
        auto& PinType = InputPin->PinType;

        bool bUpdatePin = PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard;

        if (bUpdatePin)
        {
            PinType.PinCategory = OperandType.Category;
            PinType.PinSubCategoryObject = OperandType.SubCategoryObject;
            PinType.ContainerType = OperandType.Container;

            PinTypeChanged(InputPin);
        }
    }

    RefreshOperand();
}

void UK2Node_upack::PinTypeChanged(UEdGraphPin* Pin)
{
    Super::PinTypeChanged(Pin);

    const auto& PinType { Pin->PinType };

    if (Pin->Direction == EEdGraphPinDirection::EGPD_Input)
    {
        // Update the tooltip
        for (const auto& Type : SupportedTypes)
        {
            if (Type.Is(PinType))
            {
                Pin->PinToolTip = FString::Printf(TEXT("Vector value (%s)"), *(Type.GetDisplayNameString()));
                break;
            }
        }

        // Notify any connections that this pin changed... which gives them the
        // opportunity to adapt, themselves...
        for (auto Connection : Pin->LinkedTo)
        {
            if (auto MathGeneric = Cast<IK2Node_MathGenericInterface>(Connection->GetOwningNode()))
            {
                MathGeneric->NotifyConnectionChanged(Connection, Pin);
            }
        }
    }
}


void UK2Node_upack::NotifyConnectionChanged(UEdGraphPin* Pin, UEdGraphPin* Connection)
{
    auto& PinType = Pin->PinType;
    auto& ConnectedPinType = Connection->PinType;

    // Only consider flipping if this type is a wildcard, but the other one isn't...
    if (PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard && ConnectedPinType.PinCategory != UEdGraphSchema_K2::PC_Wildcard)
    {
        NodeConnectionListChanged();
    }
}


bool UK2Node_upack::CheckForErrors(FKismetCompilerContext& CompilerContext, FK2SingleInputOp& Operation)
{
    for (const auto& op : SupportedOperations)
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

void UK2Node_upack::Serialize(FArchive& Ar)
{
    Super::Serialize(Ar);
}

void UK2Node_upack::PostLoad()
{
    Super::PostLoad();
}

void UK2Node_upack::PostPasteNode()
{
    Super::PostPasteNode();

//    RestoreStateMachineNode();
}


bool UK2Node_upack::IsActionFilteredOut(FBlueprintActionFilter const& Filter)
{
    return false;
}

FSlateIcon UK2Node_upack::GetIconAndTint(FLinearColor& OutColor) const
{
    OutColor = FColor::Emerald;
    return FSlateIcon("EditorStyle", "Kismet.AllClasses.FunctionIcon");
}

FLinearColor UK2Node_upack::GetNodeTitleColor() const
{
    return NodeBackgroundColor;
}


void UK2Node_upack::RefreshOperand()
{
    if (OperandType.SubCategoryObject.Get())
    {
        PinLabels.Empty();

        PinLabels = FK2Type::GetTypePinLabels(OperandType.SubCategoryObject.Get());
    }
    else
    {
        PinLabels.Empty();

        constexpr int NumberOfOutputs = 3;

        for (int i = 0; i < NumberOfOutputs; ++i)
        {
            PinLabels.Add(FString(USpiceK2::vupack_outputs[i]));
        }
    }

    bool visibilityChange = false;

    for (int i = 0; i < USpiceK2::vupack_outputs_n; ++i)
    {
        const auto& PinName = FName(USpiceK2::vupack_outputs[i]);
        auto Pin = FindPin(PinName);
        if (i < PinLabels.Num())
        {
            Pin->PinFriendlyName = FText::FromString(PinLabels[i]);
            visibilityChange |= Pin->bHidden;
            Pin->bHidden = false;
        }
        else
        {
            visibilityChange |= !Pin->bHidden;
            Pin->bHidden = true;
        }
    }

    if (visibilityChange)
    {
        GetGraph()->NotifyGraphChanged();
        FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
    }
    else
    {
        const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
        K2Schema->ForceVisualizationCacheClear();
    }
}

void UK2Node_upack::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
    Super::ExpandNode(CompilerContext, SourceGraph);

    auto Schema = Cast< UEdGraphSchema_K2 >(GetSchema());

    FK2SingleInputOp Operation;

    if (CheckForErrors(CompilerContext, Operation))
    {
        BreakAllNodeLinks();
        return;
    }

    UEdGraphPin** ppInputPin = Pins.FindByPredicate([](const UEdGraphPin* Pin) -> bool
    {
        return Pin->Direction == EEdGraphPinDirection::EGPD_Input;
    });

    if (!ppInputPin)
    {
        CompilerContext.MessageLog.Error(*LOCTEXT("Error", "Node @@ had an internal type error.").ToString(), this);
        BreakAllNodeLinks();
        return;
    }

    UEdGraphPin* InputPin{ *ppInputPin };

    auto InternalNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
    InternalNode->FunctionReference.SetExternalMember(Operation.K2NodeName, USpiceK2::StaticClass());
    InternalNode->AllocateDefaultPins();
    CompilerContext.MessageLog.NotifyIntermediateObjectCreation(InternalNode, this);

    uint32 outputCount = 0;
    for(const auto& PinName : USpiceK2::vupack_outputs )
    {
        auto OutputPin = FindPin(FName{PinName}, EEdGraphPinDirection::EGPD_Output);
        if (auto InternalPin = InternalNode->FindPin(FName{ PinName }, EEdGraphPinDirection::EGPD_Output))
        {
            MovePinLinksOrCopyDefaults(CompilerContext, OutputPin, InternalPin);
            outputCount++;
        }
    }

    auto InternalIn { InternalNode->FindPin(FName{ USpiceK2::vupack_input }) };

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
}

void UK2Node_upack::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    RegisterAction(ActionRegistrar, GetClass());
}

FText UK2Node_upack::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    constexpr bool bUseShortNameForTitle{ true };

    switch (TitleType)
    {
    case ENodeTitleType::FullTitle:
        /** The full title, may be multiple lines. */
        return LOCTEXT("ListViewTitle", "vupack (experimental)");
        if (!bUseShortNameForTitle && !OperandType.TypeName.IsNone())
        {
            return FText::FromString(FString::Printf(TEXT("vupack %s"), *OperandType.TypeName.ToString()));
        }
        break;
    case ENodeTitleType::MenuTitle:
        /** Menu Title for context menus to be displayed in context menus referencing the node. */
        return LOCTEXT("MenuTitle", "vupack - Unpack MaxQ vector (experimental)");
    case ENodeTitleType::ListView:
        /** More concise, single line title. */
        return LOCTEXT("ListViewTitle", "vupack - Unpack vector (experimental)");
    }

    return LOCTEXT("ShortTitle", "vpack");
}



FText UK2Node_upack::GetMenuCategory() const
{
    return LOCTEXT("Category", "MaxQ|Math|Vector");
}


FText UK2Node_upack::GetKeywords() const
{
    return LOCTEXT("Keywords", "VECTOR");
}


FText UK2Node_upack::GetTooltipText() const
{
    
    FText Tooltip = LOCTEXT("Tooltip", "Unpack a MaxQ vector Type.\nStill experimental/under testing.\nThe intent is to support limited wildcards in a single action.\n\nSupports");

    FText ListStart = LOCTEXT("ListStart", ":\n");
    FText ListSItemeparator = LOCTEXT("ListItemSeparator", ",\n");
    bool bIsFirstItem = true;
    for (const FK2Type& Type : SupportedTypes)
    {
        Tooltip = Tooltip.Join(bIsFirstItem ? ListStart : ListSItemeparator, Tooltip, Type.GetDisplayNameText());
        bIsFirstItem = false;
    }

    return Tooltip;
}

#undef LOCTEXT_NAMESPACE