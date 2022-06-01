// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

#include "SpiceOrbits.h"
#include "DrawDebugHelpers.h"
#include "SpiceUtilities.h"
using namespace SpiceUtilities;

PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
extern "C"
{
#include "SpiceUsr.h"
}
PRAGMA_POP_PLATFORM_DEFAULT_PACKING


USpiceOrbits::USpiceOrbits()
{

}

void USpiceOrbits::EvaluateOrbit(
    ES_ResultCode& ResultCode,
    FString& ErrorMessage,
    FSStateVector& state,
    const FSEphemerisTime& et,
    const FSConicElements& orbit,
    const FString& orbitReferenceFrame,
    const FString& observerReferenceFrame
)
{
    // Inputs
    SpiceDouble _elts[8];	orbit.CopyTo(_elts);
    SpiceDouble _et = et.seconds;
    // Outputs
    SpiceDouble _state[6];	memset(_state, 0, sizeof(_state));

    // Invocation
    conics_c(_elts, _et, _state);

    if (orbitReferenceFrame.Compare(observerReferenceFrame, ESearchCase::IgnoreCase))
    {
        double m[3][3];
        pxform_c(TCHAR_TO_ANSI(*orbitReferenceFrame), TCHAR_TO_ANSI(*observerReferenceFrame), et.AsSpiceDouble(), m);

        // Clear any errors if necessary
        ErrorCheck(ResultCode, ErrorMessage);

        if (ResultCode == ES_ResultCode::Success)
        {
            /*
            *  CSpice docs:
                Particulars
                   The intermediate results of the operation performed by this routine
                   are buffered in a temporary vector which is later moved to the output
                   vector.  Thus vout can be actually be vin if desired without
                   interfering with the computation.
            */

            mxv_c(m, &_state[0], &_state[0]);
            mxv_c(m, &_state[3], &_state[3]);
        }
    }


    // Return Value
    state = FSStateVector(_state);

    // Error Handling
    ErrorCheck(ResultCode, ErrorMessage);
}

void USpiceOrbits::RenderDebugConic(
    const AActor* actor,
    const FSEllipse& conic,
    bool isHyperbolic,
    const FTransform& localTransform,
    const FColor& color,
    float thickness
)
{
    if (isHyperbolic)
    {
        RenderDebugHyperbola(actor->GetWorld(), conic, localTransform, color, thickness);
    }
    else
    {
        RenderDebugEllipse(actor->GetWorld(), conic, localTransform, color, thickness);
    }
}


void USpiceOrbits::RenderDebugOrbit(
    const AActor* actor,
    const FTransform& localTransform,
    const FSEphemerisTime& et,
    const FSConicElements& orbit,
    const FString& orbitReferenceFrame,
    const FString& observerReferenceFrame,
    const FColor& color,
    float thickness
)
{
    FSEllipse conic = FSEllipse();
    bool isHyperbolic;
    ComputeConic(conic, isHyperbolic, et,  orbit, orbitReferenceFrame, observerReferenceFrame);
    RenderDebugConic(actor, conic, isHyperbolic, localTransform, color, thickness);
}

