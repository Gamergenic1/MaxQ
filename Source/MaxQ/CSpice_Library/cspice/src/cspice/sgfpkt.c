/* sgfpkt.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__12 = 12;
static integer c__10 = 10;
static integer c__16 = 16;
static integer c__15 = 15;
static integer c__11 = 11;
static integer c__8 = 8;
static integer c__9 = 9;

/* $Procedure      SGFPKT ( Generic Segment: Fetch data packets ) */
/* Subroutine */ int sgfpkt_(integer *handle, doublereal *descr, integer *
	first, integer *last, doublereal *values, integer *ends)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    integer size, b, e, i__;
    extern /* Subroutine */ int chkin_(char *, ftnlen);
    doublereal dtemp[2];
    integer begin1, begin2;
    extern /* Subroutine */ int dafgda_(integer *, integer *, integer *, 
	    doublereal *);
    extern logical failed_(void);
    extern /* Subroutine */ int sgmeta_(integer *, doublereal *, integer *, 
	    integer *), sigerr_(char *, ftnlen);
    integer mypdrb;
    extern /* Subroutine */ int chkout_(char *, ftnlen);
    integer soffst;
    extern /* Subroutine */ int setmsg_(char *, ftnlen);
    integer mypktb, voffst;
    extern /* Subroutine */ int errint_(char *, integer *, ftnlen);
    integer mynpdr;
    extern logical return_(void);
    integer mypdrt, mynpkt, mypkto, mypksz;

/* $ Abstract */

/*     Given the descriptor for a generic segment in a DAF file */
/*     associated with HANDLE, fetch the data packets indexed from FIRST */
/*     to LAST from the packet partition of the generic segment. */

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

/*      DAF Required Reading */

/* $ Keywords */

/*      GENERIC SEGMENTS */

/* $ Declarations */
/* $ Brief_I/O */

/*      VARIABLE  I/O  DESCRIPTION */
/*      --------  ---  -------------------------------------------------- */
/*      HANDLE     I   The file handle attached to an open DAF. */
/*      DESCR      I   The descriptor associated with a generic segment. */
/*      FIRST      I   The index of the first data packet to fetch. */
/*      LAST       I   The index of the last data packet to fetch. */
/*      VALUES     O   The data packets that have been fetched. */
/*      ENDS       O   An array of pointers to the ends of the packets. */

/* $ Detailed_Input */

/*      HANDLE     is the handle of a DAF opened for reading that */
/*                 contains the segment described by DESCR. */

/*      DESCR      is the descriptor of the segment with the desired */
/*                 constant values. This must be the descriptor for a */
/*                 generic segment in the DAF associated with HANDLE. */

/*      FIRST      is the index of the first value to fetch from the */
/*                 constants section of the DAF segment described */
/*                 by DESCR. */

/*      LAST       is the index of the last value to fetch from the */
/*                 constants section of the DAF segment described */
/*                 by DESCR */

/* $ Detailed_Output */

/*     VALUES      is the array of values constructed by concatenating */
/*                 requested packets one after the other into */
/*                 an array.  Pictorially we can represent VALUES */
/*                 as: */

/*                    +--------------------------+ */
/*                    | first requested packet   | */
/*                    +--------------------------+ */
/*                    | second requested packet  | */
/*                    +--------------------------+ */
/*                               . */
/*                               . */
/*                               . */
/*                    +--------------------------+ */
/*                    | first requested packet   | */
/*                    +--------------------------+ */

/*     ENDS        is an array of pointers to the ends of the */
/*                 fetched packets.  ENDS(1) gives the index */
/*                 of the last item of the first packet fetched. */
/*                 ENDS(2) gives the index of the last item of */
/*                 the second packet fetched, etc. */

/* $ Parameters */

/*     This subroutine makes use of parameters defined in the file */
/*     'sgparam.inc'. */

/* $ Files */

/*      See the description of HANDLE above. */

/* $ Exceptions */

/*     1) The error SPICE(REQUESTOUTOFBOUNDS) will be signalled */
/*        if FIRST is less than 1 or LAST is greater than the */
/*        number of packets. */

