// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"


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


TEST(spkezr_test, EMB_Is_OrbitingSun) {

    // 981005_PLTEPH-DE405S.bsp validity range:
    // 2004 JUN 11 05:01:04 - 2004 JUN 12 12:01:04
    // Bodies: MERCURY BARYCENTER(1)  SATURN BARYCENTER(6)   MERCURY(199)
    // VENUS BARYCENTER(2)    URANUS BARYCENTER(7)   VENUS(299)
    // EARTH BARYCENTER(3)    NEPTUNE BARYCENTER(8)  MOON(301)
    // MARS BARYCENTER(4)     PLUTO BARYCENTER(9)    EARTH(399)
    // JUPITER BARYCENTER(5)  SUN(10)                MARS(499)

    USpice::init_all();

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    USpice::furnsh_absolute("naif0008.tls");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    USpice::furnsh_absolute("981005_PLTEPH-DE405S.bsp");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSEphemerisTime et;
    USpice::str2et(ResultCode, ErrorMessage, et, TEXT("2004 JUN 11 12:00:00.000"));

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSStateVector stateVector;
    FSEphemerisPeriod lt = FSEphemerisPeriod(1.5);
    FString targ = TEXT("EMB");
    FString obs = TEXT("SSB");
    FString ref = TEXT("ECLIPJ2000");
    ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::None;

    USpice::spkezr(ResultCode, ErrorMessage, et, stateVector, lt, targ, obs, ref, abcorr);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);
    // SPICE populates something into lt... something non-zero... Even if we set it to ::None
    // EXPECT_DOUBLE_EQ(lt.seconds, 0.);
    
    // On June 11, both x, y should be -
    EXPECT_LT(stateVector.r.x.km, 0.);
    EXPECT_LT(stateVector.r.y.km, 0.);
    // Should be relatively near zero, but not close enough to test...
    EXPECT_NE(stateVector.r.z.km, 0.);

    // On June 11:
    EXPECT_GT(stateVector.v.dx.kmps, 0.);
    EXPECT_LT(stateVector.v.dy.kmps, 0.);
    EXPECT_NE(stateVector.v.dz.kmps, 0.);

    // It's nearing summer solstice, inferring:
    EXPECT_LT(stateVector.r.y.km, stateVector.r.x.km);
    EXPECT_GT(stateVector.v.dx.kmps, -stateVector.v.dy.kmps);
}

