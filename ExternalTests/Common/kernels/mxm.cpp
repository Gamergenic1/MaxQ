// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(mxm_test, DefaultsTestCase) {

    FSRotationMatrix m1, m2, mout;

    USpice::mxm(m1, m2, mout);

    EXPECT_EQ(mout.m.Num(), 3);

    for (int i = 0; i < mout.m.Num(); ++i)
    {
        EXPECT_DOUBLE_EQ(mout.m[i].x, i == 0 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(mout.m[i].y, i == 1 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(mout.m[i].z, i == 2 ? 1. : 0.);

    }
}