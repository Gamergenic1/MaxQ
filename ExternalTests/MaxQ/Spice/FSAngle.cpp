// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

class UScriptStruct;

#include "UE5HostDefs.h"
#include "SpiceHostDefs.h"

#include "Spice.h"

#include "gtest/gtest.h"

TEST(FSAngleTest, DefaultConstruction_Is_Initialized) {
    FSAngle angle;

    EXPECT_EQ(angle.degrees, 0.);
}

TEST(FSAngleTest, StaticZero_Is_Zero) {

    EXPECT_EQ(FSAngle::_0.degrees, 0.);
}