TEST(spkezr_test, EMB_IsNot_OrbitingTitan) {

    // 981005_PLTEPH-DE405S.bsp validity range:
    // 2004 JUN 11 05:01:04 - 2004 JUN 12 12:01:04
    // Bodies: MERCURY BARYCENTER(1)  SATURN BARYCENTER(6)   MERCURY(199)
    // VENUS BARYCENTER(2)    URANUS BARYCENTER(7)   VENUS(299)
    // EARTH BARYCENTER(3)    NEPTUNE BARYCENTER(8)  MOON(301)
    // MARS BARYCENTER(4)     PLUTO BARYCENTER(9)    EARTH(399)
    // JUPITER BARYCENTER(5)  SUN(10)                MARS(499)

    USpice::init_all();

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    USpice::furnsh_absolute("naif0008.tls");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    USpice::furnsh_absolute("981005_PLTEPH-DE405S.bsp");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSEphemerisTime et;
    USpice::str2et(ResultCode, ErrorMessage, et, TEXT("2004 JUN 11 12:00:00.000"));

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSStateVector stateVector;
    FSEphemerisPeriod lt = FSEphemerisPeriod(1.5);
    FString targ = TEXT("EMB");
    FString obs = TEXT("TITAN");
    FString ref = TEXT("ECLIPJ2000");
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



TEST(spkezr_test, Cassini_Needs_TitanSpk) {

    // 030201AP_SK_SM546_T45.bsp validity range:
    // 2004 JUN 11 05:01 : 04 - 2004 JUN 12 12:01:04
    // CASSINI (-82)

    // 020514_SE_SAT105.bsp validity range:
    // 2004 JUN 11 05:01 : 04 - 2004 JUN 12 12:01:04
    // Bodies: MIMAS (601)      DIONE (604)      HYPERION (607)   SATURN (699)
    // ENCELADUS(602)  RHEA(605)       IAPETUS(608)
    //    TETHYS(603)     TITAN(606)      PHOEBE(609)

    // 981005_PLTEPH-DE405S.bsp validity range:
    // 2004 JUN 11 05:01:04 - 2004 JUN 12 12:01:04
    // Bodies: MERCURY BARYCENTER(1)  SATURN BARYCENTER(6)   MERCURY(199)
    // VENUS BARYCENTER(2)    URANUS BARYCENTER(7)   VENUS(299)
    // EARTH BARYCENTER(3)    NEPTUNE BARYCENTER(8)  MOON(301)
    // MARS BARYCENTER(4)     PLUTO BARYCENTER(9)    EARTH(399)
    // JUPITER BARYCENTER(5)  SUN(10)                MARS(499)

    USpice::init_all();

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;

    USpice::furnsh_absolute("naif0008.tls");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    USpice::furnsh_absolute("981005_PLTEPH-DE405S.bsp");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    USpice::furnsh_absolute("030201AP_SK_SM546_T45.bsp");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Success;
    ErrorMessage.Empty();

    FSEphemerisTime et;
    USpice::str2et(ResultCode, ErrorMessage, et, TEXT("2004 JUN 11 12:00:00.000"));

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSStateVector stateVector;
    FSEphemerisPeriod lt = FSEphemerisPeriod(1.5);
    FString targ = TEXT("CASSINI");
    FString obs = TEXT("TITAN");
    FString ref = TEXT("ECLIPJ2000");
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


TEST(spkezr_test, Cassini_Is_AtTitan) {

    // 030201AP_SK_SM546_T45.bsp validity range:
    // 2004 JUN 11 05:01 : 04 - 2004 JUN 12 12:01:04
    // CASSINI (-82)

    // 020514_SE_SAT105.bsp validity range:
    // 2004 JUN 11 05:01 : 04 - 2004 JUN 12 12:01:04
    // Bodies: MIMAS (601)      DIONE (604)      HYPERION (607)   SATURN (699)
    // ENCELADUS(602)  RHEA(605)       IAPETUS(608)
    //    TETHYS(603)     TITAN(606)      PHOEBE(609)

    // 981005_PLTEPH-DE405S.bsp validity range:
    // 2004 JUN 11 05:01:04 - 2004 JUN 12 12:01:04
    // Bodies: MERCURY BARYCENTER(1)  SATURN BARYCENTER(6)   MERCURY(199)
    // VENUS BARYCENTER(2)    URANUS BARYCENTER(7)   VENUS(299)
    // EARTH BARYCENTER(3)    NEPTUNE BARYCENTER(8)  MOON(301)
    // MARS BARYCENTER(4)     PLUTO BARYCENTER(9)    EARTH(399)
    // JUPITER BARYCENTER(5)  SUN(10)                MARS(499)

    USpice::init_all();

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;
    USpice::furnsh_absolute("maxq_unit_test_metakernel.tm");
    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);

    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSEphemerisTime et;
    USpice::str2et(ResultCode, ErrorMessage, et, TEXT("2004 JUN 11 12:00:00.000"));

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSStateVector stateVector;
    FSEphemerisPeriod lt = FSEphemerisPeriod(1.5);
    FString targ = TEXT("CASSINI");
    FString obs = TEXT("TITAN");
    FString ref = TEXT("ECLIPJ2000");
    ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::None;

    USpice::spkezr(ResultCode, ErrorMessage, et, stateVector, lt, targ, obs, ref, abcorr);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);
    // SPICE populates something into lt... something non-zero... Even if we set it to ::None
    // EXPECT_DOUBLE_EQ(lt.seconds, 0.);
    EXPECT_NE(stateVector.r.x.km, 0.);
    EXPECT_NE(stateVector.r.y.km, 0.);
    EXPECT_NE(stateVector.r.z.km, 0.);
    EXPECT_NE(stateVector.v.dx.kmps, 0.);
    EXPECT_NE(stateVector.v.dy.kmps, 0.);
    EXPECT_NE(stateVector.v.dz.kmps, 0.);
}


TEST(spkezr_test, Cassini_IsNot_AtTitanALongTimeFromNow) {

    // 030201AP_SK_SM546_T45.bsp validity range:
    // 2004 JUN 11 05:01 : 04 - 2004 JUN 12 12:01:04
    // CASSINI (-82)

    // 020514_SE_SAT105.bsp validity range:
    // 2004 JUN 11 05:01 : 04 - 2004 JUN 12 12:01:04
    // Bodies: MIMAS (601)      DIONE (604)      HYPERION (607)   SATURN (699)
    // ENCELADUS(602)  RHEA(605)       IAPETUS(608)
    //    TETHYS(603)     TITAN(606)      PHOEBE(609)

    // 981005_PLTEPH-DE405S.bsp validity range:
    // 2004 JUN 11 05:01:04 - 2004 JUN 12 12:01:04
    // Bodies: MERCURY BARYCENTER(1)  SATURN BARYCENTER(6)   MERCURY(199)
    // VENUS BARYCENTER(2)    URANUS BARYCENTER(7)   VENUS(299)
    // EARTH BARYCENTER(3)    NEPTUNE BARYCENTER(8)  MOON(301)
    // MARS BARYCENTER(4)     PLUTO BARYCENTER(9)    EARTH(399)
    // JUPITER BARYCENTER(5)  SUN(10)                MARS(499)

    USpice::init_all();

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;
    USpice::furnsh_absolute("maxq_unit_test_metakernel.tm");

    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);

    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSEphemerisTime et;
    USpice::str2et(ResultCode, ErrorMessage, et, TEXT("2222 JUN 22 22:22:22.222"));

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSStateVector stateVector;
    FSEphemerisPeriod lt = FSEphemerisPeriod(1.5);
    FString targ = TEXT("CASSINI");
    FString obs = TEXT("TITAN");
    FString ref = TEXT("ECLIPJ2000");
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


