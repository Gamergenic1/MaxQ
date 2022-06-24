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
#include "K2SingleOutputOp.generated.h"

USTRUCT()
struct FK2SingleOutputOp
{
    GENERATED_BODY()
        
    UPROPERTY() FName ShortName;
    UPROPERTY() FString FullName;
    UPROPERTY() FName K2NodeName;
    UPROPERTY() FK2Type InnerType;
    UPROPERTY() FK2Type OuterType;
    UPROPERTY() FK2Conversion InnerToOuterConversion;

    FK2SingleOutputOp()
    {
        ShortName = FName();
        FullName = FString();
        K2NodeName = FName();
        InnerType = FK2Type();
        OuterType = FK2Type();
        InnerToOuterConversion = FK2Conversion();
    }

    FK2SingleOutputOp(FName _name, FName _k2NodeName, const FK2Type& _final)
    {
        ShortName = _name;
        FullName = _name.ToString();
        K2NodeName = _k2NodeName;
        OuterType = _final;
        InnerType = _final;
        InnerToOuterConversion = FK2Conversion();
    }

    FK2SingleOutputOp(FName _name, FName _k2NodeName,const FK2Conversion& _InnerToOuterConversion)
    {
        ShortName = _name;
        FullName = _name.ToString();
        K2NodeName = _k2NodeName;
        InnerType = _InnerToOuterConversion.In;
        OuterType = _InnerToOuterConversion.Out;
        InnerToOuterConversion = _InnerToOuterConversion;
    }

    FK2SingleOutputOp(const FK2SingleOutputOp& other)
    {
        ShortName = other.ShortName;
        FullName = other.FullName;
        K2NodeName = other.K2NodeName;
        OuterType = other.OuterType;
        InnerType = other.InnerType;
        InnerToOuterConversion = other.InnerToOuterConversion;
    }

    FK2SingleOutputOp& operator= (const FK2SingleOutputOp& other)
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
        InnerToOuterConversion = other.InnerToOuterConversion;

        // return the existing object so we can chain this operator
        return *this;
    }


    bool operator== (const FK2SingleOutputOp& other) const
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
            check(InnerToOuterConversion == other.InnerToOuterConversion);
        }
#endif

        return bEqual;
    }
};
