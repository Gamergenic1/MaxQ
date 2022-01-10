// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

#include "K2Node_OperationNOutput.h"
#include "K2Utilities.h"
#include "SpiceK2.h"

#include "EdGraphSchema_K2.h"

#include "KismetCompiler.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Node_CallFunction.h"

using namespace ENodeTitleType;

#define LOCTEXT_NAMESPACE "OperationNOutput_bodvrd"


UK2Node_OperationNOutput::UK2Node_OperationNOutput()
{
}


bool UK2Node_OperationNOutput::IsNodeSafeToIgnore() const {
    return true;
}

void UK2Node_OperationNOutput::AllocateDefaultPins()
{
    Super::AllocateDefaultPins();

    const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

    // Exec pins - In
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);

    // Exec out w/return values
    // Success - Exec
    UEdGraphPin* successPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, success_Field);
    successPin->PinToolTip = TEXT("Exit, if the action succeeds");

    // Success - return
    UEdGraphPin* OutputPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, value_Field);
    OutputPin->PinToolTip = "Return Value (Wildcard), if successful";

    // Error - Exec
    UEdGraphPin* errorPin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, error_Field);
    errorPin->PinToolTip = TEXT("Exit, if the action fails");

    // Error - return
    UEdGraphPin* errorMessagePin = CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_String, errorMessage_Field);
    errorMessagePin->PinToolTip = TEXT("An error message, if the action fails");
}

void UK2Node_OperationNOutput::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
    Super::NotifyPinConnectionListChanged(Pin);

    if (Pin == returnValuePin())
    {
//        Pin->PinFriendlyName = FText::GetEmpty();

        FEdGraphPinType& ReturnValuePinType = Pin->PinType;

        ReturnValuePinType.PinCategory = UEdGraphSchema_K2::PC_Wildcard;
        ReturnValuePinType.PinSubCategory = NAME_None;
        ReturnValuePinType.PinSubCategoryObject = nullptr;

        if (Pin->LinkedTo.Num() == 1)
        {
            const FEdGraphPinType& ConnectedPinType = Pin->LinkedTo[0]->PinType;

            for (auto kvp : OperationsMap)
            {
                if (kvp.Value.Final.Matches(ConnectedPinType))
                {
                    CurrentOperation = kvp.Value;

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
}


void UK2Node_OperationNOutput::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
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

        bool found = true;
        for (auto kvp : OperationsMap)
        {
            if (kvp.Value.Final.Matches(pinType))
            {
                CurrentOperation = kvp.Value;
                link->PinType.PinCategory = CurrentOperation.Final.Category;
                link->PinType.PinSubCategoryObject = CurrentOperation.Final.SubCategoryObject;
            }
        }

        if (!found)
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
        OperationFunctionName = GET_FUNCTION_NAME_CHECKED(USpiceK2, bodvrd_double_K2);
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
            auto conversionInput = ConversionNode->FindPinChecked(value_Field);
            auto conversionReturn = ConversionNode->GetReturnValuePin();
            auto myReturn = returnValuePin();

            // Connect the interal operation's output to the conversion input
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

    UEdGraphPin* InternalSuccess = InternalNode->FindPinChecked(success_Field);
    check(InternalSuccess != nullptr);
    MovePinLinksOrCopyDefaults(CompilerContext, NodeSuccess, InternalSuccess);

    UEdGraphPin* InternalError = InternalNode->FindPinChecked(error_Field);
    check(InternalError != nullptr);
    MovePinLinksOrCopyDefaults(CompilerContext, NodeError, InternalError);

    UEdGraphPin* InternalNodeErrorMessage = InternalNode->FindPinChecked(errorMessage_Field);
    MovePinLinksOrCopyDefaults(CompilerContext, errorMessagePin(), InternalNodeErrorMessage);

    ExpandOperationNode(CompilerContext, SourceGraph, InternalNode);

    BreakAllNodeLinks();
}

void UK2Node_OperationNOutput::PreloadRequiredAssets()
{
    PreloadObject(FSDimensionlessVector::StaticStruct());
    PreloadObject(FSMassConstant::StaticStruct());
    PreloadObject(FSDistance::StaticStruct());
    PreloadObject(FSAngle::StaticStruct());
    PreloadObject(FSDistanceVector::StaticStruct());
    PreloadObject(FSVelocityVector::StaticStruct());
    PreloadObject(FK2Type::StaticStruct());
    PreloadObject(FK2Conversion::StaticStruct());
    PreloadObject(FK2OperationNOutput::StaticStruct());
    Super::PreloadRequiredAssets();
}


bool UK2Node_OperationNOutput::CheckForErrors(FKismetCompilerContext& CompilerContext)
{
    bool bError = false;

    if (false)
    {
        CompilerContext.MessageLog.Error(*LOCTEXT("Error", "Node @@ had an input error.").ToString(), this);
        bError = true;
    }

    return bError;
}


bool UK2Node_OperationNOutput::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const
{
    if (OtherPin)
    {
        if ((MyPin->Direction == EGPD_Output) && (MyPin->GetName() == returnValuePin()->GetName()))
        {
            bool compatible = IsOutputCompatible(OtherPin);

            if (!compatible)
            {
                OutReason = LOCTEXT("TypeDisallowed", "Pin does not match a supported type").ToString();
                return true;
            }
        }
    }

    return Super::IsConnectionDisallowed(MyPin, OtherPin, OutReason);
}

bool UK2Node_OperationNOutput::IsOutputCompatible(const UEdGraphPin* ThePin) const
{
    if (ThePin)
    {
        // Loop through our operations and try to find a match
        auto pinType = ThePin->PinType;

        for (auto kvp : OperationsMap)
        {
            if (kvp.Value.Final.Matches(pinType))
                return true;
        }
    }

    return false;
}

UEdGraphPin* UK2Node_OperationNOutput::getReturnValuePin(UK2Node_CallFunction* other) const
{
    return other->GetReturnValuePin();
}

#undef LOCTEXT_NAMESPACE