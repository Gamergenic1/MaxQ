// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "Sample06Actor.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Engine/Engine.h"
#include "Spice.h"

using MaxQSamples::Log;
using namespace MaxQ::Data;
using namespace MaxQ::Core;
using namespace MaxQ::Constants;
using namespace MaxQ::Math;



//-----------------------------------------------------------------------------
// Sample06
// Setting orientations with PCK Kernels, Reference Frames, and more
// Credit for planet textures: NASA
//-----------------------------------------------------------------------------


/*
* How this system was created:
* 
* 1. System Structure - fk kernel
* File name: MaxQ-TRAPPIST_1-fk.tf
* * Body Naif Names
* * Body Naif ID Codes
* * Reference Frames
* Make a Frames Kernel that defines the structure of the system
* This file establishes the new bodies and their name->id code mapings
* Then, it created new reference frames based on TRAPPIST-1's Right Ascension/
* Declination...  An "eye" frame where the +X points from Earth to Trappist-1.
* An "ECLIPTIC" plane which the planet's are loosely orbiting... So that +Z
* Points to Earth... (This allows the transit "inclinations" to roughly equate
* to orbital element inclinations).
* And an Ecliptic "North Pole" reference frame for viewing the planets from above.
* Then, for each planet it creates a Principle Axes (PA) frame that will be controlled
* by the PCK Kernel.
* And then for each PA frame it creates an IAU_<body> frame per the standard namings.
* For each planet, a barycenter is created, and the planet itself.
* If it had moons they would mutually orbit the barycenter.
* 
* 2. Body orientations and rotation models - pck kernel
* File name: MaxQ-TRAPPIST_1-pck.tpc
* * Rotation Models
* * Body Mass, Radii
* For each body, set it's mass and radii.
* Then, specify what direction the planet's north pole is by right ascension/declination.
* (That's the axis the planet will rotate around) - <body>_POLE_RA and <body>_POLE_DEC.
* Set the initial angle of rotation, and the degrees of rotation/day in the _PM var.
* 
* 3. Planet positions relative to barycenters
* File name: MaxQ-TRAPPIST_1-barycenters.bsp
* This kernel just glues each planet directly onto its barycenter.
* It was created with NASA's "Pinpoint" utility, from the text file:
* MaxQ/Content/NonAssetData/MaxQ/site_defs/trappist-1-barycenters.defs
* See https://naif.jpl.nasa.gov/pub/naif/utilities/PC_Windows_64bit/pinpoint.ug
* 
* 4. Barycenters orbits around star TRAPPIST-1
* File name: MaxQ-TRAPPIST_1-orbits.bsp
* This kernel provides position information - the orbit of planet/barycenters
* around the star.
* See function GenerateTrappistSPKKernel() in this file.
* For each planet there's a simple kepler orbit, which is sampled at one day increments
* and store as state values.  The orbits are computed from the current date/time
* for the next 30 days.
* When the animation starts it looks for this kernel, and sets the start time of the
* animation to the start of coverage in this kernel.
* To regenerate this kernel, either use the Inspector Button on actor BP_Sample06Actor
* in the scene "Generate Trappist SPKKernel", or, you can set boolean "Update SPK File"
* which will trigger an update every time the scene plays.
* Generating the SPK file is simple.
* USpice::spkopn: create a new file.  (note:  it fails if the file exists, delete it first)
* USpice::dafac: add a comments block to the file.
* USpice::conics: evaluate orbital elements to get a state (states are saved to an arrary of "observations")
* USpice::spkw05: writes an array of observations (for one object) to the spk kernel
* USpice::spkcls: closes the file
* The kernel it creates is a normal binary spk kernel file that works with all
* SPICE utility programs. 
* See https://naif.jpl.nasa.gov/naif/utilities_PC_Windows_64bit.html
* To see the comments inside the file:
* commnt -r MaxQ-TRAPPIST_1-orbits.bsp
* To see a summary of the file's contents:
* brief -c -t MaxQ-TRAPPIST_1-orbits.bsp
* The orbit data is stored in a UE TMap<FName,FSConicElements> map, which is then
* processed into the kernel file.   It would probably be slicker to store the
* system data inside a kernel file, then read that kernel to make the new kernel,
* but that would obscure the sample, so it uses plain UE data instead.
* 
* All files are in the marketplace plugin's MaxQ directory
* ./MaxQ/Content/NonAssetData/MaxQ/kernels/TRAPPIST-1 
* 
*/ 

