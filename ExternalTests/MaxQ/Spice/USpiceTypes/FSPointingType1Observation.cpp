// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSPointingType1ObservationTest, DefaultConstruction_IsInitialized) {
    FSPointingType1Observation pointingType1Observation;

    EXPECT_DOUBLE_EQ(pointingType1Observation.sclkdp, 0.);
    
    EXPECT_DOUBLE_EQ(pointingType1Observation.quat.w, 1.);
    EXPECT_DOUBLE_EQ(pointingType1Observation.quat.x, 0.);
    EXPECT_DOUBLE_EQ(pointingType1Observation.quat.y, 0.);
    EXPECT_DOUBLE_EQ(pointingType1Observation.quat.z, 0.);

    EXPECT_DOUBLE_EQ(pointingType1Observation.avv.x.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(pointingType1Observation.avv.y.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(pointingType1Observation.avv.z.radiansPerSecond, 0.);
}

