// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSPlanetographicVectorRatesTest, DefaultConstruction_IsInitialized) {
    FSPlanetographicVectorRates planetographicVectorRates;

    EXPECT_DOUBLE_EQ(planetographicVectorRates.dlon.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(planetographicVectorRates.dlat.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(planetographicVectorRates.dalt.kmps, 0.);
}

