/* ckmp06.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__2 = 2;
static integer c__6 = 6;

/* $Procedure CKMP06 ( C-kernel, get mini-segment parameters, type 06 ) */
/* Subroutine */ int ckmp06_(integer *handle, doublereal *descr, integer *
	msno, doublereal *rate, integer *subtyp, integer *winsiz, integer *
	nrec, doublereal *ivlbds, doublereal *lstepc)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    integer i_dnnt(doublereal *);

    /* Local variables */
    integer ndir, baddr, eaddr;
    extern /* Subroutine */ int chkin_(char *, ftnlen);
    integer minie;
    extern /* Subroutine */ int dafus_(doublereal *, integer *, integer *, 
	    doublereal *, integer *), dafgda_(integer *, integer *, integer *,
	     doublereal *);
    doublereal dc[2];
    integer ic[6];
    extern logical failed_(void);
    doublereal dpdata[1];
    integer epaddr;
    doublereal buffer[4];
    integer ivlbas, nepdir, ptrbas;
    extern /* Subroutine */ int sigerr_(char *, ftnlen), chkout_(char *, 
	    ftnlen), setmsg_(char *, ftnlen), errint_(char *, integer *, 
	    ftnlen);
    integer nintvl;
    extern logical return_(void);

/* $ Abstract */

/*     Return the mini-segment control parameters, mini-segment interval */
/*     bounds, and last epoch for a specified mini-segment in a type 6 */
/*     CK segment. */

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
/*     DESCR      I   The descriptor of the type 6 segment. */
/*     MSNO       I   Mini-segment index. */
/*     RATE       O   SCLK rate in seconds/tick. */
/*     SUBTYP     O   Subtype code. */
/*     WINSIZ     O   Interpolation window size. */
/*     NREC       O   Number of records in mini-segment. */
/*     IVLBDS     O   Mini-segment interval bounds of mini-segment. */
/*     LSTEPC     O   Last epoch of mini-segment. */

/* $ Detailed_Input */

/*     HANDLE     is the handle of the binary CK file containing the */
/*                segment. Normally the CK file should be open for */
/*                read access. See the Files section below for details. */

/*     DESCR      is the DAF descriptor of a CK data type 6 segment. */

/*     MSNO       is the index of a mini-segment within the segment */
/*                identified by HANDLE and DESCR. */

/* $ Detailed_Output */

/*     RATE       is the spacecraft clock rate for the specified */
/*                mini-segment. RATE has units of seconds/tick. */

/*     SUBTYP     is the subtype code of the specified mini-segment. */

/*     WINSIZ     is the interpolation window size for the specified */
/*                mini-segment. The window size is */

/*                   ( DEGREE + 1 ) / 2     for subtypes 0 and 2 */
/*                     DEGREE + 1           for subtypes 1 and 3 */

/*                where DEGREE is the interpolation degree of the */
/*                mini-segment. */

/*     NREC       is the number of data records in the CK mini-segment */
/*                identified by HANDLE, DESCR, and MSNO */

/*     IVLBDS     is a two-element array containing, in order, the */
/*                encoded SCLK start and stop times of the coverage */
/*                interval of the specified mini-segment. The */
/*                mini-segment provides data for times within this */
/*                interval. */

/*     LSTEPC     is the last epoch in the sequence of time tags */
/*                belonging to the specified mini-segment. LSTEPC is */
/*                an encoded SCLK time. */

/*                If LSTEPC precedes IVLBDS(2), the mini-segment has */
/*                a coverage gap between those two epochs. */

/* $ Parameters */

/*     See the include file ck06.inc for a description of CK type 6 */
/*     subtypes. */

/* $ Exceptions */

/*     1)  If the segment indicated by DESCR is not a type 6 segment, */
/*         the error 'SPICE(CKWRONGDATATYPE)' is signaled. */

/*     2)  If the specified handle does not belong to any DAF file that */
/*         is currently known to be open, an error is diagnosed by a */
/*         routine that this routine calls. */

/*     3)  If DESCR is not a valid descriptor of a valid segment in the */
/*         CK file specified by HANDLE, the results of this routine are */
/*         unpredictable. */

