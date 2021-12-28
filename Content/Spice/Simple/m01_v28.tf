KPL/FK

Mars'01 Orbiter Frames Kernel
===============================================================================

   This frame kernel contains complete set of frame definitions for the 
   Mars'01 Orbiter (M01) spacecraft including definitions for the s/c 
   fixed frame, high and low gain antenna frames and science instrument 
   frames.


Important Note
-------------------------------------------------------------------------------

   The instrument frame orientations provided in this version of the FK
   file are based on the alignment data from PRE-LAUNCH calibration
   reports and/or NOMINAL instrument design documents (excepting the
   preliminary in-flight calibrated value of the THEMIS IR and VIS yaw
   rotations.) 

   While the PRE-LAUNCH and NOMINAL values give a good approximation of
   the instrument's orientation, they should be replaced with
   the more accurate IN-FLIGHT calibrated values to achieve correct
   instrument pointing computations, especially for high-resolution
   instruments such as THEMIS.

   Unfortunately, the complete set of IN-FLIGHT calibrated geometric
   instrument models was not available at the time when this FK was
   released. As soon as such data become available, the FK will be
   updated to incorporate it.


Version and Date
-------------------------------------------------------------------------------

   Version 2.8 -- March 13, 2006 -- Boris Semenov, NAIF

      Corrected frame table and frame tree diagram to indicate that
      M01_SPACECRAFT frame orientation in the CKs is provided with
      respect to the MARSIAU frame rather than to the J2000 frame.

      Added a note indicating UHF antenna clock angle reference axis
      direction to the M01_UHF frame description.
      
   Version 2.7 -- August 23, 2005 -- Boris Semenov, NAIF

      Added UHF antenna frame.
      
   Version 2.6 -- June 2, 2003 -- Boris Semenov, NAIF

      Fixed typos found by Jim Torson.
      
   Version 2.5 -- March 25, 2003 -- Boris Semenov, NAIF

      Replaced rotation about +Z ("yaw rotation") in the ``M01_THEMIS_IR'' 
      and ``M01_THEMIS_VIS'' frame definitions with the improved offset 
      values determined by Jim Torson, USGS. Current values are -0.672 for IR 
      and -0.25 for VIS.
      
   Version 2.4 -- September 25, 2002 -- Boris Semenov, NAIF

      Replaced nominal 0-degree rotation about +Z ("yaw rotation") in
      the ``M01_THEMIS_IR'' frame definition with the offset determined
      from the early mapping image analysis by Jim Torson, U.S. Geological
      Survey, Flagstaff, AZ.
      
   Version 2.3 -- August 8, 2001 -- Boris Semenov, NAIF

      Corrected MATRIX assignment in the M01_HGA_BOOM definition.

   Version 2.2 -- August 7, 2001 -- Boris Semenov, NAIF

      Added name-NAIF ID code mapping section at the end of the file.

   Version 2.1 -- May 17, 2001 -- Boris Semenov, NAIF

      Added X-band pattern based companion frame for each of the 
      HGA and MGA frames.

   Version 2.0 -- March 5, 2001 -- Boris Semenov, NAIF

      Described s/c, antenna and instrument frames. Filled in instrument 
      frame alignment (except THEMIS) using nominal SIS data. Filled in
      THEMIS final pre-launch alignments. Added solar array frames.

   Version 1.1 -- September 29, 2000 -- Boris Semenov, NAIF

      Corrected LGA frame orientation per Bill Adam's comment.

   Version 1.0 -- September 25, 2000 -- Boris Semenov, NAIF

      Initial Release: both instrument and antenna frame definitions are
      only place-holders.


References
-------------------------------------------------------------------------------

   1. ``Frames Required Reading''

   2. ``Kernel Pool Required Reading''

   3. ``C-Kernel Required Reading''

   4. ``GRS ICD'', MSP01-98-0014, June 24, 1999

   5. ``THEMIS ICD'', MSP01-97-0008, June 10, 1999

   6. ``MARIE ICD'', MSP01-98-0016, June 23, 1999

   7. ``MSP01 Orbiter Pointing and Alignment Criteria'', MSP01-98-0096,
      June 7, 1999

   8. ``Mars Surveyor Program '01 Orbiter. AACS Hardware Coordinate 
      Frame Definitions and transformations'', Rev. 3, 11/30/99
 
   9. Final Launch Site THEMIS Alignment Verification Spreadsheet, 
      01/20/01 (provided by Carl Kloss)
 
   10. E-mail exchange with R.Tung & B.Adams, M01 Telecom, re. HGA and 
      MGA X-band pattern-based frames
      
 

Contact Information
-------------------------------------------------------------------------------

   Boris V. Semenov, NAIF/JPL, (818)-354-8136, bsemenov@spice.jpl.nasa.gov


