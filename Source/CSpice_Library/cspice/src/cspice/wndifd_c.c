/*

-Procedure wndifd_c ( Difference two DP windows )

-Abstract
 
   Place the difference of two double precision windows into 
   a third window. 
 
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
 
   WINDOWS 
 
-Keywords
 
   WINDOWS 
 
*/

   #include "SpiceUsr.h"
   #include "SpiceZfc.h"
   #include "SpiceZmc.h"

   void wndifd_c (  SpiceCell   * a,
                    SpiceCell   * b,
                    SpiceCell   * c  ) 

/*

-Brief_I/O
 
   VARIABLE  I/O  DESCRIPTION 
   --------  ---  -------------------------------------------------- 
   a, 
   b          I   Input windows. 
   c          O   Difference of a and b. 
 
-Detailed_Input
 
   a, 
   b           are CSPICE windows, each of which contains zero or more 
               intervals. 
 
               a and b must be declared as double precision 
               SpiceCells.

-Detailed_Output
 
   c           is the output CSPICE window, containing the difference 
               of a and b---every point contained in a, but not 
               contained in b. 

               c must be declared as a double precision SpiceCell.

               c must be distinct from both a and b. 
-Parameters
 
   None. 
 
-Exceptions
  
   1) If any of the function arguments are SpiceCells of type
      other than double precision, the error SPICE(TYPEMISMATCH)
      is signaled.

   2) If the difference of the two windows results in an excess of 
      elements, the error SPICE(WINDOWEXCESS) is signaled. 
 
-Files
 
   None. 
 
-Particulars
 
   Mathematically, the difference of two windows contains every 
   point contained in the first window but not contained in the 
   second window. 

   Fortran offers no satisfactory floating point representation 
   of open intervals. Thus, for floating point windows we must 
   return the closure of the set theoretical difference.
 
-Examples
 
   Let a contain the intervals 

      [ 1, 3 ]  [ 7, 11 ]  [ 23, 27 ] 

   and b contain the intervals 

      [ 2, 4 ]  [ 8, 10 ]  [ 16, 18 ] 

   Then the difference of a and b contains the intervals 

      [ 1, 2 ]  [ 7, 8 ]  [ 10, 11 ]  [ 23, 27 ] 
 
-Restrictions
 
   None. 
 
-Literature_References
 
   None. 
 
-Author_and_Institution
 
   N.J. Bachman    (JPL)
   H.A. Neilan     (JPL) 
   B.V. Semenov    (JPL) 
   W.L. Taber      (JPL) 
   I.M. Underwood  (JPL) 
 
-Version
 
   -CSPICE Version 1.0.1, 11-FEB-2013 (BVS)

       Corrected typo in Brief I/O section.

   -CSPICE Version 1.0.0, 29-JUL-2002 (NJB) (HAN) (WLT) (IMU)

-Index_Entries
 
   difference two d.p. windows 
 
-&
*/

{ /* Begin wndifd_c */

   /*
   Local constants
   */


   /*
   Participate in error tracing.
   */
   if ( return_c() )
   {
      return;
   }
   chkin_c ( "wndifd_c" );


   /*
   Make sure cell data types are d.p. 
   */
   CELLTYPECHK3 ( CHK_STANDARD, "wndifd_c", SPICE_DP, a, b, c );


   /*
   Initialize the cells if necessary. 
   */
   CELLINIT3 ( a, b, c );
   

   /*
   Let the f2c'd routine do the work. 
   */
   wndifd_ ( (doublereal * ) (a->base),
             (doublereal * ) (b->base), 
             (doublereal * ) (c->base)  );

   /*
   Sync the output cell. 
   */
   if ( !failed_c() )
   {
      zzsynccl_c ( F2C, c );
   }


   chkout_c ( "wndifd_c" );

} /* End wndifd_c */
