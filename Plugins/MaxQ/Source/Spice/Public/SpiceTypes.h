// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceTypes.h
// 
// API Comments
// 
// USpiceTypes : public UBlueprintFunctionLibrary
// 
// Purpose:
// Blueprint implementations of CSPICE UE-Type wrappers  
// 
// MaxQ:
// * Base API
// * Refined API
//    * C++
//    * Blueprints
//
// USpiceTypes is part of the base API, where CSPICE functionality is initially
// implemented/tested/studied.
// 
// This is the core Blueprint Library that exposes CSPICE types to Blueprints.
//
// The API here is maintained for compatibility with code depends on it (with
// breaking changes minimized, and deprecation > replacement).
// 
// SpiceTypes implements both the wrapped CSPICE Types (FSDistanceVector, etc)
// and the Blueprint Function Library that manipulates them.  This will
// eventually be refactored and broken down into multiple smaller units.
// E.g., this is just an initial working implementation and it's refactored
// over time, with things moving from the Base API to the Refined API, while
// the Base API maintains compatibility with client code.
//  
// See implementation comments in SpiceTypes.cpp.
//------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpicePlatformDefs.h"
#include "SpiceLog.h"
#include "SpiceEnums.h"
#include "SpiceStructs.h"
#include "SpiceTypes.generated.h"


// See:
// https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/getmsg_c.html
// "msglen  The current maximum long error message length is in fact 1840 characters"
constexpr uint32 SpiceLongMessageMaxLength = 1841;


// Container for Blueprint constants
USTRUCT(BlueprintType, Category = "MaxQ|Constants")
struct SPICE_API FConst
{
    GENERATED_BODY()
};



UCLASS(Category = "MaxQ")
class SPICE_API USpiceTypes : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    static double normalize180to180(double degrees);
    static double normalize0to360(double degrees);
    static double normalizePiToPi(double radians);
    static double normalizeZeroToTwoPi(double radians);
    static FString formatAngle(double degrees, ES_AngleFormat format);

public:
    // See notes below regarding EnumAsString.
    [[deprecated("Use MaxQ::Core::ToANSIString()")]]
    inline static const char* toString(ES_Units units) { return  MaxQ::Core::ToANSIString(units); }
    [[deprecated("Use MaxQ::Core::ToANSIString()")]]
    inline static const char* toString(ES_ReferenceFrameLocus locus) { return  MaxQ::Core::ToANSIString(locus); }
    [[deprecated("Use MaxQ::Core::ToANSIString()")]] 
    inline static const char* toString(ES_AberrationCorrectionFov abcorr) { return  MaxQ::Core::ToANSIString(abcorr); }
    [[deprecated("Use MaxQ::Core::ToANSIString()")]]
    inline static const char* toString(ES_AberrationCorrectionWithNewtonians abcorr) { return  MaxQ::Core::ToANSIString(abcorr); }
    [[deprecated("Use MaxQ::Core::ToANSIString()")]]
    inline static const char* toString(ES_AberrationCorrectionForOccultation abcorr) { return  MaxQ::Core::ToANSIString(abcorr); }
    [[deprecated("Use MaxQ::Core::ToANSIString()")]]
    inline static const char* toString(ES_AberrationCorrectionWithTransmissions abcorr) { return  MaxQ::Core::ToANSIString(abcorr); }
    [[deprecated("Use MaxQ::Core::ToANSIString()")]]
    inline static const char* toString(ES_AberrationCorrectionLocus corloc) { return  MaxQ::Core::ToANSIString(corloc); }
    [[deprecated("Use MaxQ::Core::ToANSIString()")]]
    inline static const char* toString(ES_AberrationCorrectionLocusTerminator corloc) { return  MaxQ::Core::ToANSIString(corloc); }
    [[deprecated("Use MaxQ::Core::ToANSIString()")]]
    inline static const char* toString(ES_TimeScale timeScale) { return  MaxQ::Core::ToANSIString(timeScale); }
    [[deprecated("Use MaxQ::Core::ToANSIString()")]]
    inline static const char* toString(ES_GeometricModel model) { return  MaxQ::Core::ToANSIString(model); }
    [[deprecated("Use MaxQ::Core::ToANSIString()")]]
    inline static const char* toString(ES_OtherGeometricModel model) { return  MaxQ::Core::ToANSIString(model); }
    [[deprecated("Use MaxQ::Core::ToANSIString()")]] 
    inline static const char* toString(ES_RelationalOperator relate) { return  MaxQ::Core::ToANSIString(relate); }
    [[deprecated("Use MaxQ::Core::ToANSIString()")]]
    inline static const char* toString(ES_CoordinateSystemInclRadec coords) { return  MaxQ::Core::ToANSIString(coords); }
    [[deprecated("Use MaxQ::Core::ToANSIString()")]]
    inline static const char* toString(ES_CoordinateSystem coords) { return  MaxQ::Core::ToANSIString(coords); }
    [[deprecated("Use MaxQ::Core::ToANSIString()")]]
    inline static const char* toString(ES_CoordinateName coord) { return  MaxQ::Core::ToANSIString(coord); }
    [[deprecated("Use MaxQ::Core::ToANSIString()")]]
    inline static const char* toString(ES_SubpointComputationMethod method) { return  MaxQ::Core::ToANSIString(method); }
    [[deprecated("Use MaxQ::Core::ToANSIString()")]]
    inline static const char* toString(ES_IlluminationAngleType angleType) { return  MaxQ::Core::ToANSIString(angleType); }

    [[deprecated("Use MaxQ::Core::ToString()")]]
    inline static FString toFString(ES_GeometricModel model, const TArray<FString>& shapeSurfaces) { return  MaxQ::Core::ToString(model, shapeSurfaces); }

    [[deprecated("Use MaxQ::Core::ToString()")]]
    inline static FString toFString(ES_ComputationMethod method, const TArray<FString>& shapeSurfaces) { return  MaxQ::Core::ToString(method, shapeSurfaces); }

    [[deprecated("Use MaxQ::Core::ToString()")]]
    inline static FString toFString(ES_LimbComputationMethod method, const TArray<FString>& shapeSurfaces) { return  MaxQ::Core::ToString(method, shapeSurfaces); }

    [[deprecated("Use MaxQ::Core::ToString()")]]
    inline static FString toFString(ES_Shadow shadow, ES_CurveType curveType, ES_GeometricModel method, const TArray<FString>& shapeSurfaces) { return  MaxQ::Core::ToString(shadow, curveType, method, shapeSurfaces); }

    [[deprecated("Use MaxQ::Core::ToString()")]]
    inline static FString ToString(ES_Axis Axis) { return  MaxQ::Core::ToString(Axis); }

    [[deprecated("Use MaxQ::Core::ToString()")]]
    inline static FString ToString(ES_KernelType KernelType) { return  MaxQ::Core::ToString(KernelType); }

    [[deprecated("Use MaxQ::Core::Parse<ES_KernelType>()")]]
    static ES_KernelType FromString(const FString& KernelType) { return  MaxQ::Core::Parse<ES_KernelType>(KernelType); }

    // ---------------------------------------------------------------------------
    // NOTE:
    // For API invocation, use the above (toString), not EnumAsString!
    // 
    // EnumAsString is lower maintenance, for sure.  But, it's an exchange of developer time
    // for end-user safety.  Using EnumAsString means renaming an enum, however innocently,
    // can break functionality and it's NOT caught at compile time.
    // It also breaks end-user code which may have already been tested etc etc.
    // EnumAsString is suitable for diagnostic messages etc etc.
    template<typename T> inline static const FString EnumAsString(const char* EnumName, T EnumValue)
    {
        static const FString InvalidEnum("Invalid");

        const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, UTF8_TO_TCHAR(EnumName), true);
        if (!EnumPtr)
        {
            return InvalidEnum;
        }
        return EnumPtr->GetNameStringByIndex(static_cast<int32>(EnumValue));
    }

