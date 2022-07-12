// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceStructs.cpp
// 
// Implementation Comments
// 
// SpiceStructs : public CSPICE type to UE type wrappers (Structs)
// 
// Purpose:
// Purpose:  Blueprint implementations of CSPICE Type wrappers
//------------------------------------------------------------------------------

#include "SpiceStructs.h"
#include "Containers/StringFwd.h"
#include "Spice.h"
#include "SpiceUtilities.h"


PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
extern "C"
{
#include "SpiceUsr.h"
}
PRAGMA_POP_PLATFORM_DEFAULT_PACKING

using namespace MaxQ::Private;

SPICE_API const FSDistance FSDistance::Zero = FSDistance(0.);
SPICE_API const FSDistance FSDistance::OneKm = FSDistance::FromKilometers(1.);
SPICE_API const FSDistance FSDistance::OneKilometer = FSDistance::FromKilometers(1.);
SPICE_API const FSDistance FSDistance::OneMeter = FSDistance::FromMeters(1.);
SPICE_API const FSDistance FSDistance::OneFoot = FSDistance::FromFeet(1.);
SPICE_API const FSDistance FSDistance::OneStatuteMile = FSDistance::FromStatuteMiles(1.);
SPICE_API const FSDistance FSDistance::OneNauticalMile = FSDistance::FromNauticalMiles(1.);
SPICE_API const FSDistance FSDistance::OneAstronomicalUnit = FSDistance::FromAstronomicalUnits(1.);
SPICE_API const FSDistance FSDistance::OneLightYear = FSDistance::FromLightYears(1.);
SPICE_API const FSSpeed FSSpeed::Zero = FSSpeed();
SPICE_API const FSSpeed FSSpeed::OneKmps = FSSpeed(1.);
SPICE_API const FSDistanceVector FSDistanceVector::Zero = FSDistanceVector();
SPICE_API const FSVelocityVector FSVelocityVector::Zero = FSVelocityVector();
SPICE_API const FSStateTransform FSStateTransform::Identity = FSStateTransform();
SPICE_API const double FSAngle::pi = pi_c();
SPICE_API const double FSAngle::halfpi = halfpi_c();
SPICE_API const double FSAngle::twopi = twopi_c();
SPICE_API const double FSAngle::dpr = dpr_c();
SPICE_API const FSAngle FSAngle::_0 = FSAngle();
SPICE_API const FSAngle FSAngle::_360 = FSAngle(twopi_c());
SPICE_API const FSEulerAngles FSEulerAngles::Zero = FSEulerAngles();
SPICE_API const FSQuaternion FSQuaternion::Identity = FSQuaternion();
SPICE_API const FSQuaternionDerivative FSQuaternionDerivative::Zero = FSQuaternionDerivative();
SPICE_API const FSAngularRate FSAngularRate::Zero = FSAngularRate();
SPICE_API const FSAngularVelocity FSAngularVelocity::Zero = FSAngularVelocity();
SPICE_API const FSEulerAngularState FSEulerAngularState::Zero = FSEulerAngularState();
SPICE_API const FSEulerAngularTransform FSEulerAngularTransform::Identity = FSEulerAngularTransform();
SPICE_API const FSComplexScalar FSComplexScalar::Zero = FSComplexScalar();
SPICE_API const FSEphemerisTime FSEphemerisTime::J2000 = FSEphemerisTime();
SPICE_API const FSEphemerisPeriod FSEphemerisPeriod::Zero = FSEphemerisPeriod();
SPICE_API const FSEphemerisPeriod FSEphemerisPeriod::OneSecond = FSEphemerisPeriod(1.);
SPICE_API const FSEphemerisPeriod FSEphemerisPeriod::OneMinute = FSEphemerisPeriod(60.);
SPICE_API const FSEphemerisPeriod FSEphemerisPeriod::OneHour = FSEphemerisPeriod(60. * 60.);
SPICE_API const FSEphemerisPeriod FSEphemerisPeriod::Day = FSEphemerisPeriod((double) spd_c());
SPICE_API const FSEphemerisPeriod FSEphemerisPeriod::OneDay = FSEphemerisPeriod((double) spd_c());
SPICE_API const FSEphemerisPeriod FSEphemerisPeriod::OneJulianYear = FSEphemerisPeriod((double) jyear_c() );
SPICE_API const FSEphemerisPeriod FSEphemerisPeriod::OneTropicalYear = FSEphemerisPeriod((double) tyear_c());
SPICE_API const FSRotationMatrix FSRotationMatrix::Identity = FSRotationMatrix();
SPICE_API const FSDimensionlessVector FSDimensionlessVector::Zero = FSDimensionlessVector();
SPICE_API const FSDimensionlessVector FSDimensionlessVector::X_Axis = FSDimensionlessVector(1., 0., 0.);
SPICE_API const FSDimensionlessVector FSDimensionlessVector::Y_Axis = FSDimensionlessVector(0., 1., 0.);
SPICE_API const FSDimensionlessVector FSDimensionlessVector::Z_Axis = FSDimensionlessVector(0., 0., 1.);
SPICE_API const FSMassConstant FSMassConstant::Zero = FSMassConstant(0.);
SPICE_API int USpiceTypes::FloatFormatPrecision = 8;

