// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSStateVectorTest, DefaultConstruction_IsInitialized) {
    FSStateVector stateVector;

    EXPECT_DOUBLE_EQ(stateVector.r.x.km, 0.);
    EXPECT_DOUBLE_EQ(stateVector.r.y.km, 0.);
    EXPECT_DOUBLE_EQ(stateVector.r.z.km, 0.);
    EXPECT_DOUBLE_EQ(stateVector.v.dx.kmps, 0.);
    EXPECT_DOUBLE_EQ(stateVector.v.dy.kmps, 0.);
    EXPECT_DOUBLE_EQ(stateVector.v.dz.kmps, 0.);
}

