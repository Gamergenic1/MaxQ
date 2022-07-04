// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "Sample01Actor.h"
#include "Engine/StaticMesh.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "EngineUtils.h"
#include "Spice.h"
#include "SpiceK2.h"
#include "SampleUtilities.h"
#include "SpiceDiagnostics.h"

using MaxQSamples::Log;
using namespace MaxQ::Data;
using namespace MaxQ::Core;
using namespace MaxQ::Constants;
using namespace MaxQ::Math;

//-----------------------------------------------------------------------------
// Sample01
// Initialization and kernel data
// See:
// https://maxq.gamergenic.com/getting-started/plugin-content/samples/sample-01/
//-----------------------------------------------------------------------------
/*
 * Additional Info:  Documentation
 * 
 * Plugin documentation is available in the plugin's directory
 *      /Documentation
 *          /naif - Helpful documentation on SPICE
 *          /gamergenic
 *              /MaxQ   - Helpful documentation on MaxQ
*/
ASample01Actor::ASample01Actor()
{
    SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));

    RelativePathToGMKernel = TEXT("NonAssetData/naif/kernels/Generic/PCK/gm_de431.tpc");
    RelativePathToPCKKernels.Path = TEXT("NonAssetData/naif/kernels/Generic/PCK");

    KilometersPerScenegraphUnit = 3000;
}


