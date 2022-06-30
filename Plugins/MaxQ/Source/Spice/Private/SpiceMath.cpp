// Copyright 2021 Gamergenic.  See full copyright notice in SpiceK2.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "SpiceMath.h"
#include "SpiceUtilities.h"

PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
extern "C"
{
#include "SpiceUsr.h"
}
PRAGMA_POP_PLATFORM_DEFAULT_PACKING

namespace MaxQ::Math
{
    template<typename VectorType>
    SPICE_API void bodvrd(
        VectorType& Value,
        const FString& bodynm,
        const FString& item,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        SpiceDouble _result[3]; Value.CopyTo(_result);
        SpiceInt n_actual = 0;
        constexpr int n_expected = sizeof(_result) / sizeof(_result[0]);

        bodvrd_c(TCHAR_TO_ANSI(*bodynm), TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);

        Value = VectorType{ _result };

        ES_ResultCode DummyResultCode;
        FString DummyErrorMessage;

        if(ResultCode == nullptr) ResultCode = &DummyResultCode;
        if (ErrorMessage == nullptr) ErrorMessage = &DummyErrorMessage;

        if (!ErrorCheck(*ResultCode, *ErrorMessage) && n_actual != n_expected)
        {
            *ResultCode = ES_ResultCode::Error;
            *ErrorMessage = FString::Printf(TEXT("Blueprint request for %s_%s Expected double[%d] but proc returned double[%d]"), *bodynm, *item, n_expected, n_actual);
        }
    }

