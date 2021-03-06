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
    CurrentOperation = WildcardOp();
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
    UEdGraphPin* item = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_String, item_Field);
    K2Schema->SetPinAutogeneratedDefaultValue(item, item_DefaultValue);
    item->PinToolTip = TEXT("Item for which values are desired. (\"BODY399_RADII\", \"BODY399_NUT_PREC_ANGLES\", etc.)");

    UEdGraphPin* start = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Int, start_Field);
    K2Schema->SetPinAutogeneratedDefaultValue(start, FString::FromInt(start_DefaultValue));
    start->PinToolTip = TEXT("First array index to fetch");
    start->SafeSetHidden(CurrentOperation.Final.Container != EPinContainerType::Array);

#if WITH_EDITORONLY_DATA
    successPin()->PinFriendlyName = LOCTEXT("SuccessPinName", "Found");
    errorPin()->PinFriendlyName = LOCTEXT("ErrorPinName", "Not Found");
#endif

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

const UK2Node_gdpool::OperationType& UK2Node_gdpool::WildcardOp()
{
    static auto v{ OperationType(FName("gdpool"), USpiceK2::gdpool_double, FK2Type::Wildcard()) };
    v.FullName = v.ShortName.ToString() + "\nReturn value from the kernel pool";
    return v;
}

namespace gdpool
{
    static const UK2Node_gdpool::OperationType& DoubleOp()
    {
        static auto v{ UK2Node_gdpool::OperationType(FName("gdpool Double"), USpiceK2::gdpool_double, FK2Type::Double()) };
        return v;
    }

    static const UK2Node_gdpool::OperationType& RealOp()
    {
        static auto v{ UK2Node_gdpool::OperationType(FName("gdpool Real"), USpiceK2::gdpool_double, FK2Type::Real()) };
        return v;
    }

    static const UK2Node_gdpool::OperationType& ArrayDoubleOp()
    {
        static auto v{ UK2Node_gdpool::OperationType(FName("gdpool Array(Double)"), USpiceK2::gdpool_array, FK2Type::DoubleArray()) };
        return v;
    }

    static const UK2Node_gdpool::OperationType& ArrayRealOp()
    {
        static auto v{ UK2Node_gdpool::OperationType(FName("gdpool Array(Real)"), USpiceK2::gdpool_array, FK2Type::RealArray()) };
        return v;
    }

    static const UK2Node_gdpool::OperationType& SDimensionlessVectorOp()
    {
        static auto v{ UK2Node_gdpool::OperationType(FName("gdpool SDimensionlessVector"), USpiceK2::gdpool_vector, FK2Type::SDimensionlessVector()) };
        return v;
    }

    static const UK2Node_gdpool::OperationType& SMassConstantOp()
    {
        static auto v{ UK2Node_gdpool::OperationType(FName("gdpool SMassConstant"), USpiceK2::gdpool_double, FK2Conversion::DoubleToSMassConstant()) };
        return v;
    }

    static const UK2Node_gdpool::OperationType& SDistanceOp()
    {
        static auto v{ UK2Node_gdpool::OperationType(FName("gdpool SDistance"), USpiceK2::gdpool_double, FK2Conversion::DoubleToSDistance()) };
        return v;
    }

    static const UK2Node_gdpool::OperationType& SDegreesOp()
    {
        static auto v{ UK2Node_gdpool::OperationType(FName("gdpool SAngle(Degrees)"), USpiceK2::gdpool_double, FK2Conversion::DegreesToSAngle()) };
        return v;
    }

    static const UK2Node_gdpool::OperationType& SDistanceVectorOp()
    {

        static auto v{ UK2Node_gdpool::OperationType(FName("gdpool SDistanceVector"), USpiceK2::gdpool_vector, FK2Conversion::SDimensionlessVectorToSDistanceVector()) };
        return v;
    }

    static const UK2Node_gdpool::OperationType& SVelocityVectorOp()
    {
        static auto v{ UK2Node_gdpool::OperationType(FName("gdpool SVelocityVector"), USpiceK2::gdpool_vector, FK2Conversion::SDimensionlessVectorToSVelocityVector()) };
        return v;
    }

    static const UK2Node_gdpool::OperationType& SDistanceX()
    {
        static auto v{ UK2Node_gdpool::OperationType(FName("gdpool SDistanceVector.X"), USpiceK2::gdpool_vector, FK2Conversion::SDimensionlessVectorXToSDistance()) };
        return v;
    }

    static const UK2Node_gdpool::OperationType& SDistanceY()
    {
        static auto v{ UK2Node_gdpool::OperationType(FName("gdpool SDistanceVector.Y"), USpiceK2::gdpool_vector, FK2Conversion::SDimensionlessVectorYToSDistance()) };
        return v;
    }

    static const UK2Node_gdpool::OperationType& SDistanceZ()
    {
        static auto v{ UK2Node_gdpool::OperationType(FName("gdpool SDistanceVector.Z"), USpiceK2::gdpool_vector, FK2Conversion::SDimensionlessVectorZToSDistance()) };
        return v;
    }

    static const TMap<FName, UK2Node_gdpool::OperationType>& MakeOperationsMap()
    {
        static auto OperationsMap = TMap<FName, UK2Node_gdpool::OperationType>();

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

        return OperationsMap;
    }
}

const TMap<FName, UK2Node_gdpool::OperationType>& UK2Node_gdpool::GetOperationsMap() const
{
    static const auto OperationsMap{ gdpool::MakeOperationsMap() };
    return OperationsMap;
}


#undef LOCTEXT_NAMESPACE