/* cposr.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* $Procedure            CPOSR ( Character position, reverse ) */
integer cposr_(char *str, char *chars, integer *start, ftnlen str_len, ftnlen 
	chars_len)
{
    /* System generated locals */
    integer ret_val;

    /* Builtin functions */
    integer i_len(char *, ftnlen), i_indx(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    integer b;
    logical found;
    integer lenstr;

/* $ Abstract */

/*     Find the first occurrence in a string of a character belonging */
/*     to a collection of characters, starting at a specified location, */
/*     searching in reverse. */

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
/*     STR        I   Any character string. */
/*     CHARS      I   A collection of characters. */
/*     START      I   Position to begin looking for one of CHARS */

/*     The function returns the index of the last character of STR */
/*     at or before index START that is in the collection CHARS. */

/* $ Detailed_Input */

/*     STR        is any character string. */

/*     CHARS      is a character string containing a collection of */
/*                characters.  Spaces in CHARS are significant. */

/*     START      is the position in STR to begin looking for one of the */
/*                characters in CHARS. */

/* $ Detailed_Output */

/*     The function returns the index of the last character of STR (at */
/*     or before index START) that is one of the characters in the */
/*     string CHARS.  If none of the characters is found, the function */
/*     returns zero. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     Error Free. */

/*     1) If START is less than 1, CPOSR returns zero. */

/*     2) If START is greater than LEN(STRING), the search begins */
/*        at the last character of the string. */

/* $ Files */

/*     None. */

/* $ Particulars */

/*     CPOSR is case sensitive. */

/*     An entire family of related SPICELIB routines (POS, CPOS, NCPOS, */
/*     POSR, CPOSR, NCPOSR) is desribed in the Required Reading. */

/*     Those familiar with the True BASIC language should note that */
/*     these functions are equivalent to the True BASIC intrinsic */
/*     functions with the same name. */

/* $ Examples */

/*     Let STRING = 'BOB, JOHN, TED, AND MARTIN    ' */
/*                   123456789012345678901234567890 */

/*     Normal (sequential) searching: */
/*     ------------------------------ */

/*           CPOSR( STRING, ' ,',    30 ) = 30 */

/*           CPOSR( STRING, ' ,',    29 ) = 29 */

/*           CPOSR( STRING, ' ,',    28 ) = 28 */

/*           CPOSR( STRING, ' ,',    27 ) = 27 */

/*           CPOSR( STRING, ' ,',    26 ) = 20 */

/*           CPOSR( STRING, ' ,',    19 ) = 16 */

/*           CPOSR( STRING, ' ,',    15 ) = 15 */

/*           CPOSR( STRING, ' ,',    14 ) = 11 */

/*           CPOSR( STRING, ' ,',    10 ) = 10 */

/*           CPOSR( STRING, ' ,',     9 ) =  5 */

/*           CPOSR( STRING, ' ,',     4 ) =  4 */

/*           CPOSR( STRING, ' ,',     3 ) =  0 */

/*     START out of bounds: */
/*     -------------------- */

/*           CPOSR( STRING, ' ,',   231 ) = 30 */

/*           CPOSR( STRING, ' ,',    31 ) = 30 */

/*           CPOSR( STRING, ' ,',     0 ) =  0 */

/*           CPOSR( STRING, ' ,',   -10 ) =  0 */


/*     Order within CHARS */
/*     ------------------ */

/*           CPOSR( STRING, 'JOHN',  23 ) =  18 */

/*           CPOSR( STRING, 'OHNJ',  23 ) =  18 */

/*           CPOSR( STRING, 'HNJO',  23 ) =  18 */

/*           CPOSR( STRING, 'NJOH',  23 ) =  18 */

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

/*     backward search for the position of a character */

/* -& */

/*     Local variables */

    lenstr = i_len(str, str_len);
    b = min(lenstr,*start);
    found = FALSE_;
    ret_val = 0;
    while(! found) {
	if (b <= 0) {
	    return ret_val;
	} else if (i_indx(chars, str + (b - 1), chars_len, (ftnlen)1) != 0) {
	    ret_val = b;
	    return ret_val;
	} else {
	    --b;
	}
    }
    return ret_val;
} /* cposr_ */

