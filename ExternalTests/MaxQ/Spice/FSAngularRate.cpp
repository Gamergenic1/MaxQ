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

TEST(FSAngularRateTest, DefaultConstruction_Is_Initialized) {
    FSAngularRate angularRate;

    EXPECT_EQ(angularRate.radiansPerSecond, 0.);
}

TEST(FSAngularRateTest, StaticZero_Is_Zero) {

    EXPECT_EQ(FSAngularRate::Zero.radiansPerSecond, 0.);
}


