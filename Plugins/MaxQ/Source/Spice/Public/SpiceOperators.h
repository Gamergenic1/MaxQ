// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceOperators.h
// 
// API Comments
// 
// Purpose: C++ Operators for ue-wrapped CSPICE types.
// 
// MaxQ:
// * Base API
// * Refined API
//    * C++
//    * Blueprints
//
// SpiceOperators.h is part of the "refined C++ API".
// 
// fyi-
// The operators are in randomish order, sometimes grouped by operator type,
// sometimes grouped by ue-type, sometimes just whereever Visual Assist
// wanted to plop an implmenetation when hitting Alt-C to create an
// implementation :-D.
//------------------------------------------------------------------------------

#pragma once

#include "SpiceTypes.h"
#include "SpiceMath.h"

template<class VectorType>
inline VectorType operator*(const FSRotationMatrix& lhs, const VectorType& rhs)
{
    VectorType result;
    MaxQ::Math::MxV(result, lhs, rhs);
    return result;
}

template<class VectorType>
inline VectorType operator*(const FSStateTransform& lhs, const VectorType& rhs)
{
    VectorType result;
    MaxQ::Math::MxV(result, lhs, rhs);
    return result;
}

inline FSRotationMatrix operator*(const FSRotationMatrix& m1, const FSRotationMatrix& m2)
{
    return MaxQ::Math::MxM(m1, m2);
}

inline FSStateTransform operator*(const FSStateTransform& m1, const FSStateTransform& m2)
{
    return MaxQ::Math::MxM(m1, m2);
}

inline FSRotationMatrix& operator*=(FSRotationMatrix& m1, const FSRotationMatrix& m2)
{
    m1 = MaxQ::Math::MxM(m1, m2);
    return m1;
}

inline FSStateTransform& operator*=(FSStateTransform& m1, const FSStateTransform& m2)
{
    m1 = MaxQ::Math::MxM(m1, m2);
    return m1;
}

static inline FSDimensionlessVector& operator-=(FSDimensionlessVector& lhs, const FSDimensionlessVector& rhs)
{
    lhs = MaxQ::Math::Vsub(lhs, rhs);
    return lhs;
}

static inline FSDimensionlessVector& operator+=(FSDimensionlessVector& lhs, const FSDimensionlessVector& rhs)
{
    lhs = MaxQ::Math::Vadd(lhs, rhs);
    return lhs;
}

static inline FSDimensionlessVector operator+(const FSDimensionlessVector& lhs, const FSDimensionlessVector& rhs)
{
    return MaxQ::Math::Vadd(lhs, rhs);
}

static inline FSDimensionlessVector operator-(const FSDimensionlessVector& lhs, const FSDimensionlessVector& rhs)
{
    return MaxQ::Math::Vsub(lhs, rhs);
}


static inline FSDimensionlessVector operator-(const FSDimensionlessVector& v)
{
    return MaxQ::Math::Vminus(v);
}

static inline FSDistanceVector& operator-=(FSDistanceVector& lhs, const FSDistanceVector& rhs)
{
    lhs = MaxQ::Math::Vsub(lhs, rhs);
    return lhs;
}


static inline FSDistanceVector& operator+=(FSDistanceVector& lhs, const FSDistanceVector& rhs)
{
    lhs = MaxQ::Math::Vadd(lhs, rhs);
    return lhs;
}

static inline FSDistanceVector operator+(const FSDistanceVector& lhs, const FSDistanceVector& rhs)
{
    return MaxQ::Math::Vadd(lhs, rhs);
}

static inline FSDistanceVector operator-(const FSDistanceVector& lhs, const FSDistanceVector& rhs)
{
    return MaxQ::Math::Vsub(lhs, rhs);
}


static inline FSDistanceVector operator-(const FSDistanceVector& v)
{
    return MaxQ::Math::Vminus(v);
}

static inline FSVelocityVector& operator-=(FSVelocityVector& lhs, const FSVelocityVector& rhs)
{
    lhs = MaxQ::Math::Vsub(lhs, rhs);
    return lhs;
}


static inline FSVelocityVector& operator+=(FSVelocityVector& lhs, const FSVelocityVector& rhs)
{
    lhs = MaxQ::Math::Vadd(lhs, rhs);
    return lhs;
}

static inline FSVelocityVector operator+(const FSVelocityVector& lhs, const FSVelocityVector& rhs)
{
    return MaxQ::Math::Vadd(lhs, rhs);
}

