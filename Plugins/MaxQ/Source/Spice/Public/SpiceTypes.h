// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpicePlatformDefs.h"
#include "SpiceTypes.generated.h"

// Log category for MaxQ SPICE releated messages.
SPICE_API DECLARE_LOG_CATEGORY_EXTERN(LogSpice, Log, All);

// See:
// https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/getmsg_c.html
// "msglen  The current maximum long error message length is in fact 1840 characters"
constexpr uint32 SpiceLongMessageMaxLength = 1841;

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


USTRUCT(BlueprintType, Category = "MaxQ|DimensionlessVector")
struct SPICE_API FSDimensionlessVector
{
    GENERATED_BODY()

    // Note *: UNREAL ENGINE SERIALIZATION's impacts on internal representation:
    // note that UE does not support serialization of "plain" arrays.  Only TArray.
    // TArray exposes a data pointers, so refs & pointers to an xyz[3] triplet
    // would be possible, and then type-changing between double/SpiceDouble
    // in-place would be possible, rather than copy operations when interfacing
    // with Spice.
    // But IMO that's a case of premature optimizations a hoop or two too many
    // to jump through under a shaky assumption that the performance
    // considerations of it will ever matter.
    // IMO it's a safer assumption that SPICE interfacing will always be
    // outer loop territory with performance characteristics dominated either 
    // inside spice or by the caller.  Minimal Gains.  A few assumptions required
    // go achieve the gains (SpiceDouble == double, etc).
    // So, the choice is to go with the quite save individual member representation
    // and by-member copy to/from SpiceDouble[] arrays each time they're exchanged
    // to/from spice.  (This is deliberate, and it goes for all similar types.)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double x;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double y;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double z;

    // Note **: MODERN C++'s VIEW OF STRUCTs as POD:
    // A tenant of "Modern C++" is:  use structs for "Plane old data" only.
    // However.
    // Unreal Engine attaches special meaning to USTRUCT and UCLASS.
    // We don't want a garbage collected UCLASS for "flat" like vectors
    // going in/out of SPICE.
    // And... we do want operators etc  etc on things like distance vectors,
    // right?
    // Best practices of modern c++ are in conflict with what we want to
    // express, largely because of Modern C++ is trying to be too cute
    // by half with brace elision in its initialization syntax, which
    // makes it ambiguous (to a dev), often, whether struct initializers are
    // doing by-member initialization or invoking constructors.
    // Anyways, to be useful our USTRUCTS need to be more than POD, have
    // methods and constructors, the defects of Modern C++ not withstanding.
    // If you're confused about this rant, see:
    // https://www.open-std.org/jtc1/sc22/wg21/docs/cwg_defects.html#1270
    // https://blog.feabhas.com/2019/04/brace-initialization-of-user-defined-types/
    // What kind of language seemingly intentionally creates tricky interview
    // questions, obscure bug opportunities, and high learning curves towards mastery??

    inline FSDimensionlessVector()
    {
        x = 0.;
        y = 0.;
        z = 0.;
    }