TEST(spkezr_test, Cassini_IsNot_AtTitanALongTimeAgo) {

    // 030201AP_SK_SM546_T45.bsp validity range:
    // 2004 JUN 11 05:01 : 04 - 2004 JUN 12 12:01:04
    // CASSINI (-82)

    // 020514_SE_SAT105.bsp validity range:
    // 2004 JUN 11 05:01 : 04 - 2004 JUN 12 12:01:04
    // Bodies: MIMAS (601)      DIONE (604)      HYPERION (607)   SATURN (699)
    // ENCELADUS(602)  RHEA(605)       IAPETUS(608)
    //    TETHYS(603)     TITAN(606)      PHOEBE(609)

    // 981005_PLTEPH-DE405S.bsp validity range:
    // 2004 JUN 11 05:01:04 - 2004 JUN 12 12:01:04
    // Bodies: MERCURY BARYCENTER(1)  SATURN BARYCENTER(6)   MERCURY(199)
    // VENUS BARYCENTER(2)    URANUS BARYCENTER(7)   VENUS(299)
    // EARTH BARYCENTER(3)    NEPTUNE BARYCENTER(8)  MOON(301)
    // MARS BARYCENTER(4)     PLUTO BARYCENTER(9)    EARTH(399)
    // JUPITER BARYCENTER(5)  SUN(10)                MARS(499)

    USpice::init_all();

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;
    USpice::furnsh_absolute("maxq_unit_test_metakernel.tm");

    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);

    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSEphemerisTime et;
    USpice::str2et(ResultCode, ErrorMessage, et, TEXT("1111 JUN 11 11:11:11.111"));

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSStateVector stateVector;
    FSEphemerisPeriod lt = FSEphemerisPeriod(1.5);
    FString targ = TEXT("CASSINI");
    FString obs = TEXT("TITAN");
    FString ref = TEXT("ECLIPJ2000");
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

TEST(spkezr_test, Cassini_Has_AberrationToEarth) {

    // 030201AP_SK_SM546_T45.bsp validity range:
    // 2004 JUN 11 05:01 : 04 - 2004 JUN 12 12:01:04
    // CASSINI (-82)

    // 020514_SE_SAT105.bsp validity range:
    // 2004 JUN 11 05:01 : 04 - 2004 JUN 12 12:01:04
    // Bodies: MIMAS (601)      DIONE (604)      HYPERION (607)   SATURN (699)
    // ENCELADUS(602)  RHEA(605)       IAPETUS(608)
    //    TETHYS(603)     TITAN(606)      PHOEBE(609)

    // 981005_PLTEPH-DE405S.bsp validity range:
    // 2004 JUN 11 05:01:04 - 2004 JUN 12 12:01:04
    // Bodies: MERCURY BARYCENTER(1)  SATURN BARYCENTER(6)   MERCURY(199)
    // VENUS BARYCENTER(2)    URANUS BARYCENTER(7)   VENUS(299)
    // EARTH BARYCENTER(3)    NEPTUNE BARYCENTER(8)  MOON(301)
    // MARS BARYCENTER(4)     PLUTO BARYCENTER(9)    EARTH(399)
    // JUPITER BARYCENTER(5)  SUN(10)                MARS(499)

    USpice::init_all();

    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage;
    USpice::furnsh_absolute("maxq_unit_test_metakernel.tm");

    USpice::get_implied_result(ResultCode, ErrorMessage);
    EXPECT_EQ(ResultCode, ES_ResultCode::Success);

    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSEphemerisTime et;
    USpice::str2et(ResultCode, ErrorMessage, et, TEXT("2004 JUN 11 12:00:00.000"));

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    ResultCode = ES_ResultCode::Error;
    ErrorMessage.Empty();

    FSStateVector stateVector;
    FSEphemerisPeriod lt = FSEphemerisPeriod(1.5);
    FString targ = TEXT("CASSINI");
    FString obs = TEXT("EMB");
    FString ref = TEXT("J2000");
    ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::CN_S;

    USpice::spkezr(ResultCode, ErrorMessage, et, stateVector, lt, targ, obs, ref, abcorr);

    EXPECT_EQ(ResultCode, ES_ResultCode::Success);
    EXPECT_EQ(ErrorMessage.Len(), 0);
    EXPECT_GT(lt.seconds, 0.);
    EXPECT_NE(stateVector.r.x.km, 0.);
    EXPECT_NE(stateVector.r.y.km, 0.);
    EXPECT_NE(stateVector.r.z.km, 0.);
    EXPECT_NE(stateVector.v.dx.kmps, 0.);
    EXPECT_NE(stateVector.v.dy.kmps, 0.);
    EXPECT_NE(stateVector.v.dz.kmps, 0.);
}