Implementation Notes
-------------------------------------------------------------------------------

   This file is used by the SPICE system as follows: programs that make
   use of this frame kernel must `load' the kernel, normally during program
   initialization. The SPICELIB routine LDPOOL loads a kernel file into the 
   pool as shown below.

      CALL LDPOOL ( frame_kernel_name )

   This file was created and may be updated with a text editor or word
   processor.


M01 Frames
-------------------------------------------------------------------------------

   The following M01 frames are defined in this kernel file:

           Name                  Relative to           Type       NAIF ID
      ======================  ===================  ============   =======

   Spacecraft frame:
   -----------------
      M01_SPACECRAFT          rel.to MARSIAU       CK             -53000

   Science Instrument frames:
   --------------------------
      M01_GRS_HEAD_STOWED     rel.to SPACECRAFT    FIXED          -53020
      M01_GRS_HEAD_DEPLOYED   rel.to SPACECRAFT    FIXED          -53021
      M01_GRS_HEAD_COOLER     rel.to GRS_HEAD_DEP. FIXED          -53024

      M01_GRS_HEND            rel.to SPACECRAFT    FIXED          -53022

      M01_GRS_NS              rel.to SPACECRAFT    FIXED          -53023

      M01_THEMIS_OPTICS       rel.to SPACECRAFT    FIXED          -53030
      M01_THEMIS_IR           rel.to THEMIS        FIXED          -53031
      M01_THEMIS_VIS          rel.to THEMIS        FIXED          -53032

      M01_MARIE               rel.to SPACECRAFT    FIXED          -53040

   Antenna frames:
   ---------------
      M01_HGA_BOOM            rel.to SPACECRAFT    FIXED          -53210
      M01_HGA_INNER_GIMBAL    rel.to HGA_BOOM      CK             -53211
      M01_HGA_OUTER_GIMBAL    rel.to HGA_INNER_GIM CK             -53212

      M01_HGA_DEPLOYED        rel.to HGA_OUTER_GIM FIXED          -53213
      M01_MGA_DEPLOYED        rel.to HGA_DEPLOYED  FIXED          -53214
      M01_HGA_X_DEPLOYED      rel.to HGA_DEPLOYED  FIXED          -53215
      M01_MGA_X_DEPLOYED      rel.to MGA_DEPLOYED  FIXED          -53216

      M01_HGA_STOWED          rel.to SPACECRAFT    FIXED          -53223
      M01_MGA_STOWED          rel.to HGA_STOWED    FIXED          -53224
      M01_HGA_X_STOWED        rel.to HGA_STOWED    FIXED          -53225
      M01_MGA_X_STOWED        rel.to MGA_STOWED    FIXED          -53226

      M01_LGA                 rel.to SPACECRAFT    FIXED          -53230

      M01_UHF                 rel.to SPACECRAFT    FIXED          -53240

   Solar Array frames:
   -------------------
      M01_SA_INNER_GIMBAL     rel.to SPACECRAFT    CK             -53311
      M01_SA_OUTER_GIMBAL     rel.to SA_INNER_GIM  CK             -53312
      M01_SA_DEPLOYED         rel.to SA_OUTER_GIM  FIXED          -53313

      M01_SA_STOWED           rel.to SPACECRAFT    FIXED          -53323


M01 Frames Hierarchy
-------------------------------------------------------------------------------

   The diagram below shows M01 frames hierarchy:


                               "J2000" INERTIAL
        +------------------------------------------------------------+
        |                              |                             |
        | <--pck                       | <--built-in                 | <--pck
        |                              |                             |
        V                              |                             V
    "IAU_MARS"                         V                        "IAU_EARTH"
    MARS BFR(*)                    "MARSIAU"                    EARTH BFR(*)
    -----------                    ---------                    ------------
                                       |
                                       | <-ck
                                       |
                                       |
                                       |   "M01_MGA_X_DEPLOYED"
                                       |   --------------------
                                       |            ^
                                       |            |
                                       |            | <--fixed
                                       |            |
                                       |
                                       |    "M01_MGA_DEPLOYED"
                                       |    ------------------
                                       |            ^
                                       |            |
                                       |            | <--fixed
                                       |            |
                                       |            |    "M01_HGA_X_DEPLOYED"
                                       |            |    -------------------
                                       |            |                ^
                                       |            |                |
                                       |            |       fixed--> |
                                       |            |                |
    "M01_SA_DEPLOYED"                  |            |      "M01_HGA_DEPLOYED"
    -----------------                  |            +------------------------
        ^                              |                             ^
        |                              |                             |
        | <--fixed                     |                    fixed--> |
        |                              |                             |
    "M01_SA_OUTER_GIMBAL"              |               "M01_HGA_OUTER_GIMBAL"
    ---------------------              |               ----------------------
        ^                              |                             ^
        |                              |                             |
        | <--ck                        |                       ck--> |
        |                              |                             |
    "M01_SA_INNER_GIMBAL"              |               "M01_HGA_INNER_GIMBAL"
    ---------------------              |               ----------------------
        ^                              |                             ^
        |                              |                             |
        | <--ck                        |                       ck--> |
        |                              |                             |
        |                              |                       "M01_HGA_BOOM"
        |                              |                       --------------
        |                              |                             |
        |                              |                             |
        |                              |   "M01_MGA_X_STOWED"        |
        |                              |   ------------------        |
        |                              |     ^                       |
        |                              |     |                       |
        |                              |     | <--fixed              |
        |                              |     |                       |
        |    "M01_SA_STOWED"           |   "M01_MGA_STOWED"          |
        |    ---------------           |   ----------------          |
        |       ^                      |     ^                       |
        |       |                      |     |                       |
        |       | <--fixed             |     | <--fixed              |
        |       |                      |     |                       |
        |       |   "M01_LGA"          |     |   "M01_HGA_X_STOWED"  |
        |       |   ---------          |     |   ------------------  |
        |       |    ^                 |     |           ^           |
        |       |    |                 |     |           |           |
        |       |    | <--fixed        |     |           | <--fixed  |
        |       |    |                 |     |           |           |
        |       |    |   "M01_UHF"     |     |    "M01_HGA_STOWED"   |
        |       |    |   ---------     |     +--------------------   |
        |       |    |    ^            |              ^              |
        |       |    |    |            |              |              |
        |       |    |    |<--fixed    |     fixed--> |        ck--> |
        |       |    |    |            |              |              |
        |       |    |    |            |              |              |
        |       |    |    |    "M01_SPACECRAFT"       |              |
        +------------------------------------------------------------+
        |            |                     |    |               |    |
        | <--fixed   |                     |    |               |    |
        |            |                     |    |               |    |
        V            |                     |    |               |    |
    "M01_MARIE"      |                     |    |               |    |
    -----------      |                     |    |               |    |
                     | <--fixed            |    |               |    |
                     |                     |    |               |    |
                     V                     |    |               |    |
            "M01_THEMIS_OPTICS"            |    |               |    |
            +-----------------+            |    |               |    |
            |                 |            |    |               |    | 
            | <--fixed        | <--fixed   |    |               |    | 
            |                 |            |    |               |    |
            V                 V            |    |               |    |
      M01_THEMIS_IR"   "M01_THEMIS_VIS"    |    |               |    |
      --------------   ----------------    |    |               |    |
                                           |    |               |    |
                                           |    |               |    |
                                  fixed--> |    |      fixed--> |    |
                                           |    |               |    |
                                           V    |               V    |
                               "M01_GRS_HEND"   |     "M01_GRS_NS"   |
                               --------------   |     ------------   |
                                                |                    |
                                                | <--fixed           | <--fixed
                                                |                    |
                                                V                    V
                              "M01_GRS_HEAD_STOWED"  "M01_GRS_HEAD_DEPLOYED"
                              ---------------------  -----------------------
                                                                     |
                                                                     | <--fixed
                                                                     |
                                                                     V
                                                        "M01_GRS_HEAD_COOLER"
                                                        ---------------------

   (*) BFR -- body-fixed rotating frame


Spacecraft Bus Frame
-------------------------------------------------------------------------------
 

   The spacecraft frame (or AACS control frame) is defined by the s/c design 
   as follows [from 8]:

      -  X axis is parallel to stowed high gain antenna boresight;
 
      -  Y axis is normal to stowed solar arrays;

      -  Z axis is in the direction of the main engine thrust;

      -  the origin of the frame is centered on the launch 
         vehicle separation plane.

   (In [8] this frame is designated as "M" frame.)

   Since the S/C bus attitude with respect to an inertial frame is provided
   by a C kernel (see [3] for more information), this frame is defined as 
   a CK-based frame.

   \begindata

      FRAME_M01_SPACECRAFT     = -53000
      FRAME_-53000_NAME        = 'M01_SPACECRAFT'
      FRAME_-53000_CLASS       = 3
      FRAME_-53000_CLASS_ID    = -53000
      FRAME_-53000_CENTER      = -53
      CK_-53000_SCLK           = -53
      CK_-53000_SPK            = -53

   \begintext


M01 Science Instrument Frames
-------------------------------------------------------------------------------

   This section contains frame definitions for M01 science instruments --
   GRS (GRS Sensor Head, NS & HEND), THEMIS (IR & VIS) and MARIE.


GRS Frames
-----------

   The Gamma Ray Spectrometer (GRS) Sensor Head is mounted on the deployable
   boom attached to center of the science  deck. Its orientation in both 
   stowed and deployed configurations is constant with respect to the 
   spacecraft and, therefore, its frames for both configurations are a fixed 
   offset frames with orientation specified with respect to the spacecraft 
   frame.

   The axes of the M01_GRS_HEAD_STOWED and M01_GRS_HEAD_DEPLOYED frames are 
   defined by the instrument design as follows [see 4]:

      -  Z axis is perpendicular to the head sensor mounting plate and 
         points from the plate towards the opposite side of the instrument
         (nominally, this axis points in the same direction as the spacecraft 
         +Z axis)
         
      -  X axis is perpendicular to the +Z axis and is parallel to the plane
         containing +Z axis and the cooler symmetry axis (nominally, this  
         axis is rotated by -17 degrees from spacecraft +X axis about 
         spacecraft +Z axis)
         
      -  Y axis complements to the right hand frame (nominally, this axis 
         is rotated by -17 degrees from spacecraft +Y axis about spacecraft 
         +Z axis);
      
      -  the origin of this frame is located at the geometric center of the 
         sensor head.

   This diagram illustrates orientation of GRS sensor head frame (labeled
   "grs"):

                       _______________ HGA
                       \             /
                   ..   `._________.'  
    Science        || .___ +Xsc _ +Xgrs Science
     Orbit         ||+Ygrs    ^   ^   | Deck
   Velocity        || | ^     |  /    |
      ^.           || |  `.  _|_/     |
        `.         || |    `/ |/|     |
          `.       ||@| <--.--o /+Zsc |
                   || +Ysc  `._/ +Zgrs| (out of page)
                   || |               |
                   || | Science Deck  |
            Solar  || ._______________.
            Array  ..      
                           
                         / 
                        /  
                       / 
                      V
                Nadir

   Nominally, the GRS sensor head frames are rotated with respect to the 
   spacecraft frame by -17 degrees about spacecraft +Z axis [see 4]:

           grs
          M    = | 0.0 |  * | 0.0 |  * | -17.0 |
           sc           X          Y            Z

   (The frame definitions below contains the opposite of this rotation 
   because Euler angles specified in it define transformation from GRS 
   head frames to s/c frame -- see [1].)

   \begindata

      FRAME_M01_GRS_HEAD_STOWED    = -53020
      FRAME_-53020_NAME            = 'M01_GRS_HEAD_STOWED'
      FRAME_-53020_CLASS           = 4
      FRAME_-53020_CLASS_ID        = -53020
      FRAME_-53020_CENTER          = -53
      TKFRAME_-53020_SPEC          = 'ANGLES'
      TKFRAME_-53020_RELATIVE      = 'M01_SPACECRAFT'
      TKFRAME_-53020_ANGLES        = ( 0.0, 0.0, 17.0 )
      TKFRAME_-53020_AXES          = ( 1,   2,    3   )
      TKFRAME_-53020_UNITS         = 'DEGREES'

      FRAME_M01_GRS_HEAD_DEPLOYED  = -53021
      FRAME_-53021_NAME            = 'M01_GRS_HEAD_DEPLOYED'
      FRAME_-53021_CLASS           = 4
      FRAME_-53021_CLASS_ID        = -53021
      FRAME_-53021_CENTER          = -53
      TKFRAME_-53021_SPEC          = 'ANGLES'
      TKFRAME_-53021_RELATIVE      = 'M01_SPACECRAFT'
      TKFRAME_-53021_ANGLES        = ( 0.0, 0.0, 17.0 )
      TKFRAME_-53021_AXES          = ( 1,   2,    3   )
      TKFRAME_-53021_UNITS         = 'DEGREES'

   \begintext

   The axes of the M01_GRS_HEAD_COOLER frame are defined by the instrument 
   design as follows:

      -  Z axis is parallel to and points in the same direction as the 
         cooler FOV symmetry axis (nominally, this axis is rotated by +57 
         degrees from +Z axis of the GRS sensor head frame about +Y axis)
         
      -  Y axis is parallel to and points in the same direction as the GRS
         sensor head +Y axis;
         
      -  X axis complements to the right hand frame (nominally, this axis 
         is rotated by +57 degrees from +X axis of the GRS sensor head frame 
         about +Y axis)
      
      -  the origin of this frame is located at the geometric center of the 
         sensor head.

   Nominally, the GRS cooler frame is rotated with respect to the GRS sensor
   head frame by +57 degrees about sensor head frame +Y axis. The diagram 
   below illustrates this:

                                ^ +Zhead, +Zsc
                                |
                                |     57 deg
                                | /\
                                |/  \         .> +Zcooler
                                |    \    . '
                               /|     \ '     33 deg
                       +Yhead  \|  . ' \   
                       +Ycooler x'---------------> +Xhead
                     (into page) \_______o_
                             .____\______.\\
                             ._____\_____. \\
                               |`.  \  |    \\
                               |  `  v |     \\
                               | +Xcooler     \\ Cooler door (open)
                               |'----- |       -
                               |`.   .'|
                               |  `.'  |
                               | .' `. |
                               |'-----`|
                               |`.   .'|
                               

   In the definition below, the GRS cooler frame orientation is given with
   respect to the M01_GRS_HEAD_DEPLOYED frame.

   (The frame definitions below contains the opposite of this rotation 
   because Euler angles specified in it define transformation from cooler 
   frame to head frame -- see [1].)

   \begindata

      FRAME_M01_GRS_HEAD_COOLER    = -53024
      FRAME_-53024_NAME            = 'M01_GRS_HEAD_COOLER'
      FRAME_-53024_CLASS           = 4
      FRAME_-53024_CLASS_ID        = -53024
      FRAME_-53024_CENTER          = -53
      TKFRAME_-53024_SPEC          = 'ANGLES'
      TKFRAME_-53024_RELATIVE      = 'M01_GRS_HEAD_DEPLOYED'
      TKFRAME_-53024_ANGLES        = ( 0.0, -57.0,  0.0 )
      TKFRAME_-53024_AXES          = ( 1,     2,    3  )
      TKFRAME_-53024_UNITS         = 'DEGREES'

   \begintext

   The High Energy Neutron Detector (HEND) is mounted on the -Y side of the 
   science deck. Its orientation is constant with respect to the spacecraft 
   and, therefore, its frame is a fixed offset frame with orientation 
   specified with respect to the spacecraft frame.

   The axes of the M01_GRS_HEND frame are defined by the instrument design 
   as follows [see 4]:

      -  Z axis is perpendicular to the instrument mounting plate and 
         points from this plate towards the opposite side of the instrument
         (nominally, this axis is co-aligned with the spacecraft +Z axis);
         
      -  X axis is perpendicular to +Z axis and points towards [TBD] 
         (nominally, this axis is co-aligned with the spacecraft +X axis);
         
      -  Y axis complements to the right hand frame (nominally, this axis 
         is co-aligned with the spacecraft +Y axis);
      
      -  the origin of this frame is located at the geometric center of the 
         instrument.

   This diagram illustrates orientation of HEND frame [see 4]:

                       _______________ HGA
                       \             /
                   ..   `._________.'   ^+Xhend          
    Science        || ._______________. |
     Orbit         || |       ^+Xsc   |._. 
   Velocity        || |       |       ||||
      ^.           || |       | +Yhend_.||
        `.         || |       |   <-|---o| +Zhend
          `.       ||@| <-----o     .__ _.  (out of page)
                   || +Ysc   +Zsc     |
                   || |    (out of    |  HEND
                   || |      page)    |
            Solar  || ._______________.
            Array  ..    Science Deck

                         /
                        /
                       /
                      V Nadir 

   Since nominally axes of the spacecraft frame and HEND frame are co-aligned,
   no rotations are needed to transform one frame into the other.

   (The frame definition below contains the opposite of this rotation 
   because Euler angles specified in it define transformation from HEND 
   to s/c frame -- see [1].)

   \begindata

      FRAME_M01_GRS_HEND       = -53022
      FRAME_-53022_NAME        = 'M01_GRS_HEND'
      FRAME_-53022_CLASS       = 4
      FRAME_-53022_CLASS_ID    = -53022
      FRAME_-53022_CENTER      = -53
      TKFRAME_-53022_SPEC      = 'ANGLES'
      TKFRAME_-53022_RELATIVE  = 'M01_SPACECRAFT'
      TKFRAME_-53022_ANGLES    = ( 0.0, 0.0, 0.0 )
      TKFRAME_-53022_AXES      = ( 1,   2,    3  )
      TKFRAME_-53022_UNITS     = 'DEGREES'

   \begintext

   The Neutron Spectrometer (NS) is mounted on the -X side of the science 
   deck. Its orientation is constant with respect to the spacecraft and,
   therefore, its frame is a fixed offset frame with orientation specified 
   with respect to the spacecraft frame.

   The axes of the M01_GRS_NS frame are defined by the instrument design as 
   follows [see 4]:

      -  Z axis is along the instrument central axis and points from the 
         instrument edge by it is mounted to the deck (nominally, this axis 
         is co-aligned with the spacecraft +Z axis);
         
      -  X axis is perpendicular to +Z axis and points towards the edge by 
         which the instrument is mounted to the deck (nominally, it points 
         in the direction opposite to science orbit nadir direction);
         
      -  Y axis complements to the right hand frame (nominally it points 
         in the direction of science orbit velocity);
      
      -  the origin of this frame is located at the geometric center of the 
         instrument.

   This diagram illustrates orientation of NS frame:  

                       _______________ HGA
                       \             /
    Science        ..   `._________.'             
     Orbit         || ._______________.
   Velocity        || |       ^+Xsc   | Science Deck
      ^.           || |       |       |
        `.         || |       |       |
          `.       || +Ysc    |       | 
                   ||@| <-----o +Zsc (out of page)
                   || |               |
                   || |               |
                   || |         ^+Xns |
            Solar  || .________/______.
            Array  ..  ^. .___/
                     +Yns`.  /|
                          |`o | +Zns (out of page)
                          .___.
                            
                         /
                        /
                       /
                      V Nadir 
                          
   Nominally, a single rotation of -17 degrees about s/c +Z axis is needed 
   to align spacecraft frame axes with the NS frame axes [see 4]. 

   (The frame definition below contains the opposite of this rotation 
   because Euler angles specified in it define transformation from NS 
   to s/c frame -- see [1].)

   \begindata

      FRAME_M01_GRS_NS         = -53023
      FRAME_-53023_NAME        = 'M01_GRS_NS'
      FRAME_-53023_CLASS       = 4
      FRAME_-53023_CLASS_ID    = -53023
      FRAME_-53023_CENTER      = -53
      TKFRAME_-53023_SPEC      = 'ANGLES'
      TKFRAME_-53023_RELATIVE  = 'M01_SPACECRAFT'
      TKFRAME_-53023_ANGLES    = ( 0.0, 0.0, 17.0 )
      TKFRAME_-53023_AXES      = ( 1,   2,    3   )
      TKFRAME_-53023_UNITS     = 'DEGREES'

   \begintext


THEMIS Frames
-------------

   The Thermal Emission Imaging System (THEMIS) is mounted on the -X/-Y 
   corner of the science  deck. Its orientation is constant with respect to 
   the spacecraft and, therefore, its optics frame is a fixed offset frame 
   with orientation specified with respect to the spacecraft frame.

   The axes of the M01_THEMIS_OPTICS frame are defined by the instrument 
   design as follows [see 4,9]:

      -  X axis is parallel to the instrument optics boresight and
         points in the direction opposite (!) to the instrument
         boresight direction. (nominally, this axis is rotated by -17
         degrees from spacecraft +X axis about spacecraft +Z axis)
         
      -  Z axis is perpendicular to the instrument mounting plate and 
         points from this plate towards the opposite side of the instrument
         (nominally, this axis is parallel to and points in the same 
         direction as the spacecraft +Z axis);
         
      -  Y axis complements to the right hand frame (nominally, this axis 
         is rotated by -17 degrees from spacecraft +Y axis about spacecraft 
         +Z axis);
      
      -  the origin of this frame is located at the geometric center of the 
         instrument.

   This diagram illustrates orientation of THEMIS Optics frame (labeled
   "to"):

                       _______________ HGA
                       \             /
                   ..   `._________.'  
    Science        || ._______________. Science
     Orbit         || |       ^+Xsc   | Deck
   Velocity        || |       |       |
      ^.           || |       |       |
        `.         || |   +Zsc|       | ^
          `.       ||@| <-----o       |/ +Xto
                   || +Ysc     ^.     /
                   || |     +Yto `. _/_.
                   || |           /`o +Zto (out of page)
            Solar  || .__________/     |
            Array  ..           /   /._.
                               /   /
                         /     `. /
                        /      / `
                       /      /
                      V      V THEMIS Boresight
                Nadir

   Nominally, THEMIS Optics frame is rotated with respect to the spacecraft 
   frame by -17 degrees about spacecraft +Z axis [see 4]:

           to
          M    = | 0.0 |  * | 0.0 |  * | -17.0 |
           sc           X          Y            Z

   Actual THEMIS optics frame axis directions, as measured during final 
   pre-launch calibration with respect to the spacecraft frame axes and 
   provided in [9], are:

          Xto  = |  0.956737  -0.290952   0.001068  |
          Yto  = |  0.290953   0.956737  -0.000415  |
          Zto  = | -0.000901   0.000707   0.999999  |

   A matrix rotating vectors from the spacecraft frame to the THEMIS optics 
   frame can be constructed from these directions as follows:

           to    |  0.956737    0.290953  -0.000901 |
          M    = | -0.290952    0.956737   0.000707 |
           sc    |  0.001068   -0.000415   0.999999 |

   This matrix corresponds to the following combination of rotation angles:

           to
          M    = | -0.02377777 |  * | -0.06119193 |  * | -16.91497745 |
           sc                   X                  Y                   Z

   Note that these rotation angles approximately agree in magnitude and 
   direction with the THEMIS optical frame axes offset angles (AZ and EL) 
   measured during calibration and provided in [9].

   (The frame definition below contains the opposite of this rotation 
   because Euler angles specified in it define transformation from THEMIS 
   optics to s/c frame -- see [1].)

   \begindata

      FRAME_M01_THEMIS_OPTICS  = -53030
      FRAME_-53030_NAME        = 'M01_THEMIS_OPTICS'
      FRAME_-53030_CLASS       = 4
      FRAME_-53030_CLASS_ID    = -53030
      FRAME_-53030_CENTER      = -53
      TKFRAME_-53030_SPEC      = 'ANGLES'
      TKFRAME_-53030_RELATIVE  = 'M01_SPACECRAFT'
      TKFRAME_-53030_ANGLES    = ( 16.91497745, 0.06119193, 0.02377777 )
      TKFRAME_-53030_AXES      = ( 3,           2,          1          )
      TKFRAME_-53030_UNITS     = 'DEGREES'

   \begintext

   The axes of the M01_THEMIS_IR and M01_THEMIS_VIS frames are defined 
   along the lines of standard image frame convention:

      -  Z axis is along the instrument boresight (nominally, it points in 
         the direction opposite to the +X axis of the THEMIS optics frame);
         
      -  X axis is along the instrument CCD lines (nominally, it points in 
         the same direction as the +Z axis of the THEMIS optics frame);
         
      -  Y axis is perpendicular to the instrument CCD lines and complements 
         to the right hand frame (nominally, it points in the same direction 
         as the +Y axis of the THEMIS optics frame);
      
      -  the origin of this frame is located at the geometric center of the 
         instrument.

   This diagram illustrates orientation of THEMIS IR and VIS frames 
   (labeled "ir" and "vis"):

                       _______________ HGA
                       \             /
                   ..   `._________.'  
    Science        || ._______________. Science
     Orbit         || |       ^+Xsc   | Deck
   Velocity        || |       |       |
      ^.           || |       |       |
        `.         || |   +Zsc|       | ^
          `.       ||@| <-----o       |/ +Xto
                   || +Ysc     ^.     /
                   || |    +Yto  `. _/_.
                   || |    +Yir   /`o +Zto (out of page)
            Solar  || .____+Yvis_/ /  +Xir
            Array  ..           / / /.+Xvis
                               / / /
                         /     `/ /
                        /      / `
                       /      /
                      V      V +Zir
                Nadir          +Zvis
                               THEMIS Boresight

   Nominally, THEMIS IR and VIS frames are rotated with respect to the THEMIS
   optics frame by -90 degrees about THEMIS optics frame +Y axis:

           ir/vis
          M       = | 0.0 |  * | -90.0 |  * | 0.0 |
           to              X            Y          Z


   As part of the mapping image analysis carried out in March-July
   2002, Jim Torson, USGS determined that the actual IR detector rotation
   about +Z ("yaw rotation") is 0.572 degrees. Although the other two
   offsets -- about X and Y -- are not yet available, the value for Z
   rotation is provided in the 'M01_THEMIS_IR' definition below.

   Additional analysis by Jim Torson done during the fall of 2002
   resulted in the IR detector rotation about +Z of 0.672 degrees and
   the VIS detector rotation about +Z of 0.25 degrees. These offsets
   are provided in the definitions below; the offsets about the other
   two axes are still not available.

   (The frame definitions below contain the opposite of this rotation 
   because Euler angles specified in it define transformation from THEMIS 
   IR/VIS to optics frame -- see [1].)

   \begindata

      FRAME_M01_THEMIS_IR      = -53031
      FRAME_-53031_NAME        = 'M01_THEMIS_IR'
      FRAME_-53031_CLASS       = 4
      FRAME_-53031_CLASS_ID    = -53031
      FRAME_-53031_CENTER      = -53
      TKFRAME_-53031_SPEC      = 'ANGLES'
      TKFRAME_-53031_RELATIVE  = 'M01_THEMIS_OPTICS'
      TKFRAME_-53031_ANGLES    = ( 0.0, 90.0, -0.672 )
      TKFRAME_-53031_AXES      = ( 1,    2,    3     )
      TKFRAME_-53031_UNITS     = 'DEGREES'

      FRAME_M01_THEMIS_VIS     = -53032
      FRAME_-53032_NAME        = 'M01_THEMIS_VIS'
      FRAME_-53032_CLASS       = 4
      FRAME_-53032_CLASS_ID    = -53032
      FRAME_-53032_CENTER      = -53
      TKFRAME_-53032_SPEC      = 'ANGLES'
      TKFRAME_-53032_RELATIVE  = 'M01_THEMIS_OPTICS'
      TKFRAME_-53032_ANGLES    = ( 0.0, 90.0, -0.25  )
      TKFRAME_-53032_AXES      = ( 1,    2,    3  )
      TKFRAME_-53032_UNITS     = 'DEGREES'

   \begintext


MARIE Frame
-----------

   The Mars Radiation Environment Experiment (MARIE) is mounted on the -Y
   side of the propulsion unit deck. Its orientation is constant with 
   respect to the spacecraft and, therefore, its frame is a fixed offset 
   frame with orientation specified with respect to the spacecraft frame.

   The axes of the M01_MARIE frame are defined by the instrument design as 
   follows [see 6]:

      -  Y axis is parallel to the instrument FOV central axis and points 
         in the direction opposite to the FOV direction (nominally, this 
         axis is co-aligned with the spacecraft +Y axis);
         
      -  Z axis is perpendicular to +Y axis and instrument mounting plate 
         and points from mounting plate towards the opposite side 
         of the instrument enclosure (nominally, this axis is co-aligned 
         with the spacecraft +Z axis);
         
      -  X axis complements to the right hand frame (nominally, this axis 
         is co-aligned with the spacecraft +X axis);
      
      -  the origin of this frame is located at the instrument FOV focal 
         point.

   This diagram illustrates orientation of MARIE frame:

                       _______________ HGA
                       \             /
                   ..   `._________.'  
    Science        || ._______________.Science deck
     Orbit         || |       ^+Xsc   |
   Velocity        || |       |       |
      ^.           || |       |      ^+Xmarie .'   MARIE FOV 
        `.         || |       |+Zsc /||     .'   (68 deg cone)
          `.       ||@| <-----o ..'._|_.  .'
                   || +Ysc     /   | | |.'
                   || |     _.' <----o o-------->  MARIE FOV 
                   || |  _.'  +Ymarie _.`.         boresight
            Solar  || ..'_____________.   `.
            Array  ..       Bottom Deck     `.
                                              `.
                         /
                        /                            -------->
                       /                            Aerobraking 
                      V Nadir                        Velocity

   Since nominally axes of the spacecraft frame and MARIE frame are 
   co-aligned, no rotations are needed to transform one frame into 
   the other.

   (The frame definition below contains the opposite of this rotation 
   because Euler angles specified in it define transformation from MARIE
   to s/c frame -- see [1].)

   \begindata

      FRAME_M01_MARIE          = -53040
      FRAME_-53040_NAME        = 'M01_MARIE'
      FRAME_-53040_CLASS       = 4
      FRAME_-53040_CLASS_ID    = -53040
      FRAME_-53040_CENTER      = -53
      TKFRAME_-53040_SPEC      = 'ANGLES'
      TKFRAME_-53040_RELATIVE  = 'M01_SPACECRAFT'
      TKFRAME_-53040_ANGLES    = ( 0.0, 0.0, 0.0 )
      TKFRAME_-53040_AXES      = ( 1,   2,    3  )
      TKFRAME_-53040_UNITS     = 'DEGREES'

   \begintext


