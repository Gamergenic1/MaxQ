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

FSRotationMatrix USpiceK2::mtxm_matrix_K2(const FSRotationMatrix& m1, const FSRotationMatrix& m2)
{
    SpiceDouble _m1[3][3];  m1.CopyTo(_m1);
    SpiceDouble _m2[3][3];  m2.CopyTo(_m2);
    SpiceDouble _mout[3][3];

    mtxm_c(_m1, _m2, _mout);

    return FSRotationMatrix(_mout);
}

FSStateTransform USpiceK2::mtxm_state_transform_K2(const FSStateTransform& m1, const FSStateTransform& m2)
{
    SpiceDouble _m1[6][6];  m1.CopyTo(_m1);
    SpiceDouble _m2[6][6];  m2.CopyTo(_m2);
    constexpr SpiceInt    _nc1 = 6;
    constexpr SpiceInt    _nr1r2 = 6;
    constexpr SpiceInt    _nc2 = 6;

    SpiceDouble _mout[6][6];

    mtxmg_c(_m1, _m2, _nc1, _nr1r2, _nc2, _mout);

    return FSStateTransform(_mout);
}

FSDimensionlessVector USpiceK2::mtxv_vector_K2(const FSRotationMatrix& m, const FSDimensionlessVector& v)
{
    // Inputs
    SpiceDouble    _m[3][3];	m.CopyTo(_m);
    SpiceDouble    _v[3];		v.CopyTo(_v);

    // Outputs
    SpiceDouble    _vout[3];

    // Invocation
    mtxv_c(_m, _v, _vout);

    // Return Value
    return FSDimensionlessVector(_vout);
}

FSDimensionlessStateVector USpiceK2::mtxv_state_vector_K2(const FSStateTransform& m, const FSDimensionlessStateVector& v)
{
    // Input
    double _m[6][6];       m.CopyTo(_m);
    double _v[6];          v.CopyTo(_v);
    SpiceInt    _nrow1 = 6;
    SpiceInt    _nc1r2 = 6;

    // Output
    double _vout[6];

    // Invocation
    mtxvg_c(_m, _v, _nrow1, _nc1r2, _vout);

    // Pack outputs
    return FSDimensionlessStateVector(_vout);
}

FSRotationMatrix USpiceK2::mxm_matrix_K2(const FSRotationMatrix& m1, const FSRotationMatrix& m2)
{
    SpiceDouble _m1[3][3];  m1.CopyTo(_m1);
    SpiceDouble _m2[3][3];  m2.CopyTo(_m2);
    SpiceDouble _mout[3][3];

    mxm_c(_m1, _m2, _mout);

    return FSRotationMatrix(_mout);
}

FSStateTransform USpiceK2::mxm_state_transform_K2(const FSStateTransform& m1, const FSStateTransform& m2)
{
    SpiceDouble _m1[6][6];  m1.CopyTo(_m1);
    SpiceDouble _m2[6][6];  m2.CopyTo(_m2);
    SpiceDouble _mout[6][6];

    constexpr SpiceInt nr1 = 6;
    constexpr SpiceInt nc1r2 = 6;
    constexpr SpiceInt nc2 = 6;

    mxmg_c(_m1, _m2, nr1, nc1r2, nc2, _mout);

    return FSStateTransform(_mout);
}

FSRotationMatrix USpiceK2::mxmt_matrix_K2(const FSRotationMatrix& m1, const FSRotationMatrix& m2)
{
    SpiceDouble _m1[3][3];  m1.CopyTo(_m1);
    SpiceDouble _m2[3][3];  m2.CopyTo(_m2);
    SpiceDouble _mout[3][3];

    mxmt_c(_m1, _m2, _mout);

    return FSRotationMatrix(_mout);
}

FSStateTransform USpiceK2::mxmt_state_transform_K2(const FSStateTransform& m1, const FSStateTransform& m2)
{
    SpiceDouble _m1[6][6];  m1.CopyTo(_m1);
    SpiceDouble _m2[6][6];  m2.CopyTo(_m2);
    SpiceDouble _mout[6][6];

    constexpr SpiceInt nr1 = 6;
    constexpr SpiceInt nc1c2 = 6;
    constexpr SpiceInt nr2 = 6;

    mxmtg_c(_m1, _m2, nr1, nc1c2, nr2, _mout);

    return FSStateTransform(_mout);
}

