// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSSphericalVectorRatesTest, DefaultConstruction_IsInitialized) {
    FSSphericalVectorRates sphericalVectorRates;

    EXPECT_DOUBLE_EQ(sphericalVectorRates.dcolat.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(sphericalVectorRates.dlon.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(sphericalVectorRates.dr.kmps, 0.);
}

