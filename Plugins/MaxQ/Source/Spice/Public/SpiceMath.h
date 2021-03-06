// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceMath.h
// 
// API Comments
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
// SpiceMath.h is part of the "refined C++ API".
//------------------------------------------------------------------------------

#pragma once

#include "SpiceTypes.h"

namespace MaxQ::Math
{
    // Values from CSPICE Toolkit
    // Which is why they're const, instead of constexpr.
    SPICE_API extern const double pi;
    SPICE_API extern const double halfpi;
    SPICE_API extern const double twopi;
    SPICE_API extern const double dpr;
    SPICE_API extern const double rpd;

    // m * v
    template<class VectorType>
    SPICE_API void MxV(VectorType& vout, const FSRotationMatrix& m, const VectorType& v);

    template<class VectorType>
    inline VectorType MxV(const FSRotationMatrix& m, const VectorType& v)
    {
        VectorType vout;
        MxV(vout, m, v);
        return vout;
    }

    template<class VectorType>
    SPICE_API void MxV(VectorType& vout, const FSStateTransform& m, const VectorType& v);

    template<class VectorType>
    inline VectorType MxV(const FSStateTransform& m, const VectorType& v)
    {
        VectorType vout;
        MxV(vout, m, v);
        return vout;
    }

    // m_transpose * v
    template<class VectorType>
    SPICE_API void MTxV(VectorType& vout, const FSRotationMatrix& m, const VectorType& v);

    template<class VectorType>
    inline VectorType MTxV(const FSRotationMatrix& m, const VectorType& v)
    {
        VectorType vout;
        MTxV(vout, m, v);
        return vout;
    }

    template<class VectorType>
    SPICE_API void MTxV(VectorType& vout, const FSStateTransform& m, const VectorType& v);

    template<class VectorType>
    inline VectorType MTxV(const FSStateTransform& m, const VectorType& v)
    {
        VectorType vout;
        MTxV(vout, m, v);
        return vout;
    }


    // m * m
    SPICE_API void MxM(FSRotationMatrix& mout, const FSRotationMatrix& m1, const FSRotationMatrix& m2);
    
    inline FSRotationMatrix MxM(const FSRotationMatrix& m1, const FSRotationMatrix& m2)
    {
        FSRotationMatrix mout;
        MxM(mout, m1, m2);
        return mout;
    }
    SPICE_API void MxM(FSStateTransform& mout, const FSStateTransform& m1, const FSStateTransform& m2);
    inline FSStateTransform MxM(const FSStateTransform& m1, const FSStateTransform& m2)
    {
        FSStateTransform mout;
        MxM(mout, m1, m2);
        return mout;
    }

    // m_transpose * m
    SPICE_API void MTxM(FSRotationMatrix& mout, const FSRotationMatrix& m1, const FSRotationMatrix& m2);
    inline FSRotationMatrix MTxM(const FSRotationMatrix& m1, const FSRotationMatrix& m2)
    {
        FSRotationMatrix mout;
        MTxM(mout, m1, m2);
        return mout;
    }
    SPICE_API void MTxM(FSStateTransform& mout, const FSStateTransform& m1, const FSStateTransform& m2);
    inline FSStateTransform MTxM(const FSStateTransform& m1, const FSStateTransform& m2)
    {
        FSStateTransform mout;
        MTxM(mout, m1, m2);
        return mout;
    }

    // m * m_transpose
    SPICE_API void MxMT(FSRotationMatrix& mout, const FSRotationMatrix& m1, const FSRotationMatrix& m2);
    inline FSRotationMatrix MxMT(const FSRotationMatrix& m1, const FSRotationMatrix& m2)
    {
        FSRotationMatrix mout;
        MxMT(mout, m1, m2);
        return mout;
    }
    SPICE_API void MxMT(FSStateTransform& mout, const FSStateTransform& m1, const FSStateTransform& m2);
    inline FSStateTransform MxMT(const FSStateTransform& m1, const FSStateTransform& m2)
    {
        FSStateTransform mout;
        MxMT(mout, m1, m2);
        return mout;
    }