ASample06Actor::ASample06Actor()
{
    SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
    PrimaryActorTick.bCanEverTick = true;

    GetDefaultTrappistKernels(TrappistSystemKernels);

    SolarSystemState.TimeScale = 10000.0;

    BodyScale = 50.0;
    DistanceScale = 50.0;

    OriginNaifName = "TRAPPIST_1_BARYCENTER";
    OriginReferenceFrame = "TRAPPIST_1_EYE";

    // Sun is needed to determine light direction
    SunNaifName = "TRAPPIST_1";

    PlanetFocusName = "TRAPPIST_1E";

    // This is the SPK Kernel we're going to programmatically generate.
    // We'll use simple kepler orbits to generate the object state vectors.
    RelativePathToSPKFile = TEXT("NonAssetData/MaxQ/kernels/TRAPPIST-1/MaxQ-TRAPPIST_1-orbits.bsp");

    CommentsToWrite.Emplace(TEXT("Created by MaxQ Spaceflight Toolkit for Unreal Engine."));
    CommentsToWrite.Emplace(TEXT("This file should not be used for any purpose other"));
    CommentsToWrite.Emplace(TEXT("that testing MaxQ.  (C++ Sample 06)"));

    OrbitalElements = GetTrappist1OrbitalElements();
}


//-----------------------------------------------------------------------------
// Name: BeginPlay
// Desc: Calls each of the sample/demo methods once when play begins
//-----------------------------------------------------------------------------
void ASample06Actor::BeginPlay()
{
    Super::BeginPlay();

    Log(FString::Printf(TEXT("PluginInfo: %s"), *MaxQSamples::MaxQPluginInfo()), FColor::Purple);
    Log(TEXT("Sample06: Authoring new bodies - TRAPPIST-1 System"), FColor::Blue);
    Log(TEXT("** Please see Sample06Actor.cpp for more info **"), FColor::Blue);
    Log(TEXT("See Sample06Actor (scene instance) Details Panel for time/obs/ref control buttons."), FColor::Blue);

    // init_all:  clears kernel memory and any error state.
    InitAll();

    // Don't tick unless we have the kernels required to update the solar system
    bool EnableTick = USampleUtilities::LoadKernelList(TEXT("TRAPPIST System"), TrappistSystemKernels);
    if (EnableTick)
    {
        InitializeSolarSystem();

        FString ReadFilePath = MaxQSamples::MaxQPathAbsolutified(RelativePathToSPKFile);

        if (!ReadFilePath.IsEmpty() && FPaths::ValidatePath(ReadFilePath))
        {
            // If the body SPK kernel doesn't exist, create a new one.
            // Or, if the bool forces re-creation.
            if (!FPaths::FileExists(ReadFilePath) || UpdateSpkFile)
            {
                GenerateTrappistSPKKernel();
            }
        }

        // Try to find the coverage window in the existing file.
        auto IdCode = 0;
        if (Bods2c(IdCode, FString{ TEXT("TRAPPIST_1B") }))
        {
            ES_ResultCode ResultCode;
            FString ErrorMessage;
            TArray<FSWindowSegment> CoverageWindows;
            USpice::spkcov(ResultCode, ErrorMessage, ReadFilePath, IdCode, {}, CoverageWindows);
            if (ResultCode == ES_ResultCode::Success)
            {
                for (const auto WindowSegment : CoverageWindows)
                {
                    // We found a segment!
                    // There was probably only one.
                    // Anyhoo, set the current solar system time to the SPK segment time.
                    SolarSystemState.CurrentTime = FSEphemerisTime{ WindowSegment.start };
                    SolarSystemState.InitialTime = SolarSystemState.CurrentTime.ToString();
                    break;
                }
            }
        }

        bool bSuccess = Furnsh(ReadFilePath);
        Log(FString::Printf(TEXT("furnsh: %s"), *ReadFilePath), bSuccess);

        ResetYawPitch();
    }


    PrimaryActorTick.SetTickFunctionEnable(EnableTick);
}


//-----------------------------------------------------------------------------
// Name: Tick
// Desc: 
//-----------------------------------------------------------------------------
void ASample06Actor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateSolarSystem(DeltaTime);
}



// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: InitializeSolarSystem
// Desc: Scale the Trappist-1 System Star and Planets to size
//-----------------------------------------------------------------------------

