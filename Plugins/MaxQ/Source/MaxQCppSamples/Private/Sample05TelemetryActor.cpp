// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "Sample05TelemetryActor.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "SpiceTypes.h"
#include "Spice.h"
#include "SampleUtilities.h"

using MaxQSamples::Log;


ASample05TelemetryActor::ASample05TelemetryActor()
{
    // For a lot of telemetry objects (asteroids, NEO debris), we might use one instanced mesh for all of them.
    // In this case we'll use individual Actors with name labels.
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Root");
    SetRootComponent(MeshComponent);

    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickGroup = ETickingGroup::TG_PostPhysics;

    VelocityBumpFraction = 0.01;
}


//-----------------------------------------------------------------------------
// Name: BeginPlay
// Desc: 
//-----------------------------------------------------------------------------
void ASample05TelemetryActor::BeginPlay()
{
    Super::BeginPlay();
}



void ASample05TelemetryActor::Init(const FString& NewObjectId, const FString& NewObjectName, const FSTwoLineElements& NewTLEs, bool bNewShouldRenderOrbit)
{
    ObjectId = NewObjectId;
    ObjectName = NewObjectName;
    TLElements = NewTLEs;
    bShouldRenderOrbit = false;

    if (NametagWidgetInstance.Get() == nullptr && NametagWidgetClass && GetNetMode() != ENetMode::NM_DedicatedServer)
    {
        USampleNametagWidget* Nametag = CreateWidget<USampleNametagWidget>(GetWorld()->GetFirstPlayerController(), NametagWidgetClass);

        if (Nametag)
        {
            Nametag->Init(ObjectName, PositionUpdate, VisibilityUpdate);
        }

        NametagWidgetInstance = Nametag;
        VisibilityUpdate.ExecuteIfBound(false);

        if (ComputeConic.IsBound())
        {
            FSStateVector StateVector;
            
            if (PropagateByTLEs.Execute(TLElements, StateVector))
            {
                if (ComputeConic.Execute(StateVector, OrbitalConic, bIsHyperbolic))
                {
                    bShouldRenderOrbit = bNewShouldRenderOrbit;
                }
            }
        }
    }
}


//-----------------------------------------------------------------------------
// Name: Tick
// Desc: 
//-----------------------------------------------------------------------------
void ASample05TelemetryActor::Tick(float DeltaSeconds)
{
    if (PropagateStateByTLEs)
    {
        PropagateTLE();
    }
    else
    {
        PropagateKepler();
    }

    bool bVisible = true;

    if (GetNetMode() != ENetMode::NM_DedicatedServer)
    {
        // Dirty hack cheat... Knowing the view is centered around the origin
        APlayerController* PC = GetWorld()->GetFirstPlayerController();
        if (PC && PC->PlayerCameraManager)
        {
            FVector CameraLocation = PC->PlayerCameraManager->GetCameraLocation();
            FVector MyLocation = GetActorLocation();
            FVector LookDirection = MyLocation - CameraLocation;

            bVisible = LookDirection.Dot(MyLocation) < 0;
            if (bWasVisible ^ bVisible)
            {
                VisibilityUpdate.ExecuteIfBound(bVisible);
                bWasVisible = bVisible;
            }
        }
    }

    if (RenderDebugOrbit.IsBound() && bShouldRenderOrbit)
    {
        RenderDebugOrbit.Execute(OrbitalConic, bIsHyperbolic, PropagateStateByTLEs ? FColor::Red : FColor::Yellow, PropagateStateByTLEs ? 0.2f : 0.5f);
    }
}

//-----------------------------------------------------------------------------
// Name: Tick
// Desc: 
//-----------------------------------------------------------------------------
void ASample05TelemetryActor::PropagateTLE()
{
    if (PropagateByTLEs.IsBound() && XformPositionCallback.IsBound())
    {
        FSStateVector StateVector;
        bool bResult = PropagateByTLEs.Execute(TLElements, StateVector);

        FVector UEScenegraphVector;
        bResult &= XformPositionCallback.Execute(StateVector.r, UEScenegraphVector);

        if (bResult)
        {
            SetActorLocation(UEScenegraphVector);
            PositionUpdate.ExecuteIfBound(UEScenegraphVector);
        }
    }
}

//-----------------------------------------------------------------------------
// Name: Tick
// Desc: 
//-----------------------------------------------------------------------------
void ASample05TelemetryActor::PropagateKepler()
{

    if (PropagateByKeplerianElements.IsBound() && XformPositionCallback.IsBound())
    {
        FSStateVector StateVector;
        if (PropagateByKeplerianElements.Execute(KeplerianElements, StateVector))
        {
            FVector UEScenegraphVector;
            if (XformPositionCallback.Execute(StateVector.r, UEScenegraphVector))
            {
                SetActorLocation(UEScenegraphVector);
                PositionUpdate.ExecuteIfBound(UEScenegraphVector);
            }
        }
    }
}


