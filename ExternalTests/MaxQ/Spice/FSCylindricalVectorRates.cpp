// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSCylindricalVectorRates, DefaultConstruction_IsInitialized) {
    FSCylindricalVectorRates cylindricalVectorRates;

    EXPECT_DOUBLE_EQ(cylindricalVectorRates.dlon.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(cylindricalVectorRates.dr.kmps, 0.);
    EXPECT_DOUBLE_EQ(cylindricalVectorRates.dz.kmps, 0.);
}

