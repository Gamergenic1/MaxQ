// Copyright 2021 Gamergenic.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this
// software and associated documentation files (the "Software"), to deal in the Software
// without restriction, including without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

#pragma once

#include "CoreMinimal.h"
#include "SpiceTypes.h"
#include "Spice.generated.h"

#pragma once

DECLARE_DYNAMIC_DELEGATE_TwoParams(FDerivativeDelegate, double, et, double&, value);

UCLASS(BlueprintType, Blueprintable)
class SPICE_API USpice : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    // No scaling... Swizzle only!
    static void SwizzleToUE(const double(&v)[3], FVector& ue);
    static void SwizzleToSpice(const FVector& ue, double(&v)[3]);
    static void SwizzleToUE(const double(&q)[4], FQuat& ue);
    static void SwizzleToSpice(const FQuat& ue, double(&q)[4]);

public:
    USpice();

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ToolTip = "List files at given relative directory"
            ))
    static void enumerate_kernels(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        TArray<FString>& kernelFileRelativePaths,
        const FString& relativeDirectory = TEXT("Content/Spice/Kernels/Core")
        );

    UFUNCTION(BlueprintCallable, Exec,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ToolTip = "Load a kernel file (relative path)"
            ))
    static void furnsh(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& relativePath
    );

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ToolTip = "Load a list of kernel files (relative paths)"
            ))
    static void furnsh_list(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const TArray<FString>& relativePaths
    );

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ToolTip = "Join a path to a list of paths"
            ))
    static void combine_paths(
        const FString& basePath,
        const TArray<FString>& relativePaths,
        TArray<FString>& joinedPaths
    );

    UFUNCTION(BlueprintCallable, Exec,
        Category = "Spice|Api|Data",
        meta = (
            ToolTip = "Clear all kernel file / kernel pool"
            ))
    static void clear_all();

    UFUNCTION(BlueprintCallable, Exec,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ToolTip = "Clear unload kernel file"
            ))
    static void unload(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& absolutePath
    );

    UFUNCTION(BlueprintCallable, Exec,
        Category = "Spice|Api|Control",
        meta = (
            ToolTip = "reset/init cspice"
            ))
    static void init_all();

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Error Handling",
        meta = (
            ToolTip = "Get Default Error Action"
            ))
    static void get_erract(ES_ErrorAction& Result);

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Error Handling",
        meta = (
            ToolTip = "Get Error Output Device Name"
            ))
    static void get_errdev(ES_ErrorDevice& device);

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Error Handling",
        meta = (
            ToolTip = "Get Error Output Items"
            ))
    static void get_errprt(FString& OutMessage);

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Error Handling",
        meta = (
            ToolTip = "Set Default Error Action"
            ))
    static void set_erract(ES_ErrorAction actionToSet);

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Error Handling",
        meta = (
            ToolTip = "Set Error Output Device Name"
            ))
    static void set_errdev(ES_ErrorDevice Device, const FString& LogFilePath);

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Error Handling",
        meta = (ToolTip = "Set Error Output Items"
            ))
    static void set_errprt(ES_Items items);

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Error Handling",
        meta = (
            ToolTip = "Reset Error Status"
            ))
    static void reset();

    /// <summary>Construct a rotation matrix that rotates vectors by a specified angle about a specified axis</summary>
    /// <param name="axis">[in] Rotation axis</param>
    /// <param name="angle">[in] Rotation angle, in radians</param>
    /// <param name="r">[out] Rotation matrix corresponding to axis and angle</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Axis and angle to rotation",
            ToolTip = "Construct a rotation matrix that rotates vectors by a specified angle about a specified axis"
            ))
    static void axisar(
        const FSDimensionlessVector& axis,
        const FSAngle& angle,
        FSRotationMatrix& r
    );

    /// <summary>Body name to ID code translation</summary>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "found",
            ToolTip = "Determine whether values exist for some item for any body in the kernel pool"
            ))
    static void bodfnd(
        ES_FoundCode& found,
        int64 body = 399,
        const FString& item = TEXT("RADAII")
    );

    /// <summary>Body name to ID code translation</summary>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "found",
            ToolTip = "Translate the SPICE integer code of a body into a common name for that body"
            ))
    static void bodc2n(
        ES_FoundCode& found,
        int64 code,
        FString& name
    );

    /// <summary>Body name to ID code translation</summary>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "found",
            ShortToolTip = "Body name to ID code translation",
            ToolTip = "Translate the name of a body or object to the corresponding SPICE integer ID code"
            ))
    static void bodn2c(
        ES_FoundCode& found,
        int64& code,
        const FString& name = TEXT("EARTH")
    );

    /// <summary>Fetch from the kernel pool the double precision values of an item associated with a body</summary>
    /// <param name="bodyid">[in] Body ID code</param>
    /// <param name="item">[in] Item for which values are desired. ("RADII", "NUT_PREC_ANGLES", etc. )</param>
    /// <param name="maxn">[in] Maximum number of values that may be returned</param>
    /// <param name="dim">[out] Number of values returned</param>
    /// <param name="values">[out] Values</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Return d.p. values from the kernel pool",
            ToolTip = "(double) Fetch from the kernel pool the double precision values of an item associated with a body, where the body is specified by an integer ID code"
            ))
    static void bodvcd_scalar(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        double& ReturnValue,
        int64 bodyid = 399,
        const FString& item = TEXT("RADII")
    );

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Return d.p. values from the kernel pool",
            ToolTip = "(double vector3) Fetch from the kernel pool the double precision values of an item associated with a body, where the body is specified by an integer ID code"
            ))
    static void bodvcd_vector(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        FSDimensionlessVector& ReturnValue,
        int64 bodyid = 399,
        const FString& item = TEXT("RADII")
    );

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Return d.p. values from the kernel pool",
            ToolTip = "(double) Fetch from the kernel pool the double precision values of an item associated with a body, where the body is specified by an integer ID code"
            ))
    static void bodvcd_mass(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        FSMassConstant& ReturnValue,
        int64 bodyid = 399,
        const FString& item = TEXT("GM")
    );

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Return d.p. values from the kernel pool",
            ToolTip = "(double) Fetch from the kernel pool the double precision values of an item associated with a body, where the body is specified by an integer ID code"
            ))
    static void bodvcd_distance_vector(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        FSDistanceVector& ReturnValue,
        int64 bodyid = 399,
        const FString& item = TEXT("GM")
    );

    /// <summary>Fetch from the kernel pool the double precision values of an item associated with a body</summary>
    /// <param name="bodynm">[in] Body name</param>
    /// <param name="item">[in] Item for which values are desired. ("RADII", "NUT_PREC_ANGLES", etc. )</param>
    /// <param name="maxn">[in] Maximum number of values that may be returned</param>
    /// <param name="dim">[out] Number of values returned</param>
    /// <param name="values">[out] Values</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Return d.p. values from the kernel pool",
            ToolTip = "(double) Fetch from the kernel pool the double precision values of an item associated with a body"
            ))
    static void bodvrd_scalar(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        double& ReturnValue,
        const FString& bodynm = TEXT("EARTH"),
        const FString& item = TEXT("RADII")
    );

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Return d.p. values from the kernel pool",
            ToolTip = "(double vector3) Fetch from the kernel pool the double precision values of an item associated with a body"
            ))
    static void bodvrd_vector(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        FSDimensionlessVector& ReturnValue,
        const FString& bodynm = TEXT("EARTH"),
        const FString& item = TEXT("RADII")
    );

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Return d.p. values from the kernel pool",
            ToolTip = "(double) Fetch from the kernel pool the double precision values of an item associated with a body"
            ))
    static void bodvrd_mass(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        FSMassConstant& ReturnValue,
        const FString& bodynm = TEXT("EARTH"),
        const FString& item = TEXT("GM")
    );
    
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Return d.p. values from the kernel pool",
            ToolTip = "(double) Fetch from the kernel pool the double precision values of an item associated with a body"
            ))
    static void bodvrd_distance_vector(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        FSDistanceVector& ReturnValue,
        const FString& bodynm = TEXT("EARTH"),
        const FString& item = TEXT("RADII")
    );

    
    /// <summary>CK, Close file</summary>
    /// <param name="handle">[in] Handle of the CK file to be closed</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Center and generating vectors to ellipse",
            ToolTip = "Form a CSPICE ellipse from a center vector and two generating vectors"
            ))
    static void cgv2el(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FSDistanceVector& center,
        const FSDistanceVector& vec1,
        const FSDistanceVector& vec2,
        FSEllipse& ellipse
    );


    /// <summary>CK, Close file</summary>
    /// <param name="handle">[in] Handle of the CK file to be closed</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Pointing",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "CK, Close file",
            ToolTip = "Close an open CK file"
            ))
    static void ckcls(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        int64 handle
    );

    /// <summary>Find the coverage window for a specified object in a specified CK file</summary>
    /// <param name="ck">[in] Name of CK file</param>
    /// <param name="idcode">[in] ID code of object</param>
    /// <param name="needav">[in] Flag indicating whether angular velocity is needed</param>
    /// <param name="level">[in] Coverage level:  "SEGMENT" OR "INTERVAL"</param>
    /// <param name="tol">[in] Tolerance in ticks</param>
    /// <param name="timsys">[in] Time system used to represent coverage</param>
    /// <param name="cover">[out] Window giving coverage for `idcode'</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Pointing",
        meta = (
            AutoCreateRefTerm = "merge_to",
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "CK coverage",
            ToolTip = "Find the coverage window for a specified object in a specified CK file"
            ))
    static void ckcov(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        UPARAM(meta = (DisplayName = "project-relative file path")) const FString& ck_relative_path,
        int64 idcode,
        bool need_av,
        double tol,
        UPARAM(meta = (DisplayName = "(optional) existing window to merge results with")) const TArray<FSWindowSegment>& merge_to,
        TArray<FSWindowSegment>& coverage,
        ES_CoverageLevel level = ES_CoverageLevel::Interval,
        ES_TimeSystem    timsys = ES_TimeSystem::SCLK
    );


    /// <summary>C-kernel, get pointing</summary>
    /// <param name="inst">[in] NAIF ID of instrument, spacecraft, or structure</param>
    /// <param name="sclkdp">[in] Encoded spacecraft clock time</param>
    /// <param name="tol">[in] Time tolerance</param>
    /// <param name="ref">[in] Reference frame</param>
    /// <param name="cmat">[out] C-matrix pointing data</param>
    /// <param name="clkout">[out] Output encoded spacecraft clock time</param>
    /// <param name="found">[out] True when requested pointing is available</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Pointing",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "C-kernel, get pointing",
            ToolTip = "Get pointing (attitude) for a specified spacecraft clock time"
            ))
    static void ckgp(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        int64 inst,
        double sclkdp,
        double tol,
        const FString& ref,
        FSRotationMatrix& cmat,
        double& clkout,
        bool& found
    );

    /// <summary>C-kernel, get pointing and angular velocity</summary>
    /// <param name="inst">[in] NAIF ID of instrument, spacecraft, or structure</param>
    /// <param name="sclkdp">[in] Encoded spacecraft clock time</param>
    /// <param name="tol">[in] Time tolerance</param>
    /// <param name="ref">[in] Reference frame</param>
    /// <param name="cmat">[in] C-matrix pointing data</param>
    /// <param name="av">[in] Angular velocity vector</param>
    /// <param name="clkout">[out] Output encoded spacecraft clock time</param>
    /// <param name="found">[out] True when requested pointing is available</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Pointing",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "C-kernel, get pointing and angular velocity",
            ToolTip = "Get pointing (attitude) and angular velocity for a specified spacecraft clock time"
            ))
    static void ckgpav(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        int64 inst,
        double sclkdp,
        double tol,
        const FString& ref,
        FSRotationMatrix& cmat,
        FSAngularVelocity& av,
        double& clkout,
        bool& found
    );


    /// <summary>C-kernel, load pointing file</summary>
    /// <param name="filename">[in] Name of the CK file to be loaded</param>
    /// <param name="handle">[out] Loaded file's handle</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Pointing",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "C-kernel, load pointing file",
            ToolTip = "Load a CK pointing file for use by the CK readers"
            ))
    static void cklpf(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        UPARAM(meta = (DisplayName = "project-relative file path")) const FString& ck_relative_path,
        int64& handle
    );

    /// <summary>CK objects</summary>
    /// <param name="ck">[in] Name of CK file</param>
    /// <param name="ids">[in/out] Set of ID codes of objects in CK file</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Pointing",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "CK objects",
            ToolTip = "Find the set of ID codes of all objects in a specified CK file"
            ))
    static void ckobj(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        UPARAM(meta = (DisplayName = "project-relative file path")) const FString& relative_path,
        TArray<int64>& ids
    );

    /// <summary>CK, open new file</summary>
    /// <param name="fname">[in] The name of the CK file to be opened</param>
    /// <param name="ifname">[in] The internal filename for the CK</param>
    /// <param name="ncomch">[in] The number of characters to reserve for comments</param>
    /// <param name="handle">[out] The handle of the opened CK file</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Pointing",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "CK, open new file",
            ToolTip = "Open a new CK file, returning the handle of the opened file"
            ))
    static void ckopn(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        UPARAM(meta = (DisplayName = "project-relative file path")) const FString& relativePath,
        UPARAM(meta = (DisplayName = "internal filename")) const FString& ifname,
        UPARAM(meta = (DisplayName = "number of characters to reserve for comments")) const int ncomch,
        int64& handle
    );

    /// <summary>C-kernel, Unload pointing file</summary>
    /// <param name="handle">[in] Handle of CK file to be unloaded</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Pointing",
        meta = (
            ShortToolTip = "C-kernel, Unload pointing file",
            ToolTip = "Unload a CK pointing file so that it will no longer be searched by the readers"
            ))
    static void ckupf(
        int64 handle
    );

    /// <summary>C-Kernel, write segment to C-kernel, data type 1</summary>
    /// <param name="handle">[in] Handle of an open CK file</param>
    /// <param name="begtim">[in] The beginning encoded SCLK of the segment</param>
    /// <param name="endtim">[in] The ending encoded SCLK of the segment</param>
    /// <param name="inst">[in] The NAIF instrument ID code</param>
    /// <param name="ref">[in]  The reference frame of the segment</param>
    /// <param name="avflag">[in] True if the segment will contain angular velocity</param>
    /// <param name="segid">[in] Segment identifier</param>
    /// <param name="nrec">[in] Number of pointing records</param>
    /// <param name="sclkdp">[in] Encoded SCLK times</param>
    /// <param name="quats">[in] Quaternions representing instrument pointing</param>
    /// <param name="avvs">[in] Angular velocity vectors</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Pointing",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "C-Kernel, write segment to C-kernel, data type 1",
            ToolTip = "Add a type 1 segment to a C-kernel"
            ))
    static void ckw01(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        int64 handle,
        double begtim,
        double endtim,
        int64 inst,
        const FString& ref,
        bool        avflag,
        const FString& segid,
        const TArray<FSPointingType1Observation>& records
    );


    /// <summary>C-Kernel, write segment to C-kernel, data type 2</summary>
    /// <param name="handle">[in] Handle of an open CK file</param>
    /// <param name="begtim">[in] The beginning encoded SCLK of the segment</param>
    /// <param name="endtim">[in] The ending encoded SCLK of the segment</param>
    /// <param name="inst">[in] The NAIF instrument ID code</param>
    /// <param name="ref">[in] The reference frame of the segment</param>
    /// <param name="segid">[in] Segment identifier</param>
    /// <param name="nrec">[in] Number of pointing records</param>
    /// <param name="start">[in] Encoded SCLK interval start times</param>
    /// <param name="stop">[in] Encoded SCLK interval stop times</param>
    /// <param name="quats">[in] Quaternions representing instrument pointing</param>
    /// <param name="avvs">[in] Angular velocity vectors</param>
    /// <param name="rates">[in] Number of seconds per tick for each interval</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Pointing",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "C-Kernel, write segment to C-kernel, data type 2",
            ToolTip = "Write a type 2 segment to a C-kernel"
            ))
    static void ckw02(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        int64 handle,
        double begtim,
        double endtim,
        int64 inst,
        const FString& ref,
        const FString& segid,
        const TArray<FSPointingType2Observation>& records
    );

    /// <summary>C-Kernel, write segment to C-kernel, data type 3</summary>
    /// <param name="handle">[in] Handle of an open CK file</param>
    /// <param name="begtim">[in] The beginning encoded SCLK of the segment</param>
    /// <param name="endtim">[in] The ending encoded SCLK of the segment</param>
    /// <param name="inst">[in] The NAIF instrument ID code</param>
    /// <param name="ref">[in] The reference frame of the segment</param>
    /// <param name="avflag">[in] True if the segment will contain angular velocity</param>
    /// <param name="segid">[in] Segment identifier</param>
    /// <param name="nrec">[in] Number of pointing records</param>
    /// <param name="sclkdp">[in] Encoded SCLK times</param>
    /// <param name="quats">[in] Quaternions representing instrument pointing</param>
    /// <param name="avvs">[in] Angular velocity vectors</param>
    /// <param name="nints">[in] Number of intervals</param>
    /// <param name="starts">[in] Encoded SCLK interval start times</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Pointing",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "C-Kernel, write segment to C-kernel, data type 3",
            ToolTip = "Add a type 3 segment to a C-kernel"
            ))
    static void ckw03(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        int64 handle,
        double begtim,
        double endtim,
        int64 inst,
        const FString& ref,
        bool        avflag,
        const FString& segid,
        const TArray<FSPointingType1Observation>& records,
        const TArray<double>& starts
    );


    /// <summary>Write CK segment, type 5</summary>
    /// <param name="handle">[in] Handle of an open CK file</param>
    /// <param name="subtyp">[in] CK type 5 subtype code</param>
    /// <param name="degree">[in] Degree of interpolating polynomials</param>
    /// <param name="begtim">[in] The beginning encoded SCLK of the segment</param>
    /// <param name="endtim">[in] The ending encoded SCLK of the segment</param>
    /// <param name="inst">[in] The NAIF instrument ID code</param>
    /// <param name="ref">[in] The reference frame of the segment</param>
    /// <param name="avflag">[in] True if the segment will contain angular velocity</param>
    /// <param name="segid">[in] Segment identifier</param>
    /// <param name="n">[in] Number of packets</param>
    /// <param name="sclkdp">[in] Encoded SCLK times</param>
    /// <param name="packts">[in] Array of packets</param>
    /// <param name="rate">[in] Nominal SCLK rate in seconds per tick</param>
    /// <param name="nints">[in] Number of intervals</param>
    /// <param name="starts">[in] Encoded SCLK interval start times</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Pointing",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Write CK segment, type 5",
            ToolTip = "Write a type 5 segment to a CK file"
            ))
    static void ckw05(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        int64 handle,
        ES_CK05Subtype      subtyp,
        int                 degree,
        double begtim,
        double endtim,
        int64 inst,
        const FString& ref,
        bool  avflag,
        const FString& segid,
        const TArray<FSPointingType5Observation>& records,
        double rate,
        const TArray<double>& starts
    );

    /// <summary>Return the speed of light in a vacuum (IAU official value, in km / sec)</summary>
    /// <returns>The function returns the IAU official value for the speed of light in vacuo : 299792.458 km / sec</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "C, Speed of light in a vacuum",
            ToolTip = "Return the speed of light in a vacuum (IAU official value, in km / sec)"
            ))
        static void clight(FSSpeed& c);

    /**
      Determine the state (position, velocity) of an orbiting body
      from a set of elliptic, hyperbolic, or parabolic orbital
      elements.  See:
       https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/conics_c.html
       Google: cspice conics_c
      */
    UFUNCTION(
        BlueprintCallable,
        Category = "Spice|Api|Conics",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Determine state from conic elements",
            ToolTip = "Determine the state (position, velocity) of an orbiting body from a set of elliptic, hyperbolic, or parabolic orbital elements"
            ))
    static void conics(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FSConicElements& elts,
        const FSEphemerisTime& et,
        FSStateVector& state
    );

    /// <summary>Take a measurement X, the units associated with X, and units to which X should be converted; return Y-- -the value of the measurement in the output units.  Google cspice+convrt for units</summary>
    /// <param name="x">[in] Number representing a measurement in some units</param>
    /// <param name="in">[in] The units in which x is measured</param>
    /// <param name="out">[in] Desired units for the measurement</param>
    /// <param name="y">[out] The measurment in the desired units</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintCallable,
        Category = "Spice|Api|Utility",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ToolTip = "Convert Units"
            ))
    static void convrt(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        double in_value,
        ES_Units            in,
        ES_Units            out,
        double& out_value
    );

    /// <summary>DAF add comments</summary>
    /// <param name="handle">[in] handle of a DAF opened with write access</param>
    /// <param name="n">[in] Number of comments to put into the comment area</param>
    /// <param name="lenvals">[in] Length of elements</param>
    /// <param name="buffer">[in] Buffer of comments to put into the comment area</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintCallable,
        Category = "Spice|Api|DAF",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "DAF add comments",
            ToolTip = "Add comments from a buffer of character strings to the comment area of a binary DAF file, appending them to any comments which are already present in the file's comment area"
            ))
    static void dafac(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        int64 handle,                       // Todo, make a blue printable abstraction instead of handles!
        const TArray<FString>& comments
    );

    /// <summary>DAF, close</summary>
    /// <param name="handle">[in] Handle of DAF to be closed</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintCallable,
        Category = "Spice|Api|DAF",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "DAF, close",
            ToolTip = "Close the DAF associated with a given handle"
            ))
        static void dafcls(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            int64 handle
        );

    /// <summary>DAF extract comments</summary>
    /// <param name="handle">[in] Handle of binary DAF opened with read access</param>
    /// <param name="bufsiz">[in] Maximum size, in lines, of buffer</param>
    /// <param name="lenout">[in] Length of strings in output buffer</param>
    /// <param name="n">[out] Number of extracted comment lines</param>
    /// <param name="buffer">[out] Buffer where extracted comment lines are placed</param>
    /// <param name="done">[out] Indicates whether all comments have been extracted</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintCallable,
        Category = "Spice|Api|DAF",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Extract comments from the comment area of a binary DAF",
            ToolTip = "Close the DAF associated with a given handle"
            ))
        static void dafec(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            int64 handle,
            TArray<FString>& comments
        );

    /// <summary>DAF, open for read</summary>
    /// <param name="fname">[in] Name of DAF to be opened</param>
    /// <param name="handle">[in] Handle assigned to DAF</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintCallable,
        Category = "Spice|Api|DAF",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "DAF, open for read",
            ToolTip = ""
            ))
        static void dafopr(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FString& relativePath,
            int64& handle
        );

    /// <summary>DAF, open for write</summary>
    /// <param name="fname">[in] Name of DAF to be opened</param>
    /// <param name="handle">[in] Handle assigned to DAF</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintCallable,
        Category = "Spice|Api|DAF",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "DAF, open for write",
            ToolTip = ""
            ))
    static void dafopw(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& relativePath,
        int64& handle
    );

    /// <summary>Return the value of Delta ET (ET-UTC) for an input epoch</summary>
    /// <param name="epoch">[in] Input epoch (seconds past J2000)</param>
    /// <param name="eptype">[in] Type of input epoch ("UTC" or "ET")</param>
    /// <param name="delta">[out] Delta ET (ET-UTC) at input epoch</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintCallable,
        Category = "Spice|Api|Utility",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Delta ET, ET - UTC",
            ToolTip = "Return the value of Delta ET (ET-UTC) for an input epoch"
            ))
    static void deltet(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FSEphemerisTime& epoch,
        ES_EpochType            eptype,
        FSEphemerisPeriod& delta
    );

    /// <summary>Compute the determinant of a double precision 3x3 matrix</summary>
    /// <param name="m1">Matrix whose determinant is to be found</param>
    /// <returns>the value of the determinant found by direct application of the definition of the determinan</returns>
    UFUNCTION(
        BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Determinant of a double precision 3x3 matrix",
            ToolTip = "Compute the determinant of a double precision 3x3 matrix"
            ))
    static void det(const FSRotationMatrix& m1, double& ReturnValue);

    /// <summary>Return the value of the largest (positive) number representable in a double precision variable</summary>
    /// <returns>largest (positive) number that can be represented in a double precision variable</returns>
    UFUNCTION(
        BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Largest DP number",
            ToolTip = "Return the value of the largest (positive) number representable in a double precision variable"
            ))
    static void dpmax(double& doublePrecisionMax);

    /// <summary>Return the value of the smallest (negative) number representable in a double precision variable</summary>
    /// <returns>smallest (negative) number that can be represented in a double precision variable</returns>
    UFUNCTION(
        BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Smallest DP number",
            ToolTip = "Return the value of the smallest (negative) number representable in a double precision variable"
            ))
    static void dpmin(double& doublePrecisionMin);

    /// <summary>Return the number of degrees per radian</summary>
    /// <returns>The value of pi is determined by the ACOS function</returns>
    UFUNCTION(
        BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Degrees per radian",
            ToolTip = "Return the number of degrees per radian"
            ))
    static void dpr(double& degreesPerRadian);

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/eqncpv_c.html
    /// <summary>Compute the state (position and velocity of an object whose trajectory is described via equinoctial elements relative to some fixed plane(usually the equatorial plane of some planet) </summary>
    /// <param name="et">Epoch in seconds past J2000 to find state</param>
    /// <param name="epoch">Epoch of elements in seconds past J2000</param>
    /// <param name="eqel">Array of equinoctial elements</param>
    /// <param name="rapol">Right Ascension of the pole of the reference plane</param>
    /// <param name="decpol">Declination of the pole of the reference plane</param>
    /// <param name="state">State of the object described by eqel</param>
    /// <returns></returns>
    /// 
    UFUNCTION(
        BlueprintPure,
        Category = "Spice|Api|State",
        meta = (
            ShortToolTip = "Equinoctial Elements to position and velocity",
            ToolTip = "Compute the state (position and velocity of an object whose trajectory is described via equinoctial elements relative to some fixed plane(usually the equatorial plane of some planet)"
            ))
    static void eqncpv(
        const FSEphemerisTime& et,
        const FSEphemerisTime& epoch,
        const FSEquinoctialElements& eqel,
        const FSAngle& rapol,
        const FSAngle& decpol,
        FSStateVector& state
    );


    /// <summary>Given an ephemeris epoch, compute the local solar time for an object on the surface of a body at a specified longitude</summary>
    /// <param name="et">[in] Epoch in seconds past J2000 epoch</param>
    /// <param name="body">[in] ID-code of the body of interest</param>
    /// <param name="lon">[in] Longitude of surface point (RADIANS)</param>
    /// <param name="type">[in] Type of longitude "PLANETOCENTRIC", etc</param>
    /// <param name="timlen">[in] Available room in output time string</param>
    /// <param name="ampmlen">[in] Available room in output `ampm' string</param>
    /// <param name="hr">[out] Local hour on a "24 hour" clock</param>
    /// <param name="mn">[out] Minutes past the hour</param>
    /// <param name="sc">[out] Seconds past the minute</param>
    /// <param name="time">[out] String giving local time on 24 hour clock</param>
    /// <param name="ampm">[out] String giving time on A.M./ P.M. scale</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintCallable,
        Category = "Spice|Api|State",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "ET to Local Solar Time",
            ToolTip = "Given an ephemeris epoch, compute the local solar time for an object on the surface of a body at a specified longitude"
            ))
    static void et2lst(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FSEphemerisTime& et,
        int64 body,
        const FSAngle& lon,
        ES_LongitudeType type,
        int& hr,
        int& mn,
        int& sc,
        FString& time,
        FString& ampm
    );


    /// <summary>Convert an input time from ephemeris seconds past J2000 to Calendar, Day - of - Year, or Julian Date format, UTC</summary>
    /// <param name="et">[in] Input epoch, given in ephemeris seconds past J2000</param>
    /// <param name="format">[in] Format of output epoch</param>
    /// <param name="prec">[in] Digits of precision in fractional seconds or days</param>
    /// <param name="lenout">[in] The length of the output string plus 1</param>
    /// <param name="utcstr">[out] Output time string, UTC</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintCallable,
        Category = "Spice|Api|Time",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Ephemeris Time to UTC",
            ToolTip = "Convert an input time from ephemeris seconds past J2000 to Calendar, Day - of - Year, or Julian Date format, UTC"
            ))
    static void et2utc(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FSEphemerisTime& et,
        ES_UTCTimeFormat format,
        int          prec,
        FString& utcstr
    );


    /// <summary>Convert ET to Calendar format</summary>
    /// <param name="et">Equivalent UTC seconds past J2000</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Time",
        meta = (
            ShortToolTip = "Convert ET to Calendar format",
            ToolTip = "Convert from an ephemeris epoch measured in seconds past the epoch of J2000 to a calendar string format using a formal calendar free of leapseconds"
            ))
    static void etcal(const FSEphemerisTime& et, FString& ReturnValue);

    /// <summary>Construct a rotation matrix from a set of Euler angles</summary>
    /// <param name="angle3, angle2, angle1">[in] Rotation angles about third, second, and first rotation axes(radians)</param>
    /// <param name="axis3, axis2, axis1">[in] Axis numbers of third, second, and first rotation axes</param>
    /// <param name="o">Product of the 3 rotations</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Euler angles to matrix",
            ToolTip = "Construct a rotation matrix from a set of Euler angles"
            ))
    static void eul2m(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        FSRotationMatrix& r,
        const FSAngle& angle3,
        const FSAngle& angle2,
        const FSAngle& angle1,
        ES_Axis axis3 = ES_Axis::X,
        ES_Axis axis2 = ES_Axis::Y,
        ES_Axis axis1 = ES_Axis::Z
    );

    /// <summary>This routine computes a state transformation from an Euler angle factorization of a rotationand the derivatives of those Euler angles</summary>
    /// <param name="eulang">An array of Euler angles and their derivatives</param>
    /// <param name="axisa">Axis A of the Euler angle factorization</param>
    /// <param name="axisb">Axis B of the Euler angle factorization</param>
    /// <param name="axisc">Axis C of the Euler angle factorization</param>
    /// <param name="xform">A state transformation matrix</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Euler angles and derivative to transformation",
            ToolTip = "computes a state transformation from an Euler angle factorization of a rotation and the derivatives of those Euler angles"
            ))
    static void eul2xf(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FSEulerAngularState& eulang,
        FSEulerAngularTransform& xform
    );

    /// <summary>Given a vector x, this routine builds a right handed orthonormal frame x, y, z where the output x is parallel to the input x</summary>
    /// <param name="x">[in/out]Input vector. A parallel unit vector on output</param>
    /// <param name="y">[out]Unit vector in the plane orthogonal to x</param>
    /// <param name="z">[out]Unit vector given by x X y</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Build a right handed coordinate frame",
            ToolTip = "Given a vector x, this routine builds a right handed orthonormal frame x, y, z where the output x is parallel to the input x"
            ))
    static void frame(
        const FSDimensionlessVector& x_in,
        FSDimensionlessVector& x,
        FSDimensionlessVector& y,
        FSDimensionlessVector& z
    );

    /// <summary>Get character data from the kernel pool</summary>
    /// <param name="name">[in] Name of the variable whose value is to be returned</param>
    /// <param name="start">[in] Which component to start retrieving for name</param>
    /// <param name="room">[in] The largest number of values to return</param>
    /// <param name="lenout">[in] The length of the output string</param>
    /// <param name="n">[out] Number of values returned for name</param>
    /// <param name="cvals">[out] Values associated with name</param>
    /// <param name="found">[out] True if variable is in pool</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Get character data from the kernel pool",
            ToolTip = "Return the character value of a kernel variable from the kernel pool"
            ))
    static void gcpool(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        TArray<FString>& cvals,
        bool& found,
        const FString& name = TEXT("PATH_VALUES"),
        int                 start = 0,
        int                 room = 1
    );

    /// <summary>Get d.p. values from the kernel pool</summary>
    /// <param name="name">[in] Name of the variable whose value is to be returned</param>
    /// <param name="start">[in] Which component to start retrieving for name</param>
    /// <param name="room">[in] The largest number of values to return</param>
    /// <param name="n">[out] Number of values returned for name</param>
    /// <param name="values">[out] Values associated with name</param>
    /// <param name="found">[out] True if variable is in pool</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Get d.p. values from the kernel pool",
            ToolTip = "Return the d.p. value of a kernel variable from the kernel pool"
            ))
    static void gdpool(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        TArray<double>& values,
        bool& found,
        const FString& name = TEXT("BODY514_NUT_PREC_RA"),
        int                 start = 0,
        int                 room = 7
    );

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Get SDistance values from the kernel pool",
            ToolTip = "Return the SDistance value of a kernel variable from the kernel pool"
            ))
    static void gdpool_scalar(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        double& value,
        bool& found,
        const FString& name = TEXT("BODY514_LONG_AXIS")
    );


    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Get SDistance values from the kernel pool",
            ToolTip = "Return the SDistance value of a kernel variable from the kernel pool"
            ))
    static void gdpool_distance(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        FSDistance& value,
        bool& found,
        const FString& name = TEXT("BODY514_LONG_AXIS")
    );


    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Get SDistanceVector values from the kernel pool",
            ToolTip = "Return the SDistanceVector value of a kernel variable from the kernel pool"
            ))
    static void gdpool_vector(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        FSDistanceVector& value,
        bool& found,
        const FString& name
    );


    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Get SMassConstant values from the kernel pool",
            ToolTip = "Return the SMassConstant value of a kernel variable from the kernel pool"
            ))
    static void gdpool_mass(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        FSMassConstant& value,
        bool& found,
        const FString& name = TEXT("BODY399_GM")
    );

    /// <summary>Convert geodetic coordinates to rectangular coordinates</summary>
    /// <param name="lon">[in] Geodetic longitude of point (radians)</param>
    /// <param name="lat">[in] Geodetic latitude  of point (radians)</param>
    /// <param name="alt">[in] Altitude of point above the reference spheroid</param>
    /// <param name="re">[in] Equatorial radius of the reference spheroid</param>
    /// <param name="f">[in] Flattening coefficient</param>
    /// <param name="rectan">[out] Rectangular coordinates of point</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Geometry",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = " Geodetic to rectangular coordinates",
            ToolTip = "Convert geodetic coordinates to rectangular coordinates"
            ))
    static void georec(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FSLonLat& lonlat,
        const FSDistance& alt,
        const FSDistance& re,
        FSDistanceVector& rectan,
        double f = 0.00335281066474748071984552861852
    );


    /// <summary>
    //   Return the field-of-view (FOV) parameters for a specified 
    //   instrument.The instrument is specified by its NAIF ID code.
    /// </summary>
    /// <param name="instid"></param>
    /// <param name="shape"></param>
    /// <param name="frame"></param>
    /// <param name="bsight"></param>
    /// <param name="bounds"></param>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Geometry",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ToolTip = "Get instrument FOV parameters"
            ))
    static void getfov(
        ES_ResultCode&  ResultCode,
        FString&        ErrorMessage,
        int64           instid,
        FString&        shape,
        FString&        frame,
        FSDimensionlessVector&          bsight,
        TArray<FSDimensionlessVector>&   bounds
    );


    /// <summary>Get integers from the kernel pool</summary>
    /// <param name="name">[in] Name of the variable whose value is to be returned</param>
    /// <param name="start">[in] Which component to start retrieving for `name'</param>
    /// <param name="room">[in] The largest number of values to return</param>
    /// <param name="n">[out] Number of values returned for `name'</param>
    /// <param name="ivals">[out] Values associated with `name'</param>
    /// <param name="found">[out] True if variable is in pool</param>
    /// <returns></returns>

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Get integers from the kernel pool",
            ToolTip = "Return the integer value of a kernel variable from the kernel pool"
            ))
    static void gipool(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        TArray<int64>& ivals,
        bool& found,
        const FString& name,
        int             start,
        int             room
    );

    /// <summary>Get names of kernel pool variables</summary>
    /// <param name="name">[in] Template that names should match</param>
    /// <param name="start">[in] Index of first matching name to retrieve</param>
    /// <param name="room">[in] The largest number of values to return</param>
    /// <param name="lenout">[in] Length of strings in output array kvars</param>
    /// <param name="n">[out] Number of values returned for name</param>
    /// <param name="kvars">[out] Kernel pool variables whose names match name</param>
    /// <param name="found">[out] True if there is at least one match</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Get names of kernel pool variables",
            ToolTip = "Return names of kernel variables matching a specified template"
            ))
    static void gnpool(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        TArray<FString>& kvars,
        bool& found,
        const FString& name = TEXT("BODY%%%_*"),
        int                 start = 0,
        int                 room = 100
    );

    /// <summary>Evaluate a Hermite interpolating polynomial at a specified abscissa value</summary>
    /// <param name="n">Number of points defining the polynomial</param>
    /// <param name="xvals">Abscissa values</param>
    /// <param name="yvals">Ordinate and derivative values</param>
    /// <param name="x">Point at which to interpolate the polynomial</param>
    /// <param name="work">Work space array, generally sized at number of elements in yvals times two</param>
    /// <param name="f">Interpolated function value at x</param>
    /// <param name="df">Interpolated function's derivative at x</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Hermite polynomial interpolation",
            ToolTip = "Evaluate a Hermite interpolating polynomial at a specified abscissa value"
            ))
    static void hrmint(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const TArray<double>& xvals,
        const TArray<double>& yvals,
        double x,
        double& f,
        double& df
    );

    /// <summary>Return half the value of pi</summary>
    /// <returns>half the value of pi</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Half the value of pi",
            ToolTip = "Return half the value of pi"
            ))
    static void halfpi(double& half_pi);

    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Angle of half the value of pi",
            ToolTip = "Return angle of half the value of pi"
            ))
    static void halfpi_angle(FSAngle& half_pi);


    /// <summary>This routine returns the 3x3 identity matrix</summary>
    /// <returns>the 3x3 Identity matrix</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Return the 3x3 identity matrix",
            ToolTip = "Returns the 3x3 identity matrix"
            ))
    static void ident(
        FSRotationMatrix& identity
    );

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Geometry",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Illumination angles",
            ToolTip = "Find the illumination angles (phase, solar incidence, and emission) at a specified surface point of a target body"
            ))
    static void ilumin(
        ES_ResultCode&          ResultCode,
        FString&                ErrorMessage,
        const FSDistanceVector& spoint,
        const FSEphemerisTime&  et,
        FSEphemerisTime&        trgepc,
        FSDistanceVector&       srfvec,
        FSAngle&                phase,
        FSAngle&                incdnc,
        FSAngle&                emissn,
        const FString&          method = TEXT("ELLIPSOID"),
        const FString&          target = TEXT("EARTH"),
        const FString&          fixref = TEXT("IAU_EARTH"),
        ES_AberrationCorrectionWithTransmissions abcorr = ES_AberrationCorrectionWithTransmissions::None,
        const FString&          obsrvr = TEXT("EARTH")
    );

    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Intersection of ellipse and plane",
            ToolTip = "Find the intersection of an ellipse and a plane"
            ))
    static void inelpl(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FSEllipse& ellips,
        const FSPlane& plane,
        TArray<FSDistanceVector>& xpts,
        bool& coplanar
    );

    /// <summary>Return the value of the largest (positive) number representable in a SpiceInt variable</summary>
    /// <returns>the largest (positive) number that can be represented in a SpiceInt variable</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Largest integer number",
            ToolTip = "Value of the largest (positive) number representable in a SpiceInt variable"
            ))
    static void intmax(int64& int_max);

    /// <summary>Return the value of the smallest (negative) number representable in a SpiceInt variable</summary>
    /// <returns>the smallest (negative) number that can be represented in a SpiceInt variable</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Smallest integer number",
            ToolTip = "Value of the smallest(negative) number representable in a SpiceInt variable"
            ))
    static void intmin(int64& int_min);

    /// <summary>Generate the inverse of a 3x3 matrix</summary>
    /// <param name="m1">[in] Matrix to be inverted</param>
    /// <param name="mout">[out] Inverted matrix (m1)**-1.  If m1 is singular, then mout will be the zero matrix.mout can overwrite m1</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Invert a 3x3 matrix",
            ToolTip = "Generate the inverse of a 3x3 matrix"
            ))
    static void invert(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FSRotationMatrix& m1,
        FSRotationMatrix& mout
    );


    /// <summary>Given a matrix, construct the matrix whose rows are the columns of the first divided by the length squared of the the corresponding columns of the input matrix</summary>
    /// <param name="m">A 3x3 matrix</param>
    /// <param name="mit">m after transposition and scaling of rows</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Invert nearly orthogonal matrices",
            ToolTip = "Given a matrix, construct the matrix whose rows are the columns of the first divided by the length squared of the the corresponding columns of the input matrix"
            ))
    static void invort(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FSRotationMatrix& m,
        FSRotationMatrix& mit
    );


    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Besselian Date 1900.0",
            ToolTip = "Return the Julian Date corresponding to Besselian Date 1900.0"
            ))
    static void b1900(
        FSEphemerisTime& b1900
    );

    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Besselian Date 1950.0",
            ToolTip = "Return the Julian Date corresponding to Besselian Date 1950.0"
            ))
    static void b1950(
        FSEphemerisTime& b1950
    );

    /// <summary>Return the Julian Date of 1899 DEC 31 12:00:00 (1900 JAN 0.5)</summary>
    /// <returns>the Julian Date of 1899 DEC 31 12:00:00 (1900 JAN 0.5)</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Julian Date of 1900.0 JAN 0.5",
            ToolTip = "Return the Julian Date of 1899 DEC 31 12:00:00 (1900 JAN 0.5)"
            ))
    static void j1900(
        FSEphemerisTime& j1900
    );

    /// <summary>Return the Julian Date of 1950 JAN 01 00:00:00 (1950 JAN 1.0)</summary>
    /// <returns>the Julian Date of 1950 JAN 01 00:00:00 (1950 JAN 1.0) </returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Julian Date of 1950.0 JAN 1.0",
            ToolTip = "Return the Julian Date of 1950 JAN 01 00:00:00 (1950 JAN 1.0)"
            ))
    static void j1950(FSEphemerisTime& j1950);

    /// <summary>Return the Julian Date of 2000 JAN 01 12:00:00 (2000 JAN 1.5)</summary>
    /// <returns>the Julian Date of 2000 JAN 01 12:00:00 (2000 JAN 1.5)</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Julian Date of 2000 JAN 1.5",
            ToolTip = "Return the Julian Date of 2000 JAN 01 12:00:00 (2000 JAN 1.5)"
            ))
    static void j2000(FSEphemerisTime& j2000);

    /// <summary>Return the Julian Date of 2100 JAN 01 12:00:00 (2100 JAN 1.5)</summary>
    /// <returns>the Julian Date of 2100 JAN 01 12:00:00 (2100 JAN 1.5)</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Julian Date of 2100 JAN 1.5",
            ToolTip = "Return the Julian Date of 2100 JAN 01 12:00:00 (2100 JAN 1.5)"
            ))
    static void j2100(FSEphemerisTime& j2100);

    /// <summary>Return the number of seconds in a julian year</summary>
    /// <returns>The number of seconds/julian year</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Seconds per julian year",
            ToolTip = "Return the number of seconds in a julian year"
            ))
    static void jyear(double& secondsPerJulianYear);

    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Seconds per tropical year",
            ToolTip = "Return the number of seconds in a tropical year"
            ))
    static void tyear(double& secondsPerTropicalYear);

    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Ephemeris Period of one julian year",
            ToolTip = "Return the number of seconds in a julian year"
            ))
    static void jyear_year(FSEphemerisPeriod& oneJulianYear);

    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Ephemeris Period of one tropical year",
            ToolTip = "Return the number of seconds in a tropical year"
            ))
    static void tyear_year(FSEphemerisPeriod& oneTropicalYear);

    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Geometry",
        meta = (
            ShortToolTip = "Latitudinal to rectangular coordinates",
            ToolTip = "Convert from latitudinal coordinates to rectangular coordinates"
            ))
    static void latrec(
        const FSDistance& radius,
        const FSLonLat& lonlat,
        FSDistanceVector& rectan
    );


    /// <summary>Evaluate a Lagrange interpolating polynomial for a specified set of coordinate pairs, at a specified abscissa value. Return the value of both polynomialand derivative</summary>
    /// <param name="n">[in] Number of points defining the polynomial</param>
    /// <param name="[in] xvals">Abscissa values</param>
    /// <param name="[in] yvals">Ordinate values</param>
    /// <param name="[in] work">Work space array, n x 2 work space array, where n is the same dimension as xvals and yvals</param>
    /// <param name="x">[in] Point at which to interpolate the polynomial</param>
    /// <param name="p">[out] Polynomial value at x</param>
    /// <param name="dp">[out] Polynomial derivative at x</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Lagrange polynomial interpolation with derivative",
            ToolTip = "Evaluate a Lagrange interpolating polynomial for a specified set of coordinate pairs, at a specified abscissa value.Return the value of both polynomialand derivative"
            ))
    static void lgrind(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const TArray<double>& xvals,
            const TArray<double>& yvals,
            double x,
            double& p,
            double& dp
        );

    /// <summary>Compute L_s, the planetocentric longitude of the sun, as seen from a specified body</summary>
    /// <param name="body">[in] Name of central body</param>
    /// <param name="et">[in] Epoch in seconds past J2000 TDB</param>
    /// <param name="abcorr">[in] Aberration correction ["NONE", "LT", "LT+S"]</param>
    /// <returns>the value of L_s for the specified body at the specified time</returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Utility",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Longitude of the sun, planetocentric",
            ToolTip = "Compute L_s, the planetocentric longitude of the sun, as seen from a specified body"
            ))
        static void lspcn(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FString& body,
            const FSEphemerisTime& et,
            ES_AberrationCorrection abcorr,
            FSAngle& lon
        );

    /// <summary>Set one double precision 3x3 matrix equal to another</summary>
    /// <param name="m1">[in] Input matrix</param>
    /// <param name="mout">[out] Output matrix equal to m1</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Matrix equal to another, 3x3",
            ToolTip = "Set one double precision 3x3 matrix equal to another"
            ))
        static void mequ(
            const FSRotationMatrix& m1,
            FSRotationMatrix& mout
        );

