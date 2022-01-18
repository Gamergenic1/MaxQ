// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

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