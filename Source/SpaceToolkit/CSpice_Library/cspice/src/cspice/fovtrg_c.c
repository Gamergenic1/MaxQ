/*

-Procedure fovtrg_c ( Is target in FOV at time? )

-Abstract

   Determine if a specified ephemeris object is within the
   field-of-view (FOV) of a specified instrument at a given time.
 
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
 
   CK 
   FRAMES 
   KERNEL 
   NAIF_IDS 
   PCK 
   SPK 
   TIME   
 
-Keywords
 
   EVENT 
   FOV 
   GEOMETRY 
   INSTRUMENT      
 
*/

   #include "SpiceUsr.h"
   #include "SpiceZfc.h"
   #include "SpiceZmc.h"

   void fovtrg_c ( ConstSpiceChar   * inst,
                   ConstSpiceChar   * target,
                   ConstSpiceChar   * tshape,
                   ConstSpiceChar   * tframe,
                   ConstSpiceChar   * abcorr,
                   ConstSpiceChar   * obsrvr,
                   SpiceDouble      * et,
                   SpiceBoolean     * visible  )

/*

-Brief_I/O
 
   VARIABLE         I/O  DESCRIPTION 
   ---------------  ---  ------------------------------------------------  
   inst              I   Name or ID code string of the instrument.
   target            I   Name or ID code string of the target. 
   tshape            I   Type of shape model used for the target.
   tframe            I   Body-fixed, body-centered frame for target body.
   abcorr            I   Aberration correction flag. 
   obsrvr            I   Name or ID code string of the observer.
   et                I   Time of the observation (seconds past J2000).
   visible           O   Visibility flag (SPICETRUE/SPICEFALSE).

-Detailed_Input

   inst       indicates the name of an instrument, such as a
              spacecraft-mounted framing camera. The field of view
              (FOV) of the instrument will be used to determine if
              the target is visible with respect to the instrument.

              The position of the instrument `inst' is considered to
              coincide with that of the ephemeris object `obsrvr' (see
              description below).
       
              The size of the instrument's FOV is constrained by the
              following: There must be a vector A such that all of
              the instrument's FOV boundary vectors have an angular
              separation from A of less than (pi/2)-MARGIN radians
              (see description below). For FOVs that are circular or
              elliptical, the vector A is the boresight. For FOVs
              that are rectangular or polygonal, the vector A is
              calculated.

              See the header of the CSPICE routine getfov_c for a
              description of the required parameters associated with
              an instrument.

              Both object names and NAIF IDs are accepted. For
              example, both "CASSINI_ISS_NAC" and "-82360" are
              accepted. Case and leading or trailing blanks are not
              significant in the string.

   target     is the name of the target body. This routine determines
              if the target body appears in the instrument's field of
              view.

              Both object names and NAIF IDs are accepted. For
              example, both "Moon" and "301" are accepted. Case and
              leading or trailing blanks are not significant in the
              string.

   tshape     is a string indicating the geometric model used to
              represent the shape of the target body. The supported
              options are:

                 'ELLIPSOID'     Use a triaxial ellipsoid model,
                                 with radius values provided via the
                                 kernel pool. A kernel variable
                                 having a name of the form

                                    'BODYnnn_RADII'

                                 where nnn represents the NAIF
                                 integer code associated with the
                                 body, must be present in the kernel
                                 pool. This variable must be
                                 associated with three numeric
                                 values giving the lengths of the
                                 ellipsoid's X, Y, and Z semi-axes.

                 'POINT'         Treat the body as a single point.

              Case and leading or trailing blanks are not
              significant in the string.

   tframe     is the name of the body-fixed, body-centered reference
              frame associated with the target body. Examples of
              such names are 'IAU_SATURN' (for Saturn) and 'ITRF93'
              (for the Earth).

              If the target body is modeled as a point, `tframe'
              is ignored and should be left blank. (Ex: " ").

              Case and leading or trailing blanks bracketing a
              non-blank frame name are not significant in the string.

   abcorr     indicates the aberration corrections to be applied
              when computing the target's position and orientation.

              For remote sensing applications, where the apparent
              position and orientation of the target seen by the
              observer are desired, normally either of the
              corrections:

                 "LT+S"
                 "CN+S"

              should be used. These and the other supported options
              are described below.

              Supported aberration correction options for
              observation (the case where radiation is received by
              observer at `et') are:

                 "NONE"         No correction.
                 "LT"           Light time only
                 "LT+S"         Light time and stellar aberration.
                 "CN"           Converged Newtonian (CN) light time.
                 "CN+S"         CN light time and stellar aberration.

              Supported aberration correction options for
              transmission (the case where radiation is emitted from
              observer at `et') are:

                 "XLT"          Light time only.
                 "XLT+S"        Light time and stellar aberration.
                 "XCN"          Converged Newtonian (CN) light time.
                 "XCN+S"        CN light time and stellar aberration.

              Case, leading and trailing blanks are not significant
              in the string.

   obsrvr     is the name of the body from which the target is
              observed. The instrument `inst' is treated as if it
              were co-located with the observer.

              Both object names and NAIF IDs are accepted. For
              example, both "CASSINI" and "-82" are accepted. Case and
              leading or trailing blanks are not significant in the
              string.

   et         is the observation time in seconds past the J2000
              epoch.

-Detailed_Output

   visible    is SPICETRUE if `target' is fully or partially in the
              field-of-view of `inst' at the time `et'. Otherwise,
              `visible' is SPICEFALSE.

-Parameters

   SPICE_GF_MAXVRT     is the maximum number of vertices that may be used
                       to define the boundary of the specified instrument's
                       field of view. See SpiceGF.h for more details.

   MARGIN              is a small positive number used to constrain the
                       orientation of the boundary vectors of polygonal
                       FOVs. Such FOVs must satisfy the following constraints:

                       1)  The boundary vectors must be contained within
                           a right circular cone of angular radius less
                           than than (pi/2) - MARGIN radians; in
                           other words, there must be a vector A such that all
                           boundary vectors have angular separation from
                           A of less than (pi/2)-MARGIN radians.
      
                       2)  There must be a pair of boundary vectors U, V
                           such that all other boundary vectors lie in
                           the same half space bounded by the plane
                           containing U and V. Furthermore, all other
                           boundary vectors must have orthogonal
                           projections onto a specific plane normal to
                           this plane (the normal plane contains the angle
                           bisector defined by U and V) such that the
                           projections have angular separation of at least
                           2*MARGIN radians from the plane spanned
                           by U and V.
      
                       MARGIN is currently set to 1.D-6.

-Exceptions

   1)  If the name of either the target or observer cannot be
       translated to a NAIF ID code, the error will be diagnosed by
       a routine in the call tree of this routine.

   2)  If the specified aberration correction is an unrecognized
       value, the error will be diagnosed and signaled by a routine
       in the call tree of this routine.

   3)  If the radii of a target body modeled as an ellipsoid cannot
       be determined by searching the kernel pool for a kernel
       variable having a name of the form

          'BODYnnn_RADII'

       where nnn represents the NAIF integer code associated with
       the body, the error will be diagnosed by a routine in the
       call tree of this routine.

   4)  If the target and observer bodies are the same, the error will
       be diagnosed by a routine in the call tree of this routine.

   5)  If the body model specifier `tshape' is invalid, the error will
       be diagnosed either here or by a routine in the call tree of
       this routine.

   6)  If a target body-fixed reference frame associated with a
       non-point target is not recognized, the error will be
       diagnosed by a routine in the call tree of this routine.

   7)  If a target body-fixed reference frame is not centered at
       the corresponding target body, the error will be
       diagnosed by a routine in the call tree of this routine.

   8)  If the instrument name `inst' does not have a corresponding NAIF
       ID code, the error will be diagnosed by a routine in the call
       tree of this routine.

   9)  If the FOV parameters of the instrument are not present in
       the kernel pool, the error will be diagnosed by routines
       in the call tree of this routine.

   10) If the FOV boundary has more than SPICE_GF_MAXVRT vertices, the error
       will be diagnosed by routines in the call tree of this
       routine.
       
   11) If the instrument FOV shape is a polygon or rectangle, and
       this routine cannot find a ray R emanating from the FOV
       vertex such that maximum angular separation of R and any FOV
       boundary vector is within the limit (pi/2)-MARGIN radians,
       the error will be diagnosed by a routine in the call tree of
       this routine. If the FOV is any other shape, the same error
       check will be applied with the instrument boresight vector
       serving the role of R.

   12) If the loaded kernels provide insufficient data to compute a
       requested state vector, the error will be diagnosed by a
       routine in the call tree of this routine.

   13) If an error occurs while reading an SPK or other kernel file,
       the error will be diagnosed by a routine in the call tree
       of this routine.
       
   14) If any input string argument pointer is null, the error
       SPICE(NULLPOINTER) will be signaled.
 
   15) If any input string argument other than `tframe' is empty, the
       error SPICE(EMPTYSTRING) will be signaled.

-Files

   Appropriate SPICE kernels must be loaded by the calling program
   before this routine is called.

   The following data are required:

      - SPK data: ephemeris data for target and observer that
        describe the ephemerides of these objects at the time `et'.
        If aberration corrections are used, the states of
        target and observer relative to the solar system barycenter
        must be calculable from the available ephemeris data.

      - Frame data: if a frame definition is required to convert
        the observer and target states to the body-fixed frame of
        the target, that definition must be available in the kernel
        pool. Typically the definitions of frames not already
        built-in to SPICE are supplied by loading a frame kernel.

      - Data defining the reference frame in which the instrument's
        FOV is defined must be available in the kernel pool. Additionally,
        the name `inst' must be associated with an ID code.

      - IK data: the kernel pool must contain data such that
        the CSPICE routine getfov_c may be called to obtain
        parameters for `inst'.

   The following data may be required:

      - PCK data: bodies modeled as triaxial ellipsoids must have
        orientation data provided by variables in the kernel pool.

        Bodies modeled as triaxial ellipsoids must have radii
        lengths provided by variables in the kernel pool.

      - CK data: if the frame in which the instrument's FOV is
        defined is fixed to a spacecraft, at least one CK file will
        be needed to permit transformation of vectors between that
        frame and both J2000 and the target body-fixed frame.

      - SCLK data: if a CK file is needed, an associated SCLK
        kernel is required to enable conversion between encoded SCLK
        (used to time-tag CK data) and barycentric dynamical time
        (TDB).

   Kernel data are normally loaded via furnsh_c once per program run,
   NOT every time this routine is called.

-Particulars

   To treat the target as a ray rather than as an ephemeris object,
   use the higher-level CSPICE routine fovray_c. fovray_c may be used
   to determine if distant target objects such as stars are visible
   in an instrument's FOV at a given time, as long as the direction
   from the observer to the target can be modeled as a ray.

-Examples
 
   The numerical results shown for these examples may differ across 
   platforms. The results depend on the SPICE kernels used as 
   input, the compiler and supporting libraries, and the machine  
   specific arithmetic implementation.  

   1) A spectacular picture was taken by Cassini's
      narrow-angle camera on Oct. 6, 2010 that shows
      six of Saturn's moons. Let's verify that the moons
      in the picture are Epimetheus, Atlas, Daphnis, Pan,
      Janus, and Enceladus.

      To see this picture, visit:
      http://photojournal.jpl.nasa.gov/catalog/PIA12741
      or go to the PDS Image Node's Image Atlas at
      http://pds-imaging.jpl.nasa.gov/search/search.html.
      Select Cassini as the mission, ISS as the instrument,
      and enter 1_N1665078907.122 as the Product ID in the
      Product tab. Note: these directions may change as the
      PDS Imaging Node changes.

      Use the meta-kernel shown below to load the required SPICE
      kernels. For project meta-kernels similar to the one shown
      below, please see the PDS section of the NAIF FTP server.
      For example, look at the following path for Cassini
      meta-kernels: ftp://naif.jpl.nasa.gov//pub/naif/pds/data/
      co-s_j_e_v-spice-6-v1.0/cosp_1000/extras/mk

         KPL/MK

         File name: fovtrg_ex.tm

         This meta-kernel is intended to support operation of SPICE
         example programs. The kernels shown here should not be
         assumed to contain adequate or correct versions of data
         required by SPICE-based user applications.

         In order for an application to use this meta-kernel, the
         kernels referenced here must be present in the user's
         current working directory.

         The names and contents of the kernels referenced
         by this meta-kernel are as follows:

            File name                     Contents
            ---------                     --------
            naif0010.tls                  Leapseconds
            cpck*.tpc                     Satellite orientation and
                                          radii
            pck00010.tpc                  Planet orientation and
                                          radii
            cas_rocks_v18.tf              FK for small satellites
                                          around Saturn
            cas_v40.tf                    Cassini FK
            cas_iss_v10.ti                Cassini ISS IK
            cas00149.tsc                  Cassini SCLK
            *.bsp                         Ephemeris for Cassini,
                                          planets, and satellites
            10279_10284ra.bc              Orientation for Cassini

         \begindata

            KERNELS_TO_LOAD = ( 'naif0010.tls'
                                'cpck14Oct2010.tpc'
                                'cpck_rock_21Jan2011_merged.tpc'
                                'pck00010.tpc'
                                'cas_rocks_v18.tf'
                                'cas_v40.tf'
                                'cas_iss_v10.ti'
                                'cas00149.tsc'
                                '110317AP_RE_90165_18018.bsp'
                                '110120BP_IRRE_00256_25017.bsp'
                                '101210R_SCPSE_10256_10302.bsp'
                                '10279_10284ra.bc'              )

         \begintext

      Example code begins here.

         #include <stdio.h>
         #include "SpiceUsr.h"
         #include "SpiceZmc.h"
         
         int main()
         {
            
            /.
            Local constants 
            ./ 
            #define META  "fovtrg_ex.tm"
            #define BODLEN 32
            #define TIMLEN 32
            #define FRMLEN 32
            
            /.
            Local variables 
            
            The variable `sclk' is the spacecraft clock time of the image.
            ./
            
            SpiceChar               body[BODLEN];
            SpiceChar               frame_name[FRMLEN];
            SpiceChar             * sclk = "1665078907.122";
            SpiceChar               time[TIMLEN];
            ConstSpiceChar        * time_format = 
                                    "YYYY-MON-DD HR:MN:SC.###::TDB (TDB)";
         
            SpiceDouble             et;
            
            SpiceInt                body_id;
            SpiceInt                cassini_id;
            SpiceInt                frame_code;
            
            SpiceBoolean            found;
            SpiceBoolean            visible;
            
            /.
            Load kernels.
            ./
            furnsh_c ( META );
            
            /.
            Retrieve Cassini's NAIF ID.
            ./
            bodn2c_c ( "Cassini", &cassini_id, &found );
            
            if ( !found ) {
               printf ( "Could not find ID code for Cassini." );
               return (1);     
            }
            
            /.
            Convert the image tag SCLK to ET.
            ./
            scs2e_c ( cassini_id, sclk, &et );
            
            /.
            Convert the ET to a string format for the output.
            ./
            timout_c ( et, time_format, TIMLEN, time );
            
            /.
            Search through all of Saturn's moons to see if each
            satellite was in the ISS NAC's field-of-view at
            the image time. We're going to take advantage of the
            fact that all Saturn's moons have a NAIF ID of 6xx.
            ./
            printf ( "At time %s the following were\n", time );
            printf ( "in the field of view of CASSINI_ISS_NAC\n" );
            
            for ( body_id = 600; body_id < 700; body_id++ ) {
         
               /.
               Check to see if the `body_id' has a translation.
               ./
               bodc2n_c ( body_id, BODLEN, body, &found );
               
               if ( found ) {
                  /.
                  Check to see if a body-fixed frame for this ID exists.
                  If the frame is not in the kernel pool, we cannot
                  perform the visibility test. The main cause of a
                  failure is a missing kernel.
                  ./
                  cidfrm_c ( body_id, FRMLEN, &frame_code, frame_name,
                             &found );
                  
                  if ( found ) {
                     /.
                     Is this body in the field-of-view of Cassini's
                     ISS narrow-angle camera?
                     ./
                     fovtrg_c ( "CASSINI_ISS_NAC", body, "Ellipsoid",
                                 frame_name, "CN+S", "Cassini", &et, 
                                 &visible );
                     if ( visible ) {
                        printf ( "  %s\n", body );
                     }
                  }
               }
            }
            return (0);
         }

      When this program was executed on a PC/Linux/gcc platform, the 
      output was: 

         At time 2010-OCT-06 17:09:45.346 (TDB) the following were
         in the field of view of CASSINI_ISS_NAC
           ENCELADUS
           JANUS
           EPIMETHEUS
           ATLAS
           PAN
           DAPHNIS
           ANTHE
           
      Note: there were actually 7 of Saturn's satellites in the
      field-of-view of Cassini's narrow-angle camera. However, Anthe
      is very small and was probably obscured by other objects or
      shadow.

-Restrictions
 
   The reference frame associated with `inst' must be centered at the
   observer or must be inertial. No check is done to ensure this.
 
-Literature_References
 
   None. 
 
-Author_and_Institution
 
   S.C. Krening  (JPL)
   N.J. Bachman  (JPL) 
 
-Version
 
   -CSPICE Version 1.0.0, 15-FEB-2012 (SCK) (NJB)

-Index_Entries
 
   Target in instrument FOV at specified time
   Target in instrument field_of_view at specified time

-&
*/

