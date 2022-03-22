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

TEST(FSAngularVelocityTest, DefaultConstruction_IsInitialized) {
    FSAngularVelocity angularVelocity;

    EXPECT_EQ(angularVelocity.x.AsRadiansPerSecond(), 0.);
    EXPECT_EQ(angularVelocity.y.AsRadiansPerSecond(), 0.);
    EXPECT_EQ(angularVelocity.z.AsRadiansPerSecond(), 0.);
}


TEST(FSAngularVelocityTest, StaticZero_Is_Zero) {
    EXPECT_EQ(FSAngularVelocity::Zero.x.AsRadiansPerSecond(), 0.);
    EXPECT_EQ(FSAngularVelocity::Zero.y.AsRadiansPerSecond(), 0.);
    EXPECT_EQ(FSAngularVelocity::Zero.z.AsRadiansPerSecond(), 0.);
}

