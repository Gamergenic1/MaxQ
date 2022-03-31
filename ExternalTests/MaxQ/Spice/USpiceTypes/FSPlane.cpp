// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSPlaneTest, DefaultConstruction_IsInitialized) {
    FSPlane plane;

    EXPECT_DOUBLE_EQ(plane.normal.x, 0.);
    EXPECT_DOUBLE_EQ(plane.normal.y, 0.);
    EXPECT_DOUBLE_EQ(plane.normal.z, 0.);
    EXPECT_DOUBLE_EQ(plane.constant.km, 0.);
}

