// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSAngleTest, DefaultConstruction_Is_Initialized) {
    FSAngle angle;

    EXPECT_DOUBLE_EQ(angle.degrees, 0.);
}

TEST(FSAngleTest, StaticZero_Is_Zero) {

    EXPECT_DOUBLE_EQ(FSAngle::_0.degrees, 0.);
}
