// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceTypes.cpp
// 
// Implementation Comments
// 
// USpiceTypes : public UBlueprintFunctionLibrary
// 
// Purpose:  Blueprint implementations of CSPICE Type wrappers
// 
// MaxQ:
// * Base API
// * Refined API
//    * C++
//    * Blueprints
//
// MaxQ: Three APIs
// * Base API :  Initial Harness for studying integration with UE
//    ~ USpice, USpiceTypes, etc
// * Refined API
//    * C++ :  C++-friendly
//      ~ SpiceMath.h, SpiceOperators.h, etc
//    * Blueprints :  C++-friendly
//      ~ USpiceK2, UK2Node_unorm, etc
// 
// USpiceTypes is part of the base API, where CSPICE functionality is initially
// implemented/tested/studied.
// 
// This is the core Blueprint Library that exposes CSPICE types to Blueprints.
// It is purposefully simple and linear.
// Here, blueprints actions and types are implemented by UFUNCTION reflection.
// This means a lot of duplication due to limitations of the reflection system
// and how it handles types.
// When bringing up new CSPICE types it starts here where it's exposed
// to Blueprints in a way that's easy to debug and determine the best manner
// to expose it in a UE-friendly manner.
// Many operators etc are reintegrated in the C++-friendly API (SpiceMath.h,
// SpiceOperators.h, etc) and then the Blueprint-friendly API (K2 Nodes).
// K2 Nodes support BP wildcards, so that one operation supports multiple
// Types to support Blueprint-friendly actions.
// The implementations here are maintained for compatibility and then may be
// redirected at the refined API.
//------------------------------------------------------------------------------


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

using namespace MaxQ::Private;

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

FSDimensionlessVector USpiceTypes::MultiplyVec_SRotationMatrixSDimensionlessVector(const FSRotationMatrix& A, const FSDimensionlessVector& B)
{
    return A * B;
}


FSDistanceVector USpiceTypes::MultiplyDist_SRotationMatrixSDistanceVector(const FSRotationMatrix& A, const FSDistanceVector& B)
{
    return A * B;
}


FSVelocityVector USpiceTypes::MultiplyVel_SRotationMatrixVelocityVector(const FSRotationMatrix& A, const FSVelocityVector& B)
{
    return A * B;
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
    return MaxQ::Math::Swizzle(value);
}

FVector USpiceTypes::Conv_SDistanceVectorToVector(
    const FSDistanceVector& value
)
{
    return MaxQ::Math::Swizzle(value);
}

FVector USpiceTypes::Conv_SVelocityVectorToVector(
    const FSVelocityVector& value
)
{
    return MaxQ::Math::Swizzle(value);
}

FSDimensionlessVector USpiceTypes::Conv_VectorToSDimensionless(
    const FVector& value
)
{
    return MaxQ::Math::Swizzle<FSDimensionlessVector>(value);
}


FSAngularVelocity USpiceTypes::Conv_VectorToSAngularVelocity(
    const FVector& value
)
{
    return MaxQ::Math::Swizzle<FSAngularVelocity>(value);
}

FVector USpiceTypes::Conv_SAngularVelocityToVector(
    const FSAngularVelocity& value
)
{
    return MaxQ::Math::Swizzle(value);
}


FString USpiceTypes::Conv_SAngularVelocityToString(const FSAngularVelocity& value)
{
    return value.ToString();
}

FString USpiceTypes::Conv_SQuaternionToString(const FSQuaternion& value)
{
    return value.ToString();
}


FString USpiceTypes::Conv_SQuaternionDerivativeToString(const FSQuaternionDerivative& value)
{
    return value.ToString();
}

FVector4 USpiceTypes::Conv_SQuaternionDerivativeToVector4(const FSQuaternionDerivative& value)
{
    return value.Swizzle();
}

FSQuaternionDerivative USpiceTypes::Conv_Vector4ToSQuaternionDerivative(const FVector4& value)
{
    return FSQuaternionDerivative::Swizzle(value);
}


FSDistanceVector USpiceTypes::Conv_VectorToSDistanceVector(
    const FVector& value
)
{
    return MaxQ::Math::Swizzle<FSDistanceVector>(value);
}


FSVelocityVector USpiceTypes::Conv_VectorToSVelocityVector(
    const FVector& value
)
{
    return MaxQ::Math::Swizzle<FSVelocityVector>(value);
}


FQuat USpiceTypes::Conv_SQuaternionToQuat(
    const FSQuaternion& value
)
{
    return MaxQ::Math::Swizzle(value);
}


FSQuaternion USpiceTypes::Conv_QuatToSQuaternion(
    const FQuat& value
)
{
    return MaxQ::Math::Swizzle(value);
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
    return { MaxQ::Core::ToANSIString(units) };
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


FString USpiceTypes::Conv_SEquinoctialElementsToString(const FSEquinoctialElements& value)
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

    // Use caller-specified precision when provided, otherwise fall back to the global default
    int usePrecision = precision >= 0 ? precision : FloatFormatPrecision;

    // Set precision
    streamObj << std::setprecision(usePrecision);
    
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
        convrt_c(value, MaxQ::Core::ToANSIString(ES_Units::KILOMETERS), MaxQ::Core::ToANSIString(Units), &value);
        UnexpectedErrorCheck(false);
    }

    return FormatDoublePrecisely(value, precision);
}

FString USpiceTypes::FormatPeriod(const FSEphemerisPeriod& period, ES_Units Units /*= ES_Units::SECONDS*/, int precision)
{
    double value = period.AsSeconds();

    if(Units != ES_Units::SECONDS)
    {
        convrt_c(value, MaxQ::Core::ToANSIString(ES_Units::SECONDS), MaxQ::Core::ToANSIString(Units), &value);

        UnexpectedErrorCheck(false);
    }

    return FormatDoublePrecisely(value, precision);
}

FString USpiceTypes::FormatSpeed(const FSSpeed& speed, ES_Units NumeratorUnits /*= ES_Units::KILOMETERS*/, ES_Units DenominatorUnits /*= ES_Units::SECONDS*/, int precision)
{
    double value = speed.AsKilometersPerSecond();

    if(NumeratorUnits != ES_Units::KILOMETERS)
    {
        convrt_c(value, MaxQ::Core::ToANSIString(ES_Units::KILOMETERS), MaxQ::Core::ToANSIString(NumeratorUnits), &value);
        UnexpectedErrorCheck(false);
    }

    if(DenominatorUnits != ES_Units::SECONDS)
    {
        double denominator = 1.;
        convrt_c(denominator, MaxQ::Core::ToANSIString(ES_Units::SECONDS), MaxQ::Core::ToANSIString(DenominatorUnits), &denominator);
        UnexpectedErrorCheck(false);
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


