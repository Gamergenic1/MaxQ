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

TEST(FSEulerAnglesTest, DefaultConstruction_IsInitialized) {
    FSEulerAngles eulerAngles;

    EXPECT_EQ(eulerAngles.angle1.degrees, 0.);
    EXPECT_EQ(eulerAngles.angle2.degrees, 0.);
    EXPECT_EQ(eulerAngles.angle3.degrees, 0.);
    EXPECT_EQ(eulerAngles.axis1, ES_Axis::Z);
    EXPECT_EQ(eulerAngles.axis2, ES_Axis::Y);
    EXPECT_EQ(eulerAngles.axis3, ES_Axis::X);
}

