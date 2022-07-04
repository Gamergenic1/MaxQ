// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceUtilities.h
// 
// Private API Comments
// 
// Purpose:
// Utilities useful when interacting with CSPICE
//
// Internal utilities that deal with CSPICE Toolkit types (SpiceDouble,
// SpiceEllipse, SpicePlanet, etc etc).
// CSPICE Toolkit types cannot appear in the public headers, but we still
// want a few utilities, etc.  This is the place for them.
// Also... Utilities that shouldn't be exposed because they're not stable
// (churn a lot) or otherwise just not somehting we'd like to expose...
//------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "SpiceTypes.h"

PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
extern "C"
{
#include "SpiceUsr.h"
}
PRAGMA_POP_PLATFORM_DEFAULT_PACKING

namespace MaxQ::Private
{
    FString toPath(const FString& file);

    template<class T>
    inline void ZeroOut(T(&value)[3][3])
    {
        FMemory::Memset(value, 0);
    }

    template<class T>
    inline void ZeroOut(T(&value)[6][6])
    {
        FMemory::Memset(value, 0);
    }


    template<class T>
    inline void ZeroOut(T& value)
    {
        FMemory::Memset(value, 0);
    }

    void CopyFrom(const SpicePlane& _plane, FSPlane& dest);
    void CopyTo(const FSPlane& src, SpicePlane& _plane);
    void CopyFrom(const SpiceEllipse& _ellipse, FSEllipse& dest);
    void CopyTo(const FSEllipse& src, SpiceEllipse& _ellipse);

    uint8 ErrorCheck(ES_ResultCode& ResultCode, FString& ErrorMessage, bool BeQuiet = false);
    uint8 ErrorCheck(ES_ResultCode* ResultCode, FString* ErrorMessage, bool BeQuiet = false);
    uint8 UnexpectedErrorCheck(bool bReset = true);
    void MakeErrorGutter(ES_ResultCode*& pResultCode, FString*& pErrorMessage);
}
