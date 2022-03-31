// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"
#include "MaxQTestDefinitions.h"

TEST(FSAngularRateTest, DefaultConstruction_Is_Zero) {
    FSAngularRate angularRate;

    EXPECT_DOUBLE_EQ(angularRate.radiansPerSecond, 0.);
}

TEST(FSAngularRateTest, StaticZero_Is_Zero) {

    EXPECT_DOUBLE_EQ(FSAngularRate::Zero.radiansPerSecond, 0.);
}

TEST(FSAngularRateTest, SpiceDoubleConstructionOne_Is_One) {
    FSAngularRate angularRate(1.);

    EXPECT_DOUBLE_EQ(angularRate.radiansPerSecond, 1.);
}

TEST(FSAngularRateTest, OneAsSpiceDouble_Is_One) {
    FSAngularRate angularRate(1.);

    EXPECT_DOUBLE_EQ(angularRate.AsSpiceDouble(), 1.);
}

TEST(FSAngularRateTest, OneAsRadiansPerSecond_Is_One) {
    FSAngularRate angularRate(1.);

    EXPECT_DOUBLE_EQ(angularRate.AsRadiansPerSecond(), 1.);
}

TEST(FSAngularRateTest, PiAsDegreesPerSecond_Is_180) {
    FSAngularRate angularRate(pi);

    EXPECT_DOUBLE_EQ(angularRate.AsDegreesPerSecond(), 180.);
}


TEST(FSAngularRateTest, TwoTimesThreeRps_Is_6rps) {
    double two = 2.;
    FSAngularRate three(3.);

    FSAngularRate six = two * three;

    EXPECT_DOUBLE_EQ(six.radiansPerSecond, 6.);
}


TEST(FSAngularRateTest, ThreeRpsTimesTwo_Is_6rps) {
    FSAngularRate three(3.);
    double two = 2.;

    FSAngularRate six = three * two;

    EXPECT_DOUBLE_EQ(six.radiansPerSecond, 6.);
}


TEST(FSAngularRateTest, OnePlusTwo_Is_Three) {
    
    FSAngularRate one(1.1);
    FSAngularRate two(2.1);

    FSAngularRate three = one + two;

    EXPECT_DOUBLE_EQ(three.radiansPerSecond, 3.2);
}

TEST(FSAngularRateTest, ThreeMinusTwo_Is_One) {

    FSAngularRate three(3.2);
    FSAngularRate two(2.1);

    FSAngularRate one = three - two;

    EXPECT_DOUBLE_EQ(one.radiansPerSecond, 1.1);
}

TEST(FSAngularRateTest, OneNegated_Is_NegativeOne) {

    FSAngularRate one(1.1);

    FSAngularRate minusone = -one;

    EXPECT_DOUBLE_EQ(minusone.radiansPerSecond, -1.1);
}

TEST(FSAngularRateTest, SixDpsDividedByTwo_Is_ThreeDps) {

    FSAngularRate six(6.8);
    double two = -2.;

    FSAngularRate three = six / two;

    EXPECT_DOUBLE_EQ(three.radiansPerSecond, -3.4);
}


TEST(FSAngularRateTest, SixDpsDividedByTwoDps_Is_Three) {

    FSAngularRate six(-6.8);
    FSAngularRate two(2.);

    double three = six / two;

    EXPECT_DOUBLE_EQ(three, -3.4);
}


TEST(FSAngularRateTest, OnePlusEqualsTwo_Is_Three) {

    FSAngularRate one(1.1);
    FSAngularRate two(2.1);

    one += two;

    EXPECT_DOUBLE_EQ(one.radiansPerSecond, 3.2);
}

TEST(FSAngularRateTest, ThreeMinusEqualsTwo_Is_One) {

    FSAngularRate three(3.2);
    FSAngularRate two(2.1);

    three -= two;

    EXPECT_DOUBLE_EQ(three.radiansPerSecond, 1.1);
}