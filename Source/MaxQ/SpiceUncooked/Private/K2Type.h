// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "EdGraphSchema_K2.h"
#include "SpiceTypes.h"
#include "K2Type.generated.h"

USTRUCT()
struct FK2Type
{
    GENERATED_BODY()

    UPROPERTY() FName TypeName;
    UPROPERTY() FName Category;
    UPROPERTY() UScriptStruct* SubCategoryObject;
    UPROPERTY() EPinContainerType Container;

    FK2Type()
    {
        TypeName = FName("");
        Category = FName("");
        SubCategoryObject = nullptr;
        Container = EPinContainerType::None;
    }

    FK2Type(
        UScriptStruct* _type
    )
    {
        TypeName = _type->GetFName();
        Category = UEdGraphSchema_K2::PC_Struct;
        SubCategoryObject = _type;
        Container = EPinContainerType::None;
    }

    FK2Type(
        FName _typename,
        FName _category,
        EPinContainerType _container = EPinContainerType::None
    )
    {
        TypeName = _typename;
        Category = _category;
        SubCategoryObject = nullptr;
        Container = _container;
    }

    FK2Type(const FK2Type& other)
    {
        TypeName = other.TypeName;
        Category = other.Category;
        SubCategoryObject = other.SubCategoryObject;
        Container = other.Container;
    }

    FK2Type& FK2Type::operator= (const FK2Type& other)
    {
        // self-assignment guard
        if (this == &other)
            return *this;

        // do the copy
        TypeName = other.TypeName;
        Category = other.Category;
        SubCategoryObject = other.SubCategoryObject;
        Container = other.Container;

        // return the existing object so we can chain this operator
        return *this;
    }
    

    bool Matches(FName otherCategory, UObject* otherSubCategory, EPinContainerType otherContainer)
    {
        if (otherCategory == UEdGraphSchema_K2::PC_Struct)
        {
            if (SubCategoryObject != nullptr && otherSubCategory != nullptr)
                return otherSubCategory->GetFName() == SubCategoryObject->GetFName() && otherContainer == Container;
            else
                return false;
        }
        return otherCategory == Category && otherContainer == Container;
    }

    bool Matches(FEdGraphPinType pinType)
    {
        return Matches(pinType.PinCategory, Cast<UObject>(pinType.PinSubCategoryObject), pinType.ContainerType);
    }

    static SPICEUNCOOKED_API FK2Type Wildcard();
    static SPICEUNCOOKED_API FK2Type Double();
    static SPICEUNCOOKED_API FK2Type DoubleArray();
    static SPICEUNCOOKED_API FK2Type SDimensionlessVector();
    static SPICEUNCOOKED_API FK2Type SMassConstant();
    static SPICEUNCOOKED_API FK2Type SDistance();
    static SPICEUNCOOKED_API FK2Type SAngle();
    static SPICEUNCOOKED_API FK2Type SDistanceVector();
    static SPICEUNCOOKED_API FK2Type SVelocityVector();
};