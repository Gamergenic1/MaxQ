// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSCylindricalVectorTest, DefaultConstruction_IsInitialized) {
    FSCylindricalVector cylindricalVector;

    EXPECT_DOUBLE_EQ(cylindricalVector.lon.degrees, 0.);
    EXPECT_DOUBLE_EQ(cylindricalVector.r.km, 0.);
    EXPECT_DOUBLE_EQ(cylindricalVector.z.km, 0.);
}

