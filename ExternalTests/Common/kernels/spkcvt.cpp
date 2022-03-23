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