//-----------------------------------------------------------------------------
// Name: BeginPlay
// Desc: Calls each of the sample/demo methods once when play begins
//-----------------------------------------------------------------------------
void ASample01Actor::BeginPlay()
{
    Super::BeginPlay();

    Log(FString::Printf(TEXT("PluginInfo: %s"), *MaxQSamples::MaxQPluginInfo()), FColor::Purple);
    Log(TEXT("Sample01: Initialization and kernel data"), FColor::Blue);
    Log(TEXT("** Please see Sample01Actor.cpp for more info **"), FColor::Blue);

    InitializeSpice();

    LoadGMKernel();
    
    EnumeratePCKKernels();
    
    EnumerateAndLoadPCKKernelList();

    QueryEarthsGM();

    QueryEarthsRadius();

    DumpKernelDiagnostics();

    ScaleAllBodies();
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: InitializeSpice
// Desc: Demonstrate how to initialize the SPICE module
//-----------------------------------------------------------------------------

void ASample01Actor::InitializeSpice()
{
    // MaxQ::Core::InitAll:  clears kernel memory and any error state.
    // Before your app starts it should initialize the USpice library.
    // Do this once, before you load kernel files.
    InitAll();

    Log(TEXT("InitializeSpice initialized spice (InitAll)"), FColor::White);
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: LoadGMKernel
// Desc: Demonstrate how to load one kernel data file
//-----------------------------------------------------------------------------
/*
 * Additional Info:  furnsh (SPICE API)
 * furnsh
        Load one or more SPICE kernels into a program.
        https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/furnsh_c.html
 * kernels
        https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/kernel.html
*/
/*
 * Additional Info:  generic kernels (download repository)
 * Link: https://naif.jpl.nasa.gov/pub/naif/generic_kernels/
*/
/*
 * Additional Info:  Kernel file naming conventions used by naif

   SPICE Kernel files:

      *.bc            Binary CK (pointing) files.
      *.bdb           Binary DBK (database) files.
      *.bds           Binary DSK (digital shape) files.
      *.bep           Binary EK (events) Science Plan files.
      *.bes           Binary EK (events) Sequence files.
      *.bpc           Binary PCK (planetary rotation) files.
      *.bsp           Binary SPK (ephemeris) files.

      *.ten           Text EK (events) Experimenter's Notebook files.
      *.tep           Text EK (events) Science Plan files.
      *.tf            Text FK (frame definitions) files.
      *.ti            Text IK (instrument parameters) files.
      *.tls           Text LSK (leapseconds) files.
      *.tm            Text MK (meta-kernels, aka ``furnsh'') files
      *.tpc           Text PCK (planetary constants) files.
      *.tsc           Text SCLK (spacecraft clock) files.

      *.xc            Transfer format CK (pointing) files.
      *.xdb           Transfer format DBK (database) files.
      *.xds           Transfer format DSK (digital shape) files.
      *.xep           Transfer format EK (events) Science Plan files.
      *.xes           Transfer format EK (events) Sequence files.
      *.xpc           Transfer format PCK (planetary rotation) files.
      *.xsp           Transfer format SPK (ephemeris) files.
*/

bool ASample01Actor::LoadGMKernel(bool Squawk)
{
    // Reinitialize kernel & error state
    InitAll();

    // NOTE: *1*
    // **MaxQPathAbsolutified is not normally needed** (it converts a Plugin-relative path into an absolute path)
    // Your kernels should be placed in a sub-directory of the project's /Content directory
    // paths in Spice are relative to /Content
    // So, if your kernel is: /Content/Kernels/my_kernel.tf
    // You'd just pass path "Kernels/my_kernel.tf" into furnsh.
    // Absolute paths work if really really needed, like to load something in the plugins directory for a sample ;)
    // Kernel files can only be copied into a shipping build as a subdirectory of /Content
    // (Have not tested if relative directories such as "..\Other\Kernels" might work.  (Undefined behavior?)
    FString KernelGMPath = MaxQSamples::MaxQPathAbsolutified(RelativePathToGMKernel);

    // furnsh:  the most basic way to load spice kernel data
    // furnsh will look for the file relative to the project directory
    // ...if that fails, furnsh will check the plugin path (EDITOR BUILDS ONLY)
    bool bSuccess = Furnsh(KernelGMPath);

    // Another way is to use the USpice Blueprint Library:
    // USpice::furnsh(ResultCode, ErrorMessage, KernelGMPath);

    if (Squawk)
    {
        Log(FString::Printf(TEXT("LoadOneKernel loaded kernel file %s"), *KernelGMPath), bSuccess);
    }

    return bSuccess;
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: EnumeratePCKKernels
// Desc: Demonstrate how to enumerate all kernel files in a project directory
//-----------------------------------------------------------------------------

void ASample01Actor::EnumeratePCKKernels()
{
    // Reinitialize kernel & error state
    InitAll();

    // See NOTE: *1*, above, about MaxQPathAbsolutified
    FString KernelPCKsPath = MaxQSamples::MaxQPathAbsolutified(RelativePathToPCKKernels.Path);

    // EnumerateDirectory:  get a list of relative paths to all files in a directory...
    // EnumerateDirectory will look for the file (relative to /Content, or absolute)
    // Note:  this returns ALL files, not just kernels!
    const auto& FoundKernels = EnumerateDirectory(KernelPCKsPath);

    Log(FString::Printf(TEXT("EnumeratePCKKernels enumerated kernel files at %s"), *KernelPCKsPath), FoundKernels.Num() > 0);

    for (auto KernelPath : FoundKernels)
    {
        Log(FString::Printf(TEXT("EnumeratePCKKernels found kernel: %s"), *KernelPath), FColor::Green);
    }
}



// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: EnumerateAndLoadPCKKernelList
// Desc: Demonstrate how to load all kernel files in a given directory
//-----------------------------------------------------------------------------

bool ASample01Actor::EnumerateAndLoadPCKKernelList(bool Squawk)
{
    // Reinitialize
    InitAll();

    // See NOTE: *1*, above, about MaxQPathAbsolutified
    FString KernelPCKsPath = MaxQSamples::MaxQPathAbsolutified(RelativePathToPCKKernels.Path);

    // Get a list of kernels (relative to /Content, or absolute paths if KernelPCKsPath is absolute
    const auto FoundKernels = EnumerateDirectory(KernelPCKsPath);

    bool bSuccess = FoundKernels.Num() > 0;
    if (Squawk)
    {
        Log(FString::Printf(TEXT("EnumerateAndLoadPCKKernelList enumerated kernel files at %s"), *KernelPCKsPath), bSuccess);
    }

    // If we succeeded, we have a whole list of files.   We will load them with furnsh_list.
    if (bSuccess)
    {
        // furnsh_list will load the list of relative paths as kernel files
        bSuccess &= Furnsh(FoundKernels);

        if (Squawk)
        {
            Log(FString::Printf(TEXT("EnumerateAndLoadPCKKernelList loaded kernel files at %s"), *KernelPCKsPath), bSuccess);

            for (auto KernelPath : FoundKernels)
            {
                Log(FString::Printf(TEXT("EnumerateAndLoadPCKKernelList loaded kernel: %s"), *KernelPath), FColor::Green);
            }
        }
    }

    return bSuccess;
}

// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: QueryEarthsGM
// Desc: 
// Demonstrate fetching gravitational (mass) constants from the loaded kernels
//-----------------------------------------------------------------------------
/*
 * Additional Info: Documentation (SPICE API)
 * bodvrd
        Fetch from the kernel pool the double precision values
        of an item associated with a body.
        https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/bodvrd_c.html
 * bodvcd
        Fetch from the kernel pool the double precision values of an item
        associated with a body, where the body is specified by an integer ID
        code.
        https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/bodvcd_c.html
 * bods2c
        Translate a string containing a body name or ID code to an integer
        code.
        https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/bods2c_c.html
*/
void ASample01Actor::QueryEarthsGM()
{
    // Reinitialize and load the GM (gravitational constant) kernel file
    if (LoadGMKernel(false))
    {
        ES_ResultCode ResultCode = ES_ResultCode::Success;
        FString ErrorMessage = "";

        // bodvrd_mass is one way of getting a GM from the kernel data.
        // It's in the USpice Blueprint library, which is less covenient to use
        // than many of the alternatives to follow.
        FSMassConstant gm;
        USpice::bodvrd_mass(ResultCode, ErrorMessage, gm, EARTH, GM);

        // Every MaxQ structure has a "ToString".
        Log(FString::Printf(TEXT("QueryEarthsGM bodvrd_mass - Earth's GM: %s"), *gm.ToString()), ResultCode);

        // And then there's this...:
        gm = Bodvrd<FSMassConstant>(EARTH, GM, &ResultCode);

        Log(FString::Printf(TEXT("QueryEarthsGM MaxQ::Math::bodvrd - Earth's GM: %s"), *gm.ToString()), ResultCode);

        // bodvcd_mass is another way to get a GM, by integer ID code instead of ID string.
        if (ResultCode == ES_ResultCode::Success)
        {
            int Bodyid;

            if (Bods2c(Bodyid, MOON))
            {
                // If we found the id code, look up its mass
                gm = Bodvcd<FSMassConstant>(Bodyid, GM, &ResultCode);

                Log(FString::Printf(TEXT("QueryEarthsGM bodvcd_mass - Moon's GM: %s"), *gm.ToString()), ResultCode);
            }
        }

        // One more way to get a mass is using the K2 Node equivalents (USpiceK2::bodvrd_double_K2, USpiceK2::gdpool_double_K2)
        // The raw values can be reliably converted into a mass via USpiceK2::Conv_DoubleToSMassConstant_K2
        // (This is preferable over FSEphemerisMass() or FSEphemerisMass::FromGM() because you don't know what units the mass is in,
        // but Conv_DoubleToSMassConstant_K2 does...
        if (ResultCode == ES_ResultCode::Success)
        {
            double dvalue = USpiceK2::bodvrd_double_K2(ResultCode, ErrorMessage, SUN, GM);
            gm = USpiceK2::Conv_DoubleToSMassConstant_K2(dvalue);
        }

        // Yet more ways: USpice::gdpool, USpiceK2::gdpool_double_K2
    }
    else
    {
        Log(TEXT("QueryEarthsGM EnumerateAndLoadPCKKernelList failed"), FColor::Red);
    }
}



// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: QueryEarthsRadius
// Desc: 
// Demonstrate fetching planetary radii constants from the loaded kernels
//-----------------------------------------------------------------------------
/*
 * Additional Info: Documentation (SPICE API)
 * gdpool
        Return the d.p. value of a kernel variable from the kernel pool.
        https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/cspice/gdpool_c.html
*/

void ASample01Actor::QueryEarthsRadius()
{
    // Reinitialize and load the SPK kernels
    if (EnumerateAndLoadPCKKernelList(false))
    {
        ES_ResultCode ResultCode = ES_ResultCode::Success;
        FString ErrorMessage = "";

        // bodvrd_distance_vector is one way of getting a RADII distance vector from the kernel data
        // .x, .y = equatorial radius
        // .z = polar radius
        auto Radii = Bodvrd<FSDistanceVector>(EARTH, RADII, &ResultCode);

        Log(FString::Printf(TEXT("QueryEarthsRadius bodvrd_mass - Earth's Radii: %s"), *Radii.ToString()), ResultCode);

        // bodvcd_distance_vector is another way to get a radii, by integer ID code instead of ID string.
        if (ResultCode == ES_ResultCode::Success)
        {
            int Bodyid;

            // Look up mars's Id
            if (Bods2c(Bodyid, MARS))
            {
                // This works too, if you're worried about misspelling somethings.
                // There are constants for Parameter Names, Reference Frame Names, Naif Object Names, etc.
                const FString& RadiiParameterName = RADII;

                // If we found the id code, look up its mass
                Radii = Bodvcd<FSDistanceVector>(Bodyid, RadiiParameterName, &ResultCode);

                Log(FString::Printf(TEXT("QueryEarthsRadius Bodvrd - Mars's Equatorial Radius: %s, Polar Radius: %s"), *Radii.x.ToString(), *Radii.z.ToString()), ResultCode);
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

            Log(FString::Printf(TEXT("QueryEarthsRadius gdpool_vector_K2 - Venus's Radii: %s"), *Radii.ToString()), ResultCode);
        }

        // Yet more ways: USpice::gdpool, USpiceK2::bodvcd_vector_K2, or even bodvcd_array_K2, bodvrd_array_K2, or gdpool_array_K2
    }
    else
    {
        Log(TEXT("QueryEarthsRadius EnumerateAndLoadPCKKernelList failed"), FColor::Red);
    }
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: DumpKernelDiagnostics
// Desc: 
// Demonstrate interrogating kernel files regarding validity windows
//-----------------------------------------------------------------------------

void ASample01Actor::DumpKernelDiagnostics()
{

    ES_ResultCode ResultCode;
    FString ErrorMessage;
    FString LogString1;

    FString LSKKernelPath = TEXT("NonAssetData/naif/kernels/Generic/LSK/naif0012.tls");
    FString SPKKernelPath = TEXT("NonAssetData/naif/kernels/Generic/SPK/planets/de440s.bsp");
 
    USpiceDiagnostics::DumpSpkSummary(
        ResultCode,
        ErrorMessage,
        LogString1,
        MaxQSamples::MaxQPathAbsolutified(LSKKernelPath),
        MaxQSamples::MaxQPathAbsolutified(SPKKernelPath)
    );

    if (GEngine)
    {
        if (ResultCode == ES_ResultCode::Success)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, LogString1);
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, ErrorMessage);
        }
    }

    FString BinaryPCKKernelPath = TEXT("NonAssetData/naif/kernels/Generic/PCK/earth_200101_990628_predict.bpc");
    FString LogString2;

    USpiceDiagnostics::DumpPckSummary(
        ResultCode,
        ErrorMessage,
        LogString2,
        MaxQSamples::MaxQPathAbsolutified(LSKKernelPath),
        MaxQSamples::MaxQPathAbsolutified(BinaryPCKKernelPath)
    );

    if (GEngine)
    {
        if (ResultCode == ES_ResultCode::Success)
        {
            GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, LogString2);
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, ErrorMessage);
        }
    }

    
    FString BinarySCLKKernelPath = TEXT("NonAssetData/naif/kernels/INSIGHT/SCLK/NSY_SCLKSCET.00023.tsc");
    FString BinaryCKKernelPath = TEXT("NonAssetData/naif/kernels/INSIGHT/CK/insight_ida_pot_210801_211218_v1.bc");
    FString LogString3;

    USpiceDiagnostics::DumpCkSummary(
        ResultCode,
        ErrorMessage,
        LogString3,
        MaxQSamples::MaxQPathAbsolutified(LSKKernelPath),
        MaxQSamples::MaxQPathAbsolutified(BinarySCLKKernelPath),
        MaxQSamples::MaxQPathAbsolutified(BinaryCKKernelPath)
    );

    if (GEngine)
    {
        if (ResultCode == ES_ResultCode::Success)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f,FColor::Green, LogString3);
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ErrorMessage);
        }
    }

    FString LogString4;
    USpiceDiagnostics::DumpLoadedKernelFiles(LogString4);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, LogString4);
    }
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: ScaleAllBodies
// Desc: 
// Demonstrate using SPICE bodvrd RADII data to set mesh dimensions
//-----------------------------------------------------------------------------

