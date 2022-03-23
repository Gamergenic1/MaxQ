// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 


#include "pch.h"


TEST(xf2rav_test, DefaultsTestCase) {

    FSStateTransform StateTransform;
    FSAngularVelocity av;
    FSRotationMatrix rotationMatrix;

    USpice::xf2rav(StateTransform, rotationMatrix, av);

    EXPECT_EQ(rotationMatrix.m.Num(), 3);
    for (int i = 0; i < rotationMatrix.m.Num(); ++i)
    {
        EXPECT_DOUBLE_EQ(rotationMatrix.m[i].x, i == 0 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(rotationMatrix.m[i].y, i == 1 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(rotationMatrix.m[i].z, i == 2 ? 1. : 0.);
    }

    EXPECT_DOUBLE_EQ(av.x.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(av.y.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(av.z.radiansPerSecond, 0.);
}



TEST(xf2rav_test, ZRotation_Is_Correct) {

    FSStateTransform StateTransform;
    
    StateTransform.m.Init(FSDimensionlessStateVector(FSDimensionlessVector::Zero, FSDimensionlessVector::Zero), 6);

    StateTransform.m[0].r = FSDimensionlessVector(0, -1, 0);
    StateTransform.m[1].r = FSDimensionlessVector(1,  0, 0);
    StateTransform.m[2].r = FSDimensionlessVector(0,  0, 1);

    StateTransform.m[0].dr = FSDimensionlessVector(1, 0, 0);
    StateTransform.m[1].dr = FSDimensionlessVector(0, 1, 0);
    StateTransform.m[2].dr = FSDimensionlessVector(0, 0, 0);

    StateTransform.m[3].r = FSDimensionlessVector(1, 0, 0);
    StateTransform.m[4].r = FSDimensionlessVector(0, 1, 0);
    StateTransform.m[5].r = FSDimensionlessVector(0, 0, 0);

    StateTransform.m[3].dr = FSDimensionlessVector(0, -1, 0);
    StateTransform.m[4].dr = FSDimensionlessVector(1,  0, 0);
    StateTransform.m[5].dr = FSDimensionlessVector(0,  0, -1);

    FSAngularVelocity av;
    FSRotationMatrix rotationMatrix;

    USpice::xf2rav(StateTransform, rotationMatrix, av);

    EXPECT_EQ(rotationMatrix.m.Num(), 3);
    if (rotationMatrix.m.Num() >= 3)
    {
        EXPECT_DOUBLE_EQ(rotationMatrix.m[0].x, 0.);
        EXPECT_DOUBLE_EQ(rotationMatrix.m[0].y, -1.);
        EXPECT_DOUBLE_EQ(rotationMatrix.m[0].z, 0.);

        EXPECT_DOUBLE_EQ(rotationMatrix.m[1].x, 1.);
        EXPECT_DOUBLE_EQ(rotationMatrix.m[1].y, 0.);
        EXPECT_DOUBLE_EQ(rotationMatrix.m[1].z, 0.);

        EXPECT_DOUBLE_EQ(rotationMatrix.m[2].x, 0.);
        EXPECT_DOUBLE_EQ(rotationMatrix.m[2].y, 0.);
        EXPECT_DOUBLE_EQ(rotationMatrix.m[2].z, 1.);
    }
    
    EXPECT_DOUBLE_EQ(av.x.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(av.y.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(av.z.radiansPerSecond, 1.);
}