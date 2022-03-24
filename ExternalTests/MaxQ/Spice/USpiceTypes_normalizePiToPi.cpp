// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"

#include "MaxQTestDefinitions.h"

#define PI_MACRO 3.1415926535897932384626433832795028841971693993751058209749445923078164

const double pi = (double)PI_MACRO;
const double _pos0_as_radians = (double)(+0. * PI_MACRO);
const double _pos90_as_radians = (double)(+0.5 * PI_MACRO);
const double _pos180_as_radians = (double)(+1. * PI_MACRO);
const double _pos270_as_radians = (double)(+1.5 * PI_MACRO);
const double _pos360_as_radians = (double)(+2. * PI_MACRO);
const double _pos540_as_radians = (double)(+3. * PI_MACRO);
const double _neg0_as_radians = (double)(-0. * PI_MACRO);
const double _neg90_as_radians = (double)(-0.5 * PI_MACRO);
const double _neg180_as_radians = (double)(-1. * PI_MACRO);
const double _neg270_as_radians = (double)(-1.5 * PI_MACRO);
const double _neg360_as_radians = (double)(-2. * PI_MACRO);
const double _neg540_as_radians = (double)(-3 * PI_MACRO);


TEST(piTest, halfpi_Is_halfpi) {
    double _halfpi;

    USpice::halfpi(_halfpi);

    EXPECT_DOUBLE_EQ(_halfpi, _pos90_as_radians);
}

TEST(piTest, pi_Is_pi) {
    double _pi;
    
    USpice::pi(_pi);

    EXPECT_DOUBLE_EQ(_pi, _pos180_as_radians);
}

TEST(piTest, twopi_Is_twopi) {
    double _twopi;

    USpice::twopi(_twopi);

    EXPECT_DOUBLE_EQ(_twopi, _pos360_as_radians);
}

// ---


TEST(normalizePiToPiTest, Zero_Is_Zero) {
    double input = _pos0_as_radians;
    double output = USpiceTypes::normalizePiToPi(input);

    EXPECT_DOUBLE_EQ(output, _pos0_as_radians);
}


TEST(normalizePiToPiTest, pos90_Is_pos90) {
    double input = _pos90_as_radians;
    double output = USpiceTypes::normalizePiToPi(input);

    EXPECT_DOUBLE_EQ(output, _pos90_as_radians);
}

TEST(normalizePiToPiTest, neg90_Is_neg90) {
    double input = _neg90_as_radians;
    double output = USpiceTypes::normalizePiToPi(input);

    EXPECT_DOUBLE_EQ(output, _neg90_as_radians);
}


TEST(normalizePiToPiTest, pos180_Is_pos180) {
    double input = _pos180_as_radians;
    double output = USpiceTypes::normalizePiToPi(input);

    EXPECT_DOUBLE_EQ(output, _pos180_as_radians);
}

TEST(normalizePiToPiTest, neg180_Is_pos180) {
    double input = _neg180_as_radians;
    double output = USpiceTypes::normalizePiToPi(input);

    EXPECT_DOUBLE_EQ(output, _pos180_as_radians);
}

TEST(normalizePiToPiTest, pos270_Is_neg90) {
    double input = _pos270_as_radians;
    double output = USpiceTypes::normalizePiToPi(input);

    EXPECT_DOUBLE_EQ(output, _neg90_as_radians);
}

TEST(normalizePiToPiTest, neg270_Is_pos90) {
    double input = _neg270_as_radians;
    double output = USpiceTypes::normalizePiToPi(input);

    EXPECT_DOUBLE_EQ(output, _pos90_as_radians);
}


TEST(normalizePiToPiTest, pos360_Is_Zero) {
    double input = _pos360_as_radians;
    double output = USpiceTypes::normalizePiToPi(input);

    EXPECT_DOUBLE_EQ(output, _pos0_as_radians);
}

TEST(normalizePiToPiTest, neg360_Is_Zero) {
    double input = _neg360_as_radians;
    double output = USpiceTypes::normalizePiToPi(input);

    EXPECT_DOUBLE_EQ(output, _pos0_as_radians);
}

TEST(normalizePiToPiTest, pos540_Is_180) {
    double input = _pos540_as_radians;
    double output = USpiceTypes::normalizePiToPi(input);

    EXPECT_DOUBLE_EQ(output, _pos180_as_radians);
}

TEST(normalizePiToPiTest, neg540_Is_180) {
    double input = _neg540_as_radians;
    double output = USpiceTypes::normalizePiToPi(input);

    EXPECT_DOUBLE_EQ(output, _pos180_as_radians);
}