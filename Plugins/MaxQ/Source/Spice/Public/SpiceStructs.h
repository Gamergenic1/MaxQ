// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceStructs.h
// 
// API Comments
// 
// SpiceStructs : public CSPICE type to UE type wrappers (Structs)
// 
// Purpose:
// BlueprintType Structs implementations of CSPICE UE-Type wrappers  
//------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "SpicePlatformDefs.h"
#include "SpiceEnums.h"
#include "SpiceStructs.generated.h"

USTRUCT(BlueprintType, Category = "MaxQ|DimensionlessVector")
struct SPICE_API FSDimensionlessVector
{
    GENERATED_BODY()

    // Note *: UNREAL ENGINE SERIALIZATION's impacts on internal representation:
    // note that UE does not support serialization of "plain" arrays.  Only TArray.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double x;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double y;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MaxQ") double z;

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

    inline FSDistance(double _km)
    {
        km = _km;
    }

    // For bodvrd template, basically.
    inline FSDistance(double (&_km)[1])
    {
        km = _km[0];
    }

    inline FSDistance(const FSDistance& other) { km = other.km; }
    inline FSDistance& operator=(const FSDistance& other) { km = other.km; return *this; }


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

    inline explicit operator double() const { return AsSpiceDouble(); }

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

    double f() const;

    FString ToString() const;

    // IMPORTANT!:
    // Swizzles between UE/SPICE (LHS and RHS coordinate systems)
    // You must swizzle positional data (quaternions, vectors, etc) when
    // exchanging between SPICE and Unreal Engine scenegraph coordinates.
    FVector Swizzle() const;
    static FSDistanceVector Swizzle(const FVector& UEVector);

    static const FSDistanceVector Zero;
};


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
    inline explicit operator double() const { return AsSpiceDouble(); }

    inline FSSpeed(const FSSpeed& other) { kmps = other.kmps; }
    inline FSSpeed& operator=(const FSSpeed& other) { kmps = other.kmps; return *this; }

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

    // Supports bodvrd templates, etc
    FSAngle(const double(&__degrees)[1]);


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

    //  Required by templates.  Ambiguous units, so best to avoid (but, they're Radians).
    inline explicit operator double() const { return AsSpiceDouble(); }

    // Supports Bodvrd etc templates
    inline void CopyTo(double (&_degrees)[1]) const
    {
        _degrees[0] = degrees;
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
    inline FSAngularRate(const FSAngularRate& other) { radiansPerSecond = other.radiansPerSecond; }
    inline FSAngularRate& operator=(const FSAngularRate& other) { radiansPerSecond = other.radiansPerSecond; return *this; }

    [[deprecated("Use AsDegreesPerSecond()")]]
    double degreesPerSecond() const { return AsDegreesPerSecond(); }


    [[deprecated("Use AsRadiansPerSecond()")]]
    inline double AsDouble() const { return AsRadiansPerSecond(); }
    /// <summary>Returns value in Radians/Second</summary>
    /// <returns>Radians/Second</returns>
    inline double AsSpiceDouble() const { return radiansPerSecond; }
    inline double AsRadiansPerSecond() const { return radiansPerSecond; }
    double AsDegreesPerSecond() const;

    inline explicit operator double() const { return AsSpiceDouble(); }

    FString ToString() const;

    static inline FSAngularRate FromSpiceDouble(double SpiceDouble) { return FSAngularRate(SpiceDouble); }
    static inline FSAngularRate FromRadiansPerSecond(double RadiansPerSecond) { return FSAngularRate(RadiansPerSecond); }
    static FSAngularRate FromDegreesPerSecond(double DegreesPerSecond);

    static const FSAngularRate Zero;
};


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

    inline FSEphemerisTime(const FSEphemerisTime& other) { seconds = other.seconds; }
    inline FSEphemerisTime& operator=(const FSEphemerisTime& other) { seconds = other.seconds; return *this; }

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

    inline FSEphemerisPeriod(const FSEphemerisPeriod& other) { seconds = other.seconds; }
    inline FSEphemerisPeriod& operator=(const FSEphemerisPeriod& other) { seconds = other.seconds; return *this; }

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

    FSEulerAngles(double _angle3, double _angle2, double _angle1, uint8 _axis3, uint8 _axis2, uint8 _axis1)
    {
        angle3 = _angle3;
        angle2 = _angle2;
        angle1 = _angle1;
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

    // For bodvrd template, basically.
    FSMassConstant(double(&_GM)[1])
    {
        GM = _GM[0];
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

    [[deprecated("Use AsDimensionlessVector()")]]
    FSDimensionlessStateVector AsDimensionlessStateVector() const
    {
        FSDimensionlessStateVector vector;
        AsDimensionlessVectors(vector);
        return vector;
    }

    FSDimensionlessStateVector AsDimensionlessVector() const
    {
        FSDimensionlessStateVector vector;
        AsDimensionlessVectors(vector);
        return vector;
    }

    FString ToString() const;
};


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

    operator FSRotationMatrix() const;
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

    FSConicElements(
        const FSDistance& _PerifocalDistance,
        double _Eccentricity,
        const FSAngle& _Inclination,
        const FSAngle& _LongitudeOfAscendingNode,
        const FSAngle& _ArgumentOfPeriapse,
        const FSAngle& _MeanAnomalyAtEpoch,
        const FSEphemerisTime& _Epoch,
        const FSMassConstant& _GravitationalParameter
        )
    {
        PerifocalDistance = _PerifocalDistance;
        Eccentricity = _Eccentricity;
        Inclination = _Inclination;
        LongitudeOfAscendingNode = _LongitudeOfAscendingNode;
        ArgumentOfPeriapse = _ArgumentOfPeriapse;
        MeanAnomalyAtEpoch = _MeanAnomalyAtEpoch;
        Epoch = _Epoch;
        GravitationalParameter = _GravitationalParameter;
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

