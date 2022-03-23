// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSEphemerisTimeTest, DefaultConstruction_IsInitialized) {
    FSEphemerisTime ephemerisTime;

    EXPECT_DOUBLE_EQ(ephemerisTime.seconds, 0.);
}

