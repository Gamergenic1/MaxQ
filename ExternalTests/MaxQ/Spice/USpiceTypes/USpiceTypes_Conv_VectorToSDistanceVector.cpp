// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"

#include "MaxQTestDefinitions.h"

TEST(Conv_VectorToSDistanceVectorTest, OneTwoThree_Is_TwoOneThree) {
    FVector LHS_UEScenegraphDistanceKilometers(1.1f, -2.1f, 3.1f);

    FSDistanceVector RHS_SpiceDistance = USpiceTypes::Conv_VectorToSDistanceVector(LHS_UEScenegraphDistanceKilometers);

    // No units conversion is attempted here, the client code is responsible for scaling.
    EXPECT_NEAR(RHS_SpiceDistance.x.AsKilometers(), -2.1, 0.0000001);
    EXPECT_NEAR(RHS_SpiceDistance.y.AsKilometers(), 1.1, 0.0000001);
    EXPECT_NEAR(RHS_SpiceDistance.z.AsKilometers(), 3.1, 0.0000001);
}