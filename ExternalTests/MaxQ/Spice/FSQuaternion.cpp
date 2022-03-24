// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


static const double v1 = 1.5, v2 = -2.5, v3 = 3.5, v4 = -4.5, v5 = 5.5;

TEST(FSQuaternionTest, DefaultConstruction_Is_Initialized) {
    FSQuaternion quaternion;

    EXPECT_DOUBLE_EQ(quaternion.w, 1.);
    EXPECT_DOUBLE_EQ(quaternion.x, 0.);
    EXPECT_DOUBLE_EQ(quaternion.y, 0.);
    EXPECT_DOUBLE_EQ(quaternion.z, 0.);
}

TEST(FSQuaternionTest, Identity_Is_Initialized) {
    FSQuaternion quaternion;

    EXPECT_DOUBLE_EQ(FSQuaternion::Identity.w, 1.);
    EXPECT_DOUBLE_EQ(FSQuaternion::Identity.x, 0.);
    EXPECT_DOUBLE_EQ(FSQuaternion::Identity.y, 0.);
    EXPECT_DOUBLE_EQ(FSQuaternion::Identity.z, 0.);
}

TEST(FSQuaternionTest, DefaultConstructor_Is_Correct) {

    FSQuaternion quaternion (v1, v2, v3, v4);

    EXPECT_DOUBLE_EQ(quaternion.w, v1);
    EXPECT_DOUBLE_EQ(quaternion.x, v2);
    EXPECT_DOUBLE_EQ(quaternion.y, v3);
    EXPECT_DOUBLE_EQ(quaternion.z, v4);
}

TEST(FSQuaternionTest, DoubleConstructor_Is_Correct) {

    double q[4];
    q[0] = v4;
    q[1] = v1;
    q[2] = v2;
    q[3] = v3;

    FSQuaternion quaternion(q);

    EXPECT_DOUBLE_EQ(quaternion.w, v4);
    EXPECT_DOUBLE_EQ(quaternion.x, v1);
    EXPECT_DOUBLE_EQ(quaternion.y, v2);
    EXPECT_DOUBLE_EQ(quaternion.z, v3);
}

TEST(FSQuaternionTest, DoubleCopy_Is_Correct) {

    double q[4];
    q[0] = v5;
    q[1] = v5;
    q[2] = v5;
    q[3] = v5;

    FSQuaternion quaternion(v1, v2, v3, v4);

    quaternion.CopyTo(q);

    EXPECT_DOUBLE_EQ(v1, q[0]);
    EXPECT_DOUBLE_EQ(v2, q[1]);
    EXPECT_DOUBLE_EQ(v3, q[2]);
    EXPECT_DOUBLE_EQ(v4, q[3]);
}

TEST(FSQuaternionTest, SPICE_Is_Correct) {

    FSQuaternion q = FSQuaternion::SPICE(v1, v2, v3, v4);

    EXPECT_DOUBLE_EQ(v1, q.w);
    EXPECT_DOUBLE_EQ(v2, q.x);
    EXPECT_DOUBLE_EQ(v3, q.y);
    EXPECT_DOUBLE_EQ(v4, q.z);
}

TEST(FSQuaternionTest, ENG_Is_Correct) {

    FSQuaternion q = FSQuaternion::ENG(v1, v2, v3, v4);

    EXPECT_DOUBLE_EQ(v1, q.w);
    EXPECT_DOUBLE_EQ(-v2, q.x);
    EXPECT_DOUBLE_EQ(-v3, q.y);
    EXPECT_DOUBLE_EQ(-v4, q.z);
}


TEST(FSQuaternionTest, QSPICE_Is_Correct) {

    FSQuaternion q(v1, v2, v3, v4);

    double w = 1., x = 1., y = 1., z = 1.;
    q.QSPICE(w, x, y, z);

    EXPECT_DOUBLE_EQ(v1, w);
    EXPECT_DOUBLE_EQ(v2, x);
    EXPECT_DOUBLE_EQ(v3, y);
    EXPECT_DOUBLE_EQ(v4, z);
}

TEST(FSQuaternionTest, QENG_Is_Correct) {

    FSQuaternion q(v1, v2, v3, v4);

    double w = 1., x = 1., y = 1., z = 1.;
    q.QENG(w, x, y, z);

    EXPECT_DOUBLE_EQ(v1, w);
    EXPECT_DOUBLE_EQ(-v2, x);
    EXPECT_DOUBLE_EQ(-v3, y);
    EXPECT_DOUBLE_EQ(-v4, z);
}
