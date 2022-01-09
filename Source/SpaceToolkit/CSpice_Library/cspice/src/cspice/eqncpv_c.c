/*

-Procedure eqncpv_c (Equinoctial Elements to position and velocity)

-Abstract

   Compute the state (position and velocity of an object whose
   trajectory is described via equinoctial elements relative to some
   fixed plane (usually the equatorial plane of some planet).

-Disclaimer

   THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE
   CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S.
   GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE
   ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE
   PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS"
   TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY
   WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A
   PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC
   SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE
   SOFTWARE AND RELATED MATERIALS, HOWEVER USED.

   IN NO EVENT SHALL CALTECH, ITS Jet PROPULSION LABORATORY, OR NASA
   BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT
   LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND,
   INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS,
   REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE
   REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY.

   RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF
   THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY
   CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE
   ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE.

-Required_Reading

   None.

-Keywords

   EPHEMERIS

*/

   #include "SpiceUsr.h"
   #include "SpiceZfc.h"
   #include "SpiceZmc.h"
   #undef eqncpv_c

   void eqncpv_c ( SpiceDouble        et,
                   SpiceDouble        epoch,
                   ConstSpiceDouble   eqel[9],
                   SpiceDouble        rapol,
                   SpiceDouble        decpol,
                   SpiceDouble        state[6] )

