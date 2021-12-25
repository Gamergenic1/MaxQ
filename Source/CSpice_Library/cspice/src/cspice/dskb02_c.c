/*

-Procedure dskb02_c ( DSK, fetch type 2 bookkeeping data )

-Abstract
 
   Return bookkeeping data from a DSK type 2 segment.
 
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
   DSK 
 
-Keywords
 
   DAS 
   DSK 
   FILES 
 
*/

   #include "SpiceUsr.h"
   #include "SpiceZfc.h"
   #include "SpiceZmc.h"
   #undef dskb02_c

   void dskb02_c ( SpiceInt               handle,
                   ConstSpiceDLADescr   * dladsc,
                   SpiceInt             * nv,
                   SpiceInt             * np,
                   SpiceInt             * nvxtot,
                   SpiceDouble            vtxbds  [3][2],
                   SpiceDouble          * voxsiz,
                   SpiceDouble            voxori  [3],
                   SpiceInt               vgrext  [3],
                   SpiceInt             * cgscal,
                   SpiceInt             * vtxnpl,
                   SpiceInt             * voxnpt,
                   SpiceInt             * voxnpl          )

/*

-Brief_I/O
 
   Variable  I/O  Description 
   --------  ---  -------------------------------------------------- 
   handle     I   DSK file handle. 
   dladsc     I   DLA descriptor. 
   nv         O   Number of vertices in model. 
   np         O   Number of plates in model. 
   nvxtot     O   Number of voxels in fine grid. 
   vtxbds     O   Vertex bounds. 
   voxsiz     O   Fine voxel edge length. 
   voxori     O   Fine voxel grid origin. 
   vgrext     O   Fine voxel grid exent. 
   cgscal     O   Coarse voxel grid scale. 
   vtxnpl     O   Size of vertex-plate correspondence list. 
   voxnpt     O   Size of voxel-plate pointer list. 
   voxnpl     O   Size of voxel-plate correspondence list. 
 
-Detailed_Input
 
   handle         is the handle of a DSK file containing a type 2 
                  segment from which data are to be fetched. 
 
   dladsc         is the DLA descriptor associated with the segment 
                  from which data are to be fetched.  
 
-Detailed_Output
 
   nv         Number of vertices in model. 
 
   np         Number of plates in model. 
 
   nvxtot     Total number of voxels in fine grid. 
 
   vtxbds     Vertex bounds. This is an array of six values giving 
              the minimum and maximum values of each component of 
              the vertex set.  `vtxbds' has dimensions [3][2]. 
              Units are km. 
 
   voxsiz     Fine grid voxel size.  DSK voxels are cubes; the edge 
              length of each cube is given by the voxel size.  This 
              size applies to the fine voxel grid.  Units are km. 
 
   voxori     Voxel grid origin.  This is the location of the voxel 
              grid origin in the body-fixed frame associated with 
              the target body.  Units are km. 
 
   vgrext     Voxel grid extent.  This extent is an array of three
              integers indicating the number of voxels in the X, Y, and
              Z directions in the fine voxel grid.
 
   cgscal     Coarse voxel grid scale.  The extent of the fine voxel
              grid is related to the extent of the coarse voxel grid by
              this scale factor.
 
   vtxnpl     Vertex-plate correspondence list size.
 
   voxnpt     Size of the voxel-to-plate pointer list.
 
   voxnpl     Voxel-plate correspondence list size. 
 
 
-Parameters
 
   See the header files  
 
      SpiceDLA.h
      SpiceDSK.h
 
-Exceptions
 
   1) If the input handle is invalid, the error will be diagnosed by 
      routines in the call tree of this routine.  
 
   2) If a file read error occurs, the error will be diagnosed by 
      routines in the call tree of this routine. 
 
   3) If the input DLA descriptor is invalid, the effect of this 
      routine is undefined. The error *may* be diagnosed by routines 
      in the call tree of this routine, but there are no 
      guarantees. 
 
-Files
 
   See input argument `handle'. 
 
-Particulars
 
   This routine supports computations involving bookkeeping information
   stored in DSK type 2 segments. User applications typically will not
   need to call this routine.
 
   DSK files are built using the DLA low-level format and the DAS
   architecture; DLA files are a specialized type of DAS file in which
   data are organized as a doubly linked list of segments.  Each
   segment's data belong to contiguous components of character, double
   precision, and integer type.
 
-Examples
   
   The numerical results shown for this example may differ across 
   platforms. The results depend on the SPICE kernels used as 
   input, the compiler and supporting libraries, and the machine  
   specific arithmetic implementation.  


   1) Dump several parameters from the first DLA segment of  
      a DSK file. The segment is assumed to be of type 2. 
 
      Example code begins here. 

         #include <stdio.h>
         #include "SpiceUsr.h"
         #include "SpiceDLA.h"
         #include "SpiceDSK.h"

         int main()
         {   
            /.
            Constants 
            ./
            #define FILSIZ          256

            /.
            Local variables 
            ./
            SpiceBoolean            found;

            SpiceChar               dsk  [ FILSIZ ];

            SpiceDLADescr           dladsc;

            SpiceDouble             voxori [3];
            SpiceDouble             voxsiz;
            SpiceDouble             vtxbds [3][2];

            SpiceInt                cgscal;
            SpiceInt                handle;
            SpiceInt                np;
            SpiceInt                nv;
            SpiceInt                nvxtot;
            SpiceInt                vgrext [3];
            SpiceInt                voxnpl;
            SpiceInt                voxnpt;
            SpiceInt                vtxnpl;

            /.
            Prompt for the name of DSK to read.
            ./
            prompt_c ( "Enter DSK name > ", FILSIZ, dsk );

            /.
            Open the DSK file for read access. We use the 
            DAS-level interface for this function.
            ./
            dasopr_c ( dsk, &handle );

            /.
            Begin a forward search through the kernel. In 
            this example, it's a very short search.
            ./
            dlabfs_c ( handle, &dladsc, &found );

            if ( !found )
            { 
               setmsg_c ( "No segment found in file #." );
               errch_c  ( "#",  dsk                     );
               sigerr_c ( "SPICE(NOSEGMENT)"            );
            }

            /.
            If we made it this far, DLADSC is the
            DLA descriptor of the first segment.
            Read and display type 2 bookkeeping data.
            ./
            dskb02_c ( handle,  &dladsc, &nv,    &np,    &nvxtot,
                       vtxbds,  &voxsiz, voxori, vgrext, &cgscal,
                       &vtxnpl, &voxnpt, &voxnpl                 );

            printf ( "\n" 
                     "Number of vertices:                 %d\n"
                     "Number of plates:                   %d\n"
                     "Number of voxels:                   %d\n"
                     "Vertex bounds in X direction (km):  %f : %f\n"
                     "Vertex bounds in Y direction (km):  %f : %f\n"
                     "Vertex bounds in Z direction (km):  %f : %f\n"
                     "Voxel edge length (km):             %f\n"
                     "Voxel grid origin (km):           ( %f %f %f )\n"
                     "Voxel grid extents:                 %d %d %d\n"
                     "Coarse voxel grid scale:            %d\n"
                     "Size of vertex-plate list:          %d\n"
                     "Size of voxel-plate pointer array:  %d\n"
                     "Size of voxel-plate list:           %d\n",
                     (int)nv,
                     (int)np,
                     (int)nvxtot,          
                     vtxbds[0][0], vtxbds[0][1],
                     vtxbds[1][0], vtxbds[1][1],
                     vtxbds[2][0], vtxbds[2][1],
                     voxsiz,
                     voxori[0], voxori[1], voxori[2],
                     (int)vgrext[0], (int)vgrext[1], (int)vgrext[2],
                     (int)cgscal,
                     (int)vtxnpl,
                     (int)voxnpt,
                     (int)voxnpl                                       );
            /.
            Close the kernel.  This isn't necessary in a stand-
            alone program, but it's good practice in subroutines
            because it frees program and system resources.
            ./
            dascls_c ( handle );

            return ( 0 );
         }

   When this program was executed on a PC/Linux/gcc/64bit 
   platform, using a DSK file representing a regular icosahedron, 
   the output was:  

      Number of vertices:                 12
      Number of plates:                   20
      Number of voxels:                   512
      Vertex bounds in X direction (km):  -1.051460 : 1.051460
      Vertex bounds in Y direction (km):  -1.000000 : 1.000000
      Vertex bounds in Z direction (km):  -1.175570 : 1.175570
      Voxel edge length (km):             0.901744
      Voxel grid origin (km):           ( -3.606976 -3.606976 -3.606976 )
      Voxel grid extents:                 8 8 8
      Coarse voxel grid scale:            2
      Size of vertex-plate list:          72
      Size of voxel-plate pointer array:  64
      Size of voxel-plate list:           288



-Restrictions
  
   1) The caller must verify that the segment associated with 
      the input DLA descriptor is a DSK type 2 segment. 
 
-Literature_References
 
   None. 
 
-Author_and_Institution
 
   N.J. Bachman    (JPL) 
 
-Version
 
   -CSPICE Version 2.1.0, 11-JUL-2016 (NJB)

      Edit to example program to use "%d" with explicit casts
      to int for printing SpiceInts with printf.

      Removed unnecessary include statements. Updated
      header.

   -DSKLIB_C Version 2.0.1, 11-JUL-2014 (NJB)

      Added example program to header.

   -DSKLIB_C Version 2.0.0, 13-MAY-2010 (NJB)

      Updated for compatibility with new DSK type 2 design.
      Name has been changed from dskp02_c to dskb02_c.

   -DSKLIB_C Version 1.0.0, 11-FEB-2010 (NJB)

-Index_Entries
 
   fetch parameters from a type 2 dsk segment 
 
-&
*/

