// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

#include "Spice.h"


PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
extern "C"
{
#include "SpiceUsr.h"
}
PRAGMA_POP_PLATFORM_DEFAULT_PACKING

#define LONG_MESSAGE_MAX_LENGTH 1841

// May need a little rewrite for any platforms that don't support stack allocations.
#define StackAlloc _alloca


USpice::USpice()
{

}


void USpice::SwizzleToUE(const double(&v)[3], FVector& ue)
{
    ue = FVector(v[1], v[0], v[2]);
}

void USpice::SwizzleToSpice(const FVector& ue, double(&v)[3])
{
    v[0] = ue.Y;
    v[1] = ue.X;
    v[2] = ue.Z;
}

void USpice::SwizzleToUE(const double(&q)[4], FQuat& ue)
{
    ue = FQuat(-q[2], -q[1], -q[3], q[0]);
}

void USpice::SwizzleToSpice(const FQuat& ue, double(&q)[4])
{
    q[0] = ue.W;
    q[1] = -ue.Y;
    q[2] = -ue.X;
    q[3] = -ue.Z;
}



template<class T>
inline void ZeroOut(T(&value)[3][3])
{
    memset(value, 0, sizeof(value));
}

template<class T>
inline void ZeroOut(T(&value)[6][6])
{
    memset(value, 0, sizeof(value));
}


template<class T>
inline void ZeroOut(T& value)
{
    memset(&value, 0, sizeof(value));
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
    SpiceDouble _planeNormal[3], _planeConstant = (SpiceDouble)(src.constant.AsDouble());
    src.normal.CopyTo(_planeNormal);

    memset(&_plane, 0, sizeof(_plane));

    nvc2pl_c(_planeNormal, _planeConstant, &_plane);

    // Ensure a failure in nvc2pl is logged
    // ...but let the caller pick up the signal and determine what to do
    USpice::UnexpectedErrorCheck(false);
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
    USpice::UnexpectedErrorCheck(false);
}


uint8 USpice::ErrorCheck(ES_ResultCode& ResultCode, FString& ErrorMessage)
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
        char szBuffer[LONG_MESSAGE_MAX_LENGTH];

        szBuffer[0] = '\0';
        getmsg_c("LONG", sizeof(szBuffer), szBuffer);

        if (!strnlen_s(szBuffer, sizeof(szBuffer)))
        {
            szBuffer[0] = '\0';
            getmsg_c("SHORT", sizeof(szBuffer), szBuffer);
        }

        ErrorMessage = szBuffer;

        UE_LOG(LogTemp, Warning, TEXT("USpice Runtime Error: %s"), *ErrorMessage);

        reset_c();
    }

    return failed;
}


uint8 USpice::UnexpectedErrorCheck(bool bReset)
{
    uint8 failed = failed_c();

    if (failed)
    {
        char szBuffer[LONG_MESSAGE_MAX_LENGTH];

        szBuffer[0] = '\0';
        getmsg_c("LONG", sizeof(szBuffer), szBuffer);

        if (!strnlen_s(szBuffer, sizeof(szBuffer)))
        {
            szBuffer[0] = '\0';
            getmsg_c("SHORT", sizeof(szBuffer), szBuffer);
        }

        FString ErrorMessage = szBuffer;
        UE_LOG(LogTemp, Warning, TEXT("USpice Runtime Unexpected Error: %s"), *ErrorMessage);

        if (bReset)
        {
            reset_c();
        }
    }

    return failed;
}

void USpice::enumerate_kernels(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    TArray<FString>& kernelFilePaths,
    const FString& relativeDirectory
)
{
    auto gameDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());

    kernelFilePaths.Empty();

    TArray<FString> foundFiles;
    IFileManager::Get().FindFiles(foundFiles, *FPaths::Combine(gameDir,relativeDirectory));
    if (foundFiles.Num() > 0)
    {
        for (auto file : foundFiles)
        {
            kernelFilePaths.Add(FPaths::Combine(relativeDirectory,file));
        }
    }

    ResultCode = ES_ResultCode::Success;
    ErrorMessage.Empty();
}


void USpice::furnsh(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& file
)
{
    auto gameDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());

    auto path = FPaths::Combine(gameDir, file);
    auto path_cstr = TCHAR_TO_ANSI(*path);
    
    furnsh_c(path_cstr);

    ErrorCheck(ResultCode, ErrorMessage);
}


void USpice::furnsh_list(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const TArray<FString>& files
)
{
    for (auto file : files)
    {
        furnsh(ResultCode, ErrorMessage, file);

        if (ResultCode != ES_ResultCode::Success) break;
    }
}


void USpice::combine_paths(
    const FString& basePath,
    const TArray<FString>& relativePaths,
    TArray<FString>& joinedPaths
)
{
    joinedPaths.Empty();

    for (FString relativePath : relativePaths)
    {
        joinedPaths.Add(FPaths::Combine(basePath, relativePath));
    }
}


void USpice::clear_all()
{
    kclear_c();
    clpool_c();
}


void USpice::unload(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& absolutePath
)
{
    unload_c(TCHAR_TO_ANSI(*absolutePath));

    ErrorCheck(ResultCode, ErrorMessage);
}


void USpice::init_all()
{
    reset_c();
    clear_all();

    char szBuffer[LONG_MESSAGE_MAX_LENGTH];
    strcpy_s(szBuffer, "SHORT,LONG");
    errprt_c("SET", sizeof(szBuffer), szBuffer);

    strcpy_s(szBuffer, "REPORT");
    erract_c("SET", sizeof(szBuffer), szBuffer);

    strcpy_s(szBuffer, "NULL");
    errdev_c("SET", sizeof(szBuffer), szBuffer);

    UnexpectedErrorCheck();
}


/*
Exceptions
   This routine does not detect any errors.

   However, this routine is part of the CSPICE error
   handling mechanism.
*/
void USpice::reset()
{
    reset_c();
}

/*
Exceptions
   1) If the input argument op does not indicate a valid operation,
      the error SPICE(INVALIDOPERATION) will be signaled.

   2) When op is "SET", if the input argument action does not indicate a
      valid error handling action, the error SPICE(INVALIDACTION) will
      be signaled.

   3) The error SPICE(EMPTYSTRING) is signaled if either input string
      does not contain at least one character, since an input string
      cannot be converted to a Fortran-style string in this case.  This
      check always applies to op; it applies to action only when
      action is an input, that is, when op is "SET."

   4) The error SPICE(NULLPOINTER) is signaled if either string pointer
      argument is null.

   5) The caller must pass a value indicating the length of the output
      string, when action is an output.  If this value is not at least
      2, the error SPICE(STRINGTOOSHORT) is signaled.
*/
void USpice::get_erract(ES_ErrorAction& Result)
{
    char szBuffer[WINDOWS_MAX_PATH];
    ZeroOut(szBuffer);

    erract_c("GET", WINDOWS_MAX_PATH, szBuffer);

    if (!_stricmp(szBuffer, "REPORT"))
    {
        Result = ES_ErrorAction::Report;
    }
    else if (!_stricmp(szBuffer, "RETURN"))
    {
        Result = ES_ErrorAction::Return;
    }
    else if (!_stricmp(szBuffer, "IGNORE"))
    {
        Result = ES_ErrorAction::Ignore;
    }
    else
    {
        Result = ES_ErrorAction::Abort;
    }

    UnexpectedErrorCheck();
}



void USpice::set_erract(ES_ErrorAction Action)
{
    char szAction[WINDOWS_MAX_PATH];

    switch (Action)
    {
    case ES_ErrorAction::Report:
        strcpy_s(szAction, "REPORT");
        break;
    case ES_ErrorAction::Return:
        strcpy_s(szAction, "RETURN");
        break;
    case ES_ErrorAction::Ignore:
        strcpy_s(szAction, "IGNORE");
        break;
    case ES_ErrorAction::Abort:
    default:
        strcpy_s(szAction, "ABORT");
        break;
    }

    erract_c("SET", 0, szAction);

    UnexpectedErrorCheck();
}

/*
Exceptions
   1) If the input argument op does not indicate a valid operation,
      the error SPICE(INVALIDOPERATION) will be signaled.

   2) When op is "SET", if the input argument device has length greater
      than FILEN characters, the error SPICE(DEVICENAMETOOLONG) will
      be signaled.

   3) The error SPICE(EMPTYSTRING) is signaled if either input string
      does not contain at least one character, since an input string
      cannot be converted to a Fortran-style string in this case.  This
      check always applies to op; it applies to device only when
      device is an input, that is, when op is "SET."

   4) The error SPICE(NULLPOINTER) is signaled if either string pointer
      argument is null.

   5) The caller must pass a value indicating the length of the output
      string, when device is an output.  If this value is not at least
      2, the error SPICE(STRINGTOOSHORT) is signaled
*/

void USpice::get_errdev(ES_ErrorDevice& device)
{
    char szBuffer[WINDOWS_MAX_PATH];
    ZeroOut(szBuffer);

    errdev_c("GET", sizeof(szBuffer), szBuffer);

    if (!_stricmp(szBuffer, "NULL"))
    {
        device = ES_ErrorDevice::Null;
    }
    else if (!_stricmp(szBuffer, "SCREEN"))
    {
        device = ES_ErrorDevice::Screen;
    }
    else
    {
        device = ES_ErrorDevice::LogFile;
    }

    UnexpectedErrorCheck();
}

/*
Exceptions
   1) If the input argument op does not indicate a valid operation,
      the error SPICE(INVALIDOPERATION) will be signaled.

   2) When op is "SET", if the input argument device has length greater
      than FILEN characters, the error SPICE(DEVICENAMETOOLONG) will
      be signaled.

   3) The error SPICE(EMPTYSTRING) is signaled if either input string
      does not contain at least one character, since an input string
      cannot be converted to a Fortran-style string in this case.  This
      check always applies to op; it applies to device only when
      device is an input, that is, when op is "SET."

   4) The error SPICE(NULLPOINTER) is signaled if either string pointer
      argument is null.

   5) The caller must pass a value indicating the length of the output
      string, when device is an output.  If this value is not at least
      2, the error SPICE(STRINGTOOSHORT) is signaled
*/

void USpice::set_errdev(ES_ErrorDevice Device, const FString& LogFilePath)
{
    char szBuffer[WINDOWS_MAX_PATH];
    ZeroOut(szBuffer);

    if ((uint8)Device & (uint8)ES_ErrorDevice::LogFile)
    {
        strcpy_s(szBuffer, TCHAR_TO_ANSI(*LogFilePath));
    }
    else
    {
        switch (Device)
        {
        case ES_ErrorDevice::Screen:
            strcpy_s(szBuffer, "SCREEN");
            break;
        case ES_ErrorDevice::Null:
        default:
            strcpy_s(szBuffer, "NULL");
            break;
        }
    }

    errdev_c("SET", WINDOWS_MAX_PATH, szBuffer);

    UnexpectedErrorCheck();
}

/*
Exceptions
   1) If the input argument op does not indicate a valid operation,
      the error SPICE(INVALIDOPERATION) will be signaled.

   2) If the input argument list does not indicate a valid list of
      error message types, the error SPICE(INVALIDLISTITEM) will be
      signaled.

   3) The error SPICE(EMPTYSTRING) is signalled if the input
      string does not contain at least one character, since the
      input string cannot be converted to a Fortran-style string
      in this case.

   4) The error SPICE(NULLPOINTER) is signalled if the input string
      pointer is null.

   5) The user must pass a value indicating the length of the output
      string, when list is an output.  If this value is not at least 2,
      the error SPICE(STRINGTOOSHORT) is signaled.
*/

void USpice::get_errprt(FString& message)
{
    char szBuffer[WINDOWS_MAX_PATH];
    ZeroOut(szBuffer);

    errprt_c("GET", WINDOWS_MAX_PATH, szBuffer);
    message = FString(szBuffer);

    UnexpectedErrorCheck();
}

/*
Exceptions
   1) If the input argument op does not indicate a valid operation,
      the error SPICE(INVALIDOPERATION) will be signaled.

   2) If the input argument list does not indicate a valid list of
      error message types, the error SPICE(INVALIDLISTITEM) will be
      signaled.

   3) The error SPICE(EMPTYSTRING) is signalled if the input
      string does not contain at least one character, since the
      input string cannot be converted to a Fortran-style string
      in this case.

   4) The error SPICE(NULLPOINTER) is signalled if the input string
      pointer is null.

   5) The user must pass a value indicating the length of the output
      string, when list is an output.  If this value is not at least 2,
      the error SPICE(STRINGTOOSHORT) is signaled.
*/
void USpice::set_errprt(ES_Items items)
{
    char szBuffer[WINDOWS_MAX_PATH];
    ZeroOut(szBuffer);

    if ((uint8)items & (uint8)ES_Items::Default)
    {
        items = (ES_Items)-1;
    }

    bool commaPrepened = false;
    if ((uint8)items & (uint8)ES_Items::Short)
    {
        if (commaPrepened) strcpy_s(szBuffer, ", ");
        strcpy_s(szBuffer, "SHORT");
        commaPrepened |= true;
    }

    if ((uint8)items & (uint8)ES_Items::Explain)
    {
        if (commaPrepened) strcpy_s(szBuffer, ", ");
        strcpy_s(szBuffer, "EXPLAIN");
        commaPrepened |= true;
    }

    if ((uint8)items & (uint8)ES_Items::Long)
    {
        if (commaPrepened) strcpy_s(szBuffer, ", ");
        strcpy_s(szBuffer, "LONG");
        commaPrepened |= true;
    }

    if ((uint8)items & (uint8)ES_Items::Traceback)
    {
        if (commaPrepened) strcpy_s(szBuffer, ", ");
        strcpy_s(szBuffer, "TRACEBACK");
        commaPrepened |= true;
    }

    errprt_c("SET", sizeof(szBuffer), szBuffer);

    UnexpectedErrorCheck();
}


/*
Error free.

   1)  If axis is the zero vector, the rotation generated is the
       identity.  This is consistent with the specification of vrotv.
*/

void USpice::axisar(
    const FSDimensionlessVector& axis,
    const FSAngle& angle,
    FSRotationMatrix& r
)
{
    // Inputs
    SpiceDouble	_axis[3];	axis.CopyTo(_axis);
    SpiceDouble	_angle = angle.AsDouble();
    // Outputs
    SpiceDouble	_r[3][3];   ZeroOut(_r);


    // Invocation
    axisar_c(_axis, _angle, _r);

    // Return Value
    r = FSRotationMatrix(_r);
}


/*
Exceptions
   Error free.
*/
void USpice::bodfnd(
    ES_FoundCode& found,
    int body,
    const FString& item
)
{
    SpiceBoolean result = bodfnd_c((SpiceInt)body, TCHAR_TO_ANSI(*item));

    found = (result != SPICEFALSE) ? ES_FoundCode::Found : ES_FoundCode::NotFound;

    // Reset the current spice error in case a spice exception happened.
    UnexpectedErrorCheck(true);
}


void USpice::bodc2n(
    ES_FoundCode& found,
    int code,
    FString& name
)
{
    SpiceChar szBuffer[WINDOWS_MAX_PATH];
    ZeroOut(szBuffer);

    SpiceBoolean _found = SPICEFALSE;

    bodc2n_c(
        (SpiceInt)code,
        WINDOWS_MAX_PATH,
        szBuffer,
        &_found
    );

    if (_found != SPICEFALSE)
    {
        name = FString(szBuffer);
        found = ES_FoundCode::Found;
    }
    else
    {
        found = ES_FoundCode::NotFound;
    }

    // Reset the current spice error in case a spice exception happened.
    UnexpectedErrorCheck(true);
}


/*
Exceptions
   1) The error SPICE(EMPTYSTRING) is signaled if the input string
      `name' does not contain at least one character, since the input
      string cannot be converted to a Fortran-style string in this
      case.

   2) The error SPICE(NULLPOINTER) is signaled if the input string
      pointer `name' is null.
*/
void USpice::bodn2c(
    ES_FoundCode& found,
    int& code,
    const FString& name
)
{
    ConstSpiceChar* _name = TCHAR_TO_ANSI(*name);
    SpiceInt _code = 0;
    SpiceBoolean _found = SPICEFALSE;

    bodn2c_c(_name, &_code, &_found);

    if (_found != SPICEFALSE)
    {
        code = (int)_code;
        found = ES_FoundCode::Found;
    }
    else
    {
        found = ES_FoundCode::NotFound;
    }

    // Reset the current spice error in case a spice exception happened.
    UnexpectedErrorCheck(true);
}

/*
Exceptions

   1) If the requested kernel variable is not found in the kernel
      pool, the error SPICE(KERNELVARNOTFOUND) is signaled.

   2) If the requested kernel variable is found but the associated
      values aren't numeric, the error SPICE(TYPEMISMATCH) is
      signaled.

   3) The output array `values' must be declared with sufficient size
      to contain all of the values associated with the requested kernel
      variable.  If the dimension of `values' indicated by `maxn' is
      too small to contain the requested values, the error
      SPICE(ARRAYTOOSMALL) is signaled.

   4) If the input dimension `maxn' indicates there is more room
      in `values' than there really is---for example, if `maxn' is
      10 but `values' is declared with dimension 5---and the dimension
      of the requested kernel variable is larger than the actual
      dimension of `values', then this routine may overwrite
      memory.  The results are unpredictable.

   5) If the input string pointer `item' is null, the error
      SPICE(NULLPOINTER) will be signaled.

   6) If either of the input strings referred to by `item' contains
      no data characters, the error SPICE(EMPTYSTRING) will
      be signaled.
*/
void USpice::bodvcd_scalar(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    double& ReturnValue,
    int bodyid,
    const FString& item
)
{
    SpiceDouble _result[1];
    SpiceInt n_actual, n_expected = sizeof(_result) / sizeof(_result[0]);

    ZeroOut(_result);
    bodvcd_c(bodyid, TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);
    ReturnValue = _result[0];

    ErrorCheck(ResultCode, ErrorMessage);
    if (ResultCode == ES_ResultCode::Success && n_actual != n_expected)
    {
        ResultCode = ES_ResultCode::Error;
        ErrorMessage = FString::Printf(TEXT("Blueprint request for BODY%ld_%s Expected double[%d] but proc returned double[%d]"), bodyid, *item, n_expected, n_actual);
    }
}

void USpice::bodvcd_mass(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    FSMassConstant& ReturnValue,
    int bodyid,
    const FString& item
)
{
    SpiceDouble _result[1];
    SpiceInt n_actual, n_expected = sizeof(_result) / sizeof(_result[0]);

    ZeroOut(_result);
    bodvcd_c(bodyid, TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);
    ReturnValue = FSMassConstant(_result[0]);

    ErrorCheck(ResultCode, ErrorMessage);
    if (ResultCode == ES_ResultCode::Success && n_actual != n_expected)
    {
        ResultCode = ES_ResultCode::Error;
        ErrorMessage = FString::Printf(TEXT("Blueprint request for BODY%ld_%s Expected double[%d] but proc returned double[%d]"), bodyid, *item, n_expected, n_actual);
    }
}

void USpice::bodvcd_distance_vector(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    FSDistanceVector& ReturnValue,
    int bodyid,
    const FString& item
)
{
    SpiceDouble _result[3];
    SpiceInt n_actual, n_expected = sizeof(_result) / sizeof(_result[0]);

    ZeroOut(_result);
    bodvcd_c(bodyid, TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);
    ReturnValue = FSDistanceVector(_result);

    ErrorCheck(ResultCode, ErrorMessage);
    if (ResultCode == ES_ResultCode::Success && n_actual != n_expected)
    {
        ResultCode = ES_ResultCode::Error;
        ErrorMessage = FString::Printf(TEXT("Blueprint request for BODY%ld_%s Expected double[%d] but proc returned double[%d]"), bodyid, *item, n_expected, n_actual);
    }
}

/*
Exceptions

   1) If the input body name cannot be translated to an ID code,
      and if the name is not a string representation of an integer
      (for example, "399"), the error SPICE(NOTRANSLATION) is
      signaled.

   2) If the requested kernel variable is not found in the kernel
      pool, the error SPICE(KERNELVARNOTFOUND) is signaled.

   3) If the requested kernel variable is found but the associated
      values aren't numeric, the error SPICE(TYPEMISMATCH) is
      signaled.

   4) The output array `values' must be declared with sufficient size
      to contain all of the values associated with the requested kernel
      variable.  If the dimension of `values' indicated by `maxn' is
      too small to contain the requested values, the error
      SPICE(ARRAYTOOSMALL) is signaled.

   5) If the input dimension `maxn' indicates there is more room
      in `values' than there really is---for example, if `maxn' is
      10 but `values' is declared with dimension 5---and the dimension
      of the requested kernel variable is larger than the actual
      dimension of `values', then this routine may overwrite
      memory.  The results are unpredictable.

   6) If either of the input string pointers `bodynm' or `item'
      are null, the error SPICE(NULLPOINTER) will be signaled.

   7) If either of the input strings referred to by `bodynm' or `item'
      contain no data characters, the error SPICE(EMPTYSTRING) will
      be signaled.
*/
void USpice::bodvcd_vector(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    FSDimensionlessVector& ReturnValue,
    int bodyid,
    const FString& item
)
{
    SpiceDouble _result[3];
    SpiceInt n_actual, n_expected = sizeof(_result) / sizeof(_result[0]);

    ZeroOut(_result);
    bodvcd_c(bodyid, TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);
    ReturnValue = FSDimensionlessVector(_result);

    ErrorCheck(ResultCode, ErrorMessage);
    if (ResultCode == ES_ResultCode::Success && n_actual != n_expected)
    {
        ResultCode = ES_ResultCode::Error;
        ErrorMessage = FString::Printf(TEXT("Blueprint request for BODY%ld_%s Expected double[%d] but proc returned double[%d]"), bodyid, *item, n_expected, n_actual);
    }
}


/*
Exceptions

   1) If the input body name cannot be translated to an ID code,
      and if the name is not a string representation of an integer
      (for example, "399"), the error SPICE(NOTRANSLATION) is
      signaled.

   2) If the requested kernel variable is not found in the kernel
      pool, the error SPICE(KERNELVARNOTFOUND) is signaled.

   3) If the requested kernel variable is found but the associated
      values aren't numeric, the error SPICE(TYPEMISMATCH) is
      signaled.

   4) The output array `values' must be declared with sufficient size
      to contain all of the values associated with the requested kernel
      variable.  If the dimension of `values' indicated by `maxn' is
      too small to contain the requested values, the error
      SPICE(ARRAYTOOSMALL) is signaled.

   5) If the input dimension `maxn' indicates there is more room
      in `values' than there really is---for example, if `maxn' is
      10 but `values' is declared with dimension 5---and the dimension
      of the requested kernel variable is larger than the actual
      dimension of `values', then this routine may overwrite
      memory.  The results are unpredictable.

   6) If either of the input string pointers `bodynm' or `item'
      are null, the error SPICE(NULLPOINTER) will be signaled.

   7) If either of the input strings referred to by `bodynm' or `item'
      contain no data characters, the error SPICE(EMPTYSTRING) will
      be signaled.
*/
void USpice::bodvrd_scalar(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    double& ReturnValue,
    const FString& bodynm,
    const FString& item
)
{
    SpiceDouble _result[1];
    SpiceInt n_actual, n_expected = sizeof(_result) / sizeof(_result[0]);

    ZeroOut(_result);
    bodvrd_c(TCHAR_TO_ANSI(*bodynm), TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);
    ReturnValue = _result[0];

    ErrorCheck(ResultCode, ErrorMessage);
    if (ResultCode == ES_ResultCode::Success && n_actual != n_expected)
    {
        ResultCode = ES_ResultCode::Error;
        ErrorMessage = FString::Printf(TEXT("Blueprint request for %s_%s Expected double[%d] but proc returned double[%d]"), *bodynm, *item, n_expected, n_actual);
    }
}

void USpice::bodvrd_mass(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    FSMassConstant& ReturnValue,
    const FString& bodynm,
    const FString& item
)
{
    SpiceDouble _result[1];
    SpiceInt n_actual, n_expected = sizeof(_result) / sizeof(_result[0]);

    ZeroOut(_result);
    bodvrd_c(TCHAR_TO_ANSI(*bodynm), TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);
    ReturnValue = FSMassConstant(_result[0]);

    ErrorCheck(ResultCode, ErrorMessage);
    if (ResultCode == ES_ResultCode::Success && n_actual != n_expected)
    {
        ResultCode = ES_ResultCode::Error;
        ErrorMessage = FString::Printf(TEXT("Blueprint request for %s_%s Expected double[%d] but proc returned double[%d]"), *bodynm, *item, n_expected, n_actual);
    }
}

void USpice::bodvrd_distance_vector(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    FSDistanceVector& ReturnValue,
    const FString& bodynm,
    const FString& item
)
{
    SpiceDouble _result[3];
    SpiceInt n_actual, n_expected = sizeof(_result) / sizeof(_result[0]);

    ZeroOut(_result);
    bodvrd_c(TCHAR_TO_ANSI(*bodynm), TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);
    ReturnValue = FSDistanceVector(_result);

    ErrorCheck(ResultCode, ErrorMessage);
    if (ResultCode == ES_ResultCode::Success && n_actual != n_expected)
    {
        ResultCode = ES_ResultCode::Error;
        ErrorMessage = FString::Printf(TEXT("Blueprint request for %s_%s Expected double[%d] but proc returned double[%d]"), *bodynm, *item, n_expected, n_actual);
    }
}


void USpice::bodvrd_vector(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    FSDimensionlessVector& ReturnValue,
    const FString& bodynm,
    const FString& item
)
{
    SpiceDouble _result[3];
    SpiceInt n_actual, n_expected = sizeof(_result) / sizeof(_result[0]);

    ZeroOut(_result);
    bodvrd_c(TCHAR_TO_ANSI(*bodynm), TCHAR_TO_ANSI(*item), n_expected, &n_actual, _result);
    ReturnValue = FSDimensionlessVector(_result);

    ErrorCheck(ResultCode, ErrorMessage);
    if (ResultCode == ES_ResultCode::Success && n_actual != n_expected)
    {
        ResultCode = ES_ResultCode::Error;
        ErrorMessage = FString::Printf(TEXT("Blueprint request for %s_%s Expected double[%d] but proc returned double[%d]"), *bodynm, *item, n_expected, n_actual);
    }
}


/*
1)  If vec1 and vec2 are linearly dependent, ellips will be
       degenerate.  CSPICE ellipses are allowed to represent
       degenerate geometric ellipses.
*/
void USpice::cgv2el(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSDistanceVector& center,
    const FSDistanceVector& vec1,
    const FSDistanceVector& vec2,
    FSEllipse& ellipse
)
{
    // Unpack inputs
    SpiceDouble    _center[3];  center.CopyTo(_center);
    SpiceDouble    _vec1[3];    center.CopyTo(_vec1);
    SpiceDouble    _vec2[3];    center.CopyTo(_vec2);
    
    // Default outputs
    SpiceEllipse _ellipse;      ZeroOut(_ellipse);

    // Invocation
    cgv2el_c(_center, _vec1, _vec2, &_ellipse);

    // Pack outputs
    CopyFrom(_ellipse, ellipse);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


/*
Exceptions

   1) If there are no segments in the file the error
      SPICE(NOSEGMENTSFOUND) will be signalled
*/
void USpice::ckcls(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int handle
)
{
    // Inputs
    SpiceInt _handle = handle;

    // Invocation
    ckcls_c(_handle);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  If the input file has transfer format, the error
       SPICE(INVALIDFORMAT) is signaled.

   2)  If the input file is not a transfer file but has architecture
       other than DAF, the error SPICE(BADARCHTYPE) is signaled.

   3)  If the input file is a binary DAF file of type other than
       CK, the error SPICE(BADFILETYPE) is signaled.

   4)  If the CK file cannot be opened or read, the error will
       be diagnosed by routines called by this routine. The output
       window will not be modified.

   5)  If the size of the output window argument `cover' is
       insufficient to contain the actual number of intervals in the
       coverage window for `idcode', the error will be diagnosed by
       routines called by this routine.

   6)  If `tol' is negative, the error SPICE(VALUEOUTOFRANGE) is
       signaled.

   7)  If `level' is not recognized, the error SPICE(INVALIDOPTION)
       is signaled.

   8)  If `timsys' is not recognized, the error SPICE(INVALIDOPTION)
       is signaled.

   9)  If a time conversion error occurs, the error will be
       diagnosed by a routine in the call tree of this routine.

   10) If the output time system is TDB, the CK subsystem must be
       able to map `idcode' to the ID code of the associated
       spacecraft clock.  If this mapping cannot be performed, the
       error will be diagnosed by a routine in the call tree of this
       routine.

   11) The error SPICE(EMPTYSTRING) is signaled if any of the input
       strings `ck', `level', or `timsys' do not contain at least one
       character, since such an input string cannot be converted to a
       Fortran-style string in this case.

   12) The error SPICE(NULLPOINTER) is signaled if the if any of the input
       strings `ck', `level', or `timsys' are null.
