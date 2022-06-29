// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "K2Conversion.h"
#include "SpiceK2.h"

SPICEUNCOOKED_API FK2Conversion FK2Conversion::None() {
    FK2Conversion none = FK2Conversion(FName(), FK2Type(), FK2Type());
    return none;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::DoubleToSMassConstant(){
    FK2Conversion doubletosmassconstant = FK2Conversion(USpiceK2::Conv_DoubleToSMassConstant, FK2Type::Double(), FK2Type::SMassConstant());
    return doubletosmassconstant;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::DegreesToSAngle() {
    FK2Conversion degreestosangle = FK2Conversion(USpiceK2::Conv_DegreesToSAngle, FK2Type::Double(), FK2Type::SAngle());
    return degreestosangle;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::DoubleToSDistance() {
    FK2Conversion doubletosdistance = FK2Conversion(USpiceK2::Conv_DoubleToSDistance, FK2Type::Double(), FK2Type::SDistance());
    return doubletosdistance;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::DoubleToSSpeed() {
    FK2Conversion doubletosspeed = FK2Conversion(USpiceK2::Conv_DoubleToSSpeed, FK2Type::Double(), FK2Type::SSpeed());
    return doubletosspeed;
}


SPICEUNCOOKED_API FK2Conversion FK2Conversion::DoubleToSAngularRate() {
    FK2Conversion doubletosangularrate= FK2Conversion(USpiceK2::Conv_DoubleToSAngularRate, FK2Type::Double(), FK2Type::SAngularRate());
    return doubletosangularrate;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::SDimensionlessVectorToSDistanceVector() {
    FK2Conversion sdimensionlessvectortodistancevector = FK2Conversion(USpiceK2::Conv_SDimensionlessVectorToSDistanceVector, FK2Type::SDimensionlessVector(), FK2Type::SDistanceVector());
    return sdimensionlessvectortodistancevector;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::SDimensionlessVectorToSVelocityVector() {
    FK2Conversion sdimensionlessvectortovelocityvector = FK2Conversion(USpiceK2::Conv_SDimensionlessVectorToSVelocityVector, FK2Type::SDimensionlessVector(), FK2Type::SVelocityVector());
    return sdimensionlessvectortovelocityvector;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::SDimensionlessVectorToSAngularVelocity()
{
    FK2Conversion sdimensionlessvectortoangularvelocity = FK2Conversion(USpiceK2::Conv_SDimensionlessVectorToSAngularVelocity, FK2Type::SDimensionlessVector(), FK2Type::SAngularVelocity());
    return sdimensionlessvectortoangularvelocity;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::SDistanceVectorToSDimensionlessVector()
{
    FK2Conversion sdimensionlessvectortovelocityvector = FK2Conversion(USpiceK2::Conv_SDistanceVectorToSDimensionlessVector, FK2Type::SDistanceVector(), FK2Type::SDimensionlessVector());
    return sdimensionlessvectortovelocityvector;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::SVelocityVectorToSDimensionlessVector()
{
    FK2Conversion sdimensionlessvectortovelocityvector = FK2Conversion(USpiceK2::Conv_SVelocityVectorToSDimensionlessVector, FK2Type::SVelocityVector(), FK2Type::SDimensionlessVector());
    return sdimensionlessvectortovelocityvector;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::SAngularVelocityToSDimensionlessVector()
{
    FK2Conversion sdimensionlessvectortoangularvelocity = FK2Conversion(USpiceK2::Conv_SAngularVelocityToSDimensionlessVector, FK2Type::SAngularVelocity(), FK2Type::SDimensionlessVector());
    return sdimensionlessvectortoangularvelocity;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::SStateVectorToSDimensionlessStateVector()
{
    FK2Conversion sdimensionlessvectortovelocityvector = FK2Conversion(USpiceK2::Conv_SStateVectorToSDimensionlessStateVector, FK2Type::SStateVector(), FK2Type::SDimensionlessStateVector());
    return sdimensionlessvectortovelocityvector;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::SDimensionlessStateVectorToSStateVector() {
    FK2Conversion sdimensionlessvectortovelocityvector = FK2Conversion(USpiceK2::Conv_SDimensionlessStateVectorToSStateVector, FK2Type::SDimensionlessStateVector(), FK2Type::SStateVector());
    return sdimensionlessvectortovelocityvector;
}


SPICEUNCOOKED_API FK2Conversion FK2Conversion::SDimensionlessVectorXToSDistance() {
    FK2Conversion sdimensionlessvectorxtodistance = FK2Conversion(USpiceK2::Conv_SDimensionlessVector_X_ToSDistance, FK2Type::SDimensionlessVector(), FK2Type::SDistance(), EK2_ComponentSelector::X);
    return sdimensionlessvectorxtodistance;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::SDimensionlessVectorYToSDistance() {
    FK2Conversion sdimensionlessvectorytodistance = FK2Conversion(USpiceK2::Conv_SDimensionlessVector_Y_ToSDistance, FK2Type::SDimensionlessVector(), FK2Type::SDistance(), EK2_ComponentSelector::Y);
    return sdimensionlessvectorytodistance;
}

SPICEUNCOOKED_API FK2Conversion FK2Conversion::SDimensionlessVectorZToSDistance() {
    FK2Conversion sdimensionlessvectorztodistance = FK2Conversion(USpiceK2::Conv_SDimensionlessVector_Z_ToSDistance, FK2Type::SDimensionlessVector(), FK2Type::SDistance(), EK2_ComponentSelector::Z);
    return sdimensionlessvectorztodistance;
}

