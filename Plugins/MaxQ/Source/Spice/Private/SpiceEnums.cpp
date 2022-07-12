// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceEnums.cpp
// 
// Implementation Comments
// 
// SpiceStructs : public CSPICE type to UE type wrappers (Enums)
// 
// Purpose:
// Purpose:  Blueprint implementations of CSPICE Type wrappers
//------------------------------------------------------------------------------

#include "SpiceEnums.h"

namespace MaxQ::Core
{
    /******************************************************************************************
    *  NOTE:
         See comments in SpiceEnums.h (EnumAsString)
         Yes, we really want to hardcode these ToANSIString's vs pulling values from UE reflection.
    *******************************************************************************************/
    SPICE_API const ANSICHAR* ToANSIString(ES_Units units)
    {
        switch (units)
        {
        case ES_Units::RADIANS:
            return "RADIANS";
        case ES_Units::DEGREES:
            return "DEGREES";
        case ES_Units::ARCMINUTES:
            return "ARCMINUTES";
        case ES_Units::ARCSECONDS:
            return "ARCSECONDS";
        case ES_Units::HOURANGLE:
            return "HOURANGLE";
        case ES_Units::MINUTEANGLE:
            return "MINUTEANGLE";
        case ES_Units::SECONDANGLE:
            return "SECONDANGLE";
        case ES_Units::METERS:
            return "METERS";
        case ES_Units::KILOMETERS:
            return "KILOMETERS";
        case ES_Units::CENTIMETERS:
            return "CENTIMETERS";
        case ES_Units::MILLIMETERS:
            return "MILLIMETERS";
        case ES_Units::FEET:
            return "FEET";
        case ES_Units::INCHES:
            return "INCHES";
        case ES_Units::YARDS:
            return "YARDS";
        case ES_Units::STATUTE_MILES:
            return "STATUTE_MILES";
        case ES_Units::NAUTICAL_MILES:
            return "NAUTICAL_MILES";
        case ES_Units::AU:
            return "AU";
        case ES_Units::PARSECS:
            return "PARSECS";
        case ES_Units::LIGHTSECS:
            return "LIGHTSECS";
        case ES_Units::LIGHTYEARS:
            return "LIGHTYEARS";
        case ES_Units::SECONDS:
            return "SECONDS";
        case ES_Units::MINUTES:
            return "MINUTES";
        case ES_Units::HOURS:
            return "HOURS";
        case ES_Units::DAYS:
            return "DAYS";
        case ES_Units::JULIAN_YEARS:
            return "JULIAN_YEARS";
        case ES_Units::TROPICAL_YEARS:
            return "TROPICAL_YEARS";
        case ES_Units::YEARS:
            return "YEARS";
        }

        return "NONE";
    }

    SPICE_API const ANSICHAR* ToANSIString(ES_ReferenceFrameLocus locus)
    {
        switch (locus)
        {
        case ES_ReferenceFrameLocus::OBSERVER:
            return "OBSERVER";
        case ES_ReferenceFrameLocus::TARGET:
            return "TARGET";
        case ES_ReferenceFrameLocus::CENTER:
            return "CENTER";
        }

        return "NONE";
    }

    SPICE_API const ANSICHAR* ToANSIString(ES_AberrationCorrectionWithNewtonians abcorr)
    {
        switch (abcorr)
        {
        case ES_AberrationCorrectionWithNewtonians::LT:
            return "LT";
        case ES_AberrationCorrectionWithNewtonians::LT_S:
            return "LT+S";
        case ES_AberrationCorrectionWithNewtonians::CN:
            return "CN";
        case ES_AberrationCorrectionWithNewtonians::CN_S:
            return "CN+S";
        }

        return "NONE";
    }


    SPICE_API const ANSICHAR* ToANSIString(ES_AberrationCorrectionFov abcorr)
    {
        switch (abcorr)
        {
        case ES_AberrationCorrectionFov::S:
            return "S";
        case ES_AberrationCorrectionFov::XS:
            return "XS";
        }

        return "NONE";
    }

