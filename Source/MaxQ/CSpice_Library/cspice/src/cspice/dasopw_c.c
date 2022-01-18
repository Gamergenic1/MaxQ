/*

-Procedure dasopw_c ( DAS, open for write )

-Abstract
 
   Open a DAS file for writing. 
 
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
 
   DAS 
 
-Keywords
 
   DAS 
   FILES 
 
*/

   #include "SpiceUsr.h"
   #include "SpiceZfc.h"
   #include "SpiceZmc.h"


   void dasopw_c ( ConstSpiceChar  * fname,
                   SpiceInt        * handle ) 

/*

-Brief_I/O
 
   Variable  I/O  Description 
   --------  ---  -------------------------------------------------- 
   fname      I   Name of a DAS file to be opened. 
   handle     O   Handle assigned to the opened DAS file. 
 
-Detailed_Input
 
   fname       is the name of a DAS file to be opened with write 
               access. 
 
-Detailed_Output
 
   handle      is the handle that is associated with the file. This 
               handle is used to identify the file in subsequent 
               calls to other DAS routines. 
 
-Parameters
 
   None. 
 
-Exceptions
 
   1)  If the input filename is blank, the error SPICE(BLANKFILENAME)
       will be signaled.
 
   2)  If the specified file does not exist, the error 
       SPICE(FILENOTFOUND) will be signaled. 
 
   3)  If the specified file has already been opened, either by the DAS
       file routines or by other code, the error SPICE(DASOPENCONFLICT)
       is signaled. Note that this response is not paralleled by
       dasopr_c, which allows you to open a DAS file for reading even
       if it is already open for reading.
 
   4)  If the specified file cannot be opened without exceeding the
       maximum allowed number of open DAS files, the error
       SPICE(DASFTFULL) is signaled.
 
   5)  If the named file cannot be opened properly, the error
       SPICE(DASOPENFAIL) is signaled.
 
   6)  If the file record cannot be read, the error
       SPICE(FILEREADFAILED) will be signaled.
 
   7)  If the specified file is not a DAS file, as indicated by the
       file's ID word, the error SPICE(NOTADASFILE) is signaled.
 
   8)  If no logical units are available, the error will be signaled by
       routines called by this routine.
 
-Files
 
   See argument `fname'. 
 
-Particulars
 
   Most DAS files require only read access. If you do not need to 
   change the contents of a file, you should open it using dasopr_c. 
 
-Examples
 
   1)  Open the existing DAS file TEST.DAS for writing. 
 
          dasopw_c ( "TEST.DAS", &handle );
 
-Restrictions
 
   None. 
 
-Literature_References
 
   None. 
 
-Author_and_Institution
 
   N.J. Bachman    (JPL) 
   K.R. Gehringer  (JPL) 
   W.L. Taber      (JPL) 
   F.S. Turner     (JPL) 
   I.M. Underwood  (JPL) 
 
-Version
 
   -CSPICE Version 1.0.0, 11-NOV-2016 (NJB) (KRG) (WLT) (FST) (IMU)

-Index_Entries
 
   open a DAS file for writing 
   open a DAS file for write access 
 
-&
*/

{ /* Begin dasopw_c */


   /*
   Participate in error tracing.
   */
   chkin_c ( "dasopw_c" );

   /*
   Check the input string to make sure the pointer is non-null
   and the string length is non-zero.
   */
   CHKFSTR ( CHK_STANDARD, "dasopw_c", fname );


   /*
   Call the f2c'd Fortran routine.  Use explicit type casts for every
   type defined by f2c.
   */
   dasopw_ ( ( char       * )  fname,
             ( integer    * )  handle,
             ( ftnlen       )  strlen(fname) );


   chkout_c ( "dasopw_c" );

} /* End dasopw_c */