    inline FSDimensionlessVector(const FSDimensionlessVector& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    // Not necessary for Modern C++ initialization syntax, because 
    // { x, y, z } would do a by-member initialization.
    // But, for consistency with C++98 constructors it is necessary.
    // Many devs will want to initialize C++98 style.
    inline FSDimensionlessVector(double _x, double _y, double _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    // See note Note * (above)
    inline FSDimensionlessVector(const double(&xyz)[3])
    {
        x = xyz[0];
        y = xyz[1];
        z = xyz[2];
    }

    // See note Note * (above)
    inline void CopyTo(double(&xyz)[3]) const
    {
        xyz[0] = x;
        xyz[1] = y;
        xyz[2] = z;
    }

    inline FSDimensionlessVector& operator=(const FSDimensionlessVector& other)
    {
        // No self-assignment guard needed in this case.
        x = other.x;
        y = other.y;
        z = other.z;

        return *this;
    }

    void Normalize();
    static void Normalize(FSDimensionlessVector& vector);
    FSDimensionlessVector Normalized() const;

    double Magnitude() const;

    FString ToString() const;

    static const FSDimensionlessVector Zero;
    static const FSDimensionlessVector X_Axis;
    static const FSDimensionlessVector Y_Axis;
    static const FSDimensionlessVector Z_Axis;

    // IMPORTANT!:
    // Swizzles between UE/SPICE (LHS and RHS coordinate systems)
    // You must swizzle positional data (quaternions, vectors, etc) when
    // exchanging between SPICE and Unreal Engine scenegraph coordinates.
    FVector Swizzle() const;
    static FSDimensionlessVector Swizzle(const FVector& UEVector);
};

static inline FSDimensionlessVector operator+(const FSDimensionlessVector& lhs, const FSDimensionlessVector& rhs) {

    return FSDimensionlessVector(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

static inline FSDimensionlessVector operator-(const FSDimensionlessVector& value)
{
    return FSDimensionlessVector(-value.x, -value.y, -value.z);
}

static inline FSDimensionlessVector operator-(const FSDimensionlessVector& lhs, const FSDimensionlessVector& rhs){

    return FSDimensionlessVector(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

// "exact", but probably not reliable depending on compiler flags, etc etc
// Used in S/C for non-critical things like firing an OnChange event etc
static inline bool operator==(const FSDimensionlessVector& lhs, const FSDimensionlessVector& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

static inline FSDimensionlessVector operator*(double scalar, const FSDimensionlessVector& vector)
{
    return FSDimensionlessVector(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}

static inline FSDimensionlessVector operator*(const FSDimensionlessVector& vector, double scalar)
{
    return FSDimensionlessVector(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}

static inline FSDimensionlessVector operator/(const FSDimensionlessVector& vector, double scalar)
{
    return FSDimensionlessVector(vector.x / scalar, vector.y / scalar, vector.z / scalar);
}


static inline FSDimensionlessVector& operator+=(FSDimensionlessVector& lhs, const FSDimensionlessVector& rhs) {

    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
}

static inline FSDimensionlessVector& operator-=(FSDimensionlessVector& lhs, const FSDimensionlessVector& rhs) {

    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    return lhs;
}

static inline FSDimensionlessVector& operator*=(FSDimensionlessVector& lhs, double rhs) {

    lhs.x *= rhs;
    lhs.y *= rhs;
    lhs.z *= rhs;
    return lhs;
}

static inline FSDimensionlessVector& operator/=(FSDimensionlessVector& lhs, double rhs) {

    lhs.x /= rhs;
    lhs.y /= rhs;
    lhs.z /= rhs;
    return lhs;
}


USTRUCT(BlueprintType, Category = "MaxQ|Distance")
struct SPICE_API FSDistance
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double km;

    static constexpr double KilometersToMeters { 1000. };
    static constexpr double MetersToKilometers { 1. / KilometersToMeters };

    FSDistance()
    {
        km = 0;
    }

    FSDistance(double _km)
    {
        km = _km;
    }

    // "AsDouble()" means the units SPICE expects, so it should really be "AsSpiceDouble"
    [[deprecated("Use AsKilometers() etc")]]
    inline double AsDouble() const  { return AsKilometers(); }
    [[deprecated("Use AsKilometers()")]]
    inline double As_Km() const     { return km; }
    [[deprecated("Use AsMeters()")]]
    inline double As_M() const      { return AsMeters(); }
    [[deprecated("Use AsMeters()")]]
    inline double As_Meters() const { return AsMeters(); }

    inline double AsSpiceDouble() const { return km; }
    inline double AsKilometers() const { return km; }
    inline double AsMeters() const { return AsKilometers() * KilometersToMeters; }
    inline double AsFeet() const;
    inline double AsNauticalMiles() const;
    inline double AsStatuteMiles() const;
    inline double AsAstronomicalUnits() const;
    inline double AsLightYears() const;

    FString ToString() const;
    FString ToString(ES_Units Units, int precision = 12) const;

    [[deprecated("Use FromKilometers()")]]
    inline static FSDistance From_Km(double _km)    { return FromKilometers(_km); }
    [[deprecated("Use FromMeters()")]]
    inline static FSDistance From_M(double _m)      { return FromMeters(_m * MetersToKilometers); }
    [[deprecated("Use FromMeters()")]]
    inline static FSDistance From_Meters(double _m) { return FromMeters(_m); }
    
    inline static FSDistance FromMeters(double _m) { return FromKilometers(_m * MetersToKilometers); }
    [[deprecated("Use FromKilometers()")]]
    inline static FSDistance FromKm(double _km)    { return FromKilometers(_km); }
    inline static FSDistance FromKilometers(double _km)    { return FSDistance(_km); }
    inline static FSDistance FromFeet(double _m);
    inline static FSDistance FromNauticalMiles(double _m);
    inline static FSDistance FromStatuteMiles(double _m);
    inline static FSDistance FromAstronomicalUnits(double _au);
    inline static FSDistance FromLightYears(double _ly);

    FSDistance(const FSDistance& other)
    {
        km = other.km;
    }

    FSDistance& operator=(const FSDistance& other)
    {
        km = other.km;
        return *this;
    }

    static const FSDistance Zero;
    [[deprecated("Use OneMKilometer")]]
    static const FSDistance OneKm;
    static const FSDistance OneKilometer;
    static const FSDistance OneMeter;
    static const FSDistance OneFoot;
    static const FSDistance OneStatuteMile;
    static const FSDistance OneNauticalMile;
    static const FSDistance OneAstronomicalUnit;
    static const FSDistance OneLightYear;
};

static inline bool operator<(const FSDistance& lhs, const FSDistance& rhs)
{
    return lhs.km < rhs.km;
}

static inline bool operator>(const FSDistance& lhs, const FSDistance& rhs)
{
    return lhs.km > rhs.km;
}

static inline FSDistance operator+(const FSDistance& lhs, const FSDistance& rhs)
{
    return FSDistance(lhs.km + rhs.km);
}

static inline FSDistance operator-(const FSDistance& lhs, const FSDistance& rhs)
{
    return FSDistance(lhs.km - rhs.km);
}

static inline FSDistance operator-(const FSDistance& rhs)
{
    return FSDistance(-rhs.km);
}

static inline double operator/(const FSDistance& lhs, const FSDistance& rhs)
{
    return lhs.km / rhs.km;
}

static inline FSDistance operator/(const FSDistance& lhs, double rhs)
{
    return lhs.km / rhs;
}

static inline FSDistance operator*(double lhs, const FSDistance& rhs)
{
    return FSDistance(lhs * rhs.km);
}

static inline FSDistance operator*(const FSDistance& lhs, double rhs)
{
    return FSDistance(lhs.km * rhs);
}

static inline FSDistance& operator*=(FSDistance& lhs, double rhs) {

    lhs.km *= rhs;
    return lhs;
}

static inline bool operator==(const FSDistance& lhs, const FSDistance& rhs)
{
    return lhs.km == rhs.km;
}

static inline bool operator!=(const FSDistance& lhs, const FSDistance& rhs)
{
    return !(lhs == rhs);
}

static inline FSDistance& operator+=(FSDistance& lhs, const FSDistance& rhs) {

    lhs.km += rhs.km;
    return lhs;
}

static inline FSDistance& operator-=(FSDistance& lhs, const FSDistance& rhs) {

    lhs.km -= rhs.km;
    return lhs;
}


USTRUCT(BlueprintType, Category = "MaxQ|DistanceVector", Meta = (ToolTip = "Rectangular coordinates (X, Y, Z)"))
struct SPICE_API FSDistanceVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistance x;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistance y;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistance z;

    inline FSDistanceVector()
    {
        x = FSDistance::Zero;
        y = FSDistance::Zero;
        z = FSDistance::Zero;
    }

    inline FSDistanceVector(double _x, double _y, double _z)
    {
        x = FSDistance(_x);
        y = FSDistance(_y);
        z = FSDistance(_z);
    }

    inline FSDistanceVector(const FSDistance& _x, const FSDistance& _y, const FSDistance& _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    inline FSDistanceVector(const double(&xyz)[3])
    {
        x = FSDistance(xyz[0]);
        y = FSDistance(xyz[1]);
        z = FSDistance(xyz[2]);
    }

    inline FSDistanceVector(const FSDimensionlessVector& value)
    {
        x = FSDistance(value.x);
        y = FSDistance(value.y);
        z = FSDistance(value.z);
    }

    inline void AsDimensionlessVector(FSDimensionlessVector& vector) const
    {
        vector.x = x.AsSpiceDouble();
        vector.y = y.AsSpiceDouble();
        vector.z = z.AsSpiceDouble();
    }

    inline FSDimensionlessVector AsDimensionlessVector() const
    {
        FSDimensionlessVector vector;
        AsDimensionlessVector(vector);
        return vector;
    }

    inline FSDimensionlessVector AsKilometers() const
    {
        return FSDimensionlessVector(x.AsKilometers(), y.AsKilometers(), z.AsKilometers());
    }

    inline void CopyTo(double(&xyz)[3]) const
    {
        xyz[0] = x.km;
        xyz[1] = y.km;
        xyz[2] = z.km;
    }

    FSDimensionlessVector Normalized() const;
    void Normalized(FSDimensionlessVector& v) const;
    FSDistance Magnitude() const;

    inline FSDistance Re() const
    {
        return x;
    }
    inline FSDistance Rp() const
    {
        return z;
    }
    inline double f() const
    {
        return (Re()-Rp())/Re();
    }

    FString ToString() const;

    // IMPORTANT!:
    // Swizzles between UE/SPICE (LHS and RHS coordinate systems)
    // You must swizzle positional data (quaternions, vectors, etc) when
    // exchanging between SPICE and Unreal Engine scenegraph coordinates.
    FVector Swizzle() const;
    static FSDistanceVector Swizzle(const FVector& UEVector);

    static const FSDistanceVector Zero;
};


static inline FSDistanceVector operator+(const FSDistanceVector& lhs, const FSDistanceVector& rhs)
{
    return FSDistanceVector(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

static inline FSDistanceVector operator-(const FSDistanceVector& lhs, const FSDistanceVector& rhs)
{
    return FSDistanceVector(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

static inline FSDistanceVector operator-(const FSDistanceVector& rhs)
{
    return FSDistanceVector(-rhs.x, -rhs.y, -rhs.z);
}

static inline FSDistanceVector operator*(double lhs, const FSDistanceVector& rhs)
{
    return FSDistanceVector(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

static inline FSDistanceVector operator*(const FSDistanceVector& lhs, double rhs)
{
    return FSDistanceVector(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

static inline FSDistanceVector operator/(const FSDistanceVector& lhs, double rhs)
{
    return FSDistanceVector(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

static inline FSDistanceVector operator*(const FSDimensionlessVector& lhs, const FSDistance& rhs)
{
    return FSDistanceVector(lhs.x * rhs.km, lhs.y * rhs.km, lhs.z * rhs.km);
}

static inline FSDistanceVector operator*(const FSDistance& lhs, const FSDimensionlessVector& rhs)
{
    return rhs * lhs;
}

static inline FSDistanceVector& operator+=(FSDistanceVector& lhs, const FSDistanceVector& rhs) {

    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
}

static inline FSDistanceVector& operator-=(FSDistanceVector& lhs, const FSDistanceVector& rhs) {

    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    return lhs;
}

static inline FSDistanceVector& operator*=(FSDistanceVector& lhs, double rhs) {

    lhs.x *= rhs;
    lhs.y *= rhs;
    lhs.z *= rhs;
    return lhs;
}

static inline bool operator==(const FSDistanceVector& lhs, const FSDistanceVector& rhs)
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
}


static inline bool operator!=(const FSDistanceVector& lhs, const FSDistanceVector& rhs)
{
    return !(lhs == rhs);
}

static inline FSDimensionlessVector operator/(const FSDistanceVector& lhs, const FSDistanceVector& rhs)
{
    return FSDimensionlessVector(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

static inline FSDimensionlessVector operator/(const FSDistanceVector& lhs, const FSDistance& rhs)
{
    return FSDimensionlessVector(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}


USTRUCT(BlueprintType, Category = "MaxQ|Speed")
struct SPICE_API FSSpeed
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double kmps;

    FSSpeed()
    {
        kmps = 0;
    }

    FSSpeed(double _kmps)
    {
        kmps = _kmps;
    }

    // "AsDouble()" means the units SPICE expects, so it should really be "AsSpiceDouble"
    [[deprecated("Use AsKilometersPerSecond()")]]
    inline double AsDouble() const { return AsKilometersPerSecond(); }
    /// <summary>Returns value in km/sec</summary>
    /// <returns>Kilometers Per Second</returns>
    inline double AsSpiceDouble() const { return kmps; }
    inline double AsKilometersPerSecond() const { return kmps; }

    FSSpeed(const FSSpeed& other)
    {
        kmps = other.kmps;
    }

    FSSpeed& operator=(const FSSpeed& other)
    {
        kmps = other.kmps;
        return *this;
    }

    static inline FSSpeed FromKilometersPerSecond(double KilometersPerSecond)
    {
        return FSSpeed(KilometersPerSecond);
    }

    static inline FSSpeed FromMetersPerSecond(double MetersPerSecond)
    {
        return FSSpeed(MetersPerSecond * FSDistance::MetersToKilometers);
    }

    FString ToString() const;
    FString ToString(ES_Units NumeratorUnits, ES_Units DenominatorUnits = ES_Units::SECONDS, int precision = 12) const;

    static const FSSpeed Zero;
    static const FSSpeed OneKmps;
};

static inline FSSpeed operator+(const FSSpeed& lhs, const FSSpeed& rhs)
{
    return FSSpeed(lhs.kmps + rhs.kmps);
}

static inline FSSpeed operator-(const FSSpeed& rhs)
{
    return FSSpeed(-rhs.kmps);
}

static inline FSSpeed operator-(const FSSpeed& lhs, const FSSpeed& rhs)
{
    return FSSpeed(lhs.kmps - rhs.kmps);
}

static inline double operator/(const FSSpeed& lhs, const FSSpeed& rhs)
{
    return lhs.kmps / rhs.kmps;
}

static inline FSSpeed operator/(const FSSpeed& lhs, double rhs)
{
    return lhs.kmps / rhs;
}

static inline bool operator>(const FSSpeed& lhs, const FSSpeed& rhs)
{
    return lhs.kmps > rhs.kmps;
}

static inline bool operator<(const FSSpeed& lhs, const FSSpeed& rhs)
{
    return lhs.kmps < rhs.kmps;
}

static inline FSSpeed operator*(double lhs, const FSSpeed& rhs)
{
    return FSSpeed(lhs * rhs.kmps);
}

static inline FSSpeed operator*(const FSSpeed& lhs, double rhs)
{
    return FSSpeed(lhs.kmps * rhs);
}

static inline bool operator==(const FSSpeed& lhs, const FSSpeed& rhs)
{
    return lhs.kmps == rhs.kmps;
}

static inline bool operator!=(const FSSpeed& lhs, const FSSpeed& rhs)
{
    return !(lhs == rhs);
}

static inline FSSpeed& operator+=(FSSpeed& lhs, const FSSpeed& rhs) {

    lhs.kmps += rhs.kmps;
    return lhs;
}

static inline FSSpeed& operator-=(FSSpeed& lhs, const FSSpeed& rhs) {

    lhs.kmps -= rhs.kmps;
    return lhs;
}





/*  You decide:
 *
 *  If you prefer editability over numerical stability, serialize to/from degrees.
 *  Unfortunately, since the value could be dirtied at any time we'll have to multiple/divide
 *  anytime the code needs the value, as all client code assumed radians.
 *
 *  If you prefer numerical stablity, serialize the data to/from radians.
 *
 *  If anyone knows a way to have custom serialization for a struct and defer the
 *  multiplication/division until the value is actually serialized/displayed/etc
 *  please le me know!
 *  Otherwise, we'll need to multiply/divide on every read/write.
 *
 *  UE doesn't allow putting the member definitions inside a preprocessor #if/#endif
 *  block, or we could support either or with a PREFER_NUMERICAL_STABILTY_OVER_EDITABILITY
 *  macro definition.
 */
USTRUCT(BlueprintType, Category = "MaxQ|Angle")
struct SPICE_API FSAngle
{
    GENERATED_BODY()

    // However, we want users to see degrees when editing or looking at serialized data.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double degrees;

private:
    // Q: why keep 180/pi's value in every instance of the struct?
    // A: to keep it in the same cache line as our data
    // Premature optimization may be the root of all evil, but this hurts nothing.
    // CSPICE was built with numerical stability in mind, I think it's preferable
    // to defer to it for definitions of all constants.
    double cachedDpr;

    // Use AsRadians(), (or AsSpiceDouble if you need Spice-default units)
    inline double radians() const
    {
        return degrees / cachedDpr;
    }

public:

    // Let's use the CSPICE version of pi.  Since this is a header file, and we
    // don't want other modules to require the spice headers to use this module,
    // we'll need to bounce the constructor definitions out to a cpp file.
    FSAngle();

    FSAngle(double __radians);


    inline FSAngle(const FSAngle& other)
    {
        degrees = other.degrees;
        cachedDpr = other.cachedDpr;
    }

    // "AsDouble()" means "AsSpiceDouble()"
    [[deprecated("Use AsRadians()")]]
    inline double AsDouble() const { return AsRadians(); }
    /// <summary>Returns value in Radians</summary>
    /// <returns>Radians</returns>
    inline double AsSpiceDouble() const { return radians(); }
    inline double AsRadians() const { return radians(); }
    inline double AsDegrees() const { return degrees; }
    static inline FSAngle FromSpiceDouble(double spiceDoubleAkaRadians)
    {
        return FSAngle(spiceDoubleAkaRadians);
    }
    static inline FSAngle FromRadians(double radians)
    {
        return FSAngle(radians);
    }
    static inline FSAngle FromDegrees(double degrees)
    {
        FSAngle Result;
        Result.degrees = degrees;
        return Result;
    }

    bool operator==(const FSAngle& Other) const
    {
        return degrees == Other.degrees;
    }

    bool operator!=(const FSAngle& Other) const
    {
        return !(*this == Other);
    }

    FString ToString() const;
    FString ToString(ES_AngleFormat format) const;

    static const FSAngle _0;
    static const FSAngle _360;
    static const double halfpi;
    static const double pi;
    static const double twopi;
    static const double dpr;
};



static inline FSAngle operator*(double lhs, const FSAngle& rhs)
{
    return FSAngle(rhs.AsSpiceDouble() * lhs);
}

static inline FSAngle operator*(const FSAngle& lhs,double rhs)
{
    return FSAngle(lhs.AsSpiceDouble() * rhs);
}

static inline FSAngle operator+(const FSAngle& lhs, const FSAngle& rhs)
{
    return FSAngle(lhs.AsSpiceDouble() + rhs.AsSpiceDouble());
}

static inline FSAngle operator-(const FSAngle& rhs)
{
    return FSAngle(-rhs.AsSpiceDouble());
}

static inline FSAngle operator-(const FSAngle& lhs, const FSAngle& rhs)
{
    return FSAngle(lhs.AsSpiceDouble() - rhs.AsSpiceDouble());
}

static inline FSAngle operator/(const FSAngle& lhs, double rhs)
{
    return FSAngle(lhs.AsSpiceDouble() / rhs);
}

static inline double operator/(const FSAngle& lhs, const FSAngle& rhs)
{
    return lhs.AsSpiceDouble() / rhs.AsSpiceDouble();
}

static inline FSAngle& operator+=(FSAngle& lhs, const FSAngle& rhs) {

    lhs = FSAngle(lhs.AsSpiceDouble() + rhs.AsSpiceDouble());
    return lhs;
}

static inline FSAngle& operator-=(FSAngle& lhs, const FSAngle& rhs) {

    lhs = FSAngle(lhs.AsSpiceDouble() - rhs.AsSpiceDouble());
    return lhs;
}

static inline FSAngle& operator*=(FSAngle& lhs, double rhs) {

    lhs = FSAngle(lhs.AsSpiceDouble() * rhs);
    return lhs;
}


USTRUCT(BlueprintType, Category = "MaxQ|AngularRate")
struct SPICE_API FSAngularRate
{
    GENERATED_BODY()

    // It's not much of a win serializizing this as degreesPerSecond,
    // as serialized data for angular rates are rarely edited compared to angles.
    // However, a period/revolution could make sense, ... but time is very messy
    // anyways.  How many seconds long is one sidereal day?  Not much of a win
    // editing "seconds" versus "radiansPerSecond".
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double radiansPerSecond;

    FSAngularRate()
    {
        radiansPerSecond = 0.;
    }

    FSAngularRate(double _radiansPerSecond)
    {
        radiansPerSecond = _radiansPerSecond;
    }

    [[deprecated("Use AsDegreesPerSecond()")]]
    double degreesPerSecond() const { return AsDegreesPerSecond(); }


    [[deprecated("Use AsRadiansPerSecond()")]]
    inline double AsDouble() const { return AsRadiansPerSecond(); }
    /// <summary>Returns value in Radians/Second</summary>
    /// <returns>Radians/Second</returns>
    inline double AsSpiceDouble() const { return radiansPerSecond; }
    inline double AsRadiansPerSecond() const { return radiansPerSecond; }
    double AsDegreesPerSecond() const;

    FString ToString() const;

    static inline FSAngularRate FromSpiceDouble(double SpiceDouble) { return FSAngularRate(SpiceDouble); }
    static inline FSAngularRate FromRadiansPerSecond(double RadiansPerSecond) { return FSAngularRate(RadiansPerSecond); }
    static FSAngularRate FromDegreesPerSecond(double DegreesPerSecond);

    static const FSAngularRate Zero;
};



static inline FSAngularRate operator*(double lhs, const FSAngularRate& rhs)
{
    return FSAngularRate(rhs.AsSpiceDouble() * lhs);
}

static inline FSAngularRate operator*(const FSAngularRate& lhs, double rhs)
{
    return FSAngularRate(lhs.AsSpiceDouble() * rhs);
}

static inline FSAngularRate operator+(const FSAngularRate& lhs, const FSAngularRate& rhs)
{
    return FSAngularRate(lhs.AsSpiceDouble() + rhs.AsSpiceDouble());
}

static inline FSAngularRate operator-(const FSAngularRate& lhs, const FSAngularRate& rhs)
{
    return FSAngularRate(lhs.AsSpiceDouble() - rhs.AsSpiceDouble());
}

static inline FSAngularRate operator-(const FSAngularRate& rhs)
{
    return FSAngularRate(-rhs.AsSpiceDouble());
}

static inline FSAngularRate operator/(const FSAngularRate& lhs, double rhs)
{
    return FSAngularRate(lhs.AsSpiceDouble() / rhs);
}

static inline double operator/(const FSAngularRate& lhs, const FSAngularRate& rhs)
{
    return lhs.AsSpiceDouble() / rhs.AsSpiceDouble();
}

static inline FSAngularRate& operator+=(FSAngularRate& lhs, const FSAngularRate& rhs) {

    lhs = FSAngularRate(lhs.AsSpiceDouble() + rhs.AsSpiceDouble());
    return lhs;
}

static inline FSAngularRate& operator-=(FSAngularRate& lhs, const FSAngularRate& rhs) {

    lhs = FSAngularRate(lhs.AsSpiceDouble() - rhs.AsSpiceDouble());
    return lhs;
}

static inline bool operator==(const FSAngularRate& lhs, const FSAngularRate& rhs) {

    return lhs.AsSpiceDouble() == rhs.AsSpiceDouble();
}

static inline bool operator!=(const FSAngularRate& lhs, const FSAngularRate& rhs) {

    return !(lhs == rhs);
}



USTRUCT(BlueprintType, Category = "MaxQ|ComplexScalar")
struct SPICE_API FSComplexScalar
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double real;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double imaginary;

    FSComplexScalar()
    {
        real = 0.;
        imaginary = 0.;
    }

    FSComplexScalar(const double(&_value)[2])
    {
        real = _value[0];
        imaginary = _value[1];
    }

    /// <summary>Returns value (Dimensionless)</summary>
    /// <returns>Value</returns>
    void CopyTo(double(&_value)[2]) const
    {
        _value[0] = real;
        _value[1] = imaginary;
    }

    FString ToString() const;

    static const FSComplexScalar Zero;
};


USTRUCT(BlueprintType, Category = "MaxQ|EphemerisTime")
struct SPICE_API FSEphemerisTime
{
    GENERATED_BODY()

    // ephemeris seconds past J2000
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double seconds;

    FSEphemerisTime()
    {
        seconds = 0.;
    }

    FSEphemerisTime(double _seconds)
    {
        seconds = _seconds;
    }

    [[deprecated("Use AsSeconds()")]]
    inline double AsDouble() const { return AsSeconds(); }
    /// <summary>Returns value in Seconds past J2000 Epoch</summary>
    /// <returns>Seconds</returns>
    inline double AsSpiceDouble() const { return seconds; }
    inline double AsSeconds() const { return seconds; }

    FString ToString() const;
    FString ToString(ES_UTCTimeFormat TimeFormat, int precision = 4) const;
    static FSEphemerisTime FromString(const FString& Str);

    // The J2000 epoch (1 Jan 2000, 11:58:55.816 UTC)
    // https://en.wikipedia.org/wiki/Equinox_(celestial_coordinates)#J2000.0
    static const FSEphemerisTime J2000;
};

static inline bool operator==(const FSEphemerisTime& lhs, const FSEphemerisTime& rhs)
{
    return lhs.seconds == rhs.seconds;
}

static inline bool operator!=(const FSEphemerisTime& lhs, const FSEphemerisTime& rhs)
{
    return !(lhs == rhs);
}

static inline bool operator<(const FSEphemerisTime& lhs, const FSEphemerisTime& rhs)
{
    return lhs.seconds < rhs.seconds;
}

static inline bool operator>(const FSEphemerisTime& lhs, const FSEphemerisTime& rhs)
{
    return lhs.seconds > rhs.seconds;
}


USTRUCT(BlueprintType, Category = "MaxQ|EphemerisPeriod")
struct SPICE_API FSEphemerisPeriod
{
    GENERATED_BODY()

    // ephemeris seconds
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double seconds;

    FSEphemerisPeriod()
    {
        seconds = 0.;
    }

    FSEphemerisPeriod(double _seconds)
    {
        seconds = _seconds;
    }

    /// <summary>Ephemeris Period in seconds</summary>
    /// <returns>Seconds</returns>
    [[deprecated("Use AsSeconds()")]]
    inline double AsDouble() const { return AsSeconds(); }
    /// <summary>Ephemeris Period in seconds</summary>
    /// <returns>Seconds</returns>
    inline double AsSpiceDouble() const { return seconds; }
    inline double AsSeconds() const { return seconds; }

    FString ToString() const;
    FString ToString(ES_Units Units, int precision = 12) const;

    static inline FSEphemerisPeriod FromSeconds(double InSeconds)
    {
        return FSEphemerisPeriod(InSeconds);
    }

    static const FSEphemerisPeriod Zero;
    static const FSEphemerisPeriod OneSecond;
    static const FSEphemerisPeriod OneMinute;
    static const FSEphemerisPeriod OneHour;
    [[deprecated("Use OneDay")]]
    static const FSEphemerisPeriod Day;
    static const FSEphemerisPeriod OneDay;
    static const FSEphemerisPeriod OneTropicalYear;
    static const FSEphemerisPeriod OneJulianYear;
};

static inline FSEphemerisPeriod operator+(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return FSEphemerisPeriod(A.AsSpiceDouble() + B.AsSpiceDouble());
}

static inline FSEphemerisPeriod operator-(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return FSEphemerisPeriod(A.AsSpiceDouble() - B.AsSpiceDouble());
}

static inline FSEphemerisTime operator+(const FSEphemerisPeriod& A, const FSEphemerisTime& B)
{
    return FSEphemerisTime(A.AsSpiceDouble() + B.AsSpiceDouble());
}

static inline FSEphemerisTime operator+(const FSEphemerisTime& A, const FSEphemerisPeriod& B)
{
    return FSEphemerisTime(A.AsSpiceDouble() + B.AsSpiceDouble());
}

static inline FSEphemerisTime operator-(const FSEphemerisTime& A, const FSEphemerisPeriod& B)
{
    return FSEphemerisTime(A.AsSpiceDouble() - B.AsSpiceDouble());
}


static inline FSEphemerisPeriod& operator+=(FSEphemerisPeriod& lhs, const FSEphemerisPeriod& rhs) {

    lhs = FSEphemerisPeriod(lhs.AsSpiceDouble() + rhs.AsSpiceDouble());
    return lhs;
}

static inline FSEphemerisPeriod& operator-=(FSEphemerisPeriod& lhs, const FSEphemerisPeriod& rhs) {

    lhs = FSEphemerisPeriod(lhs.AsSpiceDouble() - rhs.AsSpiceDouble());
    return lhs;
}

static inline FSEphemerisTime& operator+=(FSEphemerisTime& lhs, const FSEphemerisPeriod& rhs) {

    lhs = lhs + rhs;
    return lhs;
}

static inline FSEphemerisTime& operator-=(FSEphemerisTime& lhs, const FSEphemerisPeriod& rhs) {

    lhs = lhs - rhs;
    return lhs;
}

static inline FSEphemerisPeriod operator-(const FSEphemerisTime& A, const FSEphemerisTime& B)
{
    return FSEphemerisPeriod(A.AsSpiceDouble() - B.AsSpiceDouble());
}

static inline FSEphemerisPeriod operator*(double A, const FSEphemerisPeriod& B)
{
    return FSEphemerisPeriod(A * B.AsSpiceDouble());
}

static inline FSEphemerisPeriod operator*(const FSEphemerisPeriod& A, double B)
{
    return FSEphemerisPeriod(A.AsSpiceDouble() * B);
}

static inline FSEphemerisPeriod& operator*=(FSEphemerisPeriod& lhs, double rhs) {

    lhs.seconds *= rhs;
    return lhs;
}

static inline FSEphemerisPeriod& operator/=(FSEphemerisPeriod& lhs, double rhs) {

    lhs.seconds /= rhs;
    return lhs;
}

static inline FSEphemerisPeriod operator/(const FSEphemerisPeriod& A, double B)
{
    return FSEphemerisPeriod(A.AsSpiceDouble() / B);
}

static inline double operator/(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return A.AsSpiceDouble() / B.AsSpiceDouble();
}

static inline FSEphemerisPeriod operator%(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return FSEphemerisPeriod( fmod(A.AsSpiceDouble(), B.AsSpiceDouble()) );
}


static inline bool operator==(const FSEphemerisPeriod& lhs, const FSEphemerisPeriod& rhs)
{
    return lhs.seconds == rhs.seconds;
}

static inline bool operator!=(const FSEphemerisPeriod& lhs, const FSEphemerisPeriod& rhs)
{
    return !(lhs == rhs);
}


static inline bool operator>(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return A.AsSpiceDouble() > B.AsSpiceDouble();
}

static inline bool operator<(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return A.AsSpiceDouble() < B.AsSpiceDouble();
}

static inline FSDistance operator*(const FSEphemerisPeriod& lhs, const FSSpeed& rhs)
{
    return FSDistance(lhs.seconds * rhs.kmps);
}

static inline FSDistance operator*(const FSSpeed& lhs, const FSEphemerisPeriod& rhs)
{
    return FSDistance(lhs.kmps * rhs.seconds);
}

static inline FSAngularRate operator/(const FSAngle& lhs, const FSEphemerisPeriod& rhs)
{
    return FSAngularRate(lhs.AsRadians() / rhs.AsSeconds());
}

USTRUCT(BlueprintType, Category = "MaxQ|VelocityVector", Meta = (ToolTip = "Rectangular  coordinates (DX, DY, DZ)"))
struct SPICE_API FSVelocityVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSSpeed dx;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSSpeed dy;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSSpeed dz;

    inline FSVelocityVector()
    {
        dx = FSSpeed::Zero;
        dy = FSSpeed::Zero;
        dz = FSSpeed::Zero;
    }

    inline FSVelocityVector(const double(&xyz)[3])
    {
        dx = FSSpeed(xyz[0]);
        dy = FSSpeed(xyz[1]);
        dz = FSSpeed(xyz[2]);
    }

    inline FSVelocityVector(double _dx, double _dy, double _dz)
    {
        dx = FSSpeed(_dx);
        dy = FSSpeed(_dy);
        dz = FSSpeed(_dz);
    }

    inline FSVelocityVector(const FSSpeed& _dx, const FSSpeed& _dy, const FSSpeed& _dz)
    {
        dx = FSSpeed(_dx);
        dy = FSSpeed(_dy);
        dz = FSSpeed(_dz);
    }

    inline FSVelocityVector(const FSDimensionlessVector& value)
    {
        dx = FSSpeed(value.x);
        dy = FSSpeed(value.y);
        dz = FSSpeed(value.z);
    }

    inline void AsDimensionlessVector(FSDimensionlessVector& vector) const
    {
        vector.x = dx.AsSpiceDouble();
        vector.y = dy.AsSpiceDouble();
        vector.z = dz.AsSpiceDouble();
    }

    inline FSDimensionlessVector AsDimensionlessVector() const
    {
        FSDimensionlessVector vector;
        AsDimensionlessVector(vector);
        return vector;
    }

    inline FSDimensionlessVector AsKilometersPerSecond() const
    {
        return FSDimensionlessVector(dx.AsKilometersPerSecond(), dy.AsKilometersPerSecond(), dz.AsKilometersPerSecond());
    }

    FString ToString() const;

    inline void CopyTo(double(&xyz)[3]) const
    {
        xyz[0] = dx.kmps;
        xyz[1] = dy.kmps;
        xyz[2] = dz.kmps;
    }

    FSDimensionlessVector Normalized() const;
    void Normalized(FSDimensionlessVector& v) const;
    FSSpeed Magnitude() const;

    // IMPORTANT!:
    // Swizzles between UE/SPICE (LHS and RHS coordinate systems)
    // You must swizzle positional data (quaternions, vectors, etc) when
    // exchanging between SPICE and Unreal Engine scenegraph coordinates.
    FVector Swizzle() const;
    static FSVelocityVector Swizzle(const FVector& UEVector);

    static const FSVelocityVector Zero;
};


static inline FSVelocityVector operator+(const FSVelocityVector& lhs, const FSVelocityVector& rhs)
{
    return FSVelocityVector(lhs.dx + rhs.dx, lhs.dy + rhs.dy, lhs.dz + rhs.dz);
}

static inline FSVelocityVector operator-(const FSVelocityVector& rhs)
{
    return FSVelocityVector(-rhs.dx, -rhs.dy, -rhs.dz);
}

static inline FSVelocityVector operator-(const FSVelocityVector& lhs, const FSVelocityVector& rhs)
{
    return FSVelocityVector(lhs.dx - rhs.dx, lhs.dy - rhs.dy, lhs.dz - rhs.dz);
}

static inline FSVelocityVector operator/(const FSVelocityVector& lhs, double rhs)
{
    return FSVelocityVector(lhs.dx / rhs, lhs.dy / rhs, lhs.dz / rhs);
}

static inline FSDimensionlessVector operator/(const FSVelocityVector& lhs, const FSVelocityVector& rhs)
{
    return FSDimensionlessVector(lhs.dx / rhs.dx, lhs.dy / rhs.dy, lhs.dz / rhs.dz);
}

static inline FSVelocityVector operator*(double lhs, const FSVelocityVector& rhs)
{
    return FSVelocityVector(lhs * rhs.dx, lhs * rhs.dy, lhs * rhs.dz);
}

static inline FSVelocityVector operator*(const FSVelocityVector& lhs, double rhs)
{
    return FSVelocityVector(lhs.dx * rhs, lhs.dy * rhs, lhs.dz * rhs);
}

static inline FSVelocityVector operator*(const FSDimensionlessVector& lhs, const FSSpeed& rhs)
{
    return FSVelocityVector(lhs.x * rhs.kmps, lhs.y * rhs.kmps, lhs.z * rhs.kmps);
}

static inline FSVelocityVector operator*(const FSSpeed& lhs, const FSDimensionlessVector& rhs)
{
    return rhs * lhs;
}

static inline FSDistanceVector operator*(const FSEphemerisPeriod& lhs, const FSVelocityVector& rhs)
{
    return FSDistanceVector(lhs * rhs.dx, lhs * rhs.dy, lhs * rhs.dz);
}

static inline FSDistanceVector operator*(const FSVelocityVector& lhs, const FSEphemerisPeriod& rhs)
{
    return FSDistanceVector(rhs * lhs.dx, rhs * lhs.dy, rhs * lhs.dz);
}

static inline bool operator==(const FSVelocityVector& lhs, const FSVelocityVector& rhs)
{
    return (lhs.dx == rhs.dx) && (lhs.dy == rhs.dy) && (lhs.dz == rhs.dz);
}

static inline bool operator!=(const FSVelocityVector& lhs, const FSVelocityVector& rhs)
{
    return !(lhs == rhs);
}

static inline FSVelocityVector& operator+=(FSVelocityVector& lhs, const FSVelocityVector& rhs) {

    lhs.dx += rhs.dx;
    lhs.dy += rhs.dy;
    lhs.dz += rhs.dz;
    return lhs;
}

static inline FSVelocityVector& operator-=(FSVelocityVector& lhs, const FSVelocityVector& rhs) {

    lhs.dx -= rhs.dx;
    lhs.dy -= rhs.dy;
    lhs.dz -= rhs.dz;
    return lhs;
}


// In SPICE longitude is always given first, which is opposite of many conventions.
// Maintaining consistency with SPICE is higher priority for MaxQ.
USTRUCT(BlueprintType)
struct SPICE_API FSLonLat
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngle longitude;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngle latitude;

    FSLonLat()
    {
        longitude = FSAngle::_0;
        latitude = FSAngle::_0;
    }

    FSLonLat(double lon, double lat)
    {
        longitude = FSAngle(lon);
        latitude = FSAngle(lat);
    }

    FSLonLat(const FSAngle& lon, const FSAngle& lat)
    {
        longitude = FSAngle(lon);
        latitude = FSAngle(lat);
    }

    void AsAngles(FSAngle& lon, FSAngle& lat) const
    {
        lon = longitude;
        lat = latitude;
    }

    FString ToString() const;
    FString ToString(const FString& separator, ES_AngleFormat format = ES_AngleFormat::DD) const;

    void CopyTo(double& lon, double& lat) const
    {
        lon = longitude.AsSpiceDouble();
        lat = latitude.AsSpiceDouble();
    }
};




USTRUCT(BlueprintType, Category = "MaxQ|EulerAngles")
struct SPICE_API FSEulerAngles
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngle angle3;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngle angle2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngle angle1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") ES_Axis axis3;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") ES_Axis axis2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") ES_Axis axis1;

    FSEulerAngles()
    {
        angle3 = FSAngle::_0;
        angle2 = FSAngle::_0;
        angle1 = FSAngle::_0;
        axis3 = ES_Axis::X;
        axis2 = ES_Axis::Y;
        axis1 = ES_Axis::Z;
    }

    FSEulerAngles(const double(&_eulang)[3], uint8 _axis3, uint8 _axis2, uint8 _axis1)
    {
        angle3 = _eulang[0];
        angle2 = _eulang[1];
        angle1 = _eulang[2];
        axis3 = (ES_Axis)_axis3;
        axis2 = (ES_Axis)_axis2;
        axis1 = (ES_Axis)_axis1;
    }

    FSEulerAngles(const FSDimensionlessVector& value);
    void AsDimensionlessVector(FSDimensionlessVector& vector) const;

    FString ToString() const;

    void CopyTo(double(&_eulang)[3], uint8& _axis3, uint8& _axis2, uint8& _axis1) const
    {
        _eulang[0] = angle3.AsSpiceDouble();
        _eulang[1] = angle2.AsSpiceDouble();
        _eulang[2] = angle1.AsSpiceDouble();
        _axis3 = (uint8)axis3;
        _axis2 = (uint8)axis2;
        _axis1 = (uint8)axis1;
    }

    static const FSEulerAngles Zero;
};


USTRUCT(BlueprintType, Category = "MaxQ|AngularVelocity")
struct SPICE_API FSAngularVelocity
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularRate x;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularRate y;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularRate z;

    FSAngularVelocity()
    {
        x = FSAngularRate::Zero;
        y = FSAngularRate::Zero;
        z = FSAngularRate::Zero;
    }

    FSAngularVelocity(const double(&_av)[3])
    {
        x = FSAngularRate(_av[0]);
        y = FSAngularRate(_av[1]);
        z = FSAngularRate(_av[2]);
    }

    FSAngularVelocity(const FSAngularRate& _x, const FSAngularRate& _y, const FSAngularRate& _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    FSAngularVelocity(const FSDimensionlessVector& value)
    {
        x = FSAngularRate(value.x);
        y = FSAngularRate(value.y);
        z = FSAngularRate(value.z);
    }

    void AsDimensionlessVector(FSDimensionlessVector& vector) const
    {
        vector.x = x.AsSpiceDouble();
        vector.y = y.AsSpiceDouble();
        vector.z = z.AsSpiceDouble();
    }

    FSDimensionlessVector AsDimensionlessVector() const
    {
        FSDimensionlessVector vector;
        AsDimensionlessVector(vector);
        return vector;
    }

    FSDimensionlessVector AsRadiansPerSecond() const
    {
        return FSDimensionlessVector(x.AsRadiansPerSecond(), y.AsRadiansPerSecond(), z.AsRadiansPerSecond());
    }

    FString ToString() const;

    static FSAngularVelocity FromRadiansPerSecond(const FSDimensionlessVector& RadsPerSec)
    {
        return FSAngularVelocity(RadsPerSec);
    }

    void CopyTo(double(&_av)[3]) const
    {
        _av[0] = x.radiansPerSecond;
        _av[1] = y.radiansPerSecond;
        _av[2] = z.radiansPerSecond;
    }

    FSDimensionlessVector Normalized() const;
    void Normalized(FSDimensionlessVector& v) const;

    FSAngularRate Magnitude() const;

    static const FSAngularVelocity Zero;

    // IMPORTANT!:
    // Swizzles between UE/SPICE (LHS and RHS coordinate systems)
    // You must swizzle positional data (quaternions, vectors, etc) when
    // exchanging between SPICE and Unreal Engine scenegraph coordinates.
    FVector Swizzle() const;
    static FSAngularVelocity Swizzle(const FVector& UEVector);
};


static inline FSAngularVelocity operator+(const FSAngularVelocity& lhs, const FSAngularVelocity& rhs)
{
    return FSAngularVelocity(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

static inline FSAngularVelocity operator-(const FSAngularVelocity& rhs)
{
    return FSAngularVelocity(-rhs.x, -rhs.y, -rhs.z);
}

static inline FSAngularVelocity operator-(const FSAngularVelocity& lhs, const FSAngularVelocity& rhs)
{
    return FSAngularVelocity(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

static inline FSAngularVelocity operator/(const FSAngularVelocity& lhs, double rhs)
{
    return FSAngularVelocity(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

static inline FSDimensionlessVector operator/(const FSAngularVelocity& lhs, const FSAngularVelocity& rhs)
{
    return FSDimensionlessVector(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

static inline FSAngularVelocity operator*(double lhs, const FSAngularVelocity& rhs)
{
    return FSAngularVelocity(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

static inline FSAngularVelocity operator*(const FSAngularVelocity& lhs, double rhs)
{
    return FSAngularVelocity(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

static inline FSAngularVelocity& operator+=(FSAngularVelocity& lhs, const FSAngularVelocity& rhs) {

    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
}

static inline FSAngularVelocity& operator-=(FSAngularVelocity& lhs, const FSAngularVelocity& rhs) {

    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    return lhs;
}

// The equality operator is useful for unit tests.
static inline bool operator==(const FSAngularVelocity& lhs, const FSAngularVelocity& rhs) {

    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

// The equality operator is used primarily for unit tests.
static inline bool operator!=(const FSAngularVelocity& lhs, const FSAngularVelocity& rhs) {

    return !(lhs == rhs);
}



USTRUCT(BlueprintType, Category = "MaxQ|EulerAngularState")
struct SPICE_API FSEulerAngularState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngle angle3;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngle angle2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngle angle1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularRate rate3;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularRate rate2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularRate rate1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") ES_Axis axis3;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") ES_Axis axis2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") ES_Axis axis1;

    FSEulerAngularState()
    {
        angle3 = FSAngle::_0;
        angle2 = FSAngle::_0;
        angle1 = FSAngle::_0;
        rate3 = FSAngularRate::Zero;
        rate2 = FSAngularRate::Zero;
        rate1 = FSAngularRate::Zero;
        axis3 = ES_Axis::X;
        axis2 = ES_Axis::Y;
        axis1 = ES_Axis::Z;
    }

    FSEulerAngularState(const double(&_eulang)[6], uint8 _axis3, uint8 _axis2, uint8 _axis1)
    {
        angle3 = _eulang[0];
        angle2 = _eulang[1];
        angle1 = _eulang[2];
        rate3 = _eulang[3];
        rate2 = _eulang[4];
        rate1 = _eulang[5];
        axis3 = (ES_Axis)_axis3;
        axis2 = (ES_Axis)_axis2;
        axis1 = (ES_Axis)_axis1;
    }

    void CopyTo(double(&_eulang)[6], uint8& _axis3, uint8& _axis2, uint8& _axis1) const
    {
        _eulang[0] = angle3.AsSpiceDouble();
        _eulang[1] = angle2.AsSpiceDouble();
        _eulang[2] = angle1.AsSpiceDouble();
        _eulang[3] = rate3.radiansPerSecond;
        _eulang[4] = rate2.radiansPerSecond;
        _eulang[5] = rate1.radiansPerSecond;
        _axis3 = (uint8)axis3;
        _axis2 = (uint8)axis2;
        _axis1 = (uint8)axis1;
    }

    static const FSEulerAngularState Zero;

    FString ToString() const;
};





USTRUCT(BlueprintType, Category = "MaxQ|MassConstant")
struct SPICE_API FSMassConstant
{
    GENERATED_BODY()

    // In many cases GM is known to greater accuracy than G or M.
    // https://en.wikipedia.org/wiki/Standard_gravitational_parameter
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double GM;

    FSMassConstant()
    {
        GM = 0;
    }

    FSMassConstant(double _GM)
    {
        GM = _GM;
    }

    [[deprecated("Use AsKm3perSec2()")]]
    inline double AsDouble() const
    {
        return AsKm3perSec2();
    }
    /// <summary>Returns value in km^3/sec^2/</summary>
    /// <returns>km^3/sec^2</returns>
    inline double AsSpiceDouble() const
    {
        return GM;
    }

    inline double AsKm3perSec2() const
    {
        return GM;
    }

    inline bool IsPositive() const
    {
        return GM > 0.;
    }

    static const FSMassConstant Zero;

    FString ToString() const;
};


static inline bool operator==(const FSMassConstant& lhs, const FSMassConstant& rhs)
{
    return (lhs.GM == rhs.GM) && (lhs.GM == rhs.GM);
}

static inline bool operator!=(const FSMassConstant& lhs, const FSMassConstant& rhs)
{
    return !(lhs == rhs);
}


USTRUCT(BlueprintType)
struct SPICE_API FSDimensionlessStateVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDimensionlessVector r;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDimensionlessVector dr;

    FSDimensionlessStateVector()
    {
        r = FSDimensionlessVector();
        dr = FSDimensionlessVector();
    }

    FSDimensionlessStateVector(const double(&state)[6])
    {
        r = FSDimensionlessVector(state[0], state[1], state[2]);
        dr = FSDimensionlessVector(state[3], state[4], state[5]);
    }

    void CopyTo(double(&state)[6]) const
    {
        state[0] = r.x;
        state[1] = r.y;
        state[2] = r.z;
        state[3] = dr.x;
        state[4] = dr.y;
        state[5] = dr.z;
    }


    FSDimensionlessStateVector(const FSDimensionlessVector& _r, const FSDimensionlessVector& _dr)
    {
        r = FSDimensionlessVector(_r);
        dr = FSDimensionlessVector(_dr);
    }

    FString ToString() const;
};



USTRUCT(BlueprintType, Meta = (ToolTip = "Rectangular  coordinates (X, Y, Z, DX, DY, DZ)"))
struct SPICE_API FSStateVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistanceVector r;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSVelocityVector v;

    FSStateVector()
    {
        r = FSDistanceVector();
        v = FSVelocityVector();
    }

    FSStateVector(const double(&state)[6])
    {
        r = FSDistanceVector(state[0], state[1], state[2]);
        v = FSVelocityVector(state[3], state[4], state[5]);
    }

    FSStateVector(const FSDistanceVector& _r, const FSVelocityVector& _v)
    {
        r = _r;
        v = _v;
    }

    void CopyTo(double(&state)[6]) const
    {
        state[0] = r.x.km;
        state[1] = r.y.km;
        state[2] = r.z.km;
        state[3] = v.dx.kmps;
        state[4] = v.dy.kmps;
        state[5] = v.dz.kmps;
    }

    FSStateVector(const FSDimensionlessStateVector& _v)
    {
        r = FSDistanceVector(_v.r);
        v = FSVelocityVector(_v.dr);
    }

    void AsDimensionlessVectors(FSDimensionlessStateVector& _v) const
    {
        r.AsDimensionlessVector(_v.r);
        v.AsDimensionlessVector(_v.dr);
    }

    FSDimensionlessStateVector AsDimensionlessStateVector() const
    {
        FSDimensionlessStateVector vector;
        AsDimensionlessVectors(vector);
        return vector;
    }

    FString ToString() const;
};


static inline bool operator==(const FSStateVector& lhs, const FSStateVector& rhs)
{
    return (lhs.r == rhs.r) && (lhs.v == rhs.v);
}

static inline bool operator!=(const FSStateVector& lhs, const FSStateVector& rhs)
{
    return !(lhs == rhs);
}


static inline FSStateVector operator+(const FSStateVector& lhs, const FSStateVector& rhs)
{
    return FSStateVector(lhs.r + rhs.r, lhs.v + rhs.v);
}

static inline FSStateVector operator-(const FSStateVector& rhs)
{
    return FSStateVector(-rhs.r, -rhs.v);
}

static inline FSStateVector operator-(const FSStateVector& lhs, const FSStateVector& rhs)
{
    return FSStateVector(lhs.r - rhs.r, lhs.v - rhs.v);
}

static inline FSStateVector& operator+=(FSStateVector& lhs, const FSStateVector& rhs) {

    lhs.r += rhs.r;
    lhs.v += rhs.v;
    return lhs;
}

static inline FSStateVector& operator-=(FSStateVector& lhs, const FSStateVector& rhs) {

    lhs.r -= rhs.r;
    lhs.v -= rhs.v;
    return lhs;
}


USTRUCT(BlueprintType, Meta = (ToolTip = "Cylindrical coordinates (R, LONG, Z)"))
struct SPICE_API FSCylindricalVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistance r;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngle lon;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistance z;

    FSCylindricalVector()
    {
        r = FSDistance();
        lon = FSAngle();
        z = FSDistance();
    }

    FSCylindricalVector(const double(&v)[3])
    {
        r = FSDistance(v[0]);
        lon = FSAngle(v[1]);
        z = FSDistance(v[2]);
    }

    FSCylindricalVector(const double(&state)[6])
    {
        r = FSDistance(state[0]);
        lon = FSAngle(state[1]);
        z = FSDistance(state[2]);
    }

    void CopyTo(double(&v)[3]) const
    {
        v[0] = r.AsSpiceDouble();
        v[1] = lon.AsSpiceDouble();
        v[2] = z.AsSpiceDouble();
    }

    void CopyTo(double(&state)[6]) const
    {
        state[0] = r.AsSpiceDouble();
        state[1] = lon.AsSpiceDouble();
        state[2] = z.AsSpiceDouble();
    }

    FSCylindricalVector(const FSDimensionlessVector& v)
    {
        r = FSDistance(v.x);
        lon = FSAngle(v.y);
        z = FSDistance(v.z);
    }

    FSCylindricalVector(const FSDistance& _r, const FSAngle& _lon, const FSDistance& _z)
    {
        r = FSDistance(_r);
        lon = FSAngle(_lon);
        z = FSDistance(_z);
    }

    void AsDimensionlessVector(FSDimensionlessVector& v) const
    {
        v.x = r.AsSpiceDouble();
        v.y = lon.AsSpiceDouble();
        v.z = z.AsSpiceDouble();
    }

    FString ToString() const;
};


USTRUCT(BlueprintType, Meta = (ToolTip = "Cylindrical coordinates (DR, DLONG, DZ)"))
struct SPICE_API FSCylindricalVectorRates
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSSpeed dr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularRate dlon;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSSpeed dz;

    FSCylindricalVectorRates()
    {
        dr = FSSpeed();
        dlon = FSAngularRate();
        dz = FSSpeed();
    }

    FSCylindricalVectorRates(const double(&v)[3])
    {
        dr = FSSpeed(v[0]);
        dlon = FSAngularRate(v[1]);
        dz = FSSpeed(v[2]);
    }

    FSCylindricalVectorRates(const double(&state)[6])
    {
        dr = FSSpeed(state[3]);
        dlon = FSAngularRate(state[4]);
        dz = FSSpeed(state[5]);
    }

    void CopyTo(double(&v)[3]) const
    {
        v[0] = dr.AsSpiceDouble();
        v[1] = dlon.AsSpiceDouble();
        v[2] = dz.AsSpiceDouble();
    }

    void CopyTo(double(&state)[6]) const
    {
        state[3] = dr.AsSpiceDouble();
        state[4] = dlon.AsSpiceDouble();
        state[5] = dz.AsSpiceDouble();
    }

    FSCylindricalVectorRates(const FSDimensionlessVector& v)
    {
        dr = FSSpeed(v.x);
        dlon = FSAngularRate(v.y);
        dz = FSSpeed(v.z);
    }

    void AsDimensionlessVector(FSDimensionlessVector& v) const
    {
        v.x = dr.AsSpiceDouble();
        v.y = dlon.AsSpiceDouble();
        v.z = dz.AsSpiceDouble();
    }

    FSDimensionlessVector AsDimensionlessVector() const
    {
        FSDimensionlessVector v;
        AsDimensionlessVector(v);
        return v;
    }

    FString ToString() const;
};


USTRUCT(BlueprintType, Meta = (ToolTip = "Cylindrical coordinates (R, LONG, Z, DR, DLONG, DZ)"))
struct SPICE_API FSCylindricalStateVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSCylindricalVector r;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSCylindricalVectorRates dr;

    FSCylindricalStateVector()
    {
        r = FSCylindricalVector();
        dr = FSCylindricalVectorRates();
    }

    FSCylindricalStateVector(const double(&state)[6])
    {
        r = FSCylindricalVector(state);
        dr = FSCylindricalVectorRates(state);
    }

    void CopyTo(double(&state)[6]) const
    {
        r.CopyTo(state);
        dr.CopyTo(state);
    }

    FSCylindricalStateVector(const FSDimensionlessStateVector& v)
    {
        r = FSCylindricalVector(v.r);
        dr = FSCylindricalVectorRates(v.dr);
    }

    void AsDimensionlessVectors(FSDimensionlessStateVector& v) const
    {
        r.AsDimensionlessVector(v.r);
        dr.AsDimensionlessVector(v.dr);
    }

    FString ToString() const;
};


USTRUCT(BlueprintType, Meta = (ToolTip = "Latitudinal coordinates (R, LONGLAT"))
struct SPICE_API FSLatitudinalVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistance r;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSLonLat lonlat;

    FSLatitudinalVector()
    {
        r = FSDistance();
        lonlat = FSLonLat();
    }

    FSLatitudinalVector(const double(&v)[3])
    {
        r = FSDistance(v[0]);
        lonlat = FSLonLat(v[1], v[2]);
    }

    FSLatitudinalVector(const double(&state)[6])
    {
        r = FSDistance(state[0]);
        lonlat = FSLonLat(state[1], state[2]);
    }

    void CopyTo(double(&v)[3]) const
    {
        v[0] = r.AsSpiceDouble();
        lonlat.CopyTo(v[1], v[2]);
    }

    void CopyTo(double(&state)[6]) const
    {
        state[0] = r.AsSpiceDouble();
        lonlat.CopyTo(state[1], state[2]);
    }

    FSLatitudinalVector(const FSDistance& _r, const FSLonLat& _lonlat)
    {
        r = FSDistance(_r);
        lonlat = FSLonLat(_lonlat);
    }

    FSLatitudinalVector(const FSDimensionlessVector& v)
    {
        r = FSDistance(v.x);
        lonlat = FSLonLat(v.y, v.z);
    }

    void AsDimensionlessVector(FSDimensionlessVector& v) const
    {
        v.x = r.AsSpiceDouble();
        lonlat.CopyTo(v.y, v.z);
    }

    FString ToString() const;
};


USTRUCT(BlueprintType, Meta = (ToolTip = "Latitudinal coordinates (DR, DLONG, DLAT)"))
struct SPICE_API FSLatitudinalVectorRates
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSSpeed dr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularRate dlon;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularRate dlat;

    FSLatitudinalVectorRates()
    {
        dr = FSSpeed();
        dlon = FSAngularRate();
        dlat = FSAngularRate();
    }

    FSLatitudinalVectorRates(const double(&v)[3])
    {
        dr = FSSpeed(v[0]);
        dlon = FSAngularRate(v[1]);
        dlat = FSAngularRate(v[2]);
    }

    FSLatitudinalVectorRates(const double(&state)[6])
    {
        dr = FSSpeed(state[3]);
        dlon = FSAngularRate(state[4]);
        dlat = FSAngularRate(state[5]);
    }

    void CopyTo(double(&v)[3]) const
    {
        v[0] = dr.AsSpiceDouble();
        v[1] = dlon.AsSpiceDouble();
        v[2] = dlat.AsSpiceDouble();
    }

    void CopyTo(double(&state)[6]) const
    {
        state[3] = dr.AsSpiceDouble();
        state[4] = dlon.AsSpiceDouble();
        state[5] = dlat.AsSpiceDouble();
    }

    FSLatitudinalVectorRates(const FSDimensionlessVector& v)
    {
        dr = FSSpeed(v.x);
        dlon = FSAngularRate(v.y);
        dlat = FSAngularRate(v.z);
    }

    void AsDimensionlessVector(FSDimensionlessVector& v) const
    {
        v.x = dr.AsSpiceDouble();
        v.y = dlon.AsSpiceDouble();
        v.z = dlat.AsSpiceDouble();
    }

    FString ToString() const;
};


USTRUCT(BlueprintType, Meta = (ToolTip = "Latitudinal coordinates (R, LONGLAT, DR, DLONG, DLAT)"))
struct SPICE_API FSLatitudinalStateVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSLatitudinalVector r;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSLatitudinalVectorRates dr;

    FSLatitudinalStateVector()
    {
        r = FSLatitudinalVector();
        dr = FSLatitudinalVectorRates();
    }

    FSLatitudinalStateVector(const double(&state)[6])
    {
        r = FSLatitudinalVector(state);
        dr = FSLatitudinalVectorRates(state);
    }

    void CopyTo(double(&state)[6]) const
    {
        r.CopyTo(state);
        dr.CopyTo(state);
    }

    FSLatitudinalStateVector(const FSDimensionlessStateVector& v)
    {
        r = FSLatitudinalVector(v.r);
        dr = FSLatitudinalVectorRates(v.dr);
    }

    void AsDimensionlessVectors(FSDimensionlessStateVector& v) const
    {
        r.AsDimensionlessVector(v.r);
        dr.AsDimensionlessVector(v.dr);
    }

    FString ToString() const;
};


USTRUCT(BlueprintType, Meta = (ToolTip = "Spherical coordinates (R, COLAT, LONG)"))
struct SPICE_API FSSphericalVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistance r;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngle colat;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngle lon;

    FSSphericalVector()
    {
        r = FSDistance();
        colat = FSAngle();
        lon = FSAngle();
    }

    FSSphericalVector(const double(&v)[3])
    {
        r = FSDistance(v[0]);
        colat = FSAngle(v[1]);
        lon = FSAngle(v[2]);
    }

    FSSphericalVector(const double(&state)[6])
    {
        r = FSDistance(state[0]);
        colat = FSAngle(state[1]);
        lon = FSAngle(state[2]);
    }

    void CopyTo(double(&v)[3]) const
    {
        v[0] = r.AsSpiceDouble();
        v[1] = colat.AsSpiceDouble();
        v[2] = lon.AsSpiceDouble();
    }

    void CopyTo(double(&state)[6]) const
    {
        state[0] = r.AsSpiceDouble();
        state[1] = colat.AsSpiceDouble();
        state[2] = lon.AsSpiceDouble();
    }

    FSSphericalVector(const FSDimensionlessVector& v)
    {
        r = FSDistance(v.x);
        colat = FSAngle(v.y);
        lon = FSAngle(v.z);
    }

    FSSphericalVector(const FSDistance& _r, const FSAngle& _colat, const FSAngle& _lon)
    {
        r = FSDistance(_r);
        colat = FSAngle(_colat);
        lon = FSAngle(_lon);
    }

    void AsDimensionlessVector(FSDimensionlessVector& v) const
    {
        v.x = r.AsSpiceDouble();
        v.y = colat.AsSpiceDouble();
        v.z = lon.AsSpiceDouble();
    }

    FString ToString() const;
};


USTRUCT(BlueprintType, Meta = (ToolTip = "Spherical coordinates (DR, DCOLAT, DLONG)"))
struct SPICE_API FSSphericalVectorRates
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSSpeed dr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularRate dcolat;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularRate dlon;

    FSSphericalVectorRates()
    {
        dr = FSSpeed();
        dcolat = FSAngularRate();
        dlon = FSAngularRate();
    }

    FSSphericalVectorRates(const double(&v)[3])
    {
        dr = FSSpeed(v[0]);
        dcolat = FSAngularRate(v[1]);
        dlon = FSAngularRate(v[2]);
    }

    FSSphericalVectorRates(const double(&state)[6])
    {
        dr = FSSpeed(state[3]);
        dcolat = FSAngularRate(state[4]);
        dlon = FSAngularRate(state[5]);
    }

    void CopyTo(double(&v)[3]) const
    {
        v[0] = dr.AsSpiceDouble();
        v[1] = dcolat.AsSpiceDouble();
        v[2] = dlon.AsSpiceDouble();
    }

    void CopyTo(double(&state)[6]) const
    {
        state[3] = dr.AsSpiceDouble();
        state[4] = dcolat.AsSpiceDouble();
        state[5] = dlon.AsSpiceDouble();
    }

    FSSphericalVectorRates(const FSDimensionlessVector& v)
    {
        dr = FSSpeed(v.x);
        dcolat = FSAngularRate(v.y);
        dlon = FSAngularRate(v.z);
    }

    void AsDimensionlessVector(FSDimensionlessVector& v) const
    {
        v.x = dr.AsSpiceDouble();
        v.y = dcolat.AsSpiceDouble();
        v.z = dlon.AsSpiceDouble();
    }

    FString ToString() const;
};

USTRUCT(BlueprintType, Meta = (ToolTip = "Spherical coordinates (R, COLAT, LONG, DR, DCOLAT, DLONG)"))
struct SPICE_API FSSphericalStateVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSSphericalVector r;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSSphericalVectorRates dr;

    FSSphericalStateVector()
    {
        r = FSSphericalVector();
        dr = FSSphericalVectorRates();
    }

    FSSphericalStateVector(const double(&state)[6])
    {
        r = FSSphericalVector(state);
        dr = FSSphericalVectorRates(state);
    }

    void CopyTo(double(&state)[6]) const
    {
        r.CopyTo(state);
        dr.CopyTo(state);
    }

    FSSphericalStateVector(const FSDimensionlessStateVector& v)
    {
        r = FSSphericalVector(v.r);
        dr = FSSphericalVectorRates(v.dr);
    }

    void AsDimensionlessVectors(FSDimensionlessStateVector& v) const
    {
        r.AsDimensionlessVector(v.r);
        dr.AsDimensionlessVector(v.dr);
    }

    FString ToString() const;
};


USTRUCT(BlueprintType, Meta = (ToolTip = "Geodetic coordinates (LONG, LAT, ALT)"))
struct SPICE_API FSGeodeticVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSLonLat lonlat;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistance alt;

    FSGeodeticVector()
    {
        lonlat = FSLonLat();
        alt = FSDistance();
    }

    FSGeodeticVector(const double(&v)[3])
    {
        lonlat = FSLonLat(v[0], v[1]);
        alt = FSDistance(v[2]);
    }

    FSGeodeticVector(const double(&state)[6])
    {
        lonlat = FSLonLat(state[0], state[1]);
        alt = FSDistance(state[2]);
    }

    void CopyTo(double(&v)[3]) const
    {
        lonlat.CopyTo(v[0], v[1]);
        v[2] = alt.AsSpiceDouble();
    }

    void CopyTo(double(&state)[6]) const
    {
        lonlat.CopyTo(state[0], state[1]);
        state[2] = alt.AsSpiceDouble();
    }

    FSGeodeticVector(const FSDimensionlessVector& v)
    {
        lonlat = FSLonLat(v.x, v.y);
        alt = FSDistance(v.z);
    }

    FSGeodeticVector(const FSLonLat& _lonlat, const FSDistance& _alt)
    {
        lonlat = FSLonLat(_lonlat);
        alt = FSDistance(_alt);
    }

    void AsDimensionlessVector(FSDimensionlessVector& v) const
    {
        lonlat.CopyTo(v.x, v.y);
        v.z = alt.AsSpiceDouble();
    }

    FString ToString() const;
};


USTRUCT(BlueprintType, Meta = (ToolTip = "Geodetic coordinates (DLONG, DLAT, DALT"))
struct SPICE_API FSGeodeticVectorRates
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularRate dlon;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularRate dlat;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSSpeed dalt;

    FSGeodeticVectorRates()
    {
        dlon = FSAngularRate();
        dlat = FSAngularRate();
        dalt = FSSpeed();
    }

    FSGeodeticVectorRates(const double(&v)[3])
    {
        dlon = FSAngularRate(v[0]);
        dlat = FSAngularRate(v[1]);
        dalt = FSSpeed(v[2]);
    }

    FSGeodeticVectorRates(const double(&state)[6])
    {
        dlon = FSAngularRate(state[3]);
        dlat = FSAngularRate(state[4]);
        dalt = FSSpeed(state[5]);
    }

    void CopyTo(double(&v)[3]) const
    {
        v[0] = dlon.AsSpiceDouble();
        v[1] = dlat.AsSpiceDouble();
        v[2] = dalt.AsSpiceDouble();
    }

    void CopyTo(double(&state)[6]) const
    {
        state[3] = dlon.AsSpiceDouble();
        state[4] = dlat.AsSpiceDouble();
        state[5] = dalt.AsSpiceDouble();
    }

    FSGeodeticVectorRates(const FSDimensionlessVector& v)
    {
        dlon = FSAngularRate(v.x);
        dlat = FSAngularRate(v.y);
        dalt = FSSpeed(v.z);
    }

    void AsDimensionlessVector(FSDimensionlessVector& v) const
    {
        v.x = dlon.AsSpiceDouble();
        v.y = dlat.AsSpiceDouble();
        v.z = dalt.AsSpiceDouble();
    }

    FString ToString() const;
};

USTRUCT(BlueprintType, Meta = (ToolTip = "Geodetic coordinates (LONG, LAT, ALT, DLONG, DLAT, DALT"))
struct SPICE_API FSGeodeticStateVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSGeodeticVector r;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSGeodeticVectorRates dr;

    FSGeodeticStateVector()
    {
        r = FSGeodeticVector();
        dr = FSGeodeticVectorRates();
    }

    FSGeodeticStateVector(const double(&state)[6])
    {
        r = FSGeodeticVector(state);
        dr = FSGeodeticVectorRates(state);
    }

    void CopyTo(double(&state)[6]) const
    {
        r.CopyTo(state);
        dr.CopyTo(state);
    }

    FSGeodeticStateVector(const FSDimensionlessStateVector& v)
    {
        r = FSGeodeticVector(v.r);
        dr = FSGeodeticVectorRates(v.dr);
    }

    void AsDimensionlessVectors(FSDimensionlessStateVector& v) const
    {
        r.AsDimensionlessVector(v.r);
        dr.AsDimensionlessVector(v.dr);
    }

    FString ToString() const;
};


USTRUCT(BlueprintType, Meta = (ToolTip = "Planetographic coordinates (LONG, LAT, ALT)"))
struct SPICE_API FSPlanetographicVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSLonLat lonlat;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistance alt;

    FSPlanetographicVector()
    {
        lonlat = FSLonLat();
        alt = FSDistance();
    }

    FSPlanetographicVector(const double(&v)[3])
    {
        lonlat = FSLonLat(v[0], v[1]);
        alt = FSDistance(v[2]);
    }

    FSPlanetographicVector(const double(&state)[6])
    {
        lonlat = FSLonLat(state[0], state[1]);
        alt = FSDistance(state[2]);
    }

    void CopyTo(double(&v)[3]) const
    {
        lonlat.CopyTo(v[0], v[1]);
        v[2] = alt.AsSpiceDouble();
    }

    void CopyTo(double(&state)[6]) const
    {
        lonlat.CopyTo(state[0], state[1]);
        state[2] = alt.AsSpiceDouble();
    }

    FSPlanetographicVector(const FSDimensionlessVector& v)
    {
        lonlat = FSLonLat(v.x, v.y);
        alt = FSDistance(v.z);
    }

    FSPlanetographicVector(const FSLonLat& _lonlat, const FSDistance& _alt)
    {
        lonlat = FSLonLat(_lonlat);
        alt = FSDistance(_alt);
    }

    void AsDimensionlessVector(FSDimensionlessVector& v) const
    {
        lonlat.CopyTo(v.x, v.y);
        v.z = alt.AsSpiceDouble();
    }

    FString ToString() const;
};


USTRUCT(BlueprintType, Meta = (ToolTip = "Planetographic coordinates (DLONG, DLAT, DALT)"))
struct SPICE_API FSPlanetographicVectorRates
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularRate dlon;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularRate dlat;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSSpeed dalt;

    FSPlanetographicVectorRates()
    {
        dlon = FSAngularRate();
        dlat = FSAngularRate();
        dalt = FSSpeed();
    }

    FSPlanetographicVectorRates(const double(&v)[3])
    {
        dlon = FSAngularRate(v[0]);
        dlat = FSAngularRate(v[1]);
        dalt = FSSpeed(v[2]);
    }

    FSPlanetographicVectorRates(const double(&state)[6])
    {
        dlon = FSAngularRate(state[3]);
        dlat = FSAngularRate(state[4]);
        dalt = FSSpeed(state[5]);
    }

    void CopyTo(double(&v)[3]) const
    {
        v[0] = dlon.AsSpiceDouble();
        v[1] = dlat.AsSpiceDouble();
        v[2] = dalt.AsSpiceDouble();
    }

    void CopyTo(double(&state)[6]) const
    {
        state[3] = dlon.AsSpiceDouble();
        state[4] = dlat.AsSpiceDouble();
        state[5] = dalt.AsSpiceDouble();
    }

    FSPlanetographicVectorRates(const FSDimensionlessVector& v)
    {
        dlon = FSAngularRate(v.x);
        dlat = FSAngularRate(v.y);
        dalt = FSSpeed(v.z);
    }

    void AsDimensionlessVector(FSDimensionlessVector& v) const
    {
        v.x = dlon.AsSpiceDouble();
        v.y = dlat.AsSpiceDouble();
        v.z = dalt.AsSpiceDouble();
    }

    FString ToString() const;
};

USTRUCT(BlueprintType, Meta = (ToolTip = "Planetographic coordinates (LONG, LAT, ALT, DLONG, DLAT, DALT)"))
struct SPICE_API FSPlanetographicStateVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSPlanetographicVector r;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSPlanetographicVectorRates dr;

    FSPlanetographicStateVector()
    {
        r = FSPlanetographicVector();
        dr = FSPlanetographicVectorRates();
    }

    FSPlanetographicStateVector(const double(&state)[6])
    {
        r = FSPlanetographicVector(state);
        dr = FSPlanetographicVectorRates(state);
    }

    void CopyTo(double(&state)[6]) const
    {
        r.CopyTo(state);
        dr.CopyTo(state);
    }

    FSPlanetographicStateVector(const FSDimensionlessStateVector& v)
    {
        r = FSPlanetographicVector(v.r);
        dr = FSPlanetographicVectorRates(v.dr);
    }

    void AsDimensionlessVectors(FSDimensionlessStateVector& v) const
    {
        r.AsDimensionlessVector(v.r);
        dr.AsDimensionlessVector(v.dr);
    }

    FString ToString() const;
};


USTRUCT(BlueprintType, Category = "MaxQ|StateTransform")
struct SPICE_API FSStateTransform
{
    GENERATED_BODY()

    TArray<FSDimensionlessStateVector> m;

    FSStateTransform()
    {
        m.Init(FSDimensionlessStateVector(), 6);
        m[0].r.x = m[1].r.y = m[2].r.z = m[3].dr.x = m[4].dr.y = m[5].dr.z = 1.;
    }

    FSStateTransform(const double(&_m)[6][6])
    {
        m = {
            FSDimensionlessStateVector(_m[0]),
            FSDimensionlessStateVector(_m[1]),
            FSDimensionlessStateVector(_m[2]),
            FSDimensionlessStateVector(_m[3]),
            FSDimensionlessStateVector(_m[4]),
            FSDimensionlessStateVector(_m[5])
        };
    }

    void CopyTo(double (&_m)[6][6]) const
    {
        m[0].CopyTo(_m[0]);
        m[1].CopyTo(_m[1]);
        m[2].CopyTo(_m[2]);
        m[3].CopyTo(_m[3]);
        m[4].CopyTo(_m[4]);
        m[5].CopyTo(_m[5]);
    }

    static const FSStateTransform Identity;
    FString ToString() const;
};




USTRUCT(BlueprintType, Category = "MaxQ|RotationMatrix",
    Meta = (
        ShortToolTip = "C-Matrix",
        ToolTip = "3x3 Rotation Matrix (AKA C-Matrix, or Camera-Matrix)"
        ))
struct SPICE_API FSRotationMatrix
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ")
    TArray<FSDimensionlessVector> m;

    FSRotationMatrix()
    {
        m = {
            FSDimensionlessVector::X_Axis,
            FSDimensionlessVector::Y_Axis,
            FSDimensionlessVector::Z_Axis
        };
    }

    FSRotationMatrix(const double(&_m)[3][3])
    {
        m = { 
            FSDimensionlessVector(_m[0]),
            FSDimensionlessVector(_m[1]),
            FSDimensionlessVector(_m[2])
        };
    }

    FSRotationMatrix(
        const FSDimensionlessVector& x,
        const FSDimensionlessVector& y,
        const FSDimensionlessVector& z
    )
    {
        m = { x, y, z };
    }


    void CopyTo(double(&_m)[3][3]) const
    {
        m[0].CopyTo(_m[0]);
        m[1].CopyTo(_m[1]);
        m[2].CopyTo(_m[2]);
    }

    static const FSRotationMatrix Identity;
    FString ToString() const;
};


USTRUCT(BlueprintType, Category = "MaxQ|Quaternion")
struct SPICE_API FSQuaternion
{
    GENERATED_BODY()

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/q2m_c.html
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double w;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double x;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double y;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double z;

    FSQuaternion(double _w, double _x, double _y, double _z)
    {
        w = _w;
        x = _x;
        y = _y;
        z = _z;
    }

    inline void QSPICE(double& _w, double& _x, double& _y, double& _z) const
    {
        _w = w;
        _x = x;
        _y = y;
        _z = z;
    }
    inline void QENG(double& _w, double& _x, double& _y, double& _z) const
    {
        _w = w;
        _x = -x;
        _y = -y;
        _z = -z;
    }
    inline static FSQuaternion SPICE(double _w, double _x, double _y, double _z)
    {
        return FSQuaternion(_w, _x, _y, _z);
    }
    inline static FSQuaternion ENG(double _w, double _x, double _y, double _z)
    {
        return FSQuaternion(_w, -_x, -_y, -_z);
    }

    FSQuaternion()
    {
        w = 1.;
        x = y = z = 0.;
    }

    FSQuaternion(const double(&_q)[4])
    {
        w = _q[0];
        x = _q[1];
        y = _q[2];
        z = _q[3];
    }

    void CopyTo(double(&_q)[4]) const
    {
        _q[0] = w;
        _q[1] = x;
        _q[2] = y;
        _q[3] = z;
    }

    static const FSQuaternion Identity;
    FString ToString() const;

    // IMPORTANT!:
    // Swizzles between UE/SPICE (LHS and RHS coordinate systems)
    // You must swizzle positional data (quaternions, vectors, etc) when
    // exchanging between SPICE and Unreal Engine scenegraph coordinates.
    FQuat Swizzle() const;
    static FSQuaternion Swizzle(const FQuat& UnrealQuat);
};



USTRUCT(BlueprintType, Category = "MaxQ|QuaternionDerivative")
struct SPICE_API FSQuaternionDerivative
{
    GENERATED_BODY()

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/qdq2av_c.html
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double dw;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double dx;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double dy;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double dz;

    FSQuaternionDerivative(double _dw, double _dx, double _dy, double _dz)
    {
        dw = _dw;
        dx = _dx;
        dy = _dy;
        dz = _dz;
    }

    inline void QSPICE(double& _dw, double& _dx, double& _dy, double& _dz) const
    {
        _dw = dw;
        _dx = dx;
        _dy = dy;
        _dz = dz;
    }
    inline void QENG(double& _dw, double& _dx, double& _dy, double& _dz) const
    {
        _dw = dw;
        _dx = -dx;
        _dy = -dy;
        _dz = -dz;
    }
    inline static FSQuaternionDerivative SPICE(double _dw, double _dx, double _dy, double _dz)
    {
        return FSQuaternionDerivative(_dw, _dx, _dy, _dz);
    }
    inline static FSQuaternionDerivative ENG(double _dw, double _dx, double _dy, double _dz)
    {
        return FSQuaternionDerivative(_dw, -_dx, -_dy, -_dz);
    }

    FSQuaternionDerivative()
    {
        dw = 0.;
        dx = dy = dz = 0.;
    }

    FSQuaternionDerivative(const double(&_dq)[4])
    {
        dw = _dq[0];
        dx = _dq[1];
        dy = _dq[2];
        dz = _dq[3];
    }

    void CopyTo(double(&_dq)[4]) const
    {
        _dq[0] = dw;
        _dq[1] = dx;
        _dq[2] = dy;
        _dq[3] = dz;
    }

    static const FSQuaternionDerivative Zero;
    FString ToString() const;

    // IMPORTANT!:
    // Swizzles between UE/SPICE (LHS and RHS coordinate systems)
    // You must swizzle positional data (quaternions, vectors, etc) when
    // exchanging between SPICE and Unreal Engine scenegraph coordinates.
    FVector4 Swizzle() const;
    static FSQuaternionDerivative Swizzle(const FVector4& UnrealQuat);
};


SPICE_API FSRotationMatrix operator*(const FSRotationMatrix& lhs, const FSRotationMatrix& rhs);
SPICE_API FSDimensionlessVector operator*(const FSRotationMatrix& lhs, const FSDimensionlessVector& rhs);
SPICE_API FSDistanceVector operator*(const FSRotationMatrix& lhs, const FSDistanceVector& rhs);
SPICE_API FSVelocityVector operator*(const FSRotationMatrix& lhs, const FSVelocityVector& rhs);
SPICE_API FSQuaternion operator*(const FSQuaternion& lhs, const FSQuaternion& rhs);

USTRUCT(BlueprintType)
struct SPICE_API FSEllipse
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistanceVector center;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistanceVector v_major;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistanceVector v_minor;

public:

    FSEllipse()
    {
        center = FSDistanceVector::Zero;
        v_major = FSDistanceVector::Zero;
        v_minor = FSDistanceVector::Zero;
    }

    FSEllipse(
        const FSEllipse& other
    )
    {
        center = other.center;
        v_major = other.v_major;
        v_minor = other.v_minor;
    }

    FSEllipse(
        const double(&_center)[3],
        const double(&_v_major)[3],
        const double(&_v_minor)[3]
    )
    {
        center = FSDistanceVector(_center);
        v_major = FSDistanceVector(_v_major);
        v_minor = FSDistanceVector(_v_minor);
    }

    FString ToString() const;
};


USTRUCT(BlueprintType)
struct SPICE_API FSPlane
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDimensionlessVector normal;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistance constant;

public:

    FSPlane()
    {
        normal = FSDimensionlessVector::Zero;
        constant = FSDistance::Zero;
    }

    FSPlane(
        const FSDimensionlessVector& _normal,
        const FSDistance& _constant
    )
    {
        normal = _normal;
        constant = _constant;
    }

    FSPlane(
        const FSPlane& other
    )
    {
        normal = other.normal;
        constant = other.constant;
    }

    FSPlane(
        const double(&_normal)[3],
        double _constant
    )
    {
        normal = FSDimensionlessVector(_normal);
        constant = FSDistance(_constant);
    }

    FString ToString() const;
};

USTRUCT(BlueprintType, Category = "MaxQ|EulerAngularTransform")
struct SPICE_API FSEulerAngularTransform
{
    GENERATED_BODY()

        // Must be a TArray of a serializable type to be serialized to/from network or disk,
        // as C++ native arrays are not serializable.
        TArray<FSDimensionlessStateVector> m;

    FSEulerAngularTransform()
    {
        m.Init(FSDimensionlessStateVector(), 6);
        m[0].r.x = m[1].r.y = m[2].r.z = m[3].dr.x = m[4].dr.y = m[5].dr.z = 1.;
    }

    FSEulerAngularTransform(const double(&_m)[6][6])
    {
        m = {
            FSDimensionlessStateVector(_m[0]),
            FSDimensionlessStateVector(_m[1]),
            FSDimensionlessStateVector(_m[2]),
            FSDimensionlessStateVector(_m[3]),
            FSDimensionlessStateVector(_m[4]),
            FSDimensionlessStateVector(_m[5])
        };
    }

    void CopyTo(double(&_m)[6][6]) const
    {
        m[0].CopyTo(_m[0]);
        m[1].CopyTo(_m[1]);
        m[2].CopyTo(_m[2]);
        m[3].CopyTo(_m[3]);
        m[4].CopyTo(_m[4]);
        m[5].CopyTo(_m[5]);
    }

    static const FSEulerAngularTransform Identity;
    FString ToString() const;
};



USTRUCT(BlueprintType)
struct SPICE_API FSConicElements
{
    GENERATED_BODY()

    // q
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistance PerifocalDistance;
    // e
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double Eccentricity;
    // i
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngle Inclination;
    // node
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngle LongitudeOfAscendingNode;
    // peri
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngle ArgumentOfPeriapse;
    // M
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngle MeanAnomalyAtEpoch;
    // epoch
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSEphemerisTime Epoch;
    // GM
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSMassConstant GravitationalParameter;

    FSConicElements()
    {
        PerifocalDistance = FSDistance();
        Eccentricity = 0.;
        Inclination = FSAngle();
        LongitudeOfAscendingNode = FSAngle();
        ArgumentOfPeriapse = FSAngle();
        MeanAnomalyAtEpoch = FSAngle();
        Epoch = FSEphemerisTime();
        GravitationalParameter = FSMassConstant();
    }

    FSConicElements(const FSConicElements& other)
    {
        PerifocalDistance = other.PerifocalDistance;
        Eccentricity = other.Eccentricity;
        Inclination = other.Inclination;
        LongitudeOfAscendingNode = other.LongitudeOfAscendingNode;
        ArgumentOfPeriapse = other.ArgumentOfPeriapse;
        MeanAnomalyAtEpoch = other.MeanAnomalyAtEpoch;
        Epoch = other.Epoch;
        GravitationalParameter = other.GravitationalParameter;
    }


    FSConicElements(double(&elts)[8])
    {
        PerifocalDistance = FSDistance(elts[0]);
        Eccentricity = elts[1];
        Inclination = FSAngle(elts[2]);
        LongitudeOfAscendingNode = FSAngle(elts[3]);
        ArgumentOfPeriapse = FSAngle(elts[4]);
        MeanAnomalyAtEpoch = FSAngle(elts[5]);
        Epoch = FSEphemerisTime(elts[6]);
        GravitationalParameter = FSMassConstant(elts[7]);
    }

    FSConicElements(double(&elts)[20])
    {
        PerifocalDistance = FSDistance(elts[0]);
        Eccentricity = elts[1];
        Inclination = FSAngle(elts[2]);
        LongitudeOfAscendingNode = FSAngle(elts[3]);
        ArgumentOfPeriapse = FSAngle(elts[4]);
        MeanAnomalyAtEpoch = FSAngle(elts[5]);
        Epoch = FSEphemerisTime(elts[6]);
        GravitationalParameter = FSMassConstant(elts[7]);
    }

    void CopyTo(double(&elts)[8]) const
    {
        elts[0] = PerifocalDistance.km;
        elts[1] = Eccentricity;
        elts[2] = Inclination.AsSpiceDouble();
        elts[3] = LongitudeOfAscendingNode.AsSpiceDouble();
        elts[4] = ArgumentOfPeriapse.AsSpiceDouble();
        elts[5] = MeanAnomalyAtEpoch.AsSpiceDouble();
        elts[6] = Epoch.seconds;
        elts[7] = GravitationalParameter.GM;
    }

    void CopyTo(double(&elts)[20]) const
    {
        elts[0] = PerifocalDistance.km;
        elts[1] = Eccentricity;
        elts[2] = Inclination.AsSpiceDouble();
        elts[3] = LongitudeOfAscendingNode.AsSpiceDouble();
        elts[4] = ArgumentOfPeriapse.AsSpiceDouble();
        elts[5] = MeanAnomalyAtEpoch.AsSpiceDouble();
        elts[6] = Epoch.seconds;
        elts[7] = GravitationalParameter.GM;
    }

    FSConicElements& operator=(const FSConicElements& other)
    {
        if (this != &other)
        {
            PerifocalDistance = other.PerifocalDistance;
            Eccentricity = other.Eccentricity;
            Inclination = other.Inclination;
            LongitudeOfAscendingNode = other.LongitudeOfAscendingNode;
            ArgumentOfPeriapse = other.ArgumentOfPeriapse;
            MeanAnomalyAtEpoch = other.MeanAnomalyAtEpoch;
            Epoch = other.Epoch;
            GravitationalParameter = other.GravitationalParameter;
        }

        return *this;
    }

    FString ToString() const;
};

USTRUCT(BlueprintType)
struct SPICE_API FSEquinoctialElements
{
    GENERATED_BODY()

    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "MaxQ",
        Meta = (
            ShortToolTip = "semi-major axis"
            ))
    FSDistance a;
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "MaxQ",
        Meta = (
            ShortToolTip = "e*sin(argp+node)"
            ))
    double h;
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "MaxQ",
        Meta = (
            ShortToolTip = "e*cos(argp+node)"
            ))
    double k;
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "MaxQ",
        Meta = (
            ShortToolTip = "mean0+argp+node"
            ))
    FSAngle MeanLongitude;
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "MaxQ",
        Meta = (
            ShortToolTip = "(tan(inc/2)*sin(node))at the specified epoch"
            ))
    double p;
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "MaxQ",
        Meta = (
            ShortToolTip = "(tan(inc/2)*cos(node))at the specified epoch"
            ))
    double q;
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "MaxQ",
        Meta = (
            ShortToolTip = "dargp/dt + dnode/dt (rate is assumed to hold for all time)"
            ))
    FSAngularRate RateOfLongitudeOfPeriapse;
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "MaxQ",
        Meta = (
            ShortToolTip = "dm/dt + dargp/dt + dnode/dt (rate is assumed to hold for all time)"
            ))
    FSAngularRate MeanLongitudeDerivative;
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Category = "MaxQ",
        Meta = (
            ShortToolTip = "dnode/dt"
            ))
    FSAngularRate RateOfLongitudeOfAscendingNode;

    FSEquinoctialElements()
    {
        a = FSDistance();
        h = 0.;
        k = 0.;
        MeanLongitude = FSAngle();
        p = 0.;
        q = 0.;
        RateOfLongitudeOfPeriapse = FSAngularRate();
        MeanLongitudeDerivative = FSAngularRate();
        RateOfLongitudeOfAscendingNode = FSAngularRate();
    }


    FSEquinoctialElements(double(&elts)[9])
    {
        a = FSDistance(elts[0]);
        h = elts[1];
        k = elts[2];
        MeanLongitude = FSAngle(elts[3]);
        p = elts[4];
        q = elts[5];
        RateOfLongitudeOfPeriapse = FSAngularRate(elts[6]);
        MeanLongitudeDerivative = FSAngularRate(elts[7]);
        RateOfLongitudeOfAscendingNode = FSAngularRate(elts[8]);
    }

    void CopyTo(double(&elts)[9]) const
    {
        elts[0] = a.km;
        elts[1] = h;
        elts[2] = k;
        elts[3] = MeanLongitude.AsSpiceDouble();
        elts[4] = p;
        elts[5] = q;
        elts[6] = RateOfLongitudeOfPeriapse.radiansPerSecond;
        elts[7] = MeanLongitudeDerivative.radiansPerSecond;
        elts[8] = RateOfLongitudeOfAscendingNode.radiansPerSecond;
    }

    FString ToString() const;
};


