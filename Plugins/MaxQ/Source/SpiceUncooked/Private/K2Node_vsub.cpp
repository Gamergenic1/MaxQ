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


#include "K2Node_vsub.h"
#include "K2Type.h"
#include "SpiceK2.h"
#include "K2PassThroughOp.h"

#define LOCTEXT_NAMESPACE "K2Node_vsub"

UK2Node_vsub::UK2Node_vsub()
{
    OutputPinName = "Difference";
}

FText UK2Node_vsub::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    // constexpr bool bUseShortNameForTitle{ true };

    switch (TitleType)
    {
    case ENodeTitleType::FullTitle:
        return LOCTEXT("ListViewTitle", "vsub");
        // if (!bUseShortNameForTitle && !OperandType.TypeName.IsNone())
        // {
        //     /** The full title, may be multiple lines. */
        //     return FText::FromString(FString::Printf(TEXT("vsub %s"), *OperandType.TypeName.ToString()));
        // }
        // break;
    case ENodeTitleType::MenuTitle:
        /** Menu Title for context menus to be displayed in context menus referencing the node. */
        return LOCTEXT("MenuTitle", "vsub - Subtract two MaxQ vectors");
    case ENodeTitleType::ListView:
        /** More concise, single line title. */
        return LOCTEXT("ListViewTitle", "vsub - Subtract two vectors");
    }

    return LOCTEXT("ShortTitle", "vsub");
}


FText UK2Node_vsub::GetMenuCategory() const
{
    return LOCTEXT("Category", "MaxQ|Math|Vector");
}


FText UK2Node_vsub::GetKeywords() const
{
    return LOCTEXT("Keywords", "VECTOR");
}


FText UK2Node_vsub::GetTooltipText() const
{

    FText Tooltip = LOCTEXT("Tooltip", "Subtract two MaxQ vector types.  Support limited wildcards in a single action.");

    FText ListStart = LOCTEXT("ListStart", ":\n");
    FText ListSItemeparator = LOCTEXT("ListSItemeparator", ",\n");
    bool bIsFirstItem = true;
    for (const FK2Type& Type : GetSupportedTypes())
    {
        Tooltip = Tooltip.Join(bIsFirstItem ? ListStart : ListSItemeparator, Tooltip, Type.GetDisplayNameText());
        bIsFirstItem = false;
    }

    return Tooltip;
}


#undef LOCTEXT_NAMESPACE


const TArray<FK2Type>& UK2Node_vsub::GetSupportedTypes() const
{
    static const TArray<FK2Type> SupportedTypes
    {
        OperationType::GetTypesFromOperations(GetSupportedOperations())
    };

    return SupportedTypes;
}

const TArray<UK2Node_vsub::OperationType>& UK2Node_vsub::GetSupportedOperations() const
{
    static const TArray<OperationType> SupportedOperations
    {
        OperationType{ "vsub dimensionless vector", USpiceK2::vsub_vector, FK2Type::SDimensionlessVector() },
        OperationType{ "vsub distance vector", USpiceK2::vsub_vector, FK2Conversion::SDistanceVectorToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSDistanceVector() },
        OperationType{ "vsub velocity vector", USpiceK2::vsub_vector, FK2Conversion::SVelocityVectorToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSVelocityVector() },
        OperationType{ "vsub angular velocity", USpiceK2::vsub_vector, FK2Conversion::SAngularVelocityToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSAngularVelocity() },
        OperationType{ "vsub dimensionless state vector", USpiceK2::vsub_state_vector, FK2Type::SDimensionlessStateVector() },
        OperationType{ "vsub state vector", USpiceK2::vsub_state_vector, FK2Conversion::SStateVectorToSDimensionlessStateVector(), FK2Conversion::SDimensionlessStateVectorToSStateVector() }
    };

    return SupportedOperations;
}
