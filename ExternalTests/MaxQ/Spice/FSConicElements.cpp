// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSConicElementsTest, DefaultConstruction_IsInitialized) {
    FSConicElements conicElements;

    EXPECT_DOUBLE_EQ(conicElements.PerifocalDistance.km, 0.);
    EXPECT_DOUBLE_EQ(conicElements.Eccentricity, 0.);
    EXPECT_DOUBLE_EQ(conicElements.Inclination.degrees, 0.);
    EXPECT_DOUBLE_EQ(conicElements.LongitudeOfAscendingNode.degrees, 0.);
    EXPECT_DOUBLE_EQ(conicElements.ArgumentOfPeriapse.degrees, 0.);
    EXPECT_DOUBLE_EQ(conicElements.MeanAnomalyAtEpoch.degrees, 0.);
    EXPECT_DOUBLE_EQ(conicElements.Epoch.seconds, 0.);
    EXPECT_DOUBLE_EQ(conicElements.GravitationalParameter.GM, 0.);
}