USTRUCT(BlueprintType)
struct SPICE_API FSEphemerisTimeWindowSegment
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSEphemerisTime start;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSEphemerisTime stop;

    FSEphemerisTimeWindowSegment()
    {
        start = FSEphemerisTime::J2000;
        stop = FSEphemerisTime::J2000;
    }

    FSEphemerisTimeWindowSegment(
        double _start,
        double _stop
    )
    {
        start = FSEphemerisTime(_start);
        stop = FSEphemerisTime(_stop);
    }

    FSEphemerisTimeWindowSegment(
        const FSEphemerisTime& _start,
        const FSEphemerisTime& _stop
    )
    {
        start = _start;
        stop = _stop;
    }


    FSEphemerisTimeWindowSegment(
        const double(&_segment)[2]
    )
    {
        start = FSEphemerisTime(_segment[0]);
        stop = FSEphemerisTime(_segment[1]);
    }

    void CopyTo(
        double& _start,
        double& _stop
    ) const
    {
        _start = start.AsSpiceDouble();
        _stop = stop.AsSpiceDouble();
    }

    void CopyTo(
        double(&_segment)[2]
    ) const
    {
        _segment[0] = start.AsSpiceDouble();
        _segment[1] = stop.AsSpiceDouble();
    }

    FString ToString() const;
};


