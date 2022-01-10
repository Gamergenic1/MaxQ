// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

#pragma once

#include "EdGraphSchema_K2.h"

#include "KismetCompiler.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"

void RegisterAction(class FBlueprintActionDatabaseRegistrar& ActionRegistrar, UClass* actionKey);
void MovePinLinksOrCopyDefaults(FKismetCompilerContext& CompilerContext, UEdGraphPin* Source, UEdGraphPin* Dest);



