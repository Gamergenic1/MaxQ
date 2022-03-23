// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(combine_paths_test, DefaultsTestCase) {
    FString base;
    TArray<FString> inputs;
    TArray<FString> outputs;
    USpice::combine_paths(base, inputs, outputs);

    EXPECT_EQ(outputs.Num(), 0);
}