*/
void USpice::ckcov(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& ck_relative_path,
    int idcode,
    bool                            need_av,
    double tol,
    const TArray<FSWindowSegment>& merge_to,
    TArray<FSWindowSegment>& coverage,
    ES_CoverageLevel                level,
    ES_TimeSystem                   timsys
)
{
    auto gameDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
    auto path = FPaths::Combine(gameDir, ck_relative_path);

    const int smallCellSize = 100;
    const int largeCellSize = 10000;

    // Inputs
    ConstSpiceChar* _ck = TCHAR_TO_ANSI(*path);
    SpiceInt        _idcode = idcode;
    SpiceBoolean    _needav = need_av ? SPICETRUE : SPICEFALSE;
    SpiceDouble     _tol = tol;
    ConstSpiceChar* _level = "";
    ConstSpiceChar* _timsys = "";
    switch (level)
    {
    case ES_CoverageLevel::Segment:
        _level = "SEGMENT";
        break;
    case ES_CoverageLevel::Interval:
        _level = "INTERVAL";
        break;
    }
    switch (timsys)
    {
    case ES_TimeSystem::SCLK:
        _timsys = "SCLK";
        break;
    case ES_TimeSystem::TDB:
        _timsys = "TDB";
        break;
    }

    SpiceCell* _cover;

    bool haveData = false;
    SPICEDOUBLE_CELL(_cover_small, smallCellSize);
    _cover = &_cover_small;

    if (merge_to.Num() <= smallCellSize / 2)
    {
        // Outputs
        if (merge_to.Num() > 0)
        {
            for (int i = 0; i < merge_to.Num(); ++i)
            {
                appndd_c(merge_to[i].start, _cover);
                appndd_c(merge_to[i].stop, _cover);
            }
        }

        // Invocation
        ckcov_c(_ck, _idcode, _needav, _level, _tol, _timsys, _cover);

        haveData = !failed_c();
    }

    if (!haveData)
    {
        if (merge_to.Num() <= largeCellSize / 2)
        {
            reset_c();

            SPICEDOUBLE_CELL(_cover_large, largeCellSize);
            _cover = &_cover_large;

            if (merge_to.Num() > 0)
            {
                for (int i = 0; i < merge_to.Num(); ++i)
                {
                    appndd_c(merge_to[i].start, _cover);
                    appndd_c(merge_to[i].stop, _cover);
                }
            }

            // Re-Invocation
            ckcov_c(_ck, _idcode, _needav, _level, _tol, _timsys, _cover);

            haveData = !failed_c();
        }
        else
        {
            setmsg_c("[in] Window Segment count = #; maximum allowed value is #");
            errdp_c("#", merge_to.Num());
            errdp_c("#", largeCellSize / 2);
            sigerr_c("SPICE(VALUEOUTOFRANGE)");
        }
    }

    // Return Values
    coverage = TArray<FSWindowSegment>();
    if (haveData)
    {
        int niv = wncard_c(_cover);
        for (int i = 0; i < niv; ++i)
        {
            SpiceDouble _start, _stop;
            wnfetd_c(_cover, i, &_start, &_stop);
            coverage.Add(FSWindowSegment(_start, _stop));
        }
    }

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  If a C-kernel file has not been loaded using furnsh_c prior to a
       call to this routine, an error is signaled by a routine in the
       call tree of this routine.

   2)  If `tol' is negative, found is set to SPICEFALSE.

   3)  If `ref' is not a supported reference frame, an error is
       signaled by a routine in the call tree of this routine and
       `found' is set to SPICEFALSE.
*/
void USpice::ckgp(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int inst,
    double sclkdp,
    double tol,
    const FString& ref,
    FSRotationMatrix& cmat,
    double& clkout,
    bool& found
)
{
    // Inputs
    SpiceInt        _inst = inst;
    SpiceDouble     _sclkdp = sclkdp;
    SpiceDouble     _tol = tol;
    ConstSpiceChar* _ref = TCHAR_TO_ANSI(*ref);
    // Outputs
    SpiceDouble     _cmat[3][3];    ZeroOut(_cmat);
    SpiceDouble     _clkout = 0;
    SpiceBoolean    _found = SPICEFALSE;

    // Invocation
    ckgp_c(_inst, _sclkdp, _tol, _ref, _cmat, &_clkout, &_found);

    // Return Values
    cmat = FSRotationMatrix(_cmat);
    clkout = _clkout;
    found = _found ? true : false;

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

void USpice::ckgpav(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int inst,
    double sclkdp,
    double tol,
    const FString& ref,
    FSRotationMatrix& cmat,
    FSAngularVelocity& av,
    double& clkout,
    bool& found
)
{
    // Inputs
    SpiceInt        _inst = inst;
    SpiceDouble     _sclkdp = sclkdp;
    SpiceDouble     _tol = tol;
    ConstSpiceChar* _ref = TCHAR_TO_ANSI(*ref);
    // Outputs
    SpiceDouble     _cmat[3][3];    ZeroOut(_cmat);
    SpiceDouble     _av[3];         ZeroOut(_av);
    SpiceDouble     _clkout = 0;
    SpiceBoolean    _found = SPICEFALSE;

    // Invocation
    ckgpav_c(_inst, _sclkdp, _tol, _ref, _cmat, _av, &_clkout, &_found);

    // Return Values
    cmat = FSRotationMatrix(_cmat);
    av = FSAngularVelocity(_av);
    clkout = _clkout;
    found = _found ? true : false;

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

void USpice::cklpf(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& relativePath,
    int& handle
)
{
    auto gameDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
    ConstSpiceChar* _fname = TCHAR_TO_ANSI(*(gameDir + relativePath));

    // Outputs
    SpiceInt _handle = 0;

    // Invocation
    cklpf_c(_fname, &_handle);

    // Return Values
    handle = _handle;

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  If the input file has transfer format, the error
       SPICE(INVALIDFORMAT) is signaled.

   2)  If the input file is not a transfer file but has architecture
       other than DAF, the error SPICE(BADARCHTYPE) is signaled.

   3)  If the input file is a binary DAF file of type other than
       CK, the error SPICE(BADFILETYPE) is signaled.

   4)  If the CK file cannot be opened or read, the error will
       be diagnosed by routines called by this routine.

   5)  If the size of the output set argument `ids' is insufficient to
       contain the actual number of ID codes of objects covered by
       the indicated CK file, the error will be diagnosed by
       routines called by this routine.

   6) The error SPICE(EMPTYSTRING) is signaled if the input
      string `ck' does not contain at least one character, since the
      input string cannot be converted to a Fortran-style string in
      this case.

   7) The error SPICE(NULLPOINTER) is signaled if the input string
      pointer `ck' is null.
*/
void USpice::ckobj(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& relativePath,
    TArray<int>& ids
)
{
    const int MAXOBJ = 1000;

    SPICEINT_CELL(idscell, MAXOBJ);

    // Inputs
    auto gameDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
    ConstSpiceChar* _fname = TCHAR_TO_ANSI(*(gameDir + relativePath));

    // Outputs
    SpiceCell* _ids = &idscell;

    // Invocation
    ckobj_c(_fname, _ids);

    ids = TArray<int>();
    int count = card_c(_ids);
    for (int i = 0; i < count; i++)
    {
        SpiceInt id = SPICE_CELL_ELEM_I(_ids, i);
        ids.Add(id);
    }

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1) If the value of ncomch is negative, a value of zero will
      be used for the number of comment characters to be set aside
      for comments.

   2) If an error occurs while attempting to open a CK file the
      value of handle will not represent a valid file handle.
*/
void USpice::ckopn(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& relativePath,
    const FString& ifname,
    const int ncomch,
    int& handle
)
{
    // Inputs
    auto gameDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
    ConstSpiceChar* _fname = TCHAR_TO_ANSI(*(gameDir + relativePath));
    ConstSpiceChar* _ifname = TCHAR_TO_ANSI(*ifname);
    SpiceInt        _ncomch = ncomch;
    // Outputs
    SpiceInt        _handle = 0;

    // Invocation
    ckopn_c(_fname, _ifname, _ncomch, &_handle);

    // Return Values
    handle = _handle;

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   Error free.

   1) If the file specified by handle does not appear in the file
      table, nothing happens.
*/
void USpice::ckupf(
    int handle
)
{
    // Inputs
    SpiceInt _handle = handle;

    // Invocation
    ckupf_c(_handle);
}


void USpice::ckw01(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int handle,
    double begtim,
    double endtim,
    int inst,
    const FString& ref,
    bool        avflag,
    const FString& segid,
    const TArray<FSPointingType1Observation>& records
)
{
    // Inputs
    SpiceInt        _handle = handle;
    SpiceDouble     _begtim = begtim;
    SpiceDouble     _endtim = endtim;
    SpiceInt        _inst = inst;
    ConstSpiceChar* _ref = TCHAR_TO_ANSI(*ref);
    SpiceBoolean        _avflag = avflag ? SPICETRUE : SPICEFALSE;
    ConstSpiceChar* _segid = TCHAR_TO_ANSI(*segid);
    SpiceInt        _nrec = records.Num();
    SpiceDouble* _sclkdp = (SpiceDouble*)StackAlloc(_nrec * sizeof(SpiceDouble));
    SpiceDouble(*_quats)[4] = (SpiceDouble(*)[4])StackAlloc(_nrec * sizeof(SpiceDouble[4]));
    SpiceDouble(*_avvs)[3] = (SpiceDouble(*)[3])StackAlloc(_nrec * sizeof(SpiceDouble[3]));

    for (int i = 0; i < records.Num(); ++i)
    {
        _sclkdp[i] = records[i].sclkdp;
        records[i].quat.CopyTo(_quats[i]);
        records[i].avv.CopyTo(_avvs[i]);
    }

    // Invocation
    ckw01_c(_handle, _begtim, _endtim, _inst, _ref, _avflag, _segid, _nrec, _sclkdp, _quats, _avvs);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


void USpice::ckw02(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int handle,
    double begtim,
    double endtim,
    int inst,
    const FString& ref,
    const FString& segid,
    const TArray<FSPointingType2Observation>& records
)
{
    // Inputs
    SpiceInt        _handle = handle;
    SpiceDouble     _begtim = begtim;
    SpiceDouble     _endtim = endtim;
    SpiceInt        _inst = inst;
    ConstSpiceChar* _ref = TCHAR_TO_ANSI(*ref);
    ConstSpiceChar* _segid = TCHAR_TO_ANSI(*segid);
    SpiceInt        _nrec = records.Num();
    SpiceDouble* _start = (SpiceDouble*)StackAlloc(_nrec * sizeof(SpiceDouble));
    SpiceDouble* _stop = (SpiceDouble*)StackAlloc(_nrec * sizeof(SpiceDouble));
    SpiceDouble(*_quats)[4] = (SpiceDouble(*)[4])StackAlloc(_nrec * sizeof(SpiceDouble[4]));
    SpiceDouble(*_avvs)[3] = (SpiceDouble(*)[3])StackAlloc(_nrec * sizeof(SpiceDouble[3]));
    SpiceDouble* _rates = (SpiceDouble*)StackAlloc(_nrec * sizeof(SpiceDouble));

    for (int i = 0; i < records.Num(); ++i)
    {
        records[i].segment.CopyTo(_start[i], _stop[i]);
        records[i].quat.CopyTo(_quats[i]);
        records[i].avv.CopyTo(_avvs[i]);
        _rates[i] = records[i].rate;
    }

    // Invocation
    ckw02_c(_handle, _begtim, _endtim, _inst, _ref, _segid, _nrec, _start, _stop, _quats, _avvs, _rates);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

void USpice::ckw03(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int handle,
    double begtim,
    double endtim,
    int inst,
    const FString& ref,
    bool        avflag,
    const FString& segid,
    const TArray<FSPointingType1Observation>& records,
    const TArray<double>& starts
)
{
    // Inputs
    SpiceInt        _handle = handle;
    SpiceDouble     _begtim = begtim;
    SpiceDouble     _endtim = endtim;
    SpiceInt        _inst = inst;
    ConstSpiceChar* _ref = TCHAR_TO_ANSI(*ref);
    SpiceBoolean    _avflag = avflag ? SPICETRUE : SPICEFALSE;
    ConstSpiceChar* _segid = TCHAR_TO_ANSI(*segid);
    SpiceInt        _nrec = records.Num();
    SpiceDouble* _sclkdp = (SpiceDouble*)StackAlloc(_nrec * sizeof(SpiceDouble));
    SpiceDouble(*_quats)[4] = (SpiceDouble(*)[4])StackAlloc(_nrec * sizeof(SpiceDouble[4]));
    SpiceDouble(*_avvs)[3] = (SpiceDouble(*)[3])StackAlloc(_nrec * sizeof(SpiceDouble[3]));

    for (int i = 0; i < _nrec; ++i)
    {
        _sclkdp[i] = records[i].sclkdp;
        records[i].quat.CopyTo(_quats[i]);
        records[i].avv.CopyTo(_avvs[i]);
    }

    SpiceInt        _nints = starts.Num();
    SpiceDouble* _starts = (SpiceDouble*)StackAlloc(_nints * sizeof(SpiceDouble));
    for (int i = 0; i < _nints; ++i)
    {
        _starts[i] = starts[i];
    }

    // Invocation
    ckw03_c(_handle, _begtim, _endtim, _inst, _ref, _avflag, _segid, _nrec, _sclkdp, _quats, _avvs, _nints, _starts);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

void USpice::ckw05(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int handle,
    ES_CK05Subtype      subtyp,
    int                 degree,
    double begtim,
    double endtim,
    int inst,
    const FString& ref,
    bool  avflag,
    const FString& segid,
    const TArray<FSPointingType5Observation>& records,
    double rate,
    const TArray<double>& starts
)
{
    // Inputs
    SpiceInt        _handle = handle;
    SpiceCK05Subtype    _subtyp = (SpiceCK05Subtype)subtyp;
    SpiceInt            _degree = (SpiceInt)degree;
    SpiceDouble     _begtim = begtim;
    SpiceDouble     _endtim = endtim;
    SpiceInt        _inst = inst;
    ConstSpiceChar* _ref = TCHAR_TO_ANSI(*ref);
    SpiceBoolean    _avflag = avflag ? SPICETRUE : SPICEFALSE;
    ConstSpiceChar* _segid = TCHAR_TO_ANSI(*segid);
    SpiceDouble         _rate = rate;

    SpiceInt        _nints = starts.Num();
    SpiceDouble* _starts = (SpiceDouble*)StackAlloc(_nints * sizeof(SpiceDouble));
    for (int i = 0; i < _nints; ++i)
    {
        _starts[i] = starts[i];
    }

    SpiceInt        _n = records.Num();
    SpiceDouble* _sclkdp = (SpiceDouble*)StackAlloc(_n * sizeof(SpiceDouble));
    const void* _packts = nullptr;
    if (subtyp == ES_CK05Subtype::Hermite8)
    {
        SpiceDouble(*__packts)[8] = (SpiceDouble(*)[8])StackAlloc(_n * sizeof(SpiceDouble[8]));
        for (int i = 0; i < _n; i++)
        {
            records[i].CopyToSubtype1(_sclkdp[i], __packts[i]);
        }
        _packts = __packts;
    }
    else if (subtyp == ES_CK05Subtype::Lagrange4)
    {
        SpiceDouble(*__packts)[4] = (SpiceDouble(*)[4])StackAlloc(_n * sizeof(SpiceDouble[4]));
        for (int i = 0; i < _n; i++)
        {
            records[i].CopyToSubtype2(_sclkdp[i], __packts[i]);
        }
        _packts = __packts;
    }
    else if (subtyp == ES_CK05Subtype::Hermite14)
    {
        SpiceDouble(*__packts)[14] = (SpiceDouble(*)[14])StackAlloc(_n * sizeof(SpiceDouble[14]));
        for (int i = 0; i < _n; i++)
        {
            records[i].CopyToSubtype3(_sclkdp[i], __packts[i]);
        }
        _packts = __packts;
    }
    else if (subtyp == ES_CK05Subtype::Lagrange7)
    {
        SpiceDouble(*__packts)[7] = (SpiceDouble(*)[7])StackAlloc(_n * sizeof(SpiceDouble[7]));
        for (int i = 0; i < _n; i++)
        {
            records[i].CopyToSubtype4(_sclkdp[i], __packts[i]);
        }
        _packts = __packts;
    }
    // else, just let the call fail on the unrecognized subtype.  Spice can generate a decent
    // message for it.

    // Invocation
    ckw05_c(_handle, _subtyp, _degree, _begtim, _endtim, _inst, _ref, _avflag, _segid, _n, _sclkdp, _packts, _rate, _nints, _starts);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions
   Error free.
*/

void USpice::clight(FSSpeed& c)
{
    // Outputs
    SpiceDouble	_c;

    // Invocation
    _c = clight_c();

    // Return Value
    c = FSSpeed(_c);
}

/*
Exceptions
   1) If the eccentricity supplied is less than 0, the error
      SPICE(BADECCENTRICITY) is signaled.

   2) If a non-positive periapse distance is supplied, the error
      SPICE(BADPERIAPSEVALUE) is signaled.

   3) If a non-positive value for the attracting mass is supplied,
      the error SPICE(BADGM),  is signaled.

   4) Errors such as an out of bounds value for `et' are diagnosed
      by routines in the call tree of this routine.
*/

void USpice::conics(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSConicElements& elts,
    const FSEphemerisTime& et,
    FSStateVector& state
)
{
    // Inputs
    SpiceDouble _elts[8];	elts.CopyTo(_elts);
    SpiceDouble _et = et.seconds;
    // Outputs
    SpiceDouble _state[6];	ZeroOut(_state);

    // Invocation
    conics_c(_elts, _et, _state);
     
    // Return Value
    state = FSStateVector(_state);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1) If the input units, output units, or both input and
      output units are not recognized, the error
      SPICE(UNITSNOTREC) is signaled.

   2) If the units being converted between are incompatible, the
      error SPICE(INCOMPATIBLEUNITS) is signaled.
*/
void USpice::convrt(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    double in_value,
    ES_Units            in,
    ES_Units            out,
    double& out_value
)
{
    // Inputs
    SpiceDouble		_x = in_value;
    ConstSpiceChar* _in = USpiceTypes::UnitsToChar(in);
    ConstSpiceChar* _out = USpiceTypes::UnitsToChar(out);
    // Outputs
    SpiceDouble		_y = 0;

    // Invocation
    convrt_c(_x, _in, _out, &_y);

    // Return Value
    out_value = _y;

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1) If the number of comments to be added is not positive, the
      error SPICE(INVALIDARGUMENT) will be signaled.

   2) If a non printing ASCII character is encountered in the
      comments, the error SPICE(ILLEGALCHARACTER) will be signaled.

   3) If the binary DAF file attached to HANDLE is not open with
      write access an error will be signalled by a routine called by
      this routine.

   4) If the end of the comments cannot be found, i.e., the end of
      comments marker is missing on the last comment record, the error
      SPICE(BADCOMMENTAREA) will be signaled.

   5) If the input pointer `buffer' is null, the error
      SPICE(NULLPOINTER) will be signaled.

   6) If the input buffer string length indicated by `lenvals'
      is less than 2, the error SPICE(STRINGTOOSHORT) will be signaled.
*/
void USpice::dafac(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int handle,
    const TArray<FString>& comments
)
{
    // Buffers
    int32 maxCommentLineLength = 0;
    for (int32 i = 0; i < comments.Num(); ++i)
    {
        maxCommentLineLength = std::max(comments[i].Len() + 1, maxCommentLineLength);
    }
    size_t bytesPerLine = maxCommentLineLength * sizeof(SpiceChar);
    size_t totalBytes = comments.Num() * bytesPerLine;
    SpiceChar* _buffer = (SpiceChar*)StackAlloc(totalBytes);
    memset(_buffer, 0, totalBytes);

    for (int32 i = 0; i < comments.Num(); ++i)
    {
        SpiceChar* lineBuffer = _buffer + maxCommentLineLength * i;
        // NOTE:!!  Assumes SpiceChar == char!!   should assert sizeof(SpiceChar) == 1.
        strncpy_s(lineBuffer, maxCommentLineLength, TCHAR_TO_ANSI(*comments[i]), maxCommentLineLength);
    }

    // Inputs
    SpiceInt    _handle = handle;
    SpiceInt    _n = comments.Num();
    SpiceInt    _lenvals = maxCommentLineLength;

    dafac_c(_handle, _n, _lenvals, _buffer);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


/*
Exceptions
   1) If the specified handle is not known to the DAF subsystem
      (because it does not belong to a file opened via the DAF
      API), nothing happens.

   2) If this routine is used to close a file whose handle is
      known to the DAF subsystem, and if the file handle is
      attached to a non-DAF file, routines called by this
      routine signal an error.
*/
void USpice::dafcls(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int handle
)
{
    // Input
    SpiceInt    _handle = handle;

    // Invocation
    dafcls_c(_handle);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)   If the size of the output line buffer is is not positive,
        the error SPICE(INVALIDARGUMENT) will be signaled.

   3)   If a comment line in a DAF is longer than the length
        of a character string array element of BUFFER, the error
        SPICE(COMMENTTOOLONG) will be signaled.

   3)   If the end of the comments cannot be found, i.e., the end of
        comments marker is missing on the last comment record, the
        error SPICE(BADCOMMENTAREA) will be signaled.

   4)   If the number of comment characters scanned exceeds the
        number of comment characters computed, the error
        SPICE(BADCOMMENTAREA) will be signaled.

   5)   If the binary DAF attached to HANDLE is not open for
        reading,an error will be signaled by a routine called by
        this routine.

   6)   If the output buffer pointer is null the error SPICE(NULLPOINTER)
        will be signaled.

   7)   If the output buffer string length is less than 2, the error
        SPICE(STRINGTOOSHORT) will be signaled.
*/
void USpice::dafec(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int handle,
    TArray<FString>& comments
)
{
    // Inputs
    SpiceInt _handle = handle;

    // Buffer stuff...
    SpiceInt _bufsiz = 20;
    SpiceInt _lenout = WINDOWS_MAX_PATH;
    SpiceInt _n = 0;
    void* _buffer;

    // Return Value
    // extracting comments is "stately", in that successive calls fetch the NEXT batch of comments
    // (comments that have not previously been read.)
    comments = TArray<FString>();

    SpiceBoolean _done = SPICEFALSE;

    size_t chafBufferSize = _bufsiz * _lenout * sizeof(SpiceChar);
    _buffer = (SpiceChar*)StackAlloc(chafBufferSize);

    while (!_done)
    {
        // If some preceeding call has failed and not reset the failure, break now.
        // Otherwise, catch a failure of our previous iteration
        if (failed_c()) break;

        memset(_buffer, 0, chafBufferSize);

        dafec_c(_handle, _bufsiz, _lenout, &_n, _buffer, &_done);

        for (int i = 0; i < _n; ++i)
        {
            SpiceChar* commentLine = (SpiceChar*)_buffer + _lenout * i;
            comments.Add(FString(commentLine));
        }
    }

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions
   1) If the specified file has already been opened for read
      access, the handle already associated with the file is
      returned.

   2) If the specified file has already been opened for write
      access, the error SPICE(DAFRWCONFLICT) is signaled.

   3) If the specified file has already been opened by a non-DAF
      routine, the error SPICE(DAFIMPROPOPEN) is signaled.

   4) If the specified file cannot be opened without exceeding
      the maximum number of files, the error SPICE(DAFFTFULL)
      is signaled.

   5) If (for some reason) the file cannot be opened properly,
      the error SPICE(DAFOPENFAIL) is signaled.

   6) If the attempt to read the file's ID word fails, the error
      SPICE(FILEREADFAILED) will be signaled.

   7) If the specified file is not a DAF file, as indicated by the
      file's ID word, the error SPICE(NOTADAFFILE) is signaled.

   8) If no logical units are available, the error will be
      signaled by routines called by this routine.

   9) If the file does not exist, the error SPICE(FILEDOESNOTEXIST)
      is signaled.

  10) If the INQUIRE fails, the error SPICE(INQUIREFAILED)
      is signaled.

  11) If the file record cannot (for some reason) be read,
      the error SPICE(DAFFRNOTFOUND) is signaled.

  12) If the file name is blank, the error SPICE(BLANKFILENAME)
      is signaled.
*/
void USpice::dafopr(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& relativePath,
    int& handle
)
{
    // Input
    auto gameDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
    ConstSpiceChar* _fname = TCHAR_TO_ANSI(*(gameDir + relativePath));
    // Output
    SpiceInt        _handle = 0;

    // Invocation
    dafopr_c(_fname, &_handle);

    // Return Value
    handle = _handle;

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1) If the specified file has already been opened, either by
      the DAF routines or by other code, an error is signaled by
      routines in the call tree of this routine.  Note that this
      response is not paralleled by dafopr_c, which allows you
      to open a DAF for reading even if it is already open for
      reading.

   2) If the specified file cannot be opened without exceeding
      the maximum number of files, the error SPICE(DAFFTFULL)
      is signaled.

   3) If the attempt to read the file's file record fails, the
      error SPICE(FILEREADFAILED) will be signaled.

   4) If the specified file is not a DAF file, an error is
      signaled by routines in the call tree of this routine.

   5) If no logical units are available, an error is
      signaled by routines called by this routine.

   6) If the file does not exist, the error SPICE(FILENOTFOUND)
      is signaled by routines in the call tree of this routine.

   7) If an I/O error occurs in the process of opening the file,
      routines in the call tree of this routine signal an error.

   8) If the file name is blank or otherwise inappropriate
      routines in the call tree of this routine signal an error.

   9) If the file was transferred improperly via FTP, routines
      in the call tree of this routine signal an error.

  10) If the file utilizes a non-native binary file format, an
      error is signaled by routines in the call tree of this
      routine.

  11) The error SPICE(EMPTYSTRING) is signaled if the file namne
      string does not contain at least one character, since the
      string cannot be converted to a Fortran-style string
      in this case.

  12) The error SPICE(NULLPOINTER) is signaled if the input file
      name string pointer is null.