    template SPICE_API void bodvrd<FSAngularVelocity>(FSAngularVelocity&, const FString& bodynm, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void bodvrd<FSDistanceVector>(FSDistanceVector&, const FString& bodynm, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void bodvrd<FSVelocityVector>(FSVelocityVector&, const FString& bodynm, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void bodvrd<FSDimensionlessVector>(FSDimensionlessVector&, const FString& bodynm, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);


    template<typename VectorType>
    SPICE_API void bodvrd(
        VectorType& Value,
        const FName& bodynm,
        const FName& item,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        bodvrd<VectorType>(Value, bodynm.ToString(), item.ToString(), ResultCode, ErrorMessage);
    }

    template SPICE_API void bodvrd<FSAngularVelocity>(FSAngularVelocity&, const FName& bodynm, const FName& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void bodvrd<FSDistanceVector>(FSDistanceVector&, const FName& bodynm, const FName& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void bodvrd<FSVelocityVector>(FSVelocityVector&, const FName& bodynm, const FName& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void bodvrd<FSDimensionlessVector>(FSDimensionlessVector&, const FName& bodynm, const FName& item, ES_ResultCode* ResultCode, FString* ErrorMessage);

    template<>
    SPICE_API void bodvrd(
        FSDistance& Value,
        const FString& bodynm,
        const FString& item,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        SpiceDouble _result = Value.AsSpiceDouble();
        SpiceInt n_actual = 0;
        constexpr int n_expected = 1;

        bodvrd_c(TCHAR_TO_ANSI(*bodynm), TCHAR_TO_ANSI(*item), n_expected, &n_actual, &_result);

        Value = FSDistance{ _result };

        ES_ResultCode DummyResultCode;
        FString DummyErrorMessage;

        if (ResultCode == nullptr) ResultCode = &DummyResultCode;
        if (ErrorMessage == nullptr) ErrorMessage = &DummyErrorMessage;

        if (!ErrorCheck(*ResultCode, *ErrorMessage) && n_actual != n_expected)
        {
            *ResultCode = ES_ResultCode::Error;
            *ErrorMessage = FString::Printf(TEXT("Blueprint request for %s_%s Expected double[%d] but proc returned double[%d]"), *bodynm, *item, n_expected, n_actual);
        }
    }

    template<>
    SPICE_API void bodvrd(
        FSDistance& Value,
        const FName& bodynm,
        const FName& item,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        bodvrd<FSDistance>(Value, bodynm.ToString(), item.ToString(), ResultCode, ErrorMessage);
    }

    template<>
    SPICE_API void bodvrd(
        FSMassConstant& Value,
        const FString& bodynm,
        const FString& item,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        SpiceDouble _result = Value.AsSpiceDouble();
        SpiceInt n_actual = 0;
        constexpr int n_expected = 1;

        bodvrd_c(TCHAR_TO_ANSI(*bodynm), TCHAR_TO_ANSI(*item), n_expected, &n_actual, &_result);

        Value = FSMassConstant{ _result };

        ES_ResultCode DummyResultCode;
        FString DummyErrorMessage;

        if (ResultCode == nullptr) ResultCode = &DummyResultCode;
        if (ErrorMessage == nullptr) ErrorMessage = &DummyErrorMessage;

        if (!ErrorCheck(*ResultCode, *ErrorMessage) && n_actual != n_expected)
        {
            *ResultCode = ES_ResultCode::Error;
            *ErrorMessage = FString::Printf(TEXT("Blueprint request for %s_%s Expected double[%d] but proc returned double[%d]"), *bodynm, *item, n_expected, n_actual);
        }
    }

    template<>
    SPICE_API void bodvrd(
        FSMassConstant& Value,
        const FName& bodynm,
        const FName& item,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        return bodvrd<FSMassConstant>(Value, bodynm.ToString(), item.ToString(), ResultCode, ErrorMessage);
    }

    template<>
    SPICE_API void bodvrd(
        double& Value,
        const FString& bodynm,
        const FString& item,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        SpiceDouble _result = Value;
        SpiceInt n_actual = 0;
        constexpr int n_expected = 1;

        bodvrd_c(TCHAR_TO_ANSI(*bodynm), TCHAR_TO_ANSI(*item), n_expected, &n_actual, &_result);

        Value = _result;

        ES_ResultCode DummyResultCode;
        FString DummyErrorMessage;

        if (ResultCode == nullptr) ResultCode = &DummyResultCode;
        if (ErrorMessage == nullptr) ErrorMessage = &DummyErrorMessage;

        if (!ErrorCheck(*ResultCode, *ErrorMessage) && n_actual != n_expected)
        {
            *ResultCode = ES_ResultCode::Error;
            *ErrorMessage = FString::Printf(TEXT("Blueprint request for %s_%s Expected double[%d] but proc returned double[%d]"), *bodynm, *item, n_expected, n_actual);
        }
    }

    template<>
    SPICE_API void bodvrd(
        double& Value,
        const FName& bodynm,
        const FName& item,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        return bodvrd<double>(Value, bodynm.ToString(), item.ToString(), ResultCode, ErrorMessage);
    }

    template<>
    SPICE_API void bodvrd(
        TArray<double>& Values,
        const FString& bodynm,
        const FString& item,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        // Max array dimension... Maybe we should allow the caller to specify size...?
        SpiceDouble _result[256];
        SpiceInt n_actual, n_expected = sizeof(_result) / sizeof(_result[0]);

        ZeroOut(_result);
        bodvrd_c(TCHAR_TO_ANSI(*bodynm), TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);

        Values = TArray<double>();

        ES_ResultCode DummyResultCode;
        FString DummyErrorMessage;

        if (ResultCode == nullptr) ResultCode = &DummyResultCode;
        if (ErrorMessage == nullptr) ErrorMessage = &DummyErrorMessage;

        ErrorCheck(*ResultCode, *ErrorMessage);

        if (*ResultCode == ES_ResultCode::Success)
        {
            Values.Init(0., n_actual);

            check(sizeof(double) == sizeof(SpiceDouble));
            FMemory::Memcpy(Values.GetData(), _result, n_actual * sizeof(SpiceDouble));
        }
    }

    template<>
    SPICE_API void bodvrd(
        TArray<double>& Values,
        const FName& bodynm,
        const FName& item,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        bodvrd<TArray<double>>(Values, bodynm.ToString(), item.ToString(), ResultCode, ErrorMessage);
    }


    template<typename VectorType>
    SPICE_API void MxV(
        const FSRotationMatrix& m,
        const VectorType& vin,
        VectorType& vout
    )
    {
        // Inputs
        SpiceDouble    _m1[3][3];	m.CopyTo(_m1);
        SpiceDouble    _vin[3];		vin.CopyTo(_vin);

        // Outputs
        SpiceDouble    _vout[3];

        // Invocation
        mxv_c(_m1, _vin, _vout);

        // Return Value
        vout = {_vout};
    }

    
    template SPICE_API void MxV<FSAngularVelocity>(const FSRotationMatrix& m, const FSAngularVelocity& vin, FSAngularVelocity& vout);
    template SPICE_API void MxV<FSDistanceVector>(const FSRotationMatrix& m, const FSDistanceVector& vin, FSDistanceVector& vout);
    template SPICE_API void MxV<FSVelocityVector>(const FSRotationMatrix& m, const FSVelocityVector& vin, FSVelocityVector& vout);
    template SPICE_API void MxV<FSDimensionlessVector>(const FSRotationMatrix& m, const FSDimensionlessVector& vin, FSDimensionlessVector& vout);

    template<class VectorType>
    SPICE_API void MxV(
        const FSStateTransform& m,
        const VectorType& vin,
        VectorType& vout
    )
    {
        // Input
        double _m1[6][6];       m.CopyTo(_m1);
        double _v2[6];          vin.CopyTo(_v2);
        SpiceInt    _nrow1 = 6;
        SpiceInt    _nc1r2 = 6;

        // Output
        double _vout[6];

        // Invocation
        mxvg_c(_m1, _v2, _nrow1, _nc1r2, _vout);

        // Pack outputs
        vout = { _vout };
    }

    template SPICE_API void MxV<FSDimensionlessStateVector>(const FSStateTransform& m, const FSDimensionlessStateVector& vin, FSDimensionlessStateVector& vout);
    template SPICE_API void MxV<FSStateVector>(const FSStateTransform& m, const FSStateVector& vin, FSStateVector& vout);

    template<typename VectorType>
    SPICE_API void MTxV(
        const FSRotationMatrix& m,
        const VectorType& vin,
        VectorType& vout
    )
    {
        // Inputs
        SpiceDouble    _m1[3][3];	m.CopyTo(_m1);
        SpiceDouble    _vin[3];		vin.CopyTo(_vin);

        // Outputs
        SpiceDouble    _vout[3];

        // Invocation
        mtxv_c(_m1, _vin, _vout);

        // Return Value
        vout = VectorType{ _vout };
    }

    template SPICE_API void MTxV<FSAngularVelocity>(const FSRotationMatrix& m, const FSAngularVelocity& vin, FSAngularVelocity& vout);
    template SPICE_API void MTxV<FSDistanceVector>(const FSRotationMatrix& m, const FSDistanceVector& vin, FSDistanceVector& vout);
    template SPICE_API void MTxV<FSVelocityVector>(const FSRotationMatrix& m, const FSVelocityVector& vin, FSVelocityVector& vout);
    template SPICE_API void MTxV<FSDimensionlessVector>(const FSRotationMatrix& m, const FSDimensionlessVector& vin, FSDimensionlessVector& vout);

    template<class VectorType>
    SPICE_API void MTxV(
        const FSStateTransform& m,
        const VectorType& vin,
        VectorType& vout
    )
    {
        // Input
        double _m1[6][6];       m.CopyTo(_m1);
        double _v2[6];          vin.CopyTo(_v2);
        constexpr SpiceInt _nrow1 = 6;
        constexpr SpiceInt _nc1r2 = 6;

        // Output
        double _vout[6];

        // Invocation
        mtxvg_c(_m1, _v2, _nrow1, _nc1r2, _vout);

        // Pack outputs
        vout = VectorType{ _vout };
    }

    template SPICE_API void MTxV<FSDimensionlessStateVector>(const FSStateTransform& m, const FSDimensionlessStateVector& vin, FSDimensionlessStateVector& vout);
    template SPICE_API void MTxV<FSStateVector>(const FSStateTransform& m, const FSStateVector& vin, FSStateVector& vout);

    SPICE_API void MxM(const FSRotationMatrix& m1, const FSRotationMatrix& m2, FSRotationMatrix& mout)
    {
        SpiceDouble _m1[3][3];  m1.CopyTo(_m1);
        SpiceDouble _m2[3][3];  m2.CopyTo(_m2);
        SpiceDouble _mout[3][3];

        mxm_c(_m1, _m2, _mout);

        mout = FSRotationMatrix(_mout);
    }

    SPICE_API FSRotationMatrix MxM(const FSRotationMatrix& m1, const FSRotationMatrix& m2)
    {
        FSRotationMatrix mout;
        MxM(m1, m2, mout);
        return mout;
    }

    SPICE_API void MxM(const FSStateTransform& m1, const FSStateTransform& m2, FSStateTransform& mout)
    {
        SpiceDouble _m1[6][6];  m1.CopyTo(_m1);
        SpiceDouble _m2[6][6];  m2.CopyTo(_m2);
        SpiceDouble _mout[6][6];

        constexpr SpiceInt _nrow1 = 6;
        constexpr SpiceInt _ncol1 = 6;
        constexpr SpiceInt _ncol2 = 6;

        mxmg_c(_m1, _m2, _nrow1, _ncol1, _ncol2, _mout);

        mout = FSStateTransform(_mout);
    }

    SPICE_API FSStateTransform MxM(const FSStateTransform& m1, const FSStateTransform& m2)
    {
        FSStateTransform mout;
        MxM(m1, m2, mout);
        return mout;
    }

    SPICE_API void MTxM(const FSRotationMatrix& m1, const FSRotationMatrix& m2, FSRotationMatrix& mout)
    {
        SpiceDouble _m1[3][3];  m1.CopyTo(_m1);
        SpiceDouble _m2[3][3];  m2.CopyTo(_m2);
        SpiceDouble _mout[3][3];

        mtxm_c(_m1, _m2, _mout);

        mout = FSRotationMatrix(_mout);
    }

    SPICE_API FSRotationMatrix MTxM(const FSRotationMatrix& m1, const FSRotationMatrix& m2)
    {
        FSRotationMatrix mout;
        MTxM(m1, m2, mout);
        return mout;
    }

    SPICE_API void MTxM(const FSStateTransform& m1, const FSStateTransform& m2, FSStateTransform& mout)
    {
        SpiceDouble _m1[6][6];  m1.CopyTo(_m1);
        SpiceDouble _m2[6][6];  m2.CopyTo(_m2);
        SpiceDouble _mout[6][6];

        constexpr SpiceInt _nrow1 = 6;
        constexpr SpiceInt _ncol1 = 6;
        constexpr SpiceInt _ncol2 = 6;

        mtxmg_c(_m1, _m2, _nrow1, _ncol1, _ncol2, _mout);

        mout = FSStateTransform(_mout);
    }

    SPICE_API FSStateTransform MTxM(const FSStateTransform& m1, const FSStateTransform& m2)
    {
        FSStateTransform mout;
        MTxM(m1, m2, mout);
        return mout;
    }

    SPICE_API void MxMT(const FSRotationMatrix& m1, const FSRotationMatrix& m2, FSRotationMatrix& mout)
    {
        SpiceDouble _m1[3][3];  m1.CopyTo(_m1);
        SpiceDouble _m2[3][3];  m2.CopyTo(_m2);
        SpiceDouble _mout[3][3];

        mxmt_c(_m1, _m2, _mout);

        mout = FSRotationMatrix(_mout);
    }

    SPICE_API FSRotationMatrix MxMT(const FSRotationMatrix& m1, const FSRotationMatrix& m2)
    {
        FSRotationMatrix mout;
        MxMT(m1, m2, mout);
        return mout;
    }

    SPICE_API void MxMT(const FSStateTransform& m1, const FSStateTransform& m2, FSStateTransform& mout)
    {
        SpiceDouble _m1[6][6];  m1.CopyTo(_m1);
        SpiceDouble _m2[6][6];  m2.CopyTo(_m2);
        SpiceDouble _mout[6][6];

        constexpr SpiceInt _nrow1 = 6;
        constexpr SpiceInt _ncol1 = 6;
        constexpr SpiceInt _ncol2 = 6;

        mxmtg_c(_m1, _m2, _nrow1, _ncol1, _ncol2, _mout);

        mout = FSStateTransform(_mout);
    }

    SPICE_API FSStateTransform MxMT(const FSStateTransform& m1, const FSStateTransform& m2)
    {
        FSStateTransform mout;
        MxMT(m1, m2, mout);
        return mout;
    }

    template<class VectorType>
    SPICE_API void Vadd(const VectorType& v1, const VectorType& v2, VectorType& vsum)
    {
        // Inputs
        SpiceDouble    _v1[3];  v1.CopyTo(_v1);
        SpiceDouble    _v2[3];  v2.CopyTo(_v2);

        // Outputs
        SpiceDouble    _sum[3];  vsum.CopyTo(_sum);

        // Invocation
        vadd_c(_v1, _v2, _sum);

        // Return Value
        vsum = VectorType{ _sum };
    }

    template SPICE_API void Vadd<FSAngularVelocity>(const FSAngularVelocity& v1, const FSAngularVelocity& v2, FSAngularVelocity& vsum);
    template SPICE_API void Vadd<FSDistanceVector>(const FSDistanceVector& v1, const FSDistanceVector& v2, FSDistanceVector& vsum);
    template SPICE_API void Vadd<FSVelocityVector>(const FSVelocityVector& v1, const FSVelocityVector& v2, FSVelocityVector& vsum);
    template SPICE_API void Vadd<FSDimensionlessVector>(const FSDimensionlessVector& v1, const FSDimensionlessVector& v2, FSDimensionlessVector& vsum);


    template<>
    SPICE_API void Vadd(const FSStateVector& v1, const FSStateVector& v2, FSStateVector& sum)
    {
        // Inputs
        constexpr SpiceInt _ndim = 6;
        SpiceDouble    _v1[_ndim];  v1.CopyTo(_v1);
        SpiceDouble    _v2[_ndim];  v2.CopyTo(_v2);

        // Outputs
        SpiceDouble    _sum[_ndim];  sum.CopyTo(_sum);

        // Invocation
        vaddg_c(_v1, _v2, _ndim, _sum);

        // Return Value
        sum = FSStateVector{ _sum };
    }

    template<>
    SPICE_API void Vadd(const FSDimensionlessStateVector& v1, const FSDimensionlessStateVector& v2, FSDimensionlessStateVector& sum)
    {
        // Inputs
        constexpr SpiceInt _ndim = 6;
        SpiceDouble    _v1[_ndim];  v1.CopyTo(_v1);
        SpiceDouble    _v2[_ndim];  v2.CopyTo(_v2);

        // Outputs
        SpiceDouble    _sum[_ndim];  sum.CopyTo(_sum);

        // Invocation
        vaddg_c(_v1, _v2, _ndim, _sum);

        // Return Value
        sum = FSDimensionlessStateVector{ _sum };
    }

    template<class VectorType>
    SPICE_API void Vsub(const VectorType& v1, const VectorType& v2, VectorType& vdifference)
    {
        // Inputs
        SpiceDouble    _v1[3];  v1.CopyTo(_v1);
        SpiceDouble    _v2[3];  v2.CopyTo(_v2);

        // Outputs
        SpiceDouble    _vdifference[3];  vdifference.CopyTo(_vdifference);

        // Invocation
        vsub_c(_v1, _v2, _vdifference);

        // Return Value
        vdifference = VectorType{ _vdifference };
    }


    template SPICE_API void Vsub<FSAngularVelocity>(const FSAngularVelocity& v1, const FSAngularVelocity& v2, FSAngularVelocity&);
    template SPICE_API void Vsub<FSDistanceVector>(const FSDistanceVector& v1, const FSDistanceVector& v2, FSDistanceVector&);
    template SPICE_API void Vsub<FSVelocityVector>(const FSVelocityVector& v1, const FSVelocityVector& v2, FSVelocityVector&);
    template SPICE_API void Vsub<FSDimensionlessVector>(const FSDimensionlessVector& v1, const FSDimensionlessVector& v2, FSDimensionlessVector&);

    template<class VectorType>
    SPICE_API void Vminus(const VectorType& v, VectorType& vminus)
    {
        // Inputs
        SpiceDouble    _v[3];  v.CopyTo(_v);

        // Outputs
        SpiceDouble    _vminus[3];  vminus.CopyTo(_vminus);

        // Invocation
        vminus_c(_v, _vminus);

        // Return Value
        vminus = VectorType{ _vminus };
    }


    template<>
    SPICE_API void Vsub(const FSStateVector& v1, const FSStateVector& v2, FSStateVector& vdifference)
    {
        // Inputs
        constexpr SpiceInt _ndim = 6;
        SpiceDouble    _v1[_ndim];  v1.CopyTo(_v1);
        SpiceDouble    _v2[_ndim];  v2.CopyTo(_v2);

        // Outputs
        SpiceDouble    _vdifference[_ndim];  vdifference.CopyTo(_vdifference);

        // Invocation
        vsubg_c(_v1, _v2, _ndim, _vdifference);

        // Return Value
        vdifference = FSStateVector{ _vdifference };
    }

    template<>
    SPICE_API void Vsub(const FSDimensionlessStateVector& v1, const FSDimensionlessStateVector& v2, FSDimensionlessStateVector& vdifference)
    {
        // Inputs
        constexpr SpiceInt _ndim = 6;
        SpiceDouble    _v1[_ndim];  v1.CopyTo(_v1);
        SpiceDouble    _v2[_ndim];  v2.CopyTo(_v2);

        // Outputs
        SpiceDouble    _vdifference[_ndim];  vdifference.CopyTo(_vdifference);

        // Invocation
        vsubg_c(_v1, _v2, _ndim, _vdifference);

        // Return Value
        vdifference = FSDimensionlessStateVector{ _vdifference };
    }

    template SPICE_API void Vminus<FSAngularVelocity>(const FSAngularVelocity&, FSAngularVelocity&);
    template SPICE_API void Vminus<FSDistanceVector>(const FSDistanceVector&, FSDistanceVector&);
    template SPICE_API void Vminus<FSVelocityVector>(const FSVelocityVector&, FSVelocityVector&);
    template SPICE_API void Vminus<FSDimensionlessVector>(const FSDimensionlessVector&, FSDimensionlessVector&);

    template<>
    SPICE_API void Vminus(const FSStateVector& v, FSStateVector& vminus)
    {
        // Inputs
        constexpr SpiceInt _ndim = 6;
        SpiceDouble    _v[_ndim];  v.CopyTo(_v);

        // Outputs
        SpiceDouble    _vminus[_ndim];  vminus.CopyTo(_vminus);

        // Invocation
        vminug_c(_v, _ndim, _vminus);

        // Return Value
        vminus = FSStateVector{ _vminus };
    }

    template<>
    SPICE_API void Vminus(const FSDimensionlessStateVector& v, FSDimensionlessStateVector& vminus)
    {
        // Inputs
        constexpr SpiceInt _ndim = 6;
        SpiceDouble    _v[_ndim];  v.CopyTo(_v);
        // Outputs
        SpiceDouble    _vminus[_ndim];  vminus.CopyTo(_vminus);

        // Invocation
        vminug_c(_v, _ndim, _vminus);

        // Return Value
        vminus = FSDimensionlessStateVector{ _vminus };
    }
}

