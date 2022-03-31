// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSVelocityVectorTest, DefaultConstruction_IsInitialized) {
    FSVelocityVector velocityVector;

    EXPECT_DOUBLE_EQ(velocityVector.dx.kmps, 0.);
    EXPECT_DOUBLE_EQ(velocityVector.dy.kmps, 0.);
    EXPECT_DOUBLE_EQ(velocityVector.dz.kmps, 0.);
}

TEST(FSVelocityVectorTest, Zero_Is_Zero) {

    EXPECT_DOUBLE_EQ(FSVelocityVector::Zero.dx.kmps, 0.);
    EXPECT_DOUBLE_EQ(FSVelocityVector::Zero.dy.kmps, 0.);
    EXPECT_DOUBLE_EQ(FSVelocityVector::Zero.dz.kmps, 0.);
}

TEST(FSVelocityVectorTest, SpiceDoubleConstruction_Sets_Kilometers) {
    FSVelocityVector velocityVector(1.1, 2.2, 3.3);

    EXPECT_DOUBLE_EQ(velocityVector.dx.kmps, 1.1);
    EXPECT_DOUBLE_EQ(velocityVector.dy.kmps, 2.2);
    EXPECT_DOUBLE_EQ(velocityVector.dz.kmps, 3.3);
}


TEST(FSVelocityVectorTest, SpeedConstruction_Sets_Kilometers) {
    FSVelocityVector velocityVector(FSSpeed(1.1), FSSpeed(2.2), FSSpeed(3.3));

    EXPECT_DOUBLE_EQ(velocityVector.dx.kmps, 1.1);
    EXPECT_DOUBLE_EQ(velocityVector.dy.kmps, 2.2);
    EXPECT_DOUBLE_EQ(velocityVector.dz.kmps, 3.3);
}


TEST(FSVelocityVectorTest, SpiceDoubleArrayConstruction_Sets_Kilometers) {
    double xyz[3] = { 1.1, 2.2, 3.3 };

    FSVelocityVector velocityVector(xyz);

    EXPECT_DOUBLE_EQ(velocityVector.dx.kmps, 1.1);
    EXPECT_DOUBLE_EQ(velocityVector.dy.kmps, 2.2);
    EXPECT_DOUBLE_EQ(velocityVector.dz.kmps, 3.3);
}

TEST(FSVelocityVectorTest, CopyConstructor_Sets_Kilometers) {
    FSVelocityVector velocityVector1;

    velocityVector1.dx.kmps = 1.1;
    velocityVector1.dy.kmps = 2.2;
    velocityVector1.dz.kmps = 3.3;

    FSVelocityVector velocityVector2(velocityVector1);

    EXPECT_DOUBLE_EQ(velocityVector2.dx.kmps, 1.1);
    EXPECT_DOUBLE_EQ(velocityVector2.dy.kmps, 2.2);
    EXPECT_DOUBLE_EQ(velocityVector2.dz.kmps, 3.3);
}


TEST(FSVelocityVectorTest, AsDimensionlessVector_Sets_ValuesAsKilometers) {
    FSVelocityVector velocityVector1;

    velocityVector1.dx.kmps = 1.1;
    velocityVector1.dy.kmps = 2.2;
    velocityVector1.dz.kmps = 3.3;

    FSDimensionlessVector dimensionlessVector2;

    velocityVector1.AsDimensionlessVector(dimensionlessVector2);

    EXPECT_DOUBLE_EQ(dimensionlessVector2.x, 1.1);
    EXPECT_DOUBLE_EQ(dimensionlessVector2.y, 2.2);
    EXPECT_DOUBLE_EQ(dimensionlessVector2.z, 3.3);
}


