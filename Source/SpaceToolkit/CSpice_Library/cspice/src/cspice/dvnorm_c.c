/*

-Procedure dvnorm_c ( Derivative of vector norm )

-Abstract

   Function to calculate the derivative of the norm of a 3-vector.

-Disclaimer

   THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE
   CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S.
   GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE
   ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE
   PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS"
   TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY
   WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A
   PARTICULAR USE OR PURPOSE (AS set_c FORTH IN UNITED STATES UCC
   SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE
   SOFTWARE AND RELATED MATERIALS, HOWEVER USED.

   IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA
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

   DERIVATIVES
   MATH
   VECTOR

*/

   #include "SpiceUsr.h"
   #include "SpiceZfc.h"
   #undef dvnorm_c

   SpiceDouble       dvnorm_c ( ConstSpiceDouble state[6] )

/*

-Brief_I/O

   VARIABLE  I/O  DESCRIPTION
   --------  ---  --------------------------------------------------
   state      I   A 6-vector composed of three coordinates and their
                  derivatives.

-Detailed_Input

   state   A double precision 6-vector, the second three
           components being the derivatives of the first three
           with respect to some scalar.

              state =  ( x, dx )
                            --
                            ds

           A common form for 'state' would contain position and
           velocity.

-Detailed_Output

   dvnorm_c   The value of d||x|| corresponding to 'state'.
                           ------
                             ds

                                 1/2         2    2    2  1/2
            where ||x|| = < x, x >    =  ( x1 + x2 + x3 )


                      v = ( dx1, dx2, dx3 )
                            ---  ---  ---
                            ds   ds   ds

                 d||x||   < x, v >
                 ------ =  ------     =  < xhat, v >
                   ds            1/2
                          < x, x >

-Parameters

   None.

-Exceptions

   None.

-Files

   None.

-Particulars

   A common use for this routine is to calculate the time derivative
   of the radius corresponding to a state vector.

-Examples

   Any numerical results shown for this example may differ between
   platforms as the results depend on the SPICE kernels used as input
   and the machine specific arithmetic implementation.

      #include "SpiceUsr.h"
      #include <stdio.h>
      #include <math.h>

      int main()
         {

         SpiceDouble     mag  [3] =
                          { -4., 4., 12. };

         SpiceDouble     x1   [3] =
                          { 1., sqrt(2.), sqrt(3.) };

         SpiceDouble     y   [6];

         /.
         Parallel...
         ./
         y[0] = x1[0] * pow(10., mag[0] );
         y[1] = x1[1] * pow(10., mag[0] );
         y[2] = x1[2] * pow(10., mag[0] );
         y[3] = x1[0];
         y[4] = x1[1];
         y[5] = x1[2];

         printf( "Parallel x, dx/ds         : %f\n", dvnorm_c( y ) );

         /.
         ...anti-parallel...
         ./
         y[0] = x1[0] * pow(10., mag[1] );
         y[1] = x1[1] * pow(10., mag[1] );
         y[2] = x1[2] * pow(10., mag[1] );
         y[3] = -x1[0];
         y[4] = -x1[1];
         y[5] = -x1[2];

         printf( "Anti-parallel x, dx/ds    : %f\n", dvnorm_c( y ) );


         /.
         ...'x' zero vector.
         ./
         y[0] = 0.;
         y[1] = 0.;
         y[2] = 0.;
         y[3] = x1[0] * pow(10., mag[2] );
         y[4] = x1[1] * pow(10., mag[2] );
         y[5] = x1[2] * pow(10., mag[2] );

         printf( "Zero vector x, large dx/ds: %f\n", dvnorm_c( y ) );

         return 0;
         }

   The program outputs:

      Parallel x, dx/ds         :  2.449490
      Anti-parallel x, dx/ds    : -2.449490
      Zero vector x, large dx/ds:  0.000000

-Restrictions

   Error free.

   1) If the first three components of 'state' ("x") describes the
      origin (zero vector) the routine returns zero as the
      derivative of the vector norm.

-Literature_References

   None.

-Author_and_Institution

   Ed Wright     (JPL)

-Version

   -CSPICE Version 1.0.0, 04-MAY-2010 (EDW)

-Index_Entries

   derivative of 3-vector norm

-&
*/

{ /* Begin dvnorm_c */

   /*
   Local variables
   */
   SpiceDouble       retval;

   /*
   Participate in error tracing.
   */

   chkin_c ( "dvnorm_c" );

   /*
   Call the f2c'd Fortran routine.
   */
   retval = (SpiceDouble) dvnorm_( (doublereal*) state);

   chkout_c ( "dvnorm_c" );

   return( retval );

} /* End dvnorm_c */