    // addition
    template<class VectorType>
    SPICE_API void Vadd(VectorType& vsum, const VectorType& v1, const VectorType& v2);

    template<class VectorType>
    inline VectorType Vadd(const VectorType& v1, const VectorType& v2)
    {
        VectorType vsum;
        Vadd(vsum, v1, v2);
        return vsum;
    }

    // return unit normal
    template<class VectorType>
    SPICE_API void Vhat(FSDimensionlessVector& vhat, const VectorType& vin);

    template<class VectorType>
    inline FSDimensionlessVector Vhat(const VectorType& vin)
    {
        FSDimensionlessVector vhat;
        Vhat(vhat, vin);
        return vhat;
    }

    // norm (magnitude)
    SPICE_API void Vnorm(double& vnorm, const FSDimensionlessVector& v);
    inline void Vnorm(FSDistance& vnorm, const FSDistanceVector& v) { double norm; Vnorm(norm, v.AsDimensionlessVector()); vnorm = norm;}
    inline void Vnorm(FSSpeed& vnorm, const FSVelocityVector& v)    { double norm; Vnorm(norm, v.AsDimensionlessVector()); vnorm = norm; }
    inline void Vnorm(FSAngularRate& vnorm, const FSAngularVelocity& v) { double norm; Vnorm(norm, v.AsDimensionlessVector()); vnorm = norm; }

    inline double Vnorm(const FSDimensionlessVector& v) { double norm; Vnorm(norm, v); return norm; }
    inline FSDistance Vnorm(const FSDistanceVector& v) { FSDistance norm; Vnorm(norm, v); return norm; }
    inline FSSpeed Vnorm(const FSVelocityVector& v) { FSSpeed norm; Vnorm(norm, v); return norm; }
    inline FSAngularRate Vnorm(const FSAngularVelocity& v) { FSAngularRate norm; Vnorm(norm, v); return norm; }

    // subtraction
    template<class VectorType>
    SPICE_API void Vsub(VectorType& vdifference, const VectorType& v1, const VectorType& v2);

    template<class VectorType>
    inline VectorType Vsub(const VectorType& v1, const VectorType& v2)
    {
        VectorType vdifference;
        Vsub(vdifference, v1, v2);
        return vdifference;
    }

    // "relative distance"
    //             || v1 - v2 ||
    // vrel = ------------------------
    //        max(|| v1 ||, || v2 || )
    SPICE_API void Vrel(double& vrel, const FSDimensionlessVector& v1, const FSDimensionlessVector& v2);
    inline void Vrel(FSDistance& vrel, const FSDistanceVector& v1, const FSDistanceVector& v2) { double vout; Vrel(vout, v1.AsDimensionlessVector(), v2.AsDimensionlessVector()); vrel = vout; }
    inline void Vrel(FSSpeed& vrel, const FSVelocityVector& v1, const FSVelocityVector& v2) { double vout; Vrel(vout, v1.AsDimensionlessVector(), v2.AsDimensionlessVector()); vrel = vout; }
    inline void Vrel(FSAngularRate& vrel, const FSAngularVelocity& v1, const FSAngularVelocity& v2) { double vout; Vrel(vout, v1.AsDimensionlessVector(), v2.AsDimensionlessVector()); vrel = vout; }

    inline double Vrel(const FSDimensionlessVector& v1, const FSDimensionlessVector& v2) { double vrel; Vrel(vrel, v1, v2); return vrel; }
    inline FSDistance Vrel(const FSDistanceVector& v1, const FSDistanceVector& v2) { FSDistance vrel; Vrel(vrel, v1, v2); return vrel; }
    inline FSSpeed Vrel(const FSVelocityVector& v1, const FSVelocityVector& v2) { FSSpeed vrel; Vrel(vrel, v1, v2); return vrel; }
    inline FSAngularRate Vrel(const FSAngularVelocity& v1, const FSAngularVelocity& v2) { FSAngularRate vrel; Vrel(vrel, v1, v2); return vrel; }