/*

-Brief_I/O

   VARIABLE  I/O  DESCRIPTION
   --------  ---  --------------------------------------------------
   et         I   Epoch in seconds past J2000 to find state
   epoch      I   Epoch of elements in seconds past J2000
   eqel       I   Array of equinoctial elements
   rapol      I   Right Ascension of the pole of the reference plane
   decpol     I   Declination of the pole of the reference plane
   state      O   State of the object described by eqel.

-Detailed_Input

   et         is the epoch (ephemeris time) at which the state
              of the target body is to be computed. et is measured
              in seconds past the J2000 epoch.

   epoch      is the epoch of the equinoctial elements in seconds
              past the J2000 epoch.

   eqel       is an array of 9 double precision numbers that
              are the equinoctial elements for some orbit expressed
              relative to the equatorial frame of the central body.
              (The z-axis of the equatorial frame is the direction
              of the pole of the central body relative to some
              inertial frame.  The x-axis is given by the cross
              product of the Z-axis of the inertial frame
              with the direction of the pole of the central body.
              The Y-axis completes a right handed frame.
              (If the z-axis of the equatorial frame is aligned
              with the z-axis of the inertial frame, then the
              x-axis of the equatorial frame will be located at
              90 degrees + rapol in the inertial frame.)

              The specific arrangement of the elements is spelled
              out below.  The following terms are used in the
              discussion of elements of eqel

                  inc  --- inclination of the orbit
                  argp --- argument of periapse
                  node --- longitude of the ascending node
                  e    --- eccentricity of the orbit

              eqel[0] is the semi-major axis (a) of the orbit in km.

              eqel[1] is the value of 'h' at the specified epoch.
                      ( e*sin(argp+node) ).

              eqel[2] is the value of 'k' at the specified epoch
                      ( e*cos(argp+node) ).

              eqel[3] is the mean longitude (mean0+argp+node) at
                      the epoch of the elements measured in radians.

              eqel[4] is the value of 'p' (tan(inc/2)*sin(node))at
                      the specified epoch.

              eqel[5] is the value of 'q' (tan(inc/2)*cos(node))at
                      the specified epoch.

              eqel[6] is the rate of the longitude of periapse
                      (dargp/dt + dnode/dt ) at the epoch of
                      the elements. This rate is assumed to hold
                      for all time. The rate is measured in
                      radians per second.

              eqel[7] is the derivative of the mean longitude
                      ( dm/dt + dargp/dt + dnode/dt ). This
                      rate is assumed to be constant and is
                      measured in radians/second.

              eqel[8] is the rate of the longitude of the ascending
                      node ( dnode/dt). This rate is measured
                      in radians per second.

   rapol      Right Ascension of the pole of the reference plane
              with respect to some inertial frame (measured in
              radians).

   decpol     Declination of the pole of the reference plane
              with respect to some inertial frame (measured in
              radians).

-Detailed_Output

   state      State of the object described by eqel relative to the
              inertial frame used to define rapol and decpol. Units
              are in km and km/sec.

-Parameters

   None.

-Exceptions

   None.

-Files

   None.

-Particulars

   This routine evaluates the input equinoctial elements for
   the specified epoch and return the corresponding state.

   This routine was adapted from a routine provided by
   Bob Jacobson at JPL.

-Examples

   Any numerical results shown for this example may differ between
   platforms as the results depend on the SPICE kernels used as input
   and the machine specific arithmetic implementation.

      Compute a state vector from a set of equinoctial elements.

      #include "SpiceUsr.h"
      #include <stdio.h>
      #include <math.h>

      int main()
         {

         /.

         Suppose you have classical elements and rates of
         change of the ascending node and argument of periapse
         for some satellite of the earth.

         By transforming the classical elements this routine
         compute the state of the object at an arbitrary epoch.
         The code below illustrates how to do this.

         The table below illustrates the meanings of the various
         variables used in the discussion below.

              Variable     Meaning
              --------     ----------------------------------
              a            Semi-major axis in km.
              ecc          Eccentricity of orbit.
              inc          Inclination of orbit.
              node         Longitude of the ascending node at epoch.
              omega        Argument of periapse at epoch.
              m            Mean anomaly at epoch.
              dmdt         Mean anomaly rate in radians/second.
              dnode        Rate of change of longitude of ascending node
                           in radians/second.
              domega       Rate of change of argument of periapse in
                           radians/second.
              epoch        is the epoch of the elements in seconds past
                           the J2000 epoch.

              eqel[0] = a
              eqel[1] = ecc * sin( omega + node )
              eqel[2] = ecc * cos( omega + node )

              eqel[3] = m + omega + node

              eqel[4] = tan(inc/2.0) * sin(node)
              eqel[5] = tan(inc/2.0) * cos(node)

              eqel[6] = domega
              eqel[7] = domega + dmdt + dnode
              eqel[8] = dnode

         In this case, the rates of node and argument of
         periapse are zero and the pole of the central
         frame is aligned with the pole of an inertial frame.

         ./

         SpiceInt               i;

         SpiceDouble            a;
         SpiceDouble            argp;
         SpiceDouble            decpol;
         SpiceDouble            ecc;
         SpiceDouble            eqel   [9];
         SpiceDouble            et;
         SpiceDouble            gm;
         SpiceDouble            inc;
         SpiceDouble            m0;
         SpiceDouble            n;
         SpiceDouble            node;
         SpiceDouble            p;
         SpiceDouble            rapol;
         SpiceDouble            t0;
         SpiceDouble            theta;
         SpiceDouble            state  [6];

         p    =      1.0e4;
         gm   = 398600.436;
         ecc  =      0.1;
         a    = p/( 1. - ecc );
         n    = sqrt ( gm / a ) / a;
         argp = 30. * rpd_c();
         node = 15. * rpd_c();
         inc  = 10. * rpd_c();
         m0   = 45. * rpd_c();
         t0   = -100000000.;

         eqel[0] = a;
         eqel[1] = ecc*sin(argp+node);
         eqel[2] = ecc*cos(argp+node);
         eqel[3] = m0 + argp + node;
         eqel[4] = tan(inc/2.)*sin(node);
         eqel[5] = tan(inc/2.)*cos(node);
         eqel[6] = 0.;
         eqel[7] = n;
         eqel[8] = 0.;

         rapol    = -halfpi_c();
         decpol   =  halfpi_c();

         et = t0 - 10000.0;

         for ( i = 0; i < 10; i++)
            {
            et = et + 250.;

            eqncpv_c ( et, t0, eqel, rapol, decpol, state );
            printf ("\nPos = %16.6f %16.6f %16.6f \n",
                             state[0], state[1], state[2] );
            printf (  "Vel = %16.6f %16.6f %16.6f \n",
                             state[3], state[4], state[5] );
            }

         return 0;
         }

   The program outputs:

      Pos =    -10732.167433      3902.505791      1154.451615
      Vel =        -2.540767        -5.152269        -0.761576

      Pos =    -11278.382863      2586.179875       955.184099
      Vel =        -1.827156        -5.362916        -0.830020

      Pos =    -11645.295454      1228.612448       740.709574
      Vel =        -1.108096        -5.482811        -0.883256

      Pos =    -11832.799901      -147.990984       514.805250
      Vel =        -0.393421        -5.515905        -0.921508

      Pos =    -11843.089312     -1522.469846       281.175257
      Vel =         0.308288        -5.466565        -0.945128

      Pos =    -11680.364607     -2874.784755        43.424394
      Vel =         0.989520        -5.339364        -0.954552

      Pos =    -11350.589872     -4186.049765      -194.958526
      Vel =         1.643649        -5.138938        -0.950269

      Pos =    -10861.293274     -5438.536175      -430.610411
      Vel =         2.264759        -4.869899        -0.932792

      Pos =    -10221.410986     -6615.660644      -660.298988
      Vel =         2.847476        -4.536794        -0.902651

      Pos =     -9441.170335     -7701.967890      -880.925189
      Vel =         3.386822        -4.144103        -0.860382

-Restrictions

   The equinoctial elements used by this routine are taken
   from  "Tangent" formulation of equinoctial elements

      p = Tan(inclination/2) * Sin(R.A. of ascending node)
      q = Tan(inclination/2) * Cos(R.A. of ascending node)

   Other formulations use Sine instead of Tangent.  We shall
   call these the "Sine" formulations.

      p = Sin(inclination/2) * Sin(R.A. of ascending node)
      q = Sin(inclination/2) * Cos(R.A. of ascending node)

   If you have equinoctial elements from this alternative
   formulation you should replace p and q  by the
   expressions below.

     P = P / sqrt( 1.0 - P*P - Q*Q )
     Q = Q / sqrt( 1.0 - P*P - Q*Q )

   This will convert the Sine formulation to the Tangent formulation.

-Literature_References

   JPL Engineering Memorandum 314-513 "Optical Navigation Program
   Mathematical Models" by William M. Owen, Jr. and Robin M Vaughan
   August 9, 1991.

-Author_and_Institution

   W.L. Taber      (JPL)
   R.A. Jacobson   (JPL)
   B.V. Semenov    (JPL)

-Version

   -CSPICE Version 1.0.0, 20-MAR-2012  (EDW)

-Index_Entries

   Compute a state from equinoctial elements

-&
*/

{ /* Begin eqncpv_c */

   /*
   Local constants
   */


   /*
   Local macros
   */


   /*
   Local variables
   */


   /*
   Static variables
   */


   /*
   Participate in error tracing.
   */

   chkin_c ( "eqncpv_c" );

   eqncpv_ ( ( doublereal * ) &et,
             ( doublereal * ) &epoch,
             ( doublereal * ) eqel,
             ( doublereal * ) &rapol,
             ( doublereal * ) &decpol,
             ( doublereal * ) state);

   chkout_c ( "eqncpv_c" );

} /* End eqncpv_c */
