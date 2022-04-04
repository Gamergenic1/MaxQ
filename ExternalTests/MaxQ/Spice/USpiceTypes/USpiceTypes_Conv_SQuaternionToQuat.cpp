// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"

#include "MaxQTestDefinitions.h"

TEST(Conv_SQuaternionToQuatTest, XAroundNinety) {
    double sincos = FMath::Sqrt(2.) / 2.;
    // +x rotation = w=x=sincos, y=z=0;
    // = -y rotation in LHS
    FSQuaternion RHS_SQuaternion(sincos, +sincos, 0, 0);

    FSRotationMatrix m;
    USpice::q2m(RHS_SQuaternion, m);

    FQuat LHS_Quat = USpiceTypes::Conv_SQuaternionToQuat(RHS_SQuaternion);
    EXPECT_NEAR(LHS_Quat.X, 0, 0.000001);
    EXPECT_NEAR(LHS_Quat.Y, -sincos, 0.000001);
    EXPECT_NEAR(LHS_Quat.Z, 0, 0.000001);
    EXPECT_NEAR(LHS_Quat.W, sincos, 0.000001);

    FVector LHS_Z(0, 0, 1);
    FVector LHS_Z_Rotated = LHS_Quat * LHS_Z;

    EXPECT_NEAR(LHS_Z_Rotated.X, -1, 0.000001);
    EXPECT_NEAR(LHS_Z_Rotated.Y, 0, 0.000001);
    EXPECT_NEAR(LHS_Z_Rotated.Z, 0, 0.000001);

}


TEST(Conv_SQuaternionToQuatTest, 9994_Is_Rotating_25) {
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
    double fractionalRotationAtEpoch = 0.25;
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

    FSQuaternion q;
    USpice::m2q(ResultCode, ErrorMessage, rotationMatrix, q);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    FQuat UERotation = USpiceTypes::Conv_SQuaternionToQuat(q);
    FVector UEAngularVelocity = USpiceTypes::Conv_SAngularVelocityToVector(angularVelocity);

    // At T/4, the rotation:
    // +90 +Z in RHS.
    // -90 +Z in LHS
    // But sxform/xf2rax give a coordinate system rotation from J2000 to Bodyframe...
    // So, rotating the body frame into J2000 is inverse: +90 Z+
    float sincos = FMath::Sqrt(2.f) / 2.f;

    EXPECT_NEAR(UERotation.W, sincos, 0.000001f);
    EXPECT_NEAR(UERotation.X, 0, 0.000001f);
    EXPECT_NEAR(UERotation.Y, 0, 0.000001f);
    EXPECT_NEAR(UERotation.Z, +sincos, 0.000001f);

    // in UE scenegraph should be -90d around +Z
    // and the angular velocity (0,0,-w)
    EXPECT_NEAR(UEAngularVelocity.X, 0.f, 0.000001f);
    EXPECT_NEAR(UEAngularVelocity.Y, 0.f, 0.000001f);
    EXPECT_NEAR(UEAngularVelocity.Z, (float)-w.AsRadiansPerSecond(), 0.000001f);
}