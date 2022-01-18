/*

-Procedure hrmint_c ( Hermite polynomial interpolation  )

-Abstract

   Evaluate a Hermite interpolating polynomial at a specified
   abscissa value.

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

   INTERPOLATION
   MATH
   POLYNOMIAL

*/

   #include "SpiceUsr.h"
   #include "SpiceZfc.h"
   #undef    hrmint_c

   void hrmint_c ( SpiceInt            n,
                   ConstSpiceDouble  * xvals,
                   ConstSpiceDouble  * yvals,
                   SpiceDouble         x,
                   SpiceDouble       * work,
                   SpiceDouble       * f,
                   SpiceDouble       * df )

/*

-Brief_I/O

   Variable  I/O  Description
   --------  ---  --------------------------------------------------
   n          I   Number of points defining the polynomial.
   xvals      I   Abscissa values.
   yvals      I   Ordinate and derivative values.
   x          I   Point at which to interpolate the polynomial.
   work      I-O  Work space array.
   f          O   Interpolated function value at x.
   df         O   Interpolated function's derivative at x.

-Detailed_Input

   n              is the number of points defining the polynomial.
                  The arrays xvals and yvals contain n and 2*n
                  elements respectively.

   xvals          is an array of length n containing abscissa values.

   yvals          is an array of length 2*n containing ordinate and
                  derivative values for each point in the domain
                  defined by xvals and n. The elements

                     yvals[ 2*i    ]
                     yvals[ 2*i +1 ]

                  give the value and first derivative of the output
                  polynomial at the abscissa value

                     xvals[i]

                  where i ranges from 0 to n - 1.

   work           is a work space array.  It is used by this routine
                  as a scratch area to hold intermediate results.
                  Generally sized at number of elements in yvals
                  time two.

   x              is the abscissa value at which the interpolating
                  polynomial and its derivative are to be evaluated.

-Detailed_Output

   f,
   df             are the value and derivative at x of the unique
                  polynomial of degree 2n-1 that fits the points and
                  derivatives defined by xvals and yvals.

-Parameters

   None.

-Exceptions

   1)  The error SPICE(DIVIDEBYZERO) signals from a routine
       in the call tree if two input abscissas are equal,

   2)  The error SPICE(INVALIDSIZE) signals from a routine
       in the call tree if n is less than 1.

   3)  This routine does not attempt to ward off or diagnose
       arithmetic overflows.

-Files

   None.

-Particulars

   Users of this routine must choose the number of points to use
   in their interpolation method.  The authors of Reference [1] have
   this to say on the topic:

      Unless there is solid evidence that the interpolating function
      is close in form to the true function f, it is a good idea to
      be cautious about high-order interpolation.  We
      enthusiastically endorse interpolations with 3 or 4 points, we
      are perhaps tolerant of 5 or 6; but we rarely go higher than
      that unless there is quite rigorous monitoring of estimated
      errors.

   The same authors offer this warning on the use of the
   interpolating function for extrapolation:

      ...the dangers of extrapolation cannot be overemphasized:
      An interpolating function, which is perforce an extrapolating
      function, will typically go berserk when the argument x is
      outside the range of tabulated values by more than the typical
      spacing of tabulated points.

-Examples

   Example:
   
      Fit a 7th degree polynomial through the points ( x, y, y' )

           ( -1,      6,       3 )
           (  0,      5,       0 )
           (  3,   2210,    5115 )
           (  5,  78180,  109395 )

      and evaluate this polynomial at x = 2.

      #include <stdio.h>
      #include "SpiceUsr.h"

      int main()
         {

         /.
         Local variables.
         ./
         SpiceDouble      answer;
         SpiceDouble      deriv;
         SpiceDouble      xvals [] = {-1., 0., 3., 5.};
         SpiceDouble      yvals [] = {6., 3., 5., 0.,
                                      2210., 5115., 78180., 109395.};
         SpiceDouble      work  [2*8];
         SpiceDouble      x = 2;
         SpiceInt         n = 4;

         hrmint_c ( n, xvals, yvals, x, work, &answer, &deriv );

         printf( "answer = %lf\n", answer );
         printf( "deriv  = %lf\n", deriv );

         return(0);
         }

      The returned value of 'answer' should be 141., and the returned
      value of 'deriv' should be 456., since the unique 7th degree
      polynomial that fits these constraints is

                   7       2
         f(x)  =  x   +  2x  + 5

-Restrictions

   None.

-Literature_References

   [1]  "Numerical Recipes---The Art of Scientific Computing" by
         William H. Press, Brian P. Flannery, Saul A. Teukolsky,
         William T. Vetterling (see sections 3.0 and 3.1).

   [2]  "Elementary Numerical Analysis---An Algorithmic Approach"
         by S. D. Conte and Carl de Boor.  See p. 64.

-Author_and_Institution

    N.J. Bachman    (JPL)
    E.D. Wright     (JPL)

-Version

   -CSPICE Version 1.0.0, 24-AUG-2015 (EDW)

-Index_Entries

   interpolate function using Hermite polynomial
   Hermite interpolation

-&
*/

{ /* Begin hrmint_c */

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

   chkin_c ( "hrmint_c" );

   /*
   The f2c'd routine does the work.
   */
   hrmint_( (integer *   ) &n,
            (doublereal *) xvals,
            (doublereal *) yvals,
            (doublereal *) &x,
            (doublereal *) work,
            (doublereal *) f,
            (doublereal *) df);

   chkout_c ( "hrmint_c" );

} /* End hrmint_c */
