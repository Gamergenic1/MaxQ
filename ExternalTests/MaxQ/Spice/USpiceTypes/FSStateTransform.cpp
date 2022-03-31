// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSStateTransformTest, DefaultConstruction_Is_Initialized) {
    FSStateTransform stateTransform;

    EXPECT_EQ(stateTransform.m.Num(), 6);

    for (int i = 0; i < stateTransform.m.Num(); ++i)
    {
        EXPECT_DOUBLE_EQ(stateTransform.m[i].r.x, i == 0 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform.m[i].r.y, i == 1 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform.m[i].r.z, i == 2 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform.m[i].dr.x, i == 3 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform.m[i].dr.y, i == 4 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform.m[i].dr.z, i == 5 ? 1. : 0.);
    }
}


TEST(FSStateTransformTest, Identity_Is_Identity) {
    EXPECT_EQ(FSStateTransform::Identity.m.Num(), 6);

    for (int i = 0; i < FSStateTransform::Identity.m.Num(); ++i)
    {
        EXPECT_DOUBLE_EQ(FSStateTransform::Identity.m[i].r.x, i == 0 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(FSStateTransform::Identity.m[i].r.y, i == 1 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(FSStateTransform::Identity.m[i].r.z, i == 2 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(FSStateTransform::Identity.m[i].dr.x, i == 3 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(FSStateTransform::Identity.m[i].dr.y, i == 4 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(FSStateTransform::Identity.m[i].dr.z, i == 5 ? 1. : 0.);
    }
}


TEST(FSStateTransformTest, Assignment_Is_Correct) {
    FSStateTransform stateTransform1;

    // Note:  Matrix is diagonal opposite of identity
    for (int i = 0; i < stateTransform1.m.Num(); ++i)
    {
        stateTransform1.m[i].r.x = i == 5 ? 1. : 0.;
        stateTransform1.m[i].r.y = i == 4 ? 1. : 0.;
        stateTransform1.m[i].r.z = i == 3 ? 1. : 0.;
        stateTransform1.m[i].dr.x = i == 2 ? 1. : 0.;
        stateTransform1.m[i].dr.y = i == 1 ? 1. : 0.;
        stateTransform1.m[i].dr.z = i == 0 ? 1. : 0.;
    }

    FSStateTransform stateTransform2 = stateTransform1;

    //
    stateTransform1.m[0] = FSDimensionlessStateVector(FSDimensionlessVector::Zero, FSDimensionlessVector::Zero);

    EXPECT_EQ(stateTransform2.m.Num(), 6);

    for (int i = 0; i < stateTransform2.m.Num(); ++i)
    {
        EXPECT_DOUBLE_EQ(stateTransform2.m[i].r.x, i == 5 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform2.m[i].r.y, i == 4 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform2.m[i].r.z, i == 3 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform2.m[i].dr.x, i == 2 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform2.m[i].dr.y, i == 1 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform2.m[i].dr.z, i == 0 ? 1. : 0.);
    }
}



TEST(FSStateTransformTest, CopyConstructor_Is_Correct) {
    FSStateTransform stateTransform1;

    // Note:  Matrix is diagonal opposite of identity
    for (int i = 0; i < stateTransform1.m.Num(); ++i)
    {
        stateTransform1.m[i].r.x = i == 5 ? 1. : 0.;
        stateTransform1.m[i].r.y = i == 4 ? 1. : 0.;
        stateTransform1.m[i].r.z = i == 3 ? 1. : 0.;
        stateTransform1.m[i].dr.x = i == 2 ? 1. : 0.;
        stateTransform1.m[i].dr.y = i == 1 ? 1. : 0.;
        stateTransform1.m[i].dr.z = i == 0 ? 1. : 0.;
    }

    FSStateTransform stateTransform2 = FSStateTransform(stateTransform1);

    //
    stateTransform1.m[0] = FSDimensionlessStateVector(FSDimensionlessVector::Zero, FSDimensionlessVector::Zero);

    EXPECT_EQ(stateTransform2.m.Num(), 6);

    for (int i = 0; i < stateTransform2.m.Num(); ++i)
    {
        EXPECT_DOUBLE_EQ(stateTransform2.m[i].r.x, i == 5 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform2.m[i].r.y, i == 4 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform2.m[i].r.z, i == 3 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform2.m[i].dr.x, i == 2 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform2.m[i].dr.y, i == 1 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(stateTransform2.m[i].dr.z, i == 0 ? 1. : 0.);
    }
}


TEST(FSStateTransformTest, stateTransform) {
    FSStateTransform stateTransform;

    // Note:  Matrix is diagonal opposite of identity
    for (int i = 0; i < stateTransform.m.Num(); ++i)
    {
        stateTransform.m[i].r.x = i == 5 ? 1. : 0.;
        stateTransform.m[i].r.y = i == 4 ? 1. : 0.;
        stateTransform.m[i].r.z = i == 3 ? 1. : 0.;
        stateTransform.m[i].dr.x = i == 2 ? 1. : 0.;
        stateTransform.m[i].dr.y = i == 1 ? 1. : 0.;
        stateTransform.m[i].dr.z = i == 0 ? 1. : 0.;
    }

    double _m[6][6];

    FPlatformMemory::Memset(_m, 0, sizeof(_m));

    stateTransform.CopyTo(_m);

    for (int i = 0; i < 6; ++i)
    {
        EXPECT_DOUBLE_EQ(_m[i][0], i == 5 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(_m[i][1], i == 4 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(_m[i][2], i == 3 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(_m[i][3], i == 2 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(_m[i][4], i == 1 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(_m[i][5], i == 0 ? 1. : 0.);
    }
}