FSQuaternion::operator FSRotationMatrix() const
{
    return MaxQ::Math::Q2m(*this);
}

double FSDistanceVector::f() const
{
    return (Re() - Rp()) / Re();
}


FString FSDistanceVector::ToString() const
{
    return FString::Printf(TEXT("(%s, %s, %s)"), *USpiceTypes::FormatDouble(x.km), *USpiceTypes::FormatDouble(y.km), *USpiceTypes::FormatDouble(z.km));
}


FString FSDistance::ToString() const
{
    return USpiceTypes::FormatDistance(*this);
}

FString FSDistance::ToString(ES_Units Units, int precision /*= 12*/) const
{
    return USpiceTypes::FormatDistance(*this, Units, precision);
}

FString FSDimensionlessVector::ToString() const
{
    return FString::Printf(TEXT("(%s, %s, %s)"), *USpiceTypes::FormatDouble(x), *USpiceTypes::FormatDouble(y), *USpiceTypes::FormatDouble(z));
}


FString FSSpeed::ToString() const
{
    return USpiceTypes::FormatSpeed(*this);
}


FString FSSpeed::ToString(ES_Units NumeratorUnits, ES_Units DenominatorUnits /*= ES_Units::SECONDS*/, int precision /*= 12*/) const
{
    return USpiceTypes::FormatSpeed(*this, NumeratorUnits, DenominatorUnits, precision);
}

FString FSAngle::ToString() const
{
    return USpiceTypes::FormatAngle(*this);
}

FString FSAngle::ToString(ES_AngleFormat format) const
{
    return USpiceTypes::FormatAngle(*this, format);
}

FString FSAngularRate::ToString() const
{
    return USpiceTypes::FormatDouble(AsDegreesPerSecond());
}

FString FSComplexScalar::ToString() const
{
    return FString::Printf(TEXT("(%s + %s i)"), *USpiceTypes::FormatDouble(real), *USpiceTypes::FormatDouble(imaginary));
}

FString FSEphemerisTime::ToString() const
{
    SpiceChar sz[SPICE_MAX_PATH];
    memset(sz, 0, sizeof(sz));

    et2utc_c(AsSpiceDouble(), "C", 4, SPICE_MAX_PATH, sz);

    SpiceStringConcat(sz, " UTC");

    // Do not reset any error state, the downstream computation will detect the signal if the string failed to convert.
    UnexpectedErrorCheck(false);

    return FString(sz);
}


FString FSEphemerisTime::ToString(ES_UTCTimeFormat TimeFormat, int precision /*= 4*/) const
{
    return USpiceTypes::FormatUtcTime(*this, TimeFormat, precision);
}

FSEphemerisTime FSEphemerisTime::FromString(const FString& Str)
{
    double et = 0.;
    str2et_c(TCHAR_TO_ANSI(*Str), &et);

    // Do not reset any error state, the downstream computation will detect the signal if the string failed to convert.
    UnexpectedErrorCheck(false);

    return FSEphemerisTime(et);
}

FString FSEphemerisPeriod::ToString() const
{
    return USpiceTypes::FormatPeriod(*this);
}

FString FSEphemerisPeriod::ToString(ES_Units Units, int precision /*= 12*/) const
{
    return USpiceTypes::FormatPeriod(*this, Units, precision);
}

FString FSVelocityVector::ToString() const
{
    return FString::Printf(TEXT("(%s, %s, %s)"), *USpiceTypes::FormatDouble(dx.kmps), *USpiceTypes::FormatDouble(dy.kmps), *USpiceTypes::FormatDouble(dz.kmps));
}

FString FSLonLat::ToString() const
{
    return USpiceTypes::FormatLonLat(*this);
}

FString FSLonLat::ToString(const FString& separator, ES_AngleFormat format /*= ES_AngleFormat::DD*/) const
{
    return USpiceTypes::FormatLonLat(*this, separator, format);
}

FString FSEulerAngles::ToString() const
{
    return FString::Printf(TEXT("{%s %s %s}(%s * %s * %s)"), *MaxQ::Core::ToString(axis3), *MaxQ::Core::ToString(axis2), *MaxQ::Core::ToString(axis1), *angle3.ToString(), *angle2.ToString(), *angle1.ToString());
}

