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


#include "K2Node_norm.h"
#include "K2Utilities.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "ToolMenu.h"
#include "K2Node_CallFunction.h"
#include "SpiceK2.h"
#include "SpicePlatformDefs.h"
#include "K2Node_norm.h"


#define LOCTEXT_NAMESPACE "K2Node_norm"

UK2Node_norm::UK2Node_norm(const FObjectInitializer& ObjectInitializer)
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



void UK2Node_norm::AllocateDefaultPins()
{
    Super::AllocateDefaultPins();

    const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

    auto InputPin{ CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, FName("vin")) };
    InputPin->PinToolTip = TEXT("Input Vector");

    auto OutputPin{ CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, FName("out")) };
    OutputPin->PinToolTip = TEXT("Vector magnitude");

    // The module is 'uncooked' and thus only compiles with editor data, but still...
#if WITH_EDITORONLY_DATA
    InputPin->PinFriendlyName = LOCTEXT("v", "v");
    OutputPin->PinFriendlyName = LOCTEXT("v_norm", "vmag");
#endif

    if (!CurrentOperation.ShortName.IsNone())
    {
        SetPinType(this, InputPin, CurrentOperation.InputVectorType);
        SetPinType(this, OutputPin, CurrentOperation.OutputScalarType);
    }
}


void UK2Node_norm::ReconstructNode()
{
    Super::ReconstructNode();
}

void UK2Node_norm::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
    Super::ReallocatePinsDuringReconstruction(OldPins);
}

bool UK2Node_norm::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const
{
    const auto& MyPinType{ MyPin->PinType };
    const auto& OtherPinType { OtherPin->PinType };
    const bool bIsOutput { MyPin->Direction == EEdGraphPinDirection::EGPD_Output };

    if (!CurrentOperation.ShortName.IsNone())
    {
        const FK2Type& RequiredType = bIsOutput ?
            CurrentOperation.OutputScalarType : CurrentOperation.InputVectorType;
        
        if (!RequiredType.Is(OtherPinType))
        {
            OutReason = FString::Printf(TEXT("Must connect to type %s"), *RequiredType.TypeName.ToString());
            return true;
        }
        return false;
    }

    for (const auto& Op : GetSupportedOperations())
    {
        const FK2Type& MatchingType = MyPin->Direction == EEdGraphPinDirection::EGPD_Input ? Op.InputVectorType : Op.OutputScalarType;
        
        if(MatchingType.Matches(OtherPinType)) return false;
    }

    OutReason = TEXT("Pin connection type not supported");
    return true;
}


void UK2Node_norm::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
    Super::NotifyPinConnectionListChanged(Pin);
}

void UK2Node_norm::NodeConnectionListChanged()
{
    Super::NodeConnectionListChanged();

    auto InputPin = FindPinChecked(FName("vin"));
    auto OutputPin = FindPinChecked(FName("out"));

    CurrentOperation = OperationType();
    for (const auto& Op : GetSupportedOperations())
    {
        if ((InputPin->LinkedTo.Num() > 0 && Op.InputVectorType.Is(InputPin->LinkedTo[0]->PinType)) || (OutputPin->LinkedTo.Num() > 0 && Op.OutputScalarType.Is(OutputPin->LinkedTo[0]->PinType)))
        {
            CurrentOperation = Op;
            break;
        }
    }

    bool NodeIsGeneric = CurrentOperation.ShortName.IsNone();

    if (NodeIsGeneric)
    {
        SetPinTypeToWildcard(this, InputPin, TEXT("Input vector"));
        SetPinTypeToWildcard(this, OutputPin, TEXT("Vector magnitude"));
    }
    else
    {
        SetPinType(this, InputPin, CurrentOperation.InputVectorType, FString::Printf(TEXT("Input vector (%s)"), *CurrentOperation.InputVectorType.TypeName.ToString()));
        SetPinType(this, OutputPin, CurrentOperation.OutputScalarType, FString::Printf(TEXT("Magnitude (%s)"), *CurrentOperation.OutputScalarType.TypeName.ToString()));
    }
}

void UK2Node_norm::PinTypeChanged(UEdGraphPin* Pin)
{
    Super::PinTypeChanged(Pin);

    ThisPinTypeChanged(Pin);
}

bool UK2Node_norm::CheckForErrors(FKismetCompilerContext& CompilerContext, OperationType& Operation)
{
    auto InputPin = FindPinChecked(FName("vin"));
    auto OutputPin = FindPinChecked(FName("out"));

    Operation = OperationType();
    for (const auto& Op : GetSupportedOperations())
    {
        if ((InputPin->LinkedTo.Num() > 0 && Op.InputVectorType.Is(InputPin->LinkedTo[0]->PinType)) && (OutputPin->LinkedTo.Num() > 0 && Op.OutputScalarType.Is(OutputPin->LinkedTo[0]->PinType)))
        {
            Operation = Op;
            return false;
        }
    }

    CompilerContext.MessageLog.Error(*LOCTEXT("Error", "Node @@ had an operand type error.").ToString(), this);
    return true;
}


