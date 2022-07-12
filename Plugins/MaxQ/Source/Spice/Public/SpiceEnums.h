// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceEnums.h
// 
// API Comments
// 
// SpiceStructs : public CSPICE type to UE type wrappers (enums)
// 
// Purpose:
// BlueprintType implementations of CSPICE UE-Type wrappers  
//------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "SpicePlatformDefs.h"

UENUM(BlueprintType)
enum class ES_ResultCode : uint8
{
    Success UMETA(DisplayName = "Ok"),
    Error UMETA(DisplayName = "Error")
};

UENUM(BlueprintType)
enum class ES_FoundCode : uint8
{
    Found UMETA(DisplayName = "Found"),
    NotFound UMETA(DisplayName = "Not Found")
};

UENUM(BlueprintType)
enum class ES_GetOrSet : uint8
{
    Get UMETA(DisplayName = "Get"),
    Set UMETA(DisplayName = "Set")
};

UENUM(BlueprintType)
enum class ES_ErrorDevice : uint8
{
    LogFile UMETA(DisplayName = "LogFile"),
    Screen UMETA(DisplayName = "Screen"),
    Null UMETA(DisplayName = "No Device")
};

UENUM(BlueprintType)
enum class ES_ErrorAction : uint8
{
    Abort UMETA(DisplayName = "Abort (Default)"),
    Report UMETA(DisplayName = "Report"),
    Return UMETA(DisplayName = "Return"),
    Ignore UMETA(DisplayName = "Ignore")
};

UENUM(BlueprintType)
enum class ES_AberrationCorrectionWithNewtonians : uint8
{
    None = 0 UMETA(DisplayName = "None (No Correction)"),
    LT = 1 UMETA(DisplayName = "LT (Planetary Abberration)"),
    LT_S = 2 UMETA(DisplayName = "LT+S (Planetary + Stellar Abberation, Newtonian)"),
    CN = 3 UMETA(DisplayName = "CN (Converged Newtonian light time correction"),
    CN_S = 4 UMETA(DisplayName = "CN+S (Converged Newtonian light time correction and stellar aberration correction)")
};

UENUM(BlueprintType)
enum class ES_AberrationCorrectionWithTransmissions : uint8
{
    None  = 0 UMETA(DisplayName = "None (No Correction)"),
    LT    = 1 UMETA(DisplayName = "LT (Planetary Abberration)"),
    LT_S  = 2 UMETA(DisplayName = "LT+S (Planetary + Stellar Abberation, Newtonian)"),
    CN    = 3 UMETA(DisplayName = "CN (Converged Newtonian light time correction"),
    CN_S  = 4 UMETA(DisplayName = "CN+S (Converged Newtonian light time correction and stellar aberration correction)"),
    XLT   = 5 UMETA(DisplayName = "Transmission LT (Planetary Abberration)"),
    XLT_S = 6 UMETA(DisplayName = "Transmission LT+S (Planetary + Stellar Abberation, Newtonian)"),
    XCN   = 7 UMETA(DisplayName = "Transmission CN (Converged Newtonian light time correction"),
    XCN_S = 8 UMETA(DisplayName = "Transmission CN+S (Converged Newtonian light time correction and stellar aberration correction)")
};


UENUM(BlueprintType)
enum class ES_AberrationCorrectionForOccultation : uint8
{
    None = 0 UMETA(DisplayName = "None (No Correction)"),
    LT = 1 UMETA(DisplayName = "LT (Planetary Abberration)"),
    CN = 3 UMETA(DisplayName = "CN (Converged Newtonian light time correction"),
    XLT = 5 UMETA(DisplayName = "Transmission LT (Planetary Abberration)"),
    XCN = 7 UMETA(DisplayName = "Transmission CN (Converged Newtonian light time correction"),
};

UENUM(BlueprintType)
enum class ES_AberrationCorrectionFov : uint8
{
    None = 0 UMETA(DisplayName = "None (No Correction)"),
    S  = 1 UMETA(DisplayName = "S (Stellar aberration correction, reception case)"),
    XS = 2 UMETA(DisplayName = "XS (Stellar aberration correction, transmission case)")
};

UENUM(BlueprintType)
enum class ES_AberrationCorrection : uint8
{
    None = 0 UMETA(DisplayName = "None (No Correction)"),
    LT = 1 UMETA(DisplayName = "LT (Planetary Abberration)"),
    LT_S = 2 UMETA(DisplayName = "LT+S (Planetary + Stellar Abberation, Newtonian)"),
};

