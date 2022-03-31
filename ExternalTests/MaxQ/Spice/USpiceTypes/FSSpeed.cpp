// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSSpeedTest, DefaultConstruction_IsInitialized) {
    FSSpeed speed;

    EXPECT_DOUBLE_EQ(speed.kmps, 0.);
}


TEST(FSSpeedTest, Zero_Is_ZeroKmps) {
    EXPECT_DOUBLE_EQ(FSSpeed::Zero.kmps, 0.);
}

TEST(FSSpeedTest, OneKmps_Is_OnKmps) {
    EXPECT_DOUBLE_EQ(FSSpeed::OneKmps.kmps, 1.);
}



TEST(FSSpeedTest, Constructor_Sets_Kmps) {
    FSSpeed speed(1);

    EXPECT_DOUBLE_EQ(speed.kmps, 1.);
}


TEST(FSSpeedTest, AsKmps_Returns_Kmps) {
    FSSpeed speed(1);

    EXPECT_DOUBLE_EQ(speed.kmps, speed.AsKilometersPerSecond());
}

TEST(FSSpeedTest, AsSpiceDouble_Returns_Kmpss) {
    FSSpeed speed(1);

    EXPECT_DOUBLE_EQ(speed.kmps, speed.AsSpiceDouble());
}



TEST(FSSpeedTest, CopyConstructor_Sets_Kmps) {
    FSSpeed speed1(1);
    FSSpeed speed2(speed1);

    EXPECT_DOUBLE_EQ(speed2.kmps, 1.);
}


TEST(FSSpeedTest, Assignment_Sets_Kmps) {
    FSSpeed speed1(1.);
    FSSpeed speed2(0.);

    speed2 = speed1;
    speed1.kmps = 0;

    EXPECT_DOUBLE_EQ(speed2.kmps, 1.);
}


TEST(FSSpeedTest, ZeroLessThanOne_Returns_True) {
    FSSpeed speed1(0.);
    FSSpeed speed2(1.);

    EXPECT_TRUE(speed1 < speed2);
}

TEST(FSSpeedTest, OneLessThanOne_Returns_False) {
    FSSpeed speed1(1.);
    FSSpeed speed2(1.);

    EXPECT_FALSE(speed1 < speed2);
}


TEST(FSSpeedTest, OneLessThanZero_Returns_False) {
    FSSpeed speed1(1.);
    FSSpeed speed2(0.);

    EXPECT_FALSE(speed1 < speed2);
}


TEST(FSSpeedTest, ZeroGreaterThanOne_Returns_False) {
    FSSpeed speed1(0.);
    FSSpeed speed2(1.);

    EXPECT_FALSE(speed1 > speed2);
}

TEST(FSSpeedTest, OneGreaterThanOne_Returns_False) {
    FSSpeed speed1(1.);
    FSSpeed speed2(1.);

    EXPECT_FALSE(speed1 > speed2);
}


TEST(FSSpeedTest, OneGreaterThanZero_Returns_True) {
    FSSpeed speed1(1.);
    FSSpeed speed2(0.);

    EXPECT_TRUE(speed1 > speed2);
}


TEST(FSSpeedTest, OnePlusTwo_Is_Three) {
    FSSpeed speed1(1.2);
    FSSpeed speed2(2.3);

    FSSpeed speed3 = speed1 + speed2;

    EXPECT_DOUBLE_EQ(speed3.kmps, 3.5);
}

TEST(FSSpeedTest, OneMinusTwo_Is_NegativeOne) {
    FSSpeed speed1(1.2);
    FSSpeed speed2(2.3);

    FSSpeed speed3 = speed1 - speed2;

    EXPECT_DOUBLE_EQ(speed3.kmps, -1.1);
}


TEST(FSSpeedTest, OneNegated_Is_NegativeOne) {
    FSSpeed speed1(1.2);
    FSSpeed speed2 = -speed1;

    EXPECT_DOUBLE_EQ(speed2.kmps, -1.2);
}

TEST(FSSpeedTest, TwelveDividedByThree_Is_Four) {
    FSSpeed speed1(-12.4);
    FSSpeed speed2(3.1);

    double double3 = speed1 / speed2;

    EXPECT_DOUBLE_EQ(double3, -4);
}


TEST(FSSpeedTest, TwelveKmpsDividedByThree_Is_FourKmps) {
    FSSpeed speed1(-12.4);
    double double2(3.1);

    FSSpeed speed3 = speed1 / double2;

    EXPECT_DOUBLE_EQ(speed3.kmps, -4);
}


TEST(FSSpeedTest, ThreeTimesFouKmps_Is_TwelvKmps) {
    double value1(3.1);
    FSSpeed value2(-4);

    FSSpeed value3 = value1 * value2;

    EXPECT_DOUBLE_EQ(value3.kmps, -12.4);
}


TEST(FSSpeedTest, ThreeKmpsTimesFour_Is_TwelveKmps) {
    FSSpeed value1(3.1);
    double value2(-4);

    FSSpeed value3 = value1 * value2;

    EXPECT_DOUBLE_EQ(value3.kmps, -12.4);
}

TEST(FSSpeedTest, TwelveKmps_Equals_TwelveKmps_Is_True) {
    FSSpeed value1(-12.4);
    FSSpeed value2(-12.4);

    bool value3 = (value1 == value2);

    EXPECT_EQ(value3, true);
}

TEST(FSSpeedTest, TwelveKmps_Equals_ElevenKmps_Is_False) {
    FSSpeed value1(-12.4);
    FSSpeed value2(-12.3);

    bool value3 = (value1 == value2);

    EXPECT_EQ(value3, false);
}


TEST(FSSpeedTest, TwelveKmps_NotEquals_TwelveKmps_Is_False) {
    FSSpeed value1(-12.4);
    FSSpeed value2(-12.4);

    bool value3 = (value1 != value2);

    EXPECT_EQ(value3, false);
}

TEST(FSSpeedTest, TwelveKmps_NotEquals_ElevenKmps_Is_True) {
    FSSpeed value1(-12.4);
    FSSpeed value2(-12.3);

    bool value3 = (value1 != value2);

    EXPECT_EQ(value3, true);
}


TEST(FSSpeedTest, OneKmpsPlusEqualsTwoKmps_Is_ThreeKmpss) {
    FSSpeed speed1(1.2);
    FSSpeed speed2(2.3);

    speed1 += speed2;

    EXPECT_DOUBLE_EQ(speed1.kmps, 3.5);
}


TEST(FSSpeedTest, OneKmpsMinusEqualsTwoKmpss_Is_NegativeOneKmps) {
    FSSpeed speed1(1.2);
    FSSpeed speed2(2.3);

    speed1 -= speed2;

    EXPECT_DOUBLE_EQ(speed1.kmps, -1.1);
}