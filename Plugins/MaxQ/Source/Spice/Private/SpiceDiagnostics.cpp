// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// USpiceDiagnostics.cpp
// 
// Implementation Comments
// 
// USpiceDiagnostics : public UBlueprintFunctionLibrary
// 
// See API comments in USpiceDiagnostics.h
//------------------------------------------------------------------------------

#include "SpiceDiagnostics.h"
#include "SpiceTypes.h"
#include "Containers/StringFwd.h"
#include "Spice.h"
#include "SpiceUtilities.h"

#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>


PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
extern "C"
{
#include "SpiceUsr.h"
}
PRAGMA_POP_PLATFORM_DEFAULT_PACKING

using namespace MaxQ;
using namespace MaxQ::Private;

DEFINE_LOG_CATEGORY(LogSpiceDiagnostics);

void USpiceDiagnostics::DumpSpkSummary(ES_ResultCode& ResultCode, FString& ErrorMessage, FString& LogString, const FString& relativeLskPath, const FString& relativeSpkPath)
{
    LogString.Empty();
    FString fullPathToFile = toPath(relativeSpkPath);

#ifdef SET_WORKING_DIRECTORY_IN_FURNSH
    // Get the current working directory...
    TCHAR buffer[WINDOWS_MAX_PATH];
    TCHAR* oldWorkingDirectory = _tgetcwd(buffer, sizeof(buffer) / sizeof(buffer[0]));

    // Trim the file name to just the full directory path...
    FString fullPathToDirectory = FPaths::GetPath(fullPathToFile);
    fullPathToDirectory.ReplaceCharInline('/', '\\');

    if (FPaths::DirectoryExists(fullPathToDirectory))
    {
        // Set the current working directory
        _tchdir(*fullPathToDirectory);
    }
#endif

    // Implementation from:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/spkcov_c.html
    constexpr int32  MAXIV{ 1000 };
    constexpr int32  WINSIZ{ (2 * MAXIV) };
    constexpr int32  TIMLEN{ 51 };
    constexpr int32  MAXOBJ{ 1000 };

    /*
        Local variables
    */

    SPICEDOUBLE_CELL(cover, WINSIZ);
    SPICEINT_CELL(ids, MAXOBJ);

    SpiceChar               timstr[TIMLEN];

    SpiceDouble             b;
    SpiceDouble             e;

    SpiceInt                i;
    SpiceInt                j;
    SpiceInt                niv;
    SpiceInt                obj;


    /*
    Load a leapseconds kernel for output time conversion.
    spkcov_c itself does not require a leapseconds kernel.
    */
    furnsh_c(TCHAR_TO_ANSI(*toPath(relativeLskPath)));

    if (ErrorCheck(ResultCode, ErrorMessage)) return;

    /*
    Get name of SPK file.
    */
    LogString += FString::Printf(TEXT("Name of LSK file > %s\n"), *relativeLskPath);

    /*
    Find the set of objects in the SPK file.
    */
    spkobj_c(TCHAR_TO_ANSI(*toPath(relativeSpkPath)), &ids);

    if (ErrorCheck(ResultCode, ErrorMessage)) return;

    LogString += FString::Printf(TEXT("Name of SPK file > %s\n"), *relativeSpkPath);

    /*
    We want to display the coverage for each object.Loop over
    the contents of the ID code set, find the coverage for
    each item in the set, and display the coverage.
    */
    for (i = 0; i < card_c(&ids); i++)
    {
        /*
        Find the coverage window for the current object.
        Empty the coverage window each time so we don't
        include data for the previous object.
        */
        obj = SPICE_CELL_ELEM_I(&ids, i);

        scard_c(0, &cover);
        spkcov_c(TCHAR_TO_ANSI(*toPath(relativeSpkPath)), obj, &cover);

        if (ErrorCheck(ResultCode, ErrorMessage)) return;

        /*
        Get the number of intervals in the coverage window.
        */
        niv = wncard_c(&cover);

        /*
        Display a simple banner.
        */
        LogString += FString::Printf(TEXT("%s\n"), TEXT("========================================"));

        SpiceBoolean found;
        char szBodyName[256];
        bodc2n_c(obj, sizeof(szBodyName) - 1, szBodyName, &found);

        LogString += FString::Printf(TEXT("Coverage for object %d (%s)\n"), (int)obj, found ? *FString(szBodyName) : TEXT("NAIF ID not found"));

        /*
        Convert the coverage interval start and stop times to TDB
        calendar strings.
        */
        for (j = 0; j < niv; j++)
        {
            /*
            Get the endpoints of the jth interval.
            */
            wnfetd_c(&cover, j, &b, &e);

            /*
            Convert the endpoints to TDB calendar
            format time strings and display them.
            */
            timout_c(b,
                "YYYY MON DD HR:MN:SC.### (TDB) ::TDB",
                TIMLEN,
                timstr);

            LogString += FString::Printf(TEXT("\n")
                TEXT("Interval:  %d\n")
                TEXT("Start:     %s\n"),
                (int)j,
                *FString(timstr));

            timout_c(e,
                "YYYY MON DD HR:MN:SC.### (TDB) ::TDB",
                TIMLEN,
                timstr);
            LogString += FString::Printf(TEXT("Stop:      %s\n"), *FString(timstr));

        }
    }

    LogString += FString::Printf(TEXT("%s\n"), TEXT("========================================"));

    UE_LOG(LogSpiceDiagnostics, Log, TEXT("Spice SPK Coverage diagnostic:\n%s"), *LogString);

#ifdef SET_WORKING_DIRECTORY_IN_FURNSH
    // Reset the working directory to prior state...
    if (oldWorkingDirectory)
    {
        _tchdir(oldWorkingDirectory);
    }
#endif

    ErrorCheck(ResultCode, ErrorMessage);
}

