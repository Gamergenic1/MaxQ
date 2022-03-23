// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(pxform_test, DefaultsTestCase) {
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSRotationMatrix rotationMatrix;
    FSEphemerisTime et;
    FString from;
    FString to;

    USpice::pxform(ResultCode, ErrorMessage, rotationMatrix, et, from, to);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);

    EXPECT_EQ(rotationMatrix.m.Num(), 3);
    for (int i = 0; i < rotationMatrix.m.Num(); ++i)
    {
        EXPECT_DOUBLE_EQ(rotationMatrix.m[i].x, i == 0 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(rotationMatrix.m[i].y, i == 1 ? 1. : 0.);
        EXPECT_DOUBLE_EQ(rotationMatrix.m[i].z, i == 2 ? 1. : 0.);
    }
}