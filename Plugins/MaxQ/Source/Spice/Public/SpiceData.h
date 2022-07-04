// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceData.h
// 
// API Comments
// 
// Purpose:  C++ Data stuff
// (kernel file reading, etc.)
// 
// MaxQ:
// * Base API
// * Refined API
//    * C++
//    * Blueprints
//
// SpiceData.h is part of the "refined C++ API".
//------------------------------------------------------------------------------

#pragma once

#include "SpiceTypes.h"

namespace MaxQ::Data
{
    SPICE_API TArray<FString> EnumerateDirectory(
        const FString& relativeDirectory = TEXT("NonAssetData/kernels"),
        bool ErrorIfNoFilesFound = true,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    );

    SPICE_API bool FurnshDirectory(
        const FString& relativeDirectory = TEXT("NonAssetData/kernels"),
        bool ErrorIfNoFilesFound = true,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    );

     SPICE_API bool Furnsh(
        const FString& relativePath = TEXT("NonAssetData/kernels/naif0012.tls"),
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    );

    SPICE_API bool Furnsh(
        const TArray<FString>& relativePaths,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    );

    SPICE_API bool Unload(
        const FString& relativePath,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    );

    SPICE_API FSEphemerisTime Now();

    // bodvrd
    template<class ValueType>
    SPICE_API void Bodvrd(
        ValueType& Value,
        const FString& bodynm,
        const FString& item,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    );

    template<class ValueType>
    inline void Bodvrd(
        ValueType& Value,
        const FName& bodynm,
        const FName& item,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    )
    {
        Bodvrd<VectorType>(Value, bodynm.ToString(), item.ToString(), ResultCode, ErrorMessage);
    }

    template<class ValueType>
    inline void Bodvrd(
        ValueType& Value,
        const TCHAR* bodynm,
        const TCHAR* item,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr)
    {
        Bodvrd<VectorType>(Value, FString(bodynm), FString(item), ResultCode, ErrorMessage);
    }

    template<class ValueType>
    inline ValueType Bodvrd(
        const FString& bodynm,
        const FString& item,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    )
    {
        ValueType ReturnValue;
        Bodvrd<ValueType>(ReturnValue, bodynm, item, ResultCode, ErrorMessage);
        return ReturnValue;
    }

    template<class ValueType>
    inline ValueType Bodvrd(
        const FName& bodynm,
        const FName& item,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    )
    {
        return Bodvrd<ValueType>(bodynm.ToString(), item.ToString(), ResultCode, ErrorMessage)
    }

    template<class ValueType>
    inline ValueType Bodvrd(
        const TCHAR* bodynm,
        const TCHAR* item,
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr)
    {
        return Bodvrd<ValueType>(FString(bodynm), FString(item), ResultCode, ErrorMessage);
    }

    // bodvcd
    template<class ValueType>
    SPICE_API void Bodvcd(
        ValueType& Value,
        int bodyid = 399,
        const FString& item = TEXT("RADII"),
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    );

    template<class ValueType>
    inline void Bodvcd(
        ValueType& Value,
        int bodyid = 399,
        const FName& item = TEXT("RADII"),
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    )
    {
        Bodvcd<VectorType>(Value, bodyid, item.ToString(), ResultCode, ErrorMessage);
    }

    template<class ValueType>
    inline ValueType Bodvcd(
        int bodyid = 399,
        const FString& item = TEXT("RADII"),
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    )
    {
        ValueType ReturnValue;
        Bodvcd<ValueType>(ReturnValue, bodyid, item, ResultCode, ErrorMessage);
        return ReturnValue;
    }

    template<class ValueType>
    inline ValueType Bodvcd(
        int bodyid = 399,
        const FName& item = "RADII",
        ES_ResultCode* ResultCode = nullptr,
        FString* ErrorMessage = nullptr
    )
    {
        return Bodvcd<ValueType>(bodyid, item.ToString(), ResultCode, ErrorMessage)
    }
    
    SPICE_API bool Bods2c(
        int& code,
        const FString& name = TEXT("EARTH")
    );
    inline bool Bods2c(int& code, FName name = "EARTH") { return Bods2c(code, name.ToString());}
    inline bool Bods2c(int& code, TCHAR* name =TEXT("EARTH")) { return Bods2c(code, FString(name));}

    SPICE_API bool Bodc2n(
        FString& name,
        int code = 399
    );
    inline bool Bodc2n(FName& name, int code = 399)
    {
        FString _name;
        bool result = Bodc2n(_name, code);
        name = FName(_name);
    }

    SPICE_API bool Bodfnd(
        int body,
        const FString& item = TEXT("RADII")
    );
    inline bool Bodfnd(int body=399, FName item = "RADII") { return Bodfnd(body, item.ToString()); }
    inline bool Bodfnd(int body=399, TCHAR* item = TEXT("RADII")) { return Bodfnd(body, FString(item)); }
};