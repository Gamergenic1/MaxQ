/* dasine.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* $Procedure DASINE (arc sine of bracketed argument) */
doublereal dasine_(doublereal *arg, doublereal *tol)
{
    /* System generated locals */
    doublereal ret_val, d__1, d__2;

    /* Builtin functions */
    double asin(doublereal);

    /* Local variables */
    extern /* Subroutine */ int chkin_(char *, ftnlen), errdp_(char *, 
	    doublereal *, ftnlen), sigerr_(char *, ftnlen), chkout_(char *, 
	    ftnlen), setmsg_(char *, ftnlen);

/* $ Abstract */

/*     This routine produces a SPICE error if the |argument| exceeds */
/*     1.D0 by more than TOL. If ARG exceeds 1.D0, the argument is */
/*     evaluated as if it equaled 1.D0, if ARG is less than -1., */
/*     the argument is evaluated as if it equaled -1.D0. */

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

/*      INTERVALS,  NUMBERS,  UTILITY, INVERSE TRIGONOMETRIC FUNCTION */

/* $ Declarations */
/* $ Brief_I/O */

/*      VARIABLE  I/O  DESCRIPTION */
/*      --------  ---  -------------------------------------------------- */
/*      ARG        I   Argument to be evaluated. */
/*      TOL        I   Tolerance. */
/*      DASINE     O   The function returns the arc sine of ARG. */

/* $ Detailed_Input */

/*      ARG         is the arc sine argument that is to be evaluated */
/*                  such that if it is less than -1.D0 by more than TOL */
/*                  or greater than 1.D0 by more than TOL, an error */
/*                  results. */

/*      TOL         is a tolerance such that |ARG| is considered to be */
/*                  equal to 1.D0 if |ARG| <= 1.D0 + TOL. TOL must be */
/*                  non-negative. */

/* $ Detailed_Output */

/*      DASINE      The function returns the arc sine of ARG. If |ARG| */
/*                  >= 1.D0, it returns DASIN (1.D0) or DASIN (-1.D0) as */
/*                  appropriate. Values range from -PI/2 to PI/2. */

/* $ Parameters */

/*      None. */

/* $ Exceptions */

/*     1) If |ARG| > 1.D0 + TOL, the error SPICE(INPUTOUTOFBOUNDS) is */
/*        signaled. */

/*     2) If TOL is less than zero, the error SPICE(VALUEOUTOFRANGE) is */
/*        signaled. */

/* $ Files */

/*      None. */

/* $ Particulars */

/*      This routine determines whether |ARG| > 1.D0 + TOL. If */
/*      it is, an error will be flagged. In addition, */
/*      the values of ARG are constrained to [-1.D0, 1.D0]. */

/* $ Examples */

/*      The following illustrate the operation of DASINE. */

/*            DASINE (  -1.D0,        1.D-7 )  =  -PI/2 */
/*            DASINE (  -1.00001D0,   1.D-3 )  =  -PI/2 */
/*            DASINE (  -1.00001D0,   1.D-7 )  =  -PI/2 (error flagged) */
/*            DASINE (   0.D0,        1.D-7 )  =   0.D0 */
/*            DASINE (   1.00001D0,   1.D-3 )  =   PI/2 */
/*            DASINE (   1.00001D0,   1.D-7 )  =   PI/2 (error flagged) */

/* $ Restrictions */

/*      None. */

/* $ Author_and_Institution */

/*     L.S. Elson      (JPL) */

/* $ Literature_References */

/*      None. */

/* $ Version */

/* -    SPICELIB Version 1.0.0, 28-FEB-2006 (LSE) */

/* -& */
/* $ Index_Entries */

/*     check a d.p. argument for ASIN before evaluation */

/* -& */

/*     Bracket ARG. */

/* Computing MAX */
    d__1 = -1., d__2 = min(1.,*arg);
    ret_val = asin((max(d__1,d__2)));

/*     Check that tolerance is non negative. */

    if (*tol < 0.) {
	chkin_("DASINE", (ftnlen)6);
	setmsg_("TOL was #; must be non-negative.", (ftnlen)32);
	errdp_("#", tol, (ftnlen)1);
	sigerr_("SPICE(VALUEOUTOFRANGE)", (ftnlen)22);
	chkout_("DASINE", (ftnlen)6);
	return ret_val;
    }

/*     Check to see if |ARG| is within TOL of 1.D0. Signal error if */
/*     appropriate. */

    if (abs(*arg) - *tol > 1.) {
	chkin_("DASINE", (ftnlen)6);
	setmsg_("The |argument| specified was greater than 1.D0 by more than"
		" #. The value of the argument is #. ", (ftnlen)95);
	errdp_("#", tol, (ftnlen)1);
	errdp_("#", arg, (ftnlen)1);
	sigerr_("SPICE(INPUTOUTOFBOUNDS)", (ftnlen)23);
	chkout_("DASINE", (ftnlen)6);
	return ret_val;
    }
    return ret_val;
} /* dasine_ */