FString FSAngularVelocity::ToString() const
{
    FSDimensionlessVector dimensionlessVector;
    FSAngularRate angularRate;
    USpice::unorm_angular_velocity(*this, dimensionlessVector, angularRate);
    return FString::Printf(TEXT("{%s * (%s)}"), *angularRate.ToString(), *dimensionlessVector.ToString());
}

FString FSEulerAngularState::ToString() const
{
    return FString::Printf(TEXT("{%s %s %s}(%s * %s * %s) d/dt(%s * %s * %s)"), *MaxQ::Core::ToString(axis3), *MaxQ::Core::ToString(axis2), *MaxQ::Core::ToString(axis1), *angle3.ToString(), *angle2.ToString(), *angle1.ToString(), *rate3.ToString(), *rate2.ToString(), *rate1.ToString());
}

FString FSMassConstant::ToString() const
{
    return USpiceTypes::FormatDouble(GM);
}

FString FSDimensionlessStateVector::ToString() const
{
    return FString::Printf(TEXT("[(%s, %s, %s); (%s, %s, %s)]"), *USpiceTypes::FormatDouble(r.x), *USpiceTypes::FormatDouble(r.y), *USpiceTypes::FormatDouble(r.z), *USpiceTypes::FormatDouble(dr.x), *USpiceTypes::FormatDouble(dr.y), *USpiceTypes::FormatDouble(dr.z));
}

FString FSStateVector::ToString() const
{
    return FString::Printf(TEXT("[(%s, %s, %s); (%s, %s, %s)]"), *USpiceTypes::FormatDouble(r.x.km), *USpiceTypes::FormatDouble(r.y.km), *USpiceTypes::FormatDouble(r.z.km), *USpiceTypes::FormatDouble(v.dx.kmps), *USpiceTypes::FormatDouble(v.dy.kmps), *USpiceTypes::FormatDouble(v.dz.kmps));
}

FString FSCylindricalVector::ToString() const
{
    return FString::Printf(TEXT("(%s, %s, %s)"), *USpiceTypes::FormatDouble(r.km), *USpiceTypes::FormatDouble(lon.degrees), *USpiceTypes::FormatDouble(z.km));
}

FString FSCylindricalVectorRates::ToString() const
{
    return FString::Printf(TEXT("(%s, %s, %s)"), *USpiceTypes::FormatDouble(dr.kmps), *USpiceTypes::FormatDouble(dlon.AsDegreesPerSecond()), *USpiceTypes::FormatDouble(dz.kmps));

}

FString FSCylindricalStateVector::ToString() const
{
    return FString::Printf(TEXT("[(%s, %s, %s); (%s, %s, %s)]"), *USpiceTypes::FormatDouble(r.r.km), *USpiceTypes::FormatDouble(r.lon.degrees), *USpiceTypes::FormatDouble(r.z.km), *USpiceTypes::FormatDouble(dr.dr.kmps), *USpiceTypes::FormatDouble(dr.dlon.AsDegreesPerSecond()), *USpiceTypes::FormatDouble(dr.dz.kmps));
}

FString FSLatitudinalVector::ToString() const
{
    return FString::Printf(TEXT("(%s; %s)"), *USpiceTypes::FormatDouble(r.km), *USpiceTypes::FormatLonLat(lonlat));
}

FString FSLatitudinalVectorRates::ToString() const
{
    return FString::Printf(TEXT("(%s, %s, %s)"), *USpiceTypes::FormatDouble(dr.kmps), *USpiceTypes::FormatDouble(dlon.AsDegreesPerSecond()), *USpiceTypes::FormatDouble(dlat.AsDegreesPerSecond()));
}

FString FSLatitudinalStateVector::ToString() const
{
    return FString::Printf(TEXT("[%s, (%s, %s); (%s, %s, %s)]"), *USpiceTypes::FormatDouble(r.r.km), *USpiceTypes::FormatDouble(r.lonlat.longitude.degrees), *USpiceTypes::FormatDouble(r.lonlat.latitude.degrees), *USpiceTypes::FormatDouble(dr.dr.kmps), *USpiceTypes::FormatDouble(dr.dlon.AsDegreesPerSecond()), *USpiceTypes::FormatDouble(dr.dlat.AsDegreesPerSecond()));
}

FString FSSphericalVector::ToString() const
{
    return FString::Printf(TEXT("(%s; %s, %s)"), *USpiceTypes::FormatDouble(r.km), *USpiceTypes::FormatDouble(colat.degrees), *USpiceTypes::FormatDouble(lon.degrees));
}

FString FSSphericalVectorRates::ToString() const
{
    return FString::Printf(TEXT("(%s, %s, %s)"), *USpiceTypes::FormatDouble(dr.kmps), *USpiceTypes::FormatDouble(dcolat.AsDegreesPerSecond()), *USpiceTypes::FormatDouble(dlon.AsDegreesPerSecond()));
}

