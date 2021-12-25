/* inedpl.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static doublereal c_b32 = 0.;
static doublereal c_b33 = 1.;

/* $Procedure      INEDPL ( Intersection of ellipsoid and plane ) */
/* Subroutine */ int inedpl_(doublereal *a, doublereal *b, doublereal *c__, 
	doublereal *plane, doublereal *ellips, logical *found)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1, d__2;

    /* Builtin functions */
    integer s_rnge(char *, integer, char *, integer);
    double sqrt(doublereal);

    /* Local variables */
    doublereal dist, span1[3], span2[3];
    integer i__;
    extern /* Subroutine */ int chkin_(char *, ftnlen), errdp_(char *, 
	    doublereal *, ftnlen);
    doublereal const__, point[3];
    extern doublereal vnorm_(doublereal *);
    extern logical vzero_(doublereal *);
    extern /* Subroutine */ int cgv2el_(doublereal *, doublereal *, 
	    doublereal *, doublereal *), pl2nvc_(doublereal *, doublereal *, 
	    doublereal *), pl2psv_(doublereal *, doublereal *, doublereal *, 
	    doublereal *), psv2pl_(doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    doublereal dplane[4];
    extern doublereal brcktd_(doublereal *, doublereal *, doublereal *);
    doublereal maxrad, rcircl, center[3], normal[3];
    extern /* Subroutine */ int sigerr_(char *, ftnlen), chkout_(char *, 
	    ftnlen), vsclip_(doublereal *, doublereal *), setmsg_(char *, 
	    ftnlen);
    doublereal invdst[3];
    extern logical return_(void);
    doublereal dstort[3], vec1[3], vec2[3];

/* $ Abstract */

/*     Find the intersection of a triaxial ellipsoid and a plane. */

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

/*     ELLIPSES */
/*     PLANES */

/* $ Keywords */

/*     ELLIPSE */
/*     ELLIPSOID */
/*     GEOMETRY */
/*     MATH */

/* $ Declarations */
/* $ Brief_I/O */

/*     Variable  I/O  Description */
/*     --------  ---  -------------------------------------------------- */
/*     A          I   Length of ellipsoid semi-axis lying on the x-axis. */
/*     B          I   Length of ellipsoid semi-axis lying on the y-axis. */
/*     C          I   Length of ellipsoid semi-axis lying on the z-axis. */
/*     PLANE      I   Plane that intersects ellipsoid. */
/*     ELLIPS     O   Intersection ellipse, when FOUND is .TRUE. */
/*     FOUND      O   Flag indicating whether ellipse was found. */

/* $ Detailed_Input */

/*     A, */
/*     B, */
/*     C              are the lengths of the semi-axes of a triaxial */
/*                    ellipsoid.  The ellipsoid is centered at the */
/*                    origin and oriented so that its axes lie on the */
/*                    x, y and z axes.  A, B, and C are the lengths of */
/*                    the semi-axes that point in the x, y, and z */
/*                    directions respectively. */

/*     PLANE          is a SPICELIB plane. */

/* $ Detailed_Output */

/*     ELLIPS         is the SPICELIB ellipse formed by the intersection */
/*                    of the input plane and ellipsoid.  ELLIPS will */
/*                    represent a single point if the ellipsoid and */
/*                    plane are tangent. */

/*                    If the intersection of the ellipsoid and plane is */
/*                    empty, ELLIPS is not modified. */


/*     FOUND          is .TRUE. if and only if the intersection of the */
/*                    ellipsoid and plane is non-empty. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     1)  If any of the lengths of the semi-axes of the input ellipsoid */
/*         are non-positive, the error SPICE(DEGENERATECASE) is */
/*         signaled.  ELLIPS is not modified.  FOUND is set to .FALSE. */

/*     2)  If the input plane in invalid, in other words, if the input */
/*         plane as the zero vector as its normal vector, the error */
/*         SPICE(INVALIDPLANE) is signaled. ELLIPS is not modified. */
/*         FOUND is set to .FALSE. */

/*     3)  If the input plane and ellipsoid are very nearly tangent, */
/*         roundoff error may cause this routine to give unreliable */
/*         results. */

/*     4)  If the input plane and ellipsoid are precisely tangent, the */
/*         intersection is a single point.  In this case, the output */
/*         ellipse is degenerate, but FOUND will still have the value */
/*         .TRUE.  You must decide whether this output makes sense for */
/*         your application. */

/* $ Files */

/*     None. */

/* $ Particulars */

/*     An ellipsoid and a plane can intersect in an ellipse, a single */
/*     point, or the empty set. */

/* $ Examples */

/*     1)  Suppose we wish to find the limb of a body, as observed from */
/*         location LOC in body-fixed coordinates.  The SPICELIB routine */
/*         EDLIMB solves this problem.  Here's how INEDPL is used in */
/*         that solution. */

/*         We assume LOC is outside of the body. The body is modelled as */
/*         a triaxial ellipsoid with semi-axes of length A, B, and C. */
/*         The notation */

/*            < X, Y > */

/*         indicates the inner product of the vectors X and Y. */

/*         The limb lies on the plane defined by */

/*            < X,  N >  =  1, */

/*         where the vector N is defined as */

/*            ( LOC(1) / A**2,   LOC(2) / B**2,   LOC(3) / C**2 ). */

/*         The assignments */

/*            N(1) = LOC(1) / A**2 */
/*            N(2) = LOC(2) / B**2 */
/*            N(3) = LOC(3) / C**2 */

/*         and the calls */

/*            CALL NVC2PL ( N,  1.0D0,  PLANE ) */

/*            CALL INEDPL ( A,  B,  C,  PLANE,  LIMB,  FOUND ) */

/*            CALL EL2CGV ( LIMB, CENTER, SMAJOR, SMINOR ) */

/*         will return the center and semi-axes of the limb. */


/*         How do we know that  < X, N > = 1  for all X on the limb? */
/*         This is because all limb points X satisfy */

/*            < LOC - X, SURFNM(X) >  =  0, */

/*         where SURFNM(X) is a surface normal at X.  SURFNM(X) is */
/*         parallel to the vector */

/*            V = (  X(1) / A**2,   X(2) / B**2,   X(3) / C**2  ) */

/*         so we have */

/*            < LOC - X, V >  =  0, */

/*            < LOC, V >      =  < X, V >  =  1  (from the original */
/*                                                ellipsoid */
/*                                                equation); */
/*         and finally */

/*            < X,   N >      =  1, */

/*         where the vector N is defined as */

/*            (  LOC(1) / A**2,    LOC(2) / B**2,   LOC(3) / C**2  ). */


/*     2)  Suppose we wish to find the terminator of a body.  We can */
/*         make a fair approximation to the location of the terminator */
/*         by finding the limb of the body as seen from the vertex of */
/*         the umbra; then the problem is essentially the same as in */
/*         example 1.  Let VERTEX be this location.  We make the */
/*         assignments */

/*            P(1) =   VERTEX(1) / A**2 */
/*            P(2) =   VERTEX(2) / B**2 */
/*            P(3) =   VERTEX(3) / C**2 */

/*         and then make the calls */

/*            CALL NVC2PL ( P,  1.0D0,  PLANE ) */

/*            CALL INEDPL ( A,  B,  C,  PLANE,  TERM,  FOUND ) */

/*         The SPICELIB ellipse TERM represents the terminator of the */
/*         body. */


/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman   (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.2.0, 16-NOV-2005 (NJB) */

/*        Bug fix:  error detection for case of invalid input plane was */
/*        added. */

/*        Updated to remove non-standard use of duplicate arguments */
/*        in VSCL calls. */

/* -    SPICELIB Version 1.1.0, 11-JUL-1995 (KRG) */

/*        Removed potential numerical precision problems that could be */
/*        caused by using a REAL constant in a double precision */
/*        computation. The value 1.0 was repaced with the value 1.0D0 in */
/*        the following three lines: */

/*           DSTORT(1) = 1.0 / A */
/*           DSTORT(2) = 1.0 / B */
/*           DSTORT(3) = 1.0 / C */

/*        Also changed was a numeric constant from 1.D0 to the */
/*        equivalent, but more aesthetically pleasing 1.0D0. */

/* -    SPICELIB Version 1.0.1, 10-MAR-1992 (WLT) */

/*        Comment section for permuted index source lines was added */
/*        following the header. */

/* -    SPICELIB Version 1.0.0, 02-NOV-1990 (NJB) */

/* -& */
/* $ Index_Entries */

/*     intersection of ellipsoid and plane */

/* -& */
/* $ Revisions */

/* -    SPICELIB Version 1.2.0, 16-NOV-2005 (NJB) */

/*        Bug fix:  error detection for case of invalid input plane was */
/*        added. */

/*        Updated to remove non-standard use of duplicate arguments */
/*        in VSCL calls. */

/* -    SPICELIB Version 1.1.0, 11-JUL-1995 (KRG) */

/*        Removed potential numerical precision problems that could be */
/*        caused by using a REAL constant in a double precision */
/*        computation. The value 1.0 was repaced with the value 1.0D0 in */
/*        the following three lines: */

/*           DSTORT(1) = 1.0 / A */
/*           DSTORT(2) = 1.0 / B */
/*           DSTORT(3) = 1.0 / C */

/*        Also changed was a numeric constant from 1.D0 to the */
/*        equivalent, but more aesthetically pleasing 1.0D0. */

/* -    SPICELIB Version 1.0.1, 10-MAR-1992 (WLT) */

/*        Comment section for permuted index source lines was added */
/*        following the header. */

/* -& */

/*     SPICELIB functions */


/*     Local variables */


/*     Standard SPICE error handling. */

    if (return_()) {
	return 0;
    } else {
	chkin_("INEDPL", (ftnlen)6);
    }

/*     We don't want to worry about flat ellipsoids: */

    if (*a <= 0. || *b <= 0. || *c__ <= 0.) {
	*found = FALSE_;
	setmsg_("Semi-axes: A = #,  B = #,  C = #.", (ftnlen)33);
	errdp_("#", a, (ftnlen)1);
	errdp_("#", b, (ftnlen)1);
	errdp_("#", c__, (ftnlen)1);
	sigerr_("SPICE(DEGENERATECASE)", (ftnlen)21);
	chkout_("INEDPL", (ftnlen)6);
	return 0;
    }

/*     Check input plane for zero normal vector. */

    pl2nvc_(plane, normal, &const__);
    if (vzero_(normal)) {
	setmsg_("Normal vector of the input PLANE is the zero vector.", (
		ftnlen)52);
	sigerr_("SPICE(INVALIDPLANE)", (ftnlen)19);
	chkout_("INEDPL", (ftnlen)6);
	return 0;
    }

/*     This algorithm is partitioned into a series of steps: */


/*     1)  Identify a linear transformation that maps the input */
/*         ellipsoid to the unit sphere.  We'll call this mapping the */
/*         `distortion' mapping.  Apply the distortion mapping to both */
/*         the input plane and ellipsoid.  The image of the plane under */
/*         this transformation will be a plane. */

/*     2)  Find the intersection of the transformed plane and the unit */
/*         sphere. */

/*     3)  Apply the inverse of the distortion mapping to the */
/*         intersection ellipse to find the undistorted intersection */
/*         ellipse. */


/*     Step 1: */

/*     Find the image of the ellipsoid and plane under the distortion */
/*     matrix.  Since the image of the ellipsoid is the unit sphere, */
/*     only the plane transformation requires any work. */

/*     If the input plane is too far from the origin to possibly */
/*     intersect the ellipsoid, return now.  This can save us */
/*     some numerical problems when we scale the plane and ellipsoid. */

/*     The point returned by PL2PSV is the closest point in PLANE */
/*     to the origin, so its norm gives the distance of the plane */
/*     from the origin. */

    pl2psv_(plane, point, span1, span2);
/* Computing MAX */
    d__1 = abs(*a), d__2 = abs(*b), d__1 = max(d__1,d__2), d__2 = abs(*c__);
    maxrad = max(d__1,d__2);
    if (vnorm_(point) > maxrad) {
	*found = FALSE_;
	chkout_("INEDPL", (ftnlen)6);
	return 0;
    }

/*     The distortion matrix and its inverse are */

/*        +-               -+        +-               -+ */
/*        |  1/A   0    0   |        |   A    0    0   | */
/*        |   0   1/B   0   |,       |   0    B    0   |. */
/*        |   0    0   1/C  |        |   0    0    C   | */
/*        +-               -+        +-               -+ */

/*     We declare them with length three, since we are going to make */
/*     use of the diagonal elements only. */

    dstort[0] = 1. / *a;
    dstort[1] = 1. / *b;
    dstort[2] = 1. / *c__;
    invdst[0] = *a;
    invdst[1] = *b;
    invdst[2] = *c__;

/*     Apply the distortion mapping to the input plane.  Applying */
/*     the distortion mapping to a point and two spanning vectors that */
/*     define the input plane yields a point and two spanning vectors */
/*     that define the distorted plane. */

    for (i__ = 1; i__ <= 3; ++i__) {
	point[(i__1 = i__ - 1) < 3 && 0 <= i__1 ? i__1 : s_rnge("point", i__1,
		 "inedpl_", (ftnlen)449)] = dstort[(i__2 = i__ - 1) < 3 && 0 
		<= i__2 ? i__2 : s_rnge("dstort", i__2, "inedpl_", (ftnlen)
		449)] * point[(i__3 = i__ - 1) < 3 && 0 <= i__3 ? i__3 : 
		s_rnge("point", i__3, "inedpl_", (ftnlen)449)];
	span1[(i__1 = i__ - 1) < 3 && 0 <= i__1 ? i__1 : s_rnge("span1", i__1,
		 "inedpl_", (ftnlen)450)] = dstort[(i__2 = i__ - 1) < 3 && 0 
		<= i__2 ? i__2 : s_rnge("dstort", i__2, "inedpl_", (ftnlen)
		450)] * span1[(i__3 = i__ - 1) < 3 && 0 <= i__3 ? i__3 : 
		s_rnge("span1", i__3, "inedpl_", (ftnlen)450)];
	span2[(i__1 = i__ - 1) < 3 && 0 <= i__1 ? i__1 : s_rnge("span2", i__1,
		 "inedpl_", (ftnlen)451)] = dstort[(i__2 = i__ - 1) < 3 && 0 
		<= i__2 ? i__2 : s_rnge("dstort", i__2, "inedpl_", (ftnlen)
		451)] * span2[(i__3 = i__ - 1) < 3 && 0 <= i__3 ? i__3 : 
		s_rnge("span2", i__3, "inedpl_", (ftnlen)451)];
    }
    psv2pl_(point, span1, span2, dplane);

/*     Step 2: */

/*     Find the intersection of the distorted plane and unit sphere. */


/*     The intersection of the distorted plane and the unit sphere */
/*     may be a circle, a point, or the empty set.  The distance of the */
/*     plane from the origin determines which type of intersection we */
/*     have.  If we represent the distorted plane by a unit normal */
/*     vector and constant, the size of the constant gives us the */
/*     distance of the plane from the origin.  If the distance is greater */
/*     than 1, the intersection of plane and unit sphere is empty. If */
/*     the distance is equal to 1, we have the tangency case. */

/*     The routine PL2PSV always gives us an output point that is the */
/*     closest point to the origin in the input plane.  This point is */
/*     the center of the intersection circle.  The spanning vectors */
/*     returned by PL2PSV, after we scale them by the radius of the */
/*     intersection circle, become an orthogonal pair of vectors that */
/*     extend from the center of the circle to the circle itself.  So, */
/*     the center and these scaled vectors define the intersection */
/*     circle. */

    pl2psv_(dplane, center, vec1, vec2);
    dist = vnorm_(center);
    if (dist > 1.) {
	*found = FALSE_;
	chkout_("INEDPL", (ftnlen)6);
	return 0;
    }

/*     Scale the generating vectors by the radius of the intersection */
/*     circle. */

/* Computing 2nd power */
    d__2 = dist;
    d__1 = 1. - d__2 * d__2;
    rcircl = sqrt(brcktd_(&d__1, &c_b32, &c_b33));
    vsclip_(&rcircl, vec1);
    vsclip_(&rcircl, vec2);

/*     Step 3: */

/*     Apply the inverse distortion to the intersection circle to find */
/*     the actual intersection ellipse. */

    for (i__ = 1; i__ <= 3; ++i__) {
	center[(i__1 = i__ - 1) < 3 && 0 <= i__1 ? i__1 : s_rnge("center", 
		i__1, "inedpl_", (ftnlen)511)] = invdst[(i__2 = i__ - 1) < 3 
		&& 0 <= i__2 ? i__2 : s_rnge("invdst", i__2, "inedpl_", (
		ftnlen)511)] * center[(i__3 = i__ - 1) < 3 && 0 <= i__3 ? 
		i__3 : s_rnge("center", i__3, "inedpl_", (ftnlen)511)];
	vec1[(i__1 = i__ - 1) < 3 && 0 <= i__1 ? i__1 : s_rnge("vec1", i__1, 
		"inedpl_", (ftnlen)512)] = invdst[(i__2 = i__ - 1) < 3 && 0 <=
		 i__2 ? i__2 : s_rnge("invdst", i__2, "inedpl_", (ftnlen)512)]
		 * vec1[(i__3 = i__ - 1) < 3 && 0 <= i__3 ? i__3 : s_rnge(
		"vec1", i__3, "inedpl_", (ftnlen)512)];
	vec2[(i__1 = i__ - 1) < 3 && 0 <= i__1 ? i__1 : s_rnge("vec2", i__1, 
		"inedpl_", (ftnlen)513)] = invdst[(i__2 = i__ - 1) < 3 && 0 <=
		 i__2 ? i__2 : s_rnge("invdst", i__2, "inedpl_", (ftnlen)513)]
		 * vec2[(i__3 = i__ - 1) < 3 && 0 <= i__3 ? i__3 : s_rnge(
		"vec2", i__3, "inedpl_", (ftnlen)513)];
    }

/*     Make an ellipse from the center and generating vectors. */

    cgv2el_(center, vec1, vec2, ellips);
    *found = TRUE_;
    chkout_("INEDPL", (ftnlen)6);
    return 0;
} /* inedpl_ */

