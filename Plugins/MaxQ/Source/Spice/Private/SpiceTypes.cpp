// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "SpiceTypes.h"
#include "Containers/StringFwd.h"
#include "Spice.h"
#include "SpiceUtilities.h"

#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>


PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
extern "C"
{
#include "SpiceUsr.h"
}
PRAGMA_POP_PLATFORM_DEFAULT_PACKING


// Create a future regret:
//  1 platform differentiation
//  2 using std::basic_ostringstream at all
// ostringstream supports prettier angle formating in formatAngle
#if PLATFORM_WIDECHAR_IS_CHAR16
// Mac supports WIDECHAR as char16_t, which has no std::basic_ostringstream implementation
#define EXTENDED_CHAR(x) x
#define EXTENDED_CHAR_TYPE ANSICHAR
#else
#define EXTENDED_CHAR(x) L ## x
#define EXTENDED_CHAR_TYPE WIDECHAR
#endif


DEFINE_LOG_CATEGORY(LogSpice);

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
    return FString::Printf(TEXT("{%s %s %s}(%s * %s * %s)"), *USpiceTypes::ToString(axis3), *USpiceTypes::ToString(axis2), *USpiceTypes::ToString(axis1), *angle3.ToString(), *angle2.ToString(), *angle1.ToString());
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
    return FString::Printf(TEXT("{%s %s %s}(%s * %s * %s) d/dt(%s * %s * %s)"), *USpiceTypes::ToString(axis3), *USpiceTypes::ToString(axis2), *USpiceTypes::ToString(axis1), *angle3.ToString(), *angle2.ToString(), *angle1.ToString(), *rate3.ToString(), *rate2.ToString(), *rate1.ToString());
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
    return USpiceTypes::Swizzle(*this);
}

FSAngularVelocity FSAngularVelocity::Swizzle(const FVector& UEVector)
{
    FSAngularVelocity av;
    USpiceTypes::Swizzle(UEVector, av);

    return av;
}

FVector FSDimensionlessVector::Swizzle() const
{
    return USpiceTypes::Swizzle(*this);
}

FSDimensionlessVector FSDimensionlessVector::Swizzle(const FVector& UEVector)
{
    FSDimensionlessVector vec;
    USpiceTypes::Swizzle(UEVector, vec);

    return vec;
}


FVector FSDistanceVector::Swizzle() const
{
    return USpiceTypes::Swizzle(*this);
}

FSDistanceVector FSDistanceVector::Swizzle(const FVector& UEVector)
{
    FSDistanceVector vec;
    USpiceTypes::Swizzle(UEVector, vec);

    return vec;
}


FVector FSVelocityVector::Swizzle() const
{
    return USpiceTypes::Swizzle(*this);
}

FSVelocityVector FSVelocityVector::Swizzle(const FVector& UEVector)
{
    FSVelocityVector vec;
    USpiceTypes::Swizzle(UEVector, vec);

    return vec;
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
    // Swazzle = Fancier name for "Swizzle"
    // (It's actually because Blueprints doesn't support overloading names.)
    return USpiceTypes::Swazzle(*this);
}

FSQuaternion FSQuaternion::Swizzle(const FQuat& UnrealQuat)
{
    return USpiceTypes::Swazzle(UnrealQuat);
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
    convrt_c(km, USpiceTypes::toString(ES_Units::KILOMETERS), USpiceTypes::toString(ES_Units::NAUTICAL_MILES), &_nm);
    UnexpectedErrorCheck(false);
    return _nm;
}

FSDistance FSDistance::FromNauticalMiles(double _nm)
{
    double km;
    convrt_c(_nm, USpiceTypes::toString(ES_Units::NAUTICAL_MILES), USpiceTypes::toString(ES_Units::KILOMETERS), &km);
    UnexpectedErrorCheck(false);
    return FSDistance(km);
}

double FSDistance::AsStatuteMiles() const
{
    double _miles;
    convrt_c(km, USpiceTypes::toString(ES_Units::KILOMETERS), USpiceTypes::toString(ES_Units::STATUTE_MILES), &_miles);
    UnexpectedErrorCheck(false);
    return _miles;
}

FSDistance FSDistance::FromStatuteMiles(double _miles)
{
    double km;
    convrt_c(_miles, USpiceTypes::toString(ES_Units::STATUTE_MILES), USpiceTypes::toString(ES_Units::KILOMETERS), &km);
    UnexpectedErrorCheck(false);
    return FSDistance(km);
}

double FSDistance::AsFeet() const
{
    double _feet;
    convrt_c(km, USpiceTypes::toString(ES_Units::KILOMETERS), USpiceTypes::toString(ES_Units::FEET), &_feet);
    UnexpectedErrorCheck(false);
    return _feet;
}

FSDistance FSDistance::FromFeet(double _feet)
{
    double km;
    convrt_c(_feet, USpiceTypes::toString(ES_Units::FEET), USpiceTypes::toString(ES_Units::KILOMETERS), &km);
    UnexpectedErrorCheck(false);
    return FSDistance(km);
}

double FSDistance::AsAstronomicalUnits() const
{
    double _au;
    convrt_c(km, USpiceTypes::toString(ES_Units::KILOMETERS), USpiceTypes::toString(ES_Units::AU), &_au);
    UnexpectedErrorCheck(false);
    return _au;
}

FSDistance FSDistance::FromAstronomicalUnits(double _au)
{
    double km;
    convrt_c(_au, USpiceTypes::toString(ES_Units::AU), USpiceTypes::toString(ES_Units::KILOMETERS), &km);
    UnexpectedErrorCheck(false);
    return FSDistance(km);
}

double FSDistance::AsLightYears() const
{
    double _ly;
    convrt_c(km, USpiceTypes::toString(ES_Units::KILOMETERS), USpiceTypes::toString(ES_Units::LIGHTYEARS), &_ly);
    UnexpectedErrorCheck(false);
    return _ly;
}


