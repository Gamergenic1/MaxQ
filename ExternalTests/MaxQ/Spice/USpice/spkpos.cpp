// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"
#include "MaxQTestDefinitions.h"

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


TEST(spkpos_test, FAKEBODY9993_Is_OrbitingFAKEBODY9995) {

    USpice::init_all();

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    USpice::furnsh_absolute("maxq_unit_test_meta.tm");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSDistanceVector ptarg;
    FSEphemerisPeriod lt(1.5);
    FString targ = TEXT("FAKEBODY9993");
    FString obs = TEXT("FAKEBODY9995");
    FString ref = TEXT("J2000");
    ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::None;

    USpice::spkpos(ResultCode, ErrorMessage, et0, ptarg, lt, targ, obs, ref, abcorr);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);
    // SPICE populates something into lt... something non-zero... Even if we set it to ::None
    // EXPECT_DOUBLE_EQ(lt.seconds, 0.);
    EXPECT_LT((ptarg - state_target_9993_center_9995_j2000_et0.r).Magnitude(), 0.000001);
}