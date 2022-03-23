// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(m2q_test, DefaultsTestCase) {

    ES_ResultCode ResultCode = ES_ResultCode::Error;
    FString ErrorMessage;

    FSRotationMatrix m;
    FSQuaternion q;

    USpice::m2q(ResultCode, ErrorMessage, m, q);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    EXPECT_DOUBLE_EQ(q.w, 1.);
    EXPECT_DOUBLE_EQ(q.x, 0.);
    EXPECT_DOUBLE_EQ(q.y, 0.);
    EXPECT_DOUBLE_EQ(q.z, 0.);
}


TEST(m2q_test, ZeroMatrix_Is_Error) {

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSRotationMatrix m;
    FSQuaternion q;

    m.m[0] = FSDimensionlessVector(0, 0, 0);
    m.m[1] = FSDimensionlessVector(0, 0, 0);
    m.m[2] = FSDimensionlessVector(0, 0, 0);

    USpice::m2q(ResultCode, ErrorMessage, m, q);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_TRUE(ErrorMessage.Len() > 0);

    EXPECT_DOUBLE_EQ(q.w, 1.);
    EXPECT_DOUBLE_EQ(q.x, 0.);
    EXPECT_DOUBLE_EQ(q.y, 0.);
    EXPECT_DOUBLE_EQ(q.z, 0.);
}

TEST(m2q_test, Identity_Is_Correct) {

    ES_ResultCode ResultCode = ES_ResultCode::Error;
    FString ErrorMessage;

    FSRotationMatrix m;
    FSQuaternion q;

    m.m[0] = FSDimensionlessVector(1, 0, 0);
    m.m[1] = FSDimensionlessVector(0, 1, 0);
    m.m[2] = FSDimensionlessVector(0, 0, 1);

    USpice::m2q(ResultCode, ErrorMessage, m, q);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    EXPECT_DOUBLE_EQ(q.w, 1.);
    EXPECT_DOUBLE_EQ(q.x, 0.);
    EXPECT_DOUBLE_EQ(q.y, 0.);
    EXPECT_DOUBLE_EQ(q.z, 0.);
}


TEST(m2q_test, Xp90_Is_Correct) {

    ES_ResultCode ResultCode = ES_ResultCode::Error;
    FString ErrorMessage;

    FSRotationMatrix m;
    FSQuaternion q;

    m.m[0] = FSDimensionlessVector( 1,  0,  0);
    m.m[1] = FSDimensionlessVector( 0,  0, -1);
    m.m[2] = FSDimensionlessVector( 0,  1,  0);

    USpice::m2q(ResultCode, ErrorMessage, m, q);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    const double invsqrt2 = 1./sqrt(2);
    EXPECT_NEAR(q.w, invsqrt2, 0.00000001);
    EXPECT_NEAR(q.x, invsqrt2, 0.00000001);
    EXPECT_DOUBLE_EQ(q.y, 0.);
    EXPECT_DOUBLE_EQ(q.z, 0.);
}


TEST(m2q_test, Yp90_Is_Correct) {

    ES_ResultCode ResultCode = ES_ResultCode::Error;
    FString ErrorMessage;

    FSRotationMatrix m;
    FSQuaternion q;

    m.m[0] = FSDimensionlessVector( 0, 0,  1);
    m.m[1] = FSDimensionlessVector( 0, 1,  0);
    m.m[2] = FSDimensionlessVector(-1, 0,  0);

    USpice::m2q(ResultCode, ErrorMessage, m, q);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    const double invsqrt2 = 1. / sqrt(2);
    EXPECT_NEAR(q.w, invsqrt2, 0.00000001);
    EXPECT_DOUBLE_EQ(q.x, 0.);
    EXPECT_NEAR(q.y, invsqrt2, 0.00000001);
    EXPECT_DOUBLE_EQ(q.z, 0.);
}


TEST(m2q_test, Zp90_Is_Correct) {

    ES_ResultCode ResultCode = ES_ResultCode::Error;
    FString ErrorMessage;

    FSRotationMatrix m;
    FSQuaternion q;

    m.m[0] = FSDimensionlessVector(0, -1, 0);
    m.m[1] = FSDimensionlessVector(1, 0, 0);
    m.m[2] = FSDimensionlessVector(0, 0, 1);

    USpice::m2q(ResultCode, ErrorMessage, m, q);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    const double invsqrt2 = 1. / sqrt(2);
    EXPECT_NEAR(q.w, invsqrt2, 0.00000001);
    EXPECT_DOUBLE_EQ(q.x, 0.);
    EXPECT_DOUBLE_EQ(q.y, 0.);
    EXPECT_NEAR(q.z, invsqrt2, 0.00000001);
}

TEST(m2q_test, NonRotation_Is_Error) {

    ES_ResultCode ResultCode = ES_ResultCode::Error;
    FString ErrorMessage;

    FSRotationMatrix m;
    FSQuaternion q;

    m.m[0] = FSDimensionlessVector(1, -1,  0);
    m.m[1] = FSDimensionlessVector(1,  0,  0);
    m.m[2] = FSDimensionlessVector(0,  0,  1);

    USpice::m2q(ResultCode, ErrorMessage, m, q);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);

    EXPECT_DOUBLE_EQ(q.w, 1.);
    EXPECT_DOUBLE_EQ(q.x, 0.);
    EXPECT_DOUBLE_EQ(q.y, 0.);
    EXPECT_DOUBLE_EQ(q.z, 0.);
}


TEST(m2q_test, Scaling_Is_Error) {

    ES_ResultCode ResultCode = ES_ResultCode::Error;
    FString ErrorMessage;

    FSRotationMatrix m;
    FSQuaternion q;

    m.m[0] = FSDimensionlessVector(2, 0, 0);
    m.m[1] = FSDimensionlessVector(0, 2, 0);
    m.m[2] = FSDimensionlessVector(0, 0, 2);

    USpice::m2q(ResultCode, ErrorMessage, m, q);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);

    EXPECT_DOUBLE_EQ(q.w, 1.);
    EXPECT_DOUBLE_EQ(q.x, 0.);
    EXPECT_DOUBLE_EQ(q.y, 0.);
    EXPECT_DOUBLE_EQ(q.z, 0.);
}