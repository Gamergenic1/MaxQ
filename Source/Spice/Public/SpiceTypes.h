// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

#pragma once

#include "CoreMinimal.h"
#include "SpiceTypes.generated.h"

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
    NotFound UMETA(DisplayName = "No Found")
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
enum class ES_AberrationCorrection : uint8
{
    None = 0 UMETA(DisplayName = "None (No Correction)"),
    LT = 1 UMETA(DisplayName = "LT (Planetary Abberration)"),
    LT_S = 2 UMETA(DisplayName = "LT+S (Planetary + Stellar Abberation, Newtonian)"),
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
enum class ES_Units : uint8
{
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
enum class ES_TimeScale : uint8
{
    NONE UMETA(Hidden),
    TAI UMETA(DisplayName = "International Atomic Time"),
    TDB UMETA(DisplayName = "Barycentric Dynamical Time"),
    TDT UMETA(DisplayName = "Terrestrial Dynamical Time"),
    ET UMETA(DisplayName = "Ephemeris time (TBD)"),
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




USTRUCT(BlueprintType)
struct FSDimensionlessVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) double x;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) double y;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) double z;

    FSDimensionlessVector()
    {
        x = 0.;
        y = 0.;
        z = 0.;
    }

    FSDimensionlessVector(const double(&xyz)[3])
    {
        x = xyz[0];
        y = xyz[1];
        z = xyz[2];
    }

    FSDimensionlessVector(double _x, double _y, double _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    void CopyTo(double(&xyz)[3]) const
    {
        xyz[0] = x;
        xyz[1] = y;
        xyz[2] = z;
    }

    static SPICE_API const FSDimensionlessVector Zero;
};

USTRUCT(BlueprintType)
struct FSDistance
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) double km;

    FSDistance()
    {
        km = 0;
    }

    FSDistance(double _km)
    {
        km = _km;
    }

    double AsDouble() const { return km; }

    FSDistance(const FSDistance& other)
    {
        km = other.km;
    }

    FSDistance operator=(const FSDistance& other)
    {
        km = other.km;
        return *this;
    }

    static SPICE_API const FSDistance Zero;
    static SPICE_API const FSDistance OneKm;
};


inline FSDistance operator+(const FSDistance& lhs, const FSDistance& rhs)
{
    return FSDistance(lhs.km + rhs.km);
}

inline FSDistance operator-(const FSDistance& lhs, const FSDistance& rhs)
{
    return FSDistance(lhs.km - rhs.km);
}

inline double operator/(const FSDistance& lhs, const FSDistance& rhs)
{
    return lhs.km / rhs.km;
}

inline FSDistance operator/(const FSDistance& lhs, double rhs)
{
    return lhs.km / rhs;
}


inline FSDistance operator*(double lhs, const FSDistance& rhs)
{
    return FSDistance(lhs * rhs.km);
}

inline FSDistance operator*(const FSDistance& lhs, double rhs)
{
    return FSDistance(lhs.km * rhs);
}



USTRUCT(BlueprintType)
struct FSDistanceVector
{
    GENERATED_BODY()

        UPROPERTY(EditAnywhere, BlueprintReadWrite) FSDistance x;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSDistance y;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSDistance z;

    FSDistanceVector()
    {
        x = FSDistance::Zero;
        y = FSDistance::Zero;
        z = FSDistance::Zero;
    }

    FSDistanceVector(double _x, double _y, double _z)
    {
        x = FSDistance(_x);
        y = FSDistance(_y);
        z = FSDistance(_z);
    }

