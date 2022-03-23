// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSPlanetographicVectorTest, DefaultConstruction_IsInitialized) {
    FSPlanetographicVector planetographicVector;

    EXPECT_DOUBLE_EQ(planetographicVector.lonlat.longitude.degrees, 0.);
    EXPECT_DOUBLE_EQ(planetographicVector.lonlat.latitude.degrees, 0.);
    EXPECT_DOUBLE_EQ(planetographicVector.alt.km, 0.);
}

