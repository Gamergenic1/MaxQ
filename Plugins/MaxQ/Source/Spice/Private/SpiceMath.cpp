// Copyright 2021 Gamergenic.  See full copyright notice in SpiceK2.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceMath.cpp
// 
// Implementation Comments
// 
// Purpose:  C++ Math stuff
// (like "matrix-transpose times vector" for which there's no c++ operator to
// overload.)
// 
// MaxQ:
// * Base API
// * Refined API
//    * C++
//    * Blueprints
//
// SpiceMath.cpp is part of the "refined C++ API".
//------------------------------------------------------------------------------

#include "SpiceMath.h"
#include "SpiceUtilities.h"
#include <cmath>

PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
extern "C"
{
#include "SpiceUsr.h"
}
PRAGMA_POP_PLATFORM_DEFAULT_PACKING

using namespace MaxQ::Private;

namespace MaxQ::Math
{
    SPICE_API const double pi = (double)pi_c();
    SPICE_API const double halfpi = (double)halfpi_c();
    SPICE_API const double twopi = (double)twopi_c();
    SPICE_API const double dpr = (double)dpr_c();
    SPICE_API const double rpd = (double)rpd_c();

    template<typename VectorType, auto func>
    inline void xV(
        VectorType& vout,
        const FSRotationMatrix& m,
        const VectorType& vin
    )
    {
        // Inputs
        SpiceDouble    _m1[3][3];	m.CopyTo(_m1);
        SpiceDouble    _vin[3];		vin.CopyTo(_vin);

        // Outputs
        SpiceDouble    _vout[3];

        // Invocation
        func(_m1, _vin, _vout);

        // Return Value
        vout = { _vout };
    }

    template<typename VectorType>
    SPICE_API void MxV(
        VectorType& vout,
        const FSRotationMatrix& m,
        const VectorType& vin)
    {
        xV<VectorType,mxv_c>(vout, m, vin);
    }

    
    template SPICE_API void MxV<FSAngularVelocity>(FSAngularVelocity& vout, const FSRotationMatrix& m, const FSAngularVelocity& vin);
    template SPICE_API void MxV<FSDistanceVector>(FSDistanceVector& vout, const FSRotationMatrix& m, const FSDistanceVector& vin);
    template SPICE_API void MxV<FSVelocityVector>(FSVelocityVector& vout, const FSRotationMatrix& m, const FSVelocityVector& vin);
    template SPICE_API void MxV<FSDimensionlessVector>(FSDimensionlessVector& vout, const FSRotationMatrix& m, const FSDimensionlessVector& vin);

    template<typename VectorType, class MatrixType, SpiceInt _nrow1, auto func>
    inline void xV(
        VectorType& vout,
        const MatrixType& m,
        const VectorType& vin
    )
    {
        constexpr SpiceInt _nc1r2 = sizeof VectorType / sizeof SpiceDouble;
        /*
        * Not cool, according to the compiler.
        constexpr SpiceInt _nrow1 = sizeof MatrixType / sizeof VectorType;
        */

        // Input
        double _m1[_nrow1][_nc1r2];  m.CopyTo(_m1);
        double _v2[_nc1r2];          vin.CopyTo(_v2);

        // Output
        double _vout[_nrow1];

        // Invocation
        func(_m1, _v2, _nrow1, _nc1r2, _vout);

        // Pack outputs
        vout = { _vout };
    }

    template<typename VectorType, auto func>
    inline void xV(
        VectorType& vout,
        const FSStateTransform& m,
        const VectorType& vin
    )
    {
        return xV<VectorType, FSStateTransform, 6, func>(vout, m, vin);
    }

    template<class VectorType>
    SPICE_API void MxV(
        VectorType& vout,
        const FSStateTransform& m,
        const VectorType& vin
    )
    {
        return xV<VectorType, mxvg_c>(vout, m, vin);
    }

    template SPICE_API void MxV<FSDimensionlessStateVector>(FSDimensionlessStateVector& vout, const FSStateTransform& m, const FSDimensionlessStateVector& vin);
    template SPICE_API void MxV<FSStateVector>(FSStateVector& vout, const FSStateTransform& m, const FSStateVector& vin);

    template<typename VectorType>
    SPICE_API void MTxV(
        VectorType& vout,
        const FSRotationMatrix& m,
        const VectorType& vin
    )
    {
        xV<VectorType, mtxv_c>(vout, m, vin);
    }

