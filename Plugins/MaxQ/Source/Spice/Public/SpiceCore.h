// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceCore.h
// 
// API Comments
// 
// Purpose:  Core/Flow Control (Initialization, etc)
// 
// MaxQ:
// * Base API
// * Refined API
//    * C++
//    * Blueprints
//
// SpiceCore.h is part of the "refined C++ API".
//------------------------------------------------------------------------------

#pragma once

#include "SpiceTypes.h"

namespace MaxQ::Core
{
    SPICE_API void InitAll(bool bPrintCallstack = false);
    SPICE_API void Reset();
    SPICE_API void ClearAll();
};