// Copyright 2021 Gamergenic.  See full copyright notice in SpiceK2.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceOperators.cpp
// 
// Implementation Comments
// 
// C++ Operators for ue-wrapped CSPICE types.
// 
// Purpose:  Blueprint implementations of CSPICE Type wrappers  
// 
// MaxQ:
// * Base API
// * Refined API
//    * C++
//    * Blueprints
//
// SpiceOperators.cpp is part of the "refined C++ API".
//------------------------------------------------------------------------------

#include "SpiceOperators.h"

PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
extern "C"
{
#include "SpiceUsr.h"
}
PRAGMA_POP_PLATFORM_DEFAULT_PACKING

FSQuaternion operator*(const FSQuaternion& lhs, const FSQuaternion& rhs)
{
    SpiceDouble _qout[4];
    SpiceDouble _q1[4];  lhs.CopyTo(_q1);
    SpiceDouble _q2[4];  rhs.CopyTo(_q2);

    qxq_c(_q1, _q2, _qout);
    return FSQuaternion{_qout};
}
