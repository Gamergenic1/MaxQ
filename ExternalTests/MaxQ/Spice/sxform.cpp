// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"
#include "MaxQTestDefinitions.h"

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

    USpice::furnsh_absolute("maxq_unit_test_meta.tm");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSStateTransform stateTransform;
    FString from = TEXT("J2000");
    FString to = TEXT("IAU_FAKEBODY9994");

    // 90 degree rotation around +Z...
    FSEphemerisPeriod T = FSEphemerisPeriod::Day / 10.;
    FSAngularRate w = (_pos360_as_radians / T.AsSeconds());
    FSEphemerisTime et(FSEphemerisTime::J2000 + 0.25 * T);

    USpice::sxform(ResultCode, ErrorMessage, stateTransform, et, from, to);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);

    EXPECT_EQ(stateTransform.m.Num(), 6);


    EXPECT_LT((stateTransform.m[0].r - FSDistanceVector(0, 1, 0)).Magnitude().AsKilometers(), 0.0000001);
    EXPECT_LT((stateTransform.m[1].r - FSDistanceVector(-1, 0, 0)).Magnitude().AsKilometers(), 0.0000001);
    EXPECT_LT((stateTransform.m[2].r - FSDistanceVector(0, 0, 1)).Magnitude().AsKilometers(), 0.0000001);

    EXPECT_LT((stateTransform.m[3].r - FSDistanceVector(-w.AsRadiansPerSecond(), 0, 0)).Magnitude().AsKilometers(), 0.000000001);
    EXPECT_LT((stateTransform.m[4].r - FSDistanceVector(0, -w.AsRadiansPerSecond(), 0)).Magnitude().AsKilometers(), 0.000000001);
    EXPECT_LT((stateTransform.m[5].r - FSDistanceVector(0, 0, 0)).Magnitude().AsKilometers(), 0.000000001);


    EXPECT_LT((stateTransform.m[3].dr - FSVelocityVector(0, 1, 0)).Magnitude().AsKilometersPerSecond(), 0.0000001);
    EXPECT_LT((stateTransform.m[4].dr - FSVelocityVector(-1, 0, 0)).Magnitude().AsKilometersPerSecond(), 0.0000001);
    EXPECT_LT((stateTransform.m[5].dr - FSVelocityVector(0, 0, 1)).Magnitude().AsKilometersPerSecond(), 0.0000001);
}