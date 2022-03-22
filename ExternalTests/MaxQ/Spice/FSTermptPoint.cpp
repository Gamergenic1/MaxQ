// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "UE5HostDefs.h"
#include "SpiceHostDefs.h"

#include "Spice.h"
#include "SpiceTypes.h"

#include "gtest/gtest.h"

TEST(FSTermptPointTest, DefaultConstruction_IsInitialized) {
    FSTermptPoint termptPoint;

    EXPECT_EQ(termptPoint.point.x.km, 0.);
    EXPECT_EQ(termptPoint.point.y.km, 0.);
    EXPECT_EQ(termptPoint.point.z.km, 0.);
    EXPECT_EQ(termptPoint.epoch.seconds, 0.);
    EXPECT_EQ(termptPoint.trmvc.x.km, 0.);
    EXPECT_EQ(termptPoint.trmvc.y.km, 0.);
    EXPECT_EQ(termptPoint.trmvc.z.km, 0.);
}

