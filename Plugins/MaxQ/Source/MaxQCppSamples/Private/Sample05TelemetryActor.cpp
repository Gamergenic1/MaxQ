// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "Sample05TelemetryActor.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "Spice.h"
#include "SampleUtilities.h"

using MaxQSamples::Log;
using namespace MaxQ::Data;
using namespace MaxQ::Core;
using namespace MaxQ::Constants;
using namespace MaxQ::Math;


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


//-----------------------------------------------------------------------------
// Name: Init
// Desc: Initialize this object with data (it's name, etc.)
//-----------------------------------------------------------------------------
void ASample05TelemetryActor::Init(const FString& NewObjectId, const FString& NewObjectName, const FSTwoLineElements& NewTLEs, bool bNewShouldRenderOrbit)
{
    ObjectId = NewObjectId;
    ObjectName = NewObjectName;
    TLElements = NewTLEs;
    bShouldRenderOrbit = false;

    // Create the Nametag UI-widget.
    if (NametagWidgetInstance.Get() == nullptr && NametagWidgetClass && GetNetMode() != ENetMode::NM_DedicatedServer)
    {
        USampleNametagWidget* Nametag = CreateWidget<USampleNametagWidget>(GetWorld()->GetFirstPlayerController(), NametagWidgetClass);

        if (Nametag)
        {
            // The nametag needs to know:
            // 1. The object's name.
            // 2. When the position updates.
            // 3. When the nametag is visible or hidden behind the planet
            Nametag->Init(ObjectName, PositionUpdate, VisibilityUpdate);
        }

        // Initially hide the nametag until we know otherwise.
        NametagWidgetInstance = Nametag;
        VisibilityUpdate.ExecuteIfBound(false);

        // Use the telemetry to compute a state vector (location & velocity)
        if (ComputeConic.IsBound())
        {
            FSStateVector StateVector;
            
            // Compute the shape of the orbit (conic: ellipse or hyperbola)
            // This will be used to render the orbit if desired.
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
// Desc: Tok
//-----------------------------------------------------------------------------
void ASample05TelemetryActor::Tick(float DeltaSeconds)
{
    // Which mode are we in?  Propagate accordingly
    if (PropagateStateByTLEs)
    {
        PropagateTLE();
    }
    else
    {
        PropagateKepler();
    }

    bool bVisible = true;

    // Don't bother unless this is a client/listen server...
    // But fade the object's label out unless it's near the front of the
    // planet... don't let it be so visible behind it.
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

    // Render the debug orbit for a sub-set of objects.
    // Debug orbit rendering is SLOW.
    if (RenderDebugOrbit.IsBound() && bShouldRenderOrbit)
    {
        RenderDebugOrbit.Execute(OrbitalConic, bIsHyperbolic, PropagateStateByTLEs ? FColor::Red : FColor::Yellow, PropagateStateByTLEs ? 0.2f : 0.5f);
    }
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: PropagateTLE
// Desc:
// Call the main actor, which owns the state to propagate the orbit by
// "Two Line Element"
//-----------------------------------------------------------------------------

void ASample05TelemetryActor::PropagateTLE()
{
    // Sample05Actor owns the state of the universe... the current time, etc
    // Instead of pulling thee state from there or pushing it to here,
    // have that actor do the propagating etc.
    if (PropagateByTLEs.IsBound() && XformPositionCallback.IsBound())
    {
        FSStateVector StateVector;
        bool bResult = PropagateByTLEs.Execute(TLElements, StateVector);

        // We got an orbital state vector (location etc)
        // So transform it to a UE position and place the actor.
        FVector UEScenegraphVector;
        bResult &= XformPositionCallback.Execute(StateVector.r, UEScenegraphVector);

        if (bResult)
        {
            SetActorLocation(UEScenegraphVector);
            PositionUpdate.ExecuteIfBound(UEScenegraphVector);
        }
    }
}


// ============================================================================
//
//-----------------------------------------------------------------------------
// Name: PropagateKepler
// Desc:
// Call the main actor, which owns the state to propagate the orbit by
// "classical" orbital elements.
//-----------------------------------------------------------------------------

void ASample05TelemetryActor::PropagateKepler()
{
    // Same deal as above (PropagateTLE) about the state of the universe etc.
    if (PropagateByKeplerianElements.IsBound() && XformPositionCallback.IsBound())
    {
        FSStateVector StateVector;
        if (PropagateByKeplerianElements.Execute(KeplerianElements, StateVector))
        {
            // Transform the state to a UE position and place the actor.
            FVector UEScenegraphVector;
            if (XformPositionCallback.Execute(StateVector.r, UEScenegraphVector))
            {
                SetActorLocation(UEScenegraphVector);
                PositionUpdate.ExecuteIfBound(UEScenegraphVector);
            }
        }
    }
}



//-----------------------------------------------------------------------------

// Support for debug buttons (see the object's Details panel, in the editor)

//-----------------------------------------------------------------------------
// Name: GoKeplerian
// Desc:
// Stop updating by TLE, switch to orbital params...     
//-----------------------------------------------------------------------------
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
        {   // No more updating by TLEs!  Go Kepler!
            PropagateStateByTLEs = false;
        }
        
        // Start rendering this orbit, if we're not already.
        bShouldRenderOrbit = true;
    }
}


//-----------------------------------------------------------------------------
// Name: BumpVelocity
// Desc:
// Modify the state vector to add velocity.
// Update the orbital params and the debug orbit accordingly.
//-----------------------------------------------------------------------------
void ASample05TelemetryActor::BumpVelocity(const FSVelocityVector& Direction)
{
    if (PropagateByKeplerianElements.IsBound() && GetOrbitalElements.IsBound() && GetConicFromKepler.IsBound())
    {
        // Make sure the orbital elements are valid.
        GoKeplerian();

        // Compute the current statevector from orbital elements.
        FSStateVector StateVector;
        if (!PropagateStateByTLEs && PropagateByKeplerianElements.Execute(KeplerianElements, StateVector))
        {
            // Adjust the velocity.
            StateVector.v += Direction;
            
            // Now recompute the new orbital elements
            if (GetOrbitalElements.Execute(StateVector, KeplerianElements))
            {
                // And update the debug-orbit conic (ellipse/hyperbola) for orbit rendering
                GetConicFromKepler.Execute(KeplerianElements, OrbitalConic, bIsHyperbolic);
            }
        }
    }
}


//-----------------------------------------------------------------------------
// Name: BumpPrograde
// Desc:
// Add some velocity in the direction of travel (velocity)
//-----------------------------------------------------------------------------
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


//-----------------------------------------------------------------------------
// Name: BumpRetrograde
// Desc:
// Add some velocity opposite of the direction of travel (velocity)
//-----------------------------------------------------------------------------
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


//-----------------------------------------------------------------------------
// Name: BumpRadial
// Desc:
// Add some velocity away from the planet ("up", as laypeople say.)
//-----------------------------------------------------------------------------
void ASample05TelemetryActor::BumpRadial()
{
    if (PropagateByKeplerianElements.IsBound())
    {
        GoKeplerian();

        FSStateVector StateVector;
        if (PropagateByKeplerianElements.Execute(KeplerianElements, StateVector))
        {
            FSDistance Speed;
            auto Radial = Unorm(Speed, StateVector.r);
            FSVelocityVector bump = VelocityBumpFraction * StateVector.v.Magnitude() * Radial;

            BumpVelocity(bump);
        }
    }
}


//-----------------------------------------------------------------------------
// Name: BumpAntiRadial
// Desc:
// Add some velocity towards the planet ("down")
//-----------------------------------------------------------------------------
void ASample05TelemetryActor::BumpAntiRadial()
{
    if (PropagateByKeplerianElements.IsBound())
    {
        GoKeplerian();

        FSStateVector StateVector;
        if (PropagateByKeplerianElements.Execute(KeplerianElements, StateVector))
        {
            FSDistance Speed;
            auto Radial = Unorm(Speed, StateVector.r);
            FSVelocityVector bump = -VelocityBumpFraction * Radial * StateVector.v.Magnitude();

            BumpVelocity(bump);
        }
    }
}



//-----------------------------------------------------------------------------
// Name: BumpNormal
// Desc:
// Add some velocity in the direction ortho/normal to the orbital plane
// (towards north pole)
//-----------------------------------------------------------------------------
void ASample05TelemetryActor::BumpNormal()
{
    if (PropagateByKeplerianElements.IsBound() && GetOrbitalElements.IsBound() && GetConicFromKepler.IsBound())
    {
        GoKeplerian();

        FSStateVector StateVector;
        if (PropagateByKeplerianElements.Execute(KeplerianElements, StateVector))
        {
            auto Normal = Ucrss(StateVector);

            FSVelocityVector bump = VelocityBumpFraction * Normal * StateVector.v.Magnitude();
            BumpVelocity(bump);
        }
    }
}


//-----------------------------------------------------------------------------
// Name: BumpAntiNormal
// Desc:
// Add some velocity in the direction ortho/normal to the orbital plane
// (towards south pole)
//-----------------------------------------------------------------------------

void ASample05TelemetryActor::BumpAntiNormal()
{
    if (PropagateByKeplerianElements.IsBound() && GetOrbitalElements.IsBound() && GetConicFromKepler.IsBound())
    {
        GoKeplerian();

        FSStateVector StateVector;
        if (PropagateByKeplerianElements.Execute(KeplerianElements, StateVector))
        {
            auto Normal = Ucrss(StateVector);

            FSVelocityVector bump = -VelocityBumpFraction * Normal * StateVector.v.Magnitude();
            BumpVelocity(bump);
        }
    }
}
