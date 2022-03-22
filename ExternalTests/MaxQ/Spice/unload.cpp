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

TEST(unload_test, DefaultsTestCase) {
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;
    FString path;

    USpice::unload(ResultCode, ErrorMessage, path);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_TRUE(ErrorMessage.Len() > 0);
}

