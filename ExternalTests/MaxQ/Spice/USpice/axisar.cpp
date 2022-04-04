// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"
#include "MaxQTestDefinitions.h"

// See:
// https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/axisar_c.html


TEST(AxisarTest, RotatePositive90degZ_Is_Rotated) {

    const FSDimensionlessVector Axis(0, 0, 1);
    const FSAngle Angle(_pos90_as_radians);
    FSRotationMatrix RotationMatrix;

    // Expected result is a rotation matrix... E.g.,
    // A matrix that rotates vectors within a coordinate system
    USpice::axisar(Axis, Angle, RotationMatrix);

    EXPECT_TRUE(IsNear(RotationMatrix.m[0], FSDimensionlessVector(0, -1, 0)));
    EXPECT_TRUE(IsNear(RotationMatrix.m[1], FSDimensionlessVector(+1, 0, 0)));
    EXPECT_TRUE(IsNear(RotationMatrix.m[2], FSDimensionlessVector(0, 0, 1)));

    // Just to demonstrate, we rotate the vector (1,0,0) and expect (0,+1,0)
    FSDimensionlessVector RotatedVector;
    USpice::mxv(RotationMatrix, FSDimensionlessVector(1, 0, 0), RotatedVector);

    // E.g., the vector was rotated the +90 degrees around Z.
    EXPECT_TRUE(IsNear(RotatedVector, FSDimensionlessVector(0, +1, 0)));
}