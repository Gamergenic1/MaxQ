// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSDistanceVectorTest, DefaultConstruction_Is_Initialized) {
    FSDistanceVector distanceVector;

    EXPECT_DOUBLE_EQ(distanceVector.x.km, 0.);
    EXPECT_DOUBLE_EQ(distanceVector.y.km, 0.);
    EXPECT_DOUBLE_EQ(distanceVector.z.km, 0.);
}

TEST(FSDistanceVectorTest, Zero_Is_Zero) {

    EXPECT_DOUBLE_EQ(FSDistanceVector::Zero.x.km, 0.);
    EXPECT_DOUBLE_EQ(FSDistanceVector::Zero.y.km, 0.);
    EXPECT_DOUBLE_EQ(FSDistanceVector::Zero.z.km, 0.);
}

TEST(FSDistanceVectorTest, SpiceDoubleConstruction_Sets_Kilometers) {
    FSDistanceVector distanceVector(1.1, 2.2, 3.3);

    EXPECT_DOUBLE_EQ(distanceVector.x.km, 1.1);
    EXPECT_DOUBLE_EQ(distanceVector.y.km, 2.2);
    EXPECT_DOUBLE_EQ(distanceVector.z.km, 3.3);
}


TEST(FSDistanceVectorTest, DistanceConstruction_Sets_Kilometers) {
    FSDistanceVector distanceVector(FSDistance(1.1), FSDistance(2.2), FSDistance(3.3));

    EXPECT_DOUBLE_EQ(distanceVector.x.km, 1.1);
    EXPECT_DOUBLE_EQ(distanceVector.y.km, 2.2);
    EXPECT_DOUBLE_EQ(distanceVector.z.km, 3.3);
}


TEST(FSDistanceVectorTest, SpiceDoubleArrayConstruction_Sets_Kilometers) {
    double xyz[3] = { 1.1, 2.2, 3.3 };

    FSDistanceVector distanceVector(xyz);

    EXPECT_DOUBLE_EQ(distanceVector.x.km, 1.1);
    EXPECT_DOUBLE_EQ(distanceVector.y.km, 2.2);
    EXPECT_DOUBLE_EQ(distanceVector.z.km, 3.3);
}

TEST(FSDistanceVectorTest, CopyConstructor_Sets_Kilometers) {
    FSDistanceVector distanceVector1;

    distanceVector1.x.km = 1.1;
    distanceVector1.y.km = 2.2;
    distanceVector1.z.km = 3.3;
    
    FSDistanceVector distanceVector2(distanceVector1);

    EXPECT_DOUBLE_EQ(distanceVector2.x.km, 1.1);
    EXPECT_DOUBLE_EQ(distanceVector2.y.km, 2.2);
    EXPECT_DOUBLE_EQ(distanceVector2.z.km, 3.3);
}


TEST(FSDistanceVectorTest, AsDimensionlessVector_Sets_ValuesAsKilometers) {
    FSDistanceVector distanceVector1;

    distanceVector1.x = 1.1;
    distanceVector1.y = 2.2;
    distanceVector1.z = 3.3;

    FSDimensionlessVector dimensionlessVector2;

    distanceVector1.AsDimensionlessVector(dimensionlessVector2);

    EXPECT_DOUBLE_EQ(dimensionlessVector2.x, 1.1);
    EXPECT_DOUBLE_EQ(dimensionlessVector2.y, 2.2);
    EXPECT_DOUBLE_EQ(dimensionlessVector2.z, 3.3);
}


TEST(FSDistanceVectorTest, CopyTo_Sets_SpiceDoublesAsKilometerValues) {
    FSDistanceVector distanceVector;

    distanceVector.x = 1.1;
    distanceVector.y = 2.2;
    distanceVector.z = 3.3;

    double xyz[3] = { -7.7, 1.2, 1.3 };

    distanceVector.CopyTo(xyz);

    EXPECT_DOUBLE_EQ(xyz[0], 1.1);
    EXPECT_DOUBLE_EQ(xyz[1], 2.2);
    EXPECT_DOUBLE_EQ(xyz[2], 3.3);
}