#if 0
    /// <summary>Multiply a matrix and a vector of arbitrary size</summary>
    /// <param name="m1">[in] Left-hand matrix to be multiplied</param>
    /// <param name="v2">[in] Right-hand vector to be multiplied</param>
    /// <param name="nrow1">[in] Row dimension of m1 and length of vout</param>
    /// <param name="nc1r2">[in] Column dimension of m1 and length of v2</param>
    /// <param name="vout">[out] Product vector m1*v2</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable, Category = "Spice|Api", meta = (ToolTip = ""))
        static void mxvg(
            const void* m1,
            const void* v2,
            SpiceInt       nrow1,
            SpiceInt       nc1r2,
            void* vout
        );
#endif

    /// <summary>Find a unit quaternion corresponding to a specified rotation matrix</summary>
    /// <param name="r">[in] Rotation matrix</param>
    /// <param name="q">[out] unit quaternion representing 'r'</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Matrix to quaternion",
            ToolTip = "Find a unit quaternion corresponding to a specified rotation matrix"
            ))
        static void m2q(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FSRotationMatrix& r,
            FSQuaternion& q
        );

    /// <summary>Multiply two 3x3 matrices</summary>
    /// <param name="m1">[in] 3x3 double precision matrix</param>
    /// <param name="m2">[in] 3x3 double precision matrix</param>
    /// <param name="mout">[out] 3x3 double precision matrix. mout is the product m1* m2</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Matrix times matrix, 3x3",
            ToolTip = "Multiply two 3x3 matrices"
            ))
        static void mxm(
            const FSRotationMatrix& m1,
            const FSRotationMatrix& m2,
            FSRotationMatrix& mout
        );

    /// <summary>Factor a rotation matrix as a product of three rotations about specified coordinate axes</summary>
    /// <param name="r">[in] Rotation matrix to be factored</param>
    /// <param name="[out] axis1, axis2, axis3">Numbers of third, second, and first rotation axes</param>
    /// <param name="[out] angle1, angle2, angle3">Third, second, and first Euler angles, in radians</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Matrix to Euler angles",
            ToolTip = "Factor a rotation matrix as a product of three rotations about specified coordinate axes"
            ))
        static void m2eul(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            FSEulerAngles& eulers,
            const FSRotationMatrix& r,
            ES_Axis axis3 = ES_Axis::X,
            ES_Axis axis2 = ES_Axis::Y,
            ES_Axis axis1 = ES_Axis::Z
        );


    /// <summary>Multiply a 3x3 double precision matrix with a 3-dimensional double precision vector</summary>
    /// <param name="m1">[in] 3x3 double precision matrix</param>
    /// <param name="vin">[in] 3-dimensional double precision vector</param>
    /// <param name="vout">[out] 3-dimensinoal double precision vector. vout is the product m1* vin</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Matrix times vector, 3x3",
            ToolTip = "Multiply a 3x3 double precision matrix with a 3-dimensional double precision vector"
            ))
        static void mxv_distance(
            const FSRotationMatrix& m1,
            const FSDistanceVector& vin,
            FSDistanceVector& vout
        );

    /// <summary>Multiply a 3x3 double precision matrix with a 3-dimensional double precision vector</summary>
    /// <param name="m1">[in] 3x3 double precision matrix</param>
    /// <param name="vin">[in] 3-dimensional double precision vector</param>
    /// <param name="vout">[out] 3-dimensinoal double precision vector. vout is the product m1* vin</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Matrix times vector, 3x3",
            ToolTip = "Multiply a 3x3 double precision matrix with a 3-dimensional double precision vector"
            ))
        static void mxv_velocity(
            const FSRotationMatrix& m1,
            const FSVelocityVector& vin,
            FSVelocityVector& vout
        );

    /// <summary>Multiply a 3x3 double precision matrix with a 3-dimensional double precision vector</summary>
    /// <param name="m1">[in] 3x3 double precision matrix</param>
    /// <param name="vin">[in] 3-dimensional double precision vector</param>
    /// <param name="vout">[out] 3-dimensinoal double precision vector. vout is the product m1* vin</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Matrix times vector, 3x3",
            ToolTip = "Multiply a 3x3 double precision matrix with a 3-dimensional double precision vector"
            ))
        static void mxv(
            const FSRotationMatrix& m1,
            const FSDimensionlessVector& vin,
            FSDimensionlessVector& vout
        );


    /// <summary>
    /// Look up the frame ID code associated with a string.
    /// </summary>
    /// <param name="frname">[in] The name of some reference frame</param>
    /// <param name="frcode">[out] The SPICE ID code of the frame</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Data",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Name to frame",
            ToolTip = "Look up the frame ID code associated with a string"
            ))
        static void namfrm(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FString& frname,
            int64& frcode
        );

    /// <summary>Find the nearest point on an ellipse to a specified point, both in three - dimensional space, and find the distance between the ellipseand the point</summary>
    /// <param name="point">[in] Point whose distance to an ellipse is to be found</param>
    /// <param name="ellips">[in] A CSPICE ellipse</param>
    /// <param name="pnear">[out] Nearest point on ellipse to input point</param>
    /// <param name="dist">[out] Distance of input point to ellipse</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Nearest point on ellipse to point",
            ToolTip = "Find the nearest point on an ellipse to a specified point, both in three - dimensional space, and find the distance between the ellipse and the point"
            ))
        static void npelpt(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FSDistanceVector& point,
            const FSEllipse& ellips,
            FSDistanceVector& pnear,
            FSDistance& dist
        );

    /// <summary>This routine locates the point on the surface of an ellipsoid that is nearest to a specified position.It also returns the altitude of the position above the ellipsoid</summary>
    /// <param name="positn">Position of a point in bodyfixed frame</param>
    /// <param name="a">[in] Length of semi-axis parallel to x-axis</param>
    /// <param name="b">[in] Length of semi-axis parallel to y-axis</param>
    /// <param name="c">[in] Length on semi-axis parallel to z-axis</param>
    /// <param name="npoint">[out] Point on the ellipsoid closest to positn</param>
    /// <param name="alt">[out] Altitude of positn above the ellipsoid</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Nearest point on an ellipsoid",
            ToolTip = "Locates the point on the surface of an ellipsoid that is nearest to a specified position.It also returns the altitude of the position above the ellipsoid"
            ))
        static void nearpt(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FSDistanceVector& positn,
            const FSDistance& a,
            const FSDistance& b,
            const FSDistance& c,
            FSDistanceVector& npoint,
            FSDistance& alt
        );

    /// <summary>Find nearest point on a triaxial ellipsoid to a specified line, and the distance from the ellipsoid to the line</summary>
    /// <param name="a">[in] Length of ellipsoid's semi-axis in the x direction</param>
    /// <param name="b">[in] Length of ellipsoid's semi-axis in the y direction</param>
    /// <param name="c">[in] Length of ellipsoid's semi-axis in the z direction</param>
    /// <param name="linept">[in] Point on line</param>
    /// <param name="linedr">[in] Direction vector of line</param>
    /// <param name="pnear">[out] Nearest point on ellipsoid to line</param>
    /// <param name="dist">[out] Distance of ellipsoid from line</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Nearest point on ellipsoid to line",
            ToolTip = "Find nearest point on a triaxial ellipsoid to a specified line, and the distance from the ellipsoid to the line"
            ))
        static void npedln(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FSDistance& a,
            const FSDistance& b,
            const FSDistance& c,
            const FSDistanceVector& linept,
            const FSDimensionlessVector& linedr,
            FSDistanceVector& pnear,
            FSDistance& dist
        );

    /// <summary>Find the nearest point on a line to a specified point, and find the distance between the two points</summary>
    /// <param name="linpt">[in] Point on a line</param>
    /// <param name="lindir">[in] The line's direction vector</param>
    /// <param name="point">[in] A second point</param>
    /// <param name="pnear">[out] Nearest point on the line to point</param>
    /// <param name="dist">[out] Distance between point and pnear</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Nearest point on line to point",
            ToolTip = ""
            ))
        static void nplnpt(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FSDistanceVector& linpt,
            const FSDimensionlessVector& lindir,
            const FSDistanceVector& point,
            FSDistanceVector& pnear,
            double& dist
        );

    /// <summary>Make a CSPICE plane from a normal vector and a constant</summary>
    /// <param name="normal">[in] A normal vector</param>
    /// <param name="constant">[in] constant defining a plane</param>
    /// <param name="plane">[out] A CSPICE plane structure representing the plane</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Normal vector and constant to plane",
            ToolTip = "Make a plane from a normal vector and a constant"
            ))
        static void nvc2pl(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FSDimensionlessVector& normal,
            const FSDistance& constant,
            FSPlane& plane
        );

    /// <summary>Make a CSPICE plane from a normal vector and a point</summary>
    /// <param name="">[in] A normal vector</param>
    /// <param name="">[in] a point defining a plane</param>
    /// <param name="">[out] A CSPICE plane structure representing the plane</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Normal vector and point to plane",
            ToolTip = "Make a plane from a normal vector and a point"
            ))
        static void nvp2pl(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FSDimensionlessVector& normal,
            const FSDistanceVector& point,
            FSPlane& plane
        );


    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/oscelt_c.html
    /// <summary>Determine the set of osculating conic orbital elements that corresponds to the state(position, velocity) of a body at some epoch</summary>
    /// <param name="state">[in] State of body at epoch of elements</param>
    /// <param name="et">[in] Epoch of elements</param>
    /// <param name="mu">[in] Gravitational parameter (GM) of primary body</param>
    /// <param name="elts">[out] Equivalent conic elements</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintPure,
        Category = "Spice|Api|Conics",
        meta = (
            ShortToolTip = "Determine conic elements from state",
            ToolTip = "Determine the set of osculating conic orbital elements that corresponds to the state(position, velocity) of a body at some epoch"
            ))
    static void oscelt(
        const FSStateVector& state,
        const FSEphemerisTime& et,
        const FSMassConstant& mu,
        FSConicElements& elts
    );

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/oscltx_c.html
    /// <summary>Determine the set of osculating conic orbital elements that corresponds to the state(position, velocity) of a body at some epoch. In additional to the classical elements, return the true anomaly, semi - major axis, and period, if applicable</summary>
    /// <param name="state">[in] State of body at epoch of elements</param>
    /// <param name="et">[in] Epoch of elements</param>
    /// <param name="mu">[in] Gravitational parameter (GM) of primary body</param>
    /// <param name="elts">[out] Extended set of classical conic elements</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintPure,
        Category = "Spice|Api|Conics",
        meta = (
            ShortToolTip = "Extended osculating elements from state",
            ToolTip = "Determine the set of osculating conic orbital elements that corresponds to the state(position, velocity) of a body at some epoch.  In additional to the classical elements, return the true anomaly, semi - major axis, and period, if applicable"
            ))
    static void oscltx(
        const FSStateVector& state,
        const FSEphemerisTime& et,
        const FSMassConstant& mu,
        FSConicElements& elts,
        FSAngle& nu,
        FSDistance& a,
        FSEphemerisPeriod& tau
    );


    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Geometry",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Planetographic to rectangular",
            ToolTip = "Convert planetographic coordinates to rectangular coordinates"
            ))
    static void pgrrec(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FSLonLat& lonlat,
        const FSDistance& alt,
        const FSDistance& re,
        FSDistanceVector& rectan,
        const FString& body = TEXT("EARTH"),
        double f = 0.00335281066474748071984552861852
    );


    /// <summary>the value of pi</summary>
    /// <returns>pi</returns>
    UFUNCTION(
        BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Value of pi",
            ToolTip = "Return the value of pi (the ratio of the circumference of a circle to its diameter)"
            ))
    static void pi(double& pi);


    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Angle of value pi",
            ToolTip = "Return angle with the value of pi"
            ))
    static void pi_angle(FSAngle& pi);


    /// <summary>Project an ellipse onto a plane, orthogonally</summary>
    /// <param name="elin">A CSPICE ellipse to be projected</param>
    /// <param name="plane">A plane onto which elin is to be projected</param>
    /// <param name="elout">A CSPICE ellipse resulting from the projection</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Project ellipse onto plane",
            ToolTip = "Project an ellipse onto a plane, orthogonally"
            ))
    static void pjelpl(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FSEllipse& elin,
        const FSPlane& plane,
        FSEllipse& elout
    );

    /// <summary>Return a unit normal vector and constant that define a specified plane</summary>
    /// <param name="plane">[in] A CSPICE plane</param>
    /// <param name="normal, constant">[out] A normal vector and constant defining the geometric plane represented by plane</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Plane to normal vector and constant",
            ToolTip = "Return a unit normal vector and constant that define a specified plane"
            ))
        static void pl2nvc(
            const FSPlane& plane,
            FSDimensionlessVector& normal,
            FSDistance& constant
        );

    /// <summary>Return a unit normal vector and point that define a specified plane</summary>
    /// <param name="plane">[in] A CSPICE plane</param>
    /// <param name="normal, point">[out] A unit normal vector and point that define plane</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Plane to normal vector and point",
            ToolTip = "Return a unit normal vector and point that define a specified plane"
            ))
        static void pl2nvp(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FSPlane& plane,
            FSDistanceVector& normal,
            FSDistanceVector& point
        );

    /// <summary>Return a point and two orthogonal spanning vectors that generate a specified plane</summary>
    /// <param name="plane">[in] A CSPICE plane</param>
    /// <param name="point>[out] A point in the input plane</param>
    /// <param name="span1>[out] A vector spanning the input plane</param>
    /// <param name="span2>[out] A vector spanning the input plane</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Plane to point and spanning vectors",
            ToolTip = "Return a point and two orthogonal spanning vectors that generate a specified plane"
            ))
        static void pl2psv(
            const FSPlane& plane,
            FSDistanceVector& point,
            FSDistanceVector& span1,
            FSDistanceVector& span2
        );

    /// <summary>Given a central mass and the state of massless body at time t_0, this routine determines the state as predicted by a two - body force model at time t_0 + dt</summary>
    /// <param name="gm">[in] Gravity of the central mass (G times the mass M)</param>
    /// <param name="pvinit">[in] Initial state from which to propagate a state</param>
    /// <param name="dt">[in] Time offset from initial state to propagate to</param>
    /// <param name="pvprop">[out] The propagated state</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|State",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Propagate a two-body solution",
            ToolTip = "Given a central mass and the state of massless body at time t_0, this routine determines the state as predicted by a two - body force model at time t_0 + dt"
            ))
        static void prop2b(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FSMassConstant& gm,
            const FSStateVector& pvinit,
            const FSEphemerisPeriod& dt,
            FSStateVector& pvprop
        );

    /// <summary>Make a plane from a point and two spanning vectors</summary>
    /// <param name="point">[in] A point</param>
    /// <param name="point">[in] Spanning vector</param>
    /// <param name="point">[in] Spanning vector</param>
    /// <param name="plane">[out] A CSPICE plane representing the plane</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Point and spanning vectors to plane",
            ToolTip = "Make a plane from a point and two spanning vectors"
            ))
        static void psv2pl(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FSDistanceVector& point,
            const FSDistanceVector& span1,
            const FSDistanceVector& span2,
            FSPlane& plane
        );

    /// <summary>Position Transformation Matrix</summary>
    /// <param name="from">[in] Name of the frame to transform from</param>
    /// <param name="to">[in] Name of the frame to transform to</param>
    /// <param name="et">[in] Epoch of the rotation matrix</param>
    /// <param name="rotate">[out] A rotation matrix</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintCallable,
        Category = "Spice|Api|PX",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Position Transformation Matrix",
            ToolTip = "Return the matrix that transforms position vectors from one specified frame to another at a specified epoch"
            ))
        static void pxform(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FString& from,
            const FSEphemerisTime& et,
            FSRotationMatrix& rotate,
            const FString& to = TEXT("ECLIPJ2000")
        );

    /// <summary>Position Transform Matrix, Different Epochs</summary>
    /// <param name="from">[in] Name of the frame to transform from</param>
    /// <param name="to">[in] Name of the frame to transform to</param>
    /// <param name="et">[in] Epoch of the rotation matrix</param>
    /// <param name="etto">[in] Evaluation time of `to' frame</param>
    /// <param name="rotate">[out] A rotation matrix</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintCallable,
        Category = "Spice|Api|PX",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Position Transform Matrix, Different Epochs",
            ToolTip = "Return the 3x3 matrix that transforms position vectors from one specified frame at a specified epoch to another specified frame at another specified epoch"
            ))
        static void pxfrm2(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FString& from,
            const FSEphemerisTime& etfrom,
            const FSEphemerisTime& etto,
            FSRotationMatrix& rotate,
            const FString& to = TEXT("ECLIPJ2000")
        );

    /// <summary>Find a unit quaternion corresponding to a specified rotation matrix</summary>
    /// <param name="q">[in] unit quaternion</param>
    /// <param name="r">[out] rotation matrix corresponding to 'q'</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Quaternion to matrix",
            ToolTip = "Find the rotation matrix corresponding to a specified unit quaternion"
            ))
        static void q2m(
            const FSQuaternion& q,
            FSRotationMatrix& r
        );

    /// <summary>Multiply two quaternions</summary>
    /// <param name="q1">[in] First SPICE quaternion factor</param>
    /// <param name="q2">[in] Second SPICE quaternion factor</param>
    /// <param name="qout">[out] Product of 'q1' and 'q2'</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Quaternion times quaternion",
            ToolTip = "Multiply two quaternions"
            ))
        static void qxq(
            const FSQuaternion& q1,
            const FSQuaternion& q2,
            FSQuaternion& qout
        );

    /// <summary>Convert from range, right ascension, and declination to rectangular coordinates</summary>
    /// <param name="range">[in] Distance of a point from the origin</param>
    /// <param name="ra">[in] Right ascension of point in radians</param>
    /// <param name="dec">[in] Declination of point in radians</param>
    /// <param name="rectan">[out] Rectangular coordinates of the point</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintPure,
        Category = "Spice|Api|Geometry",
        meta = (
            ShortToolTip = "Convert from range, right ascension, and declination to rectangular coordinates",
            ToolTip = "Convert from range, right ascension, and declination to rectangular coordinates"
            ))
        static void radrec(
            const FSDistance& range,
            const FSAngle& ra,
            const FSAngle& dec,
            FSDistanceVector& rectan
        );

    /// <summary>This routine determines a state transformation matrix from a rotation matrixand the angular velocity of the rotation</summary>
    /// <param name="rot">[in] Rotation matrix</param>
    /// <param name="av">[in] Angular velocity vector</param>
    /// <param name="xform">[out] State transformation associated with rot and av</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Rotation and angular velocity to transform",
            ToolTip = "Determines a state transformation matrix from a rotation matrix and the angular velocity of the rotation"
            ))
        static void rav2xf(
            const FSRotationMatrix& rot,
            const FSAngularVelocity& av,
            FSEulerAngularTransform& xform
        );

    /// <summary>Compute the axis of the rotation given by an input matrix and the angle of the rotation about that axis</summary>
    /// <param name="matrix">[in] 3x3 rotation matrix in double precision</param>
    /// <param name="axis">[out] Axis of the rotation</param>
    /// <param name="angle">[out] Angle through which the rotation is performed</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Rotation axis of a matrix",
            ToolTip = "Compute the axis of the rotation given by an input matrix and the angle of the rotation about that axis"
            ))
        static void raxisa(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FSRotationMatrix& matrix,
            FSDimensionlessVector& axis,
            FSAngle& angle
        );

    /// <summary>Convert from rectangular coordinates to geodetic coordinates</summary>
    /// <param name="rectan">[in] Rectangular coordinates of a point</param>
    /// <param name="re">[in] Equatorial radius of the reference spheroid</param>
    /// <param name="f">[in] Flattening coefficient</param>
    /// <param name="lon">[out] Geodetic longitude of the point (radians)</param>
    /// <param name="lat">[out] Geodetic latitude  of the point (radians)</param>
    /// <param name="alt">[out] Altitude of the point above reference spheroid</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Geometry",
        meta = (
            ShortToolTip = "Rectangular to geodetic",
            ToolTip = "Convert from rectangular coordinates to geodetic coordinates"
            ))
    static void recgeo(
        const FSDistanceVector& rectan,
        const FSDistance& re,
        FSLonLat& lonlat,
        FSDistance& alt,
        double f = 0.00335281066474748071984552861852
    );

    /// <summary>Convert from rectangular coordinates to latitudinal coordinates</summary>
    /// <param name="rectan">[in] Rectangular coordinates of a point</param>
    /// <param name="radius">[out] Distance of the point from the origin</param>
    /// <param name="longitude">[out] Longitude of the point in radians</param>
    /// <param name="latitude">[out] Latitude of the point in radians</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Geometry",
        meta = (
            ShortToolTip = "Rectangular to latitudinal coordinates",
            ToolTip = "Convert from rectangular coordinates to latitudinal coordinates"
            ))
    static void reclat(
        const FSDistanceVector& rectan,
        FSDistance& radius,
        FSLonLat& lonlat
    );


    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Geometry",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Rectangular to planetographic",
            ToolTip = "Convert rectangular coordinates to planetographic coordinates"
            ))
    static void recpgr(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FSDistanceVector& rectan,
        const FSDistance& re,
        FSLonLat& lonlat,
        FSDistance& alt,
        const FString& body = TEXT("EARTH"),
        double f = 0.00335281066474748071984552861852
    );



    /// <summary>Convert rectangular coordinates to range, right ascension, and declination</summary>
    /// <param name="rectan">[in] Rectangular coordinates of a point</param>
    /// <param name="range">[out] Distance of the point from the origin</param>
    /// <param name="ra">[out] Right ascension in radians</param>
    /// <param name="dec">[out] Declination in radians</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Geometry",
        meta = (
            ShortToolTip = "Rectangular coordinates to RA and DEC",
            ToolTip = "Convert rectangular coordinates to range, right ascension, and declination"
            ))
        static void recrad(
            const FSDistanceVector& rectan,
            FSDistance& range,
            FSAngle& ra,
            FSAngle& dec
        );

    /// <summary>Convert from rectangular coordinates to spherical coordinates</summary>
    /// <param name="rectan">[in] Rectangular coordinates of a point</param>
    /// <param name="r">[out] Distance of the point from the origin</param>
    /// <param name="colat">[out] Angle of the point from the Z-axis in radians</param>
    /// <param name="lon">[out] Longitude of the point in radians</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Geometry",
        meta = (
            ShortToolTip = "Rectangular to spherical coordinates",
            ToolTip = "Convert from rectangular coordinates to spherical coordinates"
            ))
        static void recsph(
            const FSDistanceVector& rectan,
            FSDistance& r,
            FSAngle& colat,
            FSAngle& lon
        );

    /// <summary>Generate a rotation matrix</summary>
    /// <param name="angle">[in] Angle of rotation (radians)</param>
    /// <param name="iaxis">[in] Axis of rotation (X=1, Y=2, Z=3)</param>
    /// <param name="mout">[out] Resulting rotation matrix [angle]</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Generate a rotation matrix",
            ToolTip = "Calculate the 3x3 rotation matrix generated by a rotation of a specified angle about a specified axis. This rotation is thought of as rotating the coordinate system"
            ))
        static void rotate(
            const FSAngle& angle,
            ES_Axis         iaxis,
            FSRotationMatrix& mout
        );

    /// <summary>Rotate a matrix. This rotation is thought of as rotating the coordinate system</summary>
    /// <param name="m1">[in] Matrix to be rotated</param>
    /// <param name="angle">[in] Angle of rotation (radians)</param>
    /// <param name="iaxis">[in] Axis of rotation (X=1, Y=2, Z=3)</param>
    /// <param name="mout">[out] Resulting rotated matrix</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Rotate a matrix",
            ToolTip = "Applies a rotation of angle radians about axis iaxis to a matrix.This rotation is thought of as rotating the coordinate system."
            ))
        static void rotmat(
            const FSRotationMatrix& m1,
            const FSAngle& angle,
            ES_Axis                 iaxis,
            FSRotationMatrix& mout
        );

    /// <summary>Transform a vector via a rotation.  Transform a vector to a new coordinate system rotated by angle radians about axis iaxis.This transformation rotates v1 by - angle radians about the specified axis</summary>
    /// <param name="v1">[in] Vector whose coordinate system is to be rotated</param>
    /// <param name="angle">[in] Angle of rotation in radians</param>
    /// <param name="iaxis">[in] Axis of rotation (X=1, Y=2, Z=3)</param>
    /// <param name="vout">[out] Resulting vector</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Transform a vector via a rotation",
            ToolTip = "Transform a vector to a new coordinate system rotated by angle radians about axis iaxis.This transformation rotates v1 by - angle radians about the specified axis"
            ))
        static void rotvec(
            const FSDistanceVector& v1,
            const FSAngle& angle,
            ES_Axis                 iaxis,
            FSDistanceVector& vout
        );

    /// <summary>Radians per degree</summary>
    /// <returns>Radians.  Per degree.</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Radians per degree",
            ToolTip = "Return the number of radians per degree"
            ))
    static void rpd(
        // Hmm... scalar value?
        double& radiansPerDegree
    );

    /// <summary>Roots of a quadratic equation</summary>
    /// <param name="a">[in] Coefficient of quadratic term</param>
    /// <param name="b">[in] Coefficient of linear term</param>
    /// <param name="c">[in] Constant</param>
    /// <param name="root1">[out] Root built from positive discriminant term</param>
    /// <param name="root2">[out] Root built from negative discriminant term</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Roots of a quadratic equation",
            ToolTip = "Find the roots of a quadratic equation"
            ))
        static void rquad(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            double a,
            double b,
            double c,
            FSComplexScalar& root1,
            FSComplexScalar& root2
        );

    /// <summary>Decode spacecraft clock</summary>
    /// <param name="sc">[in] NAIF spacecraft identification code</param>
    /// <param name="sclkdp">[in] Encoded representation of a spacecraft clock count</param>
    /// <param name="lenout">[in] Maximum allowed length of output SCLK string</param>
    /// <param name="sclkch">[out] Character representation of a clock count</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Time Conversion",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Decode spacecraft clock",
            ToolTip = "Convert double precision encoding of spacecraft clock time into a character representation."
            ))
        static void scdecd(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            int64 sc,
            double sclkdp,
            FString& sclkch
        );

    /// <summary>ET to continuous SCLK ticks</summary>
    /// <param name="sc">[in] NAIF spacecraft identification code</param>
    /// <param name="et">[in] Ephemeris time, seconds past J2000</param>
    /// <param name="sclkdp">[out] SCLK, encoded as ticks since spacecraft clock start. sclkdp need not be integral</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Time Conversion",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "ET to continuous SCLK ticks",
            ToolTip = "Convert ephemeris seconds past J2000 (ET) to continuous encoded spacecraft clock(`ticks'). Non - integral tick values may be returned"
            ))
        static void sce2c(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            int64 sc,
            const FSEphemerisTime& et,
            double& sclkdp
        );

    /// <summary>ET to SCLK string</summary>
    /// <param name="sc">[in] NAIF spacecraft identification code</param>
    /// <param name="et">[in] Ephemeris time, seconds past J2000</param>
    /// <param name="lenout">[in] Maximum length of output string</param>
    /// <param name="b">[out] An SCLK string</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Time Conversion",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "ET to SCLK string",
            ToolTip = "Convert an epoch specified as ephemeris seconds past J2000 (ET) to a character string representation of a spacecraft clock value(SCLK)"
            ))
        static void sce2s(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            int64 sc,
            const FSEphemerisTime& et,
            FString& sclkch
        );

    /// <summary>ET to SCLK ticks</summary>
    /// <param name="sc">[in] NAIF spacecraft identification code</param>
    /// <param name="et">[in] Ephemeris time, seconds past J2000</param>
    /// <param name="sclkdp">[out] SCLK, encoded as ticks since spacecraft clock start</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Time Conversion",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "ET to SCLK ticks",
            ToolTip = "Convert ephemeris seconds past J2000 (ET) to integral encoded spacecraft clock('ticks').For conversion to fractional ticks, (required for C - kernel production), see the function 'sce2c'"
            ))
        static void sce2t(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            int64 sc,
            const FSEphemerisTime& et,
            double& sclkdp
        );

    /// <summary>Encode spacecraft clock</summary>
    /// <param name="sc">[in] NAIF spacecraft identification code</param>
    /// <param name="sclkch">[in] Character representation of a spacecraft clock</param>
    /// <param name="sclkdp">[out] Encoded representation of the clock count</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Time Conversion",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Encode spacecraft clock",
            ToolTip = "Encode character representation of spacecraft clock time into a double precision number"
            ))
        static void scencd(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            int64 sc,
            const FString& sclkch,
            double& sclkdp
        );

    /// <summary>Convert SCLK "ticks" to character clock format</summary>
    /// <param name="sc">[in] NAIF spacecraft identification code</param>
    /// <param name="ticks">[in] Encoded representation of a spacecraft clock count</param>
    /// <param name="lenout">[in] Maximum length of output string</param>
    /// <param name="clkstr">[out] Character representation of a clock count</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Time Conversion",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Convert SCLK \"ticks\" to character clock format",
            ToolTip = "Convert encoded spacecraft clock ticks to character clock format"
            ))
        static void scfmt(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            int64 sc,
            double ticks,
            FString& clkstr
        );

    /// <summary>Spacecraft Clock Partition Information</summary>
    /// <param name="sc">[in] NAIF spacecraft identification code</param>
    /// <param name="nparts">[out] The number of spacecraft clock partitions</param>
    /// <param name="pstart">[out] Array of partition start times</param>
    /// <param name="pstop">[out] Array of partition stop times</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Time Conversion",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Spacecraft Clock Partition Information",
            ToolTip = "Get spacecraft clock partition information from a spacecraft clock kernel file"
            ))
        static void scpart(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            int64 sc,
            TArray<double>& pstart,
            TArray<double>& pstop
        );

    /// <summary>SCLK string to ET</summary>
    /// <param name="sc">[in] NAIF spacecraft identification code</param>
    /// <param name="sclkch">[in] An SCLK string</param>
    /// <param name="et">[out] Ephemeris time, seconds past J2000</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Time Conversion",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "SCLK string to ET",
            ToolTip = "Convert a spacecraft clock string to ephemeris seconds past J2000(ET)"
            ))
        static void scs2e(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            int64 sc,
            const FString& sclkch,
            FSEphemerisTime& et
        );

    /// <summary>SCLK ticks to ET</summary>
    /// <param name="sc">[in] NAIF spacecraft identification code</param>
    /// <param name="sclkdp">[in] SCLK, encoded as ticks since spacecraft clock start</param>
    /// <param name="et">[out] Ephemeris time, seconds past J2000</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Time Conversion",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "SCLK ticks to ET",
            ToolTip = "Convert encoded spacecraft clock (`ticks') to ephemeris seconds past J2000(ET)"
            ))
        static void sct2e(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            int64 sc,
            double sclkdp,
            FSEphemerisTime& et
        );

    /// <summary>Convert spacecraft clock string to ticks</summary>
    /// <param name="sc">[in] NAIF spacecraft identification code</param>
    /// <param name="clkstr">[in] Character representation of a spacecraft clock</param>
    /// <param name="ticks">[out] Number of ticks represented by the clock string</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Time Conversion",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Convert spacecraft clock string to ticks",
            ToolTip = "Convert a spacecraft clock format string to number of \"ticks\""
            ))
    static void sctiks(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        int64 sc,
        const FString& clkstr,
        double& ticks
    );

    /// <summary>Convert spacecraft clock string to ticks</summary>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Geometry",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Surface intercept",
            ToolTip = "Given an observer and a direction vector defining a ray, compute the surface intercept of the ray on a target body at a specified epoch, optionally corrected for light timeand stellar aberration"
            ))
    static void sincpt(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FSEphemerisTime& et,
        const FString& dref,
        const FSDimensionlessVector& dvec,
        FSDistanceVector& spoint,
        FSEphemerisTime& trgepc,
        FSDistanceVector& srfvec,
        bool& found,
        const FString& method = TEXT("ELLIPSOID"),
        const FString& target = TEXT("EARTH"),
        const FString& fixref = TEXT("IAU_EARTH"),
        const FString& obsrvr = TEXT("EARTH"),
        ES_AberrationCorrectionWithTransmissions abcorr = ES_AberrationCorrectionWithTransmissions::None
    );

    /// <summary>SPK, Close file</summary>
    /// <param name="handle">[in] Handle of the SPK file to be closed</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Spk",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "SPK, Close file",
            ToolTip = "The handle of the SPK file that is to be closed"
            ))
        static void spkcls(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            int64 handle
        );


    /// <summary>SPK coverage</summary>
    /// <param name="spk">[in] Name of SPK file</param>
    /// <param name="idcode">[in] ID code of ephemeris object</param>
    /// <param name="cover">[out] Window giving coverage in `spk' for `idcode''</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Spk",
        meta = (
            AutoCreateRefTerm = "merge_to",
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "SPK coverage",
            ToolTip = "Find the coverage window for a specified ephemeris object in a specified SPK file"
            ))
    static void spkcov(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,

        UPARAM(meta = (DisplayName = "project-relative file path"))
        const FString& spk_relative_path,

        UPARAM(meta = (DisplayName = "is the integer ID code of an object in the ephemeris file"))
        int64 idcode,

        UPARAM(meta = (DisplayName = "(optional) existing window to merge results with"))
        const TArray<FSWindowSegment>& merge_to,

        TArray<FSWindowSegment>& coverage
    );

    /// <summary>SPK, constant position observer state</summary>
    /// <param name="target">[in] Name of target ephemeris object</param>
    /// <param name="et">    [in] Observation epoch</param>
    /// <param name="outref">[in] Reference frame of output state</param>
    /// <param name="refloc">[in] Output reference frame evaluation locus</param>
    /// <param name="abcorr">[in] Aberration correction</param>
    /// <param name="obspos">[in] Observer position relative to center of motion</param>
    /// <param name="obsctr">[in] Center of motion of observer</param>
    /// <param name="obsref">[in] Frame of observer position</param>
    /// <param name="state">[out] State of target with respect to observer</param>
    /// <param name="lt">   [out] One way light time between target and observer</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Spk",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "SPK, constant position observer state",
            ToolTip = "Return the state of a specified target relative to an 'observer', where the observer has constant position in a specified referencevframe.The observer's position is provided by the calling program rather than by loaded SPK files."
            ))
        static void spkcpo(
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
            abcorr = ES_AberrationCorrectionWithNewtonians::None
        );

    /// <summary>SPK, constant position target state</summary>
    /// <param name="trgpos">[in] Target position relative to center of motion</param>
    /// <param name="trgctr">[in] Center of motion of target</param>
    /// <param name="trgref">[in] Frame of target position</param>
    /// <param name="et">    [in] Observation epoch</param>
    /// <param name="outref">[in] Reference frame of output state</param>
    /// <param name="refloc">[in] Output reference frame evaluation locus</param>
    /// <param name="abcorr">[in] Aberration correction</param>
    /// <param name="obsrvr">[in] Name of observing ephemeris object</param>
    /// <param name="state">[out] State of target with respect to observer</param>
    /// <param name="lt">   [out] One way light time between target and observer</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Spk",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "SPK, constant position target state",
            ToolTip = ""
            ))
        static void spkcpt(
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
            abcorr = ES_AberrationCorrectionWithNewtonians::None
        );

    /// <summary>SPK, constant velocity observer state</summary>
    /// <param name="target">[in] Name of target ephemeris object</param>
    /// <param name="et">    [in] Observation epoch</param>
    /// <param name="outref">[in] Reference frame of output state</param>
    /// <param name="refloc">[in] Output reference frame evaluation locus</param>
    /// <param name="abcorr">[in] Aberration correction</param>
    /// <param name="obssta">[in] Observer position relative to center of motion</param>
    /// <param name="obsepc">[in] Epoch of observer state</param>
    /// <param name="obsctr">[in] Center of motion of observer</param>
    /// <param name="obsref">[in] Frame of observer position</param>
    /// <param name="state">[out] State of target with respect to observer</param>
    /// <param name="lt">   [out] One way light time between target and observer</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Spk",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "SPK, constant velocity observer state",
            ToolTip = "Return the state, relative to a specified observer, of a target having constant position in a specified reference frame.The target's position is provided by the calling program rather than by loaded SPK files."
            ))
        static void spkcvo(
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
            abcorr = ES_AberrationCorrectionWithNewtonians::None
        );

    /// <summary>SPK, constant velocity target state</summary>
    /// <param name="trgsta">[in] Target state relative to center of motion</param>
    /// <param name="trgepc">[in] Epoch of target state</param>
    /// <param name="trgctr">[in] Center of motion of target</param>
    /// <param name="trgref">[in] Frame of target position</param>
    /// <param name="et">    [in] Observation epoch</param>
    /// <param name="outref">[in] Reference frame of output state</param>
    /// <param name="refloc">[in] Output reference frame evaluation locus</param>
    /// <param name="abcorr">[in] Aberration correction</param>
    /// <param name="obsrvr">[in] Name of observing ephemeris object</param>
    /// <param name="state">[out] State of target with respect to observer</param>
    /// <param name="lt">   [out] One way light time between target and observer</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Spk",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "SPK, constant velocity target state",
            ToolTip = "Return the state of a specified target relative to an 'observer', where the observer has constant velocity in a specified reference frame.The observer's state is provided by the calling program rather than by loaded SPK files"
            ))
        static void spkcvt(
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
            abcorr = ES_AberrationCorrectionWithNewtonians::None
        );

    /// <summary>S/P Kernel, easy position</summary>
    /// <param name="targ">[in] Target body NAIF ID code</param>
    /// <param name="et">[in] Observer epoch</param>
    /// <param name="ref">[in] Reference frame of output state vector</param>
    /// <param name="abcorr">[in] Aberration correction flag ["NONE"]</param>
    /// <param name="obs">[in] Observing body NAIF ID code</param>
    /// <param name="ptarg">[out] Position of target</param>
    /// <param name="lt">[out] One way light time between observer and target</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Spk",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "S/P Kernel, easy position",
            ToolTip = "Return the position of a target body relative to an observing body, optionally corrected for light time(planetary aberration) and stellar aberration"
            ))
        static void spkezp(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FSEphemerisTime& et,
            FSDistanceVector& ptarg,
            FSEphemerisPeriod& lt,
            int64 targ,
            int64 obs,
            const FString& ref,
            ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::None
        );

    /// <summary>S/P Kernel, easier reader</summary>