    FSDistanceVector(const FSDistance& _x, const FSDistance& _y, const FSDistance& _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    FSDistanceVector(const double(&xyz)[3])
    {
        x = FSDistance(xyz[0]);
        y = FSDistance(xyz[1]);
        z = FSDistance(xyz[2]);
    }

    FSDistanceVector(const FSDimensionlessVector& value)
    {
        x = FSDistance(value.x);
        y = FSDistance(value.y);
        z = FSDistance(value.z);
    }

    void AsDimensionlessVector(FSDimensionlessVector& vector) const
    {
        vector.x = x.AsDouble();
        vector.y = y.AsDouble();
        vector.z = z.AsDouble();
    }

    void CopyTo(double(&xyz)[3]) const
    {
        xyz[0] = x.km;
        xyz[1] = y.km;
        xyz[2] = z.km;
    }

    static SPICE_API const FSDistanceVector Zero;
};


inline FSDistanceVector operator+(const FSDistanceVector& lhs, const FSDistanceVector& rhs)
{
    return FSDistanceVector(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

inline FSDistanceVector operator-(const FSDistanceVector& lhs, const FSDistanceVector& rhs)
{
    return FSDistanceVector(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

inline FSDistanceVector operator*(double lhs, const FSDistanceVector& rhs)
{
    return FSDistanceVector(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

inline FSDistanceVector operator*(const FSDistanceVector& lhs, double rhs)
{
    return FSDistanceVector(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

inline FSDistanceVector operator/(const FSDistanceVector& lhs, double rhs)
{
    return FSDistanceVector(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

inline FSDimensionlessVector operator/(const FSDistanceVector& lhs, FSDistanceVector rhs)
{
    return FSDimensionlessVector(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
}

inline FSDimensionlessVector operator/(const FSDistanceVector& lhs, const FSDistance& rhs)
{
    return FSDimensionlessVector(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}


USTRUCT(BlueprintType)
struct FSSpeed
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) double kmps;

    FSSpeed()
    {
        kmps = 0;
    }

    FSSpeed(double _kmps)
    {
        kmps = _kmps;
    }

    /// <summary>Returns value in km/sec</summary>
    /// <returns>Kilometers Per Second</returns>
    double AsDouble() const { return kmps; }

    FSSpeed(const FSSpeed& other)
    {
        kmps = other.kmps;
    }

    FSSpeed operator=(const FSSpeed& other)
    {
        kmps = other.kmps;
        return *this;
    }

    static SPICE_API const FSSpeed Zero;
    static SPICE_API const FSSpeed OneKmps;
};

inline FSSpeed operator+(const FSSpeed& lhs, const FSSpeed& rhs)
{
    return FSSpeed(lhs.kmps + rhs.kmps);
}

inline FSSpeed operator-(const FSSpeed& lhs, const FSSpeed& rhs)
{
    return FSSpeed(lhs.kmps - rhs.kmps);
}

inline double operator/(const FSSpeed& lhs, const FSSpeed& rhs)
{
    return lhs.kmps / rhs.kmps;
}

inline FSSpeed operator/(const FSSpeed& lhs, double rhs)
{
    return lhs.kmps / rhs;
}


inline FSSpeed operator*(double lhs, const FSSpeed& rhs)
{
    return FSSpeed(lhs * rhs.kmps);
}

inline FSSpeed operator*(const FSSpeed& lhs, double rhs)
{
    return FSSpeed(lhs.kmps * rhs);
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
USTRUCT(BlueprintType)
struct FSAngle
{
    GENERATED_BODY()

    // However, we want users to see degrees when editing or looking at serialized data.
    UPROPERTY(EditAnywhere, BlueprintReadWrite) double degrees;

private:
    // Q: why keep 180/pi's value in every instance of the struct?
    // A: to keep it in the same cache line as our data
    // Premature optimization may be the root of all evil, but this hurts nothing.
    // CSPICE was built with numerical stability in mind, I think it's preferable
    // to defer to it for definitions of all constants.
    double cachedDpr;
public:

    // Let's use the CSPICE version of pi.  Since this is a header file, and we
    // don't want other modules to require the spice headers to use this module,
    // we'll need to bounce the constructor definitions out to a cpp file.
    FSAngle();

    FSAngle(double __radians);

    // FOR CLARITY
    inline double radians() const
    {
        return degrees / cachedDpr;
    }

    // FOR CONSISTENCY
    /// <summary>Returns value in Radians</summary>
    /// <returns>Radians</returns>
    inline double AsDouble() const { return radians(); }


    static SPICE_API const FSAngle _0;
    static SPICE_API const FSAngle _360;
};

USTRUCT(BlueprintType)
struct FSAngularRate
{
    GENERATED_BODY()

    // It's not much of a win serializizing this as degreesPerSecond,
    // as serialized data for angular rates are rarely edited compared to angles.
    // However, a period/revolution could make sense, ... but time is very messy
    // anyways.  How many seconds long is one sidereal day?  Not much of a win
    // editing "seconds" versus "radiansPerSecond".
    UPROPERTY(EditAnywhere, BlueprintReadWrite) double radiansPerSecond;

    FSAngularRate()
    {
        radiansPerSecond = 0.;
    }

    FSAngularRate(double _radiansPerSecond)
    {
        radiansPerSecond = _radiansPerSecond;
    }


    /// <summary>Returns value in Radians/Second</summary>
    /// <returns>Radians/Second</returns>
    inline double AsDouble() const { return radiansPerSecond; }

    static SPICE_API const FSAngularRate Zero;
};


USTRUCT(BlueprintType)
struct FSComplexScalar
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) double real;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) double imaginary;

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

    static SPICE_API const FSComplexScalar Zero;
};


USTRUCT(BlueprintType)
struct FSEphemerisTime
{
    GENERATED_BODY()

    // ephemeris seconds past J2000
    UPROPERTY(EditAnywhere, BlueprintReadWrite) double seconds;

    FSEphemerisTime()
    {
        seconds = 0.;
    }

    FSEphemerisTime(double _seconds)
    {
        seconds = _seconds;
    }

    /// <summary>Returns value in Seconds past J2000 Epoch</summary>
    /// <returns>Seconds</returns>
    inline double AsDouble() const { return seconds; }

    static SPICE_API const FSEphemerisTime J2000;
};


USTRUCT(BlueprintType)
struct FSEphemerisPeriod
{
    GENERATED_BODY()

    // ephemeris seconds
    UPROPERTY(EditAnywhere, BlueprintReadWrite) double seconds;

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
    inline double AsDouble() const { return seconds; }

    static SPICE_API const FSEphemerisPeriod Zero;
    static SPICE_API const FSEphemerisPeriod Day;
};

inline static FSEphemerisTime operator+(const FSEphemerisPeriod& A, const FSEphemerisTime& B)
{
    return FSEphemerisTime(A.AsDouble() + B.AsDouble());
}

inline static FSEphemerisTime operator+(const FSEphemerisTime& A, const FSEphemerisPeriod& B)
{
    return FSEphemerisTime(A.AsDouble() + B.AsDouble());
}

inline static FSEphemerisPeriod operator+(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B)
{
    return FSEphemerisPeriod(A.AsDouble() + B.AsDouble());
}

inline static FSEphemerisPeriod operator-(const FSEphemerisTime& A, const FSEphemerisTime& B)
{
    return FSEphemerisPeriod(A.AsDouble() - B.AsDouble());
}

inline static FSEphemerisPeriod operator*(double A, const FSEphemerisPeriod& B)
{
    return FSEphemerisPeriod(A * B.AsDouble());
}

inline static FSEphemerisPeriod operator*(const FSEphemerisPeriod& A, double B)
{
    return FSEphemerisPeriod(A.AsDouble() * B);
}

inline static FSEphemerisPeriod operator/(const FSEphemerisPeriod& A, double B)
{
    return FSEphemerisPeriod(A.AsDouble() / B);
}

inline static FSEphemerisPeriod operator%(const FSEphemerisPeriod& A, double B)
{
    return FSEphemerisPeriod(A.AsDouble() / B);
}


USTRUCT(BlueprintType)
struct FSVelocityVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSSpeed x;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSSpeed y;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSSpeed z;

    FSVelocityVector()
    {
        x = FSSpeed::Zero;
        y = FSSpeed::Zero;
        z = FSSpeed::Zero;
    }

    FSVelocityVector(const double(&xyz)[3])
    {
        x = FSSpeed(xyz[0]);
        y = FSSpeed(xyz[1]);
        z = FSSpeed(xyz[2]);
    }

    FSVelocityVector(double _x, double _y, double _z)
    {
        x = FSSpeed(_x);
        y = FSSpeed(_y);
        z = FSSpeed(_z);
    }

    FSVelocityVector(const FSSpeed& _x, const FSSpeed& _y, const FSSpeed& _z)
    {
        x = FSSpeed(_x);
        y = FSSpeed(_y);
        z = FSSpeed(_z);
    }

    FSVelocityVector(const FSDimensionlessVector& value)
    {
        x = FSSpeed(value.x);
        y = FSSpeed(value.y);
        z = FSSpeed(value.z);
    }

    void AsDimensionlessVector(FSDimensionlessVector& vector) const
    {
        vector.x = x.AsDouble();
        vector.y = y.AsDouble();
        vector.z = z.AsDouble();
    }

    void CopyTo(double(&xyz)[3]) const
    {
        xyz[0] = x.kmps;
        xyz[1] = y.kmps;
        xyz[2] = z.kmps;
    }

    static SPICE_API const FSVelocityVector Zero;
};


inline FSDistance operator*(const FSEphemerisPeriod& lhs, const FSSpeed& rhs)
{
    return FSDistance(lhs.seconds * rhs.kmps);
}

inline FSDistance operator*(const FSSpeed& lhs, const FSEphemerisPeriod& rhs)
{
    return FSDistance(lhs.kmps * rhs.seconds);
}

inline FSVelocityVector operator+(const FSVelocityVector& lhs, const FSVelocityVector& rhs)
{
    return FSVelocityVector(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

inline FSVelocityVector operator-(const FSVelocityVector& lhs, const FSVelocityVector& rhs)
{
    return FSVelocityVector(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

inline FSVelocityVector operator/(const FSVelocityVector& lhs, double rhs)
{
    return FSVelocityVector(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}


inline FSVelocityVector operator*(double lhs, const FSVelocityVector& rhs)
{
    return FSVelocityVector(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}


inline FSVelocityVector operator*(const FSVelocityVector& lhs, double rhs)
{
    return FSVelocityVector(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

inline FSDistanceVector operator*(const FSEphemerisPeriod& lhs, const FSVelocityVector& rhs)
{
    return FSDistanceVector(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

inline FSDistanceVector operator*(const FSVelocityVector& lhs, const FSEphemerisPeriod& rhs)
{
    return FSDistanceVector(rhs * lhs.x, rhs * lhs.y, rhs * lhs.z);
}


USTRUCT(BlueprintType)
struct FSLonLat
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngle longitude;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngle latitude;

    FSLonLat()
    {
        longitude = FSAngle::_0;
        latitude = FSAngle::_0;
    }

    FSLonLat(double lon, double lat)
    {
        longitude = lon;
        latitude = lat;
    }

    FSLonLat(const FSAngle& lon, const FSAngle& lat)
    {
        longitude = lon;
        latitude = lat;
    }

    void AsAngles(FSAngle& lon, FSAngle& lat) const
    {
        lon = longitude;
        lat = latitude;
    }

    void CopyTo(double& lon, double& lat) const
    {
        lon = longitude.AsDouble();
        lat = latitude.AsDouble();
    }
};




USTRUCT(BlueprintType)
struct FSEulerAngles
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngle angle3;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngle angle2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngle angle1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ES_Axis axis3;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ES_Axis axis2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ES_Axis axis1;

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


    void CopyTo(double(&_eulang)[3], uint8& _axis3, uint8& _axis2, uint8& _axis1) const
    {
        _eulang[0] = angle3.radians();
        _eulang[1] = angle2.radians();
        _eulang[2] = angle1.radians();
        _axis3 = (uint8)axis3;
        _axis2 = (uint8)axis2;
        _axis1 = (uint8)axis1;
    }

    static SPICE_API const FSEulerAngles Zero;
};


USTRUCT(BlueprintType)
struct FSAngularVelocity
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngularRate x;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngularRate y;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngularRate z;

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

    FSAngularVelocity(const FSDimensionlessVector& value)
    {
        x = FSAngularRate(value.x);
        y = FSAngularRate(value.y);
        z = FSAngularRate(value.z);
    }

    void AsDimensionlessVector(FSDimensionlessVector& vector) const
    {
        vector.x = x.AsDouble();
        vector.y = y.AsDouble();
        vector.z = z.AsDouble();
    }

    void CopyTo(double(&_av)[3]) const
    {
        _av[0] = x.radiansPerSecond;
        _av[1] = y.radiansPerSecond;
        _av[2] = z.radiansPerSecond;
    }

    static SPICE_API const FSAngularVelocity Zero;
};



USTRUCT(BlueprintType)
struct FSEulerAngularState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngle angle3;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngle angle2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngle angle1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngularRate rate3;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngularRate rate2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngularRate rate1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ES_Axis axis3;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ES_Axis axis2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ES_Axis axis1;

    FSEulerAngularState()
    {
        angle3 = FSAngle::_0;
        angle2 = FSAngle::_0;
        angle1 = FSAngle::_0;
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
        _eulang[0] = angle3.radians();
        _eulang[1] = angle2.radians();
        _eulang[2] = angle1.radians();
        _eulang[3] = rate3.radiansPerSecond;
        _eulang[4] = rate2.radiansPerSecond;
        _eulang[5] = rate1.radiansPerSecond;
        _axis3 = (uint8)axis3;
        _axis2 = (uint8)axis2;
        _axis1 = (uint8)axis1;
    }

    static SPICE_API const FSEulerAngularState Zero;
};


USTRUCT(BlueprintType)
struct FSEulerAngularTransform
{
    GENERATED_BODY()

    double m[6][6];

    FSEulerAngularTransform()
    {
        memset(m, 0, sizeof(m));
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = m[4][4] = m[5][5] = 1.;
    }

    FSEulerAngularTransform(const double(&_m)[6][6])
    {
        memcpy(m, _m, sizeof(m));
    }

    void CopyTo(double(&_m)[6][6]) const
    {
        memcpy(_m, m, sizeof(_m));
    }

    static SPICE_API const FSEulerAngularTransform Identity;
};



USTRUCT(BlueprintType)
struct FSMassConstant
{
    GENERATED_BODY()

    // In many cases GM is known to greater accuracy than G or M.
    // https://en.wikipedia.org/wiki/Standard_gravitational_parameter
    UPROPERTY(EditAnywhere, BlueprintReadWrite) double GM;

    FSMassConstant()
    {
        GM = 0;
    }

    FSMassConstant(double _GM)
    {
        GM = _GM;
    }

    /// <summary>Returns value in km^3/sec^2/</summary>
    /// <returns>km^3/sec^2</returns>
    double AsDouble() const
    {
        return GM;
    }
};


USTRUCT(BlueprintType)
struct FSStateVector
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSDistanceVector r;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSVelocityVector v;

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
        state[3] = v.x.kmps;
        state[4] = v.y.kmps;
        state[5] = v.z.kmps;
    }
};


USTRUCT(BlueprintType)
struct FSStateTransform
{
    GENERATED_BODY()

    double m[6][6];

    FSStateTransform()
    {
        memset(m, 0, sizeof(m));
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = m[4][4] = m[5][5] = 1.;
    }

    FSStateTransform(const double(&_m)[6][6])
    {
        memcpy(m, _m, sizeof(m));
    }

    void CopyTo(double (&_m)[6][6]) const
    {
        memcpy(_m, m, sizeof(_m));
    }

    static SPICE_API const FSStateTransform Identity;
};




USTRUCT(BlueprintType,
    Meta = (
        ShortToolTip = "C-Matrix",
        ToolTip = "3x3 Rotation Matrix (AKA C-Matrix, or Camera-Matrix)"
        ))

struct FSRotationMatrix
{
    GENERATED_BODY()

    double m[3][3];

    FSRotationMatrix()
    {
        memset(m, 0, sizeof(m));
    }

    FSRotationMatrix(const double(&_m)[3][3])
    {
        memcpy(m, _m, sizeof(m));
    }

    void CopyTo(double(&_m)[3][3]) const
    {
        memcpy(_m, m, sizeof(_m));
    }

    static SPICE_API const FSRotationMatrix Identity;
};


USTRUCT(BlueprintType)
struct FSQuaternion
{
    GENERATED_BODY()

    // https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/q2m_c.html
    double q[4];

    inline void QSPICE(double& w, double& x, double& y, double& z) const
    {
        w = q[0];
        x = q[1];
        y = q[2];
        z = q[3];
    }
    inline void QENG(double& w, double& x, double& y, double& z) const
    {
        w = q[0];
        x = -q[1];
        y = -q[2];
        z = -q[3];
    }
    inline static FSQuaternion SPICE(double w, double x, double y, double z)
    {
        FSQuaternion value = FSQuaternion();
        value.q[0] = w;
        value.q[1] = x;
        value.q[2] = y;
        value.q[3] = z;
        return value;
    }
    inline static FSQuaternion ENG(double w, double x, double y, double z)
    {
        FSQuaternion value = FSQuaternion();
        value.q[0] = w;
        value.q[1] = -x;
        value.q[2] = -y;
        value.q[3] = -z;
        return value;
    }

    FSQuaternion()
    {
        q[0] = 1.;  // w
        q[1] = 0.;  // x
        q[2] = 0.;  // y
        q[3] = 0.;  // z
    }

    FSQuaternion(const double(&_q)[4])
    {
        memcpy(q, _q, sizeof(q));
    }

    void CopyTo(double(&_q)[4]) const
    {
        memcpy(_q, q, sizeof(_q));
    }

    static SPICE_API const FSQuaternion Identity;
};

USTRUCT(BlueprintType)
struct FSEllipse
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSDistanceVector center;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSDistanceVector v_major;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSDistanceVector v_minor;

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
};


USTRUCT(BlueprintType)
struct FSPlane
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSDimensionlessVector normal;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSDistance constant;

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
};


USTRUCT(BlueprintType)
struct FSConicElements
{
    GENERATED_BODY()

    // q
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSDistance PerifocalDistance;
    // e
    UPROPERTY(EditAnywhere, BlueprintReadWrite) double Eccentricity;
    // i
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngle Inclination;
    // node
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngle LongitudeOfAscendingNode;
    // peri
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngle ArgumentOfPeriapse;
    // M
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngle MeanAnomalyAtEpoch;
    // epoch
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSEphemerisTime Epoch;
    // GM
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSMassConstant GravitationalParameter;

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
        elts[2] = Inclination.radians();
        elts[3] = LongitudeOfAscendingNode.radians();
        elts[4] = ArgumentOfPeriapse.radians();
        elts[5] = MeanAnomalyAtEpoch.radians();
        elts[6] = Epoch.seconds;
        elts[7] = GravitationalParameter.GM;
    }
};

USTRUCT(BlueprintType)
struct FSEquinoctialElements
{
    GENERATED_BODY()

    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Meta = (
            ShortToolTip = "semi-major axis"
            ))
    FSDistance a;
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Meta = (
            ShortToolTip = "e*sin(argp+node)"
            ))
    double h;
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Meta = (
            ShortToolTip = "e*cos(argp+node)"
            ))
    double k;
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Meta = (
            ShortToolTip = "mean0+argp+node"
            ))
    FSAngle MeanLongitude;
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Meta = (
            ShortToolTip = "(tan(inc/2)*sin(node))at the specified epoch"
            ))
    double p;
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Meta = (
            ShortToolTip = "(tan(inc/2)*cos(node))at the specified epoch"
            ))
    double q;
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Meta = (
            ShortToolTip = "dargp/dt + dnode/dt (rate is assumed to hold for all time)"
            ))
    FSAngularRate RateOfLongitudeOfPeriapse;
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
        Meta = (
            ShortToolTip = "dm/dt + dargp/dt + dnode/dt (rate is assumed to hold for all time)"
            ))
    FSAngularRate MeanLongitudeDerivative;
    UPROPERTY(
        EditAnywhere,
        BlueprintReadWrite,
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
        elts[3] = MeanLongitude.radians();
        elts[4] = p;
        elts[5] = q;
        elts[6] = RateOfLongitudeOfPeriapse.radiansPerSecond;
        elts[7] = MeanLongitudeDerivative.radiansPerSecond;
        elts[8] = RateOfLongitudeOfAscendingNode.radiansPerSecond;
    }
};

USTRUCT(BlueprintType)
struct FSWindowSegment
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) double start;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) double stop;

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
};


