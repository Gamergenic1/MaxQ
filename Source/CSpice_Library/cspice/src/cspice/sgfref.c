/* sgfref.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__6 = 6;
static integer c__5 = 5;
static integer c__7 = 7;

/* $Procedure      SGFREF ( Generic Segments: Fetch references ) */
/* Subroutine */ int sgfref_(integer *handle, doublereal *descr, integer *
	first, integer *last, doublereal *values)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double d_int(doublereal *);

    /* Local variables */
    integer base, b, e, i__;
    extern /* Subroutine */ int chkin_(char *, ftnlen), dafgda_(integer *, 
	    integer *, integer *, doublereal *);
    extern logical failed_(void);
    doublereal buffer[2];
    extern /* Subroutine */ int sgmeta_(integer *, doublereal *, integer *, 
	    integer *), sigerr_(char *, ftnlen), chkout_(char *, ftnlen);
    integer mynref;
    extern /* Subroutine */ int setmsg_(char *, ftnlen), errint_(char *, 
	    integer *, ftnlen);
    integer myreft;
    extern logical return_(void);

/* $ Abstract */

/*     Given the descriptor for a generic segment in a DAF file */
/*     associated with HANDLE, fetch from the references partition */
/*     of the segment the double precision numbers from FIRST to */
/*     LAST. */

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

/*     DAF Required Reading. */

/* $ Keywords */

/*     GENERIC SEGMENTS */

/* $ Declarations */
/* $ Brief_I/O */

/*     VARIABLE  I/O  DESCRIPTION */
/*     --------  ---  -------------------------------------------------- */
/*     HANDLE     I   Handle of a DAF open for reading. */
/*     DESCR      I   Descriptor for a generic segment in the DAF. */
/*     FIRST      I   The index of the first reference value to fetch. */
/*     LAST       I   The index of the last reference value to fetch. */
/*     VALUES     O   The reference values that were requested. */

/* $ Detailed_Input */

/*     HANDLE     is the handle of a DAF file opened for reading */
/*                that contains the segment described by DESCR. */

/*     DESCR      is the descriptor of the segment with the desired */
/*                constant values. This must be the descriptor for a */
/*                segment in the DAF associated with HANDLE. */

/*     FIRST      is the index of the first value to fetch from the */
/*                reference section of the DAF generic segment associated */
/*                with HANDLE and DESCR. */

/*     LAST       is the index of the last value to fetch from the */
/*                constants section of the DAF generic segment associated */
/*                with HANDLE and DESCR. */

/* $ Detailed_Output */

/*     VALUES      is the array of reference values obtained from the */
/*                 reference section of the DAF generic segment */
/*                 associated with HANDLE and DESCR. */

/* $ Parameters */

/*     This subroutine makes use of parameters defined in the file */
/*     'sgparam.inc'. */

/* $ Files */

/*     See the description of HANDLE above. */

/* $ Exceptions */

/*     1) The error SPICE(REQUESTOUTOFBOUNDS) will be signalled */
/*        if FIRST is less than 1 or LAST is greater than the */
/*        number of reference values. */

/*     2) The error SPICE(REQUESTOUTOFORDER) will be signalled */
/*        if LAST is less than FIRST. */

/*     3) The error SPICE(UNKNOWNREFDIR) will be signalled if the */
/*        reference directory structure is unrecognized.  The most */
/*        likely cause of this error is that an upgrade to your */
/*        version of the SPICE toolkit is needed. */

/* $ Particulars */

/*     This routine allows you to easily fetch values from the reference */
/*     section of a generic segment. */

/* $ Examples */

/*     Suppose that you have located a DAF generic segment. The code */
/*     fragment below shows how to fetch the I'th reference value from */
/*     that segment. */

/*        Declarations: */

/*        DOUBLE PRECISION      REFVAL */

/*        Fetch the Ith reference value from the segment. */

/*        CALL SGFREF ( HANDLE, DESCR, I, I, REFVAL ) */


/* $ Restrictions */

/*     The segment described by DESCR MUST be a generic segment, */
/*     otherwise the results of this routine are not predictable. */

/* $ Author_and_Institution */

/*     K.R. Gehringer  (JPL) */
/*     W.L. Taber      (JPL) */

/* $ Literature_References */

/*     None. */

/* $ Version */

/* -    SPICELIB Version 1.2.0, 07-SEP-2001 (EDW) */

/*        Replaced DAFRDA call with DAFGDA. */

