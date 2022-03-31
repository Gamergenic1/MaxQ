// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(mxv_angular_test, DefaultsTestCase) {

    FSRotationMatrix m;
    FSAngularVelocity vin, vout;

    USpice::mxv_angular(m, vin, vout);

    EXPECT_DOUBLE_EQ(vout.x.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(vout.y.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(vout.z.radiansPerSecond, 0.);
}