M01 Antenna Frames
-------------------------------------------------------------------------------

   This section contains frame definitions for M01 antennas -- HGA, MGA and 
   LGA -- in stowed and deployed positions.


High Gain Antenna
-----------------

   Both HGA boresight frames -- M01_HGA_STOWED and M01_HGA_DEPLOYED -- 
   are defined by antenna design as follows:

      -  Z axis is along the HGA reflector central symmetry axis (boresight 
         axis) and points from the reflector surface towards the feed horn
         (in stowed configuration it points along the s/c +X axis);
         
      -  Y axis is parallel to the outer gimbal rotation axis and 
         points from the gimbal towards the antenna center;
         
      -  X axis complements to the right hand frame;
      
      -  the origin of this frame is located at the intersection of the 
         antenna reflector symmetry axis and a plane containing HGA  
         reflector rim circle.
     
   For stowed position HGA does not move and its boresight (+Z axis) points 
   approximately along S/C +X axis. Therefore, its orientation can be 
   specified as a fixed offset with respect to the s/c frame. 

   Two rotations -- first by +90.0 degrees about s/c +Y axis and second 
   by approximately +30 degrees about +Z axis -- are needed to align s/c 
   axes with the HGA axes in stowed configuration (note that the second 
   rotation achieves only approximate alignment of the +X and +Y axes of 
   the antenna frame.)

   (The frame definition below contains the opposite of this rotation 
   because Euler angles specified in it define transformation from antenna 
   to s/c frame -- see [1].)

   \begindata

      FRAME_M01_HGA_STOWED       = -53223
      FRAME_-53223_NAME          = 'M01_HGA_STOWED'
      FRAME_-53223_CLASS         = 4
      FRAME_-53223_CLASS_ID      = -53223
      FRAME_-53223_CENTER        = -53
      TKFRAME_-53223_SPEC        = 'ANGLES'
      TKFRAME_-53223_RELATIVE    = 'M01_SPACECRAFT'
      TKFRAME_-53223_ANGLES      = ( 0.0, -90.0, -30.0 )
      TKFRAME_-53223_AXES        = ( 1,     2,     3   )
      TKFRAME_-53223_UNITS       = 'DEGREES'

   \begintext

   For deployed position orientation of the HGA is not constant with respect 
   to the s/c because the antenna is moved constantly using two 
   gimbals to track Earth. Therefore, for deployed position HGA frame 
   orientation should be specified as a fixed offset with respect to the 
   outer most gimbal in of the antenna drive mechanism, the outer gimbal.

   The frames -- antenna frame and outer gimbal frame -- are defined such 
   the their axes are co-aligned. Therefore, no rotation are need to 
   transform one into another. 

   \begindata

      FRAME_M01_HGA_DEPLOYED     = -53213
      FRAME_-53213_NAME          = 'M01_HGA_DEPLOYED'
      FRAME_-53213_CLASS         = 4
      FRAME_-53213_CLASS_ID      = -53213
      FRAME_-53213_CENTER        = -53
      TKFRAME_-53213_SPEC        = 'ANGLES'
      TKFRAME_-53213_RELATIVE    = 'M01_HGA_OUTER_GIMBAL'
      TKFRAME_-53213_ANGLES      = ( 0.0, 0.0, 0.0 )
      TKFRAME_-53213_AXES        = (   3,   2,   1 )
      TKFRAME_-53213_UNITS       = 'DEGREES'

   \begintext


