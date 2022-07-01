// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "K2Node_OutWithSelectorOp.h"
#include "K2Utilities.h"
#include "SpiceK2.h"

#include "EdGraphSchema_K2.h"

#include "KismetCompiler.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Node_CallFunction.h"
#include "Textures/SlateIcon.h"

using namespace ENodeTitleType;

#define LOCTEXT_NAMESPACE "K2Node_OutWithSelectorOp"


UK2Node_OutWithSelectorOp::UK2Node_OutWithSelectorOp(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

bool UK2Node_OutWithSelectorOp::IsNodeSafeToIgnore() const {
    return true;
}

void UK2Node_OutWithSelectorOp::AllocateDefaultPins()
{
    Super::AllocateDefaultPins();

    static UEnum* ComponentSelectorEnum = FindObjectChecked<UEnum>(ANY_PACKAGE, TEXT("EK2_ComponentSelector"), /*ExactClass*/true);

    const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

    // Exec pins - In
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);

    // Exec out w/return values
    // Success - Exec
    UEdGraphPin* successPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, successExec_PinName);
    successPin->PinToolTip = TEXT("Exit, if the action succeeds");

    // Success - return
    UEdGraphPin* OutputPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, returnValue_PinName);
    OutputPin->PinToolTip = "Return Value (Wildcard), if successful";

    // Error - Exec
    UEdGraphPin* errorPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, errorExec_PinName);
    errorPin->PinToolTip = TEXT("Exit, if the action fails");

    // Error - return
    UEdGraphPin* errorMessagePin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_String, errorMessage_PinName);
    errorMessagePin->PinToolTip = TEXT("An error message, if the action fails");


    auto selector = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Byte, ComponentSelectorEnum, selector_PinName);
    selector->PinToolTip = TEXT("Selects all, or X/Y/Z subcomponents");
    selector->PinType.PinSubCategoryObject = ComponentSelectorEnum;
    selector->DefaultValue = ComponentSelectorEnum->GetNameStringByValue((int64)EK2_ComponentSelector::All);
    selector->DefaultTextValue = FText::FromName(ComponentSelectorEnum->GetNameByValue((int64)EK2_ComponentSelector::All));
    selector->bAdvancedView = true;
    AdvancedPinDisplay = ENodeAdvancedPins::Hidden;
}

void UK2Node_OutWithSelectorOp::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
    Super::NotifyPinConnectionListChanged(Pin);

    if (Pin == returnValuePin())
    {
//        Pin->PinFriendlyName = FText::GetEmpty();

        FEdGraphPinType& ReturnValuePinType = Pin->PinType;

        Modify();
        Pin->Modify();

        ReturnValuePinType.PinCategory = UEdGraphSchema_K2::PC_Wildcard;
        ReturnValuePinType.PinSubCategory = NAME_None;
        ReturnValuePinType.PinSubCategoryObject = nullptr;

        if (Pin->LinkedTo.Num() == 1)
        {
            const FEdGraphPinType& ConnectedPinType = Pin->LinkedTo[0]->PinType;

            if(MatchMe(CurrentOperation, ConnectedPinType, selectorPinValue()))
            {
                returnValuePin()->Modify();
                ReturnValuePinType.PinCategory = CurrentOperation.Final.Category;
                ReturnValuePinType.PinSubCategoryObject = CurrentOperation.Final.SubCategoryObject;
//                  Pin->PinFriendlyName = FText::FromName(CurrentOperation.Final.TypeName);

                const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
                K2Schema->ForceVisualizationCacheClear();
                return;
            }
        }
    }
}


void UK2Node_OutWithSelectorOp::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
    Super::ExpandNode(CompilerContext, SourceGraph);

    auto Schema = Cast< UEdGraphSchema_K2 >(GetSchema());

    if (CheckForErrors(CompilerContext))
    {
        BreakAllNodeLinks();
        return;
    }

    FName OperationFunctionName;
    FName ConvFunctionName = "";

    auto returnValue = returnValuePin();
    UEdGraphPin* link = nullptr;

    if (returnValue->LinkedTo.Num() == 1)
    {
        link = returnValue->LinkedTo[0];

        auto pinType = link->PinType;

        bool bFound = MatchMe(CurrentOperation, pinType, selectorPinValue());
        if (bFound)
        {
            link->PinType.PinCategory = CurrentOperation.Final.Category;
            link->PinType.PinSubCategoryObject = CurrentOperation.Final.SubCategoryObject;
        }
        else
        {
            CompilerContext.MessageLog.Error(*LOCTEXT("Error", "Node @@ return value link is not supported.").ToString(), this);
            BreakAllNodeLinks();
            return;
        }

        OperationFunctionName = CurrentOperation.K2NodeName;
        ConvFunctionName = CurrentOperation.Conversion.ConversionName;
    }
    else
    {
        // no output link, let's run the node anyways... and make it a double
        OperationFunctionName = CurrentOperation.K2NodeName;
    }


    auto InternalNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
    InternalNode->FunctionReference.SetExternalMember(OperationFunctionName, USpiceK2::StaticClass());
    InternalNode->AllocateDefaultPins();

    CompilerContext.MessageLog.NotifyIntermediateObjectCreation(InternalNode, this);

    if(link){
        // Wire the return value up first... it may need to go through a type converter
        if (ConvFunctionName != "")
        {
            auto ConversionNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
            ConversionNode->FunctionReference.SetExternalMember(ConvFunctionName, USpiceK2::StaticClass());
            ConversionNode->AllocateDefaultPins();

            CompilerContext.MessageLog.NotifyIntermediateObjectCreation(ConversionNode, this);

            auto internalReturn = InternalNode->GetReturnValuePin();
            auto conversionInput = ConversionNode->FindPinChecked(returnValue_PinName);
            auto conversionReturn = ConversionNode->GetReturnValuePin();
            auto myReturn = returnValuePin();

            // Connect the internal operation's output to the conversion input
            Schema->TryCreateConnection(internalReturn, conversionInput);
            // And move this node's return to the conversion return
            MovePinLinksOrCopyDefaults(CompilerContext, myReturn, conversionReturn);
        }
        else
        {
            auto internalReturn = InternalNode->GetReturnValuePin();
            auto myReturn = returnValuePin();

            MovePinLinksOrCopyDefaults(CompilerContext, myReturn, internalReturn);
        }
    }

    // Exec nodes....
    UEdGraphPin* NodeExec = GetExecPin();
    UEdGraphPin* NodeSuccess = successPin();
    UEdGraphPin* NodeError = errorPin();

    UEdGraphPin* InternalExec = InternalNode->GetExecPin();
    MovePinLinksOrCopyDefaults(CompilerContext, NodeExec, InternalExec);

    UEdGraphPin* InternalSuccess = InternalNode->FindPinChecked(successExec_PinName);
    check(InternalSuccess != nullptr);
    MovePinLinksOrCopyDefaults(CompilerContext, NodeSuccess, InternalSuccess);

    UEdGraphPin* InternalError = InternalNode->FindPinChecked(errorExec_PinName);
    check(InternalError != nullptr);
    MovePinLinksOrCopyDefaults(CompilerContext, NodeError, InternalError);

    UEdGraphPin* InternalNodeErrorMessage = InternalNode->FindPinChecked(errorMessage_PinName);
    MovePinLinksOrCopyDefaults(CompilerContext, errorMessagePin(), InternalNodeErrorMessage);

    ExpandOperationNode(CompilerContext, SourceGraph, InternalNode);

    BreakAllNodeLinks();
}

