/*

-Procedure prsint_c ( Parse integer with error checking )

-Abstract
 
   Parse a string as an integer, encapsulating error handling. 
 
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
 
   INTEGER 
   PARSING 
 
*/

   #include "SpiceUsr.h"
   #include "SpiceZfc.h"
   #include "SpiceZmc.h"


   void prsint_c ( ConstSpiceChar  * string, 
                   SpiceInt        * intval ) 

/*

-Brief_I/O
 
   Variable  I/O  Description 
   --------  ---  -------------------------------------------------- 
   string     I   String representing an integer. 
   intval     O   Integer value obtained by parsing string. 
 
-Detailed_Input
 
   string         is a string representing an integer.  Any string 
                  acceptable to the CSPICE routine nparsi_ is 
                  allowed. 
 
-Detailed_Output
 
   intval         is the integer obtained by parsing string. 
 
-Parameters
 
   None. 
 
-Exceptions
 
 
   1) If the input string pointer is null, the error 
      SPICE(NULLPOINTER) will be signaled.
       
   2) If the input string does not contain at least one character, 
      the error SPICE(EMPTYSTRING) will be signaled.

   3) If the input string cannot be parsed, the error 
      SPICE(NOTANINTEGER) is signaled. 
 
-Files
 
   None. 
 
-Particulars
 
   The purpose of this routine is to enable safe parsing of integers 
   without the necessity of in-line error checking.  This routine is 
   based on the CSPICE routine nparsi_. 
 
-Examples
 
   See the routine NPARSI for an examples of allowed strings. 
 
-Restrictions
 
   None. 
 
-Literature_References
 
   None. 
 
-Author_and_Institution
 
   N.J. Bachman       (JPL) 
 
-Version
 
   -CSPICE Version 1.1.1, 26-AUG-1999 (NJB)  
   
      Header was updated to list string exceptions.
   
   -CSPICE Version 1.1.0, 08-FEB-1998 (NJB)  
   
       References to C2F_CreateStr_Sig were removed; code was
       cleaned up accordingly.  String checks are now done using
       the macro CHKFSTR.
       
   -CSPICE Version 1.0.0, 25-OCT-1997 (NJB)

-Index_Entries
 
   parse integer with encapsulated error handling 
 
-&
*/

{ /* Begin prsint_c */

   /*
   Participate in error handling.
   */
   chkin_c ( "prsint_c");

   
   /*
   Check the input string to make sure the pointer is non-null 
   and the string length is non-zero.
   */
   CHKFSTR ( CHK_STANDARD, "prsint_c", string );

   
   prsint_ ( ( char      * ) string,
             ( integer   * ) intval,
             ( ftnlen      ) strlen(string) );  

   
   chkout_c ( "prsint_c");

} /* End prsint_c */
