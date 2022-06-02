// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "Tutorial01Actor.h"
#include "Components/SceneComponent.h"
#include "Engine/Engine.h"
#include "Spice.h"
#include "SpiceK2.h"

// Tutorial01 - Initialization and kernel data
// (see comments in TutorialActor.h)
ATutorial01Actor::ATutorial01Actor()
{
    SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
}

void ATutorial01Actor::BeginPlay()
{
    InitializeSpice();

    LoadGMKernel();
    
    EnumeratePCKKernels();
    
    EnumerateAndLoadPCKKernelList();

    QueryEarthsGM();

    QueryEarthsRadius();
}


// Demonstrate how to initialize the SPICE module
void ATutorial01Actor::InitializeSpice()
{
    // init_all:  clears kernel memory and any error state.
    // Before your app starts it should initialize the USpice library.
    // Do this once, before you load kernel files.
    USpice::init_all();

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::White, TEXT("InitializeSpice initialized spice (init_all)"));
    }
}

// Demonstrate how to load one kernel data file
bool ATutorial01Actor::LoadGMKernel(bool Squawk)
{
    // Reinitialize kernel & error state
    USpice::init_all();

    // Most MaxQ USpice API calls return a result (ok/fail) and string error message (by reference)
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage = "";

    //
    FString RelativePathToKernel = TEXT("NonAssetData/naif/kernels/Generic/PCK/gm_de431.tpc");

    // furnsh:  the most basic way to load spice kernel data
    // furnsh will look for the file relative to the project directory
    // ...if that fails, furnsh will check the plugin path (EDITOR BUILDS ONLY)
    USpice::furnsh(ResultCode, ErrorMessage, RelativePathToKernel);

    if (GEngine && Squawk)
    {
        GEngine->AddOnScreenDebugMessage(-1, 60.0f, ResultCode == ES_ResultCode::Success ? FColor::Green : FColor::Red, FString::Printf(TEXT("LoadOneKernel loaded kernel file %s"), *RelativePathToKernel));
    }

    return ResultCode == ES_ResultCode::Success;
}

// Demonstrate how to enumerate all kernel files in a project directory
void ATutorial01Actor::EnumeratePCKKernels()
{
    // Reinitialize kernel & error state
    USpice::init_all();

    // Most MaxQ USpice API calls return a result (ok/fail) and string error message (by reference)
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage = "";

    // Will hold the relative paths we're about to enumerate...
    TArray<FString> FoundKernels;

    // enumerate_kernels:  get a list of relative paths to all files in a directory...
    // enumerate_kernels will look for the file relative to the project directory
    // ...if that fails, furnsh will check the plugin path (EDITOR BUILDS ONLY)
    // warning, ALL files in directory are enumerated, kernels or not
    FString RelativePathToKernels = TEXT("NonAssetData/naif/kernels/Generic/PCK");
    USpice::enumerate_kernels(ResultCode, ErrorMessage, FoundKernels, RelativePathToKernels);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 60.0f, ResultCode == ES_ResultCode::Success ? FColor::Green : FColor::Red, FString::Printf(TEXT("EnumeratePCKKernels enumerated kernel files at %s"), *RelativePathToKernels));

        for (auto KernelPath : FoundKernels)
        {
            GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, FString::Printf(TEXT("EnumeratePCKKernels found kernel: %s"), *KernelPath));
        }
    }
}


