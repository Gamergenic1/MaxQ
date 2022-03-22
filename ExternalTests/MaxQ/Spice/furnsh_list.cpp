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

TEST(furnsh_list_test, DefaultsTestCase) {
    // Expected result is nothing happens, since there's nothing requested.
    ES_ResultCode ResultCode = static_cast<ES_ResultCode>(-1);
    FString ErrorMessage = FString();
    FString RelativePath = FString();
    TArray<FString> RelativePathList = TArray<FString>();

    USpice::furnsh_list(ResultCode, ErrorMessage, RelativePathList);

    EXPECT_EQ(ResultCode, static_cast<ES_ResultCode>(-1));
    EXPECT_EQ(ErrorMessage.Len(), 0);
}

