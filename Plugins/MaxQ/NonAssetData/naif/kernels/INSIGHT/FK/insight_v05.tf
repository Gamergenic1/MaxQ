KPL/FK


INSIGHT Frame Definitions Kernel
===============================================================================

   This frame kernel contains frame definitions for the INSIGHT Lander
   (INSIGHT) including definitions for the frames used during cruise,
   EDL and surface operations, antenna and other structure frames and
   science payload frames.


Version and Date
-------------------------------------------------------------------------------

   Version 0.5 -- January 2, 2019 -- Boris Semenov, NAIF

      Updated the INSIGHT_TOPO orientation based on the actual landing
      site coordinates, per [17].

      Re-cast INSIGHT_IDA_IDC_REF as a fixed offset frame.

      Filled in INSIGHT_IDA_IDC and INSIGHT_ICC alignments based on
      flight CAHVOR(E) models, [18] and [19].

   Version 0.4 -- December 4, 2018 -- Boris Semenov, NAIF

      Added the following frames:

         INSIGHT_IDA_IDC_REF

      Added the following name/ID mappings:

         INSIGHT_IDA_IDC_REF        -189131

         INSIGHT_CAL_TARGET_1       -189101
         INSIGHT_CAL_TARGET_2       -189102
         INSIGHT_CAL_TARGET_3       -189103
         INSIGHT_CAL_TARGET_4       -189104
         INSIGHT_CAL_TARGET_5       -189105
         INSIGHT_CAL_TARGET_6       -189106

   Version 0.3 -- July 18, 2018 -- Boris Semenov, NAIF

      Added the following frames:

         INSIGHT_PAYLOAD
         INSIGHT_SEIS
         INSIGHT_WTS
         INSIGHT_HP3
         INSIGHT_HP3_MOLE
         INSIGHT_HP3_RAD
         INSIGHT_APSS_MAG
         INSIGHT_APSS_PS
         INSIGHT_APSS_TWINS+Y
         INSIGHT_APSS_TWINS-Y
         INSIGHT_ICC
         INSIGHT_IDA_SHOULDER_AZ
         INSIGHT_IDA_SHOULDER_EL
         INSIGHT_IDA_ELBOW
         INSIGHT_IDA_WRIST
         INSIGHT_IDA_IDC
         INSIGHT_IDA_EFFECTOR
         INSIGHT_IDA_GRAPPLE_BASE
         INSIGHT_IDA_SCOOP
         INSIGHT_IDA_BLADE
         INSIGHT_IDA_GRAPPLE

      Added the following name/ID mappings:

         INSIGHT_PAYLOAD            -189100
         INSIGHT_SEIS               -189700
         INSIGHT_WTS                -189710
         INSIGHT_HP3                -189810
         INSIGHT_HP3_MOLE           -189820
         INSIGHT_HP3_RAD            -189800
         INSIGHT_HP3_RAD_NEAR       -189801
         INSIGHT_HP3_RAD_FAR        -189802
         INSIGHT_HP3_RAD_TEM        -189810
         INSIGHT_APSS_MAG           -189610
         INSIGHT_APSS_PS            -189620
         INSIGHT_APSS_TWINS+Y       -189630
         INSIGHT_APSS_TWINS-Y       -189640
         INSIGHT_ICC                -189111
         INSIGHT_IDA_SHOULDER_AZ    -189121
         INSIGHT_IDA_SHOULDER_EL    -189122
         INSIGHT_IDA_ELBOW          -189123
         INSIGHT_IDA_WRIST          -189124
         INSIGHT_IDA_IDC            -189125
         INSIGHT_IDA_GRAPPLE_BASE   -189127
         INSIGHT_IDA_SCOOP          -189128
         INSIGHT_IDA_BLADE          -189129
         INSIGHT_IDA_GRAPPLE        -189130

      Updated frame table and tree sections.

   Version 0.2 -- October 23, 2015 -- Boris Semenov, NAIF

      Updated orientation of INSIGHT_WPA based on [9]. Added 
      the INSIGHT_LANDER_POST frame based on [10].

   Version 0.1 -- September 3, 2015 -- Boris Semenov, NAIF

      Updated INSIGHT_TOPO for Target Site E9ov1.

   Version 0.0 -- September 18, 2014 -- Boris Semenov, NAIF

      Initial Release. Contains only lander, cruise, and antenna
      frame definitions


Contact Information
-------------------------------------------------------------------------------

   Boris V. Semenov, NAIF/JPL, (818)-354-8136, Boris.Semenov@jpl.nasa.gov


References
-------------------------------------------------------------------------------

   1. ``Frames Required Reading''

   2. ``Kernel Pool Required Reading''

   3. ``C-Kernel Required Reading''

   4. ``InSight GNC Hardware Coordinate Frame Definitions and
      Transformations'', LIB-13, latest version

   5. ``NSYT Landed & EDL Antenna Pattern Coordinate Frames'',
      09/11/2014

   6. ``InSight Pointing and Alignment Document (PAAD)'',
      NCYT-RQ-13-0032. Note that in this document the names of the
      Landed MGAs -- West and East -- do not match their specified
      pointing directions and should be swapped.

   7. E-mail from Gina Signori, INSIGHT SCT, from 09/17/14, regarding 
      InSight antenna nomenclature.

   8. InSight Planetary Constants and Models Document, June 11, 2015, 
      JPL D-75286, Revision B

   9. E-mail from Gina Signori, INSIGHT SCT, from 10/22/15, regarding 
      final InSight EDL Wrap around antenna clock reference vector
      orientation.

  10. E-mail from Gina Signori, INSIGHT SCT, from 10/22/15, regarding 
      POST frame used by the EDL simulation tool "POST".

  11. INSIGHT EDR SIS, latest version

  12. SEIS MICD, latest version

  13. HP3 MICD, latest version

  14. insight_dlr_v02.tf, provided by Nils Muller on April 3, 2018

  15. APSS MICD, latest version

  16. IDS MICD, latest version

  17. MCR-121458, InSight Landing Location

  18. INSIGHT_CAL_003_SN_0203_ICC-FLIGHT.cahvore

  19. INSIGHT_CAL_003_SN_0210_IDC-FLIGHT.cahvor


