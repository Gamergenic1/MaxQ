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


#include "K2Utilities.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "K2Node_MathGenericInterface.h"

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

bool SetPinType(UEdGraphNode* Node, UEdGraphPin* Pin, FName Category, TWeakObjectPtr<UScriptStruct> SubCategoryObject, EPinContainerType Container)
{
    bool bUpdatePin = Pin->PinType.PinCategory != Category;
    bUpdatePin |= Pin->PinType.PinSubCategoryObject != SubCategoryObject;
    bUpdatePin |= Pin->PinType.ContainerType != Container;

    if (bUpdatePin)
    {
        Node->Modify();
        Pin->Modify();
        Pin->PinType.PinCategory = Category;
        Pin->PinType.PinSubCategoryObject = SubCategoryObject;
        Pin->PinType.ContainerType = Container;

        Node->PinTypeChanged(Pin);
    }

    return bUpdatePin;
}


bool SetPinType(UEdGraphNode* Node, UEdGraphPin* Pin, const FK2Type& K2Type)
{
    return SetPinType(Node, Pin, K2Type.Category, K2Type.SubCategoryObject, K2Type.Container);
}

bool SetPinTypeToWildcard(UEdGraphNode* Node, UEdGraphPin* Pin)
{
    return SetPinType(Node, Pin, UEdGraphSchema_K2::PC_Wildcard, nullptr, EPinContainerType::None);
}

bool SetPinType(UEdGraphNode* Node, UEdGraphPin* Pin, FName Category, TWeakObjectPtr<UScriptStruct> SubCategoryObject, EPinContainerType Container, const FString& ToolTip)
{
    bool bUpdatePin = SetPinType(Node, Pin, Category, SubCategoryObject, Container);
    if (bUpdatePin)
    {
        Pin->PinToolTip = ToolTip;
    }

    return bUpdatePin;
}

bool SetPinType(UEdGraphNode* Node, UEdGraphPin* Pin, const FK2Type& K2Type, const FString& ToolTip)
{
    return SetPinType(Node, Pin, K2Type.Category, K2Type.SubCategoryObject, K2Type.Container, FString::Printf(TEXT("%s (%s)"), *ToolTip, *K2Type.TypeName.ToString()));
}

bool SetPinTypeToWildcard(UEdGraphNode* Node, UEdGraphPin* Pin, const FString& ToolTip)
{
    return SetPinType(Node, Pin, UEdGraphSchema_K2::PC_Wildcard, nullptr, EPinContainerType::None, ToolTip);
}


void ThisPinTypeChanged(UEdGraphPin* Pin)
{
    // Notify any connections that this pin changed... which gives them the
    // opportunity to adapt, themselves...
    for (auto Connection : Pin->LinkedTo)
    {
        if (auto MathGeneric = Cast<IK2Node_MathGenericInterface>(Connection->GetOwningNode()))
        {
            MathGeneric->NotifyConnectionChanged(Connection, Pin);
        }
    }

    const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
    K2Schema->ForceVisualizationCacheClear();
}