/*     2) The error SPICE(REQUESTOUTOFORDER) will be signalled */
/*        if LAST is less than FIRST. */

/*     3) The error SPICE(UNKNOWNPACKETDIR) will be signalled if */
/*        the packet directory structure is unrecognized.  The most */
/*        likely cause of this error is that an upgrade to your */
/*        version of the SPICE toolkit is needed. */

/* $ Particulars */

/*     This routine fetches requested packets from a generic */
/*     DAF segment.  The two arrays returned have the following */
/*     relationship to one another.  The first packet returned */
/*     resides in VALUES between indexes 1 and ENDS(1).  If a */
/*     second packet is returned it resides in VALUES between */
/*     indices ENDS(1)+1 and ENDS(2).  This relations ship is */
/*     repeated so that if I is greater than 1 and at least I */
/*     packets were returned then the I'th packet resides in */
/*     VALUES between index ENDS(I-1) + 1 and ENDS(I). */

/* $ Examples */

/*     Suppose that you have located a generic DAF segment (as */
/*     identified by the contents of a segment descriptor).  The */
/*     fragment of code below shows how you could fetch packets */
/*     3 through 7 (assuming that many packets are present). */
/*     from the segment. */

/*        Declarations: */

/*        DOUBLE PRECISION   MYPKSZ (<enough room to hold all packets>) */

/*        INTEGER               ENDS  ( 5 ) */
/*        INTEGER               MYNPKT */

/*        get the number of packets */

/*        CALL SGMETA ( HANDLE, DESCR, NPKT, MYNPKT ) */

/*        finally, fetch the packets from the segment. */

/*        IF ( 7 .LE. MYNPKT ) THEN */
/*           CALL SGFPKT ( HANDLE, DESCR, 3, 7,  MYPKSZ, ENDS ) */
/*        END IF */

/* $ Restrictions */

/*      The segment described by DESCR must be a generic segment, */
/*      otherwise the results of this routine are not predictable. */

/* $ Author_and_Institution */

/*     K.R. Gehringer  (JPL) */
/*     W.L. Taber      (JPL) */

/* $ Literature_References */

/*      None. */

/* $ Version */

/* -    SPICELIB Version 1.2.0, 07-SEP-2001 (EDW) */

/*        Replaced DAFRDA calls with DAFGDA. */

/* -    SPICELIB Version 1.1.0, 30-JUL-1996 (KRG) (NJB) */

/*        Found and fixed a bug in the calculation of the beginning */
/*        address for variable length packet fetching. The base address */
/*        for the packet directory was not added into the value. This */
/*        bug went unnoticed because of a bug in SGSEQW, entry SGWES, */
/*        that put absolute addresses into the packet directory rather */
/*        than addresses that were relative to the start of the DAF */
/*        array. The bug in SGSEQW has also been fixed. */

/* -    SPICELIB Version 1.0.0, 06-JAN-1994 (KRG) (WLT) */

/* -& */
/* $ Index_Entries */

/*     fetch packets from a generic segment */

/* -& */

/*     Spicelib Functions */


/*     Local Parameters */

/*     Include the mnemonic values. */


/*     Local Variables */


/* $ Abstract */

/*     Parameter declarations for the generic segments subroutines. */

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

/*      DAF Required Reading */

/* $ Keywords */

/*       GENERIC SEGMENTS */

/* $ Particulars */

/*     This include file contains the parameters used by the generic */
/*     segments subroutines, SGxxxx. A generic segment is a */
/*     generalization of a DAF array which places a particular structure */
/*     on the data contained in the array, as described below. */

/*     This file defines the mnemonics that are used for the index types */
/*     allowed in generic segments as well as mnemonics for the meta data */
/*     items which are used to describe a generic segment. */

/*     A DAF generic segment contains several logical data partitions: */

/*        1) A partition for constant values to be associated with each */
/*           data packet in the segment. */

/*        2) A partition for the data packets. */

/*        3) A partition for reference values. */

