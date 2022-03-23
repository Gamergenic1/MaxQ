// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(USpiceTypesTest, normalize180to180_ZeroIsZero) {
    double input = 0.;
    double output = USpiceTypes::normalize180to180(input);

    EXPECT_DOUBLE_EQ(output, 0.);
}


TEST(USpiceTypesTest, normalize0to360_ZeroIsZero) {
    double input = 0.;
    double output = USpiceTypes::normalize0to360(input);

    EXPECT_DOUBLE_EQ(output, 0.);
}


TEST(USpiceTypesTest, normalizePiToPi_ZeroIsZero) {
    double input = 0.;
    double output = USpiceTypes::normalizePiToPi(input);

    EXPECT_DOUBLE_EQ(output, 0.);
}

TEST(USpiceTypesTest, normalizeZeroToTwoPi_ZeroIsZero) {
    double input = 0.;
    double output = USpiceTypes::normalizeZeroToTwoPi(input);

    EXPECT_DOUBLE_EQ(output, 0.);
}