*/
void USpice::dafopw(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& relativePath,
    int& handle
)
{
    // Input
    auto gameDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
    ConstSpiceChar* _fname = TCHAR_TO_ANSI(*(gameDir + relativePath));
    // Output
    SpiceInt        _handle = 0;

    // Invocation
    dafopw_c(_fname, &_handle);

    // Return Value
    handle = _handle;

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1) If the input epoch is not recognized, the error
      SPICE(INVALIDEPOCH) is signaled.

   2) If the variables necessary for the computation of delta
      have not been loaded into the kernel pool, the error
      SPICE(KERNELVARNOTFOUND) is signaled.

   3) If the number of leapseconds in the pool is greater than
      the local leapseconds buffer size, the error
      SPICE(BUFFEROVERFLOW) is signaled.

   4) The error SPICE(EMPTYSTRING) is signaled if the input
      string `eptype' does not contain at least one character, since
      the input string cannot be converted to a Fortran-style string in
      this case.

   5) The error SPICE(NULLPOINTER) is signaled if the input string
      pointer is null.
*/

void USpice::deltet(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSEphemerisTime& epoch,
    ES_EpochType eptype,
    FSEphemerisPeriod& delta
)
{
    // Inputs
    SpiceDouble		_epoch = epoch.seconds;
    ConstSpiceChar* _eptype = eptype == ES_EpochType::UTC ? "UTC" : "ET";
    // Outputs
    SpiceDouble		_delta = 0;

    // Invocation
    deltet_c(_epoch, _eptype, &_delta);

    // Return Value
    delta = FSEphemerisPeriod(_delta);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   Error free.
*/
void USpice::det(const FSRotationMatrix& m1, double& ReturnValue)
{
    // Inputs
    SpiceDouble _m1[3][3];	m1.CopyTo(_m1);

    // Invocation, Return Value
    ReturnValue = det_c(_m1);
}

/*
Exceptions

   Error free.
*/
void USpice::dpmax(double& ReturnValue)
{
    // Invocation, Return Value
    ReturnValue = dpmax_c();
}

/*
Exceptions

   Error free.
*/
void USpice::dpmin(double& ReturnValue)
{
    // Invocation, Return Value
    ReturnValue = dpmin_c();
}

/*
Exceptions

   Error free.
*/
void USpice::dpr(double& ReturnValue)
{
    // Invocation, Return Value
    ReturnValue = dpr_c();
}



/*
Exceptions
   Error free.

   1) If the input et is so large that the corresponding
      number of days since 1 A.D. Jan 1, 00:00:00 is
      within 1 of overflowing or underflowing an integer,
      et will not be converted to the correct string
      representation rather, the string returned will
      state that the epoch was before or after the day
      that is min_integer_val + 1 or max_integer_val - 1 days
      after 1 A.D. Jan 1, 00:00:00.

   2) If the output string is not sufficiently long to hold
      the full date, it will be truncated on the right.
*/
void USpice::etcal(
    const FSEphemerisTime& et,
    FString& ReturnValue
)
{
    // Buffers
    SpiceChar szBuffer[WINDOWS_MAX_PATH];
    ZeroOut(szBuffer);

    // Inputs
    SpiceDouble   _et = et.seconds;
    SpiceInt      _lenout = sizeof(szBuffer);
    // Output
    SpiceChar* _string = szBuffer;

    // Invocation
    etcal_c(_et, _lenout, _string);

    // Return Value
    ReturnValue = FString(_string);
}





/*
Exceptions
   None.
*/
void USpice::eqncpv(
    const FSEphemerisTime& et,
    const FSEphemerisTime& epoch,
    const FSEquinoctialElements& eqel,
    const FSAngle& rapol,
    const FSAngle& decpol,
    FSStateVector& state
)
{
    // Inputs
    SpiceDouble	_et = et.seconds;
    SpiceDouble	_epoch = epoch.seconds;
    SpiceDouble _eqel[9];	eqel.CopyTo(_eqel);
    SpiceDouble	_rapol = rapol.radians();
    SpiceDouble	_decpol = decpol.radians();
    // Outputs
    SpiceDouble _state[6];	ZeroOut(_state);

    // Invocation
    eqncpv_c(_et, _epoch, _eqel, _rapol, _decpol, _state);

    // Return Value
    state = FSStateVector(_state);
}

/*
Exceptions

   1) This routine defines local solar time for any point on the
      surface of the Sun to be 12:00:00 noon.

   2) If the type of the coordinates is not recognized, the
      error SPICE(UNKNOWNSYSTEM) will be signaled.

   3) If the bodyfixed frame to associate with body cannot be
      determined, the error SPICE(CANTFINDFRAME) is signaled.

   4) If insufficient data are available to compute the
      location of the sun in bodyfixed coordinates, the
      error will be diagnosed by a routine called by this one.

   5) If the input type string is empty, the error SPICE(EMPTYSTRING)
      will be signaled.

   6) If any of the routine's string arguments have null pointers, the
      error SPICE(NULLPOINTER) will be signaled.

   7) If either of the output strings are too short to accommodate
      at least one character of data in addition to a terminating
      null character, the error SPICE(STRINGTOOSHORT) will be
      signaled.
      */

void USpice::et2lst(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSEphemerisTime& et,
    int body,
    const FSAngle& lon,
    ES_LongitudeType type,
    int& hr,
    int& mn,
    int& sc,
    FString& time,
    FString& ampm
)
{
    // Buffers
    SpiceChar szTime[WINDOWS_MAX_PATH];
    ZeroOut(szTime);

    SpiceChar szAmPm[WINDOWS_MAX_PATH];
    ZeroOut(szAmPm);

    // Inputs
    SpiceDouble        _et = et.seconds;
    SpiceInt           _body = body;
    SpiceDouble        _lon = lon.radians();
    SpiceChar* _type;
    SpiceInt           _timlen = sizeof(szTime);
    SpiceInt           _ampmlen = sizeof(szAmPm);
    switch (type)
    {
    case ES_LongitudeType::Planetocentric:
        _type = "PLANETOCENTRIC";
        break;
    case ES_LongitudeType::Planetographic:
        _type = "PLANETOGRAPHIC";
        break;
    default:
        _type = "";
        break;
    }

    // Outputs
    SpiceInt _hr = 0;
    SpiceInt _mn = 0;
    SpiceInt _sc = 0;
    SpiceChar* _time = szTime;
    SpiceChar* _ampm = szAmPm;

    // Invocation
    et2lst_c(_et, _body, _lon, _type, _timlen, _ampmlen, &_hr, &_mn, &_sc, _time, _ampm);

    // Return Values
    hr = _hr;
    mn = _mn;
    sc = _sc;

    time = FString(_time);
    ampm = FString(_ampm);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
1) If the format for the output string is not recognized, the
      error SPICE(INVALIDTIMEFORMAT) is signaled.

   2) If prec is less than or equal to zero, it is treated as
      zero.  If prec is greater than 14, it is treated as 14.

   3) If one of the ISO formats is specified (ISOC or ISOD) but
      the year corresponding to ET is prior to 1  A.D. on the
      Gregorian Calendar, the error SPICE(YEAROUTOFRANGE) will
      be signaled.

   4) Epochs prior to 15 Oct, 1582 on the Gregorian calendar (the
      calendar commonly used in western societies) are returned in the
      "extended" Gregorian Calendar.  To convert epochs to the Julian
      calendar see the header of the function gr2jul_ in the file
      jul2gr.c.

   5) This routine does not attempt to account for variations
      in the length of the second that were in effect prior
      to Jan 1, 1972.  For days prior to that date, we assume
      there are exactly 86400 ephemeris seconds. Consequently
      the UTC gregorian calendar strings produced for epochs
      prior to Jan 1, 1972 differ from the corresponding
      TDB calendar strings by approximately 41.18 seconds.
      (TDB gregorian calendar strings are produced by the
      routine ETCAL).

   6) The error SPICE(NULLPOINTER) is signaled if either of
      the input or output string pointers is null.

   7) If the input string has length zero, the error SPICE(EMPTYSTRING)
      will be signaled.

   8) The caller must pass a value indicating the length of the output
      string.  If this value is not at least 2, the error
      SPICE(STRINGTOOSHORT) is signaled.

   9) The user's processing environment must be properly initialized by
      loading a leapseconds kernel via the routine furnsh_c before
      calling this routine.  If a leapsecond kernel has not been
      loaded, an error will be signaled by a routine in the call tree
      of this routine.
    */
void USpice::et2utc(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSEphemerisTime& et,
    ES_UTCTimeFormat format,
    int          prec,
    FString& utcstr
)
{
    // Buffers
    SpiceChar szUtc[WINDOWS_MAX_PATH];
    ZeroOut(szUtc);

    // Inputs
    SpiceDouble     _et = et.seconds;
    SpiceInt		_prec = prec;
    ConstSpiceChar* _format;
    switch (format)
    {
    case ES_UTCTimeFormat::Calendar:
        _format = "C";
        break;
    case ES_UTCTimeFormat::DayOfYear:
        _format = "D";
        break;
    case ES_UTCTimeFormat::JulianDate:
        _format = "J";
        break;
    case ES_UTCTimeFormat::ISOCalendar:
        _format = "ISOC";
        break;
    case ES_UTCTimeFormat::ISODayOfYear:
        _format = "ISOD";
        break;
    default:
        _format = "";
        break;
    }

    // Outputs
    SpiceChar* _utcstr = szUtc;
    SpiceInt		_lenout = sizeof(szUtc);

    // Invocation
    et2utc_c(_et, _format, _prec, _lenout, _utcstr);

    // Return Value
    utcstr = FString(_utcstr);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
* Exceptions
   1)   If any of axis3, axis2, or axis1 do not have values in

           { 1, 2, 3 },

        the error SPICE(BADAXISNUMBERS) is signalled.
*/
void USpice::eul2m(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    FSRotationMatrix& r,
    const FSAngle& angle3,
    const FSAngle& angle2,
    const FSAngle& angle1,
    ES_Axis axis3,
    ES_Axis axis2,
    ES_Axis axis1
)
{
    // Inputs
    SpiceDouble  _angle3 = angle3.AsDouble();
    SpiceDouble  _angle2 = angle2.AsDouble();
    SpiceDouble  _angle1 = angle1.AsDouble();
    SpiceInt     _axis3 = (SpiceInt)axis3;
    SpiceInt     _axis2 = (SpiceInt)axis2;
    SpiceInt     _axis1 = (SpiceInt)axis1;

    // Outputs
    SpiceDouble  _r[3][3];  FSRotationMatrix::Identity.CopyTo(_r);

    // Invocation
    eul2m_c(_angle3, _angle2, _angle1, _axis3, _axis2, _axis1, _r);

    // Return Value
    r = FSRotationMatrix(_r);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
* Remember, this is a COORDINATE SYSTEM rotation by x radians; this
   matrix, when applied to a vector, rotates the vector by -x
   radians, not x radians.  Applying the matrix to a vector yields
   the vector's representation relative to the rotated coordinate
   system
/*
* Exceptions

   All erroneous inputs are diagnosed by routines in the call
   tree to this routine.  These include

   1)   If any of axisa, axisb, or axisc do not have values in

           { 1, 2, 3 },

        then the error SPICE(INPUTOUTOFRANGE) is signaled.
*/
void USpice::eul2xf(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSEulerAngularState& eulang,
    FSEulerAngularTransform& xform
)
{
    // Inputs
    uint8	_axisa;
    uint8	_axisb;
    uint8	_axisc;
    SpiceDouble	_eulang[6];		eulang.CopyTo(_eulang, _axisa, _axisb, _axisc);

    // Outputs
    SpiceDouble	_xform[6][6];	ZeroOut(_xform);

    // Invocation
    eul2xf_c(_eulang, (SpiceInt)_axisa, (SpiceInt)_axisb, (SpiceInt)_axisc, _xform);

    // Return Value
    xform = FSEulerAngularTransform(_xform);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}



/*
Exceptions

   Error Free.

   1) If x on input is the zero vector the ``standard'' frame (ijk)
      is returned.
*/
void USpice::frame(
    const FSDimensionlessVector& x_in,
    FSDimensionlessVector& x,
    FSDimensionlessVector& y,
    FSDimensionlessVector& z
)
{
    // Input/Output
    SpiceDouble _x[3];   x_in.CopyTo(_x);
    // Outputs
    SpiceDouble _y[3];
    SpiceDouble _z[3];

    // Invocation
    frame_c(_x, _y, _z);

    // Return Values
    x = FSDimensionlessVector(_x);
    y = FSDimensionlessVector(_y);
    z = FSDimensionlessVector(_z);
}


void USpice::gcpool(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    TArray<FString>&    cvals,
    bool&               found,
    const FString&      name,
    int                 start,
    int                 room
)
{
    // Inputs
    ConstSpiceChar* _name = TCHAR_TO_ANSI(*name);
    SpiceInt        _start = start;
    SpiceInt        _room = room;
    SpiceInt        _lenout = WINDOWS_MAX_PATH;
    // Outputs
    SpiceInt        _n = 0;
    size_t buffer_size = _lenout * _room * sizeof(SpiceChar);
    void* _cvals = StackAlloc(buffer_size);
    SpiceBoolean    _found = SPICEFALSE;

    // Invocation
    memset(_cvals, 0, buffer_size);
    gcpool_c(_name, _start, _room, _lenout, &_n, _cvals, &_found);

    // Return Values
    cvals = TArray<FString>();
    for (int i = 0; i < _n; ++i)
    {
        cvals.Add(FString((SpiceChar*)_cvals + i * _lenout));
    }

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


void USpice::gdpool(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    TArray<double>& values,
    bool& found,
    const FString& name,
    int                 start,
    int                 room
)
{
    // Inputs
    ConstSpiceChar* _name = TCHAR_TO_ANSI(*name);
    SpiceInt        _start = start;
    SpiceInt        _room = room;
    // Outputs
    SpiceInt        _n = 0;
    size_t buffer_size = _room * sizeof(SpiceDouble);
    SpiceDouble* _values = (SpiceDouble*)StackAlloc(buffer_size);
    SpiceBoolean    _found = SPICEFALSE;

    // Invocation
    memset(_values, 0, buffer_size);
    gdpool_c(_name, _start, _room, &_n, _values, &_found);

    // Return values
    values = TArray<double>();
    for (int i = 0; i < _n; ++i)
    {
        values.Add(*((SpiceDouble*)_values + i));
    }

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

void USpice::gdpool_scalar(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    double& value,
    bool& found,
    const FString& name
)
{
    // Inputs
    ConstSpiceChar* _name = TCHAR_TO_ANSI(*name);
    SpiceInt        _start = 0;
    SpiceInt        _room = 1;
    // Outputs
    SpiceInt        _n = 0;
    SpiceDouble     _value = 0;
    SpiceBoolean    _found = SPICEFALSE;

    // Invocation
    gdpool_c(_name, _start, _room, &_n, &_value, &_found);

    // Return values
    value = _value;

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

void USpice::gdpool_distance(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    FSDistance& value,
    bool& found,
    const FString& name
)
{
    // Inputs
    ConstSpiceChar* _name = TCHAR_TO_ANSI(*name);
    SpiceInt        _start = 0;
    SpiceInt        _room = 1;
    // Outputs
    SpiceInt        _n = 0;
    SpiceDouble     _value = 0;
    SpiceBoolean    _found = SPICEFALSE;

    // Invocation
    gdpool_c(_name, _start, _room, &_n, &_value, &_found);

    // Return values
    value = FSDistance(_value);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

void USpice::gdpool_vector(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    FSDistanceVector& value,
    bool& found,
    const FString& name
)
{
    // Inputs
    ConstSpiceChar* _name = TCHAR_TO_ANSI(*name);
    SpiceInt        _start = 0;
    SpiceInt        _room = 3;
    // Outputs
    SpiceInt        _n = 0;
    SpiceDouble     _value[3];  ZeroOut(_value);
    SpiceBoolean    _found = SPICEFALSE;

    // Invocation
    gdpool_c(_name, _start, _room, &_n, _value, &_found);

    // Return values
    value = FSDistanceVector(_value);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


void USpice::gdpool_mass(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    FSMassConstant& value,
    bool& found,
    const FString& name
)
{
    // Inputs
    ConstSpiceChar* _name = TCHAR_TO_ANSI(*name);
    SpiceInt        _start = 0;
    SpiceInt        _room = 1;
    // Outputs
    SpiceInt        _n = 0;
    SpiceDouble     _value = 0;
    SpiceBoolean    _found = SPICEFALSE;

    // Invocation
    gdpool_c(_name, _start, _room, &_n, &_value, &_found);

    // Return values
    value = FSMassConstant(_value);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


/*
Exceptions

   1) If the requested kernel variable is not found in the kernel
      pool, the error SPICE(KERNELVARNOTFOUND) is signaled.

   2) If the requested kernel variable is found but the associated
      values aren't numeric, the error SPICE(TYPEMISMATCH) is
      signaled.

   3) The output array `values' must be declared with sufficient size
      to contain all of the values associated with the requested kernel
      variable.  If the dimension of `values' indicated by `maxn' is
      too small to contain the requested values, the error
      SPICE(ARRAYTOOSMALL) is signaled.

   4) If the input dimension `maxn' indicates there is more room
      in `values' than there really is---for example, if `maxn' is
      10 but `values' is declared with dimension 5---and the dimension
      of the requested kernel variable is larger than the actual
      dimension of `values', then this routine may overwrite
      memory.  The results are unpredictable.

   5) If the input string pointer `item' is null, the error
      SPICE(NULLPOINTER) will be signaled.

   6) If either of the input strings referred to by `item' contains
      no data characters, the error SPICE(EMPTYSTRING) will
      be signaled.
