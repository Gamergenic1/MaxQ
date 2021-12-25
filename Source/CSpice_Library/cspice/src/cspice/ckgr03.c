/* ckgr03.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__2 = 2;
static integer c__6 = 6;

/* $Procedure      CKGR03 ( C-kernel, get record, type 03 ) */
/* Subroutine */ int ckgr03_(integer *handle, doublereal *descr, integer *
	recno, doublereal *record)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer i_dnnt(doublereal *);

    /* Local variables */
    integer addr__, nrec, psiz;
    extern /* Subroutine */ int chkin_(char *, ftnlen), dafus_(doublereal *, 
	    integer *, integer *, doublereal *, integer *), dafgda_(integer *,
	     integer *, integer *, doublereal *), sigerr_(char *, ftnlen), 
	    chkout_(char *, ftnlen), setmsg_(char *, ftnlen), errint_(char *, 
	    integer *, ftnlen);
    doublereal npoint;
    extern logical return_(void);
    doublereal dcd[2];
    integer beg, icd[6], end;

/* $ Abstract */

/*     Given the handle and descriptor of a type 3 segment in a CK file, */
/*     return a specified pointing instance from that segment. */

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

/*     CK */
/*     DAF */

/* $ Keywords */

/*     POINTING */

/* $ Declarations */
/* $ Brief_I/O */

/*     Variable  I/O  Description */
/*     --------  ---  -------------------------------------------------- */
/*     HANDLE     I   The handle of the file containing the segment. */
/*     DESCR      I   The segment descriptor. */
/*     RECNO      I   The number of the pointing instance to be returned. */
/*     RECORD     O   The pointing record. */

/* $ Detailed_Input */

/*     HANDLE     is the handle of the binary CK file containing the */
/*                desired segment. The file should have been opened */
/*                for read or write access, either by CKLPF, DAFOPR, */
/*                or DAFOPW. */

/*     DESCR      is the packed descriptor of the data type 3 segment. */

/*     RECNO      is the number of the discrete pointing instance to be */
/*                returned from the data type 3 segment. */

/* $ Detailed_Output */

/*     RECORD     is the pointing instance indexed by RECNO in the */
/*                segment.  The contents are as follows: */

/*                   RECORD( 1 ) = CLKOUT */

/*                   RECORD( 2 ) = q0 */
/*                   RECORD( 3 ) = q1 */
/*                   RECORD( 4 ) = q2 */
/*                   RECORD( 5 ) = q3 */

/*                   RECORD( 6 ) = av1  ] */
/*                   RECORD( 7 ) = av2  |-- Returned optionally */
/*                   RECORD( 8 ) = av3  ] */

/*                CLKOUT is the encoded spacecraft clock time associated */
/*                with the returned pointing values. */

/*                The quantities q0 - q3 are the components of the */
/*                quaternion that represents the C-matrix that transforms */
/*                vectors from the inertial reference frame of the */
/*                segment to the instrument frame at time CLKOUT. */

/*                The quantities av1, av2, and av3 represent the */
/*                angular velocity vector, and are returned only if */
/*                the segment contains angular velocity data. The */
/*                components of the angular velocity vector are */
/*                specified relative to the inertial reference */
/*                frame of the segment. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     1)  If the segment is not of data type 3, the error */
/*         SPICE(CKWRONGDATATYPE) is signalled. */

/*     2)  If RECNO is less than one or greater than the number of */
/*         records in the specified segment, the error */
/*         SPICE(CKNONEXISTREC) is signalled. */

/*     3)  If the specified handle does not belong to any DAF file that */
/*         is currently known to be open, an error is diagnosed by a */
/*         routine that this routine calls. */

/*     4)  If DESCR is not a valid descriptor of a segment in the CK */
/*         file specified by HANDLE, the results of this routine are */
/*         unpredictable. */

/* $ Files */

/*     The file specified by HANDLE should be open for read or */
/*     write access. */

/* $ Particulars */

/*     For a detailed description of the structure of a type 3 segment, */
/*     see the CK required reading. */