FString FSSphericalStateVector::ToString() const
{
    return FString::Printf(TEXT("[(%s, %s, %s); (%s, %s, %s)]"), *USpiceTypes::FormatDouble(r.r.km), *USpiceTypes::FormatDouble(r.colat.degrees), *USpiceTypes::FormatDouble(r.lon.degrees), *USpiceTypes::FormatDouble(dr.dr.kmps), *USpiceTypes::FormatDouble(dr.dcolat.AsDegreesPerSecond()), *USpiceTypes::FormatDouble(dr.dlon.AsDegreesPerSecond()));
}

FString FSGeodeticVector::ToString() const
{
    return FString::Printf(TEXT("(%s; %s)"), *USpiceTypes::FormatLonLat(lonlat), *USpiceTypes::FormatDouble(alt.km));
}

FString FSGeodeticVectorRates::ToString() const
{
    return FString::Printf(TEXT("(%s, %s, %s)"), *USpiceTypes::FormatDouble(dlon.AsDegreesPerSecond()), *USpiceTypes::FormatDouble(dlat.AsDegreesPerSecond()), *USpiceTypes::FormatDouble(dalt.kmps));
}

FString FSGeodeticStateVector::ToString() const
{
    return FString::Printf(TEXT("[(%s), %s; (%s, %s, %s)]"), *USpiceTypes::FormatLonLat(r.lonlat), *USpiceTypes::FormatDouble(r.alt.km), *USpiceTypes::FormatDouble(dr.dlon.AsDegreesPerSecond()), *USpiceTypes::FormatDouble(dr.dlat.AsDegreesPerSecond()), *USpiceTypes::FormatDouble(dr.dalt.kmps));
}

FString FSPlanetographicVector::ToString() const
{
    return FString::Printf(TEXT("(%s; %s)"), *USpiceTypes::FormatLonLat(lonlat), *USpiceTypes::FormatDouble(alt.km));

}

FString FSPlanetographicVectorRates::ToString() const
{
    return FString::Printf(TEXT("(%s, %s, %s)"), *USpiceTypes::FormatDouble(dlon.AsDegreesPerSecond()), *USpiceTypes::FormatDouble(dlat.AsDegreesPerSecond()), *USpiceTypes::FormatDouble(dalt.kmps));
}

FString FSPlanetographicStateVector::ToString() const
{
    return FString::Printf(TEXT("[(%s), %s; (%s, %s, %s)]"), *USpiceTypes::FormatLonLat(r.lonlat), *USpiceTypes::FormatDouble(r.alt.km), *USpiceTypes::FormatDouble(dr.dlon.AsDegreesPerSecond()), *USpiceTypes::FormatDouble(dr.dlat.AsDegreesPerSecond()), *USpiceTypes::FormatDouble(dr.dalt.kmps));
}

FVector FSAngularVelocity::Swizzle() const
{
    return MaxQ::Math::Swizzle(*this);
}

FSAngularVelocity FSAngularVelocity::Swizzle(const FVector& UEVector)
{
    return MaxQ::Math::Swizzle<FSAngularVelocity>(UEVector);
}

FVector FSDimensionlessVector::Swizzle() const
{
    return MaxQ::Math::Swizzle(*this);
}

FSDimensionlessVector FSDimensionlessVector::Swizzle(const FVector& UEVector)
{
    return MaxQ::Math::Swizzle<FSDimensionlessVector>(UEVector);
}


FVector FSDistanceVector::Swizzle() const
{
    return MaxQ::Math::Swizzle(*this);
}

FSDistanceVector FSDistanceVector::Swizzle(const FVector& UEVector)
{
    return MaxQ::Math::Swizzle<FSDistanceVector>(UEVector);
}


FVector FSVelocityVector::Swizzle() const
{
    return MaxQ::Math::Swizzle(*this);
}

FSVelocityVector FSVelocityVector::Swizzle(const FVector& UEVector)
{
    return MaxQ::Math::Swizzle<FSVelocityVector>(UEVector);
}

FString FSStateTransform::ToString() const
{
    static TStringBuilder<1024> sb;

    sb.Reset();

    sb.AppendChar(TCHAR('('));
    bool AppendSpace = false;    
    for (auto vec : m)
    {
        if (AppendSpace)
        {
            sb.Append(TEXT(", "));
            AppendSpace = true;
        }
        sb += vec.ToString();
    }
    sb.AppendChar(TCHAR(')'));

    return sb.ToString();
}