HGA X-band Pattern Based Frames
-------------------------------

   The HGA X-band pattern based frames for deployed and stowed 
   configuration -- M01_HGA_X_STOWED and  M01_HGA_X_DEPLOYED -- are 
   defined as follows: 

      -  Z axis is along the HGA reflector central symmetry axis (boresight 
         axis) and points from the reflector surface towards the feed horn
         (in stowed configuration it points along the s/c +X axis);
         
      -  X axis is parallel to the X-band pattern clock angle reference 
         direction (in stowed configuration it points along the s/c +Y 
         axis);
         
      -  Y axis complements to the right hand frame;
      
      -  the origin of this frame is located at the intersection of the 
         antenna reflector symmetry axis and a plane containing HGA  
         reflector rim circle.   

   These frames are rotated by +60 degrees about +Z axis with respect to the
   corresponding antenna frames -- M01_HGA_STOWED and M01_HGA_DEPLOYED --
   to co-align the pattern clock angle reference axis (parallel to the s/c
   +Y axis in stowed configuration) with the X-band pattern based frame +X 
   axis.

   (The frame definitions below contain the opposite of this rotation 
   because Euler angles specified in it define transformation from X-band 
   pattern frame to antenna mechanical frame -- see [1].)

   \begindata

      FRAME_M01_HGA_X_STOWED     = -53225
      FRAME_-53225_NAME          = 'M01_HGA_X_STOWED'
      FRAME_-53225_CLASS         = 4
      FRAME_-53225_CLASS_ID      = -53225
      FRAME_-53225_CENTER        = -53
      TKFRAME_-53225_SPEC        = 'ANGLES'
      TKFRAME_-53225_RELATIVE    = 'M01_HGA_STOWED'
      TKFRAME_-53225_ANGLES      = ( 0.0, 0.0, -60.0 )
      TKFRAME_-53225_AXES        = ( 1,   2,     3   )
      TKFRAME_-53225_UNITS       = 'DEGREES'

      FRAME_M01_HGA_X_DEPLOYED   = -53215
      FRAME_-53215_NAME          = 'M01_HGA_X_DEPLOYED'
      FRAME_-53215_CLASS         = 4
      FRAME_-53215_CLASS_ID      = -53215
      FRAME_-53215_CENTER        = -53
      TKFRAME_-53215_SPEC        = 'ANGLES'
      TKFRAME_-53215_RELATIVE    = 'M01_HGA_DEPLOYED'
      TKFRAME_-53215_ANGLES      = ( 0.0, 0.0, -60.0 )
      TKFRAME_-53215_AXES        = ( 1,   2,     3   )
      TKFRAME_-53215_UNITS       = 'DEGREES'

   \begintext


