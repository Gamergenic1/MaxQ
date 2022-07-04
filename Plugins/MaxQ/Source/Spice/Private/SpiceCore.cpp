// Copyright 2021 Gamergenic.  See full copyright notice in SpiceK2.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceCore.cpp
// 
// Implementation Comments
// 
// Purpose:  Core/Flow Control (Initialization, etc)
// 
// MaxQ:
// * Base API
// * Refined API
//    * C++
//    * Blueprints
//
// SpiceCore.cpp is part of the "refined C++ API".
//------------------------------------------------------------------------------

#include "SpiceCore.h"
#include "SpiceUtilities.h"

PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
extern "C"
{
#include "SpiceUsr.h"
}
PRAGMA_POP_PLATFORM_DEFAULT_PACKING

using namespace MaxQ::Private;

namespace MaxQ::Core
{
    SPICE_API void InitAll(bool PrintCallstack)
    {
        Reset();
        ClearAll();
        char szBuffer[SpiceLongMessageMaxLength];

        SpiceStringCopy(szBuffer, "SHORT,LONG");
        errprt_c("SET", sizeof(szBuffer), szBuffer);

        SpiceStringCopy(szBuffer, "REPORT");
        erract_c("SET", sizeof(szBuffer), szBuffer);

        SpiceStringCopy(szBuffer, "NULL");
        errdev_c("SET", sizeof(szBuffer), szBuffer);

        UE_LOG(LogSpice, Log,
            TEXT("\n*************************************************************************")
            TEXT("\n* MaxQ SPICE 'Init All'")
            TEXT("\n* All kernel memory and error states have been cleared and reset.")
            TEXT("\n***********************************************************************************")
        );

#if WITH_EDITORONLY_DATA
        if (PrintCallstack)
        {
            PrintScriptCallstack();
        }
#endif

        UnexpectedErrorCheck();
    }


    /*
    Exceptions
       This routine does not detect any errors.

       However, this routine is part of the CSPICE error
       handling mechanism.
    */
    SPICE_API void Reset()
    {
        reset_c();

        UE_LOG(LogSpice, Log, TEXT("MaxQ SPICE 'Reset' reset error handling state"));
    }

    SPICE_API void ClearAll()
    {
        kclear_c();
        clpool_c();

        UE_LOG(LogSpice, Log, TEXT("MaxQ SPICE 'Clear All' cleared kernel memory & pool"));
    }
}