/*     This is a utility routine that may be used to read the individual */
/*     pointing instances that make up a type 3 segment.  It is normally */
/*     used in conjunction with CKNR03, which gives the number of */
/*     pointing instances stored in a segment. */

/* $ Examples */

/*     Suppose that MOC.BC is a CK file that contains segments of */
/*     data type 3.  Then the following code fragment extracts the */
/*     SCLK time, boresight vector, and angular velocity vector for */
/*     each pointing instance in the first segment in the file. */


/*           INTEGER               ICD     ( 6 ) */
/*           INTEGER               HANDLE */
/*           INTEGER               NREC */
/*           INTEGER               I */

/*           DOUBLE PRECISION      DCD     ( 2 ) */
/*           DOUBLE PRECISION      DESCR   ( 5 ) */
/*           DOUBLE PRECISION      RECORD  ( 8 ) */
/*           DOUBLE PRECISION      QUAT    ( 4 ) */
/*           DOUBLE PRECISION      AV      ( 3 ) */
/*           DOUBLE PRECISION      BORE    ( 3 ) */
/*           DOUBLE PRECISION      CMAT    ( 3, 3 ) */
/*           DOUBLE PRECISION      SCLKDP */

/*           LOGICAL               FOUND */
/*           LOGICAL               AVSEG */

/*     C */
/*     C     First load the file. (The file may also be opened by using */
/*     C     CKLPF.) */
/*     C */
/*           CALL DAFOPR ( 'MOC.BC', HANDLE ) */
/*     C */
/*     C     Begin forward search.  Find the first array. */
/*     C */
/*           CALL DAFBFS ( HANDLE ) */
/*           CALL DAFFNA ( FOUND  ) */
/*     C */
/*     C     Get segment descriptor. */
/*     C */
/*           CALL DAFGS ( DESCR ) */
/*     C */
/*     C     Unpack the segment descriptor into its double precision */
/*     C     and integer components. */
/*     C */
/*           CALL DAFUS ( DESCR, 2, 6, DCD, ICD ) */
/*     C */
/*     C     The data type for a segment is located in the third integer */
/*     C     component of the descriptor. */
/*     C */
/*           IF ( ICD( 3 ) .EQ. 3 ) THEN */
/*     C */
/*     C        Does the segment contain AV data? */
/*     C */
/*              AVSEG =  ( ICD(4) .EQ. 1 ) */
/*     C */
/*     C        How many records does this segment contain? */
/*     C */
/*              CALL CKNR03 ( HANDLE, DESCR, NREC ) */

/*              DO I = 1, NREC */
/*     C */
/*     C           Get the Ith pointing instance in the segment. */
/*     C */
/*                 CALL CKGR03 ( HANDLE, DESCR, I, RECORD ) */

/*     C */
/*     C           Unpack RECORD into the time, quaternion, and av. */
/*     C */
/*                 SCLKDP = RECORD ( 1 ) */

/*                 CALL MOVED ( RECORD(2), 4, QUAT ) */

/*                 IF  ( AVSEG )  THEN */
/*                    CALL MOVED ( RECORD(6), 3, AV   ) */
/*                 END IF */

/*     C */
/*     C           The boresight vector is the third row of the C-matrix. */
/*     C */
/*                 CALL Q2M ( QUAT, CMAT ) */

/*                 BORE(1) = CMAT(3,1) */
/*                 BORE(2) = CMAT(3,2) */
/*                 BORE(3) = CMAT(3,3) */
/*     C */
/*     C           Write out the results. */
/*     C */
/*                 WRITE (*,*) 'Record: ', I */
/*                 WRITE (*,*) */
/*                 WRITE (*,*) 'SCLK time = ', SCLKDP */
/*                 WRITE (*,*) */
/*                 WRITE (*,*) 'boresight: ', BORE */

/*                 IF ( AVSEG ) THEN */
/*                    WRITE (*,*) */
/*                    WRITE (*,*) 'angular velocity: ', AV */
/*                 END IF */

/*              END DO */