TEST(FSVelocityVectorTest, CopyTo_Sets_SpiceDoublesAsKilometerValues) {
    FSVelocityVector velocityVector;

    velocityVector.dx.kmps = 1.1;
    velocityVector.dy.kmps = 2.2;
    velocityVector.dz.kmps = 3.3;

    double xyz[3] = { -7.7, 1.2, 1.3 };

    velocityVector.CopyTo(xyz);

    EXPECT_DOUBLE_EQ(xyz[0], 1.1);
    EXPECT_DOUBLE_EQ(xyz[1], 2.2);
    EXPECT_DOUBLE_EQ(xyz[2], 3.3);
}


TEST(FSVelocityVectorTest, SevenXReturnedNormalized_Is_OneX) {
    FSVelocityVector velocityVector1;

    velocityVector1.dx.kmps = 7.0;
    velocityVector1.dy.kmps = 0.0;
    velocityVector1.dz.kmps = 0.0;

    FSDimensionlessVector velocityVector2 = velocityVector1.Normalized();


    EXPECT_DOUBLE_EQ(velocityVector2.x, 1.);
    EXPECT_DOUBLE_EQ(velocityVector2.y, 0.);
    EXPECT_DOUBLE_EQ(velocityVector2.z, 0.);
}


TEST(FSVelocityVectorTest, SevenYReturnedNormalized_Is_OneY) {
    FSVelocityVector velocityVector1;

    velocityVector1.dx.kmps = 0.0;
    velocityVector1.dy.kmps = -7.0;
    velocityVector1.dz.kmps = 0.0;

    FSDimensionlessVector velocityVector2 = velocityVector1.Normalized();


    EXPECT_DOUBLE_EQ(velocityVector2.x, 0.);
    EXPECT_DOUBLE_EQ(velocityVector2.y, -1.);
    EXPECT_DOUBLE_EQ(velocityVector2.z, 0.);
}

TEST(FSVelocityVectorTest, SevenZReturnedNormalized_Is_OneZ) {
    FSVelocityVector velocityVector1;

    velocityVector1.dx.kmps = 0.0;
    velocityVector1.dy.kmps = 0.0;
    velocityVector1.dz.kmps = -7.0;

    FSDimensionlessVector velocityVector2 = velocityVector1.Normalized();


    EXPECT_DOUBLE_EQ(velocityVector2.x, 0.);
    EXPECT_DOUBLE_EQ(velocityVector2.y, 0.);
    EXPECT_DOUBLE_EQ(velocityVector2.z, -1.);
}

TEST(FSVelocityVectorTest, VectorReturnedNormalized_Is_Correct) {
    FSVelocityVector velocityVector1;

    velocityVector1.dx.kmps = 2.0;
    velocityVector1.dy.kmps = -3.0;
    velocityVector1.dz.kmps = 4.0;

    FSDimensionlessVector velocityVector2 = velocityVector1.Normalized();

    double scale = 1. / sqrt(2 * 2 + 3 * 3 + 4 * 4);

    EXPECT_DOUBLE_EQ(velocityVector2.x, 2.0 * scale);
    EXPECT_DOUBLE_EQ(velocityVector2.y, -3.0 * scale);
    EXPECT_DOUBLE_EQ(velocityVector2.z, 4.0 * scale);
}

TEST(FSVelocityVectorTest, SevenXSetNormalized_Is_OneX) {
    FSVelocityVector velocityVector1;

    velocityVector1.dx.kmps = 7.0;
    velocityVector1.dy.kmps = 0.0;
    velocityVector1.dz.kmps = 0.0;

    FSDimensionlessVector velocityVector2(10, 10, 10);
    velocityVector1.Normalized(velocityVector2);


    EXPECT_DOUBLE_EQ(velocityVector2.x, 1.);
    EXPECT_DOUBLE_EQ(velocityVector2.y, 0.);
    EXPECT_DOUBLE_EQ(velocityVector2.z, 0.);
}