    SPICE_API const ANSICHAR* ToANSIString(ES_AberrationCorrectionLocus corloc)
    {
        switch (corloc)
        {
        case ES_AberrationCorrectionLocus::CENTER:
            return "CENTER";
        case ES_AberrationCorrectionLocus::ELLIPSOID_LIMB:
            return "ELLIPSOID LIMB";
        }

        return "NONE";
    }


    SPICE_API const ANSICHAR* ToANSIString(ES_AberrationCorrectionLocusTerminator corloc)
    {
        switch (corloc)
        {
        case ES_AberrationCorrectionLocusTerminator::CENTER:
            return "CENTER";
        case ES_AberrationCorrectionLocusTerminator::ELLIPSOID_TERMINATOR:
            return "ELLIPSOID TERMINATOR";
        }

        return "NONE";
    }

    SPICE_API const ANSICHAR* ToANSIString(ES_TimeScale timeScale)
    {
        switch (timeScale)
        {
        case ES_TimeScale::TAI:
            return "TAI";
        case ES_TimeScale::TDB:
            return "TDB";
        case ES_TimeScale::TDT:
            return "TDT";
        case ES_TimeScale::ET:
            return "ET";
        case ES_TimeScale::JDTDB:
            return "JDTDB";
        case ES_TimeScale::JDTDT:
            return "JDTDT";
        case ES_TimeScale::JED:
            return "JED";
        }

        return "NONE";
    }

    SPICE_API const ANSICHAR* ToANSIString(ES_AberrationCorrectionForOccultation abcorr)
    {
        switch (abcorr)
        {
        case ES_AberrationCorrectionForOccultation::LT:
            return "LT";
        case ES_AberrationCorrectionForOccultation::CN:
            return "CN";
        case ES_AberrationCorrectionForOccultation::XLT:
            return "XLT";
        case ES_AberrationCorrectionForOccultation::XCN:
            return "XCN";
        }

        return "NONE";
    }

    SPICE_API const ANSICHAR* ToANSIString(ES_AberrationCorrectionWithTransmissions abcorr)
    {
        switch (abcorr)
        {
        case ES_AberrationCorrectionWithTransmissions::LT:
            return "LT";
        case ES_AberrationCorrectionWithTransmissions::LT_S:
            return "LT+S";
        case ES_AberrationCorrectionWithTransmissions::CN:
            return "CN";
        case ES_AberrationCorrectionWithTransmissions::CN_S:
            return "CN+S";
        case ES_AberrationCorrectionWithTransmissions::XLT:
            return "XLT";
        case ES_AberrationCorrectionWithTransmissions::XLT_S:
            return "XLT+S";
        case ES_AberrationCorrectionWithTransmissions::XCN:
            return "XCN";
        case ES_AberrationCorrectionWithTransmissions::XCN_S:
            return "XCN+S";
        };

        return "NONE";
    }


    SPICE_API const ANSICHAR* ToANSIString(ES_GeometricModel model)
    {

        if (model == ES_GeometricModel::ELLIPSOID)
        {
            return "ELLIPSOID";
        }
        else if (model == ES_GeometricModel::POINT)
        {
            return "POINT";
        }

        return "NONE";
    }


    SPICE_API const ANSICHAR* ToANSIString(ES_OtherGeometricModel model)
    {
        if (model == ES_OtherGeometricModel::SPHERE)
        {
            return "SPHERE";
        }
        else if (model == ES_OtherGeometricModel::POINT)
        {
            return "POINT";
        }

        return "NONE";
    }

    SPICE_API const ANSICHAR* ToANSIString(ES_IlluminationAngleType angleType)
    {
        switch (angleType)
        {
        case ES_IlluminationAngleType::PHASE:
            return "PHASE";
        case ES_IlluminationAngleType::INCIDENCE:
            return "INCIDENCE";
        case ES_IlluminationAngleType::EMISSION:
            return "EMISSION";
        }

        return "NONE";
    }

