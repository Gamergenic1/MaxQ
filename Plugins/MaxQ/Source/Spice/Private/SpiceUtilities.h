// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "SpiceTypes.h"

PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
extern "C"
{
#include "SpiceUsr.h"
}
PRAGMA_POP_PLATFORM_DEFAULT_PACKING

// This is private header to the module so we don't need a namespace
// to protect external users.  But, these are common names so putting
// them in a namespace will at least let us qualify the name if needed.
namespace SpiceUtilities
{
    extern const double pi;
    extern const double twopi;
    extern const double dpr;
    extern const double rpd;
}

// Utilities useful when interacting with CSPICE

SPICE_API FString toPath(const FString& file);

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

SPICE_API void CopyFrom(const SpicePlane& _plane, FSPlane& dest);
SPICE_API void CopyTo(const FSPlane& src, SpicePlane& _plane);
SPICE_API void CopyFrom(const SpiceEllipse& _ellipse, FSEllipse& dest);
SPICE_API void CopyTo(const FSEllipse& src, SpiceEllipse& _ellipse);

SPICE_API uint8 ErrorCheck(ES_ResultCode& ResultCode, FString& ErrorMessage, bool BeQuiet = false);
SPICE_API uint8 ErrorCheck(ES_ResultCode* ResultCode, FString* ErrorMessage, bool BeQuiet = false);
SPICE_API uint8 UnexpectedErrorCheck(bool bReset = true);

