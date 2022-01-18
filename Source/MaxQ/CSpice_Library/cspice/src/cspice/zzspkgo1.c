/* zzspkgo1.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__6 = 6;
static integer c__0 = 0;

/* $Procedure ZZSPKGO1 ( S/P Kernel, geometric state ) */
/* Subroutine */ int zzspkgo1_(integer *targ, doublereal *et, char *ref, 
	integer *obs, doublereal *state, doublereal *lt, ftnlen ref_len)
{
    /* Initialized data */

    static logical first = TRUE_;

    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Builtin functions */
    integer s_cmp(char *, char *, ftnlen, ftnlen), s_rnge(char *, integer, 
	    char *, integer);

    /* Local variables */
    extern /* Subroutine */ int zzfrmch1_(integer *, integer *, doublereal *, 
	    doublereal *);
    integer cobs, legs;
    doublereal sobs[6];
    extern /* Subroutine */ int mxvg_(doublereal *, doublereal *, integer *, 
	    integer *, doublereal *), zznamfrm_(integer *, char *, integer *, 
	    char *, integer *, ftnlen, ftnlen), zzctruin_(integer *);
    integer i__;
    extern /* Subroutine */ int vaddg_(doublereal *, doublereal *, integer *, 
	    doublereal *), etcal_(doublereal *, char *, ftnlen);
    integer refid;
    extern /* Subroutine */ int chkin_(char *, ftnlen);
    char oname[40];
    doublereal descr[5];
    integer ctarg[20];
    char ident[40], tname[40];
    extern /* Subroutine */ int errch_(char *, char *, ftnlen, ftnlen), 
	    moved_(doublereal *, integer *, doublereal *);
    logical found;
    extern /* Subroutine */ int repmi_(char *, char *, integer *, char *, 
	    ftnlen, ftnlen, ftnlen);
    doublereal starg[120]	/* was [6][20] */;
    logical nofrm;
    static char svref[32];
    extern /* Subroutine */ int vsubg_(doublereal *, doublereal *, integer *, 
	    doublereal *);
    doublereal stemp[6];
    integer ctpos;
    doublereal vtemp[6];
    extern doublereal vnorm_(doublereal *);
    extern /* Subroutine */ int bodc2n_(integer *, char *, logical *, ftnlen);
    static integer svctr1[2];
    extern logical failed_(void);
    extern /* Subroutine */ int cleard_(integer *, doublereal *);
    integer handle, cframe;
    extern doublereal clight_(void);
    integer tframe[20];
    extern integer isrchi_(integer *, integer *, integer *);
    extern /* Subroutine */ int sigerr_(char *, ftnlen), chkout_(char *, 
	    ftnlen);
    static integer svrefi;
    extern /* Subroutine */ int irfnum_(char *, integer *, ftnlen), prefix_(
	    char *, integer *, char *, ftnlen, ftnlen), setmsg_(char *, 
	    ftnlen), suffix_(char *, integer *, char *, ftnlen, ftnlen);
    integer tmpfrm;
    extern /* Subroutine */ int irfrot_(integer *, integer *, doublereal *), 
	    spksfs_(integer *, doublereal *, integer *, doublereal *, char *, 
	    logical *, ftnlen);
    extern integer frstnp_(char *, ftnlen);
    extern logical return_(void);
    extern /* Subroutine */ int spkpvn_(integer *, doublereal *, doublereal *,
	     integer *, doublereal *, integer *);
    doublereal stxfrm[36]	/* was [6][6] */;
    extern /* Subroutine */ int intstr_(integer *, char *, ftnlen);
    integer nct;
    doublereal rot[9]	/* was [3][3] */;
    extern /* Subroutine */ int mxv_(doublereal *, doublereal *, doublereal *)
	    ;
    char tstring[80];

/* $ Abstract */

/*     SPICE Private routine intended solely for the support of SPICE */
/*     routines.  Users should not call this routine directly due */
/*     to the volatile nature of this routine. */

/*     Compute the geometric state (position and velocity) of a target */
/*     body relative to an observing body. */

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

/*     SPK */

/* $ Keywords */

/*     EPHEMERIS */

/* $ Declarations */
/* $ Abstract */

/*     This file contains the number of inertial reference */
/*     frames that are currently known by the SPICE toolkit */
/*     software. */

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

/*     FRAMES */

/* $ Declarations */
/* $ Brief_I/O */

/*     VARIABLE  I/O  DESCRIPTION */
/*     --------  ---  -------------------------------------------------- */
/*     NINERT     P   Number of known inertial reference frames. */

/* $ Parameters */

/*     NINERT     is the number of recognized inertial reference */
/*                frames.  This value is needed by both CHGIRF */
/*                ZZFDAT, and FRAMEX. */

/* $ Author_and_Institution */

/*     W.L. Taber      (JPL) */

/* $ Literature_References */

/*     None. */

/* $ Version */

/* -    SPICELIB Version 1.0.0, 10-OCT-1996 (WLT) */

/* -& */
/* $ Abstract */

/*     This include file defines the dimension of the counter */
/*     array used by various SPICE subsystems to uniquely identify */
/*     changes in their states. */

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

/* $ Parameters */

/*     CTRSIZ      is the dimension of the counter array used by */
/*                 various SPICE subsystems to uniquely identify */
/*                 changes in their states. */

/* $ Author_and_Institution */

/*     B.V. Semenov    (JPL) */

/* $ Literature_References */

/*     None. */

/* $ Version */

/* -    SPICELIB Version 1.0.0, 29-JUL-2013 (BVS) */

/* -& */

/*     End of include file. */

/* $ Brief_I/O */

/*     Variable  I/O  Description */
/*     --------  ---  -------------------------------------------------- */
/*     TARG       I   Target body. */
/*     ET         I   Target epoch. */
/*     REF        I   Target reference frame. */
/*     OBS        I   Observing body. */
/*     STATE      O   State of target. */
/*     LT         O   Light time. */

/* $ Detailed_Input */

/*     TARG        is the standard NAIF ID code for a target body. */

/*     ET          is the epoch (ephemeris time) at which the state */
/*                 of the target body is to be computed. */

/*     REF         is the name of the reference frame to */
/*                 which the vectors returned by the routine should */
/*                 be rotated. This may be any frame supported by */
/*                 the SPICELIB subroutine ZZFRMCH1. */

/*     OBS         is the standard NAIF ID code for an observing body. */

/* $ Detailed_Output */

/*     STATE       contains the geometric position and velocity of the */
/*                 target body, relative to the observing body, at epoch */
/*                 ET. STATE has six elements: the first three contain */
/*                 the target's position; the last three contain the */
/*                 target's velocity. These vectors are transformed into */
/*                 the specified reference frame. Units are always km */
/*                 and km/sec. */

/*     LT          is the one-way light time in seconds from the */
/*                 observing body to the geometric position of the */
/*                 target body at the specified epoch. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     1) If insufficient ephemeris data has been loaded to compute */
/*        the necessary states, the error SPICE(SPKINSUFFDATA) is */
/*        signaled. */

/* $ Files */

/*     See: $Restrictions. */

/* $ Particulars */

/*     ZZSPKGO1 computes the geometric state, T(t), of the target */
/*     body and the geometric state, O(t), of the observing body */
/*     relative to the first common center of motion.  Subtracting */
/*     O(t) from T(t) gives the geometric state of the target */
/*     body relative to the observer. */


/*        CENTER ----- O(t) */
/*            |      / */
/*            |     / */
/*            |    / */
/*            |   /  T(t) - O(t) */
/*            |  / */
/*           T(t) */


/*     The one-way light time, tau, is given by */


/*               | T(t) - O(t) | */
/*        tau = ----------------- */
/*                      c */


/*     For example, if the observing body is -94, the Mars Observer */
/*     spacecraft, and the target body is 401, Phobos, then the */
/*     first common center is probably 4, the Mars Barycenter. */
/*     O(t) is the state of -94 relative to 4 and T(t) is the */
/*     state of 401 relative to 4. */

/*     The center could also be the Solar System Barycenter, body 0. */
/*     For example, if the observer is 399, Earth, and the target */
/*     is 299, Venus, then O(t) would be the state of 399 relative */
/*     to 0 and T(t) would be the state of 299 relative to 0. */

/*     Ephemeris data from more than one segment may be required */
/*     to determine the states of the target body and observer */
/*     relative to a common center.  ZZSPKGO1 reads as many segments */
/*     as necessary, from as many files as necessary, using files */
/*     that have been loaded by previous calls to SPKLEF (load */
/*     ephemeris file). */

/*     ZZSPKGO1 is similar to SPKEZ but returns geometric states */
/*     only, with no option to make planetary (light-time) nor */
/*     stellar aberration corrections.  The geometric states */
/*     returned by SPKEZ and ZZSPKGO1 are the same. */

/* $ Examples */

/*     The following code example computes the geometric */
/*     state of the moon with respect to the earth and */
/*     then prints the distance of the moon from the */
/*     the earth at a number of epochs. */

/*     Assume the SPK file SAMPLE.BSP contains ephemeris data */
/*     for the moon relative to earth over the time interval */
/*     from BEGIN to END. */

/*            INTEGER               EARTH */
/*            PARAMETER           ( EARTH = 399 ) */

/*            INTEGER               MOON */
/*            PARAMETER           ( MOON  = 301 ) */

/*            INTEGER               N */
/*            PARAMETER           ( N     = 100 ) */

/*            INTEGER               I */
/*            CHARACTER*(20)        UTC */
/*            DOUBLE PRECISION      BEGIN */
/*            DOUBLE PRECISION      DELTA */
/*            DOUBLE PRECISION      END */
/*            DOUBLE PRECISION      ET */
/*            DOUBLE PRECISION      LT */
/*            DOUBLE PRECISION      STATE ( 6 ) */

/*            DOUBLE PRECISION      VNORM */

/*     C */
/*     C      Load the binary SPK ephemeris file. */
/*     C */
/*            CALL FURNSH ( 'SAMPLE.BSP' ) */

/*            . */
/*            . */
/*            . */

/*     C */
/*     C      Divide the interval of coverage [BEGIN,END] into */
/*     C      N steps.  At each step, compute the state, and */
/*     C      print out the epoch in UTC time and position norm. */
/*     C */
/*            DELTA = ( END - BEGIN ) / N */

/*            DO I = 0, N */

/*               ET = BEGIN + I*DELTA */

/*               CALL ZZSPKGO1 ( MOON, ET, 'J2000', EARTH, STATE, LT ) */

/*               CALL ET2UTC ( ET, 'C', 0, UTC ) */

/*               WRITE (*,*) UTC, VNORM ( STATE ) */

/*            END DO */

/* $ Restrictions */

/*     1) SPICE Private routine. */

/*     2) The ephemeris files to be used by ZZSPKGO1 must be loaded */
/*        by SPKLEF before ZZSPKGO1 is called. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman  (JPL) */
/*     J.E. McLean   (JPL) */
/*     B.V. Semenov  (JPL) */
/*     W.L. Taber    (JPL) */
/*     W.D. Wright   (JPL) */

/* $ Version */

/* -    SPICELIB Version 2.0.0, 08-JAN-2014 (BVS) */

/*        Updated to save the input frame name and POOL state counter */
/*        and to do frame name-ID conversion only if the counter has */
/*        changed. */

/*        Updated to map the input frame name to its ID by first calling */
/*        ZZNAMFRM, and then calling IRFNUM. The side effect of this */
/*        change is that now the frame with the fixed name 'DEFAULT' */
/*        that can be associated with any code via CHGIRF's entry point */
/*        IRFDEF will be fully masked by a frame with indentical name */
/*        defined via a text kernel. Previously the CHGIRF's 'DEFAULT' */
/*        frame masked the text kernel frame with the same name. */

/*        Fixed description of STATE in Detailed Output. Replaced */
/*        SPKLEF with FURNSH and fixed errors in Examples. */

/* -    SPICELIB Version 1.1.0, 06-SEP-2005 (NJB) */

/*        Updated to remove non-standard use of duplicate arguments */
/*        in VADDG calls. */

/* -    SPICELIB Version 1.0.0, 05-JAN-2005 (NJB) */

/*        Based on SPICELIB Version 2.3.0, 05-JAN-2005 (NJB) */

/* -& */
/* $ Index_Entries */

/*     geometric state of one body relative to another */

/* -& */
/* $ Revisions */

/* -    SPICELIB Version 1.1.0, 06-SEP-2005 (NJB) */

/*        Updated to remove non-standard use of duplicate arguments */
/*        in VADDG calls. */

/* -& */

/*     This is the idea: */

/*     Every body moves with respect to some center. The center */
/*     is itself a body, which in turn moves about some other */
/*     center.  If we begin at the target body (T), follow */
/*     the chain, */

/*                                   T */
/*                                     \ */
/*           SSB                        \ */
/*               \                     C[1] */
/*                \                     / */
/*                 \                   / */
/*                  \                 / */
/*                   \               / */
/*                  C[3]-----------C[2] */

/*     and avoid circular definitions (A moves about B, and B moves */
/*     about A), eventually we get the state relative to the solar */
/*     system barycenter (which, for our purposes, doesn't move). */
/*     Thus, */

/*        T    = T     + C[1]     + C[2]     + ... + C[n] */
/*         SSB    C[1]       C[2]       [C3]             SSB */

/*     where */

/*        X */
/*         Y */

/*     is the state of body X relative to body Y. */

/*     However, we don't want to follow each chain back to the SSB */
/*     if it isn't necessary.  Instead we will just follow the chain */
/*     of the target body and follow the chain of the observing body */
/*     until we find a common node in the tree. */

/*     In the example below, C is the first common node.  We compute */
/*     the state of TARG relative to C and the state of OBS relative */
/*     to C, then subtract the two states. */

/*                                   TARG */
/*                                     \ */
/*           SSB                        \ */
/*               \                       A */
/*                \                     /            OBS */
/*                 \                   /              | */
/*                  \                 /               | */
/*                   \               /                | */
/*                    B-------------C-----------------D */




/*     SPICELIB functions */


/*     Local parameters */


/*     CHLEN is the maximum length of a chain.  That is, */
/*     it is the maximum number of bodies in the chain from */
/*     the target or observer to the SSB. */


/*     Saved frame name length. */


/*     Local variables */


/*     Saved frame name/ID item declarations. */


/*     Saved frame name/ID items. */


/*     Initial values. */


/*     In-line Function Definitions */


/*     Standard SPICE error handling. */

    if (return_()) {
	return 0;
    } else {
	chkin_("ZZSPKGO1", (ftnlen)8);
    }

/*     Initialization. */

    if (first) {

/*        Initialize counter. */

	zzctruin_(svctr1);
	first = FALSE_;
    }

/*     We take care of the obvious case first.  It TARG and OBS are the */
/*     same we can just fill in zero. */

    if (*targ == *obs) {
	*lt = 0.;
	cleard_(&c__6, state);
	chkout_("ZZSPKGO1", (ftnlen)8);
	return 0;
    }

/*     CTARG contains the integer codes of the bodies in the */
/*     target body chain, beginning with TARG itself and then */
/*     the successive centers of motion. */

/*     STARG(1,I) is the state of the target body relative */
/*     to CTARG(I).  The id-code of the frame of this state is */
/*     stored in TFRAME(I). */

/*     COBS and SOBS will contain the centers and states of the */
/*     observing body.  (They are single elements instead of arrays */
/*     because we only need the current center and state of the */
/*     observer relative to it.) */

/*     First, we construct CTARG and STARG.  CTARG(1) is */
/*     just the target itself, and STARG(1,1) is just a zero */
/*     vector, that is, the state of the target relative */
/*     to itself. */

/*     Then we follow the chain, filling up CTARG and STARG */
/*     as we go.  We use SPKSFS to search through loaded */
/*     files to find the first segment applicable to CTARG(1) */
/*     and time ET.  Then we use SPKPVN to compute the state */
/*     of the body CTARG(1) at ET in the segment that was found */
/*     and get its center and frame of motion (CTARG(2) and TFRAME(2). */

/*     We repeat the process for CTARG(2) and so on, until */
/*     there is no data found for some CTARG(I) or until we */
/*     reach the SSB. */

/*     Next, we find centers and states in a similar manner */
/*     for the observer.  It's a similar construction as */
/*     described above, but I is always 1.  COBS and SOBS */
/*     are overwritten with each new center and state, */
/*     beginning at OBS.  However, we stop when we encounter */
/*     a common center of motion, that is when COBS is equal */
/*     to CTARG(I) for some I. */

/*     Finally, we compute the desired state of the target */
/*     relative to the observer by subtracting the state of */
/*     the observing body relative to the common node from */
/*     the state of the target body relative to the common */
/*     node. */

/*     CTPOS is the position in CTARG of the common node. */

/*     Since the upgrade to use hashes and counter bypass ZZNAMFRM */
/*     became more efficient in looking up frame IDs than IRFNUM. So the */
/*     original order of calls "IRFNUM first, NAMFRM second" was */
/*     switched to "ZZNAMFRM first, IRFNUM second". */

/*     The call to IRFNUM, now redundant for built-in inertial frames, */
/*     was preserved to for a sole reason -- to still support the */
/*     ancient and barely documented ability for the users to associate */
/*     a frame with the fixed name 'DEFAULT' with any CHGIRF inertial */
/*     frame code via CHGIRF's entry point IRFDEF. */

/*     Note that in the case of ZZNAMFRM's failure to resolve name and */
/*     IRFNUM's success to do so, the code returned by IRFNUM for */
/*     'DEFAULT' frame is *not* copied to the saved code SVREFI (which */
/*     would be set to 0 by ZZNAMFRM) to make sure that on subsequent */
/*     calls ZZNAMFRM does not do a bypass (as SVREFI always forced look */
/*     up) and calls IRFNUM again to reset the 'DEFAULT's frame ID */
/*     should it change between the calls. */

    zznamfrm_(svctr1, svref, &svrefi, ref, &refid, (ftnlen)32, ref_len);
    if (refid == 0) {
	irfnum_(ref, &refid, ref_len);
    }
    if (refid == 0) {
	if (frstnp_(ref, ref_len) > 0) {
	    setmsg_("The string supplied to specify the reference frame, ('#"
		    "') contains non-printing characters.  The two most commo"
		    "n causes for this kind of error are: 1. an error in the "
		    "call to ZZSPKGO1; 2. an uninitialized variable. ", (
		    ftnlen)215);
	    errch_("#", ref, (ftnlen)1, ref_len);
	} else if (s_cmp(ref, " ", ref_len, (ftnlen)1) == 0) {
	    setmsg_("The string supplied to specify the reference frame is b"
		    "lank.  The most common cause for this kind of error is a"
		    "n uninitialized variable. ", (ftnlen)137);
	} else {
	    setmsg_("The string supplied to specify the reference frame was "
		    "'#'.  This frame is not recognized. Possible causes for "
		    "this error are: 1. failure to load the frame definition "
		    "into the kernel pool; 2. An out-of-date edition of the t"
		    "oolkit. ", (ftnlen)231);
	    errch_("#", ref, (ftnlen)1, ref_len);
	}
	sigerr_("SPICE(UNKNOWNFRAME)", (ftnlen)19);
	if (failed_()) {
	    chkout_("ZZSPKGO1", (ftnlen)8);
	    return 0;
	}
    }

/*     Fill in CTARG and STARG until no more data is found */
/*     or until we reach the SSB.  If the chain gets too */
/*     long to fit in CTARG, that is if I equals CHLEN, */
/*     then overwrite the last elements of CTARG and STARG. */

/*     Note the check for FAILED in the loop.  If SPKSFS */
/*     or SPKPVN happens to fail during execution, and the */
/*     current error handling action is to NOT abort, then */
/*     FOUND may be stuck at TRUE, CTARG(I) will never */
/*     become zero, and the loop will execute indefinitely. */


/*     Construct CTARG and STARG.  Begin by assigning the */
/*     first elements:  TARG and the state of TARG relative */
/*     to itself. */

    i__ = 1;
    ctarg[(i__1 = i__ - 1) < 20 && 0 <= i__1 ? i__1 : s_rnge("ctarg", i__1, 
	    "zzspkgo1_", (ftnlen)615)] = *targ;
    found = TRUE_;
    cleard_(&c__6, &starg[(i__1 = i__ * 6 - 6) < 120 && 0 <= i__1 ? i__1 : 
	    s_rnge("starg", i__1, "zzspkgo1_", (ftnlen)618)]);
    while(found && i__ < 20 && ctarg[(i__1 = i__ - 1) < 20 && 0 <= i__1 ? 
	    i__1 : s_rnge("ctarg", i__1, "zzspkgo1_", (ftnlen)620)] != *obs &&
	     ctarg[(i__2 = i__ - 1) < 20 && 0 <= i__2 ? i__2 : s_rnge("ctarg",
	     i__2, "zzspkgo1_", (ftnlen)620)] != 0) {

/*        Find a file and segment that has state */
/*        data for CTARG(I). */

	spksfs_(&ctarg[(i__1 = i__ - 1) < 20 && 0 <= i__1 ? i__1 : s_rnge(
		"ctarg", i__1, "zzspkgo1_", (ftnlen)629)], et, &handle, descr,
		 ident, &found, (ftnlen)40);
	if (found) {

/*           Get the state of CTARG(I) relative to some */
/*           center of motion.  This new center goes in */
/*           CTARG(I+1) and the state is called STEMP. */

	    ++i__;
	    spkpvn_(&handle, descr, et, &tframe[(i__1 = i__ - 1) < 20 && 0 <= 
		    i__1 ? i__1 : s_rnge("tframe", i__1, "zzspkgo1_", (ftnlen)
		    639)], &starg[(i__2 = i__ * 6 - 6) < 120 && 0 <= i__2 ? 
		    i__2 : s_rnge("starg", i__2, "zzspkgo1_", (ftnlen)639)], &
		    ctarg[(i__3 = i__ - 1) < 20 && 0 <= i__3 ? i__3 : s_rnge(
		    "ctarg", i__3, "zzspkgo1_", (ftnlen)639)]);

/*           Here's what we have.  STARG is the state of CTARG(I-1) */
/*           relative to CTARG(I) in reference frame TFRAME(I) */

/*           If one of the routines above failed during */
/*           execution, we just give up and check out. */

	    if (failed_()) {
		chkout_("ZZSPKGO1", (ftnlen)8);
		return 0;
	    }
	}
    }
    tframe[0] = tframe[1];

/*     If the loop above ended because we ran out of */
/*     room in the arrays CTARG and STARG, then we */
/*     continue finding states but we overwrite the */
/*     last elements of CTARG and STARG. */

/*     If, as a result, the first common node is */
/*     overwritten, we'll just have to settle for */
/*     the last common node.  This will cause a small */
/*     loss of precision, but it's better than other */
/*     alternatives. */

    if (i__ == 20) {
	while(found && ctarg[19] != 0 && ctarg[19] != *obs) {

/*           Find a file and segment that has state */
/*           data for CTARG(CHLEN). */

	    spksfs_(&ctarg[19], et, &handle, descr, ident, &found, (ftnlen)40)
		    ;
	    if (found) {

/*              Get the state of CTARG(CHLEN) relative to */
/*              some center of motion.  The new center */
/*              overwrites the old.  The state is called */
/*              STEMP. */

		spkpvn_(&handle, descr, et, &tmpfrm, stemp, &ctarg[19]);

/*              Add STEMP to the state of TARG relative to */
/*              the old center to get the state of TARG */
/*              relative to the new center.  Overwrite */
/*              the last element of STARG. */

		if (tframe[19] == tmpfrm) {
		    moved_(&starg[114], &c__6, vtemp);
		} else if (tmpfrm > 0 && tmpfrm <= 21 && tframe[19] > 0 && 
			tframe[19] <= 21) {
		    irfrot_(&tframe[19], &tmpfrm, rot);
		    mxv_(rot, &starg[114], vtemp);
		    mxv_(rot, &starg[117], &vtemp[3]);
		} else {
		    zzfrmch1_(&tframe[19], &tmpfrm, et, stxfrm);
		    if (failed_()) {
			chkout_("ZZSPKGO1", (ftnlen)8);
			return 0;
		    }
		    mxvg_(stxfrm, &starg[114], &c__6, &c__6, vtemp);
		}
		vaddg_(vtemp, stemp, &c__6, &starg[114]);
		tframe[19] = tmpfrm;

/*              If one of the routines above failed during */
/*              execution, we just give up and check out. */

		if (failed_()) {
		    chkout_("ZZSPKGO1", (ftnlen)8);
		    return 0;
		}
	    }
	}
    }
    nct = i__;

/*     NCT is the number of elements in CTARG, */
/*     the chain length.  We have in hand the following information */

/*        STARG(1...6,K)  state of body */
/*        CTARG(K-1)      relative to body CTARG(K) in the frame */
/*        TFRAME(K) */


/*     For K = 2,..., NCT. */

/*     CTARG(1) = TARG */
/*     STARG(1...6,1) = ( 0, 0, 0, 0, 0, 0 ) */
/*     TFRAME(1)      = TFRAME(2) */


/*     Now follow the observer's chain.  Assign */
/*     the first values for COBS and SOBS. */

    cobs = *obs;
    cleard_(&c__6, sobs);

/*     Perhaps we have a common node already. */
/*     If so it will be the last node on the */
/*     list CTARG. */

/*     We let CTPOS will be the position of the common */
/*     node in CTARG if one is found.  It will */
/*     be zero if COBS is not found in CTARG. */

    if (ctarg[(i__1 = nct - 1) < 20 && 0 <= i__1 ? i__1 : s_rnge("ctarg", 
	    i__1, "zzspkgo1_", (ftnlen)775)] == cobs) {
	ctpos = nct;
	cframe = tframe[(i__1 = ctpos - 1) < 20 && 0 <= i__1 ? i__1 : s_rnge(
		"tframe", i__1, "zzspkgo1_", (ftnlen)777)];
    } else {
	ctpos = 0;
    }

/*     Repeat the same loop as above, but each time */
/*     we encounter a new center of motion, check to */
/*     see if it is a common node.  (When CTPOS is */
/*     not zero, CTARG(CTPOS) is the first common node.) */

/*     Note that we don't need a centers array nor a */
/*     states array, just a single center and state */
/*     is sufficient --- we just keep overwriting them. */
/*     When the common node is found, we have everything */
/*     we need in that one center (COBS) and state */
/*     (SOBS-state of the target relative to COBS). */

    found = TRUE_;
    nofrm = TRUE_;
    legs = 0;
    while(found && cobs != 0 && ctpos == 0) {

/*        Find a file and segment that has state */
/*        data for COBS. */

	spksfs_(&cobs, et, &handle, descr, ident, &found, (ftnlen)40);
	if (found) {

/*           Get the state of COBS; call it STEMP. */
/*           The center of motion of COBS becomes the */
/*           new COBS. */

	    if (legs == 0) {
		spkpvn_(&handle, descr, et, &tmpfrm, sobs, &cobs);
	    } else {
		spkpvn_(&handle, descr, et, &tmpfrm, stemp, &cobs);
	    }
	    if (nofrm) {
		nofrm = FALSE_;
		cframe = tmpfrm;
	    }

/*           Add STEMP to the state of OBS relative to */
/*           the old COBS to get the state of OBS */
/*           relative to the new COBS. */

	    if (cframe == tmpfrm) {

/*              On the first leg of the state of the observer, we */
/*              don't have to add anything, the state of the observer */
/*              is already in SOBS.  We only have to add when the */
/*              number of legs in the observer state is one or greater. */

		if (legs > 0) {
		    vaddg_(sobs, stemp, &c__6, vtemp);
		    moved_(vtemp, &c__6, sobs);
		}
	    } else if (tmpfrm > 0 && tmpfrm <= 21 && cframe > 0 && cframe <= 
		    21) {
		irfrot_(&cframe, &tmpfrm, rot);
		mxv_(rot, sobs, vtemp);
		mxv_(rot, &sobs[3], &vtemp[3]);
		vaddg_(vtemp, stemp, &c__6, sobs);
		cframe = tmpfrm;
	    } else {
		zzfrmch1_(&cframe, &tmpfrm, et, stxfrm);
		if (failed_()) {
		    chkout_("ZZSPKGO1", (ftnlen)8);
		    return 0;
		}
		mxvg_(stxfrm, sobs, &c__6, &c__6, vtemp);
		vaddg_(vtemp, stemp, &c__6, sobs);
		cframe = tmpfrm;
	    }

/*           Check failed.  We don't want to loop */
/*           indefinitely. */

	    if (failed_()) {
		chkout_("ZZSPKGO1", (ftnlen)8);
		return 0;
	    }

/*           We now have one more leg of the path for OBS.  Set */
/*           LEGS to reflect this.  Then see if the new center */
/*           is a common node. If not, repeat the loop. */

	    ++legs;
	    ctpos = isrchi_(&cobs, &nct, ctarg);
	}
    }

/*     If CTPOS is zero at this point, it means we */
/*     have not found a common node though we have */
/*     searched through all the available data. */

    if (ctpos == 0) {
	bodc2n_(targ, tname, &found, (ftnlen)40);
	if (found) {
	    prefix_("# (", &c__0, tname, (ftnlen)3, (ftnlen)40);
	    suffix_(")", &c__0, tname, (ftnlen)1, (ftnlen)40);
	    repmi_(tname, "#", targ, tname, (ftnlen)40, (ftnlen)1, (ftnlen)40)
		    ;
	} else {
	    intstr_(targ, tname, (ftnlen)40);
	}
	bodc2n_(obs, oname, &found, (ftnlen)40);
	if (found) {
	    prefix_("# (", &c__0, oname, (ftnlen)3, (ftnlen)40);
	    suffix_(")", &c__0, oname, (ftnlen)1, (ftnlen)40);
	    repmi_(oname, "#", obs, oname, (ftnlen)40, (ftnlen)1, (ftnlen)40);
	} else {
	    intstr_(obs, oname, (ftnlen)40);
	}
	setmsg_("Insufficient ephemeris data has been loaded to compute the "
		"state of TARG relative to OBS at the ephemeris epoch #. ", (
		ftnlen)115);
	etcal_(et, tstring, (ftnlen)80);
	errch_("TARG", tname, (ftnlen)4, (ftnlen)40);
	errch_("OBS", oname, (ftnlen)3, (ftnlen)40);
	errch_("#", tstring, (ftnlen)1, (ftnlen)80);
	sigerr_("SPICE(SPKINSUFFDATA)", (ftnlen)20);
	chkout_("ZZSPKGO1", (ftnlen)8);
	return 0;
    }

/*     If CTPOS is not zero, then we have reached a */
/*     common node, specifically, */

/*        CTARG(CTPOS) = COBS = CENTER */

/*     (in diagram below).  The STATE of the target */
/*     (TARG) relative to the observer (OBS) is just */

/*        STARG(1,CTPOS) - SOBS. */



/*                     SOBS */
/*         CENTER ---------------->OBS */
/*            |                  . */
/*            |                . */
/*         S  |              .   E */
/*         T  |            .   T */
/*         A  |          .   A */
/*         R  |        .   T */
/*         G  |      .   S */
/*            |    . */
/*            |  . */
/*            V L */
/*           TARG */


/*     And the light-time between them is just */

/*               | STATE | */
/*          LT = --------- */
/*                   c */


/*     Compute the state of the target relative to CTARG(CTPOS) */

    if (ctpos == 1) {
	tframe[0] = cframe;
    }
    i__1 = ctpos - 1;
    for (i__ = 2; i__ <= i__1; ++i__) {
	if (tframe[(i__2 = i__ - 1) < 20 && 0 <= i__2 ? i__2 : s_rnge("tframe"
		, i__2, "zzspkgo1_", (ftnlen)973)] == tframe[(i__3 = i__) < 
		20 && 0 <= i__3 ? i__3 : s_rnge("tframe", i__3, "zzspkgo1_", (
		ftnlen)973)]) {
	    vaddg_(&starg[(i__2 = i__ * 6 - 6) < 120 && 0 <= i__2 ? i__2 : 
		    s_rnge("starg", i__2, "zzspkgo1_", (ftnlen)975)], &starg[(
		    i__3 = (i__ + 1) * 6 - 6) < 120 && 0 <= i__3 ? i__3 : 
		    s_rnge("starg", i__3, "zzspkgo1_", (ftnlen)975)], &c__6, 
		    vtemp);
	    moved_(vtemp, &c__6, &starg[(i__2 = (i__ + 1) * 6 - 6) < 120 && 0 
		    <= i__2 ? i__2 : s_rnge("starg", i__2, "zzspkgo1_", (
		    ftnlen)976)]);
	} else if (tframe[(i__3 = i__) < 20 && 0 <= i__3 ? i__3 : s_rnge(
		"tframe", i__3, "zzspkgo1_", (ftnlen)978)] > 0 && tframe[(
		i__3 = i__) < 20 && 0 <= i__3 ? i__3 : s_rnge("tframe", i__3, 
		"zzspkgo1_", (ftnlen)978)] <= 21 && tframe[(i__2 = i__ - 1) < 
		20 && 0 <= i__2 ? i__2 : s_rnge("tframe", i__2, "zzspkgo1_", (
		ftnlen)978)] > 0 && tframe[(i__2 = i__ - 1) < 20 && 0 <= i__2 
		? i__2 : s_rnge("tframe", i__2, "zzspkgo1_", (ftnlen)978)] <= 
		21) {
	    irfrot_(&tframe[(i__2 = i__ - 1) < 20 && 0 <= i__2 ? i__2 : 
		    s_rnge("tframe", i__2, "zzspkgo1_", (ftnlen)980)], &
		    tframe[(i__3 = i__) < 20 && 0 <= i__3 ? i__3 : s_rnge(
		    "tframe", i__3, "zzspkgo1_", (ftnlen)980)], rot);
	    mxv_(rot, &starg[(i__2 = i__ * 6 - 6) < 120 && 0 <= i__2 ? i__2 : 
		    s_rnge("starg", i__2, "zzspkgo1_", (ftnlen)981)], stemp);
	    mxv_(rot, &starg[(i__2 = i__ * 6 - 3) < 120 && 0 <= i__2 ? i__2 : 
		    s_rnge("starg", i__2, "zzspkgo1_", (ftnlen)982)], &stemp[
		    3]);
	    vaddg_(stemp, &starg[(i__2 = (i__ + 1) * 6 - 6) < 120 && 0 <= 
		    i__2 ? i__2 : s_rnge("starg", i__2, "zzspkgo1_", (ftnlen)
		    983)], &c__6, vtemp);
	    moved_(vtemp, &c__6, &starg[(i__2 = (i__ + 1) * 6 - 6) < 120 && 0 
		    <= i__2 ? i__2 : s_rnge("starg", i__2, "zzspkgo1_", (
		    ftnlen)984)]);
	} else {
	    zzfrmch1_(&tframe[(i__2 = i__ - 1) < 20 && 0 <= i__2 ? i__2 : 
		    s_rnge("tframe", i__2, "zzspkgo1_", (ftnlen)988)], &
		    tframe[(i__3 = i__) < 20 && 0 <= i__3 ? i__3 : s_rnge(
		    "tframe", i__3, "zzspkgo1_", (ftnlen)988)], et, stxfrm);
	    if (failed_()) {
		chkout_("ZZSPKGO1", (ftnlen)8);
		return 0;
	    }
	    mxvg_(stxfrm, &starg[(i__2 = i__ * 6 - 6) < 120 && 0 <= i__2 ? 
		    i__2 : s_rnge("starg", i__2, "zzspkgo1_", (ftnlen)995)], &
		    c__6, &c__6, stemp);
	    vaddg_(stemp, &starg[(i__2 = (i__ + 1) * 6 - 6) < 120 && 0 <= 
		    i__2 ? i__2 : s_rnge("starg", i__2, "zzspkgo1_", (ftnlen)
		    996)], &c__6, vtemp);
	    moved_(vtemp, &c__6, &starg[(i__2 = (i__ + 1) * 6 - 6) < 120 && 0 
		    <= i__2 ? i__2 : s_rnge("starg", i__2, "zzspkgo1_", (
		    ftnlen)997)]);
	}
    }

/*     To avoid unnecessary frame transformations we'll do */
/*     a bit of extra decision making here.  It's a lot */
/*     faster to make logical checks than it is to compute */
/*     frame transformations. */

    if (tframe[(i__1 = ctpos - 1) < 20 && 0 <= i__1 ? i__1 : s_rnge("tframe", 
	    i__1, "zzspkgo1_", (ftnlen)1010)] == cframe) {
	vsubg_(&starg[(i__1 = ctpos * 6 - 6) < 120 && 0 <= i__1 ? i__1 : 
		s_rnge("starg", i__1, "zzspkgo1_", (ftnlen)1012)], sobs, &
		c__6, state);
    } else if (tframe[(i__1 = ctpos - 1) < 20 && 0 <= i__1 ? i__1 : s_rnge(
	    "tframe", i__1, "zzspkgo1_", (ftnlen)1014)] == refid) {

/*        If the last frame associated with the target is already */
/*        in the requested output frame, we convert the state of */
/*        the observer to that frame and then subtract the state */
/*        of the observer from the state of the target. */

	if (refid > 0 && refid <= 21 && cframe > 0 && cframe <= 21) {
	    irfrot_(&cframe, &refid, rot);
	    mxv_(rot, sobs, stemp);
	    mxv_(rot, &sobs[3], &stemp[3]);
	} else {
	    zzfrmch1_(&cframe, &refid, et, stxfrm);
	    if (failed_()) {
		chkout_("ZZSPKGO1", (ftnlen)8);
		return 0;
	    }
	    mxvg_(stxfrm, sobs, &c__6, &c__6, stemp);
	}

/*        We've now transformed SOBS into the requested reference frame. */
/*        Set CFRAME to reflect this. */

	cframe = refid;
	vsubg_(&starg[(i__1 = ctpos * 6 - 6) < 120 && 0 <= i__1 ? i__1 : 
		s_rnge("starg", i__1, "zzspkgo1_", (ftnlen)1046)], stemp, &
		c__6, state);
    } else if (cframe > 0 && cframe <= 21 && tframe[(i__1 = ctpos - 1) < 20 &&
	     0 <= i__1 ? i__1 : s_rnge("tframe", i__1, "zzspkgo1_", (ftnlen)
	    1049)] > 0 && tframe[(i__1 = ctpos - 1) < 20 && 0 <= i__1 ? i__1 :
	     s_rnge("tframe", i__1, "zzspkgo1_", (ftnlen)1049)] <= 21) {

/*        If both frames are inertial we use IRFROT instead of */
/*        ZZFRMCH1 to get things into a common frame. */

	irfrot_(&tframe[(i__1 = ctpos - 1) < 20 && 0 <= i__1 ? i__1 : s_rnge(
		"tframe", i__1, "zzspkgo1_", (ftnlen)1055)], &cframe, rot);
	mxv_(rot, &starg[(i__1 = ctpos * 6 - 6) < 120 && 0 <= i__1 ? i__1 : 
		s_rnge("starg", i__1, "zzspkgo1_", (ftnlen)1056)], stemp);
	mxv_(rot, &starg[(i__1 = ctpos * 6 - 3) < 120 && 0 <= i__1 ? i__1 : 
		s_rnge("starg", i__1, "zzspkgo1_", (ftnlen)1057)], &stemp[3]);
	vsubg_(stemp, sobs, &c__6, state);
    } else {

/*        Use the more general routine ZZFRMCH1 to make the */
/*        transformation. */

	zzfrmch1_(&tframe[(i__1 = ctpos - 1) < 20 && 0 <= i__1 ? i__1 : 
		s_rnge("tframe", i__1, "zzspkgo1_", (ftnlen)1065)], &cframe, 
		et, stxfrm);
	if (failed_()) {
	    chkout_("ZZSPKGO1", (ftnlen)8);
	    return 0;
	}
	mxvg_(stxfrm, &starg[(i__1 = ctpos * 6 - 6) < 120 && 0 <= i__1 ? i__1 
		: s_rnge("starg", i__1, "zzspkgo1_", (ftnlen)1072)], &c__6, &
		c__6, stemp);
	vsubg_(stemp, sobs, &c__6, state);
    }

/*     Finally, rotate as needed into the requested frame. */

    if (cframe == refid) {

/*        We don't have to do anything in this case. */

    } else if (refid > 0 && refid <= 21 && cframe > 0 && cframe <= 21) {

/*        Since both frames are inertial, we use the more direct */
/*        routine IRFROT to get the transformation to REFID. */

	irfrot_(&cframe, &refid, rot);
	mxv_(rot, state, stemp);
	mxv_(rot, &state[3], &stemp[3]);
	moved_(stemp, &c__6, state);
    } else {
	zzfrmch1_(&cframe, &refid, et, stxfrm);
	if (failed_()) {
	    chkout_("ZZSPKGO1", (ftnlen)8);
	    return 0;
	}
	mxvg_(stxfrm, state, &c__6, &c__6, stemp);
	moved_(stemp, &c__6, state);
    }
    *lt = vnorm_(state) / clight_();
    chkout_("ZZSPKGO1", (ftnlen)8);
    return 0;
} /* zzspkgo1_ */

