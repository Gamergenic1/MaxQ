// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSAngularRateTest, DefaultConstruction_Is_Initialized) {
    FSAngularRate angularRate;

    EXPECT_DOUBLE_EQ(angularRate.radiansPerSecond, 0.);
}

TEST(FSAngularRateTest, StaticZero_Is_Zero) {

    EXPECT_DOUBLE_EQ(FSAngularRate::Zero.radiansPerSecond, 0.);
}


