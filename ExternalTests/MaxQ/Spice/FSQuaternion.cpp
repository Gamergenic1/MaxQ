// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "UE5HostDefs.h"
#include "SpiceHostDefs.h"

#include "Spice.h"
#include "SpiceTypes.h"

#include "gtest/gtest.h"

static const double v1 = 1.5, v2 = -2.5, v3 = 3.5, v4 = -4.5, v5 = 5.5;

TEST(FSQuaternionTest, DefaultConstruction_Is_Initialized) {
    FSQuaternion quaternion;

    EXPECT_EQ(quaternion.w, 1.);
    EXPECT_EQ(quaternion.x, 0.);
    EXPECT_EQ(quaternion.y, 0.);
    EXPECT_EQ(quaternion.z, 0.);
}


TEST(FSQuaternionTest, DefaultConstructor_Is_Correct) {

    FSQuaternion quaternion (v1, v2, v3, v4);

    EXPECT_EQ(quaternion.w, v1);
    EXPECT_EQ(quaternion.x, v2);
    EXPECT_EQ(quaternion.y, v3);
    EXPECT_EQ(quaternion.z, v4);
}

TEST(FSQuaternionTest, DoubleConstructor_Is_Correct) {

    double q[4];
    q[0] = v4;
    q[1] = v1;
    q[2] = v2;
    q[3] = v3;

    FSQuaternion quaternion(q);

    EXPECT_EQ(quaternion.w, v4);
    EXPECT_EQ(quaternion.x, v1);
    EXPECT_EQ(quaternion.y, v2);
    EXPECT_EQ(quaternion.z, v3);
}

TEST(FSQuaternionTest, DoubleCopy_Is_Correct) {

    double q[4];
    q[0] = v5;
    q[1] = v5;
    q[2] = v5;
    q[3] = v5;

    FSQuaternion quaternion(v1, v2, v3, v4);

    quaternion.CopyTo(q);

    EXPECT_EQ(v1, q[0]);
    EXPECT_EQ(v2, q[1]);
    EXPECT_EQ(v3, q[2]);
    EXPECT_EQ(v4, q[3]);
}

