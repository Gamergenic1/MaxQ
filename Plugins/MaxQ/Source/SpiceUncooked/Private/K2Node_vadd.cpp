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


#include "K2Node_vadd.h"
#include "K2Type.h"
#include "SpiceK2.h"
#include "K2PassThroughOp.h"

#define LOCTEXT_NAMESPACE "K2Node_vadd"

UK2Node_vadd::UK2Node_vadd()
{
    OutputPinName = "Sum";
}

FText UK2Node_vadd::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    constexpr bool bUseShortNameForTitle{ false };

    switch (TitleType)
    {
    case ENodeTitleType::FullTitle:
        /** The full title, may be multiple lines. */
        return LOCTEXT("ListViewTitle", "vadd");
    case ENodeTitleType::MenuTitle:
        /** Menu Title for context menus to be displayed in context menus referencing the node. */
        return LOCTEXT("MenuTitle", "vadd - Add MaxQ vectors");
    case ENodeTitleType::ListView:
        /** More concise, single line title. */
        return LOCTEXT("ListViewTitle", "vadd - Add vectors");
    }

    return LOCTEXT("ShortTitle", "vadd");
}


FText UK2Node_vadd::GetMenuCategory() const
{
    return LOCTEXT("Category", "MaxQ|Math|Vector");
}


FText UK2Node_vadd::GetKeywords() const
{
    return LOCTEXT("Keywords", "VECTOR");
}


FText UK2Node_vadd::GetTooltipText() const
{
    FText Tooltip = LOCTEXT("Tooltip", "Add two (or more) MaxQ vector types.  Support limited wildcards in a single action.");

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


const TArray<FK2Type>& UK2Node_vadd::GetSupportedTypes() const
{
    static const TArray<FK2Type> SupportedTypes
    {
        OperationType::GetTypesFromOperations(GetSupportedOperations())
    };

    return SupportedTypes;
}

const TArray<UK2Node_vadd::OperationType>& UK2Node_vadd::GetSupportedOperations() const
{
    static const TArray<OperationType> SupportedOperations
    {
        OperationType{ "vadd dimensionless vector", USpiceK2::vadd_vector, FK2Type::SDimensionlessVector() },
        OperationType{ "vadd distance vector", USpiceK2::vadd_vector, FK2Conversion::SDistanceVectorToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSDistanceVector() },
        OperationType {"vadd velocity vector", USpiceK2::vadd_vector, FK2Conversion::SVelocityVectorToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSVelocityVector() },
        OperationType {"vadd angular velocity", USpiceK2::vadd_vector, FK2Conversion::SAngularVelocityToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSAngularVelocity() },
        OperationType { "vadd dimensionless state vector", USpiceK2::vadd_state_vector, FK2Type::SDimensionlessStateVector() },
        OperationType { "vadd state vector", USpiceK2::vadd_state_vector, FK2Conversion::SStateVectorToSDimensionlessStateVector(), FK2Conversion::SDimensionlessStateVectorToSStateVector() }
    };

    return SupportedOperations;
}


#undef LOCTEXT_NAMESPACE