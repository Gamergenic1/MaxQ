// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"

#include "MaxQTestDefinitions.h"

TEST(Conv_VectorToSDimensionlessVectorTest, OneTwoThree_Is_TwoOneThree) {
    FVector LHS_UEDimensionlessVector(1.1f, -2.1f, 3.1f);

    FSDimensionlessVector RHS_SpiceDimensionlessVector = USpiceTypes::Conv_VectorToSDimensionless(LHS_UEDimensionlessVector);

    EXPECT_NEAR(RHS_SpiceDimensionlessVector.x, -2.1, 0.0000001);
    EXPECT_NEAR(RHS_SpiceDimensionlessVector.y, 1.1, 0.0000001);
    EXPECT_NEAR(RHS_SpiceDimensionlessVector.z, 3.1, 0.0000001);
}