{ /* Begin fovtrg_c */

   /*
   Local variables 
   */
   SpiceChar               * tFrameStr;

   /*
   Static variables
   */
   static const SpiceChar  * blankStr = " ";
   
   /*
   Participate in error tracing.
   */
   if ( return_c() )
   {
      return;
   }
   chkin_c ( "fovtrg_c" );

   /*
   Check the input strings to make sure the pointers are non-null
   and the string lengths are non-zero.
   */
   CHKFSTR ( CHK_STANDARD, "fovtrg_c", inst   );
   CHKFSTR ( CHK_STANDARD, "fovtrg_c", target );
   CHKFSTR ( CHK_STANDARD, "fovtrg_c", tshape );
   CHKFSTR ( CHK_STANDARD, "fovtrg_c", abcorr );
   CHKFSTR ( CHK_STANDARD, "fovtrg_c", obsrvr );

   /*
   The input frame name is a special case because we allow the caller
   to pass in an empty string. If this string is empty,
   we pass a null-terminated string containing one blank character to
   the underlying f2c'd routine. 

   First make sure the frame name pointer is non-null.
   */
   CHKPTR ( CHK_STANDARD, "fovtrg_c", tframe );
   
   /*
   Use the input frame string if it's non-empty; otherwise
   use a blank string for the frame name.
   */
  
   if ( tframe[0] )
   {
      tFrameStr = (SpiceChar *) tframe;
   }
   else
   {
      tFrameStr = (SpiceChar *) blankStr;
   }
   
   /*
   Call the f2c'd Fortran routine. Use explicit type casts for every
   type defined by f2c.
   */
   fovtrg_ ( (char         *) inst,
             (char         *) target,
             (char         *) tshape,
             (char         *) tFrameStr,
             (char         *) abcorr,
             (char         *) obsrvr,
             (doublereal   *) et,
             (logical      *) visible,
             (ftnlen        ) strlen(inst),
             (ftnlen        ) strlen(target),
             (ftnlen        ) strlen(tshape),
             (ftnlen        ) strlen(tframe),
             (ftnlen        ) strlen(abcorr),
             (ftnlen        ) strlen(obsrvr)  );
 
 
   chkout_c ( "fovtrg_c" );
 

} /* End fovtrg_c */