FString FSRotationMatrix::ToString() const
{
    ES_ResultCode ResultCode;
    FString ErrorMessage;

    FSQuaternion q = FSQuaternion::Identity;
    USpice::m2q(ResultCode, ErrorMessage, *this, q);

    ErrorCheck(ResultCode, ErrorMessage);

    return ResultCode == ES_ResultCode::Success ? q.ToString() : TEXT("BAD ROTATION MATRIX");
}

FString FSQuaternion::ToString() const
{
    FSRotationMatrix m;
    USpice::q2m(*this, m);
    ES_ResultCode ResultCode;
    FString ErrorMessage;

    FSDimensionlessVector RotationAxis;
    FSAngle RotationAngle;
    USpice::raxisa(ResultCode, ErrorMessage, m, RotationAxis, RotationAngle);

    if (ResultCode == ES_ResultCode::Success)
    {
        return FString::Format(TEXT("{0} deg * [{1}]"), { USpiceTypes::FormatAngle(RotationAngle, ES_AngleFormat::DD), RotationAxis.ToString() });
    }
    else
    {
        return ErrorMessage;
    }
}

FQuat FSQuaternion::Swizzle() const
{
    return MaxQ::Math::Swizzle(*this);
}

FSQuaternion FSQuaternion::Swizzle(const FQuat& UnrealQuat)
{
    return MaxQ::Math::Swizzle(UnrealQuat);
}

FString FSQuaternionDerivative::ToString() const
{
    return FString::Printf(TEXT("(dx:%s, dy:%s, dz:%s, dw:%s)"), *USpiceTypes::FormatDouble(dx), *USpiceTypes::FormatDouble(dy), *USpiceTypes::FormatDouble(dz), *USpiceTypes::FormatDouble(dw));
}

FVector4 FSQuaternionDerivative::Swizzle() const
{
    double x = 0., y = 0., z = 0., w = 0.;
    QENG(w, x, y, z);
    return FVector4((FVector::FReal)y, (FVector::FReal)x, (FVector::FReal)z, (FVector::FReal)w);
}

FSQuaternionDerivative FSQuaternionDerivative::Swizzle(const FVector4& UnrealVector4)
{
    return FSQuaternionDerivative::ENG(UnrealVector4.W, UnrealVector4.Y, UnrealVector4.X, UnrealVector4.Z);
}


FString FSEllipse::ToString() const
{
    return FString::Printf( TEXT("(center %s; v_major %s; v_minor %s)"), *center.ToString(), *v_major.ToString(), *v_minor.ToString() );
}

FString FSPlane::ToString() const
{
    return FString::Printf( TEXT("(normal %s; constant %s)"), *normal.ToString(), *constant.ToString() );
}

FString FSEulerAngularTransform::ToString() const
{
    static TStringBuilder<1024> sb;

    sb.Reset();

    sb.AppendChar(TCHAR('('));
    bool AppendSpace = false;
    for (auto vec : m)
    {
        if (AppendSpace)
        {
            sb.Append(TEXT(", "));
            AppendSpace = true;
        }
        sb += vec.ToString();
    }
    sb.AppendChar(TCHAR(')'));

    return sb.ToString();
}

FString FSConicElements::ToString() const
{
    return FString::Printf(
        TEXT("(q %s km; e %s; i %s, node %s, peri %s; M %s Epoch %s; GM %s)"),
        *USpiceTypes::FormatDouble(PerifocalDistance.km),
        *USpiceTypes::FormatDouble(Eccentricity),
        *USpiceTypes::FormatAngle(Inclination),
        *USpiceTypes::FormatAngle(LongitudeOfAscendingNode),
        *USpiceTypes::FormatAngle(ArgumentOfPeriapse),
        *USpiceTypes::FormatAngle(MeanAnomalyAtEpoch),
        *USpiceTypes::FormatDouble(Epoch.seconds),
        *USpiceTypes::FormatDouble(GravitationalParameter.GM)
    );
}

FString FSEquinoctialElements::ToString() const
{
    return FString::Printf(
        TEXT("(a %s, h %s, k %s, MeanLongitude %s, p %s, q %s, RateOfLongitudeOfPeriapse %s, MeanLongitudeDerivative %s, RateOfLongitudeOfAscendingNode %s)"),
        *a.ToString(),
        *USpiceTypes::FormatDouble(h),
        *USpiceTypes::FormatDouble(k),
        *MeanLongitude.ToString(),
        *USpiceTypes::FormatDouble(p),
        *USpiceTypes::FormatDouble(q),
        *RateOfLongitudeOfPeriapse.ToString(),
        *MeanLongitudeDerivative.ToString(),
        *RateOfLongitudeOfAscendingNode.ToString()
    );
}

FString FSEphemerisTimeWindowSegment::ToString() const
{
    return FString::Printf(TEXT("(start %s, stop %s)"), *start.ToString(), *stop.ToString());
}

