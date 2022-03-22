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

TEST(FSRotationMatrixTest, DefaultConstruction_IsInitialized) {
    FSRotationMatrix rotationMatrix;

    EXPECT_EQ(rotationMatrix.m.Num(), 3);
    for (int i = 0; i < rotationMatrix.m.Num(); ++i)
    {
        EXPECT_EQ(rotationMatrix.m[i].x, i == 0 ? 1. : 0.);
        EXPECT_EQ(rotationMatrix.m[i].y, i == 1 ? 1. : 0.);
        EXPECT_EQ(rotationMatrix.m[i].z, i == 2 ? 1. : 0.);
    }
}