    template SPICE_API void MTxV<FSAngularVelocity>(FSAngularVelocity& vout, const FSRotationMatrix& m, const FSAngularVelocity& vin);
    template SPICE_API void MTxV<FSDistanceVector>(FSDistanceVector& vout, const FSRotationMatrix& m, const FSDistanceVector& vin);
    template SPICE_API void MTxV<FSVelocityVector>(FSVelocityVector& vout, const FSRotationMatrix& m, const FSVelocityVector& vin);
    template SPICE_API void MTxV<FSDimensionlessVector>(FSDimensionlessVector& vout, const FSRotationMatrix& m, const FSDimensionlessVector& vin);

    template<class VectorType>
    SPICE_API void MTxV(
        VectorType& vout,
        const FSStateTransform& m,
        const VectorType& vin
    )
    {
        xV<VectorType, mtxvg_c>(vout, m, vin);
    }

    template SPICE_API void MTxV<FSDimensionlessStateVector>(FSDimensionlessStateVector& vout, const FSStateTransform& m, const FSDimensionlessStateVector& vin);
    template SPICE_API void MTxV<FSStateVector>(FSStateVector& vout, const FSStateTransform& m, const FSStateVector& vin);

    template<auto func>
    inline void xM(FSRotationMatrix& mout, const FSRotationMatrix& m1, const FSRotationMatrix& m2)
    {
        SpiceDouble _m1[3][3];  m1.CopyTo(_m1);
        SpiceDouble _m2[3][3];  m2.CopyTo(_m2);
        SpiceDouble _mout[3][3];

        func(_m1, _m2, _mout);

        mout = FSRotationMatrix(_mout);
    }

    SPICE_API void MxM(FSRotationMatrix& mout, const FSRotationMatrix& m1, const FSRotationMatrix& m2)
    {
        xM<mxm_c>(mout, m1, m2);
    }

    template<auto func>
    inline void xM(FSStateTransform& mout, const FSStateTransform& m1, const FSStateTransform& m2)
    {
        SpiceDouble _m1[6][6];  m1.CopyTo(_m1);
        SpiceDouble _m2[6][6];  m2.CopyTo(_m2);
        SpiceDouble _mout[6][6];

        constexpr SpiceInt _nrow1 = 6;
        constexpr SpiceInt _ncol1 = 6;
        constexpr SpiceInt _ncol2 = 6;

        func(_m1, _m2, _nrow1, _ncol1, _ncol2, _mout);

        mout = FSStateTransform(_mout);
    }


    SPICE_API void MxM(FSStateTransform& mout, const FSStateTransform& m1, const FSStateTransform& m2)
    {
        xM<mxmg_c>(mout, m1, m2);
    }

    SPICE_API void MTxM(FSRotationMatrix& mout, const FSRotationMatrix& m1, const FSRotationMatrix& m2)
    {
        xM<mtxm_c>(mout, m1, m2);
    }

    SPICE_API void MTxM(FSStateTransform& mout, const FSStateTransform& m1, const FSStateTransform& m2)
    {
        xM<mtxmg_c>(mout, m1, m2);
    }

    SPICE_API void MxMT(FSRotationMatrix& mout, const FSRotationMatrix& m1, const FSRotationMatrix& m2)
    {
        xM<mxmt_c>(mout, m1, m2);
    }

    SPICE_API void MxMT(FSStateTransform& mout, const FSStateTransform& m1, const FSStateTransform& m2)
    {
        xM<mxmtg_c>(mout, m1, m2);
    }

    template<class VectorType, auto func>
    inline void v3op(VectorType& vout, const VectorType& v)
    {
        // Inputs
        SpiceDouble    _v[3];  v.CopyTo(_v);

        // Outputs
        SpiceDouble    _vout[3];  vout.CopyTo(_vout);

        // Invocation
        func(_v, _vout);

        // Return Value
        vout = VectorType{ _vout };
    }


    template<class VOutType, class V1Type, class V2Type, auto func>
    inline void v3op(VOutType& vout, const V1Type& v1, const V2Type& v2)
    {
        // Inputs
        SpiceDouble    _v1[3];  v1.CopyTo(_v1);
        SpiceDouble    _v2[3];  v2.CopyTo(_v2);

        // Outputs
        SpiceDouble    _vout[3];  vout.CopyTo(_vout);

        // Invocation
        func(_v1, _v2, _vout);

        // Return Value
        vout = VOutType{ _vout };
    }

