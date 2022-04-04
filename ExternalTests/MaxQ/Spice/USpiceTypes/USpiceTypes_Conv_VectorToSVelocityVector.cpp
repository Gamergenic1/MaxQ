// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"

#include "MaxQTestDefinitions.h"

TEST(Conv_VectorToSVelocityVectorTest, OneTwoThree_Is_TwoOneThree) {
    FVector LHS_UEScenegraphVelocityInKmPS(1.1f, -2.1f, 3.1f);
    
    FSVelocityVector RHS_SpiceVelocity = USpiceTypes::Conv_VectorToSVelocityVector(LHS_UEScenegraphVelocityInKmPS);

    EXPECT_NEAR(RHS_SpiceVelocity.dx.AsKilometersPerSecond(), -2.1, 0.0000001);
    EXPECT_NEAR(RHS_SpiceVelocity.dy.AsKilometersPerSecond(), 1.1, 0.0000001);
    EXPECT_NEAR(RHS_SpiceVelocity.dz.AsKilometersPerSecond(), 3.1, 0.0000001);
}