// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceUtilities.cpp
//
// Implementation Comments
// 
// MaxQ:
// * Base API
// * Refined API
//    * C++
//    * Blueprints
//
// MaxQ: Three APIs
// * Base API :  Initial Harness for studying integration with UE
//    ~ USpice, USpiceTypes, etc
// * Refined API
//    * C++ :  C++-friendly
//      ~ SpiceMath.h, SpiceOperators.h, etc
//    * Blueprints :  C++-friendly
//      ~ USpiceK2, UK2Node_unorm, etc
// 
// USpice is part of the base API, where CSPICE functionality is initially
// exposed.
// It is maintained for backwards compatibility, when possible deprecation is
// preferred to a breaking change.
// What is here is usable from either blueprints or c++, but the Refined C++/
// Blueprint APIs will be more convenient to the user when functionality is
// migrated there.
// 
// See implementation comments in Spice.cpp.
//------------------------------------------------------------------------------

#include "SpiceUtilities.h"
#include "Misc/AssertionMacros.h"
#include "CoreMinimal.h"
#include "Misc/Paths.h"
#include "SpicePlatformDefs.h"

namespace MaxQ::Private
{
    FString toPath(const FString& file)
    {
        FString path = file;

        // BaseGame.ini [/Script/UnrealEd.ProjectPackagingSettings] DirectoriesToAlwaysStageAsNonUFS
        // is relative to the project's Content directory...  Copying kernel files, then, means the directory must be relative to the content directory
    #if WITH_EDITOR
        if (path.StartsWith(TEXT("Content")))
        {
            UE_LOG(LogSpice, Error, TEXT("BREAKING SPICE BEHAVIOR CHANGE!!  Spice data must be in project /Content directory.  All paths are now relative to /Content"));
            UE_LOG(LogSpice, Error, TEXT("Is relative to Content directory: %s"), *file);
        }
    #endif

        if(FPaths::IsRelative(path))
        {
            auto gameDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
            path = FPaths::Combine(gameDir, path);
        }

        const TCHAR* PathDelimiter = FPlatformMisc::GetDefaultPathSeparator();
        if (PathDelimiter && PathDelimiter[0] != '\\')
        {
            path.ReplaceInline(TEXT("\\"), PathDelimiter);
        }
        else
        {
            path.ReplaceInline(TEXT("/"), PathDelimiter);
        }
        return path;
    }

    void CopyFrom(const SpicePlane& _plane, FSPlane& dest)
    {
        SpiceDouble _planeNormal[3] = { 0, 0, 0 }, _planeConstant = 0;

        pl2nvc_c(&_plane, _planeNormal, &_planeConstant);

        dest.normal = FSDimensionlessVector(_planeNormal);
        dest.constant = _planeConstant;
    }


    void CopyTo(const FSPlane& src, SpicePlane& _plane)
    {
        SpiceDouble _planeNormal[3], _planeConstant = (SpiceDouble)(src.constant.AsSpiceDouble());
        src.normal.CopyTo(_planeNormal);

        memset(&_plane, 0, sizeof(_plane));

        nvc2pl_c(_planeNormal, _planeConstant, &_plane);

        // Ensure a failure in nvc2pl is logged
        // ...but let the caller pick up the signal and determine what to do
        UnexpectedErrorCheck(false);
    }


    void CopyFrom(const SpiceEllipse& _ellipse, FSEllipse& dest)
    {
        SpiceDouble _center[3] = { 0, 0, 0 }, _v_major[3] = { 0, 0, 0 }, _v_minor[3] = { 0, 0, 0 };

        el2cgv_c(&_ellipse, _center, _v_major, _v_minor);

        dest.center = FSDistanceVector(_center);
        dest.v_major = FSDistanceVector(_v_major);
        dest.v_minor = FSDistanceVector(_v_minor);
    }


    void CopyTo(const FSEllipse& src, SpiceEllipse& _ellipse)
    {
        SpiceDouble _center[3], _v_major[3], _v_minor[3];

        src.center.CopyTo(_center);
        src.v_major.CopyTo(_v_major);
        src.v_minor.CopyTo(_v_minor);

        memset(&_ellipse, 0, sizeof(_ellipse));

        cgv2el_c(_center, _v_major, _v_minor, &_ellipse);

        // Ensure a failure in cgv2el is logged
        // ...but let the caller pick up the signal and determine what to do
        UnexpectedErrorCheck(false);
    }


    uint8 ErrorCheck(ES_ResultCode& ResultCode, FString& ErrorMessage, bool BeQuiet)
    {
        uint8 failed = failed_c();

        if (!failed)
        {
            ResultCode = ES_ResultCode::Success;
            ErrorMessage.Empty();
        }
        else
        {
            ResultCode = ES_ResultCode::Error;
            char szBuffer[SpiceLongMessageMaxLength];

            szBuffer[0] = '\0';
            getmsg_c("LONG", sizeof(szBuffer), szBuffer);

            if (!SpiceStringLengthN(szBuffer, sizeof(szBuffer)))
            {
                szBuffer[0] = '\0';
                getmsg_c("SHORT", sizeof(szBuffer), szBuffer);
            }

            ErrorMessage = szBuffer;

            if (!BeQuiet)
            {
                // Only logged as a warning, because the only the application knows if it was totally unexpected,
                // and it has the ability to categorize it as a true error.
                UE_LOG(LogSpice, Warning, TEXT("USpice Runtime Error: %s"), *ErrorMessage);

                PrintScriptCallstack();
            }

            reset_c();
        }

        return failed;
    }


    uint8 ErrorCheck(ES_ResultCode* ResultCode, FString* ErrorMessage, bool BeQuiet /*= false*/)
    {
        MakeErrorGutter(ResultCode, ErrorMessage);
        return ErrorCheck(*ResultCode, *ErrorMessage, BeQuiet);
    }

    void MakeErrorGutter(ES_ResultCode* &pResultCode, FString* &pErrorMessage)
    {
        static ES_ResultCode DummyResultCode;
        static FString DummyErrorMessage;
        if (pResultCode == nullptr) pResultCode = &DummyResultCode;
        if (pErrorMessage == nullptr) pErrorMessage = &DummyErrorMessage;
    }

    uint8 UnexpectedErrorCheck(bool bReset)
    {
        uint8 failed = failed_c();

        if (failed)
        {
            char szBuffer[SpiceLongMessageMaxLength];

            szBuffer[0] = '\0';
            getmsg_c("LONG", sizeof(szBuffer), szBuffer);

            if (!SpiceStringLengthN(szBuffer, sizeof(szBuffer)))
            {
                szBuffer[0] = '\0';
                getmsg_c("SHORT", sizeof(szBuffer), szBuffer);
            }

            FString ErrorMessage = szBuffer;
            UE_LOG(LogSpice, Warning, TEXT("USpice Runtime Unexpected Error: %s"), *ErrorMessage);

            PrintScriptCallstack();

            if (bReset)
            {
                reset_c();
            }
        }

        return failed;
    }
}
