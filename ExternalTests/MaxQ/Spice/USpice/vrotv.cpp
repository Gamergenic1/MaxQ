// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"
#include "MaxQTestDefinitions.h"

// See:
// https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/vrotv_c.html


TEST(VrotvTest, RotatePositive90degZ_Is_Rotated) {

    const FSDimensionlessVector Vector(1, 0, 0);
    const FSAngle Angle(_pos90_as_radians);
    const FSDimensionlessVector Axis(0,0,1);
    FSDimensionlessVector RotatedVector;

    // Expected result is the vector rotated +90 around +Z (0,1,0)
    USpice::vrotv(Vector, Axis, Angle, RotatedVector);

    EXPECT_TRUE(IsNear(RotatedVector, FSDimensionlessVector(0, +1, 0)));
}