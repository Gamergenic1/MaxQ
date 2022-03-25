// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(spkpos_test, DefaultsTestCase) {

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSEphemerisTime et;
    FSDistanceVector ptarg;
    FSEphemerisPeriod lt(1.5);
    FString targ;
    FString obs;
    FString ref;
    ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::None;

    USpice::spkpos(ResultCode, ErrorMessage, et, ptarg, lt, targ, obs, ref, abcorr);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);
    EXPECT_DOUBLE_EQ(lt.seconds, 1.5);
    EXPECT_DOUBLE_EQ(ptarg.x.km, 0.);
    EXPECT_DOUBLE_EQ(ptarg.y.km, 0.);
    EXPECT_DOUBLE_EQ(ptarg.z.km, 0.);
}


TEST(spkpos_test, EMB_Is_OrbitingSun) {

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

    FSDistanceVector ptarg;
    FSEphemerisPeriod lt(1.5);
    FString targ = TEXT("EMB");
    FString obs = TEXT("SSB");
    FString ref = TEXT("ECLIPJ2000");
    ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::None;

    USpice::spkpos(ResultCode, ErrorMessage, et, ptarg, lt, targ, obs, ref, abcorr);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);
    // SPICE populates something into lt... something non-zero... Even if we set it to ::None
    // EXPECT_DOUBLE_EQ(lt.seconds, 0.);

    // On June 11, both x, y should be -
    EXPECT_LT(ptarg.x.km, 0.);
    EXPECT_LT(ptarg.y.km, 0.);
    // Should be retively near zero, but not close enough to test...
    EXPECT_NE(ptarg.z.km, 0.);

    // It's nearing summer solstice, inferring:
    EXPECT_LT(ptarg.y.km, ptarg.x.km);
}