FString FSWindowSegment::ToString() const
{
    return FString::Printf(TEXT("(start %s, stop %s)"), *USpiceTypes::FormatDouble(start), *USpiceTypes::FormatDouble(stop));
}

FString FSPointingType2Observation::ToString() const
{
    return FString::Printf(TEXT("(segment %s, quat %s, avv %s rate %s)"), *segment.ToString(), *quat.ToString(), *avv.ToString(), *USpiceTypes::FormatDouble(rate));
}

FString FSPointingType1Observation::ToString() const
{
    return FString::Printf(TEXT("(sclkdp %s, quat %s, avv %s)"), *USpiceTypes::FormatDouble(sclkdp), *quat.ToString(), *avv.ToString());
}

FString FSPointingType5Observation::ToString() const
{
    static TStringBuilder<1024> sb;

    sb.Reset();

    sb.Appendf(TEXT("(sclkdp=%d "), *USpiceTypes::FormatDouble(sclkdp));
    sb.Appendf(TEXT("quat=%s "), *quat.ToString());
    sb.Appendf(TEXT("quatderiv=%s "), *quatderiv.ToString());
    sb.Appendf(TEXT("avv=%s "), *avv.ToString());
    sb.Appendf(TEXT("avvderiv=%s)"), *avvderiv.ToString());

    return sb.ToString();
}

FString FSPKType5Observation::ToString() const
{
    return FString::Printf(TEXT("(et %s, state %s)"), *USpiceTypes::FormatDouble(et.AsSeconds()), *state.ToString());
}

FString FSPKType15Observation::ToString() const
{
    static TStringBuilder<1024> sb;

    sb.Reset();
    sb.Appendf(TEXT("(epoch=%s "), *epoch.ToString());
    sb.Appendf(TEXT("tp=%s "), *tp.ToString());
    sb.Appendf(TEXT("pa=%s "), *pa.ToString());
    sb.Appendf(TEXT("p=%s "), *p.ToString());
    sb.Appendf(TEXT("ecc=%f "), ecc);
    sb.Appendf(TEXT("j2flg=%f "), j2flg);
    sb.Appendf(TEXT("pv=%s "), *pv.ToString());
    sb.Appendf(TEXT("gm=%s "), *gm.ToString());
    sb.Appendf(TEXT("j2=%f "), j2);
    sb.Appendf(TEXT("radius=%s)"), *radius.ToString());

    return sb.ToString();
}

FString FSTwoLineElements::ToString() const
{
    static TStringBuilder<1024> sb;

    sb.Reset();

    sb.AppendChar(TCHAR('('));
    bool AppendSpace = false;

    for (int i = 0; i < elems.Num(); ++i)
    {

        if (AppendSpace)
        {
            sb.Append(TEXT(", "));
            AppendSpace = true;
        }
        
        switch (i)
        {
        case XNDT2O:
            sb.Append(TEXT("XNDT2O="));
            break;
        case XNDD6O:
            sb.Append(TEXT("XNDD6O="));
            break;
        case BSTAR:
            sb.Append(TEXT("BSTAR="));
            break;
        case XINCL:
            sb.Append(TEXT("XINCL="));
            break;
        case XNODEO:
            sb.Append(TEXT("XNODEO="));
            break;
        case EO:
            sb.Append(TEXT("EO="));
            break;
        case OMEGAO:
            sb.Append(TEXT("OMEGAO="));
            break;
        case XMO:
            sb.Append(TEXT("XMO="));
            break;
        case XNO:
            sb.Append(TEXT("XNO="));
            break;
        case EPOCH:
            sb.Append(TEXT("EPOCH="));
            break;
        }

        sb += USpiceTypes::FormatDouble(elems[i]);
    }

    sb.AppendChar(TCHAR(')'));

    return sb.ToString();
}

FString FSTLEGeophysicalConstants::ToString() const
{
    static TStringBuilder<1024> sb;

    sb.Reset();

    sb.AppendChar(TCHAR('('));
    bool AppendSpace = false;

    for (int i = 0; i < geophs.Num(); ++i)
    {
        if (AppendSpace)
        {
            sb.Append(TEXT(", "));
            AppendSpace = true;
        }
        sb += USpiceTypes::FormatDouble(geophs[i]);
    }

    sb.AppendChar(TCHAR(')'));

    return sb.ToString();
}

FString FSLimptPoint::ToString() const
{
    return FString::Printf(TEXT("(point %s; epoch %s; tangt %s)"), *point.ToString(), *epoch.ToString(), *tangt.ToString());
}

