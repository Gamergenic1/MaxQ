// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSDimensionlessVectorTest, DefaultConstruction_Is_Initialized) {
    FSDimensionlessVector dimensionlessVector;

    EXPECT_DOUBLE_EQ(dimensionlessVector.x, 0.);
    EXPECT_DOUBLE_EQ(dimensionlessVector.y, 0.);
    EXPECT_DOUBLE_EQ(dimensionlessVector.z, 0.);
}

TEST(FSDimensionlessVectorTest, Zero_Is_Zero) {
    FSDimensionlessVector dimensionlessVector;

    EXPECT_DOUBLE_EQ(FSDimensionlessVector::Zero.x, 0.);
    EXPECT_DOUBLE_EQ(FSDimensionlessVector::Zero.y, 0.);
    EXPECT_DOUBLE_EQ(FSDimensionlessVector::Zero.z, 0.);
}


TEST(FSDimensionlessVectorTest, Assignment_Is_Correct) {
    FSDimensionlessVector dimensionlessVector1 = FSDimensionlessVector(1.5, -2.4, 3.3);
    FSDimensionlessVector dimensionlessVector2 = dimensionlessVector1;

    EXPECT_DOUBLE_EQ(dimensionlessVector2.x, 1.5);
    EXPECT_DOUBLE_EQ(dimensionlessVector2.y, -2.4);
    EXPECT_DOUBLE_EQ(dimensionlessVector2.z, 3.3);
}


TEST(FSDimensionlessVectorTest, CopyConstructor_Is_Correct) {
    FSDimensionlessVector dimensionlessVector = FSDimensionlessVector(1.5, -2.4, 3.3);

    EXPECT_DOUBLE_EQ(dimensionlessVector.x, 1.5);
    EXPECT_DOUBLE_EQ(dimensionlessVector.y, -2.4);
    EXPECT_DOUBLE_EQ(dimensionlessVector.z, 3.3);
}