Implementation Notes
-------------------------------------------------------------------------------

   This file is used by the SPICE system as follows: programs that make
   use of this frame kernel must ``load'' the kernel, normally during
   program initialization. The SPICELIB routine FURNSH loads a
   kernel file into the pool as shown below.

      CALL FURNSH ( 'frame_kernel_name; )     (FORTRAN)
      furnsh_c ( "frame_kernel_name" );       (C)
      cspice_furnsh, "frame_kernel_name"      (IDL)
      cspice_furnsh( 'frame_kernel_name' )    (MATLAB)

   This file was created and may be updated with a text editor.


INSIGHT NAIF ID Codes
========================================================================

   The following names and NAIF ID codes are assigned to the INSIGHT
   lander, its structures and science instruments (the keywords
   implementing these name-ID mappings are located in the section
   "INSIGHT NAIF ID Codes -- Definition Section" at the end of this
   file):

   INSIGHT lander and landing site:
   ----------------------------
      INSIGHT                    -189   
      INSIGHT_LANDING_SITE       -189900
      INSIGHT_LANDER             -189000

   Antennas:
   ---------
      INSIGHT_CLGA_TX            -189410
      INSIGHT_CLGA_RX            -189420
      INSIGHT_CMGA               -189430
      INSIGHT_LMGA_EAST          -189440
      INSIGHT_LMGA_WEST          -189450
      INSIGHT_HELIX              -189460
      INSIGHT_WPA                -189470

   Payload Origin:
   ---------------
      INSIGHT_PAYLOAD            -189100

   Deck Locations:
   ---------------
      INSIGHT_CAL_TARGET_1       -189101
      INSIGHT_CAL_TARGET_2       -189102
      INSIGHT_CAL_TARGET_3       -189103
      INSIGHT_CAL_TARGET_4       -189104
      INSIGHT_CAL_TARGET_5       -189105
      INSIGHT_CAL_TARGET_6       -189106

   SEIS:
   -----
      INSIGHT_SEIS               -189700
      INSIGHT_WTS                -189710

   HP3:
   ----
      INSIGHT_HP3                -189810
      INSIGHT_HP3_MOLE           -189820
      INSIGHT_HP3_RAD            -189800
      INSIGHT_HP3_RAD_NEAR       -189801
      INSIGHT_HP3_RAD_FAR        -189802
      INSIGHT_HP3_RAD_TEM        -189810

   APSS:
   -----
      INSIGHT_APSS_MAG           -189610
      INSIGHT_APSS_PS            -189620
      INSIGHT_APSS_TWINS+Y       -189630
      INSIGHT_APSS_TWINS-Y       -189640

   IDS:
   ----
      INSIGHT_ICC                -189111
      INSIGHT_IDA_SHOULDER_AZ    -189121
      INSIGHT_IDA_SHOULDER_EL    -189122
      INSIGHT_IDA_ELBOW          -189123
      INSIGHT_IDA_WRIST          -189124
      INSIGHT_IDA_IDC_REF        -189131
      INSIGHT_IDA_IDC            -189125
      INSIGHT_IDA_GRAPPLE_BASE   -189127
      INSIGHT_IDA_SCOOP          -189128
      INSIGHT_IDA_BLADE          -189129
      INSIGHT_IDA_GRAPPLE        -189130


INSIGHT Frames
-------------------------------------------------------------------------------

   The following INSIGHT frames are defined in this kernel file:

      Name                       Relative to                 Type   Frame ID
      ========================== ========================== ======= ========

   Non Built-in Mars Frames:
   -------------------------
      INSIGHT_MME_2000           J2000                      FIXED   -189910

   Surface/descent frames (-1899xx):
   --------------------------------
      INSIGHT_TOPO               IAU_MARS                   FIXED   -189900
      INSIGHT_SURFACE_FIXED      INSIGHT_TOPO               FIXED   -189901
      INSIGHT_MRD                INSIGHT_TOPO               FIXED   -189902
      INSIGHT_LL                 INSIGHT_TOPO               FIXED   -189903

   Lander frames (-18900x):
   -----------------------
      INSIGHT_LANDER             INSIGHT_LL                 CK      -189001
      INSIGHT_LANDER_CRUISE      J2000                      CK      -189000
      INSIGHT_LANDER_POST        J2000                      CK      -189002

   Antenna frames (-1894xx):
   ------------------------
      INSIGHT_CLGA_TX            INSIGHT_LANDER             FIXED   -189410
      INSIGHT_CLGA_RX            INSIGHT_LANDER             FIXED   -189420
      INSIGHT_CMGA               INSIGHT_LANDER             FIXED   -189430
      INSIGHT_LMGA_EAST          INSIGHT_LANDER             FIXED   -189440
      INSIGHT_LMGA_WEST          INSIGHT_LANDER             FIXED   -189450
      INSIGHT_HELIX              INSIGHT_LANDER             FIXED   -189460
      INSIGHT_WPA                INSIGHT_LANDER             FIXED   -189470

   Payload frame (-18910x):
   ------------------------
      INSIGHT_PAYLOAD            INSIGHT_LANDER             FIXED   -189100

   SEIS frames (-1897xx):
   ----------------------
      INSIGHT_SEIS               INSIGHT_LANDER             FIXED   -189700
      INSIGHT_WTS                INSIGHT_LANDER             FIXED   -189710

   HP3 frames (-1898xx):
   ---------------------
      INSIGHT_HP3                INSIGHT_LANDER             FIXED   -189810
      INSIGHT_HP3_MOLE           INSIGHT_HP3                FIXED   -189820
      INSIGHT_HP3_RAD            INSIGHT_LANDER             FIXED   -189800

   APSS frames (-1896xx):
   ----------------------
      INSIGHT_APSS_MAG           INSIGHT_LANDER             FIXED   -189610
      INSIGHT_APSS_PS            INSIGHT_LANDER             FIXED   -189620
      INSIGHT_APSS_TWINS+Y       INSIGHT_LANDER             FIXED   -189630
      INSIGHT_APSS_TWINS-Y       INSIGHT_LANDER             FIXED   -189640

   IDS frames (-1891xx):
   ---------------------
      INSIGHT_ICC                INSIGHT_PAYLOAD            FIXED   -189111
      INSIGHT_IDA_SHOULDER_AZ    INSIGHT_PAYLOAD            CK      -189121
      INSIGHT_IDA_SHOULDER_EL    INSIGHT_IDA_SHOULDER_AZ    CK      -189122
      INSIGHT_IDA_ELBOW          INSIGHT_IDA_SHOULDER_EL    CK      -189123
      INSIGHT_IDA_WRIST          INSIGHT_IDA_ELBOW          CK      -189124
      INSIGHT_IDA_IDC_REF        INSIGHT_IDA_ELBOW          CK      -189131
      INSIGHT_IDA_IDC            INSIGHT_IDA_IDC_REF        FIXED   -189125
      INSIGHT_IDA_EFFECTOR       INSIGHT_IDA_WRIST          FIXED   -189126
      INSIGHT_IDA_GRAPPLE_BASE   INSIGHT_IDA_EFFECTOR       FIXED   -189127
      INSIGHT_IDA_SCOOP          INSIGHT_IDA_EFFECTOR       FIXED   -189128
      INSIGHT_IDA_BLADE          INSIGHT_IDA_EFFECTOR       FIXED   -189129
      INSIGHT_IDA_GRAPPLE        INSIGHT_IDA_WRIST          CK      -189130

   The frame descriptions and definitions are provided in the sections
   below.


INSIGHT Frame Hierarchy
-------------------------------------------------------------------------------

   The diagram below shows the INSIGHT frames hierarchy:


                             "J2000" INERTIAL
       +------------------------------------------------------------+
       |                      |                       |             |
       | <--pck               | <--pck       fixed--> |             | <--ck
       V                      V                       V             |
   "IAU_EARTH"            "IAU_MARS"          "INSIGHT_MME_2000"    |
   EARTH BFR(2)           MARS BFR(2)         MME J2000 Inertial    |
   ------------   +-----------------------+  -------------------    |
                  |                       |           |             |
                  |  <--fixed             | <--fixed  |             |
                  V                       V           |             |
              "INSIGHT_TOPO"         "INSIGHT_MRD"    |             |
             +-------------+         -------------    |             |
             |             |              |           |             |
             |    fixed--> |              |           |             |
             |             V              |           |             V
             |   "INSIGHT_SURFACE_FIXED"  |           |  "INSIGHT_LANDER_POST"
             |   -----------------------  |           |  ---------------------
             |                            |           |             |
             |                            |           |             |
             |                            |           |             |
             | <--fixed                   | <--ck     | <--ck       |
             V                            V           V             |
       "INSIGHT_LL"                  "INSIGHT_LANDER_CRUISE"        |
       ------------                  -----------------------        | 
             |                                 |                    |
             |                                 |                    |
             | <--ck(1)                        | <--ck(1)           | <--ck(1)
             V                                 V                    V
                                "INSIGHT_LANDER"
   +------------------------------------------------------------------------+
   | | | | | | | |                      |                       | | | | | | |
   | | | | | | | |<--fixed              |              fixed--> | | | | | | |
   | | | | | | | V                      |                       V | | | | | |
   | | | | | | | "INSIGHT_SEIS"         |       "INSIGHT_CLGA_TX" | | | | | |
   | | | | | | | --------------         |       ----------------- | | | | | |
   | | | | | | |                        |                         | | | | | |
   | | | | | | |<--fixed                |                fixed--> | | | | | |
   | | | | | | V                        |                         V | | | | |
   | | | | | | "INSIGHT_WTS"            |         "INSIGHT_CLGA_RX" | | | | |
   | | | | | | -------------            |         ----------------- | | | | |
   | | | | | |                          |                           | | | | |
   | | | | | |<--fixed                  |                  fixed--> | | | | |
   | | | | | V                          |                           V | | | |
   | | | | | "INSIGHT_APSS_MAG"         |              "INSIGHT_CMGA" | | | |
   | | | | | ------------------         |              -------------- | | | |
   | | | | |                            |                             | | | |
   | | | | |<--fixed                    |                    fixed--> | | | |
   | | | | V                            |                             V | | |
   | | | | "INSIGHT_APSS_PS"            |           "INSIGHT_LMGA_EAST" | | |
   | | | | -----------------            |           ------------------- | | |
   | | | |                              |                               | | |
   | | | |<--fixed                      |                      fixed--> | | |
   | | | V                              |                               V | |
   | | | "INSIGHT_APSS_TWINS+Y"         |             "INSIGHT_LMGA_WEST" | |
   | | | ----------------------         |             ------------------- | |
   | | |                                |                                 | |
   | | |<--fixed                        |                        fixed--> | |
   | | V                                |                                 V |
   | | "INSIGHT_APSS_TWINS-Y"           |                   "INSIGHT_HELIX" |
   | | ----------------------           |                   --------------- |
   | |                                  |                                   |
   | |<--fixed                          |                          fixed--> |
   | V                                  V                                   V
   | "INSIGHT_HP3_RAD"          "INSIGHT_PAYLOAD"               "INSIGHT_WPA"
   | -----------------     +---------------------------+        -------------
   |                       |            |              |
   |<--fixed               |<--fixed    |              |<--ck
   V                       V            |              V   
   "INSIGHT_HP3"     "INSIGHT_ICC"      |  "INSIGHT_IDA_SHOULDER_AZ"
   -------------     -------------      |  -------------------------
   |                                    |              |
   |<--fixed                            |              |<--ck
   V                                    |              V
   "INSIGHT_HP3_MOLE"                   |   "INSIGHT_IDA_SHOULDER_EL"
   ------------------                   |   -------------------------
                                        |              |
                                        |              |<--ck
                                        |              V
                                        |     "INSIGHT_IDA_ELBOW"
                                        |  +---------------------
                                        |  |           |
                                   ck-->|  |<--ck(3)   |<--ck
                                        V  V           V
                         "INSIGHT_IDA_IDC_REF"  "INSIGHT_IDA_WRIST"
                         ---------------------  -------------------
                                        |              |
                                        |<--fixed      |<--fixed
                                        V              |
                                "INSIGHT_IDA_IDC"      |
                                -----------------      |
                                                       |
                                                       |
                                                       V
                                            "INSIGHT_IDA_EFFECTOR"
            +------------------------------------------------------+
            |                 |                    |               |
            |<--fixed         |                    |               |<--ck(4)
            V                 |                    |               V
   "INSIGHT_IDA_GRAPPLE_BASE" |                    |    "INSIGHT_IDA_GRAPPLE"
   -------------------------- |                    |     -------------------
                              |                    |
                              |<--fixed            |<--fixed
                              V                    V
                     "INSIGHT_IDA_SCOOP"    "INSIGHT_IDA_BLADE"
                     -------------------    -------------------


   (1)      In these cases transformation is fixed but it has to be
            stored in a CK to make SPICE "traverse" appropriate frame
            tree branch based on the time of interest and/or loaded
            kernels.

   (2)      BFR -- body-fixed rotating frame.

   (3)      The orientation of the INSIGHT_IDA_IDC_REF frame is more
            likely to be given w.r.t. to the INSIGHT_PAYLOAD frame.

   (4)      The orientation of the INSIGHT_IDA_GRAPPLE frame is more likely 
            to be given w.r.t. to the INSIGHT_LL frame.


Implementation of Frame Chains for Different Mission Phases
-------------------------------------------------------------------------------

   Different routes along the branches of the INSIGHT frame hierarchy
   are implemented for different mission phases depending on the
   availability of the orientation data and the source, format and type
   of the data.

   This subsection summarizes mission phase specific implementations.


Cruise
------


     "J2000" Inertial
     ----------------
            |
            | <----------- Fixed transformation defined in this FK
            V
    "INSIGHT_MME_2000" Inertial
    ---------------------------
            |
            | <----------- CK segment containing TLM quaternions
            V
    "INSIGHT_LANDER_CRUISE"
    -----------------------
            |
            | <----------- CK segment representing fixed rotation defined
            |              by the lander design
            V
       "INSIGHT_LANDER"
       ----------------


Entry-Descent-Landing (chain 1)
-------------------------------


     "J2000" Inertial
     ----------------
            |
            | <----------- PCK-based transformation
            V
      "IAU_MARS" BFR
      --------------
            |
            | <----------- CK segment representing fixed rotation derived
            |              from TLM (based on s/c position at the time of
            V              parachute pre-deploy + 13 seconds)
      "INSIGHT_MRD"
      -------------
            |
            | <----------- CK segment based on TLM Quaternion
            V
   "INSIGHT_LANDER_CRUISE"
   -----------------------
            |
            | <----------- CK segment representing fixed rotation defined
            |              by the lander design
            V
     "INSIGHT_LANDER"
     ----------------


Entry-Descent-Landing (chain 2)
-------------------------------


     "J2000" Inertial
     ----------------
            |
            | <----------- CK segment based on POST tool EDL simulation or 
            |              reconstruction
            V
   "INSIGHT_LANDER_POST"
   -----------------------
            |
            | <----------- CK segment representing fixed rotation defined
            |              by the lander design
            V
     "INSIGHT_LANDER"
     ----------------


Surface Operations
------------------

   During surface operations the lander orientation is available from
   the following source(s):

      -  initial orientation is provided by the spacecraft team in the
         form of quaternion defining orientation of the INSIGHT_LANDER
         frame with respect to the INSIGHT_LL frame;

   To accommodate this(ese) source(s) the following frame chain(s) can
   be implemented:

   Chain 1 (based on spacecraft team quaternion):


     "J2000" Inertial
     ----------------
            |
            | <----------- PCK-based transformation
            V
      "IAU_MARS" BFR
      --------------
            |
            | <----------- Fixed rotation based on the landing site
            |              coordinates
            V
      "INSIGHT_TOPO"
      --------------
            |
            | <----------- Fixed rotation based on frame definitions
            V
       "INSIGHT_LL"
       ------------
            |
            | <----------- CK segment representing fixed rotation per
            |              initial quaternion provided by LMA
            V
     "INSIGHT_LANDER"
     ----------------


Inertial Frames
-------------------------------------------------------------------------------

   This section defines the INSIGHT-specific inertial frames.


MME ``2000'' Frame
------------------

   The INSIGHT_MME_2000 frame is the Mars Mean Equator and IAU Vector of J2000
   inertial reference frame defined using Mars rotation constants
   from the IAU 2000 report. This frame defined as a fixed offset frame
   with respect to the J2000 frame.

   \begindata

      FRAME_INSIGHT_MME_2000           = -189910
      FRAME_-189910_NAME               = 'INSIGHT_MME_2000'
      FRAME_-189910_CLASS              = 4
      FRAME_-189910_CLASS_ID           = -189910
      FRAME_-189910_CENTER             = 499
      TKFRAME_-189910_SPEC             = 'MATRIX'
      TKFRAME_-189910_RELATIVE         = 'J2000'
      TKFRAME_-189910_MATRIX           = (

         0.6732521982472339       0.7394129276360180       0.0000000000000000
        -0.5896387605430040       0.5368794307891331       0.6033958972853946
         0.4461587269353556      -0.4062376142607541       0.7974417791532832

                                         )

   \begintext


Surface-Based Frames
-------------------------------------------------------------------------------

   This section defines the INSIGHT-specific surface-based frames.


Topocentric Frame
-----------------

   This frame defines the z axis as the normal outward at the landing
   site, the x axis points at local north with the y axis completing
   the right handed frame (points at local west.)

   Orientation of the frame is given relative to the body fixed
   rotating frame 'IAU_MARS' (x - along the line of zero longitude
   intersecting the equator, z - along the spin axis, y - completing
   the right hand coordinate frame.)
 
   The transformation from 'INSIGHT_TOPO' frame to 'IAU_MARS' frame is
   a 3-2-3 rotation with defined angles as the negative of the site
   longitude, the negative of the site colatitude, 180 degrees.

   This frame is currently defined for the actual site based on the MRO
   HIRISE image taken on Dec 6, 2018 (per [17]).
 
   The landing site Gaussian longitude and latitude upon which the
   definition is built are:

      Lon = 135.623447 degrees East
      Lat =  4.555681 degrees North

   These Gaussian coordinates correspond to the following areocentric
   coordinates (R, LON, LAT) = (3393.079,135.623447,4.502384) and Mars
   radii (Re, Re, Rp) = (3396.19, 3396.19, 3376.20).
 
   The coordinates specified above are given with respect to the
   'IAU_MARS' instance defined by the rotation/shape model from the the
   PCK file 'pck00010.tpc'.

   These keywords implement the frame definition.

   \begindata

      FRAME_INSIGHT_TOPO               = -189900
      FRAME_-189900_NAME               = 'INSIGHT_TOPO'
      FRAME_-189900_CLASS              =  4
      FRAME_-189900_CLASS_ID           =  -189900
      FRAME_-189900_CENTER             =  -189900

      TKFRAME_-189900_RELATIVE         = 'IAU_MARS'
      TKFRAME_-189900_SPEC             = 'ANGLES'
      TKFRAME_-189900_UNITS            = 'DEGREES'
      TKFRAME_-189900_AXES             = ( 3, 2, 3 )
      TKFRAME_-189900_ANGLES           = ( -135.623447, -85.444319, 180.000 )

   \begintext


Surface Fixed Frame
-------------------

   The orientation of the SURFACE_FIXED frame is by definition the same
   as of the INSIGHT_TOPO frame. Therefore this frame is defined as a zero
   offset frame relative to the INSIGHT_TOPO frame.

   \begindata

      FRAME_INSIGHT_SURFACE_FIXED      = -189901
      FRAME_-189901_NAME               = 'INSIGHT_SURFACE_FIXED'
      FRAME_-189901_CLASS              = 4
      FRAME_-189901_CLASS_ID           = -189901
      FRAME_-189901_CENTER             = -189

      TKFRAME_-189901_RELATIVE         = 'INSIGHT_TOPO'
      TKFRAME_-189901_SPEC             = 'ANGLES'
      TKFRAME_-189901_UNITS            = 'DEGREES'
      TKFRAME_-189901_AXES             = ( 1, 2, 3 )
      TKFRAME_-189901_ANGLES           = ( 0.0, 0.0, 0.0 )

   \begintext


Mars Relative Descent (MRD) Frame
---------------------------------

   This frame is the frame used by INSIGHT AACS on-board software to
   control the lander attitude during "terminal descent" phase -- from
   the "parachute pre-deploy + <specified epoch>" time through the
   "surface touchdown" time.

   The frame is defined in [4] as follows:

     "The Mars Relative Descent Frame Local Vertical, Local Horizontal
      Coordinate system used by the InSight Lander is a coordinate
      system fixed with respect to the MCMF [Mars body-fixed rotating
      frame -- BVS] frame and is based on the position of (Pmcmf) of
      the Lander and the north pole unit vector (Nmcmf) in the MCMF
      frame at a specified epoch relative to parachute pre-deploy (see
      the EDL Baseline Reference Mission document for the current
      definition) Note: The epoch of MRD frame initialization is tied
      to the epoch of radar "altitude-mode" start; a change in one
      epoch may drive a change in the other. The axes are defined as
      follows:

                           -Pmcmf            [points from the spacecraft
               +Zmrd = -----------------      in Mars body-fixed frame
                           |Pmcmf|            towards the center of the 
                                              planet at the time
                                              "pre-deploy + specified
                                              time" - BVS]


                         +Zmrd x Nmcmf       [points to local East from sub-
               +Ymrd = -----------------      spacecraft point computed at 
                        |+Zmrd x Nmcmf|       the time "pre-deploy + 
                                              specified time" in Mars
                                              body-fixed frame - BVS]


               +Xmrd =   +Ymrd x +Zmrd       [points to local North from sub-
                                              spacecraft point computed
                                              at the time "pre-deploy +
                                              specified time" in Mars
                                              body-fixed frame - BVS]
     "

   Since "parachute pre-deploy + specified time" time and position of
   the spacecraft position at that time are not known until the actual
   decent and landing, and assuming that the final landing location
   will not be very far from the sub-spacecraft point at "parachute
   pre-deploy + specified time", we can specify orientation of the
   INSIGHT_MRD frame as a fixed, 180 degrees rotation about +X with
   respect to the INSIGHT_TOPO frame. The nominal definition below
   implements this rotation:

   \begindata

      FRAME_INSIGHT_MRD                = -189902
      FRAME_-189902_NAME               = 'INSIGHT_MRD'
      FRAME_-189902_CLASS              = 4
      FRAME_-189902_CLASS_ID           = -189902
      FRAME_-189902_CENTER             = -189

      TKFRAME_-189902_RELATIVE         = 'INSIGHT_TOPO'
      TKFRAME_-189902_SPEC             = 'ANGLES'
      TKFRAME_-189902_UNITS            = 'DEGREES'
      TKFRAME_-189902_AXES             = ( 1, 2, 3 )
      TKFRAME_-189902_ANGLES           = ( 180.0, 0.0, 0.0 )

   \begintext

   When the actual transformation from the "IAU_MARS" frame to the
   "INSIGHT_MRD" frame, computed on-board and send down to Earth in
   channelized telemetry as a 3x3 transformation matrix, will become
   available, it should be inserted into the definition below as
   follows:

      TKFRAME_-189902_MATRIX       = (
               A-xxx(LVLH_MTRX_11)  A-xxx(LVLH_MTRX_12)  A-xxx(LVLH_MTRX_13)
               A-xxx(LVLH_MTRX_21)  A-xxx(LVLH_MTRX_22)  A-xxx(LVLH_MTRX_23)
               A-xxx(LVLH_MTRX_31)  A-xxx(LVLH_MTRX_32)  A-xxx(LVLH_MTRX_33)
                                    )

   where A-xxx are channel IDs and (LVLH_MTRX_xx) are channel names.

   (TBD: channels above must be verified against TLM dictionary.)

   Then, the definition should be "activated" by placing it between
   \begindata ... \begintext tokens:

   begindata

      FRAME_INSIGHT_MRD                =  -189902
      FRAME_-189902_NAME               = 'INSIGHT_MRD'
      FRAME_-189902_CLASS              =  4
      FRAME_-189902_CLASS_ID           =  -189902
      FRAME_-189902_CENTER             =  -189

      TKFRAME_-189902_RELATIVE         = 'IAU_MARS'
      TKFRAME_-189902_SPEC             = 'MATRIX'
      TKFRAME_-189902_MATRIX           = (
                d.dddddddd          d.dddddddd          d.dddddddd
                d.dddddddd          d.dddddddd          d.dddddddd
                d.dddddddd          d.dddddddd          d.dddddddd
                                         )

   begintext


Landed Local Vertical, Local Horizontal (LL) Frame
--------------------------------------------------

   This frame is the frame with respect to which the landed lander
   orientation is determined by the on-board GyroCompass process.

   The frame is defined in [11] as follows:

     "The Landed Local Vertical, Local Horizontal Coordinate System
      used by the Lander is a coordinate system [the origin of which is
      -- BVS] fixed with respect to the landed spacecraft. The
      coordinate frame is is related to the MCI [INSIGHT_MME_2000 Inertial --
      BVS] frame by rotation of the right ascension of the Mars local
      meridian and the latitude of the landed spacecraft."

   The axes of this frame point as follows:

      +Z    points along local gravity vector (because the latitude of
            the landing is determined as [11]:

              "LAT = arcsin( -G local * W local )
                 where:
               LAT      = latitude of landed s/c
               -G local = gravity vector measured in s/c body frame
               w local  = Mars rotational rate measure in the s/ body frame"

      +X    points towards local North

      +Y    completes the right-hand frame (and, thus points towards
            local East)

   One principal axis of this frame is based on the measured gravity
   vector direction at the landing site, which can be computed using
   different assumptions:

      -  local gravity vector points towards the center of Mars; in
         this case the latitude defining the axis is planetocentric
         latitude;

      -  local gravity vector points along normal to the nominal Mars
         spheroid surface; in this case the latitude defining the axis
         is planetographic latitude;

      -  local gravity vector points along the gravitational potential
         vector computed using some Mars gravity field model.

   It's obvious that the first assumption is the most inaccurate of the
   three while the last one the most accurate, with the difference
   between planetocentric and planetographic latitudes at the nominal
   landing site being:

      delta = | LAT_plcen - LAT_plgraph | = | 4.4576 - 4.5104 | = 0.0528 deg.

   In this file the INSIGHT_LL frame is defined as a fixed offset frame
   with respect to the INSIGHT_TOPO frame that is based on the
   planetographic latitude.

   \begindata

      FRAME_INSIGHT_LL                 = -189903
      FRAME_-189903_NAME               = 'INSIGHT_LL'
      FRAME_-189903_CLASS              = 4
      FRAME_-189903_CLASS_ID           = -189903
      FRAME_-189903_CENTER             = -189

      TKFRAME_-189903_RELATIVE         = 'INSIGHT_TOPO'
      TKFRAME_-189903_SPEC             = 'ANGLES'
      TKFRAME_-189903_UNITS            = 'DEGREES'
      TKFRAME_-189903_AXES             = ( 1, 2, 3 )
      TKFRAME_-189903_ANGLES           = ( 180.0, 0.0, 0.0 )

   \begintext


Lander Frames
-------------------------------------------------------------------------------

   Two primary frames are defined for the INSIGHT spacecraft -- the
   LANDER frame (or Mechanical frame) and the LANDER CRUISE frame.

   An additional frame is used by the POST EDL simulation/reconstruction
   tool -- the LANDER POST frame.


Lander Frame
------------

   The LANDER frame is the one used in all solid modeling and design of
   the lander. This frame, also called "Lander Mechanical frame", is
   defined in [4] as follows:

     "+Xm = pointed towards foot of deployed lander 0 degree leg
      +Zm = normal to launch vehicle interface plane (in direction of flight)
      +Ym = +Zm x +Xm, parallel to landed solar array axis of symmetry

      The origin of the frame is centered on the launch vehicle separation
      plane."

   If someone would look at the normal landed spacecraft configuration,
   he/she would see:

      -  Z axis is vertical and points down (from the lander deck
         toward the lander "legs");

      -  X axis is parallel to the lander deck plane and lander solar
         array yoke and points away from the deck center toward the
         deck side opposite to the arm;

      -  Y completes the right-handed frame and points along solar
         array axis of symmetry;

      -  origin of this frame is TBD millimeters above the lander
         deck.


Lander Cruise Frame
-------------------

   This frame is defined in [4] as follows:

     "+Xc = +Zm
      +Zc = center line of REMs #3 and #4
      +Yc = +Zc x +Xc

      ...

      The +X axis of the cruise frame is aligned with the +Z axis of
      the mechanical [INSIGHT_LANDER -- BVS] frame. The +Y axis is rotated
      -120 degrees from the +X axis of the mechanical frame, about the
      +X axis of the cruise frame."

   The INSIGHT_LANDER frame can be transformed to the INSIGHT_LANDER_CRUISE
   frame by two rotations, first by -90 degrees about Y, second by +150
   degrees about the new position of X.


Lander and Lander Cruise Frame Diagram
--------------------------------------

   This diagram illustrates the LANDER and LANDER CRUISE frames for 
   cruise configuration (cruise solar panel side view):

                     .-'-.
                  .-'     \
                -'         \____
                \           \   `-.
                 \         ^+Ylnd  \
                  \        | |      \
                 / `-      |         \
                |          | +Zlnd    | 
                |   <------x +Xcru    |
               +Xlnd    .-' \   .     |
                 \   <-'     \   `-. /
                +Zcru     |   \     \
                   \      |    V     \
                    `-.   \     +Ycru.\   +Zlnd and +Xcru are into the page.
                       `---\         .- 
                            \     .-'
                             `-.-'

   This diagram illustrates the LANDER and LANDER CRUISE frames for 
   landed configuration (top view of the lander deck):

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.       .'   | _|
                      `--H--'     //
                      ___H_______//
                     /     ^+Ylnd \
                    /      |       \
                   /       |        \
             --    |       | +Zlnd  |
            | =====|<------x +Xcru  |
             -- +Xlnd   .-' \       |                _
                   \ <-'     \      o==============='_' IDA
                 +Zcru        \   /
                     \________ V /
                         H    +Ycru
                      .--H--.     \\_
                    .'       `.   |__|
                   /           \
                  .  -Y solar   .      
                  |    panel    |    +Zlnd and +Xcru are into the page.
                  `~ ~ ~ ~ ~ ~ ~'


Lander Frame Definitions
------------------------

   Both lander frames are defined as CK frames for the following
   reasons:

      -  during cruise the s/c "flies" using the INSIGHT_LANDER_CRUISE
         frame; the orientation of this frame is determined on-board
         with respect to the INSIGHT_MME_2000 frame; this orientation
         is sent down in the channelized telemetry, from which it is
         extracted and stored in the cruise CK file;

      -  during descent the s/c also "flies" using the
         INSIGHT_LANDER_CRUISE frame; the orientation of this frame is
         determined on-board with respect to the Mars Relative Descent
         frame (INSIGHT_MRD); this orientation is sent down in the
         channelized telemetry, from which it is extracted and stored
         in the descent CK file(s);

      -  after landing the initial orientation of the INSIGHT_LANDER_CRUISE
         frame is determined (by running GyroCompass process) with
         respect the Landed Local Vertical, Local Horizontal frame
         (INSIGHT_LL); it is stored in the surface orientation CK file(s);

      -  after landing the orientation of the INSIGHT_LANDER frame may
         be determined with respect the local level or topocentric
         frame; this orientation is stored in the surface orientation
         CK file(s);

      -  for different periods (cruise, descent, surface ops) the
         INSIGHT_LANDER frame can be specified as offset to the
         INSIGHT_LANDER_CRUISE frame or the LL frame depending on for
         which of these the orientation data is available.

   Also, should the landed orientation change during surface operations
   due to the arm or other activities, the change in orientation will
   be captured in the landed CK file(s).

   \begindata

      FRAME_INSIGHT_LANDER             = -189001
      FRAME_-189001_NAME               = 'INSIGHT_LANDER'
      FRAME_-189001_CLASS              = 3
      FRAME_-189001_CLASS_ID           = -189001
      FRAME_-189001_CENTER             = -189
      CK_-189001_SCLK                  = -189
      CK_-189001_SPK                   = -189

      FRAME_INSIGHT_LANDER_CRUISE      = -189000
      FRAME_-189000_NAME               = 'INSIGHT_LANDER_CRUISE'
      FRAME_-189000_CLASS              = 3
      FRAME_-189000_CLASS_ID           = -189000
      FRAME_-189000_CENTER             = -189
      CK_-189000_SCLK                  = -189
      CK_-189000_SPK                   = -189

   \begintext


Lander POST Frame
-----------------

   According to [10] the POST frame (INSIGHT_LANDER_POST/-189002) is
   used by the POST EDL simulation tool. Its +X axis is co-aligned with
   the CRUISE frame's +X axis and its +Z axis is co-aligned with the
   CRUISE frame's +Y axis.
 
   This diagram illustrates the LANDER CRUISE and POST frames for the
   cruise configuration (cruise solar panel side view):

                     .-'-.
                  .-'     \
                -'         \____
                \           \   `-.
                 \                 \
                  \          |   +Ypost
                 / `-           .->  \
                |   +Xpost   .-'      | 
                |   +Xcru  x'         |
                |       .-' \   .     |
                 \   <-'     \   `-. /
                +Zcru     |   \     \
                   \      |    V+Zpost
                    `-.   \     +Ycru.\       +Xpost and +Xcru
                       `---\         .-       are into the page.  
                            \     .-'
                             `-.-'

   As seen on the diagram, a single +90 degree rotation about +X is
   needed to align the POST frame with the CRUISE frame. (Note: since
   the CRUISE frame is defined as a CK-based frame this fixed rotation
   will stored in a CK file.)

   Because the orientation of the POST frame is time varying and will
   be stored in CK files this frame is defined as a CK-based frame.

   \begindata

      FRAME_INSIGHT_LANDER_POST        = -189002
      FRAME_-189002_NAME               = 'INSIGHT_LANDER_POST'
      FRAME_-189002_CLASS              = 3
      FRAME_-189002_CLASS_ID           = -189002
      FRAME_-189002_CENTER             = -189
      CK_-189002_SCLK                  = -189
      CK_-189002_SPK                   = -189

   \begintext


Antenna Frames
-------------------------------------------------------------------------------

   The all INSIGHT Antenna frames are fixed offset frames with their
   orientation given relative to the LANDER Mechanical frame.

   All antenna frames are defined such that +Z axis is the antenna
   boresight and +X axis is lined up with the reference direction for
   the antenna pattern clock angle.


Cruise LGA Transmit Antenna Frame
---------------------------------

   According to [6] and [7], the Cruise LGA Transmit antenna boresight
   -- +Z axis of the INSIGHT_CLGA_TX frame -- is the (0, 0, -1) vector
   in the lander mechanical frame and its clock reference direction --
   +X axis of the INSIGHT_CLGA_TX frame -- is the (1, 0, 0) vector in
   the lander mechanical frame.
 
   The INSIGHT_LANDER frame can be transformed to the INSIGHT_CLGA_TX
   frame by a single rotation of 180 degrees about +X axis.

   This diagram illustrates the INSIGHT_CLGA_TX frame (cruise solar
   panel side view for cruise configuration):

                     .-'-.
                  .-'     \
                -'         \____
                \           \   `-.
                 \         ^+Ylnd  \
                  \        | |      \
             +Xclga        |         \
                | <------o | +Zlnd    | 
                |   <----|-x +Xcru    |
               +Xlnd    .|' \   .     |
                 \   <-' |   \   `-. /
                +Zcru    V    \     \
                   \   +Yclga  V     \
                    `-.   \     +Ycru.\   +Zlnd and +Xcru are into the page.
                       `---\         .- 
                            \     .-'     +Zclga is out of the page.
                             `-.-'

   Since the frame definition below contains the reverse transformation
   (i.e. from the antenna frame to the lander frame), the order and the
   signs of the rotations are reversed.

   \begindata

      FRAME_INSIGHT_CLGA_TX            = -189410
      FRAME_-189410_NAME               = 'INSIGHT_CLGA_TX'
      FRAME_-189410_CLASS              = 4
      FRAME_-189410_CLASS_ID           = -189410
      FRAME_-189410_CENTER             = -189

      TKFRAME_-189410_RELATIVE         = 'INSIGHT_LANDER'
      TKFRAME_-189410_SPEC             = 'ANGLES'
      TKFRAME_-189410_UNITS            = 'DEGREES'
      TKFRAME_-189410_AXES             = ( 3, 1, 3 )
      TKFRAME_-189410_ANGLES           = ( 0.0, 180.0, 0.0 )

   \begintext


Cruise LGA Receive Antenna Frame
--------------------------------

   According to [6] and [7], the Cruise LGA Receive antenna boresight
   -- +Z axis of the INSIGHT_CLGA_RX frame -- is the (0, 0, -1) vector
   in the lander mechanical frame and its clock reference direction --
   +X axis of the INSIGHT_CLGA_RX frame -- is the (1, 0, 0) vector in
   the lander mechanical frame.
 
   The INSIGHT_LANDER frame can be transformed to the INSIGHT_CLGA_RX
   frame by a single rotation of 180 degrees about +X axis.

   This diagram illustrates the INSIGHT_CLGA_RX frame (cruise solar
   panel side view for cruise configuration):

                     .-'-.
                  .-'     \
                -'         \____
                \           \   `-.
                 \         ^+Ylnd  \
                  \        | |      \
             +Xclga        |         \
                | <------o | +Zlnd    | 
                |   <----|-x +Xcru    |
               +Xlnd    .|' \   .     |
                 \   <-' |   \   `-. /
                +Zcru    V    \     \
                   \   +Yclga  V     \
                    `-.   \     +Ycru.\   +Zlnd and +Xcru are into the page.
                       `---\         .- 
                            \     .-'     +Zclga is out of the page.
                             `-.-'

   Since the frame definition below contains the reverse transformation
   (i.e. from the antenna frame to the lander frame), the order and the
   signs of the rotations are reversed.

   \begindata

      FRAME_INSIGHT_CLGA_RX            = -189420
      FRAME_-189420_NAME               = 'INSIGHT_CLGA_RX'
      FRAME_-189420_CLASS              = 4
      FRAME_-189420_CLASS_ID           = -189420
      FRAME_-189420_CENTER             = -189

      TKFRAME_-189420_RELATIVE         = 'INSIGHT_LANDER'
      TKFRAME_-189420_SPEC             = 'ANGLES'
      TKFRAME_-189420_UNITS            = 'DEGREES'
      TKFRAME_-189420_AXES             = ( 3, 1, 3 )
      TKFRAME_-189420_ANGLES           = ( 0.0, 180.0, 0.0 )

   \begintext


Cruise Medium Gain Antenna Frame
--------------------------------

   According to [6], the Cruise Medium Gain antenna boresight -- +Z
   axis of the INSIGHT_CMGA frame -- is the (0.703306, -0.151033,
   -0.694658) vector in the lander mechanical frame. The antenna clock
   reference direction -- +X axis of the INSIGHT_CMGA frame -- is
   chosen arbitrarily to be in the lander XY plane in the +X/+Y quadrant.
 
   The INSIGHT_LANDER frame can be transformed to the INSIGHT_CMGA frame
   by two rotations: first by +77.879965 degrees about the +Z axis,
   then by +133.999970 degrees about +X axis. 

   This diagram illustrates the INSIGHT_CMGA frame (cruise solar
   panel side view for cruise configuration):

                     .-'-.
                  .-'     \
                -'         \____
                \           \   `-.
                +Xcmga ^   ^+Ylnd  \
                  \     .  | |      \
                 / `-      |         \
                +Xlnd    ' | +Zlnd    | 
                |   <-----*x +Xcru    |
            +Zcmga <--''.-' \   .     |
                 \   <-'     \   `-. /
                +Zcru     |   \     \
                   \      |    V     \
                    `-.   \     +Ycru.\   +Zlnd and +Xcru are into the page.
                       `---\         .- 
                            \     .-'     +Zcmga points ~44 degrees
                                              above the page. 
                             `-.-' 
                                          +Ycmga points ~46 degrees
                                              into the page.

   Since the frame definition below contains the reverse transformation
   (i.e. from the antenna frame to the lander frame), the order and the
   signs of the rotations are reversed.

   \begindata

      FRAME_INSIGHT_CMGA               = -189430
      FRAME_-189430_NAME               = 'INSIGHT_CMGA'
      FRAME_-189430_CLASS              = 4
      FRAME_-189430_CLASS_ID           = -189430
      FRAME_-189430_CENTER             = -189

      TKFRAME_-189430_RELATIVE         = 'INSIGHT_LANDER'
      TKFRAME_-189430_SPEC             = 'ANGLES'
      TKFRAME_-189430_UNITS            = 'DEGREES'
      TKFRAME_-189430_AXES             = ( 3, 1, 3 )
      TKFRAME_-189430_ANGLES           = ( -77.879965, -133.999970, 0.0 )

   \begintext


Landed East Medium Gain Antenna Frame
-------------------------------------

   According to [6], the Landed East Medium Gain antenna boresight --
   +Z axis of the INSIGHT_LMGA_EAST frame -- is the (-0.2360, 0.8508,
   -0.4695) vector in the lander mechanical frame. The antenna clock
   reference direction -- +X axis of the INSIGHT_LMGA_EAST -- is chosen
   arbitrarily to be in the lander XY plane in the -X/-Y quadrant.
 
   The INSIGHT_LANDER frame can be transformed to the INSIGHT_LMGA_EAST
   frame by two rotations: first by +195.503269 degrees about the +Z
   axis, then by +118.002045 degrees about +X axis.

   This diagram illustrates the INSIGHT_LMGA_EAST frame (top view of
   the lander deck for landed configuration):

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar   
                  `     panel    
                   \            ^ +Zlmgae
                    `.         .
                      `--H-
                      ___H__  '
                     +Ylnd ^ * .
                    /      |     ' > +Xlmgae
                   /       |      
             --    |       | +Zlnd  |
            | =====|<------x +Xcru  |
             -- +Xlnd   .-' \       |                _
                   \ <-'     \      o==============='_' IDA
                 +Zcru        \   /
                     \________ V /
                         H    +Ycru
                      .--H--.     \\_
                    .'       `.   |__|
                   /           \
                  .  -Y solar   .      
                  |    panel    |    +Zlnd and +Xcru are into the page.
                  `~ ~ ~ ~ ~ ~ ~'
                                   +Zlmgae points ~28 degrees above the page.

                                   +Ylmgae points ~62 degrees into the page.

   Since the frame definition below contains the reverse transformation
   (i.e. from the antenna frame to the lander frame), the order and the
   signs of the rotations are reversed.  

   \begindata

      FRAME_INSIGHT_LMGA_EAST          = -189440
      FRAME_-189440_NAME               = 'INSIGHT_LMGA_EAST'
      FRAME_-189440_CLASS              = 4
      FRAME_-189440_CLASS_ID           = -189440
      FRAME_-189440_CENTER             = -189

      TKFRAME_-189440_RELATIVE         = 'INSIGHT_LANDER'
      TKFRAME_-189440_SPEC             = 'ANGLES'
      TKFRAME_-189440_UNITS            = 'DEGREES'
      TKFRAME_-189440_AXES             = ( 3, 1, 3 )
      TKFRAME_-189440_ANGLES           = ( -195.503269, -118.002045, 0.0 )

   \begintext


Landed West Medium Gain Antenna Frame
-------------------------------------

   According to [6], the Landed West Medium Gain antenna boresight --
   +Z axis of the INSIGHT_LMGA_WEST frame -- is the (0.0923, -0.8781,
   -0.4695) vector in the lander mechanical frame. The antenna clock
   reference direction -- +X axis of the INSIGHT_LMGA_WEST -- is chosen
   arbitrarily to be in the lander XY plane in the +X/+Y quadrant.
 
   The INSIGHT_LANDER frame can be transformed to the INSIGHT_LMGA_WEST
   frame by two rotations: first by +6.000514 degrees about the +Z
   axis, then by +118.001706 degrees about +X  axis.
 
   This diagram illustrates the INSIGHT_LMGA_WEST frame (top view of
   the lander deck for landed configuration):

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.       .'   | _|
                      `--H--'     //
                      ___H_______//
                     /     ^+Ylnd \
                    /      |       \
                   /       |        \
             --    |       | +Zlnd  |
            | =====|<------x +Xcru  |
             -- +Xlnd   .-' \       |                _
               +Zcru <-'     \      o==============='_' IDA
             +Xlmgaw < .      \   /
                          '* _ V /
                          .   +Ycru
                                  \\_
                         '    .   |__|
                        v      \
                 +Zlmgaw        .      
                                |    +Zlnd and +Xcru are into the page.
                  `~ ~ ~ ~ ~ ~ ~'
                                   +Zlmgaw points ~28 degrees above the page.

                                   +Ylmgaw points ~62 degrees into the page.

   Since the frame definition below contains the reverse transformation
   (i.e. from the antenna frame to the lander frame), the order and the
   signs of the rotations are reversed.

   \begindata

      FRAME_INSIGHT_LMGA_WEST          = -189450
      FRAME_-189450_NAME               = 'INSIGHT_LMGA_WEST'
      FRAME_-189450_CLASS              = 4
      FRAME_-189450_CLASS_ID           = -189450
      FRAME_-189450_CENTER             = -189

      TKFRAME_-189450_RELATIVE         = 'INSIGHT_LANDER'
      TKFRAME_-189450_SPEC             = 'ANGLES'
      TKFRAME_-189450_UNITS            = 'DEGREES'
      TKFRAME_-189450_AXES             = ( 3, 1, 3 )
      TKFRAME_-189450_ANGLES           = ( -6.000514, -118.001706, 0.0 )

   \begintext


Landed/EDL UHF Helix Antenna Frame
----------------------------------

   According to [6], the Landed/EDL UHF Helix antenna boresight -- +Z
   axis of the INSIGHT_HELIX frame -- is the (0, 0, -1) vector in the
   lander mechanical frame and its clock reference direction -- +X axis
   of the INSIGHT_HELIX frame -- is the (1, 0, 0) vector in the lander
   mechanical frame.
 
   The INSIGHT_LANDER frame can be transformed to the INSIGHT_HELIX
   frame by a single rotation of 180 degrees about +X axis.

   This diagram illustrates the INSIGHT_HELIX frame (top view of
   the lander deck for landed configuration):

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.       .'   | _|
                      `--H--'     //
                      ___H_______//
                     /     ^+Ylnd \
                  +Xhelix  |       \
                   /    <------o +Zhelix
             --    |       |   |    |
            | =====|<------x   |    |
             -- +Xlnd   .-' \  |    |                _
                   \ <-'     \ V    o==============='_' IDA
                 +Zcru        \  +Yhelix
                     \________ V /
                         H    +Ycru
                      .--H--.     \\_
                    .'       `.   |__|
                   /           \
                  .  -Y solar   .      
                  |    panel    |    +Zlnd and +Xcru are into the page.
                  `~ ~ ~ ~ ~ ~ ~'
                                     +Z helix is out of the page.

   Since the frame definition below contains the reverse transformation
   (i.e. from the antenna frame to the lander frame), the order and the
   signs of the rotations are reversed.

   \begindata

      FRAME_INSIGHT_HELIX              = -189460
      FRAME_-189460_NAME               = 'INSIGHT_HELIX'
      FRAME_-189460_CLASS              = 4
      FRAME_-189460_CLASS_ID           = -189460
      FRAME_-189460_CENTER             = -189

      TKFRAME_-189460_RELATIVE         = 'INSIGHT_LANDER'
      TKFRAME_-189460_SPEC             = 'ANGLES'
      TKFRAME_-189460_UNITS            = 'DEGREES'
      TKFRAME_-189460_AXES             = ( 3, 1, 3 )
      TKFRAME_-189460_ANGLES           = ( 0.0, 180.0, 0.0 )

   \begintext


EDL Wrap Around Patch Antenna Frame
-----------------------------------

   According to [9], the EDL Wrap Around Patch antenna boresight -- +Z
   axis of the INSIGHT_WPA frame -- is the (0, 0, -1) vector in the
   lander mechanical frame and its clock reference direction -- +X axis
   of the INSIGHT_WPA frame -- is the (1, 0, 0) vector in the
   lander mechanical frame.
 
   The INSIGHT_LANDER frame can be transformed to the INSIGHT_WPA frame
   by a single rotation of 180 degrees about the +X axis.

   This diagram illustrates the INSIGHT_WPA frame (parachute cone 
   side view for EDL configuration):
                       
                       _________
                    .-'         `- 
                   / +Ylnd ^       \
                  /        |        \
                 /         |         \
               +Xwpa       |  +Zlnd   |
                |   <------*  +Xcru   |
               +Xlnd    .-'|\ +Zwpa   |
                 \   <-'   | \       /
                +Zcru      |  \     /
                   \       V   V   /  
                    ` +Ywpa     +Ycru.    +Zlnd and +Xcru are into the page.
                        -------'           
                                              +Zwpa is out of the page. 

   Since the frame definition below contains the reverse transformation
   (i.e. from the antenna frame to the lander frame), the order and the
   signs of the rotations are reversed.

   \begindata

      FRAME_INSIGHT_WPA                = -189470
      FRAME_-189470_NAME               = 'INSIGHT_WPA'
      FRAME_-189470_CLASS              = 4
      FRAME_-189470_CLASS_ID           = -189470
      FRAME_-189470_CENTER             = -189

      TKFRAME_-189470_RELATIVE         = 'INSIGHT_LANDER'
      TKFRAME_-189470_SPEC             = 'ANGLES'
      TKFRAME_-189470_UNITS            = 'DEGREES'
      TKFRAME_-189470_AXES             = ( 3, 1, 3 )
      TKFRAME_-189470_ANGLES           = ( 0.0, 180.0, 0.0 )

   \begintext


Payload Frame
-------------

   According to [11], the INSIGHT_PAYLOAD frame +Z axis is along the
   lander frame +Z axis and its +X axis is along the lander frame -X
   axis.
 
   The INSIGHT_PAYLOAD frame is defined as a fixed-offset frame with
   respect to the INSIGHT_LANDER frame.
 
   The INSIGHT_LANDER frame can be transformed to the INSIGHT_PAYLOAD
   frame by a single rotation of 180 degrees about +Z axis.
 
   This diagram illustrates the INSIGHT_PAYLOAD frame (top view of the
   lander deck for landed configuration):

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.       .'   | _|
                      `--H--'     //
                      ___H_______//
                     /     ^+Ylnd \
                    /      |       \
                   /       |        \
             --    |       |        |
            | =====|<------x        |
             -- +Xlnd                     +Xp        _
                   \                x------> ======='_' IDA
                    \             / |
                     \___________/  |
                         H       \\ |
                      .--H--.     \ v +Yp
                    .'       `.   |__ 
                   /           \
                  .  -Y solar   .      
                  |    panel    |    +Zlnd and +Zp are into the page.
                  `~ ~ ~ ~ ~ ~ ~'


   Since the frame definition below contains the reverse transformation
   (i.e. from the  INSIGHT_PAYLOAD frame to the INSIGHT_LANDER frame),
   the order and the signs of the rotations are reversed.

   \begindata

      FRAME_INSIGHT_PAYLOAD            = -189100
      FRAME_-189100_NAME               = 'INSIGHT_PAYLOAD'
      FRAME_-189100_CLASS              = 4
      FRAME_-189100_CLASS_ID           = -189100
      FRAME_-189100_CENTER             = -189

      TKFRAME_-189100_RELATIVE         = 'INSIGHT_LANDER'
      TKFRAME_-189100_SPEC             = 'ANGLES'
      TKFRAME_-189100_UNITS            = 'DEGREES'
      TKFRAME_-189100_AXES             = ( 3, 1, 3 )
      TKFRAME_-189100_ANGLES           = ( 180.0, 0.0, 0.0 )

   \begintext


SEIS Frames
-------------------------------------------------------------------------------

   This section defines frames for the SEIS experiment.


SEIS Frame
----------

   According to [12], the INSIGHT_SEIS frame +Z axis is along the
   instrument center axis and points towards the top and its +X axis
   point towards the tether side.
 
   The INSIGHT_SEIS frame is defined as a fixed-offset frame with
   respect to the INSIGHT_LANDER frame.
 
   The nominal deployed position the INSIGHT_LANDER frame can be
   transformed to the INSIGHT_SEIS frame by a single rotation of 180
   degrees about +X axis.
 
   This diagram illustrates the INSIGHT_SEIS frame (top view of the
   lander deck for landed configuration):

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.       .'   | _|
                      `--H--'     //
                      ___H_______//
                     /     ^+Ylnd \
                    /      |       \
                   /       |        \
             --    |       |        |  +Xseis .-.
            | =====|<------x        |   <------o|
             -- +Xlnd               |          |     _
                   \                o==========|===='_' IDA
                    \             /            |
                     \___________/             v
                         H       \\             +Yseis   
                      .--H--.     \\_
                    .'       `.   |__|
                   /           \
                  .  -Y solar   .      
                  |    panel    |    +Zlnd is into the page.
                  `~ ~ ~ ~ ~ ~ ~'
                                     +Zseis is out of the page.


   Since the frame definition below contains the reverse transformation
   (i.e. from the  INSIGHT_SEIS frame to the INSIGHT_LANDER frame), the
   order and the signs of the rotations are reversed.

   \begindata

      FRAME_INSIGHT_SEIS               = -189700
      FRAME_-189700_NAME               = 'INSIGHT_SEIS'
      FRAME_-189700_CLASS              = 4
      FRAME_-189700_CLASS_ID           = -189700
      FRAME_-189700_CENTER             = -189

      TKFRAME_-189700_RELATIVE         = 'INSIGHT_LANDER'
      TKFRAME_-189700_SPEC             = 'ANGLES'
      TKFRAME_-189700_UNITS            = 'DEGREES'
      TKFRAME_-189700_AXES             = ( 3, 1, 3 )
      TKFRAME_-189700_ANGLES           = ( 0.0, 180.0, 0.0 )

   \begintext


WTS Frame
---------

   According to [12], the INSIGHT_WTS frame +Z axis is along the
   instrument center axis and points towards the top and its +X axis
   point towards the foot to be placed on the SEIS tether side.
 
   The INSIGHT_WTS frame is defined as a fixed-offset frame with
   respect to the INSIGHT_LANDER frame.
 
   The nominal deployed position the INSIGHT_LANDER frame can be
   transformed to the INSIGHT_WTS frame by a single rotation of 180
   degrees about +X axis.
 
   This diagram illustrates the INSIGHT_WTS frame (top view of the
   lander deck for landed configuration):

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.       .'   | _|
                      `--H--'     //
                      ___H_______//
                     /     ^+Ylnd \
                    /      |       \
                   /       |        \
             --    |       |        |  +Xwts  .-.
            | =====|<------x        |   <------o|
             -- +Xlnd               |          |     _
                   \                o==========|===='_' IDA
                    \             /            |
                     \___________/             v
                         H       \\             +Ywts
                      .--H--.     \\_
                    .'       `.   |__|
                   /           \
                  .  -Y solar   .      
                  |    panel    |    +Zlnd is into the page.
                  `~ ~ ~ ~ ~ ~ ~'
                                     +Zwts is out of the page.


   Since the frame definition below contains the reverse transformation
   (i.e. from the  INSIGHT_WTS frame to the INSIGHT_LANDER frame), the
   order and the signs of the rotations are reversed.

   \begindata

      FRAME_INSIGHT_WTS                = -189710
      FRAME_-189710_NAME               = 'INSIGHT_WTS'
      FRAME_-189710_CLASS              = 4
      FRAME_-189710_CLASS_ID           = -189710
      FRAME_-189710_CENTER             = -189

      TKFRAME_-189710_RELATIVE         = 'INSIGHT_LANDER'
      TKFRAME_-189710_SPEC             = 'ANGLES'
      TKFRAME_-189710_UNITS            = 'DEGREES'
      TKFRAME_-189710_AXES             = ( 3, 1, 3 )
      TKFRAME_-189710_ANGLES           = ( 0.0, 180.0, 0.0 )

   \begintext


HP3 Frames
-------------------------------------------------------------------------------

   This section defines frames for the HP3 experiment.


HP3 Frame
---------

   According to [12], the INSIGHT_HP3 frame +Z axis is along the
   instrument center axis and points towards the top and its +X axis
   point towards the tether side.
 
   The INSIGHT_HP3 frame is defined as a fixed-offset frame with
   respect to the INSIGHT_LANDER frame.
 
   The nominal deployed position the INSIGHT_LANDER frame can be
   transformed to the INSIGHT_HP3 frame by a single rotation of 180
   degrees about +X axis.
 
   This diagram illustrates the INSIGHT_HP3 frame (top view of the
   lander deck for landed configuration):

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.       .'   | _|
                      `--H--'     //
                      ___H_______//
                     /     ^+Ylnd \
                    /      |       \  +Xhp3  H
                   /       |        \ <------o===H 
             --    |       |        |        |
            | =====|<------x        |        |
             -- +Xlnd               |        |       _
                   \                o======= v ====='_' IDA
                    \             /           +Yhp3
                     \___________/              
                         H       \\             
                      .--H--.     \\_
                    .'       `.   |__|
                   /           \
                  .  -Y solar   .      
                  |    panel    |    +Zlnd is into the page.
                  `~ ~ ~ ~ ~ ~ ~'
                                     +Zhp3 is out of the page.


   Since the frame definition below contains the reverse transformation
   (i.e. from the  INSIGHT_HP3 frame to the INSIGHT_LANDER frame), the
   order and the signs of the rotations are reversed.

   \begindata

      FRAME_INSIGHT_HP3                = -189810
      FRAME_-189810_NAME               = 'INSIGHT_HP3'
      FRAME_-189810_CLASS              = 4
      FRAME_-189810_CLASS_ID           = -189810
      FRAME_-189810_CENTER             = -189

      TKFRAME_-189810_RELATIVE         = 'INSIGHT_LANDER'
      TKFRAME_-189810_SPEC             = 'ANGLES'
      TKFRAME_-189810_UNITS            = 'DEGREES'
      TKFRAME_-189810_AXES             = ( 3, 1, 3 )
      TKFRAME_-189810_ANGLES           = ( 0.0, 180.0, 0.0 )

   \begintext


HP3 Mole Frame
--------------

   The INSIGHT_HP3_MOLE frame is provided solely for the sake of
   completeness. It is defined as a fixed-offset frame with respect to,
   and co-aligned with the INSIGHT_HP3 frame.
 
   This diagram illustrates the INSIGHT_HP3_MOLE frame (top view of the
   lander deck for landed configuration):

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.       .'   | _|
                      `--H--'     //
                      ___H_______//
                     /     ^+Ylnd \
                    /      |       \  +Xmole H
                   /       |        \ <------o===H 
             --    |       |        |        |
            | =====|<------x        |        |
             -- +Xlnd               |        |       _
                   \                o======= v ====='_' IDA
                    \             /           +Ymole
                     \___________/
                         H       \\
                      .--H--.     \\_
                    .'       `.   |__|
                   /           \
                  .  -Y solar   .      
                  |    panel    |    +Zlnd is into the page.
                  `~ ~ ~ ~ ~ ~ ~'
                                     +Zhp3 is out of the page.


   Since the frame definition below contains the reverse transformation
   (i.e. from the  INSIGHT_HP3_MOLE frame to the INSIGHT_HP3 frame),
   the order and the signs of the rotations are reversed.

   \begindata

      FRAME_INSIGHT_HP3_MOLE           = -189820
      FRAME_-189820_NAME               = 'INSIGHT_HP3_MOLE'
      FRAME_-189820_CLASS              = 4
      FRAME_-189820_CLASS_ID           = -189820
      FRAME_-189820_CENTER             = -189

      TKFRAME_-189820_RELATIVE         = 'INSIGHT_HP3'
      TKFRAME_-189820_SPEC             = 'ANGLES'
      TKFRAME_-189820_UNITS            = 'DEGREES'
      TKFRAME_-189820_AXES             = ( 3, 1, 3 )
      TKFRAME_-189820_ANGLES           = ( 0.0, 0.0, 0.0 )

   \begintext


HP3 Radiometer Frame
--------------------

   This section defines the INSIGHT_HP3_RAD frame as provided in [14]
   except for the frame name change (INSIGHT_HP3RAD -> INSIGHT_HP3_RAD). 

   The HP3 Radiometer measures the temperature of two patches of the
   surface, one near the lander (~1 m), one more distant (~3.5 m). HP3
   Radiometer is mounted on the lower side of the lander deck. The HP3
   Radiometer frame INSIGHT_HP3_RAD is fixed with respect to the lander
   frame INSIGHT_LANDER, and defined as follows:

      -  +Z is the normal of the backcap plane of the instrument
 
      -  +Y lies nominally in the rover X-Y plane and points roughly
         into the same direction as the rover's +Y axis
 
      -  +X completes the right handed frame, pointing roughly into the
         same direction as the rover's -Z axis
 
      -  the origin is at the intersection of the instrument Z axis and
         the dust cover, i.e. the "Rotor Blade Nut"

   The reference frame, INSIGHT_LANDER, can be transformed into this
   frame, INSIGHT_HP3RAD, by the two rotations: first by -20 degrees
   about Z, then by  50 degrees about Y.
 
   This diagram illustrates the LANDER and HP3 Radiometer frames for
   landed configuration (top view of the lander deck):

    Top view:
    ---------
                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.       .'   | _|
                      `--H--'     //
                      ___H_______//
        +Yhp3rad ^   /     ^+Ylnd \
                  \ /      |       \
                   \       |        \
             --    |\      | +Zlnd  |
            | =====|<\-----x        |
             -- +Xlnd \             |                _
                   \   o +Xhp3rad   o==============='_' IDA
                     .'           / 
                   .'\___________/
                 .'     H       \\
      +Zhp3rad <'    .--H--.     \\_
                    .'       `.   |__|
                   /           \
                  .  -Y solar   .      
                  |    panel    |    +Zlnd is into the page
                  `~ ~ ~ ~ ~ ~ ~'   
                                     +Xhp3rad is out of the page


   Side view:
   ----------
               +Xlnd  <----X             
                           |             .o.
                           |            // \\
                     +Zlnd V           //   \\
                                      //     \\
           +Xhp3rad ^                //       \\
                     \              //         \\     IDA
                      \            //           \\  _
                    ___\____________             .o| |
                   |____o __________|              `.
                   |   /            |
                  /|__/________\\___|
                 //\ /          \\ / 
                //  /____________\\
               //  v              \\
             _//    +Zhp3rad       \\_        +Ylnd and +Yhp3rad 
            |__|                   |__|        are into the page

                   

   Since the frame definition below contains the reverse
   transformation, i.e. from the HP3RAD frame to the LANDER frame, the
   order of rotations is reversed and the signs of rotation angles are
   changed to the opposite ones.
 
   \begindata

      FRAME_INSIGHT_HP3_RAD            = -189800
      FRAME_-189800_NAME               = 'INSIGHT_HP3_RAD'
      FRAME_-189800_CLASS              = 4
      FRAME_-189800_CLASS_ID           = -189800
      FRAME_-189800_CENTER             = -189

      TKFRAME_-189800_RELATIVE         = 'INSIGHT_LANDER'
      TKFRAME_-189800_SPEC             = 'ANGLES'
      TKFRAME_-189800_UNITS            = 'DEGREES'
      TKFRAME_-189800_AXES             = ( 1, 3, 2 )
      TKFRAME_-189800_ANGLES           = ( 0.0, 20.0, -50.0 )

   \begintext


APSS Frames
-------------------------------------------------------------------------------

   This section defines frames for the APSS experiment.


APSS Magnetometer Frame
-----------------------

   According to [15], the INSIGHT_APSS_MAG frame +Z axis is normal to
   the sensor base and points towards the top, and its +Y axis points
   from the sensor toward the cable connector.
 
   The INSIGHT_APSS_MAG frame is defined as a fixed-offset frame with
   respect to the INSIGHT_LANDER frame.
 
   The INSIGHT_LANDER frame can be transformed to the INSIGHT_APSS_MAG
   frame by a single rotation of -148 degrees about +Z axis.
 
   This diagram illustrates the INSIGHT_APSS_MAG frame (top view of the
   lander deck for landed configuration):

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.       .'   | _|
                      `--H--'     //
                      ___H_______//
                     /     ^+Ylnd \
                    /      |      x\
                   /       |    .' \\
             --    |       |  <'    \
            | =====|<------x +Ymag  |V +Xmag
             -- +Xlnd               |                _
                   \                o==============='_' IDA
                    \             /
                     \___________/
                         H       \\
                      .--H--.     \\_
                    .'       `.   |__|
                   /           \
                  .  -Y solar   .      
                  |    panel    |    +Zlnd and +Z mag are into the page.
                  `~ ~ ~ ~ ~ ~ ~'


   Since the frame definition below contains the reverse transformation
   (i.e. from the  INSIGHT_APSS_MAG frame to the INSIGHT_LANDER frame),
   the order and the signs of the rotations are reversed.

   \begindata

      FRAME_INSIGHT_APSS_MAG           = -189610
      FRAME_-189610_NAME               = 'INSIGHT_APSS_MAG'
      FRAME_-189610_CLASS              = 4
      FRAME_-189610_CLASS_ID           = -189610
      FRAME_-189610_CENTER             = -189

      TKFRAME_-189610_RELATIVE         = 'INSIGHT_LANDER'
      TKFRAME_-189610_SPEC             = 'ANGLES'
      TKFRAME_-189610_UNITS            = 'DEGREES'
      TKFRAME_-189610_AXES             = ( 3, 1, 3 )
      TKFRAME_-189610_ANGLES           = ( 0.0, 0.0, 148.0 )

   \begintext


APSS Pressure Sensor Frame
--------------------------

   According to [15], the INSIGHT_APSS_PS frame +Z axis is along the
   pressure port central axis, pointing down from the top toward the
   base, and +X axis points from the central axis towards the reference
   mounting hole.

   The INSIGHT_APSS_PS frame is defined as a fixed-offset frame with
   respect to the INSIGHT_LANDER frame.
 
   The INSIGHT_LANDER frame can be transformed to the INSIGHT_APSS_PS
   frame by a single rotation of +22.5 degrees about +Z axis.
 
   This diagram illustrates the INSIGHT_APSS_PS frame (top view of the
   lander deck for landed configuration):

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.       .'   | _|
                      `--H--'     //
                      ___H_______//
                     /+Ylnd^      \
                    /      |  ^ +Yps
                +Xps <.    | /      \
             --    |   `-. |/       |
            | =====|<------x        |
             -- +Xlnd               |                _
                   \                o==============='_' IDA
                    \             /
                     \___________/
                         H       \\
                      .--H--.     \\_
                    .'       `.   |__|
                   /           \
                  .  -Y solar   .      
                  |    panel    |    +Zlnd and +Zps are into the page.
                  `~ ~ ~ ~ ~ ~ ~'


   Since the frame definition below contains the reverse transformation
   (i.e. from the  INSIGHT_APSS_PS frame to the INSIGHT_LANDER frame),
   the order and the signs of the rotations are reversed.

   \begindata

      FRAME_INSIGHT_APSS_PS            = -189620
      FRAME_-189620_NAME               = 'INSIGHT_APSS_PS'
      FRAME_-189620_CLASS              = 4
      FRAME_-189620_CLASS_ID           = -189620
      FRAME_-189620_CENTER             = -189

      TKFRAME_-189620_RELATIVE         = 'INSIGHT_LANDER'
      TKFRAME_-189620_SPEC             = 'ANGLES'
      TKFRAME_-189620_UNITS            = 'DEGREES'
      TKFRAME_-189620_AXES             = ( 3, 1, 3 )
      TKFRAME_-189620_ANGLES           = ( 0.0, 0.0, -22.5 )

   \begintext


APSS TWINS Frames
-----------------

   According to [15], the INSIGHT_APSS_TWINS+Y and INSIGHT_APSS_TWINS-Y
   frames +Z axes point up from the mounting base towards the sensor, -Y
   axes point along the sensor axis from the mount side toward the
   sensor tip.

   The INSIGHT_APSS_TWINS+Y and INSIGHT_APSS_TWINS-Y frames are defined
   as fixed-offset frames with respect to the INSIGHT_LANDER frame.
 
   The INSIGHT_LANDER frame can be transformed to the
   INSIGHT_APSS_TWINS+Y frame by a single rotation of 180 degrees about
   +X axis. 

   The INSIGHT_LANDER frame can be transformed to the
   INSIGHT_APSS_TWINS-Y frame by two rotations -- of 180 degrees about
   +X axis, then by 180 degrees about +Z axis.
 
   This diagram illustrates the INSIGHT_APSS_TWINS+Y and
   INSIGHT_APSS_TWINS-Y frames (top view of the lander deck for landed
   configuration):

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.       .'   | _|
                      `--H--'     //
                      ___H_+Ylnd_//
                     /  <--^-o    \
                    /+Xtmy | |     \
                   /       | |      \
             --    |       | v+Ytpy |
            | =====|<------x        |
             -- +Xlnd        ^+Ytmy |                _
                   \         |      o==============='_' IDA
                    \        |    /
                     \_______o----> +Xtmy
                         H       \\
                      .--H--.     \\_
                    .'       `.   |__|
                   /           \
                  .  -Y solar   .      
                  |    panel    |    +Zlnd is into the page.
                  `~ ~ ~ ~ ~ ~ ~'
                                    +Ztpy and +Ztmy are out of the page.


   Since the frame definitions below contains the reverse
   transformations (i.e. from the  INSIGHT_APSS_TWINS+Y frame to the
   INSIGHT_LANDER frame, and from the  INSIGHT_APSS_TWINS-Y frame to the
   INSIGHT_LANDER frame), the order and the signs of the rotations are
   reversed.

   \begindata

      FRAME_INSIGHT_APSS_TWINS+Y       = -189630
      FRAME_-189630_NAME               = 'INSIGHT_APSS_TWINS+Y'
      FRAME_-189630_CLASS              = 4
      FRAME_-189630_CLASS_ID           = -189630
      FRAME_-189630_CENTER             = -189

      TKFRAME_-189630_RELATIVE         = 'INSIGHT_LANDER'
      TKFRAME_-189630_SPEC             = 'ANGLES'
      TKFRAME_-189630_UNITS            = 'DEGREES'
      TKFRAME_-189630_AXES             = ( 3, 1, 3 )
      TKFRAME_-189630_ANGLES           = ( 0.0, 180.0, 0.0 )

      FRAME_INSIGHT_APSS_TWINS-Y       = -189640
      FRAME_-189640_NAME               = 'INSIGHT_APSS_TWINS-Y'
      FRAME_-189640_CLASS              = 4
      FRAME_-189640_CLASS_ID           = -189640
      FRAME_-189640_CENTER             = -189

      TKFRAME_-189640_RELATIVE         = 'INSIGHT_LANDER'
      TKFRAME_-189640_SPEC             = 'ANGLES'
      TKFRAME_-189640_UNITS            = 'DEGREES'
      TKFRAME_-189640_AXES             = ( 3, 1, 3 )
      TKFRAME_-189640_ANGLES           = ( 0.0, 180.0, 180.0 )

   \begintext


ICC Frames
-------------------------------------------------------------------------------

   This section defines frames for the ICC subsystem.


Instrument Context Camera Frame
-------------------------------

   According to [16], the INSIGHT_ICC frame +Z axis is along the camera
   boresight and +Y is along the camera image columns, pointing up away
   from the surface.
 
   The INSIGHT_ICC frame is defined as a fixed-offset frame with
   respect to the INSIGHT_PAYLOAD frame.
 
   Nominally the INSIGHT_PAYLOAD frame can be transformed to the
   INSIGHT_ICC frame by a three rotations -- first +52 degrees about
   +Y, then by -4 degrees about +X, then -90 deg about +Z.
 
   This diagram illustrates the INSIGHT_ICC frame (top view of the
   lander deck for landed configuration):

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.       .'   | _|
                      `--H--'     //
                      ___H_______//
                     /     ^+Ylnd \
                    /      |       \
                   /       |        \
             --    |       |          +Xicc
            | =====|<------x         ^
             -- +Xlnd               /     +Xp        _
                   \               /x------> ======='_' IDA
                    \             *..
                     \___________/  |``> +Zicc
                         H       \\ |    +Yicc
                      .--H--.     \ v +Yp
                    .'       `.   |__ 
                   /           \
                  .  -Y solar   .      
                  |    panel    |    +Zlnd and +Zp are into the page.
                  `~ ~ ~ ~ ~ ~ ~'
                                     +Zicc points 52 deg into the page.

                                     +Yicc points 38 deg above the page.


   The actual INSIGHT_ICC frame orientation provided in the frame
   definition below was computed using the CAHVOR(E) camera model file,
   [18]. According to this model the reference frame, INSIGHT_PAYLOAD,
   can be transformed into the camera frame, INSIGHT_ICC, by the
   following sequence of rotations: first by 51.70218243 degrees about
   Y, then by -3.76245486 degrees about X, and finally by -87.14567449
   degrees about Z.
 
   The frame definition below contains the opposite of this
   transformation because Euler angles specified in it define rotations
   from the "destination" frame to the "reference" frame.

   \begindata

      FRAME_INSIGHT_ICC                = -189111
      FRAME_-189111_NAME               = 'INSIGHT_ICC'
      FRAME_-189111_CLASS              = 4
      FRAME_-189111_CLASS_ID           = -189111
      FRAME_-189111_CENTER             = -189
      TKFRAME_-189111_RELATIVE         = 'INSIGHT_PAYLOAD'
      TKFRAME_-189111_SPEC             = 'ANGLES'
      TKFRAME_-189111_UNITS            = 'DEGREES'
      TKFRAME_-189111_AXES             = (    2,        1,        3     )
      TKFRAME_-189111_ANGLES           = (  -51.702,    3.762,   87.146 )

   \begintext


IDA Frames
-------------------------------------------------------------------------------

   This section defines frames for the Instrument Deployment Arm (IDA)
   joints (SHOULDER_AZ, SHOULDER_EL, ELBOW, and WRIST) and instruments
   and tools (IDC, EFFECTOR, GRAPPLE_BASE, SCOOP, BLADE, and GRAPPLE).


IDA Gimbal Frames Schematic Diagram
-------------------------------------------

   This diagram illustrates the IDA joint frames (the IDA is shown fully
   extended in the "zero" gimbal angle configuration):

   Top view:
   ---------

                                +Zpayload(in) x-----> +Xpayload
                                              |
                                              |
                                              |
                                              V +Ypayload
             +Zse
              ^
              |
         .____|_.
         |    | | +Xsa +Xse
         | x--x-->-->
   +Zsa(in)| +Yse(in)                 
         ._|____.                    +Ze                       +Zw
           | | |______________________^                        ^
           V |                        ||                       |
        +Ysa .________________________||                       |_____ 
                                     |||______________________'|.    |
                                     |x-----> +Xe             |x-----> +Xw
                                     |_+Ye(in)________________| +Yw(in)
                                                              .______| 
                                     

   Side view:
   ----------
                               +Ypayload(out) o-----> +Xpayload
                                              |
                                              |
                                              |
                                              V +Zpayload         Scoop
                                                               ______
                                                              |     /
                                                              |    /
           .___                       _                       | __/
          /    \_____________________/ \______________________/ \ 
      +Zse(in)X-----> +Xse    +Ze(in) X-----> +Xe      +Zw(in) X-----> +Xw
        /     | |___________________\ | /____________________\ | /
  +Ysa(out)o-----> +Xsa              \|/   ||                 \|/  
      /____|__|_|                     |    |`-.                |    
           |  V                       V    `--' IDC            V     
           |  +Yse                    +Ye                      +Yw
           V                                                   |
         +Zsa                                                 .^.
                                                              | |
                                                              \ /
                                                                 Grapple


IDA Shoulder Azimuth Frame
--------------------------

   The INSIGHT_IDA_SHOULDER_AZ frame is a CK-based frame with
   orientation given relative to the INSIGHT_PAYLOAD frame.
 
   The INSIGHT_IDA_SHOULDER_AZ frame is defined as follows:

      -  +Z axis is along the shoulder azimuth joint rotation axis and
         point down toward the ground; nominally, this axis is
         co-aligned with the payload frame +Z axis;
 
      -  +X axis lies in the lander deck plane and points from the
         shoulder azimuth joint rotation axis toward the shoulder
         elevation joint rotation axis; nominally, it is co-aligned
         with the payload frame +X axis for the torso joint in zero
         position;
 
      -  +Y completes the right-handed frame;

   The origin of the INSIGHT_IDA_SHOULDER_AZ frame is located at the
   intersection of the shoulder azimuth rotation axis and the lander
   deck plane.

   \begindata

      FRAME_INSIGHT_IDA_SHOULDER_AZ    = -189121
      FRAME_-189121_NAME               = 'INSIGHT_IDA_SHOULDER_AZ'
      FRAME_-189121_CLASS              = 3
      FRAME_-189121_CLASS_ID           = -189121
      FRAME_-189121_CENTER             = -189
      CK_-189121_SCLK                  = -189
      CK_-189121_SPK                   = -189

   \begintext


IDA Shoulder Elevation Frame
----------------------------

   The INSIGHT_IDA_SHOULDER_EL frame is a CK-based frame with
   orientation given relative to the INSIGHT_IDA_SHOULDER_AZ frame.
 
   The INSIGHT_IDA_SHOULDER_EL frame is defined as follows:

      -  +Z axis is along the shoulder elevation joint rotation axis
         and points in the direction of the -Y axis of the
         INSIGHT_IDA_SHOULDER_AZ frame;
 
      -  +X is perpendicular to and intersects both the shoulder
         elevation and the elbow joint rotation axes and points from
         the shoulder elevation axis towards the elbow axis;
 
      -  +Y completes the right-handed frame;
 
   The origin of the INSIGHT_IDA_SHOULDER_EL frame is located in the
   middle of the shoulder gimbal.

   \begindata

      FRAME_INSIGHT_IDA_SHOULDER_EL    = -189122
      FRAME_-189122_NAME               = 'INSIGHT_IDA_SHOULDER_EL'
      FRAME_-189122_CLASS              = 3
      FRAME_-189122_CLASS_ID           = -189122
      FRAME_-189122_CENTER             = -189
      CK_-189122_SCLK                  = -189
      CK_-189122_SPK                   = -189

   \begintext


IDA Elbow Frame
---------------

   The INSIGHT_IDA_ELBOW frame is a CK-based frame with orientation
   given relative to the IDA SHOULDER_EL frame.
 
   The INSIGHT_IDA_ELBOW frame is defined as follows:

      -  +Z axis is along the elbow joint rotation axis and points in
         the same direction as the +Z axis of the
         INSIGHT_IDA_SHOULDER_EL frame;
 
      -  +X is perpendicular to and intersects both the elbow and the
         wrist joint rotation axes and points from the elbow axis
         towards the wrist axis;
 
      -  +Y completes the right-handed frame;

   The origin of the INSIGHT_IDA_ELBOW frame is located in the middle
   of the elbow gimbal.

   \begindata

      FRAME_INSIGHT_IDA_ELBOW          = -189123
      FRAME_-189123_NAME               = 'INSIGHT_IDA_ELBOW'
      FRAME_-189123_CLASS              = 3
      FRAME_-189123_CLASS_ID           = -189123
      FRAME_-189123_CENTER             = -189
      CK_-189123_SCLK                  = -189
      CK_-189123_SPK                   = -189

   \begintext



IDA Wrist Frame
---------------

   The INSIGHT_IDA_WRIST frame is a CK-based frame with orientation
   given relative to the INSIGHT_IDA_ELBOW frame.
 
   The INSIGHT_IDA_WRIST frame is defined as follows:

      -  +Z axis is along the wrist joint rotation axis and points in
         the same direction as the +Z axis of the INSIGHT_IDA_ELBOW
         frame;
 
      -  +Y is perpendicular to the wrist axis and points away from the
         scoop;
 
      -  +X completes the right-handed frame;

   The origin of the INSIGHT_IDA_WRIST frame is located in the middle
   of the wrist gimbal.

   \begindata

      FRAME_INSIGHT_IDA_WRIST          = -189124
      FRAME_-189124_NAME               = 'INSIGHT_IDA_WRIST'
      FRAME_-189124_CLASS              = 3
      FRAME_-189124_CLASS_ID           = -189124
      FRAME_-189124_CENTER             = -189
      CK_-189124_SCLK                  = -189
      CK_-189124_SPK                   = -189

   \begintext


IDA Instrument and Tool Frames Schematic Diagram
------------------------------------------------

   This diagram illustrates the IDA instrument and tool frames (IDA
   Effector Instruments side view with the wrist joint in "0" position;
   instrument and tool frame offset angles are from [TBD]):
 
   IDA Effector Side view:

                                   ^ +Zblade
                                   |
                                   |
                                   |     +Xblade
                                   x----->            ..-> +Zscoop
                                  ||______________x-''
                                  |              /\
                                  |             /  \ 
                                  |            /    \
                                  |           /      V
                                  |+Zeff     /        +Xscoop
                                  |___^__ __/
                                  |___|__|
     ____________________________ /   |  \
                                 /    |   \
   x-----> +Xelb                <-----x-----> +Xeff
   | ____ ^ +Yidc ___________+Xga\    |   /   +Xwrist
   |   |  |                       \___|__/
   |   |--|---.                       |
   V   |  |   | +Zidc                 V +Ywrist            +Zelbow,
   +Yelb  x---x->--->                 | +Zga               +Zwrist,
       |      |      +Zidcr           |                    +Yidc, +Xidcr,
       `------|                       |                    +Yeff,
              |                       |                    +Yblade,
              V +Xidcr                |                    +Yscoop,
                                     / \                   +Yga
                                     | |               are into the page.
                                     | |
                                     |_|                   +Ygrapple
                                    /   \               is out the page.
                                    \   /
                                     \ /
                                      o-----> +Xgrapple
                                      |
                                      |
                                      |
                                      V +Zgrapple
                 

   Note that the IDC is mounted on the elbow link of the IDA while the
   SCOOP and GRAPPLE are mounted on the wrist gimbal. (The ISAD and
   BLADE are mounted on the SCOOP.)


IDC_REF and IDC Frames
----------------------

   Two frames are defined for IDC -- the IDC reference point frame
   (INSIGHT_IDA_IDC_REF) and the IDC camera frame (INSIGHT_IDA_IDC).

   The INSIGHT_IDA_IDC_REF frame is defined as follows:

      -  +Z axis points along the camera boresight;
 
      -  +Y axis points in the same direction as the +Z axis of the
         INSIGHT_IDA_ELBOW frame;
 
      -  +X completes the right-handed frame.

      -  the origin of this frame is located at the center of the front
         face of the camera.

   Nominally the INSIGHT_IDA_IDC_REF frame is rotated from the
   INSIGHT_IDA_ELBOW frame by +90 degrees about Y, then by +90 degrees
   about Z.
 
   While the INSIGHT_IDA_IDC_REF frame has fixed orientation with
   respect to the INSIGHT_IDA_ELBOW frame, it is defined as CK based
   frames to allow storing its orientation provided in the image
   headers as deflected IDC device orientation quaternion in CK files.

   \begindata

      FRAME_INSIGHT_IDA_IDC_REF        = -189131
      FRAME_-189131_NAME               = 'INSIGHT_IDA_IDC_REF'
      FRAME_-189131_CLASS              = 3
      FRAME_-189131_CLASS_ID           = -189131
      FRAME_-189131_CENTER             = -189
      CK_-189131_SCLK                  = -189
      CK_-189131_SPK                   = -189

   \begintext

   The INSIGHT_IDA_IDC frame is defined as follows:

      -  +Z axis points along the camera boresight;
 
      -  +X axis points in the same direction as the +Z axis of the
         INSIGHT_IDA_ELBOW frame;
 
      -  +Y completes the right-handed frame.

      -  the origin of this frame is located at the nodal point of the
         camera.

   Nominally the INSIGHT_IDA_IDC frame is rotated from the
   INSIGHT_IDA_IDC_REF frame by +90 degrees about Z and defined as a
   fixed-offset frame with respect to it.

   The actual INSIGHT_IDA_IDC frame orientation provided in the frame
   definition below was computed using the CAHVOR(E) camera model file,
   [19]. According to this model the reference frame,
   INSIGHT_IDA_IDC_REF, can be transformed into the camera frame,
   INSIGHT_IDA_IDC, by the following sequence of rotations: first by
   -0.38874186 degrees about Y, then by -0.86474082 degrees about X,
   and finally by 89.16016508 degrees about Z.
 
   The frame definition below contains the opposite of this
   transformation because Euler angles specified in it define rotations
   from the "destination" frame to the "reference" frame.

   \begindata

      FRAME_INSIGHT_IDA_IDC            = -189125
      FRAME_-189125_NAME               = 'INSIGHT_IDA_IDC'
      FRAME_-189125_CLASS              = 4
      FRAME_-189125_CLASS_ID           = -189125
      FRAME_-189125_CENTER             = -189
      TKFRAME_-189125_RELATIVE         = 'INSIGHT_IDA_IDC_REF'
      TKFRAME_-189125_SPEC             = 'ANGLES'
      TKFRAME_-189125_UNITS            = 'DEGREES'
      TKFRAME_-189125_AXES             = (    2,        1,        3     )
      TKFRAME_-189125_ANGLES           = (    0.389,    0.865,  -89.160 )

   \begintext


IDA Effector Frame
------------------

   The INSIGHT_IDA_EFFECTOR frame is a fixed offset frame with
   orientation given relative to the INSIGHT_IDA_WRIST frame.
 
   The INSIGHT_IDA_EFFECTOR frame is defined as follows:

      -  +X axis points in the same direction as the wrist +X axis;
 
      -  +Y axis points is the same direction as the wrist +Z axis;
 
      -  +Z completes the right-handed frame.

   The origin of the INSIGHT_IDA_EFFECTOR frame is located
   approximately at the middle of the wrist gimbal.
 
   The INSIGHT_IDA_WRIST frame can be transformed to the
   INSIGHT_IDA_EFFECTOR frame with one rotations -- +90 degrees about
   +X axis.
 
   Since the frame definition below contains the reverse
   transformation, from the INSIGHT_IDA_WRIST frame to the
   INSIGHT_IDA_WRIST frame, the order of rotations is reversed and the
   sign of rotation angles is changed to the opposite one.
 
   \begindata

      FRAME_INSIGHT_IDA_EFFECTOR       = -189126
      FRAME_-189126_NAME               = 'INSIGHT_IDA_EFFECTOR'
      FRAME_-189126_CLASS              = 4
      FRAME_-189126_CLASS_ID           = -189126
      FRAME_-189126_CENTER             = -189

      TKFRAME_-189126_RELATIVE         = 'INSIGHT_IDA_WRIST'
      TKFRAME_-189126_SPEC             = 'ANGLES'
      TKFRAME_-189126_UNITS            = 'DEGREES'
      TKFRAME_-189126_AXES             = ( 3, 1, 3 )
      TKFRAME_-189126_ANGLES           = ( 0.0, -90.0, 0.0 )

   \begintext


IDA Grapple Base Frame
----------------------

   The INSIGHT_IDA_GRAPPLE_BASE frame is a fixed offset frame with
   orientation given relative to the INSIGHT_IDA_EFFECTOR frame.
 
   The INSIGHT_IDA_GRAPPLE_BASE frame is defined as follows:

      -  +Y axis points in the same direction as the effector +Y axis;
 
      -  +Z axis points is the same direction as the effector -Z axis;
 
      -  +X completes the right-handed frame.

   The origin of the INSIGHT_IDA_GRAPPLE_BASE frame is located
   approximately at the middle of the wrist gimbal.
 
   The INSIGHT_IDA_EFFECTOR frame can be transformed to the
   INSIGHT_IDA_GRAPPLE_BASE frame by a single rotation of 180.0 degrees
   about Y axis.
 
   Since the frame definition below contains the reverse
   transformation, from the INSIGHT_IDA_GRAPPLE_BASE frame to the
   INSIGHT_IDA_EFFECTOR frame, the order of rotations is reversed and
   the signs of rotation angles are changed to the opposite ones.

   \begindata

      FRAME_INSIGHT_IDA_GRAPPLE_BASE   = -189127
      FRAME_-189127_NAME               = 'INSIGHT_IDA_GRAPPLE_BASE'
      FRAME_-189127_CLASS              = 4
      FRAME_-189127_CLASS_ID           = -189127
      FRAME_-189127_CENTER             = -189

      TKFRAME_-189127_RELATIVE         = 'INSIGHT_IDA_EFFECTOR'
      TKFRAME_-189127_SPEC             = 'ANGLES'
      TKFRAME_-189127_UNITS            = 'DEGREES'
      TKFRAME_-189127_AXES             = ( 3, 2, 3 )
      TKFRAME_-189127_ANGLES           = ( 0.0, 180.0, 0.0 )

   \begintext


IDA Scoop Frame
---------------

   The INSIGHT_IDA_SCOOP frame is a fixed offset frame with orientation
   given relative to the INSIGHT_IDA_EFFECTOR frame.
 
   The INSIGHT_IDA_SCOOP frame is defined as follows:

      -  Z axis is parallel to the scoop edge outside surface,
         perpendicular to the blade edge and points away from the
         blade;

      -  Y axis is along the wrist joint rotation axis and points in the
         same direction as the +Y axis of the INSIGHT_IDA_EFFECTOR frame;

      -  X completes the right-handed frame;

   The origin of the INSIGHT_IDA_SCOOP frame is located in the middle
   of the blade edge.
 
   The INSIGHT_IDA_EFFECTOR frame can be transformed to the
   INSIGHT_IDA_SCOOP frame by a single rotation of +82.0 degrees about
   Y axis.
 
   Since the frame definition below contains the reverse
   transformation, from the INSIGHT_IDA_SCOOP frame to the
   INSIGHT_IDA_EFFECTOR frame, the order of rotations is reversed and
   the signs of rotation angles are changed to the opposite ones.

   \begindata

      FRAME_INSIGHT_IDA_SCOOP          = -189128
      FRAME_-189128_NAME               = 'INSIGHT_IDA_SCOOP'
      FRAME_-189128_CLASS              = 4
      FRAME_-189128_CLASS_ID           = -189128
      FRAME_-189128_CENTER             = -189

      TKFRAME_-189128_RELATIVE         = 'INSIGHT_IDA_EFFECTOR'
      TKFRAME_-189128_SPEC             = 'ANGLES'
      TKFRAME_-189128_UNITS            = 'DEGREES'
      TKFRAME_-189128_AXES             = ( 3, 2, 3 )
      TKFRAME_-189128_ANGLES           = ( 0.0, -82.0, 0.0 )

   \begintext


IDA Blade Frame
---------------

   The INSIGHT_IDA_BLADE frame is a fixed offset frame with orientation
   given relative to the INSIGHT_IDA_EFFECTOR frame.

   The INSIGHT_IDA_BLADE frame is defined as follows:

      -  Z axis is parallel to the blade outside surface, perpendicular
         to the blade edge and points from the blade;
 
      -  Y axis is along the wrist joint rotation axis and points in
         the same direction as the +Y axis of the INSIGHT_IDA_EFFECTOR
         frame;
 
      -  X completes the right-handed frame;

   The origin of the INSIGHT_IDA_BLADE frame is located in the middle
   of the blade edge.
 
   The INSIGHT_IDA_EFFECTOR frame is nominally co-aligned with the
   INSIGHT_IDA_BLADE frame.
 
   Since the frame definition below contains the reverse
   transformation, from the INSIGHT_IDA_BLADE frame to the
   INSIGHT_IDA_EFFECTOR frame, the order of rotations is reversed and
   the signs of rotation angles are changed to the opposite ones.

   \begindata

      FRAME_INSIGHT_IDA_BLADE          = -189129
      FRAME_-189129_NAME               = 'INSIGHT_IDA_BLADE'
      FRAME_-189129_CLASS              = 4
      FRAME_-189129_CLASS_ID           = -189129
      FRAME_-189129_CENTER             = -189

      TKFRAME_-189129_RELATIVE         = 'INSIGHT_IDA_EFFECTOR'
      TKFRAME_-189129_SPEC             = 'ANGLES'
      TKFRAME_-189129_UNITS            = 'DEGREES'
      TKFRAME_-189129_AXES             = ( 3, 2, 3 )
      TKFRAME_-189129_ANGLES           = ( 0.0, 0.0, 0.0 )

   \begintext


IDA Grapple Frame
-------------------------------------------

   Because the grapple is a free dangling tool, the INSIGHT_IDA_GRAPPLE
   frame is defined as a CK-base frame. It is provided in the FK solely
   for completeness sake as it is unlikely that its time varying
   orientation needs to be -- and will ever be -- reconstructed.

   The INSIGHT_IDA_GRAPPLE frame is defined as follows:

      -  +Z axis is along the tool, pointing from the connector side
         towards the grappling side;

      -  +Y axis is [TBD];

      -  +X completes the right-handed frame;

   The origin of the INSIGHT_IDA_GRAPPLE frame is located at the center 
   between the grappling tips.

   \begindata

      FRAME_INSIGHT_IDA_GRAPPLE        = -189130
      FRAME_-189130_NAME               = 'INSIGHT_IDA_GRAPPLE'
      FRAME_-189130_CLASS              = 3
      FRAME_-189130_CLASS_ID           = -189130
      FRAME_-189130_CENTER             = -189
      CK_-189130_SCLK                  = -189
      CK_-189130_SPK                   = -189

   \begintext


INSIGHT NAIF ID Codes -- Definition Section
-------------------------------------------------------------------------------

   This section contains name to NAIF ID mappings for INSIGHT.

   \begindata

      NAIF_BODY_NAME                  += ( 'INSIGHT' )
      NAIF_BODY_CODE                  += ( -189 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_LANDING_SITE' )
      NAIF_BODY_CODE                  += ( -189900 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_LANDER' )
      NAIF_BODY_CODE                  += ( -189000 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_CLGA_TX' )
      NAIF_BODY_CODE                  += ( -189410 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_CLGA_RX' )
      NAIF_BODY_CODE                  += ( -189420 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_CMGA' )
      NAIF_BODY_CODE                  += ( -189430 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_LMGA_EAST' )
      NAIF_BODY_CODE                  += ( -189440 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_LMGA_WEST' )
      NAIF_BODY_CODE                  += ( -189450 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_HELIX' )
      NAIF_BODY_CODE                  += ( -189460 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_WPA' )
      NAIF_BODY_CODE                  += ( -189470 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_PAYLOAD' )
      NAIF_BODY_CODE                  += ( -189100 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_CAL_TARGET_1' )
      NAIF_BODY_CODE                  += ( -189101 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_CAL_TARGET_2' )
      NAIF_BODY_CODE                  += ( -189102 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_CAL_TARGET_3' )
      NAIF_BODY_CODE                  += ( -189103 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_CAL_TARGET_4' )
      NAIF_BODY_CODE                  += ( -189104 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_CAL_TARGET_5' )
      NAIF_BODY_CODE                  += ( -189105 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_CAL_TARGET_6' )
      NAIF_BODY_CODE                  += ( -189106 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_SEIS' )
      NAIF_BODY_CODE                  += ( -189700 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_WTS' )
      NAIF_BODY_CODE                  += ( -189710 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_HP3' )
      NAIF_BODY_CODE                  += ( -189810 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_HP3_MOLE' )
      NAIF_BODY_CODE                  += ( -189820 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_HP3_RAD' )
      NAIF_BODY_CODE                  += ( -189800 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_HP3_RAD_NEAR' )
      NAIF_BODY_CODE                  += ( -189801 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_HP3_RAD_FAR' )
      NAIF_BODY_CODE                  += ( -189802 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_HP3_RAD_TEM' )
      NAIF_BODY_CODE                  += ( -189810 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_APSS_MAG' )
      NAIF_BODY_CODE                  += ( -189610 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_APSS_PS' )
      NAIF_BODY_CODE                  += ( -189620 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_APSS_TWINS+Y' )
      NAIF_BODY_CODE                  += ( -189630 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_APSS_TWINS-Y' )
      NAIF_BODY_CODE                  += ( -189640 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_ICC' )
      NAIF_BODY_CODE                  += ( -189111 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_IDA_SHOULDER_AZ' )
      NAIF_BODY_CODE                  += ( -189121 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_IDA_SHOULDER_EL' )
      NAIF_BODY_CODE                  += ( -189122 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_IDA_ELBOW' )
      NAIF_BODY_CODE                  += ( -189123 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_IDA_WRIST' )
      NAIF_BODY_CODE                  += ( -189124 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_IDA_IDC_REF' )
      NAIF_BODY_CODE                  += ( -189131 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_IDA_IDC' )
      NAIF_BODY_CODE                  += ( -189125 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_IDA_GRAPPLE_BASE' )
      NAIF_BODY_CODE                  += ( -189127 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_IDA_SCOOP' )
      NAIF_BODY_CODE                  += ( -189128 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_IDA_BLADE' )
      NAIF_BODY_CODE                  += ( -189129 )

      NAIF_BODY_NAME                  += ( 'INSIGHT_IDA_GRAPPLE' )
      NAIF_BODY_CODE                  += ( -189130 )

   \begintext

End of FK file.
