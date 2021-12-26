KPL/FK

   Topocentric Reference Frame Definition Kernel for DSN Stations
   =====================================================================

   Original file name:                   earth_topo_201023.tf
   Creation date:                        2020 Oct 28 12:35
   Created by:                           Nat Bachman  (NAIF/JPL)


   Introduction
   =====================================================================

   This file defines topocentric reference frames associated with each
   of the DSN stations cited in the list below under "Position Data."
   Each topocentric reference frame ("frame" for short) is centered at
   the associated station and is fixed to the earth. Mathematically, a
   frame "definition" is a specification of the orientation of the
   frame relative to another frame. In this file, the other frame,
   which we'll refer to as the "base frame," is the terrestrial
   reference frame ITRF93.

   The orientation of a topocentric frame relative to the base frame
   relies on a reference spheroid (see "Data Sources" below). The
   z-axis of the topocentric frame contains the station location and is
   normal to the reference spheroid:  the line containing the z-axis
   intersects the reference spheroid at right angles. The x-axis
   points north and the y-axis points west.  Note that stations
   normally have non-zero altitude with respect to the spheroid.

   Loosely speaking, a topocentric frame enables computations involving
   the local directions "north", "west," and "up" at a surface point on
   an extended body. For example, the "elevation" of an object relative
   to the center of a topocentric frame is the object's latitude in
   that frame. The corresponding azimuth is the angle from the
   topocentric frame's x-axis to the projection of the center-to-object
   vector onto the topocentric frame's x-y plane, measured in the
   clockwise direction.

   The orientation of a topocentric frame relative to the base frame can
   be described by an Euler angle sequence.  Let M be the rotation
   matrix that maps vectors from the base frame to a specified
   topocentric frame.  Then


      M   =  [ Pi  ]  [ Pi/2 - LAT ]  [ LON ]
                    3               2        3

   where LON, LAT are the associated station's geodetic latitude and
   longitude.  Note that the frame definitions below actually
   provide Euler angles for the inverse of M and use units of
   degrees, so the angle sequences are

       -1                         o          o
      M   =  [ -LON ]   [ LAT - 90 ]    [ 180 ]
                     3               2         3

   See the Rotation Required Reading for details concerning Euler angles.


   Regarding the structure of this file
   ------------------------------------

   The SPICE utility PINPOINT was used to create the topocentric frame
   specifications contained in this file. The comment file

      earthstns_fx_201023.cmt

   was used as an input to the PINPOINT run, and that file is automatically
   included by PINPOINT in the frame kernel it creates.


   Using this kernel
   =====================================================================

   Revision description
   --------------------

   This kernel is based on data from a single, current source: [1].

   This kernel supersedes the kernel

      earth_topo_050714_v2.tf

   The set of stations covered by this file has changed from that file as
   follows:

      Deleted stations (not present in current file):

         PARKES
         DSS-12
         DSS-16
         DSS-17
         DSS-23
         DSS-27
         DSS-28
         DSS-33
         DSS-42
         DSS-46
         DSS-49 (alternate name for PARKES)
         DSS-61
         DSS-64 (alternate name for DSS-65)
         DSS-66

      Added stations:

         DSS-35
         DSS-36
         DSS-56

      Name transfers---name now refers to a new station:

         DSS-53


   Planned updates
   ---------------

   Updates will be be made to keep this file in sync with updates to the
   source document [1].

   Values for DSS-53 are expected to be updated. Values for DSS-23 will be
   added. There is no schedule for these changes at this time.


   Using this kernel
   =====================================================================

   Kernel loading
   --------------

   In order for a SPICE-based program to make use of this kernel, the
   kernel must be loaded via the SPICE routine FURNSH.  If you are
   running application software created by a third party, see the
   documentation for that software for instructions on kernel
   management.

   See also "Associated frame kernels" and "Associated PCK files" below.

   Users requiring data from the superseded frame kernel

      earth_topo_050714_v2.tf

   can load that file in addition to this one. In the case of conflicting
   data, data from the file loaded later will take precedence.

   ** Caution **: the file named above is the only DSN station frame kernel
   that may be safely loaded together with this file. The first version of
   that file

      earth_topo_050714.tf

   and older DSN station frame kernels contain incompatible frame
   specification keywords that prevent the SPICE library's kernel data
   precedence algorithm from operating correctly.


   Associated PCK files
   --------------------

   For high-accuracy work, this kernel should be used together with a
   high-precision, binary earth PCK file.

      NAIF produces these kernels on a regular basis; they can be
      obtained via anonymous ftp from the NAIF server

         naif.jpl.nasa.gov

      or downloaded from the URL

         https://naif.jpl.nasa.gov/pub/naif/generic_kernels/pck/

      The PCK is located in the path

         pub/naif/generic_kernels/pck

      The file name is of the form

         earth_000101_yymmdd_yymmdd.bpc

      The first two dates are the file's start and stop times; the third
      is the epoch of the last datum in the EOP file:  data from
      this epoch forward are predicted.

      The file's coverage starts at a fixed date (currently chosen to
      be 2000 Jan. 1) and extends to the end of the predict region,
      which has a duration of roughly 3 months.

      The same location contains a file with identical contents and a fixed
      name:

         earth_latest_high_prec.bpc

      This file may be convenient for automated downloads.

      NAIF also provides a low-accuracy, long-term predict binary Earth PCK.
      See the file

          aareadme.txt

      in the location cited above for details.

   Associated SPK files
   --------------------

   This file is compatible with the SPK files

       earthstns_fx_201023.bsp       [reference frame: EARTH_FIXED]
       earthstns_itrf93_201023.bsp   [reference frame: ITRF93     ]

   both of which provide state vectors for each station covered by this file.

   Most applications will need to load one of the above SPK files in order to
   make use of this frame kernel.


   Data sources
   =====================================================================

   All data presented here are from reference [1].


   Reference Spheroid
   ------------------

   The reference bi-axial spheroid is defined by an equatorial and a
   polar radius. Calling these Re and Rp respectively, the flattening
   factor f is defined as

      f = ( Re - Rp ) / Re

   For the reference spheroid used by this file, the equatorial radius
   Re and inverse flattening factor 1/f are

      Re  = 6378137 m
      1/f = 298.2572236

   These parameters may be used to convert station locations at the epoch
   2003 JAN 01 TDB to geodetic coordinates matching those given in [1].

   The reference spheroid is used for derivation of the topocentric frame
   orientation Euler angles used in this file.

   The PCK file listed as a PINPOINT input below defines Earth radii
   consistent with these parameters. This PCK is not provided by NAIF, but
   the PCK may be created from the following text by prefixing a backslash
   character to the

       begindata
       begintext

   strings in the lines below:

      KPL/PCK

      begindata

         BODY399_RADII = ( 6378.137,  6378.137, 6356.752314247833 )

      begintext

   Users who create this file must be sure that the "ID word" KPL/PCK
   occupies the very first 7 characters of the file, and to add a carriage
   return at the end of the file. See the SPICE Toolkit documents "PCK
   Required Reading" and "Kernel Required Reading" for details of the SPICE
   text PCK format.


   Epoch
   -----

   The epoch associated with these data is given by the source as
   "2003.0."  The time variation of the data is slow enough so that
   specification of the time system is unimportant. However, in the
   creation of this file, the epoch is assumed to be

      2003 Jan 1 00:00:00 TDB

   At this epoch, the station positions are as given below.

   The movement of the stations due to tectonic plate motion is taken
   into account in creation of the frame definitions used in this file:
   the center locations and orientations of the reference frames are
   associated with station locations extrapolated to the date

      2020 October 23 00:00:00 TDB

   This extrapolation results in a small rotation of the frames relative
   to their orientations as given by the previous version of this kernel.


   Position data
   -------------

   Station locations in the ITRF93 frame at the specified epoch are:

       Antenna  Diameter   x (m)            y (m)           z (m)

       DSS 13   34m     -2351112.659    -4655530.636    +3660912.728
       DSS 14   70m     -2353621.420    -4641341.472    +3677052.318
       DSS 15   34m     -2353538.958    -4641649.429    +3676669.984 {3}
       DSS 24   34m     -2354906.711    -4646840.095    +3669242.325
       DSS 25   34m     -2355022.014    -4646953.204    +3669040.567
       DSS 26   34m     -2354890.797    -4647166.328    +3668871.755
       DSS 34   34m     -4461147.093    +2682439.239    -3674393.133 {1}
       DSS 35   34m     -4461273.090    +2682568.925    -3674152.093 {1}
       DSS 36   34m     -4461168.415    +2682814.657    -3674083.901 {1}
       DSS 43   70m     -4460894.917    +2682361.507    -3674748.152
       DSS 45   34m     -4460935.578    +2682765.661    -3674380.982 {3}
       DSS 53   34m     +4849339.965     -360658.246    +4114747.290 {2}
       DSS 54   34m     +4849434.488     -360723.8999   +4114618.835
       DSS 55   34m     +4849525.256     -360606.0932   +4114495.084
       DSS 56   34m     +4849421.679     -360549.659    +4114646.987
       DSS 63   70m     +4849092.518     -360180.3480   +4115109.251
       DSS 65   34m     +4849339.634     -360427.6637   +4114750.733

       Notes from [1]:

       {1} Position absolute accuracy estimated to be +/- 3cm (0.030m)
           (1-sigma) for each coordinate.

       {2} Position absolute accuracy estimated to be +/- 3m (3-sigma)
           for each coordinate.

       {3} Decommissioned. For historical reference only.


   Velocity data
   -------------

   Station velocities in Cartesian coordinates, with respect to the
   ITRF93 frame, are shown below.

       Reference epoch for plate motion: 01-JAN-2003 00:00

       Plate motion model, m/year

                                         X         Y         Z
       Goldstone:

          Stations numbered 1X & 2X   -0.0180    0.0065    -0.0038

       Canberra:

          Stations numbered 3X & 4X   -0.0335   -0.0041     0.0392

       Madrid:

          Stations numbered 5X & 6X   -0.0100    0.0242     0.0156


   Accuracy
   --------

   Location uncertainties at the 1 sigma level, for cylindrical coordinates,
   are given by Table 7 of reference [1].


   References
   ----------

   The data provided here are taken from the DSN document

      [1] "301 Coverage and Geometry." DSN No. 810-005, 301, Rev. M
          Issue Date: September 04, 2020. JPL D-19379; CL#20-3996.

          URL: https://deepspace.jpl.nasa.gov/dsndocs/810-005/301/301M.pdf


   Documentation for the SPICE Toolkit software is available here:

       URL:  https://naif.jpl.nasa.gov


   Kernel Data
   =====================================================================


   EARTH_FIXED alias mapping
   -------------------------

   Constant-offset frame definition for the frame alias EARTH_FIXED:
   EARTH_FIXED is mapped to ITRF93.


