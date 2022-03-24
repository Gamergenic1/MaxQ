// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"

#include "MaxQTestDefinitions.h"


TEST(FSAngleTest, DefaultConstruction_Is_Initialized) {
    FSAngle angle;

    EXPECT_DOUBLE_EQ(angle.degrees, 0.);
}

TEST(FSAngleTest, StaticZero_Is_Zero) {

    EXPECT_DOUBLE_EQ(FSAngle::_0.degrees, 0.);
}

TEST(FSAngleTest, Static360_Is_360) {

    EXPECT_DOUBLE_EQ(FSAngle::_360.degrees, 360);
}

TEST(FSAngleTest, SpiceDoubleConstruction_Is_Initialized) {

    FSAngle angle(pi);

    EXPECT_DOUBLE_EQ(angle.degrees, 180.);
}


TEST(FSAngleTest, OneRadian_Is_RadiansOne) {

    FSAngle angle(1.5);

    EXPECT_DOUBLE_EQ(angle.radians(), 1.5);
}

TEST(FSAngleTest, OneRadianAsSpiceDouble_Is_One) {

    FSAngle angle(1.5);

    EXPECT_DOUBLE_EQ(angle.AsSpiceDouble(), 1.5);
}

TEST(FSAngleTest, OneRadianAsRadians_Is_One) {

    FSAngle angle(1.5);

    EXPECT_DOUBLE_EQ(angle.AsRadians(), 1.5);
}


TEST(FSAngleTest, _180DegreesAsDegrees_Is_180) {

    FSAngle angle(pi);

    EXPECT_DOUBLE_EQ(angle.AsDegrees(), 180.);
}

TEST(FSAngleTest, OneRadianEqualsOneRadian_Is_True) {

    FSAngle one1(1.5);
    FSAngle one2(1.5);

    bool equals = (one1 == one2);

    EXPECT_EQ(equals, true);
}

TEST(FSAngleTest, OneRadianEqualsTwoRadians_Is_False) {

    FSAngle one(1.5);
    FSAngle two(2.5);

    bool equals = (one == two);

    EXPECT_EQ(equals, false);
}

TEST(FSAngleTest, OneRadianNotEqualsOneRadian_Is_False) {

    FSAngle one1(1.5);
    FSAngle one2(1.5);

    bool equals = (one1 != one2);

    EXPECT_EQ(equals, false);
}

TEST(FSAngleTest, OneRadianNotEqualsTwoRadians_Is_True) {

    FSAngle one(1.5);
    FSAngle two(2.5);

    bool equals = (one != two);

    EXPECT_EQ(equals, true);
}

TEST(FSAngleTest, _2Times90deg_Is_180deg) {

    double _2 = 2.;
    FSAngle _90(_pos90_as_radians);

    FSAngle _180 = _2 * _90;

    EXPECT_EQ(_180.degrees, 180);
}

TEST(FSAngleTest, _90degTimes2_Is_180deg) {

    FSAngle _90(_pos90_as_radians);
    double _2 = 2.;

    FSAngle _180 = _90 * _2;

    EXPECT_EQ(_180.degrees, 180);
}

TEST(FSAngleTest, OnePlusTwo_Is_Three) {

    FSAngle one(_pos1_as_radians);
    FSAngle two(_pos2_as_radians);

    FSAngle three = one + two;

    EXPECT_NEAR(three.degrees, 3., 0.0000000001);
}


TEST(FSAngleTest, ThreeMinusTwo_Is_One) {

    FSAngle three(_pos3_as_radians);
    FSAngle two(_pos2_as_radians);

    FSAngle one = three - two;


    EXPECT_NEAR(one.degrees, 1., 0.0000000001);
}

TEST(FSAngleTest, ThreeDegreesDividedByTwo_Is_OnePointFiveDegrees) {

    FSAngle three(_pos3_as_radians);
    double two = 2.;

    FSAngle onePointFive = three / two;

    EXPECT_NEAR(onePointFive.degrees, 1.5, 0.0000000001);
}

TEST(FSAngleTest, ThreeDegreesDividedByThreeDegrees_Is_OnePointFive) {

    FSAngle three(_pos3_as_radians);
    FSAngle two(_pos2_as_radians);

    double onePointFive = three / two;

    EXPECT_NEAR(onePointFive, 1.5, 0.0000000001);
}


TEST(FSAngleTest, OnePlusEqualsTwo_Is_Three) {

    FSAngle one(_pos1_as_radians);
    FSAngle two(_pos2_as_radians);

    one += two;

    EXPECT_NEAR(one.degrees, 3., 0.0000000001);
}


TEST(FSAngleTest, ThreeMinusEqualsTwo_Is_One) {

    FSAngle three(_pos3_as_radians);
    FSAngle two(_pos2_as_radians);

    three -= two;


    EXPECT_NEAR(three.degrees, 1., 0.0000000001);
}