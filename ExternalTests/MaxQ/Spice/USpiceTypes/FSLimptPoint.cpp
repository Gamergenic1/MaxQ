// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


TEST(FSLimptPointTest, DefaultConstruction_IsInitialized) {
    FSLimptPoint limptPoint;

    EXPECT_DOUBLE_EQ(limptPoint.point.x.km, 0.);
    EXPECT_DOUBLE_EQ(limptPoint.point.y.km, 0.);
    EXPECT_DOUBLE_EQ(limptPoint.point.z.km, 0.);
    EXPECT_DOUBLE_EQ(limptPoint.epoch.seconds, 0.);
    EXPECT_DOUBLE_EQ(limptPoint.tangt.x.km, 0.);
    EXPECT_DOUBLE_EQ(limptPoint.tangt.y.km, 0.);
    EXPECT_DOUBLE_EQ(limptPoint.tangt.z.km, 0.);
}

