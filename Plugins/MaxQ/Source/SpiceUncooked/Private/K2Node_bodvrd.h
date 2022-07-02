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

#include "CoreMinimal.h"
#include "K2Node.h"
#include "SpiceTypes.h"
#include "K2Type.h"
#include "K2Conversion.h"
#include "K2SingleOutputOpWithComponentFilter.h"
#include "K2Node_OutWithSelectorOp.h"
#include "K2Node_bodvrd.generated.h"

#pragma once

UCLASS(BlueprintType, Blueprintable)
class SPICEUNCOOKED_API UK2Node_bodvrd : public UK2Node_OutWithSelectorOp
{
    GENERATED_BODY()

public:
    UK2Node_bodvrd();

    void AllocateDefaultPins();
    void NotifyPinConnectionListChanged(UEdGraphPin* Pin);
    FText GetNodeTitle(ENodeTitleType::Type TitleType) const;
    FText GetMenuCategory() const;
    FText GetKeywords() const;
    FText GetTooltipText() const;
    void ReconstructNode();
    void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const;

protected:
    void ExpandOperationNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UK2Node* operationNode);

private:
    const FName bodynm_Field = FName("bodynm");
    const FName item_Field = FName("item");

    const FString bodynm_DefaultValue = TEXT("EARTH");
    const FString item_DefaultValue = TEXT("RADII");

    UEdGraphPin* bodynmPin() const { return FindPinChecked(bodynm_Field); }
    UEdGraphPin* itemPin() const { return FindPinChecked(item_Field); }

private:
    static const OperationType& WildcardOp();

protected:
    virtual const TMap<FName, OperationType>& GetOperationsMap() const override;
    virtual const OperationType& GetWildcardOp() const { return WildcardOp(); }
};


