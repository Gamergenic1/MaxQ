// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tutorial01Actor.generated.h"

// Tutorial01 - Initialization and kernel data
// * init_all
// * furnsh
// * enumerate_kernels
// * furnsh_list
// * bodvrd, bodvcd, gdpool, etc

UCLASS()
class MAXQCPPTUTORIAL_API ATutorial01Actor : public AActor
{
    GENERATED_BODY()

public:
    ATutorial01Actor();

    void BeginPlay() override;

    void InitializeSpice();
    bool LoadGMKernel(bool Squawk = true);
    void EnumeratePCKKernels();
    bool EnumerateAndLoadPCKKernelList(bool Squawk = true);
    void QueryEarthsGM();
    void QueryEarthsRadius();
};


