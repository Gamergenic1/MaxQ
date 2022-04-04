// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"

#include "MaxQTestDefinitions.h"

TEST(Conv_SDimensionlessVectorToVectorTest, OneTwoThree_Is_TwoOneThree) {
    FSDimensionlessVector RHS_SpiceDimensionlessVector(1.1, 2.1, -3.1);

    FVector LHS_UEDimensionlessVector = USpiceTypes::Conv_SDimensionlessToVector(RHS_SpiceDimensionlessVector);

    EXPECT_EQ(LHS_UEDimensionlessVector.X, 2.1f);
    EXPECT_EQ(LHS_UEDimensionlessVector.Y, 1.1f);
    EXPECT_EQ(LHS_UEDimensionlessVector.Z, -3.1f);
}