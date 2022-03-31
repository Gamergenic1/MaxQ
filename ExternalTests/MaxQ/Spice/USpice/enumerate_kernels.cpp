// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(enumerate_kernels_test, DefaultsTestCase) {
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage = FString();
    TArray<FString> RelativePathList = TArray<FString>();
    FString RelativePath = FString();

    
    /*
    * enumerate_kernels triggers an error when executed without UE running:
    Fatal error: [File:D:/build/++UE5/Sync/Engine/Source/Runtime/Core/Private/Misc/CommandLine.cpp] [Line: 43]
    Attempting to get the command line but it hasn't been initialized yet.
    */

    /*
    USpice::enumerate_kernels(ResultCode, ErrorMessage, RelativePathList, RelativePath);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_TRUE(ErrorMessage.Len() > 0);
    EXPECT_EQ(RelativePathList.Num(), 0);
    */
}

