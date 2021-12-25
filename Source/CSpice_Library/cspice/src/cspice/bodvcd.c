/* bodvcd.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__0 = 0;
static integer c__1 = 1;

/* $Procedure      BODVCD ( Return d.p. values from the kernel pool ) */
/* Subroutine */ int bodvcd_(integer *bodyid, char *item, integer *maxn, 
	integer *dim, doublereal *values, ftnlen item_len)
{
    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    char code[16], type__[1];
    extern /* Subroutine */ int chkin_(char *, ftnlen), errch_(char *, char *,
	     ftnlen, ftnlen);
    logical found;
    char varnam[32];
    extern /* Subroutine */ int gdpool_(char *, integer *, integer *, integer 
	    *, doublereal *, logical *, ftnlen), sigerr_(char *, ftnlen), 
	    chkout_(char *, ftnlen), dtpool_(char *, logical *, integer *, 
	    char *, ftnlen, ftnlen), setmsg_(char *, ftnlen), errint_(char *, 
	    integer *, ftnlen), suffix_(char *, integer *, char *, ftnlen, 
	    ftnlen);
    extern logical return_(void);
    extern /* Subroutine */ int intstr_(integer *, char *, ftnlen);

/* $ Abstract */

/*     Fetch from the kernel pool the double precision values */
/*     of an item associated with a body, where the body is */
/*     specified by an integer ID code. */

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

/*     KERNEL */
/*     NAIF_IDS */

/* $ Keywords */

/*     CONSTANTS */

/* $ Declarations */
/* $ Brief_I/O */

/*     VARIABLE  I/O  DESCRIPTION */
/*     --------  ---  -------------------------------------------------- */
/*     BODYID     I   Body ID code. */
/*     ITEM       I   Item for which values are desired. ('RADII', */
/*                    'NUT_PREC_ANGLES', etc. ) */
/*     MAXN       I   Maximum number of values that may be returned. */
/*     DIM        O   Number of values returned. */
/*     VALUES     O   Values. */

/* $ Detailed_Input */

/*     BODYID     is the NAIF integer ID code for a body of interest. */
/*                For example, if the body is the earth, the code is */
/*                399. */

/*     ITEM       is the item to be returned. Together, the NAIF ID */
/*                code of the body and the item name combine to form a */
/*                kernel variable name, e.g., */

/*                      'BODY599_RADII' */
/*                      'BODY401_POLE_RA' */

/*                The values associated with the kernel variable having */
/*                the name constructed as shown are sought.  Below */
/*                we'll take the shortcut of calling this kernel variable */
/*                the "requested kernel variable." */

/*                Note that ITEM *is* case-sensitive.  This attribute */
/*                is inherited from the case-sensitivity of kernel */
/*                variable names. */

/*     MAXN       is the maximum number of values that may be returned. */
/*                The output array VALUES must be declared with size at */
/*                least MAXN.  It's an error to supply an output array */
/*                that is too small to hold all of the values associated */
/*                with the requested kernel variable. */

/* $ Detailed_Output */

/*     DIM        is the number of values returned; this is always the */
/*                number of values associated with the requested kernel */
/*                variable unless an error has been signaled. */

/*     VALUES     is the array of values associated with the requested */
/*                kernel variable.  If VALUES is too small to hold all */
/*                of the values associated with the kernel variable, the */
/*                returned values of DIM and VALUES are undefined. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     1) If the requested kernel variable is not found in the kernel */
/*        pool, the error SPICE(KERNELVARNOTFOUND) is signaled. */

/*     2) If the requested kernel variable is found but the associated */
/*        values aren't numeric, the error SPICE(TYPEMISMATCH) is */
/*        signaled. */

/*     3) The output array VALUES must be declared with sufficient size */
/*        to contain all of the values associated with the requested */
/*        kernel variable.  If the dimension of */
/*        VALUES indicated by MAXN is too small to contain the */
/*        requested values, the error SPICE(ARRAYTOOSMALL) is signaled. */

/*     4) If the input dimension MAXN indicates there is more room */
/*        in VALUES than there really is---for example, if MAXN is */
/*        10 but values is declared with dimension 5---and the dimension */
/*        of the requested kernel variable is larger than the actual */
/*        dimension of VALUES, then this routine may overwrite */
/*        memory.  The results are unpredictable. */

/* $ Files */

/*     None. */

/* $ Particulars */

/*     This routine simplifies looking up PCK kernel variables by */
/*     constructing names of requested kernel variables and by */
/*     performing error checking. */

/*     This routine is intended for use in cases where the maximum */
/*     number of values that may be returned is known at compile */
/*     time.  The caller fetches all of the values associated with */
/*     the specified kernel variable via a single call to this */
/*     routine.  If the number of values to be fetched cannot be */
/*     known until run time, the lower-level routine  GDPOOL (an */
/*     entry point of POOL) should be used instead.  GDPOOL supports */
/*     fetching arbitrary amounts of data in multiple "chunks." */

/*     This routine is intended for use in cases where the requested */
/*     kernel variable is expected to be present in the kernel pool.  If */
/*     the variable is not found or has the wrong data type, this */
/*     routine signals an error.  In cases where it is appropriate to */
/*     indicate absence of an expected kernel variable by returning a */
/*     boolean "found flag" with the value .FALSE., again the routine */
/*     GDPOOL should be used. */

/* $ Examples */

/*     1)  When the kernel variable */

/*            BODY399_RADII */

/*         is present in the kernel pool---normally because a PCK */
/*         defining this variable has been loaded---the call */

/*            CALL BODVCD ( 399, 'RADII', 3, DIM, VALUES ) */

/*         returns the dimension and values associated with the variable */
/*         'BODY399_RADII', for example, */

/*            DIM       = 3 */
/*            VALUES(1) = 6378.140 */
/*            VALUES(2) = 6378.140 */
/*            VALUES(3) = 6356.755 */

/*     2) The call */

/*           CALL BODVCD ( 399, 'radii', 3, DIM, VALUES ) */

/*        usually will cause a SPICE(KERNELVARNOTFOUND) error to be */
/*        signaled, because this call will attempt to look up the */
/*        values associated with a kernel variable of the name */

/*           'BODY399_radii' */

/*        Since kernel variable names are case sensitive, this */
/*        name is not considered to match the name */

/*           'BODY399_RADII' */

/*        which normally would be present after a text PCK */
/*        containing data for all planets and satellites has */
/*        been loaded. */

/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman    (JPL) */
/*     B.V. Semenov    (JPL) */
/*     W.L. Taber      (JPL) */
/*     I.M. Underwood  (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.0.0, 24-OCT-2004 (NJB) (BVS) (WLT) (IMU) */

/* -& */
/* $ Index_Entries */

/*     fetch constants for a body from the kernel pool */
/*     physical constants for a body */

/* -& */

/*     SPICELIB functions */


/*     Local parameters */


/*     Local variables */


/*     Standard SPICE error handling. */

    if (return_()) {
	return 0;
    } else {
	chkin_("BODVCD", (ftnlen)6);
    }

/*     Construct the variable name from BODY and ITEM. */

    s_copy(varnam, "BODY", (ftnlen)32, (ftnlen)4);
    intstr_(bodyid, code, (ftnlen)16);
    suffix_(code, &c__0, varnam, (ftnlen)16, (ftnlen)32);
    suffix_("_", &c__0, varnam, (ftnlen)1, (ftnlen)32);
    suffix_(item, &c__0, varnam, item_len, (ftnlen)32);

/*     Make sure the item is present in the kernel pool. */

    dtpool_(varnam, &found, dim, type__, (ftnlen)32, (ftnlen)1);
    if (! found) {
	setmsg_("The variable # could not be found in the kernel pool.", (
		ftnlen)53);
	errch_("#", varnam, (ftnlen)1, (ftnlen)32);
	sigerr_("SPICE(KERNELVARNOTFOUND)", (ftnlen)24);
	chkout_("BODVCD", (ftnlen)6);
	return 0;
    }

/*     Make sure the item's data type is numeric. */

    if (*(unsigned char *)type__ != 'N') {
	setmsg_("The data associated with variable # are not of numeric type."
		, (ftnlen)60);
	errch_("#", varnam, (ftnlen)1, (ftnlen)32);
	sigerr_("SPICE(TYPEMISMATCH)", (ftnlen)19);
	chkout_("BODVCD", (ftnlen)6);
	return 0;
    }

/*     Make sure there's enough room in the array VALUES to hold */
/*     the requested data. */

    if (*maxn < *dim) {
	setmsg_("The data array associated with variable # has dimension #, "
		"which is larger than the available space # in the output arr"
		"ay.", (ftnlen)122);
	errch_("#", varnam, (ftnlen)1, (ftnlen)32);
	errint_("#", dim, (ftnlen)1);
	errint_("#", maxn, (ftnlen)1);
	sigerr_("SPICE(ARRAYTOOSMALL)", (ftnlen)20);
	chkout_("BODVCD", (ftnlen)6);
	return 0;
    }

/*     Grab the values.  We know at this point they're present in */
/*     the kernel pool, so we don't check the FOUND flag. */

    gdpool_(varnam, &c__1, maxn, dim, values, &found, (ftnlen)32);
    chkout_("BODVCD", (ftnlen)6);
    return 0;
} /* bodvcd_ */