    // negation
    template<class VectorType>
    SPICE_API void Vminus(VectorType& vminus, const VectorType& vin);

    template<class VectorType>
    inline VectorType Vminus(const VectorType& vin)
    {
        VectorType vminus;
        Vminus(vminus, vin);
        return vminus;
    }

    template<class ParamRateType, class ParamType>
    SPICE_API void Qderiv(ParamRateType& dfdt, const ParamType& f0, const ParamType& f2, double delta);

    template<class ParamRateType, class ParamType>
    inline ParamRateType Qderiv(const ParamType& f0, const ParamType& f2, double delta)
    {
        ParamRateType dfdt;
        Qderiv(dfdt, f0, f2, delta);
        return dfdt;
    }

    SPICE_API void TwoVec(
        FSRotationMatrix& m,
        ES_Axis axisa,
        const FSDimensionlessVector& axdef,
        ES_Axis axisp,
        const FSDimensionlessVector& plndef,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    );

    inline FSRotationMatrix TwoVec(
        ES_Axis axisa,
        const FSDimensionlessVector& axdef,
        ES_Axis axisp,
        const FSDimensionlessVector& plndef,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
        )
    {
        FSRotationMatrix m;
        TwoVec(m, axisa, axdef, axisp, plndef, ResultCode, ErrorMessage);
        return m;
    }

    SPICE_API void TwoVXF(
        FSStateTransform& m,
        ES_Axis axisa,
        const FSDimensionlessStateVector& axdef,
        ES_Axis axisp,
        const FSDimensionlessStateVector& plndef,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    );

    inline FSStateTransform TwoVXF(
        ES_Axis axisa,
        const FSDimensionlessStateVector& axdef,
        ES_Axis axisp,
        const FSDimensionlessStateVector& plndef,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    )
    {
        FSStateTransform m;
        TwoVXF(m, axisa, axdef, axisp, plndef, ResultCode, ErrorMessage);
        return m;
    }


    // unit cross product
    template<class VectorType>
    SPICE_API void Ucrss(VectorType& vout, const VectorType& v1, const VectorType& v2);

    template<class VectorType>
    inline VectorType Ucrss(const VectorType& v1, const VectorType& v2)
    {
        VectorType vout;
        Ucrss(vout, v1, v2);
        return vout;
    }

    SPICE_API void Ucrss(FSDimensionlessVector& vout, const FSDistanceVector& r, const FSVelocityVector& v);
    inline FSDimensionlessVector Ucrss(const FSDistanceVector& r, const FSVelocityVector& v)
    {
        FSDimensionlessVector vout;
        Ucrss(vout, r, v);
        return vout;
    }

    inline void Ucrss(FSDimensionlessVector& vout, const FSStateVector& state) { Ucrss(vout, state.r, state.v); }
    inline FSDimensionlessVector Ucrss(const FSStateVector& state) { return Ucrss(state.r, state.v); }

    // vector cross product
    template<class VectorType>
    SPICE_API void Vcrss(VectorType& vout, const VectorType& v1, const VectorType& v2);

    template<class VectorType>
    inline VectorType Vcrss(const VectorType& v1, const VectorType& v2)
    {
        VectorType vout;
        Vcrss(vout, v1, v2);
        return vout;
    }

    SPICE_API void Vcrss(FSDimensionlessVector& vout, const FSDistanceVector& r, const FSVelocityVector& v);
    inline FSDimensionlessVector Vcrss(const FSDistanceVector& r, const FSVelocityVector& v)
    {
        FSDimensionlessVector vout;
        Vcrss(vout, r, v);
        return vout;
    }

