// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(oscelt_test, DefaultsTestCase) {

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;
    FSStateVector stateVector;
    FSEphemerisTime et;
    FSMassConstant gm;
    FSConicElements elts;

    USpice::oscelt(ResultCode, ErrorMessage, stateVector, et, gm, elts);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);

    EXPECT_DOUBLE_EQ(elts.PerifocalDistance.km, 0.);
    EXPECT_DOUBLE_EQ(elts.Eccentricity, 0.);
    EXPECT_DOUBLE_EQ(elts.Inclination.degrees, 0.);
    EXPECT_DOUBLE_EQ(elts.ArgumentOfPeriapse.degrees, 0.);
    EXPECT_DOUBLE_EQ(elts.LongitudeOfAscendingNode.degrees, 0.);
    EXPECT_DOUBLE_EQ(elts.MeanAnomalyAtEpoch.degrees, 0.);
    EXPECT_DOUBLE_EQ(elts.Epoch.seconds, 0.);
    EXPECT_DOUBLE_EQ(elts.GravitationalParameter.GM, 0.);
}