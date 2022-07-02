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


#include "K2Node_unorm.h"
#include "K2Utilities.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "ToolMenu.h"
#include "K2Node_CallFunction.h"
#include "SpiceK2.h"
#include "SpicePlatformDefs.h"
#include "K2Node_norm.h"


#define LOCTEXT_NAMESPACE "K2Node_unorm"


UK2Node_unorm::UK2Node_unorm(const FObjectInitializer& ObjectInitializer)
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



void UK2Node_unorm::AllocateDefaultPins()
{
    Super::AllocateDefaultPins();

    const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

    auto InputPin{ CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, FName("v")) };
    InputPin->PinToolTip = TEXT("Input Vector");

    auto OutputPin{ CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, FName("vmag")) };
    OutputPin->PinToolTip = TEXT("Vector magnitude");

    auto UnitVectorOutputPin{ CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Struct, FName("vout")) };
    UnitVectorOutputPin->PinToolTip = TEXT("Vector unit normal (SDimensionlessVector");
    UnitVectorOutputPin->PinType.PinSubCategoryObject = FSDimensionlessVector::StaticStruct();
    UnitVectorOutputPin->PinType.ContainerType = EPinContainerType::None;

    // The module is 'uncooked' and thus only compiles with editor data, but still...
#if WITH_EDITORONLY_DATA
    InputPin->PinFriendlyName = LOCTEXT("v", "v");
    OutputPin->PinFriendlyName = LOCTEXT("v_mag", "vmag");
    UnitVectorOutputPin->PinFriendlyName = LOCTEXT("v_out", "vout");
#endif

    if (!CurrentOperation.ShortName.IsNone())
    {
        SetPinType(this, InputPin, CurrentOperation.InputVectorType, FString::Printf(TEXT("Input vector (%s)"), *CurrentOperation.InputVectorType.TypeName.ToString()));
        SetPinType(this, OutputPin, CurrentOperation.OutputScalarType, FString::Printf(TEXT("Magnitude (%s)"), *CurrentOperation.OutputScalarType.TypeName.ToString()));
    }
}


void UK2Node_unorm::ReconstructNode()
{
    Super::ReconstructNode();
}

void UK2Node_unorm::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
    Super::ReallocatePinsDuringReconstruction(OldPins);
}

bool UK2Node_unorm::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const
{
    const auto& MyPinType{ MyPin->PinType };
    const auto& OtherPinType { OtherPin->PinType };
    const bool bIsOutput { MyPin->Direction == EEdGraphPinDirection::EGPD_Output };

    if (bIsOutput && MyPin == FindPinChecked(FName("vout")))
    {
        bool isokay = OtherPinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard;
        isokay |= OtherPinType.PinCategory == UEdGraphSchema_K2::PC_Struct &&  OtherPinType.PinSubCategoryObject == FSDimensionlessVector::StaticStruct() && OtherPinType.ContainerType == EPinContainerType::None;
        return !isokay;
    }

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


void UK2Node_unorm::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
    Super::NotifyPinConnectionListChanged(Pin);
}

void UK2Node_unorm::NodeConnectionListChanged()
{
    Super::NodeConnectionListChanged();

    auto InputPin = FindPinChecked(FName("v"));
    auto OutputPin = FindPinChecked(FName("vmag"));

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
        SetPinTypeToWildcard(this, InputPin, FString::Printf(TEXT("Input vector (%s)"), TEXT("Input vector")));
        SetPinTypeToWildcard(this, OutputPin, FString::Printf(TEXT("Magnitude (%s)"), TEXT("Vector magnitude")));
    }
    else
    {
        SetPinType(this, InputPin, CurrentOperation.InputVectorType, FString::Printf(TEXT("Input vector (%s)"), *CurrentOperation.InputVectorType.TypeName.ToString()));
        SetPinType(this, OutputPin, CurrentOperation.OutputScalarType, FString::Printf(TEXT("Magnitude (%s)"), *CurrentOperation.OutputScalarType.TypeName.ToString()));
    }
}

void UK2Node_unorm::PinTypeChanged(UEdGraphPin* Pin)
{
    Super::PinTypeChanged(Pin);

    ThisPinTypeChanged(Pin);
}