// CK Files include windows in spacecraft clock encoded time (type: double)
USTRUCT(BlueprintType)
struct SPICE_API FSWindowSegment
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double start;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double stop;

    FSWindowSegment()
    {
        start = 0.;
        stop = 0.;
    }

    FSWindowSegment(
        double _start,
        double _stop
    )
    {
        start = _start;
        stop = _stop;
    }

    FSWindowSegment(
        const double(&_segment)[2]
    )
    {
        start = _segment[0];
        stop = _segment[1];
    }

    void CopyTo(
        double& _start,
        double& _stop
    ) const
    {
        _start = start;
        _stop = stop;
    }

    void CopyTo(
        double(&_segment)[2]
    ) const
    {
        _segment[0] = start;
        _segment[1] = stop;
    }

    FString ToString() const;
};


USTRUCT(BlueprintType)
struct SPICE_API FSPointingType2Observation
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSWindowSegment segment;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSQuaternion quat;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularVelocity avv;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double rate;

    FSPointingType2Observation()
    {
        segment = FSWindowSegment();
        quat = FSQuaternion();
        avv = FSAngularVelocity();
        rate = 0.;
    }


    FSPointingType2Observation(
        double _start,
        double _stop,
        const double(&_quat)[4],
        const double(&_avv)[3],
        double _rate
    )
    {
        segment = FSWindowSegment(_start, _stop);
        quat = FSQuaternion(_quat);
        avv = FSAngularVelocity(_avv);
        rate = _rate;
    }

    void CopyTo(
        double& _start,
        double& _stop,
        double(&_quat)[4],
        double(&_avv)[3],
        double& _rate
    ) const
    {
        segment.CopyTo(_start, _stop);
        quat.CopyTo(_quat);
        avv.CopyTo(_avv);
        _rate = rate;
    }

    FString ToString() const;
};