FSDimensionlessVector USpiceK2::mxv_vector_K2(const FSRotationMatrix& m, const FSDimensionlessVector& v)
{
    // Inputs
    SpiceDouble    _m[3][3];	m.CopyTo(_m);
    SpiceDouble    _v[3];		v.CopyTo(_v);

    // Outputs
    SpiceDouble    _vout[3];

    // Invocation
    mxv_c(_m, _v, _vout);

    // Return Value
    return FSDimensionlessVector(_vout);
}

FSDimensionlessStateVector USpiceK2::mxv_state_vector_K2(const FSStateTransform& m, const FSDimensionlessStateVector& v)
{
    // Inputs
    SpiceDouble    _m[6][6];	m.CopyTo(_m);
    SpiceDouble    _v[6];		v.CopyTo(_v);

    // Outputs
    SpiceDouble    _vout[6];

    constexpr SpiceInt _nr1   { 6 };
    constexpr SpiceInt _nc1r2 { 6 };

    // Invocation
    mxvg_c(_m, _v, _nr1, _nc1r2, _vout);

    // Return Value
    return FSDimensionlessStateVector(_vout);
}

FSDimensionlessVector USpiceK2::qderiv_vector_K2(const FSDimensionlessVector& f0, const FSDimensionlessVector& f2, double delta)
{
    constexpr SpiceInt _ndim { 3 };
    SpiceDouble    _f0[3];		f0.CopyTo(_f0);
    SpiceDouble    _f2[3];		f2.CopyTo(_f2);
    SpiceDouble _delta = delta;

    SpiceDouble    _dfdt[3];
    qderiv_c(_ndim, _f0, _f2, _delta, _dfdt);

    return FSDimensionlessVector(_dfdt);
}

FSRotationMatrix USpiceK2::twovec_vector_K2(ES_ResultCode& ResultCode, FString& ErrorMessage, ES_Axis axisa, const FSDimensionlessVector& axdef, ES_Axis axisp, const FSDimensionlessVector& plndef)
{
    SpiceDouble _axdef[3];   axdef.CopyTo(_axdef);
    SpiceInt    _indexa      = (SpiceInt)axisa;
    SpiceDouble _plndef[3];  plndef.CopyTo(_plndef);
    SpiceInt    _indexp      = (SpiceInt)axisp;

    SpiceDouble _mout[3][3];

    twovec_c(_axdef, _indexa, _plndef, _indexp, _mout);

    return FSRotationMatrix(_mout);
}

FSStateTransform USpiceK2::twovxf_state_vector_K2(ES_ResultCode& ResultCode, FString& ErrorMessage, ES_Axis axisa, const FSDimensionlessStateVector& axdef, ES_Axis axisp, const FSDimensionlessStateVector& plndef)
{
    SpiceDouble _axdef[6];   axdef.CopyTo(_axdef);
    SpiceInt    _indexa = (SpiceInt)axisa;
    SpiceDouble _plndef[6];  plndef.CopyTo(_plndef);
    SpiceInt    _indexp = (SpiceInt)axisp;

    SpiceDouble _mout[6][6];

    twovxf_c(_axdef, _indexa, _plndef, _indexp, _mout);

    return FSStateTransform(_mout);
}

FSDimensionlessVector USpiceK2::ucrss_vector_K2(const FSDimensionlessVector& v1, const FSDimensionlessVector& v2)
{
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    SpiceDouble _v2[3]; v2.CopyTo(_v2);

    SpiceDouble _vout[3]; ZeroOut(_vout);

    ucrss_c(_v1, _v2, _vout);

    return FSDimensionlessVector(_vout);
}

void USpiceK2::unorm_vector_K2(const FSDimensionlessVector& v1, FSDimensionlessVector& vout, double& vmag)
{
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    // Initialize outputs to whatever was passed in by reference (so that if nothing was written,
    // we return the original value unchanged.
    SpiceDouble _vout[3]; vout.CopyTo(_vout);
    SpiceDouble _vmag = (SpiceDouble)vmag;

    unorm_c(_v1, _vout, &_vmag);

    vout = FSDimensionlessVector(_vout);
    vmag = (double)_vmag;
}

FSDimensionlessVector USpiceK2::vadd_vector_K2(const FSDimensionlessVector& v1, const FSDimensionlessVector& v2)
{
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    SpiceDouble _v2[3]; v2.CopyTo(_v2);

    SpiceDouble _vout[3]; ZeroOut(_vout);

    vadd_c(_v1, _v2, _vout);

    return FSDimensionlessVector(_vout);
}

