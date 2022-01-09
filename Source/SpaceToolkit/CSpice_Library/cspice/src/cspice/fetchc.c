/* fetchc.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* $Procedure            FETCHC ( Fetch from a character set ) */
integer fetchc_(integer *nth, char *set, ftnlen set_len)
{
    /* System generated locals */
    integer ret_val;

    /* Local variables */
    extern integer cardc_(char *, ftnlen);
    extern /* Subroutine */ int chkin_(char *, ftnlen), sigerr_(char *, 
	    ftnlen), chkout_(char *, ftnlen), setmsg_(char *, ftnlen), 
	    errint_(char *, integer *, ftnlen);
    extern logical return_(void);

/* $ Abstract */

/*      Returns the location within the set array of the NTH element */
/*      within the order imposed by the ASCII collating sequence. */

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

/*      None. */

/* $ Keywords */

/*      SETS */

/* $ Declarations */
/* $ Brief_I/O */

/*      VARIABLE  I/O  DESCRIPTION */
/*      --------  ---  -------------------------------------------------- */
/*      NTH        I   Index of a particular element. */
/*      SET        I   Input set. */

/*      The function returns the location of the NTH element in the set. */

/* $ Detailed_Input */

/*      NTH         is an index to an element of a set.  If the set is to */
/*                  be conceived as sorted in increasing order, then the */
/*                  NTH element of a set is well defined. */

/*      SET         is a set. */


/* $ Detailed_Output */

/*      The function returns the location within the set array of the */
/*      NTH element within the order imposed by the ASCII collating */
/*      sequence. Thus, a set may be traversed in order: */

/*         SET( FETCHC ( 1 ) ) */
/*         SET( FETCHC ( 2 ) ) */
/*          . */
/*          . */
/*         SET( FETCHC ( CARDC ( SET ) ) ) */

/* $ Parameters */

/*     None. */

/* $ Particulars */

/*      Within a set, the elements may be stored in arbitrary */
/*      order. The elements of a set may be retrieved by stepping */
/*      through the set array: */

/*         SET( 1 ) */
/*         SET( 2 ) */
/*          . */
/*          . */
/*         SET( CARDC ( SET ) ) */

/*      Likewise, the elements may be retreived in the order imposed by */
/*      the ASCII collating sequence, by using FETCHC: */

/*         SET( FETCHC ( 1, SET ) ) */
/*         SET( FETCHC ( 2, SET ) ) */
/*          . */
/*          . */
/*         SET( FETCHC ( CARDC ( SET ), SET ) ) */

/*      In general, FETCHC ( I, SET ) is not equal to I. */

/* $ Examples */

/*      Let SET contain the following elements. */

/*         'Feynman' */
/*         'Einstein' */
/*         'Bohr' */
/*         'Newton' */

/*      Then the code fragment */

/*         DO I = 1, CARDC ( SET ) */
/*            WRITE (*,*) SET(FETCHC(I,SET)) */
/*         END DO */

/*      always produces the following output. */

/*         Bohr */
/*         Einstein */
/*         Feynman */
/*         Newton */

/*      The code fragment */

/*         DO I = 1, CARDC ( SET ) */
/*            WRITE (*,*) SET(I) */
/*         END DO */

/*      produces the same elements in unspecified order. */

/* $ Restrictions */

/*      None. */

/* $ Exceptions */

/*      1) If the element does not exist, the error SPICE(INVALIDINDEX) */
/*         is signalled, and the value of FETCHC is zero. */

/* $ Files */

/*      None. */

/* $ Literature_References */

/*      None. */

/* $ Author_and_Institution */

/*      H.A. Neilan     (JPL) */
/*      W.L. Taber      (JPL) */
/*      I.M. Underwood  (JPL) */

/* $ Version */

/* -     SPICELIB Version 1.1.0, 17-MAY-1994 (HAN) */

/*        If the value of the function RETURN is TRUE upon execution of */
/*        this module, this function is assigned a default value of */
/*        either 0, 0.0D0, .FALSE., or blank depending on the type of */
/*        the function. */

/* -     SPICELIB Version 1.0.1, 10-MAR-1992 (WLT) */

/*         Comment section for permuted index source lines was added */
/*         following the header. */

/* -     SPICELIB Version 1.0.0, 31-JAN-1990 (WLT) (IMU) */

/* -& */
/* $ Index_Entries */

/*     fetch from a character set */

/* -& */

/*     SPICELIB functions */


/*     Set up the error processing. */

    if (return_()) {
	ret_val = 0;
	return ret_val;
    } else {
	chkin_("FETCHC", (ftnlen)6);
    }

/*     Check to see if the N'TH element exists. */

    if (*nth < 1 || *nth > cardc_(set, set_len)) {
	ret_val = 0;
	setmsg_("NTH element does not exist. NTH was *.", (ftnlen)38);
	errint_("*", nth, (ftnlen)1);
	sigerr_("SPICE(INVALIDINDEX)", (ftnlen)19);

/*     The great secret is that, for now, sets really are maintained */
/*     in order, for reasons of efficiency. */

    } else {
	ret_val = *nth;
    }
    chkout_("FETCHC", (ftnlen)6);
    return ret_val;
} /* fetchc_ */