USTRUCT(BlueprintType)
struct SPICE_API FSPointingType1Observation
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double sclkdp;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSQuaternion quat;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularVelocity avv;

    FSPointingType1Observation()
    {
        sclkdp = 0.;
        quat = FSQuaternion();
        avv = FSAngularVelocity();
    }


    FSPointingType1Observation(
        double _sclkdp,
        const double(&_quat)[4],
        const double(&_avv)[3]
    )
    {
        sclkdp = _sclkdp;
        quat = FSQuaternion(_quat);
        avv = FSAngularVelocity(_avv);
    }

    void CopyTo(
        double& _sclkdp,
        double(&_quat)[4],
        double(&_avv)[3]
    ) const
    {
        _sclkdp = sclkdp;
        quat.CopyTo(_quat);
        avv.CopyTo(_avv);
    }

    FString ToString() const;
};


USTRUCT(BlueprintType)
struct SPICE_API FSPointingType5Observation
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double sclkdp;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSQuaternion quat;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSQuaternion quatderiv;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularVelocity avv;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSAngularVelocity avvderiv;

    FSPointingType5Observation()
    {
        sclkdp = 0.;
        quat = FSQuaternion();
        quatderiv = FSQuaternion();
        avv = FSAngularVelocity();
        avvderiv = FSAngularVelocity();
    }

    // ------------------------------------------------------------------------
    // Subtype 1
    static FSPointingType5Observation MakeObservationSubtype1(
        double _sclkdp,
        const double(&_quat)[4],
        const double(&_quatderiv)[4]
    )
    {
        FSPointingType5Observation result = FSPointingType5Observation();
        result.sclkdp = _sclkdp;
        result.quat = FSQuaternion(_quat);
        result.quatderiv = FSQuaternion(_quatderiv);
        return result;
    }

    void CopyToSubtype1(
        double _sclkdp,
        double(&_packet)[8]
    ) const
    {
        _sclkdp = sclkdp;

        double _quat_copy[4];
        quat.CopyTo(_quat_copy);

        double _quatderiv_copy[4];
        quatderiv.CopyTo(_quatderiv_copy);

        FMemory::Memcpy(&_packet[0], _quat_copy, sizeof(double[4]));
        FMemory::Memcpy(&_packet[4], _quatderiv_copy, sizeof(double[4]));
    }

    // ------------------------------------------------------------------------
    // Subtype 2
    static FSPointingType5Observation MakeObservationSubtype2(
        double _sclkdp,
        const double(&_quat)[4]
    )
    {
        FSPointingType5Observation result = FSPointingType5Observation();
        result.sclkdp = _sclkdp;
        result.quat = FSQuaternion(_quat);
        return result;
    }

    void CopyToSubtype2(
        double& _sclkdp,
        double(&_packet)[4]
    ) const
    {
        _sclkdp = sclkdp;

        double _quat_copy[4];
        quat.CopyTo(_quat_copy);

        FMemory::Memcpy(&_packet[0], _quat_copy, sizeof(double[4]));
    }

    // ------------------------------------------------------------------------
    // Subtype 3
    static FSPointingType5Observation MakeObservationSubtype3(
        double _sclkdp,
        const double(&_quat)[4],
        const double(&_quatderiv)[4],
        const double(&_avv)[3],
        const double(&_avvderiv)[3]
    )
    {
        FSPointingType5Observation result = FSPointingType5Observation();
        result.sclkdp = _sclkdp;
        result.quat = FSQuaternion(_quat);
        result.quatderiv = FSQuaternion(_quatderiv);
        result.avv = FSAngularVelocity(_avv);
        result.avvderiv = FSAngularVelocity(_avvderiv);
        return result;
    }

    void CopyToSubtype3(
        double& _sclkdp,
        double(&_packet)[14]
    ) const
    {
        _sclkdp = sclkdp;

        double _avv_copy[3];
        avv.CopyTo(_avv_copy);
        double _avvderiv_copy[3];
        avvderiv.CopyTo(_avvderiv_copy);

        double _quat_copy[4];
        quat.CopyTo(_quat_copy);
        double _quatderiv_copy[4];
        quatderiv.CopyTo(_quatderiv_copy);

        FMemory::Memcpy(&_packet[0], _quat_copy, sizeof(double[4]));
        FMemory::Memcpy(&_packet[4], _quatderiv_copy, sizeof(double[4]));
        FMemory::Memcpy(&_packet[8], _avv_copy, sizeof(double[3]));
        FMemory::Memcpy(&_packet[11], _avvderiv_copy, sizeof(double[3]));

    }

    // ------------------------------------------------------------------------
    // Subtype 4
    static FSPointingType5Observation MakeObservationSubtype4(
        double _sclkdp,
        const double(&_quat)[4],
        const double(&_avv)[3]
    )
    {
        FSPointingType5Observation result = FSPointingType5Observation();
        result.sclkdp = _sclkdp;
        result.quat = FSQuaternion(_quat);
        result.avv = FSAngularVelocity(_avv);

        return result;
    }

    void CopyToSubtype4(
        double _sclkdp,
        double(&_packet)[7]
    ) const
    {
        _sclkdp = sclkdp;

        double _avv_copy[3];
        avv.CopyTo(_avv_copy);

        double _quat_copy[4];
        quat.CopyTo(_quat_copy);

        FMemory::Memcpy(&_packet[0], _quat_copy, sizeof(double[4]));
        FMemory::Memcpy(&_packet[4], _avv_copy, sizeof(double[3]));
    }

    FString ToString() const;
};