UENUM(BlueprintType)
enum class ES_AberrationCorrectionLocus : uint8
{
    CENTER          UMETA(DisplayName = "Center"),
    ELLIPSOID_LIMB  UMETA(DisplayName = "Ellipsoid Limb")
};

UENUM(BlueprintType)
enum class ES_AberrationCorrectionLocusTerminator : uint8
{
    CENTER                  UMETA(DisplayName = "Center"),
    ELLIPSOID_TERMINATOR    UMETA(DisplayName = "Ellipsoid Terminator")
};

UENUM(BlueprintType)
enum class ES_EpochType : uint8
{
    UTC UMETA(DisplayName = "UTC seconds past J2000 UTC"),
    ET UMETA(DisplayName = "Ephemeris seconds past J2000 TDB, also known as barycentric dynamical time(TDB)")
};

UENUM(BlueprintType)
enum class ES_LongitudeType : uint8
{
    Planetocentric UMETA(DisplayName = "Planetocentric"),
    Planetographic UMETA(DisplayName = "Planetographic")
};


UENUM(BlueprintType)
enum class ES_UTCTimeFormat : uint8
{
    Calendar UMETA(DisplayName = "Calendar format, UTC"),
    DayOfYear UMETA(DisplayName = "Day-of-Year format, UTC"),
    JulianDate UMETA(DisplayName = "Julian Date format, UTC"),
    ISOCalendar UMETA(DisplayName = "ISO Calendar format, UTC"),
    ISODayOfYear UMETA(DisplayName = "ISO Day-of-Year format, UTC")
};


UENUM(BlueprintType)
enum class ES_Axis : uint8
{
    NONE = 0 UMETA(Hidden),
    X = 1 UMETA(DisplayName = "Spice X Axis (UE Y Axis)"),
    Y = 2 UMETA(DisplayName = "Spice Y Axis (UE X Axis)"),
    Z = 3 UMETA(DisplayName = "Spice Z Axis (UE Z Axis)")
};


UENUM(BlueprintType)
enum class ES_CoordinateSystem : uint8
{
    NONE            = 0 UMETA(Hidden),
    RECTANGULAR     = 1 UMETA(DisplayName = "Rectangular"),
    CYLINDRICAL     = 2 UMETA(DisplayName = "Cylindrical"),
    LATITUDINAL     = 3 UMETA(DisplayName = "Latitudinal"),
    SPHERICAL       = 4 UMETA(DisplayName = "Spherical"),
    GEODETIC        = 5 UMETA(DisplayName = "Geodetic"),
    PLANETOGRAPHIC  = 6 UMETA(DisplayName = "Planetographic")
};

UENUM(BlueprintType)
enum class ES_CoordinateSystemInclRadec : uint8
{
    NONE            = 0 UMETA(Hidden),
    RECTANGULAR     = 1 UMETA(DisplayName = "Rectangular"),
    CYLINDRICAL     = 2 UMETA(DisplayName = "Cylindrical"),
    LATITUDINAL     = 3 UMETA(DisplayName = "Latitudinal"),
    SPHERICAL       = 4 UMETA(DisplayName = "Spherical"),
    GEODETIC        = 5 UMETA(DisplayName = "Geodetic"),
    PLANETOGRAPHIC  = 6 UMETA(DisplayName = "Planetographic"),
    RADEC           = 7 UMETA(DisplayName = "Range/RA/Dec")
};


UENUM(BlueprintType)
enum class ES_CoordinateName : uint8
{
    NONE UMETA(Hidden),
    X               UMETA(DisplayName = "X"),
    Y               UMETA(DisplayName = "Y"),
    Z               UMETA(DisplayName = "Z"),
    RADIUS          UMETA(DisplayName = "Radius"),
    LONGITUDE       UMETA(DisplayName = "Longitude"),
    LATITUDE        UMETA(DisplayName = "Latitude"),
    RANGE           UMETA(DisplayName = "Range"),
    RIGHT_ASCENSION UMETA(DisplayName = "Right Ascension"),
    DECLINATION     UMETA(DisplayName = "Declination"),
    COLATITUDE      UMETA(DisplayName = "Colatitude"),
    ALTITUDE        UMETA(DisplayName = "Altitude")
};


UENUM(BlueprintType)
enum class ES_GeometricModel : uint8
{
    NONE UMETA(Hidden),
    ELLIPSOID     UMETA(DisplayName = "Ellipsoid"),
    POINT         UMETA(DisplayName = "Point"),
    DSK           UMETA(DisplayName = "DSK/Unprioritized")
};


