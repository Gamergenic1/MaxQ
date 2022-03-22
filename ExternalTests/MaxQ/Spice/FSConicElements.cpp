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

TEST(FSConicElementsTest, DefaultConstruction_IsInitialized) {
    FSConicElements conicElements;

    EXPECT_EQ(conicElements.PerifocalDistance.km, 0.);
    EXPECT_EQ(conicElements.Eccentricity, 0.);
    EXPECT_EQ(conicElements.Inclination.degrees, 0.);
    EXPECT_EQ(conicElements.LongitudeOfAscendingNode.degrees, 0.);
    EXPECT_EQ(conicElements.ArgumentOfPeriapse.degrees, 0.);
    EXPECT_EQ(conicElements.MeanAnomalyAtEpoch.degrees, 0.);
    EXPECT_EQ(conicElements.Epoch.seconds, 0.);
    EXPECT_EQ(conicElements.GravitationalParameter.GM, 0.);
}

