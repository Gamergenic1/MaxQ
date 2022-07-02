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


#include "K2Node_TwoInOneOut.h"
#include "K2Utilities.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "ToolMenu.h"
#include "K2Node_CallFunction.h"
#include "SpiceK2.h"
//#include "EdGraphSchema_K2.h"
//#include "KismetCompiler.h"


#define LOCTEXT_NAMESPACE "K2Node_TwoInOneOut"


UK2Node_TwoInOneOut::UK2Node_TwoInOneOut(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
#if WITH_EDITOR
    for (const auto& op : GetSupportedOperations())
    {
        op.CheckClass(USpiceK2::StaticClass());
    }
#endif
}


void UK2Node_TwoInOneOut::AllocateDefaultPins()
{
    Super::AllocateDefaultPins();

    for (FName PinName : PinNames)
    {   
        if (!FindPin(PinName))
        {
            AllocateInputPin(PinName);
        }
    }

    while (PinNames.Num() < 2)
    {
        CreateInputPin();
    }

    if(!FindPin(OutputPinName))
    {
        FName PinCategory = UEdGraphSchema_K2::PC_Wildcard;
        if (!OperandType.Category.IsNone() && OperandType.Category != UEdGraphSchema_K2::PC_Wildcard)
        {
            PinCategory = OperandType.Category;
        }

        UEdGraphPin* OutputPin = CreatePin(EGPD_Output, PinCategory, CreateUniquePinName(OutputPinName));
        if (!OperandType.Category.IsNone() && OperandType.Category != UEdGraphSchema_K2::PC_Wildcard)
        {
            SetPinType(this, OutputPin, OperandType);
        }

        OutputPin->PinToolTip = OutputPinName.ToString() + TEXT(" of inputs");
    }
}


void UK2Node_TwoInOneOut::ReconstructNode()
{
    Super::ReconstructNode();
}

void UK2Node_TwoInOneOut::CreateInputPin()
{
    FName PinName;
    AllocateInputPin(PinName);

    PinNames.Add(PinName);
}

void UK2Node_TwoInOneOut::AllocateInputPin(FName& PinName /*= NAME_None*/)
{
    FName PinCategory = UEdGraphSchema_K2::PC_Wildcard;

    if (!OperandType.Category.IsNone() && OperandType.Category != UEdGraphSchema_K2::PC_Wildcard)
    {
        PinCategory = OperandType.Category;
    }

    if (PinName.IsNone())
    {
        PinName = CreateUniquePinName("v");
    }

    UEdGraphPin* NewPin = CreatePin(EGPD_Input, PinCategory, PinName);
    if (NewPin->PinName.IsNone())
    {
        // Makes sure pin has a name for lookup purposes but user will never see it
        NewPin->PinName = CreateUniquePinName(TEXT("v"));
        PinName = NewPin->PinName;
    }

    if (!OperandType.Category.IsNone() && OperandType.Category != UEdGraphSchema_K2::PC_Wildcard)
    {
        NewPin->PinType.PinSubCategoryObject = OperandType.SubCategoryObject;
        NewPin->PinType.ContainerType = OperandType.Container;
    }

#if WITH_EDITORONLY_DATA
    NewPin->PinFriendlyName = FText::FromString(TEXT(" "));
#endif
    NewPin->PinToolTip = "Operand";
}

void UK2Node_TwoInOneOut::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
    Super::ReallocatePinsDuringReconstruction(OldPins);
}

bool UK2Node_TwoInOneOut::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const
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


void UK2Node_TwoInOneOut::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
    Super::NotifyPinConnectionListChanged(Pin);
}

void UK2Node_TwoInOneOut::NodeConnectionListChanged()
{
    Super::NodeConnectionListChanged();

    bool NodeIsGeneric = true;
    bool bOperandChanged = false;
    FEdGraphPinType FoundType;

    // Determine if there are any connected pins that aren't wildcards.
    // And, if so, what type is it connected to?
    for (UEdGraphPin* Pin : Pins)
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

    if (NodeIsGeneric)
    {
        // Switch any non-wildcard pins to wildcards.
        for (UEdGraphPin* Pin : Pins)
        {
            bOperandChanged |= SetPinTypeToWildcard(this, Pin);
        }
        OperandType = FK2Type::Wildcard();
    }
    else
    {
        // Find what supported operand type is connected...
        for (const auto& op : GetSupportedTypes())
        {
            if (op.Is(FoundType))
            {
                bOperandChanged = !(OperandType == op);
                OperandType = op;

                // Flip any generic pins to this type...
                for (UEdGraphPin* Pin : Pins)
                {
                    bOperandChanged |= SetPinType(this, Pin, OperandType);
                }

                break;
            }
        }
    }

    if (bOperandChanged)
    {
        const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
        K2Schema->ForceVisualizationCacheClear();
    }
}

void UK2Node_TwoInOneOut::PinTypeChanged(UEdGraphPin* Pin)
{
    Super::PinTypeChanged(Pin);

    const auto& PinType { Pin->PinType };

    Pin->PinToolTip = Pin->Direction == EEdGraphPinDirection::EGPD_Input ? TEXT("Operand") : OutputPinName.ToString() + TEXT(" of input vectors");

    // Update the tooltip
    for (const auto& Type : GetSupportedTypes())
    {
        if (Type.Is(PinType))
        {
            Pin->PinToolTip = FString::Printf(TEXT("%s (%s)"), *Pin->PinToolTip, *Type.GetDisplayNameString());
            break;
        }
    }

    ThisPinTypeChanged(Pin);
}


bool UK2Node_TwoInOneOut::CheckForErrors(FKismetCompilerContext& CompilerContext, OperationType& Operation)
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

