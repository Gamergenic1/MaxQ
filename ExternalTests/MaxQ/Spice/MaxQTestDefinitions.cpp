// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "pch.h"

#include "MaxQTestDefinitions.h"

#define PI_MACRO 3.1415926535897932384626433832795028841971693993751058209749445923078164

const double pi = (double)PI_MACRO;
const double _pos0_as_radians = (double)(+0. * PI_MACRO);
const double _pos1_as_radians = (double)(+1. / 180. * PI_MACRO);
const double _pos2_as_radians = (double)(+2. / 180. * PI_MACRO);
const double _pos3_as_radians = (double)(+3. / 180. * PI_MACRO);
const double _pos90_as_radians = (double)(+0.5 * PI_MACRO);
const double _pos180_as_radians = (double)(+1. * PI_MACRO);
const double _pos270_as_radians = (double)(+1.5 * PI_MACRO);
const double _pos360_as_radians = (double)(+2. * PI_MACRO);
const double _pos540_as_radians = (double)(+3. * PI_MACRO);
const double _neg0_as_radians = (double)(-0. * PI_MACRO);
const double _neg90_as_radians = (double)(-0.5 * PI_MACRO);
const double _neg180_as_radians = (double)(-1. * PI_MACRO);
const double _neg270_as_radians = (double)(-1.5 * PI_MACRO);
const double _neg360_as_radians = (double)(-2. * PI_MACRO);
const double _neg540_as_radians = (double)(-3 * PI_MACRO);

const FSEphemerisTime et0(999870.5);
const FSStateVector state_target_9994_center_9995_eclipj2000_et0(FSDistanceVector(+9.9999916148762E+02, -1.2949996380422E+00, +0.0000000000000E+00), FSVelocityVector(+1.2949996380420E-05, +9.9999916148762E-03, +0.0000000000000E+00));
const FSStateVector state_target_9993_center_9994_eclipj2000_et0(FSDistanceVector(+1.6279454484152E+02, +1.6211827074811E+02, -8.6428223080490E+01), FSVelocityVector(-2.6473667587253E-03, +1.3157620906873E-03, +4.7683791858486E-03));
const FSStateVector state_target_9993_center_9995_eclipj2000_et0(FSDistanceVector(+1.1627937063291E+03, +1.6082327111007E+02, -8.6428223080490E+01), FSVelocityVector(-2.6344167623449E-03, +1.1315753705563E-02, +4.7683791858486E-03));
const FSStateVector state_target_9994_center_9995_j2000_et0(FSDistanceVector(+9.9999916148762E+02, -1.1881389382898E+00, -5.1512127295327E-01), FSVelocityVector(+1.2949996380420E-05, +9.1748129274911E-03, +3.9777682239084E-03));
const FSStateVector state_target_9993_center_9994_j2000_et0(FSDistanceVector(+1.6279454484152E+02, +1.8311977811427E+02, -1.4809399670080E+01), FSVelocityVector(-2.6473667587253E-03, -6.8956419479555E-04, +4.8982824704768E-03));
const FSStateVector state_target_9993_center_9995_j2000_et0(FSDistanceVector(+1.1627937063291E+03, +1.8193163917598E+02, -1.5324520943033E+01), FSVelocityVector(-2.6344167623449E-03, +8.4852487326956E-03, +8.8760506943852E-03));


bool IsNear(const FSStateVector& state1, const FSStateVector& state2, double rtol, double vtol)
{
    FSStateVector delta = state2 - state1;
    return delta.r.Magnitude() < rtol && delta.v.Magnitude() < vtol;
}

#if 0
const FString fileName = TEXT("celestialmath_unit_test_spk.bsp");
const FString Ref = TEXT("ECLIPJ2000");


int moon1 = 9993;
int body1 = 9994;
int center1 = 9995;
FSMassConstant BODY9995_GM = FSMassConstant(0.1);
FSMassConstant BODY9994_GM = FSMassConstant(0.01);

ES_ResultCode ResultCode;
FString ErrorMessage;

FSEphemerisTime et1_center(1000000);

FSConicElements conicsAtEpoch1;
conicsAtEpoch1.PerifocalDistance = 1000;
conicsAtEpoch1.Eccentricity = 0.;
conicsAtEpoch1.Inclination = 0.;
conicsAtEpoch1.ArgumentOfPeriapse = 0.;
conicsAtEpoch1.LongitudeOfAscendingNode = 0.;
conicsAtEpoch1.MeanAnomalyAtEpoch = 0.;
conicsAtEpoch1.Epoch = et1_center;
conicsAtEpoch1.GravitationalParameter = BODY9995_GM;


FSEphemerisTime et_start = et1_center - FSEphemerisPeriod::Day;
FSStateVector state1AtStart;
USpice::conics(ResultCode, ErrorMessage, conicsAtEpoch1, et_start, state1AtStart);

FSEphemerisTime et_end = et1_center + FSEphemerisPeriod::Day;
FSStateVector state1AtEnd;
USpice::conics(ResultCode, ErrorMessage, conicsAtEpoch1, et_end, state1AtEnd);


FSConicElements conicsAtEpoch2;
conicsAtEpoch2.PerifocalDistance = 100;
conicsAtEpoch2.Eccentricity = 0.5;
conicsAtEpoch2.Inclination = 45.;
conicsAtEpoch2.ArgumentOfPeriapse = 90.;
conicsAtEpoch2.LongitudeOfAscendingNode = 45.;
conicsAtEpoch2.MeanAnomalyAtEpoch = 300.;
conicsAtEpoch2.Epoch = et1_center;
conicsAtEpoch2.GravitationalParameter = BODY9994_GM;

FSStateVector state2AtStart;
USpice::conics(ResultCode, ErrorMessage, conicsAtEpoch2, et_start, state2AtStart);

FSStateVector state2AtEnd;
USpice::conics(ResultCode, ErrorMessage, conicsAtEpoch2, et_end, state2AtEnd);
#endif