void ASample06Actor::InitializeSolarSystem()
{
    USampleUtilities::InitializeTime(SolarSystemState);
    MaxQSamples::InitBodyScales(BodyScale, SolarSystemState);
}



// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: UpdateSolarSystem
// Desc: Position and rotate the Star & Planets.  Orient the directional light.
//-----------------------------------------------------------------------------

void ASample06Actor::UpdateSolarSystem(float DeltaTime)
{
    SolarSystemState.CurrentTime += DeltaTime * SolarSystemState.TimeScale;

    bool success = true;
    success &= MaxQSamples::UpdateSunDirection(OriginNaifName, OriginReferenceFrame, SolarSystemState.CurrentTime, SunNaifName, SunDirectionalLight);
    success &= MaxQSamples::UpdateBodyPositions(OriginNaifName, OriginReferenceFrame, DistanceScale, SolarSystemState);
    success &= MaxQSamples::UpdateBodyOrientations(OriginReferenceFrame, SolarSystemState);

    if (!success)
    {
        // Restart time... we must have run out of kernel data
        Restart();
    }

    if (GEngine)
    {
        double UE_Units_Per_KM = 100 * 1000.;
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Time Scale: %f x"), SolarSystemState.TimeScale.AsSeconds()));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Scale PLANETS/MOON : 1/%d"), (int)(BodyScale * UE_Units_Per_KM)));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Scale Solar System Distances : 1/%d"), (int)(DistanceScale * UE_Units_Per_KM)));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Display Time: %s"), *SolarSystemState.CurrentTime.ToString()));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Origin Reference Frame: %s"), *OriginReferenceFrame.ToString()));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, *FString::Printf(TEXT("Origin Observer Naif Name: %s"), *OriginNaifName.ToString()));

        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Silver, TEXT("See Sample06Actor.cpp for details on creating new planets, moons, etc."));
        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::White, TEXT("This solar system was created from scratch, using data from Wikipedia on the TRAPPIST-1 system"));

        GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Orange, TEXT("Select BP_Sample06Actor in the world outliner, then use buttons on details panel to control frame/position"));
    }
}