/*     4)  If N is less than 1 or greater than the number of */
/*         mini-segments in the specified segment, the error */
/*         SPICE(INDEXOUTOFRANGE) is signaled. */

/* $ Files */

/*     The CK file specified by HANDLE may be open for read or write */
/*     access. Normally, the file should have been opened for read */
/*     access. If the file is open for write access, the calling */
/*     application must ensure integrity of the CK segment being read. */
/*     If the structure of the segment is invalid---for example, if the */
/*     segment has been partially written---this routine will either */
/*     return invalid results, or it will cause a system-level runtime */
/*     error. */

/* $ Particulars */

/*     For a complete description of the internal structure of a type 6 */
/*     segment, see the CK Required Reading. */

/*     This routine is normally used in conjunction with CKNM06 and */
/*     CKGR06 to obtain time tags and packet data from a specified type */
/*     6 CK segment. */

/* $ Examples */

/*     The numerical results shown for this example may differ across */
/*     platforms. The results depend on the SPICE kernels used as */
/*     input, the compiler and supporting libraries, and the machine */
/*     specific arithmetic implementation. */


/*     1) The following program dumps records from a CK file that */
/*        contains only type 6 segments. */


/*        Example code begins here. */


/*             PROGRAM GREX1 */
/*             IMPLICIT NONE */
/*       C */
/*       C     Dump all records from a CK that */
/*       C     contains only segments of type 6. */
/*       C */

/*             INCLUDE 'ck06.inc' */
/*       C */
/*       C     Local parameters */
/*       C */
/*             INTEGER               ND */
/*             PARAMETER           ( ND     = 2 ) */

/*             INTEGER               NI */
/*             PARAMETER           ( NI     = 6 ) */

/*             INTEGER               DSCSIZ */
/*             PARAMETER           ( DSCSIZ = 5 ) */

/*             INTEGER               FILSIZ */
/*             PARAMETER           ( FILSIZ = 255 ) */

/*       C */
/*       C     RECSIZ is the size of the largest pointing */
/*       C     record, which corresponds to subtype 2. */
/*       C */
/*             INTEGER               RECSIZ */
/*             PARAMETER           ( RECSIZ = C06PS2 + 3 ) */

/*       C */
/*       C     Local variables */
/*       C */
/*             CHARACTER*(FILSIZ)    CK */

/*             DOUBLE PRECISION      DC     ( ND ) */
/*             DOUBLE PRECISION      DESCR  ( DSCSIZ ) */
/*             DOUBLE PRECISION      IVLBDS ( 2 ) */
/*             DOUBLE PRECISION      LSTEPC */
/*             DOUBLE PRECISION      RATE */
/*             DOUBLE PRECISION      RECORD ( RECSIZ ) */

/*             INTEGER               DTYPE */
/*             INTEGER               HANDLE */
/*             INTEGER               IC     ( NI ) */
/*             INTEGER               RECNO */
/*             INTEGER               MSNO */
/*             INTEGER               NMINI */
/*             INTEGER               NREC */
/*             INTEGER               SEGNO */
/*             INTEGER               SUBTYP */
/*             INTEGER               WINSIZ */

/*             LOGICAL               FOUND */


/*             CALL PROMPT ( 'Enter name of CK to dump > ', CK ) */

/*             CALL DAFOPR ( CK, HANDLE ) */
/*       C */
/*       C     Dump data from each CK segment. */
/*       C */
/*             SEGNO = 0 */

/*             CALL DAFBFS ( HANDLE ) */
/*             CALL DAFFNA ( FOUND  ) */

/*             DO WHILE ( FOUND ) */

/*                SEGNO = SEGNO + 1 */

/*                WRITE (*,*) ' ' */
/*                WRITE (*,*) ' ' */
/*                WRITE (*,*) 'Segment number: ', SEGNO */

/*       C */
/*       C        Fetch and unpack the descriptor of the */
/*       C        current segment; check the data type. */
/*       C */
/*                CALL DAFGS ( DESCR ) */
/*                CALL DAFUS ( DESCR, ND, NI, DC, IC ) */

