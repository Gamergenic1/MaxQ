// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSDLADescrTest, DefaultConstruction_IsInitialized) {
    FSDLADescr DLADescr;

    EXPECT_EQ(DLADescr.bwdptr, 0);
    EXPECT_EQ(DLADescr.fwdptr, 0);
    EXPECT_EQ(DLADescr.ibase, 0);
    EXPECT_EQ(DLADescr.isize, 0);
    EXPECT_EQ(DLADescr.dbase, 0);
    EXPECT_EQ(DLADescr.dsize, 0);
    EXPECT_EQ(DLADescr.cbase, 0);
    EXPECT_EQ(DLADescr.csize, 0);
}

