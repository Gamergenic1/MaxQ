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
#include "K2PassThroughOp.generated.h"

USTRUCT()
struct FK2PassThroughOp
{
    typedef FK2PassThroughOp OperationType;

    GENERATED_BODY()
        
    UPROPERTY() FName ShortName;
    UPROPERTY() FString FullName;
    UPROPERTY() FName K2NodeName;
    UPROPERTY() FK2Type OuterType;
    UPROPERTY() FK2Type InnerType;
    UPROPERTY() FK2Conversion InnerToOuterConversion;
    UPROPERTY() FK2Conversion OuterToInnerConversion;

    FK2PassThroughOp()
    {
        ShortName = FName();
        FullName = FString();
        K2NodeName = FName();
        OuterType = FK2Type();
        InnerType = FK2Type();
        InnerToOuterConversion = FK2Conversion();
        OuterToInnerConversion = FK2Conversion();
    }

    FK2PassThroughOp(FName _name, FName _k2NodeName, const FK2Type& _final)
    {
        ShortName = _name;
        FullName = _name.ToString();
        K2NodeName = _k2NodeName;
        OuterType = _final;
        InnerType = _final;
        InnerToOuterConversion = FK2Conversion();
        OuterToInnerConversion = FK2Conversion();
    }

    FK2PassThroughOp(FName _name, FName _k2NodeName, const FK2Conversion& _OuterToInnerConversion, const FK2Conversion& _InnerToOuterConversion)
    {
        ShortName = _name;
        FullName = _name.ToString();
        K2NodeName = _k2NodeName;
        OuterType = _OuterToInnerConversion.In;
        InnerType = _OuterToInnerConversion.Out;
        OuterToInnerConversion = _OuterToInnerConversion;
        InnerToOuterConversion = _InnerToOuterConversion;

        check(InnerToOuterConversion.In == InnerType);
        check(InnerToOuterConversion.Out == OuterType);
    }

    FK2PassThroughOp(const OperationType& other)
    {
        ShortName = other.ShortName;
        FullName = other.FullName;
        K2NodeName = other.K2NodeName;
        OuterType = other.OuterType;
        InnerType = other.InnerType;
        OuterToInnerConversion = other.OuterToInnerConversion;
        InnerToOuterConversion = other.InnerToOuterConversion;
    }

    FK2PassThroughOp& operator= (const OperationType& other)
    {
        // self-assignment guard
        if (this == &other)
            return *this;

        // do the copy
        ShortName = other.ShortName;
        FullName = other.FullName;
        K2NodeName = other.K2NodeName;
        OuterType = other.OuterType;
        InnerType = other.InnerType;
        OuterToInnerConversion = other.OuterToInnerConversion;
        InnerToOuterConversion = other.InnerToOuterConversion;

        // return the existing object so we can chain this operator
        return *this;
    }


    bool operator== (const OperationType& other) const
    {
        // self equality
        if (this == &other)
            return true;

        bool bEqual = ShortName.IsEqual(other.ShortName);

#if WITH_EDITOR
        if (bEqual)
        {
            check(FullName.Compare(other.FullName) == 0);
            check(K2NodeName.IsEqual(other.K2NodeName));
            check(OuterType == other.OuterType);
            check(InnerType == other.InnerType);
            check(OuterToInnerConversion == other.OuterToInnerConversion);
            check(InnerToOuterConversion == other.InnerToOuterConversion);
        }
#endif

        return bEqual;
    }

#if WITH_EDITOR
    void CheckClass(UClass* Class) const
    {
        // Ensure the specified actions actually exist!
        if (!OuterToInnerConversion.ConversionName.IsNone())
        {
            check(Class->FindFunctionByName(OuterToInnerConversion.ConversionName));
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
            types.Add(op.OuterType);
        }

        return types;
    }
};
