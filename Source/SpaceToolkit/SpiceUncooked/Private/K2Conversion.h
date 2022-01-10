// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

#pragma once

#include "CoreMinimal.h"
#include "K2Type.h"
#include "K2Conversion.generated.h"

USTRUCT()
struct FK2Conversion
{
    GENERATED_BODY()

    UPROPERTY() FName ConversionName;
    UPROPERTY() FK2Type In;
    UPROPERTY() FK2Type Out;

    FK2Conversion()
    {
        ConversionName = FName();
        In = FK2Type();
        Out = FK2Type();
    }

    FK2Conversion(FName name, const FK2Type& _in, const FK2Type& _out)
    {
        ConversionName = name;
        In = _in;
        Out = _out;
    }

    FK2Conversion(const FK2Conversion& other)
    {
        ConversionName = other.ConversionName;
        In = FK2Type(other.In);
        Out = FK2Type(other.Out);
    }

    FK2Conversion& FK2Conversion::operator= (const FK2Conversion& other)
    {
        // self-assignment guard
        if (this == &other)
            return *this;

        // do the copy
        ConversionName = other.ConversionName;
        In = other.In;
        Out = other.Out;

        // return the existing object so we can chain this operator
        return *this;
    }

    static SPICEUNCOOKED_API FK2Conversion None();
    static SPICEUNCOOKED_API FK2Conversion DoubleToSMassConstant();
    static SPICEUNCOOKED_API FK2Conversion DegreesToSAngle();
    static SPICEUNCOOKED_API FK2Conversion DoubleToSDistance();
    static SPICEUNCOOKED_API FK2Conversion SDimensionlessVectorToSDistanceVector();
    static SPICEUNCOOKED_API FK2Conversion SDimensionlessVectorToSVelocityVector();
};