void UK2Node_OutWithSelectorOp::PreloadRequiredAssets()
{
    PreloadObject(FSDimensionlessVector::StaticStruct());
    PreloadObject(FSMassConstant::StaticStruct());
    PreloadObject(FSDistance::StaticStruct());
    PreloadObject(FSAngle::StaticStruct());
    PreloadObject(FSDistanceVector::StaticStruct());
    PreloadObject(FSVelocityVector::StaticStruct());
    PreloadObject(FK2Type::StaticStruct());
    PreloadObject(FK2Conversion::StaticStruct());
    PreloadObject(FK2SingleOutputOpWithComponentFilter::StaticStruct());
    Super::PreloadRequiredAssets();
}


bool UK2Node_OutWithSelectorOp::CheckForErrors(FKismetCompilerContext& CompilerContext)
{
    bool bError = false;

    if (bError)
    {
        CompilerContext.MessageLog.Error(*LOCTEXT("Error", "Node @@ had an input error.").ToString(), this);
        bError = true;
    }

    return bError;
}


bool UK2Node_OutWithSelectorOp::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const
{
    if (OtherPin)
    {
        if ((MyPin->Direction == EGPD_Output) && (MyPin->GetName() == returnValuePin()->GetName()))
        {
            bool compatible = IsOutputCompatible(OtherPin, selectorPinValue());

            if (!compatible)
            {
                OutReason = TEXT("Pin does not match a supported type");
                return true;
            }
        }
    }

    return Super::IsConnectionDisallowed(MyPin, OtherPin, OutReason);
}

bool UK2Node_OutWithSelectorOp::IsOutputCompatible(const UEdGraphPin* ThePin, EK2_ComponentSelector selector) const
{
    if (ThePin)
    {
        // Loop through our operations and try to find a match
        auto pinType = ThePin->PinType;

        FK2SingleOutputOpWithComponentFilter dummyOperation;
        return MatchMe(dummyOperation, pinType, selector);
    }

    return false;
}

bool UK2Node_OutWithSelectorOp::MatchMe(FK2SingleOutputOpWithComponentFilter& operation, FEdGraphPinType pinType, EK2_ComponentSelector selector) const
{
    for (auto kvp : OperationsMap)
    {
        if (kvp.Value.Final.Is(pinType) && kvp.Value.Selector == selector)
        {
            operation = kvp.Value;
            return true;
        }
    }

    return false;
}


EK2_ComponentSelector UK2Node_OutWithSelectorOp::selectorPinValue() const
{
    static UEnum* ComponentSelectorEnum = FindObjectChecked<UEnum>(ANY_PACKAGE, TEXT("EK2_ComponentSelector"), /*ExactClass*/true);
    EK2_ComponentSelector selector = EK2_ComponentSelector::All;
    if (selectorPin() != nullptr)
    {
        selector = (EK2_ComponentSelector)ComponentSelectorEnum->GetValueByNameString(selectorPin()->DefaultValue);
    }
    return selector;
}


FSlateIcon UK2Node_OutWithSelectorOp::GetIconAndTint(FLinearColor& OutColor) const
{
    OutColor = FColor::Turquoise;
    return FSlateIcon("EditorStyle", "Kismet.AllClasses.FunctionIcon");
}

FLinearColor UK2Node_OutWithSelectorOp::GetNodeTitleColor() const
{
    return NodeBackgroundColor;
}

void UK2Node_OutWithSelectorOp::NotifyConnectionChanged(UEdGraphPin* Pin, UEdGraphPin* Connection)
{
    NotifyPinConnectionListChanged(Pin);
}

#undef LOCTEXT_NAMESPACE