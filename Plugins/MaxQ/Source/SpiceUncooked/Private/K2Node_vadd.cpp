// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "K2Node_vadd.h"
#include "K2Type.h"
#include "SpiceK2.h"
#include "K2PassThroughOp.h"

#define LOCTEXT_NAMESPACE "K2Node_vadd"

UK2Node_vadd::UK2Node_vadd()
{
    SupportedOperations.Add(FK2PassThroughOp{ "vadd dimensionless vector", USpiceK2::vadd_vector, FK2Type::SDimensionlessVector() });
    SupportedOperations.Add(FK2PassThroughOp{ "vadd distance vector", USpiceK2::vadd_vector, FK2Conversion::SDistanceVectorToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSDistanceVector() });
    SupportedOperations.Add(FK2PassThroughOp {"vadd velocity vector", USpiceK2::vadd_vector, FK2Conversion::SVelocityVectorToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSVelocityVector() } );
    SupportedOperations.Add(FK2PassThroughOp {"vadd angular velocity", USpiceK2::vadd_vector, FK2Conversion::SAngularVelocityToSDimensionlessVector(), FK2Conversion::SDimensionlessVectorToSAngularVelocity() } );
    SupportedOperations.Add(FK2PassThroughOp { "vadd dimensionless state vector", USpiceK2::vadd_state_vector, FK2Type::SDimensionlessStateVector() });
    SupportedOperations.Add(FK2PassThroughOp { "vadd state vector", USpiceK2::vadd_state_vector, FK2Conversion::SStateVectorToSDimensionlessStateVector(), FK2Conversion::SDimensionlessStateVectorToSStateVector() });

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

    OutputPinName = "Sum";
}

FText UK2Node_vadd::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    constexpr bool bUseShortNameForTitle{ true };

    switch (TitleType)
    {
    case ENodeTitleType::FullTitle:
        /** The full title, may be multiple lines. */
        return LOCTEXT("ListViewTitle", "vadd");
        if (!bUseShortNameForTitle && !OperandType.TypeName.IsNone())
        {
            return FText::FromString(FString::Printf(TEXT("vadd %s"), *OperandType.TypeName.ToString()));
        }
        break;
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
    for (const FK2Type& Type : SupportedTypes)
    {
        Tooltip = Tooltip.Join(bIsFirstItem ? ListStart : ListSItemeparator, Tooltip, Type.GetDisplayNameText());
        bIsFirstItem = false;
    }

    return Tooltip;
}


#undef LOCTEXT_NAMESPACE