HGA Gimbal Drive Frames
-----------------------

   When HGA is deployed using boom attached to the spacecraft bus by 
   a hinge, it can be rotated using two independent gimbals (i.e. it has 
   two degrees of freedom.) 
   
   After deployment the antenna boom position remains constant relative to
   the s/c bus. Therefore, its orientation can be provided as a fixed 
   offset with respect to the spacecraft frame. 

   The M01 HGA deployed boom frame (also known as antenna baseplate 
   frame HGABP, see [8]) is defined such that when antenna 
   is deployed and both gimbals are in zero position, the s/c frame can be 
   transformed into the HGA boom frame by four consequent rotations
   (angles are in degrees, rotation axes are specified as subscripts):

             boom          
            M     =  [180.0]  [30.056]  [-1.731]  [9.851]
             sc             Y         Z         Y        X

   or 
             boom   | -0.86514132  -0.48898862  -0.11144787 |
            M     = | -0.50061765   0.85536322   0.13317560 | 
             sc     |  0.03020705   0.17100849  -0.98480639 |

   
   (The frame definition below contains the opposite of this rotation, i.e.
   transpose of the matrix specified above, because it defines transformation 
   from boom to s/c frame -- see [1].)

   \begindata

      FRAME_M01_HGA_BOOM         = -53210
      FRAME_-53210_NAME          = 'M01_HGA_BOOM'
      FRAME_-53210_CLASS         = 4
      FRAME_-53210_CLASS_ID      = -53210
      FRAME_-53210_CENTER        = -53
      TKFRAME_-53210_SPEC        = 'MATRIX'
      TKFRAME_-53210_RELATIVE    = 'M01_SPACECRAFT'
      TKFRAME_-53210_MATRIX      = ( -0.86514132, -0.48898862, -0.11144787,
                                     -0.50061765,  0.85536322,  0.13317560,
                                      0.03020705,  0.17100849, -0.98480639 )

   \begintext

   The inner and outer gimbal rotations are time-dependent and should be 
   stored in a CK file. Therefore, inner and outer gimbal frames are 
   defined as CK-based frames.

   The M01 HGA inner gimbal frame:
   
      -  Y axis is along the inner gimbal rotation axis and points 
         toward outer gimbal; in deployed configuration with 
         the inner and outer gimbal angles set to zero it points along 
         the boom frame +Y axis;
         
      -  X axis is such that in deployed configuration with 
         the inner and outer gimbal angles set to zero it points along 
         the boom frame +X axis;

      -  Z axis complements to the right hand frame and in deployed 
         configuration with the inner and outer gimbal angles set to zero 
         it points along the boom frame +Z axis;
      
      -  the origin of this frame is located at the intersection of the 
         inner gimbal rotation axis and a plane perpendicular to this 
         rotation axis and containing the outer gimbal rotation axis.
            
   The M01 HGA outer gimbal frame:
   
      -  X axis is along the outer gimbal rotation axis and points 
         along the boom +X in deployed configuration with the inner and 
         outer gimbal angles set to zero;
         
      -  Y axis is such that in deployed configuration with 
         the inner and outer gimbal angles set to zero it points along 
         the boom +Y axis;

      -  Z axis complements to the right hand frame and in deployed 
         configuration with the inner and outer gimbal angles set to zero 
         it points along the boom +Z axis;
      
      -  the origin of this frame is located at the intersection of the 
         outer gimbal rotation axis and a plane perpendicular to this 
         rotation axis and containing the HGA frame origin;

   When antenna is deployed and both gimbals are in zero position axes 
   of the boom, inner gimbal, outer gimbal and HGA frames are co-aligned.
   The diagram below illustrates this:

                            * * * * *           
                         *             *        
                       *                 *     
                      *                   *     
                     *                     *    _  (into page)        
                    *     +Zhga (into page) *  / \   +Zboom        
                    *     .____________________\.x\  +Zig
                    *     |    .x             .'\_\\ +Zog          
                    *     .__.'__\__________.'_/ //\
                    *      .'     \        v    //  \        
                    *     V        \   +Yboom  //    V +Xboom        
                     +Yhga    +Xhga V  +Yig * //       +Xig      
                      *                +Yog* //        +Xog
                        *                 * //
                          *             *  //
                             * * * * *    //          
                                         //
                                        //     -- rotation in the inner  
                                       //         gimbal is about +Y (+Yig) 
                   ..                 // 
                   || .______________@@       
                   || |       ^+Xsc   |        -- rotation in the outer
                   || |       |       |           gimbal is about +X (+Xog)
                   || |       |       |
                   || |       |       |
                   ||@| <-----o       |
                   || | +Ysc   +Zsc (out of page)
                   || |               |
                   || | science deck  |
            solar  || ._______________.
            array  ..
                    

   Note that gimbal frames are defined such that rotation axis designations 
   are consistent with [8].
     
   Two sets of keywords below contain definitions for these frames.   

   \begindata

      FRAME_M01_HGA_INNER_GIMBAL = -53211
      FRAME_-53211_NAME          = 'M01_HGA_INNER_GIMBAL'
      FRAME_-53211_CLASS         = 3
      FRAME_-53211_CLASS_ID      = -53211
      FRAME_-53211_CENTER        = -53
      CK_-53211_SCLK             = -53
      CK_-53211_SPK              = -53

      FRAME_M01_HGA_OUTER_GIMBAL = -53212
      FRAME_-53212_NAME          = 'M01_HGA_OUTER_GIMBAL'
      FRAME_-53212_CLASS         = 3
      FRAME_-53212_CLASS_ID      = -53212
      FRAME_-53212_CENTER        = -53
      CK_-53212_SCLK             = -53
      CK_-53212_SPK              = -53

   \begintext


