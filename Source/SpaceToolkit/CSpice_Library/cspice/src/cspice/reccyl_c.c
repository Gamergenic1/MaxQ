/*

-Procedure reccyl_c ( Rectangular to cylindrical coordinates )

-Abstract

   Convert from rectangular to cylindrical coordinates. 
 
 
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
 
   CONVERSION, COORDINATES 
 
*/

   #include <math.h>
   #include "SpiceUsr.h"
   #include "SpiceZmc.h"
   #include "SpiceZim.h"
   #undef    reccyl_c


   void reccyl_c ( ConstSpiceDouble     rectan[3], 
                   SpiceDouble        * r, 
                   SpiceDouble        * lon, 
                   SpiceDouble        * z         ) 

/*

-Brief_I/O
 
   VARIABLE  I/O  DESCRIPTION 
   --------  ---  ------------------------------------------------- 
   rectan     I   Rectangular coordinates of a point. 
   r          O   Distance of the point from Z axis. 
   lon        O   Angle (radians) of the point from XZ plane 
   z          O   Height of the point above XY plane. 
 
-Detailed_Input
 
   rectan     Rectangular coordinates of the point of interest. 
 
-Detailed_Output
 
   r          Distance of the point of interest from Z axis. 
 
   lon        Cylindrical angle (in radians) of the point of 
              interest from XZ plane. The `lon' range is [0, 2pi].
 
   z          Height of the point above XY plane. 
 
-Parameters
 
   None. 
 
-Exceptions
 
   Error free. 
 
-Files
 
   None. 
 
-Particulars
 
   This routine transforms the coordinates of a point from 
   rectangular to cylindrical coordinates. 
 
-Examples
 
   Below are two tables. 
 
   Listed in the first table (under x(1), x(2) and x(3) ) are a 
   number of points whose rectangular coordinates coorindates are 
   taken from the set {-1, 0, 1}. 
 
   The result of the code fragment 
 
        reccyl_c ( x, r,  lon, z );
 
        Use the CSPICE routine convrt_c to convert the angular 
        quantities to degrees 
 
        convrt_c (  lon, "RADIANS", "DEGREES", lon  );
 
   are listed to 4 decimal places in the second parallel table under 
   r (radius), lon  (longitude), and  z (same as rectangular z 
   coordinate). 
 
 
     x(1)       x(2)     x(3)        r         lon      z 
     --------------------------      ------------------------- 
     0.0000     0.0000   0.0000      0.0000    0.0000   0.0000 
     1.0000     0.0000   0.0000      1.0000    0.0000   0.0000 
     0.0000     1.0000   0.0000      1.0000   90.0000   0.0000 
     0.0000     0.0000   1.0000      0.0000    0.0000   1.0000 
    -1.0000     0.0000   0.0000      1.0000  180.0000   0.0000 
     0.0000    -1.0000   0.0000      1.0000  270.0000   0.0000 
     0.0000     0.0000  -1.0000      0.0000    0.0000  -1.0000 
     1.0000     1.0000   0.0000      1.4142   45.0000   0.0000 
     1.0000     0.0000   1.0000      1.0000    0.0000   1.0000 
     0.0000     1.0000   1.0000      1.0000   90.0000   1.0000 
     1.0000     1.0000   1.0000      1.4142   45.0000   1.0000 
 
-Restrictions
 
   None. 
 
-Literature_References
 
   None. 
 
-Author_and_Institution
 
   W.L. Taber      (JPL) 
 
-Version
 
   -CSPICE Version 1.2.1, 26-JUL-2016 (BVS)

      Minor headers edits.

   -CSPICE Version 1.2.0, 28-AUG-2001 (NJB)
     
      Removed tab characters from source file.  Include interface
      macro definition header SpiceZim.h.

   -CSPICE Version 1.1.0, 21-OCT-1998 (NJB)

      Made input vector const.

   -CSPICE Version 1.0.0, 08-FEB-1998 (EDW)

-Index_Entries
 
   rectangular to cylindrical coordinates 
 
-&
*/

{ /* Begin reccyl_c */

   /*
   Local variables
   */

   SpiceDouble    x;
   SpiceDouble    y;
   SpiceDouble    big;


   /* Computing max absolute value of x and y components */
   big = MaxAbs( rectan[0], rectan[1] );


   /*  Convert to cylindrical coordinates */

   *z = rectan[2];

   if ( big == 0.)
      {
      *r   = 0.;
      *lon = 0.;
      }
   else
      {
      x   = rectan[0] / big;
      y   = rectan[1] / big;
      *r   = big * sqrt(x * x + y * y);
      *lon = atan2(y, x);
      }

   if ( *lon < 0.)
      {
      *lon += twopi_c();
      }


} /* End reccyl_c */
