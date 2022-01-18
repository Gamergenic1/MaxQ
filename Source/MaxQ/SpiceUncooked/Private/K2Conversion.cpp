// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Implementation of:
// "Adding Third-Party Libraries to Unreal Engine : NASA's SPICE Toolkit"
// https://gamedevtricks.com/post/third-party-libs-1/

#pragma once

#include "K2Conversion.h"

SPICEUNCOOKED_API FK2Conversion FK2Conversion::None() {
    FK2Conversion none = FK2Conversion(FName(""), FK2Type(), FK2Type());
    return none;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::DoubleToSMassConstant(){
    FK2Conversion doubletosmassconstant = FK2Conversion(FName("Conv_DoubleToSMassConstant_K2"), FK2Type::Double(), FK2Type::SMassConstant());
    return doubletosmassconstant;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::DegreesToSAngle() {
    FK2Conversion degreestosangle = FK2Conversion(FName("Conv_DegreesToSAngle_K2"), FK2Type::Double(), FK2Type::SAngle());
    return degreestosangle;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::DoubleToSDistance() {
    FK2Conversion doubletosdistance = FK2Conversion(FName("Conv_DoubleToSDistance_K2"), FK2Type::Double(), FK2Type::SDistance());
    return doubletosdistance;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::SDimensionlessVectorToSDistanceVector() {
    FK2Conversion sdimensionlessvectortodistancevector = FK2Conversion(FName("Conv_SDimensionlessVectorToSDistanceVector_K2"), FK2Type::SDimensionlessVector(), FK2Type::SDistanceVector());
    return sdimensionlessvectortodistancevector;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::SDimensionlessVectorToSVelocityVector() {
    FK2Conversion sdimensionlessvectortovelocityvector = FK2Conversion(FName("Conv_SDimensionlessVectorToSVelocityVector_K2"), FK2Type::SDimensionlessVector(), FK2Type::SVelocityVector());
    return sdimensionlessvectortovelocityvector;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::SDimensionlessVectorXToSDistance() {
    FK2Conversion sdimensionlessvectorxtodistance = FK2Conversion(FName("Conv_SDimensionlessVector_X_ToSDistance_K2"), FK2Type::SDimensionlessVector(), FK2Type::SDistance(), EK2_ComponentSelector::X);
    return sdimensionlessvectorxtodistance;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::SDimensionlessVectorYToSDistance() {
    FK2Conversion sdimensionlessvectorytodistance = FK2Conversion(FName("Conv_SDimensionlessVector_Y_ToSDistance_K2"), FK2Type::SDimensionlessVector(), FK2Type::SDistance(), EK2_ComponentSelector::Y);
    return sdimensionlessvectorytodistance;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::SDimensionlessVectorZToSDistance() {
    FK2Conversion sdimensionlessvectorztodistance = FK2Conversion(FName("Conv_SDimensionlessVector_Z_ToSDistance_K2"), FK2Type::SDimensionlessVector(), FK2Type::SDistance(), EK2_ComponentSelector::Z);
    return sdimensionlessvectorztodistance;
}