\begindata

   TKFRAME_EARTH_FIXED_RELATIVE = 'ITRF93'
   TKFRAME_EARTH_FIXED_SPEC     = 'MATRIX'
   TKFRAME_EARTH_FIXED_MATRIX   = ( 1   0   0
                                    0   1   0
                                    0   0   1 )

\begintext


   Kernel contents below were created by PINPOINT. The output includes
   the full PINPOINT setup file, including its comment area.


   PINPOINT output
   =====================================================================


   FILE: earth_topo_201023.tf

   This file was created by PINPOINT.

   PINPOINT Version 3.2.0 --- September 6, 2016
   PINPOINT RUN DATE/TIME:    2020-10-23T19:33:32
   PINPOINT DEFINITIONS FILE: earthstns_fx_201023.cmt
   PINPOINT PCK FILE:         earthstns_itrf93_201023.tpc
   PINPOINT SPK FILE:         bogus

   The input definitions file is appended to this
   file as a comment block.


   Body-name mapping follows:

\begindata

   NAIF_BODY_NAME                      += 'DSS-13'
   NAIF_BODY_CODE                      += 399013

   NAIF_BODY_NAME                      += 'DSS-14'
   NAIF_BODY_CODE                      += 399014

   NAIF_BODY_NAME                      += 'DSS-15'
   NAIF_BODY_CODE                      += 399015

   NAIF_BODY_NAME                      += 'DSS-24'
   NAIF_BODY_CODE                      += 399024

   NAIF_BODY_NAME                      += 'DSS-25'
   NAIF_BODY_CODE                      += 399025

   NAIF_BODY_NAME                      += 'DSS-26'
   NAIF_BODY_CODE                      += 399026

   NAIF_BODY_NAME                      += 'DSS-34'
   NAIF_BODY_CODE                      += 399034

   NAIF_BODY_NAME                      += 'DSS-35'
   NAIF_BODY_CODE                      += 399035

   NAIF_BODY_NAME                      += 'DSS-36'
   NAIF_BODY_CODE                      += 399036

   NAIF_BODY_NAME                      += 'DSS-43'
   NAIF_BODY_CODE                      += 399043

   NAIF_BODY_NAME                      += 'DSS-45'
   NAIF_BODY_CODE                      += 399045

   NAIF_BODY_NAME                      += 'DSS-53'
   NAIF_BODY_CODE                      += 399053

   NAIF_BODY_NAME                      += 'DSS-54'
   NAIF_BODY_CODE                      += 399054

   NAIF_BODY_NAME                      += 'DSS-55'
   NAIF_BODY_CODE                      += 399055

   NAIF_BODY_NAME                      += 'DSS-56'
   NAIF_BODY_CODE                      += 399056

   NAIF_BODY_NAME                      += 'DSS-63'
   NAIF_BODY_CODE                      += 399063

   NAIF_BODY_NAME                      += 'DSS-65'
   NAIF_BODY_CODE                      += 399065

\begintext


   Reference frame specifications follow:


   Topocentric frame DSS-13_TOPO

      The Z axis of this frame points toward the zenith.
      The X axis of this frame points North.

      Topocentric frame DSS-13_TOPO is centered at the
      site DSS-13, which at the epoch

          2020 OCT 23 00:00:00.000 TDB

      has Cartesian coordinates

         X (km):                 -0.2351112979575E+04
         Y (km):                 -0.4655530520237E+04
         Z (km):                  0.3660912660323E+04

      and planetodetic coordinates

         Longitude (deg):      -116.7944627147624
         Latitude  (deg):        35.2471635434595
         Altitude   (km):         0.1070439519876E+01

      These planetodetic coordinates are expressed relative to
      a reference spheroid having the dimensions

         Equatorial radius (km):  6.3781370000000E+03
         Polar radius      (km):  6.3567523142478E+03

      All of the above coordinates are relative to the frame EARTH_FIXED.


\begindata

   FRAME_DSS-13_TOPO                   =  1399013
   FRAME_1399013_NAME                  =  'DSS-13_TOPO'
   FRAME_1399013_CLASS                 =  4
   FRAME_1399013_CLASS_ID              =  1399013
   FRAME_1399013_CENTER                =  399013

   OBJECT_399013_FRAME                 =  'DSS-13_TOPO'

   TKFRAME_1399013_RELATIVE            =  'EARTH_FIXED'
   TKFRAME_1399013_SPEC                =  'ANGLES'
   TKFRAME_1399013_UNITS               =  'DEGREES'
   TKFRAME_1399013_AXES                =  ( 3, 2, 3 )
   TKFRAME_1399013_ANGLES              =  ( -243.2055372852376,
                                             -54.7528364565405,
                                             180.0000000000000 )


\begintext

   Topocentric frame DSS-14_TOPO

      The Z axis of this frame points toward the zenith.
      The X axis of this frame points North.

      Topocentric frame DSS-14_TOPO is centered at the
      site DSS-14, which at the epoch

          2020 OCT 23 00:00:00.000 TDB

      has Cartesian coordinates

         X (km):                 -0.2353621740575E+04
         Y (km):                 -0.4641341356237E+04
         Z (km):                  0.3677052250323E+04

      and planetodetic coordinates

         Longitude (deg):      -116.8895419347303
         Latitude  (deg):        35.4259001525718
         Altitude   (km):         0.1001385765773E+01

      These planetodetic coordinates are expressed relative to
      a reference spheroid having the dimensions

         Equatorial radius (km):  6.3781370000000E+03
         Polar radius      (km):  6.3567523142478E+03

      All of the above coordinates are relative to the frame EARTH_FIXED.


