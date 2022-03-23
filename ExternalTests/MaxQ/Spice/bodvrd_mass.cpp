// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"

TEST(bodvrd_mass_test, DefaultsTestCase) {

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSMassConstant ResultMass = FSMassConstant(1.5);

    FString Body, Item;

    USpice::bodvrd_mass(
        ResultCode,
        ErrorMessage,
        ResultMass,
        Body,
        Item
    );

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);

    // Since the call should have failed, we expect the ResultMass to be unchanged...
    EXPECT_DOUBLE_EQ(ResultMass.GM, 1.5);
}

TEST(bodvrd_mass_test, BODY9999_GM_Is_Correct) {
    // BODY9999_GM       = ( 123456789.1011 )
    USpice::init_all();
    USpice::furnsh_absolute("maxq_unit_test_vars.pck");

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSMassConstant ResultMass = FSMassConstant(1.5);

    FString Body = TEXT("9999"), Item = TEXT("GM");

    USpice::bodvrd_mass(
        ResultCode,
        ErrorMessage,
        ResultMass,
        Body,
        Item
    );

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    // No mercy for ~=
    EXPECT_DOUBLE_EQ(ResultMass.AsSpiceDouble(), 123456789.1011);
}



TEST(bodvrd_mass_test, BODY9997_RADII_2D_Is_Error) {
    // BODY9997_GM       = ( 12.34   56.78 )
    USpice::init_all();
    USpice::furnsh_absolute("maxq_unit_test_vars.pck");

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSMassConstant ResultMass = FSMassConstant(1.5);

    FString Body = TEXT("9997"), Item = TEXT("GM");

    USpice::bodvrd_mass(
        ResultCode,
        ErrorMessage,
        ResultMass,
        Body,
        Item
    );

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);

    // No mercy for ~=
    EXPECT_DOUBLE_EQ(ResultMass.AsSpiceDouble(), 1.5);
}