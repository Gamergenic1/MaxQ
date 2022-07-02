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

#pragma once

#include "EdGraphSchema_K2.h"

#include "KismetCompiler.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Type.h"

constexpr FLinearColor NodeBackgroundColor{ 0.1f, 0.82f, 0.2f };
void RegisterAction(class FBlueprintActionDatabaseRegistrar& ActionRegistrar, UClass* actionKey);
void MovePinLinksOrCopyDefaults(FKismetCompilerContext& CompilerContext, UEdGraphPin* Source, UEdGraphPin* Dest);\
UEdGraphPin* GetReturnValuePin(UEdGraphNode* Node);
bool SetPinType(UEdGraphNode* Node, UEdGraphPin* Pin, const FK2Type& K2Type);
bool SetPinTypeToWildcard(UEdGraphNode* Node, UEdGraphPin* Pin);
bool SetPinType(UEdGraphNode* Node, UEdGraphPin* Pin, const FK2Type& K2Type, const FString& ToolTip);
bool SetPinTypeToWildcard(UEdGraphNode* Node, UEdGraphPin* Pin, const FString& ToolTip);
void ThisPinTypeChanged(UEdGraphPin* Pin);

// We don't care about const, etc
static inline bool IsExactPair(const FEdGraphPinType& lhs, const FEdGraphPinType& rhs)
{
    if(lhs.ContainerType != rhs.ContainerType) return false;
    if(lhs.PinCategory != rhs.PinCategory) return false;

    if (lhs.PinCategory == UEdGraphSchema_K2::PC_Struct)
    {
        return lhs.PinSubCategory == rhs.PinSubCategory;
    }
    return true;
}

static inline bool IsExactPair(const UEdGraphPin* lhs, const UEdGraphPin* rhs)
{
    if(!lhs || !rhs) return false;
    return IsExactPair(lhs->PinType, rhs->PinType) && (lhs->Direction != rhs->Direction);
}

