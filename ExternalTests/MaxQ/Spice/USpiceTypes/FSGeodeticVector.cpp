// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSGeodeticVectorTest, DefaultConstruction_IsInitialized) {
    FSGeodeticVector geodeticVector;

    EXPECT_DOUBLE_EQ(geodeticVector.lonlat.longitude.degrees, 0.);
    EXPECT_DOUBLE_EQ(geodeticVector.lonlat.latitude.degrees, 0.);
    EXPECT_DOUBLE_EQ(geodeticVector.alt.km, 0.);
}

