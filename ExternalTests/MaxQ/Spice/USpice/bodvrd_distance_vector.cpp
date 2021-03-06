// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(bodvrd_distance_vector_test, DefaultsTestCase) {
    
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSDistanceVector ResultVector( 1., 2., 3.);

    FString Body, Item;

    USpice::bodvrd_distance_vector(
        ResultCode,
        ErrorMessage,
        ResultVector,
        Body,
        Item
    );

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);

    // Since the call should have failed, we expect the ResultVector to be unchanged...
    EXPECT_DOUBLE_EQ(ResultVector.x.km, 1.);
    EXPECT_DOUBLE_EQ(ResultVector.y.km, 2.);
    EXPECT_DOUBLE_EQ(ResultVector.z.km, 3.);
}

TEST(bodvrd_distance_vector_test, BODY9994_RADII_Is_Correct) {
    USpice::init_all();
    USpice::furnsh_absolute("maxq_unit_test_meta.tm");

    ES_ResultCode ResultCode = ES_ResultCode::Error;
    FString ErrorMessage;

    FSDistanceVector ResultVector(1., 2., 3.);

    FString Body = TEXT("FAKEBODY9994"), Item = TEXT("RADII");

    USpice::bodvrd_distance_vector(
        ResultCode,
        ErrorMessage,
        ResultVector,
        Body,
        Item
    );

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    // No mercy for ~=
    EXPECT_DOUBLE_EQ(ResultVector.x.km, 123.45);
    EXPECT_DOUBLE_EQ(ResultVector.y.km, 123.45);
    EXPECT_DOUBLE_EQ(ResultVector.z.km, 123.);
}

TEST(bodvrd_distance_vector_test, BODY9995_RADII_4D_Is_Error) {
    // BODY9998_RADII    = ( 12.34   56.78   91.0   11.12 )
    USpice::init_all();
    USpice::furnsh_absolute("maxq_unit_test_meta.tm");

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSDistanceVector ResultVector = FSDistanceVector(1., 2., 3.);

    FString Body = TEXT("9995"), Item = TEXT("BADVALUE4");

    USpice::bodvrd_distance_vector(
        ResultCode,
        ErrorMessage,
        ResultVector,
        Body,
        Item
    );

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);

    // No mercy for ~=
    EXPECT_DOUBLE_EQ(ResultVector.x.km, 1.);
    EXPECT_DOUBLE_EQ(ResultVector.y.km, 2.);
    EXPECT_DOUBLE_EQ(ResultVector.z.km, 3.);
}


TEST(bodvrd_distance_vector_test, BODY9995_GM_2D_Is_Error) {

    USpice::init_all();
    USpice::furnsh_absolute("maxq_unit_test_meta.tm");

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSDistanceVector ResultVector = FSDistanceVector(1., 2., 3.);

    FString Body = TEXT("9995"), Item = TEXT("BADVALUE2");

    USpice::bodvrd_distance_vector(
        ResultCode,
        ErrorMessage,
        ResultVector,
        Body,
        Item
    );

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);

    // No mercy for ~=
    EXPECT_DOUBLE_EQ(ResultVector.x.km, 2001.);
    EXPECT_DOUBLE_EQ(ResultVector.y.km, 2002.);
    EXPECT_DOUBLE_EQ(ResultVector.z.km, 3.);
}