USTRUCT(BlueprintType)
struct SPICE_API FSPKType5Observation
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSEphemerisTime et;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSStateVector state;

    FSPKType5Observation()
    {
        et = FSEphemerisTime();
        state = FSStateVector();
    }

    FSPKType5Observation(const FSEphemerisTime& _et, const FSStateVector& _state)
    {
        et = _et;
        state = _state;
    }


    FSPKType5Observation(
        double _et,
        const double(&_state)[6]
    )
    {
        et = FSEphemerisTime(_et);
        state = FSStateVector(_state);
    }

    void CopyTo(
        double& _et,
        double(&_state)[6]
    ) const
    {
        _et = et.AsSpiceDouble();
        state.CopyTo(_state);
    }

    FString ToString() const;
};


USTRUCT(BlueprintType)
struct SPICE_API FSPKType15Observation
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSEphemerisTime epoch;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDimensionlessVector tp;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDimensionlessVector pa;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistance p;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double ecc;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double j2flg;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDimensionlessVector pv;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSMassConstant gm;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double j2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistance radius;

    FSPKType15Observation()
    {
        epoch = FSEphemerisTime();
        tp = FSDimensionlessVector();
        pa = FSDimensionlessVector();
        p = FSDistance();
        ecc = 0.;
        j2flg = 0.;
        pv = FSDimensionlessVector();
        gm = FSMassConstant();
        j2 = 0.;
        radius = FSDistance();
    }


    FSPKType15Observation(
        const FSEphemerisTime& _epoch,
        const FSDimensionlessVector& _tp,
        const FSDimensionlessVector& _pa,
        const FSDistance& _p,
        double _ecc,
        double _j2flg,
        const FSDimensionlessVector& _pv,
        const FSMassConstant& _gm,
        double _j2,
        const FSDistance& _radius
        )
    {
        epoch = _epoch;
        tp = _tp;
        pa = _pa;
        p = _p;
        ecc = _ecc;
        j2flg = _j2flg;
        pv = _pv;
        gm = _gm;
        j2 = _j2;
        radius = _radius;
    }

    void CopyTo(
        double& _epoch,
        double(&_tp)[3],
        double(&_pa)[3],
        double& _p,
        double& _ecc,
        double& _j2flg,
        double(&_pv)[3],
        double& _gm,
        double& _j2,
        double& _radius
        ) const
    {
        _epoch = epoch.AsSpiceDouble();
        tp.CopyTo(_tp);
        pa.CopyTo(_pa);
        _ecc = ecc;
        _j2flg = j2flg;
        pv.CopyTo(_pv);
        _gm = gm.AsSpiceDouble();
        _j2 = j2;
        _radius = radius.AsSpiceDouble();
    }

    FString ToString() const;
};