/*        4) A partition for a packet directory, if the segment contains */
/*           variable sized packets. */

/*        5) A partition for a reference value directory. */

/*        6) A reserved partition that is not currently used. This */
/*           partition is only for the use of the NAIF group at the Jet */
/*           Propulsion Laboratory (JPL). */

/*        7) A partition for the meta data which describes the locations */
/*           and sizes of other partitions as well as providing some */
/*           additional descriptive information about the generic */
/*           segment. */

/*                 +============================+ */
/*                 |         Constants          | */
/*                 +============================+ */
/*                 |          Packet 1          | */
/*                 |----------------------------| */
/*                 |          Packet 2          | */
/*                 |----------------------------| */
/*                 |              .             | */
/*                 |              .             | */
/*                 |              .             | */
/*                 |----------------------------| */
/*                 |          Packet N          | */
/*                 +============================+ */
/*                 |      Reference Values      | */
/*                 +============================+ */
/*                 |      Packet Directory      | */
/*                 +============================+ */
/*                 |    Reference  Directory    | */
/*                 +============================+ */
/*                 |       Reserved  Area       | */
/*                 +============================+ */
/*                 |     Segment Meta Data      | */
/*                 +----------------------------+ */

/*     Only the placement of the meta data at the end of a generic */
/*     segment is required. The other data partitions may occur in any */
/*     order in the generic segment because the meta data will contain */
/*     pointers to their appropriate locations within the generic */
/*     segment. */

/*     The meta data for a generic segment should only be obtained */
/*     through use of the subroutine SGMETA. The meta data should not be */
/*     written through any mechanism other than the ending of a generic */
/*     segment begun by SGBWFS or SGBWVS using SGWES. */

/* $ Restrictions */

/*     1) If new reference index types are added, the new type(s) should */
/*        be defined to be the consecutive integer(s) after the last */
/*        defined reference index type used. In this way a value for */
/*        the maximum allowed index type may be maintained. This value */
/*        must also be updated if new reference index types are added. */

/*     2) If new meta data items are needed, mnemonics for them must be */
/*        added to the end of the current list of mnemonics and before */
/*        the NMETA mnemonic. In this way compatibility with files having */
/*        a different, but smaller, number of meta data items may be */
/*        maintained. See the description and example below. */

/* $ Author_and_Institution */

/*     N.J. Bachman      (JPL) */
/*     K.R. Gehringer    (JPL) */
/*     W.L. Taber        (JPL) */
/*     F.S. Turner       (JPL) */

/* $ Literature_References */

/*     Generic Segments Required Reading. */
/*     DAF Required Reading. */

/* $ Version */

/* -    SPICELIB Version 1.1.1, 28-JAN-2004 (NJB) */

/*        Header update: equations for comptutations of packet indices */
/*        for the cases of index types 0 and 1 were corrected. */

/* -    SPICELIB Version 1.1.0, 25-09-98 (FST) */

/*        Added parameter MNMETA, the minimum number of meta data items */
/*        that must be present in a generic DAF segment. */

/* -    SPICELIB Version 1.0.0, 04-03-95 (KRG) (WLT) */

/* -& */

/*     Mnemonics for the type of reference value index. */

/*     Two forms of indexing are provided: */

/*        1) An implicit form of indexing based on using two values, a */
/*           starting value, which will have an index of 1, and a step */
/*           size between reference values, which are used to compute an */
/*           index and a reference value associated with a specified key */
/*           value. See the descriptions of the implicit types below for */
/*           the particular formula used in each case. */

/*        2) An explicit form of indexing based on a reference value for */
/*           each data packet. */


/*     Reference Index Type 0 */
/*     ---------------------- */

/*     Implied index. The index and reference value of a data packet */
/*     associated with a specified key value are computed from the two */
/*     generic segment reference values using the formula below. The two */
/*     generic segment reference values, REF(1) and REF(2), represent, */
/*     respectively, a starting value and a step size between reference */
/*     values. The index of the data packet associated with a key value */
/*     of VALUE is given by: */