USTRUCT(BlueprintType)
struct FSPointingType2Observation
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSWindowSegment segment;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSQuaternion quat;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngularVelocity avv;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) double rate;

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
};


USTRUCT(BlueprintType)
struct FSPointingType1Observation
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) double sclkdp;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSQuaternion quat;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngularVelocity avv;

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
};


USTRUCT(BlueprintType)
struct FSPointingType5Observation
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) double sclkdp;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSQuaternion quat;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSQuaternion quatderiv;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngularVelocity avv;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSAngularVelocity avvderiv;

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
        memcpy(&_packet[0], &quat.q, sizeof(double[4]));
        memcpy(&_packet[4], &quatderiv.q, sizeof(double[4]));
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
        memcpy(&_packet[0], &quat.q, sizeof(double[4]));
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

        memcpy(&_packet[0], &quat.q, sizeof(double[4]));
        memcpy(&_packet[4], &quatderiv.q, sizeof(double[4]));
        memcpy(&_packet[8], _avv_copy, sizeof(double[3]));
        memcpy(&_packet[11], _avvderiv_copy, sizeof(double[3]));

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

        memcpy(&_packet[0], &quat.q, sizeof(double[4]));
        memcpy(&_packet[4], _avv_copy, sizeof(double[3]));
    }
};