void USpiceDiagnostics::DumpPckSummary(ES_ResultCode& ResultCode, FString& ErrorMessage, FString& LogString, const FString& relativeLskPath /*= TEXT("NonAssetData/naif/kernels/Generic/LSK/naif0012.tls")*/, const FString& relativePckPath /*= TEXT("NonAssetData/naif/kernels/Generic/PCK/earth_200101_990628_predict.bpc") */)
{
    LogString.Empty();
    FString fullPathToFile = toPath(relativePckPath);

#ifdef SET_WORKING_DIRECTORY_IN_FURNSH
    // Get the current working directory...
    TCHAR buffer[WINDOWS_MAX_PATH];
    TCHAR* oldWorkingDirectory = _tgetcwd(buffer, sizeof(buffer) / sizeof(buffer[0]));

    // Trim the file name to just the full directory path...
    FString fullPathToDirectory = FPaths::GetPath(fullPathToFile);
    fullPathToDirectory.ReplaceCharInline('/', '\\');

    if (FPaths::DirectoryExists(fullPathToDirectory))
    {
        // Set the current working directory
        _tchdir(*fullPathToDirectory);
    }
#endif

    // Implementation from:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/pckfrm_c.html

    /*
        Local parameters
    */
    constexpr int32  FILSIZ{ 256 };
    constexpr int32  MAXIV{ 1000 };
    constexpr int32  WINSIZ{ (2 * MAXIV) };
    constexpr int32  TIMLEN{ 51 };
    constexpr int32  MAXOBJ{ 1000 };

    /*
    Local variables
    */
    SPICEDOUBLE_CELL(cover, WINSIZ);
    SPICEINT_CELL(ids, MAXOBJ);

    SpiceChar               timstr[TIMLEN];

    SpiceDouble             b{ 0. };
    SpiceDouble             e{ 0. };

    SpiceInt                i;
    SpiceInt                j;
    SpiceInt                niv;
    SpiceInt                obj;


    /*
        Load a leapseconds kernel for output time conversion.
        pckcov_c itself does not require a leapseconds kernel.
        */

    furnsh_c(TCHAR_TO_ANSI(*toPath(relativeLskPath)));

    if (ErrorCheck(ResultCode, ErrorMessage)) return;

    LogString += FString::Printf(TEXT("Name of LSK file > %s\n"), *relativeLskPath);


    /*
        Find the set of frames in the PCK file.
        */
    pckfrm_c(TCHAR_TO_ANSI(*toPath(relativePckPath)), &ids);

    if (ErrorCheck(ResultCode, ErrorMessage)) return;

    LogString += FString::Printf(TEXT("Name of PCK file > %s\n"), *relativePckPath);

    /*
        We want to display the coverage for each frame.Loop over
        the contents of the ID code set, find the coverage for
        each item in the set, and display the coverage.
        */
    for (i = 0; i < card_c(&ids); i++)
    {
        /*
            Find the coverage window for the current frame.
            Empty the coverage window each time so we don't
            include data for the previous frame.
            */
        obj = SPICE_CELL_ELEM_I(&ids, i);

        scard_c(0, &cover);
        pckcov_c(TCHAR_TO_ANSI(*toPath(relativePckPath)), obj, &cover);

        if (ErrorCheck(ResultCode, ErrorMessage)) return;

        /*
            Get the number of intervals in the coverage window.
            */
        niv = wncard_c(&cover);

        /*
            Display a simple banner.
            */
        LogString += FString::Printf(TEXT("%s\n"), TEXT("========================================"));

        LogString += FString::Printf(TEXT("Coverage for frame %d\n"), (int)obj);

        /*
            Convert the coverage interval start and stop times to TDB
            calendar strings.
            */
        for (j = 0; j < niv; j++)
        {
            /*
                Get the endpoints of the jth interval.
                . /
                wnfetd_c(&cover, j, &b, &e);

            */
            timout_c(b,
                "YYYY MON DD HR:MN:SC.### (TDB) ::TDB",
                TIMLEN,
                timstr);

            LogString += FString::Printf(TEXT("\n")
                TEXT("Interval:  %d\n")
                TEXT("Start:     %s\n"),
                (int)j,
                *FString(timstr));

            timout_c(e,
                "YYYY MON DD HR:MN:SC.### (TDB) ::TDB",
                TIMLEN,
                timstr);
            LogString += FString::Printf(TEXT("Stop:      %s\n"), *FString(timstr));
        }
    }

    LogString += FString::Printf(TEXT("%s\n"), TEXT("========================================"));


    UE_LOG(LogSpiceDiagnostics, Log, TEXT("Spice Binary PCK Coverage diagnostic:\n%s"), *LogString);

#ifdef SET_WORKING_DIRECTORY_IN_FURNSH
    // Reset the working directory to prior state...
    if (oldWorkingDirectory)
    {
        _tchdir(oldWorkingDirectory);
    }
#endif

    ErrorCheck(ResultCode, ErrorMessage);
}

