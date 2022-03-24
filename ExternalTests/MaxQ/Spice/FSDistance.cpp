// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSDistanceTest, DefaultConstruction_Is_Initialized) {
    FSDistance distance;

    EXPECT_DOUBLE_EQ(distance.km, 0.);
}

TEST(FSDistanceTest, Zero_Is_ZeroKilomenters) {
    EXPECT_DOUBLE_EQ(FSDistance::Zero.km, 0.);
}

TEST(FSDistanceTest, OneKm_Is_OneKilometer) {
    EXPECT_DOUBLE_EQ(FSDistance::OneKm.km, 1.);
}

TEST(FSDistanceTest, OneMeter_Is_OneMeter) {
    FSDistance dist = FSDistance::FromMeters(1.);

    EXPECT_DOUBLE_EQ(dist.km, 1. / 1000.);

    EXPECT_DOUBLE_EQ(FSDistance::OneMeter.km, 1./1000.);
}


TEST(FSDistanceTest, Constructor_Sets_Kilometers) {
    FSDistance distance(1);

    EXPECT_DOUBLE_EQ(distance.km, 1.);
}


TEST(FSDistanceTest, AsKilometers_Returns_Kilometers) {
    FSDistance distance(1);

    EXPECT_DOUBLE_EQ(distance.km, distance.AsKilometers());
}

TEST(FSDistanceTest, AsSpiceDouble_Returns_Kilometers) {
    FSDistance distance(1);

    EXPECT_DOUBLE_EQ(distance.km, distance.AsSpiceDouble());
}

TEST(FSDistanceTest, AsMeters_Returns_Kilometers) {
    FSDistance distance(1);

    EXPECT_DOUBLE_EQ(distance.km * 1000., distance.AsMeters());
}


TEST(FSDistanceTest, CopyConstructor_Sets_Kilometers) {
    FSDistance distance1(1);
    FSDistance distance2(distance1);

    EXPECT_DOUBLE_EQ(distance2.km, 1.);
}


TEST(FSDistanceTest, Assignment_Sets_Kilometers) {
    FSDistance distance1(1.);
    FSDistance distance2(0.);

    distance2 = distance1;
    distance1.km = 0;

    EXPECT_DOUBLE_EQ(distance2.km, 1.);
}


TEST(FSDistanceTest, ZeroLessThanOne_Returns_True) {
    FSDistance distance1(0.);
    FSDistance distance2(1.);

    EXPECT_TRUE(distance1 < distance2);
}

TEST(FSDistanceTest, OneLessThanOne_Returns_False) {
    FSDistance distance1(1.);
    FSDistance distance2(1.);

    EXPECT_FALSE(distance1 < distance2);
}


TEST(FSDistanceTest, OneLessThanZero_Returns_False) {
    FSDistance distance1(1.);
    FSDistance distance2(0.);

    EXPECT_FALSE(distance1 < distance2);
}


TEST(FSDistanceTest, ZeroGreaterThanOne_Returns_False) {
    FSDistance distance1(0.);
    FSDistance distance2(1.);

    EXPECT_FALSE(distance1 > distance2);
}

TEST(FSDistanceTest, OneGreaterThanOne_Returns_False) {
    FSDistance distance1(1.);
    FSDistance distance2(1.);

    EXPECT_FALSE(distance1 > distance2);
}


TEST(FSDistanceTest, OneGreaterThanZero_Returns_True) {
    FSDistance distance1(1.);
    FSDistance distance2(0.);

    EXPECT_TRUE(distance1 > distance2);
}


TEST(FSDistanceTest, OnePlusTwo_Is_Three) {
    FSDistance distance1(1.2);
    FSDistance distance2(2.3);

    FSDistance distance3 = distance1 + distance2;

    EXPECT_DOUBLE_EQ(distance3.km, 3.5);
}

TEST(FSDistanceTest, OneMinusTwo_Is_NegativeOne) {
    FSDistance distance1(1.2);
    FSDistance distance2(2.3);

    FSDistance distance3 = distance1 - distance2;

    EXPECT_DOUBLE_EQ(distance3.km, -1.1);
}


TEST(FSDistanceTest, TwelveDividedByThree_Is_Four) {
    FSDistance distance1(-12.4);
    FSDistance distance2(3.1);

    double double3 = distance1 / distance2;

    EXPECT_DOUBLE_EQ(double3, -4);
}