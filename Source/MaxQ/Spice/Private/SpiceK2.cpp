// Copyright 2021 Gamergenic.  See full copyright notice in SpiceK2.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "SpiceK2.h"
#include "SpicePlatformDefs.h"
#include "Spice.h"
#include "SpiceUtilities.h"

PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
extern "C"
{
#include "SpiceUsr.h"
}
PRAGMA_POP_PLATFORM_DEFAULT_PACKING



double USpiceK2::bodvrd_double_K2(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& bodynm,
    const FString& item
)
{
    SpiceDouble _result[1];
    SpiceInt n_actual, n_expected = sizeof(_result) / sizeof(_result[0]);

    ZeroOut(_result);
    bodvrd_c(TCHAR_TO_ANSI(*bodynm), TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);
    double ReturnValue = _result[0];

    ErrorCheck(ResultCode, ErrorMessage);
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
    SpiceDouble _result[3];
    SpiceInt n_actual, n_expected = sizeof(_result) / sizeof(_result[0]);

    ZeroOut(_result);
    bodvrd_c(TCHAR_TO_ANSI(*bodynm), TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);
    auto ReturnValue = FSDimensionlessVector(_result);

    ErrorCheck(ResultCode, ErrorMessage);
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
    SpiceDouble _result[256];
    SpiceInt n_actual, n_expected = sizeof(_result) / sizeof(_result[0]);

    ZeroOut(_result);
    bodvrd_c(TCHAR_TO_ANSI(*bodynm), TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);
    
    auto ReturnValue = TArray<double>();

    ErrorCheck(ResultCode, ErrorMessage);

    if (ResultCode == ES_ResultCode::Success)
    {
        ReturnValue.Init(0., n_actual);

        check(sizeof(double) == sizeof(SpiceDouble));
        FMemory::Memcpy(ReturnValue.GetData(), _result, n_actual * sizeof(SpiceDouble));
    }

    return ReturnValue;
}


double USpiceK2::bodvcd_double_K2(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int bodyid,
    const FString& item
)
{
    SpiceDouble _result[1];
    SpiceInt n_actual, n_expected = sizeof(_result) / sizeof(_result[0]);

    ZeroOut(_result);
    bodvcd_c((SpiceInt)bodyid, TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);
    double ReturnValue = _result[0];

    ErrorCheck(ResultCode, ErrorMessage);
    if (ResultCode == ES_ResultCode::Success && n_actual != n_expected)
    {
        ResultCode = ES_ResultCode::Error;
        ErrorMessage = FString::Printf(TEXT("Blueprint request for BODY%d_%s Expected double[%d] but proc returned double[%d]"), bodyid, *item, n_expected, n_actual);
    }

    return ReturnValue;
}

FSDimensionlessVector USpiceK2::bodvcd_vector_K2(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int bodyid,
    const FString& item
)
{
    SpiceDouble _result[3];
    SpiceInt n_actual, n_expected = sizeof(_result) / sizeof(_result[0]);

    ZeroOut(_result);
    bodvcd_c((SpiceInt)bodyid, TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);
    auto ReturnValue = FSDimensionlessVector(_result);

    ErrorCheck(ResultCode, ErrorMessage);
    if (ResultCode == ES_ResultCode::Success && n_actual != n_expected)
    {
        ResultCode = ES_ResultCode::Error;
        ErrorMessage = FString::Printf(TEXT("Blueprint request for BODY%d_%s Expected double[%d] but proc returned double[%d]"), bodyid, *item, n_expected, n_actual);
    }

    return ReturnValue;
}

TArray<double> USpiceK2::bodvcd_array_K2(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int bodyid,
    const FString& item
)
{
    SpiceDouble _result[256];
    SpiceInt n_actual, n_expected = sizeof(_result) / sizeof(_result[0]);

    ZeroOut(_result);
    bodvcd_c((SpiceInt)bodyid, TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);

    auto ReturnValue = TArray<double>();

    ErrorCheck(ResultCode, ErrorMessage);

    if (ResultCode == ES_ResultCode::Success)
    {
        ReturnValue.Init(0., n_actual);

        check(sizeof(double) == sizeof(SpiceDouble));
        FMemory::Memcpy(ReturnValue.GetData(), _result, n_actual * sizeof(SpiceDouble));
    }

    return ReturnValue;
}