\begindata

   FRAME_DSS-14_TOPO                   =  1399014
   FRAME_1399014_NAME                  =  'DSS-14_TOPO'
   FRAME_1399014_CLASS                 =  4
   FRAME_1399014_CLASS_ID              =  1399014
   FRAME_1399014_CENTER                =  399014

   OBJECT_399014_FRAME                 =  'DSS-14_TOPO'

   TKFRAME_1399014_RELATIVE            =  'EARTH_FIXED'
   TKFRAME_1399014_SPEC                =  'ANGLES'
   TKFRAME_1399014_UNITS               =  'DEGREES'
   TKFRAME_1399014_AXES                =  ( 3, 2, 3 )
   TKFRAME_1399014_ANGLES              =  ( -243.1104580652697,
                                             -54.5740998474282,
                                             180.0000000000000 )


\begintext

   Topocentric frame DSS-15_TOPO

      The Z axis of this frame points toward the zenith.
      The X axis of this frame points North.

      Topocentric frame DSS-15_TOPO is centered at the
      site DSS-15, which at the epoch

          2020 OCT 23 00:00:00.000 TDB

      has Cartesian coordinates

         X (km):                 -0.2353539278575E+04
         Y (km):                 -0.4641649313237E+04
         Z (km):                  0.3676669916323E+04

      and planetodetic coordinates

         Longitude (deg):      -116.8871988309114
         Latitude  (deg):        35.4218525623111
         Altitude   (km):         0.9732064489353E+00

      These planetodetic coordinates are expressed relative to
      a reference spheroid having the dimensions

         Equatorial radius (km):  6.3781370000000E+03
         Polar radius      (km):  6.3567523142478E+03

      All of the above coordinates are relative to the frame EARTH_FIXED.


\begindata

   FRAME_DSS-15_TOPO                   =  1399015
   FRAME_1399015_NAME                  =  'DSS-15_TOPO'
   FRAME_1399015_CLASS                 =  4
   FRAME_1399015_CLASS_ID              =  1399015
   FRAME_1399015_CENTER                =  399015

   OBJECT_399015_FRAME                 =  'DSS-15_TOPO'

   TKFRAME_1399015_RELATIVE            =  'EARTH_FIXED'
   TKFRAME_1399015_SPEC                =  'ANGLES'
   TKFRAME_1399015_UNITS               =  'DEGREES'
   TKFRAME_1399015_AXES                =  ( 3, 2, 3 )
   TKFRAME_1399015_ANGLES              =  ( -243.1128011690886,
                                             -54.5781474376889,
                                             180.0000000000000 )


\begintext

   Topocentric frame DSS-24_TOPO

      The Z axis of this frame points toward the zenith.
      The X axis of this frame points North.

      Topocentric frame DSS-24_TOPO is centered at the
      site DSS-24, which at the epoch

          2020 OCT 23 00:00:00.000 TDB

      has Cartesian coordinates

         X (km):                 -0.2354907031575E+04
         Y (km):                 -0.4646839979237E+04
         Z (km):                  0.3669242257323E+04

      and planetodetic coordinates

         Longitude (deg):      -116.8747981085639
         Latitude  (deg):        35.3398920801982
         Altitude   (km):         0.9515064184845E+00

      These planetodetic coordinates are expressed relative to
      a reference spheroid having the dimensions

         Equatorial radius (km):  6.3781370000000E+03
         Polar radius      (km):  6.3567523142478E+03

      All of the above coordinates are relative to the frame EARTH_FIXED.


\begindata

   FRAME_DSS-24_TOPO                   =  1399024
   FRAME_1399024_NAME                  =  'DSS-24_TOPO'
   FRAME_1399024_CLASS                 =  4
   FRAME_1399024_CLASS_ID              =  1399024
   FRAME_1399024_CENTER                =  399024

   OBJECT_399024_FRAME                 =  'DSS-24_TOPO'

   TKFRAME_1399024_RELATIVE            =  'EARTH_FIXED'
   TKFRAME_1399024_SPEC                =  'ANGLES'
   TKFRAME_1399024_UNITS               =  'DEGREES'
   TKFRAME_1399024_AXES                =  ( 3, 2, 3 )
   TKFRAME_1399024_ANGLES              =  ( -243.1252018914361,
                                             -54.6601079198018,
                                             180.0000000000000 )


\begintext

   Topocentric frame DSS-25_TOPO

      The Z axis of this frame points toward the zenith.
      The X axis of this frame points North.

      Topocentric frame DSS-25_TOPO is centered at the
      site DSS-25, which at the epoch

          2020 OCT 23 00:00:00.000 TDB

      has Cartesian coordinates

         X (km):                 -0.2355022334575E+04
         Y (km):                 -0.4646953088237E+04
         Z (km):                  0.3669040499323E+04

      and planetodetic coordinates

         Longitude (deg):      -116.8753669250068
         Latitude  (deg):        35.3376112513319
         Altitude   (km):         0.9596290815794E+00

      These planetodetic coordinates are expressed relative to
      a reference spheroid having the dimensions

         Equatorial radius (km):  6.3781370000000E+03
         Polar radius      (km):  6.3567523142478E+03

      All of the above coordinates are relative to the frame EARTH_FIXED.


\begindata

   FRAME_DSS-25_TOPO                   =  1399025
   FRAME_1399025_NAME                  =  'DSS-25_TOPO'
   FRAME_1399025_CLASS                 =  4
   FRAME_1399025_CLASS_ID              =  1399025
   FRAME_1399025_CENTER                =  399025

   OBJECT_399025_FRAME                 =  'DSS-25_TOPO'

   TKFRAME_1399025_RELATIVE            =  'EARTH_FIXED'
   TKFRAME_1399025_SPEC                =  'ANGLES'
   TKFRAME_1399025_UNITS               =  'DEGREES'
   TKFRAME_1399025_AXES                =  ( 3, 2, 3 )
   TKFRAME_1399025_ANGLES              =  ( -243.1246330749932,
                                             -54.6623887486681,
                                             180.0000000000000 )


\begintext

   Topocentric frame DSS-26_TOPO

      The Z axis of this frame points toward the zenith.
      The X axis of this frame points North.

      Topocentric frame DSS-26_TOPO is centered at the
      site DSS-26, which at the epoch

          2020 OCT 23 00:00:00.000 TDB

      has Cartesian coordinates

         X (km):                 -0.2354891117575E+04
         Y (km):                 -0.4647166212237E+04
         Z (km):                  0.3668871687323E+04

      and planetodetic coordinates

         Longitude (deg):      -116.8730201399196
         Latitude  (deg):        35.3356884666268
         Altitude   (km):         0.9686879437011E+00

      These planetodetic coordinates are expressed relative to
      a reference spheroid having the dimensions

         Equatorial radius (km):  6.3781370000000E+03
         Polar radius      (km):  6.3567523142478E+03

      All of the above coordinates are relative to the frame EARTH_FIXED.


\begindata

   FRAME_DSS-26_TOPO                   =  1399026
   FRAME_1399026_NAME                  =  'DSS-26_TOPO'
   FRAME_1399026_CLASS                 =  4
   FRAME_1399026_CLASS_ID              =  1399026
   FRAME_1399026_CENTER                =  399026

   OBJECT_399026_FRAME                 =  'DSS-26_TOPO'

   TKFRAME_1399026_RELATIVE            =  'EARTH_FIXED'
   TKFRAME_1399026_SPEC                =  'ANGLES'
   TKFRAME_1399026_UNITS               =  'DEGREES'
   TKFRAME_1399026_AXES                =  ( 3, 2, 3 )
   TKFRAME_1399026_ANGLES              =  ( -243.1269798600804,
                                             -54.6643115333732,
                                             180.0000000000000 )