    SPICE_API FString ToString(ES_GeometricModel model, const TArray<FString>& shapeSurfaces)
    {

        if (model == ES_GeometricModel::ELLIPSOID)
        {
            return FString(TEXT("ELLIPSOID"));
        }
        else if (model == ES_GeometricModel::POINT)
        {
            return FString(TEXT("POINT"));
        }

        // From the docs:
        // "DSK/UNPRIORITIZED[/SURFACES = <surface list>]"
        // Which makes it look like UPRIORITIZED isn't optional or mutually esclusive with a list of surfaces..
        // Is that correct, though?

        FString result = "DSK/UNPRIORITIZED";

        if (shapeSurfaces.Num() > 0)
        {
            result += "/SURFACES = ";

            int num = shapeSurfaces.Num();

            for (int i = 0; i < num; ++i)
            {
                result += shapeSurfaces[i];

                if (i + 1 < num)
                {
                    result += ", ";
                }
            }
        }

        return result;
    }

    SPICE_API const ANSICHAR* ToANSIString(ES_Axis Axis)
    {
        const ANSICHAR* sz = "No_Axis";
        switch (Axis)
        {
        case ES_Axis::X:
            sz = "X_Axis";
            break;
        case ES_Axis::Y:
            sz = "Y_Axis Axis";
            break;
        case ES_Axis::Z:
            sz = "Z_Axis Axis";
            break;
        }

        return sz;
    }

    SPICE_API FString ToString(ES_KernelType KernelType)
    {
        if (((uint8)KernelType & 0x7f) == 0x7f)
        {
            return TEXT("ALL");
        }

        static TStringBuilder<64> sb;

        sb.Reset();

        if ((uint8)KernelType & (uint8)ES_KernelType::SPK)   sb += TEXT(" SPK");
        if ((uint8)KernelType & (uint8)ES_KernelType::CK)    sb += TEXT(" CK");
        if ((uint8)KernelType & (uint8)ES_KernelType::PCK)   sb += TEXT(" PCK");
        if ((uint8)KernelType & (uint8)ES_KernelType::DSK)   sb += TEXT(" DSK");
        if ((uint8)KernelType & (uint8)ES_KernelType::EK)    sb += TEXT(" EK");
        if ((uint8)KernelType & (uint8)ES_KernelType::TEXT)  sb += TEXT(" TEXT");
        if ((uint8)KernelType & (uint8)ES_KernelType::META)  sb += TEXT(" META");

        FString result = sb.ToString();
        result.TrimStartInline();
        return result;
    }

    template<class T>
    SPICE_API T Parse(const FString& Str);

    template<>
    SPICE_API ES_KernelType Parse<ES_KernelType>(const FString& KernelType)
    {
        FString _KernelTypeString = KernelType.TrimStartAndEnd();
        if (!_KernelTypeString.Compare(TEXT("ALL"), ESearchCase::IgnoreCase)) return (ES_KernelType)0x7f;

        static const TMap<FString, ES_KernelType> Flags
        {
            // Verbose guard against brace elision cpp defect
            TMap<FString,ES_KernelType>::ElementType{ TEXT("SPK"), ES_KernelType::SPK },
            TMap<FString,ES_KernelType>::ElementType{ TEXT("CK"), ES_KernelType::CK },
            TMap<FString,ES_KernelType>::ElementType{ TEXT("PCK"), ES_KernelType::PCK },
            TMap<FString,ES_KernelType>::ElementType{ TEXT("DSK"), ES_KernelType::DSK },
            TMap<FString,ES_KernelType>::ElementType{ TEXT("EK"), ES_KernelType::EK },
            TMap<FString,ES_KernelType>::ElementType{ TEXT("TEXT"), ES_KernelType::TEXT },
            TMap<FString,ES_KernelType>::ElementType{ TEXT("META"), ES_KernelType::META }
        };

        ES_KernelType Result = ES_KernelType::NONE;
        // Reverse PCK, because CK is a substring of PCK, and we can't guaranteed map enumeration order
        _KernelTypeString.ReplaceInline(TEXT("PCK"), TEXT("KCP"), ESearchCase::IgnoreCase);

        for (const auto& [TypeText, TypeFlag] : Flags)
        {
            if (_KernelTypeString.ReplaceInline(*TypeText, TEXT(""), ESearchCase::IgnoreCase))
            {
                Result |= TypeFlag;
                if (!_KernelTypeString.Len()) return Result;
            }
        }

        return Result;
    }