// Demonstrate how to load all kernel files in a given directory
bool ATutorial01Actor::EnumerateAndLoadPCKKernelList(bool Squawk)
{
    // Reinitialize
    USpice::init_all();

    // SPICE return values
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage = "";

    // return value holding enumerated list of kernel files...
    TArray<FString> FoundKernels;

    FString RelativePathToKernels = TEXT("NonAssetData/naif/kernels/Generic/PCK");
    USpice::enumerate_kernels(ResultCode, ErrorMessage, FoundKernels, RelativePathToKernels);

    if (GEngine && Squawk)
    {
        GEngine->AddOnScreenDebugMessage(-1, 60.0f, ResultCode == ES_ResultCode::Success ? FColor::Green : FColor::Red, FString::Printf(TEXT("EnumerateAndLoadPCKKernelList enumerated kernel files at %s"), *RelativePathToKernels));
    }

    // If we succeeded, we have a whole list of files.   We will load them with furnsh_list.
    if (ResultCode == ES_ResultCode::Success)
    {
        // furnsh_list will load the list of relative paths as kernel files
        USpice::furnsh_list(ResultCode, ErrorMessage, FoundKernels);

        if (GEngine && Squawk)
        {
            GEngine->AddOnScreenDebugMessage(-1, 60.0f, ResultCode == ES_ResultCode::Success ? FColor::Green : FColor::Red, FString::Printf(TEXT("EnumerateAndLoadPCKKernelList loaded kernel files at %s"), *RelativePathToKernels));

            for (auto KernelPath : FoundKernels)
            {
                GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Green, FString::Printf(TEXT("EnumerateAndLoadPCKKernelList loaded kernel: %s"), *KernelPath));
            }
        }
    }

    return ResultCode == ES_ResultCode::Success;
}

// Demonstrate fetching gravitational (mass) constants from the loaded kernels
void ATutorial01Actor::QueryEarthsGM()
{
    // Reinitialize and load the GM (gravitational constant) kernel file
    if (LoadGMKernel(false))
    {
        ES_ResultCode ResultCode = ES_ResultCode::Success;
        FString ErrorMessage = "";

        // bodvrd_mass is one way of getting a GM from the kernel data
        FSMassConstant GM;
        USpice::bodvrd_mass(ResultCode, ErrorMessage, GM, TEXT("EARTH"), TEXT("GM"));

        if (GEngine)
        {
            // Conv_S*ToString prints strings with units for most data types
            GEngine->AddOnScreenDebugMessage(-1, 60.0f, ResultCode == ES_ResultCode::Success ? FColor::Green : FColor::Red, FString::Printf(TEXT("QueryEarthsGM bodvrd_mass - Earth's GM: %s"), *USpiceTypes::Conv_SMassConstantToString(GM)));
        }

        // bodvcd_mass is another way to get a GM, by integer ID code instead of ID string.
        if (ResultCode == ES_ResultCode::Success)
        {
            int Bodyid;

            // Look up the moon's Id
            ES_FoundCode FoundCode;
            USpice::bods2c(FoundCode, Bodyid, TEXT("MOON"));

            if (FoundCode == ES_FoundCode::Found)
            {
                // If we found the id code, look up its mass
                USpice::bodvcd_mass(ResultCode, ErrorMessage, GM, Bodyid, TEXT("GM"));

                if (GEngine)
                {
                    // Conv_S*ToString prints strings with units for most data types
                    GEngine->AddOnScreenDebugMessage(-1, 60.0f, ResultCode == ES_ResultCode::Success ? FColor::Green : FColor::Red, FString::Printf(TEXT("QueryEarthsGM bodvcd_mass - Moon's GM: %s"), *USpiceTypes::Conv_SMassConstantToString(GM)));
                }
            }
        }

        // One more way to get a mass is using the K2 Node equivalents (USpiceK2::bodvrd_double_K2, USpiceK2::gdpool_double_K2)
        // The raw values can be reliably converted into a mass via USpiceK2::Conv_DoubleToSMassConstant_K2
        // (This is preferable over FSEphemerisMass() or FSEphemerisMass::FromGM() because you don't know what units the mass is in,
        // but Conv_DoubleToSMassConstant_K2 does...
        if (ResultCode == ES_ResultCode::Success)
        {
            double dvalue = USpiceK2::bodvrd_double_K2(ResultCode, ErrorMessage, TEXT("SUN"), TEXT("GM"));
            GM = USpiceK2::Conv_DoubleToSMassConstant_K2(dvalue);

            GEngine->AddOnScreenDebugMessage(-1, 60.0f, ResultCode == ES_ResultCode::Success ? FColor::Green : FColor::Red, FString::Printf(TEXT("QueryEarthsGM bodvcd_mass - Sun's GM: %s"), *USpiceTypes::Conv_SMassConstantToString(GM)));
        }

        // Yet more ways: USpice::gdpool, USpiceK2::gdpool_double_K2
    }
    else if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, TEXT("QueryEarthsGM EnumerateAndLoadPCKKernelList failed"));
    }
}