*/
void USpice::georec(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSLonLat& lonlat,
    const FSDistance& alt,
    const FSDistance& re,
    FSDistanceVector& rectan,
    double f
)
{
    SpiceDouble _rectan[3];
    ZeroOut(_rectan);

    georec_c(lonlat.longitude.radians(), lonlat.latitude.radians(), alt.km, re.km, f, _rectan);
    rectan = FSDistanceVector(_rectan);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


/*
* Exceptions - a lot
*/
#define MAXBND 16
#define WDSIZE 256
void USpice::getfov(
    ES_ResultCode& ResultCode,
    FString&    ErrorMessage,
    int       instid,
    FString&    shape,
    FString&    frame,
    FSDimensionlessVector&          bsight,
    TArray<FSDimensionlessVector>&   bounds
)
{
    SpiceInt        _instid = instid;
    SpiceInt        _room = MAXBND;
    SpiceChar       _shape[WDSIZE];     ZeroOut(_shape);
    SpiceChar       _frame[WDSIZE];     ZeroOut(_frame);
    SpiceInt        _shapelen = sizeof(_shape);
    SpiceInt        _framelen = sizeof(_frame);
    SpiceDouble     _bsight[3];  ZeroOut(_bsight);
    SpiceInt        _n = 0;
    SpiceDouble     _bounds[MAXBND][3];  ZeroOut(_bounds);

    // Invocation
    getfov_c(
            _instid,
            _room,
            _shapelen,
            _framelen,
            _shape,
            _frame,
            _bsight,
            &_n,
            _bounds
        );

    // Set Outputs
    shape = FString(_shape);
    frame = FString(_frame);
    bsight = FSDimensionlessVector(_bsight);

    bounds.Empty();
    for (int i = 0; i < _n; ++i)
    {
        bounds.Add(FSDimensionlessVector(_bounds[i]));
    }

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


void USpice::gipool(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    TArray<int>& ivals,
    bool& found,
    const FString& name,
    int             start,
    int             room
)
{
    // Inputs
    ConstSpiceChar* _name = TCHAR_TO_ANSI(*name);
    SpiceInt        _start = start;
    SpiceInt        _room = room;
    // Outputs
    SpiceInt        _n = 0;
    size_t buffer_size = _room * sizeof(SpiceInt);
    SpiceInt* _ivals = (SpiceInt*)StackAlloc(buffer_size);
    SpiceBoolean    _found = SPICEFALSE;

    // invocation
    memset(_ivals, 0, buffer_size);
    gipool_c(_name, _start, _room, &_n, _ivals, &_found);

    // Return values
    ivals = TArray<int>();
    for (int i = 0; i < _n; ++i)
    {
        ivals.Add((int)*((SpiceInt*)_ivals + i));
    }

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

void USpice::gnpool(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    TArray<FString>& kvars,
    bool& found,
    const FString& name,
    int                 start,
    int                 room
)
{
    // Inputs
    ConstSpiceChar* _name = TCHAR_TO_ANSI(*name);
    SpiceInt        _start = start;
    SpiceInt        _room = room;
    SpiceInt        _lenout = WINDOWS_MAX_PATH;
    // Outputs
    SpiceInt        _n = 0;
    size_t buffer_size = _lenout * _room * sizeof(SpiceChar);
    void* _kvars = StackAlloc(buffer_size);
    SpiceBoolean    _found = SPICEFALSE;

    // Invocation
    memset(_kvars, 0, buffer_size);
    gnpool_c(_name, _start, _room, _lenout, &_n, _kvars, &_found);

    // Return Values
    kvars = TArray<FString>();
    for (int i = 0; i < _n; ++i)
    {
        kvars.Add(FString((SpiceChar*)_kvars + i * _lenout));
    }

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}



/*
Exceptions


   1)  If the specified aberration correction is relativistic or
       calls for stellar aberration but not light time correction,
       the error SPICE(NOTSUPPORTED) is signaled. If the specified
       aberration correction is any other unrecognized value, the
       error will be diagnosed and signaled by a routine in the call
       tree of this routine.

   2)  If either the target or observer input strings cannot be
       converted to an integer ID code, the error SPICE(IDCODENOTFOUND)
       is signaled.

   3)  If `obsrvr' and `target' map to the same NAIF integer ID code,
       the error SPICE(BODIESNOTDISTINCT) is signaled.

   4)  If the input target body-fixed frame `fixref' is not
       recognized, the error SPICE(NOFRAME) is signaled. A frame
       name may fail to be recognized because a required frame
       specification kernel has not been loaded; another cause is a
       misspelling of the frame name.

   5)  If the input frame `fixref' is not centered at the target body,
       the error SPICE(INVALIDFRAME) is signaled.

   6)  If the input argument `METHOD' is not recognized, the error
       SPICE(INVALIDMETHOD) is signaled.

   7)  If insufficient ephemeris data have been loaded prior to
       calling ilumin_c, the error will be diagnosed and signaled by a
       routine in the call tree of this routine. Note that when
       light time correction is used, sufficient ephemeris data must
       be available to propagate the states of observer, target, and
       the sun to the solar system barycenter.

   8)  If the computation method specifies an ellipsoidal target
       shape and triaxial radii of the target body have not been
       loaded into the kernel pool prior to calling ilumin_c, the
       error will be diagnosed and signaled by a routine in the call
       tree of this routine.

   9)  The target must be an extended body: if any of the radii of
       the target body are non-positive, the error will be
       diagnosed and signaled by routines in the call tree of this
       routine.

   10) If PCK or CK data specifying the target body-fixed frame
       orientation have not been loaded prior to calling ilumin_c,
       the error will be diagnosed and signaled by a routine in the
       call tree of this routine.

   11) If ``method'' specifies that the target surface is represented by
       DSK data, and no DSK files are loaded for the specified
       target, the error is signaled by a routine in the call tree
       of this routine.

   12) If `method' specifies that the target surface is represented
       by DSK data, and data representing the portion of the surface
       on which `spoint' is located are not available, an error will
       be signaled by a routine in the call tree of this routine.

   13) If `method' specifies that the target surface is represented
       by DSK data, `spoint' must lie on the target surface, not above
       or below it. A small tolerance is used to allow for round-off
       error in the calculation determining whether `spoint' is on the
       surface. If, in the DSK case, `spoint' is too far from the
       surface, an error will be signaled by a routine in the call
       tree of this routine.

       If the surface is represented by a triaxial ellipsoid, `spoint'
       is not required to be close to the ellipsoid; however, the
       results computed by this routine will be unreliable if `spoint'
       is too far from the ellipsoid.
*/

void USpice::ilumin(
    ES_ResultCode&          ResultCode,
    FString&                ErrorMessage,
    const FSDistanceVector& spoint,
    const FSEphemerisTime&  et,
    FSEphemerisTime&        trgepc,
    FSDistanceVector&       srfvec,
    FSAngle&                phase,
    FSAngle&                incdnc,
    FSAngle&                emissn,
    const FString&          method,
    const FString&          target,
    const FString&          fixref,
    ES_AberrationCorrectionWithTransmissions abcorr,
    const FString&          obsrvr
)
{
    // Inputs
    ConstSpiceChar* _method = TCHAR_TO_ANSI(*method);
    ConstSpiceChar* _target = TCHAR_TO_ANSI(*target);
    SpiceDouble     _et     = et.AsDouble();
    ConstSpiceChar* _fixref = TCHAR_TO_ANSI(*fixref);
    ConstSpiceChar* _abcorr;
    ConstSpiceChar* _obsrvr = TCHAR_TO_ANSI(*obsrvr);
    SpiceDouble     _spoint[3]; spoint.CopyTo(_spoint);

    // Outputs
    SpiceDouble     _trgepc = 0.;
    SpiceDouble     _srfvec[3];     ZeroOut(_srfvec);
    SpiceDouble     _phase  = 0.;
    SpiceDouble     _incdnc = 0.;
    SpiceDouble     _emissn = 0.;

    switch (abcorr)
    {
    case ES_AberrationCorrectionWithTransmissions::LT:
        _abcorr = "LT";
        break;
    case ES_AberrationCorrectionWithTransmissions::LT_S:
        _abcorr = "LT+S";
        break;
    case ES_AberrationCorrectionWithTransmissions::CN:
        _abcorr = "CN";
        break;
    case ES_AberrationCorrectionWithTransmissions::CN_S:
        _abcorr = "CN+S";
        break;
    case ES_AberrationCorrectionWithTransmissions::XLT:
        _abcorr = "XLT";
        break;
    case ES_AberrationCorrectionWithTransmissions::XLT_S:
        _abcorr = "XLT+S";
        break;
    case ES_AberrationCorrectionWithTransmissions::XCN:
        _abcorr = "XCN";
        break;
    case ES_AberrationCorrectionWithTransmissions::XCN_S:
        _abcorr = "XCN+S";
        break;
    default:
        _abcorr = "NONE";
    };

    // invocation
    ilumin_c(
        _method,
        _target,
        _et,
        _fixref,
        _abcorr,
        _obsrvr,
        _spoint,
        &_trgepc,
        _srfvec,
        &_phase,
        &_incdnc,
        &_emissn
    );

    // Copy Outputs
    trgepc = FSEphemerisTime(_trgepc);
    srfvec = FSDistanceVector(_srfvec);
    phase  = FSAngle(_phase);
    incdnc = FSAngle(_incdnc);
    emissn = FSAngle(_emissn);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


/*
Exceptions

   1)  If radii for `body' are not found in the kernel pool, the error
       will be diagnosed by routines called by this routine.

   2)  If radii for `body' are invalid, the error will be diagnosed by
       routines called by this routine.  The radii should be
       positive.

*/
void USpice::srfrec(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSLonLat& lonlat,
    FSDistanceVector&   rectan,
    int           body
)
{
    // Inputs
    SpiceInt      _body         = (SpiceInt)body;
    SpiceDouble   _longitude    = lonlat.longitude.radians();
    SpiceDouble   _latitude     = lonlat.latitude.radians();
    
    // Output
    SpiceDouble   _rectan[3];     ZeroOut(_rectan);

    // invocation
    srfrec_c(_body, _longitude, _latitude, _rectan);

    // Copy Outputs
    rectan = FSDistanceVector(_rectan);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


/*
Exceptions
   1) The error SPICE(UNPARSEDTIME) is signaled if the
      string cannot be recognized as a legitimate time string.

   2) The error SPICE(TIMECONFLICT) is signaled if more than
      one time system is specified as part of the time string.

   3) The error SPICE(BADTIMESTRING) is signaled if any component
      of the time string is outside the normal range of usage.
      For example, the day January 35 is outside the normal range
      of days in January. The checks applied are spelled out in
      the routine tcheck_.

   4) The error SPICE(EMPTYSTRING) is signaled if the input
      string does not contain at least one character, since the
      input string cannot be converted to a Fortran-style string
      in this case.

   5) The error SPICE(NULLPOINTER) is signaled if the input string
      pointer is null.
*/
void USpice::str2et(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    FSEphemerisTime& et,
    const FString& str
)
{
    SpiceDouble _et;

    str2et_c(TCHAR_TO_ANSI(*str), &_et);

    et = FSEphemerisTime(_et);

    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions
   1) The error SPICE(EMPTYSTRING) is signaled if the input
      string does not contain at least one character, since the
      input string cannot be converted to a Fortran-style string
      in this case.

   2) The error SPICE(NULLPOINTER) is signaled if either of
      the input or output string pointers is null.

   3) The user must pass a value indicating the length of the output
      string.  If this value is not at least 2, the error
      SPICE(STRINGTOOSHORT) is signaled.

   The user's processing environment must be properly initialized by
   loading a leapseconds kernel via the routine furnsh_c before calling
   this routine.  If a leapsecond kernel has not been loaded, an error
   will be signaled by routines called by timout_c.
*/

void USpice::timout(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    FString& output,
    const FSEphemerisTime& et,
    const FString& pictur
)
{
    SpiceChar szBuffer[WINDOWS_MAX_PATH];
    ZeroOut(szBuffer);

    timout_c(et.seconds, TCHAR_TO_ANSI(*pictur), sizeof(szBuffer), szBuffer);

    output = FString(szBuffer);

    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   Error free.

   This routine returns information about parse errors in the output
   string `errmsg'.
*/
void USpice::tparse(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    FSEphemerisTime& ReturnValue,
    const FString& string
)
{
    // Buffer
    SpiceChar szBuffer[WINDOWS_MAX_PATH];
    ZeroOut(szBuffer);

    // Inputs
    ConstSpiceChar* _string = TCHAR_TO_ANSI(*string);
    SpiceInt        _lenout = sizeof(szBuffer);

    // Outputs
    SpiceDouble		_sp2000 = 0;
    SpiceChar* _errmsg = szBuffer;


    tparse_c(_string, _lenout, &_sp2000, _errmsg);

    if (strnlen_s(_errmsg, _lenout))
    {
        ErrorMessage = FString(_errmsg);
        ResultCode = ES_ResultCode::Error;
    }
    else
    {
        ResultCode = ES_ResultCode::Success;
    }
}

void USpice::et_now(FSEphemerisTime& Now)
{
    auto now = FDateTime::UtcNow();
    auto j2000 = FDateTime::FromJulianDay(2451545.0);
    auto now_j2000 = now - j2000;

    Now = FSEphemerisTime(now_j2000.GetTotalSeconds());
}

/*
Exceptions
   Error free.
*/
void USpice::latrec(
    const FSDistance&    radius,
    const FSLonLat& lonlat,
    FSDistanceVector& rectan
)
{
    // Inputs
    SpiceDouble    _radius = radius.AsDouble();
    SpiceDouble    _longitude;
    SpiceDouble    _latitude;
    lonlat.CopyTo(_longitude, _latitude);

    // Outputs
    SpiceDouble    _rectan[3];

    // Invocation
    latrec_c(_radius, _longitude, _latitude, _rectan);

    // Copy output
    rectan = FSDistanceVector(_rectan);
}

#if 0
void USpice::mxvg(
    const void* m1,
    const void* v2,
    SpiceInt       nrow1,
    SpiceInt       nc1r2,
    void* vout
)
{
    mxvg_c(m1, v2, nrow1, nc1r2, vout);
}
#endif

/*
* Exceptions

   Error free.

   1)  If `q' is not a unit quaternion, the output matrix `r' is
       unlikely to be a rotation matrix.
*/
void USpice::q2m(
    const FSQuaternion& q,
    FSRotationMatrix& r
)
{
    SpiceDouble _r[3][3];
    q2m_c(q.q, _r);

    r = FSRotationMatrix(_r);
}

/*
Exceptions
   1)   If `r' is not a rotation matrix, the error SPICE(NOTAROTATION)
        is signaled
*/
void USpice::m2q(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSRotationMatrix& r,
    FSQuaternion& q
)
{
    SpiceDouble _q[4];
    m2q_c(r.m, _q);

    q = FSQuaternion(_q);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions
   Error free.
*/
void USpice::qxq(
    const FSQuaternion& q1,
    const FSQuaternion& q2,
    FSQuaternion& qout
)
{
    SpiceDouble _qout[4];
    qxq_c(q1.q, q2.q, _qout);
    qout = FSQuaternion(_qout);
}

/*
Exceptions
   Error free.
*/
void USpice::mxm(
    const FSRotationMatrix& m1,
    const FSRotationMatrix& m2,
    FSRotationMatrix& mout
)
{
    SpiceDouble _mout[3][3];

    mxm_c(m1.m, m2.m, _mout);

    mout = FSRotationMatrix(_mout);
}

/*
Exceptions
   Error free.
*/
void  USpice::mxmt(
    const FSRotationMatrix& m1,
    const FSRotationMatrix& m2,
    FSRotationMatrix& mout
)
{
    SpiceDouble _mout[3][3];

    mxmt_c(m1.m, m2.m, _mout);

    mout = FSRotationMatrix(_mout);
}


/*
Exceptions
   Error free.
*/
void USpice::mtxm(
    const FSRotationMatrix& m1,
    const FSRotationMatrix& m2,
    FSRotationMatrix& mout
)
{
    SpiceDouble _mout[3][3];

    mtxm_c(m1.m, m2.m, _mout);

    mout = FSRotationMatrix(_mout);
}


/*
Exceptions
   Error free.
*/
void USpice::mtxv(
    const FSRotationMatrix& m1,
    const FSDimensionlessVector& vin,
    FSDimensionlessVector& vout
)
{
    // Inputs
    SpiceDouble    _m1[3][3];	m1.CopyTo(_m1);
    SpiceDouble    _vin[3];		vin.CopyTo(_vin);

    // Outputs
    SpiceDouble    _vout[3];

    // Invocation
    mtxv_c(_m1, _vin, _vout);

    // Return Value
    vout = FSDimensionlessVector(_vout);
}


/*
Exceptions
   Error free.
*/

void USpice::mtxv_distance(
        const FSRotationMatrix& m1,
        const FSDistanceVector& vin,
        FSDistanceVector& vout
    )
{
    // Inputs
    SpiceDouble    _m1[3][3];	m1.CopyTo(_m1);
    SpiceDouble    _vin[3];		vin.CopyTo(_vin);

    // Outputs
    SpiceDouble    _vout[3];

    // Invocation
    mtxv_c(_m1, _vin, _vout);

    // Return Value
    vout = FSDimensionlessVector(_vout);
}


/*
Exceptions
   Error free.
*/ 
void USpice::mtxv_velocity(
    const FSRotationMatrix& m1,
    const FSVelocityVector& vin,
    FSVelocityVector& vout
)
{
    // Inputs
    SpiceDouble    _m1[3][3];	m1.CopyTo(_m1);
    SpiceDouble    _vin[3];		vin.CopyTo(_vin);

    // Outputs
    SpiceDouble    _vout[3];

    // Invocation
    mtxv_c(_m1, _vin, _vout);

    // Return Value
    vout = FSDimensionlessVector(_vout);
}


/*
Exceptions
   1)   If any of axis3, axis2, or axis1 do not have values in

           { 1, 2, 3 },

        then the error SPICE(INPUTOUTOFRANGE) is signalled.

   2)   An arbitrary rotation matrix cannot be expressed using
        a sequence of Euler angles unless the second rotation axis
        differs from the other two.  If axis2 is equal to axis3 or
        axis1, then then error SPICE(BADAXISNUMBERS) is signalled.

   3)   If the input matrix r is not a rotation matrix, the error
        SPICE(NOTAROTATION) is signalled.

   4)   If angle3 and angle1 are not uniquely determined, angle3
        is set to zero, and angle1 is determined.
*/

void USpice::m2eul(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    FSEulerAngles& eulers,
    const FSRotationMatrix& r,
    ES_Axis axis3,
    ES_Axis axis2,
    ES_Axis axis1
)
{
    // Inputs
    SpiceDouble	_r[3][3];	r.CopyTo(_r);
    SpiceInt	_axis3 = (SpiceInt)axis3;
    SpiceInt	_axis2 = (SpiceInt)axis2;
    SpiceInt	_axis1 = (SpiceInt)axis1;
    // Outputs
    SpiceDouble	_angles[3];

    // Invocation
    m2eul_c(_r, _axis3, _axis2, _axis1, &_angles[0], &_angles[1], &_angles[2]);

    // Return Value
    eulers = FSEulerAngles(_angles, _axis3, _axis2, _axis1);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}



/*
Exceptions
   1)  The error SPICE(DIVIDEBYZERO) signals from a routine
       in the call tree if two input abscissas are equal,

   2)  The error SPICE(INVALIDSIZE) signals from a routine
       in the call tree if n is less than 1.

   3)  This routine does not attempt to ward off or diagnose
       arithmetic overflows.
*/
void USpice::hrmint(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const TArray<double>& xvals,
    const TArray<double>& yvals,
    double x,
    double& f,
    double& df
)
{
    // Inputs
    SpiceInt		_n = xvals.Num();
    SpiceDouble* _xvals = (SpiceDouble*)StackAlloc(xvals.Num() * sizeof(SpiceDouble));
    SpiceDouble* _yvals = (SpiceDouble*)StackAlloc(yvals.Num() * sizeof(SpiceDouble));
    SpiceDouble		_x = x;
    SpiceDouble* _work = (SpiceDouble*)StackAlloc(4 * _n * sizeof(SpiceDouble));
    for (int i = 0; i < xvals.Num(); i++) _xvals[i] = xvals[i];
    for (int i = 0; i < yvals.Num(); i++) _yvals[i] = yvals[i];
    // Outputs
    SpiceDouble _f = 0;
    SpiceDouble _df = 0;

    if (yvals.Num() != 2 * xvals.Num())
    {
        ResultCode = ES_ResultCode::Error;
        ErrorMessage = TEXT("yvals array dimension must be twice xvals array dimension");
        return;
    }

    hrmint_c(_n, _xvals, _yvals, _x, _work, &_f, &_df);

    f = _f;
    df = _df;

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   Error free.
*/
void USpice::halfpi(double& half_pi)
{
    half_pi = (double)halfpi_c();
}

void USpice::halfpi_angle(FSAngle& half_pi)
{
    half_pi = FSAngle(halfpi_c());
}

/*
Exceptions

   Error free.
*/
void USpice::ident(
    FSRotationMatrix& matrix
)
{
    SpiceDouble    _matrix[3][3];
    ZeroOut(_matrix);

    ident_c(_matrix);

    matrix = FSRotationMatrix(_matrix);
}

/*
Exceptions

   1)  The input plane must be a CSPICE plane: the normal vector must
       be non-zero and the constant must be non-negative.
       If the input plane is invalid, the error SPICE(INVALIDPLANE)
       will be signaled.

   2)  If the input ellipse has non-orthogonal axes, the error
       SPICE(INVALIDELLIPSE) will be signaled.

   3)  The input ellipse is allowed to be a line segment or a point;
       these cases are not considered to be errors. If the ellipse
       consists of a single point and lies in the plane, the number
       of intersection points is set to 1 (rather than -1) and
       the output arguments `xpt1' and `xpt2' are assigned the value
       of the ellipse's center.
*/

void USpice::inelpl(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSEllipse& ellips,
    const FSPlane& plane,
    TArray<FSDistanceVector>& xpts,
    bool& coplanar
)
{
    // Inputs
    SpiceEllipse _ellips;   CopyTo(ellips, _ellips);
    SpicePlane _plane;      CopyTo(plane, _plane);
    // Outputs
    SpiceInt			    _nxpts = 0;
    SpiceDouble			    _xpt1[3];	ZeroOut(_xpt1);
    SpiceDouble			    _xpt2[3];	ZeroOut(_xpt2);

    // Invocation
    inelpl_c(&_ellips, &_plane, &_nxpts, _xpt1, _xpt2);

    // Return Values
    coplanar = _nxpts < 0;
    xpts = TArray<FSDistanceVector>();
    if (_nxpts > 0)
    {
        xpts.Add(FSDistanceVector(_xpt1));
    }
    if (_nxpts > 1)
    {
        xpts.Add(FSDistanceVector(_xpt2));
    }

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


void USpice::intmax(int& int_max)
{
    SpiceInt _int_max = intmax_c();

    // This is a little bit terrible, because there's nothing that guarantees the max
    // int is even representable in our chosen Blueprints SpiceInt Wrapper... other than design
    // and knowledge of the relevant platforms.
    // It could perhaps be an issue if others use this module.
    int_max = _int_max;
}

void USpice::intmin(int& int_min)
{
    SpiceInt _int_min = intmin_c();

    // Ugh.  See intmax() comments
    int_min = _int_min;
}

/*
Exceptions

   1) No internal checking on the input matrix m1 is performed except on
      the size of its determinant.  Thus it is possible to generate a
      floating point overflow or underflow in the process of
      calculating the matrix of cofactors.

   2) If the determinant is less than 10**-16, the matrix is deemed to
      be singular and the output matrix is filled with zeros.
*/
void USpice::invert(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSRotationMatrix& m1,
    FSRotationMatrix& mout
)
{
    // Input
    SpiceDouble  _m1[3][3];		m1.CopyTo(_m1);
    // Output
    SpiceDouble  _mout[3][3];	ZeroOut(_mout);

    // Invocation
    invert_c(_m1, _mout);

    // Return Value
    mout = FSRotationMatrix(_mout);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

void USpice::invort(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSRotationMatrix& m,
    FSRotationMatrix& mit
)
{
    // Input
    SpiceDouble	_m[3][3];	m.CopyTo(_m);
    // Output
    SpiceDouble	_mit[3][3];	ZeroOut(_mit);

    // Invocation
    invort_c(_m, _mit);

    // Return Value
    mit = FSRotationMatrix(_mit);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions
   Error free
*/
void USpice::b1900(
    FSEphemerisTime& b1900
)
{
    SpiceDouble _b1900 = b1900_c();
    b1900 = FSEphemerisTime(_b1900);
}

/*
Exceptions
   Error free
*/
void USpice::b1950(
    FSEphemerisTime& b1950
)
{
    SpiceDouble _b1950 = b1950_c();
    b1950 = FSEphemerisTime(_b1950);
}


/*
Exceptions
   Error free
*/
void USpice::j1900(
    FSEphemerisTime& j1900
)
{
    SpiceDouble _j1900 = j1900_c();
    j1900 = FSEphemerisTime(_j1900);
}

/*
Exceptions
   Error free
*/
void USpice::j1950(
    FSEphemerisTime& j1950
)
{
    SpiceDouble _j1950 = j1950_c();
    j1950 = FSEphemerisTime(_j1950);
}

/*
Exceptions
   Error free
*/
void USpice::j2000(
    FSEphemerisTime& j2000
)
{
    SpiceDouble _j2000 = j2000_c();
    j2000 = FSEphemerisTime(_j2000);
}

/*
Exceptions
   Error free
*/
void USpice::j2100(
    FSEphemerisTime& j2100
)
{
    SpiceDouble _j2100 = j2100_c();
    j2100 = FSEphemerisTime(_j2100);
}


/*
Exceptions
   Error free
*/
void USpice::jyear(double& secondsPerJulianYear)
{
    secondsPerJulianYear = jyear_c();
}

/*
Exceptions
   Error free
*/
void USpice::tyear(double& secondsPerTropicalYear)
{
    secondsPerTropicalYear = tyear_c();
}

/*
Exceptions
   Error free
*/
void USpice::jyear_year(FSEphemerisPeriod& oneJulianYear)
{
    SpiceDouble _jyear = jyear_c();
    oneJulianYear = FSEphemerisPeriod(_jyear);
}

/*
Exceptions
   Error free
*/
void USpice::tyear_year(FSEphemerisPeriod& oneTropicalYear)
{
    SpiceDouble _tyear = tyear_c();
    oneTropicalYear = FSEphemerisPeriod(_tyear);
}


/*
Exceptions
   1)  The error SPICE(DIVIDEBYZERO) signals from a routine
       in the call tree if any two elements of the array
       xvals are equal.

   2)  The error SPICE(INVALIDSIZE) signals from a routine
       in the call tree if n is less than 1.

   3)  This routine does not attempt to ward off or diagnose
       arithmetic overflows.
*/
void USpice::lgrind(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const TArray<double>& xvals,
    const TArray<double>& yvals,
    double x,
    double& p,
    double& dp
)
{
    // Inputs
    SpiceInt		_n = xvals.Num();
    SpiceDouble* _xvals = (SpiceDouble*)StackAlloc(xvals.Num() * sizeof(SpiceDouble));
    SpiceDouble* _yvals = (SpiceDouble*)StackAlloc(xvals.Num() * sizeof(SpiceDouble));
    SpiceDouble* _work = (SpiceDouble*)StackAlloc(2 * xvals.Num() * sizeof(SpiceDouble));
    SpiceDouble		_x = x;
    for (int i = 0; i < xvals.Num(); i++) _xvals[i] = xvals[i];
    for (int i = 0; i < yvals.Num(); i++) _yvals[i] = yvals[i];
    // Outputs
    SpiceDouble _p = 0;
    SpiceDouble _dp = 0;

    // Invocation
    lgrind_c(_n, _xvals, _yvals, _work, _x, &_p, &_dp);

    // Return Values
    p = double(_p);
    dp = double(_dp);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1) If the input body name cannot be translated to an ID code,
      and if the name is not a string representation of an integer
      (for example, "399"), the error SPICE(NOTRANSLATION) is
      signaled.

   2) If no SPK (ephemeris) file has been loaded prior to calling
      this routine, or if the SPK data has insufficient coverage, an
      error will be diagnosed and signaled by a routine in the call
      tree of this routine.

   3) If a PCK file containing rotational elements for the central
      body has not been loaded prior to calling this routine, an
      error will be diagnosed and signaled by a routine called by a
      routine in the call tree of this routine.

   4) If the instantaneous angular velocity and spin axis of `body'
      are parallel, the error will be diagnosed and signaled by a
      routine in the call tree of this routine.

   5) The error SPICE(EMPTYSTRING) is signaled if the input
      string `body' does not contain at least one character, since the
      input string cannot be converted to a Fortran-style string in
      this case.

   6) The error SPICE(NULLPOINTER) is signaled if the input string
      pointer `body' is null.
*/
void USpice::lspcn(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& body,
    const FSEphemerisTime& et,
    ES_AberrationCorrection abcorr,
    FSAngle& lon
)
{
    // Inputs
    ConstSpiceChar* _body = TCHAR_TO_ANSI(*body);
    SpiceDouble		_et = et.AsDouble();
    ConstSpiceChar* _abcorr;
    switch (abcorr)
    {
    case ES_AberrationCorrection::LT:
        _abcorr = "LT";
        break;
    case ES_AberrationCorrection::LT_S:
        _abcorr = "LT+S";
        break;
    default:
        _abcorr = "NONE";
        break;
    }

    // Invocation
    SpiceDouble _lon = lspcn_c(_body, _et, _abcorr);

    // Return Value
    lon = FSAngle(_lon);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions
   Error free.
*/
void USpice::mequ(
    const FSRotationMatrix& m1,
    FSRotationMatrix& mout
)
{
    // Input
    SpiceDouble _m1[3][3];		m1.CopyTo(_m1);

    // Output
    SpiceDouble _mout[3][3];

    // Invocation
    mequ_c(_m1, _mout);

    // Return Value
    mout = FSRotationMatrix(_mout);
}

/*
Exceptions
   Error free.
*/

void USpice::mxv_distance(
    const FSRotationMatrix& m1,
    const FSDistanceVector& vin,
    FSDistanceVector& vout
)
{
    // Inputs
    SpiceDouble    _m1[3][3];	m1.CopyTo(_m1);
    SpiceDouble    _vin[3];		vin.CopyTo(_vin);

    // Outputs
    SpiceDouble    _vout[3];

    // Invocation
    mxv_c(_m1, _vin, _vout);

    // Return Value
    vout = FSDistanceVector(_vout);
}

void USpice::mxv_velocity(
    const FSRotationMatrix& m1,
    const FSVelocityVector& vin,
    FSVelocityVector& vout
)
{
    // Inputs
    SpiceDouble    _m1[3][3];	m1.CopyTo(_m1);
    SpiceDouble    _vin[3];		vin.CopyTo(_vin);

    // Outputs
    SpiceDouble    _vout[3];

    // Invocation
    mxv_c(_m1, _vin, _vout);

    // Return Value
    vout = FSVelocityVector(_vout);
}

void USpice::mxv(
    const FSRotationMatrix& m1,
    const FSDimensionlessVector& vin,
    FSDimensionlessVector& vout
)
{
    // Inputs
    SpiceDouble    _m1[3][3];	m1.CopyTo(_m1);
    SpiceDouble    _vin[3];		vin.CopyTo(_vin);

    // Outputs
    SpiceDouble    _vout[3];

    // Invocation
    mxv_c(_m1, _vin, _vout);

    // Return Value
    vout = FSDimensionlessVector(_vout);
}

/*
Exceptions

   1) If the input name is not recognized, frcode will be
      returned with a value of 0.

   2) If the input string pointer is null, the error
      SPICE(NULLPOINTER) will be signaled.

   3) If the input string has length zero, the error
      SPICE(EMPTYSTRING) will be signaled.
*/
void USpice::namfrm(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& frname,
    int& frcode
)
{
    // Input
    ConstSpiceChar* _frname = TCHAR_TO_ANSI(*frname);
    // Output
    SpiceInt       _frcode = 0;

    // Invocation
    namfrm_c(_frname, &_frcode);

    // Return Value
    frcode = int(_frcode);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  Invalid ellipses will be diagnosed by routines called by
       this routine.

   2)  Ellipses having one or both semi-axis lengths equal to zero
       are turned away at the door; the error SPICE(DEGENERATECASE)
       is signalled.

   3)  If the geometric ellipse represented by ellips does not
       have a unique point nearest to the input point, any point
       at which the minimum distance is attained may be returned
       in pnear.
*/
void USpice::npelpt(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSDistanceVector& point,
    const FSEllipse& ellips,
    FSDistanceVector& pnear,
    FSDistance& dist
)
{
    // Input
    SpiceDouble			_point[3];	point.CopyTo(_point);
    SpiceEllipse		_ellips;    CopyTo(ellips, _ellips);

    // Output
    SpiceDouble			_pnear[3];	ZeroOut(_pnear);
    SpiceDouble			_dist = 0;

    // Invocation
    npelpt_c(_point, &_ellips, _pnear, &_dist);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions
   1) If any of the inputs a, b or c are non-positive the error
      "SPICE(BADAXISLENGTH)" will be signaled.

   2) If the ratio of the longest to the shortest ellipsoid axis
      is large enough so that arithmetic expressions involving its
      squared value may overflow, the error SPICE(BADAXISLENGTH)
      will be signaled.

   3) If any of the expressions

         a * abs( positn[0] ) / (m*m)
         b * abs( positn[1] ) / (m*m)
         c * abs( positn[1] ) / (m*m)

      where m is the minimum of { a, b, c }, is large enough so
      that arithmetic expressions involving these sub-expressions
      may overflow, the error SPICE(INPUTSTOOLARGE) is signaled.

   4) If the axes of the ellipsoid have radically different
      magnitudes, for example if the ratios of the axis lengths vary
      by 10 orders of magnitude, the results may have poor
      precision. No error checks are done to identify this problem.

   5) If the axes of the ellipsoid and the input point `positn' have
      radically different magnitudes, for example if the ratio of
      the magnitude of `positn' to the length of the shortest axis is
      1.e25, the results may have poor precision. No error checks
      are done to identify this problem.
*/
void USpice::nearpt(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSDistanceVector& positn,
    const FSDistance& a,
    const FSDistance& b,
    const FSDistance& c,
    FSDistanceVector& npoint,
    FSDistance& alt
)
{
    // Inputs
    SpiceDouble _positn[3]; positn.CopyTo(_positn);
    SpiceDouble _a = a.AsDouble();
    SpiceDouble _b = b.AsDouble();
    SpiceDouble _c = c.AsDouble();
    // Outputs
    SpiceDouble _npoint[3]; ZeroOut(_npoint);
    SpiceDouble _alt = 0;

    // Invocation
    nearpt_c(_positn, _a, _b, _c, _npoint, &_alt);

    // Return Values
    npoint = FSDistanceVector(_npoint);
    alt = FSDistance(_alt);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   If this routine detects an error, the output arguments nearp and
   dist are not modified.

   1)  If the length of any semi-axis of the ellipsoid is
       non-positive, the error SPICE(INVALIDAXISLENGTH) is signaled.

   2)  If the line's direction vector is the zero vector, the error
       SPICE(ZEROVECTOR) is signaled.

   3)  If the length of any semi-axis of the ellipsoid is zero after
       the semi-axis lengths are scaled by the reciprocal of the
       magnitude of the longest semi-axis and then squared, the error
       SPICE(DEGENERATECASE) is signaled.

   4)  If the input ellipsoid is extremely flat or needle-shaped
       and has its shortest axis close to perpendicular to the input
       line, numerical problems could cause this routine's algorithm
       to fail, in which case the error SPICE(DEGENERATECASE) is
       signaled.
*/
void USpice::npedln(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSDistance& a,
    const FSDistance& b,
    const FSDistance& c,
    const FSDistanceVector& linept,
    const FSDimensionlessVector& linedr,
    FSDistanceVector& pnear,
    FSDistance& dist
)
{
    // Inputs
    SpiceDouble       _a;       _a = a.AsDouble();
    SpiceDouble       _b;       _b = b.AsDouble();
    SpiceDouble       _c;       _c = c.AsDouble();
    SpiceDouble  _linept[3];    linept.CopyTo(_linept);
    SpiceDouble  _linedr[3];    linedr.CopyTo(_linedr);
    // Outputs
    SpiceDouble  _pnear[3];     ZeroOut(pnear);
    SpiceDouble _dist = 0;

    // Invocation
    npedln_c(_a, _b, _c, _linept, _linedr, _pnear, &_dist);

    // Return Values
    pnear = FSDistanceVector(_pnear);
    dist = FSDistance(_dist);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  If the line direction vector lindir is the zero vector, the
       error SPICE(ZEROVECTOR) is signaled
*/
void USpice::nplnpt(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSDistanceVector& linpt,
    const FSDimensionlessVector& lindir,
    const FSDistanceVector& point,
    FSDistanceVector& pnear,
    double& dist
)
{
    // Inputs
    SpiceDouble _linpt[3];  linpt.CopyTo(_linpt);
    SpiceDouble _lindir[3]; lindir.CopyTo(_lindir);
    SpiceDouble _point[3];  point.CopyTo(_point);
    // Outputs
    SpiceDouble _pnear[3];  ZeroOut(_pnear);
    SpiceDouble _dist = 0;

    // Invocation
    nplnpt_c(_linpt, _lindir, _point, _pnear, &_dist);

    // Return Values
    pnear = FSDistanceVector(_pnear);
    dist = double(_dist);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  If the input vector normal is the zero vector, the error
       SPICE(ZEROVECTOR) is signalled.
*/
void USpice::nvc2pl(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSDimensionlessVector& normal,
    const FSDistance& constant,
    FSPlane& plane
)
{
    // Inputs
    SpiceDouble	_normal[3]; normal.CopyTo(_normal);
    SpiceDouble	_constant = constant.AsDouble();
    // Output
    SpicePlane	_plane;     ZeroOut(_plane);

    // Invocation - let nvc2pl do whatever it wants, if anything
    nvc2pl_c(_normal, _constant, &_plane);

    // Return Value - copy the plane back out back out
    CopyFrom(_plane, plane);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  If the input vector normal is the zero vector, the error
       SPICE(ZEROVECTOR) is signaled.
*/
void USpice::nvp2pl(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSDimensionlessVector& normal,
    const FSDistanceVector& point,
    FSPlane& plane
)
{
    // Inputs
    SpiceDouble    _normal[3];	normal.CopyTo(_normal);
    SpiceDouble    _point[3];	point.CopyTo(_normal);

    // Outputs
    SpicePlane _plane;			ZeroOut(_plane);

    // Invocation - let nvp2pl do whatever it wants, if anything, then copy it back out
    nvp2pl_c(_normal, _point, &_plane);

    // Return Value - copy the plane back out back out
    CopyFrom(_plane, plane);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


void USpice::oscelt(
    const FSStateVector& state,
    const FSEphemerisTime& et,
    const FSMassConstant& gm,
    FSConicElements& elts
)
{
    SpiceDouble _state[6];
    SpiceDouble      _elts[8];

    state.CopyTo(_state);
    oscelt_c(_state, et.seconds, gm.GM, _elts);

    elts = FSConicElements(_elts);

    UnexpectedErrorCheck();
}

void USpice::oscltx(
    const FSStateVector& state,
    const FSEphemerisTime& et,
    const FSMassConstant& gm,
    FSConicElements& elts,
    FSAngle& nu,
    FSDistance& a,
    FSEphemerisPeriod& tau
)
{
    SpiceDouble _state[6];
    SpiceDouble _elts[SPICE_OSCLTX_NELTS];

    state.CopyTo(_state);
    oscltx_c(_state, et.seconds, gm.GM, _elts);

    elts = FSConicElements(_elts);
    nu = FSAngle(_elts[8]);
    a = FSDistance(_elts[9]);
    tau = FSEphemerisPeriod(_elts[10]);

    UnexpectedErrorCheck();
}

void USpice::pckfrm(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& pckRelativePath,
    TArray<int>& ids
)
{
    const int MAXOBJ = 1000;

    SPICEINT_CELL(idscell, MAXOBJ);

    // Inputs
    auto gameDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
    ConstSpiceChar* _pck = TCHAR_TO_ANSI(*(gameDir + pckRelativePath));

    // Outputs
    SpiceCell* _ids = &idscell;

    // Invocation
    spkobj_c(_pck, _ids);

    ids = TArray<int>();
    int count = card_c(_ids);
    for (int i = 0; i < count; i++)
    {
        SpiceInt id = SPICE_CELL_ELEM_I(_ids, i);
        ids.Add(int(id));
    }

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


void checkcov(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& pckFileRelativePath,
    int idcode,
    const TArray<FSWindowSegment>& merge_to,
    TArray<FSWindowSegment>& coverage,
    void (*covfunction)(ConstSpiceChar* pck, SpiceInt idcode, SpiceCell* cover)
)
{
    auto gameDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
    auto path = FPaths::Combine(gameDir, pckFileRelativePath);

    const int smallCellSize = 100;
    const int largeCellSize = 10000;

    // Inputs
    ConstSpiceChar* _pck = TCHAR_TO_ANSI(*path);
    SpiceInt        _idcode = idcode;
    SpiceCell* _cover;

    SpiceBoolean haveData = false;
    SPICEDOUBLE_CELL(_cover_small, smallCellSize);
    _cover = &_cover_small;

    if (merge_to.Num() <= smallCellSize / 2)
    {
        // Outputs
        if (merge_to.Num() > 0)
        {
            for (int i = 0; i < merge_to.Num(); ++i)
            {
                appndd_c(merge_to[i].start, _cover);
                appndd_c(merge_to[i].stop, _cover);
            }
        }

        // Invocation
        scard_c(0, _cover);
        pckcov_c(_pck, _idcode, _cover);

        haveData = !failed_c();
    }

    if (!haveData)
    {
        if (merge_to.Num() <= largeCellSize / 2)
        {
            reset_c();

            SPICEDOUBLE_CELL(_cover_large, largeCellSize);
            _cover = &_cover_large;

            if (merge_to.Num() > 0)
            {
                for (int i = 0; i < merge_to.Num(); ++i)
                {
                    appndd_c(merge_to[i].start, _cover);
                    appndd_c(merge_to[i].stop, _cover);
                }
            }

            // Re-Invocation
            scard_c(0, _cover);
            pckcov_c(_pck, _idcode, _cover);

            haveData = !failed_c();
        }
        else
        {
            setmsg_c("[in] Window Segment count = #; maximum allowed value is #");
            errdp_c("#", merge_to.Num());
            errdp_c("#", largeCellSize / 2);
            sigerr_c("SPICE(VALUEOUTOFRANGE)");
        }
    }

    // Return Values
    coverage = TArray<FSWindowSegment>();
    if (haveData)
    {
        int niv = wncard_c(_cover);
        for (int i = 0; i < niv; ++i)
        {
            SpiceDouble _start, _stop;
            wnfetd_c(_cover, i, &_start, &_stop);
            coverage.Add(FSWindowSegment(_start, _stop));
        }
    }

    // Error Handling
   USpice::ErrorCheck(ResultCode, ErrorMessage);
}


/*
Exceptions

   1)  If the input file has transfer format, the error
       SPICE(INVALIDFORMAT) is signaled.

   2)  If the input file is not a transfer file but has architecture
       other than DAF, the error SPICE(BADARCHTYPE) is signaled.

   3)  If the input file is a binary DAF file of type other than
       PCK, the error SPICE(BADFILETYPE) is signaled.

   4)  If the PCK file cannot be opened or read, the error will
       be diagnosed by routines called by this routine. The output
       window will not be modified.

   5)  If the size of the output window argument COVER is
       insufficient to contain the actual number of intervals in the
       coverage window for IDCODE, the error will be diagnosed by
       routines called by this routine.

   6)  The error SPICE(EMPTYSTRING) is signaled if the input
       string `pck' does not contain at least one character, since the
       input string cannot be converted to a Fortran-style string in
       this case.

   7)  The error SPICE(NULLPOINTER) is signaled if the input string
       pointer `pck' is null.
*/
void USpice::pckcov(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& pckFileRelativePath,
    int idcode,
    const TArray<FSWindowSegment>& merge_to,
    TArray<FSWindowSegment>& coverage
)
{
    ::checkcov(ResultCode, ErrorMessage, pckFileRelativePath, idcode, merge_to, coverage, pckcov_c);
}


/*
Exceptions

   1) If name is already present in the kernel pool and there
      is sufficient room to hold all values supplied in values,
      the old values associated with name will be overwritten.

   2) If there is not sufficient room to insert a new variable
      into the kernel pool and name is not already present in
      the kernel pool, the error SPICE(KERNELPOOLFULL) is
      signaled by a routine in the call tree to this routine.

   3) If there is not sufficient room to insert the values associated
      with name, the error SPICE(NOMOREROOM) will be signaled.

   4) If either input string pointer is null, the error
      SPICE(NULLPOINTER) will be signaled.

   5) If the input string name has length zero, the error
      SPICE(EMPTYSTRING) will be signaled.

   6) If the input cvals string length is less than 2, the error
      SPICE(STRINGTOOSHORT) will be signaled.

   7) The error 'SPICE(BADVARNAME)' signals if the kernel pool
      variable name length exceeds 32.
*/
void USpice::pcpool_list(
    ES_ResultCode&          ResultCode,
    FString&                ErrorMessage,
    const FString&          name,
    const TArray<FString>&  cvals
)
{
    int32 maxLen = 1;
    for (auto It = cvals.CreateConstIterator(); It; ++It)
    {
        int thisLen = (*It).Len()+1;
        maxLen = FMath::Max(thisLen, maxLen);
    }

    int count = cvals.Num();
    size_t string_size = maxLen * sizeof(SpiceChar);
    size_t buffer_size = count * string_size;
    void* buffer = StackAlloc(buffer_size);
    memset(buffer, 0, buffer_size);

    for (int i = 0; i < count; ++i)
    {
        const FString& fstringValue = cvals[i];
        const char* src = TCHAR_TO_ANSI(*fstringValue);
        char* dest = (char*)buffer + i * string_size;
        strcpy_s(dest, buffer_size, src);
    }

    // Inputs
    ConstSpiceChar* _name = TCHAR_TO_ANSI(*name);
    SpiceInt        _n = (SpiceInt)count;
    SpiceInt        _lenvals = (SpiceInt)maxLen;
    const void*     _cvals = buffer;

    pcpool_c(_name, _n, _lenvals, _cvals);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

void USpice::pcpool(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& name,
    const FString& cval
)
{
    // Inputs
    ConstSpiceChar* _name = TCHAR_TO_ANSI(*name);
    SpiceInt        _n = 1;
    SpiceInt        _lenvals = (SpiceInt)(cval.Len()+1);
    const void* _cvals = TCHAR_TO_ANSI(*cval);

    pcpool_c(_name, _n, _lenvals, _cvals);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


/*
Exceptions

   1) If name is already present in the kernel pool and there
      is sufficient room to hold all values supplied in dvals,
      the old values associated with name will be overwritten.

   2) If there is not sufficient room to insert a new variable
      into the kernel pool and name is not already present in
      the kernel pool, the error SPICE(KERNELPOOLFULL) is
      signaled by a routine in the call tree to this routine.

   3) If there is not sufficient room to insert the values associated
      with name, the error SPICE(NOMOREROOM) will be signaled.

   4) If the input string pointer name is null, the error
      SPICE(NULLPOINTER) will be signaled.

   5) If the input string name has length zero, the error
      SPICE(EMPTYSTRING) will be signaled.

   6) The error 'SPICE(BADVARNAME)' signals if the kernel pool
      variable name length exceeds 32.
*/
void USpice::pdpool_list(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& name,
    const TArray<double>& dvals
)
{
    if (sizeof(double) == sizeof(ConstSpiceDouble))
    {
        // Inputs
        ConstSpiceChar*     _name = TCHAR_TO_ANSI(*name);
        SpiceInt            _n = dvals.Num();
        ConstSpiceDouble*   _dvals = dvals.GetData();

        // Invocation
        pdpool_c(_name, _n, _dvals);
    }
    else
    {
        // In the unlikely event GetData() cannot be used for some platform signal an error.
        // It is preferable to clearly call out the (unanticipated) situation for a future
        // fix than insert untestable memberwise-copy logic.
        setmsg_c("Size of double = #; Size of ConstSpiceDouble = #");
        errdp_c("#", sizeof(double));
        errdp_c("#", sizeof(ConstSpiceDouble));
        sigerr_c("SPICE(NOTSUPPORTED)");
    }

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

void USpice::pdpool(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& name,
    double dval
)
{
    // Inputs
    ConstSpiceChar* _name = TCHAR_TO_ANSI(*name);
    SpiceInt            _n = 1;
    SpiceDouble _dval = (SpiceDouble)dval;

    // Invocation
    pdpool_c(_name, _n, &_dval);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


/*
Exceptions

   1) If the body name `body' cannot be mapped to a NAIF ID code,
      and if `body' is not a string representation of an integer,
      the error SPICE(IDCODENOTFOUND) will be signaled.

   2) If the kernel variable

         BODY<ID code>_PGR_POSITIVE_LON

      is present in the kernel pool but has a value other
      than one of

          'EAST'
          'WEST'

      the error SPICE(INVALIDOPTION) will be signaled.  Case
      and blanks are ignored when these values are interpreted.

   3) If polynomial coefficients for the prime meridian of `body'
      are not available in the kernel pool, and if the kernel
      variable BODY<ID code>_PGR_POSITIVE_LON is not present in
      the kernel pool, the error SPICE(MISSINGDATA) will be signaled.

   4) If the equatorial radius is non-positive, the error
      SPICE(VALUEOUTOFRANGE) is signaled.

   5) If the flattening coefficient is greater than or equal to one,
      the error SPICE(VALUEOUTOFRANGE) is signaled.

   6) The error SPICE(EMPTYSTRING) is signaled if the input
      string `body' does not contain at least one character, since the
      input string cannot be converted to a Fortran-style string in
      this case.

   7) The error SPICE(NULLPOINTER) is signaled if the input string
      pointer `body' is null.
*/
void USpice::pgrrec(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSLonLat&       lonlat,
    const FSDistance& alt,
    const FSDistance& re,
    FSDistanceVector& rectan,
    const FString& body,
    double f
)
{
    // Inputs
    ConstSpiceChar* _body = TCHAR_TO_ANSI(*body);
    SpiceDouble     _lon = lonlat.longitude.AsDouble();
    SpiceDouble     _lat = lonlat.latitude.AsDouble();
    SpiceDouble     _alt = alt.AsDouble();
    SpiceDouble     _re  = re.AsDouble();
    SpiceDouble     _f   = (SpiceDouble)f;
    
    // Outputs
    SpiceDouble     _rectan[3]; ZeroOut(_rectan);

    // Invocation
    pgrrec_c(_body, _lon, _lat, _alt, _re, _f, _rectan);

    // Copy output
    rectan = FSDistanceVector(_rectan);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

void USpice::pi(double& pi)
{
    pi = pi_c();
}

void USpice::pi_angle(FSAngle& _pi)
{
    _pi = FSAngle(pi_c());
}


/*
Exceptions

   1) If name is already present in the kernel pool and there
      is sufficient room to hold all values supplied in values,
      the old values associated with name will be overwritten.

   2) If there is not sufficient room to insert a new variable
      into the kernel pool and name is not already present in
      the kernel pool, the error SPICE(KERNELPOOLFULL) is
      signaled by a routine in the call tree to this routine.

   3) If there is not sufficient room to insert the values associated
      with name, the error SPICE(NOMOREROOM) will be signaled.

   4) If the input string pointer name is null, the error
      SPICE(NULLPOINTER) will be signaled.

   5) If the input string name has length zero, the error
      SPICE(EMPTYSTRING) will be signaled.

   6) The error 'SPICE(BADVARNAME)' signals if the kernel pool
      variable name length exceeds 32.
*/
void USpice::pipool_list(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& name,
    const TArray<int>& ivals
)
{
    if (sizeof(int) == sizeof(SpiceInt))
    {
        // Inputs
        ConstSpiceChar* _name = TCHAR_TO_ANSI(*name);
        SpiceInt          _n = ivals.Num();
        ConstSpiceInt* _ivals = (SpiceInt*)ivals.GetData();

        // Invocation
        pipool_c(_name, _n, _ivals);
    }
    else
    {
        // In the unlikely event GetData() cannot be used for some platform signal an error.
        // It is preferable to clearly call out the (unanticipated) situation for a future
        // fix than insert untestable memberwise-copy logic.
        setmsg_c("Size of int = #; Size of SpiceInt = #");
        errdp_c("#", sizeof(int));
        errdp_c("#", sizeof(SpiceInt));
        sigerr_c("SPICE(NOTSUPPORTED)");
    }

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


void USpice::pipool(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& name,
    int ival
)
{
    // Inputs
    ConstSpiceChar* _name = TCHAR_TO_ANSI(*name);
    SpiceInt        _n = 1;
    SpiceInt        _ival = (SpiceInt)ival;

    // Invocation
    pipool_c(_name, _n, &_ival);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  If the input plane is invalid, the error will be diagnosed
       by routines called by this routine.

   2)  The input ellipse may be degenerate--its semi-axes may be
       linearly dependent.  Such ellipses are allowed as inputs.

   3)  The ellipse resulting from orthogonally projecting the input
       ellipse onto a plane may be degenerate, even if the input
       ellipse is not.
*/
void USpice::pjelpl(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSEllipse& elin,
    const FSPlane& plane,
    FSEllipse& elout
)
{
    // Inputs
    SpiceEllipse _elin;     CopyTo(elin, _elin);
    SpicePlane _plane;      CopyTo(plane, _plane);
    // Outpus
    SpiceEllipse _elout;    ZeroOut(_elout);

    // Invocation
    pjelpl_c(&_elin, &_plane, &_elout);

    // Return Value
    CopyFrom(_elout, elout);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   Error free.

   1)  The input plane MUST have been created by one of the CSPICE
       routines

          nvc2pl_c ( Normal vector and constant to plane )
          nvp2pl_c ( Normal vector and point to plane    )
          psv2pl_c ( Point and spanning vectors to plane )

       Otherwise, the results of this routine are unpredictable.
*/
void USpice::pl2nvc(
    const FSPlane& plane,
    FSDimensionlessVector& normal,
    FSDistance& constant
)
{
    // No need to call pl2nvc, because it will eventually be called when it's transformed back into
    // spice types.
    normal = plane.normal;
    constant = plane.constant;
}

/*
Exceptions

   1)  If span1 and span2 are linearly dependent, then the vectors
       point, span1, and span2 do not define a plane.  The error
       SPICE(DEGENERATECASE) is signaled.
*/
void USpice::pl2nvp(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSPlane& plane,
    FSDistanceVector& normal,
    FSDistanceVector& point
)
{
    // Input
    SpicePlane _plane;      CopyTo(plane, _plane);

    // Outputs
    SpiceDouble	_normal[3];	ZeroOut(_normal);
    SpiceDouble	_point[3];	ZeroOut(_point);

    // Invocation
    pl2nvp_c(&_plane, _normal, _point);

    // Return Values
    normal = FSDistanceVector(_normal);
    point = FSDistanceVector(_point);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


/*
Exceptions

   Error free.

   1)  The input plane MUST have been created by one of the CSPICE
       routines

          nvc2pl_c ( Normal vector and constant to plane )
          nvp2pl_c ( Normal vector and point to plane    )
          psv2pl_c ( Point and spanning vectors to plane )

       Otherwise, the results of this routine are unpredictable.
*/
void USpice::pl2psv(
    const FSPlane& plane,
    FSDistanceVector& point,
    FSDistanceVector& span1,
    FSDistanceVector& span2
)
{
    // Input
    SpicePlane  _plane;     CopyTo(plane, _plane);
    // Output
    SpiceDouble _point[3];  ZeroOut(_point);
    SpiceDouble _span1[3];  ZeroOut(_span1);
    SpiceDouble _span2[3];  ZeroOut(_span2);

    // Invocation
    pl2psv_c(&_plane, _point, _span1, _span2);

    // Return Values
    point = FSDistanceVector(_point);
    span1 = FSDistanceVector(_span1);
    span2 = FSDistanceVector(_span2);
}

/*
Exceptions
   1) If gm is not positive, the error SPICE(NONPOSITIVEMASS) will
      be signalled.

   2) If the position of the initial state is the zero vector, the
      error SPICE(ZEROPOSITION) will be signalled.

   3) If the velocity of the initial state is the zero vector, the
      error SPICE(ZEROVELOCITY) will be signalled.

   4) If the cross product of the position and velocity of pvinit
      has squared length of zero, the error SPICE(NONCONICMOTION)
      will be signalled.

   5) The value of dt must be "reasonable".  In other words, dt
      should be less than 10**20 seconds for realistic solar system
      orbits specified in the MKS system.  (The actual bounds
      on dt are much greater but require substantial computation.)
      The "reasonableness" of dt is checked at run-time.  If dt is
      so large that there is a danger of floating point overflow
      during computation, the error SPICE(DTOUTOFRANGE) is
      signalled and a message is generated describing the problem.
*/
void USpice::prop2b(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSMassConstant& gm,
    const FSStateVector& pvinit,
    const FSEphemerisPeriod& dt,
    FSStateVector& pvprop
)
{
    // Inputs
    SpiceDouble	_gm = gm.AsDouble();
    SpiceDouble	_pvinit[6]; pvinit.CopyTo(_pvinit);
    SpiceDouble	_dt = dt.AsDouble();
    // Output
    SpiceDouble	_pvprop[6];	ZeroOut(_pvprop);

    // Invocation
    prop2b_c(_gm, _pvinit, _dt, _pvprop);

    // Return Value
    pvprop = FSStateVector(_pvprop);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  If span1 and span2 are linearly dependent, then the vectors
       point, span1, and span2 do not define a plane.  The error
       SPICE(DEGENERATECASE) is signaled.
*/
void USpice::psv2pl(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSDistanceVector& point,
    const FSDistanceVector& span1,
    const FSDistanceVector& span2,
    FSPlane& plane
)
{
    // Inputs
    SpiceDouble	_point[3];	point.CopyTo(_point);
    SpiceDouble	_span1[3];	span1.CopyTo(_span1);
    SpiceDouble	_span2[3];	span2.CopyTo(_span2);
    // Outputs
    SpicePlane	_plane;		ZeroOut(_plane);

    // Invocation
    psv2pl_c(_point, _span1, _span2, &_plane);

    // Return Value - copy the plane back out back out
    CopyFrom(_plane, plane);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

void USpice::pxform(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& from,
    const FSEphemerisTime& et,
    FSRotationMatrix& rotate,
    const FString& to
)
{
    SpiceDouble _rotate[3][3];
    pxform_c(TCHAR_TO_ANSI(*from), TCHAR_TO_ANSI(*to), et.seconds, _rotate);
    rotate = FSRotationMatrix(_rotate);

    ErrorCheck(ResultCode, ErrorMessage);
}

void USpice::pxfrm2(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& from,
    const FSEphemerisTime& etfrom,
    const FSEphemerisTime& etto,
    FSRotationMatrix& rotate,
    const FString& to
)
{
    SpiceDouble _rotate[3][3];
    pxfrm2_c(TCHAR_TO_ANSI(*from), TCHAR_TO_ANSI(*to), etfrom.seconds, etto.seconds, _rotate);
    rotate = FSRotationMatrix(_rotate);

    ErrorCheck(ResultCode, ErrorMessage);
}

void USpice::radrec(
    const FSDistance& range,
    const FSAngle& ra,
    const FSAngle& dec,
    FSDistanceVector& rectan
)
{
    SpiceDouble _rectan[3];
    radrec_c(range.km, ra.radians(), dec.radians(), _rectan);
    rectan = FSDistanceVector(_rectan);

    UnexpectedErrorCheck();
}

/*
Exceptions

   Error free.

   1) No checks are performed on ROT to ensure that it is indeed
      a rotation matrix.
*/
void USpice::rav2xf(
    const FSRotationMatrix& rot,
    const FSAngularVelocity& av,
    FSEulerAngularTransform& xform
)
{
    // Inputs
    SpiceDouble    _rot[3][3];          rot.CopyTo(_rot);
    SpiceDouble    _av[3];              av.CopyTo(_av);
    // Outputs
    SpiceDouble         _xform[6][6];   xform.CopyTo(_xform);

    // Invocation
    rav2xf_c(_rot, _av, _xform);

    // Return Value
    xform = FSEulerAngularTransform(_xform);
}

/*
Exceptions

   1) If the input matrix is not a rotation matrix (a fairly
      loose tolerance is used to check this) a routine in the
      call tree of this routine will signal an error indicating
      the problem.

   2) If the input matrix is the identity matrix, this routine
      returns an angle of 0.0, and an axis of ( 0.0, 0.0, 1.0 ).
*/
void USpice::raxisa(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSRotationMatrix& matrix,
    FSDimensionlessVector& axis,
    FSAngle& angle
)
{
    // Inputs
    SpiceDouble _matrix[3][3];  matrix.CopyTo(_matrix);
    // Outputs
    SpiceDouble _axis[3];       ZeroOut(_axis);
    SpiceDouble _angle = 0;

    // Invocation
    raxisa_c(_matrix, _axis, &_angle);

    // Return Values
    axis = FSDimensionlessVector(_axis);
    angle = FSAngle(_angle);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

void USpice::recgeo(
    const FSDistanceVector& rectan,
    const FSDistance& re,
    FSLonLat& lonlat,
    FSDistance& alt,
    double f
    )
{
    SpiceDouble _rectan[3];
    rectan.CopyTo(_rectan);

    SpiceDouble _lon, _lat, _alt;

    recgeo_c(_rectan, re.km, f, &_lon, &_lat, &_alt);

    lonlat = FSLonLat(_lon, _lat);
    alt = FSDistance(_alt);

    UnexpectedErrorCheck();
}

void USpice::reclat(
    const FSDistanceVector& rectan,
    FSDistance& radius,
    FSLonLat& lonlat
)
{
    SpiceDouble _rectan[3];
    rectan.CopyTo(_rectan);

    SpiceDouble _radius, _longitude, _latitude;

    reclat_c(_rectan, &_radius, &_longitude, &_latitude);

    radius = FSDistance(_radius);
    lonlat = FSLonLat(_longitude, _latitude);

    UnexpectedErrorCheck();
}


/*
Exceptions

   1) If the body name `body' cannot be mapped to a NAIF ID code,
      and if `body' is not a string representation of an integer,
      the error SPICE(IDCODENOTFOUND) will be signaled.

   2) If the kernel variable

         BODY<ID code>_PGR_POSITIVE_LON

      is present in the kernel pool but has a value other than one
      of

          'EAST'
          'WEST'

      the error SPICE(INVALIDOPTION) will be signaled.  Case
      and blanks are ignored when these values are interpreted.

   3) If polynomial coefficients for the prime meridian of `body'
      are not available in the kernel pool, and if the kernel
      variable BODY<ID code>_PGR_POSITIVE_LON is not present in
      the kernel pool, the error SPICE(MISSINGDATA) will be signaled.

   4) If the equatorial radius is non-positive, the error
      SPICE(VALUEOUTOFRANGE) is signaled.

   5) If the flattening coefficient is greater than or equal to one,
      the error SPICE(VALUEOUTOFRANGE) is signaled.

   6) For points inside the reference ellipsoid, the nearest point
      on the ellipsoid to `rectan' may not be unique, so latitude may
      not be well-defined.

   7) The error SPICE(EMPTYSTRING) is signaled if the input
      string `body' does not contain at least one character, since the
      input string cannot be converted to a Fortran-style string in
      this case.

   8) The error SPICE(NULLPOINTER) is signaled if the input string
      pointer `body' is null.
*/

void USpice::recpgr(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSDistanceVector& rectan,
    const FSDistance&       re,
    FSLonLat&               lonlat,
    FSDistance&             alt,
    const FString&          body,
    double                  f
)
{
    // Inputs
    ConstSpiceChar*  _body          = TCHAR_TO_ANSI(*body);;
    SpiceDouble      _rectan[3];    rectan.CopyTo(_rectan);
    SpiceDouble     _re             = re.AsDouble();
    SpiceDouble     _f              = (SpiceDouble)f;

    // Outputs
    SpiceDouble _lon = 0.;
    SpiceDouble _lat = 0.;
    SpiceDouble _alt = 0.;

    // Invocation
    recpgr_c(_body, _rectan, _re, _f, &_lon, &_lat, &_alt);

    // Copy outputs
    lonlat = FSLonLat(_lon, _lat);
    alt = FSDistance(_alt);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

void USpice::recrad(
    const FSDistanceVector& rectan,
    FSDistance& range,
    FSAngle& ra,
    FSAngle& dec
)
{
    SpiceDouble _rectan[3];
    rectan.CopyTo(_rectan);

    SpiceDouble _range, _ra, _dec;

    recrad_c(_rectan, &_range, &_ra, &_dec);

    range = FSDistance(_range);
    ra = FSAngle(_ra);
    dec = FSAngle(_dec);

    UnexpectedErrorCheck();
}


void USpice::recsph(
    const FSDistanceVector& rectan,
    FSDistance& r,
    FSAngle& colat,
    FSAngle& lon
)
{
    SpiceDouble _rectan[3];
    rectan.CopyTo(_rectan);

    SpiceDouble _r, _colat, _lon;

    recsph_c(_rectan, &_r, &_colat, &_lon);

    r = FSDistance(_r);
    colat = FSAngle(_colat);
    lon = FSAngle(_lon);

    UnexpectedErrorCheck();
}


/*
Error free.

   1) If the axis index is not in the range 1 to 3 it will be
      treated the same as that integer 1, 2, or 3 that is congruent
      to it mod 3
*/
void USpice::rotate(
    const FSAngle& angle,
    ES_Axis             iaxis,
    FSRotationMatrix& mout
)
{
    // Inputs
    SpiceDouble _angle = angle.AsDouble();
    SpiceInt    _iaxis = (SpiceInt)iaxis;
    // Outputs
    SpiceDouble _mout[3][3];

    // Invocation
    rotate_c(_angle, _iaxis, _mout);

    // Return Value
    mout = FSRotationMatrix(_mout);
}

/*
Exceptions

   Error free.

   1) If the axis index is not in the range 1 to 3 it will be
      treated the same as that integer 1, 2, or 3 that is congruent
      to it mod 3.
*/

void USpice::rotmat(
    const FSRotationMatrix& m1,
    const FSAngle& angle,
    ES_Axis                 iaxis,
    FSRotationMatrix& mout
)
{
    // Inputs
    SpiceDouble _m1[3][3];  m1.CopyTo(_m1);
    SpiceDouble _angle;     _angle = angle.AsDouble();
    SpiceInt    _iaxis = (SpiceInt)iaxis;
    // Output
    SpiceDouble _mout[3][3];

    // Invocation
    rotmat_c(_m1, _angle, _iaxis, _mout);

    // Return value
    mout = FSRotationMatrix(_mout);
}

/*
Exceptions


   1) If the axis index is not in the range 1 to 3 it will be treated
      the same as that integer 1, 2, or 3 that is congruent to it mod
      3.
*/
void USpice::rotvec(
    const FSDistanceVector& v1,
    const FSAngle& angle,
    ES_Axis                 iaxis,
    FSDistanceVector& vout
)
{
    // Inputs
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    SpiceDouble _angle = angle.AsDouble();
    SpiceInt    _iaxis = (SpiceInt)iaxis;
    // Output
    SpiceDouble _vout[3];

    // Invocation
    rotvec_c(_v1, _angle, _iaxis, _vout);

    // Return Value
    vout = FSDistanceVector(_vout);
}

/*
Exceptions

   Error free.
*/
void USpice::rpd(double& value)
{
    SpiceDouble _value = rpd_c();
    value = double(_value);
}

/*
Exceptions

   1)   If the input coefficients a and b are both zero, the error
        SPICE(DEGENERATECASE) is signalled.  The output arguments
        are not modified.
*/
void USpice::rquad(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    double a,
    double b,
    double c,
    FSComplexScalar& root1,
    FSComplexScalar& root2
)
{
    // Inputs
    SpiceDouble  _a = a;
    SpiceDouble  _b = b;
    SpiceDouble  _c = c;
    // Outputs
    SpiceDouble  _root1[2]; ZeroOut(_root1);
    SpiceDouble  _root2[2]; ZeroOut(_root1);

    // Invocation
    rquad_c(_a, _b, _c, _root1, _root2);

    // Return Values
    root1 = FSComplexScalar(_root1);
    root2 = FSComplexScalar(_root2);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


/*
Exceptions

   1) If kernel variables required by this routine are unavailable,
      the error will be diagnosed by routines called by this routine.
      sclkch will be returned as a blank string in this case.

   2) If the number of partitions in the kernel file for spacecraft
      SC exceeds the parameter MXPART, the error
      SPICE(TOOMANYPARTS) is signaled.  sclkch will be returned
      as a blank string in this case.

   3) If the encoded value does not fall in the boundaries of the
      mission, the error SPICE(VALUEOUTOFRANGE) is signaled.
      sclkch will be returned as a blank string in this case.

   4) If the output string pointer is null, the error SPICE(NULLPOINTER)
      is signaled.

   5) If the output string has length less than two characters, it
      is too short to contain one character of output data plus a null
      terminator, so it cannot be passed to the underlying Fortran
      routine.  In this event, the error SPICE(STRINGTOOSHORT) is
      signaled.

   6) If the length of sclkch (indicated by lenout) is at least two
      characters but not large enough to contain the output clock
      string, the error SPICE(SCLKTRUNCATED) is signaled either by the
      underlying Fortran routine or by a routine called by that routine.
      On output sclkch will contain a portion of the truncated clock
      string.
*/
void USpice::scdecd(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int sc,
    double sclkdp,
    FString& sclkch
)
{
    // Buffers
    SpiceChar szBuffer[WINDOWS_MAX_PATH];  ZeroOut(szBuffer);

    // Inputs
    SpiceInt    _sc = sc;
    SpiceDouble _sclkdp = sclkdp;
    SpiceInt    _lenout = sizeof(szBuffer);
    // Outputs
    SpiceChar* _sclkch = szBuffer;

    // Invocation
    scdecd_c(_sc, _sclkdp, _lenout, _sclkch);

    // Return Values
    sclkch = FString(_sclkch);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  This routine assumes that that an SCLK kernel appropriate
       to the spacecraft clock identified by the input argument sc
       has been loaded.  If an SCLK kernel has not been loaded,
       does not contain all of the required data, or contains
       invalid data, error diagnoses will be performed by routines
       called by this routine.  The output argument sclkdp will not
       be modified.

   2)  When using SCLK kernels that map SCLK to a time system other
       than ET (also called barycentric dynamical time---`TDB'), it
       is necessary to have a leapseconds kernel loaded at the time
       this routine is called.  If a leapseconds kernel is required
       for conversion between SCLK and ET but is not loaded, the
       error will be diagnosed by routines called by this routine.
       The output argument sclkdp will not be modified.

       The time system that an SCLK kernel maps SCLK to is indicated
       by the variable SCLK_TIME_SYSTEM_nn in the kernel, where nn
       is the negative of the NAIF integer code for the spacecraft.
       The time system used in a kernel is TDB if and only if the
       variable is assigned the value 1.

   3)  If the clock type for the spacecraft clock identified by
       SC is not supported by this routine, the error
       SPICE(NOTSUPPORTED) is signalled.  The output argument sclkdp
       will not be modified.

   4)  If the input ET value is not representable as an encoded
       spacecraft clock value for the spacecraft clock identified by
       sc, the error will be diagnosed by routines called by this
       routine.  The output argument sclkdp will not be modified.
*/
void USpice::sce2c(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int sc,
    const FSEphemerisTime& et,
    double& sclkdp
)
{
    // Inputs
    SpiceInt    _sc = sc;
    SpiceDouble _et = et.AsDouble();
    // Outputs
    SpiceDouble _sclkdp = 0;

    // Invocation
    sce2c_c(_sc, _et, &_sclkdp);

    // Return Values
    sclkdp = double(_sclkdp);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  This routine assumes that an SCLK kernel appropriate to the
       spacecraft clock identified by the input argument SC has been
       loaded.  If an SCLK kernel has not been loaded, does not contain
       all of the required data, or contains invalid data, error
       diagnoses will be performed by routines in the call tree of this
       routine.  The output argument `sclkch' will not be modified.

   2)  When using an SCLK kernel that maps SCLK to a time system other
       than ET (also called barycentric dynamical time---"TDB"), it is
       necessary to have a leapseconds kernel loaded at the time this
       routine is called.  If a leapseconds kernel is required for
       conversion between SCLK and ET but is not loaded, the error will
       be diagnosed by routines called by this routine. The output
       argument `sclkch' will not be modified.

       The time system to which an SCLK kernel maps SCLK epochs is
       indicated by the variable SCLK_TIME_SYSTEM_nn in the kernel,
       where nn is the negative of the NAIF integer code for the
       spacecraft. The time system used in a kernel is TDB if and only
       if the variable is assigned the value 1.

   3)  If the input ET value is not representable in the spacecraft
       clock string format for the spacecraft clock identified by `sc',
       the error will be diagnosed by routines in the call tree of this
       routine.  The output argument `sclkch' will not be modified.

   4)  If the declared length of the output argument `sclkch' is too
       short to contain the output spacecraft clock string produced by
       this routine, the error will be diagnosed by routines in the
       call tree of this routine.  The output argument `sclkch' may
       contain a portion of the truncated string.
*/
void USpice::sce2s(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int sc,
    const FSEphemerisTime& et,
    FString& sclkch
)
{
    // Buffers
    SpiceChar szBuffer[WINDOWS_MAX_PATH];  ZeroOut(szBuffer);

    // Inputs
    SpiceInt    _sc = sc;
    SpiceDouble _et = et.AsDouble();
    SpiceInt    _lenout = sizeof(szBuffer);
    // Outputs
    SpiceChar* _sclkch = szBuffer;

    // Invocation
    sce2s_c(_sc, _et, _lenout, _sclkch);

    // Return Values
    sclkch = FString(_sclkch);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  This function assumes that that an SCLK kernel appropriate
       to the spacecraft clock identified by the input argument sc
       has been loaded.  If an SCLK kernel has not been loaded,
       does not contain all of the required data, or contains
       invalid data, error diagnoses will be performed by functions
       called by this function.  The output argument sclkdp will not
       be modified.

   2)  When using SCLK kernels that map SCLK to a time system other
       than ET (also called barycentric dynamical time---`TDB'), it
       is necessary to have a leapseconds kernel loaded at the time
       this function is called.  If a leapseconds kernel is required
       for conversion between SCLK and ET but is not loaded, the
       error will be diagnosed by functions called by this function.
       The output argument sclkdp will not be modified.

       The time system that an SCLK kernel maps SCLK to is indicated
       by the variable SCLK_TIME_SYSTEM_nn in the kernel, where nn
       is the negative of the NAIF integer code for the spacecraft.
       The time system used in a kernel is TDB if and only if the
       variable is assigned the value 1.


   3)  If the clock type for the spacecraft clock identified by
       `sc' is not supported by this function, the error
       SPICE(NOTSUPPORTED) is signaled.  The output argument `sclkdp'
       will not be modified.

   4)  If the input ET value is not representable as an encoded
       spacecraft clock value for the spacecraft clock identified by
       `sc', the error will be diagnosed by functions called by this
       function.  The output argument sclkdp will not be modified.
*/
void USpice::sce2t(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int sc,
    const FSEphemerisTime& et,
    double& clkdp
)
{
    // Inputs
    SpiceInt    _sc = sc;
    SpiceDouble _et = et.AsDouble();
    // Outputs
    SpiceDouble _sclkdp = 0;

    // Invocation
    sce2t_c(_sc, _et, &_sclkdp);

    // Return Values
    clkdp = double(_sclkdp);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1) If the number of partitions in the kernel file for spacecraft
      sc exceeds the parameter MXPART, the error
      SPICE(TOOMANYPARTS) is signalled.


   If a partition number is included in the SCLK string, the
   following exceptions may occur:

   2) If the partition number cannot be parsed as an integer, the
      error SPICE(BADPARTNUMBER) is signalled.

   3) If the partition number is not in the range of the number of
      partitions found in the kernel pool, the error
      SPICE(BADPARTNUMBER) is signalled.

   4) If the clock count does not fall within the boundaries of the
      specified partition, the error SPICE(NOTINPART) is signalled.

   If a partition number is not included in the SCLK string, the
   following exception may occur.

   5) If the clock count does not fall within the boundaries of any
      partition found in the kernel pool, the error SPICE(NOPARTITION)
      is signalled.


   The following error is signalled by a routine called by scencd_c.

   6)  If any of the extracted clock components cannot be parsed as
       integers, or the string has too many components, or the value
       of one of the components is less than the offset value, then
       the error SPICE(INVALIDSCLKSTRING) is signalled.
*/
void USpice::scencd(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int sc,
    const FString& sclkch,
    double& sclkdp
)
{
    // Inputs
    SpiceInt        _sc = sc;
    ConstSpiceChar* _sclkch = TCHAR_TO_ANSI(*sclkch);
    // Outputs
    SpiceDouble     _sclkdp = 0;

    // Invocation
    scencd_c(_sc, _sclkch, &_sclkdp);

    // Return Values
    sclkdp = double(_sclkdp);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1) If the data type for the spacecraft is not supported
      then the error SPICE(NOTSUPPORTED) is signaled.

   2) If the value for ticks is negative, the error is diagnosed
      by routines called by this routine.

   3) If the SCLK kernel file does not contain data for the
      spacecraft specified by sc, then the error is diagnosed
      by routines called by this routine.

   4) If the output string pointer is null, the error SPICE(NULLPOINTER)
      is signaled.

   5) If the output string has length less than two characters, it
      is too short to contain one character of output data plus a null
      terminator, so it cannot be passed to the underlying Fortran
      routine.  In this event, the error SPICE(STRINGTOOSHORT) is
      signaled.

   6) If the length of clkstr (indicated by lenout) is at least two
      characters but not large enough to contain the output clock
      string, the error is diagnosed by a routine called by this
      routine.
*/
void USpice::scfmt(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int sc,
    double ticks,
    FString& clkstr
)
{
    // Buffers
    SpiceChar szBuffer[WINDOWS_MAX_PATH];  ZeroOut(szBuffer);

    // Inputs
    SpiceInt    _sc = sc;
    SpiceDouble _ticks = ticks;
    SpiceInt    _lenout = sizeof(szBuffer);
    // Outputs
    SpiceChar* _clkstr = szBuffer;

    // Invocation
    scfmt_c(_sc, _ticks, _lenout, _clkstr);

    // Return Values
    clkstr = FString(_clkstr);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  If the kernel variables containing the spacecraft clock
       partition start and stop times have not been loaded in the
       kernel pool, the error will be diagnosed by routines called
       by this routine.

   2)  If the number of start and stop times are different then
       the error SPICE(NUMPARTSUNEQUAL) is signalled.
*/
void USpice::scpart(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int sc,
    TArray<double>& pstart,
    TArray<double>& pstop
)
{
    const int MXPART = 9999;
    // Inputs
    SpiceInt    _sc = sc;
    // Outputs
    SpiceInt    _nparts = 0;
    SpiceDouble _pstart[MXPART];    ZeroOut(_pstart);
    SpiceDouble _pstop[MXPART];     ZeroOut(_pstop);

    // Invocation
    scpart_c(_sc, &_nparts, _pstart, _pstop);

    // Return Values
    pstart = TArray<double>();
    pstop = TArray<double>();

    if (!failed_c())
    {
        for (int i = 0; i < _nparts; i++)
        {
            pstart.Add(double(_pstart[i]));
            pstop.Add(double(_pstop[i]));
        }
    }

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  This routine assumes that that an SCLK kernel appropriate
       to the spacecraft clock identified by the input argument SC
       has been loaded.  If an SCLK kernel has not been loaded,
       does not contain all of the required data, or contains
       invalid data, error diagnoses will be performed by routines
       called by this routine.  The output argument et will not
       be modified.

   2)  When using SCLK kernels that map SCLK to a time system other
       than ET (also called barycentric dynamical time---`TDB'), it
       is necessary to have a leapseconds kernel loaded at the time
       this routine is called.  If a leapseconds kernel is required
       for conversion between SCLK and ET but is not loaded, the
       error will be diagnosed by routines called by this routine.
       The output argument et will not be modified.

       The time system that an SCLK kernel maps SCLK to is indicated
       by the variable SCLK_TIME_SYSTEM_nn in the kernel, where nn
       is the negative of the NAIF integer code for the spacecraft.
       The time system used in a kernel is TDB if and only if the
       variable is assigned the value 1.


   3)  Invalid values of sclkch will be diagnosed by routines called
       by this routine.  The output argument et will not be modified.
*/
void USpice::scs2e(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int sc,
    const FString& sclkch,
    FSEphemerisTime& et
)
{
    // Inputs
    SpiceInt        _sc = sc;
    ConstSpiceChar* _sclkch = TCHAR_TO_ANSI(*sclkch);
    // Outputs
    SpiceDouble     _et = 0;

    // Invocation
    scs2e_c(_sc, _sclkch, &_et);

    // Return Values
    et = FSEphemerisTime(_et);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  This routine assumes that that an SCLK kernel appropriate
       to the spacecraft clock identified by the input argument sc
       has been loaded.  If an SCLK kernel has not been loaded,
       does not contain all of the required data, or contains
       invalid data, error diagnoses will be performed by routines
       called by this routine.  The output argument et will not be
       modified.

   2)  When using SCLK kernels that map SCLK to a time system other
       than ET (also called barycentric dynamical time---`TDB'), it
       is necessary to have a leapseconds kernel loaded at the time
       this routine is called.  If a leapseconds kernel is required
       for conversion between SCLK and ET but is not loaded, the
       error will be diagnosed by routines called by this routine.
       The output argument et will not be modified.

       The time system that an SCLK kernel maps SCLK to is indicated
       by the variable SCLK_TIME_SYSTEM_nn in the kernel, where nn
       is the negative of the NAIF integer code for the spacecraft.
       The time system used in a kernel is TDB if and only if the
       variable is assigned the value 1.


   3)  If the clock type for the spacecraft clock identified by
       sc is not supported by this routine, the error
       SPICE(NOTSUPPORTED) is signalled.  The output argument et
       will not be modified.

   4)  If the input argument sclkdp is invalid, the error will be
       diagnosed by routines called by this routine.  The output
       argument et will not be modified.
*/
void USpice::sct2e(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int sc,
    double sclkdp,
    FSEphemerisTime& et
)
{
    // Inputs
    SpiceInt    _sc = sc;
    SpiceDouble _sclkdp = sclkdp;
    // Outputs
    SpiceDouble _et = 0;

    // Invocation
    sct2e_c(_sc, _sclkdp, &_et);

    // Return Values
    et = FSEphemerisTime(_et);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  If the spacecraft clock type is not supported then the
       error SPICE(NOTSUPPORTED) is signalled.

   2)  If any of the extracted clock components cannot be parsed as
       integers, or the string has too many components, or the value
       of one of the components is less than the offset value, then
       the error is diagnosed by routines called by this routine.

   3)  Invalid spacecraft ID's are not diagnosed.
*/
void USpice::sctiks(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int sc,
    const FString& clkstr,
    double& ticks
)
{
    // Inputs
    SpiceInt           _sc = sc;
    ConstSpiceChar* _clkstr = TCHAR_TO_ANSI(*clkstr);
    // Outputs
    SpiceDouble _ticks = 0;

    // Invocation
    sctiks_c(_sc, _clkstr, &_ticks);

    // Return Values
    ticks = double(_ticks);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


/*
Exceptions


   1)  If the specified aberration correction is unrecognized, the
       error will be diagnosed and signaled by a routine in the call
       tree of this routine.

   2)  If either the target or observer input strings cannot be
       converted to an integer ID code, the error
       SPICE(IDCODENOTFOUND) is signaled.

   3)  If `obsrvr' and `target' map to the same NAIF integer ID code,
       the error SPICE(BODIESNOTDISTINCT) is signaled.

   4)  If the input target body-fixed frame `fixref' is not
       recognized, the error SPICE(NOFRAME) is signaled. A frame
       name may fail to be recognized because a required frame
       specification kernel has not been loaded; another cause is a
       misspelling of the frame name.

   5)  If the input frame `fixref' is not centered at the target body,
       the error SPICE(INVALIDFRAME) is signaled.

   6)  If the input argument `method' cannot be parsed, the error
       is signaled either by this routine or by a routine in the
       call tree of this routine.

   7)  If the target and observer have distinct identities but are
       at the same location (for example, the target is Mars and the
       observer is the Mars barycenter), the error
       SPICE(NOSEPARATION) is signaled.

   8)  If insufficient ephemeris data have been loaded prior to
       calling sincpt_c, the error will be diagnosed and signaled by a
       routine in the call tree of this routine. Note that when
       light time correction is used, sufficient ephemeris data must
       be available to propagate the states of both observer and
       target to the solar system barycenter.

   9)  If the computation method specifies an ellipsoidal target
       shape and triaxial radii of the target body have not been
       loaded into the kernel pool prior to calling sincpt_c, the
       error will be diagnosed and signaled by a routine in the call
       tree of this routine.

   10) The target must be an extended body: if the target shape is
       modeled as an ellipsoid and any of the radii of the target body
       are non-positive, the error will be diagnosed and signaled by
       routines in the call tree of this routine.

   11) If PCK or CK data specifying the target body-fixed frame
       orientation have not been loaded prior to calling sincpt_c,
       the error will be diagnosed and signaled by a routine in the
       call tree of this routine.

   12) If the reference frame designated by `dref' is not recognized
       by the SPICE frame subsystem, the error SPICE(NOFRAME)
       will be signaled.

   13) If the direction vector `dvec' is the zero vector, the error
       SPICE(ZEROVECTOR) will be signaled.

   14) If `method' specifies that the target surface is represented by
       DSK data, and no DSK files are loaded for the specified
       target, the error is signaled by a routine in the call tree
       of this routine.

   15) If `method' specifies that the target surface is represented
       by DSK data, and DSK data are not available for a portion of
       the target body's surface, an intercept might not be found.
       This routine does not revert to using an ellipsoidal surface
       in this case.

*/

void USpice::sincpt(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSEphemerisTime& et,
    const FString& dref,
    const FSDimensionlessVector& dvec,
    FSDistanceVector& spoint,
    FSEphemerisTime& trgepc,
    FSDistanceVector& srfvec,
    bool& found,
    const FString& method,
    const FString& target,
    const FString& fixref,
    const FString& obsrvr,
    ES_AberrationCorrectionWithTransmissions abcorr
)
{
    // Inputs
    ConstSpiceChar* _method = TCHAR_TO_ANSI(*method);
    ConstSpiceChar* _target = TCHAR_TO_ANSI(*target);
    SpiceDouble     _et     = et.AsDouble();
    ConstSpiceChar* _fixref = TCHAR_TO_ANSI(*fixref);
    ConstSpiceChar* _abcorr;
    ConstSpiceChar* _obsrvr = TCHAR_TO_ANSI(*obsrvr);
    ConstSpiceChar* _dref   = TCHAR_TO_ANSI(*dref);
    SpiceDouble    _dvec[3];  dvec.CopyTo(_dvec);

    switch (abcorr)
    {
    case ES_AberrationCorrectionWithTransmissions::LT:
        _abcorr = "LT";
        break;
    case ES_AberrationCorrectionWithTransmissions::LT_S:
        _abcorr = "LT+S";
        break;
    case ES_AberrationCorrectionWithTransmissions::CN:
        _abcorr = "CN";
        break;
    case ES_AberrationCorrectionWithTransmissions::CN_S:
        _abcorr = "CN+S";
        break;
    case ES_AberrationCorrectionWithTransmissions::XLT:
        _abcorr = "XLT";
        break;
    case ES_AberrationCorrectionWithTransmissions::XLT_S:
        _abcorr = "XLT+S";
        break;
    case ES_AberrationCorrectionWithTransmissions::XCN:
        _abcorr = "XCN";
        break;
    case ES_AberrationCorrectionWithTransmissions::XCN_S:
        _abcorr = "XCN+S";
        break;
    default:
        _abcorr = "NONE";
    }
    
    // Outputs
    SpiceDouble  _spoint[3];    ZeroOut(_spoint);
    SpiceDouble  _trgepc        = 0.;
    SpiceDouble  _srfvec[3];    ZeroOut(_srfvec);
    SpiceBoolean _found         = SPICEFALSE;

    // Invocation
    sincpt_c(
        _method,
        _target,
        _et,
        _fixref,
        _abcorr,
        _obsrvr,
        _dref,
        _dvec,
        _spoint,
        &_trgepc,
        _srfvec,
        &_found
    );

    // Return Values
    spoint = FSDistanceVector(_spoint);
    trgepc = FSEphemerisTime(_trgepc);
    srfvec = FSDistanceVector(_srfvec);
    found = _found != SPICEFALSE ? true : false;

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


/*
Exceptions
   Error free.
*/
void USpice::spd(double& value)
{
    SpiceDouble _value = spd_c();
    value = double(_value);
}

/*
Exceptions
   Error free.
*/
void USpice::spd_day(FSEphemerisPeriod& oneDay)
{
    oneDay = FSEphemerisPeriod::Day;
}

/*
Exceptions

   Error free.
*/
void USpice::sphlat(
    const FSDistance& r,
    const FSAngle& colat,
    const FSAngle& lons,
    FSDistance& radius,
    FSLonLat& lonlat
)
{
    // Input
    SpiceDouble _r = r.AsDouble();
    SpiceDouble _colat = colat.AsDouble();
    SpiceDouble _lons = lons.AsDouble();
    // Output
    SpiceDouble _radius;
    SpiceDouble _lon;
    SpiceDouble _lat;

    // Invocation
    sphlat_c(_r, _colat, _lons, &_radius, &_lon, &_lat);

    // Return Values
    radius = FSDistance(_radius);
    lonlat = FSLonLat(_lon, _lat);
}

/*
Exceptions

   Error free.
*/
void USpice::sphrec(
    const FSDistance& r,
    const FSAngle& colat,
    const FSAngle& lon,
    FSDistanceVector& rectan
)
{
    // Input
    SpiceDouble _r = r.AsDouble();
    SpiceDouble _colat = colat.AsDouble();
    SpiceDouble _lon = lon.AsDouble();
    // Output
    SpiceDouble _rectan[3];

    // Invocation
    sphrec_c(_r, _colat, _lon, _rectan);

    // Return Values
    rectan = FSDistanceVector(_rectan);
}
/*
Exceptions

   1) If there are no segments in the file, the error
      SPICE(NOSEGMENTSFOUND) will be signaled.
*/
void USpice::spkcls(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int handle
)
{
    // Inputs
    SpiceInt _handle = handle;

    // Invocation
    spkcls_c(_handle);

    // Error handling
    ErrorCheck(ResultCode, ErrorMessage);
}



/*
Exceptions

   1)  If the input file has transfer format, the error
       SPICE(INVALIDFORMAT) is signaled.

   2)  If the input file is not a transfer file but has architecture
       other than DAF, the error SPICE(BADARCHTYPE) is signaled.

   3)  If the input file is a binary DAF file of type other than
       SPK, the error SPICE(BADFILETYPE) is signaled.

   4)  If the SPK file cannot be opened or read, the error will
       be diagnosed by routines called by this routine. The output
       window will not be modified.
       routines called by this routine.

   5)  If the size of the output window argument `cover' is
       insufficient to contain the actual number of intervals in the
       coverage window for `idcode', the error will be diagnosed by
       routines called by this routine.

   6) The error SPICE(EMPTYSTRING) is signaled if the input
      string `spk' does not contain at least one character, since the
      input string cannot be converted to a Fortran-style string in
      this case.

   7) The error SPICE(NULLPOINTER) is signaled if the input string
      pointer `spk' is null.
*/
void USpice::spkcov(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& spkFileRelativePath,
    int idcode,
    const TArray<FSWindowSegment>& merge_to,
    TArray<FSWindowSegment>& coverage
)
{
    ::checkcov(ResultCode, ErrorMessage, spkFileRelativePath, idcode, merge_to, coverage, spkcov_c);
}


/*
Exceptions

   1)  If either the name of the center of motion or the target
       cannot be translated to its NAIF ID code, the error  will
       be diagnosed by a routine in the call tree of this routine.

   2)  If the reference frame `outref' is unrecognized, the error will
       be diagnosed by a routine in the call tree of this routine.

   3)  If the reference frame `obsref' is unrecognized, the error will
       be diagnosed by a routine in the call tree of this routine.

   4)  If the frame evaluation locus `refloc' is not recognized, the
       error  will be diagnosed by a routine in the call tree of this
       routine.

   5)  If the loaded kernels provide insufficient data to compute
       the requested state vector, the deficiency will be diagnosed
       by a routine in the call tree of this routine.

   6)  If an error occurs while reading an SPK or other kernel file,
       the error  will be diagnosed by a routine in the call tree of
       this routine.

   7)  If the aberration correction `abcorr' is not recognized,
       the error will be diagnosed by a routine in the call tree of
       this routine.

   8)  If any input string pointer is null, or if the output state
       pointer is null, the error SPICE(NULLPOINTER) will be signaled.

   9)  If any input string has length zero, the error SPICE(EMPTYSTRING)
       will be signaled.
*/
void USpice::spkcpo(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& target,
    const FSEphemerisPeriod& et,
    const FString& outref,
    const FString& refloc,
    const FSDistanceVector& obspos,
    const FString& obsctr,
    const FString& obsref,
    FSStateVector& state,
    FSEphemerisPeriod& lt,
    ES_AberrationCorrectionWithNewtonians
    abcorr
)
{
    // Inputs
    ConstSpiceChar* _target = TCHAR_TO_ANSI(*target);
    SpiceDouble     _et = et.AsDouble();
    ConstSpiceChar* _outref = TCHAR_TO_ANSI(*outref);
    ConstSpiceChar* _refloc = TCHAR_TO_ANSI(*refloc);
    ConstSpiceChar* _abcorr = USpiceTypes::_toString(abcorr);
    SpiceDouble     _obspos[3]; obspos.CopyTo(_obspos);
    ConstSpiceChar* _obsctr = TCHAR_TO_ANSI(*obsctr);
    ConstSpiceChar* _obsref = TCHAR_TO_ANSI(*obsref);
    // Outputs
    SpiceDouble     _state[6];  ZeroOut(_state);
    SpiceDouble     _lt = 0;


    // Invocation
    spkcpo_c(
        _target,
        _et,
        _outref,
        _refloc,
        _abcorr,
        _obspos,
        _obsctr,
        _obsref,
        _state,
        &_lt
    );

    // Return Values
    state = FSStateVector(_state);
    lt = FSEphemerisPeriod(_lt);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  If either the name of the center of motion or the observer
       cannot be translated to its NAIF ID code, the error will
       be diagnosed by a routine in the call tree of this routine.

   2)  If the reference frame `outref' is unrecognized, the error will
       be diagnosed by a routine in the call tree of this routine.

   3)  If the reference frame `trgref' is unrecognized, the error will
       be diagnosed by a routine in the call tree of this routine.

   4)  If the frame evaluation locus `refloc' is not recognized, the
       error will be diagnosed by a routine in the call tree of this
       routine.

   5)  If the loaded kernels provide insufficient data to compute
       the requested state vector, the deficiency will be diagnosed
       by a routine in the call tree of this routine.

   6)  If an error occurs while reading an SPK or other kernel file,
       the error will be diagnosed by a routine in the call tree of
       this routine.

   7)  If the aberration correction `abcorr' is not recognized,
       the error will be diagnosed by a routine in the call tree of
       this routine.

   8)  If any input string pointer is null, or if the output state
       pointer is null, the error SPICE(NULLPOINTER) will be signaled.

   9)  If any input string has length zero, the error SPICE(EMPTYSTRING)
       will be signaled.
*/
void USpice::spkcpt(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSDistanceVector& trgpos,
    const FString& trgctr,
    const FString& trgref,
    const FSEphemerisPeriod& et,
    const FString& outref,
    const FString& refloc,
    const FString& obsrvr,
    FSStateVector& state,
    FSEphemerisPeriod& lt,
    ES_AberrationCorrectionWithNewtonians
    abcorr
)
{
    // Inputs
    SpiceDouble     _trgpos[3]; trgpos.CopyTo(_trgpos);
    ConstSpiceChar* _trgctr = TCHAR_TO_ANSI(*trgctr);
    ConstSpiceChar* _trgref = TCHAR_TO_ANSI(*trgref);
    SpiceDouble     _et = et.AsDouble();
    ConstSpiceChar* _outref = TCHAR_TO_ANSI(*outref);
    ConstSpiceChar* _refloc = TCHAR_TO_ANSI(*refloc);
    ConstSpiceChar* _abcorr = USpiceTypes::_toString(abcorr);
    ConstSpiceChar* _obsrvr = TCHAR_TO_ANSI(*obsrvr);
    // Outputs
    SpiceDouble     _state[6];  ZeroOut(_state);
    SpiceDouble     _lt = 0;


    // Invocation
    spkcpt_c(
        _trgpos,
        _trgctr,
        _trgref,
        _et,
        _outref,
        _refloc,
        _abcorr,
        _obsrvr,
        _state,
        &_lt
    );

    // Return Values
    state = FSStateVector(_state);
    lt = FSEphemerisPeriod(_lt);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


/*
Exceptions

   1)  If either the name of the center of motion or the target
       cannot be translated to its NAIF ID code, the error
       SPICE(IDCODENOTFOUND) is signaled.

   2)  If the reference frame `outref' is unrecognized, the error
       SPICE(IDCODENOTFOUND) is signaled.

   3)  If the reference frame `obsref' is unrecognized, the error will
       be diagnosed by a routine in the call tree of this routine.

   4)  If the frame evaluation locus `refloc' is not recognized,
       the error SPICE(NOTSUPPORTED) is signaled.

   5)  If the loaded kernels provide insufficient data to compute
       the requested state vector, the deficiency will be diagnosed
       by a routine in the call tree of this routine.

   6)  If an error occurs while reading an SPK or other kernel file,
       the error  will be diagnosed by a routine in the call tree of
       this routine.

   7)  If the aberration correction `abcorr' is not recognized,
       the error will be diagnosed by a routine in the call tree of
       this routine.

   8)  If any input string pointer is null, or if the output state
       pointer is null, the error SPICE(NULLPOINTER) will be signaled.

   9)  If any input string has length zero, the error SPICE(EMPTYSTRING)
       will be signaled.
*/
void USpice::spkcvo(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& target,
    const FSEphemerisTime& et,
    const FString& outref,
    const FString& refloc,
    const FSStateVector& obssta,
    const FSEphemerisTime& obsepc,
    const FString& obsctr,
    const FString& obsref,
    FSStateVector& state,
    FSEphemerisPeriod& lt,
    ES_AberrationCorrectionWithNewtonians
    abcorr
)
{
    // Inputs
    ConstSpiceChar* _target = TCHAR_TO_ANSI(*target);
    SpiceDouble     _et = et.AsDouble();
    ConstSpiceChar* _outref = TCHAR_TO_ANSI(*outref);
    ConstSpiceChar* _refloc = TCHAR_TO_ANSI(*refloc);
    ConstSpiceChar* _abcorr = USpiceTypes::_toString(abcorr);
    SpiceDouble     _obssta[6]; obssta.CopyTo(_obssta);
    SpiceDouble     _obsepc = obsepc.AsDouble();
    ConstSpiceChar* _obsctr = TCHAR_TO_ANSI(*obsctr);
    ConstSpiceChar* _obsref = TCHAR_TO_ANSI(*obsref);
    // Outputs
    SpiceDouble     _state[6];  ZeroOut(_state);
    SpiceDouble     _lt = 0;

    // Invocation
    spkcvo_c(
        _target,
        _et,
        _outref,
        _refloc,
        _abcorr,
        _obssta,
        _obsepc,
        _obsctr,
        _obsref,
        _state,
        &_lt
    );

    // Return Values
    state = FSStateVector(_state);
    lt = FSEphemerisPeriod(_lt);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  If either the name of the center of motion or the observer
       cannot be translated to its NAIF ID code, the error
       SPICE(IDCODENOTFOUND) is signaled.

   2)  If the reference frame `outref' is unrecognized, the error
       SPICE(UNKNOWNFRAME) will be signaled.

   3)  If the reference frame `trgref' is unrecognized, the error will
       be diagnosed by a routine in the call tree of this routine.

   4)  If the frame evaluation locus `refloc' is not recognized,
       the error SPICE(NOTSUPPORTED) is signaled.

   5)  If the loaded kernels provide insufficient data to compute
       the requested state vector, the deficiency will be diagnosed
       by a routine in the call tree of this routine.

   6)  If an error occurs while reading an SPK or other kernel file,
       the error will be diagnosed by a routine in the call tree of
       this routine.

   7)  If the aberration correction `abcorr' is not recognized,
       the error will be diagnosed by a routine in the call tree of
       this routine.

   8)  If any input string pointer is null, or if the output state
       pointer is null, the error SPICE(NULLPOINTER) will be signaled.

   9)  If any input string has length zero, the error SPICE(EMPTYSTRING)
       will be signaled.
*/

void USpice::spkcvt(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSStateVector& trgsta,
    const FSEphemerisTime& trgepc,
    const FString& trgctr,
    const FString& trgref,
    const FSEphemerisTime& et,
    const FString& outref,
    const FString& refloc,
    const FString& obsrvr,
    FSStateVector& state,
    FSEphemerisPeriod& lt,
    ES_AberrationCorrectionWithNewtonians
    abcorr
)
{
    // Inputs
    SpiceDouble     _trgsta[6]; trgsta.CopyTo(_trgsta);
    SpiceDouble     _trgepc = trgepc.AsDouble();
    ConstSpiceChar* _trgctr = TCHAR_TO_ANSI(*trgctr);
    ConstSpiceChar* _trgref = TCHAR_TO_ANSI(*trgref);
    SpiceDouble     _et = et.AsDouble();
    ConstSpiceChar* _outref = TCHAR_TO_ANSI(*outref);
    ConstSpiceChar* _refloc = TCHAR_TO_ANSI(*refloc);
    ConstSpiceChar* _abcorr = USpiceTypes::_toString(abcorr);
    ConstSpiceChar* _obsrvr = TCHAR_TO_ANSI(*obsrvr);
    // Outputs
    SpiceDouble     _state[6];  ZeroOut(_state);
    SpiceDouble     _lt = 0;

    // Invocation
    spkcvt_c(
        _trgsta,
        _trgepc,
        _trgctr,
        _trgref,
        _et,
        _outref,
        _refloc,
        _abcorr,
        _obsrvr,
        _state,
        &_lt
    );

    // Return Values
    state = FSStateVector(_state);
    lt = FSEphemerisPeriod(_lt);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}


/*
Exceptions

   1) If name of target or observer cannot be translated to its
      NAIF ID code, the error SPICE(IDCODENOTFOUND) is signaled.

   2) If the reference frame 'ref' is not a recognized reference
      frame the error SPICE(UNKNOWNFRAME) is signaled.

   3) If the loaded kernels provide insufficient data to
      compute the requested position vector, the deficiency will
      be diagnosed by a routine in the call tree of this routine.

   4) If an error occurs while reading an SPK or other kernel file,
      the error  will be diagnosed by a routine in the call tree
      of this routine.
*/
void USpice::spkezp(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSEphemerisTime& et,
    FSDistanceVector& ptarg,
    FSEphemerisPeriod& lt,
    int targ,
    int obs,
    const FString& ref,
    ES_AberrationCorrectionWithNewtonians abcorr
)
{
    SpiceDouble _lt = 0;
    SpiceDouble _ptarg[3];
    ZeroOut(_ptarg);

    ConstSpiceChar* _abcorr = USpiceTypes::_toString(abcorr);

    spkezp_c(targ, et.seconds, TCHAR_TO_ANSI(*ref), _abcorr, obs, _ptarg, &_lt);

    lt = FSEphemerisPeriod(_lt);
    ptarg = FSDistanceVector(_ptarg);

    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1) If name of target or observer cannot be translated to its
      NAIF ID code, the error SPICE(IDCODENOTFOUND) is signaled.

   2) If the reference frame `ref' is not a recognized reference
      frame the error SPICE(UNKNOWNFRAME) is signaled.

   3) If the loaded kernels provide insufficient data to
      compute the requested state vector, the deficiency will
      be diagnosed by a routine in the call tree of this routine.

   4) If an error occurs while reading an SPK or other kernel file,
      the error will be diagnosed by a routine in the call tree
      of this routine.
