// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"

#include "MaxQTestDefinitions.h"

TEST(Conv_VectorToSAngularVelocityTest, OneTwoThree_Is_NegativeTwoOneThree) {
    FVector LHS_UEAngularVelocityVector(1.1f, -2.1f, 3.1f);

    FSAngularVelocity RHS_SpiceAngularVelocity = USpiceTypes::Conv_VectorToSAngularVelocity(LHS_UEAngularVelocityVector);

    // Angular velocity is negated due to the LHS-to-RHS switch
    EXPECT_NEAR(RHS_SpiceAngularVelocity.x.AsRadiansPerSecond(), +2.1, 0.0000001);
    EXPECT_NEAR(RHS_SpiceAngularVelocity.y.AsRadiansPerSecond(), -1.1, 0.0000001);
    EXPECT_NEAR(RHS_SpiceAngularVelocity.z.AsRadiansPerSecond(), -3.1, 0.0000001);
}