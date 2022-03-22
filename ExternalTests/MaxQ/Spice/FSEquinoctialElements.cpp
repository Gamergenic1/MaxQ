// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "UE5HostDefs.h"
#include "SpiceHostDefs.h"

#include "Spice.h"
#include "SpiceTypes.h"

#include "gtest/gtest.h"

TEST(FSEquinoctialElementsTest, DefaultConstruction_IsInitialized) {
    FSEquinoctialElements equinoctialElements;

    EXPECT_EQ(equinoctialElements.a.km, 0.);
    EXPECT_EQ(equinoctialElements.h, 0.);
    EXPECT_EQ(equinoctialElements.k, 0.);
    EXPECT_EQ(equinoctialElements.MeanLongitude.degrees, 0.);
    EXPECT_EQ(equinoctialElements.p, 0.);
    EXPECT_EQ(equinoctialElements.q, 0.);
    EXPECT_EQ(equinoctialElements.RateOfLongitudeOfPeriapse.radiansPerSecond, 0.);
    EXPECT_EQ(equinoctialElements.MeanLongitudeDerivative.radiansPerSecond, 0.);
    EXPECT_EQ(equinoctialElements.RateOfLongitudeOfAscendingNode.radiansPerSecond, 0.);
}

