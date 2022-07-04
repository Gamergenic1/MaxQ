// Copyright 2021 Gamergenic.  See full copyright notice in SpiceK2.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceConstants.cpp
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

#include "SpiceConstants.h"

namespace MaxQ::Constants
{
    const FString J2000{ Literal::J2000 };
    const FString ECLIPJ2000{ Literal::ECLIPJ2000 };
    const FString MARSIAU{ Literal::MARSIAU };
    const FString GALACTIC{ Literal::GALACTIC };
    const FString IAU_EARTH{ Literal::IAU_EARTH };
    const FString EARTH_FIXED{ Literal::EARTH_FIXED };
    const FString ITRF93{ Literal::ITRF93 };
    const FString IAU_MOON{ Literal::IAU_MOON };
    const FString IAU_SUN{ Literal::IAU_SUN };
    const FString IAU_MERCURY{ Literal::IAU_MERCURY };
    const FString IAU_VENUS{ Literal::IAU_VENUS };
    const FString IAU_MARS{ Literal::IAU_MARS };
    const FString IAU_DEIMOS{ Literal::IAU_DEIMOS };
    const FString IAU_PHOBOS{ Literal::IAU_PHOBOS };
    const FString IAU_JUPITER{ Literal::IAU_JUPITER };
    const FString IAU_SATURN{ Literal::IAU_SATURN };
    const FString IAU_NEPTUNE{ Literal::IAU_NEPTUNE };
    const FString IAU_URANUS{ Literal::IAU_URANUS };
    const FString IAU_PLUTO{ Literal::IAU_PLUTO };
    const FString IAU_CERES{ Literal::IAU_CERES };
    const FString EARTH{ Literal::EARTH };
    const FString MOON{ Literal::MOON };
    const FString EMB{ Literal::EMB };
    const FString EARTH_BARYCENTER{ Literal::EARTH_BARYCENTER };
    const FString SUN{ Literal::SUN };
    const FString SSB{ Literal::SSB };
    const FString SOLAR_SYSTEM_BARYCENTER{ Literal::SOLAR_SYSTEM_BARYCENTER };
    const FString MERCURY{ Literal::MERCURY };
    const FString VENUS{ Literal::VENUS };
    const FString MARS{ Literal::MARS };
    const FString PHOBOS{ Literal::PHOBOS };
    const FString DEIMOS{ Literal::DEIMOS };
    const FString MARS_BARYCENTER{ Literal::MARS_BARYCENTER };
    const FString JUPITER{ Literal::JUPITER };;
    const FString JUPITER_BARYCENTER{ Literal::JUPITER_BARYCENTER };
    const FString SATURN{ Literal::SATURN };
    const FString SATURN_BARYCENTER{ Literal::SATURN_BARYCENTER };
    const FString URANUS{ Literal::URANUS };
    const FString URANUS_BARYCENTER{ Literal::URANUS_BARYCENTER };
    const FString NEPTUNE{ Literal::NEPTUNE };
    const FString NEPTUNE_BARYCENTER{ Literal::NEPTUNE_BARYCENTER };
    const FString PLUTO{ Literal::PLUTO };
    const FString PLUTO_BARYCENTER{ Literal::PLUTO_BARYCENTER };
    const FString CERES{ Literal::CERES };
    const FString PIONEER_6{ Literal::PIONEER_6 };
    const FString PIONEER_7{ Literal::PIONEER_7 };
    const FString VIKING_1_ORBITER{ Literal::VIKING_1_ORBITER };
    const FString VIKING_2_ORBITER{ Literal::VIKING_2_ORBITER };
    const FString VOYAGER_1{ Literal::VOYAGER_1 };
    const FString VOYAGER_2{ Literal::VOYAGER_2 };
    const FString HST{ Literal::HST };
    const FString HUBBLE_SPACE_TELESCOPE{ Literal::HUBBLE_SPACE_TELESCOPE };
    const FString MARS_PATHFINDER{ Literal::MARS_PATHFINDER };
    const FString PARKER_SOLAR_PROBE{ Literal::PARKER_SOLAR_PROBE };
    const FString JWST{ Literal::JWST };
    const FString JAMES_WEBB_SPACE_TELESCOPE{ Literal::JAMES_WEBB_SPACE_TELESCOPE };
    const FString INSIGHT{ Literal::INSIGHT };
    const FString OPPORTUNITY{ Literal::OPPORTUNITY };
    const FString SPIRIT{ Literal::SPIRIT };
    const FString NOTO{ Literal::NOTO };
    const FString NEW_NORCIA{ Literal::NEW_NORCIA };
    const FString GOLDSTONE{ Literal::GOLDSTONE };
    const FString CANBERRA{ Literal::CANBERRA };
    const FString MADRID{ Literal::MADRID };
    const FString USUDA{ Literal::USUDA };
    const FString DSS_05{ Literal::DSS_05 };
    const FString PARKES{ Literal::PARKES };
    const FString GM{ Literal::GM };
    const FString RADII{ Literal::RADII };

