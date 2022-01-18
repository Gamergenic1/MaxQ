/*

-Procedure subsol_c ( Sub-solar point )

-Abstract
 
   Deprecated: This routine has been superseded by the CSPICE
   routine subslr_c. This routine is supported for purposes of
   backward compatibility only.

   Determine the coordinates of the sub-solar point on a target 
   body as seen by a specified observer at a specified epoch,  
   optionally corrected for planetary (light time) and stellar 
   aberration.   
 
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
 
   FRAMES
   PCK 
   SPK 
   TIME 
 
-Keywords
 
   GEOMETRY 
 
*/

   #include "SpiceUsr.h"
   #include "SpiceZfc.h"
   #include "SpiceZmc.h"
   

   void subsol_c ( ConstSpiceChar   * method,
                   ConstSpiceChar   * target,
                   SpiceDouble        et,
                   ConstSpiceChar   * abcorr,
                   ConstSpiceChar   * obsrvr,
                   SpiceDouble        spoint[3] ) 

/*

-Brief_I/O
 
   Variable  I/O  Description 
   --------  ---  -------------------------------------------------- 
   method     I   Computation method. 
   target     I   Name of target body. 
   et         I   Epoch in ephemeris seconds past J2000 TDB. 
   abcorr     I   Aberration correction. 
   obsrvr     I   Name of observing body. 
   spoint     O   Sub-solar point on the target body. 
 
-Detailed_Input
 
   method      is a short string specifying the computation method 
               to be used.  The choices are: 
 
                  "Near point"       The sub-solar point is defined 
                                     as the nearest point on the 
                                     target to the sun.  
 
                  "Intercept"        The sub-observer point is defined
                                     as the target surface intercept of
                                     the line containing the target's
                                     center and the sun's center.
                   
               In both cases, the intercept computation treats the 
               surface of the target body as a triaxial ellipsoid. 
               The ellipsoid's radii must be available in the kernel 
               pool. 
 
               Neither case nor white space are significant in  
               method.  For example, the string " NEARPOINT" is  
               valid.                  
 
 
   target      is the name of the target body.  `target' is
               case-insensitive, and leading and trailing blanks in
               `target' are not significant. Optionally, you may supply
               a string containing the integer ID code for the object.
               For example both "MOON" and "301" are legitimate strings
               that indicate the moon is the target body.
 
               This routine assumes that the target body is modeled by
               a tri-axial ellipsoid, and that a PCK file containing
               its radii has been loaded into the kernel pool via
               furnsh_c.
 
 
   et          is the epoch in ephemeris seconds past J2000 at which 
               the sub-solar point on the target body is to be 
               computed. 
 
 
   abcorr      indicates the aberration corrections to be applied 
               when computing the observer-target state.  abcorr 
               may be any of the following. 
 
                  "NONE"     Apply no correction. Return the 
                             geometric sub-solar point on the target 
                             body. 
 
                  "LT"       Correct for planetary (light time) 
                             aberration.  Both the state and rotation 
                             of the target body are corrected for one  
                             way light time from target to observer. 
 
                             The state of the sun relative to the  
                             target is corrected for one way light 
                             from the sun to the target; this state 
                             is evaluated at the epoch obtained by 
                             retarding et by the one way light time 
                             from target to observer. 
 
                  "LT+S"     Correct for planetary (light time) and 
                             stellar aberrations.  Light time  
                             corrections are the same as in the "LT" 
                             case above.  The target state is  
                             additionally corrected for stellar 
                             aberration as seen by the observer, and 
                             the sun state is corrected for stellar 
                             aberration as seen from the target.  
 
                  "CN"       Converged Newtonian light time
                             correction. In solving the light time
                             equation, the "CN" correction iterates
                             until the solution converges (three
                             iterations on all supported platforms).
                             Whether the "CN+S" solution is
                             substantially more accurate than the
                             "LT" solution depends on the geometry
                             of the participating objects and on the
                             accuracy of the input data. In all
                             cases this routine will execute more
                             slowly when a converged solution is
                             computed. See the Particulars section
                             below for a discussion of precision of
                             light time corrections.
 
                             Light time corrections are applied as in
                             the "LT" case.
                     
                  "CN+S"     Converged Newtonian light time correction
                             and stellar aberration correction.
 
                             Light time and stellar aberration
                             corrections are applied as in the "LT+S"
                             case.
 
 
   obsrvr      is the name of the observing body.  This is typically 
               a spacecraft, the earth, or a surface point on the 
               earth.  `obsrvr' is case-insensitive, and leading and 
               trailing blanks in `obsrvr' are not significant. 
               Optionally, you may supply a string containing the 
               integer ID code for the object.  For example both 
               "EARTH" and "399" are legitimate strings that indicate 
               the earth is the observer. 

 
-Detailed_Output
 
   spoint      is the sub-solar point on the target body at et,
               expressed relative to the body-fixed frame of the 
               target body. 
 
               The sub-solar point is defined either as the point on 
               the target body that is closest to the sun, or the 
               target surface intercept of the line containing the sun's
               center and the target's center; the input argument 
               method selects the definition to be used. 
 
               The body-fixed frame, which is time-dependent, is 
               evaluated at et if abcorr is "NONE"; otherwise the 
               frame is evaluated at et-lt, where lt is the one way 
               light time from target to observer. 
 
               The state of the target body is corrected for  
               aberration as specified by abcorr; the corrected  
               state is used in the geometric computation.  As  
               indicated above, the rotation of the target is  
               retarded by one way light time if abcorr specifies 
               that light time correction is to be done. 
   
               The state of the sun as seen from the target body  
               body is also corrected for aberration as specified 
               by abcorr.  The corrections, when selected, are 
               applied at the epoch et-lt, where lt is the one way 
               light time from target to observer. 
 
-Parameters
 
   None. 
 
-Exceptions
 
   If any of the listed errors occur, the output arguments are  
   left unchanged. 
  
 
   1)  If the input argument method is not recognized, the error 
       SPICE(DUBIOUSMETHOD) is signaled. 
 
   2)  If either of the input body names target or obsrvr cannot be 
       mapped to NAIF integer codes, the error SPICE(IDCODENOTFOUND) 
       is signaled. 
 
   3)  If obsrvr and target map to the same NAIF integer ID codes, the 
       error SPICE(BODIESNOTDISTINCT) is signaled.   
 
   4)  If frame definition data enabling the evaluation of the state  
       of the target relative to the observer in target body-fixed 
       coordinates have not been loaded prior to calling subsol_c, the 
       error will be diagnosed and signaled by a routine in the call 
       tree of this routine.    
 
   5)  If the specified aberration correction is not recognized, the 
       error will be diagnosed and signaled by a routine in the call 
       tree of this routine. 
 
   6)  If insufficient ephemeris data have been loaded prior to  
       calling subsol_c, the error will be diagnosed and signaled by a  
       routine in the call tree of this routine.   
 
   7)  If the triaxial radii of the target body have not been loaded 
       into the kernel pool prior to calling subsol_c, the error will be  
       diagnosed and signaled by a routine in the call tree of this  
       routine.    
 
   8)  The target must be an extended body:  if any of the radii of  
       the target body are non-positive, the error will be diagnosed 
       and signaled by routines in the call tree of this routine. 
  
   9)  If PCK data supplying a rotation model for the target body  
       have not been loaded prior to calling subsol_c, the error will be  
       diagnosed and signaled by a routine in the call tree of this  
       routine.    
       
   10) If any input string argument pointer is null, the error 
       SPICE(NULLPOINTER) will be signaled.
   
   11) If any input string argument is empty, the error 
       SPICE(EMPTYSTRING) will be signaled.
   
   
-Files
 
   Appropriate SPK, PCK, and frame data must be available to  
   the calling program before this routine is called.  Typically 
   the data are made available by loading kernels; however the 
   data may be supplied via subroutine interfaces if applicable. 
 
   The following data are required: 
 
      - SPK data:  ephemeris data for sun, target, and observer must be
        loaded.  If aberration corrections are used, the states of sun,
        target, and observer relative to the solar system barycenter
        must be calculable from the available ephemeris data. Ephemeris
        data are made available by loading one or more SPK files via
        furnsh_c.

      - PCK data:  triaxial radii for the target body must be loaded 
        into the kernel pool.  Typically this is done by loading a  
        text PCK file via furnsh_c.
 
      - Further PCK data:  a rotation model for the target body must be
        loaded.  This may be provided in a text or binary PCK file
        which is loaded via furnsh_c.

      - Frame data:  if a frame definition is required to convert 
        the sun, observer, and target states to the body-fixed frame 
        of the target, that definition must be available in the  
        kernel pool.  Typically the definition is supplied by loading  
        a frame kernel via furnsh_c.
 
   In all cases, kernel data are normally loaded once per program 
   run, NOT every time this routine is called. 
 
-Particulars
 
   subsol_c computes the sub-solar point on a target body, as seen by 
   a specified observer. 
 
   There are two different popular ways to define the sub-solar point:
   "nearest point on target to the sun" or "target surface intercept of
   line containing target and sun."  These coincide when the target is
   spherical and generally are distinct otherwise.
 
   When comparing sub-point computations with results from sources 
   other than SPICE, it's essential to make sure the same geometric 
   definitions are used.   
    
-Examples
 

   In the following example program, the file MGS.BSP is a
   hypothetical binary SPK ephemeris file containing data for the
   Mars Global Surveyor orbiter.  The SPK file de405s.bsp contains
   data for the planet barycenters as well as the Earth, Moon, and
   Sun for the time period including the date 1997 Dec 31 12:000
   UTC. MGS0000A.TPC is a planetary constants kernel file
   containing radii and rotation model constants.  MGS00001.TLS is
   a leapseconds file.  (File names shown here that are specific
   to MGS are not names of actual files.)


      #include <stdio.h> 
      #include "SpiceUsr.h"

      int main( void )
      {
         #define METHLN          26
         
         SpiceChar               method [2][ METHLN ] =
                                 {
                                    "Intercept", 
                                    "Near point"
                                 };

         SpiceDouble             et;
         SpiceDouble             lat;
         SpiceDouble             lon;
         SpiceDouble             radius;
         SpiceDouble             spoint[3];

         SpiceInt                i;

 
         /.    
         Load kernel files. 
         ./
         furnsh_c ( "MGS00001.TLS" ); 
         furnsh_c ( "MGS0000A.TPC" );
         furnsh_c ( "de405s.bsp"   );
         furnsh_c ( "MGS.BSP"      ); 
 
     
         /.
         Convert the UTC request time to ET (seconds past   
         J2000, TDB). 
         ./
         str2et_c ( "1997 Dec 31 12:00:00", &et );
 
         /.
         Compute sub-spacecraft point using light time and stellar  
         aberration corrections.  Use the "target surface intercept"  
         definition of sub-spacecraft point on the first loop 
         iteration, and use the "near point" definition on the 
         second. 
         ./
         
         for ( i = 0;  i < 2;  i++ )
         {
 
            subsol_c ( method[i], "mars", et, "lt+s", "mgs", spoint ); 
 
            /.
            Convert rectangular coordinates to planetocentric 
            latitude and longitude.  Convert radians to degrees. 
            ./
            reclat_c ( spoint, &radius, &lon, &lat );
 
            lon = lon * dpr_c ();
            lat = lat * dpr_c ();
 
            /.
            Write the results. 
            ./
            
            printf ( "\n"
                     "Computation method:  %s\n"
                     "\n"
                     "  Radius                   (km)  = %f\n"
                     "  Planetocentric Latitude  (deg) = %f\n"
                     "  Planetocentric Longitude (deg) = %f\n"
                     "\n",
                     
                     method[i], radius, lat, lon               );
         }
            
         return ( 0 );
      }
      
      
       
-Restrictions
 
   The appropriate kernel data must have been loaded before this  
   routine is called.  See the Files section above. 
 
-Literature_References
 
   None. 
 
-Author_and_Institution
 
   N.J. Bachman   (JPL) 
   J.E. McLean    (JPL) 
 
-Version
 
   -CSPICE Version 1.0.5, 10-JUL-2014 (NJB)

       Discussion of light time corrections was updated. Assertions
       that converged light time corrections are unlikely to be
       useful were removed.

   -CSPICE Version 1.0.4, 19-MAY-2010 (BVS)

        Index line now states that this routine is deprecated.

   -CSPICE Version 1.0.3, 07-FEB-2008 (NJB)

        Abstract now states that this routine is deprecated.

   -CSPICE Version 1.0.2, 22-JUL-2004 (NJB)

       Updated header to indicate that the `target' and `observer'
       input arguments can now contain string representations of
       integers.  Deleted references to kernel-specific loaders.
       Made miscellaneous minor corrections to header comments.

   -CSPICE Version 1.0.1, 12-DEC-2002 (NJB)

       Corrected and updated code example in header.

   -CSPICE Version 1.0.0, 03-SEP-1999 (NJB)

-Index_Entries
 
   DEPRECATED sub-solar point 
 
-&
*/

{ /* Begin subsol_c */



   /*
   Participate in error tracing.
   */
   chkin_c ( "subsol_c" );

 
   /*
   Check the input strings: method, target, abcorr, and obsrvr.  Make
   sure none of the pointers are null and that each string contains at
   least one non-null character.
   */
   CHKFSTR ( CHK_STANDARD, "subsol_c", method );
   CHKFSTR ( CHK_STANDARD, "subsol_c", target );
   CHKFSTR ( CHK_STANDARD, "subsol_c", abcorr );
   CHKFSTR ( CHK_STANDARD, "subsol_c", obsrvr );
 
 
   /*
   Call the f2c'd routine.
   */
   subsol_ (  ( char         * ) method,
              ( char         * ) target,
              ( doublereal   * ) &et,
              ( char         * ) abcorr,
              ( char         * ) obsrvr,
              ( doublereal   * ) spoint,
              ( ftnlen         ) strlen(method),
              ( ftnlen         ) strlen(target),
              ( ftnlen         ) strlen(abcorr),
              ( ftnlen         ) strlen(obsrvr)  );
 


   chkout_c ( "subsol_c" );

} /* End subsol_c */
