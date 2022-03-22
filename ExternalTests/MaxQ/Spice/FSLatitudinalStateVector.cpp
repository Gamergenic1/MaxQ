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

TEST(FSLatitudinalStateVectorTest, DefaultConstruction_IsInitialized) {
    FSLatitudinalStateVector latitudinalStateVector;

    EXPECT_EQ(latitudinalStateVector.r.lonlat.longitude, 0.);
    EXPECT_EQ(latitudinalStateVector.r.lonlat.latitude, 0.);
    EXPECT_EQ(latitudinalStateVector.r.r.km, 0.);
    EXPECT_EQ(latitudinalStateVector.dr.dlon.radiansPerSecond, 0.);
    EXPECT_EQ(latitudinalStateVector.dr.dlat.radiansPerSecond, 0.);
    EXPECT_EQ(latitudinalStateVector.dr.dr.kmps, 0.);
}