static inline FSVelocityVector operator-(const FSVelocityVector& lhs, const FSVelocityVector& rhs)
{
    return MaxQ::Math::Vsub(lhs, rhs);
}


static inline FSVelocityVector operator-(const FSVelocityVector& v)
{
    return MaxQ::Math::Vminus(v);
}

static inline FSAngularVelocity& operator-=(FSAngularVelocity& lhs, const FSAngularVelocity& rhs)
{
    lhs = MaxQ::Math::Vsub(lhs, rhs);
    return lhs;
}


static inline FSAngularVelocity& operator+=(FSAngularVelocity& lhs, const FSAngularVelocity& rhs)
{
    lhs = MaxQ::Math::Vadd(lhs, rhs);
    return lhs;
}

static inline FSAngularVelocity operator+(const FSAngularVelocity& lhs, const FSAngularVelocity& rhs)
{
    return MaxQ::Math::Vadd(lhs, rhs);
}

static inline FSAngularVelocity operator-(const FSAngularVelocity& lhs, const FSAngularVelocity& rhs)
{
    return MaxQ::Math::Vsub(lhs, rhs);
}


static inline FSAngularVelocity operator-(const FSAngularVelocity& v)
{
    return MaxQ::Math::Vminus(v);
}

static inline FSStateVector& operator-=(FSStateVector& lhs, const FSStateVector& rhs)
{
    lhs = MaxQ::Math::Vsub(lhs, rhs);
    return lhs;
}


static inline FSStateVector& operator+=(FSStateVector& lhs, const FSStateVector& rhs)
{
    lhs = MaxQ::Math::Vadd(lhs, rhs);
    return lhs;
}

static inline FSStateVector operator+(const FSStateVector& lhs, const FSStateVector& rhs)
{
    return MaxQ::Math::Vadd(lhs, rhs);
}

static inline FSStateVector operator-(const FSStateVector& lhs, const FSStateVector& rhs)
{
    return MaxQ::Math::Vsub(lhs, rhs);
}


static inline FSStateVector operator-(const FSStateVector& v)
{
    return MaxQ::Math::Vminus(v);
}

static inline FSDimensionlessStateVector& operator-=(FSDimensionlessStateVector& lhs, const FSDimensionlessStateVector& rhs)
{
    lhs = MaxQ::Math::Vsub(lhs, rhs);
    return lhs;
}


static inline FSDimensionlessStateVector& operator+=(FSDimensionlessStateVector& lhs, const FSDimensionlessStateVector& rhs)
{
    lhs = MaxQ::Math::Vadd(lhs, rhs);
    return lhs;
}

static inline FSDimensionlessStateVector operator+(const FSDimensionlessStateVector& lhs, const FSDimensionlessStateVector& rhs)
{
    return MaxQ::Math::Vadd(lhs, rhs);
}

static inline FSDimensionlessStateVector operator-(const FSDimensionlessStateVector& lhs, const FSDimensionlessStateVector& rhs)
{
    return MaxQ::Math::Vsub(lhs, rhs);
}


static inline FSDimensionlessStateVector operator-(const FSDimensionlessStateVector& v)
{
    return MaxQ::Math::Vminus(v);
}