USTRUCT(BlueprintType)
struct SPICE_API FSTwoLineElements
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") TArray<double> elems;

    const static int XNDT2O = 0;
    const static int XNDD6O = 1;
    const static int BSTAR  = 2;
    const static int XINCL  = 3;
    const static int XNODEO = 4;
    const static int EO     = 5;
    const static int OMEGAO = 6;
    const static int XMO    = 7;
    const static int XNO    = 8;
    const static int EPOCH  = 9;

public:

    FSTwoLineElements()
    {
        elems.Init(0., 10);
    }

    FSTwoLineElements(
        double(&_elems)[10]
    )
    {
        elems.Init(0., 10);

        FMemory::Memcpy(elems.GetData(), _elems, 10 * sizeof(double));
    }

    void CopyTo(double(&_elems)[10]) const;

    FSAngle M0() const { return FSAngle(elems[XMO]); }
    FSAngularRate N() const { return FSAngularRate(elems[XNO]/60.); }
    FSEphemerisTime ET() const { return FSEphemerisTime(elems[EPOCH]); }

    FString ToString() const;
};

USTRUCT(BlueprintType)
struct SPICE_API FSTLEGeophysicalConstants
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") TArray<double> geophs;

public:

    FSTLEGeophysicalConstants()
    {
    }

    FSTLEGeophysicalConstants(double(&_geophs)[8])
    {
        geophs.Init(0., 8);
        FMemory::Memcpy(geophs.GetData(), _geophs, 8 * sizeof(double));
    }

    void CopyTo(double(&_geophs)[8]) const;
    FString ToString() const;
};


USTRUCT(BlueprintType)
struct SPICE_API FSLimptPoint
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistanceVector point;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSEphemerisTime epoch;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistanceVector tangt;

public:

    FSLimptPoint()
    {
        point = FSDistanceVector();
        epoch = FSEphemerisTime();
        tangt = FSDistanceVector();
    }

    FSLimptPoint(
        const double (&_point)[3],
        double _epoch,
        const double (&_tangt)[3]
    )
    {
        point = FSDistanceVector(_point);
        epoch = FSEphemerisTime(_epoch);
        tangt = FSDistanceVector(_tangt);
    }

    void CopyTo(
        double(&_point)[3],
        double &_epoch,
        double(&_tangt)[3]
    ) const
    {
        point.CopyTo(_point);
        _epoch = epoch.AsSpiceDouble();
        tangt.CopyTo(_tangt);
    }

    FString ToString() const;
};


USTRUCT(BlueprintType)
struct SPICE_API FSLimptCut
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") TArray<FSLimptPoint> points;

public:

    FSLimptCut()
    {
    }

    FString ToString() const;
};



USTRUCT(BlueprintType)
struct SPICE_API FSTermptPoint
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistanceVector point;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSEphemerisTime epoch;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistanceVector trmvc;

public:

    FSTermptPoint()
    {
        point = FSDistanceVector();
        epoch = FSEphemerisTime();
        trmvc = FSDistanceVector();
    }

    FSTermptPoint(
        const double(&_point)[3],
        double _epoch,
        const double(&_trmvc)[3]
    )
    {
        point = FSDistanceVector(_point);
        epoch = FSEphemerisTime(_epoch);
        trmvc = FSDistanceVector(_trmvc);
    }

    void CopyTo(
        double(&_point)[3],
        double& _epoch,
        double(&_trmvc)[3]
    ) const
    {
        point.CopyTo(_point);
        _epoch = epoch.AsSpiceDouble();
        trmvc.CopyTo(_trmvc);
    }

    FString ToString() const;
};


USTRUCT(BlueprintType)
struct SPICE_API FSTermptCut
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") TArray<FSTermptPoint> points;

public:

    FSTermptCut()
    {
    }

    FString ToString() const;
};


USTRUCT(BlueprintType)
struct SPICE_API FSRay
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDistanceVector point;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") FSDimensionlessVector direction;

public:

    FSRay()
    {
        point = FSDistanceVector();
        direction = FSDimensionlessVector();
    }

    void CopyTo(double (&_point)[3], double (&_direction)[3]) const
    {
        point.CopyTo(_point);
        direction.CopyTo(_direction);
    }

    FString ToString() const;
};

USTRUCT(BlueprintType)
struct SPICE_API FSDLADescr
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") int bwdptr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") int fwdptr;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") int ibase;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") int isize;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") int dbase;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") int dsize;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") int cbase;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") int csize;

public:

    FSDLADescr()
    {
        bwdptr = 0;
        fwdptr = 0;
        ibase = 0;
        isize = 0;
        dbase = 0;
        dsize = 0;
        cbase = 0;
        csize = 0;
    }

    FSDLADescr(void* descr);
    
    void CopyTo(void* descr) const;
    FString ToString() const;
};


USTRUCT(BlueprintType)
struct SPICE_API FSDSKDescr
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") int surfce;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") int center;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") int dclass;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") int dtype;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") int frmcde;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") int corsys;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") TArray<double> corpar;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double co1min;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double co1max;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double co2min;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double co2max;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double co3min;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double co3max;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double start;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double stop;

public:

    FSDSKDescr()
    {
        surfce = 0;
        center = 0;
        dclass = 0;
        dtype = 0;
        frmcde = 0;
        corsys = 0;
        corpar = TArray<double>();
        co1min = 0.;
        co1max = 0.;
        co2min = 0.;
        co2max = 0.;
        co3min = 0.;
        co3max = 0.;
        start = 0.;
        stop = 0.;
    }

    FSDSKDescr(void* descr);

    void CopyTo(void* descr) const;
    FString ToString() const;
};


USTRUCT(BlueprintType)
struct SPICE_API FSPlateIndices
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") int i0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") int i1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") int i2;

public:

    FSPlateIndices()
    {
        i0 = i1 = i2 = 0;
    }

    FSPlateIndices(int(&_plate)[3])
    {
        i0 = _plate[0];
        i1 = _plate[1];
        i2 = _plate[2];
    }

    FSPlateIndices(int _i0, int _i1, int _i2)
    {
        i0 = _i0;
        i1 = _i1;
        i2 = _i2;
    }
    FString ToString() const;
};


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
    static const char* toString(ES_Units units);
    static const char* toString(ES_ReferenceFrameLocus locus);
    static const char* toString(ES_AberrationCorrectionFov abcorr);
    static const char* toString(ES_AberrationCorrectionWithNewtonians abcorr);
    static const char* toString(ES_AberrationCorrectionForOccultation abcorr);
    static const char* toString(ES_AberrationCorrectionWithTransmissions abcorr);
    static const char* toString(ES_AberrationCorrectionLocus corloc);
    static const char* toString(ES_AberrationCorrectionLocusTerminator corloc);
    static const char* toString(ES_TimeScale timeScale);
    static const char* toString(ES_GeometricModel model);
    static const char* toString(ES_OtherGeometricModel model);
    static const char* toString(ES_RelationalOperator relate);
    static const char* toString(ES_CoordinateSystemInclRadec coords);
    static const char* toString(ES_CoordinateSystem coords);
    static const char* toString(ES_CoordinateName coord);
    static const char* toString(ES_SubpointComputationMethod method);
    static const char* toString(ES_IlluminationAngleType);
    static FString toFString(ES_GeometricModel model, const TArray<FString>& shapeSurfaces);
    static FString toFString(ES_ComputationMethod method, const TArray<FString>& shapeSurfaces);
    static FString toFString(ES_LimbComputationMethod method, const TArray<FString>& shapeSurfaces);
    static FString toFString(ES_Shadow shadow, ES_CurveType curveType, ES_GeometricModel method, const TArray<FString>& shapeSurfaces);
    static FString ToString(ES_Axis Axis);
    static FString ToString(ES_KernelType KernelType);
    static ES_KernelType FromString(const FString& KernelType);

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
    
    /*
    *
    * Swizzling Conversions
    * For spatial data exchanged between SPICE/UE.
    * UE uses a single-precision Left-Handed Coordinate System
    * SPICE uses a double-precision Right-Handed Coordinate System
    * 
    */

    // Vectors...
    // --------------

    // From SPICE to UE
    template<typename T> static FVector Swizzle(const T& value);

    template<> SpiceStaticPartialTemplate FVector Swizzle<FSDimensionlessVector>(const FSDimensionlessVector& value)
    {
        return FVector((FVector::FReal)value.y, (FVector::FReal)value.x, (FVector::FReal)value.z);

    }

    template<> SpiceStaticPartialTemplate FVector Swizzle<FSDistanceVector>(const FSDistanceVector& value)
    {
        return FVector((FVector::FReal)value.y.km, (FVector::FReal)value.x.km, (FVector::FReal)value.z.km);
    }

    template<> SpiceStaticPartialTemplate FVector Swizzle<FSVelocityVector>(const FSVelocityVector& value)
    {
        return FVector((FVector::FReal)value.dy.kmps, (FVector::FReal)value.dx.kmps, (FVector::FReal)value.dz.kmps);
    }

    template<> SpiceStaticPartialTemplate FVector Swizzle<FSAngularVelocity>(const FSAngularVelocity& value)
    {
        // (Going from RHS/LHS negates angular velocities...)
        return FVector(-(FVector::FReal)value.y.radiansPerSecond, -(FVector::FReal)value.x.radiansPerSecond, -(FVector::FReal)value.z.radiansPerSecond);
    }

    // From UE to SPICE
    template<typename T> static void Swizzle(const FVector& in, T& out);
    
    template<> SpiceStaticPartialTemplate void Swizzle<FSDimensionlessVector>(const FVector& in,  FSDimensionlessVector& out)
    {
        out = FSDimensionlessVector(in.Y, in.X, in.Z);
    }

    template<> SpiceStaticPartialTemplate void Swizzle<FSDistanceVector>(const FVector& in, FSDistanceVector& out)
    {
        out = FSDistanceVector(in.Y, in.X, in.Z);
    }

    template<> SpiceStaticPartialTemplate void Swizzle<FSVelocityVector>(const FVector& in, FSVelocityVector& out)
    {
        out = FSVelocityVector(in.Y, in.X, in.Z);
    }

    template<> SpiceStaticPartialTemplate void Swizzle<FSAngularVelocity>(const FVector& in, FSAngularVelocity& out)
    {
        // (Going from LHS/RHS negates angular velocities...)
        out = FSAngularVelocity(FSAngularRate(-in.Y), FSAngularRate(-in.X), FSAngularRate(-in.Z));
    }


    // Quaternions...
    // --------------
    // From SPICE to UE
    inline static FQuat Swazzle(const FSQuaternion& value)
    {
        double x=0., y = 0., z = 0., w = 0.;
        value.QENG(w, x, y, z);
        return FQuat((FVector::FReal)y, (FVector::FReal)x, (FVector::FReal)z, (FVector::FReal)w);
    }

    // From UE to SPICE
    inline static FSQuaternion Swazzle(const FQuat& value)
    {
        return FSQuaternion::ENG(value.W, value.Y, value.X, value.Z);
    }

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