//-----------------------------------------------------------------------------
// Name: GetDefaultTrappistKernels
// Desc:
// Load a list with basic kernels needed for the Trappist system
//-----------------------------------------------------------------------------
void ASample06Actor::GetDefaultTrappistKernels(TArray<FString>& TrappistSystemKernelsArray)
{
    TrappistSystemKernelsArray.Empty();

    // New hand-created text kernel for Trappist system.
    // Created in a text editor.
    // This is a frames kernel, which establishes the structure of the system planet names, ID's etc
    TrappistSystemKernelsArray.Add(TEXT("NonAssetData/MaxQ/kernels/TRAPPIST-1/MaxQ-TRAPPIST_1-fk.tf"));

    // Also created in a text editor.
    // This is a PCK kernel file, which contains information about the orientation and rotation
    // of the planets.   It also contains the Mass Constant for each.
    TrappistSystemKernelsArray.Add(TEXT("NonAssetData/MaxQ/kernels/TRAPPIST-1/MaxQ-TRAPPIST_1-pck.tpc"));

    // This is a binary SPK kernel file (ephemeris position).
    // This SPK affixes the star to the system barycenter, and all planets to their own
    // subsystem barycenter (TRAPPIST_1B -> TRAPPIST_1B_BARYCENTER, etc.)
    // It was created with the NAIF 'Pinpoint' utility, which exists for this purpose.
    //
    // See:
    // https://naif.jpl.nasa.gov/pub/naif/utilities/PC_Linux_64bit/pinpoint.ug
    //
    // Pinpoint can be downloaded here (Windows version, MacOS and Linux are available too):
    // https://naif.jpl.nasa.gov/naif/utilities_PC_Windows_64bit.html
    //
    // The file used to generate the SPK:
    // \MaxQ\Content\NonAssetData\MaxQ\site_defs\trappist-1-barycenters.defs
    // (See notes in the .defs file, open it with a text editor.)
    TrappistSystemKernelsArray.Add(TEXT("NonAssetData/MaxQ/kernels/TRAPPIST-1/MaxQ-TRAPPIST_1-barycenters.bsp"));

    // The same leap seconds file we always use... No need to make a new one for this.
    // (although, we could.)
    TrappistSystemKernelsArray.Add(TEXT("NonAssetData/naif/kernels/Generic/LSK/naif0012.tls"));
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: GenerateTrappistSPKKernel
// Desc: Generate an SPK file for the planet positions...
//-----------------------------------------------------------------------------

void ASample06Actor::GenerateTrappistSPKKernel()
{
    // AbsolutifyMaxQPath fails if the file doesn't exist.  The "ForWriting" version does not.
    // In this case the kernel might not exist, and if it doesn't then we want to regenerate it.
    FString WriteFilePath = MaxQSamples::AbsolutifyMaxQPathForWriting(RelativePathToSPKFile);

    if (!WriteFilePath.IsEmpty() && FPaths::ValidatePath(WriteFilePath))
    {
        // If the file exists, delete it so we can regenerate it.
        // spkopn fails if the file already exists.
        if (FPaths::FileExists(WriteFilePath))
        {
            MaxQSamples::Log(FString::Printf(TEXT("File Exists, deleting %s"), *WriteFilePath), FColor::Yellow);
            IFileManager& FileManager = IFileManager::Get(); FileManager.Delete(*WriteFilePath);
        }

        // Initialize SPICE, load relevant kernels
        InitAll();
        if (!USampleUtilities::LoadKernelList(TEXT("TRAPPIST System"), TrappistSystemKernels))
        {
            MaxQSamples::Log(TEXT("Kernel load failed"), FColor::Red);
            return;
        }

        ES_ResultCode ResultCode;
        FString ErrorMessage;
        int Handle{ 0 };
        // Open a new SPK file for writing
        USpice::spkopn(ResultCode, ErrorMessage, WriteFilePath, FPaths::GetCleanFilename(WriteFilePath), CommentsToWrite.Num() * 128, Handle);

        MaxQSamples::Log(FString::Printf(TEXT("spkopn file %s"), *WriteFilePath, ResultCode));

        // Add the comments to the SPK file
        if (ResultCode == ES_ResultCode::Success)
        {
            USpice::dafac(ResultCode, ErrorMessage, Handle, CommentsToWrite);
            MaxQSamples::Log(FString::Printf(TEXT("dafac result: %s"), ErrorMessage.IsEmpty() ? TEXT("OK") : *ErrorMessage, ResultCode));
        }

        // We compute SPK positions from now, through 30 days into the future,
        // at one day increments.
        auto Start = Now();
        FSEphemerisTime Stop = Start + 30 * FSEphemerisPeriod::OneDay;

        // We'll need the ID for the center of motion later
        int Center = 0;
        if (!Bods2c(Center, FString{ TEXT("TRAPPIST_1") }))
        {
            MaxQSamples::Log(TEXT("Could not look up TRAPPIST_1"), FColor::Red);
            ResultCode = ES_ResultCode::Error;
        }

        // Iterate through all the orbital elements we have in the map
        if (ResultCode == ES_ResultCode::Success)
        {
            for (const auto& [BodyName, ConicElements] : OrbitalElements)
            {
                // And, we'll need the ID of this body shortly
                int Body = 0;
                if (!Bods2c(Body, BodyName))
                {
                    MaxQSamples::Log(FString::Printf(TEXT("Could not look up %s"), *BodyName), FColor::Red);
                    ResultCode = ES_ResultCode::Error;
                }

                // We're going to make a series of "Observations" (State Vector & Epoch) and keep them
                // in an array.  Again, 30 of them, at one day intervals.
                FString segid;
                TArray<FSPKType5Observation> States{};

                for (int i = 0; i < 30; ++i)
                {

                    FSPKType5Observation Observation;

                    // The time for this observation...
                    Observation.et = Start + i * FSEphemerisPeriod::OneDay;

                    // Evaluate the orbit to get the associated state vector
                    USpice::conics(ResultCode, ErrorMessage, ConicElements, Observation.et, Observation.state);

                    // Add the observation to the array of observations for this object.
                    if (ResultCode == ES_ResultCode::Success)
                    {
                        States.Add(Observation);
                        UE_LOG(LogTemp, Log, TEXT("%s, %s"), *Observation.state.ToString(), *Observation.state.r.Normalized().ToString());
                    }
                    else
                    {
                        break;
                    }
                }

                // Add the SPK segment for this object, then onto the next one.
                if (ResultCode == ES_ResultCode::Success)
                {
                    USpice::spkw05(ResultCode, ErrorMessage, Handle, Body, Center, TEXT("TRAPPIST_1_ECLIPTIC"), Start, Stop, TEXT("TEST SEGMENT"), ConicElements.GravitationalParameter, States);
                }
            }

            // Close the file... (It may fail to open again for write if this doesn't happen)
            USpice::spkcls(ResultCode, ErrorMessage, Handle);

            if (ResultCode != ES_ResultCode::Success)
            {
                MaxQSamples::Log(FString::Printf(TEXT("spkcls file %s"), *WriteFilePath, ResultCode));
            }
        }
    }
}


//-----------------------------------------------------------------------------



void ASample06Actor::VeryFastSpeed()
{
    NormalSpeed();
    FasterSpeed();
    FasterSpeed();
    FasterSpeed();
    FasterSpeed();
    FasterSpeed();
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Silver, TEXT("Very Fast"));
}

