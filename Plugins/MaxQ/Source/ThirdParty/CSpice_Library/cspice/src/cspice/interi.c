/* interi.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* $Procedure INTERI ( Intersect two integer sets ) */
/* Subroutine */ int interi_(integer *a, integer *b, integer *c__)
{
    integer over, acard, bcard, ccard;
    extern integer cardi_(integer *);
    extern /* Subroutine */ int chkin_(char *, ftnlen);
    integer csize;
    extern integer sizei_(integer *);
    extern /* Subroutine */ int scardi_(integer *, integer *);
    integer apoint, bpoint;
    extern /* Subroutine */ int excess_(integer *, char *, ftnlen), sigerr_(
	    char *, ftnlen), chkout_(char *, ftnlen);
    extern logical return_(void);

/* $ Abstract */

/*     Intersect two integer sets to form a third set. */

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

/*     CELLS */
/*     SETS */

/* $ Declarations */
/* $ Brief_I/O */

/*     VARIABLE  I/O  DESCRIPTION */
/*     --------  ---  -------------------------------------------------- */
/*     A          I   First input set. */
/*     B          I   Second input set. */
/*     C          O   Intersection of A and B. */

/* $ Detailed_Input */

/*     A        is a set. */


/*     B        is a set, distinct from A. */

/* $ Detailed_Output */

/*     C        is a set, distinct from sets A and B, which */
/*              contains the intersection of A and B (that is, */
/*              all of the elements which are in A, AND in B). */

/*              If the size (maximum cardinality) of C is smaller */
/*              than the cardinality of the intersection of A and B, */
/*              then only as many items as will fit in C are */
/*              included, and an error is signaled. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     1)  If the intersection of the two sets causes an excess of */
/*         elements, the error SPICE(SETEXCESS) is signaled. */

/* $ Files */

/*     None. */

/* $ Particulars */

/*     None. */

/* $ Examples */

/*     The INTERSECTION of two sets contains every element */
/*     which is in the first set AND in the second set. */

/*           {a,b}      intersect  {c,d}     =  {} */
/*           {a,b,c}               {b,c,d}      {b,c} */
/*           {a,b,c,d}             {}           {} */
/*           {}                    {a,b,c,d}    {} */
/*           {}                    {}           {} */

/*     The following call */

/*           CALL INTERC  ( PLANETS, ASTEROIDS, RESULT ) */

/*     places the intersection of the character sets PLANETS and */
/*     ASTEROIDS into the character set RESULT. */

/*     The output set must be distinct from both of the input sets. */
/*     For example, the following calls are invalid. */

/*           CALL INTERI  ( CURRENT,     NEW, CURRENT ) */
/*           CALL INTERI  (     NEW, CURRENT, CURRENT ) */

/*     In each of the examples above, whether or not the subroutine */
/*     signals an error, the results will almost certainly be wrong. */
/*     Nearly the same effect can be achieved, however, by placing the */
/*     result into a temporary set, which is immediately copied back */
/*     into one of the input sets, as shown below. */

/*           CALL INTERI ( CURRENT, NEW,  TEMP ) */
/*           CALL COPYI  ( TEMP,    NEW        ) */

/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman       (JPL) */
/*     C.A. Curzon        (JPL) */
/*     J. Diaz del Rio    (ODC Space) */
/*     W.L. Taber         (JPL) */
/*     I.M. Underwood     (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.1.0, 20-AUG-2021 (JDR) */

/*        Added IMPLICIT NONE statement. */

/*        Edited the header to comply with NAIF standard. */

/* -    SPICELIB Version 1.0.1, 10-MAR-1992 (WLT) */

/*        Comment section for permuted index source lines was added */
/*        following the header. */

/* -    SPICELIB Version 1.0.0, 31-JAN-1990 (CAC) (WLT) (IMU) (NJB) */

/* -& */
/* $ Index_Entries */

/*     intersect two integer sets */

/* -& */
/* $ Revisions */

/* -    Beta Version 1.1.0, 06-JAN-1989 (NJB) */

/*        Calling protocol of EXCESS changed. Call to SETMSG removed. */

/* -& */

/*     SPICELIB functions */


/*     Local variables */


/*     Set up the error processing. */

    if (return_()) {
	return 0;
    }
    chkin_("INTERI", (ftnlen)6);

/*     Find the cardinality of the input sets, and the allowed size */
/*     of the output set. */

    acard = cardi_(a);
    bcard = cardi_(b);
    csize = sizei_(c__);

/*     Begin with the input pointers at the first elements of the */
/*     input sets. The cardinality of the output set is zero. */
/*     And there is no overflow so far. */

    apoint = 1;
    bpoint = 1;
    ccard = 0;
    over = 0;

/*     When the end of either input set is reached, we're done. */

    while(apoint <= acard && bpoint <= bcard) {

/*        If there is still space in the output set, fill it */
/*        as necessary. */

	if (ccard < csize) {
	    if (a[apoint + 5] == b[bpoint + 5]) {
		++ccard;
		c__[ccard + 5] = a[apoint + 5];
		++apoint;
		++bpoint;
	    } else if (a[apoint + 5] < b[bpoint + 5]) {
		++apoint;
	    } else if (b[bpoint + 5] < a[apoint + 5]) {
		++bpoint;
	    }

/*        Otherwise, stop following the array, but continue to count the */
/*        number of elements in excess of the size of the output set. */

	} else {
	    if (a[apoint + 5] == b[bpoint + 5]) {
		++over;
		++apoint;
		++bpoint;
	    } else if (a[apoint + 5] < b[bpoint + 5]) {
		++apoint;
	    } else if (b[bpoint + 5] < a[apoint + 5]) {
		++bpoint;
	    }
	}
    }

/*     Set the cardinality of the output set. */

    scardi_(&ccard, c__);

/*     Report any excess. */

    if (over > 0) {
	excess_(&over, "set", (ftnlen)3);
	sigerr_("SPICE(SETEXCESS)", (ftnlen)16);
    }
    chkout_("INTERI", (ftnlen)6);
    return 0;
} /* interi_ */