/*                          /    VALUE - REF(1)    \ */
/*        INDEX = 1  +  INT | -------------------- | */
/*                          \        REF(2)        / */

/*     and the reference value associated with VALUE is given by: */

/*        REFVAL = REF(1) + DBLE (INDEX-1) * REF(2) */


/*     Reference Index Type 1 */
/*     ---------------------- */

/*     Implied index. The index and reference value of a data packet */
/*     associated with a specified key value are computed from the two */
/*     generic segment reference values using the formula below. The two */
/*     generic segment reference values, REF(1) and REF(2), represent, */
/*     respectively, a starting value and a step size between reference */
/*     values. The index of the data packet associated with a key value */
/*     of VALUE is given by: */

/*                          /          VALUE - REF(1)    \ */
/*        INDEX = 1  +  INT | 0.5 + -------------------- | */
/*                          \              REF(2)        / */


/*     and the reference value associated with VALUE is given by: */

/*        REFVAL = REF(1) + DBLE (INDEX-1) * REF(2) */

/*     We get the larger index in the event that VALUE is halfway between */
/*     X(I) and X(I+1), where X(I) = BUFFER(1) + DBLE (I-1) * REFDAT(2). */


/*     Reference Index Type 2 */
/*     ---------------------- */

/*     Explicit index. In this case the number of packets must equal the */
/*     number of reference values. The index of the packet associated */
/*     with a key value of VALUE is the index of the last reference item */
/*     that is strictly less than VALUE. The reference values must be in */
/*     ascending order, REF(I) < REF(I+1). */


/*     Reference Index Type 3 */
/*     ---------------------- */

/*     Explicit index. In this case the number of packets must equal the */
/*     number of reference values. The index of the packet associated */
/*     with a key value of VALUE is the index of the last reference item */
/*     that is less than or equal to VALUE. The reference values must be */
/*     in ascending order, REF(I) < REF(I+1). */


/*     Reference Index Type 4 */
/*     ---------------------- */

/*     Explicit index. In this case the number of packets must equal the */
/*     number of reference values. The index of the packet associated */
/*     with a key value of VALUE is the index of the reference item */
/*     that is closest to the value of VALUE. In the event of a "tie" */
/*     the larger index is selected. The reference values must be in */
/*     ascending order, REF(I) < REF(I+1). */


/*     These parameters define the valid range for the index types. An */
/*     index type code, MYTYPE, for a generic segment must satisfy the */
/*     relation MNIDXT <= MYTYPE <= MXIDXT. */


/*     The following meta data items will appear in all generic segments. */
/*     Other meta data items may be added if a need arises. */

/*       1)  CONBAS  Base Address of the constants in a generic segment. */

/*       2)  NCON    Number of constants in a generic segment. */

/*       3)  RDRBAS  Base Address of the reference directory for a */
/*                   generic segment. */

/*       4)  NRDR    Number of items in the reference directory of a */
/*                   generic segment. */

/*       5)  RDRTYP  Type of the reference directory 0, 1, 2 ... for a */
/*                   generic segment. */

/*       6)  REFBAS  Base Address of the reference items for a generic */
/*                   segment. */

/*       7)  NREF    Number of reference items in a generic segment. */

/*       8)  PDRBAS  Base Address of the Packet Directory for a generic */
/*                   segment. */

/*       9)  NPDR    Number of items in the Packet Directory of a generic */
/*                   segment. */

/*      10)  PDRTYP  Type of the packet directory 0, 1, ... for a generic */
/*                   segment. */

/*      11)  PKTBAS  Base Address of the Packets for a generic segment. */

/*      12)  NPKT    Number of Packets in a generic segment. */

/*      13)  RSVBAS  Base Address of the Reserved Area in a generic */
/*                   segment. */

/*      14)  NRSV    Number of items in the reserved area of a generic */
/*                   segment. */

/*      15)  PKTSZ   Size of the packets for a segment with fixed width */
/*                   data packets or the size of the largest packet for a */
/*                   segment with variable width data packets. */

