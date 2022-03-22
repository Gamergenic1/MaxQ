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

TEST(FSRayTest, DefaultConstruction_IsInitialized) {
    FSRay ray;

    EXPECT_EQ(ray.point.x.km, 0.);
    EXPECT_EQ(ray.point.y.km, 0.);
    EXPECT_EQ(ray.point.z.km, 0.);
    EXPECT_EQ(ray.direction.x, 0.);
    EXPECT_EQ(ray.direction.y, 0.);
    EXPECT_EQ(ray.direction.z, 0.);
}