#pragma region NaifFNames
namespace MaxQ::Constants
{
    namespace Literal
    {
        constexpr TCHAR* J2000{ TEXT("J2000") };
        constexpr TCHAR* ECLIPJ2000{ TEXT("ECLIPJ2000") };
        constexpr TCHAR* MARSIAU{ TEXT("MARSIAU") };
        constexpr TCHAR* GALACTIC{ TEXT("GALACTIC") };
        constexpr TCHAR* IAU_EARTH{ TEXT("IAU_EARTH") };
        constexpr TCHAR* EARTH_FIXED{ TEXT("EARTH_FIXED") };
        constexpr TCHAR* ITRF93{ TEXT("ITRF93") };
        constexpr TCHAR* IAU_MOON{ TEXT("IAU_MOON") };
        constexpr TCHAR* IAU_SUN{ TEXT("IAU_SUN") };
        constexpr TCHAR* IAU_MERCURY{ TEXT("IAU_MERCURY") };
        constexpr TCHAR* IAU_VENUS{ TEXT("IAU_VENUS") };
        constexpr TCHAR* IAU_MARS{ TEXT("IAU_MARS") };
        constexpr TCHAR* IAU_DEIMOS{ TEXT("IAU_DEIMOS") };
        constexpr TCHAR* IAU_PHOBOS{ TEXT("IAU_PHOBOS") };
        constexpr TCHAR* IAU_JUPITER{ TEXT("IAU_JUPITER") };
        constexpr TCHAR* IAU_SATURN{ TEXT("IAU_SATURN") };
        constexpr TCHAR* IAU_NEPTUNE{ TEXT("IAU_NEPTUNE") };
        constexpr TCHAR* IAU_URANUS{ TEXT("IAU_URANUS") };
        constexpr TCHAR* IAU_PLUTO{ TEXT("IAU_PLUTO") };
        constexpr TCHAR* IAU_CERES{ TEXT("IAU_CERES") };
        constexpr TCHAR* EARTH{ TEXT("EARTH") };
        constexpr TCHAR* MOON{ TEXT("MOON") };
        constexpr TCHAR* EMB{ TEXT("EMB") };
        constexpr TCHAR* EARTH_BARYCENTER{ TEXT("EARTH_BARYCENTER") };
        constexpr TCHAR* SUN{ TEXT("SUN") };
        constexpr TCHAR* SSB{ TEXT("SSB") };
        constexpr TCHAR* SOLAR_SYSTEM_BARYCENTER{ TEXT("SOLAR_SYSTEM_BARYCENTER") };
        constexpr TCHAR* MERCURY{ TEXT("MERCURY") };
        constexpr TCHAR* VENUS{ TEXT("VENUS") };
        constexpr TCHAR* MARS{ TEXT("MARS") };
        constexpr TCHAR* PHOBOS{ TEXT("PHOBOS") };
        constexpr TCHAR* DEIMOS{ TEXT("DEIMOS") };
        constexpr TCHAR* MARS_BARYCENTER{ TEXT("MARS_BARYCENTER") };
        constexpr TCHAR* JUPITER{ TEXT("JUPITER") };
        constexpr TCHAR* JUPITER_BARYCENTER{ TEXT("JUPITER_BARYCENTER") };
        constexpr TCHAR* SATURN{ TEXT("SATURN") };
        constexpr TCHAR* SATURN_BARYCENTER{ TEXT("SATURN_BARYCENTER") };
        constexpr TCHAR* URANUS{ TEXT("URANUS") };
        constexpr TCHAR* URANUS_BARYCENTER{ TEXT("URANUS_BARYCENTER") };
        constexpr TCHAR* NEPTUNE{ TEXT("NEPTUNE") };
        constexpr TCHAR* NEPTUNE_BARYCENTER{ TEXT("NEPTUNE_BARYCENTER") };
        constexpr TCHAR* PLUTO{ TEXT("PLUTO") };
        constexpr TCHAR* PLUTO_BARYCENTER{ TEXT("PLUTO_BARYCENTER") };
        constexpr TCHAR* CERES{ TEXT("CERES") };
        constexpr TCHAR* PIONEER_6{ TEXT("PIONEER-6") };
        constexpr TCHAR* PIONEER_7{ TEXT("PIONEER-7") };
        constexpr TCHAR* VIKING_1_ORBITER{ TEXT("VIKING 1 ORBITER") };
        constexpr TCHAR* VIKING_2_ORBITER{ TEXT("VIKING 2 ORBITER") };
        constexpr TCHAR* VOYAGER_1{ TEXT("VOYAGER 1") };
        constexpr TCHAR* VOYAGER_2{ TEXT("VOYAGER 2") };
        constexpr TCHAR* HST{ TEXT("HST") };
        constexpr TCHAR* HUBBLE_SPACE_TELESCOPE{ TEXT("HUBBLE SPACE TELESCOPE") };
        constexpr TCHAR* MARS_PATHFINDER{ TEXT("MARS PATHFINDER") };
        constexpr TCHAR* PARKER_SOLAR_PROBE{ TEXT("PARKER SOLAR PROBE") };
        constexpr TCHAR* JWST{ TEXT("JWST") };
        constexpr TCHAR* JAMES_WEBB_SPACE_TELESCOPE{ TEXT("JAMES WEBB SPACE TELESCOPE") };
        constexpr TCHAR* INSIGHT{ TEXT("INSIGHT") };
        constexpr TCHAR* OPPORTUNITY{ TEXT("OPPORTUNITY") };
        constexpr TCHAR* SPIRIT{ TEXT("SPIRIT") };
        constexpr TCHAR* NOTO{ TEXT("NOTO") };
        constexpr TCHAR* NEW_NORCIA{ TEXT("NEW NORCIA") };
        constexpr TCHAR* GOLDSTONE{ TEXT("GOLDSTONE") };
        constexpr TCHAR* CANBERRA{ TEXT("CANBERRA") };
        constexpr TCHAR* MADRID{ TEXT("MADRID") };
        constexpr TCHAR* USUDA{ TEXT("USUDA") };
        constexpr TCHAR* DSS_05{ TEXT("DSS-05") };
        constexpr TCHAR* PARKES{ TEXT("PARKES") };
        constexpr TCHAR* GM{ TEXT("GM") };
        constexpr TCHAR* RADII{ TEXT("RADII") };
    }

    extern SPICE_API const FString J2000;
    extern SPICE_API const FString ECLIPJ2000;
    extern SPICE_API const FString MARSIAU;
    extern SPICE_API const FString GALACTIC;
    extern SPICE_API const FString IAU_EARTH;
    extern SPICE_API const FString EARTH_FIXED;
    extern SPICE_API const FString ITRF93;
    extern SPICE_API const FString IAU_MOON;
    extern SPICE_API const FString IAU_SUN;
    extern SPICE_API const FString IAU_MERCURY;
    extern SPICE_API const FString IAU_VENUS;
    extern SPICE_API const FString IAU_MARS;
    extern SPICE_API const FString IAU_DEIMOS;
    extern SPICE_API const FString IAU_PHOBOS;
    extern SPICE_API const FString IAU_JUPITER;
    extern SPICE_API const FString IAU_SATURN;
    extern SPICE_API const FString IAU_NEPTUNE;
    extern SPICE_API const FString IAU_URANUS;
    extern SPICE_API const FString IAU_PLUTO;
    extern SPICE_API const FString IAU_CERES;
    extern SPICE_API const FString EARTH;
    extern SPICE_API const FString MOON;
    extern SPICE_API const FString EMB;
    extern SPICE_API const FString EARTH_BARYCENTER;
    extern SPICE_API const FString SUN;
    extern SPICE_API const FString SSB;
    extern SPICE_API const FString SOLAR_SYSTEM_BARYCENTER;
    extern SPICE_API const FString MERCURY;
    extern SPICE_API const FString VENUS;
    extern SPICE_API const FString MARS;
    extern SPICE_API const FString PHOBOS; 
    extern SPICE_API const FString DEIMOS; 
    extern SPICE_API const FString MARS_BARYCENTER;
    extern SPICE_API const FString JUPITER;
    extern SPICE_API const FString JUPITER_BARYCENTER;
    extern SPICE_API const FString SATURN; 
    extern SPICE_API const FString SATURN_BARYCENTER;
    extern SPICE_API const FString URANUS; 
    extern SPICE_API const FString URANUS_BARYCENTER;
    extern SPICE_API const FString NEPTUNE;
    extern SPICE_API const FString NEPTUNE_BARYCENTER;
    extern SPICE_API const FString PLUTO;
    extern SPICE_API const FString PLUTO_BARYCENTER;
    extern SPICE_API const FString CERES;
    extern SPICE_API const FString PIONEER_6;
    extern SPICE_API const FString PIONEER_7;
    extern SPICE_API const FString VIKING_1_ORBITER;
    extern SPICE_API const FString VIKING_2_ORBITER;
    extern SPICE_API const FString VOYAGER_1;
    extern SPICE_API const FString VOYAGER_2;
    extern SPICE_API const FString HST;
    extern SPICE_API const FString HUBBLE_SPACE_TELESCOPE;
    extern SPICE_API const FString MARS_PATHFINDER;
    extern SPICE_API const FString PARKER_SOLAR_PROBE;
    extern SPICE_API const FString JWST;
    extern SPICE_API const FString JAMES_WEBB_SPACE_TELESCOPE;
    extern SPICE_API const FString INSIGHT;
    extern SPICE_API const FString OPPORTUNITY;
    extern SPICE_API const FString SPIRIT; 
    extern SPICE_API const FString NOTO;
    extern SPICE_API const FString NEW_NORCIA;
    extern SPICE_API const FString GOLDSTONE;
    extern SPICE_API const FString CANBERRA;
    extern SPICE_API const FString MADRID; 
    extern SPICE_API const FString USUDA;
    extern SPICE_API const FString DSS_05; 
    extern SPICE_API const FString PARKES; 
    extern SPICE_API const FString GM;
    extern SPICE_API const FString RADII;

    extern SPICE_API const FName Name_J2000;
    extern SPICE_API const FName Name_ECLIPJ2000;
    extern SPICE_API const FName Name_MARSIAU;
    extern SPICE_API const FName Name_GALACTIC;
    extern SPICE_API const FName Name_IAU_EARTH;
    extern SPICE_API const FName Name_EARTH_FIXED;
    extern SPICE_API const FName Name_ITRF93;
    extern SPICE_API const FName Name_IAU_MOON;
    extern SPICE_API const FName Name_IAU_SUN;
    extern SPICE_API const FName Name_IAU_MERCURY;
    extern SPICE_API const FName Name_IAU_VENUS;
    extern SPICE_API const FName Name_IAU_MARS;
    extern SPICE_API const FName Name_IAU_DEIMOS;
    extern SPICE_API const FName Name_IAU_PHOBOS;
    extern SPICE_API const FName Name_IAU_JUPITER;
    extern SPICE_API const FName Name_IAU_SATURN;
    extern SPICE_API const FName Name_IAU_NEPTUNE;
    extern SPICE_API const FName Name_IAU_URANUS;
    extern SPICE_API const FName Name_IAU_PLUTO;
    extern SPICE_API const FName Name_IAU_CERES;
    extern SPICE_API const FName Name_EARTH;
    extern SPICE_API const FName Name_MOON;
    extern SPICE_API const FName Name_EMB;
    extern SPICE_API const FName Name_EARTH_BARYCENTER;
    extern SPICE_API const FName Name_SUN;
    extern SPICE_API const FName Name_SSB;
    extern SPICE_API const FName Name_SOLAR_SYSTEM_BARYCENTER;
    extern SPICE_API const FName Name_MERCURY;
    extern SPICE_API const FName Name_VENUS;
    extern SPICE_API const FName Name_MARS;
    extern SPICE_API const FName Name_PHOBOS;
    extern SPICE_API const FName Name_DEIMOS;
    extern SPICE_API const FName Name_MARS_BARYCENTER;
    extern SPICE_API const FName Name_JUPITER;
    extern SPICE_API const FName Name_JUPITER_BARYCENTER;
    extern SPICE_API const FName Name_SATURN;
    extern SPICE_API const FName Name_SATURN_BARYCENTER;
    extern SPICE_API const FName Name_URANUS;
    extern SPICE_API const FName Name_URANUS_BARYCENTER;
    extern SPICE_API const FName Name_NEPTUNE;
    extern SPICE_API const FName Name_NEPTUNE_BARYCENTER;
    extern SPICE_API const FName Name_PLUTO;
    extern SPICE_API const FName Name_PLUTO_BARYCENTER;
    extern SPICE_API const FName Name_CERES;
    extern SPICE_API const FName Name_PIONEER_6;
    extern SPICE_API const FName Name_PIONEER_7;
    extern SPICE_API const FName Name_VIKING_1_ORBITER;
    extern SPICE_API const FName Name_VIKING_2_ORBITER;
    extern SPICE_API const FName Name_VOYAGER_1;
    extern SPICE_API const FName Name_VOYAGER_2;
    extern SPICE_API const FName Name_HST;
    extern SPICE_API const FName Name_HUBBLE_SPACE_TELESCOPE;
    extern SPICE_API const FName Name_MARS_PATHFINDER;
    extern SPICE_API const FName Name_PARKER_SOLAR_PROBE;
    extern SPICE_API const FName Name_JWST;
    extern SPICE_API const FName Name_JAMES_WEBB_SPACE_TELESCOPE;
    extern SPICE_API const FName Name_INSIGHT;
    extern SPICE_API const FName Name_OPPORTUNITY;
    extern SPICE_API const FName Name_SPIRIT;
    extern SPICE_API const FName Name_NOTO;
    extern SPICE_API const FName Name_NEW_NORCIA;
    extern SPICE_API const FName Name_GOLDSTONE;
    extern SPICE_API const FName Name_CANBERRA;
    extern SPICE_API const FName Name_MADRID;
    extern SPICE_API const FName Name_USUDA;
    extern SPICE_API const FName Name_DSS_05;
    extern SPICE_API const FName Name_PARKES;
    extern SPICE_API const FName Name_GM;
    extern SPICE_API const FName Name_RADII;

#pragma endregion NaifFNames
}