/*      16)  PKTOFF  Offset of the packet data from the start of a packet */
/*                   record. Each data packet is placed into a packet */
/*                   record which may have some bookkeeping information */
/*                   prepended to the data for use by the generic */
/*                   segments software. */

/*      17)  NMETA   Number of meta data items in a generic segment. */

/*     Meta Data Item  1 */
/*     ----------------- */


/*     Meta Data Item  2 */
/*     ----------------- */


/*     Meta Data Item  3 */
/*     ----------------- */


/*     Meta Data Item  4 */
/*     ----------------- */


/*     Meta Data Item  5 */
/*     ----------------- */


/*     Meta Data Item  6 */
/*     ----------------- */


/*     Meta Data Item  7 */
/*     ----------------- */


/*     Meta Data Item  8 */
/*     ----------------- */


/*     Meta Data Item  9 */
/*     ----------------- */


/*     Meta Data Item 10 */
/*     ----------------- */


/*     Meta Data Item 11 */
/*     ----------------- */


/*     Meta Data Item 12 */
/*     ----------------- */


/*     Meta Data Item 13 */
/*     ----------------- */


/*     Meta Data Item 14 */
/*     ----------------- */


/*     Meta Data Item 15 */
/*     ----------------- */


/*     Meta Data Item 16 */
/*     ----------------- */


/*     If new meta data items are to be added to this list, they should */
/*     be added above this comment block as described below. */

/*        INTEGER               NEW1 */
/*        PARAMETER           ( NEW1   = PKTOFF + 1 ) */

/*        INTEGER               NEW2 */
/*        PARAMETER           ( NEW2   = NEW1   + 1 ) */

/*        INTEGER               NEWEST */
/*        PARAMETER           ( NEWEST = NEW2   + 1 ) */

/*     and then the value of NMETA must be changed as well to be: */

/*        INTEGER               NMETA */
/*        PARAMETER           ( NMETA  = NEWEST + 1 ) */

/*     Meta Data Item 17 */
/*     ----------------- */


/*     Maximum number of meta data items. This is always set equal to */
/*     NMETA. */


/*     Minimum number of meta data items that must be present in a DAF */
/*     generic segment.  This number is to remain fixed even if more */
/*     meta data items are added for compatibility with old DAF files. */


/*     Standard SPICE error handling. */

    if (return_()) {
	return 0;
    }
    chkin_("SGFPKT", (ftnlen)6);

/*     Perform the needed initialization */

    sgmeta_(handle, descr, &c__12, &mynpkt);
    sgmeta_(handle, descr, &c__10, &mypdrt);
    sgmeta_(handle, descr, &c__16, &mypkto);
    sgmeta_(handle, descr, &c__15, &mypksz);
    sgmeta_(handle, descr, &c__11, &mypktb);
    if (failed_()) {
	chkout_("SGFPKT", (ftnlen)6);
	return 0;
    }

/*     Perform checks on the inputs for reasonableness. */

    if (*first < 1 || *last > mynpkt) {
	setmsg_("The range of packets requested extends beyond the available"
		" packet data.  The packet data is available for indexes 1 to"
		" #.  You've requested data from # to #. ", (ftnlen)159);
	errint_("#", &mynpkt, (ftnlen)1);
	errint_("#", first, (ftnlen)1);
	errint_("#", last, (ftnlen)1);
	sigerr_("SPICE(REQUESTOUTOFBOUNDS)", (ftnlen)25);
	chkout_("SGFPKT", (ftnlen)6);
	return 0;
    }
    if (*last < *first) {
	setmsg_("The last packet requested, #, is before the first packet re"
		"quested, #. ", (ftnlen)71);
	errint_("#", last, (ftnlen)1);
	errint_("#", first, (ftnlen)1);
	sigerr_("SPICE(REQUESTOUTOFORDER)", (ftnlen)24);
	chkout_("SGFPKT", (ftnlen)6);
	return 0;
    }

