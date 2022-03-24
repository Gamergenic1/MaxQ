// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSRotationMatrixTest, DefaultConstruction_Is_Initialized) {
    FSRotationMatrix rotationMatrix;

    EXPECT_EQ(rotationMatrix.m.Num(), 3);
    for (int i = 0; i < rotationMatrix.m.Num(); ++i)
    {
        EXPECT_DOUBLE_EQ(rotationMatrix.m[i].x, i == 0 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(rotationMatrix.m[i].y, i == 1 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(rotationMatrix.m[i].z, i == 2 ? 1. : 0.);
    }
}


TEST(FSRotationMatrixTest, Identity_Is_Initialized) {

    EXPECT_EQ(FSRotationMatrix::Identity.m.Num(), 3);

    for (int i = 0; i < FSRotationMatrix::Identity.m.Num(); ++i)
    {
        EXPECT_DOUBLE_EQ(FSRotationMatrix::Identity.m[i].x, i == 0 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(FSRotationMatrix::Identity.m[i].y, i == 1 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(FSRotationMatrix::Identity.m[i].z, i == 2 ? 1. : 0.);
    }
}


TEST(FSRotationMatrixTest, SpiceDoubleConstruction_Is_Initialized) {
    
    double _m[3][3] = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9 };
    
    FSRotationMatrix rotationMatrix(_m);

    EXPECT_EQ(rotationMatrix.m.Num(), 3);

    for (int i = 0; i < rotationMatrix.m.Num(); ++i)
    {
        EXPECT_DOUBLE_EQ(rotationMatrix.m[i].x, i * 3.3 + 1.1);
        EXPECT_DOUBLE_EQ(rotationMatrix.m[i].y, i * 3.3 + 2.2);
        EXPECT_DOUBLE_EQ(rotationMatrix.m[i].z, i * 3.3 + 3.3);
    }
}

TEST(FSRotationMatrixTest, VectorConstruction_Is_Initialized) {

    FSDimensionlessVector v1(1.1, 2.2, 3.3);
    FSDimensionlessVector v2(4.4, 5.5, 6.6);
    FSDimensionlessVector v3(7.7, 8.8, 9.9);

    FSRotationMatrix rotationMatrix(v1, v2, v3);

    EXPECT_EQ(rotationMatrix.m.Num(), 3);

    for (int i = 0; i < rotationMatrix.m.Num(); ++i)
    {
        EXPECT_DOUBLE_EQ(rotationMatrix.m[i].x, i * 3.3 + 1.1);
        EXPECT_DOUBLE_EQ(rotationMatrix.m[i].y, i * 3.3 + 2.2);
        EXPECT_DOUBLE_EQ(rotationMatrix.m[i].z, i * 3.3 + 3.3);
    }
}


TEST(FSRotationMatrixTest, CopyTo_Sets_SpiceDoubles) {

    FSDimensionlessVector v1(1.1, 2.2, 3.3);
    FSDimensionlessVector v2(4.4, 5.5, 6.6);
    FSDimensionlessVector v3(7.7, 8.8, 9.9);

    FSRotationMatrix rotationMatrix(v1, v2, v3);

    double _m[3][3];
    rotationMatrix.CopyTo(_m);

    EXPECT_DOUBLE_EQ(_m[0][0], 1.1);
    EXPECT_DOUBLE_EQ(_m[0][1], 2.2);
    EXPECT_DOUBLE_EQ(_m[0][2], 3.3);
    EXPECT_DOUBLE_EQ(_m[1][0], 4.4);
    EXPECT_DOUBLE_EQ(_m[1][1], 5.5);
    EXPECT_DOUBLE_EQ(_m[1][2], 6.6);
    EXPECT_DOUBLE_EQ(_m[2][0], 7.7);
    EXPECT_DOUBLE_EQ(_m[2][1], 8.8);
    EXPECT_DOUBLE_EQ(_m[2][2], 9.9);
}


TEST(FSRotationMatrixTest, Assignment_Is_Correct) {
    
    FSDimensionlessVector v1(1.1, 2.2, 3.3);
    FSDimensionlessVector v2(4.4, 5.5, 6.6);
    FSDimensionlessVector v3(7.7, 8.8, 9.9);

    FSRotationMatrix m1(v1, v2, v3);

    FSRotationMatrix m2;

    m2 = m1;

    EXPECT_EQ(m2.m.Num(), 3);

    for (int i = 0; i < m2.m.Num(); ++i)
    {
        EXPECT_DOUBLE_EQ(m2.m[i].x, i * 3.3 + 1.1);
        EXPECT_DOUBLE_EQ(m2.m[i].y, i * 3.3 + 2.2);
        EXPECT_DOUBLE_EQ(m2.m[i].z, i * 3.3 + 3.3);
    }
}