// Demonstrate fetching planetary radii constants from the loaded kernels
void ATutorial01Actor::QueryEarthsRadius()
{
    // Reinitialize and load the SPK kernels
    if (EnumerateAndLoadPCKKernelList(false))
    {
        ES_ResultCode ResultCode = ES_ResultCode::Success;
        FString ErrorMessage = "";

        // bodvrd_distance_vector is one way of getting a RADII distance vector from the kernel data
        // .x, .y = equatorial radius
        // .z = polar radius
        FSDistanceVector Radii;
        USpice::bodvrd_distance_vector(ResultCode, ErrorMessage, Radii, TEXT("EARTH"), TEXT("RADII"));

        if (GEngine)
        {
            // Conv_S*ToString prints strings with units for most data types
            GEngine->AddOnScreenDebugMessage(-1, 60.0f, ResultCode == ES_ResultCode::Success ? FColor::Green : FColor::Red, FString::Printf(TEXT("QueryEarthsRadius bodvrd_mass - Earth's Radii: %s"), *USpiceTypes::Conv_SDistanceVectorToString(Radii)));
        }

        // bodvcd_distance_vector is another way to get a radii, by integer ID code instead of ID string.
        if (ResultCode == ES_ResultCode::Success)
        {
            int Bodyid;

            // Look up mars's Id
            ES_FoundCode FoundCode;
            USpice::bods2c(FoundCode, Bodyid, TEXT("MARS"));

            if (FoundCode == ES_FoundCode::Found)
            {
                // If we found the id code, look up its mass
                USpice::bodvcd_distance_vector(ResultCode, ErrorMessage, Radii, Bodyid, TEXT("RADII"));

                if (GEngine)
                {
                    // Conv_S*ToString prints strings with units for most data types
                    GEngine->AddOnScreenDebugMessage(-1, 60.0f, ResultCode == ES_ResultCode::Success ? FColor::Green : FColor::Red, FString::Printf(TEXT("QueryEarthsRadius bodvcd_distance_vector - Mars's Equatorial Radius: %s, Polar Radius: %s"), *USpiceTypes::Conv_SDistanceToString(Radii.x), *USpiceTypes::Conv_SDistanceToString(Radii.z)));
                }
            }
        }

        // One more way to get a mass is using the K2 Node equivalents (USpiceK2::bodvrd_double_K2, USpiceK2::gdpool_double_K2)
        // The raw values can be reliably converted into a mass via USpiceK2::Conv_SDimensionlessVectorToSDistanceVector_K2
        // (This is preferable over FSEphemerisMass() or FSEphemerisMass::FromGM() because you don't know what units the mass is in,
        // but Conv_DoubleToSMassConstant_K2 does...
        if (ResultCode == ES_ResultCode::Success)
        {
            // Venus's radii is stored by in the kernel pool in the form BODY299_RADII, "VENUS_RADII" will return nil
            FSDimensionlessVector dvvalue = USpiceK2::gdpool_vector_K2(ResultCode, ErrorMessage, TEXT("BODY299_RADII"));
            Radii = USpiceK2::Conv_SDimensionlessVectorToSDistanceVector_K2(dvvalue);

            GEngine->AddOnScreenDebugMessage(-1, 60.0f, ResultCode == ES_ResultCode::Success ? FColor::Green : FColor::Red, FString::Printf(TEXT("QueryEarthsRadius gdpool_vector_K2 - Venus's Radii: %s"), *USpiceTypes::Conv_SDistanceVectorToString(Radii)));
        }

        // Yet more ways: USpice::gdpool, USpiceK2::bodvcd_vector_K2, or even bodvcd_array_K2, bodvrd_array_K2, or gdpool_array_K2
    }
    else if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Red, TEXT("QueryEarthsRadius EnumerateAndLoadPCKKernelList failed"));
    }
}
