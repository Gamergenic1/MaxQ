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

TEST(FSEllipseTest, DefaultConstruction_IsInitialized) {
    FSEllipse ellipse;

    EXPECT_EQ(ellipse.center.x.km, 0.);
    EXPECT_EQ(ellipse.center.y.km, 0.);
    EXPECT_EQ(ellipse.center.z.km, 0.);
    EXPECT_EQ(ellipse.v_major.x.km, 0.);
    EXPECT_EQ(ellipse.v_major.y.km, 0.);
    EXPECT_EQ(ellipse.v_major.z.km, 0.);
    EXPECT_EQ(ellipse.v_minor.x.km, 0.);
    EXPECT_EQ(ellipse.v_minor.y.km, 0.);
    EXPECT_EQ(ellipse.v_minor.z.km, 0.);
}

