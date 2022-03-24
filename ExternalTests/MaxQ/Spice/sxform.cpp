// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(sxform_test, DefaultsTestCase) {
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSStateTransform stateTransform; 
    FSEphemerisTime et;
    FString from;
    FString to;

    USpice::sxform(ResultCode, ErrorMessage, stateTransform, et, from, to);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);

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



TEST(sxform_test, Earth_Was_Turning) {
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    USpice::init_all();

    USpice::furnsh_absolute("naif0008.tls");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    USpice::furnsh_absolute("cpck05Mar2004.tpc");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSEphemerisTime et;
    USpice::str2et(ResultCode, ErrorMessage, et, TEXT("2004 JUN 11 12:00:00.000"));

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSStateTransform stateTransform;
    FString from = TEXT("J2000");
    FString to = TEXT("IAU_EARTH");

    USpice::sxform(ResultCode, ErrorMessage, stateTransform, et, from, to);

    EXPECT_NE(ResultCode, ES_ResultCode::Error);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    EXPECT_EQ(stateTransform.m.Num(), 6);
    for (int i = 0; i < stateTransform.m.Num(); ++i)
    {
        EXPECT_NE(stateTransform.m[i].r.x, 0.);
        EXPECT_NE(stateTransform.m[i].r.y, 0.);
        EXPECT_NE(stateTransform.m[i].r.z, 0.);

        if (i < 3)
        {
            EXPECT_DOUBLE_EQ(stateTransform.m[i].dr.x, 0.);
            EXPECT_DOUBLE_EQ(stateTransform.m[i].dr.y, 0.);
            EXPECT_DOUBLE_EQ(stateTransform.m[i].dr.z, 0.);
        }
        else
        {
            EXPECT_NE(stateTransform.m[i].dr.x, 0.);
            EXPECT_NE(stateTransform.m[i].dr.y, 0.);
            EXPECT_NE(stateTransform.m[i].dr.z, 0.);
        }
    }
}