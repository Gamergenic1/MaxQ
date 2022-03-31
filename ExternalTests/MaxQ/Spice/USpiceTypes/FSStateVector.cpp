// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSStateVectorTest, DefaultConstruction_Is_Initialized) {
    FSStateVector stateVector;

    EXPECT_DOUBLE_EQ(stateVector.r.x.km, 0.);
    EXPECT_DOUBLE_EQ(stateVector.r.y.km, 0.);
    EXPECT_DOUBLE_EQ(stateVector.r.z.km, 0.);
    EXPECT_DOUBLE_EQ(stateVector.v.dx.kmps, 0.);
    EXPECT_DOUBLE_EQ(stateVector.v.dy.kmps, 0.);
    EXPECT_DOUBLE_EQ(stateVector.v.dz.kmps, 0.);
}

TEST(FSStateVectorTest, SpiceArrayContstructor_Is_Initialized) {
    
    double state[6] = { 1.2, -2.3, 3.4, 4.5, 5.6, -6.7 };
    
    FSStateVector stateVector(state);

    EXPECT_DOUBLE_EQ(stateVector.r.x.km, 1.2);
    EXPECT_DOUBLE_EQ(stateVector.r.y.km, -2.3);
    EXPECT_DOUBLE_EQ(stateVector.r.z.km, 3.4);
    EXPECT_DOUBLE_EQ(stateVector.v.dx.kmps, 4.5);
    EXPECT_DOUBLE_EQ(stateVector.v.dy.kmps, 5.6);
    EXPECT_DOUBLE_EQ(stateVector.v.dz.kmps, -6.7);
}


TEST(FSStateVectorTest, DistanceVelocityContstructor_Is_Initialized) {

    FSDistanceVector position(1.2, -2.3, 3.4);
    FSVelocityVector velocity(4.5, 5.6, -6.7);

    FSStateVector stateVector(position, velocity);

    EXPECT_DOUBLE_EQ(stateVector.r.x.km, 1.2);
    EXPECT_DOUBLE_EQ(stateVector.r.y.km, -2.3);
    EXPECT_DOUBLE_EQ(stateVector.r.z.km, 3.4);
    EXPECT_DOUBLE_EQ(stateVector.v.dx.kmps, 4.5);
    EXPECT_DOUBLE_EQ(stateVector.v.dy.kmps, 5.6);
    EXPECT_DOUBLE_EQ(stateVector.v.dz.kmps, -6.7);
}


TEST(FSStateVectorTest, CopyConstructor_Is_Initialized) {

    FSDistanceVector position(1.2, -2.3, 3.4);
    FSVelocityVector velocity(4.5, 5.6, -6.7);

    FSStateVector stateVector1(position, velocity);
    FSStateVector stateVector2(stateVector1);
    
    stateVector1.r = FSDistanceVector::Zero;
    stateVector1.v = FSVelocityVector::Zero;

    EXPECT_DOUBLE_EQ(stateVector2.r.x.km, 1.2);
    EXPECT_DOUBLE_EQ(stateVector2.r.y.km, -2.3);
    EXPECT_DOUBLE_EQ(stateVector2.r.z.km, 3.4);
    EXPECT_DOUBLE_EQ(stateVector2.v.dx.kmps, 4.5);
    EXPECT_DOUBLE_EQ(stateVector2.v.dy.kmps, 5.6);
    EXPECT_DOUBLE_EQ(stateVector2.v.dz.kmps, -6.7);
}


TEST(FSStateVectorTest, CopyTo_Sets_Kilometers) {

    FSDistanceVector position(1.2, -2.3, 3.4);
    FSVelocityVector velocity(4.5, 5.6, -6.7);

    FSStateVector stateVector(position, velocity);

    double state[6] = { 2., 2., 2., 2., 2., 2. };
    stateVector.CopyTo(state);

    EXPECT_DOUBLE_EQ(state[0], 1.2);
    EXPECT_DOUBLE_EQ(state[1], -2.3);
    EXPECT_DOUBLE_EQ(state[2], 3.4);
    EXPECT_DOUBLE_EQ(state[3], 4.5);
    EXPECT_DOUBLE_EQ(state[4], 5.6);
    EXPECT_DOUBLE_EQ(state[5], -6.7);
}