/// <param name="targ">[in] Target body name</param>
/// <param name="et">[in] Observer epoch</param>
/// <param name="ref">[in] Reference frame of output state vector</param>
/// <param name="abcorr">[in] Aberration correction flag ["NONE"]</param>
/// <param name="obs">[in] Observing body name</param>
/// <param name="starg">[out] State of target</param>
/// <param name="lt">[out] One way light time between observer and target</param>
/// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Spk",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "S/P Kernel, easier reader",
            ToolTip = "Return the state (position and velocity) of a target body relative to an observing body, optionally corrected for light time(planetary aberration) and stellar aberration"
            ))
        static void spkezr(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FSEphemerisTime& et,
            FSStateVector& state,
            FSEphemerisPeriod& lt,
            const FString& targ = TEXT("MOON"),
            const FString& obs = TEXT("EARTH BARYCENTER"),
            const FString& ref = TEXT("ECLIPJ2000"),
            ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::None
        );


    /// <summary>S/P Kernel, geometric state</summary>
    /// <param name="targ">[in] Target body</param>
    /// <param name="et">[in] Target epoch</param>
    /// <param name="ref">[in] Target reference frame</param>
    /// <param name="obs">[in] Observing body</param>
    /// <param name="state">[out] State of target</param>
    /// <param name="lt">[out] Light time</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Spk",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "S/P Kernel, geometric state",
            ToolTip = "Compute the geometric state (position and velocity) of a target body relative to an observing body"
            ))
        static void spkgeo(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            int64 targ,
            const FSEphemerisTime& et,
            int64 obs,
            FSStateVector& state,
            FSEphemerisPeriod& lt,
            const FString& ref = TEXT("ECLIPJ2000")
        );


    /// <summary>S/P Kernel, geometric position</summary>
    /// <param name="targ">[in] Target body</param>
    /// <param name="et">[in] Target epoch</param>
    /// <param name="ref">[in] Target reference frame</param>
    /// <param name="obs">[in] Observing body</param>
    /// <param name="pos">[out] Position of target</param>
    /// <param name="lt">[out] Light time</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Spk",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "S/P Kernel, geometric position",
            ToolTip = "Compute the geometric position of a target body relative to an observing body"
            ))
        static void spkgps(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            int64 targ,
            const FSEphemerisTime& et,
            int64 obs,
            FSDistanceVector& pos,
            FSEphemerisPeriod& lt,
            const FString& ref = TEXT("ECLIPJ2000")
        );


    /// <summary>S/P Kernel, position</summary>
    /// <param name="targ">[in] Target body name</param>
    /// <param name="et">[in] Target epoch</param>
    /// <param name="ref">[in] Target reference frame</param>
    /// <param name="obs">[in] Observing body</param>
    /// <param name="pos">[out] Position of target</param>
    /// <param name="lt">[out] Light time</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Spk",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "S/P Kernel, position",
            ToolTip = "Return the position of a target body relative to an observing body"
            ))
    static void spkpos(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FSEphemerisTime& et,
        FSDistanceVector& ptarg,
        FSEphemerisPeriod& lt,
        const FString& targ = TEXT("EARTH"),
        const FString& obs = TEXT("SSB"),
        const FString& ref = TEXT("ECLIPJ2000"),
        ES_AberrationCorrectionWithNewtonians abcorr = ES_AberrationCorrectionWithNewtonians::None
    );


    /// <summary>S/P Kernel, Load ephemeris file</summary>
    /// <param name="filename">[in] Name of the file to be loade</param>
    /// <param name="handle">[out] Loaded file's handle</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Spk",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "S/P Kernel, Load ephemeris file",
            ToolTip = "Load an ephemeris file for use by the readers"
            ))
        static void spklef(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            UPARAM(meta = (DisplayName = "project-relative file path"))
            const FString& filename,
            int64& handle
        );

    /// <summary>Find the set of ID codes of all objects in a specified SPK file</summary>
    /// <param name="spk">[in] Name of SPK file</param>
    /// <param name="ids">[out] Set of ID codes of objects in SPK file</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Spk",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "SPK objects",
            ToolTip = "Find the set of ID codes of all objects in a specified SPK file"
            ))
        static void spkobj(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            UPARAM(meta = (DisplayName = "project-relative file path"))
            const FString& relative_path,
            TArray<int64>& ids
        );

    /// <summary>SPK open for addition</summary>
    /// <param name="file">[in] The name of an existing SPK file</param>
    /// <param name="handle">[out] A handle attached to the SPK file opened to append</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Spk",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "SPK open for addition",
            ToolTip = "Open an existing SPK file for subsequent write"
            ))
        static void spkopa(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            UPARAM(meta = (DisplayName = "project-relative file path"))
            const FString& file,
            int64& handle
        );

    /// <summary>SPK, open new file</summary>
    /// <param name="name">[in] The name of the new SPK file to be created</param>
    /// <param name="ifname">[in] The internal filename for the SPK file</param>
    /// <param name="ncomch">[in] The number of characters to reserve for comments</param>
    /// <param name="handle">[out] The handle of the opened SPK file</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Spk",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "SPK, open new file",
            ToolTip = "Create a new SPK file, returning the handle of the opened file"
            ))
        static void spkopn(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FString& name,
            const FString& ifname,
            int         ncomch,
            int64& handle
        );

    /// <summary>S/P Kernel, Unload ephemeris file</summary>
    /// <param name="handle">[in] Handle of file to be unloaded</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Spk",
        meta = (
            ShortToolTip = "S/P Kernel, Unload ephemeris file",
            ToolTip = "Unload an ephemeris file so that it will no longer be searched by the readers"
            ))
        static void spkuef(
            int64 handle
        );

    /// <summary>Write SPK segment, type 5</summary>
    /// <param name="handle">[in] Handle of an SPK file open for writing</param>
    /// <param name="body">[in] Body code for ephemeris object</param>
    /// <param name="center">[in] Body code for the center of motion of the body</param>
    /// <param name="frame">[in] The reference frame of the states</param>
    /// <param name="first">[in] First valid time for which states can be computed</param>
    /// <param name="last">[in] Last valid time for which states can be computed</param>
    /// <param name="segid">[in] Segment identifier</param>
    /// <param name="gm">[in] Gravitational parameter of central body</param>
    /// <param name="n">[in] Number of states and epochs</param>
    /// <param name="states">[in] States</param>
    /// <param name="epochs">[in] Epochs</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Spk",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Write SPK segment, type 5",
            ToolTip = "Write an SPK segment of type 5 given a time-ordered set of discrete states and epochs, and the gravitational parameter of a central body"
            ))
        static void spkw05(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            int64 handle,
            int64 body,
            int64 center,
            const FString& frame,
            const FSEphemerisTime& first,
            const FSEphemerisTime& last,
            const FString& segid,
            const FSMassConstant& gm,
            const TArray<FSPKType5Observation>& states
        );

    /// <summary>Seconds in a day</summary>
    /// <returns>Seconds.  Per day.</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Seconds per day",
            ToolTip = "The number of seconds in a day"
            ))
    static void spd(double& secondsPerDay);

    /// <summary>Seconds in a day</summary>
    /// <returns>Seconds.  Per day.</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "One Day",
            ToolTip = "Ephemeris period of one day"
            ))
    static void spd_day(FSEphemerisPeriod& oneDay);


    /// <summary>Spherical to latitudinal coordinates</summary>
    /// <param name="r">[in] Distance of the point from the origin</param>
    /// <param name="colat">[in] Angle of the point from positive z axis (radians)</param>
    /// <param name="lons">[in] Angle of the point from the XZ plane (radians)</param>
    /// <param name="radius">[out] Distance of a point from the origin</param>
    /// <param name="lon">[out] Angle of the point from the XZ plane in radians</param>
    /// <param name="lat">[out] Angle of the point from the XY plane in radians</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Geometry",
        meta = (
            ShortToolTip = "Spherical to latitudinal coordinates",
            ToolTip = "Convert from spherical coordinates to latitudinal coordinates"
            ))
        static void sphlat(
            const FSDistance& r,
            const FSAngle& colat,
            const FSAngle& lons,
            FSDistance& radius,
            FSLonLat& lonlat
        );

    /// <summary>Spherical to rectangular coordinates</summary>
    /// <param name="r">[in] Distance of a point from the origin</param>
    /// <param name="colat">[in] Angle of the point from the Z-axis in radians</param>
    /// <param name="lon">[in] Angle of the point from the XZ plane in radians</param>
    /// <param name="rectan">[out] Rectangular coordinates of the point</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Geometry",
        meta = (
            ShortToolTip = "Spherical to rectangular coordinates",
            ToolTip = "Convert from spherical coordinates to rectangular coordinates"
            ))
    static void sphrec(
        const FSDistance& r,
        const FSAngle& colat,
        const FSAngle& lon,
        FSDistanceVector& rectan
    );

    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Geometry",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Surface to rectangular coordinates",
            ToolTip = "Convert planetocentric latitude and longitude of a surface point on a specified body to rectangular coordinates"
            ))
    static void srfrec(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FSLonLat& lonlat,
        FSDistanceVector& rectan,
        int64           body = 399
        );

    /// <summary>String to ET</summary>
    /// <param name="str">[in] A string representing an epoch</param>
    /// <param name="et">[out] The equivalent value in seconds past J2000</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Time",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "String to ET",
            ToolTip = "Convert a string representing an epoch to a double precision value representing the number of TDB seconds past the J2000 epoch corresponding to the input epoch"
            ))
        static void str2et(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            FSEphemerisTime& et,
            const FString& str = TEXT("2021 October 1  15:37:60.5 (PST)")
        );


    /// <summary>Map surface points to outward normal vectors</summary>
    /// <param name="a">[in] Length of the ellisoid semi-axis along the x-axis</param>
    /// <param name="b">[in] Length of the ellisoid semi-axis along the y-axis</param>
    /// <param name="c">[in] Length of the ellisoid semi-axis along the z-axis</param>
    /// <param name="point">[in] Body-fixed coordinates of a point on the ellipsoid</param>
    /// <param name="normal">[out] Outward pointing unit normal to ellipsoid at point</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Geometry",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Surface normal vector on an ellipsoid",
            ToolTip = "computes the outward-pointing, unit normal vector from a point on the surface of an ellipsoid"
            ))
        static void surfnm(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FSDistance& a,
            const FSDistance& b,
            const FSDistance& c,
            const FSDistanceVector& point,
            FSDimensionlessVector& normal
        );

    /// <summary>Determine the intersection of a line-of-sight vector with the surface of an ellipsoid</summary>
    /// <param name="positn">[in] Position of the observer in body-fixed frame</param>
    /// <param name="u">[in] Vector from the observer in some direction</param>
    /// <param name="a">[in] Length of the ellipsoid semi-axis along the x-axis</param>
    /// <param name="b">[in] Length of the ellipsoid semi-axis along the y-axis</param>
    /// <param name="c">[in] Length of the ellipsoid semi-axis along the z-axis</param>
    /// <param name="point">[out] </param>
    /// <param name="found">[out] </param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Geometry",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Surface point on an ellipsoid",
            ToolTip = "Determine the intersection of a line-of-sight vector with the surface of an ellipsoid"
            ))
        static void surfpt(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FSDistanceVector& positn,
            const FSDimensionlessVector& u,
            const FSDistance& a,
            const FSDistance& b,
            const FSDistance& c,
            FSDistanceVector& point,
            bool& found
        );

    /// <summary>Return the state transformation matrix from one frame to another at a specified epoch</summary>
    /// <param name="from">[in] Name of the frame to transform from</param>
    /// <param name="to">[in] Name of the frame to transform to</param>
    /// <param name="et">[in] Epoch of the state transformation matrix</param>
    /// <param name="xform">[out] A state transformation matrix</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|State",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "State Transformation Matrix",
            ToolTip = "Return the state transformation matrix from one frame to another at a specified epoch"
            ))
        static void sxform(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FSEphemerisTime& et,
            FSStateTransform& xform,
            const FString& from = TEXT("IAU_EARTH"),
            const FString& to = TEXT("J2000")

        );

    /// <summary>Time Output</summary>
    /// <param name="et">[in] An epoch in seconds past the ephemeris epoch J2000</param>
    /// <param name="pictur">[in] A format specification for the output string</param>
    /// <param name="lenout">[in] The length of the output string plus 1</param>
    /// <param name="output">[out] A string representation of the input epoch</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Time",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Time Output",
            ToolTip = "Converts an input epoch represented in TDB seconds past the TDB epoch of J2000 to a character string formatted to the specifications of a user's format picture"
            ))
        static void timout(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            FString& output,
            const FSEphemerisTime& et,
            const FString& pictur = TEXT("MON DD,YYYY  HR:MN:SC.#### (TDB)")
        );

    /// <summary></summary>
    /// <param name="string">Input time string, UTC</param>
    /// <param name="lenout">Available space in output error message string</param>
    /// <param name="ReturnValue">Equivalent UTC seconds past J2000</param>
    /// <param name="errmsg">Descriptive error message</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Time",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Parse a UTC time string",
            ToolTip = "Parse a time string and return seconds past the J2000 epoch on a formal calendar"
            ))
        static void tparse(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            FSEphemerisTime& ReturnValue,
            const FString& string = TEXT("2021-10-01T22:46:52.18")
        );

    /// <summary>trace of a 3x3 matrix</summary>
    /// <param name="matrix">3x3 matrix of double precision numbers</param>
    /// <returns>trace of matrix, i.e. it is the sum of the diagonal elements of matrix</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Trace of a 3x3 matrix",
            ToolTip = "Return the trace of a 3x3 matrix"
            ))
        static void trace(
            const FSRotationMatrix& matrix,
            double& trace
        );

    /// <summary>Twice the value of pi</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Twice the value of pi",
            ToolTip = "Return twice the value of pi"
            ))
    static void twopi(
        double& two_pi
    );

    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Constants",
        meta = (
            ShortToolTip = "Angle of twice the value pi",
            ToolTip = "Return angle with twice the value of pi"
            ))
    static void twopi_angle(FSAngle& two_pi);

    /// <summary>Two vectors defining an orthonormal frame</summary>
    /// <param name="axdef">[in] Vector defining a principal axis</param>
    /// <param name="indexa">[in] Principal axis number of axdef (X=1, Y=2, Z=3)</param>
    /// <param name="plndef">[in] Vector defining (with axdef) a principal plane</param>
    /// <param name="indexp">[in] Second axis number (with indexa) of principal plane</param>
    /// <param name="mout">[out] Output rotation matrix</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Two vectors defining an orthonormal frame",
            ToolTip = "Find the transformation to the right-handed frame having a given vector as a specified axis and having a second given vector lying in a specified coordinate plane"
            ))
        static void twovec(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FSDimensionlessVector& axdef,
            ES_Axis                         indexa,
            const FSDimensionlessVector& plndef,
            ES_Axis                         indexp,
            FSRotationMatrix& mout
        );

    /// <summary>Compute the normalized cross product of two 3-vectors</summary>
    /// <param name="v1">[in] Left vector for cross product</param>
    /// <param name="v2">[in] Right vector for cross product</param>
    /// <param name="vout">[out] Normalized cross product (v1xv2) / |v1xv2|</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Unitized cross product, 3x3",
            ToolTip = "Compute the normalized cross product of two 3-vectors"
            ))
        static void ucrss(
            const FSDimensionlessVector& v1,
            const FSDimensionlessVector& v2,
            FSDimensionlessVector& vout
        );

    /// <summary>First derivative of a function, df(x)/dx</summary>
    /// <param name="udfunc">[in] Name of the routine</param>
    /// <param name="x">[in] Independent variable of 'udfunc'</param>
    /// <param name="dx">[in] Interval from 'x' for derivative calculation</param>
    /// <param name="deriv">[out] Approximate derivative of 'udfunc' at 'x'</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "First derivative of a function, df(x)/dx",
            ToolTip = "Calculate the first derivative of a caller-specified function using a three - point estimation"
            ))
        static void uddf(
            const FDerivativeDelegate& udfunc,
            double x,
            double dx,
            double& deriv
        );

    /// <summary>Transform time from one uniform scale to another.  The uniform time scales are TAI, TDT, TDB, ET, JED, JDTDB, JDTDT</summary>
    /// <param name="epoch">[in] An epoch to be converted</param>
    /// <param name="insys">[in] The time scale associated with the input epoch</param>
    /// <param name="outsys">[in] The time scale associated with the function value</param>
    /// <returns> d.p. in outsys that is equivalent to the epoch on the insys time scale</returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Time",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Uniform time scale transformation",
            ToolTip = "Transform time from one uniform scale to another.  The uniform time scales are TAI, TDT, TDB, ET, JED, JDTDB, JDTDT"
            ))
    static void unitim(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        double& out,
        double epoch,
        ES_TimeScale insys = ES_TimeScale::ET,
        ES_TimeScale outsys = ES_TimeScale::ET
    );

    /// <summary>Unit vector and norm, 3 dimensional</summary>
    /// <param name="v1">[in] Vector to be normalized</param>
    /// <param name="vout">[out] Unit vector v1</param>
    /// <param name="vmag">[out] Magnitude of v1</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Unit vector and norm, 3 dimensional",
            ToolTip = "Normalize a double precision 3-vector and return its magnitude"
            ))
        static void unorm_distance(
            const FSDistanceVector& v1,
            FSDimensionlessVector& vout,
            FSDistance& vmag
        );
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Unit vector and norm, 3 dimensional",
            ToolTip = "Normalize a double precision 3-vector and return its magnitude"
            ))
        static void unorm_velocity(
            const FSVelocityVector& v1,
            FSDimensionlessVector& vout,
            FSSpeed& vmag
        );
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Unit vector and norm, 3 dimensional",
            ToolTip = "Normalize a double precision 3-vector and return its magnitude"
            ))
        static void unorm_angular_velocity(
            const FSAngularVelocity& v1,
            FSDimensionlessVector& vout,
            FSAngularRate& vmag
        );
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Unit vector and norm, 3 dimensional",
            ToolTip = "Normalize a double precision 3-vector and return its magnitude"
            ))
        static void unorm(
            const FSDimensionlessVector& v1,
            FSDimensionlessVector& vout,
            double& vmag
        );

    /// <summary>UTC to Ephemeris Time</summary>
    /// <param name="utcstr">[in] Input time string, UTC</param>
    /// <param name="et">[out] Output epoch, ephemeris seconds past J2000</param>
    /// <returns></returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Time",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "UTC to Ephemeris Time",
            ToolTip = "Convert an input time from Calendar or Julian Date format, UTC, to ephemeris seconds past J2000"
            ))
        static void utc2et(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FString& utcstr,
            FSEphemerisTime& et
        );

    /// <summary>Vector addition, 3 dimensional</summary>
    /// <param name="v1">[in] First vector to be added</param>
    /// <param name="v2">[in] Second vector to be added</param>
    /// <param name="vout">[out] Sum vector, v1 + v2</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector addition, 3 dimensional",
            ToolTip = "Add two 3 dimensional vectors"
            ))
        static void vadd_distance(
            const FSDistanceVector& v1,
            const FSDistanceVector& v2,
            FSDistanceVector& vout
        );
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector addition, 3 dimensional",
            ToolTip = "Add two 3 dimensional vectors"
            ))
        static void vadd_velocity(
            const FSVelocityVector& v1,
            const FSVelocityVector& v2,
            FSVelocityVector& vout
        );
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector addition, 3 dimensional",
            ToolTip = "Add two 3 dimensional vectors"
            ))
        static void vadd_angular_velocity(
            const FSAngularVelocity& v1,
            const FSAngularVelocity& v2,
            FSAngularVelocity& vout
        );
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector addition, 3 dimensional",
            ToolTip = "Add two 3 dimensional vectors"
            ))
        static void vadd(
            const FSDimensionlessVector& v1,
            const FSDimensionlessVector& v2,
            FSDimensionlessVector& vout
        );

    /// <summary>Vector cross product, 3 dimensions</summary>
    /// <param name="">[in] Left hand vector for cross product</param>
    /// <param name="">[in] Right hand vector for cross product</param>
    /// <param name="">[out] Cross product v1xv2</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector cross product, 3 dimensions",
            ToolTip = "Compute the cross product of two 3-dimensional vectors"
            ))
        static void vcrss(
            const FSDimensionlessVector& v1,
            const FSDimensionlessVector& v2,
            FSDimensionlessVector& vout
        );

    /// <summary>Vector distance</summary>
    /// <param name="v1, v2">[in] Two 3-vectors</param>
    /// <returns>distance between v1 and v2</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector distance",
            ToolTip = "Return the distance between two three-dimensional vectors"
            ))
        static void vdist(
            const FSDimensionlessVector& v1,
            const FSDimensionlessVector& v2,
            double& out
        );
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector distance",
            ToolTip = "Return the distance between two three-dimensional vectors"
            ))
        static void vdist_distance(
            const FSDistanceVector& v1,
            const FSDistanceVector& v2,
            FSDistance& out
        );
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector distance",
            ToolTip = "Return the distance between two three-dimensional vectors"
            ))
        static void vdist_velocity(
            const FSVelocityVector& v1,
            const FSVelocityVector& v2,
            FSSpeed& out
        );

    /// <summary>Vector dot product, 3 dimensions</summary>
    /// <param name="v1">First vector in the dot product</param>
    /// <param name="v2">Second vector in the dot product</param>
    /// <returns>dot product of v1 and v2</returns>
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector dot product, 3 dimensions",
            ToolTip = "Compute the dot product of two double precision, 3-dimensional vectors"
            ))
        static void vdot(
            const FSDimensionlessVector& v1,
            const FSDimensionlessVector& v2,
            double& out
        );
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector dot product, 3 dimensions",
            ToolTip = "Compute the dot product of two double precision, 3-dimensional vectors"
            ))
        static void dot_distance(
            const FSDistanceVector& v1,
            const FSDistanceVector& v2,
            FSDistance& out
        );
    UFUNCTION(BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector dot product, 3 dimensions",
            ToolTip = "Compute the dot product of two double precision, 3-dimensional vectors"
            ))
        static void dot_velocity(
            const FSVelocityVector& v1,
            const FSVelocityVector& v2,
            FSSpeed& out
        );

    /* this is pointless in blueprints... */
