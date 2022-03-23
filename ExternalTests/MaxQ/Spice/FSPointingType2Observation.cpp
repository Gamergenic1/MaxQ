// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSPointingType2ObservationTest, DefaultConstruction_IsInitialized) {
    FSPointingType2Observation pointingType2Observation;

    EXPECT_DOUBLE_EQ(pointingType2Observation.segment.start, 0.);
    EXPECT_DOUBLE_EQ(pointingType2Observation.segment.stop, 0.);
    EXPECT_DOUBLE_EQ(pointingType2Observation.quat.w, 1.);
    EXPECT_DOUBLE_EQ(pointingType2Observation.quat.x, 0.);
    EXPECT_DOUBLE_EQ(pointingType2Observation.quat.y, 0.);
    EXPECT_DOUBLE_EQ(pointingType2Observation.quat.z, 0.);
    EXPECT_DOUBLE_EQ(pointingType2Observation.avv.x.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(pointingType2Observation.avv.y.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(pointingType2Observation.avv.z.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(pointingType2Observation.rate, 0.);
}