TEST(FSDistanceVectorTest, SevenXReturnedNormalized_Is_OneX) {
    FSDistanceVector distanceVector1;

    distanceVector1.x = 7.0;
    distanceVector1.y = 0.0;
    distanceVector1.z = 0.0;

    FSDimensionlessVector distanceVector2 = distanceVector1.Normalized();


    EXPECT_DOUBLE_EQ(distanceVector2.x, 1.);
    EXPECT_DOUBLE_EQ(distanceVector2.y, 0.);
    EXPECT_DOUBLE_EQ(distanceVector2.z, 0.);
}


TEST(FSDistanceVectorTest, SevenYReturnedNormalized_Is_OneY) {
    FSDistanceVector distanceVector1;

    distanceVector1.x = 0.0;
    distanceVector1.y = -7.0;
    distanceVector1.z = 0.0;

    FSDimensionlessVector distanceVector2 = distanceVector1.Normalized();


    EXPECT_DOUBLE_EQ(distanceVector2.x, 0.);
    EXPECT_DOUBLE_EQ(distanceVector2.y, -1.);
    EXPECT_DOUBLE_EQ(distanceVector2.z, 0.);
}

TEST(FSDistanceVectorTest, SevenZReturnedNormalized_Is_OneZ) {
    FSDistanceVector distanceVector1;

    distanceVector1.x = 0.0;
    distanceVector1.y = 0.0;
    distanceVector1.z = -7.0;

    FSDimensionlessVector distanceVector2 = distanceVector1.Normalized();


    EXPECT_DOUBLE_EQ(distanceVector2.x, 0.);
    EXPECT_DOUBLE_EQ(distanceVector2.y, 0.);
    EXPECT_DOUBLE_EQ(distanceVector2.z, -1.);
}

TEST(FSDistanceVectorTest, VectorReturnedNormalized_Is_Correct) {
    FSDistanceVector distanceVector1;

    distanceVector1.x = 2.0;
    distanceVector1.y = -3.0;
    distanceVector1.z = 4.0;

    FSDimensionlessVector distanceVector2 = distanceVector1.Normalized();

    double scale = 1. / sqrt(2 * 2 + 3 * 3 + 4 * 4);

    EXPECT_DOUBLE_EQ(distanceVector2.x, 2.0 * scale);
    EXPECT_DOUBLE_EQ(distanceVector2.y, -3.0 * scale);
    EXPECT_DOUBLE_EQ(distanceVector2.z, 4.0 * scale);
}

TEST(FSDistanceVectorTest, SevenXSetNormalized_Is_OneX) {
    FSDistanceVector distanceVector1;

    distanceVector1.x = 7.0;
    distanceVector1.y = 0.0;
    distanceVector1.z = 0.0;

    FSDimensionlessVector distanceVector2(10, 10, 10);
    distanceVector1.Normalized(distanceVector2);


    EXPECT_DOUBLE_EQ(distanceVector2.x, 1.);
    EXPECT_DOUBLE_EQ(distanceVector2.y, 0.);
    EXPECT_DOUBLE_EQ(distanceVector2.z, 0.);
}

TEST(FSDistanceVectorTest, SevenYSetNormalized_Is_OneY) {
    FSDistanceVector distanceVector1;

    distanceVector1.x = 0.0;
    distanceVector1.y = -7.0;
    distanceVector1.z = 0.0;

    FSDimensionlessVector distanceVector2(10, 10, 10);
    distanceVector1.Normalized(distanceVector2);

    EXPECT_DOUBLE_EQ(distanceVector2.x, 0.);
    EXPECT_DOUBLE_EQ(distanceVector2.y, -1.);
    EXPECT_DOUBLE_EQ(distanceVector2.z, 0.);
}