#if 0
    /// <summary>Copy one vector to another</summary>
    /// <param name="vin">[in] 3-dimensional double precision vector</param>
    /// <param name="vout">[out] value of vin</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector equality, 3 dimensions",
            ToolTip = "Make one double precision 3-dimensional vector equal to another"
            ))
        static void vequ(
            const FSDimensionlessVector& vin,
            FSDimensionlessVector& vout
        );
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector equality, 3 dimensions",
            ToolTip = "Make one double precision 3-dimensional vector equal to another"
            ))
        static void vequ_distance(
            const FSDistanceVector& vin,
            FSDistanceVector& vout
        );
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector equality, 3 dimensions",
            ToolTip = "Make one double precision 3-dimensional vector equal to another"
            ))
        static void vequ_velocity(
            const FSVelocityVector& vin,
            FSVelocityVector& vout
        );
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector equality, 3 dimensions",
            ToolTip = "Make one double precision 3-dimensional vector equal to another"
            ))
        static void vequ_angular_velocity(
            const FSAngularVelocity& vin,
            FSAngularVelocity& vout
        );
#endif

    /// <summary>unit vector</summary>
    /// <param name="v1">[in] Vector to be unitized</param>
    /// <param name="vout">[out] Unit vector</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "",
            ToolTip = ""
            ))
        static void vhat(
            const FSDimensionlessVector& v1,
            FSDimensionlessVector& vout
        );
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "",
            ToolTip = ""
            ))
        static void vhat_distance(
            const FSDistanceVector& v1,
            FSDimensionlessVector& vout
        );
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "",
            ToolTip = ""
            ))
        static void vhat_velocity(
            const FSVelocityVector& v1,
            FSDimensionlessVector& vout
        );
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "",
            ToolTip = ""
            ))
        static void vhat_angular_velocity(
            const FSAngularVelocity& v1,
            FSDimensionlessVector& vout
        );

    /// <summary>Vector linear combination, 3 dimensions</summary>
    /// <param name="a">[in] Coefficient of v1</param>
    /// <param name="v1">[in] Vector in 3-space</param>
    /// <param name="b">[in] Coefficient of v2</param>
    /// <param name="v2">[in] Vector in 3-space</param>
    /// <param name="c">[in] Coefficient of v3</param>
    /// <param name="v3">[in] Vector in 3-space</param>
    /// <param name="sum">[out] Linear Vector Combination a*v1 + b*v2 + c*v3</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector linear combination, 3 dimensions",
            ToolTip = "Computes the vector linear combination a * v1 + b * v2 + c * v3 of double precision, 3 - dimensional vectors"
            ))
        static void vlcom3(
            double a,
            const FSDimensionlessVector& v1,
            double b,
            const FSDimensionlessVector& v2,
            double c,
            const FSDimensionlessVector& v3,
            FSDimensionlessVector& sum
        );
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector linear combination, 3 dimensions",
            ToolTip = "Computes the vector linear combination a * v1 + b * v2 + c * v3 of double precision, 3 - dimensional vectors"
            ))
        static void vlcom3_distance(
            double a,
            const FSDistanceVector& v1,
            double b,
            const FSDistanceVector& v2,
            double c,
            const FSDistanceVector& v3,
            FSDistanceVector& sum
        );

    /// <summary>Vector linear combination, 3 dimensions</summary>
    /// <param name="a">[in] Coefficient of v1</param>
    /// <param name="v1">[in] Vector in 3-space</param>
    /// <param name="b">[in] Coefficient of v2</param>
    /// <param name="v2">[in] Vector in 3-space</param>
    /// <param name="sum">[out] Linear Vector Combination a*v1 + b*v2</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector linear combination, 3 dimensions",
            ToolTip = "Compute a vector linear combination of two double precision, 3 - dimensional vectors"
            ))
        static void vlcom(
            double a,
            const FSDimensionlessVector& v1,
            double b,
            const FSDimensionlessVector& v2,
            FSDimensionlessVector& sum
        );

    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector linear combination, 3 dimensions",
            ToolTip = "Compute a vector linear combination of two double precision, 3 - dimensional vectors"
            ))
        static void vlcom_distance(
            double a,
            const FSDistanceVector& v1,
            double b,
            const FSDistanceVector& v2,
            FSDistanceVector& sum
        );

    /// <summary>Negation, 3 dimensions</summary>
    /// <param name="v1">[in] Vector to be negated</param>
    /// <param name="vout">[out] Negated vector -v1</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Minus V, \"-V\", 3 dimensions",
            ToolTip = "Negate a double precision 3-dimensional vector"
            ))
        static void vminus(
            const FSDimensionlessVector& v1,
            FSDimensionlessVector& vout
        );

    /// <summary>Vector norm, 3 dimension</summary>
    /// <param name="v1">[in] Vector whose magnitude is to be found</param>
    /// <returns>magnitude of v1 calculated in a numerically stable way</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector norm, 3 dimensions",
            ToolTip = "Compute the magnitude of a double precision, 3-dimensional vector"
            ))
        static void vnorm(
            const FSDimensionlessVector& v1,
            double& out
        );

    /// <summary>Vector norm, distance vector</summary>
    /// <param name="v1">[in] Vector whose magnitude is to be found</param>
    /// <returns>magnitude of v1 calculated in a numerically stable way</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector norm, distance vector",
            ToolTip = "Compute the magnitude of a distance vector"
            ))
    static void vnorm_distance(
        const FSDistanceVector& v1,
        FSDistance& out
    );

    /// <summary>Vector norm, velocity vector</summary>
    /// <param name="v1">[in] Vector whose magnitude is to be found</param>
    /// <returns>magnitude of v1 calculated in a numerically stable way</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector norm, velocity vector",
            ToolTip = "Compute the magnitude of a velocity vector"
            ))
    static void vnorm_velocity(
        const FSVelocityVector& v1,
        FSSpeed& out
    );


    /// <summary>Pack three scalar components into a vector</summary>
    /// <param name="x">[in] scalar x</param>
    /// <param name="y">[in] scalar y </param>
    /// <param name="z">[in] scalar z </param>
    /// <param name="v">[out] Equivalent 3-vector</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Pack three scalar components into a vector",
            ToolTip = "Pack three scalar components into a vector"
            ))
        static void vpack(
            double x,
            double y,
            double z,
            FSDimensionlessVector& v
        );


    /// <summary>Perpendicular component of a 3-vector</summary>
    /// <param name="">[in] The vector whose orthogonal component is sought</param>
    /// <param name="">[in] The vector used as the orthogonal reference</param>
    /// <param name="">[out] The component of a orthogonal to b</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Perpendicular component of a 3-vector",
            ToolTip = "Find the component of a vector that is perpendicular to a second vector"
            ))
        static void vperp(
            const FSDimensionlessVector& a,
            const FSDimensionlessVector& b,
            FSDimensionlessVector& p
        );

    /// <summary>Project a vector onto a specified plane, orthogonally</summary>
    /// <param name="vin">[in] Vector to be projected</param>
    /// <param name="plane">[in] A CSPICE plane onto which vin is projected</param>
    /// <param name="vout">[out] Vector resulting from projection</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "Vector projection onto plane",
            ToolTip = "Project a vector onto a specified plane, orthogonally"
            ))
        static void vprjp(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            const FSDimensionlessVector& vin,
            const FSPlane& plane,
            FSDimensionlessVector& vout
        );

    /// <summary>Vector projection, 3 dimensions</summary>
    /// <param name="a">[in] The vector to be projected</param>
    /// <param name="b">[in] The vector onto which a is to be projected</param>
    /// <param name="p">[out] The projection of a onto b</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector projection, 3 dimensions",
            ToolTip = "Finds the projection of one vector onto another vector. All vectors are 3 - dimensional"
            ))
        static void vproj(
            const FSDimensionlessVector& a,
            const FSDimensionlessVector& b,
            FSDimensionlessVector& p
        );

    /// <summary>Vector relative difference (scalar)</summary>
    /// <param name="v1, v2">[in] Input vectors</param>
    /// <returns>relative difference between V1 and V2</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector relative difference, 3 dimensions",
            ToolTip = "Return the relative difference between two 3-dimensional vectors"
            ))
        static void vrel(
            const FSDimensionlessVector& v1,
            const FSDimensionlessVector& v2,
            double& out
        );

    /// <summary>Vector rotation about an axis</summary>
    /// <param name="v">[in] Vector to be rotated</param>
    /// <param name="axis">[in] Axis of the rotation</param>
    /// <param name="theta">[in] Angle of rotation (radians)</param>
    /// <param name="r">[out] Result of rotating v about axis by theta</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector rotation about an axis",
            ToolTip = "Rotate a vector about a specified axis vector by a specified angle and return the rotated vector"
            ))
        static void vrotv(
            const FSDimensionlessVector& v,
            const FSDimensionlessVector& axis,
            const FSAngle& theta,
            FSDimensionlessVector& r
        );

    /// <summary>Vector scaling, 3 dimensions</summary>
    /// <param name="s">[in] Scalar to multiply a vector</param>
    /// <param name="v1">[in] Vector to be multiplied</param>
    /// <param name="vout">[out] Product vector, s*v1</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector scaling, 3 dimensions",
            ToolTip = "Multiply a scalar and a 3-dimensional double precision vector"
            ))
        static void vscl(
            double s,
            const FSDimensionlessVector& v1,
            FSDimensionlessVector& vout
        );

    /// <summary>Angular separation of vectors, 3 dimensions</summary>
    /// <param name="v1">First vector</param>
    /// <param name="v2">Second vector</param>
    /// <returns>is the angle between v1 and v2 expressed in radians</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Angular separation of vectors, 3 dimensions",
            ToolTip = "Find the separation angle in radians between two double precision, 3 - dimensional vectors.This angle is defined as zero if either vector is zero"
            ))
        static void vsep(
            const FSDimensionlessVector& v1,
            const FSDimensionlessVector& v2,
            FSAngle& out
        );

    /// <summary>Vector subtraction, 3 dimensions</summary>
    /// <param name="v1">[in] First vector (minuend)</param>
    /// <param name="v2">[in] Second vector (subtrahend)</param>
    /// <param name="vout">[out] Difference vector, v1 - v2</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Vector subtraction, 3 dimensions",
            ToolTip = "Compute the difference between two 3-dimensional, double precision vectors"
            ))
        static void vsub(
            const FSDimensionlessVector& v1,
            const FSDimensionlessVector& v2,
            FSDimensionlessVector& vout
        );

    /// <summary>Unpack three scalar components from a vector</summary>
    /// <param name="v">[in] 3-vector</param>
    /// <param name="x, y, z">[out] Scalar components of 3-vector</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Unpack three scalar components from a vector",
            ToolTip = "Unpack three scalar components from a vector"
            ))
        static void vupack(
            const FSDimensionlessVector& v,
            double& x,
            double& y,
            double& z
        );

    /// <summary></summary>
    /// <param name="v">[in] Vector to be tested</param>
    /// <returns>The function returns the value SPICETRUE if and only if v is the zero vector</returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Is a vector the zero vector?",
            ToolTip = "Indicate whether a 3-vector is the zero vector"
            ))
        void vzero(
            const FSDimensionlessVector& v,
            bool& is_zero
        );


    /// <summary>Convert a state transformation matrix to Euler angles and their derivatives with respect to a specified set of axes</summary>
    /// <param name="xform">A state transformation matrix</param>
    /// <param name="axisa">Axis A of the Euler angle factorization</param>
    /// <param name="axisb">Axis B of the Euler angle factorization</param>
    /// <param name="axisc">Axis C of the Euler angle factorization</param>
    /// <param name="eulang">An array of Euler angles and their derivatives</param>
    /// <param name="unique">Indicates if eulang is a unique representation</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ShortToolTip = "State transformation to Euler angles",
            ToolTip = "Convert a state transformation matrix to Euler angles and their derivatives with respect to a specified set of axes"
            ))
        static void xf2eul(
            ES_ResultCode& ResultCode,
            FString& ErrorMessage,
            FSEulerAngularState& eulang,
            bool& unique,
            const FSEulerAngularTransform& xform,
            ES_Axis             axis3 = ES_Axis::X,
            ES_Axis             axis2 = ES_Axis::Y,
            ES_Axis             axis1 = ES_Axis::Z
        );

    /// <summary>Transform to rotation and angular velocity</summary>
    /// <param name="xform">[in] state transformation matrix</param>
    /// <param name="rot">[out] rotation associated with xform</param>
    /// <param name="av">[out] angular velocity associated with xform</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Transform to rotation and angular velocity",
            ToolTip = "Determines the rotation matrix and angular velocity of the rotation from a state transformation matrix"
            ))
        static void xf2rav(
            const FSStateTransform& xform,
            FSRotationMatrix& rot,
            FSAngularVelocity& av
        );


    /// <summary>Transform a state between coordinate systems</summary>
    /// <param name="f">[in] Input state</param>
    /// <param name="input_coord_sys">[in] Current (input) coordinate system</param>
    /// <param name="output_coord_sys">[in] Desired (output) coordinate system</param>
    /// <param name="body">[in] Name or NAIF ID of body with which coordinates are associated</param>
    /// <param name="output_state">[out] Converted output state</param>
    /// <returns></returns>
    UFUNCTION(
        BlueprintCallable,
        Category = "Spice|Api|Math",
        meta = (
            ExpandEnumAsExecs = "ResultCode",
            ToolTip = "Transform a state between coordinate systems"
            ))
    static void xfmsta(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FSDimensionlessVector& in1,
        const FSDimensionlessVector& in2,
        FSDimensionlessVector& out1,
        FSDimensionlessVector& out2,
        ES_CoordinateSystem input_coord_sys = ES_CoordinateSystem::RECTANGULAR,
        ES_CoordinateSystem output_coord_sys = ES_CoordinateSystem::RECTANGULAR,
        const FString& body = TEXT("")
        );


    /// <summary>Transpose a matrix, 3x3</summary>
    /// <param name="m1">[in] 3x3 matrix to be transposed</param>
    /// <param name="mout">[out] Transpose of m1.  mout can overwrite m1</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Math",
        meta = (
            ShortToolTip = "Transpose a matrix, 3x3",
            ToolTip = "Indicate whether a 3-vector is the zero vector"
            ))
        static void xpose(
            const FSRotationMatrix& m1,
            FSRotationMatrix& mout
        );


    /// <summary></summary>
    /// <param name="string">Input time string, UTC</param>
    /// <param name="lenout">Available space in output error message string</param>
    /// <param name="sp2000">Equivalent UTC seconds past J2000</param>
    /// <param name="errmsg">Descriptive error message</param>
    /// <returns></returns>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Time",
        meta = (
            ShortToolTip = "Approximate current et (only suitable for visualizations)",
            ToolTip = "Approximate current ephemeris time, based on clock of local and sketchy CRT conversion"
            ))
    static void et_now(FSEphemerisTime& Now);


