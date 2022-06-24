// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "K2Node_gdpool.h"
#include "K2Node_OutWithSelectorOp.h"
#include "K2Utilities.h"
#include "SpiceK2.h"

#include "EdGraphSchema_K2.h"

#include "KismetCompiler.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Node_CallFunction.h"


using namespace ENodeTitleType;


#define LOCTEXT_NAMESPACE "K2Node_gdpool"


UK2Node_gdpool::UK2Node_gdpool()
{
    OperationsMap = TMap<FName, FK2SingleOutputOpWithComponentFilter>();

    auto op = DoubleOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = RealOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = ArrayDoubleOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = ArrayRealOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SDimensionlessVectorOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SMassConstantOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SDistanceOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SDegreesOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SDistanceVectorOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SVelocityVectorOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SDistanceX(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SDistanceY(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = SDistanceZ(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);
    op = WildcardOp(); op.FullName = op.ShortName.ToString() + "\nReturn value from the kernel pool"; OperationsMap.Emplace(op.ShortName, op);

    CurrentOperation = op;

#if WITH_EDITOR
    // Ensure the specified actions actually exist!
    for (const auto& [shortname, _op] : OperationsMap)
    {
        if (!_op.K2NodeName.IsNone())
        {
            check(USpiceK2::StaticClass()->FindFunctionByName(_op.K2NodeName));
        }
        if (!_op.Conversion.ConversionName.IsNone())
        {
            check(USpiceK2::StaticClass()->FindFunctionByName(_op.Conversion.ConversionName));
        }
    }
#endif
}


FText UK2Node_gdpool::GetNodeTitle(Type TitleType) const
{
    switch (TitleType)
    {
    case FullTitle:
        /** The full title, may be multiple lines. */
        return FText::FromString(CurrentOperation.FullName);
    case ListView:
        /** More concise, single line title. */
        return LOCTEXT("ListViewTitle", "gdpool - fetch value from kernel pool");
    case MenuTitle:
        /** Menu Title for context menus to be displayed in context menus referencing the node. */
        return LOCTEXT("MenuTitle", "gdpool");
    }

    return LOCTEXT("ShortTitle", "gdpool");
}


FText UK2Node_gdpool::GetMenuCategory() const
{
    return LOCTEXT("Category", "MaxQ|Kernel");
}


FText UK2Node_gdpool::GetKeywords() const
{
    return LOCTEXT("Keywords", "CONSTANTS, FILES");
}


FText UK2Node_gdpool::GetTooltipText() const
{
    return LOCTEXT("Tooltip", "Fetch from the kernel pool the double precision values of an item associated with a body");
}



void UK2Node_gdpool::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    RegisterAction(ActionRegistrar, GetClass());
}

void UK2Node_gdpool::NotifyPinConnectionListChanged(UEdGraphPin* Pin)
{
    Super::NotifyPinConnectionListChanged(Pin);

    if (Pin->LinkedTo.Num() != 1)
    {
        CurrentOperation = WildcardOp();
        const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
        K2Schema->ForceVisualizationCacheClear();
    }
    startPin()->SafeSetHidden(CurrentOperation.Final.Container != EPinContainerType::Array);
}



void UK2Node_gdpool::AllocateDefaultPins()
{
    Super::AllocateDefaultPins();

    const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

    // Inputs - Body/Item
    UEdGraphPin * item = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_String, item_Field);
    K2Schema->SetPinAutogeneratedDefaultValue(item, item_Value);
    item->PinToolTip = TEXT("Item for which values are desired. (\"RADII\", \"NUT_PREC_ANGLES\", etc.)");

    UEdGraphPin* start = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Int, start_Field);
    K2Schema->SetPinAutogeneratedDefaultValue(start, start_Value);
    start->PinToolTip = TEXT("First array index to fetch");
    start->DefaultValue = FString::FromInt(start_DefaultValue);
    start->SafeSetHidden(CurrentOperation.Final.Container != EPinContainerType::Array);

    successPin()->PinFriendlyName = LOCTEXT("SuccessPinName", "Found");
    errorPin()->PinFriendlyName = LOCTEXT("ErrorPinName", "Not Found");
    successPin()->PinToolTip = TEXT("Executes if variable is in pool");
    errorPin()->PinToolTip = TEXT("Executes if variable is in not pool");
    errorMessagePin()->SafeSetHidden(true);
}


