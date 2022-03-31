// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSEquinoctialElementsTest, DefaultConstruction_IsInitialized) {
    FSEquinoctialElements equinoctialElements;

    EXPECT_DOUBLE_EQ(equinoctialElements.a.km, 0.);
    EXPECT_DOUBLE_EQ(equinoctialElements.h, 0.);
    EXPECT_DOUBLE_EQ(equinoctialElements.k, 0.);
    EXPECT_DOUBLE_EQ(equinoctialElements.MeanLongitude.degrees, 0.);
    EXPECT_DOUBLE_EQ(equinoctialElements.p, 0.);
    EXPECT_DOUBLE_EQ(equinoctialElements.q, 0.);
    EXPECT_DOUBLE_EQ(equinoctialElements.RateOfLongitudeOfPeriapse.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(equinoctialElements.MeanLongitudeDerivative.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(equinoctialElements.RateOfLongitudeOfAscendingNode.radiansPerSecond, 0.);
}

