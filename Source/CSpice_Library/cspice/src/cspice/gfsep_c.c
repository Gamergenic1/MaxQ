/*

-Procedure gfsep_c (GF, angular separation search)

-Abstract

   Determine time intervals when the angular separation between
   the position vectors of two target bodies relative to an observer
   satisfies a numerical relationship.

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

   GF
   NAIF_IDS
   SPK
   TIME
   WINDOWS

-Keywords

   SEPARATION
   GEOMETRY
   SEARCH
   EVENT

*/

   #include <stdlib.h>
   #include "SpiceUsr.h"
   #include "SpiceGF.h"
   #include "SpiceZfc.h"
   #include "SpiceZmc.h"
   #include "zzalloc.h"

   void gfsep_c (  ConstSpiceChar     * targ1,
                   ConstSpiceChar     * shape1,
                   ConstSpiceChar     * frame1,
                   ConstSpiceChar     * targ2,
                   ConstSpiceChar     * shape2,
                   ConstSpiceChar     * frame2,
                   ConstSpiceChar     * abcorr,
                   ConstSpiceChar     * obsrvr,
                   ConstSpiceChar     * relate,
                   SpiceDouble          refval,
                   SpiceDouble          adjust,
                   SpiceDouble          step,
                   SpiceInt             nintvls,
                   SpiceCell          * cnfine,
                   SpiceCell          * result  )