void ASample06Actor::FasterSpeed()
{
    SolarSystemState.TimeScale *= 10.;
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Silver, TEXT("Faster"));
}

void ASample06Actor::SlowerSpeed()
{
    SolarSystemState.TimeScale *= 0.1;
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Silver, TEXT("Slower"));
}

void ASample06Actor::NormalSpeed()
{
    SolarSystemState.TimeScale = 1;
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Silver, TEXT("Normal Speed (1x)"));
}

void ASample06Actor::GoToNow()
{
    SolarSystemState.CurrentTime = Now();
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Silver, TEXT("Set time to Now"));
    NormalSpeed();
}

void ASample06Actor::Restart()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Silver, TEXT("Restart Time"));
    USampleUtilities::InitializeTime(SolarSystemState, false);
}


void ASample06Actor::TRAPPIST_1_SSB()
{
    OriginNaifName = "TRAPPIST_1_BARYCENTER";
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Purple, FString::Printf(TEXT("Set Observer to %s"), *OriginNaifName.ToString()));
}

void ASample06Actor::_1B()
{
    OriginNaifName = "TRAPPIST_1B";
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Purple, FString::Printf(TEXT("Set Observer to %s"), *OriginNaifName.ToString()));
}

void ASample06Actor::_1C()
{
    OriginNaifName = "TRAPPIST_1C";
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Purple, FString::Printf(TEXT("Set Observer to %s"), *OriginNaifName.ToString()));
}

void ASample06Actor::_1D()
{
    OriginNaifName = "TRAPPIST_1D";
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Purple, FString::Printf(TEXT("Set Observer to %s"), *OriginNaifName.ToString()));
}

void ASample06Actor::_1E()
{
    OriginNaifName = "TRAPPIST_1E";
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Purple, FString::Printf(TEXT("Set Observer to %s"), *OriginNaifName.ToString()));
}

void ASample06Actor::_1F()
{
    OriginNaifName = "TRAPPIST_1F";
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Purple, FString::Printf(TEXT("Set Observer to %s"), *OriginNaifName.ToString()));
}

void ASample06Actor::_1G()
{
    OriginNaifName = "TRAPPIST_1G";
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Purple, FString::Printf(TEXT("Set Observer to %s"), *OriginNaifName.ToString()));
}

void ASample06Actor::_1H()
{
    OriginNaifName = "TRAPPIST_1H";
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Purple, FString::Printf(TEXT("Set Observer to %s"), *OriginNaifName.ToString()));
}

void ASample06Actor::IAU_1()
{
    OriginReferenceFrame = "IAU_TRAPPIST_1";
    OriginNaifName = "TRAPPIST_1_BARYCENTER";
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, FString::Printf(TEXT("Set Frame to %s (body-fixed frame)"), *OriginReferenceFrame.ToString()));
}

void ASample06Actor::IAU_1B()
{
    OriginReferenceFrame = "IAU_TRAPPIST_1B";
    OriginNaifName = "TRAPPIST_1B";
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, FString::Printf(TEXT("Set Frame to %s (body-fixed frame)"), *OriginReferenceFrame.ToString()));
}

void ASample06Actor::IAU_1C()
{
    OriginReferenceFrame = "IAU_TRAPPIST_1C";
    OriginNaifName = "TRAPPIST_1C";
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, FString::Printf(TEXT("Set Frame to %s (body-fixed frame)"), *OriginReferenceFrame.ToString()));
}