UENUM(BlueprintType)
enum class ES_OtherGeometricModel : uint8
{
    NONE UMETA(Hidden),
    SPHERE     UMETA(DisplayName = "Sphere"),
    POINT      UMETA(DisplayName = "Point")
};


UENUM(BlueprintType)
enum class ES_ComputationMethod : uint8
{
    NONE = 0 UMETA(Hidden),
    NEAR_POINT_ELLIPSOID    = 1  UMETA(DisplayName = "Near Point/Ellipsoid"),
    INTERCEPT_ELLIPSOID     = 2  UMETA(DisplayName = "Intercept/Ellipsoid"),
    NADIR_DSK               = 3  UMETA(DisplayName = "Nadir/DSK/Unprioritized"),
    INTERCEPT_DSK           = 4  UMETA(DisplayName = "Intercept/DSK/Unprioritized")
};

UENUM(BlueprintType)
enum class ES_SubpointComputationMethod : uint8
{
    NONE = 0 UMETA(Hidden),
    NEAR_POINT_ELLIPSOID    = 1  UMETA(DisplayName = "Near Point/Ellipsoid"),
    INTERCEPT_ELLIPSOID     = 2  UMETA(DisplayName = "Intercept/Ellipsoid")
};

UENUM(BlueprintType)
enum class ES_LimbComputationMethod : uint8
{
    NONE UMETA(Hidden),
    TANGENT_ELLIPSOID   UMETA(DisplayName = "Tangent/Ellipsoid"),
    GUIDED_ELLIPSOID    UMETA(DisplayName = "Guided/Ellipsoid"),
    TANGENT_DSK         UMETA(DisplayName = "Tangent/DSK/Unprioritized"),
    GUIDED_DSK          UMETA(DisplayName = "Guided/DSK/Unprioritized")
};

UENUM(BlueprintType)
enum class ES_LocalZenithMethod : uint8
{
    NONE = 0 UMETA(Hidden),
    ELLIPSOID = 1  UMETA(DisplayName = "Ellipsoid"),
};


UENUM(BlueprintType)
enum class ES_Shadow : uint8
{
    NONE UMETA(Hidden),
    UMBRAL     UMETA(DisplayName = "Umbral"),
    PENUMBRAL  UMETA(DisplayName = "Penumbral")
};

UENUM(BlueprintType)
enum class ES_IlluminationAngleType : uint8
{
    NONE UMETA(Hidden),
    PHASE     UMETA(DisplayName = "Phase"),
    INCIDENCE UMETA(DisplayName = "Incidence"),
    EMISSION  UMETA(DisplayName = "Emission")
};

UENUM(BlueprintType)
enum class ES_CurveType : uint8
{
    NONE UMETA(Hidden),
    TANGENT UMETA(DisplayName = "Tangent"),
    GUIDED  UMETA(DisplayName = "Guided")
};

UENUM(BlueprintType)
enum class ES_OccultationType : uint8
{
    NONE    UMETA(DisplayName = "No occultation/transit"),
    FULL    UMETA(DisplayName = "Total"),
    ANNULAR UMETA(DisplayName = "Annular"),
    PARTIAL UMETA(DisplayName = "Partial"),
    ANY     UMETA(DisplayName = "Any occultation/transit")
};


UENUM(BlueprintType)
enum class ES_RelationalOperator : uint8
{
    None        UMETA(Hidden),
    GreaterThan UMETA(DisplayName = ">"),
    Equal       UMETA(DisplayName = "="),
    LessThan    UMETA(DisplayName = "<"),
    ABSMAX      UMETA(DisplayName = "Absolute Maximum"),
    ABSMIN      UMETA(DisplayName = "Absolute Minimum"),
    LOCMAX      UMETA(DisplayName = "Local Maximum"),
    LOCMIN      UMETA(DisplayName = "Local Minimum")
};

