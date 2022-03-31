// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(vcrss_test, DefaultsTestCase) {

    FSDimensionlessVector v1, v2, vout;

    USpice::vcrss(v1, v2, vout);

    EXPECT_DOUBLE_EQ(vout.x, 0.);
    EXPECT_DOUBLE_EQ(vout.y, 0.);
    EXPECT_DOUBLE_EQ(vout.z, 0.);
}


TEST(vcrss_test, Parallel_Is_Zero) {

    FSDimensionlessVector v1(1.5, -2.5, 3.5);
    FSDimensionlessVector v2(1.5, -2.5, 3.5);
    FSDimensionlessVector vout(1, 1, 1);

    USpice::vcrss(v1, v2, vout);

    EXPECT_DOUBLE_EQ(vout.x, 0.);
    EXPECT_DOUBLE_EQ(vout.y, 0.);
    EXPECT_DOUBLE_EQ(vout.z, 0.);
}


TEST(vcrss_test, XY_Is_Z) {

    FSDimensionlessVector v1(1, 0, 0);
    FSDimensionlessVector v2(0, 1, 0);
    FSDimensionlessVector vout(1, 1, 1);

    USpice::vcrss(v1, v2, vout);

    EXPECT_DOUBLE_EQ(vout.x, 0.);
    EXPECT_DOUBLE_EQ(vout.y, 0.);
    EXPECT_DOUBLE_EQ(vout.z, 1.);
}

TEST(vcrss_test, XY_Is_NegZ) {

    FSDimensionlessVector v1(0, 1, 0);
    FSDimensionlessVector v2(1, 0, 0);
    FSDimensionlessVector vout(1, 1, 1);

    USpice::vcrss(v1, v2, vout);

    EXPECT_DOUBLE_EQ(vout.x, 0.);
    EXPECT_DOUBLE_EQ(vout.y, 0.);
    EXPECT_DOUBLE_EQ(vout.z, -1.);
}


TEST(vcrss_test, YZ_Is_X) {

    FSDimensionlessVector v1(0, 1, 0);
    FSDimensionlessVector v2(0, 0, 1);
    FSDimensionlessVector vout(1, 1, 1);

    USpice::vcrss(v1, v2, vout);

    EXPECT_DOUBLE_EQ(vout.x, 1.);
    EXPECT_DOUBLE_EQ(vout.y, 0.);
    EXPECT_DOUBLE_EQ(vout.z, 0.);
}

TEST(vcrss_test, ZY_Is_NegX) {

    FSDimensionlessVector v1(0, 0, 1);
    FSDimensionlessVector v2(0, 1, 0);
    FSDimensionlessVector vout(1, 1, 1);

    USpice::vcrss(v1, v2, vout);

    EXPECT_DOUBLE_EQ(vout.x, -1.);
    EXPECT_DOUBLE_EQ(vout.y, 0.);
    EXPECT_DOUBLE_EQ(vout.z, 0.);
}


TEST(vcrss_test, ZX_Is_Y) {

    FSDimensionlessVector v1(0, 0, 1);
    FSDimensionlessVector v2(1, 0, 0);
    FSDimensionlessVector vout(1, 1, 1);

    USpice::vcrss(v1, v2, vout);

    EXPECT_DOUBLE_EQ(vout.x, 0.);
    EXPECT_DOUBLE_EQ(vout.y, 1.);
    EXPECT_DOUBLE_EQ(vout.z, 0.);
}

TEST(vcrss_test, XZ_Is_NegY) {

    FSDimensionlessVector v1(1, 0, 0);
    FSDimensionlessVector v2(0, 0, 1);
    FSDimensionlessVector vout(1, 1, 1);

    USpice::vcrss(v1, v2, vout);

    EXPECT_DOUBLE_EQ(vout.x, 0.);
    EXPECT_DOUBLE_EQ(vout.y, -1.);
    EXPECT_DOUBLE_EQ(vout.z, 0.);
}