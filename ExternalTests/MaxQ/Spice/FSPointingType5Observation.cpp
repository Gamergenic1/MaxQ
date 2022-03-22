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

TEST(FSPointingType5ObservationTest, DefaultConstruction_IsInitialized) {
    FSPointingType5Observation pointingType5Observation;

    EXPECT_EQ(pointingType5Observation.sclkdp, 0.);

    EXPECT_EQ(pointingType5Observation.quat.w, 1.);
    EXPECT_EQ(pointingType5Observation.quat.x, 0.);
    EXPECT_EQ(pointingType5Observation.quat.y, 0.);
    EXPECT_EQ(pointingType5Observation.quat.z, 0.);    
    EXPECT_EQ(pointingType5Observation.quatderiv.w, 1.);
    EXPECT_EQ(pointingType5Observation.quatderiv.x, 0.);
    EXPECT_EQ(pointingType5Observation.quatderiv.y, 0.);
    EXPECT_EQ(pointingType5Observation.quatderiv.z, 0.);
    EXPECT_EQ(pointingType5Observation.avv.x.radiansPerSecond, 0.);
    EXPECT_EQ(pointingType5Observation.avv.y.radiansPerSecond, 0.);
    EXPECT_EQ(pointingType5Observation.avv.z.radiansPerSecond, 0.);
    EXPECT_EQ(pointingType5Observation.avvderiv.x.radiansPerSecond, 0.);
    EXPECT_EQ(pointingType5Observation.avvderiv.y.radiansPerSecond, 0.);
    EXPECT_EQ(pointingType5Observation.avvderiv.z.radiansPerSecond, 0.);
}