    SPICE_API const ANSICHAR* ToANSIString(ES_SubpointComputationMethod method)
    {
        if (method == ES_SubpointComputationMethod::NEAR_POINT_ELLIPSOID)
        {
            return "NEAR POINT/ELLIPSOID";
        }
        else if (method == ES_SubpointComputationMethod::INTERCEPT_ELLIPSOID)
        {
            return "INTERCEPT/ELLIPSOID";
        }

        return "NONE";
    }

    SPICE_API FString ToString(ES_ComputationMethod method, const TArray<FString>& shapeSurfaces)
    {
        if (method == ES_ComputationMethod::NEAR_POINT_ELLIPSOID)
        {
            return FString(TEXT("NEAR POINT/ELLIPSOID"));
        }
        else if (method == ES_ComputationMethod::INTERCEPT_ELLIPSOID)
        {
            return FString(TEXT("INTERCEPT/ELLIPSOID"));
        }

        FString result;

        if (method == ES_ComputationMethod::NADIR_DSK)
        {
            result = FString(TEXT("NADIR/DSK/UNPRIORITIZED"));
        }
        else if (method == ES_ComputationMethod::INTERCEPT_DSK)
        {
            result = FString(TEXT("INTERCEPT/DSK/UNPRIORITIZED"));
        }
        else
        {
            result = "NONE";
        }

        if (shapeSurfaces.Num() > 0)
        {
            result += "/SURFACES = ";

            int num = shapeSurfaces.Num();

            for (int i = 0; i < num; ++i)
            {
                result += shapeSurfaces[i];

                if (i + 1 < num)
                {
                    result += ", ";
                }
            }
        }

        return result;
    }

    SPICE_API FString ToString(ES_LimbComputationMethod method, const TArray<FString>& shapeSurfaces)
    {
        if (method == ES_LimbComputationMethod::TANGENT_ELLIPSOID)
        {
            return FString(TEXT("TANGENT/ELLIPSOID"));
        }
        else if (method == ES_LimbComputationMethod::GUIDED_ELLIPSOID)
        {
            return FString(TEXT("GUIDED/ELLIPSOID"));
        }

        FString result;

        if (method == ES_LimbComputationMethod::TANGENT_DSK)
        {
            result = FString(TEXT("TANGENT/DSK/UNPRIORITIZED"));
        }
        else if (method == ES_LimbComputationMethod::GUIDED_DSK)
        {
            result = FString(TEXT("GUIDED/DSK/UNPRIORITIZED"));
        }
        else
        {
            result = "NONE";
        }

        if (shapeSurfaces.Num() > 0)
        {
            result += "/SURFACES = ";

            int num = shapeSurfaces.Num();

            for (int i = 0; i < num; ++i)
            {
                result += shapeSurfaces[i];

                if (i + 1 < num)
                {
                    result += ", ";
                }
            }
        }

        return result;
    }

    SPICE_API FString ToString(ES_Shadow shadow, ES_CurveType curveType, ES_GeometricModel method, const TArray<FString>& shapeSurfaces)
    {
        FString result = "";

        if (shadow == ES_Shadow::UMBRAL)
        {
            result += FString(TEXT("UMBRAL/"));
        }
        else if (shadow == ES_Shadow::PENUMBRAL)
        {
            result += FString(TEXT("PENUMBRAL/"));
        }

        if (curveType == ES_CurveType::TANGENT)
        {
            result += FString(TEXT("TANGENT/"));
        }
        else if (curveType == ES_CurveType::GUIDED)
        {
            result += FString(TEXT("GUIDED/"));
        }

        if (method == ES_GeometricModel::DSK)
        {
            result += FString(TEXT("DSK/UNPRIORITIZED"));
        }
        else if (method == ES_GeometricModel::ELLIPSOID)
        {
            result += FString(TEXT("ELLIPSOID"));
            return result;
        }
        else if (method == ES_GeometricModel::POINT)
        {
            // Technically, POINT is not not valid in this case.... But:
            // CSPICE validates its inputs perfectly well, we don't have to.
            result += FString(TEXT("POINT"));
            return result;
        }
        else
        {
            result += FString(TEXT("NONE"));
        }

        if (shapeSurfaces.Num() > 0)
        {
            result += "/SURFACES = ";

            int num = shapeSurfaces.Num();

            for (int i = 0; i < num; ++i)
            {
                result += shapeSurfaces[i];

                if (i + 1 < num)
                {
                    result += ", ";
                }
            }
        }

        return result;
    }