USTRUCT(BlueprintType)
struct FSPKType5Observation
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSEphemerisTime et;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FSStateVector state;

    FSPKType5Observation()
    {
        et = FSEphemerisTime();
        state = FSStateVector();
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
        _et = et.AsDouble();
        state.CopyTo(_state);
    }
};


UCLASS(BlueprintType, Blueprintable)
class SPICE_API USpiceTypes : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    USpiceTypes();
    static const char* UnitsToChar(ES_Units units);
    static const char* _toString(ES_AberrationCorrectionWithNewtonians abcorr);
    static const char* TimeScaleToChar(ES_TimeScale timeScale);

public:
    /// <summary>Converts a distance to a double (kilometers)</summary>
    UFUNCTION(BlueprintPure, 
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "To double (km)",
            ToolTip = "Converts a distance to a double (kilometers)"
            ))
    static double Conv_SDistanceToDouble(
        const FSDistance& value
    );

    /// <summary>Converts a double (kilometers) to a distance</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "From double (km)",
            ToolTip = "Converts a double (kilometers) to a distance"
            ))
    static FSDistance Conv_DoubleToSDistance(
        double value
    );

    /// <summary>Converts a speed to a double (kilometers/sec)</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "to double (km/s)",
            ToolTip = "Converts a speed to a double (kilometers/sec)"
            ))
    static double Conv_SSpeedToDouble(
        const FSSpeed& value
    );

    /// <summary>Converts a double (kilometers/sec) to a speed</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "from double (km/s)",
            ToolTip = "Converts a double (kilometers/sec) to a speed"
            ))
    static FSSpeed Conv_DoubleToSSpeed(
        double value
    );

    /// <summary>Converts a speed to a double (kilometers/sec)</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "to double (radians)",
            ToolTip = "Converts an angle to a double (radians)"
            ))
    static double Conv_SAngleToDouble(
        const FSAngle& value
    );

    /// <summary>Converts a double (kilometers/sec) to a speed</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "from double (radians)",
            ToolTip = "Converts an double (radians) to an angle"
            ))
    static FSAngle Conv_DoubleToSAngle(
        double value
    );

    /// <summary>Converts a speed to a double (kilometers/sec)</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "to double (radians/sec)",
            ToolTip = "Converts an angular rate to a double (radians/sec)"
            ))
    static double Conv_SAngularRateToDouble(
        const FSAngularRate& value
    );

    /// <summary>Converts a double (kilometers/sec) to a speed</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "from double (radians/sec)",
            ToolTip = "Converts a doouble (radians/sec) to an angular rate"
            ))
    static FSAngularRate Conv_DoubleToSAngularRate(
        double value
    );

    /// <summary>Converts an ephemeris time to a double (sec past J2000)</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "to double (sec past J2000)",
            ToolTip = "Converts an ephemeris time to a double (sec past J2000)"
            ))
    static double Conv_SEphemerisTimeToDouble(
        const FSEphemerisTime& value
    );

    /// <summary>Converts a double (sec past J2000) to an ephemeris time</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "from double (sec past J2000)",
            ToolTip = "Converts a double (sec past J2000) to an ephemeris time"
            ))
    static FSEphemerisTime Conv_DoubleToSEphemerisTime(
        double value
    );

    /// <summary>Converts an ephemeris period to a double (sec)</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "to double (sec)",
            ToolTip = "Converts an ephemeris period to a double (sec)"
            ))
    static double Conv_SEphemerisPeriodToDouble(
        const FSEphemerisPeriod& value
    );

    /// <summary>Converts a double (sec) to an ephemeris period</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "from double (sec)",
            ToolTip = "Converts a double (sec) to an ephemeris period"
            ))
    static FSEphemerisPeriod Conv_DoubleToSEphemerisPeriod(
        double value
    );

    /// <summary>Converts a mass constant to a double</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "to double",
            ToolTip = "Converts a mass constant to a double"
            ))
    static double Conv_SMassConstantToDouble(
        const FSMassConstant& value
    );

    /// <summary>Converts a double to a mass constant</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "from double",
            ToolTip = "Converts a double to a mass constant"
            ))
    static FSMassConstant Conv_DoubleToSMassConstant(
        double value
    );

    /// <summary>Converts a velocity vector to a dimensionless vector (km/sec)</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "to dimensionless vector (in km/sec)",
            ToolTip = "Converts a velocity vector to a dimensionless vector (km/sec)"
            ))
        static FSDimensionlessVector Conv_SVelocityVectorToSDimensionlessVector(
            const FSVelocityVector& value
        );

    /// <summary>Converts a dimensionless vector to a velocity vector (km/sec)</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "from dimensionless vector (in km/sec)",
            ToolTip = "Converts a dimensionless vector to a velocity vector (km/sec)"
            ))
        static FSVelocityVector Conv_SDimensionlessVectorToSVelocityVector(
            const FSDimensionlessVector& value
        );

    /// <summary>Converts an euler angle vector (rads) to a dimensionless vector</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            ToolTip = "Converts an euler angle vector (rads) to a dimensionless vector"
            ))
        static FSDimensionlessVector Conv_SEulerAnglesToSDimensionlessVector(
            const FSEulerAngles& value
        );

    /// <summary>Converts a dimensionless vector (rad) to an euler angle vector</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            ToolTip = "Converts a dimensionless vector (rad) to an euler angle vector"
            ))
        static FSEulerAngles Conv_SDimensionlessVectorToSEulerAngles(
            const FSDimensionlessVector& value
        );

    /// <summary>Converts an angular velocity vector to a dimensionless vector (km/sec)</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            ToolTip = "Converts an angular velocity vector to a dimensionless vector (rad/sec)"
            ))
        static FSDimensionlessVector Conv_SAngularVelocityToSDimensionlessVector(
            const FSAngularVelocity& value
        );

    /// <summary>Converts a dimensionless vector (km/sec) to an angular velocity vector</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            ToolTip = "Converts a dimensionless vector (km/sec) to an angular velocity vector"
            ))
        static FSAngularVelocity Conv_SDimensionlessVectorToSAngularVelocity(
            const FSDimensionlessVector& value
        );

    /// <summary>Converts a distance vector to a dimensionless vector (km)</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "to dimensionless vector (in km)",
            ToolTip = "Converts a distance vector to a dimensionless vector (km)"
            ))
        static FSDimensionlessVector Conv_SDistanceVectorToSDimensionlessVector(
            const FSDistanceVector& value
        );

    /// <summary>Converts a dimensionless vector (double precision) to a distance vector</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "from dimensionless vector (in km)",
            ToolTip = "Converts a dimensionless vector (double precision) to a distance vector"
            ))
    static FSDistanceVector Conv_SDimensionlessVectorToSDistanceVector(
        const FSDimensionlessVector& value
    );

    /* Addition (A + B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "time + period", CompactNodeTitle = "+", Keywords = "+ add plus"), Category = "Spice|Math|Time")
    static FSEphemerisTime Add_SEphemerisTimeSEphemerisPeriod(const FSEphemerisTime& A, const FSEphemerisPeriod& B);

    /* Addition (A + B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "period + time", CompactNodeTitle = "+", Keywords = "+ add plus"), Category = "Spice|Math|Time")
    static FSEphemerisTime Add_SEphemerisPeriodSEphemerisTime(const FSEphemerisPeriod& A, const FSEphemerisTime& B);

    /** Returns true if A is greater than B (A > B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "SEphemerisTime > SEphemerisTime", CompactNodeTitle = ">", Keywords = "> greater"), Category = "Spice|Math|DateTime")
    static bool Greater_SEphemerisTimeSEphemerisTime(const FSEphemerisTime& A, const FSEphemerisTime& B);

    /** Returns true if A is less than B (A < B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "SEphemerisTime < SEphemerisTime", CompactNodeTitle = "<", Keywords = "< less"), Category = "Spice|Math|DateTime")
    static bool Less_SEphemerisTimeSEphemerisTime(const FSEphemerisTime& A, const FSEphemerisTime& B);

    /* Addition (A + B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "period + period", CompactNodeTitle = "+", Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true"), Category = "Spice|Math|Time")
    static FSEphemerisPeriod Add_SEphemerisPeriodSEphemerisPeriod(const FSEphemerisPeriod& A, const FSEphemerisPeriod& B);

    /* Subtraction (A - B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "time - time", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "Spice|Math|Time")
    static FSEphemerisPeriod Subtract_SEphemerisTimeSEphemerisTime(const FSEphemerisTime& A, const FSEphemerisTime& B);

    /* Multiplication (A * B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "double * period", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "Spice|Math|Time")
    static FSEphemerisPeriod Multiply_DoubleSEphemerisPeriod(double A, const FSEphemerisPeriod& B);

    /* Multiplication (A * B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "period * double", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "Spice|Math|Time")
    static FSEphemerisPeriod Multiply_SEphemerisPeriodDouble(const FSEphemerisPeriod& A, double B);

    /* Division (A / B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "period / double", CompactNodeTitle = "/", Keywords = "/ divide"), Category = "Spice|Math|Time")
    static FSEphemerisPeriod Divide_SEphemerisPeriodDouble(const FSEphemerisPeriod& A, double B);

    /* Modulo (A % B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "period % (double)", CompactNodeTitle = "%", Keywords = "% modulus"), Category = "Spice|Math|Time")
    static FSEphemerisPeriod Modulus_SEphemerisPeriodDouble(const FSEphemerisPeriod& A, double B);

    //////////////////////
    /* Multiplication (A * B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance * double", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "Spice|Math|Distance")
    static FSDistance Multiply_SDistanceDouble(const FSDistance& A, double B);

    /* Multiplication (A * B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "double * distance", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "Spice|Math|Distance")
    static FSDistance Multiply_DoubleSDistance(double A, const FSDistance& B);

    /* Division (A / B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance / double", CompactNodeTitle = "/", Keywords = "/ divide"), Category = "Spice|Math|Distance")
    static FSDistance Divide_SDistanceDouble(FSDistance A, double B);

    /* Division (A / B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance / distance", CompactNodeTitle = "/", Keywords = "/ divide"), Category = "Spice|Math|Distance")
    static double Divide_SDistanceSDistance(const FSDistance& A, const FSDistance& B);

    /* Subtraction (A - B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance - distance", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "Spice|Math|Distance")
    static FSDistance Subtract_SDistanceSDistance(const FSDistance& A, const FSDistance& B);

    /*  Addition (A + B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance + distance", CompactNodeTitle = "+", Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true"), Category = "Spice|Math|Distance")
    static FSDistance Add_SDistanceSDistance(const FSDistance& A, const FSDistance& B);

    //////////////////////
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance vector * double vector", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "Spice|Math|Distance")
    static FSDistanceVector Multiply_SDistanceVectorDouble(const FSDistanceVector& A, double B);
    
    UFUNCTION(BlueprintPure, meta = (DisplayName = "double vector * distance vector", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "Spice|Math|Distance")
    static FSDistanceVector Multiply_DoubleSDistanceVector(double A, const FSDistanceVector& B);
    
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance - distance", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "Spice|Math|Distance")
    static FSDistanceVector Subtract_DoubleSDistanceVector(const FSDistanceVector& A, const FSDistanceVector& B);
    
    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance vector + distance vector", CompactNodeTitle = "+", Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true"), Category = "Spice|Math|Distance")
    static FSDistanceVector Add_DoubleSDistanceVector(const FSDistanceVector& A, const FSDistanceVector& B);

    UFUNCTION(BlueprintPure, meta = (DisplayName = "distance vector / distance vector", CompactNodeTitle = "/", Keywords = "/ divide"), Category = "Spice|Math|Distance")
    static FSDimensionlessVector Divide_SDistanceVectorSDistanceVector(const FSDistanceVector& A, const FSDistanceVector& B);


    //////////////////////
    /* Multiplication (A * B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "speed * double", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "Spice|Math|Speed")
    static FSSpeed Multiply_SSpeedDouble(const FSSpeed& A, double B);

    /* Multiplication (A * B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "double * speed", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "Spice|Math|Speed")
    static FSSpeed Multiply_DoubleSSpeed(double A, const FSSpeed& B);

    /* Division (A / B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "speed / double", CompactNodeTitle = "/", Keywords = "/ divide"), Category = "Spice|Math|Speed")
    static FSSpeed Divide_SSpeedDouble(FSSpeed A, double B);

    /* Division (A / B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "speed / speed", CompactNodeTitle = "/", Keywords = "/ divide"), Category = "Spice|Math|Speed")
    static double Divide_SSpeedSSpeed(const FSSpeed& A, const FSSpeed& B);

    /* Subtraction (A - B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "speed - speed", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "Spice|Math|Speed")
    static FSSpeed Subtract_SSpeedSSpeed(const FSSpeed& A, const FSSpeed& B);

    /*  Addition (A + B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "speed + speed", CompactNodeTitle = "+", Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true"), Category = "Spice|Math|Speed")
    static FSSpeed Add_SSpeedSSpeed(const FSSpeed& A, const FSSpeed& B);

    //////////////////////
    /* Multiplication (A * B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "velocity * double", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "Spice|Math|Speed")
    static FSVelocityVector Multiply_SVelocityVectorDouble(const FSVelocityVector& A, double B);

    /* Multiplication (A * B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "velocity * velocity", CompactNodeTitle = "*", Keywords = "* multiply"), Category = "Spice|Math|Speed")
    static FSVelocityVector Multiply_DoubleSVelocityVector(double A, const FSVelocityVector& B);

    /* Division (A / B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "velocity / double", CompactNodeTitle = "/", Keywords = "/ divide"), Category = "Spice|Math|Speed")
    static FSVelocityVector Divide_SVelocityVectorDouble(FSVelocityVector A, double B);

    /* Subtraction (A - B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "velocity - velocity", CompactNodeTitle = "-", Keywords = "- subtract minus"), Category = "Spice|Math|Speed")
    static FSVelocityVector Subtract_SVelocityVectorSVelocityVector(const FSVelocityVector& A, const FSVelocityVector& B);

    /*  Addition (A + B) */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "velocity + velocity", CompactNodeTitle = "+", Keywords = "+ add plus", CommutativeAssociativeBinaryOperator = "true"), Category = "Spice|Math|Speed")
    static FSVelocityVector Add_SVelocityVectorSVelocityVector(const FSVelocityVector& A, const FSVelocityVector& B);

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

    template<> static FVector Swizzle<FSDimensionlessVector>(const FSDimensionlessVector& value)
    {
        return FVector(value.y, value.x, value.z);

    }

    template<> static FVector Swizzle<FSDistanceVector>(const FSDistanceVector& value)
    {
        return FVector(value.y.km, value.x.km, value.z.km);
    }

    template<> static FVector Swizzle<FSVelocityVector>(const FSVelocityVector& value)
    {
        return FVector(value.y.kmps, value.x.kmps, value.z.kmps);
    }

    // From UE to SPICE
    template<typename T> static void Swizzle(const FVector& in, T& out);
    
    template<> static void Swizzle<FSDimensionlessVector>(const FVector& in,  FSDimensionlessVector& out)
    {
        out = FSDimensionlessVector(in.Y, in.X, in.Z);
    }

    template<> static void Swizzle<FSDistanceVector>(const FVector& in, FSDistanceVector& out)
    {
        out = FSDistanceVector(in.Y, in.X, in.Z);
    }

    template<> static void Swizzle<FSVelocityVector>(const FVector& in, FSVelocityVector& out)
    {
        out = FSVelocityVector(in.Y, in.X, in.Z);
    }


    // Quaternions...
    // --------------
    // From SPICE to UE
    inline static FQuat Swazzle(const FSQuaternion& value)
    {
        double x=0., y = 0., z = 0., w = 0.;
        value.QENG(w, x, y, z);
        return FQuat(y, x, z, w);
    }

    // From UE to SPICE
    inline static FSQuaternion Swazzle(const FQuat& value)
    {
        return FSQuaternion::ENG(value.W, value.Y, value.X, value.Z);
    }


    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "To UE Vector",
            ToolTip = "Converts a Spice dimensionless vector (double precision, RHS) to a UE Vector (single precision, LHS)"
            ))
        static FVector Conv_SDimensionlessToVector(
            FSDimensionlessVector value
        );

    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "To UE Vector",
            ToolTip = "Converts a Spice distance vector (double precision, RHS) to a UE Vector (km, single precision, LHS)"
            ))
        static FVector Conv_SDistanceVectorToVector(
            const FSDistanceVector& value
        );

    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "To UE Vector",
            ToolTip = "Converts a Spice velocity vector (double precision, RHS) to a UE Vector (kmps, single precision, LHS)"
            ))
        static FVector Conv_SVelocityVectorToVector(
            const FSVelocityVector& value
        );

    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "From UE Vector",
            ToolTip = "Converts a UE Vector (single precision, LHS) to a Spice dimensionless vector (double precision, RHS)"
            ))
        static FSDimensionlessVector Conv_VectorToSDimensionless(
            const FVector& value
        );

    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "From UE Vector",
            ToolTip = "Converts a UE Vector (km, single precision, LHS) to a Spice distance vector (double precision, RHS)"
            ))
        static FSDistanceVector Conv_VectorToSDistanceVector(
            const FVector& value
        );

    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "From UE Vector",
            ToolTip = "Converts a UE Vector (kmps, single precision, LHS) to a Spice velocity vector (double precision, RHS)"
            ))
        static FSVelocityVector Conv_VectorToSVelocityVector(
            const FVector& value
        );


    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "To UE Quat",
            ToolTip = "Converts a Spice quaternion (double precision, RHS) to a UE Quat (single precision, LHS)"
            ))
    static FQuat Conv_SQuaternionToQuat(const FSQuaternion& value);

    /// <summary>Demotes a quaternion to a UE FQuat</summary>
    UFUNCTION(BlueprintPure,
        Category = "Spice|Api|Types",
        meta = (
            BlueprintAutocast,
            CompactNodeTitle = "From UE Quat",
            ToolTip = "Converts a UE Quat (single precision, LHS) to a Spice quaternion (double precision, RHS)"
            ))
    static FSQuaternion Conv_QuatToSQuaternion(const FQuat& value);
};