TEST(FSVelocityVectorTest, SevenYSetNormalized_Is_OneY) {
    FSVelocityVector velocityVector1;

    velocityVector1.dx.kmps = 0.0;
    velocityVector1.dy.kmps = -7.0;
    velocityVector1.dz.kmps = 0.0;

    FSDimensionlessVector velocityVector2(10, 10, 10);
    velocityVector1.Normalized(velocityVector2);

    EXPECT_DOUBLE_EQ(velocityVector2.x, 0.);
    EXPECT_DOUBLE_EQ(velocityVector2.y, -1.);
    EXPECT_DOUBLE_EQ(velocityVector2.z, 0.);
}

TEST(FSVelocityVectorTest, SevenZSetNormalized_Is_OneZ) {
    FSVelocityVector velocityVector1;

    velocityVector1.dx.kmps = 0.0;
    velocityVector1.dy.kmps = 0.0;
    velocityVector1.dz.kmps = -7.0;

    FSDimensionlessVector velocityVector2(10, 10, 10);
    velocityVector1.Normalized(velocityVector2);

    EXPECT_DOUBLE_EQ(velocityVector2.x, 0.);
    EXPECT_DOUBLE_EQ(velocityVector2.y, 0.);
    EXPECT_DOUBLE_EQ(velocityVector2.z, -1.);
}

TEST(FSVelocityVectorTest, VectorSetNormalized_Is_Correct) {
    FSVelocityVector velocityVector1;

    velocityVector1.dx.kmps = 2.0;
    velocityVector1.dy.kmps = -3.0;
    velocityVector1.dz.kmps = 4.0;

    FSDimensionlessVector velocityVector2(10, 10, 10);
    velocityVector1.Normalized(velocityVector2);

    double scale = 1. / sqrt(2 * 2 + 3 * 3 + 4 * 4);

    EXPECT_DOUBLE_EQ(velocityVector2.x, 2.0 * scale);
    EXPECT_DOUBLE_EQ(velocityVector2.y, -3.0 * scale);
    EXPECT_DOUBLE_EQ(velocityVector2.z, 4.0 * scale);
}


TEST(FSVelocityVectorTest, SevenXMagnitude_Is_OneX) {
    FSVelocityVector velocityVector1;

    velocityVector1.dx.kmps = 7.0;
    velocityVector1.dy.kmps = 0.0;
    velocityVector1.dz.kmps = 0.0;

    FSSpeed speed = velocityVector1.Magnitude();

    EXPECT_DOUBLE_EQ(speed.kmps, 7.);
}

TEST(FSVelocityVectorTest, SevenYMagnitude_Is_OneY) {
    FSVelocityVector velocityVector1;

    velocityVector1.dx.kmps = 0.0;
    velocityVector1.dy.kmps = -7.0;
    velocityVector1.dz.kmps = 0.0;

    FSSpeed speed = velocityVector1.Magnitude();

    EXPECT_DOUBLE_EQ(speed.kmps, 7.);
}

TEST(FSVelocityVectorTest, SevenZMagnitude_Is_OneZ) {
    FSVelocityVector velocityVector1;

    velocityVector1.dx.kmps = 0.0;
    velocityVector1.dy.kmps = 0.0;
    velocityVector1.dz.kmps = -7.0;

    FSSpeed speed = velocityVector1.Magnitude();

    EXPECT_DOUBLE_EQ(speed.kmps, 7.);
}

TEST(FSVelocityVectorTest, VectorMagnitude_Is_Correct) {
    FSVelocityVector velocityVector1;

    velocityVector1.dx.kmps = 2.0;
    velocityVector1.dy.kmps = -3.0;
    velocityVector1.dz.kmps = 4.0;

    double magnitude = sqrt(2 * 2 + 3 * 3 + 4 * 4);

    FSSpeed speed = velocityVector1.Magnitude();

    EXPECT_DOUBLE_EQ(speed.kmps, magnitude);
}