TEST(FSStateVectorTest, TwoEqualsTwo_Is_True) {
    FSDistanceVector position1(1.2, -2.3, 3.4);
    FSVelocityVector velocity1(4.5, 5.6, -6.7);

    FSStateVector stateVector1(position1, velocity1);
    FSStateVector stateVector2(position1, velocity1);

    bool equals = stateVector1 == stateVector2;

    EXPECT_EQ(equals, true);
}

TEST(FSStateVectorTest, TwoEqualsThreeX_Is_False) {
    FSDistanceVector position1(1.2, -2.3, 3.4);
    FSVelocityVector velocity1(4.5, 5.6, -6.7);

    FSStateVector stateVector1(position1, velocity1);

    position1.x.km += 0.01;
    FSStateVector stateVector2(position1, velocity1);

    bool equals = stateVector1 == stateVector2;

    EXPECT_EQ(equals, false);
}

TEST(FSStateVectorTest, TwoEqualsThreeY_Is_False) {
    FSDistanceVector position1(1.2, -2.3, 3.4);
    FSVelocityVector velocity1(4.5, 5.6, -6.7);

    FSStateVector stateVector1(position1, velocity1);

    velocity1.dz.kmps += 0.01;
    FSStateVector stateVector2(position1, velocity1);

    bool equals = stateVector1 == stateVector2;

    EXPECT_EQ(equals, false);
}


TEST(FSStateVectorTest, TwoNotEqualsTwo_Is_False) {
    FSDistanceVector position1(1.2, -2.3, 3.4);
    FSVelocityVector velocity1(4.5, 5.6, -6.7);

    FSStateVector stateVector1(position1, velocity1);
    FSStateVector stateVector2(position1, velocity1);

    bool notequals = stateVector1 != stateVector2;

    EXPECT_EQ(notequals, false);
}

TEST(FSStateVectorTest, TwoNotEqualsThreeX_Is_True) {
    FSDistanceVector position1(1.2, -2.3, 3.4);
    FSVelocityVector velocity1(4.5, 5.6, -6.7);

    FSStateVector stateVector1(position1, velocity1);

    position1.x.km += 0.01;
    FSStateVector stateVector2(position1, velocity1);

    bool notequals = stateVector1 != stateVector2;

    EXPECT_EQ(notequals, true);
}

TEST(FSStateVectorTest, TwoNotEqualsThreeY_Is_True) {
    FSDistanceVector position1(1.2, -2.3, 3.4);
    FSVelocityVector velocity1(4.5, 5.6, -6.7);

    FSStateVector stateVector1(position1, velocity1);

    velocity1.dz.kmps += 0.01;
    FSStateVector stateVector2(position1, velocity1);

    bool notequals = stateVector1 != stateVector2;

    EXPECT_EQ(notequals, true);
}


TEST(FSStateVectorTest, OnePlusTwo_Is_Three) {
    FSDistanceVector position1(1.2, -1.3, 1.4);
    FSVelocityVector velocity1(1.3, 1.4, -1.2);

    FSStateVector stateVector1(position1, velocity1);


    FSDistanceVector position2(2.2, -2.3, 3.4);
    FSVelocityVector velocity2(2.5, 2.3, -2.2);
    FSStateVector stateVector2(position2, velocity2);

    FSStateVector stateVector3 = stateVector1 + stateVector2;

    EXPECT_DOUBLE_EQ(stateVector3.r.x.km, 3.4);
    EXPECT_DOUBLE_EQ(stateVector3.r.y.km, -3.6);
    EXPECT_DOUBLE_EQ(stateVector3.r.z.km, 4.8);
    EXPECT_DOUBLE_EQ(stateVector3.v.dx.kmps, 3.8);
    EXPECT_DOUBLE_EQ(stateVector3.v.dy.kmps, 3.7);
    EXPECT_DOUBLE_EQ(stateVector3.v.dz.kmps, -3.4);
}