*/
void USpice::spkezr(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSEphemerisTime& et,
    FSStateVector& state,
    FSEphemerisPeriod& lt,
    const FString& targ,
    const FString& obs,
    const FString& ref,
    ES_AberrationCorrectionWithNewtonians abcorr
)
{
    SpiceDouble _lt = 0;
    SpiceDouble _state[6];
    ZeroOut(_state);

    ConstSpiceChar* _abcorr = USpiceTypes::_toString(abcorr);

    spkezr_c(TCHAR_TO_ANSI(*targ), et.seconds, TCHAR_TO_ANSI(*ref), _abcorr, TCHAR_TO_ANSI(*obs), _state, &_lt);

    lt = FSEphemerisPeriod(_lt);
    state = FSStateVector(_state);

    ErrorCheck(ResultCode, ErrorMessage);
}


/*
Exceptions

   1) If insufficient ephemeris data have been loaded to compute
      the requested state, the error SPICE(SPKINSUFFDATA) is
      signalled.
*/
void USpice::spkgeo(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int targ,
    const FSEphemerisTime& et,
    int obs,
    FSStateVector& state,
    FSEphemerisPeriod& lt,
    const FString& ref
)
{
    SpiceDouble _lt = 0;
    SpiceDouble _state[6];
    ZeroOut(_state);

    spkgeo_c((SpiceInt)targ, et.seconds, TCHAR_TO_ANSI(*ref), (SpiceInt)obs, _state, &_lt);

    lt = FSEphemerisPeriod(_lt);
    state = FSStateVector(_state);

    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1) If insufficient ephemeris data has been loaded to compute
      the necessary positions, the error SPICE(SPKINSUFFDATA) is
      signalled.