UENUM(BlueprintType)
enum class ES_Units : uint8
{
    NONE UMETA(Hidden),
    RADIANS UMETA(DisplayName = "Radians"),
    DEGREES UMETA(DisplayName = "Degrees"),
    ARCMINUTES UMETA(DisplayName = "ArcMinutes"),
    ARCSECONDS UMETA(DisplayName = "ArcSeconds"),
    HOURANGLE UMETA(DisplayName = "HourAngle"),
    MINUTEANGLE UMETA(DisplayName = "MinuteAngle"),
    SECONDANGLE UMETA(DisplayName = "SecondAngle"),
    METERS UMETA(DisplayName = "Meters"),
    KILOMETERS UMETA(DisplayName = "Kilometers"),
    CENTIMETERS UMETA(DisplayName = "Centimeters"),
    MILLIMETERS UMETA(DisplayName = "Millimeters"),
    FEET UMETA(DisplayName = "Feet"),
    INCHES UMETA(DisplayName = "Inches"),
    YARDS UMETA(DisplayName = "Yards"),
    STATUTE_MILES UMETA(DisplayName = "Statute_miles"),
    NAUTICAL_MILES UMETA(DisplayName = "Nautical_miles"),
    AU UMETA(DisplayName = "AU (Astronomical Units)"),
    PARSECS UMETA(DisplayName = "Parsecs"),
    LIGHTSECS UMETA(DisplayName = "LightSecs"),
    LIGHTYEARS UMETA(DisplayName = "LightYears (Julian)"),
    SECONDS UMETA(DisplayName = "Seconds"),
    MINUTES UMETA(DisplayName = "Minutes"),
    HOURS UMETA(DisplayName = "Hours"),
    DAYS UMETA(DisplayName = "Days"),
    JULIAN_YEARS UMETA(DisplayName = "Julian Years"),
    TROPICAL_YEARS UMETA(DisplayName = "Tropical Years"),
    YEARS UMETA(DisplayName = "Years (same as Julian Years)")
};

UENUM(BlueprintType)
enum class ES_ReferenceFrameLocus : uint8
{
    OBSERVER UMETA(DisplayName = "Observer"),
    TARGET   UMETA(DisplayName = "Target"),
    CENTER   UMETA(DisplayName = "Center")
};

UENUM(BlueprintType)
enum class ES_TimeScale : uint8
{
    NONE UMETA(Hidden),
    TAI UMETA(DisplayName = "International Atomic Time"),
    TDB UMETA(DisplayName = "Barycentric Dynamical Time"),
    TDT UMETA(DisplayName = "Terrestrial Dynamical Time"),
    ET UMETA(DisplayName = "Ephemeris time (TDB)"),
    JDTDB UMETA(DisplayName = "Julian Date relative to TDB"),
    JDTDT UMETA(DisplayName = "Julian Date relative to TDT"),
    JED UMETA(DisplayName = "Julian Ephemeris date (JDTDB)"),
};

UENUM(BlueprintType)
enum class ES_TimeSystem : uint8
{
    NONE UMETA(Hidden),
    SCLK UMETA(DisplayName = "encoded SCLK 'ticks' (SCLK is assoc with 'idcode')"),
    TDB UMETA(DisplayName = "seconds past J2000 TDB")
};


UENUM(BlueprintType)
enum class ES_CoverageLevel : uint8
{
    NONE UMETA(Hidden),
    Segment UMETA(DisplayName = "Segment"),
    Interval UMETA(DisplayName = "Interval")
};

UENUM(BlueprintType)
enum class ES_CK05Subtype : uint8
{
    Hermite8 = 0 UMETA(DisplayName = "Hermite interpolation, 8-element packets"),
    Lagrange4 = 1 UMETA(DisplayName = "Lagrange interpolation, 4-element packets"),
    Hermite14 = 2 UMETA(DisplayName = "Hermite interpolation, 14-element packets"),
    Lagrange7 = 3 UMETA(DisplayName = "Lagrange interpolation, 7-element packets")
};

UENUM(BlueprintType)
enum class ES_AngleFormat : uint8
{
    Turns UMETA(DisplayName = "Turns"),
    DD UMETA(DisplayName = "Decimal Degrees"),
    DR UMETA(DisplayName = "Decimal Radians"),
    DMS UMETA(DisplayName = "Degrees, Arcminutes, Arcseconds"),
    HMS UMETA(DisplayName = "Hours, Minutes, Seconds"),
    DD_180 UMETA(DisplayName = "Decimal Degrees [-180,180]"),
    DR_PI UMETA(DisplayName = "Decimal Radians [-pi,pi]"),
    DD_360 UMETA(DisplayName = "Decimal Degrees [0,360]"),
    DR_2PI UMETA(DisplayName = "Decimal Radians [0,2pi]")
};



UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ES_Items : uint8
{
    NONE = 0 UMETA(Hidden),
    Short = 1 << 0,
    Explain = 1 << 1,
    Long = 1 << 2,
    Traceback = 1 << 3,
    Default = 1 << 4 UMETA(DisplayName = "All (Default)")
};
ENUM_CLASS_FLAGS(ES_Items);


UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ES_KernelType : uint8
{
    NONE    = 0      UMETA(Hidden),
    SPK     = 1 << 0 UMETA(DisplayName = "SPK", ToolTip = "All SPK files are counted in the total."),
    CK      = 1 << 1 UMETA(DisplayName = "CK", ToolTip = "All CK files are counted in the total."),
    PCK     = 1 << 2 UMETA(DisplayName = "PCK", ToolTip = "All binary PCK files are counted in the total."),
    DSK     = 1 << 3 UMETA(DisplayName = "DSK", ToolTip = "All DSK files are counted in the total."),
    EK      = 1 << 4 UMETA(DisplayName = "EK", ToolTip = "All EK files are counted in the total."),
    TEXT    = 1 << 5 UMETA(DisplayName = "TEXT", ToolTip = "All text kernels that are not meta-text kernels are included in the total."),
    META    = 1 << 6 UMETA(DisplayName = "META", ToolTip = "All meta-text kernels are counted in the total.")
};
ENUM_CLASS_FLAGS(ES_KernelType);


namespace MaxQ::Core
{
    // The problem with doing this by reflection, is that if the enum values are changed, then people's Blueprints will break with NO ERROR in the build nor for the user.
    // A hardcoded implementation ensures there's a break in the build that will call attention to the string's usage, and allows for backwards compatibility.
    SPICE_API const ANSICHAR* ToANSIString(ES_Units units);
    SPICE_API const ANSICHAR* ToANSIString(ES_ReferenceFrameLocus locus);
    SPICE_API const ANSICHAR* ToANSIString(ES_AberrationCorrectionWithNewtonians abcorr);
    SPICE_API const ANSICHAR* ToANSIString(ES_AberrationCorrectionFov abcorr);
    SPICE_API const ANSICHAR* ToANSIString(ES_AberrationCorrectionLocus corloc);
    SPICE_API const ANSICHAR* ToANSIString(ES_AberrationCorrectionLocusTerminator corloc);
    SPICE_API const ANSICHAR* ToANSIString(ES_TimeScale timeScale);
    SPICE_API const ANSICHAR* ToANSIString(ES_AberrationCorrectionForOccultation abcorr);
    SPICE_API const ANSICHAR* ToANSIString(ES_AberrationCorrectionWithTransmissions abcorr);
    SPICE_API const ANSICHAR* ToANSIString(ES_GeometricModel model);
    SPICE_API const ANSICHAR* ToANSIString(ES_OtherGeometricModel model);
    SPICE_API const ANSICHAR* ToANSIString(ES_IlluminationAngleType angleType);
    SPICE_API const ANSICHAR* ToANSIString(ES_SubpointComputationMethod method);
    SPICE_API const ANSICHAR* ToANSIString(ES_RelationalOperator relate);
    SPICE_API const ANSICHAR* ToANSIString(ES_CoordinateSystemInclRadec coords);
    SPICE_API const ANSICHAR* ToANSIString(ES_CoordinateSystem coords);
    SPICE_API const ANSICHAR* ToANSIString(ES_CoordinateName coord);
    SPICE_API const ANSICHAR* ToANSIString(ES_Axis Axis);
    
    inline FString ToString(ES_Axis Axis) { return { ToANSIString(Axis) }; }
    SPICE_API FString ToString(ES_GeometricModel model, const TArray<FString>& shapeSurfaces);
    SPICE_API FString ToString(ES_KernelType KernelType);
    SPICE_API FString ToString(ES_LimbComputationMethod method, const TArray<FString>& shapeSurfaces);
    SPICE_API FString ToString(ES_Shadow shadow, ES_CurveType curveType, ES_GeometricModel method, const TArray<FString>& shapeSurfaces);
    SPICE_API FString ToString(ES_ComputationMethod method, const TArray<FString>& shapeSurfaces);

    template<class T>
    SPICE_API T Parse(const FString& Str);

    template<>
    SPICE_API ES_KernelType Parse<ES_KernelType>(const FString& KernelType);

    inline bool IsFound(ES_FoundCode FoundCode) { return FoundCode == ES_FoundCode::Found; }
    inline bool IsSuccess(ES_ResultCode ResultCode) { return ResultCode == ES_ResultCode::Success; }
}