\begintext

   Topocentric frame DSS-34_TOPO

      The Z axis of this frame points toward the zenith.
      The X axis of this frame points North.

      Topocentric frame DSS-34_TOPO is centered at the
      site DSS-34, which at the epoch

          2020 OCT 23 00:00:00.000 TDB

      has Cartesian coordinates

         X (km):                 -0.4461147689626E+04
         Y (km):                  0.2682439165980E+04
         Z (km):                 -0.3674392434859E+04

      and planetodetic coordinates

         Longitude (deg):       148.9819684925768
         Latitude  (deg):       -35.3984712357100
         Altitude   (km):         0.6920025210140E+00

      These planetodetic coordinates are expressed relative to
      a reference spheroid having the dimensions

         Equatorial radius (km):  6.3781370000000E+03
         Polar radius      (km):  6.3567523142478E+03

      All of the above coordinates are relative to the frame EARTH_FIXED.


\begindata

   FRAME_DSS-34_TOPO                   =  1399034
   FRAME_1399034_NAME                  =  'DSS-34_TOPO'
   FRAME_1399034_CLASS                 =  4
   FRAME_1399034_CLASS_ID              =  1399034
   FRAME_1399034_CENTER                =  399034

   OBJECT_399034_FRAME                 =  'DSS-34_TOPO'

   TKFRAME_1399034_RELATIVE            =  'EARTH_FIXED'
   TKFRAME_1399034_SPEC                =  'ANGLES'
   TKFRAME_1399034_UNITS               =  'DEGREES'
   TKFRAME_1399034_AXES                =  ( 3, 2, 3 )
   TKFRAME_1399034_ANGLES              =  ( -148.9819684925768,
                                            -125.3984712357100,
                                             180.0000000000000 )


\begintext

   Topocentric frame DSS-35_TOPO

      The Z axis of this frame points toward the zenith.
      The X axis of this frame points North.

      Topocentric frame DSS-35_TOPO is centered at the
      site DSS-35, which at the epoch

          2020 OCT 23 00:00:00.000 TDB

      has Cartesian coordinates

         X (km):                 -0.4461273686626E+04
         Y (km):                  0.2682568851980E+04
         Z (km):                 -0.3674151394859E+04

      and planetodetic coordinates

         Longitude (deg):       148.9814598395941
         Latitude  (deg):       -35.3957879118433
         Altitude   (km):         0.6948787660279E+00

      These planetodetic coordinates are expressed relative to
      a reference spheroid having the dimensions

         Equatorial radius (km):  6.3781370000000E+03
         Polar radius      (km):  6.3567523142478E+03

      All of the above coordinates are relative to the frame EARTH_FIXED.


\begindata

   FRAME_DSS-35_TOPO                   =  1399035
   FRAME_1399035_NAME                  =  'DSS-35_TOPO'
   FRAME_1399035_CLASS                 =  4
   FRAME_1399035_CLASS_ID              =  1399035
   FRAME_1399035_CENTER                =  399035

   OBJECT_399035_FRAME                 =  'DSS-35_TOPO'

   TKFRAME_1399035_RELATIVE            =  'EARTH_FIXED'
   TKFRAME_1399035_SPEC                =  'ANGLES'
   TKFRAME_1399035_UNITS               =  'DEGREES'
   TKFRAME_1399035_AXES                =  ( 3, 2, 3 )
   TKFRAME_1399035_ANGLES              =  ( -148.9814598395941,
                                            -125.3957879118433,
                                             180.0000000000000 )


\begintext

   Topocentric frame DSS-36_TOPO

      The Z axis of this frame points toward the zenith.
      The X axis of this frame points North.

      Topocentric frame DSS-36_TOPO is centered at the
      site DSS-36, which at the epoch

          2020 OCT 23 00:00:00.000 TDB

      has Cartesian coordinates

         X (km):                 -0.4461169011626E+04
         Y (km):                  0.2682814583980E+04
         Z (km):                 -0.3674083202859E+04

      and planetodetic coordinates

         Longitude (deg):       148.9785483057047
         Latitude  (deg):       -35.3950941601377
         Altitude   (km):         0.6854849512296E+00

      These planetodetic coordinates are expressed relative to
      a reference spheroid having the dimensions

         Equatorial radius (km):  6.3781370000000E+03
         Polar radius      (km):  6.3567523142478E+03

      All of the above coordinates are relative to the frame EARTH_FIXED.


\begindata

   FRAME_DSS-36_TOPO                   =  1399036
   FRAME_1399036_NAME                  =  'DSS-36_TOPO'
   FRAME_1399036_CLASS                 =  4
   FRAME_1399036_CLASS_ID              =  1399036
   FRAME_1399036_CENTER                =  399036

   OBJECT_399036_FRAME                 =  'DSS-36_TOPO'

   TKFRAME_1399036_RELATIVE            =  'EARTH_FIXED'
   TKFRAME_1399036_SPEC                =  'ANGLES'
   TKFRAME_1399036_UNITS               =  'DEGREES'
   TKFRAME_1399036_AXES                =  ( 3, 2, 3 )
   TKFRAME_1399036_ANGLES              =  ( -148.9785483057047,
                                            -125.3950941601377,
                                             180.0000000000000 )


\begintext

   Topocentric frame DSS-43_TOPO

      The Z axis of this frame points toward the zenith.
      The X axis of this frame points North.

      Topocentric frame DSS-43_TOPO is centered at the
      site DSS-43, which at the epoch

          2020 OCT 23 00:00:00.000 TDB

      has Cartesian coordinates

         X (km):                 -0.4460895513626E+04
         Y (km):                  0.2682361433980E+04
         Z (km):                 -0.3674747453859E+04

      and planetodetic coordinates

         Longitude (deg):       148.9812713832932
         Latitude  (deg):       -35.4024166339779
         Altitude   (km):         0.6888490972130E+00

      These planetodetic coordinates are expressed relative to
      a reference spheroid having the dimensions

         Equatorial radius (km):  6.3781370000000E+03
         Polar radius      (km):  6.3567523142478E+03

      All of the above coordinates are relative to the frame EARTH_FIXED.


\begindata

   FRAME_DSS-43_TOPO                   =  1399043
   FRAME_1399043_NAME                  =  'DSS-43_TOPO'
   FRAME_1399043_CLASS                 =  4
   FRAME_1399043_CLASS_ID              =  1399043
   FRAME_1399043_CENTER                =  399043

   OBJECT_399043_FRAME                 =  'DSS-43_TOPO'

   TKFRAME_1399043_RELATIVE            =  'EARTH_FIXED'
   TKFRAME_1399043_SPEC                =  'ANGLES'
   TKFRAME_1399043_UNITS               =  'DEGREES'
   TKFRAME_1399043_AXES                =  ( 3, 2, 3 )
   TKFRAME_1399043_ANGLES              =  ( -148.9812713832932,
                                            -125.4024166339779,
                                             180.0000000000000 )


\begintext

   Topocentric frame DSS-45_TOPO

      The Z axis of this frame points toward the zenith.
      The X axis of this frame points North.

      Topocentric frame DSS-45_TOPO is centered at the
      site DSS-45, which at the epoch

          2020 OCT 23 00:00:00.000 TDB

      has Cartesian coordinates

         X (km):                 -0.4460936174626E+04
         Y (km):                  0.2682765587980E+04
         Z (km):                 -0.3674380283859E+04

      and planetodetic coordinates

         Longitude (deg):       148.9776897067879
         Latitude  (deg):       -35.3984500826733
         Altitude   (km):         0.6743286617334E+00

      These planetodetic coordinates are expressed relative to
      a reference spheroid having the dimensions

         Equatorial radius (km):  6.3781370000000E+03
         Polar radius      (km):  6.3567523142478E+03

      All of the above coordinates are relative to the frame EARTH_FIXED.


\begindata

   FRAME_DSS-45_TOPO                   =  1399045
   FRAME_1399045_NAME                  =  'DSS-45_TOPO'
   FRAME_1399045_CLASS                 =  4
   FRAME_1399045_CLASS_ID              =  1399045
   FRAME_1399045_CENTER                =  399045

   OBJECT_399045_FRAME                 =  'DSS-45_TOPO'

   TKFRAME_1399045_RELATIVE            =  'EARTH_FIXED'
   TKFRAME_1399045_SPEC                =  'ANGLES'
   TKFRAME_1399045_UNITS               =  'DEGREES'
   TKFRAME_1399045_AXES                =  ( 3, 2, 3 )
   TKFRAME_1399045_ANGLES              =  ( -148.9776897067879,
                                            -125.3984500826733,
                                             180.0000000000000 )


