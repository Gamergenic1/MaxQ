KPL/FK

Hera Spacecraft Frames Kernel
=============================================================================

   This frame kernel contains complete set of frame definitions for the
   Hera (named after the Greek goddess of marriage) including definitions
   for the Hera fixed and Hera science instrument frames. This kernel
   also contains NAIF ID/name mapping for the Hera science instruments
   and s/c structures (see the last section of the file).


Version and Date
-----------------------------------------------------------------------------

   Version 0.7 -- November 8, 2021 -- Alfredo Escalante Lopez, ESAC/ESA

      Updated Thermal Infrared Instrument name from TIRA to TIRI.

      Added HyperScout Hyperspectral HERA_HSH reference frame.

   Version 0.6 -- March 17, 2021 -- Alfredo Escalante Lopez, ESAC/ESA

      Added DIMORPHOS_SHM frame for locating Dart impact site.

      Updated contact information.

   Version 0.5 -- July 30, 2020 -- Marc Costa Sitja, ESAC/ESA

      Updated NAIF Body Names and IDs for the binary asteroid system
      as follows:

            DIDYMOS_BARYCENTER          2065802  (synonyms: DIDYMOS_BC,
                                                  DIDYMOS BARYCENTER)
            DIDYMOS                     -658030  (synonym: DIDYMAIN)
            DIMORPHOS                   -658031  (synonym: DIDYMOON)
            DART_IMPACT_SITE            -999900  (synonyms:
                                                  DIMORPHOS_IMPACT_SITE,
                                                  DIDYMOON_IMPACT_SITE)

      Updated Frame names accordingly: DIDYMOS_FIXED and DIMORPHOS_FIXED.
      Added Topographic frame for DART impact site DIMORPHOS_IMPACT_TOPO.

   Version 0.4 -- September 6, 2019 -- Marc Costa Sitja, ESAC/ESA

      Updated Hera ID according to standard ESOC provisional numbering:
      from -667 to -999. Changed DIDYMOS to DIDYMAIN and added the IDs.
      Added HGA, TIRA and FLAT frame definitions.

   Version 0.3 -- March 2, 2019 -- Marc Costa Sitja, ESAC/ESA

      Updated definitions of DIDYMOS and DIDYMOON reference frames.
      Minor corrections.

   Version 0.2 -- January 22, 2019 -- Marc Costa Sitja, ESAC/ESA

      Added AFC-2 on top of AFC.

   Version 0.1 -- December 3, 2018 -- Marc Costa Sitja, ESAC/ESA

      Added Frame Camera IDs, reference frames and enhanced outline.

   Version 0.0 -- September 21, 2018 -- Marc Costa Sitja, ESAC/ESA

      Preliminary Version. Only basic ID and frame definitions.


References
-----------------------------------------------------------------------------

   1.   ``Frames Required Reading''

   2.   ``Kernel Pool Required Reading''

   3.   ``C-Kernel Required Reading''


Contact Information
-----------------------------------------------------------------------------

   If you have any questions regarding this file contact the ESA SPICE
   Service at ESAC:

           Alfredo Escalante Lopez
           (+34) 91-8131-429
           spice@sciops.esa.int


Implementation Notes
-----------------------------------------------------------------------------

   This file is used by the SPICE system as follows: programs that make use
   of this frame kernel must "load" the kernel normally during program
   initialization. Loading the kernel associates the data items with
   their names in a data structure called the "kernel pool".  The SPICELIB
   routine FURNSH loads a kernel into the pool as shown below:

     FORTRAN: (SPICELIB)

       CALL FURNSH ( frame_kernel_name )

     C: (CSPICE)

       furnsh_c ( frame_kernel_name );

     IDL: (ICY)

       cspice_furnsh, frame_kernel_name

     MATLAB: (MICE)

       cspice_furnsh ( 'frame_kernel_name' )

     PYTHON: (SPICEYPY)*

       furnsh( frame_kernel_name )

   In order for a program or routine to extract data from the pool, the
   SPICELIB routines GDPOOL, GIPOOL, and GCPOOL are used.  See [2] for
   more details.

   This file was created and may be updated with a text editor or word
   processor.

   * SPICEPY is a non-official, community developed Python wrapper for the
     NAIF SPICE toolkit. Its development is managed on Github.
     It is available at: https://github.com/AndrewAnnex/SpiceyPy


