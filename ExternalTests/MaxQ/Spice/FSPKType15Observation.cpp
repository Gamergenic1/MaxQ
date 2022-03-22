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

TEST(FSPKType15ObservationTest, DefaultConstruction_IsInitialized) {
    FSPKType15Observation SPKType15Observation;

    EXPECT_EQ(SPKType15Observation.epoch.seconds, 0.);
    EXPECT_EQ(SPKType15Observation.tp.x, 0.);
    EXPECT_EQ(SPKType15Observation.tp.y, 0.);
    EXPECT_EQ(SPKType15Observation.tp.z, 0.);
    EXPECT_EQ(SPKType15Observation.pa.x, 0.);
    EXPECT_EQ(SPKType15Observation.pa.y, 0.);
    EXPECT_EQ(SPKType15Observation.pa.z, 0.);
    EXPECT_EQ(SPKType15Observation.p.km, 0.);
    EXPECT_EQ(SPKType15Observation.ecc, 0.);
    EXPECT_EQ(SPKType15Observation.j2flg, 0.);
    EXPECT_EQ(SPKType15Observation.pv.x, 0.);
    EXPECT_EQ(SPKType15Observation.pv.y, 0.);
    EXPECT_EQ(SPKType15Observation.pv.z, 0.);
    EXPECT_EQ(SPKType15Observation.gm.GM, 0.);
    EXPECT_EQ(SPKType15Observation.j2, 0.);
    EXPECT_EQ(SPKType15Observation.radius.km, 0.);
}

