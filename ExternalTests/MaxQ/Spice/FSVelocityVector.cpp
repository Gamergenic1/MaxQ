// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSVelocityVectorTest, DefaultConstruction_IsInitialized) {
    FSVelocityVector velocityVector;

    EXPECT_DOUBLE_EQ(velocityVector.dx.kmps, 0.);
    EXPECT_DOUBLE_EQ(velocityVector.dy.kmps, 0.);
    EXPECT_DOUBLE_EQ(velocityVector.dz.kmps, 0.);
}

