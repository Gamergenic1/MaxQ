// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sample01Actor.generated.h"


//-----------------------------------------------------------------------------
// Sample01
// Initialization and kernel data
//-----------------------------------------------------------------------------

UCLASS(HideCategories = (Transform, Rendering, Replication, Collision, HLOD, Input, Actor, Advanced, Cooking))
class MAXQCPPSAMPLES_API ASample01Actor : public AActor
{
    GENERATED_BODY()

    // Paths must work:
    // * For game content in PIE mode
    // * For game content in packaged builds
    //     Note that for packaged builds you will need to add the kernel directories
    //     To the editor config for copying raw directories
    //     See:   DefaultGame.ini
    //            [/Script/UnrealEd.ProjectPackagingSettings]
    //            +DirectoriesToAlwaysStageAsNonUFS=(Path="Spice")
    // * For plugin content in PIE mode
    // * For plugin content in packaged builds (?)
    // There's no good way of handling this with FFilePath/FDirectoryPath.
    // MaxQ will first check paths relative to project, then in editor builds
    // Check if they were realative to plugin directory
    UPROPERTY(EditInstanceOnly, Category="MaxQ|Samples")
    FString RelativePathToGMKernel;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples", meta = (ContentDir))
    FDirectoryPath RelativePathToPCKKernels;

    UPROPERTY(EditInstanceOnly, Category = "MaxQ|Samples")
    double KilometersPerScenegraphUnit;

public:
    ASample01Actor();

    void BeginPlay() override;

    void InitializeSpice();
    bool LoadGMKernel(bool Squawk = true);
    void EnumeratePCKKernels();
    bool EnumerateAndLoadPCKKernelList(bool Squawk = true);
    void QueryEarthsGM();
    void QueryEarthsRadius();
    void DumpKernelDiagnostics();
    void ScaleAllBodies();
};