{ /* Begin dskb02_c */


   /*
   Local variables
   */
   SpiceInt                fDLADescr  [ SPICE_DLA_DSCSIZ ];


   /*
   Participate in error tracing.
   */
   chkin_c ( "dskb02_c" );


   /*
   Populate the Fortran DLA descriptor array fCurrent with the contents
   of the input descriptor.
   */
   fDLADescr[SPICE_DLA_BWDIDX] = dladsc->bwdptr;
   fDLADescr[SPICE_DLA_FWDIDX] = dladsc->fwdptr;
   fDLADescr[SPICE_DLA_IBSIDX] = dladsc->ibase;
   fDLADescr[SPICE_DLA_ISZIDX] = dladsc->isize;
   fDLADescr[SPICE_DLA_DBSIDX] = dladsc->dbase;
   fDLADescr[SPICE_DLA_DSZIDX] = dladsc->dsize;
   fDLADescr[SPICE_DLA_CBSIDX] = dladsc->cbase;
   fDLADescr[SPICE_DLA_CSZIDX] = dladsc->csize;

   /*
   Call the f2c'd routine. 
   */
   dskb02_ ( ( integer     * ) &handle,
             ( integer     * ) fDLADescr,
             ( integer     * ) nv,
             ( integer     * ) np,
             ( integer     * ) nvxtot,
             ( doublereal  * ) vtxbds,
             ( doublereal  * ) voxsiz,
             ( doublereal  * ) voxori,
             ( integer     * ) vgrext,
             ( integer     * ) cgscal,
             ( integer     * ) vtxnpl,
             ( integer     * ) voxnpt,
             ( integer     * ) voxnpl    );             

   /*
   Note:  the array vtxbds is dimensioned

      (2,3)

   in the Fortran routine DSKB02 and

      [3][2]

   in this routine, so transposition of its contents
   is unnecessary. 
   */


   chkout_c ( "dskb02_c" );

} /* End dskb02_c */
