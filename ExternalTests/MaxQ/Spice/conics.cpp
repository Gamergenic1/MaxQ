// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(conics_test, DefaultsTestCase) {
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSStateVector stateVector;
    FSEphemerisTime et;
    FSConicElements elts;

    USpice::conics(ResultCode, ErrorMessage, elts, et, stateVector);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);

    EXPECT_DOUBLE_EQ(stateVector.r.x.km, 0.);
    EXPECT_DOUBLE_EQ(stateVector.r.y.km, 0.);
    EXPECT_DOUBLE_EQ(stateVector.r.z.km, 0.);
    EXPECT_DOUBLE_EQ(stateVector.v.dx.kmps, 0.);
    EXPECT_DOUBLE_EQ(stateVector.v.dy.kmps, 0.);
    EXPECT_DOUBLE_EQ(stateVector.v.dz.kmps, 0.);
}
