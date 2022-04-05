// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"
#include "MaxQTestDefinitions.h"

TEST(sxform_test, DefaultsTestCase) {
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSStateTransform stateTransform; 
    FSEphemerisTime et;
    FString from;
    FString to;

    USpice::sxform(ResultCode, ErrorMessage, stateTransform, et, from, to);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);

    EXPECT_EQ(stateTransform.m.Num(), 6);
    for (int i = 0; i < stateTransform.m.Num(); ++i)
    {
        EXPECT_DOUBLE_EQ(stateTransform.m[i].r.x, i == 0 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform.m[i].r.y, i == 1 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform.m[i].r.z, i == 2 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform.m[i].dr.x, i == 3 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform.m[i].dr.y, i == 4 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform.m[i].dr.z, i == 5 ? 1. : 0.);
    }
}



// See comments in 9994_Is_RotatingPM_65, below, for a breakdown of the PCK->Frame Transformation math
TEST(sxform_test, 9994_Is_RotatingPM) {
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    USpice::init_all();

    USpice::furnsh_absolute("maxq_unit_test_meta.tm");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSStateTransform stateTransform;
    FString from = TEXT("J2000");
    FString to = TEXT("IAU_FAKEBODY9994");

    // 90 degree rotation around +Z...
    FSEphemerisPeriod T = FSEphemerisPeriod::Day / 10.;
    FSAngularRate w = (_pos360_as_radians / T.AsSeconds());
    FSEphemerisTime et(FSEphemerisTime::J2000 + 0.25 * T);

    USpice::sxform(ResultCode, ErrorMessage, stateTransform, et, from, to);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);

    EXPECT_EQ(stateTransform.m.Num(), 6);


    EXPECT_LT((stateTransform.m[0].r - FSDimensionlessVector(0, 1, 0)).Magnitude(), 0.0000001);
    EXPECT_LT((stateTransform.m[1].r - FSDimensionlessVector(-1, 0, 0)).Magnitude(), 0.0000001);
    EXPECT_LT((stateTransform.m[2].r - FSDimensionlessVector(0, 0, 1)).Magnitude(), 0.0000001);
              
    EXPECT_LT((stateTransform.m[3].r - FSDimensionlessVector(-w.AsRadiansPerSecond(), 0, 0)).Magnitude(), 0.000000001);
    EXPECT_LT((stateTransform.m[4].r - FSDimensionlessVector(0, -w.AsRadiansPerSecond(), 0)).Magnitude(), 0.000000001);
    EXPECT_LT((stateTransform.m[5].r - FSDimensionlessVector(0, 0, 0)).Magnitude(), 0.000000001);

    EXPECT_LT((stateTransform.m[3].dr - FSDimensionlessVector(0, 1, 0)).Magnitude(), 0.0000001);
    EXPECT_LT((stateTransform.m[4].dr - FSDimensionlessVector(-1, 0, 0)).Magnitude(), 0.0000001);
    EXPECT_LT((stateTransform.m[5].dr - FSDimensionlessVector(0, 0, 1)).Magnitude(), 0.0000001);
}



