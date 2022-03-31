// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"

#include "MaxQTestDefinitions.h"

TEST(pxform_test, DefaultsTestCase) {
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSRotationMatrix rotationMatrix;
    FSEphemerisTime et;
    FString from;
    FString to;

    USpice::pxform(ResultCode, ErrorMessage, rotationMatrix, et, from, to);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);

    EXPECT_EQ(rotationMatrix.m.Num(), 3);
    for (int i = 0; i < rotationMatrix.m.Num(); ++i)
    {
        EXPECT_DOUBLE_EQ(rotationMatrix.m[i].x, i == 0 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(rotationMatrix.m[i].y, i == 1 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(rotationMatrix.m[i].z, i == 2 ? 1. : 0.);
    }

    // Note that rotation transforms originating from PCK orientation data represent a (3 1 3) rotation concatenation, based on and North pole RA, DEC, and PM rotation.

}


TEST(pxform_test, 9994_Is_RotatingPM) {
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    USpice::init_all();

    USpice::furnsh_absolute("maxq_unit_test_meta.tm");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSRotationMatrix rotationMatrix;
    FString from = TEXT("J2000");
    FString to = TEXT("IAU_FAKEBODY9994");

    // 90 degree rotation around +Z...
    FSEphemerisPeriod T = FSEphemerisPeriod::Day / 10.;
    const double fractionalRotationAtEpoch = 0.25;
    FSAngularRate w = (_pos360_as_radians / T.AsSeconds());
    FSEphemerisTime et(FSEphemerisTime::J2000 + fractionalRotationAtEpoch * T);

    USpice::pxform(ResultCode, ErrorMessage, rotationMatrix, et, from, to);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);

    EXPECT_EQ(rotationMatrix.m.Num(), 3);

    EXPECT_LT((rotationMatrix.m[0] - FSDimensionlessVector(0, 1, 0)).Magnitude(), 0.0000001);
    EXPECT_LT((rotationMatrix.m[1] - FSDimensionlessVector(-1, 0, 0)).Magnitude(), 0.0000001);
    EXPECT_LT((rotationMatrix.m[2] - FSDimensionlessVector(0, 0, 1)).Magnitude(), 0.0000001);

    // Note that rotation transforms originating from PCK orientation data represent a (3 1 3) rotation concatenation, based on and North pole RA, DEC, and PM rotation.
    FSEulerAngles eulers;
    USpice::m2eul(ResultCode, ErrorMessage, eulers, rotationMatrix, ES_Axis::Z, ES_Axis::X, ES_Axis::Z);

    FSAngle PM = eulers.angle3;
    FSAngle Dec = _pos90_as_radians - eulers.angle2;
    FSAngle RA = eulers.angle1 - _pos90_as_radians;

    // Mathematically, there is no rotation due to Dec or RA... And RA/PM rotate about the same Axis... so we only know the SUM of RA (-90) plus PM, we cannot isolate them...
    EXPECT_NEAR(USpiceTypes::normalize180to180(PM.AsDegrees() + RA.AsDegrees() - (fractionalRotationAtEpoch * 360. - 90.)), 0, 0.0000001);
    EXPECT_EQ(Dec.AsDegrees(), +90.);
}


TEST(pxform_test, 9994_Is_RotatingPM_65) {
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    USpice::init_all();

    USpice::furnsh_absolute("maxq_unit_test_meta.tm");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSRotationMatrix rotationMatrix;
    FString from = TEXT("J2000");
    FString to = TEXT("IAU_FAKEBODY9994");

    // 90 degree rotation around +Z...
    FSEphemerisPeriod T = FSEphemerisPeriod::Day / 10.;
    FSAngularRate w = (_pos360_as_radians / T.AsSeconds());
    const double fractionalRotationAtEpoch = 0.65;
    FSEphemerisTime et(FSEphemerisTime::J2000 + fractionalRotationAtEpoch * T);

    USpice::pxform(ResultCode, ErrorMessage, rotationMatrix, et, from, to);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);

    EXPECT_EQ(rotationMatrix.m.Num(), 3);

    // Note that rotation transforms originating from PCK orientation data represent a (3 1 3) rotation concatenation, based on and North pole RA, DEC, and PM rotation.
    FSEulerAngles eulers;
    USpice::m2eul(ResultCode, ErrorMessage, eulers, rotationMatrix, ES_Axis::Z, ES_Axis::X, ES_Axis::Z);

    FSAngle PM = eulers.angle3;
    FSAngle Dec = _pos90_as_radians - eulers.angle2;
    FSAngle RA = eulers.angle1 - _pos90_as_radians;

    PM = FSAngle(USpiceTypes::normalizeZeroToTwoPi(PM.AsRadians()));

    // Mathematically, there is no rotation due to Dec or RA... And RA/PM rotate about the same Axis... so we only know the SUM of RA (-90) plus PM, we cannot isolate them...
    EXPECT_NEAR(USpiceTypes::normalize180to180(PM.AsDegrees() + RA.AsDegrees() - (fractionalRotationAtEpoch * 360. - 90.)), 0, 0.0000001);
    EXPECT_EQ(Dec.AsDegrees(), +90.);
}



TEST(pxform_test, 9995_Is_RotatingPM_65) {
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    USpice::init_all();

    USpice::furnsh_absolute("maxq_unit_test_meta.tm");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSRotationMatrix rotationMatrix;
    FString from = TEXT("ECLIPJ2000");
    FString to = TEXT("IAU_FAKEBODY9995");

    // rotation around +Z...
    double fractionalRotation = 0.65;
    FSEphemerisPeriod T = FSEphemerisPeriod::Day;
    FSAngularRate w = (_pos360_as_radians / T.AsSeconds());
    FSEphemerisTime et(FSEphemerisTime::J2000 + fractionalRotation * T);

    USpice::pxform(ResultCode, ErrorMessage, rotationMatrix, et, from, to);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);

    EXPECT_EQ(rotationMatrix.m.Num(), 3);

    // Note that rotation transforms originating from PCK orientation data represent a (3 1 3) rotation concatenation, based on and North pole RA, DEC, and PM rotation.

//    USpice::xpose(rotationMatrix, rotationMatrix);

    FSEulerAngles eulers;
    USpice::m2eul(ResultCode, ErrorMessage, eulers, rotationMatrix, ES_Axis::Z, ES_Axis::X, ES_Axis::Z);

    FSAngle PM = eulers.angle3;
    FSAngle Dec = _pos90_as_radians - eulers.angle2;
    FSAngle RA = eulers.angle1 - _pos90_as_radians;

    PM = FSAngle(USpiceTypes::normalizeZeroToTwoPi(PM.AsRadians()));

    EXPECT_NEAR(PM.AsDegrees(), +10 + fractionalRotation * 360, 0.000001);
    EXPECT_NEAR(Dec.AsDegrees(), +30.0, 0.000001);
    EXPECT_NEAR(RA.AsDegrees(), -75.0, 0.000001);
}