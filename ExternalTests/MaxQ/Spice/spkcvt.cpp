// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(spkcvt_test, DefaultsTestCase) {

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSEphemerisTime et, targetEpoch;
    FSStateVector state, targetState;
    FSEphemerisPeriod lt = FSEphemerisPeriod(1.5);
    FString targetCenter;
    FString outRef;
    FString targetRef;
    FString obs;
    ES_ReferenceFrameLocus locus = ES_ReferenceFrameLocus::CENTER;
    ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::None;

    USpice::spkcvt(ResultCode, ErrorMessage, state, lt, targetState, targetEpoch, et, targetCenter, targetRef, outRef, locus, obs, abcorr);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);
    EXPECT_DOUBLE_EQ(lt.seconds, 1.5);
    EXPECT_DOUBLE_EQ(state.r.x.km, 0.);
    EXPECT_DOUBLE_EQ(state.r.y.km, 0.);
    EXPECT_DOUBLE_EQ(state.r.z.km, 0.);
    EXPECT_DOUBLE_EQ(state.v.dx.kmps, 0.);
    EXPECT_DOUBLE_EQ(state.v.dy.kmps, 0.);
    EXPECT_DOUBLE_EQ(state.v.dz.kmps, 0.);
}


TEST(spkcvt_test, EMB_Is_OrbitingSun) {

    // 981005_PLTEPH-DE405S.bsp validity range:
    // 2004 JUN 11 05:01:04 - 2004 JUN 12 12:01:04
    // Bodies: MERCURY BARYCENTER(1)  SATURN BARYCENTER(6)   MERCURY(199)
    // VENUS BARYCENTER(2)    URANUS BARYCENTER(7)   VENUS(299)
    // EARTH BARYCENTER(3)    NEPTUNE BARYCENTER(8)  MOON(301)
    // MARS BARYCENTER(4)     PLUTO BARYCENTER(9)    EARTH(399)
    // JUPITER BARYCENTER(5)  SUN(10)                MARS(499)

    USpice::init_all();

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    USpice::furnsh_absolute("naif0008.tls");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    USpice::furnsh_absolute("981005_PLTEPH-DE405S.bsp");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSEphemerisTime et;
    USpice::str2et(ResultCode, ErrorMessage, et, TEXT("2004 JUN 11 12:00:00.000"));

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSEphemerisTime targetEpoch = et;
    FSStateVector targetState(FSDistanceVector(7000, 0, 0), FSVelocityVector(0, -2, 0));
    FString targetCenter = TEXT("EMB");
    FString outRef = TEXT("ECLIPJ2000");
    FString targetRef = TEXT("J2000");
    FString obs = TEXT("SSB");;
    ES_ReferenceFrameLocus locus = ES_ReferenceFrameLocus::CENTER;
    ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::None;

    FSEphemerisPeriod lt(1.5);
    FSStateVector stateVector;

    USpice::spkcvt(ResultCode, ErrorMessage, stateVector, lt, targetState, targetEpoch, et, targetCenter, targetRef, outRef, locus, obs, abcorr);


    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);
    // SPICE populates something into lt... something non-zero... Even if we set it to ::None
    // EXPECT_DOUBLE_EQ(lt.seconds, 0.);

    // On June 11, both x, y should be -
    EXPECT_LT(stateVector.r.x.km, 0.);
    EXPECT_LT(stateVector.r.y.km, 0.);
    // Should be relatively near zero, but not close enough to test...
    EXPECT_NE(stateVector.r.z.km, 0.);

    // On June 11:
    EXPECT_GT(stateVector.v.dx.kmps, 0.);
    EXPECT_LT(stateVector.v.dy.kmps, 0.);
    EXPECT_NE(stateVector.v.dz.kmps, 0.);

    // It's nearing summer solstice, inferring:
    EXPECT_LT(stateVector.r.y.km, stateVector.r.x.km);
    EXPECT_GT(stateVector.v.dx.kmps, -stateVector.v.dy.kmps);
}