    template<class VectorType, auto func>
    inline void v3op(VectorType& vout, const VectorType& v1, const VectorType& v2)
    {
        v3op<VectorType,VectorType,VectorType,func>(vout, v1, v2);
    }

    template<class VectorType>
    SPICE_API void Vadd(VectorType& vsum, const VectorType& v1, const VectorType& v2)
    {
        v3op<VectorType,vadd_c>(vsum, v1, v2);
    }

    template SPICE_API void Vadd<FSAngularVelocity>(FSAngularVelocity&, const FSAngularVelocity&, const FSAngularVelocity&);
    template SPICE_API void Vadd<FSDistanceVector>(FSDistanceVector&, const FSDistanceVector&, const FSDistanceVector&);
    template SPICE_API void Vadd<FSVelocityVector>(FSVelocityVector&, const FSVelocityVector&, const FSVelocityVector&);
    template SPICE_API void Vadd<FSDimensionlessVector>(FSDimensionlessVector&, const FSDimensionlessVector&, const FSDimensionlessVector&);

    template<class VectorType, auto func>
    inline void v6op(VectorType& vout, const VectorType& v)
    {
        // Inputs
        constexpr SpiceInt _ndim = 6;
        SpiceDouble    _v[_ndim];  v.CopyTo(_v);

        // Outputs
        SpiceDouble    _vout[_ndim];  vout.CopyTo(_vout);

        // Invocation
        func(_v, _ndim, _vout);

        // Return Value
        vout = VectorType{ _vout };
    }

    template<class VectorType, auto func>
    inline void v6op(VectorType& sum, const VectorType& v1, const VectorType& v2)
    {
        // Inputs
        constexpr SpiceInt _ndim = 6;
        SpiceDouble    _v1[_ndim];  v1.CopyTo(_v1);
        SpiceDouble    _v2[_ndim];  v2.CopyTo(_v2);

        // Outputs
        SpiceDouble    _sum[_ndim];  sum.CopyTo(_sum);

        // Invocation
        func(_v1, _v2, _ndim, _sum);

        // Return Value
        sum = VectorType{ _sum };
    }

    template<>
    SPICE_API void Vadd(FSStateVector& sum, const FSStateVector& v1, const FSStateVector& v2)
    {
        v6op<FSStateVector,vaddg_c>(sum, v1, v2);
    }

    template<>
    SPICE_API void Vadd(FSDimensionlessStateVector& sum, const FSDimensionlessStateVector& v1, const FSDimensionlessStateVector& v2)
    {
        v6op<FSDimensionlessStateVector, vaddg_c>(sum, v1, v2);
    }

    template<class VectorType>
    SPICE_API void Vsub(VectorType& vdifference, const VectorType& v1, const VectorType& v2)
    {
        v3op<VectorType, vsub_c>(vdifference, v1, v2);
    }


    template SPICE_API void Vsub<FSAngularVelocity>(FSAngularVelocity&, const FSAngularVelocity&, const FSAngularVelocity&);
    template SPICE_API void Vsub<FSDistanceVector>(FSDistanceVector&, const FSDistanceVector&, const FSDistanceVector&);
    template SPICE_API void Vsub<FSVelocityVector>(FSVelocityVector&, const FSVelocityVector&, const FSVelocityVector&);
    template SPICE_API void Vsub<FSDimensionlessVector>(FSDimensionlessVector&, const FSDimensionlessVector&, const FSDimensionlessVector&);

    template<>
    SPICE_API void Vsub(FSStateVector& vdifference, const FSStateVector& v1, const FSStateVector& v2)
    {
        v6op<FSStateVector, vsubg_c>(vdifference, v1, v2);
    }

    template<>
    SPICE_API void Vsub(FSDimensionlessStateVector& vdifference, const FSDimensionlessStateVector& v1, const FSDimensionlessStateVector& v2)
    {
        v6op<FSDimensionlessStateVector, vsubg_c>(vdifference, v1, v2);
    }

    template<class VectorType>
    SPICE_API void Vminus(VectorType& vminus, const VectorType& v)
    {
        v3op<VectorType, vminus_c>(vminus, v);
    }

    template SPICE_API void Vminus<FSAngularVelocity>(FSAngularVelocity&, const FSAngularVelocity&);
    template SPICE_API void Vminus<FSDistanceVector>(FSDistanceVector&, const FSDistanceVector&);
    template SPICE_API void Vminus<FSVelocityVector>(FSVelocityVector&, const FSVelocityVector&);
    template SPICE_API void Vminus<FSDimensionlessVector>(FSDimensionlessVector&, const FSDimensionlessVector&);