/*                DTYPE = IC(3) */

/*                IF ( DTYPE .NE. 6 ) THEN */

/*                   CALL SETMSG ( 'Data type must be 6 but was #.' ) */
/*                   CALL ERRINT ( '#',  DTYPE                      ) */
/*                   CALL SIGERR ( 'SPICE(NOTSUPPORTED)'            ) */

/*                END IF */
/*       C */
/*       C        Get the mini-segment count for this */
/*       C        segment. */
/*       C */
/*                CALL CKNM06 ( HANDLE, DESCR, NMINI ) */
/*       C */
/*       C        Dump data from each mini-segment. */
/*       C */
/*                DO MSNO = 1, NMINI */
/*       C */
/*       C           Get the mini-segment's record count */
/*       C           and time bounds. */
/*       C */
/*                   CALL CKMP06 ( HANDLE, DESCR, MSNO,   RATE,  SUBTYP, */
/*            .                    WINSIZ, NREC,  IVLBDS, LSTEPC        ) */

/*                   WRITE (*,*) ' ' */
/*                   WRITE (*,*) '   Mini-segment number: ', MSNO */
/*                   WRITE (*,*) '      Rate:           ',   RATE */
/*                   WRITE (*,*) '      Subtype:        ',   SUBTYP */
/*                   WRITE (*,*) '      Window size:    ',   WINSIZ */
/*                   WRITE (*,*) '      Interval start: ',   IVLBDS(1) */
/*                   WRITE (*,*) '      Interval stop:  ',   IVLBDS(2) */
/*                   WRITE (*,*) '      Last epoch:     ',   LSTEPC */
/*                   WRITE (*,*) ' ' */

/*                   DO RECNO = 1, NREC */

/*                      CALL CKGR06 ( HANDLE, DESCR, */
/*            .                       MSNO,   RECNO,  RECORD ) */

/*                      WRITE (*,*) '      Record number: ', RECNO */
/*                      WRITE (*,*) '         SCLKDP:     ', RECORD(1) */
/*                      WRITE (*,*) '         Clock rate: ', RECORD(3) */

/*                      IF ( SUBTYP .EQ. C06TP0 ) THEN */

/*                         WRITE (*,*) '         Q(0): ', RECORD(4) */
/*                         WRITE (*,*) '         Q(1): ', RECORD(5) */
/*                         WRITE (*,*) '         Q(2): ', RECORD(6) */
/*                         WRITE (*,*) '         Q(3): ', RECORD(7) */
/*                         WRITE (*,*) '    d Q(0)/dt: ', RECORD(8) */
/*                         WRITE (*,*) '    d Q(1)/dt: ', RECORD(9) */
/*                         WRITE (*,*) '    d Q(2)/dt: ', RECORD(10) */
/*                         WRITE (*,*) '    d Q(3)/dt: ', RECORD(11) */

/*                      ELSE IF ( SUBTYP .EQ. C06TP1 ) THEN */

/*                         WRITE (*,*) '         Q(0): ', RECORD(4) */
/*                         WRITE (*,*) '         Q(1): ', RECORD(5) */
/*                         WRITE (*,*) '         Q(2): ', RECORD(6) */
/*                         WRITE (*,*) '         Q(3): ', RECORD(7) */

/*                      ELSE IF ( SUBTYP .EQ. C06TP2 ) THEN */

/*                         WRITE (*,*) '         Q(0): ', RECORD(4) */
/*                         WRITE (*,*) '         Q(1): ', RECORD(5) */
/*                         WRITE (*,*) '         Q(2): ', RECORD(6) */
/*                         WRITE (*,*) '         Q(3): ', RECORD(7) */
/*                         WRITE (*,*) '    d Q(0)/dt: ', RECORD(8) */
/*                         WRITE (*,*) '    d Q(1)/dt: ', RECORD(9) */
/*                         WRITE (*,*) '    d Q(2)/dt: ', RECORD(10) */
/*                         WRITE (*,*) '    d Q(3)/dt: ', RECORD(11) */
/*                         WRITE (*,*) '        AV(1): ', RECORD(12) */
/*                         WRITE (*,*) '        AV(2): ', RECORD(13) */
/*                         WRITE (*,*) '        AV(3): ', RECORD(14) */
/*                         WRITE (*,*) '   d AV(1)/dt: ', RECORD(15) */
/*                         WRITE (*,*) '   d AV(2)/dt: ', RECORD(16) */
/*                         WRITE (*,*) '   d AV(3)/dt: ', RECORD(17) */

