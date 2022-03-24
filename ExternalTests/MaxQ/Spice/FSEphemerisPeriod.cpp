// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSEphemerisPeriodTest, DefaultConstruction_Is_Initialized) {
    FSEphemerisPeriod ephemerisPeriod;

    EXPECT_DOUBLE_EQ(ephemerisPeriod.seconds, 0.);
}

TEST(FSEphemerisPeriodTest, SpiceDoubleConstruction_Is_Initialized) {
    FSEphemerisPeriod seven(7.1);

    EXPECT_DOUBLE_EQ(seven.seconds, 7.1);
}

TEST(FSEphemerisPeriodTest, Zero_Is_Initialized) {

    double seconds = FSEphemerisPeriod::Zero.seconds;
    EXPECT_DOUBLE_EQ(seconds, 0.);
}


TEST(FSEphemerisPeriodTest, Day_Is_Initialized) {

    double seconds = FSEphemerisPeriod::Day.seconds;
    double day = 24 * 60 * 60;
    EXPECT_DOUBLE_EQ(seconds, day);
}

TEST(FSEphemerisPeriodTest, AsSpiceDouble_Returns_Seconds) {
    FSEphemerisPeriod seven(7.1);

    EXPECT_DOUBLE_EQ(seven.AsSpiceDouble(), 7.1);
}


TEST(FSEphemerisPeriodTest, AsSeconds_Returns_Seconds) {
    FSEphemerisPeriod seven(7.1);

    EXPECT_DOUBLE_EQ(seven.AsSeconds(), 7.1);
}


TEST(FSEphemerisPeriodTest, SevenEqualsSeven_Is_True) {
    FSEphemerisPeriod seven1(7.123456789);
    FSEphemerisPeriod seven2(7.123456789);

    bool equals = (seven1 == seven2);

    EXPECT_EQ(equals, true);
}


TEST(FSEphemerisPeriodTest, SevenEqualsEight_Is_False) {
    FSEphemerisPeriod seven(7.123456789);
    FSEphemerisPeriod eight(7.223456789);

    bool equals = (seven == eight);

    EXPECT_EQ(equals, false);
}

TEST(FSEphemerisPeriodTest, SevenNotEqualsSeven_Is_False) {
    FSEphemerisPeriod seven1(7.123456789);
    FSEphemerisPeriod seven2(7.123456789);

    bool notequals = (seven1 != seven2);

    EXPECT_EQ(notequals, false);
}


TEST(FSEphemerisPeriodTest, SevenNotEqualsEight_Is_True) {
    FSEphemerisPeriod seven(7.123456789);
    FSEphemerisPeriod eight(7.223456789);

    bool equals = (seven != eight);

    EXPECT_EQ(equals, true);
}

TEST(FSEphemerisPeriodTest, SevenLessThanSix_Is_False) {
    FSEphemerisPeriod seven(7.123456789);
    FSEphemerisPeriod six(7.103456789);

    bool lessthan = (seven < six);

    EXPECT_EQ(lessthan, false);
}

TEST(FSEphemerisPeriodTest, SevenLessThanSeven_Is_False) {
    FSEphemerisPeriod seven1(7.123456789);
    FSEphemerisPeriod seven2(7.123456789);

    bool lessthan = (seven1 < seven2);

    EXPECT_EQ(lessthan, false);
}


TEST(FSEphemerisPeriodTest, SevenLessThanEight_Is_True) {
    FSEphemerisPeriod seven(7.123456789);
    FSEphemerisPeriod eight(7.223456789);

    bool lessthan = (seven < eight);

    EXPECT_EQ(lessthan, true);
}

TEST(FSEphemerisPeriodTest, SevenGreaterThanSix_Is_True) {
    FSEphemerisPeriod seven(7.123456789);
    FSEphemerisPeriod six(7.103456789);

    bool greaterthan = (seven > six);

    EXPECT_EQ(greaterthan, true);
}

TEST(FSEphemerisPeriodTest, SevenGreaterThanSeven_Is_False) {
    FSEphemerisPeriod seven1(7.123456789);
    FSEphemerisPeriod seven2(7.123456789);

    bool greaterthan = (seven1 > seven2);

    EXPECT_EQ(greaterthan, false);
}


TEST(FSEphemerisPeriodTest, SevenGreaterThanEight_Is_False) {
    FSEphemerisPeriod seven(7.123456789);
    FSEphemerisPeriod eight(7.223456789);

    bool greaterthan = (seven > eight);

    EXPECT_EQ(greaterthan, false);
}


TEST(FSEphemerisPeriodTest, OnePlusTwo_Equals_Three) {
    FSEphemerisPeriod one(1.23);
    FSEphemerisPeriod two(2.34);

    FSEphemerisPeriod three = one + two;

    EXPECT_EQ(three.seconds, 3.57);
}