*/
void USpice::spkgps(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int targ,
    const FSEphemerisTime& et,
    int obs,
    FSDistanceVector& pos,
    FSEphemerisPeriod& lt,
    const FString& ref
)
{
    SpiceDouble _lt = 0;
    SpiceDouble _pos[3];
    ZeroOut(_pos);

    spkgps_c((SpiceInt)targ, et.seconds, TCHAR_TO_ANSI(*ref), (SpiceInt)obs, _pos, &_lt);

    lt = FSEphemerisPeriod(_lt);
    pos = FSDistanceVector(_pos);

    ErrorCheck(ResultCode, ErrorMessage);
}


/*
Exceptions

   1) If name of target or observer cannot be translated to its
      NAIF ID code, the error SPICE(IDCODENOTFOUND) is signaled.

   2) If the reference frame `ref' is not a recognized reference
      frame the error SPICE(UNKNOWNFRAME) is signaled.

   3) If the loaded kernels provide insufficient data to
      compute the requested position vector, the deficiency will
      be diagnosed by a routine in the call tree of this routine.

   4) If an error occurs while reading an SPK or other kernel file,
      the error  will be diagnosed by a routine in the call tree
      of this routine.
*/
void USpice::spkpos(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSEphemerisTime& et,
    FSDistanceVector& ptarg,
    FSEphemerisPeriod& lt,
    const FString& targ,
    const FString& obs,
    const FString& ref,
    ES_AberrationCorrectionWithNewtonians abcorr
)
{
    SpiceDouble _lt = 0;
    SpiceDouble _ptarg[3];
    ZeroOut(_ptarg);

    ConstSpiceChar* _abcorr = USpiceTypes::_toString(abcorr);

    spkpos_c(TCHAR_TO_ANSI(*targ), et.seconds, TCHAR_TO_ANSI(*ref), _abcorr, TCHAR_TO_ANSI(*obs), _ptarg, &_lt);

    lt = FSEphemerisPeriod(_lt);
    ptarg = FSDistanceVector(_ptarg);

    ErrorCheck(ResultCode, ErrorMessage);
}