    template<>
    SPICE_API void Vminus(FSStateVector& vminus, const FSStateVector& v)
    {
        v6op<FSStateVector, vminug_c>(vminus, v);
    }

    template<>
    SPICE_API void Vminus(FSDimensionlessStateVector& vminus, const FSDimensionlessStateVector& v)
    {
        v6op<FSDimensionlessStateVector, vminug_c>(vminus, v);
    }

    template<class ParamRateType, class ParamType>
    SPICE_API void Qderiv(ParamRateType& dfdt, const ParamType& f0, const ParamType& f2, double delta)
    {
        constexpr SpiceInt _ndim{ 3 };
        SpiceDouble    _f0[3];      f0.CopyTo(_f0);
        SpiceDouble    _f2[3];      f2.CopyTo(_f2);
        SpiceDouble _delta = delta;

        SpiceDouble    _dfdt[3];
        qderiv_c(_ndim, _f0, _f2, _delta, _dfdt);

        dfdt = ParamRateType{_dfdt};
    }

    template SPICE_API void Qderiv<FSVelocityVector, FSDistanceVector>(FSVelocityVector& dfdt, const FSDistanceVector& f0, const FSDistanceVector& f2, double delta);
    template SPICE_API void Qderiv<FSDimensionlessVector, FSDimensionlessVector>(FSDimensionlessVector& dfdt, const FSDimensionlessVector& f0, const FSDimensionlessVector& f2, double delta);

    template<>
    SPICE_API void Qderiv(FSSpeed& dfdt, const FSDistance& f0, const FSDistance& f2, double delta)
    {
        constexpr SpiceInt _ndim{ 1 };
        SpiceDouble    _f0 = f0.AsSpiceDouble();
        SpiceDouble    _f2 = f2.AsSpiceDouble();
        SpiceDouble _delta = delta;

        SpiceDouble    _dfdt;
        qderiv_c(_ndim, &_f0, &_f2, _delta, &_dfdt);

        dfdt = FSSpeed{ _dfdt };
    }

    template<>
    SPICE_API void Qderiv(double& dfdt, const double& f0, const double& f2, double delta)
    {
        constexpr SpiceInt _ndim{ 1 };
        SpiceDouble    _f0 = f0;
        SpiceDouble    _f2 = f2;
        SpiceDouble _delta = delta;

        SpiceDouble    _dfdt;
        qderiv_c(_ndim, &_f0, &_f2, _delta, &_dfdt);

        dfdt = double{ _dfdt };
    }

    template<>
    SPICE_API void Qderiv(TArray<double>& dfdt, const TArray<double>& f0, const TArray<double>& f2, double delta)
    {
        const SpiceInt _ndim{ FMath::Min(f0.Num(), f2.Num()) };
        ConstSpiceDouble* _f0 = f0.GetData();
        ConstSpiceDouble* _f2 = f2.GetData();
        SpiceDouble _delta = delta;
        dfdt.Init(0, _ndim);

        SpiceDouble*   _dfdt = dfdt.GetData();
        qderiv_c(_ndim, _f0, _f2, _delta, _dfdt);
    }

    SPICE_API void TwoVec(
        FSRotationMatrix& m,
        ES_Axis axisa,
        const FSDimensionlessVector& axdef,
        ES_Axis axisp,
        const FSDimensionlessVector& plndef,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        SpiceDouble _axdef[3];   axdef.CopyTo(_axdef);
        SpiceInt    _indexa = (SpiceInt)axisa;
        SpiceDouble _plndef[3];  plndef.CopyTo(_plndef);
        SpiceInt    _indexp = (SpiceInt)axisp;

        SpiceDouble _mout[3][3];

        twovec_c(_axdef, _indexa, _plndef, _indexp, _mout);

        m = { FSRotationMatrix(_mout) };

        ErrorCheck(ResultCode, ErrorMessage);
    }

    SPICE_API void TwoVXF(
        FSStateTransform& m,
        ES_Axis axisa,
        const FSDimensionlessStateVector& axdef,
        ES_Axis axisp,
        const FSDimensionlessStateVector& plndef,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        SpiceDouble _axdef[6];   axdef.CopyTo(_axdef);
        SpiceInt    _indexa = (SpiceInt)axisa;
        SpiceDouble _plndef[6];  plndef.CopyTo(_plndef);
        SpiceInt    _indexp = (SpiceInt)axisp;

        SpiceDouble _mout[6][6];

        twovxf_c(_axdef, _indexa, _plndef, _indexp, _mout);

        m = { FSStateTransform(_mout) };

        ErrorCheck(ResultCode, ErrorMessage);
    }

