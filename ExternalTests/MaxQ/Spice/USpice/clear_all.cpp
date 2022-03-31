// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(clear_all_test, DefaultsTestCase) {
    USpice::clear_all();
}

TEST(clear_all_test, Execution_ClearsKernel) {
    // Note:  Does not clear body name assignments (by design, SPICE)
    USpice::furnsh_absolute("maxq_unit_test_meta.tm");
    USpice::clear_all();

    ES_ResultCode ResultCode = ES_ResultCode::Error;
    FString ErrorMessage;

    double Dvalue = 0.;
    bool bFound = true;
    USpice::gdpool_scalar(ResultCode, ErrorMessage, Dvalue, bFound, FString(TEXT("BODY9999_GM")));

    EXPECT_EQ(bFound, false);
    EXPECT_DOUBLE_EQ(Dvalue, 0.);
    EXPECT_EQ(ErrorMessage.Len(), 0);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
}