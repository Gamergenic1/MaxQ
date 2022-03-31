// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSLatitudinalStateVectorTest, DefaultConstruction_IsInitialized) {
    FSLatitudinalStateVector latitudinalStateVector;

    EXPECT_DOUBLE_EQ(latitudinalStateVector.r.lonlat.longitude.degrees, 0.);
    EXPECT_DOUBLE_EQ(latitudinalStateVector.r.lonlat.latitude.degrees, 0.);
    EXPECT_DOUBLE_EQ(latitudinalStateVector.r.r.km, 0.);
    EXPECT_DOUBLE_EQ(latitudinalStateVector.dr.dlon.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(latitudinalStateVector.dr.dlat.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(latitudinalStateVector.dr.dr.kmps, 0.);
}

