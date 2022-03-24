// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"

#include "MaxQTestDefinitions.h"

TEST(normalizeZeroToTwoPiTest, Zero_Is_Zero) {
    double input = _pos0_as_radians;
    double output = USpiceTypes::normalizeZeroToTwoPi(input);

    EXPECT_DOUBLE_EQ(output, _pos0_as_radians);
}


TEST(normalizeZeroToTwoPiTest, pos90_Is_pos90) {
    double input = _pos90_as_radians;
    double output = USpiceTypes::normalizeZeroToTwoPi(input);

    EXPECT_DOUBLE_EQ(output, _pos90_as_radians);
}

TEST(normalizeZeroToTwoPiTest, neg90_Is_pos270) {
    double input = _neg90_as_radians;
    double output = USpiceTypes::normalizeZeroToTwoPi(input);

    EXPECT_DOUBLE_EQ(output, _pos270_as_radians);
}


TEST(normalizeZeroToTwoPiTest, pos180_Is_pos180) {
    double input = _pos180_as_radians;
    double output = USpiceTypes::normalizeZeroToTwoPi(input);

    EXPECT_DOUBLE_EQ(output, _pos180_as_radians);
}

TEST(normalizeZeroToTwoPiTest, neg180_Is_pos180) {
    double input = _neg180_as_radians;
    double output = USpiceTypes::normalizeZeroToTwoPi(input);

    EXPECT_DOUBLE_EQ(output, _pos180_as_radians);
}

TEST(normalizeZeroToTwoPiTest, pos270_Is_pos270) {
    double input = _pos270_as_radians;
    double output = USpiceTypes::normalizeZeroToTwoPi(input);

    EXPECT_DOUBLE_EQ(output, _pos270_as_radians);
}

TEST(normalizeZeroToTwoPiTest, neg270_Is_pos90) {
    double input = _neg270_as_radians;
    double output = USpiceTypes::normalizeZeroToTwoPi(input);

    EXPECT_DOUBLE_EQ(output, _pos90_as_radians);
}


TEST(normalizeZeroToTwoPiTest, pos360_Is_Zero) {
    double input = _pos360_as_radians;
    double output = USpiceTypes::normalizeZeroToTwoPi(input);

    EXPECT_DOUBLE_EQ(output, _pos0_as_radians);
}

TEST(normalizeZeroToTwoPiTest, neg360_Is_Zero) {
    double input = _neg360_as_radians;
    double output = USpiceTypes::normalizeZeroToTwoPi(input);

    EXPECT_DOUBLE_EQ(output, _pos0_as_radians);
}

TEST(normalizeZeroToTwoPiTest, pos540_Is_180) {
    double input = _pos540_as_radians;
    double output = USpiceTypes::normalizeZeroToTwoPi(input);

    EXPECT_DOUBLE_EQ(output, _pos180_as_radians);
}

TEST(normalizeZeroToTwoPiTest, neg540_Is_180) {
    double input = _neg540_as_radians;
    double output = USpiceTypes::normalizeZeroToTwoPi(input);

    EXPECT_DOUBLE_EQ(output, _pos180_as_radians);
}