TEST(FSDistanceVectorTest, SevenZSetNormalized_Is_OneZ) {
    FSDistanceVector distanceVector1;

    distanceVector1.x = 0.0;
    distanceVector1.y = 0.0;
    distanceVector1.z = -7.0;

    FSDimensionlessVector distanceVector2(10, 10, 10);
    distanceVector1.Normalized(distanceVector2);

    EXPECT_DOUBLE_EQ(distanceVector2.x, 0.);
    EXPECT_DOUBLE_EQ(distanceVector2.y, 0.);
    EXPECT_DOUBLE_EQ(distanceVector2.z, -1.);
}

TEST(FSDistanceVectorTest, VectorSetNormalized_Is_Correct) {
    FSDistanceVector distanceVector1;

    distanceVector1.x = 2.0;
    distanceVector1.y = -3.0;
    distanceVector1.z = 4.0;

    FSDimensionlessVector distanceVector2(10, 10, 10);
    distanceVector1.Normalized(distanceVector2);

    double scale = 1. / sqrt(2 * 2 + 3 * 3 + 4 * 4);

    EXPECT_DOUBLE_EQ(distanceVector2.x, 2.0 * scale);
    EXPECT_DOUBLE_EQ(distanceVector2.y, -3.0 * scale);
    EXPECT_DOUBLE_EQ(distanceVector2.z, 4.0 * scale);
}


TEST(FSDistanceVectorTest, SevenXMagnitude_Is_OneX) {
    FSDistanceVector distanceVector1;

    distanceVector1.x = 7.0;
    distanceVector1.y = 0.0;
    distanceVector1.z = 0.0;

    FSDistance distance = distanceVector1.Magnitude();

    EXPECT_DOUBLE_EQ(distance.km, 7.);
}

TEST(FSDistanceVectorTest, SevenYMagnitude_Is_OneY) {
    FSDistanceVector distanceVector1;

    distanceVector1.x = 0.0;
    distanceVector1.y = -7.0;
    distanceVector1.z = 0.0;

    FSDistance distance = distanceVector1.Magnitude();

    EXPECT_DOUBLE_EQ(distance.km, 7.);
}

TEST(FSDistanceVectorTest, SevenZMagnitude_Is_OneZ) {
    FSDistanceVector distanceVector1;

    distanceVector1.x = 0.0;
    distanceVector1.y = 0.0;
    distanceVector1.z = -7.0;

    FSDistance distance = distanceVector1.Magnitude();

    EXPECT_DOUBLE_EQ(distance.km, 7.);
}

TEST(FSDistanceVectorTest, VectorMagnitude_Is_Correct) {
    FSDistanceVector distanceVector1;

    distanceVector1.x = 2.0;
    distanceVector1.y = -3.0;
    distanceVector1.z = 4.0;

    double magnitude = sqrt(2 * 2 + 3 * 3 + 4 * 4);

    FSDistance distance = distanceVector1.Magnitude();

    EXPECT_DOUBLE_EQ(distance.km, magnitude);
}

TEST(FSDistanceVectorTest, Re_Returns_X) {
    FSDistanceVector distanceVector1;

    distanceVector1.x = 2.0;
    distanceVector1.y = -3.0;
    distanceVector1.z = 4.0;

    FSDistance distance = distanceVector1.Re();

    EXPECT_DOUBLE_EQ(distance.km, 2.);
}


TEST(FSDistanceVectorTest, Rp_Returns_Z) {
    FSDistanceVector distanceVector1;

    distanceVector1.x = 2.0;
    distanceVector1.y = -3.0;
    distanceVector1.z = 4.0;

    FSDistance distance = distanceVector1.Rp();

    EXPECT_DOUBLE_EQ(distance.km, 4.);
}


TEST(FSDistanceVectorTest, f4x2_Returns_half) {
    FSDistanceVector distanceVector1;

    distanceVector1.x = 4.0;
    distanceVector1.y = -3.0;
    distanceVector1.z = 2.0;

    double f = distanceVector1.f();

    EXPECT_DOUBLE_EQ(f, 0.5);
}


TEST(FSDistanceVectorTest, OnePlusTwo_Is_Three) {
    FSDistanceVector distanceVector1(1.1, 1.2, 1.3);
    FSDistanceVector distanceVector2(2.1, 2.2, 2.3);

    FSDistanceVector distanceVector3 = distanceVector1 + distanceVector2;

    EXPECT_DOUBLE_EQ(distanceVector3.x.km, 3.2);
    EXPECT_DOUBLE_EQ(distanceVector3.y.km, 3.4);
    EXPECT_DOUBLE_EQ(distanceVector3.z.km, 3.6);
}