FString FSLimptCut::ToString() const
{
    static TStringBuilder<1024> sb;

    sb.Reset();

    sb.AppendChar(TCHAR('{'));
    bool AppendSpace = false;

    for (int i = 0; i < points.Num(); ++i)
    {
        if (AppendSpace)
        {
            sb.Append(TEXT(", "));
            AppendSpace = true;
        }
        sb += points[i].ToString();
    }

    sb.AppendChar(TCHAR('}'));

    return sb.ToString();
}

FString FSTermptPoint::ToString() const
{
    return FString::Printf(TEXT("(point %s; epoch %s; trmvc %s)"), *point.ToString(), *epoch.ToString(), *trmvc.ToString());
}

FString FSTermptCut::ToString() const
{
    static TStringBuilder<1024> sb;

    sb.Reset();

    sb.AppendChar(TCHAR('{'));
    bool AppendSpace = false;

    for (int i = 0; i < points.Num(); ++i)
    {
        if (AppendSpace)
        {
            sb.Append(TEXT(", "));
            AppendSpace = true;
        }
        sb += points[i].ToString();
    }

    sb.AppendChar(TCHAR('}'));

    return sb.ToString();
}

FString FSRay::ToString() const
{
    return FString::Printf(TEXT("(point %s, stop %s)"), *direction.ToString(), *direction.ToString());
}

FString FSDLADescr::ToString() const
{
    return FString::Printf(
        TEXT("(bwdptr %d, fwdptr %d, ibase %d, isize %d, dbase %d, dsize %d, cbase %d, csize %d)"),
        bwdptr,
        fwdptr,
        ibase,
        isize,
        dbase,
        dsize,
        cbase,
        csize
    );
}

FString FSDSKDescr::ToString() const
{
    static TStringBuilder<1024> sb;

    sb.Reset();
    sb.Appendf(TEXT("{surfce=%d "), surfce);
    sb.Appendf(TEXT("center=%d "), center);
    sb.Appendf(TEXT("dclass=%d "), dclass);
    sb.Appendf(TEXT("dtype=%d "), dtype);
    sb.Appendf(TEXT("frmcde=%d "), frmcde);
    sb.Appendf(TEXT("corsys=%d, ("), corsys);

    sb.AppendChar(TCHAR('{'));
    bool AppendSpace = false;

    for (int i = 0; i < corpar.Num(); ++i)
    {
        if (AppendSpace)
        {
            sb.Append(TEXT(", "));
            AppendSpace = true;
        }
        sb.Appendf(TEXT("%f"), corpar[i]);
    }

    sb.Appendf(TEXT("), co1min=%f "), co1min);
    sb.Appendf(TEXT("co1max=%f "), co1max);
    sb.Appendf(TEXT("co2min=%f "), co2min);
    sb.Appendf(TEXT("co2max=%f "), co2max);
    sb.Appendf(TEXT("co3min=%f "), co3min);
    sb.Appendf(TEXT("co3max=%f "), co3max);
    sb.Appendf(TEXT("start=%f "), start);
    sb.Appendf(TEXT("stop=%f}"), stop);

    return sb.ToString();
}

FString FSPlateIndices::ToString() const
{
    return FString::Printf(TEXT("(%d, %d, %d)"), i0, i1, i2);
}


double FSDistance::AsNauticalMiles() const
{
    double _nm;
    convrt_c(km, MaxQ::Core::ToANSIString(ES_Units::KILOMETERS), MaxQ::Core::ToANSIString(ES_Units::NAUTICAL_MILES), &_nm);
    UnexpectedErrorCheck(false);
    return _nm;
}

FSDistance FSDistance::FromNauticalMiles(double _nm)
{
    double km;
    convrt_c(_nm, MaxQ::Core::ToANSIString(ES_Units::NAUTICAL_MILES), MaxQ::Core::ToANSIString(ES_Units::KILOMETERS), &km);
    UnexpectedErrorCheck(false);
    return FSDistance(km);
}

double FSDistance::AsStatuteMiles() const
{
    double _miles;
    convrt_c(km, MaxQ::Core::ToANSIString(ES_Units::KILOMETERS), MaxQ::Core::ToANSIString(ES_Units::STATUTE_MILES), &_miles);
    UnexpectedErrorCheck(false);
    return _miles;
}

FSDistance FSDistance::FromStatuteMiles(double _miles)
{
    double km;
    convrt_c(_miles, MaxQ::Core::ToANSIString(ES_Units::STATUTE_MILES), MaxQ::Core::ToANSIString(ES_Units::KILOMETERS), &km);
    UnexpectedErrorCheck(false);
    return FSDistance(km);
}

double FSDistance::AsFeet() const
{
    double _feet;
    convrt_c(km, MaxQ::Core::ToANSIString(ES_Units::KILOMETERS), MaxQ::Core::ToANSIString(ES_Units::FEET), &_feet);
    UnexpectedErrorCheck(false);
    return _feet;
}

