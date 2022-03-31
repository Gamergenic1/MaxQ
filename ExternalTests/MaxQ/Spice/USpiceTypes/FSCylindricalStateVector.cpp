// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSCylindricalStateVectorTest, DefaultConstruction_IsInitialized) {
    FSCylindricalStateVector cylindricalStateVector;

    EXPECT_DOUBLE_EQ(cylindricalStateVector.r.lon.degrees, 0.);
    EXPECT_DOUBLE_EQ(cylindricalStateVector.r.r.km, 0.);
    EXPECT_DOUBLE_EQ(cylindricalStateVector.r.z.km, 0.);
    EXPECT_DOUBLE_EQ(cylindricalStateVector.dr.dlon.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(cylindricalStateVector.dr.dr.kmps, 0.);
    EXPECT_DOUBLE_EQ(cylindricalStateVector.dr.dz.kmps, 0.);
}