    inline void Vcrss(FSDimensionlessVector& vout, const FSStateVector& state) { Vcrss(vout, state.r, state.v); }
    inline FSDimensionlessVector Vcrss(const FSStateVector& state) { return Vcrss(state.r, state.v); }

    SPICE_API void Vdist(
        double& dist,
        const FSDimensionlessVector& v1,
        const FSDimensionlessVector& v2
    );

    inline double Vdist(
        const FSDimensionlessVector& v1,
        const FSDimensionlessVector& v2
    )
    {
        double dist;
        Vdist(dist, v1, v2);
        return dist;
    }

    template<class OutputType, class VectorType>
    SPICE_API void Vdist(
        OutputType& dist,
        const VectorType& v1,
        const VectorType& v2
    );

    template<class ScalarType, class VectorType>
    inline ScalarType Vdist(const VectorType& v1, const VectorType& v2)
    {
        ScalarType sout;
        Vdist(sout, v1, v2);
        return sout;
    }

    SPICE_API void Vdot(
        double& dot,
        const FSDimensionlessVector& v1,
        const FSDimensionlessVector& v2
    );

    inline double Vdot(
        const FSDimensionlessVector& v1,
        const FSDimensionlessVector& v2
    )
    {
        double vdot;
        Vdot(vdot, v1, v2);
        return vdot;
    }

    template<class ScalarType, class VectorType>
    SPICE_API void Vdot(
        ScalarType& dot,
        const VectorType& v1,
        const VectorType& v2
    );

    template<class ScalarType, class VectorType>
    inline ScalarType Vdot(const VectorType& v1, const VectorType& v2)
    {
        ScalarType sout;
        Vdot(sout, v1, v2);
        return sout;
    }

    template<class VectorType>
    SPICE_API void Vperp(VectorType& vout, const VectorType& v1, const VectorType& v2);

    template<class VectorType>
    inline VectorType Vperp(const VectorType& v1, const VectorType& v2)
    {
        VectorType vout;
        Vperp(vout, v1, v2);
        return vout;
    }

    template<class VectorType>
    SPICE_API void Vprjp(VectorType& vout, const VectorType& v1, const FSPlane& plane);

    template<class VectorType>
    inline VectorType Vprjp(const VectorType& v1, const FSPlane& plane)
    {
        VectorType vout;
        Vprjp(vout, v1, plane);
        return vout;
    }

    template<class VectorType>
    SPICE_API void Vproj(VectorType& vout, const VectorType& v1, const VectorType& v2);

    template<class VectorType>
    inline VectorType Vproj(const VectorType& v1, const VectorType& v2)
    {
        VectorType vout;
        Vproj(vout, v1, v2);
        return vout;
    }

    // scale
    template<class VectorType>
    SPICE_API void Vscl(VectorType& vscaled, double s, const VectorType& v);

    template<class VectorType>
    inline VectorType Vscl(double s, const VectorType& v)
    {
        VectorType vscaled;
        Vscl(vscaled, s, v);
        return vscaled;
    }


    template<class VectorType>
    SPICE_API void Vsep(FSAngle& angle, const VectorType& v1, const VectorType& v2);

    template<class VectorType>
    inline FSAngle Vsep(const VectorType& v1, const VectorType& v2)
    {
        FSAngle angle;
        Vsep(angle, v1, v2);
        return angle;
    }

    template<typename ScalarType, typename VectorType>
    SPICE_API void VTxMxV(
        ScalarType& sout,
        const VectorType& v1,
        const FSRotationMatrix& m,
        const VectorType& v2
    );

    template<class ScalarType, class VectorType>
    inline ScalarType VTxMxV(
    const VectorType& v1,
        const FSRotationMatrix& m,
        const VectorType& v2
    )
    {
        ScalarType sout;
        VTxMxV(sout, v1, m, v2);
        return sout;
    }