#if defined(IN_PROGRESS)
    static void pckfrm(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& pckRelativePath,
        TArray<int64>& ids
    );

    static void pckcov(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& pckFileRelativePath,
        int64           idcode,
        const TArray<FSWindowSegment>& mergeWith,
        TArray<FSWindowSegment>& coverage
    );



    static void gfoclt(
        ConstSpiceChar* occtyp,
        ConstSpiceChar* front,
        ConstSpiceChar* fshape,
        ConstSpiceChar* fframe,
        ConstSpiceChar* back,
        ConstSpiceChar* bshape,
        ConstSpiceChar* bframe,
        ConstSpiceChar* abcorr,
        ConstSpiceChar* obsrvr,
        SpiceDouble        step,
        SpiceCell* cnfine,
        SpiceCell* result
    );


    static void latsrf(
        ConstSpiceChar* method,
        ConstSpiceChar* target,
        SpiceDouble          et,
        ConstSpiceChar* fixref,
        SpiceInt             npts,
        ConstSpiceDouble     lonlat[][2],
        SpiceDouble          srfpts[][3]
    );

    static void dsksrf(
        ConstSpiceChar* dsk,
        SpiceInt          bodyid,
        SpiceCell* srfids
    );

    static void dskobj(
        ConstSpiceChar* dsk,
        SpiceCell* bodids
    );

    static void dskz02(
        SpiceInt               handle,
        ConstSpiceDLADescr* dladsc,
        SpiceInt* nv,
        SpiceInt* np
    );

    static void srfcss(
        SpiceInt          code,
        ConstSpiceChar* bodstr,
        SpiceInt          srflen,
        SpiceChar* srfstr,
        SpiceBoolean* isname
    );

    static void srfs2c(
        ConstSpiceChar* srfstr,
        ConstSpiceChar* bodstr,
        SpiceInt* code,
        SpiceBoolean* found
    );

    static void srfc2s(
        SpiceInt        code,
        SpiceInt        bodyid,
        SpiceInt        srflen,
        SpiceChar* srfstr,
        SpiceBoolean* isname
    );

    static void srfscc(
        ConstSpiceChar* srfstr,
        SpiceInt          bodyid,
        SpiceInt* code,
        SpiceBoolean* found
    );

    static void srfscc(
        ConstSpiceChar* srfstr,
        SpiceInt          bodyid,
        SpiceInt* code,
        SpiceBoolean* found
    );


    static void dskxv(
        SpiceBoolean         pri,
        ConstSpiceChar* target,
        SpiceInt             nsurf,
        ConstSpiceInt        srflst[],
        SpiceDouble          et,
        ConstSpiceChar* fixref,
        SpiceInt             nrays,
        ConstSpiceDouble     vtxarr[][3],
        ConstSpiceDouble     dirarr[][3],
        SpiceDouble          xptarr[][3],
        SpiceBoolean         fndarr[]
    );

    static void dskxsi(
        SpiceBoolean         pri,
        ConstSpiceChar* target,
        SpiceInt             nsurf,
        ConstSpiceInt        srflst[],
        SpiceDouble          et,
        ConstSpiceChar* fixref,
        ConstSpiceDouble     vertex[3],
        ConstSpiceDouble     raydir[3],
        SpiceInt             maxd,
        SpiceInt             maxi,
        SpiceDouble          xpt[3],
        SpiceInt* handle,
        SpiceDLADescr* dladsc,
        SpiceDSKDescr* dskdsc,
        SpiceDouble          dc[],
        SpiceInt             ic[],
        SpiceBoolean* found
    );

    static void subpnt(
        ConstSpiceChar* method,
        ConstSpiceChar* target,
        SpiceDouble            et,
        ConstSpiceChar* fixref,
        ConstSpiceChar* abcorr,
        ConstSpiceChar* obsrvr,
        SpiceDouble            spoint[3],
        SpiceDouble* trgepc,
        SpiceDouble            srfvec[3]
    );

    static void subslr(
        ConstSpiceChar* method,
        ConstSpiceChar* target,
        SpiceDouble            et,
        ConstSpiceChar* fixref,
        ConstSpiceChar* abcorr,
        ConstSpiceChar* obsrvr,
        SpiceDouble            spoint[3],
        SpiceDouble* trgepc,
        SpiceDouble            srfvec[3]
    );

    static SpiceDouble phaseq(
        SpiceDouble       et,
        ConstSpiceChar* target,
        ConstSpiceChar* illmn,
        ConstSpiceChar* obsrvr,
        ConstSpiceChar* abcorr
    );

    static void limbpt(
        ConstSpiceChar* method,
        ConstSpiceChar* target,
        SpiceDouble         et,
        ConstSpiceChar* fixref,
        ConstSpiceChar* abcorr,
        ConstSpiceChar* corloc,
        ConstSpiceChar* obsrvr,
        ConstSpiceDouble    refvec[3],
        SpiceDouble         rolstp,
        SpiceInt            ncuts,
        SpiceDouble         schstp,
        SpiceDouble         soltol,
        SpiceInt            maxn,
        SpiceInt            npts[],
        SpiceDouble         points[][3],
        SpiceDouble         epochs[],
        SpiceDouble         tangts[][3]
    );

    static void termpt(
        ConstSpiceChar* method,
        ConstSpiceChar* ilusrc,
        ConstSpiceChar* target,
        SpiceDouble           et,
        ConstSpiceChar* fixref,
        ConstSpiceChar* abcorr,
        ConstSpiceChar* corloc,
        ConstSpiceChar* obsrvr,
        ConstSpiceDouble      refvec[3],
        SpiceDouble           rolstp,
        SpiceInt              ncuts,
        SpiceDouble           schstp,
        SpiceDouble           soltol,
        SpiceInt              maxn,
        SpiceInt              npts[],
        SpiceDouble           points[][3],
        SpiceDouble           epochs[],
        SpiceDouble           trmvcs[][3]
    );

    static void fovray(
        ConstSpiceChar* inst,
        ConstSpiceDouble   raydir[3],
        ConstSpiceChar* rframe,
        ConstSpiceChar* abcorr,
        ConstSpiceChar* observer,
        SpiceDouble* et,
        SpiceBoolean* visible
    );

    static void fovtrg(
        ConstSpiceChar* inst,
        ConstSpiceChar* target,
        ConstSpiceChar* tshape,
        ConstSpiceChar* tframe,
        ConstSpiceChar* abcorr,
        ConstSpiceChar* obsrvr,
        SpiceDouble* et,
        SpiceBoolean* visible
    );

    static void occult(
        ConstSpiceChar* targ1,
        ConstSpiceChar* shape1,
        ConstSpiceChar* frame1,
        ConstSpiceChar* targ2,
        ConstSpiceChar* shape2,
        ConstSpiceChar* frame2,
        ConstSpiceChar* abcorr,
        ConstSpiceChar* obsrvr,
        SpiceDouble        et,
        SpiceInt* ocltid
    );

    static void gfdist(
        ConstSpiceChar* target,
        ConstSpiceChar* abcorr,
        ConstSpiceChar* obsrvr,
        ConstSpiceChar* relate,
        SpiceDouble          refval,
        SpiceDouble          adjust,
        SpiceDouble          step,
        SpiceInt             nintvls,
        SpiceCell* cnfine,
        SpiceCell* result
    );

    static void gfilum(
        ConstSpiceChar* method,
        ConstSpiceChar* angtyp,
        ConstSpiceChar* target,
        ConstSpiceChar* illmn,
        ConstSpiceChar* fixref,
        ConstSpiceChar* abcorr,
        ConstSpiceChar* obsrvr,
        ConstSpiceDouble     spoint[3],
        ConstSpiceChar* relate,
        SpiceDouble          refval,
        SpiceDouble          adjust,
        SpiceDouble          step,
        SpiceInt             nintvls,
        SpiceCell* cnfine,
        SpiceCell* result
    );

    static void gfpa(ConstSpiceChar* target,
        ConstSpiceChar* illmn,
        ConstSpiceChar* abcorr,
        ConstSpiceChar* obsrvr,
        ConstSpiceChar* relate,
        SpiceDouble          refval,
        SpiceDouble          adjust,
        SpiceDouble          step,
        SpiceInt             nintvls,
        SpiceCell* cnfine,
        SpiceCell* result);

    static void gfposc(
        ConstSpiceChar* target,
        ConstSpiceChar* frame,
        ConstSpiceChar* abcorr,
        ConstSpiceChar* obsrvr,
        ConstSpiceChar* crdsys,
        ConstSpiceChar* coord,
        ConstSpiceChar* relate,
        SpiceDouble          refval,
        SpiceDouble          adjust,
        SpiceDouble          step,
        SpiceInt             nintvls,
        SpiceCell* cnfine,
        SpiceCell* result
    );

    static void gfrr(
        ConstSpiceChar* target,
        ConstSpiceChar* abcorr,
        ConstSpiceChar* obsrvr,
        ConstSpiceChar* relate,
        SpiceDouble          refval,
        SpiceDouble          adjust,
        SpiceDouble          step,
        SpiceInt             nintvls,
        SpiceCell* cnfine,
        SpiceCell* result
    );

    static void gfsep(
        ConstSpiceChar* targ1,
        ConstSpiceChar* shape1,
        ConstSpiceChar* frame1,
        ConstSpiceChar* targ2,
        ConstSpiceChar* shape2,
        ConstSpiceChar* frame2,
        ConstSpiceChar* abcorr,
        ConstSpiceChar* obsrvr,
        ConstSpiceChar* relate,
        SpiceDouble          refval,
        SpiceDouble          adjust,
        SpiceDouble          step,
        SpiceInt             nintvls,
        SpiceCell* cnfine,
        SpiceCell* result
    );

    static void gfsntc(
        ConstSpiceChar* target,
        ConstSpiceChar* fixref,
        ConstSpiceChar* method,
        ConstSpiceChar* abcorr,
        ConstSpiceChar* obsrvr,
        ConstSpiceChar* dref,
        ConstSpiceDouble     dvec[3],
        ConstSpiceChar* crdsys,
        ConstSpiceChar* coord,
        ConstSpiceChar* relate,
        SpiceDouble          refval,
        SpiceDouble          adjust,
        SpiceDouble          step,
        SpiceInt             nintvls,
        SpiceCell* cnfine,
        SpiceCell* result
    );

    static void gfsubc(
        ConstSpiceChar* target,
        ConstSpiceChar* fixref,
        ConstSpiceChar* method,
        ConstSpiceChar* abcorr,
        ConstSpiceChar* obsrvr,
        ConstSpiceChar* crdsys,
        ConstSpiceChar* coord,
        ConstSpiceChar* relate,
        SpiceDouble          refval,
        SpiceDouble          adjust,
        SpiceDouble          step,
        SpiceInt             nintvls,
        SpiceCell* cnfine,
        SpiceCell* result
    );

    static void gfrfov(
        ConstSpiceChar* inst,
        ConstSpiceDouble     raydir[3],
        ConstSpiceChar* rframe,
        ConstSpiceChar* abcorr,
        ConstSpiceChar* obsrvr,
        SpiceDouble          step,
        SpiceCell* cnfine,
        SpiceCell* result
    );

    static void gftfov(
        ConstSpiceChar* inst,
        ConstSpiceChar* target,
        ConstSpiceChar* tshape,
        ConstSpiceChar* tframe,
        ConstSpiceChar* abcorr,
        ConstSpiceChar* obsrvr,
        SpiceDouble          step,
        SpiceCell* cnfine,
        SpiceCell* result
    );

    static void wninsd(
        SpiceDouble     left,
        SpiceDouble     right,
        SpiceCell* window
    );

    static void reccyl(
        ConstSpiceDouble     rectan[3],
        SpiceDouble* r,
        SpiceDouble* lon,
        SpiceDouble* z
    );

    static void cylrec(
        SpiceDouble r,
        SpiceDouble lon,
        SpiceDouble z,
        SpiceDouble rectan[3]
    );

    static void sphcyl(
        SpiceDouble     radius,
        SpiceDouble     colat,
        SpiceDouble     slon,
        SpiceDouble* r,
        SpiceDouble* lon,
        SpiceDouble* z
    );

    static void cylsph(
        SpiceDouble    r,
        SpiceDouble    lonc,
        SpiceDouble    z,
        SpiceDouble* radius,
        SpiceDouble* colat,
        SpiceDouble* lon
    );

    static void latsph(
        SpiceDouble    radius,
        SpiceDouble    lon,
        SpiceDouble    lat,
        SpiceDouble* rho,
        SpiceDouble* colat,
        SpiceDouble* lons
    );

    static void cyllat(
        SpiceDouble    r,
        SpiceDouble    lonc,
        SpiceDouble    z,
        SpiceDouble* radius,
        SpiceDouble* lon,
        SpiceDouble* lat
    );

    static void latcyl(
        SpiceDouble    radius,
        SpiceDouble    lon,
        SpiceDouble    lat,
        SpiceDouble* r,
        SpiceDouble* lonc,
        SpiceDouble* z
    );
#endif


public:
    static uint8 ErrorCheck(ES_ResultCode& ResultCode, FString& ErrorMessage);
    static uint8 UnexpectedErrorCheck(bool bReset = true);
};