void USpiceOrbits::ComputeConic(
    FSEllipse& ellipse,
    bool& isHyperbolic,
    const FSEphemerisTime& et,
    const FSConicElements& orbit,
    const FString& orbitReferenceFrame,
    const FString& observerReferenceFrame
    )
{
    double q, ecc, inc, lnode, argp;

    q = orbit.PerifocalDistance.AsSpiceDouble();
    ecc = orbit.Eccentricity;
    inc = orbit.Inclination.AsSpiceDouble();
    lnode = orbit.LongitudeOfAscendingNode.AsSpiceDouble();
    argp = orbit.ArgumentOfPeriapse.AsSpiceDouble();


    double ae, a, b, r[3][3];

    // Orbit's rotation matrix is a ZXZ euler multiplication
    eul2m_c(argp, inc, lnode, 3, 1, 3, r);

    if (!orbitReferenceFrame.Equals(observerReferenceFrame, ESearchCase::IgnoreCase))
    {
        double m[3][3];
        pxform_c(TCHAR_TO_ANSI(*orbitReferenceFrame), TCHAR_TO_ANSI(*observerReferenceFrame), et.AsSpiceDouble(), m);

        // Clear any errors if necessary
        ES_ResultCode ResultCode;
        FString ErrorMessage;
        ErrorCheck(ResultCode, ErrorMessage);

        if (ResultCode == ES_ResultCode::Success)
        {
            /*
            *  CSpice docs:
                Particulars
                    The intermediate results of the operation above are buffered in a
                    temporary matrix which is later moved to the output matrix.
                    Thus, to save space in the calling program, mout can be actually
                    be m1 or m2 if desired without interfering with the computations.
            */

            mxmt_c(r, m, r);
        }
    }

    // the semi-major axis length is determined by the perifocal distance
    a = q / (1 - ecc);

    // As is the semi-minor axis 
    b = a * sqrt( abs(1 - ecc * ecc) );

    // The conic is hyperbolic < 0, parabolic == 0, and elliptical > 0.
    // We are ignorant of parabolic possibilities.
    isHyperbolic = a <= 0;

    // displace the ellipse center or hyperbolic "center" by a * e * q^
    ae = a * ecc;
    ellipse.center = FSDistanceVector(-ae * r[0][0], -ae * r[0][1], -ae * r[0][2]);;

    // semi-major axis is a * q^
    ellipse.v_major = FSDistanceVector(a * r[0][0], a * r[0][1], a * r[0][2]);

    // semi-minor axis is b * q^
    ellipse.v_minor = FSDistanceVector(b * r[1][0], b * r[1][1], b * r[1][2]);
}


void USpiceOrbits::MakeSPKObservation(
    const FSConicElements& orbit,
    const FSDimensionlessVector& poleVectorOfCentralBody,
    const FSDistance& equatorialRadiusOfCentralBody,
    FSPKType15Observation& observation
)
{
    double q, ecc, inc, lnode, argp;

    q = orbit.PerifocalDistance.AsSpiceDouble();
    ecc = orbit.Eccentricity;
    inc = orbit.Inclination.AsSpiceDouble();
    lnode = orbit.LongitudeOfAscendingNode.AsSpiceDouble();
    argp = orbit.ArgumentOfPeriapse.AsSpiceDouble();

    double r[3][3];

    // Orbit's rotation matrix is a ZXZ euler multiplication
    eul2m_c(argp, inc, lnode, 3, 1, 3, r);

    double a = q / (1 - ecc);

    double gm = orbit.GravitationalParameter.AsSpiceDouble();

    double timeSincePeriapsis = orbit.MeanAnomalyAtEpoch.AsSpiceDouble() * sqrt(a * a * a / gm);

    observation = FSPKType15Observation();
    observation.epoch = FSEphemerisTime(orbit.Epoch.AsSpiceDouble() - timeSincePeriapsis);
    observation.tp = FSDimensionlessVector(r[1][0], r[1][1], r[1][2]);
    observation.pa = FSDimensionlessVector(r[0][0], r[0][1], r[0][2]);
    observation.p = (1. + ecc) * orbit.PerifocalDistance;
    observation.ecc = ecc;
    observation.j2flg = 3;
    observation.pv = poleVectorOfCentralBody;
    observation.gm = orbit.GravitationalParameter;
    observation.j2 = 0;
    observation.radius = equatorialRadiusOfCentralBody;
}