FSDimensionlessStateVector USpiceK2::vadd_state_vector_K2(const FSDimensionlessStateVector& v1, const FSDimensionlessStateVector& v2)
{
    SpiceDouble _v1[6]; v1.CopyTo(_v1);
    SpiceDouble _v2[6]; v2.CopyTo(_v2);
    constexpr SpiceInt _ndim = 6;

    SpiceDouble _vout[6]; ZeroOut(_vout);

    vaddg_c(_v1, _v2, _ndim, _vout);

    return FSDimensionlessStateVector(_vout);
}

FSDimensionlessVector USpiceK2::vcrss_vector_K2(const FSDimensionlessVector& v1, const FSDimensionlessVector& v2)
{
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    SpiceDouble _v2[3]; v2.CopyTo(_v2);

    SpiceDouble _vout[3]; ZeroOut(_vout);

    vcrss_c(_v1, _v2, _vout);

    return FSDimensionlessVector(_vout);
}

double USpiceK2::vdist_vector_K2(const FSDimensionlessVector& v1, const FSDimensionlessVector& v2)
{
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    SpiceDouble _v2[3]; v2.CopyTo(_v2);

    return (double)vdist_c(_v1, _v2);
}

double USpiceK2::vdot_vector_K2(const FSDimensionlessVector& v1, const FSDimensionlessVector& v2)
{
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    SpiceDouble _v2[3]; v2.CopyTo(_v2);

    return (double)vdot_c(_v1, _v2);
}

FSDimensionlessVector USpiceK2::vequ_vector_K2(const FSDimensionlessVector& v)
{
    SpiceDouble _vin[3];  v.CopyTo(_vin);
    SpiceDouble _vout[3]; ZeroOut(_vout);

    vequ_c(_vin, _vout);

    return FSDimensionlessVector(_vout);
}

FSDimensionlessVector USpiceK2::vhat_vector_K2(const FSDimensionlessVector& v)
{
    SpiceDouble _v1[3];  v.CopyTo(_v1);
    SpiceDouble _vout[3]; ZeroOut(_vout);

    vhat_c(_v1, _vout);

    return FSDimensionlessVector(_vout);
}

FSDimensionlessVector USpiceK2::vlcom_vector_K2(double a, const FSDimensionlessVector& v1, double b, const FSDimensionlessVector& v2)
{
    // Still deciding which form of initialization makes more sense, apologies for the inconsistency.
    // Priorities: Robustness (runtime, and regarding maintenance, compiler-catching-errors-on-new-platforms-etc),
    //             Concise & Understandable, Performance is a lower priority...
    //             Because this are blueprints implementations.  The overhead of blueprints dominates whatever the compiler
    //             does to initialize the wrapped values.
    ConstSpiceDouble _a      { a };
    ConstSpiceDouble _v1[3]  { v1.x, v1.y, v1.z };
    ConstSpiceDouble _b      { b };
    ConstSpiceDouble _v2[3]  { v2.x, v2.y, v2.z };
    SpiceDouble _sum[3] { 0, 0, 0 };

    vlcom_c(_a, _v1, _b, _v2, _sum);

    return {_sum};
}


FSDimensionlessVector USpiceK2::vlcom3_vector_K2(double a, const FSDimensionlessVector& v1, double b, const FSDimensionlessVector& v2, double c, const FSDimensionlessVector& v3)
{
    ConstSpiceDouble _a      { a };
    ConstSpiceDouble _v1[3]  { v1.x, v1.y, v1.z };
    ConstSpiceDouble _b      { b };
    ConstSpiceDouble _v2[3]  { v2.x, v2.y, v2.z };
    ConstSpiceDouble _c      { c };
    ConstSpiceDouble _v3[3]  { v3.x, v3.y, v3.z };
    SpiceDouble _sum[3] { 0, 0, 0 };

    vlcom3_c(_a, _v1, _b, _v2, _c, _v3, _sum);

    return { _sum };
}

FSDimensionlessVector USpiceK2::vminus_vector_K2(const FSDimensionlessVector& v)
{
    ConstSpiceDouble _v1[3]  { v.x, v.y, v.z };
    SpiceDouble _vout[3]{ 0, 0, 0 };

    vminus_c(_v1, _vout);

    return { _vout };
}

double USpiceK2::vnorm_vector_K2(const FSDimensionlessVector& v)
{
    ConstSpiceDouble _v1[3]{ v.x, v.y, v.z };

    return vnorm_c(_v1);
}

FSDimensionlessVector USpiceK2::vpack_vector_K2(double x, double y, double z)
{
    ConstSpiceDouble _x { x };
    ConstSpiceDouble _y { y };
    ConstSpiceDouble _z { z };
    SpiceDouble _v[3]{ 0, 0, 0 };

    vpack_c(_x, _y, _z, _v);

    return { _v };
}

