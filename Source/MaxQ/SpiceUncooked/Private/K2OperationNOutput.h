// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

#pragma once

#include "CoreMinimal.h"
#include "K2Type.h"
#include "K2Conversion.h"
#include "K2OperationNOutput.generated.h"

USTRUCT()
struct FK2OperationNOutput
{
    GENERATED_BODY()
        
    UPROPERTY() FName ShortName;
    UPROPERTY() FString FullName;
    UPROPERTY() FName K2NodeName;
    UPROPERTY() FK2Type Intermediate;
    UPROPERTY() EK2_ComponentSelector Selector;
    UPROPERTY() FK2Type Final;
    UPROPERTY() FK2Conversion Conversion;

    FK2OperationNOutput()
    {
        ShortName = FName();
        FullName = FString();
        K2NodeName = FName();
        Intermediate = FK2Type();
        Final = FK2Type();
        Conversion = FK2Conversion();
        Selector = EK2_ComponentSelector::All;
    }

    FK2OperationNOutput(FName _name, FName _k2NodeName, const FK2Type& _final)
    {
        ShortName = _name;
        FullName = _name.ToString();
        K2NodeName = _k2NodeName;
        Intermediate = _final;
        Final = _final;
        Conversion = FK2Conversion();
        Selector = EK2_ComponentSelector::All;
    }

    FK2OperationNOutput(FName _name, FName _k2NodeName, const FK2Conversion& _conversion)
    {
        ShortName = _name;
        FullName = _name.ToString();;
        K2NodeName = _k2NodeName;
        Intermediate = _conversion.In;
        Selector = _conversion.Selector;
        Final = _conversion.Out;
        Conversion = _conversion;
    }

    FK2OperationNOutput(const FK2OperationNOutput& other)
    {
        ShortName = other.ShortName;
        FullName = other.FullName;
        K2NodeName = other.K2NodeName;
        Intermediate = FK2Type(other.Intermediate);
        Final = FK2Type(other.Final);
        Conversion = FK2Conversion(other.Conversion);
        Selector = other.Selector;
    }

    FK2OperationNOutput& FK2OperationNOutput::operator= (const FK2OperationNOutput& other)
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
};
