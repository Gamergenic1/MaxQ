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


#include "K2Node_NInOneOut.h"
#include "K2Node_TwoInOneOut.h"
#include "K2Utilities.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "ToolMenu.h"
#include "K2Node_CallFunction.h"
#include "SpiceK2.h"
//#include "EdGraphSchema_K2.h"
//#include "KismetCompiler.h"


#define LOCTEXT_NAMESPACE "K2Node_NInOneOut"


UK2Node_NInOneOut::UK2Node_NInOneOut(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

bool UK2Node_NInOneOut::CanAddPin() const
{
    return true;
}

void UK2Node_NInOneOut::AddInputPin(void)
{
    Modify();
    CreateInputPin();

    // Refresh the current graph, so the pins can be updated
    GetGraph()->NotifyGraphChanged();
}

void UK2Node_NInOneOut::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
    Super::GetNodeContextMenuActions(Menu, Context);

    if (!Context->bIsDebugging)
    {
        static FName CommutativeAssociativeBinaryOperatorNodeName = FName("CommutativeAssociativeBinaryOperatorNode");
        FText CommutativeAssociativeBinaryOperatorStr = LOCTEXT("CommutativeAssociativeBinaryOperatorNode", "Operator Node");
        if (Context->Pin != NULL)
        {
            if (CanRemovePin(Context->Pin))
            {
                FToolMenuSection& Section = Menu->AddSection(CommutativeAssociativeBinaryOperatorNodeName, CommutativeAssociativeBinaryOperatorStr);
                Section.AddMenuEntry(
                    "RemovePin",
                    LOCTEXT("RemovePin", "Remove pin"),
                    LOCTEXT("RemovePinTooltip", "Remove this input pin"),
                    FSlateIcon(),
                    FUIAction(
                        FExecuteAction::CreateUObject(const_cast<UK2Node_NInOneOut*>(this), &UK2Node_NInOneOut::RemoveInputPin, const_cast<UEdGraphPin*>(Context->Pin))
                    )
                );
            }
        }
        else if (CanAddPin())
        {
            FToolMenuSection& Section = Menu->AddSection(CommutativeAssociativeBinaryOperatorNodeName, CommutativeAssociativeBinaryOperatorStr);
            Section.AddMenuEntry(
                "AddPin",
                LOCTEXT("AddPin", "Add pin"),
                LOCTEXT("AddPinTooltip", "Add another input pin"),
                FSlateIcon(),
                FUIAction(
                    FExecuteAction::CreateUObject(const_cast<UK2Node_NInOneOut*>(this), &UK2Node_NInOneOut::AddInputPin)
                )
            );
        }
    }
}



bool UK2Node_NInOneOut::CanRemovePin(const UEdGraphPin* Pin) const
{
    return Pin->Direction == EGPD_Input && Pins.Num() > 3 && !Pin->HasAnyConnections();
}

void UK2Node_NInOneOut::RemoveInputPin(UEdGraphPin* Pin)
{
    if (CanRemovePin(Pin))
    {
        Modify();

        Pin->Modify();
        Pin->MarkAsGarbage();
        Pins.Remove(Pin);
        PinNames.Remove(Pin->PinName);

        // Refresh the current graph, so the pins can be updated
        GetGraph()->NotifyGraphChanged();
        FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(GetBlueprint());
    }
}

#undef LOCTEXT_NAMESPACE