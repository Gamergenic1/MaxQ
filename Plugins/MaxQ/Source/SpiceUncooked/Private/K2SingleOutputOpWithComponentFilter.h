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
#include "K2Type.h"
#include "K2Conversion.h"
#include "K2SingleOutputOpWithComponentFilter.generated.h"

USTRUCT()
struct FK2SingleOutputOpWithComponentFilter
{
    typedef FK2SingleOutputOpWithComponentFilter OperationType;

    GENERATED_BODY()
        
    UPROPERTY() FName ShortName;
    UPROPERTY() FString FullName;
    UPROPERTY() FName K2NodeName;
    UPROPERTY() FK2Type Intermediate;
    UPROPERTY() EK2_ComponentSelector Selector;
    UPROPERTY() FK2Type Final;
    UPROPERTY() FK2Conversion Conversion;

    FK2SingleOutputOpWithComponentFilter()
    {
        ShortName = FName();
        FullName = FString();
        K2NodeName = FName();
        Intermediate = FK2Type();
        Final = FK2Type();
        Conversion = FK2Conversion();
        Selector = EK2_ComponentSelector::All;
    }

    FK2SingleOutputOpWithComponentFilter(FName _name, FName _k2NodeName, const FK2Type& _final)
    {
        ShortName = _name;
        FullName = _name.ToString();
        K2NodeName = _k2NodeName;
        Intermediate = _final;
        Final = _final;
        Conversion = FK2Conversion();
        Selector = EK2_ComponentSelector::All;
    }

    FK2SingleOutputOpWithComponentFilter(FName _name, FName _k2NodeName, const FK2Conversion& _conversion)
    {
        ShortName = _name;
        FullName = _name.ToString();
        K2NodeName = _k2NodeName;
        Intermediate = _conversion.In;
        Selector = _conversion.Selector;
        Final = _conversion.Out;
        Conversion = _conversion;
    }

    FK2SingleOutputOpWithComponentFilter(const OperationType& other)
    {
        ShortName = other.ShortName;
        FullName = other.FullName;
        K2NodeName = other.K2NodeName;
        Intermediate = FK2Type(other.Intermediate);
        Final = FK2Type(other.Final);
        Conversion = FK2Conversion(other.Conversion);
        Selector = other.Selector;
    }

    FK2SingleOutputOpWithComponentFilter& operator= (const OperationType& other)
    {
        // self-assignment guard
        if (this == &other)
            return *this;

        // do the copy
        ShortName = other.ShortName;
        FullName = other.FullName;
        K2NodeName = other.K2NodeName;
        Intermediate = other.Intermediate;
        Final = other.Final;
        Conversion = other.Conversion;
        Selector = other.Selector;

        // return the existing object so we can chain this operator
        return *this;
    }

#if WITH_EDITOR
    void CheckClass(UClass* Class) const
    {
        // Ensure the specified actions actually exist!
        if (!Conversion.ConversionName.IsNone())
        {
            check(Class->FindFunctionByName(Conversion.ConversionName));
        }
        if (!K2NodeName.IsNone())
        {
            check(Class->FindFunctionByName(K2NodeName));
        }
    }
#endif

    static TArray<FK2Type> GetTypesFromOperations(const TArray<OperationType>& ops)
    {
        TArray<FK2Type> types;

        for (const auto& op : ops)
        {
            types.Add(op.Final);
        }

        return types;
    }
};
