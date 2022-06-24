// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "K2Utilities.h"
#include "BlueprintActionDatabaseRegistrar.h"

void RegisterAction(class FBlueprintActionDatabaseRegistrar& ActionRegistrar, UClass* actionKey)
{
    if (ActionRegistrar.IsOpenForRegistration(actionKey))
    {
        UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(actionKey);
        check(NodeSpawner != nullptr);

        ActionRegistrar.AddBlueprintAction(actionKey, NodeSpawner);
    }
}


void MovePinLinksOrCopyDefaults(FKismetCompilerContext& CompilerContext, UEdGraphPin* Source, UEdGraphPin* Dest)
{
    if (Source->LinkedTo.Num() > 0)
    {
        CompilerContext.MovePinLinksToIntermediate(*Source, *Dest);
    }
    else
    {
        Dest->DefaultObject = Source->DefaultObject;
        Dest->DefaultValue = Source->DefaultValue;
        Dest->DefaultTextValue = Source->DefaultTextValue;
    }
}


UEdGraphPin* GetReturnValuePin(UEdGraphNode* Node)
{
    UEdGraphPin* Pin = Node->FindPin(UEdGraphSchema_K2::PN_ReturnValue);
    check(Pin == nullptr || Pin->Direction == EGPD_Output); // If pin exists, it must be output
    return Pin;
}