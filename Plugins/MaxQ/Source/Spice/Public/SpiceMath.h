// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "SpiceTypes.h"

namespace MaxQ::Math
{
    // Conversions from physical types to/from dimensionless types
    template<class VectorType, class DimensionlessType>
    inline VectorType Conv_FromDimensionlessType(const DimensionlessType& v) { return { v }; }

    template<>
    inline FSDimensionlessVector Conv_FromDimensionlessType(const FSDimensionlessVector& v) { return v; }

    template<>
    inline FSDimensionlessStateVector Conv_FromDimensionlessType(const FSDimensionlessStateVector& v) { return v; }

    template<class VectorType, class DimensionlessType>
    inline DimensionlessType Conv_AsDimensionlessType(const VectorType& v) { return v.AsDimensionlessVector(); }

    template<>
    inline FSDimensionlessVector Conv_AsDimensionlessType(const FSDimensionlessVector& v) { return v; }

    template<>
    inline FSDimensionlessStateVector Conv_AsDimensionlessType(const FSDimensionlessStateVector& v) { return v; }

    // bodvrd
    template<class ValueType>
    SPICE_API void bodvrd(
        ValueType& Value,
        const FString& bodynm,
        const FString& item,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    );

    template<class ValueType>
    SPICE_API void bodvrd(
        ValueType& Value,
        const FName& bodynm,
        const FName& item,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    );

    template<class ValueType>
    inline void bodvrd(
        ValueType& Value,
        const TCHAR* bodynm,
        const TCHAR* item,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr)
    {
        bodvrd<VectorType>(Value, FString(bodynm), FString(item), ResultCode, ErrorMessage);
    }

    template<class ValueType>
    inline ValueType bodvrd(
        const FString& bodynm,
        const FString& item,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    )
    {
        ValueType ReturnValue;
        bodvrd<ValueType>(ReturnValue, bodynm, item, ResultCode, ErrorMessage);
        return ReturnValue;
    }

    template<class ValueType>
    inline ValueType bodvrd(
        const FName& bodynm,
        const FName& item,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    )
    {
        ValueType ReturnValue;
        bodvrd<ValueType>(ReturnValue, bodynm, item, ResultCode, ErrorMessage);
        return ReturnValue;
    }


    template<class ValueType>
    inline ValueType bodvrd(
        const TCHAR* bodynm,
        const TCHAR* item,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr)
    {
        return bodvrd<ValueType>(FString(bodynm), FString(item), ResultCode, ErrorMessage);
    }

    // m * v
    template<class VectorType>
    SPICE_API void MxV(const FSRotationMatrix& m, const VectorType& v, VectorType& vout);

    template<class VectorType>
    inline VectorType MxV(const FSRotationMatrix& m, const VectorType& v)
    {
        VectorType vout;
        MxV(m, v, vout);
        return vout;
    }

    template<class VectorType>
    SPICE_API void MxV(const FSStateTransform& m, const VectorType& v, VectorType& vout);

    template<class VectorType>
    inline VectorType MxV(const FSStateTransform& m, const VectorType& v)
    {
        VectorType vout;
        MxV(m, v, vout);
        return vout;
    }

    // m_transpose * v
    template<class VectorType>
    SPICE_API void MTxV(const FSRotationMatrix& m, const VectorType& v, VectorType& vout);

    template<class VectorType>
    inline VectorType MTxV(const FSRotationMatrix& m, const VectorType& v)
    {
        VectorType vout;
        MTxV(m, v, vout);
        return vout;
    }

    template<class VectorType>
    SPICE_API void MTxV(const FSStateTransform& m, const VectorType& v, VectorType& vout);

    template<class VectorType>
    inline VectorType MTxV(const FSStateTransform& m, const VectorType& v)
    {
        VectorType vout;
        MTxV(m, v, vout);
        return vout;
    }

    // m * m
    SPICE_API void MxM(const FSRotationMatrix& m1, const FSRotationMatrix& m2, FSRotationMatrix& mout);
    SPICE_API FSRotationMatrix MxM(const FSRotationMatrix& m1, const FSRotationMatrix& m2);
    SPICE_API void MxM(const FSStateTransform& m1, const FSStateTransform& m2, FSStateTransform& mout);
    SPICE_API FSStateTransform MxM(const FSStateTransform& m1, const FSStateTransform& m2);
    
    // m_transpose * m
    SPICE_API void MTxM(const FSRotationMatrix& m1, const FSRotationMatrix& m2, FSRotationMatrix& mout);
    SPICE_API FSRotationMatrix MTxM(const FSRotationMatrix& m1, const FSRotationMatrix& m2);
    SPICE_API void MTxM(const FSStateTransform& m1, const FSStateTransform& m2, FSStateTransform& mout);
    SPICE_API FSStateTransform MTxM(const FSStateTransform& m1, const FSStateTransform& m2);
    
    // m * m_transpose
    SPICE_API void MxMT(const FSRotationMatrix& m1, const FSRotationMatrix& m2, FSRotationMatrix& mout);
    SPICE_API FSRotationMatrix MxMT(const FSRotationMatrix& m1, const FSRotationMatrix& m2);
    SPICE_API void MxMT(const FSStateTransform& m1, const FSStateTransform& m2, FSStateTransform& mout);
    SPICE_API FSStateTransform MxMT(const FSStateTransform& m1, const FSStateTransform& m2);


    // addition
    template<class VectorType>
    SPICE_API void Vadd(const VectorType& v1, const VectorType& v2, VectorType& vsum);

    template<class VectorType>
    inline VectorType Vadd(const VectorType& v1, const VectorType& v2)
    {
        VectorType vsum;
        Vadd(v1, v2, vsum);
        return vsum;
    }

    // subtraction
    template<class VectorType>
    SPICE_API void Vsub(const VectorType& v1, const VectorType& v2, VectorType& vdifference);

    template<class VectorType>
    inline VectorType Vsub(const VectorType& v1, const VectorType& v2)
    {
        VectorType vdifference;
        Vsub(v1, v2, vdifference);
        return vdifference;
    }

    // negation
    template<class VectorType>
    SPICE_API void Vminus(const VectorType& v, VectorType& vminus);

    template<class VectorType>
    inline VectorType Vminus(const VectorType& v)
    {
        VectorType vminus;
        Vminus(v, vminus);
        return vminus;
    }
};