    SPICE_API const ANSICHAR* ToANSIString(ES_RelationalOperator relate)
    {
        switch (relate)
        {
        case ES_RelationalOperator::GreaterThan:
            return ">";
            break;
        case ES_RelationalOperator::Equal:
            return "=";
            break;
        case ES_RelationalOperator::LessThan:
            return "<";
            break;
        case ES_RelationalOperator::ABSMAX:
            return "ABSMAX";
            break;
        case ES_RelationalOperator::ABSMIN:
            return "ABSMIN";
            break;
        case ES_RelationalOperator::LOCMAX:
            return "LOCMAX";
            break;
        case ES_RelationalOperator::LOCMIN:
            return "LOCMIN";
            break;
        };

        return "NONE";
    }



    SPICE_API const ANSICHAR* ToANSIString(ES_CoordinateSystemInclRadec coords)
    {
        check((uint8)ES_CoordinateSystem::RECTANGULAR == (uint8)ES_CoordinateSystemInclRadec::RECTANGULAR);
        check((uint8)ES_CoordinateSystem::CYLINDRICAL == (uint8)ES_CoordinateSystemInclRadec::CYLINDRICAL);
        check((uint8)ES_CoordinateSystem::LATITUDINAL == (uint8)ES_CoordinateSystemInclRadec::LATITUDINAL);
        check((uint8)ES_CoordinateSystem::SPHERICAL == (uint8)ES_CoordinateSystemInclRadec::SPHERICAL);
        check((uint8)ES_CoordinateSystem::GEODETIC == (uint8)ES_CoordinateSystemInclRadec::GEODETIC);
        check((uint8)ES_CoordinateSystem::PLANETOGRAPHIC == (uint8)ES_CoordinateSystemInclRadec::PLANETOGRAPHIC);

        switch (coords)
        {
        case ES_CoordinateSystemInclRadec::RECTANGULAR:
            return "RECTANGULAR";
        case ES_CoordinateSystemInclRadec::CYLINDRICAL:
            return "CYLINDRICAL";
        case ES_CoordinateSystemInclRadec::LATITUDINAL:
            return "LATITUDINAL";
        case ES_CoordinateSystemInclRadec::SPHERICAL:
            return "SPHERICAL";
        case ES_CoordinateSystemInclRadec::GEODETIC:
            return "GEODETIC";
        case ES_CoordinateSystemInclRadec::PLANETOGRAPHIC:
            return "PLANETOGRAPHIC";
        case ES_CoordinateSystemInclRadec::RADEC:
            return "RA/DEC";
        };

        return "NONE";
    }


    SPICE_API const ANSICHAR* ToANSIString(ES_CoordinateSystem coords)
    {
        return ToANSIString((ES_CoordinateSystemInclRadec)coords);
    }

    SPICE_API const ANSICHAR* ToANSIString(ES_CoordinateName coord)
    {
        switch (coord)
        {
        case ES_CoordinateName::X:
            return "X";
        case ES_CoordinateName::Y:
            return "Y";
        case ES_CoordinateName::Z:
            return "Z";
        case ES_CoordinateName::RADIUS:
            return "RADIUS";
        case ES_CoordinateName::LONGITUDE:
            return "LONGITUDE";
        case ES_CoordinateName::LATITUDE:
            return "LATITUDE";
        case ES_CoordinateName::RANGE:
            return "RANGE";
        case ES_CoordinateName::RIGHT_ASCENSION:
            return "RIGHT ASCENSION";
        case ES_CoordinateName::DECLINATION:
            return "DECLINATION";
        case ES_CoordinateName::COLATITUDE:
            return "COLATITUDE";
        case ES_CoordinateName::ALTITUDE:
            return "ALTITUDE";
        };

        return "NONE";
    }
}