/*                      ELSE IF ( SUBTYP .EQ. C06TP3 ) THEN */

/*                         WRITE (*,*) '         Q(0): ', RECORD(4) */
/*                         WRITE (*,*) '         Q(1): ', RECORD(5) */
/*                         WRITE (*,*) '         Q(2): ', RECORD(6) */
/*                         WRITE (*,*) '         Q(3): ', RECORD(7) */
/*                         WRITE (*,*) '        AV(1): ', RECORD(8) */
/*                         WRITE (*,*) '        AV(2): ', RECORD(9) */
/*                         WRITE (*,*) '        AV(3): ', RECORD(10) */

/*                      ELSE */
/*                         CALL SETMSG ( 'Subtype # is not ' */
/*            .            //            'recognized.'         ) */
/*                         CALL ERRINT ( '#', SUBTYP           ) */
/*                         CALL SIGERR ( 'SPICE(NOTSUPPORTED)' ) */
/*                      END IF */

/*                      WRITE (*,*) ' ' */

/*                  END DO */

/*                END DO */

/*                CALL DAFFNA ( FOUND ) */

/*             END DO */

/*             END */


/*     An initial portion of the output created by this program, when */
/*     the program was executed on a PC/Linux/gfortran platform, for */
/*     a sample CK containing type 6 segments, is shown below: */


/*        Segment number:            1 */

/*           Mini-segment number:            1 */
/*              Rate:             1.52587890625000000E-005 */
/*              Subtype:                   1 */
/*              Window size:              10 */
/*              Interval start:    11288914762710.869 */
/*              Interval stop:     11290384616127.203 */
/*              Last epoch:        11290384616127.203 */

/*              Record number:            1 */
/*                 SCLKDP:        11288914762710.869 */
/*                 Clock rate:   1.52587890625000000E-005 */
/*                 Q(0):   0.46164827229286126 */
/*                 Q(1):  -0.70575355403199758 */
/*                 Q(2):  -0.29319084125475281 */
/*                 Q(3):  -0.45036865373250068 */

/*              Record number:            2 */
/*                 SCLKDP:        11288998883607.230 */
/*                 Clock rate:   1.52587890625000000E-005 */
/*                 Q(0):   0.46162099825988423 */
/*                 Q(1):  -0.70570932104748119 */
/*                 Q(2):  -0.29323821047130305 */
/*                 Q(3):  -0.45043507864268195 */

/*              Record number:            3 */
/*                 SCLKDP:        11289077342579.063 */
/*                 Clock rate:   1.52587890625000000E-005 */
/*                 Q(0):   0.46159435700379842 */
/*                 Q(1):  -0.70566850733850173 */
/*                 Q(2):  -0.29328062251407311 */
/*                 Q(3):  -0.45049870564815003 */


/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman     (JPL) */
/*     J.M. Lynch       (JPL) */
/*     B.V. Semenov     (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.0.0, 14-MAR-2014 (NJB) (JML) (BVS) */

/* -& */
/* $ Index_Entries */

/*     get mini-segment parameters from ck type_6 segment */

/* -& */

/*     SPICELIB functions */


/*     Local parameters */

/*        ND         is the number of double precision components in an */
/*                   unpacked C-kernel descriptor. */

/*        NI         is the number of integer components in an unpacked */
/*                   C-kernel descriptor. */

/*        DTYPE      is the data type of the segment that this routine */
/*                   operates on. */


/*     Mini-segment control area size: */


/*     Local variables */


/*     Standard SPICE error handling. */

    if (return_()) {
	return 0;
    }
    chkin_("CKMP06", (ftnlen)6);

