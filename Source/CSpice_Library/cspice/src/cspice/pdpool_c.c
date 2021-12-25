/*

-Procedure pdpool_c ( Put d.p.'s into the kernel pool )

-Abstract
 
   This entry point provides toolkit programmers a method for 
   programmatically inserting double precision data into the 
   kernel pool. 
 
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
 
   POOL 
 
*/

   #include "SpiceUsr.h"
   #include "SpiceZfc.h"
   #include "SpiceZmc.h"
   #include "SpiceZim.h"
   #undef    pdpool_c

 
   void pdpool_c ( ConstSpiceChar      * name,
                   SpiceInt              n,
                   ConstSpiceDouble    * dvals ) 

/*

-Brief_I/O
 
   VARIABLE  I/O  DESCRIPTION 
   --------  ---  -------------------------------------------------- 
   name       I   The kernel pool name to associate with dvals. 
   n          I   The number of values to insert. 
   dvals      I   An array of values to insert into the kernel pool. 
 
-Detailed_Input
 
   name       is the name of the kernel pool variable to associate 
              with the values supplied in the array dvals. 'name' is
              restricted to a length of 32 characters or less.
 
   n          is the number of values to insert into the kernel pool. 
 
   dvals      is an array of d.p. values to insert into the kernel 
              pool. 
 
-Detailed_Output
 
   None. 
 
-Parameters
 
   None. 
 
-Exceptions
 
   1) If name is already present in the kernel pool and there 
      is sufficient room to hold all values supplied in dvals, 
      the old values associated with name will be overwritten. 
 
   2) If there is not sufficient room to insert a new variable 
      into the kernel pool and name is not already present in 
      the kernel pool, the error SPICE(KERNELPOOLFULL) is 
      signaled by a routine in the call tree to this routine. 
 
   3) If there is not sufficient room to insert the values associated 
      with name, the error SPICE(NOMOREROOM) will be signaled. 
 
   4) If the input string pointer name is null, the error
      SPICE(NULLPOINTER) will be signaled.
 
   5) If the input string name has length zero, the error
      SPICE(EMPTYSTRING) will be signaled.

   6) The error 'SPICE(BADVARNAME)' signals if the kernel pool
      variable name length exceeds 32.
 
-Files
 
   None. 
 
-Particulars
 
   This entry point provides a programmatic interface for inserting 
   data into the SPICE kernel pool without reading an external file. 
 
-Examples
 
   The following example program shows how a topocentric frame for a
   point on the surface of the earth may be defined at run time using
   pcpool_c, pdpool_c, and pipool_c.  In this example, the surface
   point is associated with the body code 300000.  To facilitate
   testing, the location of the surface point coincides with that of
   the DSN station DSS-12; the reference frame MYTOPO defined here
   coincides with the reference frame DSS-12_TOPO.
 
      #include <stdio.h>
      #include "SpiceUsr.h"

      int main()
      {
         /.
         The first angle is the negative of the longitude of the
         surface point; the second angle is the negative of the 
         point's colatitude.
         ./
         SpiceDouble             angles [3]      =  { -243.1945102442646,
                                                       -54.7000629043147,
                                                       180.0              };

         SpiceDouble             et              =    0.0;
         SpiceDouble             rmat   [3][3];

         SpiceInt                axes   [3]      =  { 3, 2, 3 };
         SpiceInt                center          =    300000;
         SpiceInt                frclass         =    4;
         SpiceInt                frclsid         =    1500000;
         SpiceInt                frcode          =    1500000;

         /.
         Define the MYTOPO reference frame. 

         Note that the third argument in the pcpool_c calls is
         the length of the final string argument, including the
         terminating null character.
         ./
         pipool_c ( "FRAME_MYTOPO",            1,     &frcode   );
         pcpool_c ( "FRAME_1500000_NAME",      1, 7,  "MYTOPO"  );
         pipool_c ( "FRAME_1500000_CLASS",     1,     &frclass  );
         pipool_c ( "FRAME_1500000_CLASS_ID",  1,     &frclsid  );
         pipool_c ( "FRAME_1500000_CENTER",    1,     &center   );

         pcpool_c ( "OBJECT_300000_FRAME",     1, 7,  "MYTOPO"  );

         pcpool_c ( "TKFRAME_MYTOPO_RELATIVE", 1, 7,  "ITRF93"  );
         pcpool_c ( "TKFRAME_MYTOPO_SPEC",     1, 7,  "ANGLES"  );
         pcpool_c ( "TKFRAME_MYTOPO_UNITS",    1, 8,  "DEGREES" );
         pipool_c ( "TKFRAME_MYTOPO_AXES",     3,     axes      );
         pdpool_c ( "TKFRAME_MYTOPO_ANGLES",   3,     angles    );

         /.
         Load a high precision binary earth PCK. Also load a
         topocentric frame kernel for DSN stations. The file names
         shown here are simply examples; users should replace these
         with the names of appropriate kernels.
         ./
         furnsh_c ( "earth_000101_060207_051116.bpc" );
         furnsh_c ( "earth_topo_050714.tf"           );

         /.
         Look up transformation from DSS-12_TOPO frame to MYTOPO frame.
         This transformation should differ by round-off error from
         the identity matrix. 
         ./
         pxform_c ( "DSS-12_TOPO", "MYTOPO", et, rmat );

         printf   ( "\n"
                    "DSS-12_TOPO to MYTOPO transformation at "
                    "et %23.16e = \n"
                    "\n"
                    "    %25.16f  %25.16f  %25.16f\n"
                    "    %25.16f  %25.16f  %25.16f\n"
                    "    %25.16f  %25.16f  %25.16f\n",
                    et,
                    rmat[0][0],  rmat[0][1],  rmat[0][2],
                    rmat[1][0],  rmat[1][1],  rmat[1][2],
                    rmat[2][0],  rmat[2][1],  rmat[2][2]       );

         return ( 0 );
      }


-Restrictions
 
   None. 
 
-Literature_References
 
   None. 
 
-Author_and_Institution
 
   N.J. Bachman    (JPL)
   W.L. Taber      (JPL) 
 
-Version

   -CSPICE Version 1.1.3,  17-JAN-2014 (NJB)

      Updated the Index_Entries section.

   -CSPICE Version 1.1.2,  10-FEB-2010 (EDW)

      Added mention of the restriction on kernel pool variable 
      names to 32 characters or less.

      Reordered header sections to conform to SPICE convention.

   -CSPICE Version 1.1.1, 17-NOV-2005 (NJB)

      Replaced code fragment in Examples section of header with 
      smaller, complete program. 

   -CSPICE Version 1.1.0, 24-JUL-2001   (NJB)

       Changed prototype:  input dvals is now type (ConstSpiceDouble *).
       Implemented interface macro for casting input dvals to const.

   -CSPICE Version 1.0.0, 03-JUN-1999 (NJB) (WLT)

-Index_Entries
 
   Set the value of a d.p._variable in the kernel_pool 
 
-&
*/

{ /* Begin pdpool_c */

   /*
   Participate in error tracing.
   */
   chkin_c ( "pdpool_c" );


   /*
   Check the input kernel variable name to make sure the pointer is
   non-null and the string length is non-zero.
   */
   CHKFSTR ( CHK_STANDARD, "pdpool_c", name );

   /*
   Call the f2c'd routine.
   */
   pdpool_ ( ( char        * ) name,
             ( integer     * ) &n,
             ( doublereal  * ) dvals,
             ( ftnlen        ) strlen(name) );


   chkout_c ( "pdpool_c" );

} /* End pdpool_c */
