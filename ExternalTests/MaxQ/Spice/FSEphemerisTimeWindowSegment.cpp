// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSEphemerisTimeWindowSegmentTest, DefaultConstruction_IsInitialized) {
    FSEphemerisTimeWindowSegment ephemerisTimeWindowSegment;

    EXPECT_DOUBLE_EQ(ephemerisTimeWindowSegment.start.seconds, 0.);
    EXPECT_DOUBLE_EQ(ephemerisTimeWindowSegment.stop.seconds, 0.);
}

