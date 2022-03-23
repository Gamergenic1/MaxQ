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
    FSEphemerisPeriod lt = FSEphemerisPeriod(1.5);
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
