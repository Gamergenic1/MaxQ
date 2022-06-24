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

UCLASS(Category = "MaxQ")
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
    static constexpr ANSICHAR* bodvrd_double{ "bodvrd_double_K2" };

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static FSDimensionlessVector bodvrd_vector_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& bodynm,
        const FString& item
    );
    static constexpr ANSICHAR* bodvrd_vector{ "bodvrd_vector_K2" };

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static TArray<double> bodvrd_array_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& bodynm,
        const FString& item
    );
    static constexpr ANSICHAR* bodvrd_array{ "bodvrd_array_K2" };

    // bodvcd support
    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static double bodvcd_double_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        int bodyid,
        const FString& item
    );
    static constexpr ANSICHAR* bodvcd_double{ "bodvcd_double_K2" };

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static FSDimensionlessVector bodvcd_vector_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        int bodyid,
        const FString& item
    );
    static constexpr ANSICHAR* bodvcd_vector{ "bodvcd_vector_K2" };

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static TArray<double> bodvcd_array_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        int bodyid,
        const FString& item
    );
    static constexpr ANSICHAR* bodvcd_array{ "bodvcd_array_K2" };

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static double gdpool_double_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& name
    );
    static constexpr ANSICHAR* gdpool_double{ "gdpool_double_K2" };

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static FSDimensionlessVector gdpool_vector_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& name
    );
    static constexpr ANSICHAR* gdpool_vector{ "gdpool_vector_K2" };

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static TArray<double> gdpool_array_K2(
        ES_ResultCode& ResultCode,
        FString& ErrorMessage,
        const FString& name,
        int start = 0
    );
    static constexpr ANSICHAR* gdpool_array{ "gdpool_array_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSRotationMatrix mtxm_matrix_K2(
        const FSRotationMatrix& m1,
        const FSRotationMatrix& m2
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSStateTransform mtxm_state_transform_K2(
        const FSStateTransform& m1,
        const FSStateTransform& m2
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector mtxv_vector_K2(
        const FSRotationMatrix& m,
        const FSDimensionlessVector& v
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessStateVector mtxv_state_vector_K2(
        const FSStateTransform& m,
        const FSDimensionlessStateVector& v
    );


    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSRotationMatrix mxm_matrix_K2(
        const FSRotationMatrix& m1,
        const FSRotationMatrix& m2
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSStateTransform mxm_state_transform_K2(
        const FSStateTransform& m1,
        const FSStateTransform& m2
    );


    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSRotationMatrix mxmt_matrix_K2(
        const FSRotationMatrix& m1,
        const FSRotationMatrix& m2
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSStateTransform mxmt_state_transform_K2(
        const FSStateTransform& m1,
        const FSStateTransform& m2
    );


    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector mxv_vector_K2(
        const FSRotationMatrix& m,
        const FSDimensionlessVector& v
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessStateVector mxv_state_vector_K2(
        const FSStateTransform& m,
        const FSDimensionlessStateVector& v
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector qderiv_vector_K2(
        const FSDimensionlessVector& f0,
        const FSDimensionlessVector& f2,
        double delta
    );
        
    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static FSRotationMatrix twovec_vector_K2(
        ES_ResultCode& ResultCode, FString& ErrorMessage,
        ES_Axis axis1,
        const FSDimensionlessVector& v1,
        ES_Axis axis2,
        const FSDimensionlessVector& v2
    );
    
    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "MaxQ|Internal", meta = (ExpandEnumAsExecs = "ResultCode"))
    static FSStateTransform twovxf_state_vector_K2(
        ES_ResultCode& ResultCode, FString& ErrorMessage,
        ES_Axis axis1,
        const FSDimensionlessStateVector& v1,
        ES_Axis axis2,
        const FSDimensionlessStateVector& v2
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector ucrss_vector_K2(
        const FSDimensionlessVector& v1,
        const FSDimensionlessVector& v2
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static void unorm_vector_K2(
        const FSDimensionlessVector& v1,
        FSDimensionlessVector& vout,
        double& vmag
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector vadd_vector_K2(
        const FSDimensionlessVector& v1,
        const FSDimensionlessVector& v2
    );
    // #Todo:  Convert explicitly settings this to walking meta data?
    //        It's used for initialization purposes 
    static constexpr TCHAR* vadd_vector{ TEXT("vadd_vector_K2") };
    static constexpr TCHAR* vadd_input1{ TEXT("v1") };
    static constexpr TCHAR* vadd_input2{ TEXT("v2") };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessStateVector vadd_state_vector_K2(
        const FSDimensionlessStateVector& v1,
        const FSDimensionlessStateVector& v2
    );
    static constexpr TCHAR* vadd_state_vector{ TEXT("vadd_state_vector_K2") };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector vcrss_vector_K2(
        const FSDimensionlessVector& v1,
        const FSDimensionlessVector& v2
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static double vdist_vector_K2(
        const FSDimensionlessVector& v1,
        const FSDimensionlessVector& v2
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static double vdot_vector_K2(
        const FSDimensionlessVector& v1,
        const FSDimensionlessVector& v2
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector vequ_vector_K2(
        const FSDimensionlessVector& v
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector vhat_vector_K2(
        const FSDimensionlessVector& v1
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector vlcom_vector_K2(
        double a,
        const FSDimensionlessVector& v1,
        double b,
        const FSDimensionlessVector& v2
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector vlcom3_vector_K2(
        double a,
        const FSDimensionlessVector& v1,
        double b,
        const FSDimensionlessVector& v2,
        double c,
        const FSDimensionlessVector& v3
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector vminus_vector_K2(
        const FSDimensionlessVector& v
    );
    static constexpr ANSICHAR* vminus_vector{ "vminus_vector_K2" };
    static constexpr ANSICHAR* vminus_in{ "v" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessStateVector vminus_state_vector_K2(
        const FSDimensionlessStateVector& v
    );
    static constexpr ANSICHAR* vminus_state_vector{ "vminus_state_vector_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static double vnorm_vector_K2(
        const FSDimensionlessVector& v1
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector vpack_vector_K2(
        double x,
        double y,
        double z
    );
    static constexpr ANSICHAR* vpack_vector{ "vpack_vector_K2" };
    static constexpr ANSICHAR* vpack_inputs[] { "x", "y", "z", "dx", "dy", "dz" };
    static constexpr int32 vpack_inputs_n = sizeof(vpack_inputs)/sizeof(vpack_inputs[0]);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessStateVector vpack_state_vector_K2(
        double x,
        double y,
        double z,
        double dx,
        double dy,
        double dz
    );
    static constexpr ANSICHAR* vpack_state_vector{ "vpack_state_vector_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector vperp_vector_K2(
        const FSDimensionlessVector& a,
        const FSDimensionlessVector& b
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector vprjp_vector_K2(
        const FSDimensionlessVector& vin,
        const FSPlane& plane
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector vproj_vector_K2(
        const FSDimensionlessVector& a,
        const FSDimensionlessVector& b
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector vscl_vector_K2(
        double s,
        const FSDimensionlessVector& v1
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSAngle vsep_vector_K2(
        const FSDimensionlessVector& v1,
        const FSDimensionlessVector& v2
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector vsub_vector_K2(
        const FSDimensionlessVector& v1,
        const FSDimensionlessVector& v2
    );
    static constexpr TCHAR* vsub_vector{ TEXT("vsub_vector_K2") };
    static constexpr TCHAR* vsub_input1{ TEXT("v1") };
    static constexpr TCHAR* vsub_input2{ TEXT("v2") };


    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessStateVector vsub_state_vector_K2(
        const FSDimensionlessStateVector& v1,
        const FSDimensionlessStateVector& v2
    );
    static constexpr TCHAR* vsub_state_vector{ TEXT("vsub_state_vector_K2") };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static void vupack_vector_K2(
        const FSDimensionlessVector& v,
        double& x,
        double& y,
        double& z
    );
    static constexpr ANSICHAR* vupack_vector{ "vupack_vector_K2" };
    static constexpr ANSICHAR* vupack_input{ "v" };
    static constexpr ANSICHAR* vupack_outputs[]{ "x", "y", "z", "dx", "dy", "dz" };
    static constexpr int32 vupack_outputs_n = sizeof(vpack_inputs) / sizeof(vpack_inputs[0]);

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static void vupack_state_vector_K2(
        const FSDimensionlessStateVector& v,
        double& x,
        double& y,
        double& z,
        double& dx,
        double& dy,
        double& dz
    );
    static constexpr ANSICHAR* vupack_state_vector{ "vupack_state_vector_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static double vtmv_vector_K2(
        const FSDimensionlessVector& v1,
        const FSRotationMatrix& matrix,
        const FSDimensionlessVector& v2
        );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static double vtmv_state_vector_K2(
        const FSDimensionlessStateVector& v1,
        const FSStateTransform& matrix,
        const FSDimensionlessStateVector& v2
        );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static bool vzero_vector_K2(
        const FSDimensionlessVector& v
    );
    
    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static bool vzero_state_vector_K2(
        const FSDimensionlessStateVector& v
    );

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
        static double vrel_vector_K2(
        const FSDimensionlessVector& v1,
        const FSDimensionlessVector& v2
    );

    // output converters
    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSEphemerisTime Conv_DoubleToSEphemerisTime_K2(double value);
    static constexpr ANSICHAR* Conv_DoubleToSEphemerisTime{ "Conv_DoubleToSEphemerisTime_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSEphemerisPeriod Conv_DoubleToSEphemerisPeriod_K2(double value);
    static constexpr ANSICHAR* Conv_DoubleToSEphemerisPeriod{ "Conv_DoubleToSEphemerisPeriod_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSMassConstant Conv_DoubleToSMassConstant_K2(double value);
    static constexpr ANSICHAR* Conv_DoubleToSMassConstant{ "Conv_DoubleToSMassConstant_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDistance Conv_DoubleToSDistance_K2(double value);
    static constexpr ANSICHAR* Conv_DoubleToSDistance{ "Conv_DoubleToSDistance_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSAngle Conv_DegreesToSAngle_K2(double value);
    static constexpr ANSICHAR* Conv_DegreesToSAngle{ "Conv_DegreesToSAngle_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSAngle Conv_RadiansToSAngle_K2(double value);
    static constexpr ANSICHAR* Conv_RadiansToSAngle{ "Conv_RadiansToSAngle_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSAngularRate Conv_DegreesPersecondToSAngularRate_K2(double value);
    static constexpr ANSICHAR* Conv_DegreesPersecondToSAngularRate{ "Conv_DegreesPersecondToSAngularRate_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSAngularRate Conv_RadiansPersecondToSAngularRate_K2(double value);
    static constexpr ANSICHAR* Conv_RadiansPersecondToSAngularRate{ "Conv_RadiansPersecondToSAngularRate_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSAngularRate Conv_MinutesPerTurnToSAngularRate_K2(double value);
    static constexpr ANSICHAR* Conv_MinutesPerTurnToSAngularRate{ "Conv_MinutesPerTurnToSAngularRate_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDistanceVector Conv_SDimensionlessVectorToSDistanceVector_K2(const FSDimensionlessVector& value);
    static constexpr ANSICHAR* Conv_SDimensionlessVectorToSDistanceVector{ "Conv_SDimensionlessVectorToSDistanceVector_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSVelocityVector Conv_SDimensionlessVectorToSVelocityVector_K2(const FSDimensionlessVector& value);
    static constexpr ANSICHAR* Conv_SDimensionlessVectorToSVelocityVector{ "Conv_SDimensionlessVectorToSVelocityVector_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSAngularVelocity Conv_SDimensionlessVectorToSAngularVelocity_K2(const FSDimensionlessVector& value);
    static constexpr ANSICHAR* Conv_SDimensionlessVectorToSAngularVelocity{ "Conv_SDimensionlessVectorToSAngularVelocity_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector Conv_SDistanceVectorToSDimensionlessVector_K2(const FSDistanceVector& value);
    static constexpr ANSICHAR* Conv_SDistanceVectorToSDimensionlessVector{ "Conv_SDistanceVectorToSDimensionlessVector_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector Conv_SVelocityVectorToSDimensionlessVector_K2(const FSVelocityVector& value);
    static constexpr ANSICHAR* Conv_SVelocityVectorToSDimensionlessVector{ "Conv_SVelocityVectorToSDimensionlessVector_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessVector Conv_SAngularVelocityToSDimensionlessVector_K2(const FSAngularVelocity& value);
    static constexpr ANSICHAR* Conv_SAngularVelocityToSDimensionlessVector{ "Conv_SAngularVelocityToSDimensionlessVector_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSStateVector Conv_SDimensionlessStateVectorToSStateVector_K2(const FSDimensionlessStateVector& value);
    static constexpr ANSICHAR* Conv_SDimensionlessStateVectorToSStateVector{ "Conv_SDimensionlessStateVectorToSStateVector_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDimensionlessStateVector Conv_SStateVectorToSDimensionlessStateVector_K2(const FSStateVector& value);
    static constexpr ANSICHAR* Conv_SStateVectorToSDimensionlessStateVector{ "Conv_SStateVectorToSDimensionlessStateVector_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDistance Conv_SDimensionlessVector_X_ToSDistance_K2(const FSDimensionlessVector& value);
    static constexpr ANSICHAR* Conv_SDimensionlessVector_X_ToSDistance{ "Conv_SDimensionlessVector_X_ToSDistance_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDistance Conv_SDimensionlessVector_Y_ToSDistance_K2(const FSDimensionlessVector& value);
    static constexpr ANSICHAR* Conv_SDimensionlessVector_Y_ToSDistance{ "Conv_SDimensionlessVector_Y_ToSDistance_K2" };

    UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "MaxQ|Internal")
    static FSDistance Conv_SDimensionlessVector_Z_ToSDistance_K2(const FSDimensionlessVector& value);
    static constexpr ANSICHAR* Conv_SDimensionlessVector_Z_ToSDistance{ "Conv_SDimensionlessVector_Z_ToSDistance_K2" };

    static constexpr TCHAR* conv_input{ TEXT("value") };
};
