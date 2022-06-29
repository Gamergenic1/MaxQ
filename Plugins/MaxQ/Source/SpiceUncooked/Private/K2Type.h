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

#define LOCTEXT_NAMESPACE "FK2Type"

USTRUCT()
struct SPICEUNCOOKED_API FK2Type
{
    GENERATED_BODY()

    UPROPERTY() FName TypeName;
    UPROPERTY() FName Category;
    UPROPERTY() TWeakObjectPtr<UScriptStruct> SubCategoryObject;
    UPROPERTY() EPinContainerType Container;

    FK2Type()
    {
        TypeName = { FName() };
        Category = { FName() };
        SubCategoryObject = { nullptr };
        Container = { EPinContainerType::None };
    }

    FK2Type(
        UScriptStruct* _type
    )
    {
        TypeName = { _type->GetFName() };
        Category = { UEdGraphSchema_K2::PC_Struct };
        SubCategoryObject = { _type };
        Container = { EPinContainerType::None };
    }

    FK2Type(
        FName _typename,
        FName _category,
        EPinContainerType _container = EPinContainerType::None
    )
    {
        TypeName = { _typename };
        Category = { _category };
        SubCategoryObject = { nullptr };
        Container = { _container };
    }

    FK2Type(const FK2Type& other)
    {
        TypeName = { other.TypeName };
        Category = { other.Category };
        SubCategoryObject = { other.SubCategoryObject };
        Container = { other.Container };
    }

    FK2Type& operator= (const FK2Type& other)
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

    bool operator== (const FK2Type& other) const
    {
        // self-equality
        if (this == &other)
            return true;

        bool equal = TypeName.Compare(other.TypeName) == 0;

#if WITH_EDITOR
        if (equal)
        {
            check(Category == other.Category);
            check(Container == other.Container);

            if (Category == UEdGraphSchema_K2::PC_Struct)
            {
                bool bSubCategoryOkay = (SubCategoryObject.Get() != nullptr) && (other.SubCategoryObject.Get() != nullptr);
                if (bSubCategoryOkay)
                {
                    bSubCategoryOkay |= SubCategoryObject.Get()->IsChildOf(other.SubCategoryObject.Get());
                }
                check(bSubCategoryOkay);
            }
        }
#endif

        // return the existing object so we can chain this operator
        return equal;
    }
    

    bool Matches(FName otherCategory, const UObject* otherSubCategory, EPinContainerType otherContainer) const
    {
        if(otherCategory == UEdGraphSchema_K2::PC_Wildcard) return true;

        if (otherCategory == UEdGraphSchema_K2::PC_Struct)
        {
            if (SubCategoryObject.Get() != nullptr && otherSubCategory != nullptr)
                return otherSubCategory->GetFName() == SubCategoryObject.Get()->GetFName() && otherContainer == Container;
            else
                return false;
        }
        return otherCategory == Category && otherContainer == Container;
    }

    bool Matches(const FEdGraphPinType& pinType) const
    {
        return Matches(pinType.PinCategory, Cast<UObject>(pinType.PinSubCategoryObject), pinType.ContainerType);
    }

    bool Is(FName otherCategory, const UObject* otherSubCategory, EPinContainerType otherContainer) const
    {
        if (otherCategory == UEdGraphSchema_K2::PC_Struct)
        {
            if (SubCategoryObject.Get() != nullptr && otherSubCategory != nullptr)
                return otherSubCategory->GetFName() == SubCategoryObject.Get()->GetFName() && otherContainer == Container;
            else
                return false;
        }
        return otherCategory == Category && otherContainer == Container;
    }

    bool Is(const FEdGraphPinType& pinType) const
    {
        return Is(pinType.PinCategory, Cast<UObject>(pinType.PinSubCategoryObject), pinType.ContainerType);
    }

    FString GetDisplayNameString() const
    {
        if(SubCategoryObject.Get()) return SubCategoryObject->GetName();
        if (TypeName.IsNone()) return TEXT("Wildcard");
        return TypeName.ToString();
    }

    FText GetDisplayNameText() const
    {
        if (SubCategoryObject.Get()) return SubCategoryObject->GetDisplayNameText();
        if (TypeName.IsNone()) return LOCTEXT("Wildcard", "Wildcard");
        return FText::FromName(TypeName);
    }

    static const FK2Type& Wildcard();
    static const FK2Type& Double();
    static const FK2Type& Real();
    static const FK2Type& DoubleArray();
    static const FK2Type& RealArray();
    static const FK2Type& SDimensionlessVector();
    static const FK2Type& SMassConstant();
    static const FK2Type& SDistance();
    static const FK2Type& SAngle();
    static const FK2Type& SSpeed();
    static const FK2Type& SAngularRate();
    static const FK2Type& SDistanceVector();
    static const FK2Type& SVelocityVector();
    static const FK2Type& SAngularVelocity();
    static const FK2Type& SStateVector();
    static const FK2Type& SDimensionlessStateVector();

    static TArray<FString> GetTypePinLabels(const UScriptStruct* WhatType);

private:
    static void RecurseGetTypePinLabels(const UScriptStruct* WhatType, const void* MemberOfType, const FString& BaseLabel, TArray<FString>& PinLabels);
};

#undef LOCTEXT_NAMESPACE