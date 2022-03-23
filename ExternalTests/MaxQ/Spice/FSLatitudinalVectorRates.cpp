// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 
#include "pch.h"


TEST(FSLatitudinalVectorRatesTest, DefaultConstruction_IsInitialized) {
    FSLatitudinalVectorRates latitudinalVectorRates;

    EXPECT_DOUBLE_EQ(latitudinalVectorRates.dlon.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(latitudinalVectorRates.dlat.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(latitudinalVectorRates.dr.kmps, 0.);
}