TEST(FSDistanceVectorTest, OneMinusTwo_Is_NegativeOne) {
    FSDistanceVector distanceVector1(1.2, 1.4, 1.6);
    FSDistanceVector distanceVector2(2.1, 2.2, 2.3);

    FSDistanceVector distanceVector3 = distanceVector1 - distanceVector2;

    EXPECT_DOUBLE_EQ(distanceVector3.x.km, -0.9);
    EXPECT_DOUBLE_EQ(distanceVector3.y.km, -0.8);
    EXPECT_DOUBLE_EQ(distanceVector3.z.km, -0.7);
}


TEST(FSDistanceVectorTest, OneNegated_Is_NegativeOne) {
    FSDistanceVector distanceVector1(1.1, 1.2, 1.3);

    FSDistanceVector distanceVector2 = -distanceVector1;

    EXPECT_DOUBLE_EQ(distanceVector2.x.km, -1.1);
    EXPECT_DOUBLE_EQ(distanceVector2.y.km, -1.2);
    EXPECT_DOUBLE_EQ(distanceVector2.z.km, -1.3);
}


TEST(FSDistanceVectorTest, TwoTimesThreeKilometers_Is_SixKilometers) {
    double double1 = 3.;
    FSDistanceVector distanceVector2(2.1, -2.2, 2.3);

    FSDistanceVector distanceVector3 = double1 * distanceVector2;

    EXPECT_DOUBLE_EQ(distanceVector3.x.km, 6.3);
    EXPECT_DOUBLE_EQ(distanceVector3.y.km, -6.6);
    EXPECT_DOUBLE_EQ(distanceVector3.z.km, 6.9);
}



TEST(FSDistanceVectorTest, TwoKilometersTimesThree_Is_SixKilometers) {
    FSDistanceVector distanceVector1(2.1, -2.2, 2.3);
    double double2 = 3.;

    FSDistanceVector distanceVector3 = distanceVector1 * double2;

    EXPECT_DOUBLE_EQ(distanceVector3.x.km, 6.3);
    EXPECT_DOUBLE_EQ(distanceVector3.y.km, -6.6);
    EXPECT_DOUBLE_EQ(distanceVector3.z.km, 6.9);
}


TEST(FSDistanceVectorTest, SixKilometersDividedByThree_Is_TwoKilometers) {
    FSDistanceVector distanceVector1(6.3, -6.6, -6.9);
    double double2 = 3.;

    FSDistanceVector distanceVector3 = distanceVector1 / double2;

    EXPECT_DOUBLE_EQ(distanceVector3.x.km, 2.1);
    EXPECT_DOUBLE_EQ(distanceVector3.y.km, -2.2);
    EXPECT_DOUBLE_EQ(distanceVector3.z.km, -2.3);
}


TEST(FSDistanceVectorTest, OnePlusEqualsTwo_Is_Three) {
    FSDistanceVector distanceVector1(1.1, 1.2, 1.3);
    FSDistanceVector distanceVector2(2.1, -2.2, 2.3);

    distanceVector1 += distanceVector2;

    EXPECT_DOUBLE_EQ(distanceVector1.x.km, 3.2);
    EXPECT_DOUBLE_EQ(distanceVector1.y.km, -1.0);
    EXPECT_DOUBLE_EQ(distanceVector1.z.km, 3.6);
}


TEST(FSDistanceVectorTest, OneMinusEqualsTwo_Is_NegativeOne) {
    FSDistanceVector distanceVector1(1.2, 1.4, 1.6);
    FSDistanceVector distanceVector2(2.1, 2.2, 2.3);

    distanceVector1 -= distanceVector2;

    EXPECT_DOUBLE_EQ(distanceVector1.x.km, -0.9);
    EXPECT_DOUBLE_EQ(distanceVector1.y.km, -0.8);
    EXPECT_DOUBLE_EQ(distanceVector1.z.km, -0.7);
}


