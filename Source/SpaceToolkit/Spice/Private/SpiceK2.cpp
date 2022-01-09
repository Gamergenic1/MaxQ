// Copyright 2021 Gamergenic.  See full copyright notice in SpiceK2.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

#include "SpiceK2.h"
#include "Spice.h"

PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
extern "C"
{
#include "SpiceUsr.h"

// for ev2lin, dpspce
#include "SpiceZfc.h"
}
PRAGMA_POP_PLATFORM_DEFAULT_PACKING

template<class T>
inline void ZeroOut(T& value)
{
    memset(&value, 0, sizeof(value));
}

double USpiceK2::bodvrd_double_K2(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& bodynm,
    const FString& item
)
{
    UE_LOG(LogTemp, Warning, TEXT("bodvrd_double_K2: %s_%s"), *bodynm, *item);

    SpiceDouble _result[1];
    SpiceInt n_actual, n_expected = sizeof(_result) / sizeof(_result[0]);

    ZeroOut(_result);
    bodvrd_c(TCHAR_TO_ANSI(*bodynm), TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);
    double ReturnValue = _result[0];

    USpice::ErrorCheck(ResultCode, ErrorMessage);
    if (ResultCode == ES_ResultCode::Success && n_actual != n_expected)
    {
        ResultCode = ES_ResultCode::Error;
        ErrorMessage = FString::Printf(TEXT("Blueprint request for %s_%s Expected double[%d] but proc returned double[%d]"), *bodynm, *item, n_expected, n_actual);
    }

    return ReturnValue;
}

FSDimensionlessVector USpiceK2::bodvrd_vector_K2(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& bodynm,
    const FString& item
)
{
    UE_LOG(LogTemp, Warning, TEXT("bodvrd_vector_K2: %s_%s"), *bodynm, *item);

    SpiceDouble _result[3];
    SpiceInt n_actual, n_expected = sizeof(_result) / sizeof(_result[0]);

    ZeroOut(_result);
    bodvrd_c(TCHAR_TO_ANSI(*bodynm), TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);
    auto ReturnValue = FSDimensionlessVector(_result);

    USpice::ErrorCheck(ResultCode, ErrorMessage);
    if (ResultCode == ES_ResultCode::Success && n_actual != n_expected)
    {
        ResultCode = ES_ResultCode::Error;
        ErrorMessage = FString::Printf(TEXT("Blueprint request for %s_%s Expected double[%d] but proc returned double[%d]"), *bodynm, *item, n_expected, n_actual);
    }

    return ReturnValue;
}

TArray<double> USpiceK2::bodvrd_array_K2(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& bodynm,
    const FString& item
)
{
    UE_LOG(LogTemp, Warning, TEXT("bodvrd_array_K2: %s_%s"), *bodynm, *item);

    UE_LOG(LogTemp, Warning, TEXT("bodvrd_vector_K2: %s_%s"), *bodynm, *item);

    SpiceDouble _result[256];
    SpiceInt n_actual, n_expected = sizeof(_result) / sizeof(_result[0]);

    ZeroOut(_result);
    bodvrd_c(TCHAR_TO_ANSI(*bodynm), TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);
    
    auto ReturnValue = TArray<double>();

    USpice::ErrorCheck(ResultCode, ErrorMessage);

    if (ResultCode == ES_ResultCode::Success)
    {
        ReturnValue.Init(0., n_actual);

        check(sizeof(double) == sizeof(SpiceDouble))
        memcpy(ReturnValue.GetData(), _result, n_actual * sizeof(SpiceDouble));
    }

    return ReturnValue;
}

FSEphemerisTime USpiceK2::Conv_DoubleToSEphemerisTime_K2(double value)
{
    UE_LOG(LogTemp, Warning, TEXT("Conv_DoubleToSEphemerisTime_K2"));

    return FSEphemerisTime(value);
}

FSEphemerisPeriod USpiceK2::Conv_DoubleToSEphemerisPeriod_K2(double value)
{
    UE_LOG(LogTemp, Warning, TEXT("Conv_DoubleToSEphemerisPeriod_K2"));

    return FSEphemerisPeriod(value);
}

FSMassConstant USpiceK2::Conv_DoubleToSMassConstant_K2(double value)
{
    UE_LOG(LogTemp, Warning, TEXT("Conv_DoubleToSMassConstant_K2"));

    return FSMassConstant(value);
}

FSDistanceVector USpiceK2::Conv_FSDimensionlessVectorToSDistanceVector_K2(const FSDimensionlessVector& value)
{
    UE_LOG(LogTemp, Warning, TEXT("Conv_FSDimensionlessVectorToSDistanceVector_K2"));

    return FSDistanceVector(value);
}

FSVelocityVector USpiceK2::Conv_FSDimensionlessVectorToSVelocityVector_K2(const FSDimensionlessVector& value)
{
    UE_LOG(LogTemp, Warning, TEXT("Conv_FSDimensionlessVectorToSVelocityVector_K2"));

    return FSVelocityVector(value);
}

