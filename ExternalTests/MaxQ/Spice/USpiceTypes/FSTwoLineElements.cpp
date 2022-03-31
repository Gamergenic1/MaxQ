// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSTwoLineElementsTest, DefaultConstruction_IsInitialized) {
    FSTwoLineElements twoLineElements;

    EXPECT_EQ(twoLineElements.elems.Num(), 10);

    for (int i = 0; i < twoLineElements.elems.Num(); ++i)
    {
        EXPECT_DOUBLE_EQ(twoLineElements.elems[i], 0.);
    }
}

