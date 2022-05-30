// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "K2Type.h"
#include "K2Conversion.generated.h"


UENUM(BlueprintType)
enum class EK2_ComponentSelector : uint8
{
    All UMETA(DisplayName = "*"),
    X UMETA(DisplayName = "X Only"),
    Y UMETA(DisplayName = "Y Only"),
    Z UMETA(DisplayName = "Z Only"),
};


USTRUCT()
struct FK2Conversion
{
    GENERATED_BODY()

    UPROPERTY() FName ConversionName;
    UPROPERTY() FK2Type In;
    UPROPERTY() EK2_ComponentSelector Selector;
    UPROPERTY() FK2Type Out;

    FK2Conversion()
    {
        ConversionName = FName();
        In = FK2Type();
        Out = FK2Type();
        Selector = EK2_ComponentSelector::All;
    }

    FK2Conversion(FName name, const FK2Type& _in, const FK2Type& _out, EK2_ComponentSelector _selector = EK2_ComponentSelector::All)
    {
        ConversionName = name;
        In = _in;
        Out = _out;
        Selector = _selector;
    }

    FK2Conversion(const FK2Conversion& other)
    {
        ConversionName = other.ConversionName;
        In = FK2Type(other.In);
        Selector = other.Selector;
        Out = FK2Type(other.Out);
    }

    FK2Conversion& operator= (const FK2Conversion& other)
    {
        // self-assignment guard
        if (this == &other)
            return *this;

        // do the copy
        ConversionName = other.ConversionName;
        In = other.In;
        Selector = other.Selector;
        Out = other.Out;

        // return the existing object so we can chain this operator
        return *this;
    }

    static SPICEUNCOOKED_API FK2Conversion None();
    static SPICEUNCOOKED_API FK2Conversion DoubleToSMassConstant();
    static SPICEUNCOOKED_API FK2Conversion DegreesToSAngle();
    static SPICEUNCOOKED_API FK2Conversion DoubleToSDistance();
    static SPICEUNCOOKED_API FK2Conversion SDimensionlessVectorXToSDistance();
    static SPICEUNCOOKED_API FK2Conversion SDimensionlessVectorYToSDistance();
    static SPICEUNCOOKED_API FK2Conversion SDimensionlessVectorZToSDistance();
    static SPICEUNCOOKED_API FK2Conversion SDimensionlessVectorToSDistanceVector();
    static SPICEUNCOOKED_API FK2Conversion SDimensionlessVectorToSVelocityVector();
};