    inline void VTxMxV(
        double& sout,
        const FSDimensionlessVector& v1,
        const FSRotationMatrix& m,
        const FSDimensionlessVector& v2
    )
    {
        VTxMxV<double, FSDimensionlessVector>(sout, v1, m, v2);
    }

    inline double VTxMxV(
        const FSDimensionlessVector& v1,
        const FSRotationMatrix& m,
        const FSDimensionlessVector& v2
    )
    {
        return VTxMxV<double, FSDimensionlessVector>(v1, m, v2);
    }


    template<typename VectorType>
    SPICE_API void VTxMxV(
        double& sout,
        const VectorType& v1,
        const FSStateTransform& m,
        const VectorType& v2
    );

    template<class VectorType>
    inline double VTxMxV(
        const VectorType& v1,
        const FSStateTransform& m,
        const VectorType& v2
    )
    {
        double sout;
        VTxMxV(sout, v1, m, v2);
        return sout;
    }



    // unit normal and magnitude
    // It's not necessarily obvious which combinations exist or not, so rather than
    // a two type template, we use explicit overloads here.
    SPICE_API void Unorm(FSDimensionlessVector& vout, FSDistance& vmag, const FSDistanceVector& v);
    SPICE_API void Unorm(FSDimensionlessVector& vout, FSSpeed& vmag, const FSVelocityVector& v);
    SPICE_API void Unorm(FSDimensionlessVector& vout, FSAngularRate& vmag, const FSAngularVelocity& v);
    SPICE_API void Unorm(FSDimensionlessVector& vout, double& vmag, const FSDimensionlessVector& v);

    template<class VectorType, class ScalarType>
    inline FSDimensionlessVector Unorm(ScalarType& vmag, const VectorType& v)
    {
        FSDimensionlessVector vout;
        Unorm(vout, vmag, v);
        return vout;
    }


    // Vector linear combination
    template<class VectorType>
    SPICE_API void Vlcom(VectorType& sum, double a, const VectorType& v1, double b, const VectorType& v2);

    template<class VectorType>
    inline VectorType Vlcom(double a, const VectorType& v1, double b, const VectorType& v2)
    {
        VectorType sum;
        Vlcom(sum, a, v1, b, v2);
        return sum;
    }

    // Vector linear combination
    template<class VectorType>
    SPICE_API void Vlcom3(VectorType& sum, double a, const VectorType& v1, double b, const VectorType& v2, double c, const VectorType& v3);

    template<class VectorType>
    inline VectorType Vlcom3(double a, const VectorType& v1, double b, const VectorType& v2, double c, const VectorType& v3)
    {
        VectorType sum;
        Vlcom3(sum, a, v1, b, v2, c, v3);
        return sum;
    }

    SPICE_API void M2q(FSQuaternion& q, const FSRotationMatrix& r, ES_ResultCode* ResultCode = nullptr, FString* ErrorMessage = nullptr);
    inline FSQuaternion M2q(const FSRotationMatrix& r, ES_ResultCode* ResultCode = nullptr, FString* ErrorMessage = nullptr)
    {
        FSQuaternion q;
        M2q(q, r, ResultCode, ErrorMessage);
        return q;
    }
    SPICE_API void Q2m(FSRotationMatrix& r, const FSQuaternion& q);
    inline FSRotationMatrix Q2m(const FSQuaternion& q)
    {
        FSRotationMatrix r;
        Q2m(r, q);
        return r;
    }
    SPICE_API void QxQ(FSQuaternion& qout, const FSQuaternion& q1, const FSQuaternion& q2);
    inline FSQuaternion QxQ(const FSQuaternion& q1, const FSQuaternion& q2)
    {
        FSQuaternion qout;
        QxQ(qout, q1, q2);
        return qout;
    }
    SPICE_API double normalize0to360(double degrees);
    SPICE_API double normalize180to180(double degrees);
    SPICE_API double normalizeZeroToTwoPi(double radians);
    SPICE_API double normalizePiToPi(double radians);