TArray<double> USpiceK2::gdpool_array_K2(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& name,
    int start
)
{
    // Inputs
    ConstSpiceChar* _name = TCHAR_TO_ANSI(*name);
    SpiceInt        _start = 0;
    SpiceInt        _room = 200;
    // Outputs
    SpiceInt        _n = 0;
    size_t buffer_size = _room * sizeof(SpiceDouble);
    SpiceDouble* _values = (SpiceDouble*)StackAlloc(buffer_size);
    SpiceBoolean    _found = SPICEFALSE;

    // Invocation
    memset(_values, 0, buffer_size);
    gdpool_c(_name, _start, _room, &_n, _values, &_found);

    // Return values
    TArray<double> value = TArray<double>();

    if (_found == SPICETRUE)
    {
        value.Init(0, _n);
        
        check(sizeof(SpiceDouble) == sizeof(double));
        FMemory::Memcpy(value.GetData(), _values, _n * sizeof(double));
    }

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);

    if (_found != SPICETRUE)
    {
        ResultCode = ES_ResultCode::Error;
    }

    return value;
}

FSDimensionlessVector USpiceK2::gdpool_vector_K2(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& name
)
{
    // Inputs
    ConstSpiceChar* _name = TCHAR_TO_ANSI(*name);
    SpiceInt        _start = 0;
    SpiceInt        _room = 3;
    // Outputs
    SpiceInt        _n = 0;
    SpiceDouble     _value[3];  ZeroOut(_value);
    SpiceBoolean    _found = SPICEFALSE;

    // Invocation
    gdpool_c(_name, _start, _room, &_n, _value, &_found);

    // Return values
    FSDimensionlessVector value = FSDimensionlessVector(_value);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);

    if (_found != SPICETRUE)
    {
        ResultCode = ES_ResultCode::Error;
    }

    return value;
}


double USpiceK2::gdpool_double_K2(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& name
)
{
    // Inputs
    ConstSpiceChar* _name = TCHAR_TO_ANSI(*name);
    SpiceInt        _start = 0;
    SpiceInt        _room = 1;
    // Outputs
    SpiceInt        _n = 0;
    SpiceDouble     _value = 0;
    SpiceBoolean    _found = SPICEFALSE;

    // Invocation
    gdpool_c(_name, _start, _room, &_n, &_value, &_found);

    // Return values
    double value = _value;

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);

    if (_found != SPICETRUE)
    {
        ResultCode = ES_ResultCode::Error;
    }

    return value;
}


FSEphemerisTime USpiceK2::Conv_DoubleToSEphemerisTime_K2(double value)
{
    return FSEphemerisTime(value);
}

FSEphemerisPeriod USpiceK2::Conv_DoubleToSEphemerisPeriod_K2(double value)
{
    return FSEphemerisPeriod(value);
}

FSMassConstant USpiceK2::Conv_DoubleToSMassConstant_K2(double value)
{
    return FSMassConstant(value);
}

FSDistance USpiceK2::Conv_DoubleToSDistance_K2(double value)
{
    return FSDistance(value);
}

FSAngle USpiceK2::Conv_DegreesToSAngle_K2(double value)
{
    return FSAngle(value * SpiceUtilities::rpd);
}

FSAngle USpiceK2::Conv_RadiansToSAngle_K2(double value)
{
    return FSAngle(value);
}


FSAngularRate USpiceK2::Conv_DegreesPersecondToSAngularRate_K2(double value)
{
    return FSAngularRate(value * SpiceUtilities::rpd);
}


FSAngularRate USpiceK2::Conv_RadiansPersecondToSAngularRate_K2(double value)
{
    return FSAngularRate(value);
}


FSAngularRate USpiceK2::Conv_MinutesPerTurnToSAngularRate_K2(double value)
{
    return FSAngularRate(SpiceUtilities::twopi * 60. / value);
}


FSDistanceVector USpiceK2::Conv_SDimensionlessVectorToSDistanceVector_K2(const FSDimensionlessVector& value)
{
    return FSDistanceVector(value);
}

FSVelocityVector USpiceK2::Conv_SDimensionlessVectorToSVelocityVector_K2(const FSDimensionlessVector& value)
{
    return FSVelocityVector(value);
}

FSDistance USpiceK2::Conv_SDimensionlessVector_X_ToSDistance_K2(const FSDimensionlessVector& value)
{
    return value.x;
}

FSDistance USpiceK2::Conv_SDimensionlessVector_Y_ToSDistance_K2(const FSDimensionlessVector& value)
{
    return value.y;
}

FSDistance USpiceK2::Conv_SDimensionlessVector_Z_ToSDistance_K2(const FSDimensionlessVector& value)
{
    return value.z;
}

#undef StackAlloc
