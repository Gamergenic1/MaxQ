// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"

#include "MaxQTestDefinitions.h"

TEST(Conv_QuatToSQuaternionTest, NinetyAroundX_Is_Valid) {
    FQuat LHS_UEQuat(FVector(1.f, 0.f, 0.f), (float)_pos90_as_radians);

    FSQuaternion RHS_SQuaternion = USpiceTypes::Conv_QuatToSQuaternion(LHS_UEQuat);

    // The +x UE axis is the +y axis in SPICE
    FSDimensionlessVector RHS_RotationAxis(0, 1., 0);
    // Going from a LHS rotation angle to RHS rotation angle means negation
    FSAngle RHS_Angle = FSAngle::FromRadians(-_pos90_as_radians);
    
    // axisar rotates a vector around and axis... not the coordinate system around the vector.
    // Which, is the "sense" of the quaternion UE gave us.
    FSRotationMatrix ExpectedRotation;
    USpice::axisar(RHS_RotationAxis, RHS_Angle, ExpectedRotation);


    FSQuaternion Expected_RHS_SQuaternion;
    ES_ResultCode ResultCode;
    FString ErrorMessage;
    USpice::m2q(ResultCode, ErrorMessage, ExpectedRotation, Expected_RHS_SQuaternion);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);

    EXPECT_NEAR(RHS_SQuaternion.w, Expected_RHS_SQuaternion.w, 0.0000001);
    EXPECT_NEAR(RHS_SQuaternion.x, Expected_RHS_SQuaternion.x, 0.0000001);
    EXPECT_NEAR(RHS_SQuaternion.y, Expected_RHS_SQuaternion.y, 0.0000001);
    EXPECT_NEAR(RHS_SQuaternion.z, Expected_RHS_SQuaternion.z, 0.0000001);
}

TEST(Conv_QuatToSQuaternionTest, NinetyAroundXWithVector_Is_Valid) {
    FVector LHS_UP = FVector(0, 0, 1);
    FQuat LHS_UEQuat(FVector(1.f, 0.f, 0.f), (float)_pos90_as_radians);
    FVector LHS_UP_Rotated = LHS_UEQuat * LHS_UP;

    FSQuaternion RHS_SQuaternion = USpiceTypes::Conv_QuatToSQuaternion(LHS_UEQuat);

    // The +x UE axis is the +y axis in SPICE
    FSDimensionlessVector RHS_RotationAxis(0, 1., 0);
    // Going from a LHS rotation angle to RHS rotation angle means negation
    FSAngle RHS_Angle = FSAngle::FromRadians(-_pos90_as_radians);

    // axisar rotates a vector around and axis... not the coordinate system around the vector.
    // Which, is the "sense" of the quaternion UE gave us.
    FSRotationMatrix ExpectedRotation;
    USpice::axisar(RHS_RotationAxis, RHS_Angle, ExpectedRotation);


    FSQuaternion Expected_RHS_SQuaternion;
    ES_ResultCode ResultCode;
    FString ErrorMessage;
    USpice::m2q(ResultCode, ErrorMessage, ExpectedRotation, Expected_RHS_SQuaternion);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);

    EXPECT_NEAR(RHS_SQuaternion.w, Expected_RHS_SQuaternion.w, 0.0000001);
    EXPECT_NEAR(RHS_SQuaternion.x, Expected_RHS_SQuaternion.x, 0.0000001);
    EXPECT_NEAR(RHS_SQuaternion.y, Expected_RHS_SQuaternion.y, 0.0000001);
    EXPECT_NEAR(RHS_SQuaternion.z, Expected_RHS_SQuaternion.z, 0.0000001);

    FSDimensionlessVector RHS_Up(0, 0, 1);
    FSDimensionlessVector RHS_Up_Rotated;
    USpice::mxv(ExpectedRotation, RHS_Up, RHS_Up_Rotated);

    // LHS
    // (0,0,1) rotated 90 around X should be (0,-1,0)....
    // RHS
    // (0,0,1) rotated -90 around Y should be (-1,0,0)....

    EXPECT_NEAR(RHS_Up_Rotated.x, LHS_UP_Rotated.Y, 0.000001);
}