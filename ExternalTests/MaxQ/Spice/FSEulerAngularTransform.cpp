// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSEulerAngularTransformTest, DefaultConstruction_IsInitialized) {
    FSEulerAngularTransform eulerAngularTransform;

    EXPECT_EQ(eulerAngularTransform.m.Num(), 6);
    
    for (int i = 0; i < eulerAngularTransform.m.Num(); ++i)
    {
        EXPECT_DOUBLE_EQ(eulerAngularTransform.m[i].r.x, i == 0 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(eulerAngularTransform.m[i].r.y, i == 1 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(eulerAngularTransform.m[i].r.z, i == 2 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(eulerAngularTransform.m[i].dr.x, i == 3 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(eulerAngularTransform.m[i].dr.y, i == 4 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(eulerAngularTransform.m[i].dr.z, i == 5 ? 1. : 0.);
    }
}

