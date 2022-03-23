// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSDistanceVectorTest, DefaultConstruction_IsInitialized) {
    FSDistanceVector distanceVector;

    EXPECT_DOUBLE_EQ(distanceVector.x.km, 0.);
    EXPECT_DOUBLE_EQ(distanceVector.y.km, 0.);
    EXPECT_DOUBLE_EQ(distanceVector.z.km, 0.);
}