void UK2Node_TwoInOneOut::Serialize(FArchive& Ar)
{
    Super::Serialize(Ar);
}

void UK2Node_TwoInOneOut::PostLoad()
{
    Super::PostLoad();
}

void UK2Node_TwoInOneOut::PostPasteNode()
{
    Super::PostPasteNode();

//    RestoreStateMachineNode();
}

void UK2Node_TwoInOneOut::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    RegisterAction(ActionRegistrar, GetClass());
}

bool UK2Node_TwoInOneOut::IsActionFilteredOut(FBlueprintActionFilter const& Filter)
{
    return false;
}

FSlateIcon UK2Node_TwoInOneOut::GetIconAndTint(FLinearColor& OutColor) const
{
    OutColor = FColor::Emerald;
    return FSlateIcon("EditorStyle", "Kismet.AllClasses.FunctionIcon");
}

FLinearColor UK2Node_TwoInOneOut::GetNodeTitleColor() const
{
    return NodeBackgroundColor;
}

UEdGraphPin* UK2Node_TwoInOneOut::GetReturnValuePin(UEdGraphNode* Node) const
{
    UEdGraphPin* Pin = Node->FindPin(UEdGraphSchema_K2::PN_ReturnValue);
    check(Pin == nullptr || Pin->Direction == EGPD_Output); // If pin exists, it must be output
    return Pin;
}

void UK2Node_TwoInOneOut::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
    Super::ExpandNode(CompilerContext, SourceGraph);

    auto Schema = Cast< UEdGraphSchema_K2 >(GetSchema());

    OperationType Operation;

    if (CheckForErrors(CompilerContext, Operation))
    {
        BreakAllNodeLinks();
        return;
    }

    TArray<UEdGraphPin*> InputPins = Pins.FilterByPredicate([](const UEdGraphPin* Pin) -> bool
    {
        return Pin->Direction == EEdGraphPinDirection::EGPD_Input;
    });

    UEdGraphPin** ppOutputPin = Pins.FindByPredicate([](const UEdGraphPin* Pin) -> bool
    {
        return Pin->Direction == EEdGraphPinDirection::EGPD_Output;
    });

    if (!ppOutputPin)
    {
        CompilerContext.MessageLog.Error(*LOCTEXT("Error", "Node @@ had an internal type error.").ToString(), this);
        BreakAllNodeLinks();
        return;
    }

    UEdGraphPin* OutputPin { *ppOutputPin };

    TArray<UEdGraphPin*> InternalInputPins;
    UEdGraphPin* InternalV1Pin{ nullptr };
    UEdGraphPin* InternalOutputPin{ nullptr };

    for (int i = 0; i < InputPins.Num() - 1; ++i)
    {
        auto InternalNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
        InternalNode->FunctionReference.SetExternalMember(Operation.K2NodeName, USpiceK2::StaticClass());
        InternalNode->AllocateDefaultPins();
        CompilerContext.MessageLog.NotifyIntermediateObjectCreation(InternalNode, this);

        auto v1 = InternalNode->FindPinChecked(FName(USpiceK2::vadd_input1), EEdGraphPinDirection::EGPD_Input);
        auto v2 = InternalNode->FindPinChecked(FName(USpiceK2::vadd_input2), EEdGraphPinDirection::EGPD_Input);
        auto out = InternalNode->GetReturnValuePin();

        if (InternalOutputPin)
        {
            Schema->TryCreateConnection(InternalOutputPin, v1);
        }
        else
        {
            InternalInputPins.Add(v1);
        }
        InternalInputPins.Add(v2);
        InternalOutputPin = out;
    }

    check(InternalInputPins.Num() == InputPins.Num());

    if (!Operation.OuterToInnerConversion.ConversionName.IsNone())
    {
        for (int i = 0; i < InputPins.Num(); ++i)
        {

            auto ConversionNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
            ConversionNode->FunctionReference.SetExternalMember(Operation.OuterToInnerConversion.ConversionName, USpiceK2::StaticClass());
            ConversionNode->AllocateDefaultPins();
            CompilerContext.MessageLog.NotifyIntermediateObjectCreation(ConversionNode, this);

            auto value = ConversionNode->FindPinChecked(FName(USpiceK2::conv_input), EEdGraphPinDirection::EGPD_Input);
            auto out = ConversionNode->GetReturnValuePin();

            Schema->TryCreateConnection(out, InternalInputPins[i]);
            MovePinLinksOrCopyDefaults(CompilerContext, InputPins[i], value);
        }
    }
    else
    {
        for (int i = 0; i < InputPins.Num(); ++i)
        {
            MovePinLinksOrCopyDefaults(CompilerContext, InputPins[i], InternalInputPins[i]);
        }
    }

    if (!Operation.InnerToOuterConversion.ConversionName.IsNone())
    {
        auto ConversionNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
        ConversionNode->FunctionReference.SetExternalMember(Operation.InnerToOuterConversion.ConversionName, USpiceK2::StaticClass());
        ConversionNode->AllocateDefaultPins();
        CompilerContext.MessageLog.NotifyIntermediateObjectCreation(ConversionNode, this);

        auto value = ConversionNode->FindPinChecked(FName(USpiceK2::conv_input), EEdGraphPinDirection::EGPD_Input);
        auto out = ConversionNode->GetReturnValuePin();

        Schema->TryCreateConnection(InternalOutputPin, value);
        MovePinLinksOrCopyDefaults(CompilerContext, OutputPin, out);
    }
    else
    {
        MovePinLinksOrCopyDefaults(CompilerContext, OutputPin, InternalOutputPin);
    }

    BreakAllNodeLinks(); 
}

#undef LOCTEXT_NAMESPACE