/*
Exceptions
   The parameter FTSIZE referenced below is defined in the header file
   cspicelimits.h.

   1) If an attempt is made to load more files than is specified
      by the parameter FTSIZE, the error "SPICE(SPKFILETABLEFULL)" is
      signalled.

   2) If an attempt is made to open more DAF files than is specified
      by the parameter FTSIZE, an error is signalled by a routine that
      this routine calls.
*/
void USpice::spklef(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& relativePath,
    int& handle
)
{
    // Input
    auto gameDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
    ConstSpiceChar* _filename = TCHAR_TO_ANSI(*(gameDir + relativePath));

    // Output
    SpiceInt        _handle = 0;

    // Invocation
    spklef_c(_filename, &_handle);

    // Return Value
    handle = int(_handle);

    // Error handling
    ErrorCheck(ResultCode, ErrorMessage);
}


/*
Exceptions

   1)  If the input file has transfer format, the error
       SPICE(INVALIDFORMAT) is signaled.

   2)  If the input file is not a transfer file but has architecture
       other than DAF, the error SPICE(BADARCHTYPE) is signaled.

   3)  If the input file is a binary DAF file of type other than
       SPK, the error SPICE(BADFILETYPE) is signaled.

   4)  If the SPK file cannot be opened or read, the error will
       be diagnosed by routines called by this routine.

   5)  If the size of the output set argument `ids' is insufficient to
       contain the actual number of ID codes of objects covered by
       the indicated SPK file, the error will be diagnosed by
       routines called by this routine.

   6) The error SPICE(EMPTYSTRING) is signaled if the input
      string `spk' does not contain at least one character, since the
      input string cannot be converted to a Fortran-style string in
      this case.

   7) The error SPICE(NULLPOINTER) is signaled if the input string
      pointer `spk' is null.
*/
void USpice::spkobj(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& relativePath,
    TArray<int>& ids
)
{
    const int MAXOBJ = 1000;

    SPICEINT_CELL(idscell, MAXOBJ);

    // Inputs
    auto gameDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
    ConstSpiceChar* _fname = TCHAR_TO_ANSI(*(gameDir + relativePath));

    // Outputs
    SpiceCell* _ids = &idscell;

    // Invocation
    spkobj_c(_fname, _ids);

    ids = TArray<int>();
    int count = card_c(_ids);
    for (int i = 0; i < count; i++)
    {
        SpiceInt id = SPICE_CELL_ELEM_I(_ids, i);
        ids.Add(int(id));
    }

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1)  If the file specified does not exist the error
       SPICE(FILENOTFOUND) will be signalled.

   2)  If the file specified is not an SPK file, the error
       SPICE(FILEISNOTSPK) will be signalled.

   3)  If the string pointer file is null, the error
       SPICE(NULLPOINTER) will be signaled.

   4)  If the string file has length zero, the error
       SPICE(EMPTYSTRING) will be signaled.

   All other exceptions are determined by routines in the call
   tree of this routine. If any exceptions arise that prevent
   opening of the specified file for writing, HANDLE will be
   returned with the value 0.
*/
void USpice::spkopa(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& relativePath,
    int& handle
)
{
    // Inputs
    auto gameDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
    ConstSpiceChar* _file = TCHAR_TO_ANSI(*(gameDir + relativePath));

    // Output
    SpiceInt _handle = 0;

    // Invocation
    spkopa_c(_file, &_handle);

    // Return Value
    handle = int(_handle);

    // Error handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1) If the value of ncomch is negative, a value of zero (0) will
      be used for the number of comment characters to be set aside
      for comments.

   2) If an error occurs while attempting to open a CK file, the
      value of handle will not represent a valid file handle.

   3) If any input string pointers are null, the error
      SPICE(NULLPOINTER) will be signaled.

   4) If any input strings have length zero, the error
      SPICE(EMPTYSTRING) will be signaled.
*/
void USpice::spkopn(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& relativePath,
    const FString& ifname,
    int         ncomch,
    int& handle
)
{
    // Inputs
    auto gameDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
    ConstSpiceChar* _file = TCHAR_TO_ANSI(*(gameDir + relativePath));

    ConstSpiceChar* _ifname = TCHAR_TO_ANSI(*ifname);
    SpiceInt        _ncomch = ncomch;
    // Output
    SpiceInt        _handle = 0;

    // Invocation
    spkopn_c(_file, _ifname, _ncomch, &_handle);

    // Return Value
    handle = int(_handle);

    // Error handling
    ErrorCheck(ResultCode, ErrorMessage);
}



/*
Exceptions

   None.
*/
void USpice::spkuef(
    int handle
)
{
    // Input
    SpiceInt _handle = handle;

    // Invocation
    spkuef_c(_handle);
}


void USpice::spkw05(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    int handle,
    int body,
    int center,
    const FString& frame,
    const FSEphemerisTime& first,
    const FSEphemerisTime& last,
    const FString& segid,
    const FSMassConstant& gm,
    const TArray<FSPKType5Observation>& states
)
{
    // Inputs
    SpiceInt         _handle = handle;
    SpiceInt         _body = body;
    SpiceInt         _center = center;
    ConstSpiceChar* _frame = TCHAR_TO_ANSI(*frame);
    SpiceDouble      _first = first.AsDouble();
    SpiceDouble      _last = last.AsDouble();
    ConstSpiceChar* _segid = TCHAR_TO_ANSI(*segid);
    SpiceDouble      _gm = gm.AsDouble();
    SpiceInt         _n = states.Num();

    SpiceDouble(*_states)[6] = (SpiceDouble(*)[6])StackAlloc(_n * sizeof(SpiceDouble[6]));
    SpiceDouble* _epochs = (SpiceDouble*)StackAlloc(_n * sizeof(SpiceDouble));

    for (int i = 0; i < states.Num(); ++i)
    {
        _epochs[i] = states[i].et.AsDouble();
        states[i].state.CopyTo(_states[i]);
    }

    // Invocation
    spkw05_c(
        _handle,
        _body,
        _center,
        _frame,
        _first,
        _last,
        _segid,
        _gm,
        _n,
        _states,
        _epochs
    );

    // Error handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1) If any of the axes are non-positive, the error
      SPICE(BADAXISLENGTH) will be signalled.
*/
void USpice::surfnm(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSDistance& a,
    const FSDistance& b,
    const FSDistance& c,
    const FSDistanceVector& point,
    FSDimensionlessVector& normal
)
{
    // Input
    SpiceDouble        _a = a.AsDouble();
    SpiceDouble        _b = b.AsDouble();
    SpiceDouble        _c = c.AsDouble();
    SpiceDouble _point[3];  point.CopyTo(_point);
    // Output
    SpiceDouble _normal[3]; ZeroOut(_normal);

    // Invocation
    surfnm_c(_a, _b, _c, _point, _normal);

    // Return Value
    normal = FSDimensionlessVector(_normal);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

    1) If the input vector is the zero vector, the error
       SPICE(ZEROVECTOR) is signaled.

    2) If any of the body's axes is zero, the error
       SPICE(BADAXISLENGTH) is signaled.
*/
void USpice::surfpt(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSDistanceVector& positn,
    const FSDimensionlessVector& u,
    const FSDistance& a,
    const FSDistance& b,
    const FSDistance& c,
    FSDistanceVector& point,
    bool& found
)
{
    // Input
    SpiceDouble _positn[3]; positn.CopyTo(_positn);
    SpiceDouble _u[3];      u.CopyTo(_u);
    SpiceDouble _a = a.AsDouble();
    SpiceDouble _b = b.AsDouble();
    SpiceDouble _c = c.AsDouble();
    // Output
    SpiceDouble _point[3];  ZeroOut(_point);
    SpiceBoolean* _found = false;

    // Invocation
    surfpt_c(_positn, _u, _a, _b, _c, _point, _found);

    // Return Value
    point = FSDistanceVector(_point);
    found = _found ? true : false;

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   1) If sufficient information has not been supplied via loaded
      SPICE kernels to compute the transformation between the
      two frames, the error will be diagnosed by a routine
      in the call tree of this routine.

   2) If either frame `from' or `to' is not recognized the error
      SPICE(UNKNOWNFRAME) will be signaled.