\begintext

   Topocentric frame DSS-53_TOPO

      The Z axis of this frame points toward the zenith.
      The X axis of this frame points North.

      Topocentric frame DSS-53_TOPO is centered at the
      site DSS-53, which at the epoch

          2020 OCT 23 00:00:00.000 TDB

      has Cartesian coordinates

         X (km):                  0.4849339786903E+04
         Y (km):                 -0.3606578150048E+03
         Z (km):                  0.4114747567832E+04

      and planetodetic coordinates

         Longitude (deg):        -4.2534030911179
         Latitude  (deg):        40.4270841356896
         Altitude   (km):         0.8449081257927E+00

      These planetodetic coordinates are expressed relative to
      a reference spheroid having the dimensions

         Equatorial radius (km):  6.3781370000000E+03
         Polar radius      (km):  6.3567523142478E+03

      All of the above coordinates are relative to the frame EARTH_FIXED.


\begindata

   FRAME_DSS-53_TOPO                   =  1399053
   FRAME_1399053_NAME                  =  'DSS-53_TOPO'
   FRAME_1399053_CLASS                 =  4
   FRAME_1399053_CLASS_ID              =  1399053
   FRAME_1399053_CENTER                =  399053

   OBJECT_399053_FRAME                 =  'DSS-53_TOPO'

   TKFRAME_1399053_RELATIVE            =  'EARTH_FIXED'
   TKFRAME_1399053_SPEC                =  'ANGLES'
   TKFRAME_1399053_UNITS               =  'DEGREES'
   TKFRAME_1399053_AXES                =  ( 3, 2, 3 )
   TKFRAME_1399053_ANGLES              =  ( -355.7465969088821,
                                             -49.5729158643104,
                                             180.0000000000000 )


\begintext

   Topocentric frame DSS-54_TOPO

      The Z axis of this frame points toward the zenith.
      The X axis of this frame points North.

      Topocentric frame DSS-54_TOPO is centered at the
      site DSS-54, which at the epoch

          2020 OCT 23 00:00:00.000 TDB

      has Cartesian coordinates

         X (km):                  0.4849434309903E+04
         Y (km):                 -0.3607234689048E+03
         Z (km):                  0.4114619112832E+04

      and planetodetic coordinates

         Longitude (deg):        -4.2540919192841
         Latitude  (deg):        40.4256248061962
         Altitude   (km):         0.8370724668605E+00

      These planetodetic coordinates are expressed relative to
      a reference spheroid having the dimensions

         Equatorial radius (km):  6.3781370000000E+03
         Polar radius      (km):  6.3567523142478E+03

      All of the above coordinates are relative to the frame EARTH_FIXED.


\begindata

   FRAME_DSS-54_TOPO                   =  1399054
   FRAME_1399054_NAME                  =  'DSS-54_TOPO'
   FRAME_1399054_CLASS                 =  4
   FRAME_1399054_CLASS_ID              =  1399054
   FRAME_1399054_CENTER                =  399054

   OBJECT_399054_FRAME                 =  'DSS-54_TOPO'

   TKFRAME_1399054_RELATIVE            =  'EARTH_FIXED'
   TKFRAME_1399054_SPEC                =  'ANGLES'
   TKFRAME_1399054_UNITS               =  'DEGREES'
   TKFRAME_1399054_AXES                =  ( 3, 2, 3 )
   TKFRAME_1399054_ANGLES              =  ( -355.7459080807159,
                                             -49.5743751938038,
                                             180.0000000000000 )


\begintext

   Topocentric frame DSS-55_TOPO

      The Z axis of this frame points toward the zenith.
      The X axis of this frame points North.

      Topocentric frame DSS-55_TOPO is centered at the
      site DSS-55, which at the epoch

          2020 OCT 23 00:00:00.000 TDB

      has Cartesian coordinates

         X (km):                  0.4849525077903E+04
         Y (km):                 -0.3606056622048E+03
         Z (km):                  0.4114495361832E+04

      and planetodetic coordinates

         Longitude (deg):        -4.2526283911759
         Latitude  (deg):        40.4242990309862
         Altitude   (km):         0.8190819258363E+00

      These planetodetic coordinates are expressed relative to
      a reference spheroid having the dimensions

         Equatorial radius (km):  6.3781370000000E+03
         Polar radius      (km):  6.3567523142478E+03

      All of the above coordinates are relative to the frame EARTH_FIXED.


\begindata

   FRAME_DSS-55_TOPO                   =  1399055
   FRAME_1399055_NAME                  =  'DSS-55_TOPO'
   FRAME_1399055_CLASS                 =  4
   FRAME_1399055_CLASS_ID              =  1399055
   FRAME_1399055_CENTER                =  399055

   OBJECT_399055_FRAME                 =  'DSS-55_TOPO'

   TKFRAME_1399055_RELATIVE            =  'EARTH_FIXED'
   TKFRAME_1399055_SPEC                =  'ANGLES'
   TKFRAME_1399055_UNITS               =  'DEGREES'
   TKFRAME_1399055_AXES                =  ( 3, 2, 3 )
   TKFRAME_1399055_ANGLES              =  ( -355.7473716088242,
                                             -49.5757009690138,
                                             180.0000000000000 )


\begintext

   Topocentric frame DSS-56_TOPO

      The Z axis of this frame points toward the zenith.
      The X axis of this frame points North.

      Topocentric frame DSS-56_TOPO is centered at the
      site DSS-56, which at the epoch

          2020 OCT 23 00:00:00.000 TDB

      has Cartesian coordinates

         X (km):                  0.4849421500903E+04
         Y (km):                 -0.3605492280048E+03
         Z (km):                  0.4114647264832E+04

      and planetodetic coordinates

         Longitude (deg):        -4.2520557858121
         Latitude  (deg):        40.4259678122023
         Altitude   (km):         0.8357671690735E+00

      These planetodetic coordinates are expressed relative to
      a reference spheroid having the dimensions

         Equatorial radius (km):  6.3781370000000E+03
         Polar radius      (km):  6.3567523142478E+03

      All of the above coordinates are relative to the frame EARTH_FIXED.


\begindata

   FRAME_DSS-56_TOPO                   =  1399056
   FRAME_1399056_NAME                  =  'DSS-56_TOPO'
   FRAME_1399056_CLASS                 =  4
   FRAME_1399056_CLASS_ID              =  1399056
   FRAME_1399056_CENTER                =  399056

   OBJECT_399056_FRAME                 =  'DSS-56_TOPO'

   TKFRAME_1399056_RELATIVE            =  'EARTH_FIXED'
   TKFRAME_1399056_SPEC                =  'ANGLES'
   TKFRAME_1399056_UNITS               =  'DEGREES'
   TKFRAME_1399056_AXES                =  ( 3, 2, 3 )
   TKFRAME_1399056_ANGLES              =  ( -355.7479442141879,
                                             -49.5740321877977,
                                             180.0000000000000 )


\begintext

   Topocentric frame DSS-63_TOPO

      The Z axis of this frame points toward the zenith.
      The X axis of this frame points North.

      Topocentric frame DSS-63_TOPO is centered at the
      site DSS-63, which at the epoch

          2020 OCT 23 00:00:00.000 TDB

      has Cartesian coordinates

         X (km):                  0.4849092339903E+04
         Y (km):                 -0.3601799170048E+03
         Z (km):                  0.4115109528832E+04

      and planetodetic coordinates

         Longitude (deg):        -4.2480036330327
         Latitude  (deg):        40.4312128778313
         Altitude   (km):         0.8648381805445E+00

      These planetodetic coordinates are expressed relative to
      a reference spheroid having the dimensions

         Equatorial radius (km):  6.3781370000000E+03
         Polar radius      (km):  6.3567523142478E+03

      All of the above coordinates are relative to the frame EARTH_FIXED.


