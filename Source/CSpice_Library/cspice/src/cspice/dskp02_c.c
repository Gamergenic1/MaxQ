/*

-Procedure dskp02_c ( DSK, fetch type 2 plate data )

-Abstract
 
   Fetch triangular plates from a type 2 DSK segment. 
 
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
   #include "SpiceZst.h"
   #undef dskp02_c

   void dskp02_c ( SpiceInt              handle,
                   ConstSpiceDLADescr  * dladsc,
                   SpiceInt              start,
                   SpiceInt              room,
                   SpiceInt            * n,
                   SpiceInt              plates[][3] ) 

/*

-Brief_I/O
 
   Variable  I/O  Description 
   --------  ---  -------------------------------------------------- 
   handle     I   DSK file handle. 
   dladsc     I   DLA descriptor. 
   start      I   Start index. 
   room       I   Amount of room in output array. 
   n          O   Number of plates returned. 
   plates     O   Array containing plates. 
 
-Detailed_Input
 
   handle         is the handle of a DSK file containing a type 2 
                  segment from which data are to be fetched. 
 
   dladsc         is the DLA descriptor associated with the segment 
                  from which data are to be fetched.  
 
   start          is the ID of the first plate to be fetched from the
                  segment designated by `handle' and `dladsc'. The ID
                  of a plate is its ordinal position within the
                  segment. Plate IDs range from 1 to NP, where NP is
                  the number of plates in the segment.
 
                  Note that Fortran-style 1-based indexing is used for
                  plate IDs because these IDs must be consistent with
                  the IDs used in DSK files, across all languages
                  supported by SPICE.
  
   room           is the number of plates that can fit in the output
                  `plates' array: the output array must be large enough
                  to hold at least 3*room integer values.
 
-Detailed_Output
 
   n              is the number of plates fetched to the output 
                  array `plates'. `n' is normally in the range  
                  
                     1 : min( NP, room )

                  If an error occurs on the call, `n' is undefined.
 
   plates         is a contiguous set of plates. The returned
                  plates are arranged in order of increasing plate
                  ID. The IDs of the returned plates range from

                     start

                  to

                     start + n - 1 

                  Each plate consists of three vertex indices. The
                  correspondence of elements of `plates' with the
                  elements of the set of plates contained in the
                  segment is:
 
                     plates[0][0]      plate_set[start][0]
                     plates[0][1]      plate_set[start][1]
                     plates[0][2]      plate_set[start][2]
                       ...             ... 
                     plates[n-1][0]    plate_set[start+n-1][0]
                     plates[n-1][1]    plate_set[start+n-1][1] 
                     plates[n-1][2]    plate_set[start+n-1][2] 
                   
                  If an error occurs on the call, `plates' is 
                  undefined. 
 
-Parameters
 
   See the header file
 
       SpiceDLA.h
 
-Exceptions
 
   1) If the input handle is invalid, the error will be diagnosed by 
      routines in the call tree of this routine.  
 
   2) If a file read error occurs, the error will be diagnosed by 
      routines in the call tree of this routine. 
 
   3) If the input DLA descriptor is invalid, the effect of this 
      routine is undefined. The error *may* be diagnosed by routines 
      in the call tree of this routine, but there are no guarantees. 
 
   4) If `room' is non-positive, the error SPICE(VALUEOUTOFRANGE) 
      is signaled. 
 
   5) If `start' is less than 1 or greater than the number of plates 
      in the segment, the error SPICE(INDEXOUTOFRANGE) is signaled. 
 
-Files
 
   See input argument `handle'. 
 
-Particulars
 
   This routine enables SPICE-based user applications to rapidly 
   fetch the plate data from a specified type 2 DSK segment. Using 
   a large output array generally improves efficiency. 
 
-Examples
   
   The numerical results shown for this example may differ across 
   platforms. The results depend on the SPICE kernels used as 
   input, the compiler and supporting libraries, and the machine  
   specific arithmetic implementation.  


   1) Look up all the vertices associated with each plate 
      of the model contained in a specified type 2 segment. For each 
      plate, display the plate's vertices and normal vector. 
 
      For this example, we'll show the context of this look-up: 
      opening the DSK file for read access, traversing a trivial, 
      one-segment list to obtain the segment of interest. 
 
      Example code begins here. 
 
 
         #include <stdio.h>
         #include "SpiceUsr.h"

         int main()
         {   
            /.
            Constants 
            ./
            #define PBUFSIZ         10000
            #define FILSIZ          256

            /.
            Local variables 
            ./
            SpiceBoolean            found;

            SpiceChar               dsk  [ FILSIZ ];

            SpiceDLADescr           dladsc;

            SpiceDouble             normal [3];
            SpiceDouble             verts  [3][3];

            SpiceInt                handle;
            SpiceInt                i;
            SpiceInt                j;
            SpiceInt                n;
            SpiceInt                np;
            SpiceInt                nread;
            SpiceInt                nv;
            SpiceInt                nvtx;
            SpiceInt                plates[PBUFSIZ][3];
            SpiceInt                plix;
            SpiceInt                remain;
            SpiceInt                start;

            /.
            Prompt for name of DSK and open file for reading.
            ./
            prompt_c ( "Enter DSK name > ", FILSIZ, dsk );

            dasopr_c ( dsk,    &handle );

            dlabfs_c ( handle, &dladsc, &found );

            if ( !found )
            { 
               setmsg_c ( "No segment found in file #." );
               errch_c  ( "#",  dsk                     );
               sigerr_c ( "SPICE(NOSEGMENT)"            );
            }

            /.
            Get segment vertex and plate counts.
            ./
            dskz02_c ( handle, &dladsc, &nv, &np );

            printf ( "\n" 
                     "Number of vertices:  %d\n"
                     "Number of plates:    %d\n",
                     (int)nv,
                     (int)np                      );

            /.
            Display the vertices of each plate.
            ./
            remain = np;
            start  = 1;

            while ( remain > 0 )
            { 
               /.
               `nread' is the number of plates we"ll read on this
               loop pass.
               ./
               nread  = mini_c ( 2, PBUFSIZ, remain );

               dskp02_c ( handle, &dladsc, start, nread, &n, plates );

               for ( i = 0; i < nread; i++ )
               {
                  plix = start + i;

                  /.
                  Read the vertices of the current plate.
                  ./
                  for ( j = 0;  j < 3;  j++ )
                  {         
                     dskv02_c ( handle, &dladsc, plates[i][j],  
                                1,      &nvtx,   
                                ( SpiceDouble(*)[3] )(verts[j])  );
                  }

                  /.
                  Display the vertices of the current plate:
                  ./
                  printf ( "\n" 
                           " Plate number: %d\n"
                           "    Vertex 1: ( %16.8e %16.8e %16.8e )\n"
                           "    Vertex 2: ( %16.8e %16.8e %16.8e )\n" 
                           "    Vertex 3: ( %16.8e %16.8e %16.8e )\n",
                           (int)plix,
                           verts[0][0],  verts[0][1],  verts[0][2], 
                           verts[1][0],  verts[1][1],  verts[1][2], 
                           verts[2][0],  verts[2][1],  verts[2][2]   );

                  /.
                  Display the normal vector of the current plate:
                  ./
                  dskn02_c ( handle, &dladsc, plix, normal );

                  printf( "    Normal:   ( %16.8e %16.8e %16.8e )\n",
                          normal[0], normal[1], normal[2]           );
               }

               start  = start  + nread;
               remain = remain - nread;
            }

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
 

      Number of vertices:  12
      Number of plates:    20

       Plate number: 1
          Vertex 1: (   0.00000000e+00   0.00000000e+00   1.17557000e+00 )
          Vertex 2: (   1.05146000e+00   0.00000000e+00   5.25731000e-01 )
          Vertex 3: (   3.24920000e-01   1.00000000e+00   5.25731000e-01 )
          Normal:   (   4.91124160e-01   3.56821347e-01   7.94654382e-01 )

       Plate number: 2
          Vertex 1: (   0.00000000e+00   0.00000000e+00   1.17557000e+00 )
          Vertex 2: (   3.24920000e-01   1.00000000e+00   5.25731000e-01 )
          Vertex 3: (  -8.50651000e-01   6.18034000e-01   5.25731000e-01 )
          Normal:   (  -1.87592328e-01   5.77350079e-01   7.94654645e-01 )

          ...

       Plate number: 20
          Vertex 1: (   8.50651000e-01  -6.18034000e-01  -5.25731000e-01 )
          Vertex 2: (   0.00000000e+00   0.00000000e+00  -1.17557000e+00 )
          Vertex 3: (   8.50651000e-01   6.18034000e-01  -5.25731000e-01 )
          Normal:   (   6.07061680e-01   0.00000000e+00  -7.94654715e-01 )
   
 
-Restrictions
 
   None. 
 
-Literature_References
 
   None. 
 
-Author_and_Institution
 
   N.J. Bachman    (JPL) 
 
-Version
 
   -CSPICE Version 1.1.0, APR-04-2017 (NJB)

      Removed references to old header files. Updated
      example program.

   -DSKLIB_C Version 1.0.1, 22-APR-2014 (NJB)

      The diagram in the Detailed_Output header section showing the
      contents of the output `plates' array has been corrected.

   -DSKLIB_C Version 1.0.0, 04-JUN-2010 (NJB)

-Index_Entries
 
   fetch plate data from a type 2 dsk segment 
 
-&
*/

{ /* Begin dskp02_c */

 
   /*
   Local variables
   */
   integer                 fDLADescr [ SPICE_DLA_DSCSIZ ];

   /*
   Participate in error tracing.
   */
   if ( return_c() )
   {
      return;
   }

   chkin_c ( "dskp02_c" );

   
   /*
   Populate the Fortran DLA descriptor array fDLADescr with the contents
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
   Note that we *don't* adjust the start index 
   to account for Fortran indexing. 

   Call the f2c'd routine.
   */
   dskp02_ ( ( integer  * ) &handle,
             ( integer  * ) fDLADescr,
             ( integer  * ) &start,
             ( integer  * ) &room,
             ( integer  * ) n,
             ( integer  * ) plates    );


   chkout_c ( "dskp02_c" );

} /* End dskp02_c */