TEST(FSStateVectorTest, OneMinusTwo_Is_NegativeOne) {
    FSDistanceVector position1(1.2, -1.3, 1.4);
    FSVelocityVector velocity1(1.3, 1.4, -1.2);

    FSStateVector stateVector1(position1, velocity1);


    FSDistanceVector position2(2.2, -2.3, 3.4);
    FSVelocityVector velocity2(2.5, 2.3, -2.2);
    FSStateVector stateVector2(position2, velocity2);

    FSStateVector stateVector3 = stateVector1 - stateVector2;

    EXPECT_DOUBLE_EQ(stateVector3.r.x.km, 1.2 - 2.2);
    EXPECT_DOUBLE_EQ(stateVector3.r.y.km, -1.3 - -2.3);
    EXPECT_DOUBLE_EQ(stateVector3.r.z.km, 1.4 - 3.4);
    EXPECT_DOUBLE_EQ(stateVector3.v.dx.kmps, 1.3 - 2.5);
    EXPECT_DOUBLE_EQ(stateVector3.v.dy.kmps, 1.4 - 2.3);
    EXPECT_DOUBLE_EQ(stateVector3.v.dz.kmps, -1.2 - -2.2);
}


TEST(FSStateVectorTest, OneNegated_Is_NegativeOne) {
    FSDistanceVector position1(1.2, -1.3, 1.4);
    FSVelocityVector velocity1(1.3, 1.4, -1.2);

    FSStateVector stateVector1(position1, velocity1);


    FSStateVector stateVector2 = -stateVector1;

    EXPECT_DOUBLE_EQ(stateVector2.r.x.km, -1.2);
    EXPECT_DOUBLE_EQ(stateVector2.r.y.km, +1.3);
    EXPECT_DOUBLE_EQ(stateVector2.r.z.km, -1.4);
    EXPECT_DOUBLE_EQ(stateVector2.v.dx.kmps, -1.3);
    EXPECT_DOUBLE_EQ(stateVector2.v.dy.kmps, -1.4);
    EXPECT_DOUBLE_EQ(stateVector2.v.dz.kmps, +1.2);
}


TEST(FSStateVectorTest, OnePlusEqualsTwo_Is_Three) {
    FSDistanceVector position1(1.2, -1.3, 1.4);
    FSVelocityVector velocity1(1.3, 1.4, -1.2);

    FSStateVector stateVector1(position1, velocity1);


    FSDistanceVector position2(2.2, -2.3, 3.4);
    FSVelocityVector velocity2(2.5, 2.3, -2.2);
    FSStateVector stateVector2(position2, velocity2);

    stateVector1 += stateVector2;

    EXPECT_DOUBLE_EQ(stateVector1.r.x.km, 3.4);
    EXPECT_DOUBLE_EQ(stateVector1.r.y.km, -3.6);
    EXPECT_DOUBLE_EQ(stateVector1.r.z.km, 4.8);
    EXPECT_DOUBLE_EQ(stateVector1.v.dx.kmps, 3.8);
    EXPECT_DOUBLE_EQ(stateVector1.v.dy.kmps, 3.7);
    EXPECT_DOUBLE_EQ(stateVector1.v.dz.kmps, -3.4);
}



TEST(FSStateVectorTest, OneMinusEqualsTwo_Is_NegativeOne) {
    FSDistanceVector position1(1.2, -1.3, 1.4);
    FSVelocityVector velocity1(1.3, 1.4, -1.2);

    FSStateVector stateVector1(position1, velocity1);


    FSDistanceVector position2(2.2, -2.3, 3.4);
    FSVelocityVector velocity2(2.5, 2.3, -2.2);
    FSStateVector stateVector2(position2, velocity2);

    stateVector1 -= stateVector2;

    EXPECT_DOUBLE_EQ(stateVector1.r.x.km, 1.2 - 2.2);
    EXPECT_DOUBLE_EQ(stateVector1.r.y.km, -1.3 - -2.3);
    EXPECT_DOUBLE_EQ(stateVector1.r.z.km, 1.4 - 3.4);
    EXPECT_DOUBLE_EQ(stateVector1.v.dx.kmps, 1.3 - 2.5);
    EXPECT_DOUBLE_EQ(stateVector1.v.dy.kmps, 1.4 - 2.3);
    EXPECT_DOUBLE_EQ(stateVector1.v.dz.kmps, -1.2 - -2.2);
}
