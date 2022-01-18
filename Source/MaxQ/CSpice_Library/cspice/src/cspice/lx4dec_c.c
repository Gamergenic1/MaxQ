/*

-Procedure lx4dec_c (Scan for decimal number)

-Abstract
 
   Scan a string from a specified starting position for the 
   end of a decimal number.  
 
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
 
   PARSING 
 
*/

   #include "SpiceUsr.h"
   #include "SpiceZfc.h"
   #include "SpiceZmc.h"


   void lx4dec_c ( ConstSpiceChar   * string,
                   SpiceInt           first,
                   SpiceInt         * last,
                   SpiceInt         * nchar  ) 

/*

-Brief_I/O
 
   VARIABLE  I/O  DESCRIPTION 
   --------  ---  -------------------------------------------------- 
   string     I   Any character string.
   first      I   First character to scan from in string.
   last       O   Last character that is part of a decimal number.
   nchar      O   Number of characters in the decimal number. 
 
-Detailed_Input
 
   string      is any character string. 
 
   first       is the location in the string to beginning scanning 
               for a decimal number.  It is assumed that the 
               decimal number begins at first.  

               The normal range of first is 0 : strlen(string)-1.
 
-Detailed_Output
 
   last        is the last character at or after first such that the
               substring ranging from string[first] through
               string[last] is a decimal number.  If there is no such
               substring, last will be returned with the value first-1.

               If a decimal number is found, last will be in the
               range is 0 : strlen(string)-1.


   nchar       is the number of characters in the decimal number that
               begins at index first and ends at last.  If there is no
               such string nchar will be given the value 0.
 
-Parameters
 
   None. 
 
-Exceptions
  
   1) If first is beyond either end of the string, then 
      last will be returned with the value first-1 and nchar 
      will be returned with the value 0. 
 
   2) If string[first] is not part of a decimal number then last 
      will be returned with the value first-1 and nchar will be 
      returned with the value 0. 

   3) If the input string pointer is null, the error SPICE(NULLPOINTER)
      will be signaled.

   4) If the input string has length zero, last will be set to first-1
      and nchar will be set to zero.  This case is not considered an
      error.
 
-Files
 
   None. 
 
-Particulars
 
   This routine allows you to scan forward in a string to locate 
   a decimal number that begins on the input character first.  Note 
   that all signed integers are included in the list of decimal 
   numbers.  See lx4sgn_c for a description of signed integers. 
 
   We let S stand for a signed integer and U stand for 
   an unsigned integer.  With this notation, the strings 
   recognized as decimal numbers are: 
 
      U 
      S 
      S. 
      S.U 
       .U 
      -.U 
      +.U 
 
 
-Examples
 
   1) Suppose you believe that a string has the form 
 
         X%Y%Z 
 
      where X, Y, and Z are decimal numbers of some unknown length and
      % stands for any character that cannot occur in a decimal number.
      You could use this routine to locate the decimal numbers in the
      string as shown below.  We'll keep track of the beginning and
      ending of the decimal numbers in the integer arrays b and e.
 

         #include <string.h>
         #include "SpiceUsr.h"

               .
               .
               .

         first = 0;
         i     = 0;
         len   = strlen(string);

         while ( first < len-1 )
         {
            lx4dec_c ( string, first, &last, &nchar );

            if ( nchar > 0 )
            {
               i++;

               b[i]  = first;
               e[i]  = last;
               first = last  +  2;
            }
            else
            {
               first++;  
            }
         }
          

-Restrictions
 
   None. 
 
-Author_and_Institution
 
   N.J. Bachman    (JPL)
   W.L. Taber      (JPL) 
 
-Literature_References
 
   None. 
 
-Version
 
   -CSPICE Version 1.0.0, 18-AUG-2002 (NJB) (WLT)

-Index_Entries
 
   Scan a string for a decimal number. 
 
-&
*/

{ /* Begin lx4dec_c */

   /*
   Local variables 
   */
   SpiceInt                locFirst;
   SpiceInt                len;


   /*
   Use discovery check-in.

   Check the input string argument for a null pointer.
   */
   CHKPTR ( CHK_DISCOVER, "lx4dec_c", string );


   /*
   We're done if the input string has zero length. 
   */
   len = strlen(string);

   if ( len == 0 )
   {
      *last  = -1;
      *nchar =  0;

      return;
   }


   /*
   Map first to a Fortran-style index. 
   */
   locFirst = first + 1;

   /*
   Call the f2c'd routine. 
   */
   lx4dec_ ( ( char    * ) string,
             ( integer * ) &locFirst,
             ( integer * ) last,
             ( integer * ) nchar,
             ( ftnlen    ) len      );

   /*
   Map last to a C-style index. 
   */

   (*last)--;

} /* End lx4dec_c */
