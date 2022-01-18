/*

-Procedure lstled_c ( Last double precision element less than or equal)

-Abstract
 
   Given a number x and an array of non-decreasing numbers, 
   find the index of the largest array element less than or equal 
   to x. 
 
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
 
   SEARCH,  ARRAY 
 
*/

   #include "SpiceUsr.h"
   #include "SpiceZfc.h"
   #include "SpiceZim.h"
   #undef    lstled_c

   SpiceInt lstled_c ( SpiceDouble         x,
                       SpiceInt            n,
                       ConstSpiceDouble  * array ) 
/*

-Brief_I/O
 
   VARIABLE  I/O  DESCRIPTION 
   --------  ---  -------------------------------------------------- 
   x          I   Value to search against 
   n          I   Number elements in array
   array      I   Array of possible lower bounds 

   The function returns the index of the last element of array that
   is less than or equal to x. 
 
-Detailed_Input
 
   x       Double precision number.

   n       Total number of elements in array. 

   array   Array of double precision numbers which forms a
           non-decreasing sequence.  The elements of array need not be
           distinct.
 
-Detailed_Output
 
   The function returns the index of the highest-indexed element in the 
   input array that is less than or equal to x.  The routine assumes
   the array elements are sorted in non-decreasing order.

   Indices range from 0 to n-1.
 
   If all elements of the input array are greater than x, the function
   returns -1.

-Parameters
 
   None. 
 
-Exceptions
 
   Error free.

   1) In the case that n is input with value less than or equal 
      to zero, the function returns -1.

   2) If the input array is not sorted in increasing order, the
      output of this routine are undefined.  No error is signaled.

-Files
 
   None. 
  
-Particulars
 
   Note:  If you need to find the first element of the array that 
          is greater than x, simply add 1 to the result returned 
          by this function and check to see if the result is 
          within the array bounds given by n. 
 
-Examples
 
   1)  Let array be assigned the following values:

          array[0] = -2.0;
          array[1] = -2.0;
          array[2] =  0.0;
          array[3] =  1.0;
          array[4] =  1.0;
          array[5] = 11.0;


       The table below demonstrates the behavior of lstled_c:

                    Call                       Returned Value
          ===========================          ==============
          lstled_c ( -3.0, 6, array )                -1

          lstled_c ( -2.0, 6, array )                 1

          lstled_c (  0.0, 6, array )                 2

          lstled_c (  1.0, 6, array )                 4

          lstled_c ( 11.1, 6, array )                 5


-Restrictions
 
   If the sequence of elements in array is not non-decreasing, 
   the program will run to completion but the index found will 
   not mean anything. 
 
-Author_and_Institution
 
   N.J. Bachman    (JPL) 
   W.L. Taber      (JPL) 
 
-Literature_References
 
   None. 
 
-Version
 
   -CSPICE Version 1.0.0, 09-JUL-2002 (NJB) (WLT)

-Index_Entries
 
   last d.p. element less_than_or_equal_to 
 
-&
*/

{ /* Begin lstled_c */


  /*
  Map the index returned by the f2c'd routine to the range 0 : n-1.
  The return value -1 indicates "not found." 
  */
 
  return ( (SpiceInt) lstled_ (  (doublereal *) &x,
                                 (integer    *) &n,
                                 (doublereal *) array )   -  1 );

} /* End lstled_c */
