// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"

#include "MaxQTestDefinitions.h"

TEST(Conv_SAngularVelocityToVectorTest, OneTwoThree_Is_NegativeTwoOneThree) {
    FSAngularVelocity RHS_SpiceAngularVelocity(-1.1, 2.1, 3.1);

    FVector LHS_UEAngularVelocityVector = USpiceTypes::Conv_SAngularVelocityToVector(RHS_SpiceAngularVelocity);

    // Angular velocity is negated due to the LHS-to-RHS switch
    EXPECT_EQ(LHS_UEAngularVelocityVector.X, -2.1f);
    EXPECT_EQ(LHS_UEAngularVelocityVector.Y, +1.1f);
    EXPECT_EQ(LHS_UEAngularVelocityVector.Z, -3.1f);
}