Medium Gain Antenna
-------------------

   Both MGA boresight frames -- M01_MGA_STOWED and M01_MGA_DEPLOYED -- 
   are defined by the antenna design as follows:

      -  Z axis is along the MGA reflector central symmetry axis (boresight 
         axis) and points from the reflector surface towards the feed horn
         (in stowed configuration along the s/c +X axis);
         
      -  X is [TBD] (in stowed configuration points along s/c -Z axis);
         
      -  Y complements to the right hand frame (in stowed configuration
         points along s/c +Y axis);
      
      -  the origin of this frame is located at the intersection of the 
         antenna reflector symmetry axis and a plane containing MGA reflector 
         rim circle.
     
   Since MGA is mounted on and does not move with respect to the HGA, its 
   orientation for both deployed and stowed configuration can be specified 
   as a fixed offset with respect to the corresponding HGA frames. 

   Because MGA frame orientation is the same as of the HGA, not rotations 
   needed to co-align these frames.

   \begindata

      FRAME_M01_MGA_STOWED       = -53224
      FRAME_-53224_NAME          = 'M01_MGA_STOWED'
      FRAME_-53224_CLASS         = 4
      FRAME_-53224_CLASS_ID      = -53224
      FRAME_-53224_CENTER        = -53
      TKFRAME_-53224_SPEC        = 'ANGLES'
      TKFRAME_-53224_RELATIVE    = 'M01_HGA_STOWED'
      TKFRAME_-53224_ANGLES      = ( 0.0, 0.0, 0.0 )
      TKFRAME_-53224_AXES        = ( 3,   2,   1   )
      TKFRAME_-53224_UNITS       = 'DEGREES'

      FRAME_M01_MGA_DEPLOYED     = -53214
      FRAME_-53214_NAME          = 'M01_MGA_DEPLOYED'
      FRAME_-53214_CLASS         = 4
      FRAME_-53214_CLASS_ID      = -53214
      FRAME_-53214_CENTER        = -53
      TKFRAME_-53214_SPEC        = 'ANGLES'
      TKFRAME_-53214_RELATIVE    = 'M01_HGA_DEPLOYED'
      TKFRAME_-53214_ANGLES      = ( 0.0, 0.0, 0.0 )
      TKFRAME_-53214_AXES        = ( 3,   2,   1   )
      TKFRAME_-53214_UNITS       = 'DEGREES'

   \begintext


MGA X-band Pattern Based Frames
-------------------------------

   The MGA X-band pattern based frames for deployed and stowed 
   configuration -- M01_MGA_X_STOWED and  M01_MGA_X_DEPLOYED -- are 
   defined as follows: 

      -  Z axis is along the MGA reflector central symmetry axis (boresight 
         axis) and points from the reflector surface towards the feed horn
         (in stowed configuration it points along the s/c +X axis);
         
      -  X axis is parallel to the X-band pattern clock angle reference 
         direction (in stowed configuration it points along the s/c +Y 
         axis);
         
      -  Y axis complements to the right hand frame;
      
      -  the origin of this frame is located at the intersection of the 
         antenna reflector symmetry axis and a plane containing MGA  
         reflector rim circle.   

   These frames are rotated by +60 degrees about +Z axis with respect to the
   corresponding antenna frames -- M01_MGA_STOWED and M01_MGA_DEPLOYED --
   to co-align the pattern clock angle reference axis (parallel to the s/c
   +Y axis in stowed configuration) with the X-band pattern based frame +X 
   axis.

   (The frame definitions below contain the opposite of this rotation 
   because Euler angles specified in it define transformation from X-band 
   pattern frame to antenna mechanical frame -- see [1].)

   \begindata

      FRAME_M01_MGA_X_STOWED     = -53226
      FRAME_-53226_NAME          = 'M01_MGA_X_STOWED'
      FRAME_-53226_CLASS         = 4
      FRAME_-53226_CLASS_ID      = -53226
      FRAME_-53226_CENTER        = -53
      TKFRAME_-53226_SPEC        = 'ANGLES'
      TKFRAME_-53226_RELATIVE    = 'M01_MGA_STOWED'
      TKFRAME_-53226_ANGLES      = ( 0.0, 0.0, -60.0 )
      TKFRAME_-53226_AXES        = ( 1,   2,     3   )
      TKFRAME_-53226_UNITS       = 'DEGREES'

      FRAME_M01_MGA_X_DEPLOYED   = -53216
      FRAME_-53216_NAME          = 'M01_MGA_X_DEPLOYED'
      FRAME_-53216_CLASS         = 4
      FRAME_-53216_CLASS_ID      = -53216
      FRAME_-53216_CENTER        = -53
      TKFRAME_-53216_SPEC        = 'ANGLES'
      TKFRAME_-53216_RELATIVE    = 'M01_MGA_DEPLOYED'
      TKFRAME_-53216_ANGLES      = ( 0.0, 0.0, -60.0 )
      TKFRAME_-53216_AXES        = ( 1,   2,     3   )
      TKFRAME_-53216_UNITS       = 'DEGREES'

   \begintext