void ASample05TelemetryActor::GoKeplerian()
{
    if (PropagateStateByTLEs && PropagateByTLEs.IsBound())
    {
        FSStateVector StateVector;
        bool bResult = PropagateByTLEs.Execute(TLElements, StateVector);

        if (bResult)
        {
            bResult &= GetOrbitalElements.Execute(StateVector, KeplerianElements);
        }

        if (bResult)
        {
            PropagateStateByTLEs = false;
        }

        bShouldRenderOrbit = true;
    }
}

void ASample05TelemetryActor::BumpVelocity(const FSVelocityVector& Direction)
{
    if (PropagateByKeplerianElements.IsBound() && GetOrbitalElements.IsBound() && GetConicFromKepler.IsBound())
    {
        GoKeplerian();

        FSStateVector StateVector;
        if (!PropagateStateByTLEs && PropagateByKeplerianElements.Execute(KeplerianElements, StateVector))
        {
            StateVector.v += Direction;
            
            if (GetOrbitalElements.Execute(StateVector, KeplerianElements))
            {
                GetConicFromKepler.Execute(KeplerianElements, OrbitalConic, bIsHyperbolic);
            }
        }
    }
}

void ASample05TelemetryActor::BumpPrograde()
{
    if(PropagateByKeplerianElements.IsBound())
    {
        GoKeplerian();

        FSStateVector StateVector;
        if (PropagateByKeplerianElements.Execute(KeplerianElements, StateVector))
        {
            BumpVelocity(StateVector.v * VelocityBumpFraction);
        }
    }
}

void ASample05TelemetryActor::BumpRetrograde()
{
    if (PropagateByKeplerianElements.IsBound())
    {
        GoKeplerian();

        FSStateVector StateVector;
        if (PropagateByKeplerianElements.Execute(KeplerianElements, StateVector))
        {
            BumpVelocity(-StateVector.v * VelocityBumpFraction);
        }
    }
}

void ASample05TelemetryActor::BumpRadial()
{
    if (PropagateByKeplerianElements.IsBound())
    {
        GoKeplerian();

        FSStateVector StateVector;
        if (PropagateByKeplerianElements.Execute(KeplerianElements, StateVector))
        {
            FSDimensionlessVector Radial;
            FSDistance Speed;
            USpice::unorm_distance(StateVector.r, Radial, Speed);
            FSVelocityVector bump = VelocityBumpFraction * StateVector.v.Magnitude() * Radial;

            BumpVelocity(bump);
        }
    }
}

void ASample05TelemetryActor::BumpAntiRadial()
{
    if (PropagateByKeplerianElements.IsBound())
    {
        GoKeplerian();

        FSStateVector StateVector;
        if (PropagateByKeplerianElements.Execute(KeplerianElements, StateVector))
        {
            FSDimensionlessVector Radial;
            FSDistance Speed;
            USpice::unorm_distance(StateVector.r, Radial, Speed);
            FSVelocityVector bump = -VelocityBumpFraction * Radial * StateVector.v.Magnitude();

            BumpVelocity(bump);
        }
    }
}

void ASample05TelemetryActor::BumpNormal()
{
    if (PropagateByKeplerianElements.IsBound() && GetOrbitalElements.IsBound() && GetConicFromKepler.IsBound())
    {
        GoKeplerian();

        FSStateVector StateVector;
        if (PropagateByKeplerianElements.Execute(KeplerianElements, StateVector))
        {
            FSDimensionlessVector Radial = StateVector.r.AsKilometers();
            FSDimensionlessVector Prograde = StateVector.v.AsKilometersPerSecond();
            FSDimensionlessVector Normal;
            USpice::ucrss(Radial, Prograde, Normal);

            FSVelocityVector bump = VelocityBumpFraction * Normal * StateVector.v.Magnitude();
            BumpVelocity(bump);
        }
    }
}

void ASample05TelemetryActor::BumpAntiNormal()
{
    if (PropagateByKeplerianElements.IsBound() && GetOrbitalElements.IsBound() && GetConicFromKepler.IsBound())
    {
        GoKeplerian();

        FSStateVector StateVector;
        if (PropagateByKeplerianElements.Execute(KeplerianElements, StateVector))
        {
            FSDimensionlessVector Radial = StateVector.r.AsKilometers();
            FSDimensionlessVector Prograde = StateVector.v.AsKilometersPerSecond();
            FSDimensionlessVector Normal;
            USpice::ucrss(Radial, Prograde, Normal);

            FSVelocityVector bump = -VelocityBumpFraction * Normal * StateVector.v.Magnitude();
            BumpVelocity(bump);
        }
    }
}
