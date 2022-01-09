/* pos.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* $Procedure            POS ( Position of substring ) */
integer pos_(char *str, char *substr, integer *start, ftnlen str_len, ftnlen 
	substr_len)
{
    /* System generated locals */
    integer ret_val, i__1, i__2;

    /* Builtin functions */
    integer i_len(char *, ftnlen), s_cmp(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    integer b;
    logical found;
    integer lchnce, offset, lenstr;

/* $ Abstract */

/*     Find the first occurrence in a string of a substring, starting at */
/*     a specified location, searching forward. */

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

/*     SCANNING */

/* $ Keywords */

/*     CHARACTER */
/*     SEARCH */
/*     UTILITY */

/* $ Declarations */
/* $ Brief_I/O */

/*     VARIABLE  I/O  DESCRIPTION */
/*     --------  ---  -------------------------------------------------- */
/*     STR        I   A character string */
/*     SUBSTR     I   Substring to locate in the character string. */
/*     START      I   Where to start looking for SUBSTR in STR. */

/*     The function returns the index of SUBSTR in STR following START */

/* $ Detailed_Input */

/*     STR        is any character string. */

/*     SUBSTR     is a substring to look for in STR.  Spaces in */
/*                SUBSTR are significant. */

/*     START      is the position in STR to begin looking for SUBSTR. */

/* $ Detailed_Output */

/*     The function returns the index of the beginning of the first */
/*     substring of STR that begins on or after index START and is equal */
/*     to SUBSTR. If the substring cannot be found after START, the */
/*     function is returns 0. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     Error Free. */

/*     1) If START is less than 1, the search begins at the first */
/*        character of the string. */

/*     2) If START is greater than the length of the string, POS */
/*        returns zero. */

/* $ Files */

/*     None. */

/* $ Particulars */

/*     POS is case sensitive. */

/*     An entire family of related SPICELIB routines (POS, CPOS, NCPOS, */
/*     POSR, CPOSR, NCPOSR) is described in the Required Reading. */

/*     Those familiar with the True BASIC language should note that */
/*     these functions are equivalent to the True BASIC intrinsic */
/*     functions with the same names. */

/* $ Examples */

/*     Let STRING = 'AN ANT AND AN ELEPHANT        ' */
/*                   123456789012345678901234567890 */

/*      Normal (Sequential) Searching: */
/*      ------------------------------ */

/*            POS ( STRING, 'AN',  1 ) =  1 */
/*            POS ( STRING, 'AN',  3 ) =  4 */
/*            POS ( STRING, 'AN',  6 ) =  8 */
/*            POS ( STRING, 'AN', 10 ) = 12 */
/*            POS ( STRING, 'AN', 14 ) = 20 */
/*            POS ( STRING, 'AN', 22 ) =  0 */

/*      START out of bounds: */
/*      -------------------- */

/*            POS ( STRING, 'AN', -5 ) =  1 */
/*            POS ( STRING, 'AN',  0 ) =  1 */
/*            POS ( STRING, 'AN', 31 ) =  0 */
/*            POS ( STRING, 'AN', 44 ) =  0 */

/*      Significance of Spaces: */
/*      ----------------------- */

/*            POS ( STRING, 'AN',    1 ) =  1 */
/*            POS ( STRING, ' AN',   1 ) =  3 */
/*            POS ( STRING, ' AN ',  1 ) = 11 */
/*            POS ( STRING, ' AN  ', 1 ) =  0 */

/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     W.L. Taber      (JPL) */
/*     H.A. Neilan     (JPL) */
/*     B.V. Semenov    (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.0.3, 31-JAN-2008 (BVS) */

/*        Removed non-standard end-of-declarations marker */
/*        'C%&END_DECLARATIONS' from comments. */

/* -    SPICELIB Version 1.0.2, 10-MAR-1992 (WLT) */

/*        Comment section for permuted index source lines was added */
/*        following the header. */

/* -    SPICELIB Version 1.0.1, 26-MAR-1991 (HAN) */

/*        The Required Reading file POSITION was renamed to SCANNING. */
/*        This header was updated to reflect the change. */

/* -    SPICELIB Version 1.0.0, 31-JAN-1990 (WLT) */

/* -& */
/* $ Index_Entries */

/*     position of substring */

/* -& */

/*     Local variables */


/*     Let's find out how big every body is. */

    lenstr = i_len(str, str_len);
/* Computing MAX */
    i__1 = 0, i__2 = i_len(substr, substr_len) - 1;
    offset = max(i__1,i__2);
    lchnce = lenstr - offset;
    b = max(1,*start);

/*     Look for the string until we run find it or run out of room to */
/*     look. */

    found = FALSE_;
    ret_val = 0;
    while(! found) {
	if (b > lchnce) {
	    return ret_val;
	} else if (s_cmp(str + (b - 1), substr, b + offset - (b - 1), 
		substr_len) == 0) {
	    ret_val = b;
	    return ret_val;
	} else {
	    ++b;
	}
    }
    return ret_val;
} /* pos_ */

