// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSAngularVelocityTest, DefaultConstruction_Is_Zero) {
    FSAngularVelocity angularVelocity;

    EXPECT_DOUBLE_EQ(angularVelocity.x.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(angularVelocity.y.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(angularVelocity.z.radiansPerSecond, 0.);
}


TEST(FSAngularVelocityTest, StaticZero_Is_Zero) {
    EXPECT_DOUBLE_EQ(FSAngularVelocity::Zero.x.AsRadiansPerSecond(), 0.);
    EXPECT_DOUBLE_EQ(FSAngularVelocity::Zero.y.AsRadiansPerSecond(), 0.);
    EXPECT_DOUBLE_EQ(FSAngularVelocity::Zero.z.AsRadiansPerSecond(), 0.);
}

TEST(FSAngularVelocityTest, SpiceDoubleConstruction_Is_Set) {
    
    double av[3] = { -1.1, 2.1, 3.4 };

    FSAngularVelocity angularVelocity(av);

    EXPECT_DOUBLE_EQ(angularVelocity.x.radiansPerSecond, -1.1);
    EXPECT_DOUBLE_EQ(angularVelocity.y.radiansPerSecond, 2.1);
    EXPECT_DOUBLE_EQ(angularVelocity.z.radiansPerSecond, 3.4);
}

TEST(FSAngularVelocityTest, AngularRateConstruction_Is_Set) {

    FSAngularRate av1(-1.1), av2(2.1), av3(3.4);

    FSAngularVelocity angularVelocity(av1, av2, av3);

    EXPECT_DOUBLE_EQ(angularVelocity.x.radiansPerSecond, -1.1);
    EXPECT_DOUBLE_EQ(angularVelocity.y.radiansPerSecond, 2.1);
    EXPECT_DOUBLE_EQ(angularVelocity.z.radiansPerSecond, 3.4);
}

TEST(FSAngularVelocityTest, DimensionlessVectorConstruction_Is_Set) {

    FSDimensionlessVector vector(-1.1, 2.1, 3.4);

    FSAngularVelocity angularVelocity(vector);

    EXPECT_DOUBLE_EQ(angularVelocity.x.radiansPerSecond, -1.1);
    EXPECT_DOUBLE_EQ(angularVelocity.y.radiansPerSecond, 2.1);
    EXPECT_DOUBLE_EQ(angularVelocity.z.radiansPerSecond, 3.4);
}

TEST(FSAngularVelocityTest, AsDimensionlessVector_Is_Correct) {

    FSAngularVelocity angularVelocity(FSAngularRate(-1.1), FSAngularRate(2.1), FSAngularRate(3.4));

    FSDimensionlessVector vector(5, 5, 5);

    angularVelocity.AsDimensionlessVector(vector);

    EXPECT_DOUBLE_EQ(vector.x, -1.1);
    EXPECT_DOUBLE_EQ(vector.y, 2.1);
    EXPECT_DOUBLE_EQ(vector.z, 3.4);
}


TEST(FSAngularVelocityTest, CopyTo_Is_Correct) {

    double av[3] = { 2, 2, 2 };
    FSAngularVelocity angularVelocity(FSAngularRate(-1.1), FSAngularRate(2.1), FSAngularRate(3.4));

    angularVelocity.CopyTo(av);

    EXPECT_DOUBLE_EQ(av[0], -1.1);
    EXPECT_DOUBLE_EQ(av[1], 2.1);
    EXPECT_DOUBLE_EQ(av[2], 3.4);
}


TEST(FSAngularVelocityTest, SevenXNormalized_Is_X) {

    FSAngularVelocity angularVelocity(FSAngularRate(7.1), FSAngularRate(0), FSAngularRate(0));

    FSDimensionlessVector vector = angularVelocity.Normalized();


    EXPECT_DOUBLE_EQ(vector.x, 1.);
    EXPECT_DOUBLE_EQ(vector.y, 0.);
    EXPECT_DOUBLE_EQ(vector.z, 0.);
}

TEST(FSAngularVelocityTest, SevenXNormalizedSet_Is_X) {

    FSAngularVelocity angularVelocity(FSAngularRate(7.1), FSAngularRate(0), FSAngularRate(0));

    FSDimensionlessVector vector;
    angularVelocity.Normalized(vector);

    EXPECT_DOUBLE_EQ(vector.x, 1.);
    EXPECT_DOUBLE_EQ(vector.y, 0.);
    EXPECT_DOUBLE_EQ(vector.z, 0.);
}

TEST(FSAngularVelocityTest, SevenXMagnitude_Is_Seven) {

    FSAngularVelocity angularVelocity(FSAngularRate(7.1), FSAngularRate(0), FSAngularRate(0));

    FSAngularRate magnitude = angularVelocity.Magnitude();

    EXPECT_DOUBLE_EQ(magnitude.radiansPerSecond, 7.1);
}