\begindata

   FRAME_DSS-63_TOPO                   =  1399063
   FRAME_1399063_NAME                  =  'DSS-63_TOPO'
   FRAME_1399063_CLASS                 =  4
   FRAME_1399063_CLASS_ID              =  1399063
   FRAME_1399063_CENTER                =  399063

   OBJECT_399063_FRAME                 =  'DSS-63_TOPO'

   TKFRAME_1399063_RELATIVE            =  'EARTH_FIXED'
   TKFRAME_1399063_SPEC                =  'ANGLES'
   TKFRAME_1399063_UNITS               =  'DEGREES'
   TKFRAME_1399063_AXES                =  ( 3, 2, 3 )
   TKFRAME_1399063_ANGLES              =  ( -355.7519963669673,
                                             -49.5687871221687,
                                             180.0000000000000 )


\begintext

   Topocentric frame DSS-65_TOPO

      The Z axis of this frame points toward the zenith.
      The X axis of this frame points North.

      Topocentric frame DSS-65_TOPO is centered at the
      site DSS-65, which at the epoch

          2020 OCT 23 00:00:00.000 TDB

      has Cartesian coordinates

         X (km):                  0.4849339455903E+04
         Y (km):                 -0.3604272327048E+03
         Z (km):                  0.4114751010832E+04

      and planetodetic coordinates

         Longitude (deg):        -4.2506939876788
         Latitude  (deg):        40.4272094906850
         Altitude   (km):         0.8338753136762E+00

      These planetodetic coordinates are expressed relative to
      a reference spheroid having the dimensions

         Equatorial radius (km):  6.3781370000000E+03
         Polar radius      (km):  6.3567523142478E+03

      All of the above coordinates are relative to the frame EARTH_FIXED.


\begindata

   FRAME_DSS-65_TOPO                   =  1399065
   FRAME_1399065_NAME                  =  'DSS-65_TOPO'
   FRAME_1399065_CLASS                 =  4
   FRAME_1399065_CLASS_ID              =  1399065
   FRAME_1399065_CENTER                =  399065

   OBJECT_399065_FRAME                 =  'DSS-65_TOPO'

   TKFRAME_1399065_RELATIVE            =  'EARTH_FIXED'
   TKFRAME_1399065_SPEC                =  'ANGLES'
   TKFRAME_1399065_UNITS               =  'DEGREES'
   TKFRAME_1399065_AXES                =  ( 3, 2, 3 )
   TKFRAME_1399065_ANGLES              =  ( -355.7493060123212,
                                             -49.5727905093150,
                                             180.0000000000000 )

\begintext


Definitions file earthstns_fx_201023.cmt
--------------------------------------------------------------------------------


   SPK for DSN Station Locations
   =====================================================================

   Original file name:                   earthstns_fx_201023.bsp
   Creation date:                        2020 October 23 11:35
   Created by:                           Nat Bachman  (NAIF/JPL)


   Introduction
   =====================================================================

   This file provides geocentric states---locations and velocities---for the
   set of DSN stations cited in the list below under "Position Data."  Station
   position vectors point from the earth's barycenter to the stations. Station
   velocities are estimates of the derivatives with respect to time of these
   vectors; in this file, velocities are constant. Station velocities have
   magnitudes on the order of a few cm/year.

   The states in this file are given relative to the terrestrial reference
   frame ITRF93. In the interest of flexibility, in this file the reference
   frame is labeled with the alias 'EARTH_FIXED'. Any application using this
   file must map the alias 'EARTH_FIXED' to either 'ITRF93' or 'IAU_EARTH'.
   See the discussion below under "Reference frame alias" for details.

   This SPK file has a companion file

      earthstns_itrf93_201023.bsp

   which differs from this one only in that it uses the reference frame name
   'ITRF93'. For high-accuracy work, the companion file is recommended (on the
   basis of ease of use).


   Revision description
   --------------------

   This kernel contains data from a single, current source: [1].

   This kernel supersedes the kernel

      earthstns_fx_050714.bsp

   The set of stations covered by this file has changed from that of the file

      earthstns_fx_050714.bsp

   as follows:

      Deleted stations (not present in current file):

         PARKES
         DSS-12
         DSS-16
         DSS-17
         DSS-23
         DSS-27
         DSS-28
         DSS-33
         DSS-42
         DSS-46
         DSS-49 (alternate name for PARKES)
         DSS-61
         DSS-64 (alternate name for DSS-65)
         DSS-66

      Other deleted data:

         Position data for the old location of DSS-65 prior to 2005 July 3
         TDB are no longer included. This file extrapolates current data
         backward in time for the entire time period covered by this file.
         The superseded file

            earthstns_fx_050714.bsp

         should be used to obtain the old location of DSS-65 for dates prior
         to 2005 July 3 TDB.

      Added stations:

         DSS-35
         DSS-36

      Name transfers---name now refers to a new station:

         DSS-53


   Planned updates
   ---------------

   Updates will be be made to keep this file in sync with updates to the
   source document [1].

   Values for DSS-53 are expected to be updated. Values for DSS-23 will be
   added. There is no schedule for these changes at this time.


   Using this kernel
   =====================================================================

   Kernel loading
   --------------

   In order for a SPICE-based program to make use of this kernel, the
   kernel must be loaded via the SPICE routine FURNSH.  If you are
   running application software created by a third party, see the
   documentation for that software for instructions on kernel
   management.

   See also "Associated frame kernels" and "Associated PCK files"
   below.

   Users requiring data from superseded SPK versions can load those files
   in addition to this one. In the case of conflicting data, data from SPKs
   loaded later take precedence over SPKs loaded earlier.


   Reference frame alias
   ---------------------

   This kernel uses the alias 'EARTH_FIXED' to designate the reference frame
   relative to which the data in this kernel are specified. In order for this
   kernel to be usable, the alias must be mapped to the name of a supported
   terrestrial frame. For high-accuracy work, the frame name 'ITRF93' should
   be used. In some situations, for example when low accuracy, long term
   predictions are desired, it may be convenient to map 'EARTH_FIXED'
   to 'IAU_EARTH'.

   To map the alias, an application must load a text kernel containing
   assignments as shown below.

      begintext

      Map 'EARTH_FIXED' to ITRF93.  (To map to IAU_EARTH, substitute
      'IAU_EARTH' for 'ITRF93' below.)

      begindata

         TKFRAME_EARTH_FIXED_RELATIVE = 'ITRF93'
         TKFRAME_EARTH_FIXED_SPEC     = 'MATRIX'
         TKFRAME_EARTH_FIXED_MATRIX   = ( 1   0   0
                                          0   1   0
                                          0   0   1 )

      begintext


   See the Frames Required Reading for details.

   Associated PCK files
   --------------------

   For high-accuracy work, this kernel should be used together with a
   high-precision, binary earth PCK file.

      NAIF produces these kernels on a regular basis; they can be
      obtained via anonymous ftp from the NAIF server

         naif.jpl.nasa.gov

      or downloaded from the URL

         https://naif.jpl.nasa.gov/pub/naif/generic_kernels/pck/

      The PCK is located in the path

         pub/naif/generic_kernels/pck

      The file name is of the form

         earth_000101_yymmdd_yymmdd.bpc

      The first two dates are the file's start and stop times; the third
      is the epoch of the last datum in the EOP file:  data from
      this epoch forward are predicted.

      The file's coverage starts at a fixed date (currently chosen to
      be 2000 Jan. 1) and extends to the end of the predict region,
      which has a duration of roughly 3 months.

      The same location contains a file with identical contents and a fixed
      name:

         earth_latest_high_prec.bpc

      This file may be convenient for automated downloads.

      NAIF also provides a low-accuracy, long-term predict binary Earth PCK.
      See the file

          aareadme.txt

      in the location cited above for details.


   Associated frame kernels
   ------------------------

   The frame kernel having (original) file name

      earth_topo_201023.tf

   defines topocentric reference frames associated with each of the stations
   covered by this file. That kernel supports computations such as finding the
   azimuth and elevation of a target as seen from a specified station.


   Data sources
   =====================================================================

   All data presented here are from reference [1].


   Reference Spheroid
   ------------------

   The reference bi-axial spheroid is defined by an equatorial and a
   polar radius. Calling these Re and Rp respectively, the flattening
   factor f is defined as

      f = ( Re - Rp ) / Re

   For the reference spheroid used by this file, the equatorial radius
   Re and inverse flattening factor 1/f are

      Re  = 6378137 m
      1/f = 298.2572236

   The reference spheroid is not used for the creation of this SPK file
   but is used to create the associated frame kernel named above.


   Epoch
   -----

   The epoch associated with these data is given by the source as
   "2003.0."  The time variation of the data is slow enough so that
   specification of the time system is unimportant. However, in the
   creation of this file, the epoch is assumed to be

      2003 Jan 1 00:00:00 TDB

   At this epoch, the station positions are as given below.


   Position data
   -------------

   Station locations in the ITRF93 frame at the specified epoch are:

       Antenna  Diameter   x (m)            y (m)           z (m)

       DSS 13   34m     -2351112.659    -4655530.636    +3660912.728
       DSS 14   70m     -2353621.420    -4641341.472    +3677052.318
       DSS 15   34m     -2353538.958    -4641649.429    +3676669.984 {3}
       DSS 24   34m     -2354906.711    -4646840.095    +3669242.325
       DSS 25   34m     -2355022.014    -4646953.204    +3669040.567
       DSS 26   34m     -2354890.797    -4647166.328    +3668871.755
       DSS 34   34m     -4461147.093    +2682439.239    -3674393.133 {1}
       DSS 35   34m     -4461273.090    +2682568.925    -3674152.093 {1}
       DSS 36   34m     -4461168.415    +2682814.657    -3674083.901 {1}
       DSS 43   70m     -4460894.917    +2682361.507    -3674748.152
       DSS 45   34m     -4460935.578    +2682765.661    -3674380.982 {3}
       DSS 53   34m     +4849339.965     -360658.246    +4114747.290 {2}
       DSS 54   34m     +4849434.488     -360723.8999   +4114618.835
       DSS 55   34m     +4849525.256     -360606.0932   +4114495.084
       DSS 56   34m     +4849421.679     -360549.659    +4114646.987
       DSS 63   70m     +4849092.518     -360180.3480   +4115109.251
       DSS 65   34m     +4849339.634     -360427.6637   +4114750.733

       Notes from [1]:

       {1} Position absolute accuracy estimated to be +/- 3cm (0.030m)
           (1-sigma) for each coordinate.

       {2} Position absolute accuracy estimated to be +/- 3m (3-sigma)
           for each coordinate.

       {3} Decommissioned. For historical reference only.


   Velocity data
   -------------

   Station velocities in Cartesian coordinates, with respect to the
   ITRF93 frame, are shown below.

       Reference epoch for plate motion: 01-JAN-2003 00:00

       Plate motion model, m/year

                                         X         Y         Z
       Goldstone:

          Stations numbered 1X & 2X   -0.0180    0.0065    -0.0038

       Canberra:

          Stations numbered 3X & 4X   -0.0335   -0.0041     0.0392

       Madrid:

          Stations numbered 5X & 6X   -0.0100    0.0242     0.0156


   Accuracy
   --------

   Location uncertainties at the 1 sigma level, for cylindrical coordinates,
   are given by Table 7 of reference [1].


   References
   ----------

   The data provided here are taken from the DSN document

      [1] "301 Coverage and Geometry." DSN No. 810-005, 301, Rev. M
          Issue Date: September 04, 2020. JPL D-19379; CL#20-3996.

          URL: https://deepspace.jpl.nasa.gov/dsndocs/810-005/301/301M.pdf


   Documentation for the SPICE Toolkit software is available here:

       URL:  https://naif.jpl.nasa.gov


   Kernel Data
   =====================================================================