FSDimensionlessStateVector USpiceK2::vpack_state_vector_K2(double x, double y, double z, double dx, double dy, double dz)
{
    SpiceDouble _v[3]{ 0, 0, 0 };
    {
        ConstSpiceDouble _x{ x };
        ConstSpiceDouble _y{ y };
        ConstSpiceDouble _z{ z };

        vpack_c(_x, _y, _z, _v);
    }

    SpiceDouble _dv[3]{ 0, 0, 0 };
    {
        ConstSpiceDouble _dx{ dx };
        ConstSpiceDouble _dy{ dy };
        ConstSpiceDouble _dz{ dz };

        vpack_c(_dx, _dy, _dz, _dv);
    }

    // modern c++ brace elision can get us in trouble here, unless explicit.
    // be very explicit.
    return { FSDimensionlessStateVector( FSDimensionlessVector(_v), FSDimensionlessVector(_dv)) };
}

FSDimensionlessVector USpiceK2::vperp_vector_K2(const FSDimensionlessVector& a, const FSDimensionlessVector& b)
{
    ConstSpiceDouble _a[3]{ a.x, a.y, a.z };
    ConstSpiceDouble _b[3]{ a.x, a.y, a.z };

    SpiceDouble _p[3]{ 0, 0, 0 };

    vperp_c(_a, _b, _p);

    return { _p };
}

FSDimensionlessVector USpiceK2::vprjp_vector_K2(const FSDimensionlessVector& vin, const FSPlane& plane)
{
    ConstSpiceDouble _vin[3]     { vin.x, vin.y, vin.z };
    SpicePlane _plane;      CopyTo(plane, _plane);
    SpiceDouble _vout[3]    { 0, 0, 0 };

    vprjp_c(_vin, &_plane, _vout);

    UnexpectedErrorCheck(false);

    return { _vout };
}

FSDimensionlessVector USpiceK2::vproj_vector_K2(const FSDimensionlessVector& a, const FSDimensionlessVector& b)
{
    ConstSpiceDouble _a[3]{ a.x, a.y, a.z };
    ConstSpiceDouble _b[3]{ a.x, a.y, a.z };

    SpiceDouble _p[3]{ 0, 0, 0 };

    vproj_c(_a, _b, _p);

    return { _p };
}

FSDimensionlessVector USpiceK2::vscl_vector_K2(double s, const FSDimensionlessVector& v1)
{
    ConstSpiceDouble _s          { s };
    ConstSpiceDouble _v1[3]      { v1.x, v1.y, v1.z };

    SpiceDouble _vout[3]    { 0, 0, 0 };

    vscl_c(_s, _v1, _vout);

    return { _vout };
}

FSAngle USpiceK2::vsep_vector_K2(const FSDimensionlessVector& v1, const FSDimensionlessVector& v2)
{
    // Inputs
    ConstSpiceDouble _v1[3]  { v1.x, v1.y, v1.z };
    ConstSpiceDouble _v2[3]  { v2.x, v2.y, v2.z };
    // Output
    SpiceDouble _out    { 0 };

    // Invocation
    _out = vsep_c(_v1, _v2);

    // Return Value
    return { _out };
}

FSDimensionlessVector USpiceK2::vsub_vector_K2(const FSDimensionlessVector& v1, const FSDimensionlessVector& v2)
{
    ConstSpiceDouble _v1[3]{ v1.x, v1.y, v1.z };
    ConstSpiceDouble _v2[3]{ v2.x, v2.y, v2.z };

    SpiceDouble _vout[3] { 0, 0, 0 };

    vsub_c(_v1, _v2, _vout);

    return { _vout };
}

FSDimensionlessStateVector USpiceK2::vsub_state_vector_K2(const FSDimensionlessStateVector& v1, const FSDimensionlessStateVector& v2)
{
    SpiceDouble _v1[6]; v1.CopyTo(_v1);
    SpiceDouble _v2[6]; v2.CopyTo(_v2);
    constexpr SpiceInt _ndim = 6;

    SpiceDouble _vout[6]; ZeroOut(_vout);

    vsubg_c(_v1, _v2, _ndim, _vout);

    return { _vout };
}

void USpiceK2::vupack_vector_K2(const FSDimensionlessVector& v, double& x, double& y, double& z)
{
    ConstSpiceDouble _v[3]{ v.x, v.y, v.z };
    SpiceDouble _x {x};
    SpiceDouble _y {y};
    SpiceDouble _z {z};

    vupack_c(_v, &_x, &_y, &_z);

    x = _x;
    y = _y;
    z = _z;
}

