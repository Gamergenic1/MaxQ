// Copyright 2021 Gamergenic.  See full copyright notice in SpiceK2.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceData.cpp
// 
// Implementation Comments
// 
// Purpose:  Kernel Data reads, etc
// 
// MaxQ:
// * Base API
// * Refined API
//    * C++
//    * Blueprints
//
// SpiceData.cpp is part of the "refined C++ API".
//------------------------------------------------------------------------------

#include "SpiceData.h"
#include "SpiceUtilities.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"

PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
extern "C"
{
#include "SpiceUsr.h"
}
PRAGMA_POP_PLATFORM_DEFAULT_PACKING

using namespace MaxQ::Private;

namespace MaxQ::Data
{
    SPICE_API TArray<FString> EnumerateDirectory(const FString& relativeDirectory, bool ErrorIfNoFilesFound, ES_ResultCode* pResultCode, FString* pErrorMessage)
    {
        MakeErrorGutter(pResultCode, pErrorMessage);
        ES_ResultCode& ResultCode = *pResultCode;
        FString& ErrorMessage = *pErrorMessage;

        FString FileDirectory = toPath(relativeDirectory);

        if (!FPaths::DirectoryExists(FileDirectory))
        {
            ErrorMessage = FString::Printf(
                TEXT("Directory %s does not exist.\n(MaxQ internally expanded the path to %s.)\nIs the relative directory given to Enumerate Kernels correct?\n")
                TEXT("Directories are given relative to / Content,\n   'MyProject/Content/KernelFiles/Directory1'\nwould be given as\n   'KernelFiles/Directory1' "),
                *relativeDirectory, *FileDirectory);
            UE_LOG(LogSpice, Error, TEXT("MaxQ Spice Enumerate Kernels: %s"), *ErrorMessage);
            ResultCode = ES_ResultCode::Error;
            return {};
        }

        TArray<FString> kernelFilePaths {};

        TArray<FString> foundFiles;
        IFileManager::Get().FindFiles(foundFiles, *FileDirectory);
        if (foundFiles.Num() > 0)
        {
            for (auto file : foundFiles)
            {
                kernelFilePaths.Add(FPaths::Combine(relativeDirectory, file));
            }

            ResultCode = ES_ResultCode::Success;
            ErrorMessage.Empty();
        }
        else
        {
            ErrorMessage = FString::Printf(
                TEXT("no files were found in directory %s.\n(MaxQ internally expanded the path to %s.)\nIs the relative directory given to Enumerate Kernels correct?\n")
                TEXT("Directories are given relative to / Content,\n   'MyProject/Content/KernelFiles/Directory1'\nwould be given as\n   'KernelFiles/Directory1' "),
                *relativeDirectory, *FileDirectory);

            if (ErrorIfNoFilesFound)
            {
                UE_LOG(
                    LogSpice,
                    Error,
                    TEXT("******************************************************************\nMaxQ Spice Enumerate Kernels: %s\n")
                    TEXT("***********************************************************************************"), *ErrorMessage);
                ResultCode = ES_ResultCode::Error;
            }
            else
            {
                UE_LOG(LogSpice, Error, TEXT("MaxQ Spice Enumerate Kernels: %s"), *ErrorMessage);
                ErrorMessage.Empty();
            }
        }

        return kernelFilePaths;
    }

    SPICE_API bool Furnsh(const FString& relativePath, ES_ResultCode* ResultCode, FString* ErrorMessage)
    {
        FString fullPathToFile {toPath(relativePath)};

#ifdef SET_WORKING_DIRECTORY_IN_FURNSH
        // Get the current working directory...
        TCHAR buffer[SPICE_MAX_PATH];
        TCHAR* oldWorkingDirectory = _tgetcwd(buffer, sizeof(buffer) / sizeof(buffer[0]));

        // Trim the file name to just the full directory path...
        // (There isn't a guarantee SPICE will handle the other separator)
        FString fullPathToDirectory = FPaths::GetPath(fullPathToFile);
        fullPathToDirectory.ReplaceCharInline('/', '\\');

        if (FPaths::DirectoryExists(fullPathToDirectory))
        {
            // Set the current working directory
            _tchdir(*fullPathToDirectory);
        }
#endif

        furnsh_c(TCHAR_TO_ANSI(*fullPathToFile));

#ifdef SET_WORKING_DIRECTORY_IN_FURNSH
        // Reset the working directory to prior state...
        if (oldWorkingDirectory)
        {
            _tchdir(oldWorkingDirectory);
        }
#endif

        bool bSuccess = !ErrorCheck(ResultCode, ErrorMessage);
        if (bSuccess)
        {
            UE_LOG(LogSpice, Log, TEXT("MaxQ SPICE 'Furnsh' loaded kernel: %s"), *fullPathToFile);
        }
        return bSuccess;
    }