/*           END IF */

/* $ Restrictions */

/*     1) The binary CK file containing the segment whose descriptor was */
/*        passed to this routine must be opened for read or write access */
/*        by either CKLPF, DAFOPR, DAFOPW. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     J.M. Lynch (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.1.0, 07-SEP-2001 (EDW) */

/*        Replaced DAFRDA call with DAFGDA. */
/*        Added IMPLICIT NONE. */

/* -    SPICELIB Version 1.0.0, 25-NOV-1992 (JML) */

/* -& */
/* $ Index_Entries */

/*     get ck type_3 record */

/* -& */

/*     SPICELIB functions */


/*     Local parameters */

/*        NDC        is the number of double precision components in an */
/*                   unpacked C-kernel segment descriptor. */

/*        NIC        is the number of integer components in an unpacked */
/*                   C-kernel segment descriptor. */

/*        QSIZ       is the number of double precision numbers making up */
/*                   the quaternion portion of a pointing record. */

/*        QAVSIZ     is the number of double precision numbers making up */
/*                   the quaternion and angular velocity portion of a */
/*                   pointing record. */

/*        DTYPE      is the data type of the segment that this routine */
/*                   operates on. */



/*     Local variables */


/*     Standard SPICE error handling. */

    if (return_()) {
	return 0;
    } else {
	chkin_("CKGR03", (ftnlen)6);
    }

/*     The unpacked descriptor contains the following information */
/*     about the segment: */

/*        DCD(1)  Initial encoded SCLK */
/*        DCD(2)  Final encoded SCLK */
/*        ICD(1)  Instrument */
/*        ICD(2)  Inertial reference frame */
/*        ICD(3)  Data type */
/*        ICD(4)  Angular velocity flag */
/*        ICD(5)  Initial address of segment data */
/*        ICD(6)  Final address of segment data */

/*     From the descriptor, determine */

/*       1 - Is this really a type 3 segment? */
/*       2 - The beginning address of the segment. */
/*       3 - The number of pointing instances in the segment (it's the */
/*           last word in the segment). */
/*       4 - The existence of angular velocity data, which determines how */
/*           big the pointing portion of the returned record will be. */

    dafus_(descr, &c__2, &c__6, dcd, icd);
    if (icd[2] != 3) {
	setmsg_("Data type of the segment should be 3: Passed descriptor sho"
		"ws type = #.", (ftnlen)71);
	errint_("#", &icd[2], (ftnlen)1);
	sigerr_("SPICE(CKWRONGDATATYPE)", (ftnlen)22);
	chkout_("CKGR03", (ftnlen)6);
	return 0;
    }
    if (icd[3] == 1) {
	psiz = 7;
    } else {
	psiz = 4;
    }
    beg = icd[4];
    end = icd[5];
    dafgda_(handle, &end, &end, &npoint);
    nrec = i_dnnt(&npoint);

/*     If a request was made for a record which doesn't exist, then */
/*     signal an error and leave. */

    if (*recno < 1 || *recno > nrec) {
	setmsg_("Requested record number (#) does not exist. There are # rec"
		"ords in the segment.", (ftnlen)79);
	errint_("#", recno, (ftnlen)1);
	errint_("#", &nrec, (ftnlen)1);
	sigerr_("SPICE(CKNONEXISTREC)", (ftnlen)20);
	chkout_("CKGR03", (ftnlen)6);
	return 0;
    }

/*     Get the pointing record indexed by RECNO. */

    addr__ = beg + psiz * (*recno - 1);
    i__1 = addr__ + psiz - 1;
    dafgda_(handle, &addr__, &i__1, &record[1]);

/*     Next get the SCLK time.  Need to go past all of the NREC pointing */
/*     records (PSIZ * NREC numbers), and then to the RECNOth SCLK */
/*     time. */

    addr__ = beg + psiz * nrec + *recno - 1;
    dafgda_(handle, &addr__, &addr__, record);
    chkout_("CKGR03", (ftnlen)6);
    return 0;
} /* ckgr03_ */