void ASample01Actor::ScaleAllBodies()
{
    Log(TEXT("ScaleAllBodies is rescaling mesh dimensions to scale (but not separation distances)"), FColor::White);

    AActor* Actor = nullptr;
    FString ActorName;
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage = "";

    // Iterate over all actors in the scene
    for (TActorIterator<AActor> ActorIterator(GetWorld()); ActorIterator; ++ActorIterator)
    {
        Actor = *ActorIterator;

        // Drill down on all celestial bodies
        if (Actor && Actor != this && Actor->ActorHasTag("BODY"))
        {
            // Use the actor name to get radii info from the kernel pool
            Actor->GetName(ActorName);

            ActorName.RemoveFromStart(TEXT("BP_"));

            int32 TrailingIndex;
            if (ActorName.FindChar('_', TrailingIndex))
            {
                ActorName.RemoveAt(TrailingIndex, ActorName.Len() - TrailingIndex);
            }

            FSDistanceVector Radii = Bodvrd<FSDistanceVector>(ActorName, MaxQ::Constants::RADII, &ResultCode, &ErrorMessage);

            if (ResultCode == ES_ResultCode::Success)
            {
                // Get the dimensions of the static mesh at the root...  (ringed planets have multiple meshes)
                UStaticMeshComponent* SM = Cast<UStaticMeshComponent>(Actor->GetRootComponent());

                if (SM  && SM->GetStaticMesh())
                {
                    FBoxSphereBounds Bounds = SM->GetStaticMesh()->GetBounds();

                    // ** Swizzle is the correct way to get an FVector from FSDistanceVector etc **
                    FVector ScenegraphRadii = Swizzle(Radii.AsKilometers());

                    // Swizzle does no scaling, so our values are in kilometers
                    // Normally one scenegraph unit = one centimeter, but let's scale it all down
                    ScenegraphRadii /= KilometersPerScenegraphUnit;

                    FVector ScenegraphDiameter = ScenegraphRadii;

                    // Finally, set the actor's scale based on the actual size and the mesh dimensions
                    Actor->SetActorScale3D(ScenegraphDiameter / Bounds.BoxExtent);
                }
                else
                {
                    Log(FString::Printf(TEXT("ScaleAllBodies could not find static mesh for %s"), *ActorName), FColor::Red);
                }
            }
            else
            {
                Log(FString::Printf(TEXT("ScaleAllBodies kernel pool RADII failed for %s"), *ActorName), FColor::Red);
            }
        }
    }
}
