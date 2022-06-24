// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "K2Node_vsub.h"
#include "K2Type.h"
#include "SpiceK2.h"
#include "K2PassThroughOp.h"

#define LOCTEXT_NAMESPACE "K2Node_vsub"

UK2Node_vsub::UK2Node_vsub()
{
    SupportedOperations.Add(FK2PassThroughOp{ "vsub dimensionless vector", USpiceK2::vsub_vector, FK2Type::SDimensionlessVector() });
    SupportedOperations.Add(FK2PassThroughOp{ "vsub distance vector", USpiceK2::vsub_vector, FK2Conversion::SDistanceVectorToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSDistanceVector() });
    SupportedOperations.Add(FK2PassThroughOp{ "vsub velocity vector", USpiceK2::vsub_vector, FK2Conversion::SVelocityVectorToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSVelocityVector() });
    SupportedOperations.Add(FK2PassThroughOp{ "vsub angular velocity", USpiceK2::vsub_vector, FK2Conversion::SAngularVelocityToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSAngularVelocity() });
    SupportedOperations.Add(FK2PassThroughOp{ "vsub dimensionless state vector", USpiceK2::vsub_state_vector, FK2Type::SDimensionlessStateVector() });
    SupportedOperations.Add(FK2PassThroughOp{ "vsub state vector", USpiceK2::vsub_state_vector, FK2Conversion::SStateVectorToSDimensionlessStateVector(), FK2Conversion::SDimensionlessStateVectorToSStateVector() });

    for (const auto& op : SupportedOperations)
    {
        SupportedTypes.Add(op.OuterType);

#if WITH_EDITOR
        // Ensure the specified actions actually exist!
        if (!op.InnerToOuterConversion.ConversionName.IsNone())
        {
            check(USpiceK2::StaticClass()->FindFunctionByName(op.InnerToOuterConversion.ConversionName));
        }
        if (!op.OuterToInnerConversion.ConversionName.IsNone())
        {
            check(USpiceK2::StaticClass()->FindFunctionByName(op.OuterToInnerConversion.ConversionName));
        }
        if (!op.K2NodeName.IsNone())
        {
            check(USpiceK2::StaticClass()->FindFunctionByName(op.K2NodeName));
        }
#endif
    }

    OutputPinName = "Difference";
}

FText UK2Node_vsub::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    constexpr bool bUseShortNameForTitle{ true };

    switch (TitleType)
    {
    case ENodeTitleType::FullTitle:
        return LOCTEXT("ListViewTitle", "vsub (experimental)");
        if (!bUseShortNameForTitle && !OperandType.TypeName.IsNone())
        {
            /** The full title, may be multiple lines. */
            return FText::FromString(FString::Printf(TEXT("vsub %s"), *OperandType.TypeName.ToString()));
        }
        break;
    case ENodeTitleType::MenuTitle:
        /** Menu Title for context menus to be displayed in context menus referencing the node. */
        return LOCTEXT("MenuTitle", "vsub - Subtract two MaxQ vectors (experimental)");
    case ENodeTitleType::ListView:
        /** More concise, single line title. */
        return LOCTEXT("ListViewTitle", "vsub - Subtract two vectors (experimental)");
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

    FText Tooltip = LOCTEXT("Tooltip", "Subtract two MaxQ vector types.\nStill experimental/under testing.\nThe intent is to support limited wildcards in a single action.\n\nSupports");

    FText ListStart = LOCTEXT("ListStart", ":\n");
    FText ListSItemeparator = LOCTEXT("ListSItemeparator", ",\n");
    bool bIsFirstItem = true;
    for (const FK2Type& Type : SupportedTypes)
    {
        Tooltip = Tooltip.Join(bIsFirstItem ? ListStart : ListSItemeparator, Tooltip, Type.GetDisplayNameText());
        bIsFirstItem = false;
    }

    return Tooltip;
}


#undef LOCTEXT_NAMESPACE