// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

extern const double pi;
extern const double _pos0_as_radians;
extern const double _pos1_as_radians;
extern const double _pos2_as_radians;
extern const double _pos3_as_radians;
extern const double _pos90_as_radians;
extern const double _pos180_as_radians;
extern const double _pos270_as_radians;
extern const double _pos360_as_radians;
extern const double _pos540_as_radians;
extern const double _neg0_as_radians;
extern const double _neg90_as_radians;
extern const double _neg180_as_radians;
extern const double _neg270_as_radians;
extern const double _neg360_as_radians;
extern const double _neg540_as_radians;

extern const FSEphemerisTime et0;
extern const FSStateVector state_target_9994_center_9995_eclipj2000_et0;
extern const FSStateVector state_target_9993_center_9994_eclipj2000_et0;
extern const FSStateVector state_target_9993_center_9995_eclipj2000_et0;
extern const FSStateVector state_target_9994_center_9995_j2000_et0;
extern const FSStateVector state_target_9993_center_9994_j2000_et0;
extern const FSStateVector state_target_9993_center_9995_j2000_et0;
bool IsNear(const FSStateVector&  state1, const FSStateVector& state2, double rtol = 0.00001, double vtol = 0.00000001);
bool IsNear(const FSDimensionlessVector&  vector1, const FSDimensionlessVector& vector2, double tol = 0.00001);

