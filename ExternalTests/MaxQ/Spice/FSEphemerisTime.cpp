// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSEphemerisTimeTest, DefaultConstruction_Is_Initialized) {
    FSEphemerisTime ephemerisTime;

    EXPECT_DOUBLE_EQ(ephemerisTime.seconds, 0.);
}


TEST(FSEphemerisTimeTest, SpiceDoubleConstruction_Is_Initialized) {
    FSEphemerisTime ephemerisTime(7.1);

    EXPECT_DOUBLE_EQ(ephemerisTime.seconds, 7.1);
}

TEST(FSEphemerisTimeTest, J2000_IsInitialized) {
    EXPECT_DOUBLE_EQ(FSEphemerisTime::J2000.seconds, 0.);
}

TEST(FSEphemerisTimeTest, AsSpiceDouble_Returns_Seconds) {
    FSEphemerisTime ephemerisTime(7.1);

    EXPECT_DOUBLE_EQ(ephemerisTime.AsSpiceDouble(), 7.1);
}


TEST(FSEphemerisTimeTest, AsSeconds_Returns_Seconds) {
    FSEphemerisTime ephemerisTime(7.1);

    EXPECT_DOUBLE_EQ(ephemerisTime.AsSeconds(), 7.1);
}


TEST(FSEphemerisTimeTest, SevenEqualsSeven_Is_True) {
    FSEphemerisTime seven1(7.123456789);
    FSEphemerisTime seven2(7.123456789);

    bool equals = (seven1 == seven2);

    EXPECT_EQ(equals, true);
}


TEST(FSEphemerisTimeTest, SevenEqualsEight_Is_False) {
    FSEphemerisTime seven(7.123456789);
    FSEphemerisTime eight(7.223456789);

    bool equals = (seven == eight);

    EXPECT_EQ(equals, false);
}

TEST(FSEphemerisTimeTest, SevenNotEqualsSeven_Is_False) {
    FSEphemerisTime seven1(7.123456789);
    FSEphemerisTime seven2(7.123456789);

    bool notequals = (seven1 != seven2);

    EXPECT_EQ(notequals, false);
}


TEST(FSEphemerisTimeTest, SevenNotEqualsEight_Is_True) {
    FSEphemerisTime seven(7.123456789);
    FSEphemerisTime eight(7.223456789);

    bool equals = (seven != eight);

    EXPECT_EQ(equals, true);
}

TEST(FSEphemerisTimeTest, SevenLessThanSix_Is_False) {
    FSEphemerisTime seven(7.123456789);
    FSEphemerisTime six(7.103456789);

    bool lessthan = (seven < six);

    EXPECT_EQ(lessthan, false);
}

TEST(FSEphemerisTimeTest, SevenLessThanSeven_Is_False) {
    FSEphemerisTime seven1(7.123456789);
    FSEphemerisTime seven2(7.123456789);

    bool lessthan = (seven1 < seven2);

    EXPECT_EQ(lessthan, false);
}


TEST(FSEphemerisTimeTest, SevenLessThanEight_Is_True) {
    FSEphemerisTime seven(7.123456789);
    FSEphemerisTime eight(7.223456789);

    bool lessthan = (seven < eight);

    EXPECT_EQ(lessthan, true);
}

TEST(FSEphemerisTimeTest, SevenGreaterThanSix_Is_True) {
    FSEphemerisTime seven(7.123456789);
    FSEphemerisTime six(7.103456789);

    bool greaterthan = (seven > six);

    EXPECT_EQ(greaterthan, true);
}

TEST(FSEphemerisTimeTest, SevenGreaterThanSeven_Is_False) {
    FSEphemerisTime seven1(7.123456789);
    FSEphemerisTime seven2(7.123456789);

    bool greaterthan = (seven1 > seven2);

    EXPECT_EQ(greaterthan, false);
}


TEST(FSEphemerisTimeTest, SevenGreaterThanEight_Is_False) {
    FSEphemerisTime seven(7.123456789);
    FSEphemerisTime eight(7.223456789);

    bool greaterthan = (seven > eight);

    EXPECT_EQ(greaterthan, false);
}