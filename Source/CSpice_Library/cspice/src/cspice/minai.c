/* minai.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* $Procedure  MINAI  ( Minimum element of array, integer ) */
/* Subroutine */ int minai_(integer *array, integer *ndim, integer *minval, 
	integer *loc)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    integer i__;

/* $ Abstract */

/*     Locate the minimum element of an integer array. */

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

/*      ARRAY,  SEARCH */

/* $ Declarations */
/* $ Brief_I/O */

/*      VARIABLE  I/O           DESCRIPTION */
/*      --------  ---  ------------------------------------------------- */
/*      ARRAY      I   Array. */
/*      NDIM       I   Number of elements in ARRAY. */
/*      MINVAL     O   Minimum value in ARRAY. */
/*      LOC        O   Location of MINVAL in ARRAY. */

/* $ Detailed_Input */

/*      ARRAY       is an arbitrary array. */

/*      NDIM        is the number of elements in ARRAY. */

/* $ Detailed_Output */

/*      MINVAL      is the value in array that is less than or equal */
/*                  to all other values in the array. If the array */
/*                  contains more than one element with this value, */
/*                  the first one is returned. */

/*      LOC         is the location of the minimum element. That is, */
/*                  MINVAL contains element ARRAY(LOC). */

/* $ Parameters */

/*      None. */

/* $ Exceptions */

/*     Error free. */

/*     1) If the array is empty (NDIM is less than one), LOC is zero, and */
/*        MINVAL is not changed. */

/* $ Files */

/*      None. */

/* $ Particulars */

/*      None. */

/* $ Examples */

/*      Let array A contain the following elements. */

/*         A(1) = 16 */
/*         A(2) =  4 */
/*         A(3) = 32 */
/*         A(4) = 64 */
/*         A(5) =  2 */
/*         A(6) =  8 */

/*      Then following the call */

/*         CALL MINAI ( A, 6, MINVAL, LOC ) */

/*      the values of MINVAL and LOC are 2 and 5 respectively. */

/* $ Restrictions */

/*      None */

/* $ Author_and_Institution */

/*      I.M. Underwood  (JPL) */

/* $ Literature_References */

/*      None */

/* $ Version */

/* -    SPICELIB Version 1.0.1, 10-MAR-1992 (WLT) */

/*        Comment section for permuted index source lines was added */
/*        following the header. */

/* -    SPICELIB Version 1.0.0, 31-JAN-1990 (IMU) */

/* -& */
/* $ Index_Entries */

/*     minimum element of integer array */

/* -& */
/* $ Revisions */

/* -     Beta Version 1.0.1, 2-FEB-1989 (IMU) */

/*         Missing header sections completed. */

/* -& */

/*     Local variables */

    if (*ndim <= 0) {
	*loc = 0;
	return 0;
    }
    *minval = array[0];
    *loc = 1;
    i__1 = *ndim;
    for (i__ = 2; i__ <= i__1; ++i__) {
	if (array[i__ - 1] < *minval) {
	    *minval = array[i__ - 1];
	    *loc = i__;
	}
    }
    return 0;
} /* minai_ */