/* -    SPICELIB Version 1.0.0, 12-APR-1995 (KRG) (WLT) */

/* -& */
/* $ Index_Entries */

/*     fetch reference values from a generic segment */

/* -& */

/*     Spicelib Functions */


/*     Local Parameters */

/*     Include the mnemonic values for the generic segment declarations. */


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

    if (return_()) {
	return 0;
    }
    chkin_("SGFREF", (ftnlen)6);

/*     Perform the needed initialization */

    sgmeta_(handle, descr, &c__6, &base);
    sgmeta_(handle, descr, &c__5, &myreft);
    sgmeta_(handle, descr, &c__7, &mynref);
    if (failed_()) {
	chkout_("SGFREF", (ftnlen)6);
	return 0;
    }

/*     Perform checks on the inputs for reasonableness. */

    if (*first < 1 || *last > mynref) {
	setmsg_("The range of reference items requested extends beyond the a"
		"vailable range of reference items.  The reference data is av"
		"ailable for indexes 1 to #.  You've requested data from # to"
		" #.", (ftnlen)182);
	errint_("#", &mynref, (ftnlen)1);
	errint_("#", first, (ftnlen)1);
	errint_("#", last, (ftnlen)1);
	sigerr_("SPICE(REQUESTOUTOFBOUNDS)", (ftnlen)25);
	chkout_("SGFREF", (ftnlen)6);
	return 0;
    }
    if (*last < *first) {
	setmsg_("The last reference item requested, #, is before the first r"
		"eference item requested, #.", (ftnlen)86);
	errint_("#", last, (ftnlen)1);
	errint_("#", first, (ftnlen)1);
	sigerr_("SPICE(REQUESTOUTOFORDER)", (ftnlen)24);
	chkout_("SGFREF", (ftnlen)6);
	return 0;
    }

/*     Ok.  We are ready to go. If the reference type is recognized */
/*     fetch the requested data. */

    if (myreft == 0) {

/*        The reference values are implied in this case. Read the */
/*        reference base value and step. If we fail, check out and */
/*        return; we don't want to try and comput anything with bogus */
/*        data. */

	b = base + 1;
	e = base + 2;
	dafgda_(handle, &b, &e, buffer);
	if (failed_()) {
	    chkout_("SGFREF", (ftnlen)6);
	    return 0;
	}

/*        Now simply compute the reference values using the implicit */
/*        model for them. */

	i__1 = *last;
	for (i__ = *first; i__ <= i__1; ++i__) {
	    d__1 = (doublereal) (i__ - 1) * buffer[1];
	    values[i__ - 1] = buffer[0] + d_int(&d__1);
	}
    } else if (myreft == 1) {

/*        The reference values are implied in this case. Read the */
/*        reference base value and step. If we fail, check out and */
/*        return; we don't want to try and comput anything with bogus */
/*        data. */

	b = base + 1;
	e = base + 2;
	dafgda_(handle, &b, &e, buffer);
	if (failed_()) {
	    chkout_("SGFREF", (ftnlen)6);
	    return 0;
	}

/*        Now simply compute the reference values using the implicit */
/*        model for them. */

	i__1 = *last;
	for (i__ = *first; i__ <= i__1; ++i__) {
	    d__1 = (doublereal) (i__ - 1) * buffer[1];
	    values[i__ - 1] = buffer[0] + d_int(&d__1);
	}
    } else if (myreft == 3 || myreft == 2 || myreft == 4) {

/*        In this case the reference values are actually stored */
/*        in the file.  This is even easier than the last case. */
/*        We simply fetch them with a call to DAF. We do not check for a */
/*        failure here, since all we do after the attempt to read is */
/*        checkout and return anyway. */

	b = base + *first;
	e = base + *last;
	dafgda_(handle, &b, &e, values);
    } else {
	setmsg_("The generic DAF segment you attempted to read has an unsupp"
		"orted reference directory structure. The integer code given "
		"for this structure is #. The likely cause of this anomoly is"
		" that your version of SPICELIB needs to be updated. Contact "
		"your system administrator or NAIF for a toolkit update. ", (
		ftnlen)295);
	errint_("#", &myreft, (ftnlen)1);
	sigerr_("SPICE(UNKNOWNREFDIR)", (ftnlen)20);
	chkout_("SGFREF", (ftnlen)6);
	return 0;
    }
    chkout_("SGFREF", (ftnlen)6);
    return 0;
} /* sgfref_ */

