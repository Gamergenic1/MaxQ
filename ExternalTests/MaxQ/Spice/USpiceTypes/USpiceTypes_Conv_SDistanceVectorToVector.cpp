// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"

#include "MaxQTestDefinitions.h"

TEST(Conv_SDistanceVectorToVectorTest, OneTwoThree_Is_TwoOneThree) {
    FSDistanceVector RHS_SpiceDistanceVector(1.1, 2.1, -3.1);

    FVector LHS_UEScenegraphDistanceVector = USpiceTypes::Conv_SDistanceVectorToVector(RHS_SpiceDistanceVector);

    EXPECT_EQ(LHS_UEScenegraphDistanceVector.X, 2.1f);
    EXPECT_EQ(LHS_UEScenegraphDistanceVector.Y, 1.1f);
    EXPECT_EQ(LHS_UEScenegraphDistanceVector.Z, -3.1f);
}