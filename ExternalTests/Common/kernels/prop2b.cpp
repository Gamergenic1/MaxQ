// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(prop2b_test, DefaultsTestCase) {

    ES_ResultCode ResultCode;
    FString ErrorMessage;

    FSStateVector stateIn;
    FSStateVector stateOut;
    FSEphemerisPeriod dt;
    FSMassConstant gm;
    FSConicElements elts;

    USpice::prop2b(ResultCode, ErrorMessage, gm, stateIn, dt, stateOut);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);
    
    EXPECT_DOUBLE_EQ(stateOut.r.x.km, 0.);
    EXPECT_DOUBLE_EQ(stateOut.r.y.km, 0.);
    EXPECT_DOUBLE_EQ(stateOut.r.z.km, 0.);
    EXPECT_DOUBLE_EQ(stateOut.v.dx.kmps, 0.);
    EXPECT_DOUBLE_EQ(stateOut.v.dy.kmps, 0.);
    EXPECT_DOUBLE_EQ(stateOut.v.dz.kmps, 0.);
}