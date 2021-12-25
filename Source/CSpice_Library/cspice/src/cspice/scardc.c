/* scardc.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* $Procedure      SCARDC ( Set the cardinality of a character cell ) */
/* Subroutine */ int scardc_(integer *card, char *cell, ftnlen cell_len)
{
    integer size;
    extern /* Subroutine */ int chkin_(char *, ftnlen), dechar_(char *, 
	    integer *, ftnlen), enchar_(integer *, char *, ftnlen), sigerr_(
	    char *, ftnlen), chkout_(char *, ftnlen), setmsg_(char *, ftnlen),
	     errint_(char *, integer *, ftnlen);
    extern logical return_(void);

/* $ Abstract */

/*      Set the cardinality of a character cell. */

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

/*      CELLS */

/* $ Keywords */

/*      CELLS */

/* $ Declarations */
/* $ Brief_I/O */

/*     VARIABLE  I/O  DESCRIPTION */
/*     --------  ---  -------------------------------------------------- */
/*     CARD       I   Cardinality of (number of elements in) the cell. */
/*     CELL       O   The cell. */

/* $ Detailed_Input */

/*     CARD         is the cardinality of (number of elements in) the */
/*                  cell. */

/* $ Detailed_Output */


/*      CELL        is a cell. */


/*                  On output, the cardinality of the cell is CARD. */

/* $ Parameters */

/*      None. */

/* $ Particulars */

/*     The set cardinality (SCARDC, SCARDD, and SCARDI) and set size */
/*     (SSIZEC, SSIZED, and SSIZEI) routines are typically used to */
/*     initialize cells for subsequent use. Since all cell routines */
/*     expect to find the size and cardinality of a cell in place, */
/*     no cell can be used until both have been set. */

/*     The set cardinality routines are also used by library routines */
/*     which manipulate cells (including set and window routines) to */
/*     reset the cardinalities of cells as they gain or lose elements. */

/* $ Examples */

/*     In the example below, the size and cardinality of the character */
/*     cell FRED are set in the main module of the program FLNSTN. */
/*     Both are subsequently retrieved, and the cardinality changed, */
/*     in one of its subroutines, WILMA. */

/*           PROGRAM FLNSTN */

/*           CHARACTER*30     FRED ( LBCELL:100 ) */
/*            . */
/*            . */
/*           CALL SSIZEC ( 100, FRED ) */
/*            . */
/*            . */
/*           CALL WILMA ( FRED ) */
/*            . */
/*            . */
/*           STOP */
/*           END */


/*           SUBROUTINE WILMA ( FRED ) */

/*           CHARACTER*(*)      FRED  ( LBCELL:* ) */
/*           INTEGER            SIZE */
/*           INTEGER            CARD */

/*           INTEGER            CARDC */
/*           INTEGER            SIZEC */
/*            . */
/*            . */
/*           SIZE = SIZEC ( FRED ) */
/*           CARD = CARDC ( FRED ) */
/*            . */
/*            . */
/*           CALL SCARDC ( MIN ( SIZE, CARD ), FRED ) */
/*           CALL EXCESS ( CARD-SIZE, 'cell' ) */
/*            . */
/*            . */
/*           RETURN */
/*           END */


/* $ Restrictions */

/*     None. */

/* $ Exceptions */

/*     1)  If the cardinality value supplied is less than 0 or greater */
/*         than the cell size, the error SPICE(INVALIDCARDINALITY) is */
/*         signalled. */

/* $ Files */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman    (JPL) */
/*     C.A. Curzon     (JPL) */
/*     W.L. Taber      (JPL) */
/*     I.M. Underwood  (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.0.1, 10-MAR-1992 (WLT) */

/*        Comment section for permuted index source lines was added */
/*        following the header. */

/* -    SPICELIB Version 1.0.0, 31-JAN-1990 (CAC) (WLT) (IMU) */

/* -& */
/* $ Index_Entries */

/*     set the cardinality of a character cell */

/* -& */
/* $ Revisions */

/* -    Beta Version 2.0.0, 13-MAR-1989 (NJB) */

/*        Check for invalid cardinality value added.  An error */
/*        is signalled if the value is out of range.  Examples */
/*        updated so as not to refer to the EMPTYx routines, and */
/*        to show the correct calling protocol for EXCESS. */

/* -& */

/*     SPICELIB functions */


/*     Local variables */

    if (return_()) {
	return 0;
    } else {
	chkin_("SCARDC", (ftnlen)6);
    }

/*     The cardinality may range from 0 to the size of the cell, */
/*     inclusive.  Other values will be snubbed. */

    dechar_(cell + (cell_len << 2), &size, cell_len);
    if (*card < 0 || *card > size) {
	setmsg_("Attempt to set cardinality of cell to invalid value.  The v"
		"alue was #.", (ftnlen)70);
	errint_("#", card, (ftnlen)1);
	sigerr_("SPICE(INVALIDCARDINALITY)", (ftnlen)25);
	chkout_("SCARDC", (ftnlen)6);
	return 0;
    }

/*     Not much to this. */

    enchar_(card, cell + cell_len * 5, cell_len);
    chkout_("SCARDC", (ftnlen)6);
    return 0;
} /* scardc_ */