/*

-Brief_I/O

   Variable  I/O  Description
   --------  ---  --------------------------------------------------
   SPICE_GF_CNVTOL
              P   Convergence tolerance.
   targ1      I   Name of first body
   shape1     I   Name of shape model describing the first body
   frame1     I   The body-fixed reference frame of the first body
   targ2      I   Name of second body
   shape2     I   Name of the shape model describing the second body
   frame2     I   The body-fixed reference frame of the second body
   abcorr     I   Aberration correction flag
   obsrvr     I   Name of the observing body
   relate     I   Operator that either looks for an extreme value
                  (max, min, local, absolute) or compares the
                  angular separation value and refval
   refval     I   Reference value
   adjust     I   Absolute extremum adjustment value
   step       I   Step size in seconds for finding angular separation
                  events
   nintvls    I   Workspace window interval count
   cnfine    I-O  SPICE window to which the search is restricted
   result     O   SPICE window containing results

-Detailed_Input

   targ1       the string naming the first body of interest. You can
               also supply the integer ID code for the object as an
               integer string.  For example both "MOON" and "301"
               are legitimate strings that indicate the moon is the
               target body.

   shape1      the string naming the geometric model used to represent
               the shape of the targ1 body. Models supported by this routine:

                 "SPHERE"        Treat the body as a sphere with radius
                                 equal to the maximum value of
                                 BODYnnn_RADII

                 "POINT"         Treat the body as a point;
                                 radius has value zero.

               The 'shape1' string lacks sensitivity to case, leading
               and trailing blanks.

   frame1      the string naming the body-fixed reference frame
               corresponding to targ1. gfsep_c does not currently use
               this argument's value, its use is reserved for future
               shape models. The value "NULL" will suffice for
               "POINT" and "SPHERE" shaped bodies.

   targ2       the string naming the second body of interest. You can
               also supply the integer ID code for the object as an
               integer string.  For example both "MOON" and "301"
               are legitimate strings that indicate the moon is the
               target body.

   shape2      the string naming the geometric model used to represent
               the shape of the targ2. Models supported by this routine:

                 "SPHERE"        Treat the body as a sphere with radius
                                 equal to the maximum value of
                                 BODYnnn_RADII

                 "POINT"         Treat the body as a single point;
                                 radius has value zero.

               The 'shape2' string lacks sensitivity to case, leading
               and trailing blanks.

   frame2      the string naming the body-fixed reference frame
               corresponding to 'targ2'. gfsep_c does not currently use
               this argument's value, its use is reserved for future
               shape models. The value "NULL" will suffice for
               "POINT" and "SPHERE" shaped bodies.

   abcorr      the string indicating the aberration corrections to apply
               to the observer-target position vector to account for
               one-way light time and stellar aberration.

               This routine accepts the same aberration corrections as does
               the SPICE routine SPKEZR. See the header of SPKEZR for a
               detailed description of the aberration correction options.
               For convenience, the options are listed below:

                  "NONE"     Apply no correction.

                  "LT"       "Reception" case:  correct for
                             one-way light time using a Newtonian
                             formulation.

                  "LT+S"     "Reception" case:  correct for
                             one-way light time and stellar
                             aberration using a Newtonian
                             formulation.

                  "CN"       "Reception" case:  converged
                             Newtonian light time correction.

                  "CN+S"     "Reception" case:  converged
                             Newtonian light time and stellar
                             aberration corrections.

                  "XLT"      "Transmission" case:  correct for
                             one-way light time using a Newtonian
                             formulation.

                  "XLT+S"    "Transmission" case:  correct for
                             one-way light time and stellar
                             aberration using a Newtonian
                             formulation.

                  "XCN"      "Transmission" case:  converged
                             Newtonian light time correction.

                  "XCN+S"    "Transmission" case:  converged
                             Newtonian light time and stellar
                             aberration corrections.

               The abcorr string lacks sensitivity to case, leading
               and trailing blanks.

   obsrvr      the string naming the observing body. Optionally, you
               may supply the ID code of the object as an integer
               string. For example, both "EARTH" and "399" are
               legitimate strings to supply to indicate the
               observer is Earth.

   relate      the string identifying the relational operator used to
               define a constraint on the angular separation. The result
               window found by this routine indicates the time intervals
               where the constraint is satisfied. Supported values of
               relate and corresponding meanings are shown below:

                  ">"      Separation is greater than the reference
                           value refval.

                  "="      Separation is equal to the reference
                           value refval.

                  "<"      Separation is less than the reference
                           value refval.

                 "ABSMAX"  Separation is at an absolute maximum.

                 "ABSMIN"  Separation is at an absolute  minimum.

                 "LOCMAX"  Separation is at a local maximum.

                 "LOCMIN"  Separation is at a local minimum.

              The caller may indicate that the region of interest
              is the set of time intervals where the quantity is
              within a specified angular separation of an absolute extremum.
              The argument adjust (described below) is used to
              specify this angular separation.

              Local extrema are considered to exist only in the
              interiors of the intervals comprising the confinement
              window:  a local extremum cannot exist at a boundary
              point of the confinement window.

              The relate string lacks sensitivity to case, leading
              and trailing blanks.

   refval     the double precision reference value used together with
              relate argument to define an equality or inequality to be
              satisfied by the angular separation between the specified target
              and observer. See the discussion of relate above for
              further information.

              The units of refval are radians.

   adjust     a double precision value used to modify searches for
              absolute extrema: when relate is set to ABSMAX or ABSMIN and
              adjust is set to a positive value, GFSEP finds times when the
              angular separation between the bodies is within adjust radians
              of the specified extreme value.

              For relate set to ABSMAX, the result window contains
              time intervals when the angular separation has
              values between ABSMAX - adjust and ABSMAX.

              For relate set to ABSMIN, the result window contains
              time intervals when the angular separation has
              values between ABSMIN and ABSMIN + adjust.

              adjust is not used for searches for local extrema,
              equality or inequality conditions.

   step       a double precision value defining the step size to use in
              the search. step must be short enough for a search using step
              to locate the time intervals where the specified
              angular separation function is monotone increasing or
              decreasing. However, step must not be *too* short, or
              the search will take an unreasonable amount of time.

              The choice of step affects the completeness but not
              the precision of solutions found by this routine; the
              precision is controlled by the convergence tolerance.
              See the discussion of the parameter SPICE_GF_CNVTOL for
              details.

              'step' has units of TDB seconds.

   nintvls    an integer value specifying the number of intervals in the
              the internal workspace array used by this routine. 'nintvls'
              should be at least as large as the number of intervals
              within the search region on which the specified observer-target
              vector coordinate function is monotone increasing or decreasing.
              It does no harm to pick a value of 'nintvls' larger than the
              minimum required to execute the specified search, but if chosen
              too small, the search will fail.

   cnfine     a double precision SPICE window that confines the time
              period over which the specified search is conducted.
              cnfine may consist of a single interval or a collection
              of intervals.

              In some cases the confinement window can be used to
              greatly reduce the time period that must be searched
              for the desired solution. See the Particulars section
              below for further discussion.

              See the Examples section below for a code example
              that shows how to create a confinement window.

-Detailed_Output

   cnfine     is the input confinement window, updated if necessary
              so the control area of its data array indicates the
              window's size and cardinality. The window data are
              unchanged.

   result     the SPICE window of intervals, contained within the
              confinement window cnfine, on which the specified
              constraint is satisfied.

              If 'result' is non-empty on input, its contents
              will be discarded before gfsep_c conducts its
              search.

              'result' must be declared and initialized with sufficient
              size to capture the full set of time intervals
              within the search region on which the specified constraint
              is satisfied.

              If the search is for local extrema, or for absolute
              extrema with adjust set to zero, then normally each
              interval of result will be a singleton: the left and
              right endpoints of each interval will be identical.

              If no times within the confinement window satisfy the
              constraint, result will be returned with a
              cardinality of zero.

-Parameters

   SPICE_GF_CNVTOL

              is the convergence tolerance used for finding endpoints
              of the intervals comprising the result window.
              SPICE_GF_CNVTOL is used to determine when binary searches
              for roots should terminate: when a root is bracketed
              within an interval of length SPICE_GF_CNVTOL; the root is
              considered to have been found.

              The accuracy, as opposed to precision, of roots found by
              this routine depends on the accuracy of the input data.
              In most cases, the accuracy of solutions will be inferior
              to their precision.

              SPICE_GF_CNVTOL has the value 1.0e-6. Units are TDB
              seconds.

-Exceptions

   1)  In order for this routine to produce correct results,
       the step size must be appropriate for the problem at hand.
       Step sizes that are too large may cause this routine to miss
       roots; step sizes that are too small may cause this routine
       to run unacceptably slowly and in some cases, find spurious
       roots.

       This routine does not diagnose invalid step sizes, except
       that if the step size is non-positive, an error is signaled
       by a routine in the call tree of this routine.

   2)  Due to numerical errors, in particular,

          - Truncation error in time values
          - Finite tolerance value
          - Errors in computed geometric quantities

       it is *normal* for the condition of interest to not always be
       satisfied near the endpoints of the intervals comprising the
       result window.

       The result window may need to be contracted slightly by the
       caller to achieve desired results. The SPICE window routine
       wncond_c can be used to contract the result window.

   3)  If any input string argument pointer is null, the error
       SPICE(NULLPOINTER) will be signaled.

   4)  If any input string argument is empty, the error
       SPICE(EMPTYSTRING) will be signaled.

   5)  If the workspace interval count 'nintvls' is less than 1, the
       error SPICE(VALUEOUTOFRANGE) will be signaled.

   6)  If the required amount of workspace memory cannot be
       allocated, the error SPICE(MALLOCFAILURE) will be
       signaled.

   7)  If an error (typically cell overflow) occurs while performing
       window arithmetic, the error will be diagnosed by a routine
       in the call tree of this routine.

   8)  If the relational operator `relate' is not recognized, an
       error is signaled by a routine in the call tree of this
       routine.

   9)  If the aberration correction specifier contains an
       unrecognized value, an error is signaled by a routine in the
       call tree of this routine.

   10) If 'adjust' is negative, an error is signaled by a routine in
       the call tree of this routine.

   11) If either of the input body names, 'targ1', 'targ2' do not map
       to NAIF ID codes, an error is signaled by a routine in the
       call tree of this routine.

   12) If either of the input body shape names, 'shape1', 'shape2',
       are not recognized by the GF subsystem, an error is signaled
       by a routine in the call tree of this routine.

   13) If either of the input body frame names, 'frame1', 'frame2',
       are not recognized by the frame subsystem, an error is
       signaled by a routine in the call tree of this routine.

   14) If either of the input body frames, 'frame1', 'frame2',
       are not centered on the corresponding body ('frame1' on 'targ1',
       'frame2' on 'targ2'), an error is signaled by a routine in the
       call tree of this routine.

   15) If required ephemerides or other kernel data are not
       available, an error is signaled by a routine in the call tree
       of this routine.

-Files

   Appropriate SPK and PCK kernels must be loaded by the
   calling program before this routine is called.

   The following data are required:

      - SPK data: the calling application must load ephemeris data
        for the targets, observer, and any intermediate objects in
        a chain connecting the targets and observer that cover the time
        period specified by the window CNFINE. If aberration
        corrections are used, the states of target and observer
        relative to the solar system barycenter must be calculable
        from the available ephemeris data. Typically ephemeris data
        are made available by loading one or more SPK files using
        FURNSH.

      - PCK data: bodies modeled as triaxial ellipsoids must have
        semi-axis lengths provided by variables in the kernel pool.
        Typically these data are made available by loading a text
        PCK file using FURNSH.

      - If non-inertial reference frames are used, then PCK
        files, frame kernels, C-kernels, and SCLK kernels may be
        needed.

   Such kernel data are normally loaded once per program
   run, NOT every time this routine is called.

-Particulars


   This routine provides a simpler, but less flexible interface
   than does the routine gfevnt_c for conducting searches for
   angular separation events. Applications that require support for
   progress reporting, interrupt handling, non-default step or
   refinement functions, or non-default convergence tolerance should
   call gfevnt_c rather than this routine.

   This routine determines a set of one or more time intervals
   within the confinement window for which the angular separation
   between the two bodies satisfies some defined relationship.
   The resulting set of intervals is returned as a SPICE window.

   Below we discuss in greater detail aspects of this routine's
   solution process that are relevant to correct and efficient
   use of this routine in user applications.

   The Search Process
   ==================

   Regardless of the type of constraint selected by the caller, this
   routine starts the search for solutions by determining the time
   periods, within the confinement window, over which the specified
   angular separation function is monotone increasing and monotone
   decreasing. Each of these time periods is represented by a SPICE window.
   Having found these windows, all of the angular separation function's
   local extrema within the confinement window are known. Absolute extrema
   then can be found very easily.

   Within any interval of these "monotone" windows, there will be at
   most one solution of any equality constraint. Since the boundary
   of the solution set for any inequality constraint is contained in
   the union of

      - the set of points where an equality constraint is met
      - the boundary points of the confinement window

   the solutions of both equality and inequality constraints can be
   found easily once the monotone windows have been found.


   Step Size
   =========

   The monotone windows (described above) are found using a two-step
   search process. Each interval of the confinement window is
   searched as follows: first, the input step size is used to
   determine the time separation at which the sign of the rate of
   change of angular separation (angular separation rate) will be
   sampled. Starting at the left endpoint of an interval, samples
   will be taken at each step. If a change of sign is found, a
   root has been bracketed; at that point, the time at which the
   angular separation rate is zero can be found by a refinement
   process, for example, using a binary search.

   Note that the optimal choice of step size depends on the lengths
   of the intervals over which the distance function is monotone:
   the step size should be shorter than the shortest of these
   intervals (within the confinement window).

   The optimal step size is *not* necessarily related to the lengths
   of the intervals comprising the result window. For example, if
   the shortest monotone interval has length 10 days, and if the
   shortest result window interval has length 5 minutes, a step size
   of 9.9 days is still adequate to find all of the intervals in the
   result window. In situations like this, the technique of using
   monotone windows yields a dramatic efficiency improvement over a
   state-based search that simply tests at each step whether the
   specified constraint is satisfied. The latter type of search can
   miss solution intervals if the step size is longer than the
   shortest solution interval.

   Having some knowledge of the relative geometry of the target and
   observer can be a valuable aid in picking a reasonable step size.
   In general, the user can compensate for lack of such knowledge by
   picking a very short step size; the cost is increased computation
   time.

   Note that the step size is not related to the precision with which
   the endpoints of the intervals of the result window are computed.
   That precision level is controlled by the convergence tolerance.


   Convergence Tolerance
   =====================

   As described above, the root-finding process used by this routine
   involves first bracketing roots and then using a search process to
   locate them.  "Roots" include times when extrema are attained and
   times when the geometric quantity function is equal to a reference
   value or adjusted extremum. All endpoints of the intervals comprising
   the result window are either endpoints of intervals of the confinement
   window or roots.

   Once a root has been bracketed, a refinement process is used to
   narrow down the time interval within which the root must lie.
   This refinement process terminates when the location of the root
   has been determined to within an error margin called the
   "convergence tolerance." The convergence tolerance used by this
   routine is set via the parameter SPICE_GF_CNVTOL.

   The value of SPICE_GF_CNVTOL is set to a "tight" value so that the
   tolerance doesn't limit the accuracy of solutions found by this
   routine. In general the accuracy of input data will be the limiting
   factor.

   The user may change the convergence tolerance from the default
   SPICE_GF_CNVTOL value by calling the routine gfstol_c, e.g.

      gfstol_c( tolerance value in seconds )

   Call gfstol_c prior to calling this routine. All subsequent
   searches will use the updated tolerance value.

   Searches over time windows of long duration may require use of
   larger tolerance values than the default: the tolerance must be
   large enough so that it, when added to or subtracted from the
   confinement window's lower and upper bounds, yields distinct time
   values.

   Setting the tolerance tighter than SPICE_GF_CNVTOL is unlikely to be
   useful, since the results are unlikely to be more accurate.
   Making the tolerance looser will speed up searches somewhat,
   since a few convergence steps will be omitted. However, in most
   cases, the step size is likely to have a much greater effect
   on processing time than would the convergence tolerance.


   The Confinement Window
   ======================

   The simplest use of the confinement window is to specify a time
   interval within which a solution is sought. However, the
   confinement window can, in some cases, be used to make searches
   more efficient. Sometimes it's possible to do an efficient search
   to reduce the size of the time period over which a relatively
   slow search of interest must be performed.


   Negative Angular Separation
   ===========================

   For those searches using a SPHERE shape identifier for both
   target bodies, the angular separation function returns a
   negative value when the bodies overlap (occult), e.g.
   a search for an ABSMIN of angular separation in a
   confinement window covering an occultation event will
   return the time when the apparent center of the
   occulting body passes closest to the apparent center of
   the occulted body.


   Elongation
   ===========================

   The angular separation of two targets as seen from an observer
   where one of those targets is the sun is known as elongation.

-Examples


   The numerical results shown for these examples may differ across
   platforms. The results depend on the SPICE kernels used as
   input, the compiler and supporting libraries, and the machine
   specific arithmetic implementation.

      Use the meta-kernel shown below to load the required SPICE
      kernels.

         KPL/MK

         File name: standard.tm

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
            de421.bsp                     Planetary ephemeris
            pck00009.tpc                  Planet orientation and
                                          radii
            naif0009.tls                  Leapseconds

         \begindata

            KERNELS_TO_LOAD = ( 'de421.bsp',
                                'pck00009.tpc',
                                'naif0009.tls'  )

         \begintext

   Example(1):

      Determine the times of local maxima of the angular separation
      between the moon and earth as observed from the sun from
      January 1, 2007 UTC to January 1 2008 UTC.

      #include <stdio.h>
      #include <stdlib.h>
      #include <string.h>

      #include "SpiceUsr.h"

      #define       MAXWIN    1000
      #define       TIMFMT    "YYYY-MON-DD HR:MN:SC.###### (TDB) ::TDB ::RND"
      #define       TIMLEN   41

      int main( int argc, char **argv )
         {

         /.
         Create the needed windows. Note, one window
         consists of two values, so the total number
         of cell values to allocate equals twice
         the number of windows.
         ./
         SPICEDOUBLE_CELL ( result, 2*MAXWIN );
         SPICEDOUBLE_CELL ( cnfine, 2       );

         SpiceDouble       begtim;
         SpiceDouble       endtim;
         SpiceDouble       step;
         SpiceDouble       adjust;
         SpiceDouble       refval;
         SpiceDouble       beg;
         SpiceDouble       end;

         SpiceChar         begstr [ TIMLEN ];
         SpiceChar         endstr [ TIMLEN ];

         SpiceChar       * targ1  = "MOON";
         SpiceChar       * frame1 = "NULL";
         SpiceChar       * shape1 = "SPHERE";

         SpiceChar       * targ2  = "EARTH";
         SpiceChar       * frame2 = "NULL";
         SpiceChar       * shape2 = "SPHERE";

         SpiceChar       * abcorr = "NONE";
         SpiceChar       * relate = "LOCMAX";

         SpiceChar       * obsrvr = "SUN";

         SpiceInt          count;
         SpiceInt          i;

         /.
         Load kernels.
         ./
         furnsh_c( "standard.tm" );

         /.
         Store the time bounds of our search interval in
         the cnfine confinement window.
         ./
         str2et_c( "2007 JAN 01", &begtim );
         str2et_c( "2008 JAN 01", &endtim );

         wninsd_c ( begtim, endtim, &cnfine );

         /.
         Search using a step size of 6 days (in units of seconds).
         ./
         step   = 6.*spd_c();
         adjust = 0.;
         refval = 0.;

         /.
         List the beginning and ending points in each interval
         if result contains data.
         ./
         gfsep_c ( targ1,
                  shape1,
                  frame1,
                  targ2,
                  shape2,
                  frame2,
                  abcorr,
                  obsrvr,
                  relate,
                  refval,
                  adjust,
                  step,
                  MAXWIN,
                  &cnfine,
                  &result );

         count = wncard_c( &result );

         /.
         Display the results.
         ./
         if (count == 0 )
            {
            printf ( "Result window is empty.\n\n" );
            }
         else
            {
            for ( i = 0;  i < count;  i++ )
               {

               /.
               Fetch the endpoints of the Ith interval
               of the result window.
               ./
               wnfetd_c ( &result, i, &beg, &end );

               timout_c ( beg, TIMFMT, TIMLEN, begstr );
               timout_c ( end, TIMFMT, TIMLEN, endstr );

               printf ( "Interval %d\n", i + 1);
               printf ( "Beginning TDB %s \n", begstr );
               printf ( "Ending TDB    %s \n", endstr );

               }
            }

         kclear_c();
         return( 0 );
         }

      The program's partial output:

         Interval 1
         Beginning TDB 2007-JAN-11 11:21:20.213872 (TDB)
         Ending TDB    2007-JAN-11 11:21:20.213872 (TDB)

         Interval 2
         Beginning TDB 2007-JAN-26 01:43:41.029955 (TDB)
         Ending TDB    2007-JAN-26 01:43:41.029955 (TDB)

            ...

         Interval 24
         Beginning TDB 2007-DEC-17 04:04:46.935442 (TDB)
         Ending TDB    2007-DEC-17 04:04:46.935442 (TDB)

         Interval 25
         Beginning TDB 2007-DEC-31 13:43:52.558897 (TDB)
         Ending TDB    2007-DEC-31 13:43:52.558897 (TDB)

   Example(2):

      Determine the time of local maxima elongation of the
      Moon as seen from earth for the same time interval
      as the previous example:

      Edit the Example(1) program to use the assignments:

         SpiceChar       * targ1  = "MOON";
         SpiceChar       * targ2  = "SUN";
         SpiceChar       * obsrvr = "EARTH";

      The program's partial output:

         Interval 1
         Beginning TDB 2007-JAN-03 14:20:24.618884 (TDB)
         Ending TDB    2007-JAN-03 14:20:24.618884 (TDB)

         Interval 2
         Beginning TDB 2007-FEB-02 06:16:24.101655 (TDB)
         Ending TDB    2007-FEB-02 06:16:24.101655 (TDB)

            ...

         Interval 12
         Beginning TDB 2007-NOV-24 14:31:04.334590 (TDB)
         Ending TDB    2007-NOV-24 14:31:04.334590 (TDB)

         Interval 13
         Beginning TDB 2007-DEC-24 01:40:12.238389 (TDB)
         Ending TDB    2007-DEC-24 01:40:12.238389 (TDB)

-Restrictions

   1) The kernel files to be used by this routine must be loaded
      (normally via the CSPICE routine furnsh_c) before this routine
      is called.

   2) This routine has the side effect of re-initializing the
      angular separation quantity utility package.  Callers may
      need to re-initialize the package after calling this routine.

   3) Due to the current logic implemented in zzgfspu, a direct
      search for zero angular separation of two point targets will
      always fails, i.e.,

           'relate' has value "="
           'refval' has value 0.

        Use 'relate' values of "ABSMIN" or "LOCMIN" to detect such an event(s).

-Literature_References

   None.

-Author_and_Institution

   N.J. Bachman   (JPL)
   E.D. Wright    (JPL)

-Version

   -CSPICE Version 1.0.2, 30-JUL-2014 (EDW)

      Edit to argument I/O 'frame1' and 'frame2' to mention use of
      "NULL."

      Edit to header, correct Required Reading entry eliminating ".REQ"
      suffix.

   -CSPICE Version 1.0.1, 28-FEB-2013 (NJB) (EDW)

      Header was updated to discuss use of gfstol_c.

      Edit to comments to correct search description.

      Edited argument descriptions. Removed mention of "ELLIPSOID"
      shape from 'shape1' and 'shape2' as that option is not yet
      implemented.

      Typo corrected in 1.0.1 Version description, replaced
      "gfrr_c" with "gfsep_c."

      Small text edit for clarity on example code description; full date
      strings replaced abbreviated versions.

      Edits to Example section, proper description of "standard.tm"
      meta kernel.

      Edits to Exceptions section to improve description of
      exceptions and error signals.

   -CSPICE Version 1.0.1, 19-AUG-2009 (EDW)

      Corrected typo in the VALUEOUTOFRANGE error message. Corrected
      the routine name in "chkout_c" call, "gfposc_c", with correct
      name "gfsep_c."

   -CSPICE Version 1.0.0, 10-FEB-2009 (NJB) (EDW)

-Index_Entries

   GF angular separation search

-&
*/

   { /* Begin gfsep_c */

   /*
   Local variables
   */
   doublereal            * work;

   static SpiceInt         nw = SPICE_GF_NWSEP;
   SpiceInt                nBytes;


   /*
   Participate in error tracing.
   */
   if ( return_c() )
      {
      return;
      }
   chkin_c ( "gfsep_c" );


   /*
   Make sure cell data types are d.p.
   */
   CELLTYPECHK2 ( CHK_STANDARD, "gfsep_c", SPICE_DP, cnfine, result );

   /*
   Initialize the input cells if necessary.
   */
   CELLINIT2 ( cnfine, result );

   /*
   Check the input strings to make sure each pointer is non-null
   and each string length is non-zero.
   */
   CHKFSTR ( CHK_STANDARD, "gfsep_c", targ1  );
   CHKFSTR ( CHK_STANDARD, "gfsep_c", shape1 );
   CHKFSTR ( CHK_STANDARD, "gfsep_c", frame1 );
   CHKFSTR ( CHK_STANDARD, "gfsep_c", targ2  );
   CHKFSTR ( CHK_STANDARD, "gfsep_c", shape2 );
   CHKFSTR ( CHK_STANDARD, "gfsep_c", frame2 );
   CHKFSTR ( CHK_STANDARD, "gfsep_c", abcorr );
   CHKFSTR ( CHK_STANDARD, "gfsep_c", obsrvr );
   CHKFSTR ( CHK_STANDARD, "gfsep_c", relate );

   /*
   Check the workspace size; some mallocs have a violent
   dislike for negative allocation amounts. To be safe,
   rule out a count of zero intervals as well.
   */

   if ( nintvls < 1 )
      {
      setmsg_c ( "The specified workspace interval count # was "
                 "less than the minimum allowed value of one (1)." );
      errint_c ( "#",  nintvls                              );
      sigerr_c ( "SPICE(VALUEOUTOFRANGE)"                   );
      chkout_c ( "gfsep_c"                                 );
      return;
      }

   /*
   Allocate the workspace. 'nintvls' indicates the maximum number of
   intervals returned in 'result'. An interval consists of
   two values.
   */

   nintvls = 2 * nintvls;

   nBytes = ( nintvls + SPICE_CELL_CTRLSZ ) * nw * sizeof(SpiceDouble);

   work   = (doublereal *) alloc_SpiceMemory( nBytes );

   if ( !work )
      {
      setmsg_c ( "Workspace allocation of # bytes failed due to "
                 "malloc failure"                               );
      errint_c ( "#",  nBytes                                   );
      sigerr_c ( "SPICE(MALLOCFAILED)"                          );
      chkout_c ( "gfsep_c"                                      );
      return;
      }

   /*
   Let the f2'd routine do the work.
   */

   gfsep_( ( char          * ) targ1,
           ( char          * ) shape1,
           ( char          * ) frame1,
           ( char          * ) targ2,
           ( char          * ) shape2,
           ( char          * ) frame2,
           ( char          * ) abcorr,
           ( char          * ) obsrvr,
           ( char          * ) relate,
           ( doublereal    * ) &refval,
           ( doublereal    * ) &adjust,
           ( doublereal    * ) &step,
           ( doublereal    * ) (cnfine->base),
           ( integer       * ) &nintvls,
           ( integer       * ) &nw,
           ( doublereal    * ) work,
           ( doublereal    * ) (result->base),
           ( ftnlen          ) strlen(targ1),
           ( ftnlen          ) strlen(shape1),
           ( ftnlen          ) strlen(frame1),
           ( ftnlen          ) strlen(targ2),
           ( ftnlen          ) strlen(shape2),
           ( ftnlen          ) strlen(frame2),
           ( ftnlen          ) strlen(abcorr),
           ( ftnlen          ) strlen(obsrvr),
           ( ftnlen          ) strlen(relate) );

   /*
   De-allocate the workspace.
   */
   free_SpiceMemory( work );

   /*
   Sync the output cell.
   */
   if ( !failed_c() )
      {
      zzsynccl_c ( F2C, result ) ;
      }

   ALLOC_CHECK;

   chkout_c ( "gfsep_c" );

   } /* End gfsep_c */
