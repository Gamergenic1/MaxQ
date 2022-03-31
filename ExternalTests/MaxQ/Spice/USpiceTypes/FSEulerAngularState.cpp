// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSEulerAngularState, DefaultConstruction_IsInitialized) {
    FSEulerAngularState eulerAngularState;

    EXPECT_DOUBLE_EQ(eulerAngularState.angle1.degrees, 0.);
    EXPECT_DOUBLE_EQ(eulerAngularState.angle2.degrees, 0.);
    EXPECT_DOUBLE_EQ(eulerAngularState.angle3.degrees, 0.);
    EXPECT_DOUBLE_EQ(eulerAngularState.rate1.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(eulerAngularState.rate2.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(eulerAngularState.rate3.radiansPerSecond, 0.);
    EXPECT_EQ(eulerAngularState.axis1, ES_Axis::Z);
    EXPECT_EQ(eulerAngularState.axis2, ES_Axis::Y);
    EXPECT_EQ(eulerAngularState.axis3, ES_Axis::X);
}

