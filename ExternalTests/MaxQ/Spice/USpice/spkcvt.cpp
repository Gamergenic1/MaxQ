// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"
#include "MaxQTestDefinitions.h"

TEST(spkcvt_test, DefaultsTestCase) {

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSEphemerisTime et, targetEpoch;
    FSStateVector state, targetState;
    FSEphemerisPeriod lt = FSEphemerisPeriod(1.5);
    FString targetCenter;
    FString outRef;
    FString targetRef;
    FString obs;
    ES_ReferenceFrameLocus locus = ES_ReferenceFrameLocus::CENTER;
    ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::None;

    USpice::spkcvt(ResultCode, ErrorMessage, state, lt, targetState, targetEpoch, et, targetCenter, targetRef, outRef, locus, obs, abcorr);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);
    EXPECT_DOUBLE_EQ(lt.seconds, 1.5);
    EXPECT_DOUBLE_EQ(IsNear(state, FSStateVector()), true);
}


TEST(spkcvt_test, FAKEBODY9994_Is_OrbitingFAKEBODY9995) {

    USpice::init_all();

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    USpice::furnsh_absolute("maxq_unit_test_meta.tm");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    ResultCode = ES_ResultCode::Error;
    FSEphemerisTime targetEpoch = et0;
    FSStateVector targetState(FSDistanceVector(7000, 0, 0), FSVelocityVector(0, -2, 0));
    FString targetCenter = TEXT("FAKEBODY9994");
    FString outRef = TEXT("ECLIPJ2000");
    FString targetRef = TEXT("ECLIPJ2000");
    FString obs = TEXT("FAKEBODY9995");;
    ES_ReferenceFrameLocus locus = ES_ReferenceFrameLocus::CENTER;
    ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::None;

    FSEphemerisPeriod lt(1.5);
    FSStateVector stateVector;

    USpice::spkcvt(ResultCode, ErrorMessage, stateVector, lt, targetState, targetEpoch, et0, targetCenter, targetRef, outRef, locus, obs, abcorr);

    stateVector -= targetState;


    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);
    // SPICE populates something into lt... something non-zero... Even if we set it to ::None
    // EXPECT_DOUBLE_EQ(lt.seconds, 0.);
    EXPECT_EQ(IsNear(stateVector, state_target_9994_center_9995_eclipj2000_et0), true);
}