/*     We've passed the sanity tests, if the packet directory structure */
/*     is recognized fetch the values and ends. We assume that we are */
/*     reading data from a correctly constructed generic segment, so we */
/*     do not need to worry about the type of reference index, as this is */
/*     not needed to fetch a data packet. */
/*     Currently, only two packet directory types are supported, and this */
/*     subroutine is the only place that this is documented. The types */
/*     have values zero (0) and one (1) for, respectively, fixed size */
/*     packets and variable size packets. */

    if (mypdrt == 0) {

/*        All packets have the same size MYPKSZ so the address of the */
/*        start of the first packet and end of the last packet are easily */
/*        computed. */

	if (mypkto == 0) {

/*           Compute tha addresses for the packet data in the generic */
/*           segment. */

	    b = mypktb + (*first - 1) * mypksz + 1;
	    e = mypktb + *last * mypksz;

/*           Get the packet data all in one shot since we know it's */
/*           contiguous. */

	    dafgda_(handle, &b, &e, values);
	} else {

/*           Compute the addresses for the packet data in the generic */
/*           segment. Remember that we need to account for an offset */
/*           here to get to the start of the actual data packet. */

	    size = mypksz + mypkto;

/*           Get the packet data. Because there is an offset from the */
/*           address to the start of the packet data, we need to get */
/*           the data one packet at a time rather than all at once. */

	    i__1 = *last;
	    for (i__ = *first; i__ <= i__1; ++i__) {
		soffst = (i__ - 1) * size + 1;
		voffst = (i__ - *first) * mypksz + 1;
		b = mypktb + soffst + mypkto;
		e = mypktb + soffst + mypksz;
		dafgda_(handle, &b, &e, &values[voffst - 1]);
		if (failed_()) {
		    chkout_("SGFPKT", (ftnlen)6);
		    return 0;
		}
	    }
	}

/*        Compute the ends for each of the data packets. This is the */
/*        same for both of the cases above because we have fixed size */
/*        data packets. */

	i__1 = *last - *first + 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    ends[i__ - 1] = i__ * mypksz;
	}
    } else {

/*        In addition to the other meta data items already retrieved, we */
/*        will also need a few others. */

	sgmeta_(handle, descr, &c__8, &mypdrb);
	sgmeta_(handle, descr, &c__9, &mynpdr);
	if (failed_()) {
	    chkout_("SGFPKT", (ftnlen)6);
	    return 0;
	}

/*        Each packet has a different size, so we need to fetch each one */
/*        individually, keeping track of the ends and things. We assume */
/*        that there is enough room in the array of values to hold all of */
/*        the packets. For the variable packet case, however, we do not */
/*        need to treat the implicit indexing and explicit indexing cases */
/*        separately. */

	voffst = 1;
	i__1 = *last - *first + 1;
	for (i__ = 1; i__ <= i__1; ++i__) {

/*           Compute the addresses in the generic segment for the */
/*           beginning of data packets I and I+1. We need these to */
/*           compute the size of the packet. */

	    b = mypdrb + *first + i__ - 1;
	    e = b + 1;

/*           Get the beginning addresses for the two data packets and */
/*           convert them into integers. */

	    dafgda_(handle, &b, &e, dtemp);
	    if (failed_()) {
		chkout_("SGFPKT", (ftnlen)6);
		return 0;
	    }
	    begin1 = (integer) dtemp[0];
	    begin2 = (integer) dtemp[1];

/*           Compute the size of data packet I, remembering to deal with */
/*           the packet offset that might be present, and the beginning */
/*           and ending addresses for the packet data. */

	    size = begin2 - begin1 - mypkto;
	    b = mypktb + begin1;
	    e = b + size - 1;

/*           Get the data for packet I. */

	    dafgda_(handle, &b, &e, &values[voffst - 1]);
	    if (failed_()) {
		chkout_("SGFPKT", (ftnlen)6);
		return 0;
	    }

/*           Compute the end for packet I and store it. */

	    voffst += size;
	    ends[i__ - 1] = voffst - 1;
	}
    }
    chkout_("SGFPKT", (ftnlen)6);
    return 0;
} /* sgfpkt_ */

