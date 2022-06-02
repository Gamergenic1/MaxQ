// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com|https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpiceTypes.h"
#include "SpiceK2.generated.h"

UCLASS(BlueprintType, Blueprintable)
class SPICE_API USpiceK2 : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    // bodvrd support
    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static double bodvrd_double_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& bodynm,
        const FString& item
    );

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static FSDimensionlessVector bodvrd_vector_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& bodynm,
        const FString& item
    );

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static TArray<double> bodvrd_array_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& bodynm,
        const FString& item
    );

    // bodvcd support
    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static double bodvcd_double_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        int bodyid,
        const FString& item
    );

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static FSDimensionlessVector bodvcd_vector_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        int bodyid,
        const FString& item
    );

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static TArray<double> bodvcd_array_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        int bodyid,
        const FString& item
    );

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static double gdpool_double_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& name
    );

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static FSDimensionlessVector gdpool_vector_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& name
    );

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static TArray<double> gdpool_array_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& name,
        int start = 0
    );

    // output converters
    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSEphemerisTime Conv_DoubleToSEphemerisTime_K2(double value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSEphemerisPeriod Conv_DoubleToSEphemerisPeriod_K2(double value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSMassConstant Conv_DoubleToSMassConstant_K2(double value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDistance Conv_DoubleToSDistance_K2(double value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSAngle Conv_DegreesToSAngle_K2(double value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSAngle Conv_RadiansToSAngle_K2(double value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSAngularRate Conv_DegreesPersecondToSAngularRate_K2(double value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSAngularRate Conv_RadiansPersecondToSAngularRate_K2(double value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSAngularRate Conv_MinutesPerTurnToSAngularRate_K2(double value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDistanceVector Conv_SDimensionlessVectorToSDistanceVector_K2(const FSDimensionlessVector& value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSVelocityVector Conv_SDimensionlessVectorToSVelocityVector_K2(const FSDimensionlessVector& value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDistance Conv_SDimensionlessVector_X_ToSDistance_K2(const FSDimensionlessVector& value);
    
    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDistance Conv_SDimensionlessVector_Y_ToSDistance_K2(const FSDimensionlessVector& value);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDistance Conv_SDimensionlessVector_Z_ToSDistance_K2(const FSDimensionlessVector& value);
};