bool UK2Node_unorm::CheckForErrors(FKismetCompilerContext& CompilerContext, OperationType& Operation)
{
    auto InputPin = FindPinChecked(FName("v"));
    auto OutputPin = FindPinChecked(FName("vmag"));

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


FSlateIcon UK2Node_unorm::GetIconAndTint(FLinearColor& OutColor) const
{
    OutColor = FColor::Emerald;
    return FSlateIcon("EditorStyle", "Kismet.AllClasses.FunctionIcon");
}

FLinearColor UK2Node_unorm::GetNodeTitleColor() const
{
    return NodeBackgroundColor;
}


void UK2Node_unorm::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
    Super::ExpandNode(CompilerContext, SourceGraph);

    auto Schema = Cast< UEdGraphSchema_K2 >(GetSchema());

    OperationType Operation;
    if (CheckForErrors(CompilerContext, Operation))
    {
        BreakAllNodeLinks();
        return;
    }

    UEdGraphPin* InputPin{ FindPinChecked(TEXT("v"), EEdGraphPinDirection::EGPD_Input) };
    UEdGraphPin* DirectionOutputPin{ FindPinChecked(TEXT("vout"), EEdGraphPinDirection::EGPD_Output) };
    UEdGraphPin* MagnitudeOutputPin{ FindPinChecked(TEXT("vmag"), EEdGraphPinDirection::EGPD_Output) };

    auto InternalNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
    InternalNode->FunctionReference.SetExternalMember(Operation.K2NodeName, USpiceK2::StaticClass());
    InternalNode->AllocateDefaultPins();
    CompilerContext.MessageLog.NotifyIntermediateObjectCreation(InternalNode, this);

    auto InternalIn = InternalNode->FindPinChecked(FName(USpiceK2::unorm_vector_input));

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

    auto InternalMagnitudeOut = InternalNode->FindPinChecked(FName(USpiceK2::unorm_vector_output_mag));

    if (!Operation.ScalarToOutputConversion.ConversionName.IsNone())
    {
        auto ConversionNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);

        ConversionNode->FunctionReference.SetExternalMember(Operation.ScalarToOutputConversion.ConversionName, USpiceK2::StaticClass());
        ConversionNode->AllocateDefaultPins();
        CompilerContext.MessageLog.NotifyIntermediateObjectCreation(ConversionNode, this);

        auto ConversionValueInput = ConversionNode->FindPinChecked(FName(USpiceK2::conv_input), EEdGraphPinDirection::EGPD_Input);
        auto ConversionOut = ConversionNode->GetReturnValuePin();

        Schema->TryCreateConnection(InternalMagnitudeOut, ConversionValueInput);
        MovePinLinksOrCopyDefaults(CompilerContext, MagnitudeOutputPin, ConversionOut);
    }
    else
    {
        MovePinLinksOrCopyDefaults(CompilerContext, MagnitudeOutputPin, InternalMagnitudeOut);
    }

    auto InternalDirectionOut = InternalNode->FindPinChecked(FName(USpiceK2::unorm_vector_output_direction));
    MovePinLinksOrCopyDefaults(CompilerContext, DirectionOutputPin, InternalDirectionOut);

    BreakAllNodeLinks();
}

void UK2Node_unorm::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    RegisterAction(ActionRegistrar, GetClass());
}

FText UK2Node_unorm::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    constexpr bool bUseShortNameForTitle{ true };

    switch (TitleType)
    {
    case ENodeTitleType::FullTitle:
        /** The full title, may be multiple lines. */
        return LOCTEXT("ListViewTitle", "unorm");
    case ENodeTitleType::MenuTitle:
        /** Menu Title for context menus to be displayed in context menus referencing the node. */
        return LOCTEXT("MenuTitle", "unorm - Vector magnitude and direction");
    case ENodeTitleType::ListView:
        /** More concise, single line title. */
        return LOCTEXT("ListViewTitle", "unorm - Vector magnitude and direction");
    }

    return LOCTEXT("ShortTitle", "vnorm");
}

FText UK2Node_unorm::GetMenuCategory() const
{
    return LOCTEXT("Category", "MaxQ|Math|Vector");
}


FText UK2Node_unorm::GetKeywords() const
{
    return LOCTEXT("Keywords", "VECTOR, UNIT, MAGNITUDE");
}


FText UK2Node_unorm::GetTooltipText() const
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

const TArray<UK2Node_unorm::OperationType>& UK2Node_unorm::GetSupportedOperations() const
{
    static const TArray<OperationType> SupportedOperations
    {
        OperationType{ "unorm dimensionless vector", FName(USpiceK2::unorm_vector), FK2Type::SDimensionlessVector(), FK2Type::Double() },
        OperationType{ "unorm distance vector",  USpiceK2::unorm_vector, FK2Conversion::SDistanceVectorToSDimensionlessVector(), FK2Conversion::DoubleToSDistance() },
        OperationType{ "unorm velocity vector",  USpiceK2::unorm_vector, FK2Conversion::SVelocityVectorToSDimensionlessVector(), FK2Conversion::DoubleToSSpeed() },
        OperationType{ "unorm angular velocity",  USpiceK2::unorm_vector, FK2Conversion::SAngularVelocityToSDimensionlessVector(), FK2Conversion::DoubleToSAngularRate() }
    };

    return SupportedOperations;
}

#undef LOCTEXT_NAMESPACE