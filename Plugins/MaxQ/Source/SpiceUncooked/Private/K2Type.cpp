// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "K2Type.h"


const FK2Type& FK2Type::Wildcard()
{
    static FK2Type Wildcard = FK2Type(FName("Wildcard"), UEdGraphSchema_K2::PC_Wildcard);
    return Wildcard;
}

const FK2Type& FK2Type::Double()
{
    static FK2Type Double = FK2Type(FName("Double"), UEdGraphSchema_K2::PC_Double);
    return Double;
}

const FK2Type& FK2Type::Real()
{
    static FK2Type Real = FK2Type(FName("Real"), UEdGraphSchema_K2::PC_Real);
    return Real;
}

const FK2Type& FK2Type::DoubleArray()
{
    static FK2Type ArrayDouble = FK2Type(FName("Array(Double)"), UEdGraphSchema_K2::PC_Double, EPinContainerType::Array);
    return ArrayDouble;
}

const FK2Type& FK2Type::RealArray()
{
    static FK2Type ArrayDouble = FK2Type(FName("Array(Real)"), UEdGraphSchema_K2::PC_Real, EPinContainerType::Array);
    return ArrayDouble;
}

const FK2Type& FK2Type::SDimensionlessVector()
{
    static FK2Type DimensionlessVector = FK2Type(FSDimensionlessVector::StaticStruct());
    return DimensionlessVector;
}

const FK2Type& FK2Type::SMassConstant()
{
    static FK2Type MassConstant = FK2Type(FSMassConstant::StaticStruct());
    return MassConstant;
}

const FK2Type& FK2Type::SDistance()
{
    static FK2Type Distance = FK2Type(FSDistance::StaticStruct());
    return Distance;
}

const FK2Type& FK2Type::SSpeed()
{
    static FK2Type Speed = FK2Type(FSSpeed::StaticStruct());
    return Speed;
}

const FK2Type& FK2Type::SAngularRate()
{
    static FK2Type AngularRate = FK2Type(FSAngularRate::StaticStruct());
    return AngularRate;
}

const FK2Type& FK2Type::SAngle()
{
    static FK2Type Angle = FK2Type(FSAngle::StaticStruct());
    return Angle;
}

const FK2Type& FK2Type::SDistanceVector()
{
    static FK2Type DistanceVector = FK2Type(FSDistanceVector::StaticStruct());
    return DistanceVector;
}

const FK2Type& FK2Type::SVelocityVector()
{
    static FK2Type VelocityVector = FK2Type(FSVelocityVector::StaticStruct());
    return VelocityVector;
}

const FK2Type& FK2Type::SAngularVelocity()
{
    static FK2Type AngularVelocity = FK2Type(FSAngularVelocity::StaticStruct());
    return AngularVelocity;
}

const FK2Type& FK2Type::SStateVector()
{
    static FK2Type StateVector = FK2Type(FSStateVector::StaticStruct());
    return StateVector;
}

const FK2Type& FK2Type::SDimensionlessStateVector()
{
    static FK2Type DimensionlessStateVector = FK2Type(FSDimensionlessStateVector::StaticStruct());

    return DimensionlessStateVector;
}

const FK2Type& FK2Type::SStateTransform()
{
    static FK2Type StateTransform = FK2Type(FSStateTransform::StaticStruct());
    return StateTransform;
}

const FK2Type& FK2Type::SRotationMatrix()
{
    static FK2Type RotationMatrix = FK2Type(FSRotationMatrix::StaticStruct());
    return RotationMatrix;
}



TArray<FString> FK2Type::GetTypePinLabels(const UScriptStruct* WhatType)
{
    TArray<FString> PinLabels;

    if (WhatType)
    {
        uint8* DefaultOfType = (uint8*)alloca(WhatType->GetStructureSize());
        WhatType->InitializeDefaultValue(DefaultOfType);

        RecurseGetTypePinLabels(WhatType, DefaultOfType, FString(TEXT("")), PinLabels);
    }

    return PinLabels;
}


void FK2Type::RecurseGetTypePinLabels(const UScriptStruct* WhatType, const void* MemberOfType, const FString& BaseLabel, TArray<FString>& PinLabels)
{
    if (WhatType)
    {
        for (TPropertyValueIterator<FStructProperty> StructIter(WhatType, MemberOfType, EPropertyValueIteratorFlags::NoRecursion); StructIter; ++StructIter)
        {
            FString NewBaseOfLabel = BaseLabel + FString(TEXT(" ")) + StructIter.Key()->GetName();
            RecurseGetTypePinLabels(StructIter.Key()->Struct, StructIter.Value(), NewBaseOfLabel, PinLabels);
        }

        for (TPropertyValueIterator<FDoubleProperty> DoubleIter(WhatType, MemberOfType, EPropertyValueIteratorFlags::NoRecursion); DoubleIter; ++DoubleIter)
        {
            PinLabels.Add(BaseLabel + FString(TEXT(" ")) + DoubleIter.Key()->GetName());
        }
    }
}