void UK2Node_gdpool::ReconstructNode()
{
    Super::ReconstructNode();

    if (returnValuePin()->LinkedTo.Num() != 1)
    {
        CurrentOperation = WildcardOp();
    }
}

void UK2Node_gdpool::ExpandOperationNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UK2Node* operationNode)
{
    auto Schema = Cast< UEdGraphSchema_K2 >(GetSchema());

    // Now the body and item pins...
    auto thisItem = itemPin();   auto thatItem = operationNode->FindPinChecked(item_Field);

    MovePinLinksOrCopyDefaults(CompilerContext, thisItem, thatItem);

    auto thatStartPin = FindPin(start_Field);
    if (thatStartPin != nullptr)
    {
        MovePinLinksOrCopyDefaults(CompilerContext, startPin(), thatStartPin);
    }
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_gdpool::WildcardOp()
{
    static auto v {FK2SingleOutputOpWithComponentFilter(FName("gdpool"), USpiceK2::gdpool_double, FK2Type::Wildcard())};
    v.FullName = v.ShortName.ToString() + "\nReturn value from the kernel pool";
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_gdpool::DoubleOp()
{
    static auto v {FK2SingleOutputOpWithComponentFilter(FName("gdpool Double"), USpiceK2::gdpool_double, FK2Type::Double())};
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_gdpool::RealOp()
{
    static auto v {FK2SingleOutputOpWithComponentFilter(FName("gdpool Real"), USpiceK2::gdpool_double, FK2Type::Real())};
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_gdpool::ArrayDoubleOp()
{
    static auto v {FK2SingleOutputOpWithComponentFilter(FName("gdpool Array(Double)"), USpiceK2::gdpool_array, FK2Type::DoubleArray())};
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_gdpool::ArrayRealOp()
{
    static auto v {FK2SingleOutputOpWithComponentFilter(FName("gdpool Array(Real)"), USpiceK2::gdpool_array, FK2Type::RealArray())};
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_gdpool::SDimensionlessVectorOp()
{
    static auto v {FK2SingleOutputOpWithComponentFilter(FName("gdpool SDimensionlessVector"), USpiceK2::gdpool_vector, FK2Type::SDimensionlessVector())};
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_gdpool::SMassConstantOp()
{
    static auto v {FK2SingleOutputOpWithComponentFilter(FName("gdpool SMassConstant"), USpiceK2::gdpool_double, FK2Conversion::DoubleToSMassConstant())};
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_gdpool::SDistanceOp()
{
    static auto v {FK2SingleOutputOpWithComponentFilter(FName("gdpool SDistance"), USpiceK2::gdpool_double, FK2Conversion::DoubleToSDistance())};
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_gdpool::SDegreesOp()
{
    static auto v {FK2SingleOutputOpWithComponentFilter(FName("gdpool SAngle(Degrees)"), USpiceK2::gdpool_double, FK2Conversion::DegreesToSAngle())};
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_gdpool::SDistanceVectorOp()
{

    static auto v {FK2SingleOutputOpWithComponentFilter(FName("gdpool SDistanceVector"), USpiceK2::gdpool_vector, FK2Conversion::SDimensionlessVectorToSDistanceVector())};
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_gdpool::SVelocityVectorOp()
{
    static auto v {FK2SingleOutputOpWithComponentFilter(FName("gdpool SVelocityVector"), USpiceK2::gdpool_vector, FK2Conversion::SDimensionlessVectorToSVelocityVector())};
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_gdpool::SDistanceX()
{
    static auto v {FK2SingleOutputOpWithComponentFilter(FName("gdpool SDistanceVector.X"), USpiceK2::gdpool_vector, FK2Conversion::SDimensionlessVectorXToSDistance())};
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_gdpool::SDistanceY()
{
    static auto v {FK2SingleOutputOpWithComponentFilter(FName("gdpool SDistanceVector.Y"), USpiceK2::gdpool_vector, FK2Conversion::SDimensionlessVectorYToSDistance())};
    return v;
}

SPICEUNCOOKED_API const FK2SingleOutputOpWithComponentFilter& UK2Node_gdpool::SDistanceZ()
{
    static auto v {FK2SingleOutputOpWithComponentFilter(FName("gdpool SDistanceVector.Z"), USpiceK2::gdpool_vector, FK2Conversion::SDimensionlessVectorZToSDistance())};
    return v;
}




#undef LOCTEXT_NAMESPACE