static inline bool operator==(const FSDimensionlessVector& lhs, const FSDimensionlessVector& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

static inline FSDimensionlessVector operator*(double scalar, const FSDimensionlessVector& vector)
{
    return FSDimensionlessVector(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}

static inline FSDimensionlessVector operator*(const FSDimensionlessVector& vector, double scalar)
{
    return FSDimensionlessVector(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}

static inline FSDimensionlessVector operator/(const FSDimensionlessVector& vector, double scalar)
{
    return FSDimensionlessVector(vector.x / scalar, vector.y / scalar, vector.z / scalar);
}

static inline FSDimensionlessVector& operator*=(FSDimensionlessVector& lhs, double rhs) {

    lhs.x *= rhs;
    lhs.y *= rhs;
    lhs.z *= rhs;
    return lhs;
}

static inline FSDimensionlessVector& operator/=(FSDimensionlessVector& lhs, double rhs) {

    lhs.x /= rhs;
    lhs.y /= rhs;
    lhs.z /= rhs;
    return lhs;
}

static inline bool operator<(const FSDistance& lhs, const FSDistance& rhs)
{
    return lhs.km < rhs.km;
}

static inline bool operator>(const FSDistance& lhs, const FSDistance& rhs)
{
    return lhs.km > rhs.km;
}

static inline FSDistance operator+(const FSDistance& lhs, const FSDistance& rhs)
{
    return FSDistance { lhs.AsSpiceDouble() + rhs.AsSpiceDouble() };
}

static inline FSDistance operator-(const FSDistance& lhs, const FSDistance& rhs)
{
    return FSDistance{ lhs.AsSpiceDouble() - rhs.AsSpiceDouble() };
}

static inline FSDistance operator-(const FSDistance& v)
{
    return FSDistance{ -v.AsSpiceDouble() };
}

static inline double operator/(const FSDistance& lhs, const FSDistance& rhs)
{
    return lhs.km / rhs.km;
}

static inline FSDistance operator/(const FSDistance& lhs, double rhs)
{
    return lhs.km / rhs;
}

static inline FSDistance operator*(double lhs, const FSDistance& rhs)
{
    return FSDistance(lhs * rhs.km);
}

static inline FSDistance operator*(const FSDistance& lhs, double rhs)
{
    return FSDistance(lhs.km * rhs);
}

static inline FSDistance& operator*=(FSDistance& lhs, double rhs) {

    lhs.km *= rhs;
    return lhs;
}

static inline bool operator==(const FSDistance& lhs, const FSDistance& rhs)
{
    return lhs.km == rhs.km;
}

static inline bool operator!=(const FSDistance& lhs, const FSDistance& rhs)
{
    return !(lhs == rhs);
}

static inline FSDistance& operator+=(FSDistance& lhs, const FSDistance& rhs) {

    lhs.km += rhs.km;
    return lhs;
}

static inline FSDistance& operator-=(FSDistance& lhs, const FSDistance& rhs) {

    lhs.km -= rhs.km;
    return lhs;
}

static inline FSDistanceVector operator*(double lhs, const FSDistanceVector& rhs)
{
    return FSDistanceVector(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

static inline FSDistanceVector operator*(const FSDistanceVector& lhs, double rhs)
{
    return FSDistanceVector(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

static inline FSDistanceVector operator/(const FSDistanceVector& lhs, double rhs)
{
    return FSDistanceVector(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

static inline FSDistanceVector operator*(const FSDimensionlessVector& lhs, const FSDistance& rhs)
{
    return FSDistanceVector(lhs.x * rhs.km, lhs.y * rhs.km, lhs.z * rhs.km);
}

static inline FSDistanceVector operator*(const FSDistance& lhs, const FSDimensionlessVector& rhs)
{
    return rhs * lhs;
}

static inline FSDistanceVector& operator*=(FSDistanceVector& lhs, double rhs) {

    lhs.x *= rhs;
    lhs.y *= rhs;
    lhs.z *= rhs;
    return lhs;
}

static inline bool operator==(const FSDistanceVector& lhs, const FSDistanceVector& rhs)
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
}

static inline bool operator!=(const FSDistanceVector& lhs, const FSDistanceVector& rhs)
{
    return !(lhs == rhs);
}

static inline FSDimensionlessVector operator/(const FSDistanceVector& lhs, const FSDistanceVector& rhs)
{
    return FSDimensionlessVector(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

static inline FSDimensionlessVector operator/(const FSDistanceVector& lhs, const FSDistance& rhs)
{
    return FSDimensionlessVector(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

static inline FSSpeed operator+(const FSSpeed& lhs, const FSSpeed& rhs)
{
    return FSSpeed(lhs.kmps + rhs.kmps);
}

static inline FSSpeed operator-(const FSSpeed& rhs)
{
    return FSSpeed(-rhs.kmps);
}

static inline FSSpeed operator-(const FSSpeed& lhs, const FSSpeed& rhs)
{
    return FSSpeed(lhs.kmps - rhs.kmps);
}

static inline double operator/(const FSSpeed& lhs, const FSSpeed& rhs)
{
    return lhs.kmps / rhs.kmps;
}

static inline FSSpeed operator/(const FSSpeed& lhs, double rhs)
{
    return lhs.kmps / rhs;
}

static inline bool operator>(const FSSpeed& lhs, const FSSpeed& rhs)
{
    return lhs.kmps > rhs.kmps;
}

static inline bool operator<(const FSSpeed& lhs, const FSSpeed& rhs)
{
    return lhs.kmps < rhs.kmps;
}

static inline FSSpeed operator*(double lhs, const FSSpeed& rhs)
{
    return FSSpeed(lhs * rhs.kmps);
}

static inline FSSpeed operator*(const FSSpeed& lhs, double rhs)
{
    return FSSpeed(lhs.kmps * rhs);
}

static inline bool operator==(const FSSpeed& lhs, const FSSpeed& rhs)
{
    return lhs.kmps == rhs.kmps;
}

static inline bool operator!=(const FSSpeed& lhs, const FSSpeed& rhs)
{
    return !(lhs == rhs);
}

static inline FSSpeed& operator+=(FSSpeed& lhs, const FSSpeed& rhs) {

    lhs.kmps += rhs.kmps;
    return lhs;
}

static inline FSSpeed& operator-=(FSSpeed& lhs, const FSSpeed& rhs) {

    lhs.kmps -= rhs.kmps;
    return lhs;
}

static inline bool operator==(const FSAngle& lhs, const FSAngle& rhs)
{
    return lhs.degrees == rhs.degrees;
}

static inline bool operator!=(const FSAngle& lhs, const FSAngle& rhs)
{
    return !(lhs == rhs);
}

static inline FSAngle operator*(double lhs, const FSAngle& rhs)
{
    return FSAngle(rhs.AsSpiceDouble() * lhs);
}

static inline FSAngle operator*(const FSAngle& lhs, double rhs)
{
    return FSAngle(lhs.AsSpiceDouble() * rhs);
}

static inline FSAngle operator+(const FSAngle& lhs, const FSAngle& rhs)
{
    return FSAngle(lhs.AsSpiceDouble() + rhs.AsSpiceDouble());
}

static inline FSAngle operator-(const FSAngle& rhs)
{
    return FSAngle(-rhs.AsSpiceDouble());
}

static inline FSAngle operator-(const FSAngle& lhs, const FSAngle& rhs)
{
    return FSAngle(lhs.AsSpiceDouble() - rhs.AsSpiceDouble());
}

static inline FSAngle operator/(const FSAngle& lhs, double rhs)
{
    return FSAngle(lhs.AsSpiceDouble() / rhs);
}

static inline double operator/(const FSAngle& lhs, const FSAngle& rhs)
{
    return lhs.AsSpiceDouble() / rhs.AsSpiceDouble();
}

static inline FSAngle& operator+=(FSAngle& lhs, const FSAngle& rhs) {

    lhs = FSAngle(lhs.AsSpiceDouble() + rhs.AsSpiceDouble());
    return lhs;
}

static inline FSAngle& operator-=(FSAngle& lhs, const FSAngle& rhs) {

    lhs = FSAngle(lhs.AsSpiceDouble() - rhs.AsSpiceDouble());
    return lhs;
}

static inline FSAngle& operator*=(FSAngle& lhs, double rhs) {

    lhs = FSAngle(lhs.AsSpiceDouble() * rhs);
    return lhs;
}

static inline FSAngularRate operator*(double lhs, const FSAngularRate& rhs)
{
    return FSAngularRate(rhs.AsSpiceDouble() * lhs);
}

static inline FSAngularRate operator*(const FSAngularRate& lhs, double rhs)
{
    return FSAngularRate(lhs.AsSpiceDouble() * rhs);
}

static inline FSAngularRate operator+(const FSAngularRate& lhs, const FSAngularRate& rhs)
{
    return FSAngularRate(lhs.AsSpiceDouble() + rhs.AsSpiceDouble());
}

static inline FSAngularRate operator-(const FSAngularRate& lhs, const FSAngularRate& rhs)
{
    return FSAngularRate(lhs.AsSpiceDouble() - rhs.AsSpiceDouble());
}

static inline FSAngularRate operator-(const FSAngularRate& rhs)
{
    return FSAngularRate(-rhs.AsSpiceDouble());
}

static inline FSAngularRate operator/(const FSAngularRate& lhs, double rhs)
{
    return FSAngularRate(lhs.AsSpiceDouble() / rhs);
}

static inline double operator/(const FSAngularRate& lhs, const FSAngularRate& rhs)
{
    return lhs.AsSpiceDouble() / rhs.AsSpiceDouble();
}

static inline FSAngularRate& operator+=(FSAngularRate& lhs, const FSAngularRate& rhs) {

    lhs = FSAngularRate(lhs.AsSpiceDouble() + rhs.AsSpiceDouble());
    return lhs;
}

static inline FSAngularRate& operator-=(FSAngularRate& lhs, const FSAngularRate& rhs) {

    lhs = FSAngularRate(lhs.AsSpiceDouble() - rhs.AsSpiceDouble());
    return lhs;
}

static inline bool operator==(const FSAngularRate& lhs, const FSAngularRate& rhs) {

    return lhs.AsSpiceDouble() == rhs.AsSpiceDouble();
}

static inline bool operator!=(const FSAngularRate& lhs, const FSAngularRate& rhs) {

    return !(lhs == rhs);
}

static inline bool operator==(const FSEphemerisTime& lhs, const FSEphemerisTime& rhs)
{
    return lhs.seconds == rhs.seconds;
}

static inline bool operator!=(const FSEphemerisTime& lhs, const FSEphemerisTime& rhs)
{
    return !(lhs == rhs);
}

static inline bool operator<(const FSEphemerisTime& lhs, const FSEphemerisTime& rhs)
{
    return lhs.seconds < rhs.seconds;
}

static inline bool operator>(const FSEphemerisTime& lhs, const FSEphemerisTime& rhs)
{
    return lhs.seconds > rhs.seconds;
}

static inline FSEphemerisPeriod operator+(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return FSEphemerisPeriod(A.AsSpiceDouble() + B.AsSpiceDouble());
}

static inline FSEphemerisPeriod operator-(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return FSEphemerisPeriod(A.AsSpiceDouble() - B.AsSpiceDouble());
}

static inline FSEphemerisTime operator+(const FSEphemerisPeriod& A, const FSEphemerisTime& B)
{
    return FSEphemerisTime(A.AsSpiceDouble() + B.AsSpiceDouble());
}

static inline FSEphemerisTime operator+(const FSEphemerisTime& A, const FSEphemerisPeriod& B)
{
    return FSEphemerisTime(A.AsSpiceDouble() + B.AsSpiceDouble());
}

static inline FSEphemerisTime operator-(const FSEphemerisTime& A, const FSEphemerisPeriod& B)
{
    return FSEphemerisTime(A.AsSpiceDouble() - B.AsSpiceDouble());
}

static inline FSEphemerisPeriod& operator+=(FSEphemerisPeriod& lhs, const FSEphemerisPeriod& rhs) {

    lhs = FSEphemerisPeriod(lhs.AsSpiceDouble() + rhs.AsSpiceDouble());
    return lhs;
}

static inline FSEphemerisPeriod& operator-=(FSEphemerisPeriod& lhs, const FSEphemerisPeriod& rhs) {

    lhs = FSEphemerisPeriod(lhs.AsSpiceDouble() - rhs.AsSpiceDouble());
    return lhs;
}

static inline FSEphemerisTime& operator+=(FSEphemerisTime& lhs, const FSEphemerisPeriod& rhs) {

    lhs = lhs + rhs;
    return lhs;
}

static inline FSEphemerisTime& operator-=(FSEphemerisTime& lhs, const FSEphemerisPeriod& rhs) {

    lhs = lhs - rhs;
    return lhs;
}

static inline FSEphemerisPeriod operator-(const FSEphemerisTime& A, const FSEphemerisTime& B)
{
    return FSEphemerisPeriod(A.AsSpiceDouble() - B.AsSpiceDouble());
}

static inline FSEphemerisPeriod operator*(double A, const FSEphemerisPeriod& B)
{
    return FSEphemerisPeriod(A * B.AsSpiceDouble());
}

static inline FSEphemerisPeriod operator*(const FSEphemerisPeriod& A, double B)
{
    return FSEphemerisPeriod(A.AsSpiceDouble() * B);
}

static inline FSEphemerisPeriod& operator*=(FSEphemerisPeriod& lhs, double rhs) {

    lhs.seconds *= rhs;
    return lhs;
}

static inline FSEphemerisPeriod& operator/=(FSEphemerisPeriod& lhs, double rhs) {

    lhs.seconds /= rhs;
    return lhs;
}

static inline FSEphemerisPeriod operator/(const FSEphemerisPeriod& A, double B)
{
    return FSEphemerisPeriod(A.AsSpiceDouble() / B);
}

static inline double operator/(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return A.AsSpiceDouble() / B.AsSpiceDouble();
}

static inline FSEphemerisPeriod operator%(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return FSEphemerisPeriod(fmod(A.AsSpiceDouble(), B.AsSpiceDouble()));
}

static inline bool operator==(const FSEphemerisPeriod& lhs, const FSEphemerisPeriod& rhs)
{
    return lhs.seconds == rhs.seconds;
}

static inline bool operator!=(const FSEphemerisPeriod& lhs, const FSEphemerisPeriod& rhs)
{
    return !(lhs == rhs);
}

static inline bool operator>(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return A.AsSpiceDouble() > B.AsSpiceDouble();
}

static inline bool operator<(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return A.AsSpiceDouble() < B.AsSpiceDouble();
}

static inline FSDistance operator*(const FSEphemerisPeriod& lhs, const FSSpeed& rhs)
{
    return FSDistance(lhs.seconds * rhs.kmps);
}

static inline FSDistance operator*(const FSSpeed& lhs, const FSEphemerisPeriod& rhs)
{
    return FSDistance(lhs.kmps * rhs.seconds);
}

static inline FSAngularRate operator/(const FSAngle& lhs, const FSEphemerisPeriod& rhs)
{
    return FSAngularRate(lhs.AsRadians() / rhs.AsSeconds());
}

static inline FSVelocityVector operator/(const FSVelocityVector& lhs, double rhs)
{
    return FSVelocityVector(lhs.dx / rhs, lhs.dy / rhs, lhs.dz / rhs);
}

static inline FSDimensionlessVector operator/(const FSVelocityVector& lhs, const FSVelocityVector& rhs)
{
    return FSDimensionlessVector(lhs.dx / rhs.dx, lhs.dy / rhs.dy, lhs.dz / rhs.dz);
}

static inline FSVelocityVector operator*(double lhs, const FSVelocityVector& rhs)
{
    return FSVelocityVector(lhs * rhs.dx, lhs * rhs.dy, lhs * rhs.dz);
}

static inline FSVelocityVector operator*(const FSVelocityVector& lhs, double rhs)
{
    return FSVelocityVector(lhs.dx * rhs, lhs.dy * rhs, lhs.dz * rhs);
}

static inline FSVelocityVector operator*(const FSDimensionlessVector& lhs, const FSSpeed& rhs)
{
    return FSVelocityVector(lhs.x * rhs.kmps, lhs.y * rhs.kmps, lhs.z * rhs.kmps);
}

static inline FSVelocityVector operator*(const FSSpeed& lhs, const FSDimensionlessVector& rhs)
{
    return rhs * lhs;
}

static inline FSDistanceVector operator*(const FSEphemerisPeriod& lhs, const FSVelocityVector& rhs)
{
    return FSDistanceVector(lhs * rhs.dx, lhs * rhs.dy, lhs * rhs.dz);
}

static inline FSDistanceVector operator*(const FSVelocityVector& lhs, const FSEphemerisPeriod& rhs)
{
    return FSDistanceVector(rhs * lhs.dx, rhs * lhs.dy, rhs * lhs.dz);
}

static inline bool operator==(const FSVelocityVector& lhs, const FSVelocityVector& rhs)
{
    return (lhs.dx == rhs.dx) && (lhs.dy == rhs.dy) && (lhs.dz == rhs.dz);
}

static inline bool operator!=(const FSVelocityVector& lhs, const FSVelocityVector& rhs)
{
    return !(lhs == rhs);
}

static inline FSAngularVelocity operator/(const FSAngularVelocity& lhs, double rhs)
{
    return FSAngularVelocity(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

static inline FSDimensionlessVector operator/(const FSAngularVelocity& lhs, const FSAngularVelocity& rhs)
{
    return FSDimensionlessVector(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

static inline FSAngularVelocity operator*(double lhs, const FSAngularVelocity& rhs)
{
    return FSAngularVelocity(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

static inline FSAngularVelocity operator*(const FSAngularVelocity& lhs, double rhs)
{
    return FSAngularVelocity(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

// The equality operator is useful for unit tests.
static inline bool operator==(const FSAngularVelocity& lhs, const FSAngularVelocity& rhs) {

    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

// The equality operator is used primarily for unit tests.
static inline bool operator!=(const FSAngularVelocity& lhs, const FSAngularVelocity& rhs) {

    return !(lhs == rhs);
}

static inline bool operator==(const FSMassConstant& lhs, const FSMassConstant& rhs)
{
    return (lhs.GM == rhs.GM) && (lhs.GM == rhs.GM);
}

static inline bool operator!=(const FSMassConstant& lhs, const FSMassConstant& rhs)
{
    return !(lhs == rhs);
}

static inline bool operator==(const FSStateVector& lhs, const FSStateVector& rhs)
{
    return (lhs.r == rhs.r) && (lhs.v == rhs.v);
}

static inline bool operator!=(const FSStateVector& lhs, const FSStateVector& rhs)
{
    return !(lhs == rhs);
}

SPICE_API FSQuaternion operator*(const FSQuaternion& lhs, const FSQuaternion& rhs);

