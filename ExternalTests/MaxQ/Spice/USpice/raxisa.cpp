// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"
#include "MaxQTestDefinitions.h"

// See:
// https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/raxisa_c.html

TEST(RaxisaTest, RotatePositive90degZ_Is_Rotated) {

    // +90 degree rotation around +Z.
    const FSRotationMatrix RotationMatrix(
        FSDimensionlessVector( 0, -1,  0),
        FSDimensionlessVector(+1,  0,  0),
        FSDimensionlessVector( 0,  0,  1)
        );
    FSDimensionlessVector Axis(0, 0, 1);
    FSAngle Angle(_pos90_as_radians);

    // Expected result is a rotation matrix... E.g.,
    // A matrix that rotates vectors within a coordinate system
    ES_ResultCode ResultCode;
    FString ErrorMessage;
    USpice::raxisa(ResultCode, ErrorMessage, RotationMatrix, Axis, Angle);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);
    if (Angle.degrees >= 0)
    {
        EXPECT_NEAR(Angle.degrees, 90, 0.00001);
        EXPECT_TRUE(IsNear(Axis, FSDimensionlessVector(0, 0, +1)));
    }
    else
    {
        EXPECT_NEAR(Angle.degrees, -90, 0.00001);
        EXPECT_TRUE(IsNear(Axis, FSDimensionlessVector(0, 0, -1)));
    }
}


TEST(RaxisaTest, Identity_Is_NotRotated) {

    // +90 degree rotation around +Z.
    const FSRotationMatrix RotationMatrix(
        FSDimensionlessVector(1, 0, 0),
        FSDimensionlessVector(0, 1, 0),
        FSDimensionlessVector(0, 0, 1)
    );
    FSDimensionlessVector Axis(0, 0, 1);
    FSAngle Angle(_pos90_as_radians);

    // Expected result is a rotation matrix... E.g.,
    // A matrix that rotates vectors within a coordinate system
    ES_ResultCode ResultCode;
    FString ErrorMessage;
    USpice::raxisa(ResultCode, ErrorMessage, RotationMatrix, Axis, Angle);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);
    EXPECT_EQ(Angle.degrees, 0);
}


TEST(RaxisaTest, Zero_Is_Error) {

    // +90 degree rotation around +Z.
    const FSRotationMatrix RotationMatrix(
        FSDimensionlessVector(0, 0, 0),
        FSDimensionlessVector(0, 0, 0),
        FSDimensionlessVector(0, 0, 0)
    );
    FSDimensionlessVector Axis(0, 0, 1);
    FSAngle Angle(_pos90_as_radians);

    // Expected result is a rotation matrix... E.g.,
    // A matrix that rotates vectors within a coordinate system
    ES_ResultCode ResultCode;
    FString ErrorMessage;
    USpice::raxisa(ResultCode, ErrorMessage, RotationMatrix, Axis, Angle);

    EXPECT_NE(ResultCode, ES_ResultCode::Success);
    EXPECT_GT(ErrorMessage.Len(), 0);
}