    /*
    *
    * Swizzling Conversions
    * For spatial data exchanged between SPICE/UE.
    * UE uses a single-precision Left-Handed Coordinate System
    * SPICE uses a double-precision Right-Handed Coordinate System
    *
    */

    // Vectors...
    // --------------

#pragma warning( push )
#pragma warning( disable : 4499 )

    // From SPICE to UE
    inline static FVector Swizzle(const FSDimensionlessVector& value)
    {
        return FVector((FVector::FReal)value.y, (FVector::FReal)value.x, (FVector::FReal)value.z);

    }

    inline static FVector Swizzle(const FSDistanceVector& value)
    {
        return FVector((FVector::FReal)value.y.km, (FVector::FReal)value.x.km, (FVector::FReal)value.z.km);
    }

    inline static FVector Swizzle(const FSVelocityVector& value)
    {
        return FVector((FVector::FReal)value.dy.kmps, (FVector::FReal)value.dx.kmps, (FVector::FReal)value.dz.kmps);
    }

    inline static FVector Swizzle(const FSAngularVelocity& value)
    {
        // (Going from RHS/LHS negates angular velocities...)
        return FVector(-(FVector::FReal)value.y.radiansPerSecond, -(FVector::FReal)value.x.radiansPerSecond, -(FVector::FReal)value.z.radiansPerSecond);
    }

    // From UE to SPICE
    inline static void Swizzle(const FVector& in, FSDimensionlessVector& out)
    {
        out = FSDimensionlessVector(in.Y, in.X, in.Z);
    }

    inline static void Swizzle(const FVector& in, FSDistanceVector& out)
    {
        out = FSDistanceVector(in.Y, in.X, in.Z);
    }

    inline static void Swizzle(const FVector& in, FSVelocityVector& out)
    {
        out = FSVelocityVector(in.Y, in.X, in.Z);
    }

    inline static void Swizzle(const FVector& in, FSAngularVelocity& out)
    {
        // (Going from LHS/RHS negates angular velocities...)
        out = FSAngularVelocity(FSAngularRate(-in.Y), FSAngularRate(-in.X), FSAngularRate(-in.Z));
    }

    template<typename T> static T Swizzle(const FVector& in);

    template<> FSDimensionlessVector Swizzle<FSDimensionlessVector>(const FVector& in)
    {
        return FSDimensionlessVector(in.Y, in.X, in.Z);
    }

    template<> FSDistanceVector Swizzle<FSDistanceVector>(const FVector& in)
    {
        return FSDistanceVector(in.Y, in.X, in.Z);
    }

    template<> FSVelocityVector Swizzle<FSVelocityVector>(const FVector& in)
    {
        return FSVelocityVector(in.Y, in.X, in.Z);
    }

    template<> FSAngularVelocity Swizzle<FSAngularVelocity>(const FVector& in)
    {
        // (Going from LHS/RHS negates angular velocities...)
        return FSAngularVelocity(FSAngularRate(-in.Y), FSAngularRate(-in.X), FSAngularRate(-in.Z));
    }

#pragma warning( pop )

    // Quaternions...
    // --------------
    // From SPICE to UE
    inline static FQuat Swizzle(const FSQuaternion& value)
    {
        double x = 0., y = 0., z = 0., w = 0.;
        value.QENG(w, x, y, z);
        return FQuat((FVector::FReal)y, (FVector::FReal)x, (FVector::FReal)z, (FVector::FReal)w);
    }

    // From UE to SPICE
    inline static FSQuaternion Swizzle(const FQuat& value)
    {
        return FSQuaternion::ENG(value.W, value.Y, value.X, value.Z);
    }

    SPICE_API double normalize0to360(double degrees);
    SPICE_API double normalize180to180(double degrees);
    SPICE_API double normalizeZeroToTwoPi(double radians);
    SPICE_API double normalizePiToPi(double radians);
};