*/
void USpice::sxform(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSEphemerisTime& et,
    FSStateTransform& xform,
    const FString& from,
    const FString& to
)
{
    // Input
    SpiceChar* _from = TCHAR_TO_ANSI(*from);
    SpiceChar* _to = TCHAR_TO_ANSI(*to);
    SpiceDouble _et = et.AsDouble();
    // Output
    SpiceDouble _xform[6][6];   ZeroOut(_xform);

    // Invocation
    sxform_c(_from, _to, _et, _xform);

    // Return Value
    xform = FSStateTransform(_xform);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

    Error free.
*/
void USpice::trace(
    const FSRotationMatrix& matrix,
    double& trace
)
{
    SpiceDouble  _matrix[3][3];
    matrix.CopyTo(_matrix);

    SpiceDouble _trace = trace_c(_matrix);

    trace = double(_trace);
}

/*
Exceptions

    Error free.
*/
void USpice::twopi(
    double& two_pi
)
{
    two_pi = twopi_c();
}


void USpice::twopi_angle(FSAngle& two_pi)
{
    two_pi = FSAngle(twopi_c());
}

/*
Exceptions

   1) If indexa or indexp is not in the set {1,2,3} the error
      SPICE(BADINDEX) will be signalled.

   2) If indexa and indexp are the same the error
      SPICE(UNDEFINEDFRAME) will be signalled.

   3) If the cross product of the vectors axdef and plndef is zero,
      the error SPICE(DEPENDENTVECTORS) will be signalled.
*/
void USpice::twovec(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSDimensionlessVector& axdef,
    ES_Axis                         indexa,
    const FSDimensionlessVector& plndef,
    ES_Axis                         indexp,
    FSRotationMatrix& mout
)
{
    // Input
    SpiceDouble _axdef[3];  axdef.CopyTo(_axdef);
    SpiceInt    _indexa = (SpiceInt)indexa;
    SpiceDouble _plndef[3]; plndef.CopyTo(_plndef);
    SpiceInt    _indexp = (SpiceInt)indexp;
    // Output
    SpiceDouble _mout[3][3]; ZeroOut(_mout);

    // Invocation
    twovec_c(_axdef, _indexa, _plndef, _indexp, _mout);

    // Return Value
    mout = FSRotationMatrix(_mout);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   Error free.

   1) If the cross product of v1 and v2 yields the zero-vector, then
      the zero-vector is returned instead of a vector of unit length.
*/
void USpice::ucrss(
    const FSDimensionlessVector& v1,
    const FSDimensionlessVector& v2,
    FSDimensionlessVector& vout
)
{
    // Input
    SpiceDouble _v1[3];     v1.CopyTo(_v1);
    SpiceDouble _v2[3];     v2.CopyTo(_v2);
    // Output
    SpiceDouble _vout[3];

    // Invocation
    ucrss_c(_v1, _v2, _vout);

    // Return Value
    vout = FSDimensionlessVector(_vout);
}


static FDerivativeDelegate DerivativeDelegate;
static void __udfunc(SpiceDouble et, SpiceDouble* value)
{
    double _value;
    DerivativeDelegate.Execute(et, _value);
    *value = _value;
}


/*
Exceptions
   None
*/
void USpice::uddf(
    const FDerivativeDelegate& udfunc,
    double x,
    double dx,
    double& deriv
)
{
    // Inputs
    void (*_udfunc) (SpiceDouble et, SpiceDouble * value) = __udfunc;
    SpiceDouble _x = x;
    SpiceDouble _dx = dx;
    // Output
    SpiceDouble _deriv = 0;

    // Begin reckless, ugly static hack
    DerivativeDelegate = udfunc;

    // Invoke
    uddf_c(_udfunc, _x, _dx, &_deriv);

    // End ugly static hack
    DerivativeDelegate.Unbind();

    // Return Value
    deriv = _deriv;
}


/*
Exceptions
   1) The kernel pool must contain the variables:

         "DELTET/DELTA_T_A"
         "DELTET/K"
         "DELTET/EB"
         "DELTET/M"

      If these are not present, the error SPICE(MISSINGTIMEINFO)
      will be signalled.  (These variables are typically inserted
      into the kernel pool by loading a leapseconds kernel with
      the SPICE routine furnsh_c.)

   2) If the names of either the input or output time types are
      unrecognized, the error SPICE(BADTIMETYPE) will be signalled.

   4) The error SPICE(EMPTYSTRING) is signalled if either input
      string does not contain at least one character, since an
      empty input string cannot be converted to a Fortran-style string.

   5) The error SPICE(NULLPOINTER) is signalled if either input string
      pointer is null.
*/
void USpice::unitim(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    double& out,
    double epoch,
    ES_TimeScale insys,
    ES_TimeScale outsys
)
{
    // Inputs
    SpiceDouble     _epoch = epoch;
    ConstSpiceChar* _insys = USpiceTypes::TimeScaleToChar(insys);
    ConstSpiceChar* _outsys = USpiceTypes::TimeScaleToChar(outsys);

    // Output 
    SpiceDouble _out;

    // Invocation
    _out = unitim_c(_epoch, _insys, _outsys);

    // Return Value
    out = _out;

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   Error free.
*/
void USpice::unorm_distance(
    const FSDistanceVector& v1,
    FSDimensionlessVector& vout,
    FSDistance& vmag
)
{
    // input
    SpiceDouble  _v1[3];    v1.CopyTo(_v1);
    // Outputs
    SpiceDouble  _vout[3];
    SpiceDouble _vmag;

    // Invocation
    unorm_c(_v1, _vout, &_vmag);

    // Return Value
    vout = FSDimensionlessVector(_vout);
    vmag = FSDistance(_vmag);
}


void USpice::unorm_velocity(
    const FSVelocityVector& v1,
    FSDimensionlessVector& vout,
    FSSpeed& vmag
)
{
    // input
    SpiceDouble  _v1[3];    v1.CopyTo(_v1);
    // Outputs
    SpiceDouble  _vout[3];
    SpiceDouble _vmag;

    // Invocation
    unorm_c(_v1, _vout, &_vmag);

    // Return Value
    vout = FSDimensionlessVector(_vout);
    vmag = FSSpeed(_vmag);
}


void USpice::unorm_angular_velocity(
    const FSAngularVelocity& v1,
    FSDimensionlessVector& vout,
    FSAngularRate& vmag
)
{
    // input
    SpiceDouble  _v1[3];    v1.CopyTo(_v1);
    // Outputs
    SpiceDouble  _vout[3];
    SpiceDouble _vmag;

    // Invocation
    unorm_c(_v1, _vout, &_vmag);

    // Return Value
    vout = FSDimensionlessVector(_vout);
    vmag = FSAngularRate(_vmag);
}


void USpice::unorm(
    const FSDimensionlessVector& v1,
    FSDimensionlessVector& vout,
    double& vmag
)
{
    // input
    SpiceDouble  _v1[3];    v1.CopyTo(_v1);
    // Outputs
    SpiceDouble  _vout[3];
    SpiceDouble _vmag;

    // Invocation
    unorm_c(_v1, _vout, &_vmag);

    // Return Value
    vout = FSDimensionlessVector(_vout);
    vmag = double(_vmag);
}

/*
Exceptions
   1) If the input time string is ambiguous, the error
      SPICE(INVALIDTIMESTRING) is signalled.

   2) This routine does not attempt to account for variations
      in the length of the second that were in effect prior
      to Jan 1, 1972.  For days prior to that date, we assume
      there are exactly 86400 ephemeris seconds.

   3) The error SPICE(EMPTYSTRING) is signalled if the input
      string does not contain at least one character, since the
      input string cannot be converted to a Fortran-style string
      in this case.

   4) The error SPICE(NULLPOINTER) is signalled if the input string
      pointer is null.
*/
void USpice::utc2et(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FString& utcstr,
    FSEphemerisTime& et
)
{
    // Input
    ConstSpiceChar* _utcstr = TCHAR_TO_ANSI(*utcstr);

    // Output
    SpiceDouble _et = 0;

    // Invocation
    utc2et_c(_utcstr, &_et);

    // Return Value
    et = FSEphemerisTime(_et);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   Error free
*/
void USpice::vadd_distance(
    const FSDistanceVector& v1,
    const FSDistanceVector& v2,
    FSDistanceVector& vout
)
{
    // Input
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    SpiceDouble _v2[3]; v2.CopyTo(_v2);
    // Output
    SpiceDouble _vout[3];

    // Invocation
    vadd_c(_v1, _v2, _vout);

    // Return Value
    vout = FSDistanceVector(_vout);
}


void USpice::vadd_velocity(
    const FSVelocityVector& v1,
    const FSVelocityVector& v2,
    FSVelocityVector& vout
)
{
    // Input
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    SpiceDouble _v2[3]; v2.CopyTo(_v2);
    // Output
    SpiceDouble _vout[3];

    // Invocation
    vadd_c(_v1, _v2, _vout);

    // Return Value
    vout = FSVelocityVector(_vout);
}


void USpice::vadd_angular_velocity(
    const FSAngularVelocity& v1,
    const FSAngularVelocity& v2,
    FSAngularVelocity& vout
)
{
    // Input
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    SpiceDouble _v2[3]; v2.CopyTo(_v2);
    // Output
    SpiceDouble _vout[3];

    // Invocation
    vadd_c(_v1, _v2, _vout);

    // Return Value
    vout = FSAngularVelocity(_vout);
}


void USpice::vadd(
    const FSDimensionlessVector& v1,
    const FSDimensionlessVector& v2,
    FSDimensionlessVector& vout
)
{
    // Input
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    SpiceDouble _v2[3]; v2.CopyTo(_v2);
    // Output
    SpiceDouble _vout[3];

    // Invocation
    vadd_c(_v1, _v2, _vout);

    // Return Value
    vout = FSDimensionlessVector(_vout);
}

/*
Exceptions
   Error free.
*/
void USpice::vcrss(
    const FSDimensionlessVector& v1,
    const FSDimensionlessVector& v2,
    FSDimensionlessVector& vout
)
{
    // Inputs
    SpiceDouble _v1[3];     v1.CopyTo(_v1);
    SpiceDouble _v2[3];     v2.CopyTo(_v2);
    // Output
    SpiceDouble _vout[3];

    // Invocation
    vcrss_c(_v1, _v2, _vout);

    vout = FSDimensionlessVector(_vout);
}

/*
Exceptions
   Error free.
*/
void USpice::vdist(
    const FSDimensionlessVector& v1,
    const FSDimensionlessVector& v2,
    double& out
)
{
    // Inputs
    SpiceDouble _v1[3];     v1.CopyTo(_v1);
    SpiceDouble _v2[3];     v2.CopyTo(_v2);
    // Output
    SpiceDouble _out;

    // Invocation
    _out = vdist_c(_v1, _v2);

    // Return Value
    out = double(_out);
}


void USpice::vdist_distance(
    const FSDistanceVector& v1,
    const FSDistanceVector& v2,
    FSDistance& out
)
{
    // Inputs
    SpiceDouble _v1[3];     v1.CopyTo(_v1);
    SpiceDouble _v2[3];     v2.CopyTo(_v2);
    // Output
    SpiceDouble _out;

    // Invocation
    _out = vdist_c(_v1, _v2);

    // Return Value
    out = FSDistance(_out);
}
void USpice::vdist_velocity(
    const FSVelocityVector& v1,
    const FSVelocityVector& v2,
    FSSpeed& out
)
{
    // Inputs
    SpiceDouble _v1[3];     v1.CopyTo(_v1);
    SpiceDouble _v2[3];     v2.CopyTo(_v2);
    // Output
    SpiceDouble _out;

    // Invocation
    _out = vdist_c(_v1, _v2);

    // Return Value
    out = FSSpeed(_out);
}


/*
Exceptions
   Error free.
*/
void USpice::vdot(
    const FSDimensionlessVector& v1,
    const FSDimensionlessVector& v2,
    double& out
)
{
    // Inputs
    SpiceDouble _v1[3];     v1.CopyTo(_v1);
    SpiceDouble _v2[3];     v2.CopyTo(_v2);
    // Output
    SpiceDouble _out;

    // Invocation
    _out = vdot_c(_v1, _v2);

    // Return Value
    out = double(out);
}
void USpice::dot_distance(
    const FSDistanceVector& v1,
    const FSDistanceVector& v2,
    FSDistance& out
)
{
    // Inputs
    SpiceDouble _v1[3];     v1.CopyTo(_v1);
    SpiceDouble _v2[3];     v2.CopyTo(_v2);
    // Output
    SpiceDouble _out;

    // Invocation
    _out = vdot_c(_v1, _v2);

    // Return Value
    out = FSDistance(out);
}
void USpice::dot_velocity(
    const FSVelocityVector& v1,
    const FSVelocityVector& v2,
    FSSpeed& out
)
{
    // Inputs
    SpiceDouble _v1[3];     v1.CopyTo(_v1);
    SpiceDouble _v2[3];     v2.CopyTo(_v2);
    // Output
    SpiceDouble _out;

    // Invocation
    _out = vdot_c(_v1, _v2);

    // Return Value
    out = FSSpeed(out);
}


// pointless, in blueprints
/*
Exceptions
   Error free.
*/
void USpice::vequ(
    const FSDimensionlessVector& vin,
    FSDimensionlessVector& vout
)
{
    // Input
    SpiceDouble _vin[3];
    vin.CopyTo(_vin);
    // Output
    SpiceDouble _vout[3]; ZeroOut(_vout);

    // Invocation
    vequ_c(_vin, _vout);

    // Return Value
    vout = FSDimensionlessVector(_vout);
}

void USpice::vequ_distance(
    const FSDistanceVector& vin,
    FSDistanceVector& vout
)
{
    // Input
    SpiceDouble _vin[3];
    vin.CopyTo(_vin);
    // Output
    SpiceDouble _vout[3];

    // Invocation
    vequ_c(_vin, _vout); ZeroOut(_vout);

    // Return Value
    vout = FSDistanceVector(_vout);
}

void USpice::vequ_velocity(
    const FSVelocityVector& vin,
    FSVelocityVector& vout
)
{
    // Input
    SpiceDouble _vin[3];
    vin.CopyTo(_vin);
    // Output
    SpiceDouble _vout[3]; ZeroOut(_vout);

    // Invocation
    vequ_c(_vin, _vout);

    // Return Value
    vout = FSVelocityVector(_vout);
}

void USpice::vequ_angular_velocity(
    const FSAngularVelocity& vin,
    FSAngularVelocity& vout
)
{
    // Input
    SpiceDouble _vin[3];
    vin.CopyTo(_vin);
    // Output
    SpiceDouble _vout[3]; ZeroOut(_vout);

    // Invocation
    vequ_c(_vin, _vout);

    // Return Value
    vout = FSAngularVelocity(_vout);
}


/*
Exceptions
   Error free.

   If v1 represents the zero vector, then vout will also be the zero
   vector.
*/
void USpice::vhat(
    const FSDimensionlessVector& v1,
    FSDimensionlessVector& vout
)
{
    // Input
    SpiceDouble  _v1[3];
    v1.CopyTo(_v1);
    // Output
    SpiceDouble _vout[3];

    // Invocation
    vhat_c(_v1, _vout);

    // Return Value
    vout = FSDimensionlessVector(_vout);
}
void USpice::vhat_distance(
    const FSDistanceVector& v1,
    FSDimensionlessVector& vout
)
{
    // Input
    SpiceDouble  _v1[3];
    v1.CopyTo(_v1);
    // Output
    SpiceDouble _vout[3];

    // Invocation
    vhat_c(_v1, _vout);

    // Return Value
    vout = FSDimensionlessVector(_vout);
}
void USpice::vhat_velocity(
    const FSVelocityVector& v1,
    FSDimensionlessVector& vout
)
{
    // Input
    SpiceDouble  _v1[3];
    v1.CopyTo(_v1);
    // Output
    SpiceDouble _vout[3];

    // Invocation
    vhat_c(_v1, _vout);

    // Return Value
    vout = FSDimensionlessVector(_vout);
}
void USpice::vhat_angular_velocity(
    const FSAngularVelocity& v1,
    FSDimensionlessVector& vout
)
{
    // Input
    SpiceDouble  _v1[3];
    v1.CopyTo(_v1);
    // Output
    SpiceDouble _vout[3];

    // Invocation
    vhat_c(_v1, _vout);

    // Return Value
    vout = FSDimensionlessVector(_vout);
}

/*
Exceptions
   Error free.
*/
void USpice::vlcom3(
    double a,
    const FSDimensionlessVector& v1,
    double b,
    const FSDimensionlessVector& v2,
    double c,
    const FSDimensionlessVector& v3,
    FSDimensionlessVector& sum
)
{
    // Input
    SpiceDouble _a = a;
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    SpiceDouble _b = b;
    SpiceDouble _v2[3]; v2.CopyTo(_v2);
    SpiceDouble _c = c;
    SpiceDouble _v3[3]; v3.CopyTo(_v3);
    // Output
    SpiceDouble _sum[3];

    // Invocation
    vlcom3_c(_a, _v1, _b, _v2, _c, _v3, _sum);

    // Return Value
    sum = FSDimensionlessVector(_sum);
}

void USpice::vlcom3_distance(
    double a,
    const FSDistanceVector& v1,
    double b,
    const FSDistanceVector& v2,
    double c,
    const FSDistanceVector& v3,
    FSDistanceVector& sum
)
{
    // Input
    SpiceDouble _a = a;
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    SpiceDouble _b = b;
    SpiceDouble _v2[3]; v2.CopyTo(_v2);
    SpiceDouble _c = c;
    SpiceDouble _v3[3]; v3.CopyTo(_v3);
    // Output
    SpiceDouble _sum[3];

    // Invocation
    vlcom3_c(_a, _v1, _b, _v2, _c, _v3, _sum);

    // Return Value
    sum = FSDistanceVector(_sum);
}

/*
Exceptions
   Error free.
*/
void USpice::vlcom(
    double a,
    const FSDimensionlessVector& v1,
    double b,
    const FSDimensionlessVector& v2,
    FSDimensionlessVector& sum
)
{
    // Input
    SpiceDouble _a = a;
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    SpiceDouble _b = b;
    SpiceDouble _v2[3]; v2.CopyTo(_v2);
    // Output
    SpiceDouble _sum[3];

    // Invocation
    vlcom_c(_a, _v1, _b, _v2, _sum);

    // Return Value
    sum = FSDimensionlessVector(_sum);
}

void USpice::vlcom_distance(
    double a,
    const FSDistanceVector& v1,
    double b,
    const FSDistanceVector& v2,
    FSDistanceVector& sum
)
{
    // Input
    SpiceDouble _a = a;
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    SpiceDouble _b = b;
    SpiceDouble _v2[3]; v2.CopyTo(_v2);
    // Output
    SpiceDouble _sum[3];

    // Invocation
    vlcom_c(_a, _v1, _b, _v2, _sum);

    // Return Value
    sum = FSDistanceVector(_sum);
}

/*
Exceptions
   Error free.
*/
void USpice::vminus(
    const FSDimensionlessVector& v1,
    FSDimensionlessVector& vout
)
{
    // Input
    SpiceDouble _v1[3];     v1.CopyTo(_v1);
    // Output
    SpiceDouble _vout[3];

    // Invocation
    vminus_c(_v1, _vout);

    // Return Value
    vout = FSDimensionlessVector(_vout);
}

/*
Exceptions
   Error free.
*/
void USpice::vnorm(
    const FSDimensionlessVector& v1,
    double& out
)
{
    // Input
    SpiceDouble _v1[3];     v1.CopyTo(_v1);
    // Output
    SpiceDouble _out;

    // Invocation
    _out = vnorm_c(_v1);

    // Return Value
    out = double(_out);
}

/*
Exceptions
   Error free.
*/
void USpice::vnorm_distance(
    const FSDistanceVector& v1,
    FSDistance& out
)
{
    // Input
    SpiceDouble _v1[3];     v1.CopyTo(_v1);
    // Output
    SpiceDouble _out;

    // Invocation
    _out = vnorm_c(_v1);

    // Return Value
    out = FSDistance(_out);
}

/*
Exceptions
   Error free.
*/
void USpice::vnorm_velocity(
    const FSVelocityVector& v1,
    FSSpeed& out
)
{
    // Input
    SpiceDouble _v1[3];     v1.CopyTo(_v1);
    // Output
    SpiceDouble _out;

    // Invocation
    _out = vnorm_c(_v1);

    // Return Value
    out = FSSpeed(_out);
}


/*
Exceptions
   Error free.
*/
void USpice::vpack(
    double x,
    double y,
    double z,
    FSDimensionlessVector& v
)
{
    // Input
    SpiceDouble _x = x;
    SpiceDouble _y = y;
    SpiceDouble _z = z;
    // Output
    SpiceDouble _v[3];

    // Invocation
    vpack_c(_x, _y, _z, _v);

    // Return Value
    v = FSDimensionlessVector(_v);
}

void USpice::vperp(
    const FSDimensionlessVector& a,
    const FSDimensionlessVector& b,
    FSDimensionlessVector& p
)
{
    // Input
    SpiceDouble _a[3]; a.CopyTo(_a);
    SpiceDouble _b[3]; b.CopyTo(_b);
    // Output
    SpiceDouble _p[3];

    // Invocation
    vperp_c(_a, _b, _p);

    // Return Value
    p = FSDimensionlessVector(_p);
}

/*
Exceptions

   1)  Invalid input planes are diagnosed by the routine pl2nvc_c,
       which is called by this routine.
*/
void USpice::vprjp(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSDimensionlessVector& vin,
    const FSPlane& plane,
    FSDimensionlessVector& vout
)
{
    // Input
    SpiceDouble _vin[3];    vin.CopyTo(_vin);
    SpicePlane  _plane;     CopyTo(plane, _plane);

    // Output
    SpiceDouble _vout[3];

    // Invocation
    vprjp_c(_vin, &_plane, _vout);

    // Return Value
    vout = FSDimensionlessVector(_vout);

    // Error Hanndling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions
   Error free.
*/
void USpice::vproj(
    const FSDimensionlessVector& a,
    const FSDimensionlessVector& b,
    FSDimensionlessVector& p
)
{
    // Input
    SpiceDouble _a[3]; a.CopyTo(_a);
    SpiceDouble _b[3]; b.CopyTo(_b);
    // Output
    SpiceDouble _p[3];

    // Invocation
    vproj_c(_a, _b, _p);

    // Return Value
    p = FSDimensionlessVector(_p);
}

/*
Exceptions
   Error free.

   If both v1 and v2 are zero vectors then vrel_c is defined
   to be zero.
*/
void USpice::vrel(
    const FSDimensionlessVector& v1,
    const FSDimensionlessVector& v2,
    double& out
)
{
    // Input
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    SpiceDouble _v2[3]; v2.CopyTo(_v2);
    // Output
    SpiceDouble _out;

    // Invocation
    _out = vrel_c(_v1, _v2);

    // Return Value
    out = double(_out);
}

/*
Exceptions
   Error free.

   1)  If the input axis is the zero vector r will be returned
       as v.
*/
void USpice::vrotv(
    const FSDimensionlessVector& v,
    const FSDimensionlessVector& axis,
    const FSAngle& theta,
    FSDimensionlessVector& r
)
{
    // Inputs
    SpiceDouble _v[3];      v.CopyTo(_v);
    SpiceDouble _axis[3];   axis.CopyTo(_axis);
    SpiceDouble _theta = theta.AsDouble();
    // Output                
    SpiceDouble _r[3];

    // Invocation
    vrotv_c(_v, _axis, _theta, _r);

    // Return Value
    r = FSDimensionlessVector(_r);
}

/*
Exceptions
   Error free.
*/
void USpice::vscl(
    double s,
    const FSDimensionlessVector& v1,
    FSDimensionlessVector& vout
)
{
    // Inputs
    SpiceDouble _s = s;
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    // Output
    SpiceDouble _vout[3];

    // Invocation
    vscl_c(_s, _v1, _vout);

    // Return Value
    vout = FSDimensionlessVector(_vout);
}

/*
Exceptions
   Error free.
*/
void USpice::vsep(
    const FSDimensionlessVector& v1,
    const FSDimensionlessVector& v2,
    FSAngle& out
)
{
    // Inputs
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    SpiceDouble _v2[3]; v2.CopyTo(_v2);
    // Output
    SpiceDouble _out;

    // Invocation
    _out = vsep_c(_v1, _v2);

    // Return Value
    out = FSAngle(_out);
}

/*
Exceptions
   Error free.
*/
void USpice::vsub(
    const FSDimensionlessVector& v1,
    const FSDimensionlessVector& v2,
    FSDimensionlessVector& vout
)
{
    // Inputs
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    SpiceDouble _v2[3]; v2.CopyTo(_v2);
    // Outputs
    SpiceDouble _vout[3];

    // Invocation
    vsub_c(_v1, _v2, _vout);

    // Return Value
    vout = FSDimensionlessVector(_vout);
}



double  USpice::vtmv(
    const FSDimensionlessVector& v1,
    const FSRotationMatrix& matrix,
    const FSDimensionlessVector& v2
)
{
    // Inputs
    SpiceDouble _v1[3]; v1.CopyTo(_v1);
    SpiceDouble _matrix[3][3];	matrix.CopyTo(_matrix);
    SpiceDouble _v2[3]; v2.CopyTo(_v2);

    return vtmv_c(_v1, _matrix, _v2);
}


/*
Exceptions
   Error free.
*/
void USpice::vupack(
    const FSDimensionlessVector& v,
    double& x,
    double& y,
    double& z
)
{
    // Input
    SpiceDouble _v[3];  v.CopyTo(_v);
    // Outputs
    SpiceDouble _x;
    SpiceDouble _y;
    SpiceDouble _z;

    // Invocation
    vupack_c(_v, &_x, &_y, &_z);

    // Return Values
    x = _x;
    y = _y;
    z = _z;
}


/*
Exceptions
   Error free.
*/
void USpice::vzero(
    const FSDimensionlessVector& v,
    bool& is_zero
)
{
    // Input
    SpiceDouble _v[3];  v.CopyTo(_v);
    // Output
    SpiceBoolean _is_zero;

    // Invocation
    _is_zero = vzero_c(_v);

    // Return Value
    is_zero = _is_zero ? true : false;
}

/*
* Exceptions

   All erroneous inputs are diagnosed by routines in the call
   tree to this routines.  These include

   1)   If any of axisa, axisb, or axisc do not have values in

           { 1, 2, 3 },

        then the error SPICE(INPUTOUTOFRANGE) is signaled.

   2)   An arbitrary rotation matrix cannot be expressed using
        a sequence of Euler angles unless the second rotation axis
        differs from the other two.  If axisb is equal to axisc or
        axisa, then the error SPICE(BADAXISNUMBERS) is signaled.

   3)   If the input matrix r is not a rotation matrix, the error
        SPICE(NOTAROTATION) is signaled.

   4)   If eulang[0] and eulang[2] are not uniquely determined,
        EULANG[0] is set to zero, and EULANG[2] is determined.
*/
void USpice::xf2eul(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    FSEulerAngularState& eulang,
    bool& unique,
    const FSEulerAngularTransform& xform,
    ES_Axis axis3,
    ES_Axis axis2,
    ES_Axis axis1
)
{
    // Inputs
    SpiceDouble		 _xform[6][6];	xform.CopyTo(_xform);
    SpiceInt		_axisa = (SpiceInt)axis3;
    SpiceInt		_axisb = (SpiceInt)axis2;
    SpiceInt		_axisc = (SpiceInt)axis1;
    // Outputs
    SpiceDouble		_eulang[6];		ZeroOut(_eulang);
    SpiceBoolean	_unique = false;

    // Invocation
    xf2eul_c(_xform, _axisa, _axisb, _axisc, _eulang, &_unique);

    // Return Values
    eulang = FSEulerAngularState(_eulang, _axisa, _axisb, _axisc);
    unique = _unique ? true : false;

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions

   Error free.

   1) No checks are performed on xform to ensure that it is indeed
      a state transformation matrix.
*/
void USpice::xf2rav(
    const FSStateTransform& xform,
    FSRotationMatrix& rot,
    FSAngularVelocity& av
)
{
    // Input
    SpiceDouble _xform[6][6];   xform.CopyTo(_xform);
    // Outputs
    SpiceDouble _rot[3][3];
    SpiceDouble _av[3];

    // Invocation
    xf2rav_c(_xform, _rot, _av);

    // Return Values
    rot = FSRotationMatrix(_rot);
    av = FSAngularVelocity(_av);
}


ConstSpiceChar* CoordsToStr(ES_CoordinateSystem coords)
{
    switch (coords)
    {
    case ES_CoordinateSystem::RECTANGULAR:
        return "RECTANGULAR";
    case ES_CoordinateSystem::CYLINDRICAL:
        return "CYLINDRICAL";
    case ES_CoordinateSystem::LATITUDINAL:
        return "LATITUDINAL";
    case ES_CoordinateSystem::SPHERICAL:
        return "SPHERICAL";
    case ES_CoordinateSystem::GEODETIC:
        return "GEODETIC";
    case ES_CoordinateSystem::PLANETOGRAPHIC:
        return "PLANETOGRAPHIC";
    }

    return "NONE";
}


/*
Exceptions
   1)  If either the input or output coordinate system is not
       recognized, the error SPICE(COORDSYSNOTREC) is signaled.

   2)  If the input body name cannot be converted to a NAIF ID
       (applies to geodetic and planetographic coordinate
       systems), the error 'SPICE(IDCODENOTFOUND)' is signaled.

   3)  If the input state `input_state' is not valid, meaning the position
       but not the velocity is along the z-axis, the error
       'SPICE(INVALIDSTATE)' is signaled.

       Note: If both the input position and velocity are along
       the z-axis and the output coordinate system is not
       rectangular, the velocity can still be calculated even
       though the Jacobian is undefined. This case will not
       signal an error. An example of the input position and
       velocity along the z-axis is below.

                     Term    Value
                     -----   ------
                       x       0
                       y       0
                       z       z
                     dx/dt     0
                     dy/dt     0
                     dz/dt   dz_dt

   4)  If either the input or output coordinate system is
       geodetic or planetographic and at least one of the body's
       radii is less than or equal to zero, the error
       SPICE(INVALIDRADIUS) will be signaled.

   5)  If either the input or output coordinate system is
       geodetic or planetographic and the difference of the
       equatorial and polar radii divided by the equatorial radius
       would produce numeric overflow, the error
       'SPICE(INVALIDRADIUS)' will be signaled.

   6)  If the product of the Jacobian and velocity components
       may lead to numeric overflow, the error 'SPICE(NUMERICOVERFLOW)'
       is signaled.

   7)  If body's equatorial radii are not equal and either the
       input or output coordinate system is geodetic or
       planetographic, the error 'SPICE(NOTSUPPORTED)' is signaled.
*/
void USpice::xfmsta(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    const FSDimensionlessVector& in1,
    const FSDimensionlessVector& in2,
    FSDimensionlessVector& out1,
    FSDimensionlessVector& out2,
    ES_CoordinateSystem input_coord_sys,
    ES_CoordinateSystem output_coord_sys,
    const FString& body
)
{
    // Inputs
    SpiceDouble     _input_state[6];
    _input_state[0] = in1.x;
    _input_state[1] = in1.y;
    _input_state[2] = in1.z;
    _input_state[3] = in2.x;
    _input_state[4] = in2.y;
    _input_state[5] = in2.z;
    ConstSpiceChar* _input_coord_sys = CoordsToStr(input_coord_sys);
    ConstSpiceChar* _output_coord_sys = CoordsToStr(output_coord_sys);
    ConstSpiceChar* _body = TCHAR_TO_ANSI(*body);
    // Output
    SpiceDouble _output_state[6];       ZeroOut(_output_state);

    // Invocation
    xfmsta_c(_input_state, _input_coord_sys, _output_coord_sys, _body, _output_state);

    // Return Value
    out1 = FSDimensionlessVector(_output_state[0], _output_state[1], _output_state[2]);
    out2 = FSDimensionlessVector(_output_state[3], _output_state[4], _output_state[5]);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

/*
Exceptions
   Error free.
*/
void USpice::xpose(
    const FSRotationMatrix& m1,
    FSRotationMatrix& mout
)
{
    // Input
    SpiceDouble _m1[3][3];
    m1.CopyTo(_m1);

    // Output
    SpiceDouble _mout[3][3];

    // Invocation
    xpose_c(_m1, _mout);

    // Return Value
    mout = FSRotationMatrix(_mout);
}
