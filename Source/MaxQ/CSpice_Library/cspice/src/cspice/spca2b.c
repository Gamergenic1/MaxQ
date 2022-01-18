/* spca2b.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* $Procedure SPCA2B ( SPK and CK, ASCII to binary ) */
/* Subroutine */ int spca2b_(char *text, char *binary, ftnlen text_len, 
	ftnlen binary_len)
{
    /* System generated locals */
    cllist cl__1;

    /* Builtin functions */
    integer f_clos(cllist *);

    /* Local variables */
    integer unit;
    extern /* Subroutine */ int chkin_(char *, ftnlen), spct2b_(integer *, 
	    char *, ftnlen), chkout_(char *, ftnlen);
    extern logical return_(void);
    extern /* Subroutine */ int txtopr_(char *, integer *, ftnlen);

/* $ Abstract */

/*     Convert a text (ASCII) format SPK or CK file to an equivalent */
/*     binary file, including comments. */

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

/*     SPC */

/* $ Keywords */

/*     FILES */

/* $ Declarations */
/* $ Brief_I/O */

/*     Variable  I/O  Description */
/*     --------  ---  -------------------------------------------------- */
/*     TEXT       I   Name of an existing text format SPK or CK file. */
/*     BINARY     I   Name of a binary SPK or CK file to be created. */

/* $ Detailed_Input */

/*     TEXT        is the name of an existing text format SPK or CK */
/*                 file that may contain comments in the appropriate */
/*                 SPC format, as written by SPCB2A or SPCB2T.  This */
/*                 file is unchanged by calling SPCA2B. */

/*     BINARY      is the name of a binary SPK or CK file to be created. */
/*                 The binary file contains the same data and comments */
/*                 as the text file, but in the binary format required */
/*                 for use with the SPICELIB reader subroutines. */

/* $ Detailed_Output */

/*     None. */

/* $ Parameters */

/*     None. */

/* $ Files */

/*     See arguments TEXT and BINARY above. */

/* $ Exceptions */

/*     1) If there is an IOSTAT error while opening, reading, */
/*        or writing a file, a routine that SPCA2B calls will */
/*        diagnose and signal an error. */

/*     2) If the text file is not in the correct format, a */
/*        routine that SPCA2B calls will diagnose and signal */
/*        an error. */

/* $ Particulars */

/*     The SPICELIB SPK and CK reader subroutines read binary files. */
/*     However, because different computing environments have different */
/*     binary representations of numbers, you must convert SPK and CK */
/*     files to text format when porting from one system to another. */
/*     After converting the file to text, you can transfer it using */
/*     a transfer protocol program like Kermit or FTP.  Then, convert */
/*     the text file back to binary format. */

/*     The following is a list of the SPICELIB routines that convert */
/*     SPK and CK files between binary and text format: */

/*        SPCA2B    converts text to binary.  It opens the text file, */
/*                  creates a new binary file, and closes both files. */

/*        SPCB2A    converts binary to text.  It opens the binary file, */
/*                  creates a new text file, and closes both files. */

/*        SPCT2B    converts text to binary.  It creates a new binary */
/*                  file and closes it.  The text file is open on */
/*                  entrance and exit. */

/*        SPCB2T    converts binary to text.  It opens the binary */
/*                  file and closes it.  The text file is open on */
/*                  entrance and exit */

/*     See the SPC required reading for more information */
/*     about SPC routines and the SPK and CK file formats. */

/* $ Examples */

/*     This is an example of how to use SPCB2A and SPCA2B for */
/*     transferring files.  Suppose A.BSP is a binary SPK file in */
/*     environment 1; to transfer it to environment 2, follow */
/*     these three steps: */

/*        1) Call SPCB2A within a program in environment 1 to convert */
/*           the file to text: */

/*              CALL SPCB2A ( 'A.BSP', 'A.TSP' ) */

/*        2) Transfer the text file from environment 1 to environment 2 */
/*           using FTP, Kermit, or some other file transfer utility, */
/*           for example, */

/*              ftp> put A.TSP */

/*        3) Call SPCA2B within a program in environment 2 to convert */
/*           the file to binary on the new machine, */

/*              CALL SPCA2B ( 'A.TSP', 'A.BSP' ) */

/* $ Restrictions */

/*     1)  This routine assumes that the data and comments in the */
/*         text format SPK or CK file come from a binary file */
/*         and were written by one of the routines SPCB2A or SPCB2T. */
/*         Data and/or comments written any other way may not be */
/*         in the correct format and, therefore, may not be handled */
/*         properly. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     J.E. McLean    (JPL) */
/*     H.A. Neilan    (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.1.1, 10-MAR-1992 (WLT) */

/*        Comment section for permuted index source lines was added */
/*        following the header. */

/* -    SPICELIB Version 1.1.0, 05-SEP-1991 (HAN) */

/*        Removed declarations of unused variables. */

/* -    SPICELIB Version 1.0.0, 05-APR-1991 (JEM) */

/* -& */
/* $ Index_Entries */

/*     ascii spk or ck to binary */

/* -& */

/*     SPICELIB functions */


/*     Local parameters */

/*     Local variables */


/*     Standard SPICE error handling. */

    if (return_()) {
	return 0;
    } else {
	chkin_("SPCA2B", (ftnlen)6);
    }

/*     Open the text file with read access.  SPCT2B will */
/*     create the binary file and write the data and comments */
/*     to it.  Then we close the text file, and we're done. */

    txtopr_(text, &unit, text_len);
    spct2b_(&unit, binary, binary_len);
    cl__1.cerr = 0;
    cl__1.cunit = unit;
    cl__1.csta = 0;
    f_clos(&cl__1);
    chkout_("SPCA2B", (ftnlen)6);
    return 0;
} /* spca2b_ */

