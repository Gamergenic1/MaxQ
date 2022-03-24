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

TEST(bodvrd_distance_vector_test, BODY9999_RADII_Is_Correct) {
    // BODY9999_RADII    = ( 12.34   56.78   91.01112 )
    USpice::init_all();
    USpice::furnsh_absolute("maxq_unit_test_vars.pck");

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSDistanceVector ResultVector(1., 2., 3.);

    FString Body = TEXT("9999"), Item = TEXT("RADII");

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
    EXPECT_DOUBLE_EQ(ResultVector.x.km, 12.34);
    EXPECT_DOUBLE_EQ(ResultVector.y.km, 56.78);
    EXPECT_DOUBLE_EQ(ResultVector.z.km, 91.01112);
}

TEST(bodvrd_distance_vector_test, BODY9998_RADII_4D_Is_Error) {
    // BODY9998_RADII    = ( 12.34   56.78   91.0   11.12 )
    USpice::init_all();
    USpice::furnsh_absolute("maxq_unit_test_vars.pck");

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSDistanceVector ResultVector = FSDistanceVector(1., 2., 3.);

    FString Body = TEXT("9998"), Item = TEXT("RADII");

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


TEST(bodvrd_distance_vector_test, BODY9997_RADII_2D_Is_Error) {
    // BODY9997_RADII    = ( 12.34   56.78 )
    USpice::init_all();
    USpice::furnsh_absolute("maxq_unit_test_vars.pck");

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSDistanceVector ResultVector = FSDistanceVector(1., 2., 3.);

    FString Body = TEXT("9997"), Item = TEXT("RADII");

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
    EXPECT_DOUBLE_EQ(ResultVector.x.km, 12.34);
    EXPECT_DOUBLE_EQ(ResultVector.y.km, 56.78);
    EXPECT_DOUBLE_EQ(ResultVector.z.km, 3.);
}