void USpiceDiagnostics::DumpCkSummary(ES_ResultCode& ResultCode, FString& ErrorMessage, FString& LogString, const FString& relativeLskPath /*= TEXT("NonAssetData/naif/kernels/Generic/LSK/naif0012.tls")*/, const FString& relativeSclkPath /*= TEXT("NonAssetData/naif/kernels/INSIGHT/SCLK/NSY_SCLKSCET.00023.tsc")*/, const FString& relativeCkPath /*= TEXT("NonAssetData/naif/kernels/INSIGHT/CK/ckckck") */)
{
    LogString.Empty();
    FString fullPathToFile = toPath(relativeCkPath);

#ifdef SET_WORKING_DIRECTORY_IN_FURNSH
    // Get the current working directory...
    TCHAR buffer[WINDOWS_MAX_PATH];
    TCHAR* oldWorkingDirectory = _tgetcwd(buffer, sizeof(buffer) / sizeof(buffer[0]));

    // Trim the file name to just the full directory path...
    FString fullPathToDirectory = FPaths::GetPath(fullPathToFile);
    fullPathToDirectory.ReplaceCharInline('/', '\\');

    if (FPaths::DirectoryExists(fullPathToDirectory))
    {
        // Set the current working directory
        _tchdir(*fullPathToDirectory);
    }
#endif


    // Implementation from:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/ckcov_c.html

    /*
        Local parameters
        */
    constexpr int32  FILSIZ{ 256 };
    constexpr int32  MAXIV{ 100000 };
    constexpr int32  WINSIZ{ (2 * MAXIV) };
    constexpr int32  TIMLEN{ 51 };
    constexpr int32  MAXOBJ{ 1000 };

    /*
            Local variables
            */
    SPICEDOUBLE_CELL(cover, WINSIZ);
    SPICEINT_CELL(ids, MAXOBJ);

    SpiceChar               timstr[TIMLEN];

    SpiceDouble             b;
    SpiceDouble             e;

    SpiceInt                i;
    SpiceInt                j;
    SpiceInt                niv;
    SpiceInt                obj;


    /*
        Load a leapseconds kernel and SCLK kernel for output time
        conversion.Note that we assume a single spacecraft clock is
        associated with all of the objects in the CK.
        */

    furnsh_c(TCHAR_TO_ANSI(*toPath(relativeLskPath)));

    if (ErrorCheck(ResultCode, ErrorMessage)) return;
    LogString += FString::Printf(TEXT("Name of LSK file > %s\n"), *relativeLskPath);

    furnsh_c(TCHAR_TO_ANSI(*toPath(relativeSclkPath)));
    if (ErrorCheck(ResultCode, ErrorMessage)) return;
    LogString += FString::Printf(TEXT("Name of SCLK file > %s\n"), *relativeSclkPath);

    /*
        Find the set of objects in the CK file.
        */
    ckobj_c(TCHAR_TO_ANSI(*toPath(relativeCkPath)), &ids);

    if (ErrorCheck(ResultCode, ErrorMessage)) return;

    /*
        We want to display the coverage for each object.Loop over
        the contents of the ID code set, find the coverage for
        each item in the set, and display the coverage.
        */
    for (i = 0; i < card_c(&ids); i++)
    {
        /*
            Find the coverage window for the current object.
            Empty the coverage window each time so we don't
            include data for the previous object.
            */
        obj = SPICE_CELL_ELEM_I(&ids, i);

        scard_c(0, &cover);
        ckcov_c(TCHAR_TO_ANSI(*toPath(relativeCkPath)), obj, SPICEFALSE,
            "INTERVAL", 0.0, "TDB", &cover);

        if (ErrorCheck(ResultCode, ErrorMessage)) return;
        /*
            Get the number of intervals in the coverage window.
            */
        niv = wncard_c(&cover);

        /*
            Display a simple banner.
            */
        LogString += FString::Printf(TEXT("%s\n"), TEXT("========================================"));

        LogString += FString::Printf(TEXT("Coverage for object %d\n"), (int)obj);

        /*
            Convert the coverage interval start and stop times to TDB
            calendar strings.
            */
        for (j = 0; j < niv; j++)
        {
            /*
                Get the endpoints of the jth interval.
                */
            wnfetd_c(&cover, j, &b, &e);

            /*
                Convert the endpoints to TDB calendar
                format time strings and display them.
                */
            timout_c(b,
                "YYYY MON DD HR:MN:SC.###### (TDB) ::TDB",
                TIMLEN,
                timstr);

            LogString += FString::Printf(TEXT("\n")
                TEXT("Interval:  %d\n")
                TEXT("Start:     %s\n"),
                (int)j,
                *FString(timstr));

            timout_c(e,
                "YYYY MON DD HR:MN:SC.###### (TDB) ::TDB",
                TIMLEN,
                timstr);
            LogString += FString::Printf(TEXT("Stop:      %s\n"), *FString(timstr));

        }
    }

    LogString += FString::Printf(TEXT("%s\n"), TEXT("========================================"));

    UE_LOG(LogSpiceDiagnostics, Log, TEXT("Spice CK Coverage diagnostic:\n%s"), *LogString);

#ifdef SET_WORKING_DIRECTORY_IN_FURNSH
    // Reset the working directory to prior state...
    if (oldWorkingDirectory)
    {
        _tchdir(oldWorkingDirectory);
    }
#endif

    ErrorCheck(ResultCode, ErrorMessage);
}

