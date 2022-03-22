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

TEST(FSVelocityVectorTest, DefaultConstruction_IsInitialized) {
    FSVelocityVector velocityVector;

    EXPECT_EQ(velocityVector.dx.kmps, 0.);
    EXPECT_EQ(velocityVector.dy.kmps, 0.);
    EXPECT_EQ(velocityVector.dz.kmps, 0.);
}