void ASample06Actor::IAU_1D()
{
    OriginReferenceFrame = "IAU_TRAPPIST_1D";
    OriginNaifName = "TRAPPIST_1D";
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, FString::Printf(TEXT("Set Frame to %s (body-fixed frame)"), *OriginReferenceFrame.ToString()));
}

void ASample06Actor::IAU_1E()
{
    OriginReferenceFrame = "IAU_TRAPPIST_1E";
    OriginNaifName = "TRAPPIST_1E";
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, FString::Printf(TEXT("Set Frame to %s (body-fixed frame)"), *OriginReferenceFrame.ToString()));
}

void ASample06Actor::IAU_1F()
{
    OriginReferenceFrame = "IAU_TRAPPIST_1F";
    OriginNaifName = "TRAPPIST_1F";
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, FString::Printf(TEXT("Set Frame to %s (body-fixed frame)"), *OriginReferenceFrame.ToString()));
}

void ASample06Actor::IAU_1G()
{
    OriginReferenceFrame = "IAU_TRAPPIST_1G";
    OriginNaifName = "TRAPPIST_1G";
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, FString::Printf(TEXT("Set Frame to %s (body-fixed frame)"), *OriginReferenceFrame.ToString()));
}

void ASample06Actor::IAU_1H()
{
    OriginReferenceFrame = "IAU_TRAPPIST_1H";
    OriginNaifName = "TRAPPIST_1H";
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, FString::Printf(TEXT("Set Frame to %s (body-fixed frame)"), *OriginReferenceFrame.ToString()));
}

void ASample06Actor::TRAPPIST_ECLIPTIC()
{
    OriginReferenceFrame = "TRAPPIST_1_ECLIPTIC";
    ResetYawPitch();
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("Set Frame to %s (inertial frame)"), *OriginReferenceFrame.ToString()));
}

void ASample06Actor::View_From_EARTH()
{
    OriginReferenceFrame = "TRAPPIST_1_EYE";
    ResetYawPitch();
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("Set Frame to %s (inertial frame)"), *OriginReferenceFrame.ToString()));
}

void ASample06Actor::ECLIPTIC_POLE()
{
    OriginReferenceFrame = "TRAPPIST_1_ECLIPTIC_POLE";
    ResetYawPitch();
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("Set Frame to %s (inertial frame)"), *OriginReferenceFrame.ToString()));
}


void ASample06Actor::ResetYawPitch_Implementation()
{

}


namespace MaxQSamples::Data
{
    //-----------------------------------------------------------------------------
    // Hardcoded TRAPPIST-1 System Data
    //-----------------------------------------------------------------------------

    // Values for e, sma, i obtained from:
    // https://en.wikipedia.org/wiki/TRAPPIST-1
    constexpr auto TRAPPIST_1_GM = 1.19175771158E+10;
    constexpr auto TRAPPIST_1B_e = 0.00622;
    constexpr auto TRAPPIST_1C_e = 0.00654;
    constexpr auto TRAPPIST_1D_e = 0.00837;
    constexpr auto TRAPPIST_1E_e = 0.00510;
    constexpr auto TRAPPIST_1F_e = 0.01007;
    constexpr auto TRAPPIST_1G_e = 0.00208;
    constexpr auto TRAPPIST_1H_e = 0.00567;

    // We could (should?) load the kernel files & get the value from there...
    static const FSMassConstant Trappist1GM{ TRAPPIST_1_GM };

    constexpr double sma2rp(double e, double sma)
    {
        constexpr auto au2km = 1.495978707E8;
        return (1. - e) * sma * au2km;
    }

