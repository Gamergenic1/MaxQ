/* gfdist.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__5 = 5;
static integer c_n1 = -1;
static integer c__3 = 3;
static integer c__0 = 0;
static logical c_false = FALSE_;

/* $Procedure GFDIST ( GF, distance search ) */
/* Subroutine */ int gfdist_(char *target, char *abcorr, char *obsrvr, char *
	relate, doublereal *refval, doublereal *adjust, doublereal *step, 
	doublereal *cnfine, integer *mw, integer *nw, doublereal *work, 
	doublereal *result, ftnlen target_len, ftnlen abcorr_len, ftnlen 
	obsrvr_len, ftnlen relate_len)
{
    /* System generated locals */
    integer work_dim1, work_offset, i__1;

    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    extern /* Subroutine */ int chkin_(char *, ftnlen);
    extern integer sized_(doublereal *);
    extern logical gfbail_();
    logical ok;
    extern /* Subroutine */ int scardd_(integer *, doublereal *);
    extern /* Subroutine */ int gfrefn_(), gfrepi_(), gfrepf_(), gfrepu_(), 
	    gfstep_();
    char qcpars[80*3], qpnams[80*3];
    extern logical return_(void);
    doublereal qdpars[3];
    integer qipars[3];
    logical qlpars[3];
    extern /* Subroutine */ int setmsg_(char *, ftnlen), errint_(char *, 
	    integer *, ftnlen), sigerr_(char *, ftnlen), chkout_(char *, 
	    ftnlen), gfsstp_(doublereal *), gfevnt_(U_fp, U_fp, char *, 
	    integer *, char *, char *, doublereal *, integer *, logical *, 
	    char *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    logical *, U_fp, U_fp, U_fp, integer *, integer *, doublereal *, 
	    logical *, L_fp, doublereal *, ftnlen, ftnlen, ftnlen, ftnlen);
    doublereal tol;
    extern /* Subroutine */ int zzholdd_(integer *, integer *, logical *, 
	    doublereal *);

/* $ Abstract */

/*     Determine time intervals over which a specified constraint on */
/*     observer-target distance is met. */

/* $ Disclaimer */

/*     THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE */
/*     CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S. */
/*     GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE */
/*     ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE */
/*     PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS" */
/*     TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY */
/*     WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A */
/*     PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC */
/*     SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE */
/*     SOFTWARE AND RELATED MATERIALS, HOWEVER USED. */

/*     IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA */
/*     BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT */
/*     LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND, */
/*     INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS, */
/*     REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE */
/*     REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY. */

/*     RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF */
/*     THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY */
/*     CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE */
/*     ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE. */

/* $ Required_Reading */

/*     GF */
/*     NAIF_IDS */
/*     SPK */
/*     TIME */
/*     WINDOWS */

/* $ Keywords */

/*     EVENT */
/*     GEOMETRY */
/*     EPHEMERIS */
/*     SEARCH */
/*     WINDOW */

/* $ Declarations */
/* $ Abstract */

/*     This file contains public, global parameter declarations */
/*     for the SPICELIB Geometry Finder (GF) subsystem. */

/* $ Disclaimer */

/*     THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE */
/*     CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S. */
/*     GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE */
/*     ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE */
/*     PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS" */
/*     TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY */
/*     WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A */
/*     PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC */
/*     SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE */
/*     SOFTWARE AND RELATED MATERIALS, HOWEVER USED. */

/*     IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA */
/*     BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT */
/*     LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND, */
/*     INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS, */
/*     REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE */
/*     REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY. */

/*     RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF */
/*     THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY */
/*     CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE */
/*     ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE. */

/* $ Required_Reading */

/*     GF */

/* $ Keywords */

/*     GEOMETRY */
/*     ROOT */

/* $ Restrictions */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman      (JPL) */
/*     L.E. Elson        (JPL) */
/*     E.D. Wright       (JPL) */

/* $ Literature_References */

/*     None. */

/* $ Version */

/* -    SPICELIB Version 2.0.0  29-NOV-2016 (NJB) */

/*        Upgraded to support surfaces represented by DSKs. */

/*        Bug fix: removed declaration of NVRMAX parameter. */

/* -    SPICELIB Version 1.3.0, 01-OCT-2011 (NJB) */

/*       Added NWILUM parameter. */

/* -    SPICELIB Version 1.2.0, 14-SEP-2010 (EDW) */

/*       Added NWPA parameter. */

/* -    SPICELIB Version 1.1.0, 08-SEP-2009 (EDW) */

/*       Added NWRR parameter. */
/*       Added NWUDS parameter. */

/* -    SPICELIB Version 1.0.0, 21-FEB-2009 (NJB) (LSE) (EDW) */

/* -& */

/*     Root finding parameters: */

/*     CNVTOL is the default convergence tolerance used by the */
/*     high-level GF search API routines. This tolerance is */
/*     used to terminate searches for binary state transitions: */
/*     when the time at which a transition occurs is bracketed */
/*     by two times that differ by no more than CNVTOL, the */
/*     transition time is considered to have been found. */

/*     Units are TDB seconds. */


/*     NWMAX is the maximum number of windows allowed for user-defined */
/*     workspace array. */

/*        DOUBLE PRECISION      WORK   ( LBCELL : MW, NWMAX ) */

/*     Currently no more than twelve windows are required; the three */
/*     extra windows are spares. */

/*     Callers of GFEVNT can include this file and use the parameter */
/*     NWMAX to declare the second dimension of the workspace array */
/*     if necessary. */


/*     Callers of GFIDST should declare their workspace window */
/*     count using NWDIST. */


/*     Callers of GFSEP should declare their workspace window */
/*     count using NWSEP. */


/*     Callers of GFRR should declare their workspace window */
/*     count using NWRR. */


/*     Callers of GFUDS should declare their workspace window */
/*     count using NWUDS. */


/*     Callers of GFPA should declare their workspace window */
/*     count using NWPA. */


/*     Callers of GFILUM should declare their workspace window */
/*     count using NWILUM. */


/*     ADDWIN is a parameter used to expand each interval of the search */
/*     (confinement) window by a small amount at both ends in order to */
/*     accommodate searches using equality constraints. The loaded */
/*     kernel files must accommodate these expanded time intervals. */


/*     FRMNLN is a string length for frame names. */


/*     FOVTLN -- maximum length for FOV string. */


/*     Specify the character strings that are allowed in the */
/*     specification of field of view shapes. */


/*     Character strings that are allowed in the */
/*     specification of occultation types: */


/*     Occultation target shape specifications: */


/*     Specify the number of supported occultation types and occultation */
/*     type string length: */


/*     Instrument field-of-view (FOV) parameters */

/*     Maximum number of FOV boundary vectors: */


/*     FOV shape parameters: */

/*        circle */
/*        ellipse */
/*        polygon */
/*        rectangle */


/*     End of file gf.inc. */

/* $ Abstract */

/*     SPICE private routine intended solely for the support of SPICE */
/*     routines. Users should not call this routine directly due to the */
/*     volatile nature of this routine. */

/*     This file contains parameter declarations for the ZZHOLDD */
/*     routine. */

/* $ Disclaimer */

/*     THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE */
/*     CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S. */
/*     GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE */
/*     ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE */
/*     PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS" */
/*     TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY */
/*     WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A */
/*     PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC */
/*     SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE */
/*     SOFTWARE AND RELATED MATERIALS, HOWEVER USED. */

/*     IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA */
/*     BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT */
/*     LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND, */
/*     INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS, */
/*     REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE */
/*     REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY. */

/*     RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF */
/*     THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY */
/*     CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE */
/*     ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE. */

/* $ Required_Reading */

/*     None. */

/* $ Keywords */

/*     None. */

/* $ Declarations */

/*     None. */

/* $ Brief_I/O */

/*     None. */

/* $ Detailed_Input */

/*     None. */

/* $ Detailed_Output */

/*     None. */

/* $ Parameters */

/*     GEN       general value, primarily for testing. */

/*     GF_REF    user defined GF reference value. */

/*     GF_TOL    user defined GF convergence tolerance. */

/*     GF_DT     user defined GF step for numeric differentiation. */

/* $ Exceptions */

/*     None. */

/* $ Files */

/*     None. */

/* $ Particulars */

/*     None. */

/* $ Examples */

/*     None. */

/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     E.D. Wright    (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.0.0  03-DEC-2013 (EDW) */

/* -& */

/*     OP codes. The values exist in the integer domain */
/*     [ -ZZNOP, -1], */


/*     Current number of OP codes. */


/*     ID codes. The values exist in the integer domain */
/*     [ 1, NID], */


/*     General use, primarily testing. */


/*     The user defined GF reference value. */


/*     The user defined GF convergence tolerance. */


/*     The user defined GF step for numeric differentiation. */


/*     Current number of ID codes, dimension of array */
/*     in ZZHOLDD. Bad things can happen if this parameter */
/*     does not have the proper value. */


/*     End of file zzholdd.inc. */

/* $ Brief_I/O */

/*     Variable  I/O  Description */
/*     --------  ---  -------------------------------------------------- */
/*     LBCELL     P   SPICE Cell lower bound. */
/*     CNVTOL     P   Convergence tolerance */
/*     NWDIST     P   Number of workspace windows for distance search. */
/*     TARGET     I   Name of the target body. */
/*     ABCORR     I   Aberration correction flag. */
/*     OBSRVR     I   Name of the observing body. */
/*     RELATE     I   Relational operator. */
/*     REFVAL     I   Reference value. */
/*     ADJUST     I   Adjustment value for absolute extrema searches. */
/*     STEP       I   Step size used for locating extrema and roots. */
/*     CNFINE     I   SPICE window to which the search is confined. */
/*     MW         I   Workspace window size. */
/*     NW         I   Workspace window count. */
/*     WORK      I-O   Array of workspace windows. */
/*     RESULT    I-O   SPICE window containing results. */

/* $ Detailed_Input */

/*     TARGET      is the name of a target body. Optionally, you may */
/*                 supply the integer ID code for the object as an */
/*                 integer string.  For example both 'MOON' and '301' */
/*                 are legitimate strings that indicate the moon is the */
/*                 target body. */

/*                 The target and observer define a position vector which */
/*                 points from the observer to the target; the length of */
/*                 this vector is the "distance" that serves as the */
/*                 subject of the search performed by this routine. */

/*                 Case and leading or trailing blanks are not */
/*                 significant in the string TARGET. */


/*     ABCORR      indicates the aberration corrections to be applied to */
/*                 the observer-target position vector to account for */
/*                 one-way light time and stellar aberration. */

/*                 Any aberration correction accepted by the SPICE */
/*                 routine SPKEZR is accepted here. See the header */
/*                 of SPKEZR for a detailed description of the */
/*                 aberration correction options. For convenience, */
/*                 the options are listed below: */

/*                    'NONE'     Apply no correction. */

/*                    'LT'       "Reception" case:  correct for */
/*                               one-way light time using a Newtonian */
/*                               formulation. */

/*                    'LT+S'     "Reception" case:  correct for */
/*                               one-way light time and stellar */
/*                               aberration using a Newtonian */
/*                               formulation. */

/*                    'CN'       "Reception" case:  converged */
/*                               Newtonian light time correction. */

/*                    'CN+S'     "Reception" case:  converged */
/*                               Newtonian light time and stellar */
/*                               aberration corrections. */

/*                    'XLT'      "Transmission" case:  correct for */
/*                               one-way light time using a Newtonian */
/*                               formulation. */

/*                    'XLT+S'    "Transmission" case:  correct for */
/*                               one-way light time and stellar */
/*                               aberration using a Newtonian */
/*                               formulation. */

/*                    'XCN'      "Transmission" case:  converged */
/*                               Newtonian light time correction. */

/*                    'XCN+S'    "Transmission" case:  converged */
/*                               Newtonian light time and stellar */
/*                               aberration corrections. */

/*                 Case and leading or trailing blanks are not */
/*                 significant in the string ABCORR. */


/*     OBSRVR      is the name of an observing body.  Optionally, you */
/*                 may supply the ID code of the object as an integer */
/*                 string. For example, both 'EARTH' and '399' are */
/*                 legitimate strings to supply to indicate the */
/*                 observer is Earth. */

/*                 Case and leading or trailing blanks are not */
/*                 significant in the string OBSRVR. */


/*     RELATE      is a relational operator used to define a constraint */
/*                 on the observer-target distance. The result window */
/*                 found by this routine indicates the time intervals */
/*                 where the constraint is satisfied. Supported values */
/*                 of RELATE and corresponding meanings are shown below: */

/*                    '>'      Distance is greater than the reference */
/*                             value REFVAL. */

/*                    '='      Distance is equal to the reference */
/*                             value REFVAL. */

/*                    '<'      Distance is less than the reference */
/*                             value REFVAL. */


/*                   'ABSMAX'  Distance is at an absolute maximum. */

/*                   'ABSMIN'  Distance is at an absolute  minimum. */

/*                   'LOCMAX'  Distance is at a local maximum. */

/*                   'LOCMIN'  Distance is at a local minimum. */

/*                The caller may indicate that the region of interest is */
/*                the set of time intervals where the distance is within */
/*                a specified offset relative to an absolute extremum. */
/*                The argument ADJUST (described below) is used to */
/*                specify this offset. */

/*                Local extrema are considered to exist only in the */
/*                interiors of the intervals comprising the confinement */
/*                window:  a local extremum cannot exist at a boundary */
/*                point of the confinement window. */

/*                Case and leading or trailing blanks are not */
/*                significant in the string RELATE. */


/*     REFVAL     is the reference value used together with the argument */
/*                RELATE to define an equality or inequality to be */
/*                satisfied by the distance between the specified target */
/*                and observer. See the discussion of RELATE above for */
/*                further information. */

/*                The units of REFVAL are km. */


/*     ADJUST     is a parameter used to modify searches for absolute */
/*                extrema: when RELATE is set to ABSMAX or ABSMIN and */
/*                ADJUST is set to a positive value, GFDIST */
/*                will find times when the observer-target distance is */
/*                within ADJUST km of the specified extreme value. */

/*                If ADJUST is non-zero and a search for an absolute */
/*                minimum AMIN is performed, the result window contains */
/*                time intervals when the observer-target distance has */
/*                values between AMIN and AMIN + ADJUST. */

/*                If the search is for an absolute maximum AMAX, the */
/*                corresponding range is  between AMAX - ADJUST and */
/*                AMAX. */

/*                ADJUST is not used for searches for local extrema, */
/*                equality or inequality conditions. */


/*     STEP       is the step size to be used in the search. STEP must */
/*                be shorter than any maximal time interval on which the */
/*                specified distance function is monotone increasing or */
/*                decreasing. That is, if the confinement window is */
/*                partitioned into alternating intervals on which the */
/*                distance function is either monotone increasing or */
/*                decreasing, STEP must be shorter than any of these */
/*                intervals. */

/*                However, STEP must not be *too* short, or the search */
/*                will take an unreasonable amount of time. */

/*                The choice of STEP affects the completeness but not */
/*                the precision of solutions found by this routine; the */
/*                precision is controlled by the convergence tolerance. */
/*                See the discussion of the parameter CNVTOL for */
/*                details. */

/*                STEP has units of TDB seconds. */


/*     CNFINE     is a SPICE window that confines the time period over */
/*                which the specified search is conducted. CNFINE may */
/*                consist of a single interval or a collection of */
/*                intervals. */

/*                The endpoints of the time intervals comprising CNFINE */
/*                are interpreted as seconds past J2000 TDB. */

/*                See the Examples section below for a code example */
/*                that shows how to create a confinement window. */

/*                CNFINE must be initialized by the caller via the */
/*                SPICELIB routine SSIZED. */


/*     MW         is a parameter specifying the length of the SPICE */
/*                windows in the workspace array WORK (see description */
/*                below) used by this routine. */

/*                MW should be set to a number at least twice as large */
/*                as the maximum number of intervals required by any */
/*                workspace window. In many cases, it's not necessary to */
/*                compute an accurate estimate of how many intervals are */
/*                needed; rather, the user can pick a size considerably */
/*                larger than what's really required. */

/*                However, since excessively large arrays can prevent */
/*                applications from compiling, linking, or running */
/*                properly, sometimes MW must be set according to */
/*                the actual workspace requirement. A rule of thumb */
/*                for the number of intervals NINTVLS needed is */

/*                    NINTVLS  =  2*N  +  ( M / STEP ) */

/*                where */

/*                    N     is the number of intervals in the confinement */
/*                          window */

/*                    M     is the measure of the confinement window, in */
/*                          units of seconds */

/*                    STEP  is the search step size in seconds */

/*                MW should then be set to */

/*                    2 * NINTVLS */


/*     NW         is a parameter specifying the number of SPICE windows */
/*                in the workspace array WORK (see description below) */
/*                used by this routine. NW should be set to the */
/*                parameter NWDIST; this parameter is declared in the */
/*                include file gf.inc. (The reason this dimension is */
/*                an input argument is that this allows run-time */
/*                error checking to be performed.) */


/*     WORK       is an array used to store workspace windows. This */
/*                array should be declared by the caller as shown: */

/*                   INCLUDE 'gf.inc' */
/*                      ... */

/*                   DOUBLE PRECISION    WORK ( LBCELL : MW, NWDIST ) */

/*                where MW is a constant declared by the caller and */
/*                NWDIST is a constant defined in the SPICELIB INCLUDE */
/*                file gf.inc. See the discussion of MW above. */

/*                WORK need not be initialized by the caller. */

/* $ Detailed_Output */

/*     WORK       is the input workspace array, modified by this */
/*                routine. The caller should re-initialize this array */
/*                before attempting to use it for any other purpose. */


/*     RESULT     is the window of intervals, contained within the */
/*                confinement window CNFINE, on which the specified */
/*                constraint is satisfied. */

/*                The endpoints of the time intervals comprising RESULT */
/*                are interpreted as seconds past J2000 TDB. */

/*                If RESULT is non-empty on input, its contents */
/*                will be discarded before GFDIST conducts its */
/*                search. */

/* $ Parameters */

/*     LBCELL     is the lower bound for SPICE Cell arrays. */

/*     CNVTOL     is the convergence tolerance used for finding */
/*                endpoints of the intervals comprising the result */
/*                window. CNVTOL is also used for finding intermediate */
/*                results; in particular, CNVTOL is used for finding the */
/*                windows on which the specified distance is increasing */
/*                or decreasing. CNVTOL is used to determine when binary */
/*                searches for roots should terminate: when a root is */
/*                bracketed within an interval of length CNVTOL; the */
/*                root is considered to have been found. */

/*                The accuracy, as opposed to precision, of roots found */
/*                by this routine depends on the accuracy of the input */
/*                data. In most cases, the accuracy of solutions will be */
/*                inferior to their precision. */

/*     NWDIST     is the number of workspace windows required by */
/*                this routine. */

/*     See INCLUDE file gf.inc for declarations and descriptions of */
/*     parameters used throughout the GF system. */

/* $ Exceptions */

/*     1)  In order for this routine to produce correct results, */
/*         the step size must be appropriate for the problem at hand. */
/*         Step sizes that are too large may cause this routine to miss */
/*         roots; step sizes that are too small may cause this routine */
/*         to run unacceptably slowly and in some cases, find spurious */
/*         roots. */

/*         This routine does not diagnose invalid step sizes, except */
/*         that if the step size is non-positive, the error */
/*         SPICE(INVALIDSTEP) is signaled. */

/*     2)  Due to numerical errors, in particular, */

/*            - Truncation error in time values */
/*            - Finite tolerance value */
/*            - Errors in computed geometric quantities */

/*         it is *normal* for the condition of interest to not always be */
/*         satisfied near the endpoints of the intervals comprising the */
/*         result window. */

/*         The result window may need to be contracted slightly by the */
/*         caller to achieve desired results. The SPICE window routine */
/*         WNCOND can be used to contract the result window. */

/*     3)  If an error (typically cell overflow) occurs while performing */
/*         window arithmetic, the error will be diagnosed by a routine */
/*         in the call tree of this routine. */

/*     4)  If the relational operator RELATE is not recognized, an */
/*         error is signaled by a routine in the call tree of this */
/*         routine. */

/*     5)  If the aberration correction specifier contains an */
/*         unrecognized value, an error is signaled by a routine in the */
/*         call tree of this routine */

/*     6)  If ADJUST is negative, an error is signaled by a routine in */
/*         the call tree of this routine. */

/*     7)  If either of the input body names do not map to NAIF ID */
/*         codes, an error is signaled by a routine in the call tree of */
/*         this routine. */

/*     8)  If required ephemerides or other kernel data are not */
/*         available, an error is signaled by a routine in the call tree */
/*         of this routine. */

/*     9)  If the window size MW is less than 2, the error */
/*         SPICE(INVALIDDIMENSION) will be signaled. */

/*     10) If the window count NW is less than NWDIST, the error */
/*         SPICE(INVALIDDIMENSION) will be signaled. */

/*     11) If the output SPICE window RESULT has insufficient capacity */
/*         to contain the number of intervals on which the specified */
/*         distance condition is met, the error will be diagnosed */
/*         by a routine in the call tree of this routine. If the result */
/*         window has size less than 2, the error SPICE(INVALIDDIMENSION) */
/*         will be signaled by this routine. */


/* $ Files */

/*     Appropriate kernels must be loaded by the calling program before */
/*     this routine is called. */

/*     The following data are required: */

/*        - SPK data: ephemeris data for target and observer for the */
/*          time period defined by the confinement window must be */
/*          loaded. If aberration corrections are used, the states of */
/*          target and observer relative to the solar system barycenter */
/*          must be calculable from the available ephemeris data. */
/*          Typically ephemeris data are made available by loading one */
/*          or more SPK files via FURNSH. */

/*        - If non-inertial reference frames are used, then PCK */
/*          files, frame kernels, C-kernels, and SCLK kernels may be */
/*          needed. */

/*     Kernel data are normally loaded once per program run, NOT every */
/*     time this routine is called. */

/* $ Particulars */

/*     This routine determines a set of one or more time intervals */
/*     within the confinement window when the distance between the */
/*     specified target and observer satisfies a caller-specified */
/*     constraint. The resulting set of intervals is returned as a SPICE */
/*     window. */

/*     Below we discuss in greater detail aspects of this routine's */
/*     solution process that are relevant to correct and efficient */
/*     use of this routine in user applications. */


/*     The Search Process */
/*     ================== */

/*     Regardless of the type of constraint selected by the caller, this */
/*     routine starts the search for solutions by determining the time */
/*     periods, within the confinement window, over which the */
/*     distance function is monotone increasing and monotone */
/*     decreasing. Each of these time periods is represented by a SPICE */
/*     window. Having found these windows, all of the range rate */
/*     function's local extrema within the confinement window are known. */
/*     Absolute extrema then can be found very easily. */

/*     Within any interval of these "monotone" windows, there will be at */
/*     most one solution of any equality constraint. Since the boundary */
/*     of the solution set for any inequality constraint is contained in */
/*     the union of */

/*        - the set of points where an equality constraint is met */
/*        - the boundary points of the confinement window */

/*     the solutions of both equality and inequality constraints can be */
/*     found easily once the monotone windows have been found. */


/*     Step Size */
/*     ========= */

/*     The monotone windows (described above) are found via a two-step */
/*     search process. Each interval of the confinement window is */
/*     searched as follows: first, the input step size is the time */
/*     separation at which the sign of the rate of change of distance */
/*     ("range rate") is sampled. Starting at the left endpoint of the */
/*     interval, samples will be taken at each step. If a change of sign */
/*     is found, a root has been bracketed; at that point, the time at */
/*     which the range rate is zero can be found by a refinement */
/*     process, for example, via binary search. */

/*     Note that the optimal choice of step size depends on the lengths */
/*     of the intervals over which the distance function is monotone: */
/*     the step size should be shorter than the shortest of these */
/*     intervals (within the confinement window). */

/*     The optimal step size is *not* necessarily related to the lengths */
/*     of the intervals comprising the result window. For example, if */
/*     the shortest monotone interval has length 10 days, and if the */
/*     shortest result window interval has length 5 minutes, a step size */
/*     of 9.9 days is still adequate to find all of the intervals in the */
/*     result window. In situations like this, the technique of using */
/*     monotone windows yields a dramatic efficiency improvement over a */
/*     state-based search that simply tests at each step whether the */
/*     specified constraint is satisfied. The latter type of search can */
/*     miss solution intervals if the step size is longer than the */
/*     shortest solution interval. */

/*     Having some knowledge of the relative geometry of the target and */
/*     observer can be a valuable aid in picking a reasonable step size. */
/*     In general, the user can compensate for lack of such knowledge by */
/*     picking a very short step size; the cost is increased computation */
/*     time. */

/*     Note that the step size is not related to the precision with which */
/*     the endpoints of the intervals of the result window are computed. */
/*     That precision level is controlled by the convergence tolerance. */


/*     Convergence Tolerance */
/*     ===================== */

/*     As described above, the root-finding process used by this routine */
/*     involves first bracketing roots and then using a search process */
/*     to locate them. "Roots" include times when extrema are attained */
/*     and times when the distance function is equal to a reference */
/*     value or adjusted extremum. All endpoints of the intervals */
/*     comprising the result window are either endpoints of intervals of */
/*     the confinement window or roots. */

/*     Once a root has been bracketed, a refinement process is used to */
/*     narrow down the time interval within which the root must lie. */
/*     This refinement process terminates when the location of the root */
/*     has been determined to within an error margin called the */
/*     "convergence tolerance." The default convergence tolerance */
/*     used by this routine is set by the parameter CNVTOL (defined */
/*     in gf.inc). */

/*     The value of CNVTOL is set to a "tight" value so that the */
/*     tolerance doesn't become the limiting factor in the accuracy of */
/*     solutions found by this routine. In general the accuracy of input */
/*     data will be the limiting factor. */

/*     The user may change the convergence tolerance from the default */
/*     CNVTOL value by calling the routine GFSTOL, e.g. */

/*        CALL GFSTOL( tolerance value ) */

/*     Call GFSTOL prior to calling this routine. All subsequent */
/*     searches will use the updated tolerance value. */

/*     Setting the tolerance tighter than CNVTOL is unlikely to be */
/*     useful, since the results are unlikely to be more accurate. */
/*     Making the tolerance looser will speed up searches somewhat, */
/*     since a few convergence steps will be omitted. However, in most */
/*     cases, the step size is likely to have a much greater effect */
/*     on processing time than would the convergence tolerance. */


/*     The Confinement Window */
/*     ====================== */

/*     The simplest use of the confinement window is to specify a time */
/*     interval within which a solution is sought. However, the */
/*     confinement window can, in some cases, be used to make searches */
/*     more efficient. Sometimes it's possible to do an efficient search */
/*     to reduce the size of the time period over which a relatively */
/*     slow search of interest must be performed. See the "CASCADE" */
/*     example program in gf.req for a demonstration. */


/* $ Examples */


/*     The numerical results shown for these examples may differ across */
/*     platforms. The results depend on the SPICE kernels used as */
/*     input, the compiler and supporting libraries, and the machine */
/*     specific arithmetic implementation. */


/*     1) Find times during the first three months of the year 2007 when */
/*        the geometric Earth-Moon distance is greater than 400000 km. */
/*        Display the start and stop times of the time intervals over */
/*        which this constraint is met, along with the Earth-Moon */
/*        distance at each interval endpoint. */

/*        We expect the Earth-Moon distance to be an oscillatory */
/*        function with extrema roughly two weeks apart. Using */
/*        a step size of one day guarantees that the GF system */
/*        won't fail to find any distance extrema. (Recall that a */
/*        search for distance extrema is an intermediate step */
/*        in the GF search process.) */

/*        Use the meta-kernel shown below to load the required SPICE */
/*        kernels. */


/*           KPL/MK */

/*           File name: standard.tm */

/*           This meta-kernel is intended to support operation of SPICE */
/*           example programs. The kernels shown here should not be */
/*           assumed to contain adequate or correct versions of data */
/*           required by SPICE-based user applications. */

/*           In order for an application to use this meta-kernel, the */
/*           kernels referenced here must be present in the user's */
/*           current working directory. */

/*           The names and contents of the kernels referenced */
/*           by this meta-kernel are as follows: */

/*              File name                     Contents */
/*              ---------                     -------- */
/*              de421.bsp                     Planetary ephemeris */
/*              pck00008.tpc                  Planet orientation and */
/*                                            radii */
/*              naif0009.tls                  Leapseconds */


/*           \begindata */

/*              KERNELS_TO_LOAD = ( 'de421.bsp', */
/*                                  'pck00008.tpc', */
/*                                  'naif0009.tls'  ) */

/*           \begintext */

/*           End of meta-kernel */



/*        Example code begins here. */


/*           PROGRAM EX1 */
/*           IMPLICIT NONE */
/*     C */
/*     C     Include GF parameter declarations: */
/*     C */
/*           INCLUDE 'gf.inc' */
/*     C */
/*     C     SPICELIB functions */
/*     C */
/*           DOUBLE PRECISION      SPD */
/*           DOUBLE PRECISION      VNORM */
/*           INTEGER               WNCARD */
/*     C */
/*     C     Local parameters */
/*     C */
/*           INTEGER               LBCELL */
/*           PARAMETER           ( LBCELL = -5 ) */
/*     C */
/*     C     Use the parameter MAXWIN for both */
/*     C     the result window size and the workspace */
/*     C     size. */
/*     C */
/*           INTEGER               MAXWIN */
/*           PARAMETER           ( MAXWIN = 20000 ) */
/*     C */
/*     C     Length of output time string: */
/*     C */
/*           INTEGER               TIMLEN */
/*           PARAMETER           ( TIMLEN = 26 ) */
/*     C */
/*     C     Local variables */
/*     C */
/*           CHARACTER*(TIMLEN)    TIMSTR */

/*           DOUBLE PRECISION      ADJUST */
/*           DOUBLE PRECISION      CNFINE ( LBCELL : 2 ) */
/*           DOUBLE PRECISION      DIST */
/*           DOUBLE PRECISION      ET0 */
/*           DOUBLE PRECISION      ET1 */
/*           DOUBLE PRECISION      FINISH */
/*           DOUBLE PRECISION      LT */
/*           DOUBLE PRECISION      POS    ( 3 ) */
/*           DOUBLE PRECISION      REFVAL */
/*           DOUBLE PRECISION      RESULT ( LBCELL : MAXWIN ) */
/*           DOUBLE PRECISION      START */
/*           DOUBLE PRECISION      STEP */
/*           DOUBLE PRECISION      WORK   ( LBCELL : MAXWIN, NWDIST ) */

/*           INTEGER               I */

/*     C */
/*     C     Load kernels. */
/*     C */
/*           CALL FURNSH ( 'standard.tm' ) */
/*     C */
/*     C     Initialize windows. */
/*     C */
/*           CALL SSIZED ( MAXWIN, RESULT ) */
/*           CALL SSIZED ( 2,      CNFINE ) */
/*     C */
/*     C     Store the time bounds of our search interval in */
/*     C     the confinement window. */
/*     C */
/*           CALL STR2ET ( '2007 JAN 1', ET0 ) */
/*           CALL STR2ET ( '2007 APR 1', ET1 ) */

/*           CALL WNINSD ( ET0, ET1, CNFINE ) */
/*     C */
/*     C     Search using a step size of 1 day (in units of */
/*     C     seconds). The reference value is 450000 km. */
/*     C     We're not using the adjustment feature, so */
/*     C     we set ADJUST to zero. */
/*     C */
/*           STEP   = SPD() */
/*           REFVAL = 4.D5 */
/*           ADJUST = 0.D0 */

/*     C */
/*     C     Perform the search. The set of times when the */
/*     C     constraint is met will be stored in the SPICE */
/*     C     window RESULT. */
/*     C */
/*           CALL GFDIST ( 'MOON', 'NONE', 'EARTH', '>', */
/*          .              REFVAL, ADJUST, STEP,    CNFINE, */
/*          .              MAXWIN, NWDIST, WORK,    RESULT ) */
/*     C */
/*     C     Display the results. */
/*     C */
/*           IF ( WNCARD(RESULT) .EQ. 0 ) THEN */
/*              WRITE (*, '(A)') 'Result window is empty.' */
/*           ELSE */
/*              DO I = 1, WNCARD(RESULT) */
/*     C */
/*     C           Fetch the endpoints of the Ith interval */
/*     C           of the result window. */
/*     C */
/*                 CALL WNFETD ( RESULT, I, START, FINISH ) */
/*     C */
/*     C           Check the distance at the start and stop times. */
/*     C */
/*                 CALL SPKPOS ( 'MOON',  START, 'J2000', 'NONE', */
/*          .                    'EARTH', POS,   LT              ) */
/*                 DIST = VNORM(POS) */

/*                 CALL TIMOUT ( START, 'YYYY-MON-DD HR:MN:SC.###', */
/*          .                    TIMSTR                            ) */

/*                 WRITE (*, '(A,F16.9)' ) 'Start time, distance = '// */
/*          .                              TIMSTR, DIST */

/*                 CALL SPKPOS ( 'MOON',  FINISH, 'J2000', 'NONE', */
/*          .                    'EARTH', POS,     LT              ) */
/*                 DIST = VNORM(POS) */

/*                 CALL TIMOUT ( FINISH, 'YYYY-MON-DD HR:MN:SC.###', */
/*          .                    TIMSTR                            ) */

/*                 WRITE (*, '(A,F16.9)' ) 'Stop time,  distance = '// */
/*          .                              TIMSTR, DIST */
/*              END DO */

/*           END IF */
/*           END */



/*        When this program was executed on a PC/Linux/g77 platform, the */
/*        output was: */


/*    Start time, distance = 2007-JAN-08 00:10:02.439  399999.999999989 */
/*    Stop time,  distance = 2007-JAN-13 06:36:42.770  400000.000000010 */
/*    Start time, distance = 2007-FEB-04 07:01:30.094  399999.999999990 */
/*    Stop time,  distance = 2007-FEB-10 09:29:56.659  399999.999999998 */
/*    Start time, distance = 2007-MAR-03 00:19:19.998  400000.000000006 */
/*    Stop time,  distance = 2007-MAR-10 14:03:33.312  400000.000000007 */
/*    Start time, distance = 2007-MAR-29 22:52:52.961  399999.999999995 */
/*    Stop time,  distance = 2007-APR-01 00:00:00.000  404531.955232216 */

/*        Note that at the final solutions interval's stop time is not */
/*        close to the reference value of 400000 km. This is because the */
/*        interval's stop time was determined by the stop time of the */
/*        confinement window. */



/*     2) Extend the first example to demonstrate use of all supported */
/*        relational operators. Find times when */

/*           Earth-Moon distance is = 400000 km */
/*           Earth-Moon distance is < 400000 km */
/*           Earth-Moon distance is > 400000 km */
/*           Earth-Moon distance is at a local minimum */
/*           Earth-Moon distance is at a absolute minimum */
/*           Earth-Moon distance is > the absolute minimum + 100 km */
/*           Earth-Moon distance is at a local maximum */
/*           Earth-Moon distance is at a absolute maximum */
/*           Earth-Moon distance is > the absolute maximum - 100 km */

/*        To shorten the search time and output, use the */
/*        shorter search interval */

/*           2007 JAN 15 00:00:00 UTC  to */
/*           2007 MAR 15 00:00:00 UTC */

/*        As before, use geometric (uncorrected) positions, so */
/*        set the aberration correction flag to 'NONE'. */

/*        Use the meta-kernel from the first example. */


/*        Example code begins here. */


/*           PROGRAM EX2 */
/*           IMPLICIT NONE */
/*     C */
/*     C     Include GF parameter declarations: */
/*     C */
/*           INCLUDE 'gf.inc' */
/*     C */
/*     C     SPICELIB functions */
/*     C */
/*           DOUBLE PRECISION      SPD */
/*           DOUBLE PRECISION      VNORM */
/*           INTEGER               WNCARD */
/*     C */
/*     C     Local parameters */
/*     C */
/*           INTEGER               LBCELL */
/*           PARAMETER           ( LBCELL = -5 ) */
/*     C */
/*     C     Use the parameter MAXWIN for both */
/*     C     the result window size and the workspace */
/*     C     size. */
/*     C */
/*           INTEGER               MAXWIN */
/*           PARAMETER           ( MAXWIN = 20000 ) */
/*     C */
/*     C     Length of output time string: */
/*     C */
/*           INTEGER               TIMLEN */
/*           PARAMETER           ( TIMLEN = 26 ) */

/*     C */
/*     C     Number of relational operators: */
/*     C */
/*           INTEGER               NRELOP */
/*           PARAMETER           ( NRELOP = 9 ) */

/*     C */
/*     C     Operator name length: */
/*     C */
/*           INTEGER               OPNMLN */
/*           PARAMETER           ( OPNMLN = 6 ) */

/*     C */
/*     C     Output line length: */
/*     C */
/*           INTEGER               LNSIZE */
/*           PARAMETER           ( LNSIZE = 80 ) */

/*     C */
/*     C     Local variables */
/*     C */
/*           CHARACTER*(OPNMLN)    RELATE ( NRELOP ) */
/*           CHARACTER*(LNSIZE)    TEMPLT ( NRELOP ) */
/*           CHARACTER*(TIMLEN)    TIMSTR */
/*           CHARACTER*(LNSIZE)    TITLE */

/*           DOUBLE PRECISION      ADJUST ( NRELOP ) */
/*           DOUBLE PRECISION      CNFINE ( LBCELL : 2 ) */
/*           DOUBLE PRECISION      DIST */
/*           DOUBLE PRECISION      ET0 */
/*           DOUBLE PRECISION      ET1 */
/*           DOUBLE PRECISION      FINISH */
/*           DOUBLE PRECISION      LT */
/*           DOUBLE PRECISION      POS    ( 3 ) */
/*           DOUBLE PRECISION      REFVAL */
/*           DOUBLE PRECISION      RESULT ( LBCELL : MAXWIN ) */
/*           DOUBLE PRECISION      START */
/*           DOUBLE PRECISION      STEP */
/*           DOUBLE PRECISION      WORK   ( LBCELL : MAXWIN, NWDIST ) */

/*           INTEGER               I */
/*           INTEGER               J */

/*     C */
/*     C     Saved variables */
/*     C */
/*           SAVE                  ADJUST */
/*           SAVE                  RELATE */
/*           SAVE                  TEMPLT */

/*     C */
/*     C     Initial values */
/*     C */
/*           DATA                  ADJUST / 0.D0, */
/*          .                               0.D0, */
/*          .                               0.D0, */
/*          .                               0.D0, */
/*          .                               0.D0, */
/*          .                               100.D0, */
/*          .                               0.D0, */
/*          .                               0.D0, */
/*          .                               100.D0 / */

/*           DATA                  RELATE / '=', */
/*          .                               '<', */
/*          .                               '>', */
/*          .                               'LOCMIN', */
/*          .                               'ABSMIN', */
/*          .                               'ABSMIN', */
/*          .                               'LOCMAX', */
/*          .                               'ABSMAX', */
/*          .                               'ABSMAX'  / */

/*           DATA                  TEMPLT / */
/*          .      'Condition: distance = # km', */
/*          .      'Condition: distance < # km', */
/*          .      'Condition: distance > # km', */
/*          .      'Condition: distance is a local minimum', */
/*          .      'Condition: distance is the absolute minimum', */
/*          .      'Condition: distance < the absolute minimum + * km', */
/*          .      'Condition: distance is a local maximum', */
/*          .      'Condition: distance is the absolute maximum', */
/*          .      'Condition: distance > the absolute maximum - * km' / */

/*     C */
/*     C     Load kernels. */
/*     C */
/*           CALL FURNSH ( 'standard.tm' ) */
/*     C */
/*     C     Initialize windows. */
/*     C */
/*           CALL SSIZED ( MAXWIN, RESULT ) */
/*           CALL SSIZED ( 2,      CNFINE ) */
/*     C */
/*     C     Store the time bounds of our search interval in */
/*     C     the confinement window. */
/*     C */
/*           CALL STR2ET ( '2007 JAN 15', ET0 ) */
/*           CALL STR2ET ( '2007 MAR 15', ET1 ) */

/*           CALL WNINSD ( ET0, ET1, CNFINE ) */

/*     C */
/*     C     Search using a step size of 1 day (in units of */
/*     C     seconds). Use a reference value of 400000 km. */
/*     C */
/*           STEP   = SPD() */
/*           REFVAL = 4.D5 */

/*           DO I = 1, NRELOP */

/*              CALL GFDIST ( 'MOON', 'NONE',    'EARTH', RELATE(I), */
/*          .                 REFVAL, ADJUST(I), STEP,    CNFINE, */
/*          .                 MAXWIN, NWDIST,    WORK,    RESULT    ) */
/*     C */
/*     C        Display the results. */
/*     C */
/*              WRITE (*,*) ' ' */

/*     C */
/*     C        Substitute the reference and adjustment values, */
/*     C        where applicable, into the title string: */
/*     C */
/*              CALL REPMD ( TEMPLT(I), '#', REFVAL,    6, TITLE ) */
/*              CALL REPMD ( TITLE,     '*', ADJUST(I), 6, TITLE ) */

/*              WRITE (*, '(A)' ) TITLE */

/*              IF ( WNCARD(RESULT) .EQ. 0 ) THEN */
/*                 WRITE (*, '(A)' ) ' Result window is empty.' */
/*              ELSE */
/*                 WRITE (*, '(A)' ) ' Result window:' */

/*                 DO J = 1, WNCARD(RESULT) */
/*     C */
/*     C              Fetch the endpoints of the Jth interval */
/*     C              of the result window. */
/*     C */
/*                    CALL WNFETD ( RESULT, J, START, FINISH ) */
/*     C */
/*     C              Check the distance at the start and stop times. */
/*     C */
/*                    CALL SPKPOS ( 'MOON',  START, 'J2000', 'NONE', */
/*          .                       'EARTH', POS,   LT              ) */
/*                    DIST = VNORM(POS) */

/*                    CALL TIMOUT ( START, 'YYYY-MON-DD HR:MN:SC.###', */
/*          .                       TIMSTR                            ) */

/*                    WRITE (*, '(A,F16.9)' ) '  Start time, distance = ' */
/*          .         //                      TIMSTR, DIST */

/*                    CALL SPKPOS ( 'MOON',  FINISH, 'J2000', 'NONE', */
/*          .                       'EARTH', POS,     LT              ) */
/*                    DIST = VNORM(POS) */

/*                    CALL TIMOUT ( FINISH, 'YYYY-MON-DD HR:MN:SC.###', */
/*          .                       TIMSTR                            ) */

/*                    WRITE (*, '(A,F16.9)' ) '  Stop time,  distance = ' */
/*          .         //                      TIMSTR, DIST */
/*                 END DO */

/*              END IF */

/*           END DO */

/*           WRITE (*,*) ' ' */

/*           END */


/*        When this program was executed on a PC/Linux/g77 platform, the */
/*        output was: */


/*    Condition: distance = 4.00000E+05 km */
/*     Result window: */
/*      Start time, distance = 2007-FEB-04 07:01:30.094  399999.999999998 */
/*      Stop time,  distance = 2007-FEB-04 07:01:30.094  399999.999999998 */
/*      Start time, distance = 2007-FEB-10 09:29:56.659  399999.999999989 */
/*      Stop time,  distance = 2007-FEB-10 09:29:56.659  399999.999999989 */
/*      Start time, distance = 2007-MAR-03 00:19:19.998  399999.999999994 */
/*      Stop time,  distance = 2007-MAR-03 00:19:19.998  399999.999999994 */
/*      Start time, distance = 2007-MAR-10 14:03:33.312  400000.000000000 */
/*      Stop time,  distance = 2007-MAR-10 14:03:33.312  400000.000000000 */

/*    Condition: distance < 4.00000E+05 km */
/*     Result window: */
/*      Start time, distance = 2007-JAN-15 00:00:00.000  393018.609906208 */
/*      Stop time,  distance = 2007-FEB-04 07:01:30.094  399999.999999990 */
/*      Start time, distance = 2007-FEB-10 09:29:56.659  399999.999999998 */
/*      Stop time,  distance = 2007-MAR-03 00:19:19.998  400000.000000006 */
/*      Start time, distance = 2007-MAR-10 14:03:33.312  400000.000000010 */
/*      Stop time,  distance = 2007-MAR-15 00:00:00.000  376255.453934464 */

/*    Condition: distance > 4.00000E+05 km */
/*     Result window: */
/*      Start time, distance = 2007-FEB-04 07:01:30.094  399999.999999990 */
/*      Stop time,  distance = 2007-FEB-10 09:29:56.659  399999.999999998 */
/*      Start time, distance = 2007-MAR-03 00:19:19.998  400000.000000006 */
/*      Stop time,  distance = 2007-MAR-10 14:03:33.312  400000.000000010 */

/*    Condition: distance is a local minimum */
/*     Result window: */
/*      Start time, distance = 2007-JAN-22 12:30:49.458  366925.804109350 */
/*      Stop time,  distance = 2007-JAN-22 12:30:49.458  366925.804109350 */
/*      Start time, distance = 2007-FEB-19 09:36:29.968  361435.646812061 */
/*      Stop time,  distance = 2007-FEB-19 09:36:29.968  361435.646812061 */

/*    Condition: distance is the absolute minimum */
/*     Result window: */
/*      Start time, distance = 2007-FEB-19 09:36:29.968  361435.646812061 */
/*      Stop time,  distance = 2007-FEB-19 09:36:29.968  361435.646812061 */

/*    Condition: distance < the absolute minimum + 1.00000E+02 km */
/*     Result window: */
/*      Start time, distance = 2007-FEB-19 01:09:52.706  361535.646812062 */
/*      Stop time,  distance = 2007-FEB-19 18:07:45.136  361535.646812061 */

/*    Condition: distance is a local maximum */
/*     Result window: */
/*      Start time, distance = 2007-FEB-07 12:38:29.870  404992.424288620 */
/*      Stop time,  distance = 2007-FEB-07 12:38:29.870  404992.424288620 */
/*      Start time, distance = 2007-MAR-07 03:37:02.122  405853.452130754 */
/*      Stop time,  distance = 2007-MAR-07 03:37:02.122  405853.452130754 */

/*    Condition: distance is the absolute maximum */
/*     Result window: */
/*      Start time, distance = 2007-MAR-07 03:37:02.122  405853.452130754 */
/*      Stop time,  distance = 2007-MAR-07 03:37:02.122  405853.452130754 */

/*    Condition: distance > the absolute maximum - 1.00000E+02 km */
/*     Result window: */
/*      Start time, distance = 2007-MAR-06 15:56:00.957  405753.452130753 */
/*      Stop time,  distance = 2007-MAR-07 15:00:38.674  405753.452130753 */


/* $ Restrictions */

/*     1) The kernel files to be used by this routine must be loaded */
/*        (normally via the SPICELIB routine FURNSH) before this routine */
/*        is called. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman   (JPL) */
/*     E.D. Wright    (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.1.0, 05-SEP-2012 (EDW) */

/*        Edit to comments to correct search description. */

/*        Implemented use of ZZHOLDD to allow user to alter convergence */
/*        tolerance. */

/*        Removed the STEP > 0 error check. The GFSSTP call includes */
/*        the check. */

/* -    SPICELIB Version 1.0.0, 15-APR-2009 (NJB) (EDW) */

/* -& */
/* $ Index_Entries */

/*     GF distance search */

/* -& */

/*     SPICELIB functions */


/*     External functions */


/*     Interrupt indicator function: */


/*     Routines to set step size, refine transition times */
/*     and report work. */


/*     Local parameters */


/*     Local variables */


/*     Quantity definition parameter arrays: */


/*     Standard SPICE error handling. */

    /* Parameter adjustments */
    work_dim1 = *mw + 6;
    work_offset = work_dim1 - 5;

    /* Function Body */
    if (return_()) {
	return 0;
    }
    chkin_("GFDIST", (ftnlen)6);

/*     Check the workspace window dimensions. */

    if (*mw < 2) {
	setmsg_("Workspace window size was #; size must be at least 2.", (
		ftnlen)53);
	errint_("#", mw, (ftnlen)1);
	sigerr_("SPICE(INVALIDDIMENSION)", (ftnlen)23);
	chkout_("GFDIST", (ftnlen)6);
	return 0;
    }
    if (*nw < 5) {
	setmsg_("Workspace window count was #; count must be at least #.", (
		ftnlen)55);
	errint_("#", nw, (ftnlen)1);
	errint_("#", &c__5, (ftnlen)1);
	sigerr_("SPICE(INVALIDDIMENSION)", (ftnlen)23);
	chkout_("GFDIST", (ftnlen)6);
	return 0;
    }

/*     Check the result window size. */

    if (sized_(result) < 2) {
	setmsg_("Result window size was #; size must be at least 2.", (ftnlen)
		50);
	i__1 = sized_(result);
	errint_("#", &i__1, (ftnlen)1);
	sigerr_("SPICE(INVALIDDIMENSION)", (ftnlen)23);
	chkout_("GFDIST", (ftnlen)6);
	return 0;
    }

/*     Set up a call to GFEVNT, which will handle the search. */

    s_copy(qpnams, "TARGET", (ftnlen)80, (ftnlen)6);
    s_copy(qcpars, target, (ftnlen)80, target_len);
    s_copy(qpnams + 80, "OBSERVER", (ftnlen)80, (ftnlen)8);
    s_copy(qcpars + 80, obsrvr, (ftnlen)80, obsrvr_len);
    s_copy(qpnams + 160, "ABCORR", (ftnlen)80, (ftnlen)6);
    s_copy(qcpars + 160, abcorr, (ftnlen)80, abcorr_len);

/*     Check and set the step size. */

    gfsstp_(step);

/*     Retrieve the convergence tolerance, if set. */

    zzholdd_(&c_n1, &c__3, &ok, &tol);

/*     Use the default value CNVTOL if no stored tolerance value. */

    if (! ok) {
	tol = 1e-6;
    }

/*     Initialize the RESULT window. */

    scardd_(&c__0, result);

/*     Look for solutions. */

/*     Progress report and bail-out options are set to .FALSE. */

    gfevnt_((U_fp)gfstep_, (U_fp)gfrefn_, "DISTANCE", &c__3, qpnams, qcpars, 
	    qdpars, qipars, qlpars, relate, refval, &tol, adjust, cnfine, &
	    c_false, (U_fp)gfrepi_, (U_fp)gfrepu_, (U_fp)gfrepf_, mw, &c__5, 
	    work, &c_false, (L_fp)gfbail_, result, (ftnlen)8, (ftnlen)80, (
	    ftnlen)80, relate_len);
    chkout_("GFDIST", (ftnlen)6);
    return 0;
} /* gfdist_ */

