// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"

#include "MaxQTestDefinitions.h"

TEST(Conv_SVelocityVectorToVectorTest, OneTwoThree_Is_TwoOneThree) {
    FSVelocityVector RHS_SpiceVelocityVector(1.1, 2.1, -3.1);

    FVector LHS_UEScenegraphVelocityVector = USpiceTypes::Conv_SVelocityVectorToVector(RHS_SpiceVelocityVector);
    
    EXPECT_EQ(LHS_UEScenegraphVelocityVector.X, 2.1f);
    EXPECT_EQ(LHS_UEScenegraphVelocityVector.Y, 1.1f);
    EXPECT_EQ(LHS_UEScenegraphVelocityVector.Z, -3.1f);
}