    template<class VectorType>
    SPICE_API void Ucrss(VectorType& vout, const VectorType& v1, const VectorType& v2)
    {
        return v3op<VectorType, ucrss_c>(vout, v1, v2);
    }

    template SPICE_API void Ucrss<FSAngularVelocity>(FSAngularVelocity&, const FSAngularVelocity&, const FSAngularVelocity&);
    template SPICE_API void Ucrss<FSDistanceVector>(FSDistanceVector&, const FSDistanceVector&, const FSDistanceVector&);
    template SPICE_API void Ucrss<FSVelocityVector>(FSVelocityVector&, const FSVelocityVector&, const FSVelocityVector&);
    template SPICE_API void Ucrss<FSDimensionlessVector>(FSDimensionlessVector&, const FSDimensionlessVector&, const FSDimensionlessVector&);

    SPICE_API void Ucrss(FSDimensionlessVector& vout, const FSDistanceVector& v1, const FSVelocityVector& v2)
    {
        return v3op<FSDimensionlessVector, FSDistanceVector, FSVelocityVector, ucrss_c>(vout, v1, v2);
    }

    template<class ScalarType, class VectorType>
    inline void Unorm(FSDimensionlessVector& vout, ScalarType& vmag, const VectorType& v)
    {
        // input
        SpiceDouble  _v1[3];    v.CopyTo(_v1);
        // Outputs
        SpiceDouble  _vout[3]; vout.CopyTo(_vout);
        SpiceDouble _vmag = static_cast<double>(vmag);

        // Invocation
        unorm_c(_v1, _vout, &_vmag);

        // Return Value
        vout = FSDimensionlessVector(_vout);
        vmag = { ScalarType(_vmag) };
    }

    SPICE_API void Unorm(FSDimensionlessVector& vout, FSDistance& vmag, const FSDistanceVector& v) { Unorm<FSDistance, FSDistanceVector>(vout, vmag, v); }
    SPICE_API void Unorm(FSDimensionlessVector& vout, FSSpeed& vmag, const FSVelocityVector& v) { Unorm<FSSpeed, FSVelocityVector>(vout, vmag, v); }
    SPICE_API void Unorm(FSDimensionlessVector& vout, FSAngularRate& vmag, const FSAngularVelocity& v) { Unorm<FSAngularRate, FSAngularVelocity>(vout, vmag, v); }
    SPICE_API void Unorm(FSDimensionlessVector& vout, double& vmag, const FSDimensionlessVector& v) { Unorm<double, FSDimensionlessVector>(vout, vmag, v); };

    template<class VectorType>
    SPICE_API void Vlcom(VectorType& sum, double a, const VectorType& v1, double b, const VectorType& v2)
    {
        ConstSpiceDouble _a{ a };
        SpiceDouble _v1[3]; v1.CopyTo(_v1);
        ConstSpiceDouble _b{ b };
        SpiceDouble _v2[3]; v2.CopyTo(_v2);
        SpiceDouble _sum[3]; sum.CopyTo(_sum);

        vlcom_c(_a, _v1, _b, _v2, _sum);

        sum = { _sum };
    }

    template SPICE_API void Vlcom<FSAngularVelocity>(FSAngularVelocity&, double, const FSAngularVelocity&, double, const FSAngularVelocity&);
    template SPICE_API void Vlcom<FSDistanceVector>(FSDistanceVector&, double, const FSDistanceVector&, double, const FSDistanceVector&);
    template SPICE_API void Vlcom<FSVelocityVector>(FSVelocityVector&, double, const FSVelocityVector&, double, const FSVelocityVector&);
    template SPICE_API void Vlcom<FSDimensionlessVector>(FSDimensionlessVector&, double, const FSDimensionlessVector&, double, const FSDimensionlessVector&);

    template<class VectorType, SpiceInt N>
    inline void vlcomN(VectorType& sum, double a, const VectorType& v1, double b, const VectorType& v2)
    {
        ConstSpiceDouble _a{ a };
        SpiceDouble _v1[N]; v1.CopyTo(_v1);
        ConstSpiceDouble _b{ b };
        SpiceDouble _v2[N]; v2.CopyTo(_v2);
        SpiceDouble _sum[N]; sum.CopyTo(_sum);

        vlcomg_c(N, _a, _v1, _b, _v2, _sum);

        sum = { _sum };
    }