TEST(FSDistanceVectorTest, SixKilometersDividedByThreeKilometerVector_Is_TwoKilometers) {
    FSDistanceVector distanceVector1(6.3, -6.6, -6.4);
    FSDistanceVector distanceVector2(3, -2.2, 2);

    FSDimensionlessVector vector3 = distanceVector1 / distanceVector2;

    EXPECT_DOUBLE_EQ(vector3.x, 2.1);
    EXPECT_DOUBLE_EQ(vector3.y, 3);
    EXPECT_DOUBLE_EQ(vector3.z, -3.2);
}


TEST(FSDistanceVectorTest, SixKilometersDividedByThreeKilometers_Is_TwoKilometers) {
    FSDistanceVector distanceVector1(6.3, -6.6, -6.9);
    FSDistance distance2 = 3.;

    FSDimensionlessVector vector3 = distanceVector1 / distance2;

    EXPECT_DOUBLE_EQ(vector3.x, 2.1);
    EXPECT_DOUBLE_EQ(vector3.y, -2.2);
    EXPECT_DOUBLE_EQ(vector3.z, -2.3);
}


TEST(FSDistanceVectorTest, TwoEqualsTwo_Is_True) {
    FSDistanceVector distanceVector1(2.1, -2.3, -2.7);
    FSDistanceVector distanceVector2(2.1, -2.3, -2.7);

    bool equals = distanceVector1 == distanceVector2;

    EXPECT_EQ(equals, true);
}

TEST(FSDistanceVectorTest, TwoEqualsThreeX_Is_False) {
    FSDistanceVector distanceVector1(2.1, -2.3, -2.7);
    FSDistanceVector distanceVector2(2.15, -2.3, -2.7);

    bool equals = distanceVector1 == distanceVector2;

    EXPECT_EQ(equals, false);
}

TEST(FSDistanceVectorTest, TwoEqualsThreeY_Is_False) {
    FSDistanceVector distanceVector1(2.1, -2.3, -2.7);
    FSDistanceVector distanceVector2(2.1, -2.35, -2.7);

    bool equals = distanceVector1 == distanceVector2;

    EXPECT_EQ(equals, false);
}


TEST(FSDistanceVectorTest, TwoEqualsThreeZ_Is_False) {
    FSDistanceVector distanceVector1(2.1, -2.3, -2.7);
    FSDistanceVector distanceVector2(2.1, -2.3, -2.75);

    bool equals = distanceVector1 == distanceVector2;

    EXPECT_EQ(equals, false);
}


TEST(FSDistanceVectorTest, TwoNotEqualsTwo_Is_False) {
    FSDistanceVector distanceVector1(2.1, -2.3, -2.7);
    FSDistanceVector distanceVector2(2.1, -2.3, -2.7);

    bool notequals = distanceVector1 != distanceVector2;

    EXPECT_EQ(notequals, false);
}

TEST(FSDistanceVectorTest, TwoNotEqualsThreeX_Is_True) {
    FSDistanceVector distanceVector1(2.1, -2.3, -2.7);
    FSDistanceVector distanceVector2(2.15, -2.3, -2.7);

    bool notequals = distanceVector1 != distanceVector2;

    EXPECT_EQ(notequals, true);
}

TEST(FSDistanceVectorTest, TwoNotEqualsThreeY_Is_True) {
    FSDistanceVector distanceVector1(2.1, -2.3, -2.7);
    FSDistanceVector distanceVector2(2.1, -2.35, -2.7);

    bool notequals = distanceVector1 != distanceVector2;

    EXPECT_EQ(notequals, true);
}


TEST(FSDistanceVectorTest, TwoNotEqualsThreeZ_Is_True) {
    FSDistanceVector distanceVector1(2.1, -2.3, -2.7);
    FSDistanceVector distanceVector2(2.1, -2.3, -2.75);

    bool notequals = distanceVector1 != distanceVector2;

    EXPECT_EQ(notequals, true);
}