TEST(FSVelocityVectorTest, OnePlusTwo_Is_Three) {
    FSVelocityVector velocityVector1(1.1, 1.2, 1.3);
    FSVelocityVector velocityVector2(2.1, 2.2, 2.3);

    FSVelocityVector velocityVector3 = velocityVector1 + velocityVector2;

    EXPECT_DOUBLE_EQ(velocityVector3.dx.kmps, 3.2);
    EXPECT_DOUBLE_EQ(velocityVector3.dy.kmps, 3.4);
    EXPECT_DOUBLE_EQ(velocityVector3.dz.kmps, 3.6);
}


TEST(FSVelocityVectorTest, OneMinusTwo_Is_NegativeOne) {
    FSVelocityVector velocityVector1(1.2, 1.4, 1.6);
    FSVelocityVector velocityVector2(2.1, 2.2, 2.3);

    FSVelocityVector velocityVector3 = velocityVector1 - velocityVector2;

    EXPECT_DOUBLE_EQ(velocityVector3.dx.kmps, -0.9);
    EXPECT_DOUBLE_EQ(velocityVector3.dy.kmps, -0.8);
    EXPECT_DOUBLE_EQ(velocityVector3.dz.kmps, -0.7);
}


TEST(FSVelocityVectorTest, OneNegated_Is_NegativeOne) {
    FSVelocityVector velocityVector1(1.1, 1.2, 1.3);

    FSVelocityVector velocityVector2 = -velocityVector1;

    EXPECT_DOUBLE_EQ(velocityVector2.dx.kmps, -1.1);
    EXPECT_DOUBLE_EQ(velocityVector2.dy.kmps, -1.2);
    EXPECT_DOUBLE_EQ(velocityVector2.dz.kmps, -1.3);
}


TEST(FSVelocityVectorTest, TwoTimesThreeKilometers_Is_SixKilometers) {
    double double1 = 3.;
    FSVelocityVector velocityVector2(2.1, -2.2, 2.3);

    FSVelocityVector velocityVector3 = double1 * velocityVector2;

    EXPECT_DOUBLE_EQ(velocityVector3.dx.kmps, 6.3);
    EXPECT_DOUBLE_EQ(velocityVector3.dy.kmps, -6.6);
    EXPECT_DOUBLE_EQ(velocityVector3.dz.kmps, 6.9);
}



TEST(FSVelocityVectorTest, TwoKilometersTimesThree_Is_SixKilometers) {
    FSVelocityVector velocityVector1(2.1, -2.2, 2.3);
    double double2 = 3.;

    FSVelocityVector velocityVector3 = velocityVector1 * double2;

    EXPECT_DOUBLE_EQ(velocityVector3.dx.kmps, 6.3);
    EXPECT_DOUBLE_EQ(velocityVector3.dy.kmps, -6.6);
    EXPECT_DOUBLE_EQ(velocityVector3.dz.kmps, 6.9);
}


TEST(FSVelocityVectorTest, SixKilometersDividedByThree_Is_TwoKilometers) {
    FSVelocityVector velocityVector1(6.3, -6.6, -6.9);
    double double2 = 3.;

    FSVelocityVector velocityVector3 = velocityVector1 / double2;

    EXPECT_DOUBLE_EQ(velocityVector3.dx.kmps, 2.1);
    EXPECT_DOUBLE_EQ(velocityVector3.dy.kmps, -2.2);
    EXPECT_DOUBLE_EQ(velocityVector3.dz.kmps, -2.3);
}


TEST(FSVelocityVectorTest, OnePlusEqualsTwo_Is_Three) {
    FSVelocityVector velocityVector1(1.1, 1.2, 1.3);
    FSVelocityVector velocityVector2(2.1, -2.2, 2.3);

    velocityVector1 += velocityVector2;

    EXPECT_DOUBLE_EQ(velocityVector1.dx.kmps, 3.2);
    EXPECT_DOUBLE_EQ(velocityVector1.dy.kmps, -1.0);
    EXPECT_DOUBLE_EQ(velocityVector1.dz.kmps, 3.6);
}