FSlateIcon UK2Node_norm::GetIconAndTint(FLinearColor& OutColor) const
{
    OutColor = FColor::Emerald;
    return FSlateIcon("EditorStyle", "Kismet.AllClasses.FunctionIcon");
}

FLinearColor UK2Node_norm::GetNodeTitleColor() const
{
    return NodeBackgroundColor;
}


void UK2Node_norm::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
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
    UEdGraphPin* OutputPin{ FindPinChecked(TEXT("out"), EEdGraphPinDirection::EGPD_Output) };

    auto InternalNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
    InternalNode->FunctionReference.SetExternalMember(Operation.K2NodeName, USpiceK2::StaticClass());
    InternalNode->AllocateDefaultPins();
    CompilerContext.MessageLog.NotifyIntermediateObjectCreation(InternalNode, this);

    auto InternalIn = InternalNode->FindPinChecked(FName(USpiceK2::vnorm_in));

    if (!Operation.InputToVectorConversion.ConversionName.IsNone())
    {
        auto ConversionNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);

        ConversionNode->FunctionReference.SetExternalMember(Operation.InputToVectorConversion.ConversionName, USpiceK2::StaticClass());
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

    if (!Operation.ScalarToOutputConversion.ConversionName.IsNone())
    {
        auto ConversionNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);

        ConversionNode->FunctionReference.SetExternalMember(Operation.ScalarToOutputConversion.ConversionName, USpiceK2::StaticClass());
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

void UK2Node_norm::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    RegisterAction(ActionRegistrar, GetClass());
}

FText UK2Node_norm::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    constexpr bool bUseShortNameForTitle{ true };

    switch (TitleType)
    {
    case ENodeTitleType::FullTitle:
        /** The full title, may be multiple lines. */
        return LOCTEXT("ListViewTitle", "vnorm");
    case ENodeTitleType::MenuTitle:
        /** Menu Title for context menus to be displayed in context menus referencing the node. */
        return LOCTEXT("MenuTitle", "vnorm - Vector Magnitude");
    case ENodeTitleType::ListView:
        /** More concise, single line title. */
        return LOCTEXT("ListViewTitle", "vnorm - Vector Magnitude");
    }

    return LOCTEXT("ShortTitle", "vnorm");
}

FText UK2Node_norm::GetMenuCategory() const
{
    return LOCTEXT("Category", "MaxQ|Math|Vector");
}


FText UK2Node_norm::GetKeywords() const
{
    return LOCTEXT("Keywords", "VECTOR, UNIT, MAGNITUDE");
}


FText UK2Node_norm::GetTooltipText() const
{
    FText Tooltip = LOCTEXT("Tooltip", "Compute the magnitude of a double precision, 3-dimensional vector.  Support limited wildcards in a single action.");

    FText ListStart = LOCTEXT("ListStart", ":\n");
    FText ListSItemeparator = LOCTEXT("ListItemSeparator", ",\n");
    bool bIsFirstItem = true;
    for (const OperationType& Op : GetSupportedOperations())
    {
        Tooltip = Tooltip.Join(bIsFirstItem ? ListStart : ListSItemeparator, Tooltip, Op.InputVectorType.GetDisplayNameText());
        bIsFirstItem = false;
    }

    return Tooltip;
}

const TArray<UK2Node_norm::OperationType>& UK2Node_norm::GetSupportedOperations() const
{
    static const TArray<OperationType> SupportedOperations
    {
        OperationType{ "vnorm dimensionless vector", FName(USpiceK2::vnorm_vector), FK2Type::SDimensionlessVector(), FK2Type::Double() },
        OperationType{ "vnorm distance vector",  USpiceK2::vnorm_vector, FK2Conversion::SDistanceVectorToSDimensionlessVector(), FK2Conversion::DoubleToSDistance() },
        OperationType{ "vnorm velocity vector",  USpiceK2::vnorm_vector, FK2Conversion::SVelocityVectorToSDimensionlessVector(), FK2Conversion::DoubleToSSpeed() },
        OperationType{ "vnorm angular velocity",  USpiceK2::vnorm_vector, FK2Conversion::SAngularVelocityToSDimensionlessVector(), FK2Conversion::DoubleToSAngularRate() }
    };

    return SupportedOperations;
}

#undef LOCTEXT_NAMESPACE