    const FName Name_J2000{ Literal::J2000 };
    const FName Name_ECLIPJ2000{ Literal::ECLIPJ2000 };
    const FName Name_MARSIAU{ Literal::MARSIAU };
    const FName Name_GALACTIC{ Literal::GALACTIC };
    const FName Name_IAU_EARTH{ Literal::IAU_EARTH };
    const FName Name_EARTH_FIXED{ Literal::EARTH_FIXED };
    const FName Name_ITRF93{ Literal::ITRF93 };
    const FName Name_IAU_MOON{ Literal::IAU_MOON };
    const FName Name_IAU_SUN{ Literal::IAU_SUN };
    const FName Name_IAU_MERCURY{ Literal::IAU_MERCURY };
    const FName Name_IAU_VENUS{ Literal::IAU_VENUS };
    const FName Name_IAU_MARS{ Literal::IAU_MARS };
    const FName Name_IAU_DEIMOS{ Literal::IAU_DEIMOS };
    const FName Name_IAU_PHOBOS{ Literal::IAU_PHOBOS };
    const FName Name_IAU_JUPITER{ Literal::IAU_JUPITER };
    const FName Name_IAU_SATURN{ Literal::IAU_SATURN };
    const FName Name_IAU_NEPTUNE{ Literal::IAU_NEPTUNE };
    const FName Name_IAU_URANUS{ Literal::IAU_URANUS };
    const FName Name_IAU_PLUTO{ Literal::IAU_PLUTO };
    const FName Name_IAU_CERES{ Literal::IAU_CERES };
    const FName Name_EARTH{ Literal::EARTH };
    const FName Name_MOON{ Literal::MOON };
    const FName Name_EMB{ Literal::EMB };
    const FName Name_EARTH_BARYCENTER{ Literal::EARTH_BARYCENTER };
    const FName Name_SUN{ Literal::SUN };
    const FName Name_SSB{ Literal::SSB };
    const FName Name_SOLAR_SYSTEM_BARYCENTER{ Literal::SOLAR_SYSTEM_BARYCENTER };
    const FName Name_MERCURY{ Literal::MERCURY };
    const FName Name_VENUS{ Literal::VENUS };
    const FName Name_MARS{ Literal::MARS };
    const FName Name_PHOBOS{ Literal::PHOBOS };
    const FName Name_DEIMOS{ Literal::DEIMOS };
    const FName Name_MARS_BARYCENTER{ Literal::MARS_BARYCENTER };
    const FName Name_JUPITER{ Literal::JUPITER };
    const FName Name_JUPITER_BARYCENTER{ Literal::JUPITER_BARYCENTER };
    const FName Name_SATURN{ Literal::SATURN };
    const FName Name_SATURN_BARYCENTER{ Literal::SATURN_BARYCENTER };
    const FName Name_URANUS{ Literal::URANUS };
    const FName Name_URANUS_BARYCENTER{ Literal::URANUS_BARYCENTER };
    const FName Name_NEPTUNE{ Literal::NEPTUNE };
    const FName Name_NEPTUNE_BARYCENTER{ Literal::NEPTUNE_BARYCENTER };
    const FName Name_PLUTO{ Literal::PLUTO };
    const FName Name_PLUTO_BARYCENTER{ Literal::PLUTO_BARYCENTER };
    const FName Name_CERES{ Literal::CERES };
    const FName Name_PIONEER_6{ Literal::PIONEER_6 };
    const FName Name_PIONEER_7{ Literal::PIONEER_7 };
    const FName Name_VIKING_1_ORBITER{ Literal::VIKING_1_ORBITER };
    const FName Name_VIKING_2_ORBITER{ Literal::VIKING_2_ORBITER };
    const FName Name_VOYAGER_1{ Literal::VOYAGER_1 };
    const FName Name_VOYAGER_2{ Literal::VOYAGER_2 };
    const FName Name_HST{ Literal::HST };
    const FName Name_HUBBLE_SPACE_TELESCOPE{ Literal::HUBBLE_SPACE_TELESCOPE };
    const FName Name_MARS_PATHFINDER{ Literal::MARS_PATHFINDER };
    const FName Name_PARKER_SOLAR_PROBE{ Literal::PARKER_SOLAR_PROBE };
    const FName Name_JWST{ Literal::JWST };
    const FName Name_JAMES_WEBB_SPACE_TELESCOPE{ Literal::JAMES_WEBB_SPACE_TELESCOPE };
    const FName Name_INSIGHT{ Literal::INSIGHT };
    const FName Name_OPPORTUNITY{ Literal::OPPORTUNITY };
    const FName Name_SPIRIT{ Literal::SPIRIT };
    const FName Name_NOTO{ Literal::NOTO };
    const FName Name_NEW_NORCIA{ Literal::NEW_NORCIA };
    const FName Name_GOLDSTONE{ Literal::GOLDSTONE };
    const FName Name_CANBERRA{ Literal::CANBERRA };
    const FName Name_MADRID{ Literal::MADRID };
    const FName Name_USUDA{ Literal::USUDA };
    const FName Name_DSS_05{ Literal::DSS_05 };
    const FName Name_PARKES{ Literal::PARKES };
    const FName Name_GM{ Literal::GM };
    const FName Name_RADII{ Literal::RADII };
}

#pragma endregion NaifNames
