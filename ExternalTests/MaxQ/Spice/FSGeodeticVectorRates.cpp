// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSGeodeticVectorRatesTest, DefaultConstruction_IsInitialized) {
    FSGeodeticVectorRates geodeticVectorRates;

    EXPECT_DOUBLE_EQ(geodeticVectorRates.dlon.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(geodeticVectorRates.dlat.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(geodeticVectorRates.dalt.kmps, 0.);
}

