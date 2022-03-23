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

TEST(init_all_test, DefaultsTestCase) {
    USpice::init_all();
}


TEST(init_all_test, Execution_ClearsKernel) {
    USpice::furnsh_absolute("unit_test_vars.txt");
    USpice::init_all();

    ES_ResultCode ResultCode = ES_ResultCode::Error;
    FString ErrorMessage;
    
    double Dvalue = 0.;
    bool bFound = true;
    USpice::gdpool_scalar(ResultCode, ErrorMessage, Dvalue, bFound, FString(TEXT("BODY9999_GM")));

    EXPECT_EQ(bFound, false);
    EXPECT_EQ(Dvalue, 0.);
    EXPECT_EQ(ErrorMessage.Len(), 0);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
}



TEST(init_all_test, Execution_ClearsError) {

    FString errorOutput;

    USpice::raise_spice_error();

    USpice::init_all();
    
    ES_ResultCode ResultCode;
    FString ErrorMessage;

    USpice::get_implied_result(ResultCode, ErrorMessage);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);
}