    SPICE_API bool Furnsh(const TArray<FString>& relativePaths, ES_ResultCode* ResultCode, FString* ErrorMessage)
    {
        bool bSuccess = true;
        for (auto file : relativePaths)
        {
            ES_ResultCode LocalResultCode;
            FString LocalErrorMessage;
            bool bLocalSuccess = Furnsh(file, &LocalResultCode, &LocalErrorMessage);
            if (!bLocalSuccess)
            {
                if (ResultCode) *ResultCode = LocalResultCode;
                if (ErrorMessage) *ErrorMessage = LocalErrorMessage;
            }
            bSuccess &= bLocalSuccess;
        }
        return bSuccess;
    }


    SPICE_API bool FurnshDirectory(const FString& relativeDirectory, ES_ResultCode* ResultCode, FString* ErrorMessage)
    {
        TArray<FString> relativePaths { EnumerateDirectory(relativeDirectory, true, ResultCode, ErrorMessage) };

        if (relativePaths.Num() > 0)
        {
            return Furnsh(relativePaths, ResultCode, ErrorMessage);
        }

        return false;
    }



    SPICE_API bool Unload(const FString& relativePath, ES_ResultCode* ResultCode /*= nullptr*/, FString* ErrorMessage /*= nullptr */)
    {
        FString absolutePath = toPath(relativePath);

        unload_c(TCHAR_TO_ANSI(*absolutePath));

        bool bSuccess = !ErrorCheck(ResultCode, ErrorMessage);
        if (bSuccess)
        {
            UE_LOG(LogSpice, Log, TEXT("MaxQ SPICE 'Unload' unloaded kernel : %s"), *absolutePath);
        }
        return bSuccess;
    }

    SPICE_API FSEphemerisTime Now()
    {
        auto now = FDateTime::UtcNow();
        auto j2000 = FDateTime::FromJulianDay(2451545.0);
        auto now_j2000 = now - j2000;

        return FSEphemerisTime(now_j2000.GetTotalSeconds());
    }

    // Size of FSAngle != sizeof double, ...
    template<>
    SPICE_API void Bodvrd(
        FSAngle& Value,
        const FString& bodynm,
        const FString& item,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        double _value;
        Bodvrd(_value, bodynm, item, ResultCode, ErrorMessage);
        Value = FSAngle::FromDegrees(_value);
    }

    // With a little extra complexity we could get rid of this specialized version...
    // Doubt if that's a net win, though.  Complexity FTL.
    SPICE_API void Bodvrd(
        double& Value,
        const FString& bodynm,
        const FString& item,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        constexpr SpiceInt N = sizeof (Value) / sizeof (SpiceDouble);
        SpiceDouble _result[N]; ZeroOut(Value);
        SpiceInt n_actual = 0;

        auto _bodynm = StringCast<ANSICHAR>(*bodynm);
        auto _item = StringCast<ANSICHAR>(*item);
        bodvrd_c(_bodynm.Get(), _item.Get(), N, &n_actual, _result);

        Value = _result[0];

        if (!ErrorCheck(ResultCode, ErrorMessage) && n_actual != N)
        {
            if (ResultCode) *ResultCode = ES_ResultCode::Error;
            if (ErrorMessage) *ErrorMessage = FString::Printf(TEXT("Blueprint request for %s_%s Expected double[%d] but proc returned double[%d]"), *bodynm, *item, N, n_actual);
        }
    }

    // TArray version...
    // Caller must initialize TArray size to expected size
    template<>
    SPICE_API void Bodvrd(
        TArray<double>& Values,
        const FString& bodynm,
        const FString& item,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        SpiceDouble* _result = Values.GetData();
        SpiceInt n_actual, n_expected = Values.Num();
        Values.Init(0, n_expected);

        auto _bodynm = StringCast<ANSICHAR>(*bodynm);
        auto _item = StringCast<ANSICHAR>(*item);
        bodvrd_c(_bodynm.Get(), _item.Get(), n_expected, &n_actual, _result);

        if (!ErrorCheck(ResultCode, ErrorMessage) && n_actual != n_expected)
        {
            if (ResultCode) *ResultCode = ES_ResultCode::Error;
            if (ErrorMessage) *ErrorMessage = FString::Printf(TEXT("Blueprint request for %s_%s Expected double[%d] but proc returned double[%d]"), *bodynm, *item, n_expected, n_actual);
        }
    }
    
