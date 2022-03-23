// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(mxv_distance_test, DefaultsTestCase) {

    FSRotationMatrix m;
    FSDistanceVector vin, vout;

    USpice::mxv_distance(m, vin, vout);

    EXPECT_DOUBLE_EQ(vout.x.km, 0.);
    EXPECT_DOUBLE_EQ(vout.y.km, 0.);
    EXPECT_DOUBLE_EQ(vout.z.km, 0.);
}