begintext

   Station locations and velocities, along with topocentric reference frame
   specification parameters:

begindata


   SITES            +=       'DSS-13'
   DSS-13_FRAME      =       'EARTH_FIXED'
   DSS-13_CENTER     =       399
   DSS-13_IDCODE     =       399013
   DSS-13_EPOCH      =       @2003-JAN-01/00:00
   DSS-13_BOUNDS     =    (  @1950-JAN-01/00:00,  @2150-JAN-01/00:00  )
   DSS-13_XYZ        =    ( -2351.112659    -4655.530636    +3660.912728 )
   DSS-13_DXYZ       =    (    -0.0180          0.0065         -0.0038   )
   DSS-13_TOPO_EPOCH =       @2020-OCT-23/00:00
   DSS-13_UP         =       'Z'
   DSS-13_NORTH      =       'X'


   SITES            +=       'DSS-14'
   DSS-14_FRAME      =       'EARTH_FIXED'
   DSS-14_CENTER     =       399
   DSS-14_IDCODE     =       399014
   DSS-14_EPOCH      =       @2003-JAN-01/00:00
   DSS-14_BOUNDS     =    (  @1950-JAN-01/00:00,  @2150-JAN-01/00:00  )
   DSS-14_XYZ        =    ( -2353.621420    -4641.341472    +3677.052318 )
   DSS-14_DXYZ       =    (    -0.0180          0.0065         -0.0038   )
   DSS-14_TOPO_EPOCH =       @2020-OCT-23/00:00
   DSS-14_UP         =       'Z'
   DSS-14_NORTH      =       'X'


   SITES            +=       'DSS-15'
   DSS-15_FRAME      =       'EARTH_FIXED'
   DSS-15_CENTER     =       399
   DSS-15_IDCODE     =       399015
   DSS-15_EPOCH      =       @2003-JAN-01/00:00
   DSS-15_BOUNDS     =    (  @1950-JAN-01/00:00,  @2150-JAN-01/00:00  )
   DSS-15_XYZ        =    ( -2353.538958    -4641.649429    +3676.669984 )
   DSS-15_DXYZ       =    (    -0.0180          0.0065         -0.0038   )
   DSS-15_TOPO_EPOCH =       @2020-OCT-23/00:00
   DSS-15_UP         =       'Z'
   DSS-15_NORTH      =       'X'


   SITES            +=       'DSS-24'
   DSS-24_FRAME      =       'EARTH_FIXED'
   DSS-24_CENTER     =       399
   DSS-24_IDCODE     =       399024
   DSS-24_EPOCH      =       @2003-JAN-01/00:00
   DSS-24_BOUNDS     =    (  @1950-JAN-01/00:00,  @2150-JAN-01/00:00  )
   DSS-24_XYZ        =    ( -2354.906711    -4646.840095    +3669.242325 )
   DSS-24_DXYZ       =    (    -0.0180          0.0065         -0.0038   )
   DSS-24_TOPO_EPOCH =       @2020-OCT-23/00:00
   DSS-24_UP         =       'Z'
   DSS-24_NORTH      =       'X'


   SITES            +=       'DSS-25'
   DSS-25_FRAME      =       'EARTH_FIXED'
   DSS-25_CENTER     =       399
   DSS-25_IDCODE     =       399025
   DSS-25_EPOCH      =       @2003-JAN-01/00:00
   DSS-25_BOUNDS     =    (  @1950-JAN-01/00:00,  @2150-JAN-01/00:00  )
   DSS-25_XYZ        =    ( -2355.022014    -4646.953204    +3669.040567 )
   DSS-25_DXYZ       =    (    -0.0180          0.0065         -0.0038   )
   DSS-25_TOPO_EPOCH =       @2020-OCT-23/00:00
   DSS-25_UP         =       'Z'
   DSS-25_NORTH      =       'X'


   SITES            +=       'DSS-26'
   DSS-26_FRAME      =       'EARTH_FIXED'
   DSS-26_CENTER     =       399
   DSS-26_IDCODE     =       399026
   DSS-26_EPOCH      =       @2003-JAN-01/00:00
   DSS-26_BOUNDS     =    (  @1950-JAN-01/00:00,  @2150-JAN-01/00:00  )
   DSS-26_XYZ        =    ( -2354.890797    -4647.166328    +3668.871755 )
   DSS-26_DXYZ       =    (    -0.0180          0.0065         -0.0038   )
   DSS-26_TOPO_EPOCH =       @2020-OCT-23/00:00
   DSS-26_UP         =       'Z'
   DSS-26_NORTH      =       'X'


   SITES            +=       'DSS-34'
   DSS-34_FRAME      =       'EARTH_FIXED'
   DSS-34_CENTER     =       399
   DSS-34_IDCODE     =       399034
   DSS-34_EPOCH      =       @2003-JAN-01/00:00
   DSS-34_BOUNDS     =    (  @1950-JAN-01/00:00,  @2150-JAN-01/00:00  )
   DSS-34_XYZ        =    ( -4461.147093    +2682.439239    -3674.393133 )
   DSS-34_DXYZ       =    (    -0.0335         -0.0041          0.0392   )
   DSS-34_TOPO_EPOCH =       @2020-OCT-23/00:00
   DSS-34_UP         =       'Z'
   DSS-34_NORTH      =       'X'


   SITES            +=       'DSS-35'
   DSS-35_FRAME      =       'EARTH_FIXED'
   DSS-35_CENTER     =       399
   DSS-35_IDCODE     =       399035
   DSS-35_EPOCH      =       @2003-JAN-01/00:00
   DSS-35_BOUNDS     =    (  @1950-JAN-01/00:00,  @2150-JAN-01/00:00  )
   DSS-35_XYZ        =    ( -4461.273090    +2682.568925    -3674.152093 )
   DSS-35_DXYZ       =    (    -0.0335         -0.0041          0.0392   )
   DSS-35_TOPO_EPOCH =       @2020-OCT-23/00:00
   DSS-35_UP         =       'Z'
   DSS-35_NORTH      =       'X'


   SITES            +=       'DSS-36'
   DSS-36_FRAME      =       'EARTH_FIXED'
   DSS-36_CENTER     =       399
   DSS-36_IDCODE     =       399036
   DSS-36_EPOCH      =       @2003-JAN-01/00:00
   DSS-36_BOUNDS     =    (  @1950-JAN-01/00:00,  @2150-JAN-01/00:00  )
   DSS-36_XYZ        =    ( -4461.168415    +2682.814657    -3674.083901 )
   DSS-36_DXYZ       =    (    -0.0335         -0.0041          0.0392   )
   DSS-36_TOPO_EPOCH =       @2020-OCT-23/00:00
   DSS-36_UP         =       'Z'
   DSS-36_NORTH      =       'X'


   SITES            +=       'DSS-43'
   DSS-43_FRAME      =       'EARTH_FIXED'
   DSS-43_CENTER     =       399
   DSS-43_IDCODE     =       399043
   DSS-43_EPOCH      =       @2003-JAN-01/00:00
   DSS-43_BOUNDS     =    (  @1950-JAN-01/00:00,  @2150-JAN-01/00:00  )
   DSS-43_XYZ        =    (   -4460.894917    +2682.361507    -3674.748152 )
   DSS-43_DXYZ       =    (      -0.0335         -0.0041          0.0392   )
   DSS-43_TOPO_EPOCH =       @2020-OCT-23/00:00
   DSS-43_UP         =       'Z'
   DSS-43_NORTH      =       'X'


   SITES            +=       'DSS-45'
   DSS-45_FRAME      =       'EARTH_FIXED'
   DSS-45_CENTER     =       399
   DSS-45_IDCODE     =       399045
   DSS-45_EPOCH      =       @2003-JAN-01/00:00
   DSS-45_BOUNDS     =    (  @1950-JAN-01/00:00,  @2150-JAN-01/00:00  )
   DSS-45_XYZ        =    (  -4460.935578    +2682.765661    -3674.380982 )
   DSS-45_DXYZ       =    (     -0.0335         -0.0041          0.0392   )
   DSS-45_TOPO_EPOCH =       @2020-OCT-23/00:00
   DSS-45_UP         =       'Z'
   DSS-45_NORTH      =       'X'


   SITES            +=       'DSS-53'
   DSS-53_FRAME      =       'EARTH_FIXED'
   DSS-53_CENTER     =       399
   DSS-53_IDCODE     =       399053
   DSS-53_EPOCH      =       @2003-JAN-01/00:00
   DSS-53_BOUNDS     =    (  @1950-JAN-01/00:00,  @2150-JAN-01/00:00  )
   DSS-53_XYZ        =    (  +4849.339965     -360.658246    +4114.747290  )
   DSS-53_DXYZ       =    (       -0.0100          0.0242          0.0156 )
   DSS-53_TOPO_EPOCH =       @2020-OCT-23/00:00
   DSS-53_UP         =       'Z'
   DSS-53_NORTH      =       'X'


   SITES            +=       'DSS-54'
   DSS-54_FRAME      =       'EARTH_FIXED'
   DSS-54_CENTER     =       399
   DSS-54_IDCODE     =       399054
   DSS-54_EPOCH      =       @2003-JAN-01/00:00
   DSS-54_BOUNDS     =    (  @1950-JAN-01/00:00,  @2150-JAN-01/00:00  )
   DSS-54_XYZ        =    ( +4849.434488     -360.7238999   +4114.618835 )
   DSS-54_DXYZ       =    (    -0.0100          0.0242          0.0156 )
   DSS-54_TOPO_EPOCH =       @2020-OCT-23/00:00
   DSS-54_UP         =       'Z'
   DSS-54_NORTH      =       'X'


   SITES            +=       'DSS-55'
   DSS-55_FRAME      =       'EARTH_FIXED'
   DSS-55_CENTER     =       399
   DSS-55_IDCODE     =       399055
   DSS-55_EPOCH      =       @2003-JAN-01/00:00
   DSS-55_BOUNDS     =    (  @1950-JAN-01/00:00,  @2150-JAN-01/00:00  )
   DSS-55_XYZ        =    ( +4849.525256     -360.6060932   +4114.495084 )
   DSS-55_DXYZ       =    (    -0.0100          0.0242          0.0156   )
   DSS-55_TOPO_EPOCH =       @2020-OCT-23/00:00
   DSS-55_UP         =       'Z'
   DSS-55_NORTH      =       'X'


   SITES            +=       'DSS-56'
   DSS-56_FRAME      =       'EARTH_FIXED'
   DSS-56_CENTER     =       399
   DSS-56_IDCODE     =       399056
   DSS-56_EPOCH      =       @2003-JAN-01/00:00
   DSS-56_BOUNDS     =    (  @1950-JAN-01/00:00,  @2150-JAN-01/00:00  )
   DSS-56_XYZ        =    ( +4849.421679     -360.549659    +4114.646987 )
   DSS-56_DXYZ       =    (    -0.0100          0.0242          0.0156   )
   DSS-56_TOPO_EPOCH =       @2020-OCT-23/00:00
   DSS-56_UP         =       'Z'
   DSS-56_NORTH      =       'X'


   SITES            +=       'DSS-63'
   DSS-63_FRAME      =       'EARTH_FIXED'
   DSS-63_CENTER     =       399
   DSS-63_IDCODE     =       399063
   DSS-63_EPOCH      =       @2003-JAN-01/00:00
   DSS-63_BOUNDS     =    (  @1950-JAN-01/00:00,  @2150-JAN-01/00:00  )
   DSS-63_XYZ        =    ( +4849.092518     -360.1803480   +4115.109251 )
   DSS-63_DXYZ       =    (    -0.0100          0.0242          0.0156   )
   DSS-63_TOPO_EPOCH =       @2020-OCT-23/00:00
   DSS-63_UP         =       'Z'
   DSS-63_NORTH      =       'X'


   SITES            +=       'DSS-65'
   DSS-65_FRAME      =       'EARTH_FIXED'
   DSS-65_CENTER     =       399
   DSS-65_IDCODE     =       399065
   DSS-65_EPOCH      =       @2003-JAN-01/00:00
   DSS-65_BOUNDS     =    (  @1950-JAN-01/00:00,  @2150-JAN-01/00:00  )
   DSS-65_XYZ        =    ( +4849.339634     -360.4276637   +4114.750733 )
   DSS-65_DXYZ       =    (    -0.0100          0.0242          0.0156   )
   DSS-65_TOPO_EPOCH =       @2020-OCT-23/00:00
   DSS-65_UP         =       'Z'
   DSS-65_NORTH      =       'X'

begintext

begintext

[End of definitions file]
