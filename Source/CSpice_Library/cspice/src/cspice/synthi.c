/* synthi.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* $Procedure      SYNTHI ( Return the Nth component of a symbol ) */
/* Subroutine */ int synthi_(char *name__, integer *nth, char *tabsym, 
	integer *tabptr, integer *tabval, integer *value, logical *found, 
	ftnlen name_len, ftnlen tabsym_len)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    integer nsym;
    extern integer cardc_(char *, ftnlen);
    extern /* Subroutine */ int chkin_(char *, ftnlen);
    extern integer sumai_(integer *, integer *), bsrchc_(char *, integer *, 
	    char *, ftnlen, ftnlen);
    integer locval;
    extern /* Subroutine */ int chkout_(char *, ftnlen);
    integer locsym;
    extern logical return_(void);

/* $ Abstract */

/*     Return the Nth component of a particular symbol in an integer */
/*     symbol table. */

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

/*     SYMBOLS */

/* $ Keywords */

/*     SYMBOLS */

/* $ Declarations */
/* $ Brief_I/O */

/*     VARIABLE  I/O  DESCRIPTION */
/*     --------  ---  -------------------------------------------------- */
/*     NAME       I   Name of the symbol whose Nth component is to be */
/*                    returned. */
/*     NTH        I   Index of the value to be returned. */
/*     TABSYM, */
/*     TABPTR, */
/*     TABVAL     I   Components of the symbol table. */
/*     VALUE      O   Nth value associated with the symbol. */
/*     FOUND      O   True if the Nth value of the symbol exists, false */
/*                    if it does not. */

/* $ Detailed_Input */

/*     NAME       is the name of the symbol whose Nth component is to be */
/*                returned. If NAME is not in the symbol table, FOUND is */
/*                false. */

/*     NTH        is the index of the component to be returned. If the */
/*                value of NTH is out of range ( NTH < 1 or NTH is */
/*                greater than the dimension of the symbol ) FOUND is */
/*                false. */

/*     TABSYM, */
/*     TABPTR, */
/*     TABVAL     are the components of an integer symbol table. */
/*                The symbol table is not modified by this subroutine. */

/* $ Detailed_Output */

/*     VALUES     is the NTH component of the symbol NAME. */

/*     FOUND      is true if NAME is in the symbol table and the NTH */
/*                component of NAME exists.  Otherwise FOUND is false. */

/* $ Parameters */

/*     None. */

/* $ Files */

/*     None. */

/* $ Exceptions */

/*     None. */

/* $ Particulars */

/*     Two conditions will cause the value of FOUND to be false: */

/*       1) The symbol NAME is not in the symbol table. */

/*       2) NTH is out of range ( NTH < 1 or NTH is greater than the */
/*          dimension of the symbol ). */

/* $ Examples */

/*     The contents of the symbol table are: */

/*        books   -->   5 */
/*        erasers -->   6 */
/*        pencils -->  12 */
/*                     24 */
/*        pens    -->  10 */
/*                     12 */
/*                     24 */

/*     The calls, */

/*     CALL SYNTHI ( 'pens',    2, TABSYM, TABPTR, TABVAL, VALUE, */
/*    .               FOUND                                       ) */

/*     CALL SYNTHI ( 'pencils', 3, TABSYM, TABPTR, TABVAL, VALUE, */
/*    .               FOUND                                       ) */

/*     CALL SYNTHI ( 'chairs',  1, TABPTR, TABVAL, TABVAL, VALUE, */
/*    .               FOUND                                       ) */

/*     return the values of VALUE and FOUND corresponding to NAME and */
/*     NTH: */

/*     NAME            NTH       VALUE      FOUND */
/*     ----------     -----     -------    ------- */
/*     pens             2         12         TRUE */
/*     pencils                              FALSE */
/*     chairs                               FALSE */

/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     H.A. Neilan     (JPL) */
/*     I.M. Underwood  (JPL) */

/* $ Version */

/* -     SPICELIB Version 1.0.1, 10-MAR-1992 (WLT) */

/*         Comment section for permuted index source lines was added */
/*         following the header. */

/* -     SPICELIB Version 1.0.0, 31-JAN-1990 (IMU) (HAN) */

/* -& */
/* $ Index_Entries */

/*     fetch nth value associated with a symbol */

/* -& */

/*     SPICELIB functions */


/*     Local variables */


/*     Standard SPICE error handling. */

    if (return_()) {
	return 0;
    } else {
	chkin_("SYNTHI", (ftnlen)6);
    }

/*     How many symbols to start with? */

    nsym = cardc_(tabsym, tabsym_len);

/*     Is this symbol even in the table? */

    locsym = bsrchc_(name__, &nsym, tabsym + tabsym_len * 6, name_len, 
	    tabsym_len);

/*     If it's not in the table, it's definitely a problem. */

    if (locsym == 0) {
	*found = FALSE_;

/*     If the value of NTH is out of range, that's a problem too. */

    } else if (*nth < 1 || *nth > tabptr[locsym + 5]) {
	*found = FALSE_;

/*     Otherwise, we can proceed without fear of error. Merely locate */
/*     and return the appropriate component from the values table. */

    } else {
	*found = TRUE_;
	i__1 = locsym - 1;
	locval = sumai_(&tabptr[6], &i__1) + *nth;
	*value = tabval[locval + 5];
    }
    chkout_("SYNTHI", (ftnlen)6);
    return 0;
} /* synthi_ */