void USpiceK2::vupack_state_vector_K2(const FSDimensionlessStateVector& v, double& x, double& y, double& z, double& dx, double& dy, double& dz)
{

    {
        ConstSpiceDouble _vr[3]{ v.r.x, v.r.y, v.r.z };
        SpiceDouble _x{ x };
        SpiceDouble _y{ y };
        SpiceDouble _z{ z };

        vupack_c(_vr, &_x, &_y, &_z);

        x = _x;
        y = _y;
        z = _z;
    }

    {
        ConstSpiceDouble _dvr[3]{ v.dr.x, v.dr.y, v.dr.z };
        SpiceDouble _dx{ dx };
        SpiceDouble _dy{ dy };
        SpiceDouble _dz{ dz };

        vupack_c(_dvr, &_dx, &_dy, &_dz);

        dx = _dx;
        dy = _dy;
        dz = _dz;
    }
}

double USpiceK2::vtmv_vector_K2(const FSDimensionlessVector& v1, const FSRotationMatrix& matrix, const FSDimensionlessVector& v2)
{
    ConstSpiceDouble _v1[3]{ v1.x, v1.y, v1.z };
    SpiceDouble _matrix[3][3]; matrix.CopyTo(_matrix);
    ConstSpiceDouble _v2[3]{ v2.x, v2.y, v2.z };

    return { vtmv_c(_v1, _matrix, _v2) };
}

double USpiceK2::vtmv_state_vector_K2(const FSDimensionlessStateVector& v1, const FSStateTransform& matrix, const FSDimensionlessStateVector& v2)
{
    // Modern C++ brace initialization stinks here.  Too verbose, too many points of failure.
    //
    // SpiceDouble _v1[6] { v1.r.x, v1.r.y, v1.r.z, v1.dr.x, v1.dr.y, v1.dr.z };
    //
    SpiceDouble _v1[6];         v1.CopyTo(_v1);
    SpiceDouble _matrix[6][6];  matrix.CopyTo(_matrix);
    SpiceDouble _v2[6];         v2.CopyTo(_v2);
    // Now, mixed style (C++98 and now Modern C++ braces).  Boo!
    constexpr SpiceInt nrow { 6 };
    constexpr SpiceInt ncol { 6 };

    return { vtmvg_c(_v1, _matrix, _v2, nrow, ncol) };
}

bool USpiceK2::vzero_vector_K2(const FSDimensionlessVector& v)
{
    ConstSpiceDouble _v[3]{ v.x, v.y, v.z };

    return { vzero_c(_v) == SPICETRUE };
}

bool USpiceK2::vzero_state_vector_K2(const FSDimensionlessStateVector& v)
{
    SpiceDouble _v[6];  v.CopyTo(_v);
    constexpr SpiceInt ndim{ 6 };

    return { vzerog_c(_v, ndim) == SPICETRUE };
}

double USpiceK2::vrel_vector_K2(const FSDimensionlessVector& v1, const FSDimensionlessVector& v2)
{
    ConstSpiceDouble _v1[3]{ v1.x, v1.y, v1.z };
    ConstSpiceDouble _v2[3]{ v2.x, v2.y, v2.z };

    return { vrel_c(_v1, _v2) };
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

FSAngularVelocity USpiceK2::Conv_SDimensionlessVectorToSAngularVelocity_K2(const FSDimensionlessVector& value)
{
    return FSAngularVelocity(value);
}

FSDimensionlessVector USpiceK2::Conv_SDistanceVectorToSDimensionlessVector_K2(const FSDistanceVector& value)
{
    return value.AsDimensionlessVector();
}

FSDimensionlessVector USpiceK2::Conv_SVelocityVectorToSDimensionlessVector_K2(const FSVelocityVector& value)
{
    return value.AsDimensionlessVector();
}

FSDimensionlessVector USpiceK2::Conv_SAngularVelocityToSDimensionlessVector_K2(const FSAngularVelocity& value)
{
    return value.AsDimensionlessVector();
}

FSStateVector USpiceK2::Conv_SDimensionlessStateVectorToSStateVector_K2(const FSDimensionlessStateVector& value)
{
    return FSStateVector(value);
}

FSDimensionlessStateVector USpiceK2::Conv_SStateVectorToSDimensionlessStateVector_K2(const FSStateVector& value)
{
    return value.AsDimensionlessStateVector();
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

