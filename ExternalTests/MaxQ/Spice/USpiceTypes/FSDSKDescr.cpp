// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"

TEST(FSDSKDescrTest, DefaultConstruction_IsInitialized) {
    FSDSKDescr DSKDescr;

    EXPECT_EQ(DSKDescr.surfce, 0);
    EXPECT_EQ(DSKDescr.center, 0);
    EXPECT_EQ(DSKDescr.dclass, 0);
    EXPECT_EQ(DSKDescr.dtype, 0);
    EXPECT_EQ(DSKDescr.frmcde, 0);
    EXPECT_EQ(DSKDescr.corsys, 0);
    EXPECT_EQ(DSKDescr.corpar.Num(), 0);
    EXPECT_DOUBLE_EQ(DSKDescr.co1min, 0.);
    EXPECT_DOUBLE_EQ(DSKDescr.co1max, 0.);
    EXPECT_DOUBLE_EQ(DSKDescr.co2min, 0.);
    EXPECT_DOUBLE_EQ(DSKDescr.co2max, 0.);
    EXPECT_DOUBLE_EQ(DSKDescr.co3min, 0.);
    EXPECT_DOUBLE_EQ(DSKDescr.co3max, 0.);
    EXPECT_DOUBLE_EQ(DSKDescr.start, 0.);
    EXPECT_DOUBLE_EQ(DSKDescr.stop, 0.);
}