FSDistance FSDistance::FromFeet(double _feet)
{
    double km;
    convrt_c(_feet, MaxQ::Core::ToANSIString(ES_Units::FEET), MaxQ::Core::ToANSIString(ES_Units::KILOMETERS), &km);
    UnexpectedErrorCheck(false);
    return FSDistance(km);
}

double FSDistance::AsAstronomicalUnits() const
{
    double _au;
    convrt_c(km, MaxQ::Core::ToANSIString(ES_Units::KILOMETERS), MaxQ::Core::ToANSIString(ES_Units::AU), &_au);
    UnexpectedErrorCheck(false);
    return _au;
}

FSDistance FSDistance::FromAstronomicalUnits(double _au)
{
    double km;
    convrt_c(_au, MaxQ::Core::ToANSIString(ES_Units::AU), MaxQ::Core::ToANSIString(ES_Units::KILOMETERS), &km);
    UnexpectedErrorCheck(false);
    return FSDistance(km);
}

double FSDistance::AsLightYears() const
{
    double _ly;
    convrt_c(km, MaxQ::Core::ToANSIString(ES_Units::KILOMETERS), MaxQ::Core::ToANSIString(ES_Units::LIGHTYEARS), &_ly);
    UnexpectedErrorCheck(false);
    return _ly;
}


FSDistance FSDistance::FromLightYears(double _ly)
{
    double km;
    convrt_c(_ly, MaxQ::Core::ToANSIString(ES_Units::LIGHTYEARS), MaxQ::Core::ToANSIString(ES_Units::KILOMETERS), &km);
    UnexpectedErrorCheck(false);
    return FSDistance(km);
}


FSAngle::FSAngle()
{
    // See notes about cachedPi in its declaration
    cachedDpr = dpr_c();

    degrees = 0.;
}

FSAngle::FSAngle(double __radians)
{
    // See notes about cachedPi in its declaration
    cachedDpr = dpr_c();

    degrees = __radians * cachedDpr;
}

FSAngle::FSAngle(const double (&__degrees)[1])
{
    // See notes about cachedPi in its declaration
    cachedDpr = dpr_c();

    degrees = __degrees[0];
}

double FSAngularRate::AsDegreesPerSecond() const
{
    return radiansPerSecond * dpr_c();
}

FSAngularRate FSAngularRate::FromDegreesPerSecond(double DegreesPerSecond)
{
    return FSAngularRate(DegreesPerSecond * rpd_c());
}



void FSDimensionlessVector::Normalize()
{
    Normalize(*this);
}

void FSDimensionlessVector::Normalize(FSDimensionlessVector& v)
{
    SpiceDouble xyz[3];
    v.CopyTo(xyz);
    vhat_c(xyz, xyz);
    v = FSDimensionlessVector(xyz);
}


FSDimensionlessVector FSDimensionlessVector::Normalized() const
{
    SpiceDouble xyz[3];
    CopyTo(xyz);
    vhat_c(xyz, xyz);
    return FSDimensionlessVector(xyz);
}




FSDimensionlessVector FSDistanceVector::Normalized() const
{
    SpiceDouble xyz[3];
    CopyTo(xyz);
    vhat_c(xyz, xyz);
    return FSDimensionlessVector(xyz);
}

double FSDimensionlessVector::Magnitude() const
{
    SpiceDouble xyz[3];
    CopyTo(xyz);
    return vnorm_c(xyz);
}

FSDistance FSDistanceVector::Magnitude() const
{
    SpiceDouble xyz[3];
    CopyTo(xyz);
    return FSDistance(vnorm_c(xyz));
}

void FSDistanceVector::Normalized(FSDimensionlessVector& v) const
{
    v = Normalized();
}

FSDimensionlessVector FSVelocityVector::Normalized() const
{
    SpiceDouble xyz[3];
    CopyTo(xyz);
    vhat_c(xyz, xyz);
    return FSDimensionlessVector(xyz);
}

void FSVelocityVector::Normalized(FSDimensionlessVector& v) const
{
    v = Normalized();
}

FSSpeed FSVelocityVector::Magnitude() const
{
    SpiceDouble xyz[3];
    CopyTo(xyz);
    return FSSpeed(vnorm_c(xyz));
}


void FSAngularVelocity::Normalized(FSDimensionlessVector& v) const
{
    v = Normalized();
}

FSDimensionlessVector FSAngularVelocity::Normalized() const
{
    SpiceDouble xyz[3];
    CopyTo(xyz);
    vhat_c(xyz, xyz);
    return FSDimensionlessVector(xyz);
}

FSAngularRate FSAngularVelocity::Magnitude() const
{
    SpiceDouble xyz[3];
    CopyTo(xyz);
    return FSAngularRate(vnorm_c(xyz));
}



