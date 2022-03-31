// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSMassConstantTest, DefaultConstruction_Is_Initialized) {
    FSMassConstant massConstant;

    EXPECT_DOUBLE_EQ(massConstant.GM, 0.);
}

TEST(FSMassConstantTest, SpiceDoubleConstruction_Is_Initialized) {
    FSMassConstant massConstant(1.2345);

    EXPECT_DOUBLE_EQ(massConstant.GM, 1.2345);
}


TEST(FSMassConstantTest, AsSpiceDouble_Gets_Constant) {
    FSMassConstant massConstant(1.2345);

    EXPECT_DOUBLE_EQ(massConstant.AsSpiceDouble(), 1.2345);
}

TEST(FSMassConstantTest, AsKm3perSec2_Gets_Constant) {
    FSMassConstant massConstant(1.2345);

    EXPECT_DOUBLE_EQ(massConstant.AsKm3perSec2(), 1.2345);
}


TEST(FSMassConstantTest, NegativeOneIsPositive_Is_False) {
    FSMassConstant massConstant(-1.2345);

    bool positive = massConstant.IsPositive();

    EXPECT_EQ(positive, false);
}

TEST(FSMassConstantTest, ZeroOneIsPositive_Is_False) {
    FSMassConstant massConstant(0);

    bool positive = massConstant.IsPositive();

    EXPECT_EQ(positive, false);
}


TEST(FSMassConstantTest, OneIsPositive_Is_True) {
    FSMassConstant massConstant(1.2345);

    bool positive = massConstant.IsPositive();

    EXPECT_EQ(positive, true);
}
