// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceConstants.h
// 
// API Comments
// 
// Purpose:  Constants for things like reference frame names, etc.
//
// SpiceConstants.h is part of the "refined C++ API".
//------------------------------------------------------------------------------

#pragma once

#pragma region NaifFNames
namespace MaxQ::Constants
{
    namespace Literal
    {
        constexpr TCHAR J2000[]{ TEXT("J2000") };
        constexpr TCHAR ECLIPJ2000[]{ TEXT("ECLIPJ2000") };
        constexpr TCHAR MARSIAU[]{ TEXT("MARSIAU") };
        constexpr TCHAR GALACTIC[]{ TEXT("GALACTIC") };
        constexpr TCHAR IAU_EARTH[]{ TEXT("IAU_EARTH") };
        constexpr TCHAR EARTH_FIXED[]{ TEXT("EARTH_FIXED") };
        constexpr TCHAR ITRF93[]{ TEXT("ITRF93") };
        constexpr TCHAR IAU_MOON[]{ TEXT("IAU_MOON") };
        constexpr TCHAR IAU_SUN[]{ TEXT("IAU_SUN") };
        constexpr TCHAR IAU_MERCURY[]{ TEXT("IAU_MERCURY") };
        constexpr TCHAR IAU_VENUS[]{ TEXT("IAU_VENUS") };
        constexpr TCHAR IAU_MARS[]{ TEXT("IAU_MARS") };
        constexpr TCHAR IAU_DEIMOS[]{ TEXT("IAU_DEIMOS") };
        constexpr TCHAR IAU_PHOBOS[]{ TEXT("IAU_PHOBOS") };
        constexpr TCHAR IAU_JUPITER[]{ TEXT("IAU_JUPITER") };
        constexpr TCHAR IAU_SATURN[]{ TEXT("IAU_SATURN") };
        constexpr TCHAR IAU_NEPTUNE[]{ TEXT("IAU_NEPTUNE") };
        constexpr TCHAR IAU_URANUS[]{ TEXT("IAU_URANUS") };
        constexpr TCHAR IAU_PLUTO[]{ TEXT("IAU_PLUTO") };
        constexpr TCHAR IAU_CERES[]{ TEXT("IAU_CERES") };
        constexpr TCHAR EARTH[]{ TEXT("EARTH") };
        constexpr TCHAR MOON[]{ TEXT("MOON") };
        constexpr TCHAR EMB[]{ TEXT("EMB") };
        constexpr TCHAR EARTH_BARYCENTER[]{ TEXT("EARTH_BARYCENTER") };
        constexpr TCHAR SUN[]{ TEXT("SUN") };
        constexpr TCHAR SSB[]{ TEXT("SSB") };
        constexpr TCHAR SOLAR_SYSTEM_BARYCENTER[]{ TEXT("SOLAR_SYSTEM_BARYCENTER") };
        constexpr TCHAR MERCURY[]{ TEXT("MERCURY") };
        constexpr TCHAR VENUS[]{ TEXT("VENUS") };
        constexpr TCHAR MARS[]{ TEXT("MARS") };
        constexpr TCHAR PHOBOS[]{ TEXT("PHOBOS") };
        constexpr TCHAR DEIMOS[]{ TEXT("DEIMOS") };
        constexpr TCHAR MARS_BARYCENTER[]{ TEXT("MARS_BARYCENTER") };
        constexpr TCHAR JUPITER[]{ TEXT("JUPITER") };
        constexpr TCHAR JUPITER_BARYCENTER[]{ TEXT("JUPITER_BARYCENTER") };
        constexpr TCHAR SATURN[]{ TEXT("SATURN") };
        constexpr TCHAR SATURN_BARYCENTER[]{ TEXT("SATURN_BARYCENTER") };
        constexpr TCHAR URANUS[]{ TEXT("URANUS") };
        constexpr TCHAR URANUS_BARYCENTER[]{ TEXT("URANUS_BARYCENTER") };
        constexpr TCHAR NEPTUNE[]{ TEXT("NEPTUNE") };
        constexpr TCHAR NEPTUNE_BARYCENTER[]{ TEXT("NEPTUNE_BARYCENTER") };
        constexpr TCHAR PLUTO[]{ TEXT("PLUTO") };
        constexpr TCHAR PLUTO_BARYCENTER[]{ TEXT("PLUTO_BARYCENTER") };
        constexpr TCHAR CERES[]{ TEXT("CERES") };
        constexpr TCHAR PIONEER_6[]{ TEXT("PIONEER-6") };
        constexpr TCHAR PIONEER_7[]{ TEXT("PIONEER-7") };
        constexpr TCHAR VIKING_1_ORBITER[]{ TEXT("VIKING 1 ORBITER") };
        constexpr TCHAR VIKING_2_ORBITER[]{ TEXT("VIKING 2 ORBITER") };
        constexpr TCHAR VOYAGER_1[]{ TEXT("VOYAGER 1") };
        constexpr TCHAR VOYAGER_2[]{ TEXT("VOYAGER 2") };
        constexpr TCHAR HST[]{ TEXT("HST") };
        constexpr TCHAR HUBBLE_SPACE_TELESCOPE[]{ TEXT("HUBBLE SPACE TELESCOPE") };
        constexpr TCHAR MARS_PATHFINDER[]{ TEXT("MARS PATHFINDER") };
        constexpr TCHAR PARKER_SOLAR_PROBE[]{ TEXT("PARKER SOLAR PROBE") };
        constexpr TCHAR JWST[]{ TEXT("JWST") };
        constexpr TCHAR JAMES_WEBB_SPACE_TELESCOPE[]{ TEXT("JAMES WEBB SPACE TELESCOPE") };
        constexpr TCHAR INSIGHT[]{ TEXT("INSIGHT") };
        constexpr TCHAR OPPORTUNITY[]{ TEXT("OPPORTUNITY") };
        constexpr TCHAR SPIRIT[]{ TEXT("SPIRIT") };
        constexpr TCHAR NOTO[]{ TEXT("NOTO") };
        constexpr TCHAR NEW_NORCIA[]{ TEXT("NEW NORCIA") };
        constexpr TCHAR GOLDSTONE[]{ TEXT("GOLDSTONE") };
        constexpr TCHAR CANBERRA[]{ TEXT("CANBERRA") };
        constexpr TCHAR MADRID[]{ TEXT("MADRID") };
        constexpr TCHAR USUDA[]{ TEXT("USUDA") };
        constexpr TCHAR DSS_05[]{ TEXT("DSS-05") };
        constexpr TCHAR PARKES[]{ TEXT("PARKES") };
        constexpr TCHAR GM[]{ TEXT("GM") };
        constexpr TCHAR RADII[]{ TEXT("RADII") };
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