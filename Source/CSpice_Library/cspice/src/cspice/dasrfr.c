/* dasrfr.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* $Procedure      DASRFR ( DAS, read file record ) */
/* Subroutine */ int dasrfr_(integer *handle, char *idword, char *ifname, 
	integer *nresvr, integer *nresvc, integer *ncomr, integer *ncomc, 
	ftnlen idword_len, ftnlen ifname_len)
{
    extern /* Subroutine */ int zzdasrfr_(integer *, char *, char *, integer *
	    , integer *, integer *, integer *, ftnlen, ftnlen), chkin_(char *,
	     ftnlen);
    extern logical failed_(void);
    extern /* Subroutine */ int chkout_(char *, ftnlen);
    extern logical return_(void);

/* $ Abstract */

/*     Return the contents of the file record of a specified DAS */
/*     file. */

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

/*     DAS */

/* $ Keywords */

/*     DAS */
/*     FILES */
/*     UTILITY */

/* $ Declarations */
/* $ Brief_I/O */

/*     Variable  I/O  Description */
/*     --------  ---  -------------------------------------------------- */
/*     HANDLE     I   DAS file handle. */
/*     IDWORD     O   ID word. */
/*     IFNAME     O   DAS internal file name. */
/*     NRESVR     O   Number of reserved records in file. */
/*     NRESVC     O   Number of characters in use in reserved rec. area. */
/*     NCOMR      O   Number of comment records in file. */
/*     NCOMC      O   Number of characters in use in comment area. */

/* $ Detailed_Input */

/*     HANDLE         is a file handle for a previously opened DAS file. */

/* $ Detailed_Output */

/*     IDWORD      is the `ID word' contained in the first eight */
/*                 characters of the file record. */

/*     IFNAME      is the internal file name of the DAS file.  The */
/*                 maximum length of the internal file name is 60 */
/*                 characters. */

/*     NRESVR      is the number of reserved records in the DAS file */
/*                 specified by HANDLE. */

/*     NRESVC      is the number of characters in use in the reserved */
/*                 record area of the DAS file specified by HANDLE. */

/*     NCOMR       is the number of comment records in the DAS file */
/*                 specified by HANDLE. */

/*     NCOMC       is the number of characters in use in the comment area */
/*                 of the DAS file specified by HANDLE. */


/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     1) If the file read attempted by this routine fails, the error */
/*        SPICE(DASFILEREADFAILED) will be signaled. */

/* $ Files */

/*     See the description of HANDLE under $Detailed_Input. */

/* $ Particulars */

/*     This routine provides a convenient way of retrieving the */
/*     information contained in the file record of a DAS file. */

/* $ Examples */

/*     1)  Obtain the internal file name of an existing DAS file. */


/*            C */
/*            C     Open the file for reading. */
/*            C */
/*                  CALL DASOPR ( FNAME, HANDLE  ) */

/*            C */
/*            C     Retrieve the internal file name and print it. */
/*            C */

/*                  CALL DASRFR ( HANDLE, */
/*                 .              IDWORD, */
/*                 .              IFNAME, */
/*                 .              NRESVR, */
/*                 .              NRESVC, */
/*                 .              NCOMR, */
/*                 .              NCOMC  ) */


/*                  WRITE (*,*) 'Internal file name is: ' */
/*                  WRITE (*,*)  IFNAME */

/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     K.R. Gehringer (JPL) */
/*     N.J. Bachman   (JPL) */
/*     W.L. Taber     (JPL) */

/* $ Version */

/* -    SPICELIB Version 3.0.0, 05-FEB-2015 (NJB) */

/*        Updated to support integration with the handle */
/*        manager subsystem and to support reading of DAS */
/*        files having non-native binary formats. */

/* -    SPICELIB Version 2.1.0, 25-AUG-1995 (NJB) */

/*        Bug fix:  local variables are now used in the direct */
/*        access of the file record.  Previously, the routine read */
/*        directly into the CHARACTER*(*) arguments IDWORD and IFNAME. */

/* -    SPICELIB Version 2.0.0, 27-OCT-1993 (KRG) */

/*        Removed references to specific DAS file open routines in the */
/*        $ Detailed_Input section of the header. This was done in order */
/*        to minimize documentation changes if these open routines ever */
/*        change. */

/*        Removed the DASID parameter which had the value 'NAIF/DAS', as */
/*        it was not used and is also made obsolete by the change in the */
/*        format of the ID word being implemented. */

/*        Added a check of FAILED after the call to DASHLU which will */
/*        check out and return if DASHLU fails. This is so that when in */
/*        return mode of the error handling the READ following the call */
/*        to DASHLU will not be executed. */

/*        Reworded some of the descriptions contained in the */
/*        $ Detailed_Output section of the header so that they were more */
/*        clear. */

/*        Changed the example so that it does not set a value for IFNAME */
/*        before calling DASRFR. This appears to have been a cut and */
/*        paste bug from DASWFR. */

/* -    SPICELIB Version 1.0.0, 15-JUL-1992 (NJB) (WLT) */

/* -& */
/* $ Index_Entries */

/*     read DAS file record */
/*     read DAS internal file name */

/* -& */
/* $ Revisions */

/* -    SPICELIB Version 2.1.0, 25-AUG-1995 (NJB) */

/*        Bug fix:  local variables are now used in the direct */
/*        access of the file record.  Previously, the routine read */
/*        directly into the CHARACTER*(*) arguments IDWORD and IFNAME. */

/* -    SPICELIB Version 2.0.0, 27-OCT-1993 (KRG) */

/*        Removed references to specific DAS file open routines in the */
/*        $ Detailed_Input section of the header. This was done in order */
/*        to minimize documentation changes if these open routines ever */
/*        change. */

/*        Removed the DASID parameter which had the value 'NAIF/DAS', as */
/*        it was not used and is also made obsolete by the change in the */
/*        format of the ID word being implemented. */

/*        Added a check of FAILED after the call to DASHLU which will */
/*        check out and return if DASHLU fails. This is so that when in */
/*        return mode of the error handling the READ following the call */
/*        to DASHLU will not be executed. */

/*        Reworded some of the descriptions contained in the */
/*        $ Detailed_Output section of the header so that they were more */
/*        clear. */

/*        Changed the example so that it does not set a value for IFNAME */
/*        before calling DASRFR. This appears to have been a cut and */
/*        paste bug from DASWFR. */

/* -    SPICELIB Version 1.0.0, 15-JUL-1992 (NJB) (WLT) */

/* -& */

/*     SPICELIB functions */


/*     Standard SPICE error handling. */

    if (return_()) {
	return 0;
    }
    chkin_("DASRFR", (ftnlen)6);
    zzdasrfr_(handle, idword, ifname, nresvr, nresvc, ncomr, ncomc, 
	    idword_len, ifname_len);
    if (failed_()) {
	chkout_("DASRFR", (ftnlen)6);
	return 0;
    }
    chkout_("DASRFR", (ftnlen)6);
    return 0;
} /* dasrfr_ */

