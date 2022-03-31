// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(normalize0to360Test, Zero_Is_Zero) {
    double input = 0.;
    double output = USpiceTypes::normalize0to360(input);

    EXPECT_DOUBLE_EQ(output, 0.);
}


TEST(normalize0to360Test, pos90_Is_pos90) {
    double input = 90.;
    double output = USpiceTypes::normalize0to360(input);

    EXPECT_DOUBLE_EQ(output, 90.);
}

TEST(normalize0to360Test, neg90_Is_pos270) {
    double input = -90.;
    double output = USpiceTypes::normalize0to360(input);

    EXPECT_DOUBLE_EQ(output, 270.);
}


TEST(normalize0to360Test, pos180_Is_pos180) {
    double input = 180.;
    double output = USpiceTypes::normalize0to360(input);

    EXPECT_DOUBLE_EQ(output, 180.);
}

TEST(normalize0to360Test, neg180_Is_pos180) {
    double input = -180.;
    double output = USpiceTypes::normalize0to360(input);

    EXPECT_DOUBLE_EQ(output, 180.);
}

TEST(normalize0to360Test, pos270_Is_pos270) {
    double input = 270.;
    double output = USpiceTypes::normalize0to360(input);

    EXPECT_DOUBLE_EQ(output, 270.);
}

TEST(normalize0to360Test, neg270_Is_pos90) {
    double input = -270.;
    double output = USpiceTypes::normalize0to360(input);

    EXPECT_DOUBLE_EQ(output, 90.);
}


TEST(normalize0to360Test, pos360_Is_Zero) {
    double input = 360.;
    double output = USpiceTypes::normalize0to360(input);

    EXPECT_DOUBLE_EQ(output, 0.);
}

TEST(normalize0to360Test, neg360_Is_Zero) {
    double input = -360.;
    double output = USpiceTypes::normalize0to360(input);

    EXPECT_DOUBLE_EQ(output, 0.);
}

TEST(normalize0to360Test, pos540_Is_180) {
    double input = 540.;
    double output = USpiceTypes::normalize0to360(input);

    EXPECT_DOUBLE_EQ(output, 180.);
}

TEST(normalize0to360Test, neg540_Is_180) {
    double input = -540.;
    double output = USpiceTypes::normalize0to360(input);

    EXPECT_DOUBLE_EQ(output, 180.);
}