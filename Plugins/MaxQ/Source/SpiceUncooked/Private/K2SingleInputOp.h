// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "K2Type.h"
#include "K2Conversion.h"
#include "K2SingleInputOp.generated.h"

USTRUCT()
struct FK2SingleInputOp
{
    GENERATED_BODY()
        
    UPROPERTY() FName ShortName;
    UPROPERTY() FString FullName;
    UPROPERTY() FName K2NodeName;
    UPROPERTY() FK2Type InnerType;
    UPROPERTY() FK2Type OuterType;
    UPROPERTY() FK2Conversion OuterToInnerConversion;

    FK2SingleInputOp()
    {
        ShortName = FName();
        FullName = FString();
        K2NodeName = FName();
        InnerType = FK2Type();
        OuterType = FK2Type();
        OuterToInnerConversion = FK2Conversion();
    }

    FK2SingleInputOp(FName _name, FName _k2NodeName, const FK2Type& _final)
    {
        ShortName = _name;
        FullName = _name.ToString();
        K2NodeName = _k2NodeName;
        OuterType = _final;
        InnerType = _final;
        OuterToInnerConversion = FK2Conversion();
    }

    FK2SingleInputOp(FName _name, FName _k2NodeName,const FK2Conversion& _OuterToInnerConversion)
    {
        ShortName = _name;
        FullName = _name.ToString();
        K2NodeName = _k2NodeName;
        OuterType = _OuterToInnerConversion.In;
        InnerType = _OuterToInnerConversion.Out;
        OuterToInnerConversion = _OuterToInnerConversion;
    }

    FK2SingleInputOp(const FK2SingleInputOp& other)
    {
        ShortName = other.ShortName;
        FullName = other.FullName;
        K2NodeName = other.K2NodeName;
        OuterType = other.OuterType;
        InnerType = other.InnerType;
        OuterToInnerConversion = other.OuterToInnerConversion;
    }

    FK2SingleInputOp& operator= (const FK2SingleInputOp& other)
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

        // return the existing object so we can chain this operator
        return *this;
    }


    bool operator== (const FK2SingleInputOp& other) const
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
        }
#endif

        return bEqual;
    }
};