TEST(FSEphemerisPeriodTest, OneMinusTwo_Equals_NegativeOne) {
    FSEphemerisPeriod one(1.23);
    FSEphemerisPeriod two(2.12);

    FSEphemerisPeriod three = one - two;

    EXPECT_EQ(three.seconds, 1.23 - 2.12);
}

TEST(FSEphemerisPeriodTest, OnePlusEqualsTwo_Equals_Three) {
    FSEphemerisPeriod one(1.23);
    FSEphemerisPeriod two(2.34);

    one += two;

    EXPECT_EQ(one.seconds, 3.57);
}


TEST(FSEphemerisPeriodTest, OneMinusEqualsTwo_Equals_NegativeOne) {
    FSEphemerisPeriod one(1.23);
    FSEphemerisPeriod two(2.12);

    one -= two;

    EXPECT_EQ(one.seconds, 1.23 - 2.12);
}

TEST(FSEphemerisPeriodTest, OnePlusDeltaTwo_Equals_Three) {
    FSEphemerisTime one(1.23);
    FSEphemerisPeriod two(2.34);

    FSEphemerisTime three = one + two;

    EXPECT_EQ(three.seconds, 3.57);
}

TEST(FSEphemerisPeriodTest, OneDeltaPlusTwo_Equals_Three) {
    FSEphemerisPeriod one(1.23);
    FSEphemerisTime two(2.34);

    FSEphemerisTime three = one + two;

    EXPECT_EQ(three.seconds, 3.57);
}


TEST(FSEphemerisPeriodTest, ThreeMinusDeltaTwo_Equals_One) {
    FSEphemerisTime three(3.45);
    FSEphemerisPeriod two(2.12);

    FSEphemerisTime one = three - two;

    EXPECT_EQ(one.seconds, 3.45 - 2.12);
}


TEST(FSEphemerisPeriodTest, OnePlusEqualsDeltaTwo_Equals_Three) {
    FSEphemerisTime one(1.23);
    FSEphemerisPeriod two(2.34);

    one += two;

    EXPECT_EQ(one.seconds, 3.57);
}

TEST(FSEphemerisPeriodTest, ThreeMinusEqualsDeltaTwo_Equals_One) {
    FSEphemerisTime three(3.45);
    FSEphemerisPeriod two(2.12);

    three -= two;

    EXPECT_EQ(three.seconds, 3.45 - 2.12);
}


TEST(FSEphemerisPeriodTest, OneMinusTwo_Equals_NegativeDeltaOne) {
    FSEphemerisTime one(1.23);
    FSEphemerisTime two(2.12);

    FSEphemerisPeriod three = one - two;

    EXPECT_EQ(three.seconds, 1.23 - 2.12);
}

TEST(FSEphemerisPeriodTest, TwoTimesThreeSeconds_Equals_SixSeconds) {
    double two = 2;
    FSEphemerisPeriod three(3.13);

    FSEphemerisPeriod six = two * three;

    EXPECT_EQ(six.seconds, 6.26);
}

TEST(FSEphemerisPeriodTest, TwoSecondsTimesThree_Equals_SixSeconds) {
    FSEphemerisPeriod two(2);
    double three = 3.13;

    FSEphemerisPeriod six = two * three;

    EXPECT_EQ(six.seconds, 6.26);
}


TEST(FSEphemerisPeriodTest, SixSecondsDividedByThree_Equals_TwoSeconds) {
    FSEphemerisPeriod six(6.26);
    double three = 3.13;

    FSEphemerisPeriod two = six / three;

    EXPECT_EQ(two.seconds, 2.);
}


TEST(FSEphemerisPeriodTest, SixSecondsDividedByThreeSeconds_Equals_Two) {
    FSEphemerisPeriod six(6.26);
    FSEphemerisPeriod three(3.13);

    double two = six / three;

    EXPECT_EQ(two, 2.);
}


TEST(FSEphemerisPeriodTest, SixSecondsModThree_Equals_ZeroSeconds) {
    FSEphemerisPeriod six(6.26 + 0.25);
    FSEphemerisPeriod three(3.13);

    FSEphemerisPeriod zero = six % three;

    EXPECT_EQ(zero.seconds, 0.25);
}


TEST(FSEphemerisPeriodTest, TwoSecondsTimesThreeKmps_Equals_SixKilometers) {
    FSEphemerisPeriod two(2);
    FSSpeed three(3.13);

    FSDistance six = two * three;

    EXPECT_EQ(six.km, 6.26);
}


TEST(FSEphemerisPeriodTest, TwoKmpsTimesThreeSeconds_Equals_SixKilometers) {
    FSSpeed two(2);
    FSEphemerisPeriod three(3.13);

    FSDistance six = two * three;

    EXPECT_EQ(six.km, 6.26);
}