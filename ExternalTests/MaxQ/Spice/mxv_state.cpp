// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(mxv_state_test, DefaultsTestCase) {

    FSStateTransform m;
    FSStateVector statein, stateout;

    USpice::mxv_state(m, statein, stateout);

    EXPECT_DOUBLE_EQ(stateout.r.x.km, 0.);
    EXPECT_DOUBLE_EQ(stateout.r.y.km, 0.);
    EXPECT_DOUBLE_EQ(stateout.r.z.km, 0.);
    EXPECT_DOUBLE_EQ(stateout.v.dx.kmps, 0.);
    EXPECT_DOUBLE_EQ(stateout.v.dy.kmps, 0.);
    EXPECT_DOUBLE_EQ(stateout.v.dz.kmps, 0.);
}



TEST(mxv_state_test, ZeroMatrix_Is_ZeroState) {

    FSStateTransform m;
    FSStateVector statein, stateout;

    for (int i = 0; i < m.m.Num(); ++i)
    {
        m.m[i] = FSDimensionlessStateVector(FSDimensionlessVector::Zero, FSDimensionlessVector::Zero);
    }

    USpice::mxv_state(m, statein, stateout);

    EXPECT_DOUBLE_EQ(stateout.r.x.km, 0.);
    EXPECT_DOUBLE_EQ(stateout.r.y.km, 0.);
    EXPECT_DOUBLE_EQ(stateout.r.z.km, 0.);
    EXPECT_DOUBLE_EQ(stateout.v.dx.kmps, 0.);
    EXPECT_DOUBLE_EQ(stateout.v.dy.kmps, 0.);
    EXPECT_DOUBLE_EQ(stateout.v.dz.kmps, 0.);
}


TEST(mxv_state_test, ZeroState_Is_ZeroState) {

    FSStateTransform m = FSStateTransform::Identity;
    FSStateVector statein(FSDistanceVector::Zero, FSVelocityVector::Zero);
    FSStateVector stateout;

    USpice::mxv_state(m, statein, stateout);

    EXPECT_DOUBLE_EQ(stateout.r.x.km, 0.);
    EXPECT_DOUBLE_EQ(stateout.r.y.km, 0.);
    EXPECT_DOUBLE_EQ(stateout.r.z.km, 0.);
    EXPECT_DOUBLE_EQ(stateout.v.dx.kmps, 0.);
    EXPECT_DOUBLE_EQ(stateout.v.dy.kmps, 0.);
    EXPECT_DOUBLE_EQ(stateout.v.dz.kmps, 0.);
}


TEST(mxv_state_test, StateXp90_Is_Rotated) {

    FSStateTransform m = FSStateTransform::Identity;
    
    m.m.Init(FSDimensionlessStateVector(FSDimensionlessVector::Zero, FSDimensionlessVector::Zero), 6);
    m.m[0] = FSDimensionlessStateVector(FSDimensionlessVector(0, -1, 0), FSDimensionlessVector(0, 0, 0));
    m.m[1] = FSDimensionlessStateVector(FSDimensionlessVector(1, 0, 0), FSDimensionlessVector(0, 0, 0));
    m.m[2] = FSDimensionlessStateVector(FSDimensionlessVector(0, 0, 1), FSDimensionlessVector(0, 0, 0));
    m.m[3] = FSDimensionlessStateVector(FSDimensionlessVector(0, 0, 0), FSDimensionlessVector(0, -1, 0));
    m.m[4] = FSDimensionlessStateVector(FSDimensionlessVector(0, 0, 0), FSDimensionlessVector(1, 0, 0));
    m.m[5] = FSDimensionlessStateVector(FSDimensionlessVector(0, 0, 0), FSDimensionlessVector(0, 0, 1));

    FSStateVector statein(FSDistanceVector(1.5, -2.5, 3.5), FSVelocityVector(2.5, -3.5, 4.5));
    FSStateVector stateout;

    USpice::mxv_state(m, statein, stateout);

    EXPECT_DOUBLE_EQ(stateout.r.x.km, 2.5);
    EXPECT_DOUBLE_EQ(stateout.r.y.km, 1.5);
    EXPECT_DOUBLE_EQ(stateout.r.z.km, 3.5);
    EXPECT_DOUBLE_EQ(stateout.v.dx.kmps, 3.5);
    EXPECT_DOUBLE_EQ(stateout.v.dy.kmps, 2.5);
    EXPECT_DOUBLE_EQ(stateout.v.dz.kmps, 4.5);
}