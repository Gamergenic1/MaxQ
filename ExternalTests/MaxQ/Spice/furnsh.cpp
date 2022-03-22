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

TEST(furnsh_test, DefaultsTestCase) {
    ES_ResultCode ResultCode = ES_ResultCode::Error;
    FString ErrorMessage = FString();
    FString RelativePath = FString();

    /*
    furnsh triggers the following error when executed without UE running.
    Fatal error: [File:D:/build/++UE5/Sync/Engine/Source/Runtime/Core/Private/Misc/CommandLine.cpp] [Line: 43]
    Attempting to get the command line but it hasn't been initialized yet.

    [Inline Frame] UnrealEditor-Core.dll!FCommandLine::Get::__l10::<lambda_789ce7a3e8995a5b6425f401a6fd49df>::()::__l6::<lambda_1d98d38f813b35cd4aeea022b197a965>::operator()() Line 43	C++
    [Inline Frame] UnrealEditor-Core.dll!FCommandLine::Get::__l10::<lambda_789ce7a3e8995a5b6425f401a6fd49df>::operator()(const FLogCategoryLogInit &) Line 43	C++
    UnrealEditor-Core.dll!DispatchCheckVerify<void,<lambda_789ce7a3e8995a5b6425f401a6fd49df>,FLogCategoryLogInit,wchar_t [71]>(FCommandLine::Get::__l10::<lambda_789ce7a3e8995a5b6425f401a6fd49df> && Inner={...}, const FLogCategoryLogInit & <Args_0>={...}, const wchar_t[71] & <Args_1>=...) Line 175	C++
    [Inline Frame] UnrealEditor-Core.dll!FCommandLine::Get() Line 43	C++
    UnrealEditor-Core.dll!FApp::IsInstalled() Line 194	C++
    UnrealEditor-Core.dll!FPaths::ShouldSaveToUserDir() Line 138	C++
    UnrealEditor-Core.dll!FPaths::EngineUserDir() Line 159	C++
    UnrealEditor-Core.dll!FGenericPlatformMisc::ProjectDir() Line 1079	C++
    UnrealEditor-Core.dll!FPaths::ProjectDir() Line 301	C++
    UnrealEditor-Spice.dll!toPath(const FString & file={...}) Line 32	C++
    UnrealEditor-Spice.dll!USpice::furnsh(ES_ResultCode & ResultCode=Error, FString & ErrorMessage={...}, const FString & file) Line 88	C++

    */

    /*
    USpice::furnsh(ResultCode, ErrorMessage, RelativePath);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_TRUE(ErrorMessage.Len() > 0);
    */
}