Low Gain Antenna
----------------

   The LGA frame -- M01_LGA -- is defined by the antenna design as follows:

      -  Z axis is along the LGA antenna boresight direction, which is
         perpendicular the the antenna "patch" surface and points away
         from the surface;
         
      -  Y points in the same direction as the s/c +Y axis;
      
      -  X completes to the right hand frame;
         
      -  the origin of this frame is located at the geometric center of 
         the antenna "patch" square.
     
   Since LGA is mounted on and does not move with respect to the s/c, 
   its orientation can be specified as a fixed offset with respect to the 
   s/c frame.

   The Low Gain Antenna (LGA) boresight is 45 degrees from +X towards 
   -Z in the s/c frame, or exactly between the +X and -Z axes 
   (0.7071,0,-0.7071).  

   A single rotation by +135.0 degrees about s/c +Y axis is needed 
   to align s/c axes with the LGA axes.

   (The frame definition below contains the opposite of this rotation 
   because Euler angles specified in it define transformation from antenna 
   to s/c frame -- see [1].)

   \begindata

      FRAME_M01_LGA              = -53230
      FRAME_-53230_NAME          = 'M01_LGA'
      FRAME_-53230_CLASS         = 4
      FRAME_-53230_CLASS_ID      = -53230
      FRAME_-53230_CENTER        = -53
      TKFRAME_-53230_SPEC        = 'ANGLES'
      TKFRAME_-53230_RELATIVE    = 'M01_SPACECRAFT'
      TKFRAME_-53230_ANGLES      = ( 0.0, -135.0, 0.0 )
      TKFRAME_-53230_AXES        = ( 3,      2,   1   )
      TKFRAME_-53230_UNITS       = 'DEGREES'

   \begintext


UHF Antenna
-----------

   The UHF frame -- M01_UHF -- is defined by the antenna design as follows:

      -  Z axis is along the antenna central line and points aways from
         the spacecraft, nominally in the direction of the s/c -X axis;
         
      -  Y points in the same direction as the s/c +Y axis;
      
      -  X completes to the right hand frame. This axis is the antenna
         pattern clock angle reference axis;
         
      -  the origin of the UHF frame is located at center of the outer 
         plate of the antenna structure.
     
   This diagram illustrates orientation of the UHF frame:

                       _______________ HGA
                       \             /
                   ..   `._________.'  
    Science        || ._______________. Science
     Orbit         || |       ^+Xsc   | Deck
   Velocity        || |       |       |
      ^.           || |       |       |
        `.         || |   +Zsc|       |
          `.       ||@| <-----o       |
                   || +Ysc            |
                   || |            .___. THEMIS
                   || |           /    |
            Solar  || .__________/     |
            Array  ..           /   /__.
                               /   / |
                         /    <-----o. UHF (behind THEMIS) 
                        / +Yuhf  `  |
                       /            |                  
                      V             |               +Zsc and +Xuhf are 
                Nadir               v +Zuhf           out of the page.
                             

   Since UHF antenna is mounted on and does not move with respect to
   the s/c, its orientation can be specified as a fixed offset with
   respect to the s/c frame.

   A single rotation by -90.0 degrees about s/c +Y axis is needed 
   to align s/c axes with the UHF axes.

   (The frame definition below contains the opposite of this rotation 
   because Euler angles specified in it define transformation from antenna 
   to s/c frame -- see [1].)

   \begindata

      FRAME_M01_UHF              = -53240
      FRAME_-53240_NAME          = 'M01_UHF'
      FRAME_-53240_CLASS         = 4
      FRAME_-53240_CLASS_ID      = -53240
      FRAME_-53240_CENTER        = -53
      TKFRAME_-53240_SPEC        = 'ANGLES'
      TKFRAME_-53240_RELATIVE    = 'M01_SPACECRAFT'
      TKFRAME_-53240_ANGLES      = ( 0.0, 90.0, 0.0 )
      TKFRAME_-53240_AXES        = ( 3,    2,   1   )
      TKFRAME_-53240_UNITS       = 'DEGREES'

   \begintext


M01 Solar Array Frames
-------------------------------------------------------------------------------

   This section contains frame definitions for M01 Solar Array in stowed 
   and deployed positions.


Solar Array Frame
-----------------

   Both SA boresight frames -- M01_SA_STOWED and M01_SA_DEPLOYED -- 
   are defined by the solar array design as follows:

      -  Z axis is perpendicular to and points away from the array solar 
         cell side (in stowed configuration it points along the s/c +Y 
         axis; in deployed configuration with the inner and outer gimbal 
         angles set to zero it points along the s/c -Z axis);
         
      -  X axis points in the same direction as the outer gimbal X axis,
         which is the gimbal rotation axis (in both stowed configuration 
         and deployed configuration with the inner and outer gimbal 
         angles set to zero it points along the s/c +X axis);
      
      -  Y axis complements to the right hand frame (in stowed 
         configuration it points along the s/c -Z axis; in deployed 
         configuration with the inner and outer gimbal angles set to 
         zero it points along the s/c -Y axis);
         
      -  the origin of this frame is located at the geometric center of 
         central array panel.

   These diagrams illustrate solar array frame orientation in stowed and 
   deployed "0/0" configurations:

        Stowed Configuration              Deployed "0/0" Configuration
        --------------------              ----------------------------

                  +Xsc (HGA side)                      +Xsc (HGA side)
                   ^______                                ^______         
                   |     /|                               |     /|        
                  /|    / |                              /|    / |        
                 /_|___/  |                        /|   /_|___/  |        
                 | o------> +Zsc (science         / |   | o------> +Zsc   
            +Ysc |/    |  |        deck)         /  |   |/    |  |  (science
               __^__   | /                      /   |   /+Ysc | /     deck)
              |  |+Xsa_|/                      +Xsa |  V|_____|/          
        +Ysa  |  |  |                           | ^ | @                   
           <-----o  |                           | | |^  Array Gimbal      
              | /   |                           | | /                     
              |/____|                      +Zsa | |/|+Ysa                 
              V                             <-----o |                     
            +Zsa                                |   |                     
                                                |   |                     
                                                |   |                     
                                                |  /                      
                                                | /                       
                                                |/                        

   In stowed position SA does not move and its +Z axis points approximately 
   along S/C +Y axis. Therefore, its orientation can be specified as a fixed 
   offset with respect to the s/c frame. 

   A single rotation by -90.0 degrees about s/c +X axis is needed 
   to align s/c axes with the SA axes in stowed configuration.

   (The frame definition below contains the opposite of this rotation 
   because Euler angles specified in it define transformation from SA 
   to s/c frame -- see [1].)

   \begindata

      FRAME_M01_SA_STOWED        = -53323
      FRAME_-53323_NAME          = 'M01_SA_STOWED'
      FRAME_-53323_CLASS         = 4
      FRAME_-53323_CLASS_ID      = -53323
      FRAME_-53323_CENTER        = -53
      TKFRAME_-53323_SPEC        = 'ANGLES'
      TKFRAME_-53323_RELATIVE    = 'M01_SPACECRAFT'
      TKFRAME_-53323_ANGLES      = ( 0.0, 0.0, 90.0 )
      TKFRAME_-53323_AXES        = (   3,   2,  1   )
      TKFRAME_-53323_UNITS       = 'DEGREES'

   \begintext

   In deployed position orientation of the SA is not constant with respect 
   to the s/c because the array is moved constantly using two gimbals to 
   track Sun. Therefore, for deployed position SA frame orientation 
   should be specified as a fixed offset with respect to the outer most 
   gimbal in of the SA drive mechanism, the outer gimbal.

   A single rotation of 180 degrees about outer gimbal frame +X axis is 
   needed to align outer gimbal frame axes with the SA axes. 

   \begindata

      FRAME_M01_SA_DEPLOYED      = -53313
      FRAME_-53313_NAME          = 'M01_SA_DEPLOYED'
      FRAME_-53313_CLASS         = 4
      FRAME_-53313_CLASS_ID      = -53313
      FRAME_-53313_CENTER        = -53
      TKFRAME_-53313_SPEC        = 'ANGLES'
      TKFRAME_-53313_RELATIVE    = 'M01_SA_OUTER_GIMBAL'
      TKFRAME_-53313_ANGLES      = ( 0.0, 0.0, 180.0 )
      TKFRAME_-53313_AXES        = (   3,   2,   1   )
      TKFRAME_-53313_UNITS       = 'DEGREES'

   \begintext