void USpiceDiagnostics::DumpLoadedKernelFiles(FString& LogString)
{
    LogString.Empty();

    // From:
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/kinfo_c.html

    /*
        Local constants.
        */
    constexpr uint32 FILLEN{ 256 };
    constexpr uint32 TYPLEN{ 33 };
    constexpr uint32 SRCLEN{ 256 };

    /*
    Local variables.
    */
    SpiceInt        which;
    SpiceInt        count;
    SpiceInt        handle;

    SpiceChar       file[FILLEN];
    SpiceChar       filtyp[TYPLEN];
    SpiceChar       srcfil[SRCLEN];

    SpiceBoolean    found;


    /*
        Find out the total number of kernels in the kernel pool.
        */
    ktotal_c("all", &count);

    if (count == 0)
    {
        LogString += TEXT("No files loaded at this time.\n");
    }
    else
    {
        LogString += TEXT("The loaded files files are: \n\n");
    }

    /*
        Find the file name, typeand source for each of the
        kernels in the kernel pooland print its type.
        */
    for (which = 0; which < count; which++)
    {

        kdata_c(which, "all", FILLEN, TYPLEN, SRCLEN,
            file, filtyp, srcfil, &handle, &found);

        kinfo_c(file, TYPLEN, SRCLEN,
            filtyp, srcfil, &handle, &found);

        if (eqstr_c(filtyp, "SPK"))
        {
            LogString += FString::Printf(TEXT("%s is an SPK file.\n"), *FString(file));
        }
        else if (eqstr_c(filtyp, "CK"))
        {
            LogString += FString::Printf(TEXT("%s is a CK file.\n"), *FString(file));
        }
        else if (eqstr_c(filtyp, "PCK"))
        {
            LogString += FString::Printf(TEXT("%s is a PCK file.\n"), *FString(file));
        }
        else if (eqstr_c(filtyp, "DSK"))
        {
            LogString += FString::Printf(TEXT("%s is a DSK file.\n"), *FString(file));
        }
        else if (eqstr_c(filtyp, "EK"))
        {
            LogString += FString::Printf(TEXT("%s is an EK file.\n"), *FString(file));
        }
        else if (eqstr_c(filtyp, "META"))
        {
            LogString += FString::Printf(TEXT("%s is a meta-text kernel.\n"), *FString(file));
        }
        else
        {
            LogString += FString::Printf(TEXT("%s is a text kernel.\n"), *FString(file));
        }
    }

    UE_LOG(LogSpiceDiagnostics, Log, TEXT("Spice Loaded Kernel Files dump diagnostic:\n%s"), *LogString);

    UnexpectedErrorCheck(true);
}
