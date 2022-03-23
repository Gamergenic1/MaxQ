// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSSphericalStateVectorTest, DefaultConstruction_IsInitialized) {
    FSSphericalStateVector sphericalStateVector;

    EXPECT_DOUBLE_EQ(sphericalStateVector.r.colat.degrees, 0.);
    EXPECT_DOUBLE_EQ(sphericalStateVector.r.lon.degrees, 0.);
    EXPECT_DOUBLE_EQ(sphericalStateVector.r.r.km, 0.);
    EXPECT_DOUBLE_EQ(sphericalStateVector.dr.dcolat.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(sphericalStateVector.dr.dlon.radiansPerSecond, 0.);
    EXPECT_DOUBLE_EQ(sphericalStateVector.dr.dr.kmps, 0.);
}

