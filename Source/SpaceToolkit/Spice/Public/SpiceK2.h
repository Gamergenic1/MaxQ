// Copyright 2021 Gamergenic.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this
// software and associated documentation files (the "Software"), to deal in the Software
// without restriction, including without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

#pragma once

#include "CoreMinimal.h"
#include "SpiceTypes.h"
#include "SpiceK2.generated.h"

#pragma once

UCLASS(BlueprintType, Blueprintable)
class SPICE_API USpiceK2 : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, meta = (ExpandEnumAsExecs = "ResultCode"))
    static double bodvrd_double_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& bodynm,
        const FString& item
    );

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
    static FSDimensionlessVector bodvrd_vector_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& bodynm,
        const FString& item
    );

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
    static TArray<double> bodvrd_array_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& bodynm,
        const FString& item
    );

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
    static FSEphemerisTime Conv_DoubleToSEphemerisTime_K2(double value);

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
    static FSEphemerisPeriod Conv_DoubleToSEphemerisPeriod_K2(double value);

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
    static FSMassConstant Conv_DoubleToSMassConstant_K2(double value);

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
    static FSDistanceVector Conv_FSDimensionlessVectorToSDistanceVector_K2(const FSDimensionlessVector& value);

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
    static FSVelocityVector Conv_FSDimensionlessVectorToSVelocityVector_K2(const FSDimensionlessVector& value);
};


