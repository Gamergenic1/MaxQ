// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSEphemerisPeriodTest, DefaultConstruction_IsInitialized) {
    FSEphemerisPeriod ephemerisPeriod;

    EXPECT_DOUBLE_EQ(ephemerisPeriod.seconds, 0.);
}