TEST(FSVelocityVectorTest, OneMinusEqualsTwo_Is_NegativeOne) {
    FSVelocityVector velocityVector1(1.2, 1.4, 1.6);
    FSVelocityVector velocityVector2(2.1, 2.2, 2.3);

    velocityVector1 -= velocityVector2;

    EXPECT_DOUBLE_EQ(velocityVector1.dx.kmps, -0.9);
    EXPECT_DOUBLE_EQ(velocityVector1.dy.kmps, -0.8);
    EXPECT_DOUBLE_EQ(velocityVector1.dz.kmps, -0.7);
}


TEST(FSVelocityVectorTest, SixKilometersDividedByThreeKilometerVector_Is_TwoKilometers) {
    FSVelocityVector velocityVector1(6.3, -6.6, -6.4);
    FSVelocityVector velocityVector2(3, -2.2, 2);

    FSDimensionlessVector vector3 = velocityVector1 / velocityVector2;

    EXPECT_DOUBLE_EQ(vector3.x, 2.1);
    EXPECT_DOUBLE_EQ(vector3.y, 3);
    EXPECT_DOUBLE_EQ(vector3.z, -3.2);
}


TEST(FSVelocityVectorTest, TwoEqualsTwo_Is_True) {
    FSVelocityVector velocityVector1(2.1, -2.3, -2.7);
    FSVelocityVector velocityVector2(2.1, -2.3, -2.7);

    bool equals = velocityVector1 == velocityVector2;

    EXPECT_EQ(equals, true);
}

TEST(FSVelocityVectorTest, TwoEqualsThreeX_Is_False) {
    FSVelocityVector velocityVector1(2.1, -2.3, -2.7);
    FSVelocityVector velocityVector2(2.15, -2.3, -2.7);

    bool equals = velocityVector1 == velocityVector2;

    EXPECT_EQ(equals, false);
}

TEST(FSVelocityVectorTest, TwoEqualsThreeY_Is_False) {
    FSVelocityVector velocityVector1(2.1, -2.3, -2.7);
    FSVelocityVector velocityVector2(2.1, -2.35, -2.7);

    bool equals = velocityVector1 == velocityVector2;

    EXPECT_EQ(equals, false);
}


TEST(FSVelocityVectorTest, TwoEqualsThreeZ_Is_False) {
    FSVelocityVector velocityVector1(2.1, -2.3, -2.7);
    FSVelocityVector velocityVector2(2.1, -2.3, -2.75);

    bool equals = velocityVector1 == velocityVector2;

    EXPECT_EQ(equals, false);
}


TEST(FSVelocityVectorTest, TwoNotEqualsTwo_Is_False) {
    FSVelocityVector velocityVector1(2.1, -2.3, -2.7);
    FSVelocityVector velocityVector2(2.1, -2.3, -2.7);

    bool notequals = velocityVector1 != velocityVector2;

    EXPECT_EQ(notequals, false);
}

TEST(FSVelocityVectorTest, TwoNotEqualsThreeX_Is_True) {
    FSVelocityVector velocityVector1(2.1, -2.3, -2.7);
    FSVelocityVector velocityVector2(2.15, -2.3, -2.7);

    bool notequals = velocityVector1 != velocityVector2;

    EXPECT_EQ(notequals, true);
}

TEST(FSVelocityVectorTest, TwoNotEqualsThreeY_Is_True) {
    FSVelocityVector velocityVector1(2.1, -2.3, -2.7);
    FSVelocityVector velocityVector2(2.1, -2.35, -2.7);

    bool notequals = velocityVector1 != velocityVector2;

    EXPECT_EQ(notequals, true);
}


TEST(FSVelocityVectorTest, TwoNotEqualsThreeZ_Is_True) {
    FSVelocityVector velocityVector1(2.1, -2.3, -2.7);
    FSVelocityVector velocityVector2(2.1, -2.3, -2.75);

    bool notequals = velocityVector1 != velocityVector2;

    EXPECT_EQ(notequals, true);
}

