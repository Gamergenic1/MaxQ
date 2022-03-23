// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSPlateIndicesTest, DefaultConstruction_IsInitialized) {
    FSPlateIndices plateIndices;

    EXPECT_EQ(plateIndices.i0, 0);
    EXPECT_EQ(plateIndices.i1, 0);
    EXPECT_EQ(plateIndices.i2, 0);
}

