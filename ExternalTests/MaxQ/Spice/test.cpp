#include "UE5HostDefs.h"
#include "SpiceHostDefs.h"

#include "Spice.h"
#include "SpiceTypes.h"

#include "gtest/gtest.h"

TEST(TestCaseName, TestName) {
    FSStateVector stateVector;

    EXPECT_EQ(stateVector.r, FSDistanceVector::Zero);
    EXPECT_EQ(stateVector.v, FSVelocityVector::Zero);
}