FSDistance FSDistance::FromLightYears(double _ly)
{
    double km;
    convrt_c(_ly, USpiceTypes::toString(ES_Units::LIGHTYEARS), USpiceTypes::toString(ES_Units::KILOMETERS), &km);
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


/*
*  NOTE: 
     See comments in SpiceTypes.h (EnumAsString)
     Yes, we really want to hardcode these toString's vs pulling values from UE reflection.
*/
const char* USpiceTypes::toString(ES_Units units)
{
    switch (units)
    {
    case ES_Units::RADIANS:
        return "RADIANS";
    case ES_Units::DEGREES:
        return "DEGREES";
    case ES_Units::ARCMINUTES:
        return "ARCMINUTES";
    case ES_Units::ARCSECONDS:
        return "ARCSECONDS";
    case ES_Units::HOURANGLE:
        return "HOURANGLE";
    case ES_Units::MINUTEANGLE:
        return "MINUTEANGLE";
    case ES_Units::SECONDANGLE:
        return "SECONDANGLE";
    case ES_Units::METERS:
        return "METERS";
    case ES_Units::KILOMETERS:
        return "KILOMETERS";
    case ES_Units::CENTIMETERS:
        return "CENTIMETERS";
    case ES_Units::MILLIMETERS:
        return "MILLIMETERS";
    case ES_Units::FEET:
        return "FEET";
    case ES_Units::INCHES:
        return "INCHES";
    case ES_Units::YARDS:
        return "YARDS";
    case ES_Units::STATUTE_MILES:
        return "STATUTE_MILES";
    case ES_Units::NAUTICAL_MILES:
        return "NAUTICAL_MILES";
    case ES_Units::AU:
        return "AU";
    case ES_Units::PARSECS:
        return "PARSECS";
    case ES_Units::LIGHTSECS:
        return "LIGHTSECS";
    case ES_Units::LIGHTYEARS:
        return "LIGHTYEARS";
    case ES_Units::SECONDS:
        return "SECONDS";
    case ES_Units::MINUTES:
        return "MINUTES";
    case ES_Units::HOURS:
        return "HOURS";
    case ES_Units::DAYS:
        return "DAYS";
    case ES_Units::JULIAN_YEARS:
        return "JULIAN_YEARS";
    case ES_Units::TROPICAL_YEARS:
        return "TROPICAL_YEARS";
    case ES_Units::YEARS:
        return "YEARS";
    }

    return "NONE";
}

const char* USpiceTypes::toString(ES_ReferenceFrameLocus locus)
{
    switch (locus)
    {
    case ES_ReferenceFrameLocus::OBSERVER:
        return "OBSERVER";
    case ES_ReferenceFrameLocus::TARGET:
        return "TARGET";
    case ES_ReferenceFrameLocus::CENTER:
        return "CENTER";
    }

    return "NONE";
}

const char* USpiceTypes::toString(ES_AberrationCorrectionWithNewtonians abcorr)
{
    switch (abcorr)
    {
    case ES_AberrationCorrectionWithNewtonians::LT:
        return "LT";
    case ES_AberrationCorrectionWithNewtonians::LT_S:
        return "LT+S";
    case ES_AberrationCorrectionWithNewtonians::CN:
        return "CN";
    case ES_AberrationCorrectionWithNewtonians::CN_S:
        return "CN+S";
    }

    return "NONE";
}


const char* USpiceTypes::toString(ES_AberrationCorrectionFov abcorr)
{
    switch (abcorr)
    {
    case ES_AberrationCorrectionFov::S:
        return "S";
    case ES_AberrationCorrectionFov::XS:
        return "XS";
    }

    return "NONE";
}

const char* USpiceTypes::toString(ES_AberrationCorrectionLocus corloc)
{
    switch (corloc)
    {
    case ES_AberrationCorrectionLocus::CENTER:
        return "CENTER";
    case ES_AberrationCorrectionLocus::ELLIPSOID_LIMB:
        return "ELLIPSOID LIMB";
    }

    return "NONE";
}


const char* toString(ES_AberrationCorrectionLocusTerminator corloc)
{
    switch (corloc)
    {
    case ES_AberrationCorrectionLocusTerminator::CENTER:
        return "CENTER";
    case ES_AberrationCorrectionLocusTerminator::ELLIPSOID_TERMINATOR:
        return "ELLIPSOID TERMINATOR";
    }

    return "NONE";
}

const char* USpiceTypes::toString(ES_TimeScale timeScale)
{
    switch (timeScale)
    {
    case ES_TimeScale::TAI:
        return "TAI";
    case ES_TimeScale::TDB:
        return "TDB";
    case ES_TimeScale::TDT:
        return "TDT";
    case ES_TimeScale::ET:
        return "ET";
    case ES_TimeScale::JDTDB:
        return "JDTDB";
    case ES_TimeScale::JDTDT:
        return "JDTDT";
    case ES_TimeScale::JED:
        return "JED";
    }

    return "NONE";
}

const char* USpiceTypes::toString(ES_AberrationCorrectionForOccultation abcorr)
{
    switch (abcorr)
    {
    case ES_AberrationCorrectionForOccultation::LT:
        return "LT";
    case ES_AberrationCorrectionForOccultation::CN:
        return "CN";
    case ES_AberrationCorrectionForOccultation::XLT:
        return "XLT";
    case ES_AberrationCorrectionForOccultation::XCN:
        return "XCN";
    }

    return "NONE";
}

const char* USpiceTypes::toString(ES_AberrationCorrectionWithTransmissions abcorr)
{
    switch (abcorr)
    {
    case ES_AberrationCorrectionWithTransmissions::LT:
        return "LT";
    case ES_AberrationCorrectionWithTransmissions::LT_S:
        return "LT+S";
    case ES_AberrationCorrectionWithTransmissions::CN:
        return "CN";
    case ES_AberrationCorrectionWithTransmissions::CN_S:
        return "CN+S";
    case ES_AberrationCorrectionWithTransmissions::XLT:
        return "XLT";
    case ES_AberrationCorrectionWithTransmissions::XLT_S:
        return "XLT+S";
    case ES_AberrationCorrectionWithTransmissions::XCN:
        return "XCN";
    case ES_AberrationCorrectionWithTransmissions::XCN_S:
        return "XCN+S";
    };

    return "NONE";
}


const char* USpiceTypes::toString(ES_GeometricModel model)
{

    if (model == ES_GeometricModel::ELLIPSOID)
    {
        return "ELLIPSOID";
    }
    else if (model == ES_GeometricModel::POINT)
    {
        return "POINT";
    }

    return "NONE";
}


const char* USpiceTypes::toString(ES_OtherGeometricModel model)
{
    if (model == ES_OtherGeometricModel::SPHERE)
    {
        return "SPHERE";
    }
    else if (model == ES_OtherGeometricModel::POINT)
    {
        return "POINT";
    }

    return "NONE";
}

const char* USpiceTypes::toString(ES_IlluminationAngleType angleType)
{
    switch (angleType)
    {
    case ES_IlluminationAngleType::PHASE:
        return "PHASE";
    case ES_IlluminationAngleType::INCIDENCE:
        return "INCIDENCE";
    case ES_IlluminationAngleType::EMISSION:
        return "EMISSION";
    }

    return "NONE";
}

FString USpiceTypes::toFString(ES_GeometricModel model, const TArray<FString>& shapeSurfaces)
{

    if (model == ES_GeometricModel::ELLIPSOID)
    {
        return FString(TEXT("ELLIPSOID"));
    }
    else if (model == ES_GeometricModel::POINT)
    {
        return FString(TEXT("POINT"));
    }

    // From the docs:
    // "DSK/UNPRIORITIZED[/SURFACES = <surface list>]"
    // Which makes it look like UPRIORITIZED isn't optional or mutually esclusive with a list of surfaces..
    // Is that correct, though?

    FString result = "DSK/UNPRIORITIZED";

    if (shapeSurfaces.Num() > 0)
    {
        result += "/SURFACES = ";

        int num = shapeSurfaces.Num();

        for (int i = 0; i < num; ++i)
        {
            result += shapeSurfaces[i];

            if (i + 1 < num)
            {
                result += ", ";
            }
        }
    }

    return result;
}

FString USpiceTypes::ToString(ES_Axis Axis)
{
    const TCHAR* sz = TEXT("No_Axis");
    switch (Axis)
    {
        case ES_Axis::X:
            sz = TEXT("X_Axis");
            break;
        case ES_Axis::Y:
            sz = TEXT("Y_Axis Axis");
            break;
        case ES_Axis::Z:
            sz = TEXT("Z_Axis Axis");
            break;
    }

    return FString(sz);
}

const char* USpiceTypes::toString(ES_SubpointComputationMethod method)
{
    if (method == ES_SubpointComputationMethod::NEAR_POINT_ELLIPSOID)
    {
        return "NEAR POINT/ELLIPSOID";
    }
    else if (method == ES_SubpointComputationMethod::INTERCEPT_ELLIPSOID)
    {
        return "INTERCEPT/ELLIPSOID";
    }
    
    return "NONE";
}


FString USpiceTypes::toFString(ES_ComputationMethod method, const TArray<FString>& shapeSurfaces)
{
    if (method == ES_ComputationMethod::NEAR_POINT_ELLIPSOID)
    {
        return FString(TEXT("NEAR POINT/ELLIPSOID"));
    }
    else if (method == ES_ComputationMethod::INTERCEPT_ELLIPSOID)
    {
        return FString(TEXT("INTERCEPT/ELLIPSOID"));
    }

    FString result;

    if (method == ES_ComputationMethod::NADIR_DSK)
    {
        result = FString(TEXT("NADIR/DSK/UNPRIORITIZED"));
    }
    else if (method == ES_ComputationMethod::INTERCEPT_DSK)
    {
        result = FString(TEXT("INTERCEPT/DSK/UNPRIORITIZED"));
    }
    else
    {
        result = "NONE";
    }

    if (shapeSurfaces.Num() > 0)
    {
        result += "/SURFACES = ";

        int num = shapeSurfaces.Num();

        for (int i = 0; i < num; ++i)
        {
            result += shapeSurfaces[i];

            if (i + 1 < num)
            {
                result += ", ";
            }
        }
    }

    return result;
}

FString USpiceTypes::toFString(ES_LimbComputationMethod method, const TArray<FString>& shapeSurfaces)
{
    if (method == ES_LimbComputationMethod::TANGENT_ELLIPSOID)
    {
        return FString(TEXT("TANGENT/ELLIPSOID"));
    }
    else if (method == ES_LimbComputationMethod::GUIDED_ELLIPSOID)
    {
        return FString(TEXT("GUIDED/ELLIPSOID"));
    }

    FString result;

    if (method == ES_LimbComputationMethod::TANGENT_DSK)
    {
        result = FString(TEXT("TANGENT/DSK/UNPRIORITIZED"));
    }
    else if (method == ES_LimbComputationMethod::GUIDED_DSK)
    {
        result = FString(TEXT("GUIDED/DSK/UNPRIORITIZED"));
    }
    else
    {
        result = "NONE";
    }

    if (shapeSurfaces.Num() > 0)
    {
        result += "/SURFACES = ";

        int num = shapeSurfaces.Num();

        for (int i = 0; i < num; ++i)
        {
            result += shapeSurfaces[i];

            if (i + 1 < num)
            {
                result += ", ";
            }
        }
    }

    return result;
}

FString USpiceTypes::toFString(ES_Shadow shadow, ES_CurveType curveType, ES_GeometricModel method, const TArray<FString>& shapeSurfaces)
{
    FString result = "";

    if (shadow == ES_Shadow::UMBRAL)
    {
        result += FString(TEXT("UMBRAL/"));
    }
    else if (shadow == ES_Shadow::PENUMBRAL)
    {
        result += FString(TEXT("PENUMBRAL/"));
    }

    if (curveType == ES_CurveType::TANGENT)
    {
        result += FString(TEXT("TANGENT/"));
    }
    else if (curveType == ES_CurveType::GUIDED)
    {
        result += FString(TEXT("GUIDED/"));
    }

    if (method == ES_GeometricModel::DSK)
    {
        result += FString(TEXT("DSK/UNPRIORITIZED"));
    }
    else if (method == ES_GeometricModel::ELLIPSOID)
    {
        result += FString(TEXT("ELLIPSOID"));
        return result;
    }
    else if (method == ES_GeometricModel::POINT)
    {
        // Technically, POINT is not not valid in this case.... But:
        // CSPICE validates its inputs perfectly well, we don't have to.
        result += FString(TEXT("POINT"));
        return result;
    }
    else
    {
        result += FString(TEXT("NONE"));
    }

    if (shapeSurfaces.Num() > 0)
    {
        result += "/SURFACES = ";

        int num = shapeSurfaces.Num();

        for (int i = 0; i < num; ++i)
        {
            result += shapeSurfaces[i];

            if (i + 1 < num)
            {
                result += ", ";
            }
        }
    }

    return result;
}


const char* USpiceTypes::toString(ES_RelationalOperator relate)
{
    switch (relate)
    {
    case ES_RelationalOperator::GreaterThan:
        return ">";
        break;
    case ES_RelationalOperator::Equal:
        return "=";
        break;
    case ES_RelationalOperator::LessThan:
        return "<";
        break;
    case ES_RelationalOperator::ABSMAX:
        return "ABSMAX";
        break;
    case ES_RelationalOperator::ABSMIN:
        return "ABSMIN";
        break;
    case ES_RelationalOperator::LOCMAX:
        return "LOCMAX";
        break;
    case ES_RelationalOperator::LOCMIN:
        return "LOCMIN";
        break;
    };

    return "NONE";
}



const char* USpiceTypes::toString(ES_CoordinateSystemInclRadec coords)
{
    check((uint8)ES_CoordinateSystem::RECTANGULAR == (uint8)ES_CoordinateSystemInclRadec::RECTANGULAR);
    check((uint8)ES_CoordinateSystem::CYLINDRICAL == (uint8)ES_CoordinateSystemInclRadec::CYLINDRICAL);
    check((uint8)ES_CoordinateSystem::LATITUDINAL == (uint8)ES_CoordinateSystemInclRadec::LATITUDINAL);
    check((uint8)ES_CoordinateSystem::SPHERICAL == (uint8)ES_CoordinateSystemInclRadec::SPHERICAL);
    check((uint8)ES_CoordinateSystem::GEODETIC == (uint8)ES_CoordinateSystemInclRadec::GEODETIC);
    check((uint8)ES_CoordinateSystem::PLANETOGRAPHIC == (uint8)ES_CoordinateSystemInclRadec::PLANETOGRAPHIC);

    switch (coords)
    {
    case ES_CoordinateSystemInclRadec::RECTANGULAR:
        return "RECTANGULAR";
    case ES_CoordinateSystemInclRadec::CYLINDRICAL:
        return "CYLINDRICAL";
    case ES_CoordinateSystemInclRadec::LATITUDINAL:
        return "LATITUDINAL";
    case ES_CoordinateSystemInclRadec::SPHERICAL:
        return "SPHERICAL";
    case ES_CoordinateSystemInclRadec::GEODETIC:
        return "GEODETIC";
    case ES_CoordinateSystemInclRadec::PLANETOGRAPHIC:
        return "PLANETOGRAPHIC";
    case ES_CoordinateSystemInclRadec::RADEC:
        return "RA/DEC";
    };

    return "NONE";
}


const char* USpiceTypes::toString(ES_CoordinateSystem coords)
{
    return toString((ES_CoordinateSystemInclRadec)coords);
}

const char* USpiceTypes::toString(ES_CoordinateName coord)
{
    switch (coord)
    {
    case ES_CoordinateName::X:
        return "X";
    case ES_CoordinateName::Y:
        return "Y";
    case ES_CoordinateName::Z:
        return "Z";
    case ES_CoordinateName::RADIUS:
        return "RADIUS";
    case ES_CoordinateName::LONGITUDE:
        return "LONGITUDE";
    case ES_CoordinateName::LATITUDE:
        return "LATITUDE";
    case ES_CoordinateName::RANGE:
        return "RANGE";
    case ES_CoordinateName::RIGHT_ASCENSION:
        return "RIGHT ASCENSION";
    case ES_CoordinateName::DECLINATION:
        return "DECLINATION";
    case ES_CoordinateName::COLATITUDE:
        return "COLATITUDE";
    case ES_CoordinateName::ALTITUDE:
        return "ALTITUDE";
    };

    return "NONE";
}


void FSTwoLineElements::CopyTo(double(&_elems)[10]) const
{
    if (elems.Num() == 10)
    {
        FMemory::Memcpy(_elems, elems.GetData(),sizeof(double[10]));
    }
    else
    {
        setmsg_c("FSTwoLineElements uninitialized.  Array Length: #");
        errint_c("#", elems.Num());
        sigerr_c("SPICE(VALUEOUTOFRANGE)");
    }
}


void FSTLEGeophysicalConstants::CopyTo(double(&_geophs)[8]) const
{
    if (geophs.Num() == 8)
    {
        FMemory::Memcpy(_geophs, geophs.GetData(), sizeof(double[8]));
    }
    else
    {
        setmsg_c("FSTLEGeophysicalConstants uninitialized.  Array Length: #");
        errint_c("#", geophs.Num());
        sigerr_c("SPICE(VALUEOUTOFRANGE)");
    }
}



FSEulerAngles::FSEulerAngles(const FSDimensionlessVector& value)
{
    angle3 = FSAngle(value.x);
    angle2 = FSAngle(value.y);
    angle1 = FSAngle(value.z);
    axis3 = ES_Axis::X;
    axis2 = ES_Axis::Y;
    axis1 = ES_Axis::Z;
}

void FSEulerAngles::AsDimensionlessVector(FSDimensionlessVector& vector) const
{
    if ((axis3 == ES_Axis::X) && (axis2 == ES_Axis::Y) && (axis1 == ES_Axis::Z))
    {
        // Already ZYX
        vector.x = angle3.AsSpiceDouble();
        vector.y = angle2.AsSpiceDouble();
        vector.z = angle1.AsSpiceDouble();
    }
    else
    {
        // Convert the eulers into ZYX representation
        SpiceDouble _r[3][3];
        SpiceDouble _eulang3 = angle3.AsSpiceDouble();
        SpiceDouble _eulang2 = angle2.AsSpiceDouble();
        SpiceDouble _eulang1 = angle1.AsSpiceDouble();
        SpiceInt _axis3 = (SpiceInt)axis3;
        SpiceInt _axis2 = (SpiceInt)axis2;
        SpiceInt _axis1 = (SpiceInt)axis1;

        eul2m_c(_eulang3, _eulang2, _eulang1, _axis3, _axis2, _axis1, _r);

        _axis3 = (SpiceInt)ES_Axis::X;
        _axis2 = (SpiceInt)ES_Axis::Y;
        _axis1 = (SpiceInt)ES_Axis::Z;

        m2eul_c(_r, _axis3, _axis2, _axis1, &vector.x, &vector.y, &vector.z);
    }
}


FSDLADescr::FSDLADescr(void* descr)
{
    SpiceDLADescr* dla = (SpiceDLADescr*)descr;
    bwdptr = dla->bwdptr;
    fwdptr = dla->fwdptr;
    ibase = dla->ibase;
    isize = dla->isize;
    dbase = dla->dbase;
    dsize = dla->dsize;
    cbase = dla->cbase;
    csize = dla->csize;
}

void FSDLADescr::CopyTo(void* descr) const
{
    SpiceDLADescr* dla = (SpiceDLADescr*)descr;

    dla->bwdptr = bwdptr;
    dla->fwdptr = fwdptr;
    dla->ibase = ibase;
    dla->isize = isize;
    dla->dbase = dbase;
    dla->dsize = dsize;
    dla->cbase = cbase;
    dla->csize = csize;
}

FSDSKDescr::FSDSKDescr(void* descr)
{
    SpiceDSKDescr* dsk = (SpiceDSKDescr*)descr;

    surfce = dsk->surfce;
    center = dsk->center;
    dclass = dsk->dclass;
    dtype = dsk->dtype;
    frmcde = dsk->frmcde;
    corsys = dsk->corsys;
    corpar = TArray<double>();
    corpar.Init(0., SPICE_DSK_NSYPAR);
    check(sizeof(double) == sizeof(SpiceDouble));
    FMemory::Memcpy(corpar.GetData(), dsk->corpar, SPICE_DSK_NSYPAR * sizeof(SpiceDouble));
    co1min = dsk->co1min;
    co1max = dsk->co1max;
    co2min = dsk->co2min;
    co2max = dsk->co2max;
    co3min = dsk->co3min;
    co3max = dsk->co3max;
    start = dsk->start;
    stop = dsk->stop;
}

void FSDSKDescr::CopyTo(void* descr) const
{
    SpiceDSKDescr* dsk = (SpiceDSKDescr*)descr;

    dsk->surfce = surfce;
    dsk->center = center;
    dsk->dclass = dclass;
    dsk->dtype = dtype;
    dsk->frmcde = frmcde;
    dsk->corsys = corsys;
    check(sizeof(double) == sizeof(SpiceDouble));
    FMemory::Memcpy(dsk->corpar, corpar.GetData(), SPICE_DSK_NSYPAR * sizeof(SpiceDouble));
    dsk->co1min = co1min;
    dsk->co1max = co1max;
    dsk->co2min = co2min;
    dsk->co2max = co2max;
    dsk->co3min = co3min;
    dsk->co3max = co3max;
    dsk->start = start;
    dsk->stop = stop;
}



void USpiceTypes::day_period(FSEphemerisPeriod& oneDay)
{
    oneDay = FSEphemerisPeriod::OneDay;
}
void USpiceTypes::j2000_epoch(FSEphemerisTime& J2000)
{
    J2000 = FSEphemerisTime::J2000;
}

double USpiceTypes::Conv_SDistanceToDouble(const FSDistance& value)
{
    return value.AsSpiceDouble();
}

FSDistance USpiceTypes::Conv_DoubleToSDistance(double value)
{
    return FSDistance(value);
}

double USpiceTypes::Conv_SSpeedToDouble(
    const FSSpeed& value
)
{
    return value.AsSpiceDouble();
}

FSSpeed USpiceTypes::Conv_DoubleToSSpeed(
    double value
)
{
    return FSSpeed(value);
}

double USpiceTypes::Conv_SAngleToDouble(
    const FSAngle& value
)
{
    return value.AsSpiceDouble();
}

FSAngle USpiceTypes::Conv_DoubleToSAngle(
    double value
)
{
    return FSAngle(value);
}

double USpiceTypes::Conv_SAngularRateToDouble(
    const FSAngularRate& value
)
{
    return value.AsSpiceDouble();
}

FSAngularRate USpiceTypes::Conv_DoubleToSAngularRate(
    double value
)
{
    return FSAngularRate(value);
}

FSEphemerisTime USpiceTypes::Conv_StringToSEphemerisTime(const FString& time)
{
    return FSEphemerisTime::FromString(time);
}


FString USpiceTypes::Conv_SEphemerisTimeToString(const FSEphemerisTime& et)
{
    return et.ToString();
}

FSEphemerisPeriod USpiceTypes::Conv_FloatToSEphemerisPeriod(float period)
{
    return FSEphemerisPeriod(period);
}

double USpiceTypes::Conv_SEphemerisTimeToDouble(
    const FSEphemerisTime& value
)
{
    return value.AsSpiceDouble();
}

FSEphemerisTime USpiceTypes::Conv_DoubleToSEphemerisTime(
    double value
)
{
    return FSEphemerisTime(value);
}

double USpiceTypes::Conv_SEphemerisPeriodToDouble(
    const FSEphemerisPeriod& value
)
{
    return value.AsSpiceDouble();
}

FString USpiceTypes::Conv_SEphemerisPeriodToString(const FSEphemerisPeriod& value)
{
    return value.ToString();
}

FSEphemerisPeriod USpiceTypes::Conv_DoubleToSEphemerisPeriod(
    double value
)
{
    return FSEphemerisPeriod(value);
}

double USpiceTypes::Conv_SMassConstantToDouble(
    const FSMassConstant& value
)
{
    return value.AsSpiceDouble();
}

FSMassConstant USpiceTypes::Conv_DoubleToSMassConstant(
    double value
)
{
    return FSMassConstant(value);
}

FSDimensionlessVector USpiceTypes::Conv_SVelocityVectorToSDimensionlessVector(
    const FSVelocityVector& value
)
{
    FSDimensionlessVector result;
    value.AsDimensionlessVector(result);
    return result;
}


FSVelocityVector USpiceTypes::Conv_SDimensionlessVectorToSVelocityVector(
    const FSDimensionlessVector& value
)
{
    return FSVelocityVector(value);
}


FSDimensionlessVector USpiceTypes::Conv_SEulerAnglesToSDimensionlessVector(
    const FSEulerAngles& value
)
{
    FSDimensionlessVector result;
    value.AsDimensionlessVector(result);
    return result;
}

FSEulerAngles USpiceTypes::Conv_SDimensionlessVectorToSEulerAngles(
    const FSDimensionlessVector& value
)
{
    return FSEulerAngles(value);
}


FSDimensionlessVector USpiceTypes::Conv_SAngularVelocityToSDimensionlessVector(
    const FSAngularVelocity& value
)
{
    FSDimensionlessVector result;
    value.AsDimensionlessVector(result);
    return result;
}

FSAngularVelocity USpiceTypes::Conv_SDimensionlessVectorToSAngularVelocity(
    const FSDimensionlessVector& value
)
{
    return FSAngularVelocity(value);
}


FSDimensionlessVector USpiceTypes::Conv_SDistanceVectorToSDimensionlessVector(
    const FSDistanceVector& value
)
{
    FSDimensionlessVector result;
    value.AsDimensionlessVector(result);
    return result;
}

FSDistanceVector USpiceTypes::Conv_SDimensionlessVectorToSDistanceVector(
    const FSDimensionlessVector& value
)
{
    return FSDistanceVector(value);
}

FSRotationMatrix USpiceTypes::Conv_SQuaternionToSRotationMatrix(const FSQuaternion& value)
{
    FSRotationMatrix result;
    USpice::q2m(value, result);
    return result;
}

FSQuaternion USpiceTypes::Conv_SRotationMatrixToSQuaternion(const FSRotationMatrix& value)
{
    ES_ResultCode ResultCode;
    FString ErrorMessage;
    FSQuaternion result;
    
    USpice::m2q(ResultCode, ErrorMessage, value, result);
    
    return ResultCode == ES_ResultCode::Success ? result : FSQuaternion::Identity;
}


FSStateVector USpiceTypes::Conv_SDimensionlessStateVectorToSStateVector(
    const FSDimensionlessStateVector& value
)
{
    return FSStateVector(value);
}

FSCylindricalStateVector USpiceTypes::Conv_SDimensionlessStateVectorToSCylindricalStateVector(
    const FSDimensionlessStateVector& value
)
{
    return FSCylindricalStateVector(value);
}

FSLatitudinalStateVector USpiceTypes::Conv_SDimensionlessStateVectorToSLatitudinalStateVector(
    const FSDimensionlessStateVector& value
)
{
    return FSLatitudinalStateVector(value);
}

FSSphericalStateVector USpiceTypes::Conv_SDimensionlessStateVectorToSSphericalStateVector(
    const FSDimensionlessStateVector& value
)
{
    return FSSphericalStateVector(value);
}

FSGeodeticStateVector USpiceTypes::Conv_SDimensionlessStateVectorToSGeodeticStateVector(
    const FSDimensionlessStateVector& value
)
{
    return FSGeodeticStateVector(value);
}

FSPlanetographicStateVector USpiceTypes::Conv_SDimensionlessStateVectorToSPlanetographicStateVector(
    const FSDimensionlessStateVector& value
)
{
    return FSPlanetographicStateVector(value);
}

FSDimensionlessStateVector USpiceTypes::Conv_SStateVectorToSDimensionlessStateVector(
    const FSStateVector& value
)
{
    FSDimensionlessStateVector result;
    value.AsDimensionlessVectors(result);
    return result;
}

FSDimensionlessStateVector USpiceTypes::Conv_SCylindricalStateVectorToSDimensionlessStateVector(
    const FSCylindricalStateVector& value
)
{
    FSDimensionlessStateVector result;
    value.AsDimensionlessVectors(result);
    return result;
}

FSDimensionlessStateVector USpiceTypes::Conv_SLatitudinalStateVectorToSDimensionlessStateVector(
    const FSLatitudinalStateVector& value
)
{
    FSDimensionlessStateVector result;
    value.AsDimensionlessVectors(result);
    return result;
}

FSDimensionlessStateVector USpiceTypes::Conv_SSphericalStateVectorToSDimensionlessStateVector(
    const FSSphericalStateVector& value
)
{
    FSDimensionlessStateVector result;
    value.AsDimensionlessVectors(result);
    return result;
}

FSDimensionlessStateVector USpiceTypes::Conv_FSGeodeticStateVectorToSDimensionlessStateVector(
    const FSGeodeticStateVector& value
)
{
    FSDimensionlessStateVector result;
    value.AsDimensionlessVectors(result);
    return result;
}

FSDimensionlessStateVector USpiceTypes::Conv_FSPlanetographicStateVectorToSDimensionlessStateVector(
    const FSPlanetographicStateVector& value
)
{
    FSDimensionlessStateVector result;
    value.AsDimensionlessVectors(result);
    return result;
}


// Operators that lean on SPICE's CSPICE implementations instead of implement themselves...
FSRotationMatrix operator*(const FSRotationMatrix& lhs, const FSRotationMatrix& rhs)
{
    FSRotationMatrix result;
    USpice::mxm(lhs, rhs, result);
    return result;
}


void USpiceTypes::SingleEtWindow(
    const FSEphemerisTime& et0,
    const FSEphemerisTime& et1,
    TArray<FSEphemerisTimeWindowSegment>& Window
)
{
    Window.Empty();
    FSEphemerisTimeWindowSegment segment = FSEphemerisTimeWindowSegment(et0, et1);
    Window.Add(segment);
}

void USpiceTypes::Degrees2Angle(FSAngle& angle, double degrees)
{
    angle = FSAngle();
    angle.degrees = degrees;
}

void USpiceTypes::Angle2Degrees(const FSAngle& angle, double& degrees)
{
    degrees = angle.degrees;
}

void USpiceTypes::Radians2Angle(FSAngle& angle, double radians)
{
    angle = FSAngle(radians);
}

void USpiceTypes::Angle2Radians(const FSAngle& angle, double& radians)
{
    radians = angle.AsSpiceDouble();
}


FSRotationMatrix USpiceTypes::Multiply_SRotationMatrixSRotationMatrix(const FSRotationMatrix& A, const FSRotationMatrix& B)
{
    return A * B;
}


FSDimensionlessVector operator*(const FSRotationMatrix& lhs, const FSDimensionlessVector& rhs)
{
    FSDimensionlessVector result;
    USpice::mxv(lhs, rhs, result);
    return result;
}

FSDimensionlessVector USpiceTypes::MultiplyVec_SRotationMatrixSDimensionlessVector(const FSRotationMatrix& A, const FSDimensionlessVector& B)
{
    return A * B;
}

FSDistanceVector operator*(const FSRotationMatrix& lhs, const FSDistanceVector& rhs)
{
    FSDistanceVector result;
    USpice::mxv_distance(lhs, rhs, result);
    return result;
}

FSDistanceVector USpiceTypes::MultiplyDist_SRotationMatrixSDistanceVector(const FSRotationMatrix& A, const FSDistanceVector& B)
{
    return A * B;
}


FSVelocityVector operator*(const FSRotationMatrix& lhs, const FSVelocityVector& rhs)
{
    FSVelocityVector result;
    USpice::mxv_velocity(lhs, rhs, result);
    return result;
}

FSVelocityVector USpiceTypes::MultiplyVel_SRotationMatrixVelocityVector(const FSRotationMatrix& A, const FSVelocityVector& B)
{
    return A * B;
}



FSQuaternion operator*(const FSQuaternion& lhs, const FSQuaternion& rhs)
{
    FSQuaternion result;
    USpice::qxq(lhs, rhs, result);
    return result;
}

FSQuaternion USpiceTypes::Multiply_SQuaternionSQuaternion(const FSQuaternion& A, const FSQuaternion& B)
{
    return A * B;
}


/* Addition (A + B) */
FSEphemerisTime USpiceTypes::Add_SEphemerisTimeSEphemerisPeriod(const FSEphemerisTime& A, const FSEphemerisPeriod& B)
{
    return A + B;
}



/* Addition (A + B) */
FSEphemerisPeriod USpiceTypes::Add_SEphemerisPeriodSEphemerisPeriod(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return A + B;
}

FSEphemerisPeriod USpiceTypes::Subtract_SEphemerisPeriodSEphemerisPeriod(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return A - B;
}

/* Subtraction (A - B) */
FSEphemerisPeriod USpiceTypes::Subtract_SEphemerisTimeSEphemerisTime(const FSEphemerisTime& A, const FSEphemerisTime& B)
{
    return A - B;
}


/* Multiplication (A * B) */
FSEphemerisPeriod USpiceTypes::Multiply_SEphemerisPeriodDouble(const FSEphemerisPeriod& A, double B)
{
    return A * B;
}


/* Division (A / B) */
FSEphemerisPeriod USpiceTypes::Divide_SEphemerisPeriodDouble(const FSEphemerisPeriod& A, double B)
{
    return A / B;
}

/* Modulo (A % B) */
FSEphemerisPeriod USpiceTypes::Modulus_SEphemerisPeriodDouble(const FSEphemerisPeriod& A, double B)
{
    return A % B;
}

double USpiceTypes::Ratio_SEphemerisPeriod(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return A / B;
}


/* Ratio (A / B) */
double USpiceTypes::Ratio_SDistance(const FSDistance& A, const FSDistance& B)
{
    return A / B;
}

FSDistance USpiceTypes::Divide_SDistanceDouble(const FSDistance& A, double B)
{
    return A / B;
}

/* Subtraction (A - B) */
FSDistance USpiceTypes::Subtract_SDistanceSDistance(const FSDistance& A, const FSDistance& B)
{
    return A - B;
}

FSDistance USpiceTypes::Add_SDistanceSDistance(const FSDistance& A, const FSDistance& B)
{
    return A + B;
}

bool USpiceTypes::Less_SDistanceSDistance(const FSDistance& A, const FSDistance& B)
{
    return A < B;
}

bool USpiceTypes::Greater_SDistanceSDistance(const FSDistance& A, const FSDistance& B)
{
    return A > B;
}

/* Multiplication (A * B) */
FSDistance USpiceTypes::Multiply_SDistanceDouble(const FSDistance& A, double B)
{
    return A * B;
}


/* Multiplication (A * B) */
FSDistanceVector USpiceTypes::Multiply_SDistanceVectorDouble(const FSDistanceVector& A, double B)
{
    return A * B;
}

/* Subtraction (A - B) */
FSDistanceVector USpiceTypes::Subtract_SDistanceVectorSDistanceVector(const FSDistanceVector& A, const FSDistanceVector& B)
{
    return A - B;
}

/* Addition (A + B) */
FSDistanceVector USpiceTypes::Add_SDistanceVectorSDistanceVector(const FSDistanceVector& A, const FSDistanceVector& B)
{
    return A + B;
}


FSDimensionlessVector USpiceTypes::Ratio_SDistanceVector(const FSDistanceVector& A, const FSDistanceVector& B)
{
    return A / B;
}

FSDistanceVector USpiceTypes::Divide_SDistanceVectorSDimensionlessVector(const FSDistanceVector& A, const FSDimensionlessVector& B)
{
    return A / B;
}

FSDistanceVector USpiceTypes::Divide_SDistanceVectorDouble(const FSDistanceVector& A, double B)
{
    return A / B;
}

bool USpiceTypes::Greater_SEphemerisTimeSEphemerisTime(const FSEphemerisTime& A, const FSEphemerisTime& B)
{
    return A.seconds > B.seconds;
}

bool USpiceTypes::Less_SEphemerisTimeSEphemerisTime(const FSEphemerisTime& A, const FSEphemerisTime& B)
{
    return A.seconds < B.seconds;
}


bool USpiceTypes::Greater_SEphemerisPeriodSEphemerisPeriod(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return A > B;
}

bool USpiceTypes::Less_SEphemerisPeriodSEphemerisPeriod(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return A < B;
}

FSSpeed USpiceTypes::Multiply_SSpeedDouble(const FSSpeed& A, double B)
{
    return A * B;
}

FSSpeed USpiceTypes::Divide_SSpeedDouble(FSSpeed A, double B)
{
    return A * B;
}

double USpiceTypes::Ratio_SSpeed(const FSSpeed& A, const FSSpeed& B)
{
    return A / B;
}

FSSpeed USpiceTypes::Subtract_SSpeedSSpeed(const FSSpeed& A, const FSSpeed& B)
{
    return A - B;
}

FSSpeed USpiceTypes::Add_SSpeedSSpeed(const FSSpeed& A, const FSSpeed& B)
{
    return A + B;
}

bool USpiceTypes::Less_SSpeedSSpeed(const FSSpeed& A, const FSSpeed& B)
{
    return A < B;
}

FSVelocityVector USpiceTypes::Multiply_SVelocityVectorDouble(const FSVelocityVector& A, double B)
{
    return A * B;
}

FSVelocityVector USpiceTypes::Divide_SVelocityVectorDouble(const FSVelocityVector& A, double B)
{
    return A / B;
}

FSDimensionlessVector USpiceTypes::Ratio_SVelocityVector(const FSVelocityVector& A, const FSVelocityVector& B)
{
    return A / B;
}


FSVelocityVector USpiceTypes::Subtract_SVelocityVectorSVelocityVector(const FSVelocityVector& A, const FSVelocityVector& B)
{
    return A - B;
}

FSVelocityVector USpiceTypes::Add_SVelocityVectorSVelocityVector(const FSVelocityVector& A, const FSVelocityVector& B)
{
    return A + B;
}

FSVelocityVector USpiceTypes::Multiply_SSpeedSDimensionlessVector(const FSSpeed& A, const FSDimensionlessVector& B)
{
    return A * B;
}

FSDistanceVector USpiceTypes::Multiply_SDistanceSDimensionlessVector(const FSDistance& A, const FSDimensionlessVector& B)
{
    return A * B;
}

FSDimensionlessVector USpiceTypes::Multiply_SDimensionlessVectorDouble(const FSDimensionlessVector& A, double B)
{
    return A * B;
}

FSDimensionlessVector USpiceTypes::Divide_SDimensionlessVectorDouble(const FSDimensionlessVector& A, double B)
{
    return A / B;
}

FSDimensionlessVector USpiceTypes::Subtract_SDimensionlessVectorSDimensionlessVector(const FSDimensionlessVector& A, const FSDimensionlessVector& B)
{
    return A - B;
}

FSDimensionlessVector USpiceTypes::Add_SDimensionlessVectorSDimensionlessVector(const FSDimensionlessVector& A, const FSDimensionlessVector& B)
{
    return A + B;
}

FSVelocityVector USpiceTypes::SpeedToVelocity(const FSSpeed& A, const FSDimensionlessVector& B)
{
    return A * B;
}

FSDistanceVector USpiceTypes::DistanceToVector(const FSDistance& A, const FSDimensionlessVector& B)
{
    return A * B;
}

FSDimensionlessVector USpiceTypes::ScaleDimensionlessVector(double A, const FSDimensionlessVector& B)
{
    return A * B;
}

bool USpiceTypes::Greater_SSpeedSSpeed(const FSSpeed& A, const FSSpeed& B)
{
    return A > B;
}

FSAngle USpiceTypes::Multiply_SAngleDouble(const FSAngle& A, double B)
{
    return A * B;
}

FSAngle USpiceTypes::Divide_SAngleDouble(const FSAngle A, double B)
{
    return A / B;
}

double USpiceTypes::Ratio_SAngle(const FSAngle& A, const FSAngle& B)
{
    return A / B;
}


FSAngle USpiceTypes::Subtract_SAngleSAngle(const FSAngle& A, const FSAngle& B)
{
    return A - B;
}


FSAngle USpiceTypes::Add_SAngleSAngle(const FSAngle& A, const FSAngle& B)
{
    return A + B;
}



/* -----------------------------------------------------------------------------------------
 * 
 * UE / SPICE Spatial Data transforms..
 * 
 * Any time we pass coordinate system data across the SPICE/UE boundary we have to
 * convert between the two coordinate systems... That's what Swizzle/Swazzle does.
 * 
 */

FVector USpiceTypes::Conv_SDimensionlessToVector(
    FSDimensionlessVector value
)
{
    return Swizzle(value);
}

FVector USpiceTypes::Conv_SDistanceVectorToVector(
    const FSDistanceVector& value
)
{
    return Swizzle(value);
}

FVector USpiceTypes::Conv_SVelocityVectorToVector(
    const FSVelocityVector& value
)
{
    return Swizzle(value);
}

FSDimensionlessVector USpiceTypes::Conv_VectorToSDimensionless(
    const FVector& value
)
{
    FSDimensionlessVector converted_value;
    Swizzle(value, converted_value);
    return converted_value;
}


FSAngularVelocity USpiceTypes::Conv_VectorToSAngularVelocity(
    const FVector& value
)
{
    FSAngularVelocity converted_value;
    Swizzle(value, converted_value);
    return converted_value;
}

FVector USpiceTypes::Conv_SAngularVelocityToVector(
    const FSAngularVelocity& value
)
{
    return Swizzle(value);
}


FString USpiceTypes::Conv_SAngularVelocityToString(const FSAngularVelocity& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SQuaternionToString(const FSQuaternion& value)
{
    return value.ToString();
}

FSDistanceVector USpiceTypes::Conv_VectorToSDistanceVector(
    const FVector& value
)
{
    FSDistanceVector converted_value;
    Swizzle(value, converted_value);
    return converted_value;
}


FSVelocityVector USpiceTypes::Conv_VectorToSVelocityVector(
    const FVector& value
)
{
    FSVelocityVector converted_value;
    Swizzle(value, converted_value);
    return converted_value;
}


FQuat USpiceTypes::Conv_SQuaternionToQuat(
    const FSQuaternion& value
)
{
    return Swazzle(value);
}


FSQuaternion USpiceTypes::Conv_QuatToSQuaternion(
    const FQuat& value
)
{
    return Swazzle(value);
}

/* 
 * -----------------------------------------------------------------------------------------
 */

void USpiceTypes::NormalizeAngle0To360(
    const FSAngle& Angle,
    FSAngle& AngleNormalized
)
{
    AngleNormalized = FSAngle(normalizeZeroToTwoPi(Angle.AsRadians()));
}


void USpiceTypes::NormalizeAngle180To180(
    const FSAngle& Angle,
    FSAngle& AngleNormalized
)
{
    AngleNormalized = FSAngle(normalizePiToPi(Angle.AsRadians()));
}

void USpiceTypes::NormalizeAngleMinus180To180(
    const FSAngle& Angle,
    FSAngle& AngleNormalized
)
{
    AngleNormalized = FSAngle(normalizePiToPi(Angle.AsRadians()));
}

void USpiceTypes::NormalizeDegrees0To360(double Degrees, double& NormalizedDegrees)
{
    NormalizedDegrees = normalize0to360(Degrees);
}

void USpiceTypes::NormalizeDegreesMinus180To180(double Degrees, double& NormalizedDegrees)
{
    NormalizedDegrees = normalize180to180(Degrees);
}

void USpiceTypes::NormalizeRadiansZeroToTwoPi(double Radians, double& NormalizedRadians)
{
    NormalizedRadians = normalizeZeroToTwoPi(Radians);
}


void USpiceTypes::NormalizeRadiansMinusPiToPi(double Radians, double& NormalizedRadians)
{
    NormalizedRadians = normalizePiToPi(Radians);
}


FString USpiceTypes::Conv_S_UnitsToString(ES_Units units)
{
    return FString(toString(units));
}

FString USpiceTypes::Conv_SAngleToString(const FSAngle& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SDistanceToString(const FSDistance& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SDistanceVectorToString(const FSDistanceVector& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SVelocityVectorToString(const FSVelocityVector& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SStateVectorToString(const FSStateVector& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SLonLatToString(const FSLonLat& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SSpeedToString(const FSSpeed& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SAngularRateToString(const FSAngularRate& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SDimensionlessVectorToString(const FSDimensionlessVector& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SDimensionlessStateVectorToString(const FSDimensionlessStateVector& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SPlanetographicStateVectorToString(const FSPlanetographicStateVector& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SGeodeticStateVectorToString(const FSGeodeticStateVector& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SSphericalStateVectorToString(const FSSphericalStateVector& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SLatitudinalStateVectorToString(const FSLatitudinalStateVector& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SCylindricalStateVectorToString(const FSCylindricalStateVector& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SPlanetographicVectorToString(const FSPlanetographicVector& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SGeodeticVectorToString(const FSGeodeticVector& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SSphericalVectorToString(const FSSphericalVector& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SLatitudinalVectorToString(const FSLatitudinalVector& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SCylindricalVectorToString(const FSCylindricalVector& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SPlanetographicVectorRatesToString(const FSPlanetographicVectorRates& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SGeodeticVectorRatesToString(const FSGeodeticVectorRates& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SSphericalVectorRatesToString(const FSSphericalVectorRates& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SLatitudinaVectorRatesToString(const FSLatitudinalVectorRates& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SCylindricalVectorRatesToString(const FSCylindricalVectorRates& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SConicElementsToString(const FSConicElements& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SComplexScalarToString(const FSComplexScalar& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SEulerAnglesToString(const FSEulerAngles& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SEulerAngularStateToString(const FSEulerAngularState& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SStateTransformToString(const FSStateTransform& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SRotationMatrixToString(const FSRotationMatrix& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SEllipseToString(const FSEllipse& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SPlaneToString(const FSPlane& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SEulerAngularTransformToString(const FSEulerAngularTransform& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SWindowSegmentToString(const FSEquinoctialElements& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SWindowSegmentToString(const FSWindowSegment& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SPointingType2ObservationToString(const FSPointingType2Observation& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SPointingType1ObservationToString(const FSPointingType1Observation& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SPointingType5ObservationToString(const FSPointingType5Observation& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SPKType5ObservationToString(const FSPKType5Observation& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_STermptPointToString(const FSTermptPoint& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_STermptCutToString(const FSTermptCut& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_STLEGeophysicalConstantsToString(const FSTLEGeophysicalConstants& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SLimptPointToString(const FSLimptPoint& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SLimptCutToString(const FSLimptCut& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SPKType15ObservationToString(const FSPKType15Observation& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_STwoLineElementsToString(const FSTwoLineElements& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SRayToString(const FSRay& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SDLADescrToString(const FSDLADescr& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SDSKDescrToString(const FSDSKDescr& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SPlateIndicesToString(const FSPlateIndices& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SMassConstantToString(const FSMassConstant& value)
{
    return value.ToString();
}


void USpiceTypes::SetFloatToStringPrecision(int _floatPrintPrecision)
{
    FloatFormatPrecision = _floatPrintPrecision;
}


FString USpiceTypes::FormatDouble(double value)
{
    return FormatDoublePrecisely(value, FloatFormatPrecision);
}

FString USpiceTypes::FormatDoublePrecisely(double value, int precision)
{
    // Create an output string stream
    std::ostringstream streamObj;

    // Set precision
    streamObj << std::setprecision(FloatFormatPrecision);
    
    // Add double to stream
    streamObj << value;

    // And finally, as an Unreal-Engine FString
    return FString(streamObj.str().c_str());
}


FString USpiceTypes::formatAngle(double degrees, ES_AngleFormat format)
{
    // UE displays degrees incorrectly
    bool useDegreeSymbol = false;

    std::basic_ostringstream<EXTENDED_CHAR_TYPE> streamObj;
    int floatFormatPrecision = USpiceTypes::FloatFormatPrecision;
    streamObj << std::setprecision(USpiceTypes::FloatFormatPrecision);

    if (format == ES_AngleFormat::DD)
    {
        // note there's no ANSICHAR implementation for wostringstream::setfill...
        streamObj << std::setfill(EXTENDED_CHAR_TYPE('0')) << std::setw(floatFormatPrecision + 2) << std::fixed << std::setprecision(floatFormatPrecision);
        streamObj << degrees;
#if !PLATFORM_WIDECHAR_IS_CHAR16
        if(useDegreeSymbol) streamObj << EXTENDED_CHAR('\370');
#endif
    }
    else if (format == ES_AngleFormat::DD_180)
    {
        streamObj << std::setfill(EXTENDED_CHAR_TYPE('0')) << std::setw(floatFormatPrecision + 2) << std::fixed << std::setprecision(floatFormatPrecision);
        streamObj << normalize180to180(degrees);
#if !PLATFORM_WIDECHAR_IS_CHAR16
        if (useDegreeSymbol) streamObj << EXTENDED_CHAR('\370');
#endif
    }
    else if (format == ES_AngleFormat::DD_360)
    {
        streamObj << std::setfill(EXTENDED_CHAR_TYPE('0')) << std::setw(floatFormatPrecision + 2) << std::fixed << std::setprecision(floatFormatPrecision);
        streamObj << normalize0to360(degrees);
#if !PLATFORM_WIDECHAR_IS_CHAR16
        if (useDegreeSymbol) streamObj << EXTENDED_CHAR('\370');
#endif
    }
    else if (format == ES_AngleFormat::DMS)
    {
        int frac_precision = floatFormatPrecision - 7;
        double frac = abs(degrees);
        
        long deg = floorl(frac);

        frac -= (double)deg;
        if (degrees < 0.) deg *= -1;
        streamObj << deg;
#if !PLATFORM_WIDECHAR_IS_CHAR16
        if (useDegreeSymbol) streamObj << EXTENDED_CHAR('\370');
#endif
        streamObj << ' ';

        frac *= 60.;
        long amin = floorl(frac);
        frac -= (double)amin;
        streamObj << std::setw(2) << std::setfill(EXTENDED_CHAR_TYPE('0')) << amin << '\'';

        frac *= 60;

        if (frac_precision <= 0)
        {
            long asec = lround(frac);
            streamObj << std::setw(2) << std::setfill(EXTENDED_CHAR_TYPE('0')) << asec << '"';
        }
        else
        {
            double asec = frac;
            streamObj << std::fixed << std::setprecision(frac_precision+2) << asec << '"';
        }
    }
    else if (format == ES_AngleFormat::HMS)
    {
        int frac_precision = floatFormatPrecision - 7;
        double frac = abs(degrees / 360. * 24);

        long hour = floorl(frac);
        frac -= (double)hour;

        if (degrees < 0.) hour *= -1;
        streamObj << hour << "h ";

        frac *= 60.;
        long min = floorl(frac);
        frac -= (double)min;
        streamObj << std::setw(2) << std::setfill(EXTENDED_CHAR('0')) << min << "m ";

        frac *= 60;

        if (frac_precision <= 0)
        {
            long sec = lround(frac);
            streamObj << std::setw(2) << std::setfill(EXTENDED_CHAR('0')) << sec << "s ";
        }
        else
        {
            double sec = frac;
            streamObj << std::fixed << std::setprecision(frac_precision + 2) << sec << "s";
        }
    }
    else if (format == ES_AngleFormat::DR_PI)
    {
        streamObj << std::setfill(EXTENDED_CHAR('0')) << std::setfill(EXTENDED_CHAR('0')) << std::setw(floatFormatPrecision+2) << std::fixed << std::setprecision(floatFormatPrecision);
        streamObj << normalizePiToPi(degrees / 360. * twopi_c());
    }
    else if (format == ES_AngleFormat::DR_2PI)
    {
        streamObj << std::setw(floatFormatPrecision + 2) << std::fixed << std::setprecision(floatFormatPrecision);
        streamObj << normalizeZeroToTwoPi(degrees / 360. * twopi_c());
    }
    else
    {
        streamObj << std::setfill(EXTENDED_CHAR('0')) << std::setw(floatFormatPrecision + 2) << std::fixed << std::setprecision(floatFormatPrecision);
        streamObj << (degrees / 360. * twopi_c());
    }
    
    // Collapsing this into `FString(streamObj.str().c_str())` causes the str() to go out of scope,
    // which would free the string buffer.  Bad.
    // A const ref 'pins' the string returned by str() while it stays in scope.
    const std::basic_string<EXTENDED_CHAR_TYPE>& ecstr = streamObj.str();
    return FString(ecstr.c_str());
}


double USpiceTypes::normalize0to360(double degrees)
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

double USpiceTypes::normalize180to180(double degrees)
{
    // First normalize 0 - 360
    degrees = normalize0to360(degrees);
    
    // Wrap around if need be.
    if (degrees > 180.) degrees -= 360.;
    
    return degrees;
}


double USpiceTypes::normalizeZeroToTwoPi(double radians)
{
    // First, normalize 0-360
    radians = std::fmod(radians, FSAngle::twopi);

    // Pull up negative values
    if (radians < 0.)
    {
        radians += FSAngle::twopi;
    }

    return radians;
}

double USpiceTypes::normalizePiToPi(double radians)
{
    // First normalize 0 - 360
    radians = normalizeZeroToTwoPi(radians);

    // Wrap around if need be.
    if (radians > FSAngle::pi) radians -= FSAngle::twopi;

    return radians;
}


FString USpiceTypes::FormatAngle(const FSAngle& value, ES_AngleFormat format)
{
    return formatAngle(value.degrees, format);
}

FString USpiceTypes::FormatLonLat(const FSLonLat& value, const FString& separator, ES_AngleFormat format)
{
    double longitude = value.longitude.degrees;

    // First, normalize the latitude
    double latitude = normalize180to180(value.latitude.degrees);
    
    // Deal with latitudes that wrap past the poles...
    if (latitude > 90.)
    {
        // Spin longitude to the other side
        longitude += 180.;
        // Wrap around the pole
        latitude = 180. - latitude;
    }
    else if (latitude < -90.)
    {
        // As above
        longitude -= 180.;
        latitude = -180. + latitude;
    }

    // NOW, we can normalize the longitude
    longitude = normalize180to180(longitude);

    return formatAngle(abs(longitude), format) + (longitude < 0 ? "W" : "E") + separator + formatAngle(abs(latitude), format) + (latitude < 0 ? "S" : "N");
}

FString USpiceTypes::FormatRADec(const FSAngle& rightAscension, const FSAngle& declination, const FString& separator)
{
    double ra = rightAscension.degrees;

    // First, normalize the declination
    double dec = normalize180to180(declination.degrees);

    // Deal with dec's that wrap past the poles...
    if (dec > 90.)
    {
        // Spin ra to the other side
        ra += 180.;
        // Wrap around the pole
        dec = 180 - dec;
    }
    else if (dec < -90.)
    {
        // As above
        ra -= 180.;
        dec = -180 + dec;
    }

    // NOW, we can normalize the ra
    ra = normalize0to360(ra);

    return formatAngle(ra, ES_AngleFormat::HMS) + separator + formatAngle(dec, ES_AngleFormat::DMS);
}

FString USpiceTypes::FormatDistance(const FSDistance& distance, ES_Units Units /*= ES_Units::KILOMETERS*/, int precision)
{
    double value = distance.AsKilometers();

    if(Units != ES_Units::KILOMETERS)
    {
        convrt_c(value, toString(ES_Units::KILOMETERS), toString(Units), &value);
        UnexpectedErrorCheck(false);
    }

    return FormatDoublePrecisely(value, precision);
}

FString USpiceTypes::FormatPeriod(const FSEphemerisPeriod& period, ES_Units Units /*= ES_Units::SECONDS*/, int precision)
{
    double value = period.AsSeconds();

    if(Units != ES_Units::SECONDS)
    {
        convrt_c(value, toString(ES_Units::SECONDS), toString(Units), &value);

        UnexpectedErrorCheck(false);
    }

    return FormatDoublePrecisely(value, precision);
}

FString USpiceTypes::FormatSpeed(const FSSpeed& speed, ES_Units NumeratorUnits /*= ES_Units::KILOMETERS*/, ES_Units DenominatorUnits /*= ES_Units::SECONDS*/, int precision)
{
    double value = speed.AsKilometersPerSecond();

    if(NumeratorUnits != ES_Units::KILOMETERS)
    {
        convrt_c(value, toString(ES_Units::KILOMETERS), toString(NumeratorUnits), &value);
        UnexpectedErrorCheck(false);
    }

    if(DenominatorUnits != ES_Units::SECONDS)
    {
        double denominator = 1.;
        convrt_c(denominator, toString(ES_Units::SECONDS), toString(DenominatorUnits), &denominator);
        value *= denominator;
    }

    return FormatDoublePrecisely(value, precision);
}

FString USpiceTypes::FormatUtcTime(const FSEphemerisTime& time, ES_UTCTimeFormat TimeFormat, int precision)
{
    FString Result = TEXT("Time Format Error");
    ES_ResultCode ResultCode;
    FString ErrorMessage;
    USpice::et2utc(ResultCode, ErrorMessage, time, TimeFormat, Result, precision);
    return Result;
}


FSDistance USpiceTypes::SDistance_Zero()
{
    return FSDistance::Zero;
}

FSDistance USpiceTypes::SDistance_OneKilometer()
{
    return FSDistance::OneKilometer;
}

FSDistance USpiceTypes::SDistance_OneMeter()
{
    return FSDistance::OneMeter;
}

FSDistance USpiceTypes::SDistance_OneFoot()
{
    return FSDistance::OneFoot;
}

FSDistance USpiceTypes::SDistance_OneStatuteMile()
{
    return FSDistance::OneStatuteMile;
}

FSDistance USpiceTypes::SDistance_OneNauticalMile()
{
    return FSDistance::OneNauticalMile;
}

FSDistance USpiceTypes::SDistance_OneAstronomicalUnit()
{
    return FSDistance::OneAstronomicalUnit;
}

FSDistance USpiceTypes::SDistance_OneLightYear()
{
    return FSDistance::OneLightYear;
}

FSSpeed USpiceTypes::SSpeed_Zero()
{
    return FSSpeed::Zero;
}

FSSpeed USpiceTypes::SSpeed_OneKilomenterPerSecond()
{
    return FSSpeed::OneKmps;
}

FSDistanceVector USpiceTypes::SDistanceVector_Zero()
{
    return FSDistanceVector::Zero;
}

FSVelocityVector USpiceTypes::SVelocityVector_Zero()
{
    return FSVelocityVector::Zero;
}

FSStateTransform USpiceTypes::SStateTransform_Identity()
{
    return FSStateTransform::Identity;
}

double USpiceTypes::SAngle_pi()
{
    return FSAngle::pi;
}

double USpiceTypes::SAngle_halfpi()
{
    return FSAngle::halfpi;
}

double USpiceTypes::SAngle_twopi()
{
    return FSAngle::twopi;
}

double USpiceTypes::SAngle_dpr()
{
    return FSAngle::dpr;
}

FSAngle USpiceTypes::SAngle__0()
{
    return FSAngle::_0;
}

FSAngle USpiceTypes::SAngle__360()
{
    return FSAngle::_360;
}

FSEulerAngles USpiceTypes::SEulerAngles_Zero()
{
    return FSEulerAngles::Zero;
}

FSQuaternion USpiceTypes::SQuaternion_Identity()
{
    return FSQuaternion::Identity;
}

FSAngularRate USpiceTypes::SAngularRate_Zero()
{
    return FSAngularRate::Zero;
}

FSAngularVelocity USpiceTypes::SAngularVelocity_Zero()
{
    return FSAngularVelocity::Zero;
}

FSEulerAngularState USpiceTypes::SEulerAngularState_Zero()
{
    return FSEulerAngularState::Zero;
}

FSEulerAngularTransform USpiceTypes::SEulerAngularTransform_Identity()
{
    return FSEulerAngularTransform::Identity;
}

FSComplexScalar USpiceTypes::SComplexScalar_Zero()
{
    return FSComplexScalar::Zero;
}

FSEphemerisTime USpiceTypes::SEphemerisTime_J2000()
{
    return FSEphemerisTime::J2000;
}

FSEphemerisPeriod USpiceTypes::SEphemerisPeriod_Zero()
{
    return FSEphemerisPeriod::Zero;
}

FSEphemerisPeriod USpiceTypes::SEphemerisPeriod_OneSecond()
{
    return FSEphemerisPeriod::OneSecond;
}

FSEphemerisPeriod USpiceTypes::SEphemerisPeriod_OneMinute()
{
    return FSEphemerisPeriod::OneMinute;
}

FSEphemerisPeriod USpiceTypes::SEphemerisPeriod_OneHour()
{
    return FSEphemerisPeriod::OneHour;
}

FSEphemerisPeriod USpiceTypes::SEphemerisPeriod_OneDay()
{
    return FSEphemerisPeriod::OneDay;
}

FSEphemerisPeriod USpiceTypes::SEphemerisPeriod_OneJulianYear()
{
    return FSEphemerisPeriod::OneJulianYear;
}

FSEphemerisPeriod USpiceTypes::SEphemerisPeriod_OneTropicalYear()
{
    return FSEphemerisPeriod::OneTropicalYear;
}

FSRotationMatrix USpiceTypes::SRotationMatrix_Identity()
{
    return FSRotationMatrix::Identity;
}

FSDimensionlessVector USpiceTypes::SDimensionlessVector_Zero()
{
    return FSDimensionlessVector::Zero;
}

FSDimensionlessVector USpiceTypes::SDimensionlessVector_X_Axis()
{
    return FSDimensionlessVector::X_Axis;
}

FSDimensionlessVector USpiceTypes::SDimensionlessVector_Y_Axis()
{
    return FSDimensionlessVector::Y_Axis;
}

FSDimensionlessVector USpiceTypes::SDimensionlessVector_Z_Axis()
{
    return FSDimensionlessVector::Z_Axis;
}

FSMassConstant USpiceTypes::SMassConstant_Zero()
{
    return FSMassConstant::Zero;
}


FSAngularVelocity USpiceTypes::NegateSAngularVelocity(const FSAngularVelocity& A)
{
    return FSAngularVelocity(-A.x, -A.y, -A.z);
}

FSAngularRate USpiceTypes::NegateSAngularRate(const FSAngularRate& A)
{
    return FSAngularRate::FromRadiansPerSecond(-A.AsRadiansPerSecond());
}

FSVelocityVector USpiceTypes::NegateSVelocityVector(const FSVelocityVector& A)
{
    return FSVelocityVector(-A.dx, -A.dy, -A.dz);
}

FSDistanceVector USpiceTypes::NegateSDistanceVector(const FSDistanceVector& A)
{
    return FSDistanceVector(-A.x, -A.y, -A.z);
}

FSDimensionlessVector USpiceTypes::NegateSDimensionlessVector(const FSDimensionlessVector& A)
{
    return FSDimensionlessVector(-A.x, -A.y, -A.z);
}

FSEphemerisPeriod USpiceTypes::NegateSEphemerisPeriod(const FSEphemerisPeriod& A)
{
    return FSEphemerisPeriod::FromSeconds(-A.AsSeconds());
}

FSAngle USpiceTypes::NegateSAngle(const FSAngle& A)
{
    return FSAngle::FromRadians(-A.AsRadians());
}

FSSpeed USpiceTypes::NegateSSpeed(const FSSpeed& A)
{
    return FSSpeed::FromKilometersPerSecond(-A.AsKilometersPerSecond());
}

FSDistance USpiceTypes::NegateSDistance(const FSDistance& A)
{
    return FSDistance::FromKilometers(-A.AsKilometers());
}

#pragma region NaifNames

using namespace MaxQ;

FString USpiceTypes::Const_J2000() { return Constants::J2000; }
FString USpiceTypes::Const_ECLIPJ2000() { return Constants::ECLIPJ2000; }
FString USpiceTypes::Const_MARSIAU() { return Constants::MARSIAU; }
FString USpiceTypes::Const_GALACTIC() { return Constants::GALACTIC; }
FString USpiceTypes::Const_IAU_EARTH() { return Constants::IAU_EARTH; }
FString USpiceTypes::Const_EARTH_FIXED() { return Constants::EARTH_FIXED; }
FString USpiceTypes::Const_ITRF93() { return Constants::ITRF93; }
FString USpiceTypes::Const_IAU_MOON() { return Constants::IAU_MOON; }
FString USpiceTypes::Const_IAU_SUN() { return Constants::IAU_SUN; }
FString USpiceTypes::Const_IAU_MERCURY() { return Constants::IAU_MERCURY; }
FString USpiceTypes::Const_IAU_VENUS() { return Constants::IAU_VENUS; }
FString USpiceTypes::Const_IAU_MARS() { return Constants::IAU_MARS; }
FString USpiceTypes::Const_IAU_DEIMOS() { return Constants::IAU_DEIMOS; }
FString USpiceTypes::Const_IAU_PHOBOS() { return Constants::IAU_PHOBOS; }
FString USpiceTypes::Const_IAU_JUPITER() { return Constants::IAU_JUPITER; }
FString USpiceTypes::Const_IAU_SATURN() { return Constants::IAU_SATURN; }
FString USpiceTypes::Const_IAU_NEPTUNE() { return Constants::IAU_NEPTUNE; }
FString USpiceTypes::Const_IAU_URANUS() { return Constants::IAU_URANUS; }
FString USpiceTypes::Const_IAU_PLUTO() { return Constants::IAU_PLUTO; }
FString USpiceTypes::Const_IAU_CERES() { return Constants::IAU_CERES; }
FString USpiceTypes::Const_EARTH() { return Constants::EARTH; }
FString USpiceTypes::Const_MOON() { return Constants::MOON; }
FString USpiceTypes::Const_EMB() { return Constants::EMB; }
FString USpiceTypes::Const_EARTH_BARYCENTER() { return Constants::EARTH_BARYCENTER; }
FString USpiceTypes::Const_SUN() { return Constants::SUN; }
FString USpiceTypes::Const_SSB() { return Constants::SSB; }
FString USpiceTypes::Const_SOLAR_SYSTEM_BARYCENTER() { return Constants::SOLAR_SYSTEM_BARYCENTER; }
FString USpiceTypes::Const_MERCURY() { return Constants::MERCURY; }
FString USpiceTypes::Const_VENUS() { return Constants::VENUS; }
FString USpiceTypes::Const_MARS() { return Constants::MARS; }
FString USpiceTypes::Const_PHOBOS() { return Constants::PHOBOS; }
FString USpiceTypes::Const_DEIMOS() { return Constants::DEIMOS; }
FString USpiceTypes::Const_MARS_BARYCENTER() { return Constants::MARS_BARYCENTER; }
FString USpiceTypes::Const_JUPITER() { return Constants::JUPITER; }
FString USpiceTypes::Const_JUPITER_BARYCENTER() { return Constants::JUPITER_BARYCENTER; }
FString USpiceTypes::Const_SATURN() { return Constants::SATURN; }
FString USpiceTypes::Const_SATURN_BARYCENTER() { return Constants::SATURN_BARYCENTER; }
FString USpiceTypes::Const_URANUS() { return Constants::URANUS; }
FString USpiceTypes::Const_URANUS_BARYCENTER() { return Constants::URANUS_BARYCENTER; }
FString USpiceTypes::Const_NEPTUNE() { return Constants::NEPTUNE; }
FString USpiceTypes::Const_NEPTUNE_BARYCENTER() { return Constants::NEPTUNE_BARYCENTER; }
FString USpiceTypes::Const_PLUTO() { return Constants::PLUTO; }
FString USpiceTypes::Const_PLUTO_BARYCENTER() { return Constants::PLUTO_BARYCENTER; }
FString USpiceTypes::Const_CERES() { return Constants::CERES; }
FString USpiceTypes::Const_PIONEER_6() { return Constants::PIONEER_6; }
FString USpiceTypes::Const_PIONEER_7() { return Constants::PIONEER_7; }
FString USpiceTypes::Const_VIKING_1_ORBITER() { return Constants::VIKING_1_ORBITER; }
FString USpiceTypes::Const_VIKING_2_ORBITER() { return Constants::VIKING_2_ORBITER; }
FString USpiceTypes::Const_VOYAGER_1() { return Constants::VOYAGER_1; }
FString USpiceTypes::Const_VOYAGER_2() { return Constants::VOYAGER_2; }
FString USpiceTypes::Const_HST() { return Constants::HST; }
FString USpiceTypes::Const_HUBBLE_SPACE_TELESCOPE() { return Constants::HUBBLE_SPACE_TELESCOPE; }
FString USpiceTypes::Const_MARS_PATHFINDER() { return Constants::MARS_PATHFINDER; }
FString USpiceTypes::Const_PARKER_SOLAR_PROBE() { return Constants::PARKER_SOLAR_PROBE; }
FString USpiceTypes::Const_JWST() { return Constants::JWST; }
FString USpiceTypes::Const_JAMES_WEBB_SPACE_TELESCOPE() { return Constants::JAMES_WEBB_SPACE_TELESCOPE; }
FString USpiceTypes::Const_INSIGHT() { return Constants::INSIGHT; }
FString USpiceTypes::Const_OPPORTUNITY() { return Constants::OPPORTUNITY; }
FString USpiceTypes::Const_SPIRIT() { return Constants::SPIRIT; }
FString USpiceTypes::Const_NOTO() { return Constants::NOTO; }
FString USpiceTypes::Const_NEW_NORCIA() { return Constants::NEW_NORCIA; }
FString USpiceTypes::Const_GOLDSTONE() { return Constants::GOLDSTONE; }
FString USpiceTypes::Const_CANBERRA() { return Constants::CANBERRA; }
FString USpiceTypes::Const_MADRID() { return Constants::MADRID; }
FString USpiceTypes::Const_USUDA() { return Constants::USUDA; }
FString USpiceTypes::Const_DSS_05() { return Constants::DSS_05; }
FString USpiceTypes::Const_PARKES() { return Constants::PARKES; }
FString USpiceTypes::Const_GM() { return Constants::GM; }
FString USpiceTypes::Const_RADII() { return Constants::RADII; }

namespace MaxQ::Constants
{
    const FString J2000(TEXT("J2000"));
    const FString ECLIPJ2000(TEXT("ECLIPJ2000"));
    const FString MARSIAU(TEXT("MARSIAU"));
    const FString GALACTIC(TEXT("GALACTIC"));
    const FString IAU_EARTH(TEXT("IAU_EARTH"));
    const FString EARTH_FIXED(TEXT("EARTH_FIXED"));
    const FString ITRF93(TEXT("ITRF93"));
    const FString IAU_MOON(TEXT("IAU_MOON"));
    const FString IAU_SUN(TEXT("IAU_SUN"));
    const FString IAU_MERCURY(TEXT("IAU_MERCURY"));
    const FString IAU_VENUS(TEXT("IAU_VENUS"));
    const FString IAU_MARS(TEXT("IAU_MARS"));
    const FString IAU_DEIMOS(TEXT("IAU_DEIMOS"));
    const FString IAU_PHOBOS(TEXT("IAU_PHOBOS"));
    const FString IAU_JUPITER(TEXT("IAU_JUPITER"));
    const FString IAU_SATURN(TEXT("IAU_SATURN"));
    const FString IAU_NEPTUNE(TEXT("IAU_NEPTUNE"));
    const FString IAU_URANUS(TEXT("IAU_URANUS"));
    const FString IAU_PLUTO(TEXT("IAU_PLUTO"));
    const FString IAU_CERES(TEXT("IAU_CERES"));
    const FString EARTH(TEXT("EARTH"));
    const FString MOON(TEXT("MOON"));
    const FString EMB(TEXT("EMB"));
    const FString EARTH_BARYCENTER(TEXT("EARTH_BARYCENTER"));
    const FString SUN(TEXT("SUN"));
    const FString SSB(TEXT("SSB"));
    const FString SOLAR_SYSTEM_BARYCENTER(TEXT("SOLAR_SYSTEM_BARYCENTER"));
    const FString MERCURY(TEXT("MERCURY"));
    const FString VENUS(TEXT("VENUS"));
    const FString MARS(TEXT("MARS"));
    const FString PHOBOS(TEXT("PHOBOS"));
    const FString DEIMOS(TEXT("DEIMOS"));
    const FString MARS_BARYCENTER(TEXT("MARS_BARYCENTER"));
    const FString JUPITER(TEXT("JUPITER"));
    const FString JUPITER_BARYCENTER(TEXT("JUPITER_BARYCENTER"));
    const FString SATURN(TEXT("SATURN"));
    const FString SATURN_BARYCENTER(TEXT("SATURN_BARYCENTER"));
    const FString URANUS(TEXT("URANUS"));
    const FString URANUS_BARYCENTER(TEXT("URANUS_BARYCENTER"));
    const FString NEPTUNE(TEXT("NEPTUNE"));
    const FString NEPTUNE_BARYCENTER(TEXT("NEPTUNE_BARYCENTER"));
    const FString PLUTO(TEXT("PLUTO"));
    const FString PLUTO_BARYCENTER(TEXT("PLUTO_BARYCENTER"));
    const FString CERES(TEXT("CERES"));
    const FString PIONEER_6(TEXT("PIONEER-6"));
    const FString PIONEER_7(TEXT("PIONEER-7"));
    const FString VIKING_1_ORBITER(TEXT("VIKING 1 ORBITER"));
    const FString VIKING_2_ORBITER(TEXT("VIKING 2 ORBITER"));
    const FString VOYAGER_1(TEXT("VOYAGER 1"));
    const FString VOYAGER_2(TEXT("VOYAGER 2"));
    const FString HST(TEXT("HST"));
    const FString HUBBLE_SPACE_TELESCOPE(TEXT("HUBBLE SPACE TELESCOPE"));
    const FString MARS_PATHFINDER(TEXT("MARS PATHFINDER"));
    const FString PARKER_SOLAR_PROBE(TEXT("PARKER SOLAR PROBE"));
    const FString JWST(TEXT("JWST"));
    const FString JAMES_WEBB_SPACE_TELESCOPE(TEXT("JAMES WEBB SPACE TELESCOPE"));
    const FString INSIGHT(TEXT("INSIGHT"));
    const FString OPPORTUNITY(TEXT("OPPORTUNITY"));
    const FString SPIRIT(TEXT("SPIRIT"));
    const FString NOTO(TEXT("NOTO"));
    const FString NEW_NORCIA(TEXT("NEW NORCIA"));
    const FString GOLDSTONE(TEXT("GOLDSTONE"));
    const FString CANBERRA(TEXT("CANBERRA"));
    const FString MADRID(TEXT("MADRID"));
    const FString USUDA(TEXT("USUDA"));
    const FString DSS_05(TEXT("DSS-05"));
    const FString PARKES(TEXT("PARKES"));
    const FString GM(TEXT("GM"));
    const FString RADII(TEXT("RADII"));

    const FName Name_J2000(J2000);
    const FName Name_ECLIPJ2000(ECLIPJ2000);
    const FName Name_MARSIAU(MARSIAU);
    const FName Name_GALACTIC(GALACTIC);
    const FName Name_IAU_EARTH(IAU_EARTH);
    const FName Name_EARTH_FIXED(EARTH_FIXED);
    const FName Name_ITRF93(ITRF93);
    const FName Name_IAU_MOON(IAU_MOON);
    const FName Name_IAU_SUN(IAU_SUN);
    const FName Name_IAU_MERCURY(IAU_MERCURY);
    const FName Name_IAU_VENUS(IAU_VENUS);
    const FName Name_IAU_MARS(IAU_MARS);
    const FName Name_IAU_DEIMOS(IAU_DEIMOS);
    const FName Name_IAU_PHOBOS(IAU_PHOBOS);
    const FName Name_IAU_JUPITER(IAU_JUPITER);
    const FName Name_IAU_SATURN(IAU_SATURN);
    const FName Name_IAU_NEPTUNE(IAU_NEPTUNE);
    const FName Name_IAU_URANUS(IAU_URANUS);
    const FName Name_IAU_PLUTO(IAU_PLUTO);
    const FName Name_IAU_CERES(IAU_CERES);
    const FName Name_EARTH(EARTH);
    const FName Name_MOON(MOON);
    const FName Name_EMB(EMB);
    const FName Name_EARTH_BARYCENTER(EARTH_BARYCENTER);
    const FName Name_SUN(SUN);
    const FName Name_SSB(SSB);
    const FName Name_SOLAR_SYSTEM_BARYCENTER(SOLAR_SYSTEM_BARYCENTER);
    const FName Name_MERCURY(MERCURY);
    const FName Name_VENUS(VENUS);
    const FName Name_MARS(MARS);
    const FName Name_PHOBOS(PHOBOS);
    const FName Name_DEIMOS(DEIMOS);
    const FName Name_MARS_BARYCENTER(MARS_BARYCENTER);
    const FName Name_JUPITER(JUPITER);
    const FName Name_JUPITER_BARYCENTER(JUPITER_BARYCENTER);
    const FName Name_SATURN(SATURN);
    const FName Name_SATURN_BARYCENTER(SATURN_BARYCENTER);
    const FName Name_URANUS(URANUS);
    const FName Name_URANUS_BARYCENTER(URANUS_BARYCENTER);
    const FName Name_NEPTUNE(NEPTUNE);
    const FName Name_NEPTUNE_BARYCENTER(NEPTUNE_BARYCENTER);
    const FName Name_PLUTO(PLUTO);
    const FName Name_PLUTO_BARYCENTER(PLUTO_BARYCENTER);
    const FName Name_CERES(CERES);
    const FName Name_PIONEER_6(PIONEER_6);
    const FName Name_PIONEER_7(PIONEER_7);
    const FName Name_VIKING_1_ORBITER(VIKING_1_ORBITER);
    const FName Name_VIKING_2_ORBITER(VIKING_2_ORBITER);
    const FName Name_VOYAGER_1(VOYAGER_1);
    const FName Name_VOYAGER_2(VOYAGER_2);
    const FName Name_HST(HST);
    const FName Name_HUBBLE_SPACE_TELESCOPE(HUBBLE_SPACE_TELESCOPE);
    const FName Name_MARS_PATHFINDER(MARS_PATHFINDER);
    const FName Name_PARKER_SOLAR_PROBE(PARKER_SOLAR_PROBE);
    const FName Name_JWST(JWST);
    const FName Name_JAMES_WEBB_SPACE_TELESCOPE(JAMES_WEBB_SPACE_TELESCOPE);
    const FName Name_INSIGHT(INSIGHT);
    const FName Name_OPPORTUNITY(OPPORTUNITY);
    const FName Name_SPIRIT(SPIRIT);
    const FName Name_NOTO(NOTO);
    const FName Name_NEW_NORCIA(NEW_NORCIA);
    const FName Name_GOLDSTONE(GOLDSTONE);
    const FName Name_CANBERRA(CANBERRA);
    const FName Name_MADRID(MADRID);
    const FName Name_USUDA(USUDA);
    const FName Name_DSS_05(DSS_05);
    const FName Name_PARKES(PARKES);
    const FName Name_GM(GM);
    const FName Name_RADII(RADII);
}

#pragma endregion NaifNames
