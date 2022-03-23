// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSPKType5ObservationTest, DefaultConstruction_IsInitialized) {
    FSPKType5Observation SPKType5Observation;

    EXPECT_DOUBLE_EQ(SPKType5Observation.et.seconds, 0.);
    EXPECT_DOUBLE_EQ(SPKType5Observation.state.r.x.km, 0.);
    EXPECT_DOUBLE_EQ(SPKType5Observation.state.r.y.km, 0.);
    EXPECT_DOUBLE_EQ(SPKType5Observation.state.r.y.km, 0.);
    EXPECT_DOUBLE_EQ(SPKType5Observation.state.v.dx.kmps, 0.);
    EXPECT_DOUBLE_EQ(SPKType5Observation.state.v.dy.kmps, 0.);
    EXPECT_DOUBLE_EQ(SPKType5Observation.state.v.dz.kmps, 0.);
}

