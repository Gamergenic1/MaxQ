// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "Tutorial02Actor.h"
#include "Components/SceneComponent.h"
#include "Engine/Engine.h"
#include "Spice.h"
#include "SpiceK2.h"
#include "TutorialUtilities.h"

using MaxQTutorial::Log;

//-----------------------------------------------------------------------------
// Tutorial02
// Time manipulation
//-----------------------------------------------------------------------------
/*
 * Additional Info:  Documentation
 *
 * Plugin documentation is available in the plugin's directory
 *      /Documentation
 *          /naif - Helpful documentation on SPICE
 */
 /* Additional Info: Files Kernels (SPICE API)
 * LSK kernels
        Leap seconds, for time keeping
        https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/Tutorials/pdf/individual_docs/16_lsk_and_sclk.pdf
 * PCK kernels
        Planet orientations, kernel pool data, etc
        https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/pck.html
        https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/Tutorials/pdf/individual_docs/19_pck.pdf
        https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/kernel.html
*  Time
*       https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/req/time.html
*       https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/Tutorials/pdf/individual_docs/15_time.pdf
*/
ATutorial02Actor::ATutorial02Actor()
{
    SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));

    // This is a "Leap Seconds" kernel
    // (it is a text file, open it up and take a look if you wish...)
    // It contains data on leap seconds that have been declared, which is necessary
    // for highly precise time keeping.
    RequiredKernels.Add(TEXT("NonAssetData/naif/kernels/Generic/LSK/naif0012.tls"));

    // This is a kernel pool file containing masses of celestial bodies.
    // It is also a text file, feel free to peek inside.
    RequiredKernels.Add(TEXT("NonAssetData/naif/kernels/Generic/PCK/gm_de431.tpc"));
    
    // This is a PCK kernel... Which contains data about planet orientations, etc
    // Again, another text file.
    RequiredKernels.Add(TEXT("NonAssetData/naif/kernels/Generic/PCK/pck00010.tpc"));
}

//-----------------------------------------------------------------------------
// Name: BeginPlay
// Desc: Calls each of the tutorial/demo methods once when play begins
//-----------------------------------------------------------------------------
void ATutorial02Actor::BeginPlay()
{
    Log(FString::Printf(TEXT("PluginInfo: %s"), *MaxQTutorial::MaxQPluginInfo()), FColor::Purple);
    Log(TEXT("Tutorial02: Time manipulation"), FColor::Blue);
    Log(TEXT("** Please see Tutorial02Actor.cpp for more info **"), FColor::Blue);

    InitializeSpice();
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: InitializeSpice
// Desc: Demonstrate how to initialize the SPICE module
//-----------------------------------------------------------------------------

void ATutorial02Actor::InitializeSpice()
{
    // init_all:  clears kernel memory and any error state.
    USpice::init_all();

    // SPICE return values
    ES_ResultCode ResultCode = ES_ResultCode::Success;
    FString ErrorMessage = "";

    // furnsh_list will load the list of relative paths as kernel files
    USpice::furnsh_list(ResultCode, ErrorMessage, RequiredKernels);

    Log(TEXT("InitializeSpice loaded kernel file"), ResultCode);
}

