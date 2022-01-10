// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

#include "SpiceTypes.h"
#include "Spice.h"

#include <iomanip>
#include <sstream>
#include <string>


PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
extern "C"
{
#include "SpiceUsr.h"
}
PRAGMA_POP_PLATFORM_DEFAULT_PACKING


SPICE_API const FSDistance FSDistance::Zero = FSDistance();
SPICE_API const FSDistance FSDistance::OneKm = FSDistance(1.);
SPICE_API const FSSpeed FSSpeed::Zero = FSSpeed();
SPICE_API const FSDistanceVector FSDistanceVector::Zero = FSDistanceVector();
SPICE_API const FSVelocityVector FSVelocityVector::Zero = FSVelocityVector();
SPICE_API const FSStateTransform FSStateTransform::Identity = FSStateTransform();
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
SPICE_API const FSEphemerisPeriod FSEphemerisPeriod::Day = FSEphemerisPeriod((double) spd_c());
SPICE_API const FSRotationMatrix FSRotationMatrix::Identity = FSRotationMatrix();
SPICE_API const FSDimensionlessVector FSDimensionlessVector::Zero = FSDimensionlessVector();
SPICE_API int USpiceTypes::FloatFormatPrecision = 8;

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

double FSAngularRate::degreesPerSecond() const
{
    return radiansPerSecond * dpr_c();
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


void FSTwoLineElements::CopyTo(double(_elems)[10]) const
{
    if (elems.Num() == 10)
    {
        memcpy(_elems, elems.GetData(), 8 * sizeof(double));
    }
    else
    {
        setmsg_c("FSTwoLineElements uninitialized.  Array Length: #");
        errint_c("#", elems.Num());
        sigerr_c("SPICE(VALUEOUTOFRANGE)");
    }

    memcpy(_elems, elems.GetData(), 10 * sizeof(double));
}


void FSTLEGeophysicalConstants::CopyTo(double(_geophs)[8]) const
{
    if (geophs.Num() == 8)
    {
        memcpy(_geophs, geophs.GetData(), 8 * sizeof(double));
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
        vector.x = angle3.AsDouble();
        vector.y = angle2.AsDouble();
        vector.z = angle1.AsDouble();
    }
    else
    {
        // Convert the eulers into ZYX representation
        SpiceDouble _r[3][3];
        SpiceDouble _eulang3 = angle3.AsDouble();
        SpiceDouble _eulang2 = angle2.AsDouble();
        SpiceDouble _eulang1 = angle1.AsDouble();
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
    memcpy(corpar.GetData(), dsk->corpar, SPICE_DSK_NSYPAR * sizeof(SpiceDouble));
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
    memcpy(dsk->corpar, corpar.GetData(), SPICE_DSK_NSYPAR * sizeof(SpiceDouble));
    dsk->co1min = co1min;
    dsk->co1max = co1max;
    dsk->co2min = co2min;
    dsk->co2max = co2max;
    dsk->co3min = co3min;
    dsk->co3max = co3max;
    dsk->start = start;
    dsk->stop = stop;
}


double USpiceTypes::Conv_SDistanceToDouble(const FSDistance& value)
{
    return value.AsDouble();
}

FSDistance USpiceTypes::Conv_DoubleToSDistance(double value)
{
    return FSDistance(value);
}

double USpiceTypes::Conv_SSpeedToDouble(
    const FSSpeed& value
)
{
    return value.AsDouble();
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
    return value.AsDouble();
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
    return value.AsDouble();
}

FSAngularRate USpiceTypes::Conv_DoubleToSAngularRate(
    double value
)
{
    return FSAngularRate(value);
}

FSEphemerisTime USpiceTypes::Conv_StringToSEpheremisTime(const FString& time)
{
    double et = 0.;
    str2et_c(TCHAR_TO_ANSI(*time), &et);

    // Do not reset any error state, the downstream computation will detect the signal if the string failed to convert.
    USpice::UnexpectedErrorCheck(false);

    return FSEphemerisTime(et);
}


FString USpiceTypes::Conv_SEpheremisTimeToString(const FSEphemerisTime& et)
{
    SpiceChar sz[WINDOWS_MAX_PATH];
    memset(sz, 0, sizeof(sz));

    et2utc_c(et.AsDouble(), "C", 3, WINDOWS_MAX_PATH, sz);
    strcat_s(sz, " UTC");

    // Do not reset any error state, the downstream computation will detect the signal if the string failed to convert.
    USpice::UnexpectedErrorCheck(false);

    return FString(sz);
}

double USpiceTypes::Conv_SEphemerisTimeToDouble(
    const FSEphemerisTime& value
)
{
    return value.AsDouble();
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
    return value.AsDouble();
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
    return value.AsDouble();
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
    radians = angle.AsDouble();
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
FSEphemerisTime USpiceTypes::Add_SEphemerisPeriodSEphemerisTime(const FSEphemerisPeriod& A, const FSEphemerisTime& B)
{
    return A + B;
}


/* Addition (A + B) */
FSEphemerisPeriod USpiceTypes::Add_SEphemerisPeriodSEphemerisPeriod(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return A + B;
}

/* Subtraction (A - B) */
FSEphemerisPeriod USpiceTypes::Subtract_SEphemerisTimeSEphemerisTime(const FSEphemerisTime& A, const FSEphemerisTime& B)
{
    return A - B;
}

/* Multiplication (A * B) */
FSEphemerisPeriod USpiceTypes::Multiply_DoubleSEphemerisPeriod(double A, const FSEphemerisPeriod& B)
{
    return A * B;
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

/* Multiplication (A * B) */
FSDistance USpiceTypes::Multiply_DoubleSDistance(double A, const FSDistance& B)
{
    return A * B;
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

/* Multiplication (A * B) */
FSDistanceVector USpiceTypes::Multiply_DoubleSDistanceVector(double A, const FSDistanceVector& B)
{
    return A * B;
}

/* Subtraction (A - B) */
FSDistanceVector USpiceTypes::Subtract_DoubleSDistanceVector(const FSDistanceVector& A, const FSDistanceVector& B)
{
    return A - B;
}

/* Addition (A + B) */
FSDistanceVector USpiceTypes::Add_DoubleSDistanceVector(const FSDistanceVector& A, const FSDistanceVector& B)
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


bool USpiceTypes::Greater_SEphemerisTimeSEphemerisTime(const FSEphemerisTime& A, const FSEphemerisTime& B)
{
    return A.seconds > B.seconds;
}

bool USpiceTypes::Less_SEphemerisTimeSEphemerisTime(const FSEphemerisTime& A, const FSEphemerisTime& B)
{
    return A.seconds < B.seconds;
}


FSSpeed USpiceTypes::Multiply_SSpeedDouble(const FSSpeed& A, double B)
{
    return A * B;
}

FSSpeed USpiceTypes::Multiply_DoubleSSpeed(double A, const FSSpeed& B)
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

FSVelocityVector USpiceTypes::Multiply_SVelocityVectorDouble(const FSVelocityVector& A, double B)
{
    return A * B;
}

FSVelocityVector USpiceTypes::Multiply_DoubleSVelocityVector(double A, const FSVelocityVector& B)
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


FString USpiceTypes::Conv_SAngleToString(const FSAngle& value)
{
    return FormatAngle(value);
}

FString USpiceTypes::Conv_SDistanceToString(const FSDistance& value)
{
    return FormatDouble(value.km);
}

FString USpiceTypes::Conv_SDistanceVectorToString(const FSDistanceVector& value)
{
    return FString::Printf(TEXT("(%s, %s, %s)"), *FormatDouble(value.x.km), *FormatDouble(value.y.km), *FormatDouble(value.z.km));
}

FString USpiceTypes::Conv_SVelocityVectorToString(const FSVelocityVector& value)
{
    return FString::Printf(TEXT("(%s, %s, %s)"), *FormatDouble(value.dx.kmps), *FormatDouble(value.dy.kmps), *FormatDouble(value.dz.kmps));
}

FString USpiceTypes::Conv_SStateVectorToString(const FSStateVector& value)
{
    return FString::Printf(TEXT("[(%s, %s, %s); (%s, %s, %s)]"), *FormatDouble(value.r.x.km), *FormatDouble(value.r.y.km), *FormatDouble(value.r.z.km), *FormatDouble(value.v.dx.kmps), *FormatDouble(value.v.dy.kmps), *FormatDouble(value.v.dz.kmps));
}

FString USpiceTypes::Conv_SLonLatToString(const FSLonLat& value)
{
    return FormatLonLat(value);
}

FString USpiceTypes::Conv_SSpeedToString(const FSSpeed& value)
{
    return FormatDouble(value.kmps);
}

FString USpiceTypes::Conv_SAngularRateToString(const FSAngularRate& value)
{
    return FormatDouble(value.degreesPerSecond());
}

FString USpiceTypes::Conv_SDimensionlessVectorToString(const FSDimensionlessVector& value)
{
    return FString::Printf(TEXT("(%s, %s, %s)"), *FormatDouble(value.x), *FormatDouble(value.y), *FormatDouble(value.z));
}

FString USpiceTypes::Conv_SDimensionlessStateVectorToString(const FSDimensionlessStateVector& value)
{
    return FString::Printf(TEXT("[(%s, %s, %s); (%s, %s, %s)]"), *FormatDouble(value.r.x), *FormatDouble(value.r.y), *FormatDouble(value.r.z), *FormatDouble(value.dr.x), *FormatDouble(value.dr.y), *FormatDouble(value.dr.z));
}

FString USpiceTypes::Conv_SPlanetographicStateVectorToString(const FSPlanetographicStateVector& value)
{
    return FString::Printf(TEXT("[(%s), %s; (%s, %s, %s)]"), *FormatLonLat(value.r.lonlat), *FormatDouble(value.r.alt.km), *FormatDouble(value.dr.dlon.degreesPerSecond()), *FormatDouble(value.dr.dlat.degreesPerSecond()), *FormatDouble(value.dr.dalt.kmps));
}

FString USpiceTypes::Conv_SGeodeticStateVectorToString(const FSGeodeticStateVector& value)
{
    return FString::Printf(TEXT("[(%s), %s; (%s, %s, %s)]"), *FormatLonLat(value.r.lonlat), *FormatDouble(value.r.alt.km), *FormatDouble(value.dr.dlon.degreesPerSecond()), *FormatDouble(value.dr.dlat.degreesPerSecond()), *FormatDouble(value.dr.dalt.kmps));
}

FString USpiceTypes::Conv_SSphericalStateVectorToString(const FSSphericalStateVector& value)
{
    return FString::Printf(TEXT("[(%s, %s, %s); (%s, %s, %s)]"), *FormatDouble(value.r.r.km), *FormatDouble(value.r.colat.degrees), *FormatDouble(value.r.lon.degrees), *FormatDouble(value.dr.dr.kmps), *FormatDouble(value.dr.dcolat.degreesPerSecond()), *FormatDouble(value.dr.dlon.degreesPerSecond()));
}

FString USpiceTypes::Conv_SLatitudinalStateVectorToString(const FSLatitudinalStateVector& value)
{
    return FString::Printf(TEXT("[%s, (%s, %s); (%s, %s, %s)]"), *FormatDouble(value.r.r.km), *FormatDouble(value.r.lonlat.longitude.degrees), *FormatDouble(value.r.lonlat.latitude.degrees), *FormatDouble(value.dr.dr.kmps), *FormatDouble(value.dr.dlon.degreesPerSecond()), *FormatDouble(value.dr.dlat.degreesPerSecond()));
}

FString USpiceTypes::Conv_SCylindricalStateVectorToString(const FSCylindricalStateVector& value)
{
    return FString::Printf(TEXT("[(%s, %s, %s); (%s, %s, %s)]"), *FormatDouble(value.r.r.km), *FormatDouble(value.r.lon.degrees), *FormatDouble(value.r.z.km), *FormatDouble(value.dr.dr.kmps), *FormatDouble(value.dr.dlon.degreesPerSecond()), *FormatDouble(value.dr.dz.kmps));
}

FString USpiceTypes::Conv_SPlanetographicVectorToString(const FSPlanetographicVector& value)
{
    return FString::Printf(TEXT("(%s; %s)"), *FormatLonLat(value.lonlat), *FormatDouble(value.alt.km));
}

FString USpiceTypes::Conv_SGeodeticVectorToString(const FSGeodeticVector& value)
{
    return FString::Printf(TEXT("(%s; %s)"), *FormatLonLat(value.lonlat), *FormatDouble(value.alt.km));
}

FString USpiceTypes::Conv_SSphericalVectorToString(const FSSphericalVector& value)
{
    return FString::Printf(TEXT("(%s; %s, %s)"), *FormatDouble(value.r.km), *FormatDouble(value.colat.degrees), *FormatDouble(value.lon.degrees));
}

FString USpiceTypes::Conv_SLatitudinalVectorToString(const FSLatitudinalVector& value)
{
    return FString::Printf(TEXT("(%s; %s)"), *FormatDouble(value.r.km), *FormatLonLat(value.lonlat));
}

FString USpiceTypes::Conv_SCylindricalVectorToString(const FSCylindricalVector& value)
{
    return FString::Printf(TEXT("(%s, %s, %s)"), *FormatDouble(value.r.km), *FormatDouble(value.lon.degrees), *FormatDouble(value.z.km));
}

FString USpiceTypes::Conv_SPlanetographicVectorRatesToString(const FSPlanetographicVectorRates& value)
{
    return FString::Printf(TEXT("(%s, %s, %s)"), *FormatDouble(value.dlon.degreesPerSecond()), *FormatDouble(value.dlat.degreesPerSecond()), *FormatDouble(value.dalt.kmps));
}

FString USpiceTypes::Conv_SGeodeticVectorRatesToString(const FSGeodeticVectorRates& value)
{
    return FString::Printf(TEXT("(%s, %s, %s)"), *FormatDouble(value.dlon.degreesPerSecond()), *FormatDouble(value.dlat.degreesPerSecond()), *FormatDouble(value.dalt.kmps));
}

FString USpiceTypes::Conv_SSphericalVectorRatesToString(const FSSphericalVectorRates& value)
{
    return FString::Printf(TEXT("(%s, %s, %s)"), *FormatDouble(value.dr.kmps), *FormatDouble(value.dcolat.degreesPerSecond()), *FormatDouble(value.dlon.degreesPerSecond()));
}

FString USpiceTypes::Conv_SLatitudinaVectorRatesToString(const FSLatitudinalVectorRates& value)
{
    return FString::Printf(TEXT("(%s, %s, %s)"), *FormatDouble(value.dr.kmps), *FormatDouble(value.dlon.degreesPerSecond()), *FormatDouble(value.dlat.degreesPerSecond()));
}

FString USpiceTypes::Conv_SCylindricalVectorRatesToString(const FSCylindricalVectorRates& value)
{
    return FString::Printf(TEXT("(%s, %s, %s)"), *FormatDouble(value.dr.kmps), *FormatDouble(value.dlon.degreesPerSecond()), *FormatDouble(value.dz.kmps));
}

FString USpiceTypes::Conv_SConicElementsToString(const FSConicElements& value)
{
    return FString::Printf(
        TEXT("(%s; %s, %s, %s; %s %s; %s)"),
        *FormatDouble(value.PerifocalDistance.km),
        *FormatDouble(value.Inclination.degrees),
        *FormatDouble(value.LongitudeOfAscendingNode.degrees),
        *FormatDouble(value.ArgumentOfPeriapse.degrees),
        *FormatDouble(value.MeanAnomalyAtEpoch.degrees),
        *FormatDouble(value.Epoch.seconds),
        *FormatDouble(value.GravitationalParameter.GM)
        );
}

FString USpiceTypes::Conv_SMassConstantToString(const FSMassConstant& value)
{
    return FormatDouble(value.GM);
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


FString USpiceTypes::formatAngle(const double degrees, ES_AngleFormat format)
{
    // UE displays degrees incorrectly
    bool useDegreeSymbol = false;

    std::wostringstream streamObj;
    int floatFormatPrecision = USpiceTypes::FloatFormatPrecision;
    streamObj << std::setprecision(USpiceTypes::FloatFormatPrecision);

    if (format == ES_AngleFormat::DD)
    {
        streamObj << std::setprecision(floatFormatPrecision);
        streamObj << degrees;
        if(useDegreeSymbol) streamObj << L'\370';
    }
    else if (format == ES_AngleFormat::DMS)
    {
        int frac_precision = floatFormatPrecision - 7;
        double frac = abs(degrees);
        
        long deg = floorl(frac);

        frac -= (double)deg;
        if (degrees < 0.) deg *= -1;
        streamObj << deg;
        if (useDegreeSymbol) streamObj << L'\370';
        streamObj << L' ';

        frac *= 60.;
        long amin = floorl(frac);
        frac -= (double)amin;
        streamObj << std::setw(2) << std::setfill(L'0') << amin << L'\'';

        frac *= 60;

        if (frac_precision <= 0)
        {
            long asec = lround(frac);
            streamObj << std::setw(2) << std::setfill(L'0') << asec << '"';
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
        streamObj << std::setw(2) << std::setfill(L'0') << min << "m ";

        frac *= 60;

        if (frac_precision <= 0)
        {
            long sec = lround(frac);
            streamObj << std::setw(2) << std::setfill(L'0') << sec << "s ";
        }
        else
        {
            double sec = frac;
            streamObj << std::fixed << std::setprecision(frac_precision + 2) << sec << "s";
        }
    }
    else
    {
        streamObj << std::setprecision(floatFormatPrecision);
        streamObj << (degrees / 360. * twopi_c());
    }

    return FString(streamObj.str().c_str());
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