    static const TMap<FString, FSConicElements> Trappist1OrbitalElements
    {
        TMap<FString,FSConicElements>::ElementType
        {
            TEXT("TRAPPIST_1B"),
            FSConicElements
            {
                sma2rp(TRAPPIST_1B_e, 0.01154), // PerifocalDistance
                TRAPPIST_1B_e,                  // Eccentricity
                FSAngle::FromDegrees(89.728),   // Inclination
                FSAngle::FromDegrees(0),        // LongitudeOfAscendingNode
                FSAngle::FromDegrees(0),        // ArgumentOfPeriapse
                FSAngle::FromDegrees(0),        // MeanAnomalyAtEpoch
                FSEphemerisTime::J2000,         // Epoch
                Trappist1GM                     // GravitationalParameter
            }
        },
        TMap<FString,FSConicElements>::ElementType
        {
            TEXT("TRAPPIST_1C"),
            FSConicElements
            {
                sma2rp(TRAPPIST_1C_e, 0.01580), // PerifocalDistance
                TRAPPIST_1C_e,                  // Eccentricity
                FSAngle::FromDegrees(89.778),   // Inclination
                FSAngle::FromDegrees(0),        // LongitudeOfAscendingNode
                FSAngle::FromDegrees(0),        // ArgumentOfPeriapse
                FSAngle::FromDegrees(0),        // MeanAnomalyAtEpoch
                FSEphemerisTime::J2000,         // Epoch
                Trappist1GM                     // GravitationalParameter
            }
        },
        TMap<FString,FSConicElements>::ElementType
        {
            TEXT("TRAPPIST_1D"),
            FSConicElements
            {
                sma2rp(TRAPPIST_1D_e, 0.02227), // PerifocalDistance
                TRAPPIST_1D_e,                  // Eccentricity
                FSAngle::FromDegrees(89.896),   // Inclination
                FSAngle::FromDegrees(0),        // LongitudeOfAscendingNode
                FSAngle::FromDegrees(0),        // ArgumentOfPeriapse
                FSAngle::FromDegrees(0),        // MeanAnomalyAtEpoch
                FSEphemerisTime::J2000,         // Epoch
                Trappist1GM                     // GravitationalParameter
            }
        },
        TMap<FString,FSConicElements>::ElementType
        {
            TEXT("TRAPPIST_1E"),
            FSConicElements
            {
                sma2rp(TRAPPIST_1E_e, 0.02925), // PerifocalDistance
                TRAPPIST_1E_e,                  // Eccentricity
                FSAngle::FromDegrees(89.793),   // Inclination
                FSAngle::FromDegrees(0),        // LongitudeOfAscendingNode
                FSAngle::FromDegrees(0),        // ArgumentOfPeriapse
                FSAngle::FromDegrees(0),        // MeanAnomalyAtEpoch
                FSEphemerisTime::J2000,         // Epoch
                Trappist1GM                     // GravitationalParameter
            }
        },
        TMap<FString,FSConicElements>::ElementType
        {
            TEXT("TRAPPIST_1F"),
            FSConicElements
            {
                sma2rp(TRAPPIST_1F_e, 0.03849), // PerifocalDistance
                TRAPPIST_1F_e,                  // Eccentricity
                FSAngle::FromDegrees(89.740),   // Inclination
                FSAngle::FromDegrees(0),        // LongitudeOfAscendingNode
                FSAngle::FromDegrees(0),        // ArgumentOfPeriapse
                FSAngle::FromDegrees(0),        // MeanAnomalyAtEpoch
                FSEphemerisTime::J2000,         // Epoch
                Trappist1GM                     // GravitationalParameter
            }
        },
        TMap<FString,FSConicElements>::ElementType
        {
            TEXT("TRAPPIST_1G"),
            FSConicElements
            {
                sma2rp(TRAPPIST_1G_e, 0.04683), // PerifocalDistance
                TRAPPIST_1G_e,                  // Eccentricity
                FSAngle::FromDegrees(89.742),   // Inclination
                FSAngle::FromDegrees(0),        // LongitudeOfAscendingNode
                FSAngle::FromDegrees(0),        // ArgumentOfPeriapse
                FSAngle::FromDegrees(0),        // MeanAnomalyAtEpoch
                FSEphemerisTime::J2000,         // Epoch
                Trappist1GM                     // GravitationalParameter
            }
        },
        TMap<FString,FSConicElements>::ElementType
        {
            TEXT("TRAPPIST_1H"),
            FSConicElements
            {
                sma2rp(TRAPPIST_1H_e, 0.06189), // PerifocalDistance
                TRAPPIST_1H_e,                  // Eccentricity
                FSAngle::FromDegrees(89.805),   // Inclination
                FSAngle::FromDegrees(0),        // LongitudeOfAscendingNode
                FSAngle::FromDegrees(0),        // ArgumentOfPeriapse
                FSAngle::FromDegrees(0),        // MeanAnomalyAtEpoch
                FSEphemerisTime::J2000,         // Epoch
                Trappist1GM                     // GravitationalParameter
            }
        }
    };
}

const TMap<FString, FSConicElements>& ASample06Actor::GetTrappist1OrbitalElements()
{
    return MaxQSamples::Data::Trappist1OrbitalElements;
}