Solar Array Gimbal Drive Frames
-------------------------------

   When SA is deployed, it can be rotated using two independent gimbals 
   (i.e. it has two degrees of freedom.) These two rotations -- in inner 
   and outer gimbals -- are time-dependent and should be stored in a CK 
   file. Therefore, SA inner are outer gimbal frames are CK-based frames 
   defined by the SA design as follows:

   The M01 SA inner gimbal frame:
   
      -  Y axis is along the inner gimbal rotation axis and points 
         from the s/c toward outer gimbal; in deployed configuration with 
         the inner and outer gimbal angles set to zero it points along 
         the s/c +Y axis;
         
      -  X axis is such that in deployed configuration with 
         the inner and outer gimbal angles set to zero it points along 
         the s/c +X axis;

      -  Z axis complements to the right hand frame and in deployed 
         configuration wit the inner and outer gimbal angles set to zero 
         it points along the s/c +Z axis;
      
      -  the origin of this frame is located at the intersection of the 
         inner gimbal rotation axis and a plane perpendicular to this 
         rotation axis and containing the outer gimbal rotation axis.
      
   The M01 SA outer gimbal frame:
   
      -  X axis is along the outer gimbal rotation axis and points 
         along the s/c +X in deployed configuration with the inner and 
         outer gimbal angles set to zero;
         
      -  Y axis is such that in deployed configuration with 
         the inner and outer gimbal angles set to zero it points along 
         the s/c +Y axis;

      -  Z axis complements to the right hand frame and in deployed 
         configuration with the inner and outer gimbal angles set to zero 
         it points along the s/c +Z axis;
      
      -  the origin of this frame is located at the intersection of the 
         outer gimbal rotation axis and a plane perpendicular to this 
         rotation axis and containing the solar array frame origin;

   The diagram below illustrates solar array gimbal frames in
   deployed "0/0" configuration:

                         +Xsc (HGA side)          
                              ^______         
                              |     /|        
                             /|    / |        
                            /_|___/  |        
                            | o------> +Zsc (science deck)
                 +Xig,+Xog  |/    |  |        
                        ^   /+Ysc | /         
                        |  V|_____|/          
                  /|    |                   
                 / |    o----> +Zig,+Zog                     
                /  |   /                  
             +Xsa  |  /+Yig,+Yog
               | ^ | V
               | | |^
               | | /+Ysa                -- rotation in the inner gimbal is 
          +Zsa | |/|                       about +Y axis (+Yig);
           <-----o |                     
               |   |                    -- rotation in the outer gimbal is 
               |   |                       about +X axis (+Xog)
               |   |                     
               |  /                      
               | /                       
               |/                        

   Note that gimbal frames are defined such that rotation axis designations 
   are consistent with [8].

   Two sets of keywords below contain definitions for these frames.   

   \begindata

      FRAME_M01_SA_INNER_GIMBAL  = -53311
      FRAME_-53311_NAME          = 'M01_SA_INNER_GIMBAL'
      FRAME_-53311_CLASS         = 3
      FRAME_-53311_CLASS_ID      = -53311
      FRAME_-53311_CENTER        = -53
      CK_-53311_SCLK             = -53
      CK_-53311_SPK              = -53

      FRAME_M01_SA_OUTER_GIMBAL  = -53312
      FRAME_-53312_NAME          = 'M01_SA_OUTER_GIMBAL'
      FRAME_-53312_CLASS         = 3
      FRAME_-53312_CLASS_ID      = -53312
      FRAME_-53312_CENTER        = -53
      CK_-53312_SCLK             = -53
      CK_-53312_SPK              = -53

   \begintext


Mars'01 Odyssey Mission NAIF ID Codes -- Definition Section
========================================================================

   This section contains name to NAIF ID mappings for the M01 mission.
   Once the contents of this file is loaded into the KERNEL POOL, these 
   mappings become available within SPICE, making it possible to use 
   names instead of ID code in the high level SPICE routine calls. 

   Spacecraft:
   -----------
      MARS SURVEYOR 01 ORBITER   -53
      M01                        -53
      M01_SPACECRAFT             -53000
      M01_SPACECRAFT_BUS         -53000
      M01_SC_BUS                 -53000

   Science Instruments:
   --------------------
      M01_GRS_HEAD               -53021
      M01_GRS_HEAD_STOWED        -53020
      M01_GRS_HEAD_DEPLOYED      -53021
      M01_GRS_HEAD_COOLER        -53024
      M01_GRS_HEND               -53022
      M01_GRS_NS                 -53023
      M01_THEMIS                 -53030
      M01_THEMIS_IR              -53031
      M01_THEMIS_VIS             -53032
      M01_MARIE                  -53040

   Antennas:
   ---------
      M01_HGA_BOOM               -53210
      M01_HGA_INNER_GIMBAL       -53211
      M01_HGA_OUTER_GIMBAL       -53212
      M01_HGA_DEPLOYED           -53213
      M01_MGA_DEPLOYED           -53214
      M01_HGA_STOWED             -53223
      M01_MGA_STOWED             -53224
      M01_LGA                    -53230
      M01_UHF                    -53240

   Solar Array:
   ------------
      M01_SA_INNER_GIMBAL        -53311
      M01_SA_OUTER_GIMBAL        -53312
      M01_SA_DEPLOYED            -53313
      M01_SA_DEPLOYED_C1         -53314
      M01_SA_DEPLOYED_C2         -53315
      M01_SA_DEPLOYED_C3         -53316
      M01_SA_DEPLOYED_C4         -53317

   The mappings summarized in this table are implemented by the keywords 
   below.

   \begindata

      NAIF_BODY_NAME += ( 'MARS SURVEYOR 01 ORBITER'  )
      NAIF_BODY_CODE += ( -53                         )

      NAIF_BODY_NAME += ( 'M01'                       )
      NAIF_BODY_CODE += ( -53                         )

      NAIF_BODY_NAME += ( 'M01_SPACECRAFT'            )
      NAIF_BODY_CODE += ( -53000                      )

      NAIF_BODY_NAME += ( 'M01_SPACECRAFT_BUS'        )
      NAIF_BODY_CODE += ( -53000                      )

      NAIF_BODY_NAME += ( 'M01_SC_BUS'                )
      NAIF_BODY_CODE += ( -53000                      )

      NAIF_BODY_NAME += ( 'M01_GRS_HEAD'              )
      NAIF_BODY_CODE += ( -53021                      )

      NAIF_BODY_NAME += ( 'M01_GRS_HEAD_STOWED'       )
      NAIF_BODY_CODE += ( -53020                      )
 
      NAIF_BODY_NAME += ( 'M01_GRS_HEAD_DEPLOYED'     )
      NAIF_BODY_CODE += ( -53021                      )

      NAIF_BODY_NAME += ( 'M01_GRS_HEAD_COOLER'       )
      NAIF_BODY_CODE += ( -53024                      )

      NAIF_BODY_NAME += ( 'M01_GRS_HEND'              )
      NAIF_BODY_CODE += ( -53022                      )

      NAIF_BODY_NAME += ( 'M01_GRS_NS'                )
      NAIF_BODY_CODE += ( -53023                      )

      NAIF_BODY_NAME += ( 'M01_THEMIS'                )
      NAIF_BODY_CODE += ( -53030                      )

      NAIF_BODY_NAME += ( 'M01_THEMIS_IR'             )
      NAIF_BODY_CODE += ( -53031                      )

      NAIF_BODY_NAME += ( 'M01_THEMIS_VIS'            )
      NAIF_BODY_CODE += ( -53032                      )

      NAIF_BODY_NAME += ( 'M01_MARIE'                 )
      NAIF_BODY_CODE += ( -53040                      )

      NAIF_BODY_NAME += ( 'M01_HGA_BOOM'              )
      NAIF_BODY_CODE += ( -53210                      )

      NAIF_BODY_NAME += ( 'M01_HGA_INNER_GIMBAL'      )
      NAIF_BODY_CODE += ( -53211                      )

      NAIF_BODY_NAME += ( 'M01_HGA_OUTER_GIMBAL'      )
      NAIF_BODY_CODE += ( -53212                      )

      NAIF_BODY_NAME += ( 'M01_HGA_DEPLOYED'          )
      NAIF_BODY_CODE += ( -53213                      )

      NAIF_BODY_NAME += ( 'M01_MGA_DEPLOYED'          )
      NAIF_BODY_CODE += ( -53214                      )

      NAIF_BODY_NAME += ( 'M01_HGA_STOWED'            )
      NAIF_BODY_CODE += ( -53223                      )

      NAIF_BODY_NAME += ( 'M01_MGA_STOWED'            )
      NAIF_BODY_CODE += ( -53224                      )

      NAIF_BODY_NAME += ( 'M01_LGA'                   )
      NAIF_BODY_CODE += ( -53230                      )

      NAIF_BODY_NAME += ( 'M01_UHF'                   )
      NAIF_BODY_CODE += ( -53240                      )

      NAIF_BODY_NAME += ( 'M01_SA_INNER_GIMBAL'       )
      NAIF_BODY_CODE += ( -53311                      )

      NAIF_BODY_NAME += ( 'M01_SA_OUTER_GIMBAL'       )
      NAIF_BODY_CODE += ( -53312                      )

      NAIF_BODY_NAME += ( 'M01_SA_DEPLOYED'           )
      NAIF_BODY_CODE += ( -53313                      )

      NAIF_BODY_NAME += ( 'M01_SA_DEPLOYED_C1'        )
      NAIF_BODY_CODE += ( -53314                      )

      NAIF_BODY_NAME += ( 'M01_SA_DEPLOYED_C2'        )
      NAIF_BODY_CODE += ( -53315                      )

      NAIF_BODY_NAME += ( 'M01_SA_DEPLOYED_C3'        )
      NAIF_BODY_CODE += ( -53316                      )

      NAIF_BODY_NAME += ( 'M01_SA_DEPLOYED_C4'        )
      NAIF_BODY_CODE += ( -53317                      )

   \begintext