    template<>
    SPICE_API void Vlcom(FSDimensionlessStateVector& sum, double a, const FSDimensionlessStateVector& v1, double b, const FSDimensionlessStateVector& v2)
    {
        return vlcomN<FSDimensionlessStateVector,6>(sum, a, v1, b, v2);
    }

    template<>
    SPICE_API void Vlcom(FSStateVector& sum, double a, const FSStateVector& v1, double b, const FSStateVector& v2)
    {
        return vlcomN<FSStateVector, 6>(sum, a, v1, b, v2);
    }

    template<class VectorType>
    SPICE_API void Vlcom3(VectorType& sum, double a, const VectorType& v1, double b, const VectorType& v2, double c, const VectorType& v3)
    {
        ConstSpiceDouble _a{ a };
        SpiceDouble _v1[3]; v1.CopyTo(_v1);
        ConstSpiceDouble _b{ b };
        SpiceDouble _v2[3]; v2.CopyTo(_v2);
        ConstSpiceDouble _c{ c };
        SpiceDouble _v3[3]; v3.CopyTo(_v3);
        SpiceDouble _sum[3]; sum.CopyTo(_sum);

        vlcom3_c(_a, _v1, _b, _v2, _c, _v3, _sum);

        sum = { _sum };
    }

    template SPICE_API void Vlcom3<FSAngularVelocity>(FSAngularVelocity&, double, const FSAngularVelocity&, double, const FSAngularVelocity&, double, const FSAngularVelocity&);
    template SPICE_API void Vlcom3<FSDistanceVector>(FSDistanceVector&, double, const FSDistanceVector&, double, const FSDistanceVector&, double, const FSDistanceVector&);
    template SPICE_API void Vlcom3<FSVelocityVector>(FSVelocityVector&, double, const FSVelocityVector&, double, const FSVelocityVector&, double, const FSVelocityVector&);
    template SPICE_API void Vlcom3<FSDimensionlessVector>(FSDimensionlessVector&, double, const FSDimensionlessVector&, double, const FSDimensionlessVector&, double, const FSDimensionlessVector&);

    SPICE_API void M2q(
        FSQuaternion& q,
        const FSRotationMatrix& r,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
        )
    {
        SpiceDouble _r[3][3];  r.CopyTo(_r);
        SpiceDouble _q[4];  q.CopyTo(_q);
        m2q_c(_r, _q);

        q = FSQuaternion(_q);

        // Error Handling
        ErrorCheck(ResultCode, ErrorMessage);
    }

    SPICE_API void Q2m(
        FSRotationMatrix& r,
        const FSQuaternion& q
        )
    {
        SpiceDouble _r[3][3];
        SpiceDouble _q[4];
        q.CopyTo(_q);

        q2m_c(_q, _r);

        r = FSRotationMatrix(_r);
    }

    SPICE_API void QxQ(
        FSQuaternion& qout,
        const FSQuaternion& q1,
        const FSQuaternion& q2
        )
    {
        SpiceDouble _qout[4];
        SpiceDouble _q1[4];  q1.CopyTo(_q1);
        SpiceDouble _q2[4];  q2.CopyTo(_q2);

        qxq_c(_q1, _q2, _qout);
        qout = FSQuaternion(_qout);
    }


    SPICE_API double normalize0to360(double degrees)
    {
        // First, normalize 0-360
        degrees = std::fmod(degrees, 360);

        // Pull up negative values
        if (degrees < 0.)
        {
            degrees += 360.;
        }

        return degrees;
    }

    SPICE_API double normalize180to180(double degrees)
    {
        // First normalize 0 - 360
        degrees = normalize0to360(degrees);

        // Wrap around if need be.
        if (degrees > 180.) degrees -= 360.;

        return degrees;
    }


    SPICE_API double normalizeZeroToTwoPi(double radians)
    {
        // First, normalize 0-360
        radians = std::fmod(radians, twopi);

        // Pull up negative values
        if (radians < 0.)
        {
            radians += twopi;
        }

        return radians;
    }

    SPICE_API double normalizePiToPi(double radians)
    {
        // First normalize 0 - 360
        radians = normalizeZeroToTwoPi(radians);

        // Wrap around if need be.
        if (radians > pi) radians -= twopi;

        return radians;
    }
}