TEST(sxform_test, 9994_Is_RotatingPM_65) {
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    USpice::init_all();

    USpice::furnsh_absolute("maxq_unit_test_meta.tm");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSStateTransform stateTransform;
    FString from = TEXT("J2000");
    FString to = TEXT("IAU_FAKEBODY9994");

    // degree rotation around +Z...
    double fractionalRotationAtEpoch = 0.65;
    FSEphemerisPeriod T = FSEphemerisPeriod::Day / 10.;
    FSAngularRate w = (_pos360_as_radians / T.AsSeconds());
    FSEphemerisTime et(FSEphemerisTime::J2000 + fractionalRotationAtEpoch * T);

    /*
    ------- 'FAKEBODY9994'
        BODY9995_CONSTANTS_REF_FRAME   =   1
        BODY9995_CONSTANTS_JED_EPOCH   =   0
        BODY9994_POLE_RA       = (    -90.0       0.0      0.0  )
        BODY9994_POLE_DEC      = (    +90.0       0.0      0.0  )
        BODY9994_PM            = (      0.0    3600.0      0.0  )
    English Summary:
    FAKEBODY9994
    ...with respect to J2000 REF FRAME (1 = BODY9995_CONSTANTS_REF_FRAME)
    ...starting at J2000 Epoch (0 = BODY9995_CONSTANTS_JED_EPOCH)
    ...With a north pole right ascension of -90 degrees (-90 = POLE_RA[0]) and 0.00 degrees/century precession rate RA (0 = POLE_RA[1])
    ...And a north pole declination of +90 degrees (+90 = POLE_DEC[0] and a 0.00 degrees/century precession rate of DEC (0 = POLE_DEC[1])
    ...Rotates prime meridian around north pole, starting at 0 degrees (0.0 = PM[0]) at 3600 degrees/day (3600.0 = PM[1]).
    */

    USpice::sxform(ResultCode, ErrorMessage, stateTransform, et, from, to);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);

    EXPECT_EQ(stateTransform.m.Num(), 6);

    /* https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/xf2rav_c.html
    rot       is a rotation that gives the transformation from
              some frame FRAME1 to another frame FRAME2*/
    FSRotationMatrix rotationMatrix;

    /*
    av         is the angular velocity of the transformation.
               In other words, if `p' is the position of a fixed
               point in FRAME2, then from the point of view of
               FRAME1, `p' rotates (in a right handed sense) about
               an axis parallel to `av'*/
    FSAngularVelocity angularVelocity;
    /*
               More formally, the velocity `v' of `p' in FRAME1 is
               given by
                   v  = av x ( rot  * p )*/
    USpice::xf2rav(stateTransform, rotationMatrix, angularVelocity);

    // Note that rotation transforms originating from PCK orientation data represent a (3 1 3) rotation concatenation, based on and North pole RA, DEC, and PM rotation.
    FSEulerAngles eulers;
    USpice::m2eul(ResultCode, ErrorMessage, eulers, rotationMatrix, ES_Axis::Z, ES_Axis::X, ES_Axis::Z);

    /* https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/frames.html
    The relationship of these Euler angles to RA/Dec/PM for the J2000-to-IAU Mars body-fixed transformation is as follows:
    angle_1 is        PM  * (radians/degree)
    angle_2 is pi/2 - Dec * (radians/degree)
    angle_3 is pi/2 + RA  * (radians/degree)
    Note:  The angles above are labeled as a (1)(2)(3) concatenation, while m2eul extracts a concatenation labeled (3)(2)(1), so swap angle1, and angle3 below.
   */
    FSAngle PM = eulers.angle3;
    FSAngle Dec = _pos90_as_radians - eulers.angle2;
    FSAngle RA = eulers.angle1 - _pos90_as_radians;

    // Ensure we can compare correctly [0-360)
    PM = FSAngle(USpiceTypes::normalizeZeroToTwoPi(PM.AsRadians()));

    // Mathematically, there is no rotation due to Dec or RA... And RA/PM rotate about the same Axis... so we only know the SUM of RA (-90) plus PM, we cannot isolate them...
    EXPECT_NEAR(USpiceTypes::normalize180to180(PM.AsDegrees() + RA.AsDegrees() - (fractionalRotationAtEpoch * 360. - 90.)), 0, 0.00001);
    EXPECT_EQ(Dec.AsDegrees(), +90.);

    // The angular velocity of the transformation... since the north pole is aligned with the Z+ axis, the av is (0,0,w)
    EXPECT_LT((angularVelocity - FSAngularVelocity(0, 0, w)).Magnitude().AsRadiansPerSecond(), FMath::Abs(w.AsRadiansPerSecond()) / 10000);
}




TEST(sxform_test, 9995_Is_RotatingPM_65) {
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    USpice::init_all();

    USpice::furnsh_absolute("maxq_unit_test_meta.tm");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSStateTransform stateTransform;
    FString from = TEXT("ECLIPJ2000");
    FString to = TEXT("IAU_FAKEBODY9995");

    double fractionalRotationAtEpoch = 0.65;
    FSEphemerisPeriod T = FSEphemerisPeriod::Day;
    FSAngularRate w = (_pos360_as_radians / T.AsSeconds());
    FSEphemerisTime et(FSEphemerisTime::J2000 + fractionalRotationAtEpoch * T);

    USpice::sxform(ResultCode, ErrorMessage, stateTransform, et, from, to);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);

    EXPECT_EQ(stateTransform.m.Num(), 6);

    FSRotationMatrix rotationMatrix;
    FSAngularVelocity angularVelocity;
    USpice::xf2rav(stateTransform, rotationMatrix, angularVelocity);

    FSEulerAngles eulers;
    USpice::m2eul(ResultCode, ErrorMessage, eulers, rotationMatrix, ES_Axis::Z, ES_Axis::X, ES_Axis::Z);

    FSAngle PM = eulers.angle3;
    FSAngle Dec = _pos90_as_radians - eulers.angle2;
    FSAngle RA = eulers.angle1 - _pos90_as_radians;

    PM = FSAngle(USpiceTypes::normalizeZeroToTwoPi(PM.AsRadians()));

    EXPECT_NEAR(PM.AsDegrees(), +10 + fractionalRotationAtEpoch * 360, 0.000001);
    EXPECT_NEAR(Dec.AsDegrees(), +30.0, 0.000001);
    EXPECT_NEAR(RA.AsDegrees(), -75.0, 0.000001);
    // Compare as radians/day w.r.t. tolerance
    EXPECT_NEAR(angularVelocity.Magnitude().AsRadiansPerSecond() * FSEphemerisPeriod::Day.seconds, w.AsRadiansPerSecond() * FSEphemerisPeriod::Day.seconds, 0.000001);

    // The angular velocity should be parallel to a vector at RADec -75, 30...
    double ra = RA.AsRadians();
    double dec = Dec.AsRadians();
    FSDimensionlessVector expectedAvNormal(cos(ra) * cos(dec), sin(ra) * cos(dec), sin(dec));
    FSDimensionlessVector angularVelocityNormal = angularVelocity.Normalized();
    double dotProduct;
    USpice::vdot(expectedAvNormal, angularVelocityNormal, dotProduct);
    EXPECT_NEAR(dotProduct, 1., 0.0001);
}