/*     The number of discrete pointing instances contained in a data */
/*     type 6 segment is stored in the last double precision word of the */
/*     segment. Since the address of the last word is stored in the */
/*     sixth integer component of the segment descriptor, it is a */
/*     trivial matter to extract the count. */

/*     The unpacked descriptor contains the following information about */
/*     the segment: */

/*        DC(1)  Initial encoded SCLK */
/*        DC(2)  Final encoded SCLK */

/*        IC(1)  CK frame class ID (aka "instrument") */
/*        IC(2)  Inertial reference frame */
/*        IC(3)  Data type */
/*        IC(4)  Angular velocity flag */
/*        IC(5)  Initial address of segment data */
/*        IC(6)  Final address of segment data */


    dafus_(descr, &c__2, &c__6, dc, ic);

/*     If this segment is not of data type 6, then signal an error. */

    if (ic[2] != 6) {
	setmsg_("Data type of the segment should be 6: Passed descriptor sho"
		"ws type = #.", (ftnlen)71);
	errint_("#", &ic[2], (ftnlen)1);
	sigerr_("SPICE(CKWRONGDATATYPE)", (ftnlen)22);
	chkout_("CKMP06", (ftnlen)6);
	return 0;
    }

/*     Check the mini-segment index. */

/*     The number of mini-segments is the final word in the segment. */

    baddr = ic[4];
    eaddr = ic[5];
    dafgda_(handle, &eaddr, &eaddr, dpdata);
    if (failed_()) {
	chkout_("CKMP06", (ftnlen)6);
	return 0;
    }
    nintvl = i_dnnt(dpdata);
    if (*msno < 1 || *msno > nintvl) {
	setmsg_("Mini-segment index must be in range 1:# but was #.", (ftnlen)
		50);
	errint_("#", &nintvl, (ftnlen)1);
	errint_("#", msno, (ftnlen)1);
	sigerr_("SPICE(INDEXOUTOFRANGE)", (ftnlen)22);
	chkout_("CKMP06", (ftnlen)6);
	return 0;
    }

/*     Set the base address of the mini-segment pointers. There are */
/*     NINTVL+1 pointers, and these precede the control area. */

    ptrbas = eaddr - 2 - (nintvl + 1);

/*     Set the base address of the interval bounds. There are N+1 */
/*     bounds, and these precede the interval bound directories and the */
/*     mini-segment pointers. */

/*     The directory count is */

/*        ( ( NINTVL + 1 ) - 1 ) / DIRSIZ */


    ndir = nintvl / 100;
    ivlbas = ptrbas - ndir - (nintvl + 1);

/*     Fetch the interval bounds for the mini-segment of interest. */

    i__1 = ivlbas + *msno;
    i__2 = ivlbas + *msno + 1;
    dafgda_(handle, &i__1, &i__2, ivlbds);

/*     Compute the mini-segment end pointer as an absolute DAF address. */
/*     The stored value is a relative address. Begin by looking up the */
/*     start pointer of the next mini-segment. */

    i__1 = ptrbas + *msno + 1;
    i__2 = ptrbas + *msno + 1;
    dafgda_(handle, &i__1, &i__2, buffer);
    if (failed_()) {
	chkout_("CKMP06", (ftnlen)6);
	return 0;
    }
    minie = baddr - 1 + i_dnnt(buffer) - 1;

/*     Fetch the parameters for the mini-segment. */

    i__1 = minie - 3;
    dafgda_(handle, &i__1, &minie, buffer);
    if (failed_()) {
	chkout_("CKMP06", (ftnlen)6);
	return 0;
    }
    *rate = buffer[0];
    *subtyp = i_dnnt(&buffer[1]);
    *winsiz = i_dnnt(&buffer[2]);
    *nrec = i_dnnt(&buffer[3]);

/*     The last epoch of the mini-segment precedes the mini-segment's */
/*     control area and the epoch directories. */

    nepdir = (*nrec - 1) / 100;
    epaddr = minie - 4 - nepdir;
    dafgda_(handle, &epaddr, &epaddr, lstepc);
    chkout_("CKMP06", (ftnlen)6);
    return 0;
} /* ckmp06_ */