    template<typename ValueType>
    SPICE_API void Bodvrd(
        ValueType& Value,
        const FString& bodynm,
        const FString& item,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        constexpr SpiceInt N = sizeof (Value) / sizeof (SpiceDouble);
        SpiceDouble _result[N]; ZeroOut(Value);
        SpiceInt n_actual = 0;

        auto _bodynm = StringCast<ANSICHAR>(*bodynm);
        auto _item = StringCast<ANSICHAR>(*item);

        bodvrd_c(_bodynm.Get(), _item.Get(), N, &n_actual, _result);

        Value = ValueType{ _result };

        if (!ErrorCheck(ResultCode, ErrorMessage) && n_actual != N)
        {
            if (ResultCode) *ResultCode = ES_ResultCode::Error;
            if (ErrorMessage) *ErrorMessage = FString::Printf(TEXT("Blueprint request for %s_%s Expected double[%d] but proc returned double[%d]"), *bodynm, *item, N, n_actual);
        }
    }

    template SPICE_API void Bodvrd<FSAngularVelocity>(FSAngularVelocity&, const FString& bodynm, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void Bodvrd<FSDistanceVector>(FSDistanceVector&, const FString& bodynm, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void Bodvrd<FSVelocityVector>(FSVelocityVector&, const FString& bodynm, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void Bodvrd<FSDimensionlessVector>(FSDimensionlessVector&, const FString& bodynm, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void Bodvrd<FSDistance>(FSDistance&, const FString& bodynm, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void Bodvrd<FSMassConstant>(FSMassConstant&, const FString& bodynm, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);


    // Size of FSAngle != sizeof double, ...
    template<>
    SPICE_API void Bodvcd(
        FSAngle& Value,
        int bodyid,
        const FString& item,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        double _value;
        Bodvcd(_value, bodyid, item, ResultCode, ErrorMessage);
        Value = FSAngle::FromDegrees(_value);
    }


    // TArray version...
    // Caller must initialize TArray size to expected size
    template<>
    SPICE_API void Bodvcd(
        TArray<double>& Values,
        int bodyid,
        const FString& item,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        SpiceDouble* _result = Values.GetData();
        SpiceInt n_actual, n_expected = Values.Num();
        Values.Init(0, n_expected);

        bodvcd_c(bodyid, TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);

        if (!ErrorCheck(ResultCode, ErrorMessage) && n_actual != n_expected)
        {
            if (ResultCode) *ResultCode = ES_ResultCode::Error;
            if (ErrorMessage) *ErrorMessage = FString::Printf(TEXT("Blueprint request for BODY%d_%s Expected double[%d] but proc returned double[%d]"), bodyid, *item, n_expected, n_actual);
        }
    }


    // With a little extra complexity we could get rid of this specialized version...
    // Doubt if that's a net win, though.  Complexity FTL.
    SPICE_API void Bodvcd(
        double& Value,
        int bodyid,
        const FString& item,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        constexpr SpiceInt N = sizeof (Value) / sizeof (SpiceDouble);
        SpiceDouble _result[N]; ZeroOut(Value);
        SpiceInt n_actual = 0;

        bodvcd_c(bodyid, TCHAR_TO_ANSI(*item), N, &n_actual, _result);

        Value = _result[0];

        if (!ErrorCheck(ResultCode, ErrorMessage) && n_actual != N)
        {
            if (ResultCode) *ResultCode = ES_ResultCode::Error;
            if (ErrorMessage) *ErrorMessage = FString::Printf(TEXT("Blueprint request for BODY%d_%s Expected double[%d] but proc returned double[%d]"), bodyid, *item, N, n_actual);
        }
    }

    template<typename ValueType>
    SPICE_API void Bodvcd(
        ValueType& Value,
        int bodyid,
        const FString& item,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        constexpr SpiceInt N = sizeof (Value) / sizeof (SpiceDouble);
        SpiceDouble _result[N]; ZeroOut(Value);
        SpiceInt n_actual = 0;

        bodvcd_c(bodyid, TCHAR_TO_ANSI(*item), N, &n_actual, _result);

        Value = ValueType{ _result };

        if (!ErrorCheck(ResultCode, ErrorMessage) && n_actual != N)
        {
            if (ResultCode) *ResultCode = ES_ResultCode::Error;
            if (ErrorMessage) *ErrorMessage = FString::Printf(TEXT("Blueprint request for BODY%d_%s Expected double[%d] but proc returned double[%d]"), bodyid, *item, N, n_actual);
        }
    }

    template SPICE_API void Bodvcd<FSAngularVelocity>(FSAngularVelocity&, int bodyid, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void Bodvcd<FSDistanceVector>(FSDistanceVector&, int bodyid, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void Bodvcd<FSVelocityVector>(FSVelocityVector&, int bodyid, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void Bodvcd<FSDimensionlessVector>(FSDimensionlessVector&, int bodyid, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void Bodvcd<FSDistance>(FSDistance&, int bodyid, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void Bodvcd<FSMassConstant>(FSMassConstant&, int bodyid, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);

    // TArray version...
    // Caller must initialize TArray size to expected size
    SPICE_API void Gdpool(
        double& Value,
        const FString& name,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        SpiceInt        _start{ 0 };
        SpiceInt        _room{ 1 };
        SpiceInt        _n{ 0 };
        SpiceDouble     _value { 0 };
        SpiceBoolean    _found = SPICEFALSE;

        gdpool_c(TCHAR_TO_ANSI(*name), _start, _room, &_n, &_value, &_found);

        Value = double{ _value };

        if (!ErrorCheck(ResultCode, ErrorMessage) && !_found)
        {
            if (ResultCode) *ResultCode = ES_ResultCode::Error;
            if (ErrorMessage) *ErrorMessage = FString::Printf(TEXT("Could not find pool variable %s"), *name);
        }
    }

    // Size of FSAngle != sizeof double, ...
    template<>
    SPICE_API void Gdpool(
        FSAngle& Value,
        const FString& name,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        double _value;
        Gdpool(_value, name, ResultCode, ErrorMessage);
        Value = FSAngle::FromDegrees(_value);
    }

    // TArray version...
    // Caller must initialize TArray size to expected size
    template<>
    SPICE_API void Gdpool(
        TArray<double>& Values,
        const FString& name,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        SpiceInt        _start{ 0 };
        SpiceInt        _room{ Values.Num() };
        SpiceInt        _n{ 0 };
        SpiceDouble*    _values{ Values.GetData() };
        SpiceBoolean    _found = SPICEFALSE;

        Values.Init(0, _room);

        gdpool_c(TCHAR_TO_ANSI(*name), _start, _room, &_n, _values, &_found);

        if (!ErrorCheck(ResultCode, ErrorMessage) && !_found)
        {
            if (ResultCode) *ResultCode = ES_ResultCode::Error;
            if (ErrorMessage) *ErrorMessage = FString::Printf(TEXT("Could not find pool variable %s"), *name);
        }
    }

    template<typename ValueType>
    SPICE_API void Gdpool(
        ValueType& Value,
        const FString& name,
        ES_ResultCode* ResultCode,
        FString* ErrorMessage
    )
    {
        SpiceInt        _start { 0 };
        SpiceInt        _room { sizeof (ValueType) / sizeof (SpiceDouble) };
        SpiceInt        _n { 0 };
        SpiceDouble     _values[sizeof (ValueType) / sizeof (SpiceDouble) ];
        SpiceBoolean    _found = SPICEFALSE;

        gdpool_c(TCHAR_TO_ANSI(*name), _start, _room, &_n, _values, &_found);

        Value = ValueType{ _values };

        if (!ErrorCheck(ResultCode, ErrorMessage) && !_found)
        {
            if (ResultCode) *ResultCode = ES_ResultCode::Error;
            if (ErrorMessage) *ErrorMessage = FString::Printf(TEXT("Could not find pool variable %s"), *name );
        }
    }

    template SPICE_API void Gdpool<FSAngularVelocity>(FSAngularVelocity&, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void Gdpool<FSDistanceVector>(FSDistanceVector&, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void Gdpool<FSVelocityVector>(FSVelocityVector&, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void Gdpool<FSDimensionlessVector>(FSDimensionlessVector&, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void Gdpool<FSDistance>(FSDistance&, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);
    template SPICE_API void Gdpool<FSMassConstant>(FSMassConstant&, const FString& item, ES_ResultCode* ResultCode, FString* ErrorMessage);


     SPICE_API bool Bodc2n(FString& name, int code /*= 399 */)
    {
        SpiceChar szBuffer[SPICE_MAX_PATH];
        ZeroOut(szBuffer);

        SpiceBoolean _found = SPICEFALSE;

        bodc2n_c((SpiceInt)code, sizeof(szBuffer), szBuffer, &_found);

        if (_found) name = szBuffer;

        // Reset the current spice error in case a spice exception happened.
        UnexpectedErrorCheck(true);

        return _found == SPICETRUE;
    }

    SPICE_API bool Bods2c(int& code, const FString& name /*= TEXT("EARTH") */)
    {
        SpiceInt _code = code;
        SpiceBoolean _found = SPICEFALSE;
        bods2c_c(TCHAR_TO_ANSI(*name), &_code, &_found);

        if (_found) code = (int)_code;

        // Reset the current spice error in case a spice exception happened.
        UnexpectedErrorCheck(true);

        return _found == SPICETRUE;
    }

    SPICE_API bool Bodfnd(int body, const FString& item /*= TEXT("RADII") */)
    {
        SpiceBoolean _found = bodfnd_c(body, TCHAR_TO_ANSI(*item));

        // Reset the current spice error in case a spice exception happened.
        UnexpectedErrorCheck(true);

        return _found == SPICETRUE;
    }

    SPICE_API void Boddef(const FString& name, int code /*= 3788040 */)
    {
        boddef_c(TCHAR_TO_ANSI(*name), (SpiceInt)code);

        UnexpectedErrorCheck(true);
    }
}