Hera Mission NAIF ID Codes
-----------------------------------------------------------------------------

   The following names and NAIF ID codes are assigned to the Hera spacecraft,
   its structures and science instruments (the keywords implementing these
   definitions are located in the section "Hera Mission NAIF ID
   Codes -- Definition Section" at the end of this file):

      Hera Spacecraft and Spacecraft Structures names/IDs:

            HERA                        -999

            HERA_SPACECRAFT             -999000  (synonym: HERA_SC)

            HERA_HGA                    -999010

      Asteroid Framing Cameras 1 and 2 names/IDs:

            HERA_AFC-1                  -999110
            HERA_AFC-1_FILTER_1         -999111
            HERA_AFC-1_FILTER_2         -999112
            HERA_AFC-1_FILTER_3         -999113
            HERA_AFC-1_FILTER_4         -999114
            HERA_AFC-1_FILTER_5         -999115
            HERA_AFC-1_FILTER_6         -999116
            HERA_AFC-1_FILTER_7         -999117
            HERA_AFC-1_FILTER_8         -999118

            HERA_AFC-2                  -999120
            HERA_AFC-2_FILTER_1         -999121
            HERA_AFC-2_FILTER_2         -999122
            HERA_AFC-2_FILTER_3         -999123
            HERA_AFC-2_FILTER_4         -999124
            HERA_AFC-2_FILTER_5         -999125
            HERA_AFC-2_FILTER_6         -999126
            HERA_AFC-2_FILTER_7         -999127
            HERA_AFC-2_FILTER_8         -999128

            HERA_AFC_RAD                -999109

      Thermal InfraRed Imager names/IDs:

            HERA_TIRI                   -999200

      Planetary Altimeter names/IDs:

            HERA_PALT                   -999300
            HERA_PALT_MIN               -999301

      HyperScout Hyperspectral Imager names/IDs:

            HERA_HSH                    -999400

      Asteroid Binary System names/IDs:

            DIDYMOS_BARYCENTER          2065802  (synonyms: DIDYMOS_BC,
                                                  DIDYMOS BARYCENTER)
            DIDYMOS                     -658030  (synonym: DIDYMAIN)
            DIMORPHOS                   -658031  (synonym: DIDYMOON)
            DART_IMPACT_SITE            -999900  (synonyms:
                                                  DIMORPHOS_IMPACT_SITE,
                                                  DIDYMOON_IMPACT_SITE)


Hera Mission Frames
-----------------------------------------------------------------------------

   The following Hera frames are defined in this kernel file:

           Name                  Relative to               Type       NAIF ID
      ======================  ========================  ==========   =========

    Spacecraft frames:
    ------------------
      HERA_SPACECRAFT           J2000                    CK           -999000

      HERA_HGA                  HERA_SPACECRAFT          FIXED        -999010


    Asteroid Framing Camera Frames:
    -------------------------------
      HERA_AFC-1                HERA_SPACECRAFT          FIXED        -999110
      HERA_AFC-2                HERA_SPACECRAFT          FIXED        -999120


    Thermal InfraRed Imager Frames:
    -------------------------------

      HERA_TIRI                 HERA_SPACECRAFT          FIXED        -999210


    Planetary Altimeter Frames:
    ---------------------------

      HERA_PALT                 HERA_SPACECRAFT          FIXED        -999310


    HyperScout Hyperspectral Imager Frames:
    ---------------------------------------

      HERA_HSH                  HERA_SPACECRAFT          FIXED        -999410


   In addition, the following frames, in use by the BepiColombo mission, are
   defined in other kernels or `built into' the SPICE system:


  Hera mission specific science frame:
   -------------------------------------------
      HERA_DEFAULT              J2000                  DYNAMIC       -999010
      DIDYMOS_FIXED             J2000                      PCK    -658030000
      DIMORPHOS_FIXED           DIDYMOS_FIXED          DYNAMIC    -658031000
      DIMORPHOS_IMPACT_TOPO     DIMORPHOS_FIXED        DYNAMIC       -999900


   SPICE 'Built-in' PCK frames in use by BepiColombo (3):
   ------------------------------------------------------
      IAU_EARTH                J2000                     PCK        built-in

      (3) Data for these frames is loaded using either the PCK file
          "pckVVVVV.tpc" (VVVVV is the version number)


Hera Frames Hierarchy
-----------------------------------------------------------------------------

  The diagram below shows the Hera spacecraft and its structures frame
  hierarchy (not including science instrument frames.)

                                 "J2000" INERTIAL
           +-----------------------------------------------------+
           |                            |                        |
           |<-pck                       |                        |<-pck
           |                            |                        |
           V                            |                        V
      "EARTH_FIXED"                     |                  "DIDYMOS_FIXED"
      -------------                     |                  ---------------
                                        |                        |
                                        |<-ck                    |<-dynamic
                                        |                        |
                                        V                        V
                                 "HERA_SPACECRAFT"         "DIMORPHOS_FIXED"
                  +---------------------------------+      -----------------
                  |                                 .            |
                  |<-fixed                          .            |<-dynamic
                  |                                 .            |
                  V                                 .            V
              "HERA_HGA"                            .   "DIMORPHOS_IMPACT_TOPO"
              ----------                            .   ----------------------
                                                    .
                                                    V
                   Individual instrument frame trees are provided
                     in the corresponding sections of this file


Hera Target Frames
========================================================================

   This section of the file contains the body-fixed frame definition
   for one of the Hera mission targets: asteroid Didymos and Dimorphos.

   A body-fixed frame is defined for Didymos using standard body-fixed,
   PCK-based frame formation rules:

      -  +Z axis is toward the North pole;

      -  +X axis is toward the prime meridian;

      -  +Y axis completes the right hand frame;

      -  the origin of this frame is at the center of the body.

   The orientation of this frame is computed by evaluating
   corresponding rotation constants provided in the PCK file(s).

   \begindata

      FRAME_DIDYMOS_FIXED        =  -658030
      FRAME_-658030_NAME         = 'DIDYMOS_FIXED'
      FRAME_-658030_CLASS        =  2
      FRAME_-658030_CLASS_ID     =  -658030
      FRAME_-658030_CENTER       =  -658030
      OBJECT_-658030_FRAME       = 'DIDYMOS_FIXED'

   \begintext


   For Dimorphos we use a preliminary dynamic reference frame and we assume
   that the spin is equivalent to the orbital period for Dimorphos.

   \begindata

      FRAME_DIMORPHOS_FIXED          = -658031
      FRAME_-658031_NAME            = 'DIMORPHOS_FIXED'
      FRAME_-658031_CLASS           =  5
      FRAME_-658031_CLASS_ID        = -658031
      FRAME_-658031_CENTER          = -658031
      FRAME_-658031_RELATIVE        = 'J2000'
      FRAME_-658031_DEF_STYLE       = 'PARAMETERIZED'
      FRAME_-658031_FAMILY          = 'TWO-VECTOR'
      FRAME_-658031_PRI_AXIS        = 'X'
      FRAME_-658031_PRI_VECTOR_DEF  = 'OBSERVER_TARGET_POSITION'
      FRAME_-658031_PRI_OBSERVER    = 'DIMORPHOS'
      FRAME_-658031_PRI_TARGET      = 'DIDYMOS'
      FRAME_-658031_PRI_ABCORR      = 'NONE'
      FRAME_-658031_SEC_AXIS        = 'Y'
      FRAME_-658031_SEC_VECTOR_DEF  = 'OBSERVER_TARGET_VELOCITY'
      FRAME_-658031_SEC_OBSERVER    = 'DIMORPHOS'
      FRAME_-658031_SEC_TARGET      = 'DIDYMOS'
      FRAME_-658031_SEC_ABCORR      = 'NONE'
      FRAME_-658031_SEC_FRAME       = 'J2000'

   \begintext

   Dimorphos Shape Model reference frame is a rotated frame from its
   body-fixed frame. It is used for the crater position by GMV.

   \begindata

      FRAME_DIMORPHOS_SHM              =  -6580310
      FRAME_-6580310_NAME               = 'DIMORPHOS_SHM'
      FRAME_-6580310_CLASS              =  4
      FRAME_-6580310_CLASS_ID           =  -6580310
      FRAME_-6580310_CENTER             =  -658031
      TKFRAME_-6580310_RELATIVE         = 'DIMORPHOS_FIXED'
      TKFRAME_-6580310_SPEC             = 'ANGLES'
      TKFRAME_-6580310_UNITS            = 'DEGREES'
      TKFRAME_-6580310_AXES             = ( 1,     2,   3   )
      TKFRAME_-6580310_ANGLES           = ( 0, 180, 0)

   \begintext


   For the Dimorphos impact site (DART impact site) we use a preliminary
   dynamic reference frame for the generation of a topographic frame with
   the PINPOINT utility is not possible due to a non equal equatorial radii.

   \begindata

      FRAME_DIMORPHOS_IMPACT_TOPO    = -999900
      FRAME_-999900_NAME            = 'DIMORPHOS_IMPACT_TOPO'
      FRAME_-999900_CLASS           =  5
      FRAME_-999900_CLASS_ID        = -999900
      FRAME_-999900_CENTER          = -999900
      FRAME_-999900_RELATIVE        = 'DIMORPHOS_FIXED'
      FRAME_-999900_DEF_STYLE       = 'PARAMETERIZED'
      FRAME_-999900_FAMILY          = 'TWO-VECTOR'
      FRAME_-999900_PRI_AXIS        = 'Z'
      FRAME_-999900_PRI_VECTOR_DEF = 'CONSTANT'
      FRAME_-999900_PRI_FRAME      = 'DIMORPHOS_FIXED'
      FRAME_-999900_PRI_SPEC       = 'RECTANGULAR'
      FRAME_-999900_PRI_VECTOR     = ( 1, 0, 0  )
      FRAME_-999900_PRI_ABCORR      = 'NONE'
      FRAME_-999900_SEC_AXIS        = 'X'
      FRAME_-999900_SEC_VECTOR_DEF = 'CONSTANT'
      FRAME_-999900_SEC_FRAME      = 'DIMORPHOS_FIXED'
      FRAME_-999900_SEC_SPEC       = 'RECTANGULAR'
      FRAME_-999900_SEC_VECTOR     = ( 0, 0, 1  )
      FRAME_-999900_SEC_ABCORR      = 'NONE'

   \begintext


Hera Spacecraft and Spacecraft Structures Frames
========================================================================

   This section of the file contains the definitions of the spacecraft
   and spacecraft structures frames.


Hera Spacecraft Frame
--------------------------------------

   The Hera spacecraft frame is defined as follows:

      -  +Z axis is along the nominal boresight direction of the asteroid
         framing camera;

      -  +X axis is along the nominal boresight direction of the HGA;

      -  +Y axis completes the right-hand frame;

      -  the origin of this frame is the launch vehicle interface point.

   These diagrams illustrate the HERA_SPACECRAFT frame:


   +X s/c side (HGA side) view:
   ----------------------------

                                      ^
                                      | toward asteroid
                                      |

                                 Science Deck

   .__  __..___________.     .__________________    .___________..__  ___.
   |  / / ||           |\   |        ____      |   /|           ||  / /  |
   |  / / ||           | \  .      .'    `.    .  / |           ||  \ \  |
   |  \ \ ||           |  \ |     /    |   \   | /  |           ||  / /  |
   |  / / ||           |   o|     |  _ O   |   |o   |           ||  \ \  |
   |  \ \ ||           |  / |    +Zsc ^ \  /   | \  |           ||  / /  |
   |  / / ||           | /  |      `._|__.'    |  \ |           ||  / /  |
   .__\ \_..___________./   ._________|________.   \.___________..__\ \__.
                                   /\ | /\
                                      o-------> +Ysc
                                     +Xsc
                                                       +Xsc is out of
                                                        the page.


   +Z s/c side (science deck side) view:
   -------------------------------------

                             .________________.
                             |                |
                             |           +Ysc |
   o==/ /==-=============---o|   +Zsc o-----> |o---===============-=/ /==o
       -Y Solar Array        |        |       |               +Y Solar Array
                             .________|_______.
                                   .--V +Xsc
                            HGA  .'       `.
                                /___________\
                                    `.|.'                 +Zsc is out
                                                           of the page.


   Since the orientation of the HERA_SPACECRAFT frame is computed
   on-board, sent down in telemetry, and stored in the s/c CK files, it
   is defined as a CK-based frame.

   \begindata

      FRAME_HERA_SPACECRAFT            = -999000
      FRAME_-999000_NAME               = 'HERA_SPACECRAFT'
      FRAME_-999000_CLASS              =  3
      FRAME_-999000_CLASS_ID           = -999000
      FRAME_-999000_CENTER             = -999
      CK_-999000_SCLK                  = -999
      CK_-999000_SPK                   = -999

   \begintext


Hera High Gain Antenna Frame
--------------------------------------

   The Hera High Gain Antenna is rigidly attached to the +X side of the
   S/C bus. Therefore, the Hera HGA frame, HERA_HGA, is defined as a fixed
   offset frame with its orientation given relative to the HERA_SPACECRAFT
   frame and is defined as follows:

      -  +Z axis is in the antenna boresight direction (nominally
         5 degrees off the S/C -X axis towards the S/C +Z axis);

      -  +Y axis is in the direction of the S/C +Y axis ;

      -  +X completes the right hand frame;

      -  the origin of the frame is located at the geometric center of the
         HGA dish outer rim circle.

   This diagram illustrates the HERA_HGA frame:


   +Z s/c side (science deck side) view:
   -------------------------------------

                             .________________.
                             |                |
                             |           +Ysc |
   o==/ /==-=============---o|   +Zsc o-----> |o---===============-=/ /==o
       -Y Solar Array        |        |       |               +Y Solar Array
                             .________|_______.
                                   .--V +Xsc
                            HGA  +Xhga    `.
                                /_____o----->
                                    `.|.'     +Yhga      +Zsc and +Xhga are
                                      |                   out of the page.
                                      |
                                      V
                                    +Zhga


   Nominally a single rotation of 90 degrees about the +Y axis is needed to
   co-align the S/C frame with the HGA frame.

   Since the SPICE frames subsystem calls for specifying the reverse
   transformation--going from the instrument or structure frame to the
   base frame--as compared to the description given above, the order of
   rotations assigned to the TKFRAME_*_AXES keyword is also reversed
   compared to the above text, and the signs associated with the
   rotation angles assigned to the TKFRAME_*_ANGLES keyword are the
   opposite from what is written in the above text.

   \begindata

      FRAME_HERA_HGA                   =  -999010
      FRAME_-999010_NAME               = 'HERA_HGA'
      FRAME_-999010_CLASS              =  4
      FRAME_-999010_CLASS_ID           =  -999010
      FRAME_-999010_CENTER             =  -999
      TKFRAME_-999010_RELATIVE         = 'HERA_SPACECRAFT'
      TKFRAME_-999010_SPEC             = 'ANGLES'
      TKFRAME_-999010_UNITS            = 'DEGREES'
      TKFRAME_-999010_AXES             = ( 1,     2,   3   )
      TKFRAME_-999010_ANGLES           = ( 0.0, -90.0, 0.0 )

   \begintext


AFC Frames
========================================================================

   This section of the file contains the definitions of the Asteroid Framing
   Cameras (AFC-1 and AFC-2) frames.


AFC Frame Tree
--------------------------------------

   The diagram below shows the AFC frame hierarchy.

                                 "J2000" INERTIAL
           +-----------------------------------------------------+
           |                            |                        |
           |<-pck                       |                        |<-fixed
           |                            |                        |
           V                            |                        V
      "EARTH_FIXED"                     |                  "DIDYMOS_FIXED"
      -------------                     |                  ---------------
                                        |
                                        |<-ck
                                        |
                                        V
                                "HERA_SPACECRAFT"
                             +---------------------+
                             |                     |
                             |<-fixed              |<-fixed
                             |                     |
                             V                     V
                         "HERA_AFC-1"          "HERA_AFC-2"
                         -----------            -----------
                             |                     |
                             |<-fixed              |<-fixed
                             |                     |
                             V                     V
                "HERA_AFC-1_FILTER_[1..8]"   "HERA_AFC-2_FILTER_[1..8]"
                --------------------------   --------------------------


AFC Frames
--------------------------------------

   The Asteroid Framing Camera frames -- HERA_AFC-1 and HERA_AFC-2 --
   are defined as follows:

      -  +Z axis points along the camera boresight;

      -  +X axis is parallel to the apparent image lines; it is
         nominally co-aligned with the s/c +X axis;

      -  +Y axis completes the right handed frame; it is nominally
         parallel to the apparent image columns and co-aligned with
         the s/c +Y axis;

      -  the origin of the frame is located at the camera focal point.

   The Framing Cameras filter frames -- HERA_AFC-[1,2]_FILTER_[1..8] -- are
   defined to be nominally co-aligned with the corresponding camera frame.

   This diagram illustrates the AFC-1 and AFC-2 camera frames:


   +Z s/c side (science deck side) view:
   -------------------------------------

                             .________________.
                             |   o------> +Yafc
                             |   |       +Ysc |
   o==/ /==-=============---o|   |    o-----> |o---===============-=/ /==o
       -Y Solar Array        |   V    |       |               +Y Solar Array
                             ._ +Xafc |_______.
                                   .--V +Xsc
                            HGA  .'       `.
                                /___________\
                                    `.|.'                 +Zsc and +Zafc are
                                                           out of the page.


   Nominally, the AFC frames are co-aligned with the s/c frame:

   \begindata

      FRAME_HERA_AFC-1                 = -999110
      FRAME_-999110_NAME               = 'HERA_AFC-1'
      FRAME_-999110_CLASS              =  4
      FRAME_-999110_CLASS_ID           = -999110
      FRAME_-999110_CENTER             = -999
      TKFRAME_-999110_RELATIVE         = 'HERA_SPACECRAFT'
      TKFRAME_-999110_SPEC             = 'ANGLES'
      TKFRAME_-999110_UNITS            = 'DEGREES'
      TKFRAME_-999110_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999110_AXES             = ( 1,   2,   3   )

      FRAME_HERA_AFC-2                 = -999120
      FRAME_-999120_NAME               = 'HERA_AFC-2'
      FRAME_-999120_CLASS              =  4
      FRAME_-999120_CLASS_ID           = -999120
      FRAME_-999120_CENTER             = -999
      TKFRAME_-999120_RELATIVE         = 'HERA_SPACECRAFT'
      TKFRAME_-999120_SPEC             = 'ANGLES'
      TKFRAME_-999120_UNITS            = 'DEGREES'
      TKFRAME_-999120_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999120_AXES             = ( 1,   2,   3   )

   \begintext

   The keywords below define the AFC filter frames to be co-aligned with
   the corresponding camera frames.

   \begindata

      FRAME_HERA_AFC-1_FILTER_1     = -999111
      FRAME_-999111_NAME            = 'HERA_AFC-1_FILTER_1'
      FRAME_-999111_CLASS           = 4
      FRAME_-999111_CLASS_ID        = -999111
      FRAME_-999111_CENTER          = -999
      TKFRAME_-999111_RELATIVE      = 'HERA_AFC-1'
      TKFRAME_-999111_SPEC          = 'ANGLES'
      TKFRAME_-999111_UNITS         = 'DEGREES'
      TKFRAME_-999111_ANGLES        = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999111_AXES          = ( 1,   2,   3   )

      FRAME_HERA_AFC-1_FILTER_2     = -999112
      FRAME_-999112_NAME            = 'HERA_AFC-1_FILTER_2'
      FRAME_-999112_CLASS           = 4
      FRAME_-999112_CLASS_ID        = -999112
      FRAME_-999112_CENTER          = -999
      TKFRAME_-999112_RELATIVE      = 'HERA_AFC-1'
      TKFRAME_-999112_SPEC          = 'ANGLES'
      TKFRAME_-999112_UNITS         = 'DEGREES'
      TKFRAME_-999112_ANGLES        = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999112_AXES          = ( 1,   2,   3   )

      FRAME_HERA_AFC-1_FILTER_3     = -999113
      FRAME_-999113_NAME            = 'HERA_AFC-1_FILTER_3'
      FRAME_-999113_CLASS           = 4
      FRAME_-999113_CLASS_ID        = -999113
      FRAME_-999113_CENTER          = -999
      TKFRAME_-999113_RELATIVE      = 'HERA_AFC-1'
      TKFRAME_-999113_SPEC          = 'ANGLES'
      TKFRAME_-999113_UNITS         = 'DEGREES'
      TKFRAME_-999113_ANGLES        = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999113_AXES          = ( 1,   2,   3   )

      FRAME_HERA_AFC-1_FILTER_4     = -999114
      FRAME_-999114_NAME            = 'HERA_AFC-1_FILTER_4'
      FRAME_-999114_CLASS           = 4
      FRAME_-999114_CLASS_ID        = -999114
      FRAME_-999114_CENTER          = -999
      TKFRAME_-999114_RELATIVE      = 'HERA_AFC-1'
      TKFRAME_-999114_SPEC          = 'ANGLES'
      TKFRAME_-999114_UNITS         = 'DEGREES'
      TKFRAME_-999114_ANGLES        = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999114_AXES          = ( 1,   2,   3   )

      FRAME_HERA_AFC-1_FILTER_5     = -999115
      FRAME_-999115_NAME            = 'HERA_AFC-1_FILTER_5'
      FRAME_-999115_CLASS           = 4
      FRAME_-999115_CLASS_ID        = -999115
      FRAME_-999115_CENTER          = -999
      TKFRAME_-999115_RELATIVE      = 'HERA_AFC-1'
      TKFRAME_-999115_SPEC          = 'ANGLES'
      TKFRAME_-999115_UNITS         = 'DEGREES'
      TKFRAME_-999115_ANGLES        = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999115_AXES          = ( 1,   2,   3   )

      FRAME_HERA_AFC-1_FILTER_6     = -999116
      FRAME_-999116_NAME            = 'HERA_AFC-1_FILTER_6'
      FRAME_-999116_CLASS           = 4
      FRAME_-999116_CLASS_ID        = -999116
      FRAME_-999116_CENTER          = -999
      TKFRAME_-999116_RELATIVE      = 'HERA_AFC-1'
      TKFRAME_-999116_SPEC          = 'ANGLES'
      TKFRAME_-999116_UNITS         = 'DEGREES'
      TKFRAME_-999116_ANGLES        = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999116_AXES          = ( 1,   2,   3   )

      FRAME_HERA_AFC-1_FILTER_7     = -999117
      FRAME_-999117_NAME            = 'HERA_AFC-1_FILTER_7'
      FRAME_-999117_CLASS           = 4
      FRAME_-999117_CLASS_ID        = -999117
      FRAME_-999117_CENTER          = -999
      TKFRAME_-999117_RELATIVE      = 'HERA_AFC-1'
      TKFRAME_-999117_SPEC          = 'ANGLES'
      TKFRAME_-999117_UNITS         = 'DEGREES'
      TKFRAME_-999117_ANGLES        = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999117_AXES          = ( 1,   2,   3   )

      FRAME_HERA_AFC-1_FILTER_8     = -999118
      FRAME_-999118_NAME            = 'HERA_AFC-1_FILTER_8'
      FRAME_-999118_CLASS           = 4
      FRAME_-999118_CLASS_ID        = -999118
      FRAME_-999118_CENTER          = -999
      TKFRAME_-999118_RELATIVE      = 'HERA_AFC-1'
      TKFRAME_-999118_SPEC          = 'ANGLES'
      TKFRAME_-999118_UNITS         = 'DEGREES'
      TKFRAME_-999118_ANGLES        = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999118_AXES          = ( 1,   2,   3   )

      FRAME_HERA_AFC-2_FILTER_1     = -999121
      FRAME_-999121_NAME            = 'HERA_AFC-2_FILTER_1'
      FRAME_-999121_CLASS           = 4
      FRAME_-999121_CLASS_ID        = -999121
      FRAME_-999121_CENTER          = -999
      TKFRAME_-999121_RELATIVE      = 'HERA_AFC-2'
      TKFRAME_-999121_SPEC          = 'ANGLES'
      TKFRAME_-999121_UNITS         = 'DEGREES'
      TKFRAME_-999121_ANGLES        = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999121_AXES          = ( 1,   2,   3   )

      FRAME_HERA_AFC-2_FILTER_2     = -999122
      FRAME_-999122_NAME            = 'HERA_AFC-2_FILTER_2'
      FRAME_-999122_CLASS           = 4
      FRAME_-999122_CLASS_ID        = -999122
      FRAME_-999122_CENTER          = -999
      TKFRAME_-999122_RELATIVE      = 'HERA_AFC-2'
      TKFRAME_-999122_SPEC          = 'ANGLES'
      TKFRAME_-999122_UNITS         = 'DEGREES'
      TKFRAME_-999122_ANGLES        = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999122_AXES          = ( 1,   2,   3   )

      FRAME_HERA_AFC-2_FILTER_3     = -999123
      FRAME_-999123_NAME            = 'HERA_AFC-2_FILTER_3'
      FRAME_-999123_CLASS           = 4
      FRAME_-999123_CLASS_ID        = -999123
      FRAME_-999123_CENTER          = -999
      TKFRAME_-999123_RELATIVE      = 'HERA_AFC-2'
      TKFRAME_-999123_SPEC          = 'ANGLES'
      TKFRAME_-999123_UNITS         = 'DEGREES'
      TKFRAME_-999123_ANGLES        = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999123_AXES          = ( 1,   2,   3   )

      FRAME_HERA_AFC-2_FILTER_4     = -999124
      FRAME_-999124_NAME            = 'HERA_AFC-2_FILTER_4'
      FRAME_-999124_CLASS           = 4
      FRAME_-999124_CLASS_ID        = -999124
      FRAME_-999124_CENTER          = -999
      TKFRAME_-999124_RELATIVE      = 'HERA_AFC-2'
      TKFRAME_-999124_SPEC          = 'ANGLES'
      TKFRAME_-999124_UNITS         = 'DEGREES'
      TKFRAME_-999124_ANGLES        = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999124_AXES          = ( 1,   2,   3   )

      FRAME_HERA_AFC-2_FILTER_5     = -999125
      FRAME_-999125_NAME            = 'HERA_AFC-2_FILTER_5'
      FRAME_-999125_CLASS           = 4
      FRAME_-999125_CLASS_ID        = -999125
      FRAME_-999125_CENTER          = -999
      TKFRAME_-999125_RELATIVE      = 'HERA_AFC-2'
      TKFRAME_-999125_SPEC          = 'ANGLES'
      TKFRAME_-999125_UNITS         = 'DEGREES'
      TKFRAME_-999125_ANGLES        = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999125_AXES          = ( 1,   2,   3   )

      FRAME_HERA_AFC-2_FILTER_6     = -999126
      FRAME_-999126_NAME            = 'HERA_AFC-2_FILTER_6'
      FRAME_-999126_CLASS           = 4
      FRAME_-999126_CLASS_ID        = -999126
      FRAME_-999126_CENTER          = -999
      TKFRAME_-999126_RELATIVE      = 'HERA_AFC-2'
      TKFRAME_-999126_SPEC          = 'ANGLES'
      TKFRAME_-999126_UNITS         = 'DEGREES'
      TKFRAME_-999126_ANGLES        = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999126_AXES          = ( 1,   2,   3   )

      FRAME_HERA_AFC-2_FILTER_7     = -999127
      FRAME_-999127_NAME            = 'HERA_AFC-2_FILTER_7'
      FRAME_-999127_CLASS           = 4
      FRAME_-999127_CLASS_ID        = -999127
      FRAME_-999127_CENTER          = -999
      TKFRAME_-999127_RELATIVE      = 'HERA_AFC-2'
      TKFRAME_-999127_SPEC          = 'ANGLES'
      TKFRAME_-999127_UNITS         = 'DEGREES'
      TKFRAME_-999127_ANGLES        = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999127_AXES          = ( 1,   2,   3   )

      FRAME_HERA_AFC-2_FILTER_8     = -999128
      FRAME_-999128_NAME            = 'HERA_AFC-2_FILTER_8'
      FRAME_-999128_CLASS           = 4
      FRAME_-999128_CLASS_ID        = -999128
      FRAME_-999128_CENTER          = -999
      TKFRAME_-999128_RELATIVE      = 'HERA_AFC-2'
      TKFRAME_-999128_SPEC          = 'ANGLES'
      TKFRAME_-999128_UNITS         = 'DEGREES'
      TKFRAME_-999128_ANGLES        = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999128_AXES          = ( 1,   2,   3   )

   \begintext


TIRI Frames
========================================================================

   This section of the file contains the definitions of the Thermal
   InfraRed Imager (TIRI) frames.


TIRI Frame Tree
--------------------------------------

   The diagram below shows the TIRI frame hierarchy.

                                 "J2000" INERTIAL
           +-----------------------------------------------------+
           |                            |                        |
           |<-pck                       |                        |<-pck
           |                            |                        |
           V                            |                        V
      "EARTH_FIXED"                     |                  "DIDYMOS_FIXED"
      -------------                     |                  ---------------
                                        |
                                        |<-ck
                                        |
                                        V
                                "HERA_SPACECRAFT"
                                -----------------
                                        |
                                        |<-fixed
                                        |
                                        V
                                    "HERA_TIRI"
                                    -----------


TIRI Frames
--------------------------------------

   The the Thermal InfraRed Imager frame -- HERA_TIRI -- is defined as
   follows:

      -  +Z axis points along the camera boresight;

      -  +X axis is parallel to the apparent image lines; it is
         nominally co-aligned with the s/c +X axis;

      -  +Y axis completes the right handed frame; it is nominally
         parallel to the apparent image columns and co-aligned with
         the s/c +Y axis;

      -  the origin of the frame is located at the camera focal point.


   This diagram illustrates the TRA camera frames:


   +Z s/c side (science deck side) view:
   -------------------------------------

                             .________________.
                             |   o------> +Ytiri
                             |   |       +Ysc |
   o==/ /==-=============---o|   |    o-----> |o---===============-=/ /==o
       -Y Solar Array        |   V    |       |               +Y Solar Array
                             . +Xtiri |_______.
                                   .--V +Xsc
                            HGA  .'       `.
                                /___________\
                                    `.|.'                 +Zsc and +Ztiri are
                                                           out of the page.


   Nominally, the TIRI frames are co-aligned with the s/c frame:

   \begindata

      FRAME_HERA_TIRI                  = -999210
      FRAME_-999210_NAME               = 'HERA_TIRI'
      FRAME_-999210_CLASS              =  4
      FRAME_-999210_CLASS_ID           = -999210
      FRAME_-999210_CENTER             = -999
      TKFRAME_-999210_RELATIVE         = 'HERA_SPACECRAFT'
      TKFRAME_-999210_SPEC             = 'ANGLES'
      TKFRAME_-999210_UNITS            = 'DEGREES'
      TKFRAME_-999210_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999210_AXES             = ( 1,   2,   3   )

   \begintext


PALT Frames
========================================================================

   This section of the file contains the definitions of the Planetary
   Altimeter (PALT) frames.


PALT Frame Tree
--------------------------------------

   The diagram below shows the PALT frame hierarchy.

                                 "J2000" INERTIAL
           +-----------------------------------------------------+
           |                            |                        |
           |<-pck                       |                        |<-pck
           |                            |                        |
           V                            |                        V
      "EARTH_FIXED"                     |                  "DIDYMOS_FIXED"
      -------------                     |                  ---------------
                                        |
                                        |<-ck
                                        |
                                        V
                                "HERA_SPACECRAFT"
                                -----------------
                                        |
                                        |<-fixed
                                        |
                                        V
                                    "HERA_PALT"
                                    -----------


PALT Frames
--------------------------------------

   The Planetary Altimeter frame -- HERA_PALT -- is defined as follows:

      -  +Z axis points along the camera boresight;

      -  +X axis is parallel to the apparent image lines; it is
         nominally co-aligned with the s/c +X axis;

      -  +Y axis completes the right handed frame; it is nominally
         parallel to the apparent image columns and co-aligned with
         the s/c +Y axis;

      -  the origin of the frame is located at the camera focal point.


   This diagram illustrates the PALT camera frames:


   +Z s/c side (science deck side) view:
   -------------------------------------

                             .________________.
                             |   o------> +Ypalt
                             |   |       +Ysc |
   o==/ /==-=============---o|   |    o-----> |o---===============-=/ /==o
       -Y Solar Array        |   V    |       |               +Y Solar Array
                             . +Xpalt |_______.
                                   .--V +Xsc
                            HGA  .'       `.
                                /___________\
                                    `.|.'                 +Zsc and +Zpalt are
                                                           out of the page.


   Nominally, the PALT frames are co-aligned with the s/c frame:

   \begindata

      FRAME_HERA_PALT                  = -999310
      FRAME_-999310_NAME               = 'HERA_PALT'
      FRAME_-999310_CLASS              =  4
      FRAME_-999310_CLASS_ID           = -999310
      FRAME_-999310_CENTER             = -999
      TKFRAME_-999310_RELATIVE         = 'HERA_SPACECRAFT'
      TKFRAME_-999310_SPEC             = 'ANGLES'
      TKFRAME_-999310_UNITS            = 'DEGREES'
      TKFRAME_-999310_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999310_AXES             = ( 1,   2,   3   )

   \begintext


HSH Frames
========================================================================

   This section of the file contains the definitions of the HyperScout
   Hyperspectral Imager (HSH) frames.


HSH Frame Tree
--------------------------------------

   The diagram below shows the HSH frame hierarchy.

                                 "J2000" INERTIAL
           +-----------------------------------------------------+
           |                            |                        |
           |<-pck                       |                        |<-pck
           |                            |                        |
           V                            |                        V
      "EARTH_FIXED"                     |                  "DIDYMOS_FIXED"
      -------------                     |                  ---------------
                                        |
                                        |<-ck
                                        |
                                        V
                                "HERA_SPACECRAFT"
                                -----------------
                                        |
                                        |<-fixed
                                        |
                                        V
                                    "HERA_HSH"
                                    ----------


HSH Frames
--------------------------------------

   The HyperScout Hyperspectral frame -- HERA_HSH -- is defined as follows:

      -  +Z axis points along the camera boresight;

      -  +X axis is parallel to the apparent image lines; it is
         nominally co-aligned with the s/c +X axis;

      -  +Y axis completes the right handed frame; it is nominally
         parallel to the apparent image columns and co-aligned with
         the s/c +Y axis;

      -  the origin of the frame is located at the camera focal point.


   This diagram illustrates the HSH frames:


   +Z s/c side (science deck side) view:
   -------------------------------------

                             .________________.
                             |   o------> +Yhsh
                             |   |       +Ysc |
   o==/ /==-=============---o|   |    o-----> |o---===============-=/ /==o
       -Y Solar Array        |   V    |       |               +Y Solar Array
                             . +Xhsh  |_______.
                                   .--V +Xsc
                            HGA  .'       `.
                                /___________\
                                    `.|.'                 +Zsc and +Zhsh are
                                                           out of the page.


   Nominally, the HSH frames are co-aligned with the s/c frame:

   \begindata

      FRAME_HERA_HSH                   = -999410
      FRAME_-999410_NAME               = 'HERA_HSH'
      FRAME_-999410_CLASS              =  4
      FRAME_-999410_CLASS_ID           = -999410
      FRAME_-999410_CENTER             = -999
      TKFRAME_-999410_RELATIVE         = 'HERA_SPACECRAFT'
      TKFRAME_-999410_SPEC             = 'ANGLES'
      TKFRAME_-999410_UNITS            = 'DEGREES'
      TKFRAME_-999410_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-999410_AXES             = ( 1,   2,   3   )

   \begintext


Hera NAIF ID Codes to Name Mapping
------------------------------------------------------------------------------

   This section contains name to NAIF ID mappings for the Hera mission.
   Once the contents of this file is loaded into the KERNEL POOL,
   these mappings become available within SPICE, making it possible to use
   names instead of ID code in the high level SPICE routine calls.

  Spacecraft:
  ----------------------------------------------------------------

      This table presents the Hera Spacecraft and its main
      structures' names.

      ---------------------  -------  --------------------------
       Name                   ID       Synonyms
      ---------------------  -------  --------------------------
       HERA                     -999
       HERA_SPACECRAFT       -999000   HERA_SC

       HERA_HGA              -999010
      ---------------------  -------  --------------------------

      Notes:

         -- 'HERA_SC' and 'HERA_SPACECRAFT' are synonyms and all map to the
            Hera s/c bus structure ID (-999000);

     \begindata

        NAIF_BODY_NAME += ( 'HERA'                            )
        NAIF_BODY_CODE += ( -999                              )

        NAIF_BODY_NAME += ( 'HERA_SC'                         )
        NAIF_BODY_CODE += ( -999000                           )

        NAIF_BODY_NAME += ( 'HERA_SPACECRAFT'                 )
        NAIF_BODY_CODE += ( -999000                           )

        NAIF_BODY_NAME += ( 'HERA_HGA'                        )
        NAIF_BODY_CODE += ( -999010                           )

     \begintext


  AFC:
  ----

    This table summarizes AFCs IDs:

      ----------------------  --------
       Name                    ID
      ----------------------  --------
      HERA_AF-1                -999110
      HERA_AFC-1_FILTER_1      -999111
      HERA_AFC-1_FILTER_2      -999112
      HERA_AFC-1_FILTER_3      -999113
      HERA_AFC-1_FILTER_4      -999114
      HERA_AFC-1_FILTER_5      -999115
      HERA_AFC-1_FILTER_6      -999116
      HERA_AFC-1_FILTER_7      -999117
      HERA_AFC-1_FILTER_8      -999118

      HERA_AF-2                -999120
      HERA_AFC-2_FILTER_1      -999121
      HERA_AFC-2_FILTER_2      -999122
      HERA_AFC-2_FILTER_3      -999123
      HERA_AFC-2_FILTER_4      -999124
      HERA_AFC-2_FILTER_5      -999125
      HERA_AFC-2_FILTER_6      -999126
      HERA_AFC-2_FILTER_7      -999127
      HERA_AFC-2_FILTER_8      -999128

      HERA_AFC_RAD             -999109
      ----------------------  --------

    Name-ID Mapping keywords:

   \begindata

       NAIF_BODY_NAME += ( 'HERA_AFC-1'                       )
       NAIF_BODY_CODE += ( -999110                            )

       NAIF_BODY_NAME += ( 'HERA_AFC-1_FILTER_1'              )
       NAIF_BODY_CODE += ( -999111                            )

       NAIF_BODY_NAME += ( 'HERA_AFC-1_FILTER_2'              )
       NAIF_BODY_CODE += ( -999112                            )

       NAIF_BODY_NAME += ( 'HERA_AFC-1_FILTER_3'              )
       NAIF_BODY_CODE += ( -999113                            )

       NAIF_BODY_NAME += ( 'HERA_AFC-1_FILTER_4'              )
       NAIF_BODY_CODE += ( -999114                            )

       NAIF_BODY_NAME += ( 'HERA_AFC-1_FILTER_5'              )
       NAIF_BODY_CODE += ( -999115                            )

       NAIF_BODY_NAME += ( 'HERA_AFC-1_FILTER_6'              )
       NAIF_BODY_CODE += ( -999116                            )

       NAIF_BODY_NAME += ( 'HERA_AFC-1_FILTER_7'              )
       NAIF_BODY_CODE += ( -999117                            )

       NAIF_BODY_NAME += ( 'HERA_AFC-1_FILTER_8'              )
       NAIF_BODY_CODE += ( -999118                            )

       NAIF_BODY_NAME += ( 'HERA_AFC-2'                       )
       NAIF_BODY_CODE += ( -999120                            )

       NAIF_BODY_NAME += ( 'HERA_AFC-2_FILTER_1'              )
       NAIF_BODY_CODE += ( -999121                            )

       NAIF_BODY_NAME += ( 'HERA_AFC-2_FILTER_2'              )
       NAIF_BODY_CODE += ( -999122                            )

       NAIF_BODY_NAME += ( 'HERA_AFC-2_FILTER_3'              )
       NAIF_BODY_CODE += ( -999123                            )

       NAIF_BODY_NAME += ( 'HERA_AFC-2_FILTER_4'              )
       NAIF_BODY_CODE += ( -999124                            )

       NAIF_BODY_NAME += ( 'HERA_AFC-2_FILTER_5'              )
       NAIF_BODY_CODE += ( -999125                            )

       NAIF_BODY_NAME += ( 'HERA_AFC-2_FILTER_6'              )
       NAIF_BODY_CODE += ( -999126                            )

       NAIF_BODY_NAME += ( 'HERA_AFC-2_FILTER_7'              )
       NAIF_BODY_CODE += ( -999127                            )

       NAIF_BODY_NAME += ( 'HERA_AFC-2_FILTER_8'              )
       NAIF_BODY_CODE += ( -999128                            )

       NAIF_BODY_NAME += ( 'HERA_AFC_RAD'                     )
       NAIF_BODY_CODE += ( -999109                            )

   \begintext


  Thermal InfraRed Imager:
  ----------------------------------------------------------------

      This table presents the Hera target names.

      ---------------------  -------  --------------------------
       Name                   ID       Synonyms
      ---------------------  -------  --------------------------
       HERA_TIRI             -999200

      Name-ID Mapping keywords:

     \begindata

        NAIF_BODY_NAME += ( 'HERA_TIRI'                       )
        NAIF_BODY_CODE += ( -999200                           )

     \begintext


  Planetary Altimeter:
  ----------------------------------------------------------------

      This table presents the Hera target names.

      ---------------------  -------  --------------------------
       Name                   ID       Synonyms
      ---------------------  -------  --------------------------
       HERA_PALT             -999300
       HERA_PALT_MIN         -999301

      Name-ID Mapping keywords:

     \begindata

        NAIF_BODY_NAME += ( 'HERA_PALT'                       )
        NAIF_BODY_CODE += ( -999300                           )

        NAIF_BODY_NAME += ( 'HERA_PALT_MIN'                   )
        NAIF_BODY_CODE += ( -999301                           )

     \begintext


  HyperScout Hyperspectral Imager:
  ----------------------------------------------------------------

      This table presents the Hera target names.

      ---------------------  -------  --------------------------
       Name                   ID       Synonyms
      ---------------------  -------  --------------------------
       HERA_HSH              -999400

      Name-ID Mapping keywords:

     \begindata

        NAIF_BODY_NAME += ( 'HERA_HSH'                        )
        NAIF_BODY_CODE += ( -999400                           )

     \begintext


  Asteroid Binary System:
  ----------------------------------------------------------------

      This table presents the Hera target names.

      ---------------------  -------  --------------------------
       Name                   ID       Synonyms
      ---------------------  -------  --------------------------
       DIDYMOS_BARYCENTER    2065803   DIDYMOS_BC,
                                       DIDYMOS BARYCENTER
       DIDYMOS               -658030   DIDYMAIN
       DIMORPHOS             -658031   DIDYMOON
       DART_IMPACT_SITE      -999900   DIDYMOON_IMPACT_SITE,
                                       DIMORPHOS_IMPACT_SITE
      ---------------------  -------  --------------------------

     \begindata

        NAIF_BODY_NAME += ( 'DIDYMOS BARYCENTER'              )
        NAIF_BODY_CODE += ( 2065803                           )

        NAIF_BODY_NAME += ( 'DIDYMOS_BC'                      )
        NAIF_BODY_CODE += ( 2065803                           )

        NAIF_BODY_NAME += ( 'DIDYMOS_BARYCENTER'              )
        NAIF_BODY_CODE += ( 2065803                           )

        NAIF_BODY_NAME += ( 'DIDYMAIN'                        )
        NAIF_BODY_CODE += ( -658030                           )

        NAIF_BODY_NAME += ( 'DIDYMOS'                         )
        NAIF_BODY_CODE += ( -658030                           )

        NAIF_BODY_NAME += ( 'DIDYMOON'                        )
        NAIF_BODY_CODE += ( -658031                           )

        NAIF_BODY_NAME += ( 'DIMORPHOS'                       )
        NAIF_BODY_CODE += ( -658031                           )

        NAIF_BODY_NAME += ( 'DIDYMOON_IMPACT_SITE'            )
        NAIF_BODY_CODE += ( -999900                           )

        NAIF_BODY_NAME += ( 'DIMORPHOS_IMPACT_SITE'           )
        NAIF_BODY_CODE += ( -999900                           )

        NAIF_BODY_NAME += ( 'DART_IMPACT_SITE'                )
        NAIF_BODY_CODE += ( -999900                           )

   \begintext


End of FK file.