public:

    static int FloatFormatPrecision;

    UFUNCTION(BlueprintCallable, Category = "MaxQ|Stringifier", meta = (ToolTip = "Set precision used to format floating point values"))
    static void SetFloatToStringPrecision(int _floatPrintPrecision);

    UFUNCTION(BlueprintPure, Category = "MaxQ|Stringifier", meta = (ToolTip = "double to string (uses SetFloatToStringPrecision)"))
    static FString FormatDouble(double value);

    UFUNCTION(BlueprintPure, Category = "MaxQ|Stringifier", meta = (ToolTip = "double to string"))
    static FString FormatDoublePrecisely(double value, int precision = 12);

    UFUNCTION(BlueprintPure, Category = "MaxQ|Stringifier", meta = (ToolTip = "SAngle to string"))
    static FString FormatAngle(const FSAngle& value, ES_AngleFormat format = ES_AngleFormat::DD);

    UFUNCTION(BlueprintPure, Category = "MaxQ|Stringifier", meta = (ToolTip = "SLongLat to string"))
    static FString FormatLonLat(const FSLonLat& value, const FString& separator = TEXT(", "), ES_AngleFormat format = ES_AngleFormat::DD);

    UFUNCTION(BlueprintPure, Category = "MaxQ|Stringifier", meta = (ToolTip = "Right Ascension, Declination to string"))
    static FString FormatRADec(const FSAngle& rightAscension, const FSAngle& declination, const FString& separator = TEXT(", "));

    UFUNCTION(BlueprintPure, Category = "MaxQ|Stringifier", meta = (ToolTip = "Distance To String", AdvancedDisplay = "precision"))
    static FString FormatDistance(const FSDistance& distance, ES_Units Units = ES_Units::KILOMETERS, int precision = 12);

    UFUNCTION(BlueprintPure, Category = "MaxQ|Stringifier", meta = (ToolTip = "Period To String", AdvancedDisplay = "precision"))
    static FString FormatPeriod(const FSEphemerisPeriod& period, ES_Units Units = ES_Units::SECONDS, int precision = 12);

    UFUNCTION(BlueprintPure, Category = "MaxQ|Stringifier", meta = (ToolTip = "Speed To String", AdvancedDisplay = "precision"))
    static FString FormatSpeed(const FSSpeed& speed, ES_Units NumeratorUnits = ES_Units::KILOMETERS, ES_Units DenominatorUnits = ES_Units::SECONDS, int precision = 12);

    UFUNCTION(BlueprintPure, Category = "MaxQ|Stringifier", meta = (ToolTip = "EphemerisTime To UTC String", AdvancedDisplay = "precision"))
    static FString FormatUtcTime(const FSEphemerisTime& time, ES_UTCTimeFormat TimeFormat = ES_UTCTimeFormat::Calendar, int precision = 4);

    /// <summary>Ephemeris period of one day</summary>
    /// <returns>One Day</returns>
    [[deprecated("Use SEphemerisPeriod_OneDay()")]]
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Constants",
        meta = (
            DeprecatedFunction,
            DeprecationMessage = "Use SEphemerisPeriod_OneDay",
            Keywords = "CONSTANTS, TIME",
            ShortToolTip = "One Day",
            ToolTip = "Ephemeris period of one day"
            ))
    static void day_period(FSEphemerisPeriod& oneDay);

    [[deprecated("Use SEphemerisTime_J2000()")]]
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Constants",
        meta = (
            DeprecatedFunction,
            DeprecationMessage = "Use SEphemerisTime_J2000",
            Keywords = "CONSTANTS, TIME",
            ShortToolTip = "Epoch at J2000",
            ToolTip = "Return the Epoch at Julian Date of 2000 JAN 1.5 (1 Jan 2000, 11:58:55.816 UTC)"
            ))
    static void j2000_epoch(FSEphemerisTime& J2000);

    UFUNCTION(BlueprintPure,
    Category = "MaxQ|Types",
    meta = (
        BlueprintAutocast,
        DisplayName = "To String (S_Units)",
        CompactNodeTitle = "->",
        Keywords = "CONVERSION",
        ToolTip = "Stringifies S_Units"
        ))
    static FString Conv_S_UnitsToString(
       ES_Units units
    );

    /// <summary>Converts a distance to a double (kilometers)</summary>
    UFUNCTION(BlueprintPure, 
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "To double (km)",
            Keywords = "CONVERSION",
            ToolTip = "Converts a distance to a double (kilometers)"
            ))
    static double Conv_SDistanceToDouble(
        const FSDistance& value
    );

    /// <summary>Converts a double (kilometers) to a distance</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "From double (km)",
            Keywords = "CONVERSION",
            ToolTip = "Converts a double (kilometers) to a distance"
            ))
    static FSDistance Conv_DoubleToSDistance(
        double value
    );

    /// <summary>Converts a speed to a double (kilometers/sec)</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "to double (km/s)",
            Keywords = "CONVERSION",
            ToolTip = "Converts a speed to a double (kilometers/sec)"
            ))
    static double Conv_SSpeedToDouble(
        const FSSpeed& value
    );

    /// <summary>Converts a double (kilometers/sec) to a speed</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "from double (km/s)",
            Keywords = "CONVERSION",
            ToolTip = "Converts a double (kilometers/sec) to a speed"
            ))
    static FSSpeed Conv_DoubleToSSpeed(
        double value
    );

    /// <summary>Converts a speed to a double (kilometers/sec)</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "to double (rads)",
            Keywords = "CONVERSION",
            ToolTip = "Converts an angle to a double (radians)"
            ))
    static double Conv_SAngleToDouble(
        const FSAngle& value
    );

    /// <summary>Converts a double (kilometers/sec) to a speed</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "from double (rads)",
            Keywords = "CONVERSION",
            ToolTip = "Converts an double (radians) to an angle"
            ))
    static FSAngle Conv_DoubleToSAngle(
        double value
    );

    /// <summary>Converts a speed to a double (kilometers/sec)</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "to double (rads/s)",
            Keywords = "CONVERSION",
            ToolTip = "Converts an angular rate to a double (radians/sec)"
            ))
    static double Conv_SAngularRateToDouble(
        const FSAngularRate& value
    );

    /// <summary>Converts a double (kilometers/sec) to a speed</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "from double (rads/s)",
            Keywords = "CONVERSION",
            ToolTip = "Converts a doouble (radians/sec) to an angular rate"
            ))
    static FSAngularRate Conv_DoubleToSAngularRate(
        double value
    );

    /// <summary>Converts an ephemeris time to a double (sec past J2000)</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "to double (sec-j2000)",
            Keywords = "CONVERSION",
            ToolTip = "Converts an ephemeris time to a double (sec past J2000)"
            ))
    static double Conv_SEphemerisTimeToDouble(
        const FSEphemerisTime& value
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "->",
            ShortToolTip = "String to Ephemeris Time.",
            Keywords = "CONVERSION",
            ToolTip = "Converts a string to an Ephemeris Time.  If the string fails to convert an error will remain signalled in SPICE, which the downstream computation will detect."
            ))
    static FSEphemerisTime Conv_StringToSEphemerisTime(const FString& time);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SEphemerisTime)",
            CompactNodeTitle = "->",
            Keywords = "CONVERSION",
            ScriptMethod = "ToString",
            ToolTip = "Converts an Ephemeris Time to a String"
            ))
    static FString Conv_SEphemerisTimeToString(const FSEphemerisTime& et);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SEphemerisPeriod)",
            CompactNodeTitle = "->",
            Keywords = "CONVERSION",
            ScriptMethod = "ToString",
            ToolTip = "Converts an Ephemeris Period to a String"
            ))
    static FString Conv_SEphemerisPeriodToString(const FSEphemerisPeriod& period);


    // This is common in Tick(float DeltaTime)
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "->",
            Keywords = "CONVERSION",
            ToolTip = "Converts a Float to an Ephemeris Period"
            ))
    static FSEphemerisPeriod Conv_FloatToSEphemerisPeriod(float period);


    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SMassConstant)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts Mass Constant to a String"
            ))
    static FString Conv_SMassConstantToString(const FSMassConstant& gm);


    /// <summary>Converts a double (sec past J2000) to an ephemeris time</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "from double (sec-j2000)",
            Keywords = "CONVERSION",
            ToolTip = "Converts a double (sec past J2000) to an ephemeris time"
            ))
    static FSEphemerisTime Conv_DoubleToSEphemerisTime(
        double value
    );

    /// <summary>Converts an ephemeris period to a double (sec)</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "->",
            Keywords = "CONVERSION",
            ToolTip = "Converts an ephemeris period to a double (sec)"
            ))
    static double Conv_SEphemerisPeriodToDouble(
        const FSEphemerisPeriod& value
    );

    /// <summary>Converts a double (sec) to an ephemeris period</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "->",
            Keywords = "CONVERSION",
            ToolTip = "Converts a double (sec) to an ephemeris period"
            ))
    static FSEphemerisPeriod Conv_DoubleToSEphemerisPeriod(
        double value
    );

    /// <summary>Converts a mass constant to a double</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "->",
            Keywords = "CONVERSION",
            ToolTip = "Converts a mass constant to a double"
            ))
    static double Conv_SMassConstantToDouble(
        const FSMassConstant& value
    );

    /// <summary>Converts a double to a mass constant</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "->",
            Keywords = "CONVERSION",
            ToolTip = "Converts a double to a mass constant"
            ))
    static FSMassConstant Conv_DoubleToSMassConstant(
        double value
    );

    /// <summary>Converts a velocity vector to a dimensionless vector (km/sec)</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "to dim'less (km/sec)",
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts a velocity vector to a dimensionless vector (km/sec)"
            ))
        static FSDimensionlessVector Conv_SVelocityVectorToSDimensionlessVector(
            const FSVelocityVector& value
        );

    /// <summary>Converts a dimensionless vector to a velocity vector (km/sec)</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES",
            CompactNodeTitle = "from dim'less (km/sec)",
            ToolTip = "Converts a dimensionless vector to a velocity vector (km/sec)"
            ))
        static FSVelocityVector Conv_SDimensionlessVectorToSVelocityVector(
            const FSDimensionlessVector& value
        );

    /// <summary>Converts an euler angle vector (rads) to a dimensionless vector</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts an euler angle vector (rads) to a dimensionless vector"
            ))
        static FSDimensionlessVector Conv_SEulerAnglesToSDimensionlessVector(
            const FSEulerAngles& value
        );

    /// <summary>Converts a dimensionless vector (rad) to an euler angle vector</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts a dimensionless vector (rad) to an euler angle vector"
            ))
        static FSEulerAngles Conv_SDimensionlessVectorToSEulerAngles(
            const FSDimensionlessVector& value
        );

    /// <summary>Converts an angular velocity vector to a dimensionless vector (km/sec)</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts an angular velocity vector to a dimensionless vector (rad/sec)"
            ))
        static FSDimensionlessVector Conv_SAngularVelocityToSDimensionlessVector(
            const FSAngularVelocity& value
        );

    /// <summary>Converts a dimensionless vector (km/sec) to an angular velocity vector</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts a dimensionless vector (km/sec) to an angular velocity vector"
            ))
        static FSAngularVelocity Conv_SDimensionlessVectorToSAngularVelocity(
            const FSDimensionlessVector& value
        );

    /// <summary>Converts a distance vector to a dimensionless vector (km)</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "to dim'less (km)",
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts a distance vector to a dimensionless vector (km)"
            ))
        static FSDimensionlessVector Conv_SDistanceVectorToSDimensionlessVector(
            const FSDistanceVector& value
        );

    /// <summary>Converts a dimensionless vector (double precision) to a distance vector</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "from dim'less (km)",
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts a dimensionless vector (double precision) to a distance vector"
            ))
    static FSDistanceVector Conv_SDimensionlessVectorToSDistanceVector(
        const FSDimensionlessVector& value
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts a dimensionless vector (double precision) to a rectangular state vector"
            ))
    static FSStateVector Conv_SDimensionlessStateVectorToSStateVector(
        const FSDimensionlessStateVector& value
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts a dimensionless vector (double precision) to a cylindrical state vector"
            ))
    static FSCylindricalStateVector Conv_SDimensionlessStateVectorToSCylindricalStateVector(
        const FSDimensionlessStateVector& value
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts a dimensionless vector (double precision) to a latitudinal state vector"
            ))
    static FSLatitudinalStateVector Conv_SDimensionlessStateVectorToSLatitudinalStateVector(
        const FSDimensionlessStateVector& value
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts a dimensionless vector (double precision) to a spherical state vector"
            ))
    static FSSphericalStateVector Conv_SDimensionlessStateVectorToSSphericalStateVector(
        const FSDimensionlessStateVector& value
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts a dimensionless vector (double precision) to a geodetic state vector"
            ))
    static FSGeodeticStateVector Conv_SDimensionlessStateVectorToSGeodeticStateVector(
        const FSDimensionlessStateVector& value
    );


    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts a dimensionless vector (double precision) to a planetographic state vector"
            ))
    static FSPlanetographicStateVector Conv_SDimensionlessStateVectorToSPlanetographicStateVector(
        const FSDimensionlessStateVector& value
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts a rectangular state vector to a dimensionless vector (double precision)"
            ))
    static FSDimensionlessStateVector Conv_SStateVectorToSDimensionlessStateVector(
        const FSStateVector& value
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts a cylindrical  state vector to a dimensionless vector (double precision)"
            ))
    static FSDimensionlessStateVector Conv_SCylindricalStateVectorToSDimensionlessStateVector(
        const FSCylindricalStateVector& value
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts a latitudinal state vector to a dimensionless vector (double precision)"
            ))
    static FSDimensionlessStateVector Conv_SLatitudinalStateVectorToSDimensionlessStateVector(
        const FSLatitudinalStateVector& value
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts a spherical state vector to a dimensionless vector (double precision)"
            ))
    static FSDimensionlessStateVector Conv_SSphericalStateVectorToSDimensionlessStateVector(
        const FSSphericalStateVector& value
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts a geodetic state vector to a dimensionless vector (double precision)"
            ))
    static FSDimensionlessStateVector Conv_FSGeodeticStateVectorToSDimensionlessStateVector(
        const FSGeodeticStateVector& value
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Types",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Converts a planetographic state vector to a dimensionless vector (double precision)"
            ))
    static FSDimensionlessStateVector Conv_FSPlanetographicStateVectorToSDimensionlessStateVector(
        const FSPlanetographicStateVector& value
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SAngle)",
            Keywords = "STRING",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts SAngle to a String"
            ))
    static FString Conv_SAngleToString (const FSAngle& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SDistance)",
            Keywords = "STRING",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts Distance to a String"
            ))
    static FString Conv_SDistanceToString(const FSDistance& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SDistanceVector)",
            Keywords = "STRING",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a DistanceVector to a String"
            ))
    static FString Conv_SDistanceVectorToString(const FSDistanceVector& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SVelocityVector)",
            Keywords = "STRING",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SVelocityVector to a String"
            ))
    static FString Conv_SVelocityVectorToString(const FSVelocityVector& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SStateVector)",
            Keywords = "STRING",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SStateVector to a String"
            ))
    static FString Conv_SStateVectorToString(const FSStateVector& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SLonLat)",
            Keywords = "STRING",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SLonLat to a String"
            ))
    static FString Conv_SLonLatToString(const FSLonLat& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SSpeed)",
            Keywords = "STRING",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SSpeed to a String"
            ))
    static FString Conv_SSpeedToString(const FSSpeed& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SAngularRate)",
            Keywords = "STRING",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SAngularRate to a String"
            ))
    static FString Conv_SAngularRateToString(const FSAngularRate& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SDimensionlessVector)",
            Keywords = "STRING",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SDimensionlessVector to a String"
            ))
    static FString Conv_SDimensionlessVectorToString(const FSDimensionlessVector& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SDimensionlessStateVector)",
            Keywords = "STRING",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SDimensionlessStateVector to a String"
            ))
    static FString Conv_SDimensionlessStateVectorToString(const FSDimensionlessStateVector& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SPlanetographicStateVector)",
            Keywords = "STRING",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SPlanetographicStateVector to a String"
            ))
    static FString Conv_SPlanetographicStateVectorToString(const FSPlanetographicStateVector& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SGeodeticStateVector)",
            Keywords = "STRING",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SGeodeticStateVector to a String"
            ))
    static FString Conv_SGeodeticStateVectorToString(const FSGeodeticStateVector& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SSphericalStateVector)",
            Keywords = "STRING",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SSphericalStateVector to a String"
            ))
    static FString Conv_SSphericalStateVectorToString(const FSSphericalStateVector& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SLatitudinalStateVector)",
            Keywords = "STRING",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SLatitudinalStateVector to a String"
            ))
    static FString Conv_SLatitudinalStateVectorToString(const FSLatitudinalStateVector& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SCylindricalStateVector)",
            Keywords = "STRING",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SCylindricalStateVector to a String"
            ))
    static FString Conv_SCylindricalStateVectorToString(const FSCylindricalStateVector& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SPlanetographicVector)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SPlanetographicVector to a String"
            ))
    static FString Conv_SPlanetographicVectorToString(const FSPlanetographicVector& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SGeodeticVector)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SGeodeticVector to a String"
            ))
    static FString Conv_SGeodeticVectorToString(const FSGeodeticVector& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SSphericalVector)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SSphericalVector to a String"
            ))
    static FString Conv_SSphericalVectorToString(const FSSphericalVector& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SLatitudinalVector)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SLatitudinalVector to a String"
            ))
    static FString Conv_SLatitudinalVectorToString(const FSLatitudinalVector& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SCylindricalVector)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SCylindricalVector to a String"
            ))
    static FString Conv_SCylindricalVectorToString(const FSCylindricalVector& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SPlanetographicVectorRates)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SPlanetographicVectorRates to a String"
            ))
    static FString Conv_SPlanetographicVectorRatesToString(const FSPlanetographicVectorRates& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SGeodeticVectorRates)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SGeodeticVectorRates to a String"
            ))
    static FString Conv_SGeodeticVectorRatesToString(const FSGeodeticVectorRates& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SSphericalVectorRates)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SSphericalVectorRates to a String"
            ))
    static FString Conv_SSphericalVectorRatesToString(const FSSphericalVectorRates& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SLatitudinaVectorRates)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SLatitudinaVectorRates to a String"
            ))
    static FString Conv_SLatitudinaVectorRatesToString(const FSLatitudinalVectorRates& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SCylindricalVectorRates)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SCylindricalVectorRates to a String"
            ))
    static FString Conv_SCylindricalVectorRatesToString(const FSCylindricalVectorRates& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SConicElements)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SConicElements to a String"
            ))
    static FString Conv_SConicElementsToString(const FSConicElements& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SComplexScalar)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SComplexScalar to a String"
            ))
    static FString Conv_SComplexScalarToString(const FSComplexScalar& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SEulerAngles)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SEulerAngles to a String"
            ))
    static FString Conv_SEulerAnglesToString(const FSEulerAngles& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SEulerAngularState)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SEulerAngularState to a String"
            ))
    static FString Conv_SEulerAngularStateToString(const FSEulerAngularState& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SStateTransform)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SStateTransform to a String"
            ))
    static FString Conv_SStateTransformToString(const FSStateTransform& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SRotationMatrix)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SRotationMatrix to a String"
            ))
    static FString Conv_SRotationMatrixToString(const FSRotationMatrix& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SEllipse)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SEllipse to a String"
            ))
    static FString Conv_SEllipseToString(const FSEllipse& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SPlane)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SPlane to a String"
            ))
    static FString Conv_SPlaneToString(const FSPlane& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SEulerAngular)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SEulerAngular to a String"
            ))
    static FString Conv_SEulerAngularTransformToString(const FSEulerAngularTransform& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SEquinoctialElements)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SEquinoctialElements to a String"
            ))
    static FString Conv_SEquinoctialElementsToString(const FSEquinoctialElements& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SWindowSegment)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SWindowSegment to a String"
            ))
    static FString Conv_SWindowSegmentToString(const FSWindowSegment& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SPointingType2Observation)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SPointingType2Observation to a String"
            ))
    static FString Conv_SPointingType2ObservationToString(const FSPointingType2Observation& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SPointingType1Observation)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SPointingType1Observation to a String"
            ))
    static FString Conv_SPointingType1ObservationToString(const FSPointingType1Observation& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SPointingType5Observation)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SPointingType5Observation to a String"
            ))
    static FString Conv_SPointingType5ObservationToString(const FSPointingType5Observation& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SPKType5Observation)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SPKType5Observation to a String"
            ))
    static FString Conv_SPKType5ObservationToString(const FSPKType5Observation& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (STermptPoint)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a STermptPoint to a String"
            ))
    static FString Conv_STermptPointToString(const FSTermptPoint& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (STermptCut)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a STermptCut to a String"
            ))
    static FString Conv_STermptCutToString(const FSTermptCut& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (STLEGeophysicalConstants)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a STLEGeophysicalConstants to a String"
            ))
    static FString Conv_STLEGeophysicalConstantsToString(const FSTLEGeophysicalConstants& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SLimptPoint)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SLimptPoint to a String"
            ))
    static FString Conv_SLimptPointToString(const FSLimptPoint& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SLimptCut)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SLimptCut to a String"
            ))
    static FString Conv_SLimptCutToString(const FSLimptCut& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SPKType15Observation)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SPKType15Observation to a String"
            ))
    static FString Conv_SPKType15ObservationToString(const FSPKType15Observation& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (STwoLineElements)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a STwoLineElements to a String"
            ))
    static FString Conv_STwoLineElementsToString(const FSTwoLineElements& value);


    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SRay)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SRay to a String"
            ))
    static FString Conv_SRayToString(const FSRay& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SDLADescr)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SDLADescr to a String"
            ))
    static FString Conv_SDLADescrToString(const FSDLADescr& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SDSKDescr)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SDSKDescr to a String"
            ))
    static FString Conv_SDSKDescrToString(const FSDSKDescr& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            Keywords = "STRING",
            DisplayName = "To String (SPlateIndices)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SPlateIndices to a String"
            ))
    static FString Conv_SPlateIndicesToString(const FSPlateIndices& value);

    /* Multiplication (A * B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "matrix * matrix", CompactNodeTitle = "*", Keywords = "* multiply", CommutativeAssociativeBinaryOperator = "true"), Category = "MaxQ|Math|Rotation")
    static FSRotationMatrix Multiply_SRotationMatrixSRotationMatrix(const FSRotationMatrix& A, const FSRotationMatrix& B);

    UFUNCTION(BlueprintPure, meta = (DisplayName = "matrix * vector", CompactNodeTitle = "m*vec", Keywords = "* multiply"), Category = "MaxQ|Math|Rotation")
    static FSDimensionlessVector MultiplyVec_SRotationMatrixSDimensionlessVector(const FSRotationMatrix& A, const FSDimensionlessVector& B);

    UFUNCTION(BlueprintPure, meta = (DisplayName = "matrix * distance", CompactNodeTitle = "m*dist", Keywords = "* multiply"), Category = "MaxQ|Math|Rotation")
    static FSDistanceVector MultiplyDist_SRotationMatrixSDistanceVector(const FSRotationMatrix& A, const FSDistanceVector& B);

    UFUNCTION(BlueprintPure, meta = (DisplayName = "matrix * velocity", CompactNodeTitle = "m*vel", Keywords = "* multiply"), Category = "MaxQ|Math|Rotation")
    static FSVelocityVector MultiplyVel_SRotationMatrixVelocityVector(const FSRotationMatrix& A, const FSVelocityVector& B);

    UFUNCTION(BlueprintPure, meta = (DisplayName = "quaterion * quaterion", CompactNodeTitle = "*", Keywords = "* multiply", CommutativeAssociativeBinaryOperator = "true"), Category = "MaxQ|Math|Rotation")
    static FSQuaternion Multiply_SQuaternionSQuaternion(const FSQuaternion& A, const FSQuaternion& B);

    /* Addition (A + B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "time + period", CompactNodeTitle = "+", Keywords = "+ add plus"), Category = "MaxQ|Math|Time")
    static FSEphemerisTime Add_SEphemerisTimeSEphemerisPeriod(const FSEphemerisTime& A, const FSEphemerisPeriod& B);

    /** Returns true if A is greater than B (A > B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "time > time", CompactNodeTitle = ">", Keywords = "> greater"), Category = "MaxQ|Math|Time")
    static bool Greater_SEphemerisTimeSEphemerisTime(const FSEphemerisTime& A, const FSEphemerisTime& B);

    /** Returns true if A is less than B (A < B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "time < time", CompactNodeTitle = "<", Keywords = "< less"), Category = "MaxQ|Math|Time")
    static bool Less_SEphemerisTimeSEphemerisTime(const FSEphemerisTime& A, const FSEphemerisTime& B);

    /** Returns true if A is greater than B (A > B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "period > period", CompactNodeTitle = ">", Keywords = "> greater"), Category = "MaxQ|Math|Time")
    static bool Greater_SEphemerisPeriodSEphemerisPeriod(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B);

    /** Returns true if A is less than B (A < B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "period < period", CompactNodeTitle = "<", Keywords = "< less"), Category = "MaxQ|Math|Time")
    static bool Less_SEphemerisPeriodSEphemerisPeriod(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B);

    /* Addition (A + B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "period + period", CompactNodeTitle = "+", Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true"), Category = "MaxQ|Math|Time")
    static FSEphemerisPeriod Add_SEphemerisPeriodSEphemerisPeriod(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B);

    /* Subtraction (A - B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "period - period", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "MaxQ|Math|Time")
    static FSEphemerisPeriod Subtract_SEphemerisPeriodSEphemerisPeriod(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B);

    /* Subtraction (A - B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "time - time", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "MaxQ|Math|Time")
    static FSEphemerisPeriod Subtract_SEphemerisTimeSEphemerisTime(const FSEphemerisTime& A, const FSEphemerisTime& B);

    /* Multiplication (A * B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "period * double", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "MaxQ|Math|Time")
    static FSEphemerisPeriod Multiply_SEphemerisPeriodDouble(const FSEphemerisPeriod& A, double B);

    /* Division (A / B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "period / double", CompactNodeTitle = "/", Keywords = "/ divide"), Category = "MaxQ|Math|Time")
    static FSEphemerisPeriod Divide_SEphemerisPeriodDouble(const FSEphemerisPeriod& A, double B);

    /* Ratio (A / B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "period ratio", CompactNodeTitle = "ratio", Keywords = "/ divide"), Category = "MaxQ|Math|Time")
    static double Ratio_SEphemerisPeriod(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B);

    /* Modulo (A % B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "period % (double)", CompactNodeTitle = "%", Keywords = "% modulus"), Category = "MaxQ|Math|Time")
    static FSEphemerisPeriod Modulus_SEphemerisPeriodDouble(const FSEphemerisPeriod& A, double B);

    //////////////////////
    /* Multiplication (A * B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance * double", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "MaxQ|Math|Distance")
    static FSDistance Multiply_SDistanceDouble(const FSDistance& A, double B);

    /* Division (A / B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance / double", CompactNodeTitle = "/", Keywords = "/ divide"), Category = "MaxQ|Math|Distance")
    static FSDistance Divide_SDistanceDouble(const FSDistance& A, double B);

    /* Ratio (A / B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance ratio", CompactNodeTitle = "ratio", Keywords = "/ divide"), Category = "MaxQ|Math|Distance")
    static double Ratio_SDistance(const FSDistance& A, const FSDistance& B);

    /* Subtraction (A - B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance - distance", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "MaxQ|Math|Distance")
    static FSDistance Subtract_SDistanceSDistance(const FSDistance& A, const FSDistance& B);

    /*  Addition (A + B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance + distance", CompactNodeTitle = "+", Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true"), Category = "MaxQ|Math|Distance")
    static FSDistance Add_SDistanceSDistance(const FSDistance& A, const FSDistance& B);

    /** Returns true if A is less than B (A < B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance < distance", CompactNodeTitle = "<", Keywords = "< less"), Category = "MaxQ|Math|Distance")
    static bool Less_SDistanceSDistance(const FSDistance& A, const FSDistance& B);

    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance > distance", CompactNodeTitle = ">", Keywords = "> greater"), Category = "MaxQ|Math|Distance")
    static bool Greater_SDistanceSDistance(const FSDistance& A, const FSDistance& B);

    //////////////////////
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance vector * double vector", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "MaxQ|Math|Distance")
    static FSDistanceVector Multiply_SDistanceVectorDouble(const FSDistanceVector& A, double B);
    
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance - distance", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "MaxQ|Math|Distance")
    static FSDistanceVector Subtract_SDistanceVectorSDistanceVector(const FSDistanceVector& A, const FSDistanceVector& B);
    
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance vector + distance vector", CompactNodeTitle = "+", Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true"), Category = "MaxQ|Math|Distance")
    static FSDistanceVector Add_SDistanceVectorSDistanceVector(const FSDistanceVector& A, const FSDistanceVector& B);

    UFUNCTION(BlueprintPure, meta = (DisplayName = "ratio distance vector", CompactNodeTitle = "ratio", Keywords = "/ divide"), Category = "MaxQ|Math|Distance")
    static FSDimensionlessVector Ratio_SDistanceVector(const FSDistanceVector& A, const FSDistanceVector& B);

    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance vector / distance vector", CompactNodeTitle = "/", Keywords = "/ divide"), Category = "MaxQ|Math|Distance")
    static FSDistanceVector Divide_SDistanceVectorSDimensionlessVector(const FSDistanceVector& A, const FSDimensionlessVector& B);

    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance vector / double", CompactNodeTitle = "/", Keywords = "/ divide"), Category = "MaxQ|Math|Distance")
    static FSDistanceVector Divide_SDistanceVectorDouble(const FSDistanceVector& A, double B);

    //////////////////////
    /* Multiplication (A * B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "speed * double", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "MaxQ|Math|Speed")
    static FSSpeed Multiply_SSpeedDouble(const FSSpeed& A, double B);

    /* Division (A / B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "speed / double", CompactNodeTitle = "/", Keywords = "/ divide"), Category = "MaxQ|Math|Speed")
    static FSSpeed Divide_SSpeedDouble(FSSpeed A, double B);

    /* Ratio (A / B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "speed / speed", CompactNodeTitle = "ratio", Keywords = "/ divide"), Category = "MaxQ|Math|Speed")
    static double Ratio_SSpeed(const FSSpeed& A, const FSSpeed& B);

    /* Subtraction (A - B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "speed - speed", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "MaxQ|Math|Speed")
    static FSSpeed Subtract_SSpeedSSpeed(const FSSpeed& A, const FSSpeed& B);

    /*  Addition (A + B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "speed + speed", CompactNodeTitle = "+", Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true"), Category = "MaxQ|Math|Speed")
    static FSSpeed Add_SSpeedSSpeed(const FSSpeed& A, const FSSpeed& B);

    UFUNCTION(BlueprintPure, meta = (DisplayName = "speed < speed", CompactNodeTitle = "<", Keywords = "< less"), Category = "MaxQ|Math|Speed")
    static bool Less_SSpeedSSpeed(const FSSpeed& A, const FSSpeed& B);

    UFUNCTION(BlueprintPure, meta = (DisplayName = "speed > speed", CompactNodeTitle = ">", Keywords = "> greater"), Category = "MaxQ|Math|Speed")
    static bool Greater_SSpeedSSpeed(const FSSpeed& A, const FSSpeed& B);


    //////////////////////
    //////////////////////
    /* Multiplication (A * B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "angle * double", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "MaxQ|Math|Angle")
    static FSAngle Multiply_SAngleDouble(const FSAngle& A, double B);

    /* Division (A / B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "angle / double", CompactNodeTitle = "/", Keywords = "/ divide"), Category = "MaxQ|Math|Angle")
    static FSAngle Divide_SAngleDouble(const FSAngle A, double B);

    /* Ratio (A / B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "angle ratio", CompactNodeTitle = "ratio", Keywords = "/ divide"), Category = "MaxQ|Math|Angle")
    static double Ratio_SAngle(const FSAngle& A, const FSAngle& B);

    /* Subtraction (A - B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "angle - angle", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "MaxQ|Math|Angle")
    static FSAngle Subtract_SAngleSAngle(const FSAngle& A, const FSAngle& B);

    /*  Addition (A + B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "angle + angle", CompactNodeTitle = "+", Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true"), Category = "MaxQ|Math|Angle")
    static FSAngle Add_SAngleSAngle(const FSAngle& A, const FSAngle& B);


    /* Multiplication (A * B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "velocity * double", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "MaxQ|Math|Velocity")
    static FSVelocityVector Multiply_SVelocityVectorDouble(const FSVelocityVector& A, double B);

    /* Division (A / B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "velocity / double", CompactNodeTitle = "/", Keywords = "/ divide"), Category = "MaxQ|Math|Velocity")
    static FSVelocityVector Divide_SVelocityVectorDouble(const FSVelocityVector& A, double B);

    /* Ratio (A / B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "velocity ratio", CompactNodeTitle = "ratio", Keywords = "/ divide"), Category = "MaxQ|Math|Velocity")
    static FSDimensionlessVector Ratio_SVelocityVector(const FSVelocityVector& A, const FSVelocityVector& B);

    /* Subtraction (A - B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "velocity - velocity", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "MaxQ|Math|Velocity")
    static FSVelocityVector Subtract_SVelocityVectorSVelocityVector(const FSVelocityVector& A, const FSVelocityVector& B);

    /*  Addition (A + B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "velocity + velocity", CompactNodeTitle = "+", Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true"), Category = "MaxQ|Math|Velocity")
    static FSVelocityVector Add_SVelocityVectorSVelocityVector(const FSVelocityVector& A, const FSVelocityVector& B);

    /* Multiplication (A * B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "speed * vector", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "MaxQ|Math|Speed")
    static FSVelocityVector Multiply_SSpeedSDimensionlessVector(const FSSpeed& A, const FSDimensionlessVector& B);

    /* Multiplication (A * B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance * dimensionless", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "MaxQ|Math|Distance")
    static FSDistanceVector Multiply_SDistanceSDimensionlessVector(const FSDistance& A, const FSDimensionlessVector& B);

    UFUNCTION(BlueprintPure, meta = (DisplayName = "vector * double", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "MaxQ|Math|Dimensionless")
    static FSDimensionlessVector Multiply_SDimensionlessVectorDouble(const FSDimensionlessVector& A, double B);

    /* Division (A / B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "vector / double", CompactNodeTitle = "/", Keywords = "/ divide"), Category = "MaxQ|Math|Dimensionless")
    static FSDimensionlessVector Divide_SDimensionlessVectorDouble(const FSDimensionlessVector& A, double B);

    /* Subtraction (A - B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "velocity - velocity", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "MaxQ|Math|Dimensionless")
    static FSDimensionlessVector Subtract_SDimensionlessVectorSDimensionlessVector(const FSDimensionlessVector& A, const FSDimensionlessVector& B);

    /*  Addition (A + B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "velocity + velocity", CompactNodeTitle = "+", Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true"), Category = "MaxQ|Math|Dimensionless")
    static FSDimensionlessVector Add_SDimensionlessVectorSDimensionlessVector(const FSDimensionlessVector& A, const FSDimensionlessVector& B);

    // Multipication works fine, so may deprecate this in the future.
    UFUNCTION(BlueprintPure, meta = (DisplayName = "speed * vector", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "MaxQ|Math|Speed")
    static FSVelocityVector SpeedToVelocity(const FSSpeed& A, const FSDimensionlessVector& B);

    // Multipication works fine, so may deprecate this in the future.
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance * dimensionless", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "MaxQ|Math|Distance")
    static FSDistanceVector DistanceToVector(const FSDistance& A, const FSDimensionlessVector& B);


    UFUNCTION(BlueprintPure, meta = (DisplayName = "double * vector", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "MaxQ|Math|Dimensionless")
    static FSDimensionlessVector ScaleDimensionlessVector(double A, const FSDimensionlessVector& B);

    // Negation
    UFUNCTION(BlueprintPure, meta = (ScriptMethod = "Negated", ScriptOperator = "neg"), Category = "MaxQ|Math|Distance")
    static FSDistance NegateSDistance(const FSDistance& d);

    UFUNCTION(BlueprintPure, meta = (ScriptMethod = "Negated", ScriptOperator = "neg"), Category = "MaxQ|Math|Speed")
    static FSSpeed NegateSSpeed(const FSSpeed& v);

    UFUNCTION(BlueprintPure, meta = (ScriptMethod = "Negated", ScriptOperator = "neg"), Category = "MaxQ|Math|Angle")
    static FSAngle NegateSAngle(const FSAngle& Th);

    UFUNCTION(BlueprintPure, meta = (ScriptMethod = "Negated", ScriptOperator = "neg"), Category = "MaxQ|Math|Time")
    static FSEphemerisPeriod NegateSEphemerisPeriod(const FSEphemerisPeriod& T);

    UFUNCTION(BlueprintPure, meta = (ScriptMethod = "Negated", ScriptOperator = "neg"), Category = "MaxQ|Math|Dimensionless")
    static FSDimensionlessVector NegateSDimensionlessVector(const FSDimensionlessVector& V);

    UFUNCTION(BlueprintPure, meta = (ScriptMethod = "Negated", ScriptOperator = "neg"), Category = "MaxQ|Math|Distance")
    static FSDistanceVector NegateSDistanceVector(const FSDistanceVector& r);

    UFUNCTION(BlueprintPure, meta = (ScriptMethod = "Negated", ScriptOperator = "neg"), Category = "MaxQ|Math|Velocity")
    static FSVelocityVector NegateSVelocityVector(const FSVelocityVector& v);

    UFUNCTION(BlueprintPure, meta = (ScriptMethod = "Negated", ScriptOperator = "neg"), Category = "MaxQ|Math|Angular Rate")
    static FSAngularRate NegateSAngularRate(const FSAngularRate& dTh);

    UFUNCTION(BlueprintPure, meta = (ScriptMethod = "Negated", ScriptOperator = "neg"), Category = "MaxQ|Math|Angular Velocity")
    static FSAngularVelocity NegateSAngularVelocity(const FSAngularVelocity& av);

    UFUNCTION(BlueprintPure, Category = "MaxQ|Math|Time", meta = (ToolTip = "Creates a simple ephemeris time window"))
    static void SingleEtWindow(
        const FSEphemerisTime& et0,
        const FSEphemerisTime& et1,
        TArray<FSEphemerisTimeWindowSegment>& Window
    );

    UFUNCTION(BlueprintPure, Category = "MaxQ|Math|Angle", meta = (ToolTip = "Converts degrees to an angle"))
    static void Degrees2Angle(FSAngle& angle, double degrees = 0.);

    UFUNCTION(BlueprintPure, Category = "MaxQ|Math|Angle", meta = (ToolTip = "Converts an angle to degrees"))
    static void Angle2Degrees(const FSAngle& angle, double& degrees);

    UFUNCTION(BlueprintPure, Category = "MaxQ|Math|Angle", meta = (ToolTip = "Converts radians to an angle"))
    static void Radians2Angle(FSAngle& angle, double radians = 0.);

    UFUNCTION(BlueprintPure, Category = "MaxQ|Math|Angle", meta = (ToolTip = "Converts an angle to radians"))
    static void Angle2Radians(const FSAngle& angle, double& radians);
    
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Math|Angle",
        meta = (
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Normalizes internal angle 0 to 360 deg"
            ))
    static void NormalizeAngle0To360(
        const FSAngle& Angle,
        FSAngle& AngleNormalized
    );

    [[deprecated("Use NormalizeAngleMinus180To180()")]]
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Math|Angle",
        meta = (
            DeprecatedFunction,
            DeprecationMessage = "Use NormalizeAngleMinus180To180",
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Normalizes internal angle -180 to +180 deg"
            ))
    static void NormalizeAngle180To180(
        const FSAngle& Angle,
        FSAngle& AngleNormalized
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Math|Angle",
        meta = (
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Normalizes internal angle -180 to +180 deg"
            ))
    static void NormalizeAngleMinus180To180(
        const FSAngle& Angle,
        FSAngle& AngleNormalized
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Math|Angle",
        meta = (
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Normalizes angle 0 to 360 deg"
            ))
    static void NormalizeDegrees0To360(
        double Degrees,
        double& NormalizedDegrees
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Math|Angle",
        meta = (
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Normalizes angle -180 to +180 deg"
            ))
    static void NormalizeDegreesMinus180To180(
        double Degrees,
        double& NormalizedDegrees
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Angle",
        meta = (
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Normalizes angle 0 to 2*PI radians"
            ))
        static void NormalizeRadiansZeroToTwoPi(
            double Radians,
            double& NormalizedRadians
        );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Angle",
        meta = (
            Keywords = "CONVERSION, COORDINATES",
            ToolTip = "Normalizes angle -PI to +PI radians"
            ))
    static void NormalizeRadiansMinusPiToPi(
        double Radians,
        double& NormalizedRadians
    );


    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Swizzle|To LHS",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES, SWIZZLE",
            CompactNodeTitle = "Swizzle To UE",
            ToolTip = "Convert/Swizzle a Spice dimensionless vector (double precision, RHS) to a UE Vector (single precision, LHS)"
            ))
        static FVector Conv_SDimensionlessToVector(
            FSDimensionlessVector value
        );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Swizzle|To LHS",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES, SWIZZLE",
            CompactNodeTitle = "Swizzle To UE",
            ToolTip = "Convert/Swizzle a Spice distance vector (double precision, RHS) to a UE Vector (km, single precision, LHS)"
            ))
        static FVector Conv_SDistanceVectorToVector(
            const FSDistanceVector& value
        );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Swizzle|To LHS",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES, SWIZZLE",
            CompactNodeTitle = "Swizzle To UE",
            ToolTip = "Convert/Swizzle a Spice velocity vector (double precision, RHS) to a UE Vector (kmps, single precision, LHS)"
            ))
        static FVector Conv_SVelocityVectorToVector(
            const FSVelocityVector& value
        );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Swizzle|To RHS",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES, SWIZZLE",
            CompactNodeTitle = "Swizzle From UE",
            ToolTip = "Convert/Swizzle a UE Vector (single precision, LHS) to a Spice dimensionless vector (double precision, RHS)"
            ))
        static FSDimensionlessVector Conv_VectorToSDimensionless(
            const FVector& value
        );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Swizzle|To RHS",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES, SWIZZLE",
            CompactNodeTitle = "Swizzle From UE",
            ToolTip = "Convert/Swizzle a UE Vector (km, single precision, LHS) to a Spice distance vector (double precision, RHS)"
            ))
        static FSDistanceVector Conv_VectorToSDistanceVector(
            const FVector& value
        );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Swizzle|To RHS",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES, SWIZZLE",
            CompactNodeTitle = "Swizzle From UE",
            ToolTip = "Convert/Swizzle a UE Vector (kmps, single precision, LHS) to a Spice velocity vector (double precision, RHS)"
            ))
        static FSVelocityVector Conv_VectorToSVelocityVector(
            const FVector& value
        );


    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Swizzle|To RHS",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES, SWIZZLE",
            CompactNodeTitle = "Swizzle From UE",
            ToolTip = "Convert/Swizzle a UE Vector (kmps, single precision, LHS) to a Spice angular velocity vector (double precision, RHS)"
            ))
    static FSAngularVelocity Conv_VectorToSAngularVelocity(
        const FVector& value
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Swizzle|To LHS",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES, SWIZZLE",
            CompactNodeTitle = "Swizzle To UE",
            ToolTip = "Convert/Swizzle a Spice angular velocity vector (double precision, RHS) to a UE Vector (kmps, single precision, LHS)"
            ))
    static FVector Conv_SAngularVelocityToVector(
        const FSAngularVelocity& value
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SAngularVelocity)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SAngularVelocity to a String"
            ))
    static FString Conv_SAngularVelocityToString(
        const FSAngularVelocity& value
    );

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SQuaternion)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SQuaternion to a String"
            ))
    static FString Conv_SQuaternionToString(
        const FSQuaternion& value
    );


    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Swizzle|To LHS",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES, SWIZZLE, SWAZZLE, ROTATION",
            CompactNodeTitle = "Swizzle To UE",
            ToolTip = "Convert/Swizzle a Spice quaternion (double precision, RHS) to a UE Quat (single precision, LHS)"
            ))
    static FQuat Conv_SQuaternionToQuat(const FSQuaternion& value);

    /// <summary>Demotes a quaternion to a UE FQuat</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Swizzle|To RHS",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES, SWIZZLE, SWAZZLE, ROTATION",
            CompactNodeTitle = "Swizzle From UE",
            ToolTip = "Convert/Swizzle a UE Quat (single precision, LHS) to a Spice quaternion (double precision, RHS)"
            ))
    static FSQuaternion Conv_QuatToSQuaternion(const FQuat& value);


    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Stringifier",
        meta = (
            BlueprintAutocast,
            DisplayName = "To String (SQuaternionDerivative)",
            CompactNodeTitle = "->",
            ScriptMethod = "ToString",
            ToolTip = "Converts a SQuaternionDerivative to a String"
            ))
    static FString Conv_SQuaternionDerivativeToString(const FSQuaternionDerivative& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Swizzle|To LHS",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES, SWIZZLE, SWAZZLE, ROTATION",
            CompactNodeTitle = "Swizzle To UE",
            ToolTip = "Converts a Quaternion Derivative to a Vector4"
            ))
    static FVector4 Conv_SQuaternionDerivativeToVector4(const FSQuaternionDerivative& value);

    /// <summary>Demotes a quaternion to a UE FQuat</summary>
    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Swizzle|To RHS",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES, SWIZZLE, SWAZZLE, ROTATION",
            CompactNodeTitle = "Swizzle From UE",
            ToolTip = "Convert/Swizzle a UE Vector4 (single precision, LHS) to a Spice quaternion (double precision, RHS)"
            ))
    static FSQuaternionDerivative Conv_Vector4ToSQuaternionDerivative(const FVector4& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Rotation",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES, ROTATION",
            CompactNodeTitle = "To SQuaternion",
            ToolTip = "Converts a Spice quaternion to a Rotation Matrix"
            ))
    static FSRotationMatrix Conv_SQuaternionToSRotationMatrix(const FSQuaternion& value);

    UFUNCTION(BlueprintPure,
        Category = "MaxQ|Rotation",
        meta = (
            BlueprintAutocast,
            Keywords = "CONVERSION, COORDINATES, ROTATION",
            CompactNodeTitle = "To SQuaternion",
            ToolTip = "Converts a Spice RotationMatrix to a Quaternion"
            ))
    static FSQuaternion Conv_SRotationMatrixToSQuaternion(const FSRotationMatrix& value);

    // ------------------------------------------------------------------------
    // Blueprint Constants
    // ------------------------------------------------------------------------

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "Zero", ScriptConstantHost = "SDistance"), Category = "MaxQ|Distance")
    static FSDistance SDistance_Zero();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "OneKilometer", ScriptConstantHost = "SDistance"), Category = "MaxQ|Distance")
    static FSDistance SDistance_OneKilometer();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "OneMeter", ScriptConstantHost = "SDistance"), Category = "MaxQ|Distance")
    static FSDistance SDistance_OneMeter();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "OneFoot", ScriptConstantHost = "SDistance"), Category = "MaxQ|Distance")
    static FSDistance SDistance_OneFoot();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "OneStatuteMile", ScriptConstantHost = "SDistance"), Category = "MaxQ|Distance")
    static FSDistance SDistance_OneStatuteMile();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "OneNauticalMile", ScriptConstantHost = "SDistance"), Category = "MaxQ|Distance")
    static FSDistance SDistance_OneNauticalMile();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "OneAstronomicalUnit", ScriptConstantHost = "SDistance"), Category = "MaxQ|Distance")
    static FSDistance SDistance_OneAstronomicalUnit();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "OneLightYear", ScriptConstantHost = "SDistance"), Category = "MaxQ|Distance")
    static FSDistance SDistance_OneLightYear();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "Zero", ScriptConstantHost = "SSpeed"), Category = "MaxQ|Speed")
    static FSSpeed SSpeed_Zero();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "OneKilomenterPerSecond", ScriptConstantHost = "SSpeed"), Category = "MaxQ|Speed")
    static FSSpeed SSpeed_OneKilomenterPerSecond();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "Zero", ScriptConstantHost = "SDistanceVector"), Category = "MaxQ|DistanceVector")
    static FSDistanceVector SDistanceVector_Zero();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "Zero", ScriptConstantHost = "SVelocityVector"), Category = "MaxQ|VelocityVector")
    static FSVelocityVector SVelocityVector_Zero();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "Identity", ScriptConstantHost = "SStateTransform"), Category = "MaxQ|StateTransform")
    static FSStateTransform SStateTransform_Identity();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "pi", ScriptConstantHost = "SAngle"), Category = "MaxQ|Angle")
    static double SAngle_pi();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "halfpi", ScriptConstantHost = "SAngle"), Category = "MaxQ|Angle")
    static double SAngle_halfpi();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "twopi", ScriptConstantHost = "SAngle"), Category = "MaxQ|Angle")
    static double SAngle_twopi();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "dpr", ScriptConstantHost = "SAngle"), Category = "MaxQ|Angle")
    static double SAngle_dpr();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "_0", ScriptConstantHost = "SAngle"), Category = "MaxQ|Angle")
    static FSAngle SAngle__0();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "_360", ScriptConstantHost = "SAngle"), Category = "MaxQ|Angle")
    static FSAngle SAngle__360();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "Zero", ScriptConstantHost = "SEulerAngles"), Category = "MaxQ|EulerAngles")
    static FSEulerAngles SEulerAngles_Zero();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "Identity", ScriptConstantHost = "SQuaternion"), Category = "MaxQ|Quaternion")
    static FSQuaternion SQuaternion_Identity();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "Zero", ScriptConstantHost = "SAngularRate"), Category = "MaxQ|AngularRate")
    static FSAngularRate SAngularRate_Zero();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "Zero", ScriptConstantHost = "SAngularVelocity"), Category = "MaxQ|AngularVelocity")
    static FSAngularVelocity SAngularVelocity_Zero();


    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "Zero", ScriptConstantHost = "SEulerAngularState"), Category = "MaxQ|EulerAngularState")
    static FSEulerAngularState SEulerAngularState_Zero();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "Identity", ScriptConstantHost = "SEulerAngularTransform"), Category = "MaxQ|EulerAngularTransform")
    static FSEulerAngularTransform SEulerAngularTransform_Identity();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "Zero", ScriptConstantHost = "SComplexScalar"), Category = "MaxQ|ComplexScalar")
    static FSComplexScalar SComplexScalar_Zero();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "J2000", ScriptConstantHost = "SEphemerisTime"), Category = "MaxQ|EphemerisTime")
    static FSEphemerisTime SEphemerisTime_J2000();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "Zero", ScriptConstantHost = "SEphemerisPeriod"), Category = "MaxQ|EphemerisPeriod")
    static FSEphemerisPeriod SEphemerisPeriod_Zero();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "OneSecond", ScriptConstantHost = "SEphemerisPeriod"), Category = "MaxQ|EphemerisPeriod")
    static FSEphemerisPeriod SEphemerisPeriod_OneSecond();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "OneMinute", ScriptConstantHost = "SEphemerisPeriod"), Category = "MaxQ|EphemerisPeriod")
    static FSEphemerisPeriod SEphemerisPeriod_OneMinute();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "OneHour", ScriptConstantHost = "SEphemerisPeriod"), Category = "MaxQ|EphemerisPeriod")
    static FSEphemerisPeriod SEphemerisPeriod_OneHour();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "OneDay", ScriptConstantHost = "SEphemerisPeriod"), Category = "MaxQ|EphemerisPeriod")
    static FSEphemerisPeriod SEphemerisPeriod_OneDay();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "OneJulianYear", ScriptConstantHost = "SEphemerisPeriod"), Category = "MaxQ|EphemerisPeriod")
    static FSEphemerisPeriod SEphemerisPeriod_OneJulianYear();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "OneTropicalYear", ScriptConstantHost = "SEphemerisPeriod"), Category = "MaxQ|EphemerisPeriod")
    static FSEphemerisPeriod SEphemerisPeriod_OneTropicalYear();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "Identity", ScriptConstantHost = "SRotationMatrix"), Category = "MaxQ|RotationMatrix")
    static FSRotationMatrix SRotationMatrix_Identity();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "Zero", ScriptConstantHost = "SDimensionlessVector"), Category = "MaxQ|DimensionlessVector")
    static FSDimensionlessVector SDimensionlessVector_Zero();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "X_Axis", ScriptConstantHost = "SDimensionlessVector"), Category = "MaxQ|DimensionlessVector")
    static FSDimensionlessVector SDimensionlessVector_X_Axis();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "Y_Axis", ScriptConstantHost = "SDimensionlessVector"), Category = "MaxQ|DimensionlessVector")
    static FSDimensionlessVector SDimensionlessVector_Y_Axis();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "Z_Axis", ScriptConstantHost = "SDimensionlessVector"), Category = "MaxQ|DimensionlessVector")
    static FSDimensionlessVector SDimensionlessVector_Z_Axis();

    UFUNCTION(BlueprintPure, meta = (ScriptConstant = "Zero", ScriptConstantHost = "SMassConstant"), Category = "MaxQ|MassConstant")
    static FSMassConstant SMassConstant_Zero();

#pragma region NaifNames
    // Blueprint Constants
    // The Blueprint compiler can understand they're supposed to be constant and hoist them when possible.
    // (Example, user calling J2000 inside a loop)
    // An alternative would be to make an enumeration & function to look up, but then the compiler couldn't hoist.

    // Inertial Reference Frames
    UFUNCTION(BlueprintPure, meta = (ToolTip = "J2000 EME Inertial Frame (aligned with J2000 Earth Mean Equator)", ScriptConstant = "J2000", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Inertial")
    static FString Const_J2000();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "ECLIPJ2000 Inertial Frame (aligned with J2000 Ecliptic Plane)", ScriptConstant = "ECLIPJ2000", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Inertial")
    static FString Const_ECLIPJ2000();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "MARSIAU Inertial Frame (aligned with Mars Mean Equator)", ScriptConstant = "MARSIAU", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Inertial")
    static FString Const_MARSIAU();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Galactic System II Inertial Frame", ScriptConstant = "GALACTIC", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Inertial")
    static FString Const_GALACTIC();

    // Body-Fixed Reference Frames
    UFUNCTION(BlueprintPure, meta = (ToolTip = "Earth Fixed-Frame, but you should use EARTH_FIXED, or ITRF if you have high precision kernels)", ScriptConstant = "IAU_EARTH", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Fixed")
    static FString Const_IAU_EARTH();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "EARTH_FIXED Earth-Fixed Frame (requires earth_fixed.tf)", ScriptConstant = "EARTH_FIXED", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Fixed")
    static FString Const_EARTH_FIXED();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "ITRF93 Earth-fixed Frame (binary PCK)", ScriptConstant = "ITRF93", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Fixed")
    static FString Const_ITRF93();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "IAU_MOON Moon-Fixed Frame", ScriptConstant = "IAU_MOON", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Fixed")
    static FString Const_IAU_MOON();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "IAU_SUN Sun-Fixed Frame", ScriptConstant = "IAU_SUN", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Fixed")
    static FString Const_IAU_SUN();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "IAU_MERCURY Mercury-Fixed Frame", ScriptConstant = "IAU_MERCURY", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Fixed")
    static FString Const_IAU_MERCURY();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "IAU_VENUS Venus-Fixed Frame", ScriptConstant = "IAU_VENUS", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Fixed")
    static FString Const_IAU_VENUS();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "IAU_MARS Mars-Fixed Frame", ScriptConstant = "IAU_MARS", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Fixed")
    static FString Const_IAU_MARS();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "IAU_DEIMOS Deimos-Fixed Frame", ScriptConstant = "IAU_DEIMOS", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Fixed")
    static FString Const_IAU_DEIMOS();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "IAU_PHOBOS Phobos-Fixed Frame", ScriptConstant = "IAU_PHOBOS", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Fixed")
    static FString Const_IAU_PHOBOS();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "IAU_JUPITER Jupiter-Fixed Frame", ScriptConstant = "IAU_JUPITER", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Fixed")
    static FString Const_IAU_JUPITER();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "IAU_SATURN Saturn-Fixed Frame", ScriptConstant = "IAU_SATURN", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Fixed")
    static FString Const_IAU_SATURN();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "IAU_NEPTUNE Naptune-Fixed Frame", ScriptConstant = "IAU_NEPTUNE", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Fixed")
    static FString Const_IAU_NEPTUNE();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "IAU_URANUS Uranus-Fixed Frame", ScriptConstant = "IAU_URANUS", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Fixed")
    static FString Const_IAU_URANUS();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "IAU_PLUTO Pluto-Fixed Frame", ScriptConstant = "IAU_PLUTO", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Fixed")
    static FString Const_IAU_PLUTO();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "IAU_CERES Ceres-Fixed Frame", ScriptConstant = "IAU_CERES", ScriptConstantHost = "Const"), Category = "MaxQ|Frames|Fixed")
    static FString Const_IAU_CERES();

    // Naif Body Names
    // See
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/naif_ids.html#Barycenters
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/naif_ids.html#Planets%20and%20Satellites
    // Etc
    UFUNCTION(BlueprintPure, meta = (ToolTip = "EARTH Naif Name", ScriptConstant = "EARTH", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_EARTH();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "MOON Naif Name", ScriptConstant = "MOON", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_MOON();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "EMB (Earth-Moon Barycenter) Naif Name, equivalent to EARTH_BARYCENTER", ScriptConstant = "EMB", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_EMB();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "EARTH_BARYCENTER (Earth-Moon Barycenter) Naif Name, equivalent to EMB", ScriptConstant = "EARTH_BARYCENTER", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_EARTH_BARYCENTER();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "SUN (Mass) Naif Name", ScriptConstant = "SUN", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_SUN();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "SSB (Solar System Barycenter) Naif Name, equivalent to SOLAR_SYSTEM_BARYCENTER", ScriptConstant = "SSB", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_SSB();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "SOLAR_SYSTEM_BARYCENTER (Solar System Barycenter) Naif Name, equivalent to SSB", ScriptConstant = "SOLAR_SYSTEM_BARYCENTER", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_SOLAR_SYSTEM_BARYCENTER();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "MERCURY", ScriptConstant = "MERCURY", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_MERCURY();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "VENUS Naif Name", ScriptConstant = "VENUS", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_VENUS();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "MARS Naif Name", ScriptConstant = "MARS", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_MARS();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "PHOBOS Naif Name", ScriptConstant = "PHOBOS", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_PHOBOS();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "DEIMOS Naif Name", ScriptConstant = "DEIMOS", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_DEIMOS();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "MARS_BARYCENTER Naif Name", ScriptConstant = "MARS_BARYCENTER", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_MARS_BARYCENTER();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "JUPITER Naif Name", ScriptConstant = "JUPITER", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_JUPITER();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "JUPITER_BARYCENTER Naif Name", ScriptConstant = "JUPITER_BARYCENTER", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_JUPITER_BARYCENTER();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "SATURN Naif Name", ScriptConstant = "SATURN", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_SATURN();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "SATURN_BARYCENTER Naif Name", ScriptConstant = "SATURN_BARYCENTER", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_SATURN_BARYCENTER();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "URANUS Naif Name", ScriptConstant = "URANUS", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_URANUS();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "URANUS_BARYCENTER Naif Name", ScriptConstant = "URANUS_BARYCENTER", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_URANUS_BARYCENTER();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "NEPTUNE Naif Name", ScriptConstant = "NEPTUNE", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_NEPTUNE();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "NEPTUNE_BARYCENTER Naif Name", ScriptConstant = "NEPTUNE_BARYCENTER", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_NEPTUNE_BARYCENTER();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "PLUTO Naif Name", ScriptConstant = "PLUTO", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_PLUTO();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "PLUTO_BARYCENTER Naif Name", ScriptConstant = "PLUTO_BARYCENTER", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_PLUTO_BARYCENTER();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Asteroid CERES Naif Name", ScriptConstant = "CERES", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_CERES();

    // Spacecraft
    // See: https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/naif_ids.html#Spacecraft
    UFUNCTION(BlueprintPure, meta = (ToolTip = "Spacecraft PIONEER-6 Naif Name", ScriptConstant = "PIONEER_6", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_PIONEER_6();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Spacecraft PIONEER-7 Naif Name", ScriptConstant = "PIONEER_7", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_PIONEER_7();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Spacecraft VIKING 1 ORBITER Naif Name", ScriptConstant = "VIKING_1_ORBITER", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_VIKING_1_ORBITER();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Spacecraft VIKING 2 ORBITER Naif Name", ScriptConstant = "VIKING_2_ORBITER", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_VIKING_2_ORBITER();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Spacecraft VOYAGER 1 Naif Name", ScriptConstant = "VOYAGER_1", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_VOYAGER_1();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Spacecraft VOYAGER 2 Naif Name", ScriptConstant = "VOYAGER_2", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_VOYAGER_2();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Spacecraft HST Naif Name, equivalent to HUBBLE SPACE TELESCOPE", ScriptConstant = "HST", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_HST();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Spacecraft HUBBLE SPACE TELESCOPE Naif Name, equivalent to HST", ScriptConstant = "HUBBLE_SPACE_TELESCOPE", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_HUBBLE_SPACE_TELESCOPE();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Spacecraft MARS PATHFINDER Naif Name", ScriptConstant = "MARS_PATHFINDER", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_MARS_PATHFINDER();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Spacecraft PARKER SOLAR PROBE Naif Name", ScriptConstant = "PARKER_SOLAR_PROBE", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_PARKER_SOLAR_PROBE();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Spacecraft JWST Naif Name, equivalent to JAMES WEBB SPACE TELESCOPE", ScriptConstant = "JWST", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_JWST();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Spacecraft JAMES WEBB SPACE TELESCOPE Naif Name, equivalent to JWST", ScriptConstant = "JAMES_WEBB_SPACE_TELESCOPE", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_JAMES_WEBB_SPACE_TELESCOPE();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Spacecraft INSIGHT Naif Name", ScriptConstant = "INSIGHT", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_INSIGHT();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Spacecraft OPPORTUNITY Naif Name", ScriptConstant = "OPPORTUNITY", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_OPPORTUNITY();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Spacecraft SPIRIT Naif Name", ScriptConstant = "SPIRIT", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_SPIRIT();

    // Ground stations
    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/naif_ids.html#Ground%20Stations.
    UFUNCTION(BlueprintPure, meta = (ToolTip = "Ground Station NOTO Naif Name", ScriptConstant = "NOTO", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_NOTO();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Ground Station NEW NORCIA Naif Name", ScriptConstant = "NEW_NORCIA", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_NEW_NORCIA();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Ground Station GOLDSTONE Naif Name", ScriptConstant = "GOLDSTONE", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_GOLDSTONE();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Ground Station CANBERRA Naif Name", ScriptConstant = "CANBERRA", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_CANBERRA();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Ground Station MADRID Naif Name", ScriptConstant = "MADRID", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_MADRID();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Ground Station USUDA Naif Name", ScriptConstant = "USUDA", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_USUDA();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Ground Station DSS-05 Naif Name", ScriptConstant = "DSS_05", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_DSS_05();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "Ground Station PARKES Naif Name", ScriptConstant = "PARKES", ScriptConstantHost = "Const"), Category = "MaxQ|SPK|Naif Names")
    static FString Const_PARKES();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "GM Property Name", ScriptConstant = "GM", ScriptConstantHost = "Const"), Category = "MaxQ|Kernel|Property Names")
    static FString Const_GM();

    UFUNCTION(BlueprintPure, meta = (ToolTip = "RADII Property Name", ScriptConstant = "RADII", ScriptConstantHost = "Const"), Category = "MaxQ|Kernel|Property Names")
    static FString Const_RADII();

#pragma endregion NaifNames
};

