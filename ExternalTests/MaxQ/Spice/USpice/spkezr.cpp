// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"
#include "MaxQTestDefinitions.h"

TEST(spkezr_test, DefaultsTestCase) {

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    FSEphemerisTime et;
    FSStateVector stateVector;
    FSEphemerisPeriod lt = FSEphemerisPeriod(1.5);
    FString targ;
    FString obs;
    FString ref;
    ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::None;

    USpice::spkezr(ResultCode, ErrorMessage, et, stateVector, lt, targ, obs, ref, abcorr);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);
    EXPECT_DOUBLE_EQ(lt.seconds, 1.5);
    EXPECT_DOUBLE_EQ(stateVector.r.x.km, 0.);
    EXPECT_DOUBLE_EQ(stateVector.r.y.km, 0.);
    EXPECT_DOUBLE_EQ(stateVector.r.z.km, 0.);
    EXPECT_DOUBLE_EQ(stateVector.v.dx.kmps, 0.);
    EXPECT_DOUBLE_EQ(stateVector.v.dy.kmps, 0.);
    EXPECT_DOUBLE_EQ(stateVector.v.dz.kmps, 0.);
}


TEST(spkezr_test, FAKEBODY9994_Is_OrbitingFAKEBODY9995) {

    USpice::init_all();

    ES_ResultCode ResultCode = ES_ResultCode::Error;
    FString ErrorMessage;

    USpice::furnsh_absolute("maxq_unit_test_meta.tm");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    FSStateVector stateVector;
    FSEphemerisPeriod lt(1.5);
    FString targ = TEXT("FAKEBODY9994");
    FString obs = TEXT("FAKEBODY9995");
    FString ref = TEXT("ECLIPJ2000");
    ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::None;

    USpice::spkezr(ResultCode, ErrorMessage, et0, stateVector, lt, targ, obs, ref, abcorr);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);
    // SPICE populates something into lt... something non-zero... Even if we set it to ::None
    // EXPECT_DOUBLE_EQ(lt.seconds, 0.);
    EXPECT_EQ(IsNear(stateVector, state_target_9994_center_9995_eclipj2000_et0), true);
}

TEST(spkezr_test, FAKEBODY9994_IsNot_OrbitingFAKEBODY9899) {

    USpice::init_all();

    ES_ResultCode ResultCode = ES_ResultCode::Error;
    FString ErrorMessage;
    USpice::furnsh_absolute("maxq_unit_test_meta.tm");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    FSStateVector stateVector;
    FSEphemerisPeriod lt(1.5);
    FString targ = TEXT("FAKEBODY9994");
    FString obs = TEXT("FAKEBODY9899");
    FString ref = TEXT("ECLIPJ2000");
    ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::None;

    USpice::spkezr(ResultCode, ErrorMessage, et0, stateVector, lt, targ, obs, ref, abcorr);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);
    EXPECT_DOUBLE_EQ(lt.seconds, 1.5);

    EXPECT_EQ(IsNear(stateVector, FSStateVector()), true);
}




TEST(spkezr_test, FAKEBODY9994_IsNot_AtFAKEBODY9995ALongTimeFromNow) {

    USpice::init_all();

    ES_ResultCode ResultCode = ES_ResultCode::Error;
    FString ErrorMessage;
    USpice::furnsh_absolute("maxq_unit_test_meta.tm");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    FSEphemerisTime et(et0);
    et += 100 * 365.25 * FSEphemerisPeriod::Day;

    FSStateVector stateVector;
    FSEphemerisPeriod lt(1.5);
    FString targ = TEXT("FAKEBODY9994");
    FString obs = TEXT("FAKEBODY9995");
    FString ref = TEXT("ECLIPJ2000");
    ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::None;

    USpice::spkezr(ResultCode, ErrorMessage, et, stateVector, lt, targ, obs, ref, abcorr);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);
    EXPECT_EQ(IsNear(stateVector, FSStateVector()), true);
}


TEST(spkezr_test, FAKEBODY9994_IsNot_AtFAKEBODY9995ALongTimeAgo) {

    USpice::init_all();

    ES_ResultCode ResultCode = ES_ResultCode::Error;
    FString ErrorMessage;
    USpice::furnsh_absolute("maxq_unit_test_meta.tm");
    USpice::get_implied_result(ResultCode, ErrorMessage);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);

    FSEphemerisTime et(et0);
    et -= 100 * 365.25 * FSEphemerisPeriod::Day;

    FSStateVector stateVector;
    FSEphemerisPeriod lt(1.5);
    FString targ = TEXT("FAKEBODY9994");
    FString obs = TEXT("FAKEBODY9995");
    FString ref = TEXT("ECLIPJ2000");
    ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::None;

    USpice::spkezr(ResultCode, ErrorMessage, et, stateVector, lt, targ, obs, ref, abcorr);

    EXPECT_EQ(ResultCode, ES_ResultCode::Error);
    EXPECT_GT(ErrorMessage.Len(), 0);
    EXPECT_DOUBLE_EQ(lt.seconds, 1.5);
    EXPECT_DOUBLE_EQ(IsNear(stateVector, FSStateVector()), true);
}

// 9995 must connect to SSB for Aberration value
#if 0
TEST(spkezr_test, FAKEBODY9995_Has_AberrationToFAKEBODY9993) {

    USpice::init_all();

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;
    USpice::furnsh_absolute("maxq_unit_test_meta.mk");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);

    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSEphemerisTime et(et0);
    FSStateVector stateVector;
    FSEphemerisPeriod lt(1.5);
    FString targ = TEXT("FAKEBODY9995");
    FString obs = TEXT("FAKEBODY9993");
    FString ref = TEXT("J2000");
    ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::LT;

    USpice::spkezr(ResultCode, ErrorMessage, et, stateVector, lt, targ, obs, ref, abcorr);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);
    EXPECT_GT(lt.seconds, 0.);
    EXPECT_EQ(IsNear(stateVector, FSStateVector()), true);
}
#endif