void USpiceOrbits::RenderDebugEllipse(const UWorld* world, const FSEllipse& ellipse, const FTransform& localTransform, const FColor& color, float thickness)
{
    for (double theta = 0.f; theta <= 360.f; )
    {
        float rads = rpd * theta;
        double _cos = cos(rads);
        double _sin = sin(rads);
        FVector  p1 = localTransform.TransformPosition(
            USpiceTypes::Conv_SDistanceVectorToVector(
                ellipse.center + _cos * ellipse.v_major + _sin * ellipse.v_minor
            ));

        theta += 0.25f;

        rads = rpd * theta;
        _cos = cos(rads);
        _sin = sin(rads);

        // It's not efficient to recalculate since we just calculated it last iteration...
        // ...But this is a debug function anyways
        FVector p2 = localTransform.TransformPosition(
            USpiceTypes::Conv_SDistanceVectorToVector(
                ellipse.center + _cos * ellipse.v_major + _sin * ellipse.v_minor
            ));

        DrawDebugLine(world, p1, p2, color, false, -1.f, 0, thickness );
    }
}


void USpiceOrbits::RenderDebugHyperbola(const UWorld* world, const FSEllipse& ellipse, const FTransform& localTransform, const FColor& color, float thickness)
{
    double sign = 1.;

    for (double theta =-360.; theta <= 360.; )
    {
        double rads = rpd * theta;
        double _cosh = sign * cosh(rads);
        double _sinh = sign * sinh(rads);
        FVector  p1 = localTransform.TransformPosition(
            USpiceTypes::Conv_SDistanceVectorToVector(
                ellipse.center + _cosh * ellipse.v_major + _sinh * ellipse.v_minor
            ));

        theta += 0.25;

        // It's not efficient to recalculate since we just calculated it last iteration...
        // ...But this is a debug function anyways
        rads = rpd * theta;
        _cosh = sign * cosh(rads);
        _sinh = sign * sinh(rads);

        FVector p2 = localTransform.TransformPosition(
            USpiceTypes::Conv_SDistanceVectorToVector(
                ellipse.center + _cosh * ellipse.v_major + _sinh * ellipse.v_minor
            ));

        DrawDebugLine(world, p1, p2, color, false, -1.f, 0, thickness);
    }

    {
        double theta = -30000.;
        double rads = rpd * theta;
        double _cosh = sign * cosh(rads);
        double _sinh = sign * sinh(rads);
        FVector  p1 = localTransform.TransformPosition(
            USpiceTypes::Conv_SDistanceVectorToVector(
                ellipse.center + _cosh * ellipse.v_major + _sinh * ellipse.v_minor
            ));

        theta = -360.;

        // It's not efficient to recalculate since we just calculated it last iteration...
        // ...But this is a debug function anyways
        rads = rpd * theta;
        _cosh = sign * cosh(rads);
        _sinh = sign * sinh(rads);

        FVector p2 = localTransform.TransformPosition(
            USpiceTypes::Conv_SDistanceVectorToVector(
                ellipse.center + _cosh * ellipse.v_major + _sinh * ellipse.v_minor
            ));

        DrawDebugLine(world, p1, p2, color, false, -1.f, 0, thickness);
    }

    {
        double theta = 360.;
        double rads = rpd * theta;
        double _cosh = sign * cosh(rads);
        double _sinh = sign * sinh(rads);
        FVector  p1 = localTransform.TransformPosition(
            USpiceTypes::Conv_SDistanceVectorToVector(
                ellipse.center + _cosh * ellipse.v_major + _sinh * ellipse.v_minor
            ));

        theta = 3000.f;

        // It's not efficient to recalculate since we just calculated it last iteration...
        // ...But this is a debug function anyways
        rads = rpd * theta;
        _cosh = sign * cosh(rads);
        _sinh = sign * sinh(rads);

        FVector p2 = localTransform.TransformPosition(
            USpiceTypes::Conv_SDistanceVectorToVector(
                ellipse.center + _cosh * ellipse.v_major + _sinh * ellipse.v_minor
            ));

        DrawDebugLine(world, p1, p2, color, false, -1.f, 0, thickness);
    }
}

