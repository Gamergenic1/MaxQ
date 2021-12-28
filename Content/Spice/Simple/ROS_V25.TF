KPL/FK

Rosetta Spacecraft and Rosetta Lander Frames Kernel
========================================================================

   This frame kernel contains complete set of frame definitions for the
   Rosetta Spacecraft (ROS) and Rosetta Lander (ROS_LANDER) including
   definitions for the Rosetta spacecraft and Rosetta science
   instrument frames and Rosetta Lander fixed, Rosetta Lander
   instrument, and landing site local frames. This kernel also contains
   NAIF name/ID mappings for the Rosetta and Rosetta Lander
   instruments, and name/ID mappings for the Rosetta target body DSK
   surfaces.


Version and Date
========================================================================

   Version 2.5 -- December 3, 2015 -- Boris Semenov, NAIF

      Added the ROS_AUX_NADIR frame previously defined in
      ROS_CGS_AUX_V01.TF. The frame ID was changed from -226910 to
      -226918 to avoid conflict with the existing 67P/C-G_CSEQ frame.

      Added the 67P/C-G_CK frame and accompanying SCLK keywords
      previously defined in ROS_CHURYUMOV_V01.TF.

      Added the ROS_RCO frame.

      Added the target body DSK surface name/ID mappings section.

      Added the Star Tracker frames, ROS_STR-A and ROS_STR-B.

      Updated NAVCAM alignments based on [14].

      Updated the frame summary table and frame tree diagrams.

   Version 2.4 -- September 24, 2014 -- Maud Barthelemy, ESA
                                        Boris Semenov, NAIF

      Added ROLIS frames and name/ID code mappings.

   Version 2.3 -- August 21, 2014 -- Maud Barthelemy, ESA;
                                     Boris Semenov, NAIF

      Added SESAME DIM frames.

   Version 2.2 -- August 8, 2014 -- A. Steffl, SwRI

      Alice frames updated to reflect post-hibernation boresight positions

   Version 2.1 -- July 28, 2014 -- Federico Tosi, INAF-IAPS;
                                   Boris Semenov, NAIF

      Incorporated updated VIRTIS-M VIS anf IR frame definitions from
      [12]; added NAIF ID/name mapping for
      ROS_VIRTIS-M_IR_ZERO/-226214.

   Version 2.0 -- July 18, 2014 -- J. Vazquez

      Corrected the labels +Yhga_el and +Yhga_az in the schema for the HGA.
      This information was provided by Rudy Frahm (SWRI).

   Version 1.9 -- June 12, 2013 -- Maud Barthelemy, ESAC;
                                  Boris Semenov, NAIF

      Changed the name of the surface frame at the landing site
      (ROSLND_LOCAL_LEVEL -> ROS_LANDER_TOPO); changed the lander frame
      name, ID, and type (ROSLND_LANDER -> ROS_LANDER, -226900 ->
      -226800, FIXED->CK); added CIVA-P frames
      (ROS_LANDER_CIVA_P_(1...7)); added landing site, lander and
      CIVA-P name/ID mappings;

   Version 1.8 -- December 22, 2011 -- Boris Semenov, NAIF

      Added '21/LUTETIA_CSEQ' and '67P/C-G_CSEQ' -- body-Centered Solar
      EQuatorial frames for Lutetia and 67P/Churyumov-Gerasimenko

   Version 1.7 -- November 15, 2010 --- Bjoern Grieger, ESAC/ESAC

      Added NAIF ID/name pairs for ROS_VIRTIS-M_VIS_ZERO

   Version 1.6 -- January 26, 2010 -- Jose Luis Vazquez, ESA/ESAC

      Added NAIF ID/name pairs for ALICE_-X_WIDE_TOP and ALICE_+X_WIDE_BOTTOM.
      ROS_ALICE_OUTER1 and ROS_ALICE_OUTER2 removed.

   Version 1.5 -- January 7, 2010 -- Boris Semenov, NAIF

      Added '2867/STEINS_CSO' and '21/LUTETIA_CSO' -- body-Centered
      Solar Orbital frames for Steins and Lutetia.

   Version 1.4 -- September 22, 2008 -- Jose Luis Vazquez, ESAC

      Updated frame orientation for ALICE and VIRTIS-H, with the
      information in [7].

   Version 1.3 -- April 2, 2008 -- Jose Luis Vazquez, ESAC

      Updated frame orientation for ALICE and VIRTIS-H, with the
      information in [7].

   Version 1.2 -- June 16, 2007 -- Boris Semenov, NAIF

      Incorporated updated VIRTIS-M and -H frame definitions provided
      by Federico Tosi, INAF-IFSI [10]; updated description of the
      VIRTIS alignments to be similar to those for VEX VIRTIS;

   Version 1.1 -- December 6, 2006 -- Boris Semenov, NAIF


      Added '45P/H-M-P_CSO' frame -- Comet-centered Solar Orbital frame
      for Rosetta's incidental target (July 2006 pass through the
      ion tail) comet 45P/Honda-Mrkos-Pajdusakova. Corrected the center
      ID in the '67P/C-G_CSO' frame definition (was erroneously set to
      399; was now reset to 1000012). Added aliases for the comet
      45P/Honda-Mrkos-Pajdusakova to the name-ID mapping set.

   Version 1.0 -- September 8, 2006 -- Boris Semenov, NAIF

      Added '67P/C-G_CSO' frame -- Comet-centered Solar Orbital frame
      for Rosetta's primary target comet 67P/Churyumov-Gerasimenko

   Version 0.9 -- September 7, 2006 -- Boris Semenov, NAIF

      Re-implemented the solar array and HGA frame chains to allow for
      simpler representation of the appendage orientation data using
      CKs.

      Added name/ID mappings for the solar array and spacecraft bus
      corners.

   Version 0.8 -- September 6, 2006 -- Federico Tosi, INAF-IFSI &
                                       Boris Semenov, NAIF

      Changed the VIRTIS frames implementation as follows:

         -  removed ROS_VIRTIS-M_VIS_SCAN/-226212,
            ROS_VIRTIS-M_IR_SCAN/-226214 and ROS_VIRTIS_URF/-226230
            name/ID mappings;

         -  removed ROS_VIRTIS-M_VIS_SCAN, ROS_VIRTIS-M_IR_SCAN, and
            ROS_VIRTIS_URF frames;

         -  added ROS_VIRTIS-M_SCAN, ROS_VIRTIS-M_VIS_ZERO, and
            ROS_VIRTIS-M_IR_ZERO frames;

         -  updated the VIRTIS frame tree diagram and frame
            descriptions for the new implementation.

   Version 0.7 -- September 5, 2006 -- Boris Semenov, NAIF

      Changed definition of the ROS_RPC_ICA frame to be consistent
      with [9].

   Version 0.6 -- May 31, 2005 -- Boris Semenov, NAIF

      Updated RPC/MAG instrument/frame names and other parameters
      based on the feedback comments from Dr. Ingo Richter [8],
      specifically:

         -- renamed MAG sensors (MAG1 -> MAG_OB, MAG2 -> MAG_IB)

         -- renamed MAG sensor frames the same way

         -- changed BOOM2 frame class to be CK-based frame
            (its orientation is now provided in CK files)

         -- changed MAG_OB and MAG_IB frame definitions and
            incorporated their actual alignments relative to the
            BOOM2 frame into the definitions.

   Version 0.5 -- March 21, 2005 -- Boris Semenov, NAIF

      Updated MIRO_MM frame definition based on the change of the
      alignment angle ``Offset from Z s/c: y'' from -0.0057 deg to
      -0.057 deg.

   Version 0.4 -- March 14, 2005 -- Boris Semenov, NAIF

      Preliminary Version. Pending review and approval by Rosetta and
      Rosetta Lander instrument teams and ESTEC Science operations
      team.

      Added frames and name/ID mapping for NAVCAMs. Re-arranged MIRO
      frames. Added MRO_VIRTIS-M FRAME and re-arranged VIRTIS-M frames.
      Filled in calibrated alignments based on the instrument boresight
      directions from [7] for ALICE, MIRO, OSIRIS, VIRTIS, and NAVCAMs.

   Version 0.3 -- September 24, 2004 -- Boris Semenov, NAIF

      Preliminary Version. Pending review and approval by Rosetta and
      Rosetta Lander instrument teams and ESTEC Science operations
      team.

      Added RPC frames.

   Version 0.2 -- September 2, 2004 -- Boris Semenov, NAIF

      Preliminary Version. Pending review and approval by Rosetta and
      Rosetta Lander instrument teams and ESTEC Science operations
      team.

      Added MIDAS, CONSERT, and GIADA frames.

   Version 0.1 -- August 13, 2004 -- Boris Semenov, NAIF

      Preliminary Version. Pending review and approval by Rosetta and
      Rosetta Lander instrument teams and ESTEC Science operations
      team.

      Added comet and asteroid frame and ID/name mapping definitions.

   Version 0.0 -- August 3, 2004 -- Boris Semenov, NAIF

      Preliminary Version. Pending review and approval by Rosetta and
      Rosetta Lander instrument teams and ESTEC Science operations
      team.


References
========================================================================

   1. ``Frames Required Reading''

   2. ``Kernel Pool Required Reading''

   3. ``C-Kernel Required Reading''

   4. Rosetta Instrument EID/Part B Documents; latest versions as
      of 08/03/04

   5. ``Coordinate Systems for Rosetta'', RO-DSS-TN-1081, 6d, 2004/09/17

   6. ``Rosetta Experiment Booms'', RO-SEN-TN-3501, 2000/02/16

   7. ``Payload Boresight Alignment Details'', RO-EST-TN-3305,
      2008/01/17

   8. E-mail "ROSETTA RPC-MAG FK / IK Comments" from Dr. Ingo Richter,
      2005/04/19.

   9. RPC-ICA-EAICD, November 5, 2003

  10. ``Changes in ROSETTA's FK'', E-mail from Federico Tosi, INAF -
      IFSI

  11. ``Computing Euler Angles from Offsets (title TBC)'', (Document number
      TBD) J. Vazquez

  12. ``Updated numbers for the VIRTIS section of Rosetta's FK'',
      E-mail from Federico Tosi, INAF-IAPS

  13. Draft Star Tracker name/ID and frame definitions by Bjorn Grieger,
      ROS_V24+str2.TF, November 24, 2015

  14. Updated NAVCAM alignments and frame definitions; e-mail from 
      Bernhard Geiger, November 26, 2015


Contact Information
========================================================================

   Boris V. Semenov, NAIF/JPL, (818)-354-8136, boris.semenov@jpl.nasa.gov
   Jose Luis Vazquez, ESAC/ESA, +34 91 8131 310, jlvazquez@sciops.esa.int


Implementation Notes
========================================================================

   This file is used by the SPICE system as follows: programs that make
   use of this frame kernel must `load' the kernel, normally during
   program initialization. The SPICELIB routine FURNSH and CSPICE
   function furnsh_c load a kernel file into the kernel pool as shown
   below.

      CALL FURNSH ( 'frame_kernel_name' )
      furnsh_c    ( "frame_kernel_name" );

   This file was created and may be updated with a text editor or word
   processor.


Rosetta Mission NAIF ID Codes -- Summary Section
========================================================================

   The following names and NAIF ID codes are assigned to the Rosetta
   spacecraft, its structures and science instruments (the keywords
   implementing these definitions are located in the section "Rosetta
   Mission NAIF ID Codes -- Definition Section" at the end of this
   file):

   Rosetta Targets:

      CHURYUMOV-GERASIMENKO     1000012 (synonyms: 67P/C-G,
                                         67P/CHURYUMOV-GERASIMENKO)

      STEINS                    2002867 (synonyms: 2867 STEINS)

      LUTETIA                   2000021 (synonyms: 21 LUTETIA)

      HONDA-MRKOS-PAJDUSAKOVA   1000045 (synonyms: 45P/H-M-P,
                                         45P/HONDA-MRKOS-PAJDUSAKOVA)


   Rosetta Spacecraft and Spacecraft Structures names/IDs:

      ROS                       -226      (synonyms: ROSETTA,
                                        ROSETTA ORBITER)
      ROS_SPACECRAFT            -226000 (synonym: ROS_SC)

      ROS_MGA-S                 -226030
      ROS_MGA-X                 -226040
      ROS_LGA-1                 -226050
      ROS_LGA-2                 -226060

      ROS_HGA_GIMBAL            -226070
      ROS_HGA                   -226075

      ROS_SA+Y_GIMBAL           -226010
      ROS_SA+Y_C1               -226011
      ROS_SA+Y_C2               -226012
      ROS_SA+Y_C3               -226013
      ROS_SA+Y_C4               -226014

      ROS_SA-Y_GIMBAL           -226020
      ROS_SA-Y_C1               -226021
      ROS_SA-Y_C2               -226022
      ROS_SA-Y_C3               -226023
      ROS_SA-Y_C4               -226024

      ROS_SPACECRAFT_C1         -226001
      ROS_SPACECRAFT_C2         -226002
      ROS_SPACECRAFT_C3         -226003
      ROS_SPACECRAFT_C4         -226004
      ROS_SPACECRAFT_C5         -226005
      ROS_SPACECRAFT_C6         -226006
      ROS_SPACECRAFT_C7         -226007
      ROS_SPACECRAFT_C8         -226008

   Star Tracker names/IDs:

      ROS_STR-A                 -226080
      ROS_STR-B                 -226090

   OSIRIS names/IDs:

      ROS_OSIRIS                -226110
      ROS_OSIRIS_NAC            -226111
      ROS_OSIRIS_NAC_URF        -226116
      ROS_OSIRIS_WAC            -226112
      ROS_OSIRIS_WAC_URF        -226117

   ALICE names/IDs:

      ROS_ALICE                 -226120
      ROS_ALICE_CENTER          -226121
      ROS_ALICE_-X_WIDE_BOTTOM  -226122
      ROS_ALICE_+X_WIDE_TOP     -226123
      ROS_ALICE_PINHOLE         -226124
      ROS_ALICE_URF             -226125

   VIRTIS names/IDs:

      ROS_VIRTIS                -226200
      ROS_VIRTIS-M              -226210
      ROS_VIRTIS-M_VIS          -226211
      ROS_VIRTIS-M_IR           -226213
      ROS_VIRTIS-H              -226220

   MIRO names/IDs:

      ROS_MIRO                  -226130
      ROS_MIRO_MM               -226131
      ROS_MIRO_SUBMM            -226132
      ROS_MIRO_URF              -226135

   ROSINA names/IDs:

      ROS_ROSINA                -226300
      ROS_ROSINA_DFMS           -226310
      ROS_ROSINA_DFMS_WA        -226311
      ROS_ROSINA_DFMS_NA        -226312
      ROS_ROSINA_DFMS_URF       -226319
      ROS_ROSINA_RTOF           -226320
      ROS_ROSINA_RTOF_URF       -226329
      ROS_ROSINA_COPS           -226330
      ROS_ROSINA_COPS_URF       -226339

   COSIMA names/IDs:

      ROS_COSIMA                -226140
      ROS_COSIMA_URF            -226145

   MIDAS names/IDs:

      ROS_MIDAS                 -226150
      ROS_MIDAS_URF             -226155

   CONSERT names/IDs:

      ROS_CONSERT               -226160
      ROS_CONSERT_URF           -226165

   NAVCAM names/IDs:

      ROS_NAVCAM-A              -226170
      ROS_NAVCAM-A_URF          -226175
      ROS_NAVCAM-B              -226180
      ROS_NAVCAM-B_URF          -226185

   GIADA names/IDs:

      ROS_GIADA                 -226400
      ROS_GIADA_GDS             -226410
      ROS_GIADA_IS              -226420
      ROS_GIADA_MBS1            -226431
      ROS_GIADA_MBS2            -226432
      ROS_GIADA_MBS3            -226433
      ROS_GIADA_MBS4            -226434
      ROS_GIADA_MBS5            -226435
      ROS_GIADA_URF             -226440

   RPC names/IDs:

      ROS_RPC                   -226500
      ROS_RPC_LAP1              -226511
      ROS_RPC_LAP2              -226512
      ROS_RPC_LAP1_URF          -226515
      ROS_RPC_LAP2_URF          -226516
      ROS_RPC_IES               -226520
      ROS_RPC_IES_ELECTRON      -226521
      ROS_RPC_IES_ION           -226522
      ROS_RPC_IES_URF           -226525
      ROS_RPC_IES_QUAD1         -226526
      ROS_RPC_IES_QUAD2         -226527
      ROS_RPC_IES_QUAD3         -226528
      ROS_RPC_IES_QUAD4         -226529
      ROS_RPC_ICA               -226530
      ROS_RPC_ICA_URF           -226535
      ROS_RPC_ICA_QUAD1         -226536
      ROS_RPC_ICA_QUAD2         -226537
      ROS_RPC_ICA_QUAD3         -226538
      ROS_RPC_ICA_QUAD4         -226539
      ROS_RPC_MAG_OB            -226541
      ROS_RPC_MAG_IB            -226542
      ROS_RPC_MAG_OB_URF        -226545
      ROS_RPC_MAG_IB_URF        -226546
      ROS_RPC_MIP               -226550
      ROS_RPC_MIP_R1            -226551
      ROS_RPC_MIP_T1            -226552
      ROS_RPC_MIP_T2            -226553
      ROS_RPC_MIP_R2            -226554
      ROS_RPC_MIP_URF           -226555
      ROS_RPC_BOOM1             -226560
      ROS_RPC_BOOM2             -226570

   Rosetta Lander Names/IDs:

      ROS_LANDER_LANDING_SITE   -226999 (synonyms: ROS_LANDER_LS,
                                         ROS_LANDER_TOPO)

      ROS_LANDER                -226800  PHILAE

   CIVA-P names/IDs:

      ROS_LANDER_CIVA_P_1       -226801
      ROS_LANDER_CIVA_P_2       -226802
      ROS_LANDER_CIVA_P_3       -226803
      ROS_LANDER_CIVA_P_4       -226804
      ROS_LANDER_CIVA_P_5       -226805
      ROS_LANDER_CIVA_P_6       -226806
      ROS_LANDER_CIVA_P_7       -226807

   DIM names/IDs:

      ROS_LANDER_DIM_X          -226830
      ROS_LANDER_DIM_Y          -226831
      ROS_LANDER_DIM_Z          -226832

   ROLIS names/IDs:

      ROS_LANDER_ROLIS_IFL      -226810
      ROS_LANDER_ROLIS_R        -226811
      ROS_LANDER_ROLIS_G        -226812
      ROS_LANDER_ROLIS_B        -226813
      ROS_LANDER_ROLIS_IR       -226814


Rosetta Target Body DSK Surface ID Codes -- Summary Section
========================================================================

   The following names and ID codes are assigned to the DSK surfaces
   for the Rosetta target bodies (the keywords implementing these
   definitions are located in the section "Rosetta DSK Surface ID Codes
   -- Definition Section" at the end of this file; they are supported
   in all SPICE toolkits with integrated DSK capabilities (version
   N0066 or later)):

          DSK Surface Name          ID    Body ID
      ===========================  =====  =======

   Comet 67P/Churyumov-Gerasimenko Surface name/IDs:

      ROS_CG_M004_NSPCESA_N_V1     11000  1000012

      ROS_CG_K006_OSPCLPS_N_V1     22000  1000012
      ROS_CG_K012_OSPCLPS_N_V1     22001  1000012
      ROS_CG_K024_OSPCLPS_N_V1     22002  1000012
      ROS_CG_K050_OSPCLPS_N_V1     22003  1000012
      ROS_CG_K096_OSPCLPS_N_V1     22004  1000012
      ROS_CG_K195_OSPCLPS_N_V1     22005  1000012
      ROS_CG_K399_OSPCLPS_N_V1     22006  1000012
      ROS_CG_K786_OSPCLPS_N_V1     22007  1000012

      ROS_CG_K006_OMSDLAM_N_V1     23000  1000012
      ROS_CG_K012_OMSDLAM_N_V1     23001  1000012
      ROS_CG_K024_OMSDLAM_N_V1     23002  1000012
      ROS_CG_K048_OMSDLAM_N_V1     23003  1000012
      ROS_CG_K098_OMSDLAM_N_V1     23004  1000012
      ROS_CG_K191_OMSDLAM_N_V1     23005  1000012
      ROS_CG_K391_OMSDLAM_N_V1     23006  1000012
      ROS_CG_K760_OMSDLAM_N_V1     23007  1000012
      ROS_CG_M001_OMSDLAM_N_V1     23008  1000012

   Asteroid 21 Lutetia Surface name/IDs:

      ROS_LU_K003_OSPCLAM_N_V1      1000  2000021
      ROS_LU_K006_OSPCLAM_N_V1      1001  2000021
      ROS_LU_K012_OSPCLAM_N_V1      1002  2000021
      ROS_LU_K025_OSPCLAM_N_V1      1003  2000021
      ROS_LU_K048_OSPCLAM_N_V1      1004  2000021
      ROS_LU_K098_OSPCLAM_N_V1      1005  2000021
      ROS_LU_K190_OSPCLAM_N_V1      1006  2000021
      ROS_LU_K240_OSPCLAM_N_V1      1007  2000021
      ROS_LU_K380_OSPCLAM_N_V1      1008  2000021
      ROS_LU_K780_OSPCLAM_N_V1      1009  2000021
      ROS_LU_M002_OSPCLAM_N_V1      1010  2000021
      ROS_LU_M003_OSPCLAM_N_V1      1011  2000021

   Asteroid 2867 Steins Surface name/IDs:

      ROS_ST_K020_OSPCLAM_N_V1      1000  2002867


Rosetta Frames
========================================================================

   The following Rosetta frames are defined in this kernel file:

           Name                  Relative to              Type       NAIF ID
      ======================  ======================  ============   =======

   Rosetta Target frames:
   ----------------------------------------------------
      67P/C-G_CK              J2000                   CK         -1000012000

      67P/C-G_FIXED           J2000                   PCK            1000012
      STEINS_FIXED            J2000                   PCK            2002867
      LUTETIA_FIXED           J2000                   PCK            2000021

      67P/C-G_CSO             J2000                   DYNAMIC        -226912
      45P/H-M-P_CSO           J2000                   DYNAMIC        -226945
      2867/STEINS_CSO         J2000                   DYNAMIC        -226967
      21/LUTETIA_CSO          J2000                   DYNAMIC        -226921

      67P/C-G_CSEQ            J2000                   DYNAMIC        -226910
      21/LUTETIA_CSEQ         J2000                   DYNAMIC        -226920


   Rosetta Orbiter-Centered Dynamic Frames:
   ----------------------------------------------------
      ROS_AUX_NADIR           J2000                   DYNAMIC        -226918
      ROS_RCO                 J2000                   DYNAMIC        -226919

   Rosetta Spacecraft and Spacecraft Structures frames:
   ----------------------------------------------------
      ROS_SPACECRAFT          J2000                   CK             -226000
      ROS_SA+Y_ZERO           ROS_SPACECRAFT          FIXED          -226010
      ROS_SA+Y                ROS_SA+Y_ZERO           CK             -226015
      ROS_SA-Y_ZERO           ROS_SPACECRAFT          FIXED          -226020
      ROS_SA-Y                ROS_SA-Y_ZERO           CK             -226025
      ROS_MGA-S               ROS_SPACECRAFT          FIXED          -226030
      ROS_MGA-X               ROS_SPACECRAFT          FIXED          -226040
      ROS_LGA-1               ROS_SPACECRAFT          FIXED          -226050
      ROS_LGA-2               ROS_SPACECRAFT          FIXED          -226060
      ROS_HGA_EL              ROS_SPACECRAFT          CK             -226071
      ROS_HGA_AZ              ROS_HGA_EL              CK             -226072
      ROS_HGA                 ROS_HGA_AZ              FIXED          -226075

   Star Tracker frames:
   --------------------
      ROS_STR-A               ROS_SPACECRAFT          FIXED          -226080
      ROS_STR-B               ROS_SPACECRAFT          FIXED          -226090

   OSIRIS frames:
   --------------
      ROS_OSIRIS_NAC          ROS_SPACECRAFT          FIXED          -226111
      ROS_OSIRIS_NAC_URF      ROS_SPACECRAFT          FIXED          -226116
      ROS_OSIRIS_WAC          ROS_SPACECRAFT          FIXED          -226112
      ROS_OSIRIS_WAC_URF      ROS_SPACECRAFT          FIXED          -226117

   ALICE frames:
   --------------
      ROS_ALICE               ROS_SPACECRAFT          FIXED          -226120
      ROS_ALICE_URF           ROS_SPACECRAFT          FIXED          -226125

   VIRTIS frames:
   --------------
      ROS_VIRTIS-M            ROS_SPACECRAFT          FIXED          -226210
      ROS_VIRTIS-M_SCAN       ROS_VIRTIS-M            CK             -226215
      ROS_VIRTIS-M_VIS        ROS_VIRTIS-M_SCAN       FIXED          -226211
      ROS_VIRTIS-M_IR         ROS_VIRTIS-M_SCAN       FIXED          -226213
      ROS_VIRTIS-M_VIS_ZERO   ROS_VIRTIS-M            FIXED          -226212
      ROS_VIRTIS-M_IR_ZERO    ROS_VIRTIS_M            FIXED          -226214
      ROS_VIRTIS-H            ROS_SPACECRAFT          FIXED          -226220

   MIRO frames:
   --------------
      ROS_MIRO                ROS_SPACECRAFT          FIXED          -226130
      ROS_MIRO_MM             ROS_MIRO                FIXED          -226131
      ROS_MIRO_SUBMM          ROS_MIRO                FIXED          -226132
      ROS_MIRO_URF            ROS_SPACECRAFT          FIXED          -226135

   ROSINA frames:
   --------------
      ROS_ROSINA_DFMS         ROS_SPACECRAFT          FIXED          -226310
      ROS_ROSINA_DFMS_URF     ROS_SPACECRAFT          FIXED          -226319
      ROS_ROSINA_RTOF         ROS_SPACECRAFT          FIXED          -226320
      ROS_ROSINA_RTOF_URF     ROS_SPACECRAFT          FIXED          -226329
      ROS_ROSINA_COPS         ROS_SPACECRAFT          FIXED          -226330
      ROS_ROSINA_COPS_URF     ROS_SPACECRAFT          FIXED          -226339

   COSIMA frames:
   --------------
      ROS_COSIMA              ROS_SPACECRAFT          FIXED          -226140
      ROS_COSIMA_URF          ROS_SPACECRAFT          FIXED          -226145

   MIDAS frames:
   -------------
      ROS_MIDAS               ROS_SPACECRAFT          FIXED          -226150
      ROS_MIDAS_URF           ROS_SPACECRAFT          FIXED          -226155

   CONSERT frames:
   ---------------
      ROS_CONSERT             ROS_SPACECRAFT          FIXED          -226160
      ROS_CONSERT_URF         ROS_SPACECRAFT          FIXED          -226165

   NAVCAM frames:
   --------------
      ROS_NAVCAM-A            ROS_SPACECRAFT          FIXED          -226170
      ROS_NAVCAM-A_URF        ROS_SPACECRAFT          FIXED          -226175
      ROS_NAVCAM-B            ROS_SPACECRAFT          FIXED          -226180
      ROS_NAVCAM-B_URF        ROS_SPACECRAFT          FIXED          -226185

   GIADA frames:
   -------------
      ROS_GIADA_GDS           ROS_SPACECRAFT          FIXED          -226410
      ROS_GIADA_IS            ROS_SPACECRAFT          FIXED          -226420
      ROS_GIADA_MBS1          ROS_SPACECRAFT          FIXED          -226431
      ROS_GIADA_MBS2          ROS_SPACECRAFT          FIXED          -226432
      ROS_GIADA_MBS3          ROS_SPACECRAFT          FIXED          -226433
      ROS_GIADA_MBS4          ROS_SPACECRAFT          FIXED          -226434
      ROS_GIADA_MBS5          ROS_SPACECRAFT          FIXED          -226435
      ROS_GIADA_URF           ROS_SPACECRAFT          FIXED          -226440

   RPC frames:
   -----------
      ROS_RPC_IES             ROS_SPACECRAFT          FIXED          -226520
      ROS_RPC_IES_URF         ROS_SPACECRAFT          FIXED          -226525
      ROS_RPC_ICA             ROS_SPACECRAFT          FIXED          -226530
      ROS_RPC_ICA_URF         ROS_SPACECRAFT          FIXED          -226535
      ROS_RPC_BOOM1           ROS_SPACECRAFT          FIXED          -226560
      ROS_RPC_MIP             ROS_RPC_BOOM1           FIXED          -226550
      ROS_RPC_LAP1            ROS_RPC_BOOM1           FIXED          -226511
      ROS_RPC_BOOM2           ROS_SPACECRAFT          FIXED          -226570
      ROS_RPC_MAG_OB          ROS_RPC_BOOM2           FIXED          -226541
      ROS_RPC_MAG_IB          ROS_RPC_BOOM2           FIXED          -226542
      ROS_RPC_LAP2            ROS_RPC_BOOM2           FIXED          -226512

   Rosetta Lander Frames:
   ----------------------
      ROS_LANDER_TOPO         67P/C-G_FIXED           FIXED          -226999
      ROS_LANDER              ROS_LANDER_TOPO         CK             -226800

   CIVA-P frames:
   --------------
      ROS_LANDER_CIVA_P_1     ROS_LANDER              FIXED          -226801
      ROS_LANDER_CIVA_P_2     ROS_LANDER              FIXED          -226802
      ROS_LANDER_CIVA_P_3     ROS_LANDER              FIXED          -226803
      ROS_LANDER_CIVA_P_4     ROS_LANDER              FIXED          -226804
      ROS_LANDER_CIVA_P_5     ROS_LANDER              FIXED          -226805
      ROS_LANDER_CIVA_P_6     ROS_LANDER              FIXED          -226806
      ROS_LANDER_CIVA_P_7     ROS_LANDER              FIXED          -226807

   SESAME DIM frames:
   --------------
      ROS_LANDER_DIM_X        ROS_LANDER              FIXED          -226830
      ROS_LANDER_DIM_Y        ROS_LANDER              FIXED          -226831
      ROS_LANDER_DIM_Z        ROS_LANDER              FIXED          -226832

   ROLIS frames:
   --------------
      ROS_LANDER_ROLIS        ROS_LANDER              FIXED          -226815


Rosetta Target, Spacecraft, and Spacecraft Structures Frame Tree
========================================================================

   The diagram below shows the frame hierarchy for the Rosetta spacecraft
   and its structure frame (not including science instrument frames.)

          "45P/H-M-P_CSO"
          ---------------
           ^
           |<-dyn
           |
           | "2867/STEINS_CSO"
           | -----------------
           |  ^
           |  |<-dyn
           |  |
           |  | "21/LUTETIA_CSEQ"                       "IAU_EARTH"
           |  | -----------------                       -----------
           |  |  ^                                               ^
           |  |  |<-dyn                                     pck->|
           |  |  |                                               |
           |  |  | "21/LUTETIA_CSO"                     "ITRF93" |
           |  |  | ----------------                     -------- |
           |  |  |  ^                                         ^  |
           |  |  |  |<-dyn                               pck->|  |
           |  |  |  |                                         |  |
           |  |  |  | "67P/C-G_CSEQ"                "ROS_RCO" |  |
           |  |  |  | --------------                --------- |  |
           |  |  |  |  ^                                   ^  |  |
           |  |  |  |  |<-dyn                         dyn->|  |  |
           |  |  |  |  |                                   |  |  |
           |  |  |  |  | "67P/C-G_CSO"     "ROS_AUX_NADIR" |  |  |
           |  |  |  |  | -------------     --------------- |  |  |
           |  |  |  |  |  ^                             ^  |  |  |
           |  |  |  |  |  |<-dyn                   dyn->|  |  |  |
           |  |  |  |  |  |                             |  |  |  |
           |  |  |  |  |  |                             |  |  |  |
           |  |  |  |  |  |    "J2000" INERTIAL         |  |  |  |
           +-----------------------------------------------------+
           |                 |        |        |                 |
           |<-pck        ck->|        |        |<-pck       pck->|
           |                 |        |        |                 |
           V                 V        |        V                 V
       "67P/C-G_FIXED"  "67P/C-G_CK"  | "LUTETIA_FIXED"   "STEINS_FIXED"
         COMET BFXD      COMET BFXD   |  ASTEROID BFXD    ASTEROID BFXD
       ---------------  ------------  | --------------    --------------
                  .        .          |
           fixed->.        .<-fixed   |
                  .        .          |
                  V        V          |
              "ROS_LANDER_TOPO"       |
              -----------------       |
                      |               |
                      |<-ck           |
                      |               |
                      V               |
                "ROS_LANDER"          |
                ------------          |
                      .               |
                      .               |
                      V               |
         Individual lander instrument |
           frame trees are provided   |
             in the other sections    |
                 of this file         |
                                      |
                                      |
                                      |
       "ROS_HGA"                      |
       ---------                      |
           ^                          |
           |<-fixed                   |
           |                          |
       "ROS_HGA_AZ"                   |                   ROS_STR-B
       ------------                   |                   --------- 
           ^                          |                          ^
           |<-ck                      |                   fixed->|
           |                          |                          |
       "ROS_HGA_EL"                   |               ROS_STR-A  |
       ------------                   |               ---------  |
           ^                          |                    ^     |
           |<-ck                      |<-ck         fixed->|     |
           |                          |                    |     |
           |                          V                    |     |
           |                   "ROS_SPACECRAFT"            |     |     
           +-----------------------------------------------------+
           |             |            .        |     |     |     |
           |<-fixed      |<-fixed     . fixed->|     |     |     |<-fixed
           |             |            .        |     |     |     |
           V             V            .        V     |     |     V
    "ROS_SA+Y_ZERO"  "ROS_SA-Y_ZERO"  .  "ROS_LGA-1" |     | "ROS_LGA-2"
    ---------------  ---------------  .  ----------- |     | -----------
           |             |            .              |     |
           |<-ck         |<-ck        .       fixed->|     |<-fixed
           |             |            .              |     |
           V             V            .              V     V
       "ROS_SA+Y"    "ROS_SA-Y"       .     "ROS_MGA-S"   "ROS_MGA-X"
       -----------   ----------       .     -----------   -----------
                                      .
                                      .
                                      V
                Individual instrument frame trees are provided
                      in the other sections of this file



Rosetta Target Frames
========================================================================

   This section of the file contains the body-fixed and dynamic
   (body-Centered Solar Orbital (CSO) and  body-Centered Solar
   EQuatorial (CSEQ)) frame definitions for the primary, secondary and
   incidental targets of the Rosetta mission -- comet
   67P/Churyumov-Gerasimenko, asteroids 2867 Steins and 21 Lutetia, and
   comet 45P/Honda-Mrkos-Pajdusakowa.


Body-Fixed Frames

   Three PCK-based body-fixed frames -- 67P/C-G_FIXED, STEINS_FIXED,
   and LUTETIA_FIXED -- are defined for the mission target bodies
   67P/Churyumov-Gerasimenko, asteroids 2867 Steins and 21 Lutetia.
   The orientation of these frames is computed by evaluating
   corresponding rotation constants provided in the PCK file(s).

   Because the orientation of 67P/Churyumov-Gerasimenko cannot be
   represented over long periods of time using the standard IAU body
   rotation formulation, an additional body-fixed CK-based frame,
   67P/C-G_CK, is defined for the comet. The orientation of this frame
   is computed using data provided in CK files for ID -1000012000,
   tagged encoded ticks of the artificial SCLK with ID -1000012. The
   SCLK data supporting conversions between these ticks and Ephemeris
   Time are provided next to the 67P/C-G_CK frame definition below.
   The definition of this frame and accompanying SCLK parameters were
   originally provided in the FK file ROS_CHURYUMOV_V01.TF.

   The 67P/C-G_CK is the preferred body-fixed frame for the comet
   in all cases when the comet orientation CKs are available.

   All four body fixed frames have their axes and center aligned
   according to the standard body-fixed frame formation rules:

      -  +Z axis is toward the North pole;

      -  +X axis is toward the prime meridian;

      -  +Y axis completes the right handed frame;

      -  the origin of this frame is at the center of the body.

   The keywords below define the three PCK-based frames and the
   CK-based frame and accompanying SCLK parameters.

   \begindata

      FRAME_67P/C-G_FIXED              =  1000012
      FRAME_1000012_NAME               = '67P/C-G_FIXED'
      FRAME_1000012_CLASS              =  2
      FRAME_1000012_CLASS_ID           =  1000012
      FRAME_1000012_CENTER             =  1000012
      OBJECT_1000012_FRAME             = '67P/C-G_FIXED'

      FRAME_STEINS_FIXED               =  2002867
      FRAME_2002867_NAME               = 'STEINS_FIXED'
      FRAME_2002867_CLASS              =  2
      FRAME_2002867_CLASS_ID           =  2002867
      FRAME_2002867_CENTER             =  2002867
      OBJECT_2002867_FRAME             = 'STEINS_FIXED'

      FRAME_LUTETIA_FIXED              =  2000021
      FRAME_2000021_NAME               = 'LUTETIA_FIXED'
      FRAME_2000021_CLASS              =  2
      FRAME_2000021_CLASS_ID           =  2000021
      FRAME_2000021_CENTER             =  2000021
      OBJECT_2000021_FRAME             = 'LUTETIA_FIXED'

      FRAME_67P/C-G_CK                 = -1000012000
      FRAME_-1000012000_NAME           = '67P/C-G_CK'
      FRAME_-1000012000_CLASS          =  3
      FRAME_-1000012000_CLASS_ID       = -1000012000
      FRAME_-1000012000_CENTER         =  1000012
      CK_-1000012000_SCLK              = -1000012
      CK_-1000012000_SPK               =  1000012

      SCLK_KERNEL_ID                   = ( @2011-01-05/12:01:58 )

      SCLK_DATA_TYPE_1000012           = ( 1 )
      SCLK01_TIME_SYSTEM_1000012       = ( 2 )
      SCLK01_N_FIELDS_1000012          = ( 2 )
      SCLK01_MODULI_1000012            = ( 4294967296 65536 )
      SCLK01_OFFSETS_1000012           = ( 0 0 )
      SCLK01_OUTPUT_DELIM_1000012      = ( 1 )

      SCLK_PARTITION_START_1000012     = ( 2.4123675052450E+12 )

      SCLK_PARTITION_END_1000012       = ( 2.8147497671065E+14 )

      SCLK01_COEFFICIENTS_1000012      = (

        0.0000000000000E+00     1.3146108418400E+08     1.0000000000000E+00 )

   \begintext



Body-Centered Solar Orbital (CSO) Frames

   The body-Centered Solar Orbital (CSO) frames for the Rosetta primary
   target comet 67P/Churyumov-Gerasimenko, incidental target comet
   45P/Honda-Mrkos-Pajdusakowa (Rosetta passed through its ion tail in
   July 2006), and secondary targets asteroids 2867/STEINS and
   21/LUTETIA are named '67P/C-G_CSO', '45P/H-M-P_CSO',
   '2867/STEINS_CSO', and '21/LUTETIA_CSO'. These frames are defined as
   a two-vector style dynamic frames as follows:

      -  The position of the sun relative to the body is the primary
         vector: the X axis points from the body to the sun.

      -  The inertially referenced velocity of the sun relative to the
         body is the secondary vector: the Y axis is the component of
         this velocity vector orthogonal to the X axis.

      -  The Z axis is X cross Y, completing the right-handed reference
         frame.

      -  All vectors are geometric: no aberration corrections are used.

   The '67P/C-G_CSO', '45P/H-M-P_CSO', '2867/STEINS_CSO', and
   '21/LUTETIA_CSO' definitions are implemented by the keywords below.

   \begindata

      FRAME_67P/C-G_CSO                =  -226912
      FRAME_-226912_NAME               = '67P/C-G_CSO'
      FRAME_-226912_CLASS              =  5
      FRAME_-226912_CLASS_ID           =  -226912
      FRAME_-226912_CENTER             =  1000012
      FRAME_-226912_RELATIVE           = 'J2000'
      FRAME_-226912_DEF_STYLE          = 'PARAMETERIZED'
      FRAME_-226912_FAMILY             = 'TWO-VECTOR'
      FRAME_-226912_PRI_AXIS           = 'X'
      FRAME_-226912_PRI_VECTOR_DEF     = 'OBSERVER_TARGET_POSITION'
      FRAME_-226912_PRI_OBSERVER       = 'CHURYUMOV-GERASIMENKO'
      FRAME_-226912_PRI_TARGET         = 'SUN'
      FRAME_-226912_PRI_ABCORR         = 'NONE'
      FRAME_-226912_SEC_AXIS           = 'Y'
      FRAME_-226912_SEC_VECTOR_DEF     = 'OBSERVER_TARGET_VELOCITY'
      FRAME_-226912_SEC_OBSERVER       = 'CHURYUMOV-GERASIMENKO'
      FRAME_-226912_SEC_TARGET         = 'SUN'
      FRAME_-226912_SEC_ABCORR         = 'NONE'
      FRAME_-226912_SEC_FRAME          = 'J2000'

      FRAME_45P/H-M-P_CSO              =  -226945
      FRAME_-226945_NAME               = '45P/H-M-P_CSO'
      FRAME_-226945_CLASS              =  5
      FRAME_-226945_CLASS_ID           =  -226945
      FRAME_-226945_CENTER             =  1000045
      FRAME_-226945_RELATIVE           = 'J2000'
      FRAME_-226945_DEF_STYLE          = 'PARAMETERIZED'
      FRAME_-226945_FAMILY             = 'TWO-VECTOR'
      FRAME_-226945_PRI_AXIS           = 'X'
      FRAME_-226945_PRI_VECTOR_DEF     = 'OBSERVER_TARGET_POSITION'
      FRAME_-226945_PRI_OBSERVER       = 'HONDA-MRKOS-PAJDUSAKOVA'
      FRAME_-226945_PRI_TARGET         = 'SUN'
      FRAME_-226945_PRI_ABCORR         = 'NONE'
      FRAME_-226945_SEC_AXIS           = 'Y'
      FRAME_-226945_SEC_VECTOR_DEF     = 'OBSERVER_TARGET_VELOCITY'
      FRAME_-226945_SEC_OBSERVER       = 'HONDA-MRKOS-PAJDUSAKOVA'
      FRAME_-226945_SEC_TARGET         = 'SUN'
      FRAME_-226945_SEC_ABCORR         = 'NONE'
      FRAME_-226945_SEC_FRAME          = 'J2000'

      FRAME_2867/STEINS_CSO            =  -226967
      FRAME_-226967_NAME               = '2867/STEINS_CSO'
      FRAME_-226967_CLASS              =  5
      FRAME_-226967_CLASS_ID           =  -226967
      FRAME_-226967_CENTER             =  2002867
      FRAME_-226967_RELATIVE           = 'J2000'
      FRAME_-226967_DEF_STYLE          = 'PARAMETERIZED'
      FRAME_-226967_FAMILY             = 'TWO-VECTOR'
      FRAME_-226967_PRI_AXIS           = 'X'
      FRAME_-226967_PRI_VECTOR_DEF     = 'OBSERVER_TARGET_POSITION'
      FRAME_-226967_PRI_OBSERVER       = 'STEINS'
      FRAME_-226967_PRI_TARGET         = 'SUN'
      FRAME_-226967_PRI_ABCORR         = 'NONE'
      FRAME_-226967_SEC_AXIS           = 'Y'
      FRAME_-226967_SEC_VECTOR_DEF     = 'OBSERVER_TARGET_VELOCITY'
      FRAME_-226967_SEC_OBSERVER       = 'STEINS'
      FRAME_-226967_SEC_TARGET         = 'SUN'
      FRAME_-226967_SEC_ABCORR         = 'NONE'
      FRAME_-226967_SEC_FRAME          = 'J2000'

      FRAME_21/LUTETIA_CSO             =  -226921
      FRAME_-226921_NAME               = '21/LUTETIA_CSO'
      FRAME_-226921_CLASS              =  5
      FRAME_-226921_CLASS_ID           =  -226921
      FRAME_-226921_CENTER             =  2000021
      FRAME_-226921_RELATIVE           = 'J2000'
      FRAME_-226921_DEF_STYLE          = 'PARAMETERIZED'
      FRAME_-226921_FAMILY             = 'TWO-VECTOR'
      FRAME_-226921_PRI_AXIS           = 'X'
      FRAME_-226921_PRI_VECTOR_DEF     = 'OBSERVER_TARGET_POSITION'
      FRAME_-226921_PRI_OBSERVER       = 'LUTETIA'
      FRAME_-226921_PRI_TARGET         = 'SUN'
      FRAME_-226921_PRI_ABCORR         = 'NONE'
      FRAME_-226921_SEC_AXIS           = 'Y'
      FRAME_-226921_SEC_VECTOR_DEF     = 'OBSERVER_TARGET_VELOCITY'
      FRAME_-226921_SEC_OBSERVER       = 'LUTETIA'
      FRAME_-226921_SEC_TARGET         = 'SUN'
      FRAME_-226921_SEC_ABCORR         = 'NONE'
      FRAME_-226921_SEC_FRAME          = 'J2000'

   \begintext


Body-Centered Solar EQuatorial (CSEQ) Frames

   The body-Centered Solar EQuatorial (CSEQ) frames for the Rosetta
   primary target comet 67P/Churyumov-Gerasimenko and secondary target
   asteroid 21/LUTETIA are named '67P/C-G_CSEQ' and '21/LUTETIA_CSEQ'.
   These frames are defined as a two-vector style dynamic frames as
   follows:

      -  +X axis is the position of the Sun relative to the body; it's
         the primary vector and points from the body to the Sun;

      -  +Z axis is the component of the Sun's north pole of date
         orthogonal to the +X axis;

      -  +Y axis completes the right-handed reference frame;

      -  the origin of this frame is the body's center of mass.

   All the vectors are geometric: no aberration corrections are used.

   The '67P/C-G_CSEQ' and '21/LUTETIA_CSEQ' definitions are implemented
   by the keywords below.

   \begindata

      FRAME_67P/C-G_CSEQ               = -226910
      FRAME_-226910_NAME               = '67P/C-G_CSEQ'
      FRAME_-226910_CLASS              =  5
      FRAME_-226910_CLASS_ID           =  -226910
      FRAME_-226910_CENTER             =  1000012
      FRAME_-226910_RELATIVE           = 'J2000'
      FRAME_-226910_DEF_STYLE          = 'PARAMETERIZED'
      FRAME_-226910_FAMILY             = 'TWO-VECTOR'
      FRAME_-226910_PRI_AXIS           = 'X'
      FRAME_-226910_PRI_VECTOR_DEF     = 'OBSERVER_TARGET_POSITION'
      FRAME_-226910_PRI_OBSERVER       = '67P/C-G'
      FRAME_-226910_PRI_TARGET         = 'SUN'
      FRAME_-226910_PRI_ABCORR         = 'NONE'
      FRAME_-226910_SEC_AXIS           = 'Z'
      FRAME_-226910_SEC_VECTOR_DEF     = 'CONSTANT'
      FRAME_-226910_SEC_FRAME          = 'IAU_SUN'
      FRAME_-226910_SEC_SPEC           = 'RECTANGULAR'
      FRAME_-226910_SEC_VECTOR         = ( 0, 0, 1 )

      FRAME_21/LUTETIA_CSEQ            = -226920
      FRAME_-226920_NAME               = '21/LUTETIA_CSEQ'
      FRAME_-226920_CLASS              =  5
      FRAME_-226920_CLASS_ID           =  -226920
      FRAME_-226920_CENTER             =  2000021
      FRAME_-226920_RELATIVE           = 'J2000'
      FRAME_-226920_DEF_STYLE          = 'PARAMETERIZED'
      FRAME_-226920_FAMILY             = 'TWO-VECTOR'
      FRAME_-226920_PRI_AXIS           = 'X'
      FRAME_-226920_PRI_VECTOR_DEF     = 'OBSERVER_TARGET_POSITION'
      FRAME_-226920_PRI_OBSERVER       = 'LUTETIA'
      FRAME_-226920_PRI_TARGET         = 'SUN'
      FRAME_-226920_PRI_ABCORR         = 'NONE'
      FRAME_-226920_SEC_AXIS           = 'Z'
      FRAME_-226920_SEC_VECTOR_DEF     = 'CONSTANT'
      FRAME_-226920_SEC_FRAME          = 'IAU_SUN'
      FRAME_-226920_SEC_SPEC           = 'RECTANGULAR'
      FRAME_-226920_SEC_VECTOR         = ( 0, 0, 1 )

   \begintext



Rosetta Orbiter-Centered Dynamic Frames
========================================================================

   This section of the file contains the definitions of the dynamic frames
   centered at the Rosetta orbiter.


Rosetta Auxiliary Nadir Frame

   The Rosetta auxiliary nadir frame, ROS_AUX_NADIR, needed for ROVIS
   pointing computations, is defined as a two-vector style dynamic
   frame as follows:

      -  The position of 67P/C-G relative to the spacecraft is the
         primary vector: the Z axis points from the spacecraft to
         67P/C-G.

      -  The apparent position of the Sun as seen from the spacecraft
         is the secondary vector: the X axis is the component of this
         position vector orthogonal to the Z axis.

      -  The Y axis is Z cross X, completing the right-handed frame.

   The keywords below implement this definition, which was originally
   provided in the FK file ROS_CGS_AUX_V01.TF using the frame ID
   -226910.

   \begindata

      FRAME_ROS_AUX_NADIR          = -226918
      FRAME_-226918_NAME           = 'ROS_AUX_NADIR'
      FRAME_-226918_CLASS          =  5
      FRAME_-226918_CLASS_ID       =  -226918
      FRAME_-226918_CENTER         = 'ROSETTA'
      FRAME_-226918_RELATIVE       = 'J2000'
      FRAME_-226918_DEF_STYLE      = 'PARAMETERIZED'
      FRAME_-226918_FAMILY         = 'TWO-VECTOR'
      FRAME_-226918_ANGLE_SEP_TOL  = 0.000001
      FRAME_-226918_PRI_AXIS       = 'Z'
      FRAME_-226918_PRI_VECTOR_DEF = 'OBSERVER_TARGET_POSITION'
      FRAME_-226918_PRI_OBSERVER   = 'ROSETTA'
      FRAME_-226918_PRI_TARGET     = 'CHURYUMOV-GERASIMENKO'
      FRAME_-226918_PRI_ABCORR     = 'NONE'
      FRAME_-226918_SEC_AXIS       = 'X'
      FRAME_-226918_SEC_VECTOR_DEF = 'OBSERVER_TARGET_POSITION'
      FRAME_-226918_SEC_OBSERVER   = 'ROSETTA'
      FRAME_-226918_SEC_TARGET     = 'SUN'
      FRAME_-226918_SEC_ABCORR     = 'LT+S'

   \begintext


Rosetta Body-Centered 67p/C-G Orbital Frame

   The body-Centered 67p/C-G Orbital (RCO) frame for the ROSETTA
   spacecraft, ROS_RCO, is defined as a two-vector style dynamic
   frame as follows:

      -  The position of 67P/C-G relative to the spacecraft is the
         primary vector: the X axis points from the spacecraft to
         67P/C-G.

      -  The inertially referenced velocity of 67P/C-G relative to the
         spacecraft is the secondary vector: the Y axis is the
         component of this velocity vector orthogonal to the X axis.

      -  The Z axis is X cross Y, completing the right-handed reference
         frame.

      -  All vectors are geometric: no aberration corrections are used.

   The keywords below implement this definition, which was originally
   provided in the FK file ROS_RCO.TF.

   \begindata

      FRAME_ROS_RCO                    =  -226919
      FRAME_-226919_NAME               = 'ROS_RCO'
      FRAME_-226919_CLASS              =  5
      FRAME_-226919_CLASS_ID           =  -226919
      FRAME_-226919_CENTER             =  -226
      FRAME_-226919_RELATIVE           = 'J2000'
      FRAME_-226919_DEF_STYLE          = 'PARAMETERIZED'
      FRAME_-226919_FAMILY             = 'TWO-VECTOR'
      FRAME_-226919_PRI_AXIS           = 'X'
      FRAME_-226919_PRI_VECTOR_DEF     = 'OBSERVER_TARGET_POSITION'
      FRAME_-226919_PRI_OBSERVER       = 'ROSETTA'
      FRAME_-226919_PRI_TARGET         = 'CHURYUMOV-GERASIMENKO'
      FRAME_-226919_PRI_ABCORR         = 'NONE'
      FRAME_-226919_SEC_AXIS           = 'Y'
      FRAME_-226919_SEC_VECTOR_DEF     = 'OBSERVER_TARGET_VELOCITY'
      FRAME_-226919_SEC_OBSERVER       = 'ROSETTA'
      FRAME_-226919_SEC_TARGET         = 'CHURYUMOV-GERASIMENKO'
      FRAME_-226919_SEC_ABCORR         = 'NONE'
      FRAME_-226919_SEC_FRAME          = 'J2000'

   \begintext


Rosetta Spacecraft and Spacecraft Structures Frames
========================================================================

   This section of the file contains the definitions of the spacecraft
   and spacecraft structures frames.


Rosetta Spacecraft Frame
--------------------------------------

   According to [5] the Rosetta spacecraft frame is defined as follows:

      -  +Z axis is perpendicular to the launch vehicle interface plane
         and points toward the payload side;

      -  +X axis is perpendicular to the HGA mounting plane and points
         toward HGA;

      -  +Y axis completes the frame is right-handed.

      -  the origin of this frame is the launch vehicle interface point.

   These diagrams illustrate the ROS_SPACECRAFT frame:


   +X s/c side (HGA side) view:
   ----------------------------
                                    ^
                                    | toward comet
                                    |

                               Science Deck
                             ._____________.
   .__  _______________.     |             |     .______________  ___.
   |  \ \               \    |             |    /               \ \  |
   |  / /                \   |  +Zsc       |   /                / /  |
   |  \ \                 `. |      ^      | .'                 \ \  |
   |  / /                 | o|      |      |o |                 / /  |
   |  \ \                 .' |      |      | `.                 \ \  |
   |  / /                /   |      |      |   \                / /  |
   .__\ \_______________/    |  +Xsc|      |    \_______________\ \__.
     -Y Solar Array          .______o-------> +Ysc   +Y Solar Array
                                 ._____.
                               .'       `.
                              /           \
                             .   `.   .'   .          +Xsc is out of
                             |     `o'     |             the page
                             .      |      .
                              \     |     /
                               `.       .'
                            HGA  ` --- '


   +Z s/c side (science deck side) view:
   -------------------------------------
                                  _____
                                 /     \  Lander
                                |       |
                             ._____________.
                             |             |
                             |             |
                             |  +Zsc       | +Ysc
   o==/ /==================o |      o------->o==================/ /==o
     -Y Solar Array          |      |      |        +Y Solar Array
                             |      |      |
                             .______|______.
                               `.   |   .'
                                 .--V +Xsc
                          HGA  .'       `.
                              /___________\
                                  `.|.'                 +Zsc is out
                                                       of the page


   Since the orientation of the ROS_SPACECRAFT frame is computed
   on-board, sent down in telemetry, and stored in the s/c CK files, it
   is defined as a CK-based frame.

   \begindata

      FRAME_ROS_SPACECRAFT             = -226000
      FRAME_-226000_NAME               = 'ROS_SPACECRAFT'
      FRAME_-226000_CLASS              =  3
      FRAME_-226000_CLASS_ID           = -226000
      FRAME_-226000_CENTER             = -226
      CK_-226000_SCLK                  = -226
      CK_-226000_SPK                   = -226

   \begintext


Rosetta Solar Array Frames
--------------------------------------

   Each of the solar array frame chains includes two frames. The first
   frame, named ROS_SA+Y_ZERO for +Y solar array and ROS_SA-Y_ZERO for
   -Y solar array, is a fixed offset frame that gives the array
   orientation in zero gimbal position. The second frame, named
   ROS_SA+Y for +Y solar array and ROS_SA-Y for -Y solar array, is a
   CK-based frame that incorporates rotation about the array's gimbal
   axis from zero position to the actual position.

   The array frames, ROS_SA+Y and ROS_SA-Y, are defined as follows:

      -  +Y axis is parallel to the longest side of the array and array
         rotation axis, and is positively oriented from the end of the
         wing toward the gimbal;

      -  +Z axis is normal to the solar array plane, the solar cells on
         the +Z side;

      -  +X axis is defined such that (X,Y,Z) is right handed;

      -  the origin of the frame is located at the geometric center of
         center the gimbal.

   In zero gimbal position the ROS_SA+Y frame is co-aligned with the
   ROS_SA+Y_ZERO frame and  the ROS_SA-Y frame is co-aligned with the
   ROS_SA-Y_ZERO frame. In non-zero position each of the array frames
   is rotated from its corresponding "zero" frame positive CCW about +Y
   axis, with this rotation captured in CK files.

   This diagram illustrates the solar array frames for both arrays in
   zero position:


   +X s/c side (HGA side) view:
   ----------------------------
                                    ^
                                    | toward comet
                                    |

                               Science Deck  +Xsa+y0
                             ._____________.^+Xsa+y
   .__  _______________.     |             ||    .______________  ___.
   |  \ \               \    |             ||   /               \ \  |
   |  / /                \   |  +Zsc       ||  /                / /  |
   |  \ \                 `. |      ^      ||.+Zsa+y0           \ \  |
   |  / /           +Zsa-y0 o-----> | <-----o  Zsa+y            / /  |
   |  \ \           +Zsa-y.'|+Ysa-y0|+Ysa+y0 `.                 \ \  |
   |  / /                /  ||+Ysa-y|+Ysa+y|   \                / /  |
   .__\ \_______________/   ||      |      |    \_______________\ \__.
     -Y Solar Array         |.______o-------> +Ysc   +Y Solar Array
                            v  +Xsc o__.
                     +Xsa-y0   .'       `.
                     +Xsa-y   /           \
                             .   `.   .'   .      +Zsa+y0, +Zsa+y, +Zsa-y0,
                             |     `o'     |      and +Zsa-y are out of
                             .      |      .             the page
                              \     |     /
                               `.       .'         Active solar cell is
                            HGA  ` --- '             facing the viewer


   As seen on the diagram the ROS_SA-Y_ZERO is rotated from the
   spacecraft frame by +90 degrees about +Y while the ROS_SA+Y_ZERO is
   rotated from the spacecraft frame first by 180 degrees about +X and
   then by +90 degrees about +Y.

   These sets of keywords define the solar array frames as CK frames:

   \begindata

      FRAME_ROS_SA+Y_ZERO              =  -226010
      FRAME_-226010_NAME               = 'ROS_SA+Y_ZERO'
      FRAME_-226010_CLASS              =  4
      FRAME_-226010_CLASS_ID           =  -226010
      FRAME_-226010_CENTER             =  -226
      TKFRAME_-226010_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226010_SPEC             = 'ANGLES'
      TKFRAME_-226010_UNITS            = 'DEGREES'
      TKFRAME_-226010_ANGLES           = ( 180.000, 90.000,   0.000 )
      TKFRAME_-226010_AXES             = (   3,      2,       3     )

      FRAME_ROS_SA+Y                   = -226015
      FRAME_-226015_NAME               = 'ROS_SA+Y'
      FRAME_-226015_CLASS              =  3
      FRAME_-226015_CLASS_ID           = -226015
      FRAME_-226015_CENTER             = -226
      CK_-226015_SCLK                  = -226
      CK_-226015_SPK                   = -226

      FRAME_ROS_SA-Y_ZERO              =  -226020
      FRAME_-226020_NAME               = 'ROS_SA-Y_ZERO'
      FRAME_-226020_CLASS              =  4
      FRAME_-226020_CLASS_ID           =  -226020
      FRAME_-226020_CENTER             =  -226
      TKFRAME_-226020_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226020_SPEC             = 'ANGLES'
      TKFRAME_-226020_UNITS            = 'DEGREES'
      TKFRAME_-226020_ANGLES           = (   0.000, -90.000,   0.000 )
      TKFRAME_-226020_AXES             = (   3,       2,       3     )

      FRAME_ROS_SA-Y                   = -226025
      FRAME_-226025_NAME               = 'ROS_SA-Y'
      FRAME_-226025_CLASS              =  3
      FRAME_-226025_CLASS_ID           = -226025
      FRAME_-226025_CENTER             = -226
      CK_-226025_SCLK                  = -226
      CK_-226025_SPK                   = -226

   \begintext


Rosetta High Gain Antenna Frame
--------------------------------------

   The Rosetta High Gain Antenna is attached to the +X side of the s/c
   bus by a gimbal providing two degrees of freedom and it articulates
   during flight to track Earth. To incorporate rotations in the gimbal
   the HGA frame chain includes three frames: ROS_HGA_EL, ROS_HGA_AZ,
   and ROS_HGA.

   The first two frames are defined as CK-based frames and are
   co-aligned with the spacecraft frame in the zero gimbal position. In
   a non-zero position the ROS_HGA_EL is rotated from the spacecraft
   frame by an elevation angle about +Y and the ROS_HGA_AZ frame is
   rotated from the ROS_HGA_EL frame by an azimuth angle about +Z. These
   rotations are stored in separated segments in CK files.

   The ROS_HGA frame is defined as follows:

      -  +Z axis is in the antenna boresight direction;

      -  +X axis points from the gimbal toward the antenna dish
         symmetry axis;

      -  +Y axis completes the right hand frame;

      -  the origin of the frame is located at the geometric center of
         the HGA dish outer rim circle.

   The ROS_HGA frame is defined a fixed offset frame relative to the
   ROS_HGA_AZ frame and is rotated by +90 degrees about +Y from it.

   This diagram illustrates the ROS_HGA frames in the zero gimbal
   position:

   +X s/c side (HGA side) view:
   ----------------------------
                                    ^
                                    | toward comet
                                    |

                               Science Deck
                             ._____________.
   .__  _______________.     |             |     .______________  ___.
   |  \ \               \    |             |    /               \ \  |
   |  / /                \   |  +Zsc       |   /                / /  |
   |  \ \                 `. |      ^      | .'                 \ \  |
   |  / /                 | o|      |      |o |                 / /  |
   |  \ \                 .'+Zhga_el^      | `.                 \ \  |
   |  / /                /  +Zhga_az|      |   \                / /  |
   .__\ \_______________/    |      |      |    \_______________\ \__.
     -Y Solar Array          .______o-------> +Ysc   +Y Solar Array
                                 .__o------->
                               .'       `.    +Yhga_el
                              /           \   +Yhga_az
                             .   `.   .'   .
                             |     `o-------> +Yhga    +Zhga, +Xsc, +Xhga_el,
                             .      |      .              +Xhga_az and HGA
                              \     |     /               boresight are out
                               `.   |   .'                  of the page
                            HGA  ` -|- '
                                    V +Xhga


   This set of keywords defines the HGA frame as a CK frame:

   \begindata

      FRAME_ROS_HGA_EL                 = -226071
      FRAME_-226071_NAME               = 'ROS_HGA_EL'
      FRAME_-226071_CLASS              =  3
      FRAME_-226071_CLASS_ID           = -226071
      FRAME_-226071_CENTER             = -226
      CK_-226071_SCLK                  = -226
      CK_-226071_SPK                   = -226

      FRAME_ROS_HGA_AZ                 = -226072
      FRAME_-226072_NAME               = 'ROS_HGA_AZ'
      FRAME_-226072_CLASS              =  3
      FRAME_-226072_CLASS_ID           = -226072
      FRAME_-226072_CENTER             = -226
      CK_-226072_SCLK                  = -226
      CK_-226072_SPK                   = -226

      FRAME_ROS_HGA                    =  -226075
      FRAME_-226075_NAME               = 'ROS_HGA'
      FRAME_-226075_CLASS              =  4
      FRAME_-226075_CLASS_ID           =  -226075
      FRAME_-226075_CENTER             =  -226
      TKFRAME_-226075_RELATIVE         = 'ROS_HGA_AZ'
      TKFRAME_-226075_SPEC             = 'ANGLES'
      TKFRAME_-226075_UNITS            = 'DEGREES'
      TKFRAME_-226075_ANGLES           = (   0.000, -90.000,   0.000 )
      TKFRAME_-226075_AXES             = (   1,       2,       3     )

   \begintext


Other Rosetta Antenna Frames
--------------------------------------

   The frames for the other four Rosetta antennas -- MGA-S, MGA-X, LGA-1
   and LGA-2 -- are defined as follows:

      -  +Z axis is in the antenna boresight direction;

      -  +Y axis is nominally parallel to the s/c +Y axis;

      -  +X axis completes the right hand frame;

      -  the origin of the frame is located at the geometric center of
         the antenna outer side.

   Both MGA antennas are mounted on the +X side of the s/c bus and
   nominally point in the s/c +X axis direction. One rotation by +90
   degrees about +Y is needed to align the s/c frame with their frames.

   The LGA-1 is mounted on the +Z side of the s/c bus and nominally
   points 30 degrees off the s/c +Z axis toward the s/c +X axis. One
   rotation by +30 degrees about +Y is needed to align the s/c frame
   with the LGA-1 frame.

   The LGA-2 is mounted on the -X side of the s/c bus and nominally
   points 30 degrees off the s/c -Z axis toward the s/c -X axis. One
   rotation by +210 degrees about +Y is needed to align the s/c frame
   with the LGA-2 frame.

   This diagram illustrates the ROS_MGA-S and ROS_MGA-X frames:

   +Y s/c side view:
   -----------------

                                    ^
                                    | toward comet
                                    |

                                    Science Deck
             +Zmgax          ._____________.
                    <-------o|             |
                    <-------o|             |
             +Zmgas         ||  +Zsc       |----. Lander
                            ||      ^      |  | |
                     +Xmgax ||      |      |  | |
                           .V|      |      |  | |
                     +Xmgas V|      |      |----'
                       .'    |      |+Ysc  |
                      o==== <-------o _____.
                    .//   +Xsc
                    |`.
                    |  \
                    |   .
                  o'|   |
                   \|   '
                    |  /                +Y solar array is not shown
                    |.'
                    ' HGA                +Ysc, +Ymgas, and +Ymgax
                                           are out of the page


   This diagram illustrates the ROS_LGA-1 and ROS_LGA-2 frames:

   +Y s/c side view:
   -----------------

                    +Zlga1
                          ^         ^
                           \        | toward comet
                            \       |
                             \
                              o     Science Deck
                            .'_\___________.
                          .' |             |
                        .'   |             |
                +Xlga1 v     |  +Zsc       |----. Lander
                             |      ^      |  | |
                             |      |      |  | |
                           .'|      |      |  | |  ^
                         .'  |      |      |----'.' +Xlga2
                       .'    |      |+Ysc  |\  .'
                      o==== <-------o _____._o'
                    .//   +Xsc          LGA2  \
                    |`.                        \
                    |  \                        \
                    |   .                        V +Zlga2
                  o'|   |
                   \|   '
                    |  /                +Y solar array is not shown
                    |.'
                    ' HGA                +Ysc, +Ylga1, and +Ylga2
                                           are out of the page

   These sets of keywords define MGA and LGA frames as fixed offset
   frames:

   \begindata

      FRAME_ROS_MGA-S                  =  -226030
      FRAME_-226030_NAME               = 'ROS_MGA-S'
      FRAME_-226030_CLASS              =  4
      FRAME_-226030_CLASS_ID           =  -226030
      FRAME_-226030_CENTER             =  -226
      TKFRAME_-226030_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226030_SPEC             = 'ANGLES'
      TKFRAME_-226030_UNITS            = 'DEGREES'
      TKFRAME_-226030_ANGLES           = (   0.000, -90.000,   0.000 )
      TKFRAME_-226030_AXES             = (   1,       2,       3     )

      FRAME_ROS_MGA-X                  =  -226040
      FRAME_-226040_NAME               = 'ROS_MGA-X'
      FRAME_-226040_CLASS              =  4
      FRAME_-226040_CLASS_ID           =  -226040
      FRAME_-226040_CENTER             =  -226
      TKFRAME_-226040_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226040_SPEC             = 'ANGLES'
      TKFRAME_-226040_UNITS            = 'DEGREES'
      TKFRAME_-226040_ANGLES           = (   0.000, -90.000,   0.000 )
      TKFRAME_-226040_AXES             = (   1,       2,       3     )

      FRAME_ROS_LGA-1                  =  -226050
      FRAME_-226050_NAME               = 'ROS_LGA-1'
      FRAME_-226050_CLASS              =  4
      FRAME_-226050_CLASS_ID           =  -226050
      FRAME_-226050_CENTER             =  -226
      TKFRAME_-226050_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226050_SPEC             = 'ANGLES'
      TKFRAME_-226050_UNITS            = 'DEGREES'
      TKFRAME_-226050_ANGLES           = (   0.000, -30.000,   0.000 )
      TKFRAME_-226050_AXES             = (   1,       2,       3     )

      FRAME_ROS_LGA-2                  =  -226060
      FRAME_-226060_NAME               = 'ROS_LGA-2'
      FRAME_-226060_CLASS              =  4
      FRAME_-226060_CLASS_ID           =  -226060
      FRAME_-226060_CENTER             =  -226
      TKFRAME_-226060_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226060_SPEC             = 'ANGLES'
      TKFRAME_-226060_UNITS            = 'DEGREES'
      TKFRAME_-226060_ANGLES           = (   0.000, -210.000,  0.000 )
      TKFRAME_-226060_AXES             = (   1,       2,       3     )

   \begintext


Star Tracker Frames
--------------------------------------

   The Star Tracker STR-A and STR-B frames -- ROS_STR-A and ROS_STR-B
   -- are defined as follows:

      -  +Z axis points along the Star Tracker boresight;

      -  +X axis is nominally parallel to the s/c XY plane and points
         in the direction of the s/c +Y axis for STR-A and in the
         direction of the s/c -Y axis for STR-B;

      -  +Y axis completes the right hand frame;

      -  the origin of the frame is located at the Star Tracker focal
         point.

   This diagram illustrates the Star Tracker frames:

   +Z s/c side (science deck side) view:
   -------------------------------------------------

                          15 deg          15 deg   
                         \<--->|         |<--->/
                                        
                   +Zstr-b ^      _____      ^ +Zstr-a
                            \    /     \    /
                             \  |       |  /
                             .\___________/.
                             |.o         x.|
                  +Xstr-b  .-'             `-.  +Xstr-a
                         <'   |            |  `>
   o==/ /==================o |      o------->o==================/ /==o
     -Y Solar Array          |      |      | +Ysc    +Y Solar Array
                             |      |      |
                             .______|______.
                               `.   |   .'
                                 .--V +Xsc            +Zsc and +Ystr-b
                          HGA  .'       `.           are out of the page
                              /___________\
                                  `.|.'           +Ystr-a is into the page  
                                                    
                                                  +Zstr-b points 10 deg
                                                       below the page.


   The STR-A frame is nominally rotated from the s/c frame first by -90
   degrees about X, then by -75 degrees about Y.
 
   The STR-B frame is nominally rotated from the s/c frame first by +90
   degrees about X, then by -75 degrees about Y, then by +10 degrees
   about X.
 
   Two versions of the actual Star Tracker frame alignment matrices
   rotating vectors from the S/C frame to the Star Tracker frames were
   provided in [13], identical for STR-A and slightly different (by less
   than 1 nanoradian):

   Version 1:

     ALI_STR_1 =      |  0.259034391     0.965867442     0.001126502    |
                      | -0.000751627     0.001367888    -0.999998782    |
                      | -0.965867806     0.259033229     0.001080302    |

     ALI_STR_2 =      |  0.262922759    -0.964816148     0.001223493    |
                      | -0.171316109    -0.045437446     0.984167823    |
                      | -0.949485380    -0.258969714    -0.177235081    |

   Version 2:

                      |  0.259034391087  0.965867441850  0.001126502613 |
     ALI_STR_1 =      | -0.000751627000  0.001367888000 -0.999998781969 |
                      | -0.965867806323  0.259033228865  0.001080302083 |

                      |  0.262922749372 -0.964816112494  0.001223492980 |
     ALI_STR_2 =      | -0.171316102727 -0.045437444292  0.984167786306 |
                      | -0.949485345231 -0.258969704268 -0.177235074018 |


   The frame definitions below incorporate the Version 2 rotations.

   \begindata

      FRAME_ROS_STR-A                  = -226080
      FRAME_-226080_NAME               = 'ROS_STR-A'
      FRAME_-226080_CLASS              =  4
      FRAME_-226080_CLASS_ID           = -226080
      FRAME_-226080_CENTER             = -226
      TKFRAME_-226080_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226080_SPEC             = 'MATRIX'
      TKFRAME_-226080_MATRIX           = (  0.259034391087,
                                            0.965867441850,
                                            0.001126502613,
                                           -0.000751627000,
                                            0.001367888000,
                                           -0.999998781969,
                                           -0.965867806323,
                                            0.259033228865,
                                            0.001080302083  )
      
      FRAME_ROS_STR-B                  = -226090
      FRAME_-226090_NAME               = 'ROS_STR-B'
      FRAME_-226090_CLASS              =  4
      FRAME_-226090_CLASS_ID           = -226090
      FRAME_-226090_CENTER             = -226
      TKFRAME_-226090_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226090_SPEC             = 'MATRIX'
      TKFRAME_-226090_MATRIX           = (  0.262922749372,
                                           -0.964816112494,
                                            0.001223492980,
                                           -0.171316102727,
                                           -0.045437444292,
                                            0.984167786306,
                                           -0.949485345231,
                                           -0.258969704268,
                                           -0.177235074018  )

   \begintext


OSIRIS Frames
========================================================================

   This section of the file contains the definitions of the OSIRIS
   frames.


OSIRIS Frame Tree
--------------------------------------

   The diagram below shows the OSIRIS frame hierarchy.


                               "J2000" INERTIAL
           +-----------------------------------------------------+
           |                 |        |        |                 |
           |<-pck        ck->|        |        |<-pck       pck->|
           |                 |        |        |                 |
           V                 V        |        V                 V
       "67P/C-G_FIXED"  "67P/C-G_CK"  | "LUTETIA_FIXED"   "STEINS_FIXED"
         COMET BFXD      COMET BFXD   |  ASTEROID BFXD    ASTEROID BFXD
       ---------------  ------------  | --------------    --------------
                                      |
                                      |<-ck
                                      |
                                      V
                               "ROS_SPACECRAFT"
           +-----------------------------------------------------+
           |                 |                 |                 |
           |                 |<-fixed          |<-fixed          |
           |                 |                 |                 |
           |                 V                 V                 |
           |   "ROS_OSIRIS_NAC_URF"      "ROS_OSIRIS_WAC_URF"    |
           |   --------------------      --------------------    |
           |                                                     |
           |<-fixed                                              |<-fixed
           |                                                     |
           V                                                     V
     "ROS_OSIRIS_NAC"                                     "ROS_OSIRIS_WAC"
     ----------------                                      ----------------


OSIRIS Camera Frames
--------------------------------------

   The OSIRIS camera frames -- ROS_OSIRIS_NAC and ROS_OSIRIS_WAC -- are
   defined as follows:

      -  +Z axis points along the camera boresight;

      -  +X axis is parallel to the apparent image columns; it is
         nominally co-aligned with the s/c +X axis;

      -  +Y axis completes the right hand frame; it is nominally
         parallel the to the apparent image lines and co-aligned with
         the s/c +Y axis;

      -  the origin of the frame is located at the camera focal point.

   This diagram illustrates the OSIRIS camera frames:


   +Z s/c side (science deck side) view:
   -------------------------------------

                               Lander
                                  _____
                                 /     \
                                |       |
                             .___________ +Ynac  +Ywac
                             | NAC o----o-->---->
                             |     |    |WAC
                             |     |    |  | +Ysc
   o==/ /==================o |     |o---|--->o==================/ /==o
     -Y Solar Array          |     ||   |  |        +Y Solar Array
                             +Xnac V|   V +Xwac
                             .______|______.
                               `.   |   .'
                                 .--V +Xsc
                          HGA  .'       `.
                              /___________\
                                  `.|.'                 +Zsc, +Znac, and
                                                         +Zwac are out
                                                          of the page

   Nominally, the OSIRIS camera frames are co-aligned with the s/c
   frame.

   The actual OSIRIS NAC boresight direction is specified in [7] as an
   offset from the s/c +Z axis by the following two angles:

      Offset from Z s/c: x (deg) =  -0.027
      Offset from Z s/c: y (deg) =   0.013

   while the actual OSIRIS WAC boresight direction is
   specified by:

      Offset from Z s/c: x (deg) =   0.351
      Offset from Z s/c: y (deg) =   0.0871

   The first of the two angles -- ``Offset from Z s/c: x'' -- is the
   angle between the projection of the boresight onto the s/c XZ plane
   and the s/c +Z axis, measured positive from the s/c +Z toward the
   s/c +X axis. The second of the two angles -- ``Offset from Z s/c:
   y'' -- is the angle between the projection of the boresight onto the
   s/c YZ plane and the s/c +Z axis, measured positive from the s/c +Z
   toward the s/c +Y axis.

   The following set of rotations can be applied to the s/c axes to
   align the OSIRIS NAC frame's +Z axis with the boresight defined by
   the angles above (rotation about +Z is not defined in [7] and
   assumed to be zero in this set of rotations):

      Msc->nac = [0.0]z * [-0.027]y * [-0.013]x

   These rotations can be applied to the s/c axes to align the OSIRIS
   WAC frame's +Z axis with the boresight defined by the angles above
   (rotation about +Z is not defined in [7] and assumed to be zero in
   this set of rotations):

      Msc->wac = [0.0]z * [0.35099959]y * [-0.0871]x

   The OSIRIS NAC and WAC frame definitions below incorporate these
   transformations.

   \begindata

      FRAME_ROS_OSIRIS_NAC             =  -226111
      FRAME_-226111_NAME               = 'ROS_OSIRIS_NAC'
      FRAME_-226111_CLASS              =  4
      FRAME_-226111_CLASS_ID           =  -226111
      FRAME_-226111_CENTER             =  -226
      TKFRAME_-226111_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226111_SPEC             = 'ANGLES'
      TKFRAME_-226111_UNITS            = 'DEGREES'
      TKFRAME_-226111_ANGLES           = ( 0.013, 0.027, 0.0 )
      TKFRAME_-226111_AXES             = ( 1,     2,     3   )

      FRAME_ROS_OSIRIS_WAC             =  -226112
      FRAME_-226112_NAME               = 'ROS_OSIRIS_WAC'
      FRAME_-226112_CLASS              =  4
      FRAME_-226112_CLASS_ID           =  -226112
      FRAME_-226112_CENTER             =  -226
      TKFRAME_-226112_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226112_SPEC             = 'ANGLES'
      TKFRAME_-226112_UNITS            = 'DEGREES'
      TKFRAME_-226112_ANGLES           = ( 0.0871, -0.35099959, 0.0 )
      TKFRAME_-226112_AXES             = ( 1,       2,          3   )

   \begintext


OSIRIS Unit Reference Frames
--------------------------------------

   This section implements the OSIRIS Unit Reference Frames (URF) frame
   definitions provided in [5].

   \begindata

      FRAME_ROS_OSIRIS_NAC_URF         =  -226116
      FRAME_-226116_NAME               = 'ROS_OSIRIS_NAC_URF'
      FRAME_-226116_CLASS              =  4
      FRAME_-226116_CLASS_ID           =  -226116
      FRAME_-226116_CENTER             =  -226
      TKFRAME_-226116_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226116_SPEC             = 'ANGLES'
      TKFRAME_-226116_UNITS            = 'DEGREES'
      TKFRAME_-226116_ANGLES           = ( 0.0, 90.0, -6.96 )
      TKFRAME_-226116_AXES             = ( 1,    2,    3    )

      FRAME_ROS_OSIRIS_WAC_URF         =  -226117
      FRAME_-226117_NAME               = 'ROS_OSIRIS_WAC_URF'
      FRAME_-226117_CLASS              =  4
      FRAME_-226117_CLASS_ID           =  -226117
      FRAME_-226117_CENTER             =  -226
      TKFRAME_-226117_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226117_SPEC             = 'ANGLES'
      TKFRAME_-226117_UNITS            = 'DEGREES'
      TKFRAME_-226117_ANGLES           = ( 0.0, 90.0,  7.0  )
      TKFRAME_-226117_AXES             = ( 1,    2,    3    )

   \begintext



ALICE Frames
========================================================================

   This section of the file contains the definitions of the ALICE
   frames.


ALICE Frame Tree
--------------------------------------

   The diagram below shows the ALICE frame hierarchy.


                               "J2000" INERTIAL
           +-----------------------------------------------------+
           |                 |        |        |                 |
           |<-pck        ck->|        |        |<-pck       pck->|
           |                 |        |        |                 |
           V                 V        |        V                 V
       "67P/C-G_FIXED"  "67P/C-G_CK"  | "LUTETIA_FIXED"   "STEINS_FIXED"
         COMET BFXD      COMET BFXD   |  ASTEROID BFXD    ASTEROID BFXD
       ---------------  ------------  | --------------    --------------
                                      |
                                      |<-ck
                                      |
                                      V
                               "ROS_SPACECRAFT"
           +-----------------------------------------------------
           |                 |
           |                 |<-fixed
           |                 |
           |                 V
           |          "ROS_ALICE_URF"
           |          ---------------
           |
           |<-fixed
           |
           V
     "ROS_ALICE"
     -----------


ALICE Frame
--------------------------------------

   The ALICE frame is defined as follows:

      -  +Z axis points along the instrument boresight;

      -  +X axis is parallel to the apparent spatial resolution
         direction (i.e. along the slit); it is nominally co-aligned
         with the s/c +X axis;

      -  +Y axis completes the right hand frame; it is nominally
         co-aligned with the s/c +Y axis;

      -  the origin of the frame is located at the instrument focal
         point.

   This diagram illustrates the ALICE frame:


   +Z s/c side (science deck side) view:
   -------------------------------------

                               Lander
                                  _____
                                 /     \
                                |       |
                             ._____________.     +Yalice
                             |     ALICE o------>
                             |           | |
                             |           | | +Ysc
   o==/ /==================o |      o----|-->o==================/ /==o
     -Y Solar Array          |      |    | |        +Y Solar Array
                             |      |    V+Xalice
                             .______|______.
                               `.   |   .'
                                 .--V +Xsc
                          HGA  .'       `.
                              /___________\
                                  `.|.'                 +Zsc and +Zalice
                                                            are out
                                                          of the page

   Nominally, the ALICE frame is co-aligned with the s/c frame.

   The actual ALICE boresight direction is specified in [7] as an
   offset from the s/c +Z axis by the following two angles:

      Offset from Z s/c: x (deg) =   0.0623225438
      Offset from Z s/c: y (deg) =  -0.1067957415

   The first of the two angles -- ``Offset from Z s/c: x'' -- is the
   angle between the projection of the boresight onto the s/c XZ plane
   and the s/c +Z axis, measured positive from the s/c +Z toward the
   s/c +X axis. The second of the two angles -- ``Offset from Z s/c:
   y'' -- is the angle between the projection of the boresight onto the
   s/c YZ plane and the s/c +Z axis, measured positive from the s/c +Z
   toward the s/c +Y axis.

   The Euler Angles to be applied to align the +Z axis of the s/c with
   the boresight can be calculated from the angles above using the
   formulae in [11]:

      Rotation about the +Y axis: +0.0623225438
      Rotation about the +X axis: +0.1067956783

   , which corresponds to the following matrix:

      Malice->sc = [ 0.0 ]z * [ 0.1067956783 ]x * [ 0.0623225438 ]y

   Since in SPICE it has to be specified the rotation to be applied to
   convert the ALICE frame into the s/c frame, the matrix above has to
   be inverted:

      Msc->alice = [ -0.0623225438 ]y * [ -0.1067956783 ]x * [ 0.0 ]z

   The frame definition below incorporates this transformation.

   \begindata

      FRAME_ROS_ALICE                  =  -226120
      FRAME_-226120_NAME               = 'ROS_ALICE'
      FRAME_-226120_CLASS              =  4
      FRAME_-226120_CLASS_ID           =  -226120
      FRAME_-226120_CENTER             =  -226
      TKFRAME_-226120_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226120_SPEC             = 'ANGLES'
      TKFRAME_-226120_UNITS            = 'DEGREES'
      TKFRAME_-226120_ANGLES           = ( -0.0623225438, -0.1067956783, 0.0 )
      TKFRAME_-226120_AXES             = (  2,      1,         3   )

   \begintext


ALICE Unit Reference Frame
--------------------------------------

   This section implements the ALICE Unit Reference Frames (URF) frame
   definition provided in [5].

   \begindata

      FRAME_ROS_ALICE_URF              =  -226125
      FRAME_-226125_NAME               = 'ROS_ALICE_URF'
      FRAME_-226125_CLASS              =  4
      FRAME_-226125_CLASS_ID           =  -226125
      FRAME_-226125_CENTER             =  -226
      TKFRAME_-226125_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226125_SPEC             = 'ANGLES'
      TKFRAME_-226125_UNITS            = 'DEGREES'
      TKFRAME_-226125_ANGLES           = ( 0.0, -90.0, -90.0 )
      TKFRAME_-226125_AXES             = ( 2,     3,     1   )

   \begintext


VIRTIS frames
========================================================================

   This section of the file contains the definitions of the VIRTIS
   frames.


VIRTIS Frame Tree
--------------------------------------

   The diagram below shows the VIRTIS frame hierarchy.


                               "J2000" INERTIAL
           +-----------------------------------------------------+
           |                 |        |        |                 |
           |<-pck        ck->|        |        |<-pck       pck->|
           |                 |        |        |                 |
           V                 V        |        V                 V
       "67P/C-G_FIXED"  "67P/C-G_CK"  | "LUTETIA_FIXED"   "STEINS_FIXED"
         COMET BFXD      COMET BFXD   |  ASTEROID BFXD    ASTEROID BFXD
       ---------------  ------------  | --------------    --------------
                                      |
                                      |<-ck
                                      |
                                      V
                               "ROS_SPACECRAFT"
                        +--------------------------+
                        |                          |
                        |<-fixed                   |<-fixed
                        |                          |
                        V                          |
                  "ROS_VIRTIS-H"                   |
                  --------------                   |
                                                   |
                                                   V
                                            "ROS_VIRTIS-M"
               +---------------------------------------------+
               |                      |                      |
               |<-fixed               |<-ck                  |<-fixed
               |                      |                      |
               V                      V                      V
    "ROS_VIRTIS-M_VIS_ZERO"   "ROS_VIRTIS-M_SCAN"   "ROS_VIRTIS-M_IR_ZERO"
    -----------------------   +-----------------+   ----------------------
                              |                 |
                              |<-fixed          |<-fixed
                              |                 |
                              V                 V
                     "ROS_VIRTIS-M_VIS"  "ROS_VIRTIS-M_IR"
                     ------------------  -----------------


VIRTIS Frames
--------------------------------------

   The six different frames are defined for VIRTIS-M instrument with
   the following intent:

      Frame Name                  Frame Intent
      --------------------        --------------------------------------
      ROS_VIRTIS-M                This frame is defined to capture
                                  misalignment between the instrument
                                  mirror rotation axis and the s/c +Y axis.
                                  This misalignment is constant therefore
                                  this frame is defined as a fixed offset
                                  frame relative to the ROS_SPACECRAFT
                                  frame.

      ROS_VIRTIS-M_SCAN           This frame is defined to capture
                                  orientation of the reflected instrument
                                  view direction due to the scan mirror
                                  motion. This frame is defined as
                                  CK-based frame because this time variable
                                  orientation is stored in a CK file.

      ROS_VIRTIS-M_VIS            These two frames are defined to capture
      ROS_VIRTIS-M_IR             misalignments for each of the two
                                  instrument channels relative to the
                                  reflected view direction. These
                                  frames are defined as fixed offset frames
                                  relative to the ROS_VIRTIS-M_SCAN frame.
                                  These two frames are the frames that
                                  should be used to compute the instrument
                                  pixel view directions when the CK files
                                  for the scan mirror are available.

      ROS_VIRTIS-M_VIS_ZERO       These two frames are defined to capture
      ROS_VIRTIS-M_IR_ZERO        misalignments for each of the two
                                  instrument channels relative to the
                                  reflected view direction with scan
                                  mirror in zero position. The main purpose
                                  of these frames is to capture all
                                  available misalignment data while allowing
                                  to compute reflected view direction
                                  externally to SPICE and then combine it
                                  with the misalignments. These frames should
                                  be used when CK files for the scan mirror
                                  are not available.

   Each of the VIRTIS-M frames listed above is defined in the same way
   as follows:

      -  +Z axis points along the boresight (for ROS_VIRTIS-M boresight
         is the nominal center pixel view direction for the scan mirror
         in "zero" position; for ROS_VIRTIS-M_SCAN boresight is the
         nominal center pixel view direction, "off-pointed" due to the
         scan mirror; for ROS_VIRTIS-M_VIS and ROS_VIRTIS-M_IR
         boresight is the particular detector center pixel view
         direction, "off-pointed" due to the scan mirror; for
         ROS_VIRTIS-M_VIS_ZERO and ROS_VIRTIS-M_IR_ZERO frames it is
         the center pixel view direction, adjusted for all known
         misalignments with the scan mirror in "zero" position)

      -  +Y axis is parallel to the apparent spatial resolution
         direction; it is nominally co-aligned with the s/c +Y axis;

      -  +X axis completes the right hand frame;

      -  the origin of the frame is located at the instrument focal
         point for ROS_VIRTIS-M_VIS, ROS_VIRTIS-M_IR,
         ROS_VIRTIS-M_VIS_ZERO and ROS_VIRTIS-M_IR_ZERO frames and at
         the intersection of the nominal center pixel view direction
         and the scan mirror axis for ROS_VIRTIS-M and
         ROS_VIRTIS-M_SCAN frames.

   Nominally, in "zero" scan mirror position all six frames are
   co-aligned with each other and the s/c frame.

   The VIRTIS-H frame, ROS_VIRTIS-H, is defined as follows:

      -  +Z axis points along the boresight;

      -  +Y axis is parallel to the apparent spatial resolution
         direction (i.e. along the slit); it is nominally co-aligned
         with the s/c +Y axis;

      -  +X axis completes the right hand frame; it is nominally
         co-aligned with the s/c +X axis;

      -  the origin of the frame is located at the instrument focal
         point.

   Nominally, ROS_VIRTIS-H frame is co-aligned with the s/c frame.

   This diagram illustrates the VIRTIS frames (with VIRTIS-M scan
   mirror in "zero" position):


   +Z s/c side (science deck side) view:
   -------------------------------------

                               Lander
                                  _____
                                 /     \
                                |       | +Ymir
                             .____ +Yh __ +Ymvis
                      VIRTIS | o-o---->-> +Ym
                             | | |         |
                             | | |         | +Ysc
   o==/ /==================o | | |  o------->o==================/ /==o
     -Y Solar Array            | |  |      |        +Y Solar Array
                           +Xh V v  |      |
                             ._+Xm |______.
                             +Xmvis |   .'
                              +Xmir-V +Xsc
                          HGA  .'       `.
                              /___________\
                                  `.|.'                +Zsc, +Zmvis, +Zmir,
                                                       +Zm and +Zh are out
                                                           of the page


   According to [10] alignment data for VIRTIS-M indicate that the
   instrument boresight (center pixel view direction) is tilted with
   respect to the spacecraft +Z axis by 0.075 degrees toward -X axis
   and by 0.02167 degrees toward -Y axis. This misalignment is
   incorporated as a two rotations, first by 0.02167 degrees about +X
   axis and then by -0.075 degrees about +Y axis, into the definitions
   of the ROS_VIRTIS-M_VIS, ROS_VIRTIS-M_IR, ROS_VIRTIS-M_VIS_ZERO and
   ROS_VIRTIS-M_IR_ZERO frames. These rotations were implemented by the
   following frame definition keywords in the FK versions 1.2-2.0:

      TKFRAME_-226211_RELATIVE         = 'ROS_VIRTIS-M_SCAN'
      TKFRAME_-226211_SPEC             = 'ANGLES'
      TKFRAME_-226211_UNITS            = 'DEGREES'
      TKFRAME_-226211_ANGLES           = ( -0.02167, 0.075, 0.0 )
      TKFRAME_-226211_AXES             = ( 1,   2,   3   )

      TKFRAME_-226213_RELATIVE         = 'ROS_VIRTIS-M_SCAN'
      TKFRAME_-226213_SPEC             = 'ANGLES'
      TKFRAME_-226213_UNITS            = 'DEGREES'
      TKFRAME_-226213_ANGLES           = ( -0.02167, 0.075, 0.0 )
      TKFRAME_-226213_AXES             = ( 1,   2,   3   )

      TKFRAME_-226212_RELATIVE         = 'ROS_VIRTIS-M'
      TKFRAME_-226212_SPEC             = 'ANGLES'
      TKFRAME_-226212_UNITS            = 'DEGREES'
      TKFRAME_-226212_ANGLES           = ( -0.02167, 0.075, 0.0 )
      TKFRAME_-226212_AXES             = ( 1,   2,   3   )

      TKFRAME_-226214_RELATIVE         = 'ROS_VIRTIS-M'
      TKFRAME_-226214_SPEC             = 'ANGLES'
      TKFRAME_-226214_UNITS            = 'DEGREES'
      TKFRAME_-226214_ANGLES           = ( -0.02167, 0.075, 0.0 )
      TKFRAME_-226214_AXES             = ( 1,   2,   3   )

   According to [12], based on analysis of star observations carried
   out by Rosetta/VIRTIS in 2014, the VIRTIS team at INAF-IAPS
   determined that the ROS_VIRTIS-M_VIS frame is rotated relative to
   the ROS_VIRTIS-M_SCAN frame first by -0.032945073 degrees about +X
   axis, then by -0.071619724 degrees about +Y axis while the
   ROS_VIRTIS-M_IR frame is rotated relative to the ROS_VIRTIS-M_SCAN
   frame first by +0.025926340 degrees about +X axis, then by
   -0.071619724 degrees about +Y axis. These rotations were implemented
   in the FK starting with the version 2.1.

   According to [10] alignment data for VIRTIS-H indicate that the
   instrument boresight (center pixel view direction) is tilted with
   respect to the spacecraft +Z axis by 0.0936 degrees toward -X axis
   and by 0.0027 degrees toward +Y axis. This misalignment is
   incorporated as a two rotations, first by -0.0027 degrees about +X
   axis and then by -0.0936 degrees about +Y axis, into the
   definition of the ROS_VIRTIS-H frame.

   Keyword blocks below define VIRTIS frames.

   Since the SPICE frames subsystem calls for specifying the reverse
   transformation--going from the instrument or structure frame to the
   base frame--as compared to the description given above, the order of
   rotations assigned to the TKFRAME_*_AXES keyword is also reversed
   compared to the above text, and the signs associated with the
   rotation angles assigned to the TKFRAME_*_ANGLES keyword are the
   opposite from what is written in the above text.

   \begindata

      FRAME_ROS_VIRTIS-M               =  -226210
      FRAME_-226210_NAME               = 'ROS_VIRTIS-M'
      FRAME_-226210_CLASS              =  4
      FRAME_-226210_CLASS_ID           =  -226210
      FRAME_-226210_CENTER             =  -226
      TKFRAME_-226210_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226210_SPEC             = 'ANGLES'
      TKFRAME_-226210_UNITS            = 'DEGREES'
      TKFRAME_-226210_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-226210_AXES             = ( 1,   2,   3   )

      FRAME_ROS_VIRTIS-M_SCAN          =  -226215
      FRAME_-226215_NAME               =  'ROS_VIRTIS-M_SCAN'
      FRAME_-226215_CLASS              =  3
      FRAME_-226215_CLASS_ID           =  -226215
      FRAME_-226215_CENTER             =  -226
      CK_-226215_SCLK                  =  -226
      CK_-226215_SPK                   =  -226

      FRAME_ROS_VIRTIS-M_VIS           =  -226211
      FRAME_-226211_NAME               = 'ROS_VIRTIS-M_VIS'
      FRAME_-226211_CLASS              =  4
      FRAME_-226211_CLASS_ID           =  -226211
      FRAME_-226211_CENTER             =  -226
      TKFRAME_-226211_RELATIVE         = 'ROS_VIRTIS-M_SCAN'
      TKFRAME_-226211_SPEC             = 'ANGLES'
      TKFRAME_-226211_UNITS            = 'DEGREES'
      TKFRAME_-226211_ANGLES           = ( 0.032945073, 0.071619724, 0.0 )
      TKFRAME_-226211_AXES             = ( 1,   2,   3   )

      FRAME_ROS_VIRTIS-M_IR            =  -226213
      FRAME_-226213_NAME               = 'ROS_VIRTIS-M_IR'
      FRAME_-226213_CLASS              =  4
      FRAME_-226213_CLASS_ID           =  -226213
      FRAME_-226213_CENTER             =  -226
      TKFRAME_-226213_RELATIVE         = 'ROS_VIRTIS-M_SCAN'
      TKFRAME_-226213_SPEC             = 'ANGLES'
      TKFRAME_-226213_UNITS            = 'DEGREES'
      TKFRAME_-226213_ANGLES           = ( -0.025926340, 0.071619724, 0.0 )
      TKFRAME_-226213_AXES             = ( 1,   2,   3   )

      FRAME_ROS_VIRTIS-M_VIS_ZERO       = -226212
      FRAME_-226212_NAME               = 'ROS_VIRTIS-M_VIS_ZERO'
      FRAME_-226212_CLASS              =  4
      FRAME_-226212_CLASS_ID           = -226212
      FRAME_-226212_CENTER             = -226
      TKFRAME_-226212_RELATIVE         = 'ROS_VIRTIS-M'
      TKFRAME_-226212_SPEC             = 'ANGLES'
      TKFRAME_-226212_UNITS            = 'DEGREES'
      TKFRAME_-226212_ANGLES           = ( 0.032945073, 0.071619724, 0.0 )
      TKFRAME_-226212_AXES             = ( 1,   2,   3   )

      FRAME_ROS_VIRTIS-M_IR_ZERO       = -226214
      FRAME_-226214_NAME               = 'ROS_VIRTIS-M_IR_ZERO'
      FRAME_-226214_CLASS              =  4
      FRAME_-226214_CLASS_ID           = -226214
      FRAME_-226214_CENTER             = -226
      TKFRAME_-226214_RELATIVE         = 'ROS_VIRTIS-M'
      TKFRAME_-226214_SPEC             = 'ANGLES'
      TKFRAME_-226214_UNITS            = 'DEGREES'
      TKFRAME_-226214_ANGLES           = ( -0.025926340, 0.071619724, 0.0 )
      TKFRAME_-226214_AXES             = ( 1,   2,   3   )

      FRAME_ROS_VIRTIS-H               =  -226220
      FRAME_-226220_NAME               = 'ROS_VIRTIS-H'
      FRAME_-226220_CLASS              =  4
      FRAME_-226220_CLASS_ID           =  -226220
      FRAME_-226220_CENTER             =  -226
      TKFRAME_-226220_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226220_SPEC             = 'ANGLES'
      TKFRAME_-226220_UNITS            = 'DEGREES'
      TKFRAME_-226220_ANGLES           = ( 0.0027, 0.0936, 0.0 )
      TKFRAME_-226220_AXES             = ( 1,     2,          3   )

   \begintext


MIRO frames
========================================================================

   This section of the file contains the definitions of the MIRO
   frames.


MIRO Frame Tree
--------------------------------------

   The diagram below shows the MIRO frame hierarchy.


                               "J2000" INERTIAL
           +-----------------------------------------------------+
           |                 |        |        |                 |
           |<-pck        ck->|        |        |<-pck       pck->|
           |                 |        |        |                 |
           V                 V        |        V                 V
       "67P/C-G_FIXED"  "67P/C-G_CK"  | "LUTETIA_FIXED"   "STEINS_FIXED"
         COMET BFXD      COMET BFXD   |  ASTEROID BFXD    ASTEROID BFXD
       ---------------  ------------  | --------------    --------------
                                      |
                                      |<-ck
                                      |
                                      V
                               "ROS_SPACECRAFT"
           +-----------------------------------------------------+
           |                                                     |
           |<-fixed                                              |<-fixed
           |                                                     |
           |                                                     |
       "ROS_MIRO"                                         "ROS_MIRO_URF"
       ----------------------+                            --------------
           |                 |
           |<-fixed          |<-fixed
           |                 |
           V                 V
       "ROS_MIRO_MM"  "ROS_MIRO_SUBMM"
       -------------  ----------------


MIRO Frame
--------------------------------------

   The MIRO structure frame, ROS_MIRO, and MIRO millimeter and
   sub-millimeter channels frames, ROS_MIRO_MM and ROS_MIRO_SUBMM, are
   defined as follows:

      -  +Z axis points along the boresight;

      -  +Y axis is nominally co-aligned with the s/c +Y axis;

      -  +X axis completes the right hand frame; it is nominally
         co-aligned with the s/c +X axis;

      -  the origin of the frame is located at the telescope focal point.

   This diagram illustrates the MIRO frames:


   +Z s/c side (science deck side) view:
   -------------------------------------

                               Lander
                                  _____
                                 /     \
                                |       |
                             ._____________.
                             |             |
                             |       MIRO  |     +Ymiro, +Ymm, +Ysubmm
                             |           o------>
   o==/ /==================o |      o----|-->o==================/ /==o
     -Y Solar Array          |      |    | | +Ysc   +Y Solar Array
                             |      |    | |
                             .______|____|_.
                               `.   |   .V +Xmiro, +Xmm, +Xsubmm
                                 .--V +Xsc
                          HGA  .'       `.
                              /___________\
                                  `.|.'                 +Zsc, +Zmiro, +Zmm
                                                        and +Zsubmm are out
                                                            of the page

   Nominally, the MIRO frame is co-aligned with the s/c frame.

   The actual MIRO sub-millimeter channel boresight direction is
   specified in [7] as an offset from the s/c +Z axis by the following
   two angles:

      Offset from Z s/c: x (deg) =  -0.082
      Offset from Z s/c: y (deg) =  -0.0067

   while the actual MIRO millimeter channel boresight direction is
   specified by:

      Offset from Z s/c: x (deg) =  -0.018
      Offset from Z s/c: y (deg) =  -0.057

   The first of the two angles -- ``Offset from Z s/c: x'' -- is the
   angle between the projection of the boresight onto the s/c XZ plane
   and the s/c +Z axis, measured positive from the s/c +Z toward the
   s/c +X axis. The second of the two angles -- ``Offset from Z s/c:
   y'' -- is the angle between the projection of the boresight onto the
   s/c YZ plane and the s/c +Z axis, measured positive from the s/c +Z
   toward the s/c +Y axis.

   The following set of rotations can be applied to the s/c axes to
   align the MIRO sub-millimeter channel frame's +Z axis with the
   boresight defined by the angles above (rotation about +Z is not
   defined in [7] and assumed to be zero in this set of rotations):

      Msc->miro_submm = [0.0]z * [-0.082]y * [0.0067]x

   These rotations can be applied to the s/c axes to align the MIRO
   millimeter channel frame's +Z axis with the boresight defined by the
   angles above (rotation about +Z is not defined in [7] and assumed to
   be zero in this set of rotations):

      Msc->miro_mm    = [0.0]z * [-0.01799999]y * [0.057]x

   The MIRO millimeter and sub-millimeter channel frame definitions
   below incorporate these transformations.

   \begindata

      FRAME_ROS_MIRO                   =  -226130
      FRAME_-226130_NAME               = 'ROS_MIRO'
      FRAME_-226130_CLASS              =  4
      FRAME_-226130_CLASS_ID           =  -226130
      FRAME_-226130_CENTER             =  -226
      TKFRAME_-226130_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226130_SPEC             = 'ANGLES'
      TKFRAME_-226130_UNITS            = 'DEGREES'
      TKFRAME_-226130_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-226130_AXES             = ( 1,   2,   3   )

      FRAME_ROS_MIRO_MM                =  -226131
      FRAME_-226131_NAME               = 'ROS_MIRO_MM'
      FRAME_-226131_CLASS              =  4
      FRAME_-226131_CLASS_ID           =  -226131
      FRAME_-226131_CENTER             =  -226
      TKFRAME_-226131_RELATIVE         = 'ROS_MIRO'
      TKFRAME_-226131_SPEC             = 'ANGLES'
      TKFRAME_-226131_UNITS            = 'DEGREES'
      TKFRAME_-226131_ANGLES           = ( -0.057, 0.01799999, 0.0 )
      TKFRAME_-226131_AXES             = (  1,     2,          3   )

      FRAME_ROS_MIRO_SUBMM             =  -226132
      FRAME_-226132_NAME               = 'ROS_MIRO_SUBMM'
      FRAME_-226132_CLASS              =  4
      FRAME_-226132_CLASS_ID           =  -226132
      FRAME_-226132_CENTER             =  -226
      TKFRAME_-226132_RELATIVE         = 'ROS_MIRO'
      TKFRAME_-226132_SPEC             = 'ANGLES'
      TKFRAME_-226132_UNITS            = 'DEGREES'
      TKFRAME_-226132_ANGLES           = ( -0.0067, 0.082, 0.0 )
      TKFRAME_-226132_AXES             = (  1,      2,     3   )

   \begintext


MIRO Unit Reference Frame
--------------------------------------

   This section implements the MIRO Unit Reference Frames (URF) frame
   definition provided in [5].

   \begindata

      FRAME_ROS_MIRO_URF               =  -226135
      FRAME_-226135_NAME               = 'ROS_MIRO_URF'
      FRAME_-226135_CLASS              =  4
      FRAME_-226135_CLASS_ID           =  -226135
      FRAME_-226135_CENTER             =  -226
      TKFRAME_-226135_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226135_SPEC             = 'ANGLES'
      TKFRAME_-226135_UNITS            = 'DEGREES'
      TKFRAME_-226135_ANGLES           = ( 0.0, 0.0, 180.0 )
      TKFRAME_-226135_AXES             = ( 2,   1,     3   )

   \begintext


ROSINA frames
========================================================================

   This section of the file contains the definitions of the ROSINA
   frames.


ROSINA Frame Tree
--------------------------------------

   The diagram below shows the ROSINA frame hierarchy.


                               "J2000" INERTIAL
           +-----------------------------------------------------+
           |                 |        |        |                 |
           |<-pck        ck->|        |        |<-pck       pck->|
           |                 |        |        |                 |
           V                 V        |        V                 V
       "67P/C-G_FIXED"  "67P/C-G_CK"  | "LUTETIA_FIXED"   "STEINS_FIXED"
         COMET BFXD      COMET BFXD   |  ASTEROID BFXD    ASTEROID BFXD
       ---------------  ------------  | --------------    --------------
                                      |
                                      |<-ck
                                      |
                                      V
                               "ROS_SPACECRAFT"
           +-----------------------------------------------------+
           |          |          |         |          |          |
           |<-fixed   |<-fixed   |<-fixed  |<-fixed   |<-fixed   |<-fixed
           |          |          |         |          |          |
           |          |          |         |          |          V
           |          |          |         |          | "ROS_ROSINA_COPS_URF"
           |          |          |         |          | ---------------------
           |          |          |         |          |
           |          |          |         |          V
           |          |          |         |  "ROS_ROSINA_COPS"
           |          |          |         |  -----------------
           |          |          |         |
           |          |          |         V
           |          |          | "ROS_ROSINA_RTOF_URF"
           |          |          | ---------------------
           |          |          |
           |          |          V
           |          |  "ROS_ROSINA_RTOF"
           |          |  -----------------
           |          |
           |          V
           |  "ROS_ROSINA_DFMS_URF"
           |  ---------------------
           |
           V
     "ROS_ROSINA_DFMS"
     -----------------


ROSINA Sensor Frames
--------------------------------------

   The ROSINA sensor frames -- ROS_ROSINA_DFMS, ROS_ROSINA_RTOF,
   and ROS_ROSINA_COPS -- are defined to be nominally co-aligned with
   the s/c frame.

   This diagram illustrates the ROSINA sensor frames:

   +Z s/c side (science deck side) view:
   -------------------------------------

                               Lander
                                  _____
                                 /     \
                                |       |
                             ._____________.
                         COPS          +Ycops
                             |o------->    |
                             ||            | +Ysc
   o==/ /==================o ||     o------->o==================/ /==o
     -Y Solar Array      DFMS o------->    |        +Y Solar Array
                             ||     |  +Ydfms
                       +Xcops V ____|______.
                              | .   |   .'o------->
                              |  .--V--.  |RTOF    +Yrtof
                       +Xdfms V.' +Xsc  `.|
                              /___________|
                                  `.|.'   |           +Zsc, +Zdfms, +Zrtof
                             HGA          V            and +Zcops are out
                                           +Xrtof         of the page

   Nominally, the ROSINA sensor frames are co-aligned with the s/c
   frame.

   \begindata

      FRAME_ROS_ROSINA_DFMS            =  -226310
      FRAME_-226310_NAME               = 'ROS_ROSINA_DFMS'
      FRAME_-226310_CLASS              =  4
      FRAME_-226310_CLASS_ID           =  -226310
      FRAME_-226310_CENTER             =  -226
      TKFRAME_-226310_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226310_SPEC             = 'ANGLES'
      TKFRAME_-226310_UNITS            = 'DEGREES'
      TKFRAME_-226310_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-226310_AXES             = ( 1,   2,   3   )

      FRAME_ROS_ROSINA_RTOF            =  -226320
      FRAME_-226320_NAME               = 'ROS_ROSINA_RTOF'
      FRAME_-226320_CLASS              =  4
      FRAME_-226320_CLASS_ID           =  -226320
      FRAME_-226320_CENTER             =  -226
      TKFRAME_-226320_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226320_SPEC             = 'ANGLES'
      TKFRAME_-226320_UNITS            = 'DEGREES'
      TKFRAME_-226320_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-226320_AXES             = ( 1,   2,   3   )

      FRAME_ROS_ROSINA_COPS            =  -226330
      FRAME_-226330_NAME               = 'ROS_ROSINA_COPS'
      FRAME_-226330_CLASS              =  4
      FRAME_-226330_CLASS_ID           =  -226330
      FRAME_-226330_CENTER             =  -226
      TKFRAME_-226330_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226330_SPEC             = 'ANGLES'
      TKFRAME_-226330_UNITS            = 'DEGREES'
      TKFRAME_-226330_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-226330_AXES             = ( 1,   2,   3   )

   \begintext


ROSINA Unit Reference Frames
--------------------------------------

   This section implements the ROSINA Unit Reference Frames (URF) frame
   definitions. While these were not specifically spelled out in [5],
   they are defined according to the rules outlined in the section 7.3
   of that document.

   \begindata

      FRAME_ROS_ROSINA_DFMS_URF        =  -226319
      FRAME_-226319_NAME               = 'ROS_ROSINA_DFMS_URF'
      FRAME_-226319_CLASS              =  4
      FRAME_-226319_CLASS_ID           =  -226319
      FRAME_-226319_CENTER             =  -226
      TKFRAME_-226319_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226319_SPEC             = 'ANGLES'
      TKFRAME_-226319_UNITS            = 'DEGREES'
      TKFRAME_-226319_ANGLES           = ( 0.0,  0.0,  0.0  )
      TKFRAME_-226319_AXES             = ( 1,    2,    3    )

      FRAME_ROS_ROSINA_RTOF_URF        =  -226329
      FRAME_-226329_NAME               = 'ROS_ROSINA_RTOF_URF'
      FRAME_-226329_CLASS              =  4
      FRAME_-226329_CLASS_ID           =  -226329
      FRAME_-226329_CENTER             =  -226
      TKFRAME_-226329_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226329_SPEC             = 'ANGLES'
      TKFRAME_-226329_UNITS            = 'DEGREES'
      TKFRAME_-226329_ANGLES           = ( -90.0,  0.0,  0.0  )
      TKFRAME_-226329_AXES             = (   1,    2,    3    )

      FRAME_ROS_ROSINA_COPS_URF        =  -226339
      FRAME_-226339_NAME               = 'ROS_ROSINA_COPS_URF'
      FRAME_-226339_CLASS              =  4
      FRAME_-226339_CLASS_ID           =  -226339
      FRAME_-226339_CENTER             =  -226
      TKFRAME_-226339_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226339_SPEC             = 'ANGLES'
      TKFRAME_-226339_UNITS            = 'DEGREES'
      TKFRAME_-226339_ANGLES           = ( 0.0,  0.0,  0.0  )
      TKFRAME_-226339_AXES             = ( 1,    2,    3    )

   \begintext


COSIMA frames
========================================================================

   This section of the file contains the definitions of the COSIMA
   frames.


COSIMA Frame Tree
--------------------------------------

   The diagram below shows the COSIMA frame hierarchy.


                               "J2000" INERTIAL
           +-----------------------------------------------------+
           |                 |        |        |                 |
           |<-pck        ck->|        |        |<-pck       pck->|
           |                 |        |        |                 |
           V                 V        |        V                 V
       "67P/C-G_FIXED"  "67P/C-G_CK"  | "LUTETIA_FIXED"   "STEINS_FIXED"
         COMET BFXD      COMET BFXD   |  ASTEROID BFXD    ASTEROID BFXD
       ---------------  ------------  | --------------    --------------
                                      |
                                      |<-ck
                                      |
                                      V
                               "ROS_SPACECRAFT"
           +-----------------------------------------------------
           |                 |
           |                 |<-fixed
           |                 |
           |                 V
           |          "ROS_COSIMA_URF"
           |          ----------------
           |
           |<-fixed
           |
           V
     "ROS_COSIMA"
     ------------


COSIMA Frame
--------------------------------------

   The COSIMA frame is defined as follows:

      -  +Z axis points along the boresight of the particle entrance "FOV";

      -  +Y axis is nominally co-aligned with the s/c +Y axis;

      -  +X axis completes the right hand frame; it is nominally
         co-aligned with the s/c +X axis;

      -  the origin of the frame is located at the instrument "FOV"
         vertex.

   This diagram illustrates the COSIMA frame:


   +Z s/c side (science deck side) view:
   -------------------------------------

                               Lander
                                  _____
                                 /     \
                                |       |
                             ._____________.
                             |             |
                             |             |
                             |             | +Ysc
   o==/ /==================o |      o------->o==================/ /==o
     -Y Solar Array          |      |      |        +Y Solar Array
                             |o------> +Ycosima
                      COSIMA .|_____|______.
                              |`.   |   .'
                              |  .--V +Xsc
                              | '       `.
                              V __________\
                      +Xcosima    `.|.'                 +Zsc and +Zcosima
                                      HGA                   are out
                                                          of the page

   Nominally, the COSIMA frame is co-aligned with the s/c frame.

   \begindata

      FRAME_ROS_COSIMA                 =  -226140
      FRAME_-226140_NAME               = 'ROS_COSIMA'
      FRAME_-226140_CLASS              =  4
      FRAME_-226140_CLASS_ID           =  -226140
      FRAME_-226140_CENTER             =  -226
      TKFRAME_-226140_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226140_SPEC             = 'ANGLES'
      TKFRAME_-226140_UNITS            = 'DEGREES'
      TKFRAME_-226140_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-226140_AXES             = ( 1,   2,   3   )

   \begintext


COSIMA Unit Reference Frame
--------------------------------------

   This section implements the COSIMA Unit Reference Frame (URF) frame
   definition. While this frame was not specifically spelled out in
   [5], it is defined according to the rules outlined in the section
   7.3 of that document.

   \begindata

      FRAME_ROS_COSIMA_URF             =  -226145
      FRAME_-226145_NAME               = 'ROS_COSIMA_URF'
      FRAME_-226145_CLASS              =  4
      FRAME_-226145_CLASS_ID           =  -226145
      FRAME_-226145_CENTER             =  -226
      TKFRAME_-226145_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226145_SPEC             = 'ANGLES'
      TKFRAME_-226145_UNITS            = 'DEGREES'
      TKFRAME_-226145_ANGLES           = ( 0.0,   0.0,  90.0 )
      TKFRAME_-226145_AXES             = ( 2,     3,     1   )

   \begintext


MIDAS frames
========================================================================

   This section of the file contains the definitions of the MIDAS
   frames.


MIDAS Frame Tree
--------------------------------------

   The diagram below shows the MIDAS frame hierarchy.


                               "J2000" INERTIAL
           +-----------------------------------------------------+
           |                 |        |        |                 |
           |<-pck        ck->|        |        |<-pck       pck->|
           |                 |        |        |                 |
           V                 V        |        V                 V
       "67P/C-G_FIXED"  "67P/C-G_CK"  | "LUTETIA_FIXED"   "STEINS_FIXED"
         COMET BFXD      COMET BFXD   |  ASTEROID BFXD    ASTEROID BFXD
       ---------------  ------------  | --------------    --------------
                                      |
                                      |<-ck
                                      |
                                      V
                               "ROS_SPACECRAFT"
           +-----------------------------------------------------
           |                 |
           |                 |<-fixed
           |                 |
           |                 V
           |          "ROS_MIDAS_URF"
           |          ---------------
           |
           |<-fixed
           |
           V
     "ROS_MIDAS"
     -----------


MIDAS Frame
--------------------------------------

   The MIDAS frame is defined as follows:

      -  +Z axis points along the boresight of the particle entrance "FOV";

      -  +Y axis is nominally co-aligned with the s/c +Y axis;

      -  +X axis completes the right hand frame; it is nominally
         co-aligned with the s/c +X axis;

      -  the origin of the frame is located at the instrument "FOV"
         vertex.

   This diagram illustrates the MIDAS frame:


   +Z s/c side (science deck side) view:
   -------------------------------------

                               Lander
                                  _____
                                 /     \
                                |       |
                             ._____________.
                             |             |
                             |             |
                             |             | +Ysc
   o==/ /==================o |      o------->o==================/ /==o
     -Y Solar Array          |      |      |        +Y Solar Array
                             | MIDAS|o------> +Ymidas
                             .______||_____.
                               `.   ||  .'
                                 .--V| +Xsc
                               .'    |  `.
                              /______V +Xmidas
                                  `.|.'                 +Zsc and +Zmidas
                                      HGA                   are out
                                                          of the page

   Nominally, the MIDAS frame is co-aligned with the s/c frame.

   \begindata

      FRAME_ROS_MIDAS                  =  -226150
      FRAME_-226150_NAME               = 'ROS_MIDAS'
      FRAME_-226150_CLASS              =  4
      FRAME_-226150_CLASS_ID           =  -226150
      FRAME_-226150_CENTER             =  -226
      TKFRAME_-226150_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226150_SPEC             = 'ANGLES'
      TKFRAME_-226150_UNITS            = 'DEGREES'
      TKFRAME_-226150_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-226150_AXES             = ( 1,   2,   3   )

   \begintext


MIDAS Unit Reference Frame
--------------------------------------

   This section implements the MIDAS Unit Reference Frame (URF) frame
   definition. While this frame was not specifically spelled out in
   [5], it is defined according to the rules outlined in the section
   7.3 of that document.

   \begindata

      FRAME_ROS_MIDAS_URF              =  -226155
      FRAME_-226155_NAME               = 'ROS_MIDAS_URF'
      FRAME_-226155_CLASS              =  4
      FRAME_-226155_CLASS_ID           =  -226155
      FRAME_-226155_CENTER             =  -226
      TKFRAME_-226155_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226155_SPEC             = 'ANGLES'
      TKFRAME_-226155_UNITS            = 'DEGREES'
      TKFRAME_-226155_ANGLES           = ( 0.0,   0.0,  90.0 )
      TKFRAME_-226155_AXES             = ( 1,     3,     2   )

   \begintext


CONSERT frames
========================================================================

   This section of the file contains the definitions of the CONSERT
   frames.


CONSERT Frame Tree
--------------------------------------

   The diagram below shows the CONSERT frame hierarchy.


                               "J2000" INERTIAL
           +-----------------------------------------------------+
           |                 |        |        |                 |
           |<-pck        ck->|        |        |<-pck       pck->|
           |                 |        |        |                 |
           V                 V        |        V                 V
       "67P/C-G_FIXED"  "67P/C-G_CK"  | "LUTETIA_FIXED"   "STEINS_FIXED"
         COMET BFXD      COMET BFXD   |  ASTEROID BFXD    ASTEROID BFXD
       ---------------  ------------  | --------------    --------------
                                      |
                                      |<-ck
                                      |
                                      V
                               "ROS_SPACECRAFT"
           +-----------------------------------------------------
           |                 |
           |                 |<-fixed
           |                 |
           |                 V
           |          "ROS_CONSERT_URF"
           |          -----------------
           |
           |<-fixed
           |
           V
     "ROS_CONSERT"
     -------------


CONSERT Frame
--------------------------------------

   The CONSERT frame is defined as follows:

      -  +Z axis points along the "FOV" boresight;

      -  +Y axis is nominally co-aligned with the s/c +Y axis;

      -  +X axis completes the right hand frame; it is nominally
         co-aligned with the s/c +X axis;

      -  the origin of the frame is located at the instrument "FOV"
         vertex.

   This diagram illustrates the CONSERT frame:


   +Z s/c side (science deck side) view:
   -------------------------------------

                               Lander
                                  _____
                                 /     \
                                |       |
                             ._____________.
        CONSERT `.     .'    |             |
                  `. .'     +Yconsert      |
                    o------->|             | +Ysc
   o==/ /=========.'|`.====o |      o------->o==================/ /==o
     -Y Solar   .'  |  `.    |      |      |        +Y Solar Array
      Array         |        |      |      |
                    |        .______|______.
                    V          `.   |   .'
          +Xconsert              .--V +Xsc
                               .'       `.
                              /___________\
                                  `.|.'                 +Zsc and +Zconsert
                                      HGA                   are out
                                                          of the page

   Nominally, the CONSERT frame is co-aligned with the s/c frame.

   \begindata

      FRAME_ROS_CONSERT                =  -226160
      FRAME_-226160_NAME               = 'ROS_CONSERT'
      FRAME_-226160_CLASS              =  4
      FRAME_-226160_CLASS_ID           =  -226160
      FRAME_-226160_CENTER             =  -226
      TKFRAME_-226160_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226160_SPEC             = 'ANGLES'
      TKFRAME_-226160_UNITS            = 'DEGREES'
      TKFRAME_-226160_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-226160_AXES             = ( 1,   2,   3   )

   \begintext


CONSERT Unit Reference Frame
--------------------------------------

   This section implements the CONSERT Unit Reference Frame (URF) frame
   definition. While this frame was not specifically spelled out in
   [5], it is defined according to the rules outlined in the section
   7.3 of that document.

   \begindata

      FRAME_ROS_CONSERT_URF            =  -226165
      FRAME_-226165_NAME               = 'ROS_CONSERT_URF'
      FRAME_-226165_CLASS              =  4
      FRAME_-226165_CLASS_ID           =  -226165
      FRAME_-226165_CENTER             =  -226
      TKFRAME_-226165_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226165_SPEC             = 'ANGLES'
      TKFRAME_-226165_UNITS            = 'DEGREES'
      TKFRAME_-226165_ANGLES           = ( 0.0,   0.0,   0.0 )
      TKFRAME_-226165_AXES             = ( 1,     2,     3   )

   \begintext


NAVCAM Frames
========================================================================

   This section of the file contains the definitions of the NAVCAM
   frames.


NAVCAM Frame Tree
--------------------------------------

   The diagram below shows the NAVCAM frame hierarchy.


                               "J2000" INERTIAL
           +-----------------------------------------------------+
           |                 |        |        |                 |
           |<-pck        ck->|        |        |<-pck       pck->|
           |                 |        |        |                 |
           V                 V        |        V                 V
       "67P/C-G_FIXED"  "67P/C-G_CK"  | "LUTETIA_FIXED"   "STEINS_FIXED"
         COMET BFXD      COMET BFXD   |  ASTEROID BFXD    ASTEROID BFXD
       ---------------  ------------  | --------------    --------------
                                      |
                                      |<-ck
                                      |
                                      V
                               "ROS_SPACECRAFT"
           +-----------------------------------------------------+
           |                 |                 |                 |
           |                 |<-fixed          |<-fixed          |
           |                 |                 |                 |
           |                 V                 V                 |
           |       "ROS_NAVCAM-A_URF"    "ROS_NAVCAM-B_URF"      |
           |       ------------------    ------------------      |
           |                                                     |
           |<-fixed                                              |<-fixed
           |                                                     |
           V                                                     V
     "ROS_NAVCAM-A"                                       "ROS_NAVCAM-B"
     --------------                                       --------------


NAVCAM Camera Frames
--------------------------------------

   The NAVCAM camera frames -- ROS_NAVCAM-A and ROS_NAVCAM-B -- are
   defined as follows:

      -  +Z axis points along the camera boresight;

      -  +X axis is parallel to the apparent image columns; it is
         nominally co-aligned with the s/c +X axis;

      -  +Y axis completes the right hand frame; it is nominally
         parallel the to the apparent image lines and co-aligned with
         the s/c +Y axis;

      -  the origin of the frame is located at the camera focal point.

   This diagram illustrates the NAVCAM camera frames:


   +Z s/c side (science deck side) view:
   -------------------------------------

                               Lander
                                  _____
                                 /     \
                                |       |
                             ._____________.
                             |         +Yncb +Ynca
                             |     o-o----->->
                             |     | |     | +Ysc
   o==/ /==================o |     |o|------>o==================/ /==o
     -Y Solar Array          |     |||     |        +Y Solar Array
                             +Xncb V|V +Xnca
                             .______|______.
                               `.   |   .'
                                 .--V +Xsc
                          HGA  .'       `.
                              /___________\
                                  `.|.'                 +Zsc, +Znca, and
                                                         +Zncb are out
                                                          of the page

   Nominally, the NAVCAM camera frames are co-aligned with the s/c
   frame.

   The actual NAVCAM-A boresight direction is specified in [7] as an
   offset from the s/c +Z axis by the following two angles:

      Offset from Z s/c: x (deg) =  -0.02678
      Offset from Z s/c: y (deg) =  -0.17210

   while the actual NAVCAM-B boresight direction is specified by:

      Offset from Z s/c: x (deg) =   0.03003
      Offset from Z s/c: y (deg) =   0.09747

   The first of the two angles -- ``Offset from Z s/c: x'' -- is the
   angle between the projection of the boresight onto the s/c XZ plane
   and the s/c +Z axis, measured positive from the s/c +Z toward the
   s/c +X axis. The second of the two angles -- ``Offset from Z s/c:
   y'' -- is the angle between the projection of the boresight onto the
   s/c YZ plane and the s/c +Z axis, measured positive from the s/c +Z
   toward the s/c +Y axis.

   The following set of rotations can be applied to the s/c axes to
   align the NAVCAM-A frame's +Z axis with the boresight defined by the
   angles above (rotation about +Z is not defined in [7] and assumed to
   be zero in this set of rotations):

      Msc->nca = [0.0]z * [-0.02677988]y * [0.17210]x

   These rotations can be applied to the s/c axes to align the
   NAVCAM-B frame's +Z axis with the boresight defined by the angles
   above (rotation about +Z is not defined in [7] and assumed to be
   zero in this set of rotations):

      Msc->ncb = [0.0]z * [0.03002996]y * [-0.09747]x

   The NAVCAM-A and NAVCAM-B rotations shown above were provided in 
   the FK versions 0.4 (March 2005) to 2.4 (November 2015).

   According to [14] the following NAVCAM alignments were derived from
   calibrations done in 2008:

      ALI_CAM_1 =

      |  0.9999986610169094000   0.0015268035484500271  0.0005889272559640015 |
      | -0.0015286381087705047   0.9999939415514822000  0.0031273192774521727 |
      | -0.0005841488858085904  -0.0031282153466713016  0.9999949365065925000 |

      ALI_CAM_2 =

      |  0.999998236851883       0.001874025444133808  -0.0001196735573734238 |
      | -0.001874272415777741    0.999996042598358     -0.002098068286197499  |
      |  0.000115741250425227    0.002098288887839833   0.999997791891415     |

   These alignments are incorporated in the frame definitions below.

   \begindata

      FRAME_ROS_NAVCAM-A               =  -226170
      FRAME_-226170_NAME               = 'ROS_NAVCAM-A'
      FRAME_-226170_CLASS              =  4
      FRAME_-226170_CLASS_ID           =  -226170
      FRAME_-226170_CENTER             =  -226
      TKFRAME_-226170_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226170_SPEC             = 'MATRIX'
      TKFRAME_-226170_MATRIX           = ( 

         0.9999986610169094000,  0.0015268035484500271, 0.0005889272559640015,
        -0.0015286381087705047,  0.9999939415514822000, 0.0031273192774521727,
        -0.0005841488858085904, -0.0031282153466713016, 0.9999949365065925000

                                          )

      FRAME_ROS_NAVCAM-B               =  -226180
      FRAME_-226180_NAME               = 'ROS_NAVCAM-B'
      FRAME_-226180_CLASS              =  4
      FRAME_-226180_CLASS_ID           =  -226180
      FRAME_-226180_CENTER             =  -226
      TKFRAME_-226180_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226180_SPEC             = 'MATRIX'
      TKFRAME_-226180_MATRIX           = ( 

         0.9999982368518830,     0.001874025444133808, -0.0001196735573734238,
        -0.001874272415777741,   0.9999960425983579,   -0.002098068286197499,
         0.0001157412504252270,  0.002098288887839833,  0.9999977918914150

                                         )

   \begintext


NAVCAM Unit Reference Frames
--------------------------------------

   This section implements the NAVCAM Unit Reference Frames (URF) frame
   definitions provided in [5].

   \begindata

      FRAME_ROS_NAVCAM-A_URF           =  -226175
      FRAME_-226175_NAME               = 'ROS_NAVCAM-A_URF'
      FRAME_-226175_CLASS              =  4
      FRAME_-226175_CLASS_ID           =  -226175
      FRAME_-226175_CENTER             =  -226
      TKFRAME_-226175_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226175_SPEC             = 'ANGLES'
      TKFRAME_-226175_UNITS            = 'DEGREES'
      TKFRAME_-226175_ANGLES           = ( 0.0,  0.0,  0.0  )
      TKFRAME_-226175_AXES             = ( 1,    2,    3    )

      FRAME_ROS_NAVCAM-B_URF           =  -226185
      FRAME_-226185_NAME               = 'ROS_NAVCAM-B_URF'
      FRAME_-226185_CLASS              =  4
      FRAME_-226185_CLASS_ID           =  -226185
      FRAME_-226185_CENTER             =  -226
      TKFRAME_-226185_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226185_SPEC             = 'ANGLES'
      TKFRAME_-226185_UNITS            = 'DEGREES'
      TKFRAME_-226185_ANGLES           = ( 0.0,  0.0,  0.0  )
      TKFRAME_-226185_AXES             = ( 1,    2,    3    )

   \begintext


GIADA frames
========================================================================

   This section of the file contains the definitions of the GIADA
   frames.


GIADA Frame Tree
--------------------------------------

   The diagram below shows the GIADA frame hierarchy.


                               "J2000" INERTIAL
           +-----------------------------------------------------+
           |                 |        |        |                 |
           |<-pck        ck->|        |        |<-pck       pck->|
           |                 |        |        |                 |
           V                 V        |        V                 V
       "67P/C-G_FIXED"  "67P/C-G_CK"  | "LUTETIA_FIXED"   "STEINS_FIXED"
         COMET BFXD      COMET BFXD   |  ASTEROID BFXD    ASTEROID BFXD
       ---------------  ------------  | --------------    --------------
                                      |
                                      |<-ck
                                      |
                                      V
                               "ROS_SPACECRAFT"
           +-----------------------------------------------------+
           |                 |                 |                 |
           |<-fixed          |                 |                 |<-fixed
           |                 |                 |                 |
           |                 |                 |                 |
     "ROS_GIADA_GDS"         |                 |          "ROS_GIADA_URF"
     ---------------         |                 |          --------------
                             |                 |
                             |<-fixed          |<-fixed
                             |                 |
                             V                 V
                      "ROS_GIADA_IS"    "ROS_GIADA_MBS1..5"
                      --------------    -------------------


GIADA Frame
--------------------------------------

   The GIADA GDS, GIADA IS, and GIADA MBS1 .. MBS5 frames are defined
   as follows:

      -  +Z axis points along the particle entrance FOV boresight;

      -  +Y axis is nominally parallel to the s/c XY plane and points as
         shown on the diagrams below;

      -  +X axis completes the right hand frame;

      -  the origin of the frame is located at the FOV focal point.

   This diagram illustrates the GIADA GDS, IS, and MBS5 frames:


   +Z s/c side (science deck side) view:
   -------------------------------------

                               Lander
                                  _____
                                 /     \
                                |       |
                             ._____________.
                             |             |
                          GIADA o------> +Ygds,+Yis,+Ymbs5
                             |  |          |
   o==/ /==================o |  |   o------->o==================/ /==o
     -Y Solar Array          |  |   |      | +Ysc   +Y Solar Array
                             |  |   |
                             .__V___|______.
                            +Xgds   |   .'
                            +Xis   -V +Xsc
                            +Xmbs5      `.
                              /___________\
                                  `.|.'                 +Zsc, +Zgds, +Zis,
                                      HGA               and +Zmbs5 are out
                                                          of the page


   This diagram illustrates the GIADA MBS 1..4 frames:


   +Z s/c side (science deck side) view:
   -------------------------------------

                          +Zmbs3
                                ^ +Ymbs2
                                |^ ____
                                ||     \  Lander
                                ||      |
                  +Ymbs3     .__||_________.
                       <<------43|       +Zmbs2
                 +Zmbs4      | | 2-------> |
                             | | 1-------> +Ymbs1
   o==/ /==================o | | |  o------->o==================/ /==o
     -Y Solar Array          | | |  |      | +Ysc   +Y Solar Array
                             | V |  |      |
                        +Ymbs4 __|__|______.
                               `.V  |   .'               +Zmbs* are pointed
                           +Zmbs1.--V +Xsc            20 deg above the page.
                               .'       `.
                              /___________\           +Xmbs* are roughly into
                                  `.|.'                      the page

                                                      +Zsc is out of the page

   Nominally, the GIADA GDS, GIADA IS, and GIADA MBS5 frames are co-aligned
   with the s/c frame while the GIADA MBS1, GIADA MBS2, GIADA MBS3, and
   GIADA MBS4 frames are rotated from it first by 0, 90, 180 or 270 degrees
   about Z, and then by 70 degrees about Y.

   \begindata

      FRAME_ROS_GIADA_GDS              =  -226410
      FRAME_-226410_NAME               = 'ROS_GIADA_GDS'
      FRAME_-226410_CLASS              =  4
      FRAME_-226410_CLASS_ID           =  -226410
      FRAME_-226410_CENTER             =  -226
      TKFRAME_-226410_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226410_SPEC             = 'ANGLES'
      TKFRAME_-226410_UNITS            = 'DEGREES'
      TKFRAME_-226410_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-226410_AXES             = ( 1,   2,   3   )

      FRAME_ROS_GIADA_IS               =  -226420
      FRAME_-226420_NAME               = 'ROS_GIADA_IS'
      FRAME_-226420_CLASS              =  4
      FRAME_-226420_CLASS_ID           =  -226420
      FRAME_-226420_CENTER             =  -226
      TKFRAME_-226420_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226420_SPEC             = 'ANGLES'
      TKFRAME_-226420_UNITS            = 'DEGREES'
      TKFRAME_-226420_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-226420_AXES             = ( 1,   2,   3   )

      FRAME_ROS_GIADA_MBS1             =  -226431
      FRAME_-226431_NAME               = 'ROS_GIADA_MBS1'
      FRAME_-226431_CLASS              =  4
      FRAME_-226431_CLASS_ID           =  -226431
      FRAME_-226431_CENTER             =  -226
      TKFRAME_-226431_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226431_SPEC             = 'ANGLES'
      TKFRAME_-226431_UNITS            = 'DEGREES'
      TKFRAME_-226431_ANGLES           = ( 0.0, 0.0, -70.0 )
      TKFRAME_-226431_AXES             = ( 1,   3,   2   )

      FRAME_ROS_GIADA_MBS2             =  -226432
      FRAME_-226432_NAME               = 'ROS_GIADA_MBS2'
      FRAME_-226432_CLASS              =  4
      FRAME_-226432_CLASS_ID           =  -226432
      FRAME_-226432_CENTER             =  -226
      TKFRAME_-226432_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226432_SPEC             = 'ANGLES'
      TKFRAME_-226432_UNITS            = 'DEGREES'
      TKFRAME_-226432_ANGLES           = ( 0.0, -90.0, -70.0 )
      TKFRAME_-226432_AXES             = ( 1,   3,   2   )

      FRAME_ROS_GIADA_MBS3             =  -226433
      FRAME_-226433_NAME               = 'ROS_GIADA_MBS3'
      FRAME_-226433_CLASS              =  4
      FRAME_-226433_CLASS_ID           =  -226433
      FRAME_-226433_CENTER             =  -226
      TKFRAME_-226433_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226433_SPEC             = 'ANGLES'
      TKFRAME_-226433_UNITS            = 'DEGREES'
      TKFRAME_-226433_ANGLES           = ( 0.0, -180.0, -70.0 )
      TKFRAME_-226433_AXES             = ( 1,   3,   2   )

      FRAME_ROS_GIADA_MBS4             =  -226434
      FRAME_-226434_NAME               = 'ROS_GIADA_MBS4'
      FRAME_-226434_CLASS              =  4
      FRAME_-226434_CLASS_ID           =  -226434
      FRAME_-226434_CENTER             =  -226
      TKFRAME_-226434_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226434_SPEC             = 'ANGLES'
      TKFRAME_-226434_UNITS            = 'DEGREES'
      TKFRAME_-226434_ANGLES           = ( 0.0, -270.0, -70.0 )
      TKFRAME_-226434_AXES             = ( 1,   3,   2   )

      FRAME_ROS_GIADA_MBS5             =  -226435
      FRAME_-226435_NAME               = 'ROS_GIADA_MBS5'
      FRAME_-226435_CLASS              =  4
      FRAME_-226435_CLASS_ID           =  -226435
      FRAME_-226435_CENTER             =  -226
      TKFRAME_-226435_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226435_SPEC             = 'ANGLES'
      TKFRAME_-226435_UNITS            = 'DEGREES'
      TKFRAME_-226435_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-226435_AXES             = ( 1,   2,   3   )

   \begintext


GIADA Unit Reference Frame
--------------------------------------

   This section implements the GIADA Unit Reference Frame (URF) frame
   definition. While this frame was not specifically spelled out in
   [5], it is defined according to the rules outlined in the section
   7.3 of that document.

   \begindata

      FRAME_ROS_GIADA_URF              =  -226440
      FRAME_-226440_NAME               = 'ROS_GIADA_URF'
      FRAME_-226440_CLASS              =  4
      FRAME_-226440_CLASS_ID           =  -226440
      FRAME_-226440_CENTER             =  -226
      TKFRAME_-226440_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226440_SPEC             = 'ANGLES'
      TKFRAME_-226440_UNITS            = 'DEGREES'
      TKFRAME_-226440_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-226440_AXES             = ( 2,   1,   3   )

   \begintext


RPC frames
========================================================================

   This section of the file contains the definitions of the RPC frames.


RPC Frame Tree
--------------------------------------

   The diagram below shows the RPC frame hierarchy.


          "45P/H-M-P_CSO"
          ---------------
           ^
           |<-dyn
           |
           | "2867/STEINS_CSO"
           | -----------------
           |  ^
           |  |<-dyn
           |  |
           |  | "21/LUTETIA_CSEQ"
           |  | -----------------
           |  |  ^
           |  |  |<-dyn
           |  |  |
           |  |  | "21/LUTETIA_CSO"
           |  |  | ----------------
           |  |  |  ^
           |  |  |  |<-dyn
           |  |  |  |
           |  |  |  | "67P/C-G_CSEQ"
           |  |  |  | --------------
           |  |  |  |  ^
           |  |  |  |  |<-dyn
           |  |  |  |  |
           |  |  |  |  | "67P/C-G_CSO"
           |  |  |  |  | -------------
           |  |  |  |  |  ^
           |  |  |  |  |  |<-dyn
           |  |  |  |  |  |
           |  |  |  |  |  |
           |  |  |  |  |  |    "J2000" INERTIAL
           +-----------------------------------------------------+
           |                 |        |        |                 |
           |<-pck        ck->|        |        |<-pck       pck->|
           |                 |        |        |                 |
           V                 V        |        V                 V
       "67P/C-G_FIXED"  "67P/C-G_CK"  | "LUTETIA_FIXED"   "STEINS_FIXED"
         COMET BFXD      COMET BFXD   |  ASTEROID BFXD    ASTEROID BFXD
       ---------------  ------------  | --------------    --------------
                                      |
                                      |<-ck
                                      |
                                      V
                               "ROS_SPACECRAFT"
           +-----------------------------------------------------+
           |          |          |         |          |          |
           |   fixed->|          |         |          |<-fixed   |
           |          |          |         |          |          |
           |          V          |         |          V          |
           |  "ROS_RPC_IES"      |         |      "ROS_RPC_ICA"  |
           |  -------------      |         |      -------------  |
           |                     |         |                     |
           |<-fixed              |         |                     |<-fixed
           |                     |         |                     |
           V                     |         |                     V
     "ROS_RPC_IES_URF"           |         |            "ROS_RPC_ICA_URF"
     -----------------           |         |            -----------------
                                 |         |
                          fixed->|         |<-fixed
                                 |         |
                                 V         V
                      "ROS_RPC_BOOM1"   "ROS_RPC_BOOM2"
           +-------------------------   -------------------------+
           |                     |         |                     |
           |<-fixed       fixed->|         |<-fixed       fixed->|
           |                     |         |                     |
           V                     V         V                     V
     "ROS_RPC_MIP"     "ROS_RPC_LAP1"   "ROS_RPC_LAP2"  "ROS_RPC_MAG_OB/IB"
     -------------     --------------   --------------  -------------------


RPC IES and ICA Frames
--------------------------------------

   The RPC IES sensor frame -- ROS_RPC_IES -- is defined as follows:

      -  +Z axis points along the instrument's FOV symmetry axis,
         toward the FOV side of the sensor unit;

      -  +Y axis is parallel to the instrument mounting plate plane
         (s/c XY plane) and points toward -X/+Y quadrant of the s/c
         XY plane;

      -  +X axis completes the right hand frame;

      -  the origin of the frame is located at the intersection of the
         FOV symmetry axis and the FOV focal plane.

   The RPC ICA sensor frame -- ROS_RPC_ICA -- is defined as follows:

      -  +Z axis points along the instrument's FOV symmetry axis,
         toward the FOV side of the sensor unit;

      -  +X axis is parallel to the instrument mounting plate plane
         (s/c XY plane) and nominally points along the s/c +X axis;

      -  +Y axis completes the right hand frame;

      -  the origin of the frame is located at the intersection of the
         FOV symmetry axis and the FOV focal plane.

   Defining IES and ICA sensor frame in this fashion allows easier
   specification of the sensor sector view directions and boundaries
   using polar coordinates relative to these frames.

   This diagram illustrates the RPC IES and ICA sensor frames:


   +Z s/c side (science deck side) view:
   -------------------------------------

                               Lander
                                  _____
                                 /     \
                                |       |
                             ._____________.
                             |             |
                             |             |
                             |  +Zsc       | +Ysc  +Yies
   o==/ /==================o |      o------->o== ^ =============/ /==o
     -Y Solar Array          |      |      |x------->
                             |      |      ||.'      +Zica
                             .______|_____ x|
                               `.   |   .   |.
                                 .--V +Xsc  | `.
                          HGA  .'       `   V   V +Zies
                              /_________ +Xica
                                  `.|.'          +Zsc points out of the page

                                                 +Yica points into the page

                                                +Zies points 45 deg above the
                                                       s/c XY plane.

                                                +Xies points 45 deg below the
                                                       s/c XY plane.

   As shown on the diagram, two rotations are needed to co-align the s/c
   frame with the IES sensor frame: first by +45 degrees about +Z,
   then by +45 about +Y.

   Only one rotation is needed to co-align the s/c frame with
   the ICA sensor frame: by -90 degrees about +X.

   \begindata

      FRAME_ROS_RPC_IES                =  -226520
      FRAME_-226520_NAME               = 'ROS_RPC_IES'
      FRAME_-226520_CLASS              =  4
      FRAME_-226520_CLASS_ID           =  -226520
      FRAME_-226520_CENTER             =  -226
      TKFRAME_-226520_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226520_SPEC             = 'ANGLES'
      TKFRAME_-226520_UNITS            = 'DEGREES'
      TKFRAME_-226520_ANGLES           = ( 0.0, -45.0, -45.0 )
      TKFRAME_-226520_AXES             = ( 1,     3,     2   )

      FRAME_ROS_RPC_ICA                =  -226530
      FRAME_-226530_NAME               = 'ROS_RPC_ICA'
      FRAME_-226530_CLASS              =  4
      FRAME_-226530_CLASS_ID           =  -226530
      FRAME_-226530_CENTER             =  -226
      TKFRAME_-226530_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226530_SPEC             = 'ANGLES'
      TKFRAME_-226530_UNITS            = 'DEGREES'
      TKFRAME_-226530_ANGLES           = ( 90.0,  0.0,   0.0 )
      TKFRAME_-226530_AXES             = (  1,    3,     2   )

   \begintext


RPC IES and ICA Unit Reference Frames
--------------------------------------

   This section implements the IES and ICA Unit Reference Frame (URF)
   frame definitions. While these frames were not specifically spelled
   out in [5], they are defined according to the rules outlined in the
   section 7.3 of that document.

   \begindata

      FRAME_ROS_RPC_IES_URF            =  -226525
      FRAME_-226525_NAME               = 'ROS_RPC_IES_URF'
      FRAME_-226525_CLASS              =  4
      FRAME_-226525_CLASS_ID           =  -226525
      FRAME_-226525_CENTER             =  -226
      TKFRAME_-226525_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226525_SPEC             = 'ANGLES'
      TKFRAME_-226525_UNITS            = 'DEGREES'
      TKFRAME_-226525_ANGLES           = ( 0.0, -45.0, 0.0 )
      TKFRAME_-226525_AXES             = ( 2,     3,   1   )

      FRAME_ROS_RPC_ICA_URF            =  -226535
      FRAME_-226535_NAME               = 'ROS_RPC_ICA_URF'
      FRAME_-226535_CLASS              =  4
      FRAME_-226535_CLASS_ID           =  -226535
      FRAME_-226535_CENTER             =  -226
      TKFRAME_-226535_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226535_SPEC             = 'ANGLES'
      TKFRAME_-226535_UNITS            = 'DEGREES'
      TKFRAME_-226535_ANGLES           = ( 0.0, -90.0, 0.0 )
      TKFRAME_-226535_AXES             = ( 2,     3,   1   )

   \begintext


RPC Boom and Boom-mounted Sensor Frames
---------------------------------------

   The RPC Boom 1 and 2 frames -- ROS_RPC_BOOM1 and ROS_RPC_BOOM2 -- are
   defined as follows:

      -  +Z axis is parallel to the boom and points away from the
         spacecraft;

      -  +X axis is parallel to the MIP antennas (for Boom 1) or
         MAG center axis (for Boom 2) and points away from the boom;

      -  +Y axis completes the right hand frame;

      -  the origin of the frame is located at the boom pivot point.

   All boom-mounted sensor frames (except those for the MAG sensors) --
   ROS_RPC_MIP, ROS_RPC_LAP1, and ROS_RPC_LAP2 -- are defined to be
   co-aligned with the frame of the boom on which the sensor is
   mounted.

   This diagram illustrates the RPC Boom 1 and 2 frames for booms in
   deployed position:

   +Z s/c side (science deck side) view:
   -------------------------------------

                                       +Zboom2
                               Lander     ^
                                  _____   |  ^ +Xboom2
                                 /     \  | .
                                |       | |.
                             .____________o----> +Yboom2
                             |             |x----> +Zboom1
                             |             ||
                             |  +Zsc       ||+Ysc
   o==/ /==================o |      o------->o==================/ /==o
     -Y Solar Array          |      |      ||         +Y Solar Array
                             |      |      |V
                             .______|______. +Xboom1
                               `.   |   .'
                                 .--V +Xsc
                          HGA  .'       `.
                              /___________\
                                  `.|.'         +Zsc points out of the page

                                              +Zboom1 points 45 deg above the
                                                      s/c XY plane.

                                              +Yboom1 points 45 deg below the
                                                       s/c XY plane.

                                              +Zboom2 points ~40 deg below
                                                s/c XY plane, slightly
                                                 toward s/c +Y axis.

                                              +Xboom2 points ~50 deg above
                                                 s/c XY plane, slightly
                                                   toward s/c +Y axis.


   As shown on the diagram, a single rotation of -45 degrees about +X
   is needed to co-align the s/c frame with the Boom 1 frame in
   deployed configuration.

   Nominally two rotations are needed to co-align the s/c frame with
   the Boom 2 frame in stowed configuration: first by -90.0
   degrees about +Y, then by +90.0 degrees about +X.

   Nominally three rotations are needed to co-align the s/c frame with
   the Boom 2 frame in deployed configuration: first by -126.958
   degrees about +Y, then by -4.590 degrees about +X, and finally by
   +15.358 degrees about +Z. (These angles were derived the boom pivot
   axis direction angles and boom deployment angle specified in [6].)

   Since both, pre- and post- deployment orientation of the Boom 2 is
   essential for MAG data analysis, Boom 2 frame is defined as a
   CK-based frame with its orientation provided in CK files.

   \begindata

      FRAME_ROS_RPC_BOOM1              =  -226560
      FRAME_-226560_NAME               = 'ROS_RPC_BOOM1'
      FRAME_-226560_CLASS              =  4
      FRAME_-226560_CLASS_ID           =  -226560
      FRAME_-226560_CENTER             =  -226
      TKFRAME_-226560_RELATIVE         = 'ROS_SPACECRAFT'
      TKFRAME_-226560_SPEC             = 'ANGLES'
      TKFRAME_-226560_UNITS            = 'DEGREES'
      TKFRAME_-226560_ANGLES           = ( 0.0, 0.0, 45.0 )
      TKFRAME_-226560_AXES             = ( 3,   2,    1   )

      FRAME_ROS_RPC_BOOM2              =  -226570
      FRAME_-226570_NAME               = 'ROS_RPC_BOOM2'
      FRAME_-226570_CLASS              =  3
      FRAME_-226570_CLASS_ID           =  -226570
      FRAME_-226570_CENTER             =  -226
      CK_-226570_SCLK                  =  -226
      CK_-226570_SPK                   =  -226

      FRAME_ROS_RPC_MIP                =  -226550
      FRAME_-226550_NAME               = 'ROS_RPC_MIP'
      FRAME_-226550_CLASS              =  4
      FRAME_-226550_CLASS_ID           =  -226550
      FRAME_-226550_CENTER             =  -226
      TKFRAME_-226550_RELATIVE         = 'ROS_RPC_BOOM1'
      TKFRAME_-226550_SPEC             = 'ANGLES'
      TKFRAME_-226550_UNITS            = 'DEGREES'
      TKFRAME_-226550_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-226550_AXES             = ( 2,   3,   1   )

      FRAME_ROS_RPC_LAP1               =  -226511
      FRAME_-226511_NAME               = 'ROS_RPC_LAP1'
      FRAME_-226511_CLASS              =  4
      FRAME_-226511_CLASS_ID           =  -226511
      FRAME_-226511_CENTER             =  -226
      TKFRAME_-226511_RELATIVE         = 'ROS_RPC_BOOM1'
      TKFRAME_-226511_SPEC             = 'ANGLES'
      TKFRAME_-226511_UNITS            = 'DEGREES'
      TKFRAME_-226511_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-226511_AXES             = ( 2,   3,   1   )

      FRAME_ROS_RPC_LAP2               =  -226512
      FRAME_-226512_NAME               = 'ROS_RPC_LAP2'
      FRAME_-226512_CLASS              =  4
      FRAME_-226512_CLASS_ID           =  -226512
      FRAME_-226512_CENTER             =  -226
      TKFRAME_-226512_RELATIVE         = 'ROS_RPC_BOOM2'
      TKFRAME_-226512_SPEC             = 'ANGLES'
      TKFRAME_-226512_UNITS            = 'DEGREES'
      TKFRAME_-226512_ANGLES           = ( 0.0, 0.0, 0.0 )
      TKFRAME_-226512_AXES             = ( 2,   3,   1   )

   \begintext

   The MAG OB and IB frames -- ROS_RPC_BOOM1 and ROS_RPC_BOOM2 -- are
   defined as follows:

      -  +Y axis is parallel to the boom and points from the sensor
         toward the boom deployment hinge; this axis is designated "V"
         in the instrument documentation and nominally points in the
         direction opposite to the Boom 2 +Z axis;

      -  +Z axis is normal to the boom and point from the sensor toward
         the boom; this axis is designated "W" in the instrument
         documentation and nominally points in the direction opposite
         to the Boom 2 +X axis;

      -  +X axis completes the right hand frame; this axis is
         designated "U" in the instrument documentation nominally
         points in the same direction as the Boom 2 +Y axis;

      -  the origin of the frame is located at the geometric center of
         the sensor.

   This diagram illustrates the RPC MAG OB and IB frames:

   +Z s/c side view (Boom 2 is shown in stowed position):
   ------------------------------------------------------

                         +Xmag ^          ^ +Yboom2
                               |          |
                               |+Ymag     |
                             ._x--->__<---o
                             |      +Zboom2|
                             |             |
                             |  +Zsc       | +Ysc
   o==/ /==================o |      o------->o==================/ /==o
     -Y Solar Array          |      |      |          +Y Solar Array
                             |      |      |
                             .______|______.
                               `.   |   .'
                                 .--V +Xsc
                          HGA  .'       `.
                              /___________\
                                  `.|.'         +Zsc and +Xboom2 point out
                                                        of the page

                                                +Zmag points into the page


   As shown on the diagram, nominally two rotations are needed to
   co-align the Boom 2 frame with the MAG OB/MAG IB frames: first by
   +90 degrees about Z, then by -90 degrees about X.

   The actual alignments, computed from the MAG OB and IB frames' U, V,
   and W axes directions in the s/c frame provided by  Dr. Ingo Richter
   [8], are as follows:

      Mboom2->mag_ob = [-90.23422236]x * [+89.94424999]z * [+0.14507999]x

      Mboom2->mag_ib = [-90.28478858]x * [+89.49714229]z * [+0.11719143]x

   The MAG OB and IB frame definitions below incorporate these
   transformations.

   \begindata

      FRAME_ROS_RPC_MAG_OB             =  -226541
      FRAME_-226541_NAME               = 'ROS_RPC_MAG_OB'
      FRAME_-226541_CLASS              =  4
      FRAME_-226541_CLASS_ID           =  -226541
      FRAME_-226541_CENTER             =  -226
      TKFRAME_-226541_RELATIVE         = 'ROS_RPC_BOOM2'
      TKFRAME_-226541_SPEC             = 'ANGLES'
      TKFRAME_-226541_UNITS            = 'DEGREES'
      TKFRAME_-226541_ANGLES           = ( -0.14507999, -89.94424999, +90.23422236  )
      TKFRAME_-226541_AXES             = ( 1,   3,   1   )

      FRAME_ROS_RPC_MAG_IB             =  -226542
      FRAME_-226542_NAME               = 'ROS_RPC_MAG_IB'
      FRAME_-226542_CLASS              =  4
      FRAME_-226542_CLASS_ID           =  -226542
      FRAME_-226542_CENTER             =  -226
      TKFRAME_-226542_RELATIVE         = 'ROS_RPC_BOOM2'
      TKFRAME_-226542_SPEC             = 'ANGLES'
      TKFRAME_-226542_UNITS            = 'DEGREES'
      TKFRAME_-226542_ANGLES           = ( -0.11719143, -89.49714229, +90.28478858 )
      TKFRAME_-226542_AXES             = ( 1,   3,   1   )

   \begintext


Rosetta Lander Frames
========================================================================

   This section of the file contains the definitions of the Rosetta
   topocentric, lander and instrument frames.


Rosetta Lander Frame Tree
--------------------------------------

   The diagram below shows the Rosetta Lander and its instruments frame
   hierarchy.


                               "J2000" INERTIAL
           +-----------------------------------------------------+
           |                 |                 |                 |
           |<-ck             |                 |                 |<-pck
           |                 |                 |                 |
           V                 |                 |                 V
    "ROS_SPACECRAFT"         |                 |            "IAU_EARTH"
     ---------------         |<-pck            |<-ck      EARTH BODY-FIXED
                             |                 |          ----------------
                             V                 V
                      "67P/C-G_FIXED"     "67P/C-G_CK"
                        COMET BFXD         COMET BFXD
                      ---------------     ------------
                                 .         .
                          fixed->.         .<-fixed
                                 .         .
                                 V         V
                              "ROS_LANDER_TOPO"
                              -----------------
                                      |
                                      |<-ck
                                      |
                                      V
                                 "ROS_LANDER"
                +-------------------------------------------+
                |                     |                     |
                |<-fixed              |<-fixed              |
                |                     |                     |
                V                     V                     V
    "ROS_LANDER_CIVA_P_#"     "ROS_LANDER_DIM_#"     "ROS_LANDER_ROLIS"
    ---------------------     ------------------     ------------------


Rosetta Local Level frame
--------------------------------------

   The topocentric frame at the landing site -- ROS_LANDER_TOPO -- is
   defined as follows:

      -  +Z axis is the outward normal (zenith) at the landing site;

      -  +X axis points at the local north;

      -  +Y completes the right hand frame;

      -  the origin of the frame is on the ground below center of the
         lander

   The orientation of the frame is given relative to the comet fixed
   rotating frame '67P/C-G_FIXED' and is determined by the landing site
   coordinates.

   The transformation from 'ROS_LANDER_TOPO' frame to '67P/C-G_FIXED'
   frame is a 3-2-3 rotation with defined angles as the negative of the
   site longitude, the negative of the site colatitude, 180 degrees.

   Until the target landing site is selected, the rotation angles in
   the frame transformation below are set for an arbitrarily chosen
   placeholder landing site at

        Lon = 0 degrees East
        Lat = 0 degrees North

   These keywords implement the frame definition.

   \begindata

      FRAME_ROS_LANDER_TOPO            =  -226999
      FRAME_-226999_NAME               = 'ROS_LANDER_TOPO'
      FRAME_-226999_CLASS              =  4
      FRAME_-226999_CLASS_ID           =  -226999
      FRAME_-226999_CENTER             =  -226999
      TKFRAME_-226999_RELATIVE         = '67P/C-G_FIXED'
      TKFRAME_-226999_SPEC             = 'ANGLES'
      TKFRAME_-226999_UNITS            = 'DEGREES'
      TKFRAME_-226999_ANGLES           = (   0, -90, 180 )
      TKFRAME_-226999_AXES             = (   3,   2,   3 )

   \begintext


Rosetta Lander Frame
--------------------------------------

   The lander frame -- ROS_LANDER -- is defined by the lander design as
   follows:

      -  +X axis is parallel to the lander baseplate and points from
         the lander backside toward the CIVA-P 3 camera mounted in
         the middle of the front solar hood panel;

      -  +Z axis is perpendicular to the lander baseplate and points
         from the lander baseplate towards the lander top plate;

      -  +Y axis completes the right handed frame;

      -  the origin of the frame is in the middle of the baseplate inner
         surface backside.

   These diagrams illustrate the lander frame:

   +Z lander side (top) view:
   --------------------------
                   .o
                o'\\
                   \\
                    \\
                     \\
                      \\
            +Ylnd      \\
                  ^ ----------------o-.
                  | -. SD2             \
                  | -'                  o
                  |                      `
                  |       +Xlnd          |           o
                  o-------> o            o===========|
            +Zlnd                        |           o
                  |                      .
                  |                     o
                  |                    /
                  `-----------------o-'
                       //
                      //
                     //
                    //
                   //
                o.//                  +Zlnd points out of the page.
                   `o

   -Y lander side view:
   --------------------
                  .--.
                  |  | SD2
                  .----------------------.
                  |                   |  | CIVA-P 3
                  |                   |  o
            +Zlnd                     |  |
                  ^                   |  |
                  |                   |  |
                  |                   |  |
                  |                   |  |
                  |      +Xlnd        |  |
            +Ylnd x------->  ------------'
                .----------| |.______________________.
                |   | `-.__|_|________..--''         |
               /_\ /_\                              /_\

                                       +Ylnd points into the page.

   This diagram illustrates the spacecraft and lander frame for the
   attached configuration:

   +Z s/c side (science deck side) view:
   -------------------------------------


                                    ^ +Xlnd
                                    |
                                  __|__
                                 /  |  \  Lander
                        +Ylnd   |   |   |
                            <-------o _____.
                             |       +Zlnd |
                             |             |
                             |  +Zsc       | +Ysc
   o==/ /==================o |      o------->o==================/ /==o
     -Y Solar Array          |      |      |        +Y Solar Array
                             |      |      |
                             .______|______.
                               `.   |   .'
                                 .--V +Xsc
                          HGA  .'       `.       +Zsc is out  of the page
                              /___________\
                                  `.|.'            +Zlnd is out of the
                                                  page and is inclined
                                                 2.69 deg toward the -Xsc.

   Because the lander frame changes its orientation relative to other frames
   it is defined as a CK-based frame.

   \begindata

      FRAME_ROS_LANDER                 =  -226800
      FRAME_-226800_NAME               = 'ROS_LANDER'
      FRAME_-226800_CLASS              =  3
      FRAME_-226800_CLASS_ID           =  -226800
      FRAME_-226800_CENTER             =  -226800

      CK_-226800_SCLK                  = -226
      CK_-226800_SPK                   = -226800

   \begintext


Rosetta Lander CIVA-P Frames
--------------------------------------

   The CIVA-P camera frames -- ROS_LANDER_CIVA_P_1 .. ROS_LANDER_CIVA_P_7
   -- are defined as follows:

     -  +Z axis is along the camera boresight;

     -  +X axis is along the camera CCD lines and is nominally parallel to
        the lander baseplate;

     -  +Y axis completes the right-handed frame, is along the camera CCD
        columns and points down toward the bottom of the lander;

     -  the origin of the frame is at the camera focal point.

   This diagram illustrates the CIVA-P frames:


                   .o
                o'\\
                   \\
                    \\
                     \\          ^ +Zch1
                      \\          \
            +Ylnd      \\  60 deg  \       ^ +Zch2
                  ^  ---------------x-.   /
                  |                CH1 \ / 60 deg
                  |                     x ---
                  | CH7              CH2 `
         Zch7 <---x       +Xlnd          |  +Zch3    o
                  o------->          CH3 x--->  =====|
         Zch6 <---x                      |           o
                  | CH6              CH4 .
                  |                     x ---
                  |                CH5 / \ 60 deg
                  `-----------------x-'   \
                       //  60 deg  /       V +Zch4
                      //          /
                     //          V +Zch5
                    //
                   //
                o.//          +Zlnd points out of the page.
                   `o
                              +Zch1..5 point 15 degrees into the page.

                              +Zch6..7 point 25 degrees into the page.

                              +Ych1..5 point into the page and are tilted
                              15 degrees away from corresponding +Z axes.

                              +Ych6..7 point into the page and are tilted
                              25 degrees away from corresponding +X axes.

                              +Xch1..7 (not shown) complete the right-handed
                              frames and are parallel to the lander XY plane.

   The following nominal rotations are needed to co-align the lander frame
   with the CIVA-P frames (Mlnd->ch = Rot3(Z)*Rot2(Y)*Rot1(Z)):

          Camera     Rot3(Z)  Rot2(Y)  Rot1(Z)
          ---------  -------  -------  -------
          CIVA-P 1     -90     +105     +120
          CIVA-P 2     -90     +105      +60
          CIVA-P 3     -90     +105        0
          CIVA-P 4     -90     +105      -60
          CIVA-P 5     -90     +105     -120
          CIVA-P 6     +90     -115        0
          CIVA-P 7     +90     -115        0

   The frame definitions below incorporate these nominal rotations.

   Since the SPICE frames subsystem calls for specifying the reverse
   transformation -- going from the instrument or structure frame to
   the base frame, -- the order of rotations assigned to the
   TKFRAME_*_AXES keyword is reversed and the signs associated with the
   rotation angles assigned to the TKFRAME_*_ANGLES keyword are the
   opposite from what is given in the above table.


   \begindata

      FRAME_ROS_LANDER_CIVA_P_1        =  -226801
      FRAME_-226801_NAME               = 'ROS_LANDER_CIVA_P_1'
      FRAME_-226801_CLASS              =  4
      FRAME_-226801_CLASS_ID           =  -226801
      FRAME_-226801_CENTER             =  -226800
      TKFRAME_-226801_RELATIVE         = 'ROS_LANDER'
      TKFRAME_-226801_SPEC             = 'ANGLES'
      TKFRAME_-226801_UNITS            = 'DEGREES'
      TKFRAME_-226801_AXES             = (    3,      2,      3   )
      TKFRAME_-226801_ANGLES           = ( -120.0, -105.0,   90.0 )

      FRAME_ROS_LANDER_CIVA_P_2        =  -226802
      FRAME_-226802_NAME               = 'ROS_LANDER_CIVA_P_2'
      FRAME_-226802_CLASS              =  4
      FRAME_-226802_CLASS_ID           =  -226802
      FRAME_-226802_CENTER             =  -226800
      TKFRAME_-226802_RELATIVE         = 'ROS_LANDER'
      TKFRAME_-226802_SPEC             = 'ANGLES'
      TKFRAME_-226802_UNITS            = 'DEGREES'
      TKFRAME_-226802_AXES             = (    3,      2,      3   )
      TKFRAME_-226802_ANGLES           = (  -60.0, -105.0,   90.0 )

      FRAME_ROS_LANDER_CIVA_P_3        =  -226803
      FRAME_-226803_NAME               = 'ROS_LANDER_CIVA_P_3'
      FRAME_-226803_CLASS              =  4
      FRAME_-226803_CLASS_ID           =  -226803
      FRAME_-226803_CENTER             =  -226800
      TKFRAME_-226803_RELATIVE         = 'ROS_LANDER'
      TKFRAME_-226803_SPEC             = 'ANGLES'
      TKFRAME_-226803_UNITS            = 'DEGREES'
      TKFRAME_-226803_AXES             = (    3,      2,      3   )
      TKFRAME_-226803_ANGLES           = (    0.0, -105.0,   90.0 )

      FRAME_ROS_LANDER_CIVA_P_4        =  -226804
      FRAME_-226804_NAME               = 'ROS_LANDER_CIVA_P_4'
      FRAME_-226804_CLASS              =  4
      FRAME_-226804_CLASS_ID           =  -226804
      FRAME_-226804_CENTER             =  -226800
      TKFRAME_-226804_RELATIVE         = 'ROS_LANDER'
      TKFRAME_-226804_SPEC             = 'ANGLES'
      TKFRAME_-226804_UNITS            = 'DEGREES'
      TKFRAME_-226804_AXES             = (    3,      2,      3   )
      TKFRAME_-226804_ANGLES           = (   60.0, -105.0,   90.0 )

      FRAME_ROS_LANDER_CIVA_P_5        =  -226805
      FRAME_-226805_NAME               = 'ROS_LANDER_CIVA_P_5'
      FRAME_-226805_CLASS              =  4
      FRAME_-226805_CLASS_ID           =  -226805
      FRAME_-226805_CENTER             =  -226800
      TKFRAME_-226805_RELATIVE         = 'ROS_LANDER'
      TKFRAME_-226805_SPEC             = 'ANGLES'
      TKFRAME_-226805_UNITS            = 'DEGREES'
      TKFRAME_-226805_AXES             = (    3,      2,      3   )
      TKFRAME_-226805_ANGLES           = (  120.0, -105.0,   90.0 )

      FRAME_ROS_LANDER_CIVA_P_6        =  -226806
      FRAME_-226806_NAME               = 'ROS_LANDER_CIVA_P_6'
      FRAME_-226806_CLASS              =  4
      FRAME_-226806_CLASS_ID           =  -226806
      FRAME_-226806_CENTER             =  -226800
      TKFRAME_-226806_RELATIVE         = 'ROS_LANDER'
      TKFRAME_-226806_SPEC             = 'ANGLES'
      TKFRAME_-226806_UNITS            = 'DEGREES'
      TKFRAME_-226806_AXES             = (    3,      2,      3   )
      TKFRAME_-226806_ANGLES           = (    0.0,  115.0,  -90.0 )

      FRAME_ROS_LANDER_CIVA_P_7        =  -226807
      FRAME_-226807_NAME               = 'ROS_LANDER_CIVA_P_7'
      FRAME_-226807_CLASS              =  4
      FRAME_-226807_CLASS_ID           =  -226807
      FRAME_-226807_CENTER             =  -226800
      TKFRAME_-226807_RELATIVE         = 'ROS_LANDER'
      TKFRAME_-226807_SPEC             = 'ANGLES'
      TKFRAME_-226807_UNITS            = 'DEGREES'
      TKFRAME_-226807_AXES             = (    3,      2,      3   )
      TKFRAME_-226807_ANGLES           = (    0.0,  115.0, -90.0  )

   \begintext


Rosetta Lander SESAME DIM Frames
--------------------------------------

   The SESAME DIM piezoelectric detector frames -- ROS_LANDER_DIM_X,
   ROS_LANDER_DIM_Y and ROS_LANDER_DIM_Z --  are defined as follows:

     -  +Z axis is along the normal to the detector surface facing
        outward and is nominally along s/c +X for DIM_X, s/c +Y for
        DIM_Y, and s/c +Z for DIM_Z;

     -  +X axis is nominally along s/c -Z for DIM_X, s/c +X for DIM_Y,
        and s/c +X for DIM_Z.;

     -  +Y axis completes the right-handed frame;

     -  the origin of the frame is at the geometric center of the detector
        piezoelectric element.

   These diagrams illustrate the DIM detector frames:

      DIM_X frame:
                          o
                         o\     +Ydimx
                           \   ^
                     +Ylnd  \  |
                           ^ --|-------.
                           |   x---->   \
                           | +Xdimx  +Zdimx     o
                           o---->        |======|
                     +Zlnd      +Xlnd    |      o
                           |            /
                           `-----------'
                            /
                           /
                         o/              +Zlnd  points out of the page.
                           o             +Xdimx points into the page.

      DIM_Y frame:
                          o    +Zdimy
                         o\   ^
                           \  |
                     +Ylnd  \ |    +Xdimy
                           ^ -x---->  -.
                           | +Ydimy     \
                           |             |      o
                           o---->        |======|
                     +Zlnd      +Xlnd    |      o
                           |            /
                           `-----------'
                            /
                           /
                         o/              +Zlnd  points out of the page.
                           o             +Ydimy points into the page.

      DIM_Z frame:
                          o
                         o\    +Ydimz
                           \  ^
                     +Ylnd  \ |
                           ^ -|--------.
                           |  o---->    \
                           | +Zdimz +Xdimz      o
                           o---->        |======|
                     +Zlnd      +Xlnd    |      o
                           |            /
                           `-----------'
                            /
                           /
                         o/              +Zlnd  points out of the page.
                           o             +Zdimz points out of the page.


   As seen on the diagram:

      -  DIM_X frame is nominally rotated from the lander frame
         by +90 degrees about Y.

      -  DIM_Y frame is nominally rotated from the lander frame
         by -90 degrees about X.

      -  DIM_Z frame is nominally co-aligned with the lander frame.

   The frame definitions below incorporate these nominal rotations.

   Since the SPICE frames subsystem calls for specifying the reverse
   transformation -- going from the instrument or structure frame to
   the base frame, -- the order of rotations assigned to the
   TKFRAME_*_AXES keyword is reversed and the signs associated with the
   rotation angles assigned to the TKFRAME_*_ANGLES keyword are the
   opposite from what is given in the above table.

   \begindata

      FRAME_ROS_LANDER_DIM_X           =  -226830
      FRAME_-226830_NAME               = 'ROS_LANDER_DIM_X'
      FRAME_-226830_CLASS              =  4
      FRAME_-226830_CLASS_ID           =  -226830
      FRAME_-226830_CENTER             =  -226800
      TKFRAME_-226830_RELATIVE         = 'ROS_LANDER'
      TKFRAME_-226830_SPEC             = 'ANGLES'
      TKFRAME_-226830_UNITS            = 'DEGREES'
      TKFRAME_-226830_AXES             = (   1,     2,     3    )
      TKFRAME_-226830_ANGLES           = (   0.0, -90.0,   0.0  )

      FRAME_ROS_LANDER_DIM_Y           =  -226831
      FRAME_-226831_NAME               = 'ROS_LANDER_DIM_Y'
      FRAME_-226831_CLASS              =  4
      FRAME_-226831_CLASS_ID           =  -226831
      FRAME_-226831_CENTER             =  -226800
      TKFRAME_-226831_RELATIVE         = 'ROS_LANDER'
      TKFRAME_-226831_SPEC             = 'ANGLES'
      TKFRAME_-226831_UNITS            = 'DEGREES'
      TKFRAME_-226831_AXES             = (   1,     2,     3    )
      TKFRAME_-226831_ANGLES           = (  90.0,   0.0,   0.0  )

      FRAME_ROS_LANDER_DIM_Z           =  -226832
      FRAME_-226832_NAME               = 'ROS_LANDER_DIM_Z'
      FRAME_-226832_CLASS              =  4
      FRAME_-226832_CLASS_ID           =  -226832
      FRAME_-226832_CENTER             =  -226800
      TKFRAME_-226832_RELATIVE         = 'ROS_LANDER'
      TKFRAME_-226832_SPEC             = 'ANGLES'
      TKFRAME_-226832_UNITS            = 'DEGREES'
      TKFRAME_-226832_AXES             = (   1,     2,     3    )
      TKFRAME_-226832_ANGLES           = (   0.0,   0.0,   0.0  )

   \begintext


Rosetta Lander ROLIS Frame
--------------------------------------

   The ROLIS camera frame -- ROS_LANDER_ROLIS -- is defined as follows:

     -  +Z axis is along the camera boresight and is nominally
        co-aligned with the -Z axis of the lander frame

     -  +X axis is along the camera CCD lines and nominally co-aligned
        with the -Y axis of the lander frame

     -  +Y axis completes the right-handed frame and is along the
        camera CCD columns and nominally co-aligned -X axis of the
        lander frame.

     -  the origin of the frame is at the rear principal point of the
        optics.

   This diagram illustrates the ROLIS frame:

                   .o
                o'\\
                   \\
                    \\
                     \\
                      \\
            +Ylnd      \\
                  ^ ------------------.
                  |                    \
                  |                     \
                  |                      `
            +Zlnd |       +Xldn          |           o
                  o------->              |===========|
             <-------x +ZRolfrm          |           o
      +YRolfrm    |  |                   .
                  |  |                  /
                  |  |                 /
                  `--|----------------'
                     v //
            +XRolfrm  //
                     //
                    //
                   //
                o.//          +Zlnd points out of the page.
                   `o         +ZRolfrm points into the page.


   Nominally two rotations are needed to align the lander frame with
   the ROLIS frame: first by -90 degrees about +Z axis, second by 180
   degrees about +X axis.

   The keywords below define the ROLIS frame.

   Since the SPICE frames subsystem calls for specifying the reverse
   transformation -- going from the instrument or structure frame to
   the base frame, -- the order of rotations assigned to the
   TKFRAME_*_AXES keyword is reversed and the signs associated with the
   rotation angles assigned to the TKFRAME_*_ANGLES keyword are the
   opposite from what is given in the above table.

   \begindata

      FRAME_ROS_LANDER_ROLIS           =  -226815
      FRAME_-226815_NAME               = 'ROS_LANDER_ROLIS'
      FRAME_-226815_CLASS              =  4
      FRAME_-226815_CLASS_ID           =  -226815
      FRAME_-226815_CENTER             =  -226800
      TKFRAME_-226815_RELATIVE         = 'ROS_LANDER'
      TKFRAME_-226815_SPEC             = 'ANGLES'
      TKFRAME_-226815_UNITS            = 'DEGREES'
      TKFRAME_-226815_AXES             = (   3,     1,     2    )
      TKFRAME_-226815_ANGLES           = (  90.0, 180.0,   0.0  )

   \begintext



Rosetta Mission NAIF ID Codes -- Definition Section
========================================================================

   This section contains name to NAIF ID mappings for the Rosetta mission.


Rosetta Target IDs:
-------------------------------------------------------------

   This table summarizes Rosetta Target IDs:

            Name                    ID       Synonyms
            ---------------------   -------  ---------------------------
            CHURYUMOV-GERASIMENKO   1000012  '67P/C-G'
                                             '67P/CHURYUMOV-GERASIMENKO'
            STEINS                  2002867  '2867 STEINS'
            LUTETIA                 2000021  '21 LUTETIA'
            HONDA-MRKOS-PAJDUSAKOVA 1000045  '45P/H-M-P'
                                             '45P/HONDA-MRKOS-PAJDUSAKOVA'

   Name-ID Mapping keywords:

   \begindata

      NAIF_BODY_NAME += ( '67P/CHURYUMOV-GERASIMENKO' )
      NAIF_BODY_CODE += ( 1000012 )

      NAIF_BODY_NAME += ( '67P/C-G' )
      NAIF_BODY_CODE += ( 1000012 )

      NAIF_BODY_NAME += ( 'CHURYUMOV-GERASIMENKO' )
      NAIF_BODY_CODE += ( 1000012 )

      NAIF_BODY_NAME += ( '45P/HONDA-MRKOS-PAJDUSAKOVA' )
      NAIF_BODY_CODE += ( 1000045 )

      NAIF_BODY_NAME += ( '45P/H-M-P' )
      NAIF_BODY_CODE += ( 1000045 )

      NAIF_BODY_NAME += ( 'HONDA-MRKOS-PAJDUSAKOVA' )
      NAIF_BODY_CODE += ( 1000045 )

      NAIF_BODY_NAME += ( '2867 STEINS' )
      NAIF_BODY_CODE += ( 2002867 )

      NAIF_BODY_NAME += ( 'STEINS' )
      NAIF_BODY_CODE += ( 2002867 )

      NAIF_BODY_NAME += ( '21 LUTETIA' )
      NAIF_BODY_CODE += ( 2000021 )

      NAIF_BODY_NAME += ( 'LUTETIA' )
      NAIF_BODY_CODE += ( 2000021 )

   \begintext


Rosetta Spacecraft (ROSETTA) spacecraft and instruments IDs:
-------------------------------------------------------------

   This table summarizes Rosetta Spacecraft IDs:

      Name                   ID       Synonyms
      ---------------------  -------  ---------------------------
      ROS                       -226  ROSETTA, ROSETTA ORBITER

   Notes:

      -- 'ROS', 'ROSETTA', 'ROSETTA ORBITER' are
         synonyms and all map to the official Rosetta s/c ID (-226);

   Name-ID Mapping keywords:

   \begindata

      NAIF_BODY_NAME += ( 'ROSETTA' )
      NAIF_BODY_CODE += ( -226 )

      NAIF_BODY_NAME += ( 'ROS' )
      NAIF_BODY_CODE += ( -226 )

      NAIF_BODY_NAME += ( 'ROSETTA ORBITER' )
      NAIF_BODY_CODE += ( -226 )

   \begintext


Rosetta Spacecraft Structures IDs
--------------------------------------

   This table summarizes Rosetta Spacecraft Structure IDs:

      Name                   ID       Synonyms
      ---------------------  -------  -------------------------
      ROS_SPACECRAFT         -226000   ROS_SC

      ROS_MGA-S              -226030
      ROS_MGA-X              -226040
      ROS_LGA-1              -226050
      ROS_LGA-2              -226060

      ROS_HGA_GIMBAL         -226070
      ROS_HGA                -226075

      ROS_SA+Y_GIMBAL        -226010
      ROS_SA+Y_C1            -226011
      ROS_SA+Y_C2            -226012
      ROS_SA+Y_C3            -226013
      ROS_SA+Y_C4            -226014

      ROS_SA-Y_GIMBAL        -226020
      ROS_SA-Y_C1            -226021
      ROS_SA-Y_C2            -226022
      ROS_SA-Y_C3            -226023
      ROS_SA-Y_C4            -226024

      ROS_SPACECRAFT_C1      -226001
      ROS_SPACECRAFT_C2      -226002
      ROS_SPACECRAFT_C3      -226003
      ROS_SPACECRAFT_C4      -226004
      ROS_SPACECRAFT_C5      -226005
      ROS_SPACECRAFT_C6      -226006
      ROS_SPACECRAFT_C7      -226007
      ROS_SPACECRAFT_C8      -226008

   Notes:

      -  'ROS_SC' and 'ROS_SPACECRAFT' are synonyms and all map to the
         ROSETTA s/c bus structure ID (-226000);

   Name-ID Mapping keywords:

   \begindata

      NAIF_BODY_NAME += ( 'ROS_SPACECRAFT' )
      NAIF_BODY_CODE += ( -226000 )

      NAIF_BODY_NAME += ( 'ROS_SC' )
      NAIF_BODY_CODE += ( -226000 )

      NAIF_BODY_NAME += ( 'ROS_MGA-S' )
      NAIF_BODY_CODE += ( -226030 )

      NAIF_BODY_NAME += ( 'ROS_MGA-X' )
      NAIF_BODY_CODE += ( -226040 )

      NAIF_BODY_NAME += ( 'ROS_LGA-1' )
      NAIF_BODY_CODE += ( -226050 )

      NAIF_BODY_NAME += ( 'ROS_LGA-2' )
      NAIF_BODY_CODE += ( -226060 )

      NAIF_BODY_NAME += ( 'ROS_HGA_GIMBAL' )
      NAIF_BODY_CODE += ( -226070 )

      NAIF_BODY_NAME += ( 'ROS_HGA' )
      NAIF_BODY_CODE += ( -226075 )

      NAIF_BODY_NAME += ( 'ROS_SA+Y_GIMBAL' )
      NAIF_BODY_CODE += ( -226010 )

      NAIF_BODY_NAME += ( 'ROS_SA+Y_C1' )
      NAIF_BODY_CODE += ( -226011 )

      NAIF_BODY_NAME += ( 'ROS_SA+Y_C2' )
      NAIF_BODY_CODE += ( -226012 )

      NAIF_BODY_NAME += ( 'ROS_SA+Y_C3' )
      NAIF_BODY_CODE += ( -226013 )

      NAIF_BODY_NAME += ( 'ROS_SA+Y_C4' )
      NAIF_BODY_CODE += ( -226014 )

      NAIF_BODY_NAME += ( 'ROS_SA-Y_GIMBAL' )
      NAIF_BODY_CODE += ( -226020 )

      NAIF_BODY_NAME += ( 'ROS_SA-Y_C1 ' )
      NAIF_BODY_CODE += ( -226021 )

      NAIF_BODY_NAME += ( 'ROS_SA-Y_C2 ' )
      NAIF_BODY_CODE += ( -226022 )

      NAIF_BODY_NAME += ( 'ROS_SA-Y_C3 ' )
      NAIF_BODY_CODE += ( -226023 )

      NAIF_BODY_NAME += ( 'ROS_SA-Y_C4 ' )
      NAIF_BODY_CODE += ( -226024 )

      NAIF_BODY_NAME += ( 'ROS_SPACECRAFT_C1' )
      NAIF_BODY_CODE += ( -226001 )

      NAIF_BODY_NAME += ( 'ROS_SPACECRAFT_C2' )
      NAIF_BODY_CODE += ( -226002 )

      NAIF_BODY_NAME += ( 'ROS_SPACECRAFT_C3' )
      NAIF_BODY_CODE += ( -226003 )

      NAIF_BODY_NAME += ( 'ROS_SPACECRAFT_C4' )
      NAIF_BODY_CODE += ( -226004 )

      NAIF_BODY_NAME += ( 'ROS_SPACECRAFT_C5' )
      NAIF_BODY_CODE += ( -226005 )

      NAIF_BODY_NAME += ( 'ROS_SPACECRAFT_C6' )
      NAIF_BODY_CODE += ( -226006 )

      NAIF_BODY_NAME += ( 'ROS_SPACECRAFT_C7' )
      NAIF_BODY_CODE += ( -226007 )

      NAIF_BODY_NAME += ( 'ROS_SPACECRAFT_C8' )
      NAIF_BODY_CODE += ( -226008 )

   \begintext


Rosetta Star Tracker IDs
--------------------------------------

   This table summarizes Rosetta Star Tracker IDs:

      Name                   ID     
      ---------------------  -------
      ROS_STR-A              -226080
      ROS_STR-B              -226090

   Name-ID Mapping keywords:

   \begindata

      NAIF_BODY_NAME += ( 'ROS_STR-A' )
      NAIF_BODY_CODE += ( -226080 )

      NAIF_BODY_NAME += ( 'ROS_STR-B' )
      NAIF_BODY_CODE += ( -226090 )

   \begintext


OSIRIS IDs
--------------------------------------

   This table summarizes OSIRIS IDs:

      Name                   ID
      ---------------------  -------
      ROS_OSIRIS             -226110
      ROS_OSIRIS_NAC         -226111
      ROS_OSIRIS_NAC_URF     -226116
      ROS_OSIRIS_WAC         -226112
      ROS_OSIRIS_WAC_URF     -226117

   Name-ID Mapping keywords:

   \begindata

      NAIF_BODY_NAME += ( 'ROS_OSIRIS' )
      NAIF_BODY_CODE += ( -226100 )

      NAIF_BODY_NAME += ( 'ROS_OSIRIS_NAC' )
      NAIF_BODY_CODE += ( -226111 )

      NAIF_BODY_NAME += ( 'ROS_OSIRIS_NAC_URF' )
      NAIF_BODY_CODE += ( -226116 )

      NAIF_BODY_NAME += ( 'ROS_OSIRIS_WAC' )
      NAIF_BODY_CODE += ( -226112 )

      NAIF_BODY_NAME += ( 'ROS_OSIRIS_WAC_URF' )
      NAIF_BODY_CODE += ( -226117 )

   \begintext


ALICE IDs
--------------------------------------

   This table summarizes ALICE IDs:

      Name                         ID
      ---------------------        -------
      ROS_ALICE                    -226120
      ROS_ALICE_CENTER             -226121
      ROS_ALICE_-X_WIDE_BOTTOM     -226122
      ROS_ALICE_+X_WIDE_TOP        -226123
      ROS_ALICE_PINHOLE            -226124
      ROS_ALICE_URF                -226125

   Name-ID Mapping keywords:

   \begindata

      NAIF_BODY_NAME += ( 'ROS_ALICE' )
      NAIF_BODY_CODE += ( -226120 )

      NAIF_BODY_NAME += ( 'ROS_ALICE_CENTER' )
      NAIF_BODY_CODE += ( -226121 )

      NAIF_BODY_NAME += ( 'ROS_ALICE_-X_WIDE_BOTTOM' )
      NAIF_BODY_CODE += ( -226122 )

      NAIF_BODY_NAME += ( 'ROS_ALICE_+X_WIDE_TOP' )
      NAIF_BODY_CODE += ( -226123 )

      NAIF_BODY_NAME += ( 'ROS_ALICE_PINHOLE' )
      NAIF_BODY_CODE += ( -226124 )

      NAIF_BODY_NAME += ( 'ROS_ALICE_URF' )
      NAIF_BODY_CODE += ( -226125 )

   \begintext


VIRTIS IDs
--------------------------------------

   This table summarizes VIRTIS IDs:

      Name                   ID
      ---------------------  -------
      ROS_VIRTIS             -226200
      ROS_VIRTIS-M           -226210
      ROS_VIRTIS-M_VIS       -226211
      ROS_VIRTIS-M_VIS_ZERO  -226212
      ROS_VIRTIS-M_IR        -226213
      ROS_VIRTIS-M_IR_ZERO   -226214
      ROS_VIRTIS-H           -226220

   Name-ID Mapping keywords:

   \begindata

      NAIF_BODY_NAME += ( 'ROS_VIRTIS' )
      NAIF_BODY_CODE += ( -226200 )

      NAIF_BODY_NAME += ( 'ROS_VIRTIS-M' )
      NAIF_BODY_CODE += ( -226210 )

      NAIF_BODY_NAME += ( 'ROS_VIRTIS-M_VIS' )
      NAIF_BODY_CODE += ( -226211 )

      NAIF_BODY_NAME += ( 'ROS_VIRTIS-M_VIS_ZERO' )
      NAIF_BODY_CODE += ( -226212 )

      NAIF_BODY_NAME += ( 'ROS_VIRTIS-M_IR' )
      NAIF_BODY_CODE += ( -226213 )

      NAIF_BODY_NAME += ( 'ROS_VIRTIS-M_IR_ZERO' )
      NAIF_BODY_CODE += ( -226214 )

      NAIF_BODY_NAME += ( 'ROS_VIRTIS-H' )
      NAIF_BODY_CODE += ( -226220 )

   \begintext


MIRO IDs
--------------------------------------

   This table summarizes MIRO IDs:

      Name                   ID
      ---------------------  -------
      ROS_MIRO               -226130
      ROS_MIRO_MM            -226131
      ROS_MIRO_SUBMM         -226132
      ROS_MIRO_URF           -226135

   Name-ID Mapping keywords:

   \begindata

      NAIF_BODY_NAME += ( 'ROS_MIRO' )
      NAIF_BODY_CODE += ( -226130 )

      NAIF_BODY_NAME += ( 'ROS_MIRO_MM' )
      NAIF_BODY_CODE += ( -226131 )

      NAIF_BODY_NAME += ( 'ROS_MIRO_SUBMM' )
      NAIF_BODY_CODE += ( -226132 )

      NAIF_BODY_NAME += ( 'ROS_MIRO_URF' )
      NAIF_BODY_CODE += ( -226135 )

   \begintext


ROSINA IDs
--------------------------------------

   This table summarizes ROSINA IDs:

      Name                   ID
      ---------------------  -------
      ROS_ROSINA             -226300
      ROS_ROSINA_DFMS        -226310
      ROS_ROSINA_DFMS_WA     -226311
      ROS_ROSINA_DFMS_NA     -226312
      ROS_ROSINA_DFMS_URF    -226319
      ROS_ROSINA_RTOF        -226320
      ROS_ROSINA_RTOF_URF    -226329
      ROS_ROSINA_COPS        -226330
      ROS_ROSINA_COPS_URF    -226339

   Name-ID Mapping keywords:

   \begindata

      NAIF_BODY_NAME += ( 'ROS_ROSINA' )
      NAIF_BODY_CODE += ( -226300 )

      NAIF_BODY_NAME += ( 'ROS_ROSINA_DFMS' )
      NAIF_BODY_CODE += ( -226310 )

      NAIF_BODY_NAME += ( 'ROS_ROSINA_DFMS_WA' )
      NAIF_BODY_CODE += ( -226311 )

      NAIF_BODY_NAME += ( 'ROS_ROSINA_DFMS_NA' )
      NAIF_BODY_CODE += ( -226312 )

      NAIF_BODY_NAME += ( 'ROS_ROSINA_DFMS_URF' )
      NAIF_BODY_CODE += ( -226319 )

      NAIF_BODY_NAME += ( 'ROS_ROSINA_RTOF' )
      NAIF_BODY_CODE += ( -226320 )

      NAIF_BODY_NAME += ( 'ROS_ROSINA_RTOF_URF' )
      NAIF_BODY_CODE += ( -226329 )

      NAIF_BODY_NAME += ( 'ROS_ROSINA_COPS' )
      NAIF_BODY_CODE += ( -226330 )

      NAIF_BODY_NAME += ( 'ROS_ROSINA_COPS_URF' )
      NAIF_BODY_CODE += ( -226339 )

   \begintext


COSIMA IDs
--------------------------------------

   This table summarizes COSIMA IDs:

      Name                   ID
      ---------------------  -------
      ROS_COSIMA             -226140
      ROS_COSIMA_URF         -226145

   Name-ID Mapping keywords:

   \begindata

      NAIF_BODY_NAME += ( 'ROS_COSIMA' )
      NAIF_BODY_CODE += ( -226140 )

      NAIF_BODY_NAME += ( 'ROS_COSIMA_URF' )
      NAIF_BODY_CODE += ( -226145 )

   \begintext


MIDAS IDs
--------------------------------------

   This table summarizes MIDAS IDs:

      Name                   ID
      ---------------------  -------
      ROS_MIDAS              -226150
      ROS_MIDAS_URF          -226155

   Name-ID Mapping keywords:

   \begindata

      NAIF_BODY_NAME += ( 'ROS_MIDAS' )
      NAIF_BODY_CODE += ( -226150 )

      NAIF_BODY_NAME += ( 'ROS_MIDAS_URF' )
      NAIF_BODY_CODE += ( -226155 )

   \begintext


CONSERT IDs
--------------------------------------

   This table summarizes CONSERT IDs:

      Name                   ID
      ---------------------  -------
      ROS_CONSERT            -226160
      ROS_CONSERT_URF        -226165

   Name-ID Mapping keywords:

   \begindata

      NAIF_BODY_NAME += ( 'ROS_CONSERT' )
      NAIF_BODY_CODE += ( -226160 )

      NAIF_BODY_NAME += ( 'ROS_CONSERT_URF' )
      NAIF_BODY_CODE += ( -226165 )

   \begintext


NAVCAM IDs
--------------------------------------

   This table summarizes NAVCAM IDs:

      Name                   ID
      ---------------------  -------
      ROS_NAVCAM-A           -226170
      ROS_NAVCAM-A_URF       -226175
      ROS_NAVCAM-B           -226180
      ROS_NAVCAM-B_URF       -226185

   Name-ID Mapping keywords:

   \begindata

      NAIF_BODY_NAME += ( 'ROS_NAVCAM-A' )
      NAIF_BODY_CODE += ( -226170 )

      NAIF_BODY_NAME += ( 'ROS_NAVCAM-A_URF' )
      NAIF_BODY_CODE += ( -226175 )

      NAIF_BODY_NAME += ( 'ROS_NAVCAM-B' )
      NAIF_BODY_CODE += ( -226180 )

      NAIF_BODY_NAME += ( 'ROS_NAVCAM-B_URF' )
      NAIF_BODY_CODE += ( -226185 )

   \begintext


GIADA IDs
--------------------------------------

   This table summarizes GIADA IDs:

      Name                   ID
      ---------------------  -------
      ROS_GIADA              -226400
      ROS_GIADA_GDS          -226410
      ROS_GIADA_IS           -226420
      ROS_GIADA_MBS1         -226431
      ROS_GIADA_MBS2         -226432
      ROS_GIADA_MBS3         -226433
      ROS_GIADA_MBS4         -226434
      ROS_GIADA_MBS5         -226435
      ROS_GIADA_URF          -226440

   Name-ID Mapping keywords:

   \begindata

      NAIF_BODY_NAME += ( 'ROS_GIADA' )
      NAIF_BODY_CODE += ( -226400 )

      NAIF_BODY_NAME += ( 'ROS_GIADA_GDS' )
      NAIF_BODY_CODE += ( -226410 )

      NAIF_BODY_NAME += ( 'ROS_GIADA_IS' )
      NAIF_BODY_CODE += ( -226420 )

      NAIF_BODY_NAME += ( 'ROS_GIADA_MBS1' )
      NAIF_BODY_CODE += ( -226431 )

      NAIF_BODY_NAME += ( 'ROS_GIADA_MBS2' )
      NAIF_BODY_CODE += ( -226432 )

      NAIF_BODY_NAME += ( 'ROS_GIADA_MBS3' )
      NAIF_BODY_CODE += ( -226433 )

      NAIF_BODY_NAME += ( 'ROS_GIADA_MBS4' )
      NAIF_BODY_CODE += ( -226434 )

      NAIF_BODY_NAME += ( 'ROS_GIADA_MBS5' )
      NAIF_BODY_CODE += ( -226435 )

      NAIF_BODY_NAME += ( 'ROS_GIADA_URF' )
      NAIF_BODY_CODE += ( -226440 )

   \begintext


RPC IDs
--------------------------------------

   This table summarizes RPC IDs:

      Name                   ID
      ---------------------  -------
      ROS_RPC                -226500
      ROS_RPC_LAP1           -226511
      ROS_RPC_LAP2           -226512
      ROS_RPC_LAP1_URF       -226515
      ROS_RPC_LAP2_URF       -226516
      ROS_RPC_IES            -226520
      ROS_RPC_IES_ELECTRON   -226521
      ROS_RPC_IES_ION        -226522
      ROS_RPC_IES_URF        -226525
      ROS_RPC_IES_QUAD1      -226526
      ROS_RPC_IES_QUAD2      -226527
      ROS_RPC_IES_QUAD3      -226528
      ROS_RPC_IES_QUAD4      -226529
      ROS_RPC_ICA            -226530
      ROS_RPC_ICA_URF        -226535
      ROS_RPC_ICA_QUAD1      -226536
      ROS_RPC_ICA_QUAD2      -226537
      ROS_RPC_ICA_QUAD3      -226538
      ROS_RPC_ICA_QUAD4      -226539
      ROS_RPC_MAG_OB         -226541
      ROS_RPC_MAG_IB         -226542
      ROS_RPC_MAG_OB_URF     -226545
      ROS_RPC_MAG_IB_URF     -226546
      ROS_RPC_MIP            -226550
      ROS_RPC_MIP_R1         -226551
      ROS_RPC_MIP_T1         -226552
      ROS_RPC_MIP_T2         -226553
      ROS_RPC_MIP_R2         -226554
      ROS_RPC_MIP_URF        -226555
      ROS_RPC_BOOM1          -226560
      ROS_RPC_BOOM2          -226570

   Name-ID Mapping keywords:

   \begindata

      NAIF_BODY_NAME += ( 'ROS_RPC' )
      NAIF_BODY_CODE += ( -226500 )

      NAIF_BODY_NAME += ( 'ROS_RPC_LAP1' )
      NAIF_BODY_CODE += ( -226511 )

      NAIF_BODY_NAME += ( 'ROS_RPC_LAP2' )
      NAIF_BODY_CODE += ( -226512 )

      NAIF_BODY_NAME += ( 'ROS_RPC_LAP1_URF' )
      NAIF_BODY_CODE += ( -226515 )

      NAIF_BODY_NAME += ( 'ROS_RPC_LAP2_URF' )
      NAIF_BODY_CODE += ( -226516 )

      NAIF_BODY_NAME += ( 'ROS_RPC_IES' )
      NAIF_BODY_CODE += ( -226520 )

      NAIF_BODY_NAME += ( 'ROS_RPC_IES_ELECTRON' )
      NAIF_BODY_CODE += ( -226521 )

      NAIF_BODY_NAME += ( 'ROS_RPC_IES_ION' )
      NAIF_BODY_CODE += ( -226522 )

      NAIF_BODY_NAME += ( 'ROS_RPC_IES_URF' )
      NAIF_BODY_CODE += ( -226525 )

      NAIF_BODY_NAME += ( 'ROS_RPC_IES_QUAD1' )
      NAIF_BODY_CODE += ( -226526 )

      NAIF_BODY_NAME += ( 'ROS_RPC_IES_QUAD2' )
      NAIF_BODY_CODE += ( -226527 )

      NAIF_BODY_NAME += ( 'ROS_RPC_IES_QUAD3' )
      NAIF_BODY_CODE += ( -226528 )

      NAIF_BODY_NAME += ( 'ROS_RPC_IES_QUAD4' )
      NAIF_BODY_CODE += ( -226529 )

      NAIF_BODY_NAME += ( 'ROS_RPC_ICA' )
      NAIF_BODY_CODE += ( -226530 )

      NAIF_BODY_NAME += ( 'ROS_RPC_ICA_URF' )
      NAIF_BODY_CODE += ( -226535 )

      NAIF_BODY_NAME += ( 'ROS_RPC_ICA_QUAD1' )
      NAIF_BODY_CODE += ( -226536 )

      NAIF_BODY_NAME += ( 'ROS_RPC_ICA_QUAD2' )
      NAIF_BODY_CODE += ( -226537 )

      NAIF_BODY_NAME += ( 'ROS_RPC_ICA_QUAD3' )
      NAIF_BODY_CODE += ( -226538 )

      NAIF_BODY_NAME += ( 'ROS_RPC_ICA_QUAD4' )
      NAIF_BODY_CODE += ( -226539 )

      NAIF_BODY_NAME += ( 'ROS_RPC_MAG_OB' )
      NAIF_BODY_CODE += ( -226541 )

      NAIF_BODY_NAME += ( 'ROS_RPC_MAG_IB' )
      NAIF_BODY_CODE += ( -226542 )

      NAIF_BODY_NAME += ( 'ROS_RPC_MAG_OB_URF' )
      NAIF_BODY_CODE += ( -226545 )

      NAIF_BODY_NAME += ( 'ROS_RPC_MAG_IB_URF' )
      NAIF_BODY_CODE += ( -226546 )

      NAIF_BODY_NAME += ( 'ROS_RPC_MIP' )
      NAIF_BODY_CODE += ( -226550 )

      NAIF_BODY_NAME += ( 'ROS_RPC_MIP_R1' )
      NAIF_BODY_CODE += ( -226551 )

      NAIF_BODY_NAME += ( 'ROS_RPC_MIP_T1' )
      NAIF_BODY_CODE += ( -226552 )

      NAIF_BODY_NAME += ( 'ROS_RPC_MIP_T2' )
      NAIF_BODY_CODE += ( -226553 )

      NAIF_BODY_NAME += ( 'ROS_RPC_MIP_R2' )
      NAIF_BODY_CODE += ( -226554 )

      NAIF_BODY_NAME += ( 'ROS_RPC_MIP_URF' )
      NAIF_BODY_CODE += ( -226555 )

      NAIF_BODY_NAME += ( 'ROS_RPC_BOOM1' )
      NAIF_BODY_CODE += ( -226560 )

      NAIF_BODY_NAME += ( 'ROS_RPC_BOOM2' )
      NAIF_BODY_CODE += ( -226570 )

   \begintext


Rosetta Lander IDs
--------------------------------------

   This table summarizes Rosetta Lander and Lander Instrument IDs:

      Name                     ID       Synonyms
      -----------------------  -------  -------------------------
      ROS_LANDER_LANDING_SITE  -226999  ROS_LANDER_TOPO,
                                        ROS_LANDER_LS

      ROS_LANDER               -226800  PHILAE

      ROS_LANDER_CIVA_P_1      -226801
      ROS_LANDER_CIVA_P_2      -226802
      ROS_LANDER_CIVA_P_3      -226803
      ROS_LANDER_CIVA_P_4      -226804
      ROS_LANDER_CIVA_P_5      -226805
      ROS_LANDER_CIVA_P_6      -226806
      ROS_LANDER_CIVA_P_7      -226807

      ROS_LANDER_DIM_X         -226830
      ROS_LANDER_DIM_Y         -226831
      ROS_LANDER_DIM_Z         -226832

      ROS_LANDER_ROLIS_IFL     -226810
      ROS_LANDER_ROLIS_R       -226811
      ROS_LANDER_ROLIS_G       -226812
      ROS_LANDER_ROLIS_B       -226813
      ROS_LANDER_ROLIS_IR      -226814

   Name-ID Mapping keywords:

   \begindata

      NAIF_BODY_NAME += ( 'ROS_LANDER_LS' )
      NAIF_BODY_CODE += ( -226999 )

      NAIF_BODY_NAME += ( 'ROS_LANDER_TOPO' )
      NAIF_BODY_CODE += ( -226999 )

      NAIF_BODY_NAME += ( 'ROS_LANDER_LANDING_SITE' )
      NAIF_BODY_CODE += ( -226999 )

      NAIF_BODY_NAME += ( 'PHILAE' )
      NAIF_BODY_CODE += ( -226800 )

      NAIF_BODY_NAME += ( 'ROS_LANDER' )
      NAIF_BODY_CODE += ( -226800 )

      NAIF_BODY_NAME += ( 'ROS_LANDER_CIVA_P_1' )
      NAIF_BODY_CODE += ( -226801 )

      NAIF_BODY_NAME += ( 'ROS_LANDER_CIVA_P_2' )
      NAIF_BODY_CODE += ( -226802 )

      NAIF_BODY_NAME += ( 'ROS_LANDER_CIVA_P_3' )
      NAIF_BODY_CODE += ( -226803 )

      NAIF_BODY_NAME += ( 'ROS_LANDER_CIVA_P_4' )
      NAIF_BODY_CODE += ( -226804 )

      NAIF_BODY_NAME += ( 'ROS_LANDER_CIVA_P_5' )
      NAIF_BODY_CODE += ( -226805 )

      NAIF_BODY_NAME += ( 'ROS_LANDER_CIVA_P_6' )
      NAIF_BODY_CODE += ( -226806 )

      NAIF_BODY_NAME += ( 'ROS_LANDER_CIVA_P_7' )
      NAIF_BODY_CODE += ( -226807 )

      NAIF_BODY_NAME += ( 'ROS_LANDER_DIM_X' )
      NAIF_BODY_CODE += ( -226830 )

      NAIF_BODY_NAME += ( 'ROS_LANDER_DIM_Y' )
      NAIF_BODY_CODE += ( -226831 )

      NAIF_BODY_NAME += ( 'ROS_LANDER_DIM_Z' )
      NAIF_BODY_CODE += ( -226832 )

      NAIF_BODY_NAME += ( 'ROS_LANDER_ROLIS_IFL' )
      NAIF_BODY_CODE += ( -226810 )

      NAIF_BODY_NAME += ( 'ROS_LANDER_ROLIS_R' )
      NAIF_BODY_CODE += ( -226811 )

      NAIF_BODY_NAME += ( 'ROS_LANDER_ROLIS_G' )
      NAIF_BODY_CODE += ( -226812 )

      NAIF_BODY_NAME += ( 'ROS_LANDER_ROLIS_B' )
      NAIF_BODY_CODE += ( -226813 )

      NAIF_BODY_NAME += ( 'ROS_LANDER_ROLIS_IR' )
      NAIF_BODY_CODE += ( -226814 )

   \begintext


Rosetta Target Body DSK Surface ID Codes -- Definition Section
========================================================================

   This section contains name to ID mappings for the Rosetta target
   body DSK surfaces. These mappings are supported by all SPICE
   toolkits with integrated DSK capabilities (version N0066 or later).

   Comet 67P/Churyumov-Gerasimenko Surface name/IDs:

          DSK Surface Name          ID    Body ID
      ===========================  =====  =======

      ROS_CG_M004_NSPCESA_N_V1     11000  1000012

      ROS_CG_K006_OSPCLPS_N_V1     22000  1000012
      ROS_CG_K012_OSPCLPS_N_V1     22001  1000012
      ROS_CG_K024_OSPCLPS_N_V1     22002  1000012
      ROS_CG_K050_OSPCLPS_N_V1     22003  1000012
      ROS_CG_K096_OSPCLPS_N_V1     22004  1000012
      ROS_CG_K195_OSPCLPS_N_V1     22005  1000012
      ROS_CG_K399_OSPCLPS_N_V1     22006  1000012
      ROS_CG_K786_OSPCLPS_N_V1     22007  1000012

      ROS_CG_K006_OMSDLAM_N_V1     23000  1000012
      ROS_CG_K012_OMSDLAM_N_V1     23001  1000012
      ROS_CG_K024_OMSDLAM_N_V1     23002  1000012
      ROS_CG_K048_OMSDLAM_N_V1     23003  1000012
      ROS_CG_K098_OMSDLAM_N_V1     23004  1000012
      ROS_CG_K191_OMSDLAM_N_V1     23005  1000012
      ROS_CG_K391_OMSDLAM_N_V1     23006  1000012
      ROS_CG_K760_OMSDLAM_N_V1     23007  1000012
      ROS_CG_M001_OMSDLAM_N_V1     23008  1000012


   Name-ID Mapping keywords:

   \begindata

      NAIF_SURFACE_NAME += 'ROS_CG_M004_NSPCESA_N_V1'
      NAIF_SURFACE_CODE += 11000
      NAIF_SURFACE_BODY += 1000012

      NAIF_SURFACE_NAME += 'ROS_CG_K006_OSPCLPS_N_V1'
      NAIF_SURFACE_CODE += 22000
      NAIF_SURFACE_BODY += 1000012

      NAIF_SURFACE_NAME += 'ROS_CG_K012_OSPCLPS_N_V1'
      NAIF_SURFACE_CODE += 22001
      NAIF_SURFACE_BODY += 1000012

      NAIF_SURFACE_NAME += 'ROS_CG_K024_OSPCLPS_N_V1'
      NAIF_SURFACE_CODE += 22002
      NAIF_SURFACE_BODY += 1000012

      NAIF_SURFACE_NAME += 'ROS_CG_K050_OSPCLPS_N_V1'
      NAIF_SURFACE_CODE += 22003
      NAIF_SURFACE_BODY += 1000012

      NAIF_SURFACE_NAME += 'ROS_CG_K096_OSPCLPS_N_V1'
      NAIF_SURFACE_CODE += 22004
      NAIF_SURFACE_BODY += 1000012

      NAIF_SURFACE_NAME += 'ROS_CG_K195_OSPCLPS_N_V1'
      NAIF_SURFACE_CODE += 22005
      NAIF_SURFACE_BODY += 1000012

      NAIF_SURFACE_NAME += 'ROS_CG_K399_OSPCLPS_N_V1'
      NAIF_SURFACE_CODE += 22006
      NAIF_SURFACE_BODY += 1000012

      NAIF_SURFACE_NAME += 'ROS_CG_K786_OSPCLPS_N_V1'
      NAIF_SURFACE_CODE += 22007
      NAIF_SURFACE_BODY += 1000012

      NAIF_SURFACE_NAME += 'ROS_CG_K006_OMSDLAM_N_V1'
      NAIF_SURFACE_CODE += 23000
      NAIF_SURFACE_BODY += 1000012

      NAIF_SURFACE_NAME += 'ROS_CG_K012_OMSDLAM_N_V1'
      NAIF_SURFACE_CODE += 23001
      NAIF_SURFACE_BODY += 1000012

      NAIF_SURFACE_NAME += 'ROS_CG_K024_OMSDLAM_N_V1'
      NAIF_SURFACE_CODE += 23002
      NAIF_SURFACE_BODY += 1000012

      NAIF_SURFACE_NAME += 'ROS_CG_K048_OMSDLAM_N_V1'
      NAIF_SURFACE_CODE += 23003
      NAIF_SURFACE_BODY += 1000012

      NAIF_SURFACE_NAME += 'ROS_CG_K098_OMSDLAM_N_V1'
      NAIF_SURFACE_CODE += 23004
      NAIF_SURFACE_BODY += 1000012

      NAIF_SURFACE_NAME += 'ROS_CG_K191_OMSDLAM_N_V1'
      NAIF_SURFACE_CODE += 23005
      NAIF_SURFACE_BODY += 1000012

      NAIF_SURFACE_NAME += 'ROS_CG_K391_OMSDLAM_N_V1'
      NAIF_SURFACE_CODE += 23006
      NAIF_SURFACE_BODY += 1000012

      NAIF_SURFACE_NAME += 'ROS_CG_K760_OMSDLAM_N_V1'
      NAIF_SURFACE_CODE += 23007
      NAIF_SURFACE_BODY += 1000012

      NAIF_SURFACE_NAME += 'ROS_CG_M001_OMSDLAM_N_V1'
      NAIF_SURFACE_CODE += 23008
      NAIF_SURFACE_BODY += 1000012

   \begintext


   Asteroid 21 Lutetia Surface name/IDs:

          DSK Surface Name          ID    Body ID
      ===========================  =====  =======

      ROS_LU_K003_OSPCLAM_N_V1      1000  2000021
      ROS_LU_K006_OSPCLAM_N_V1      1001  2000021
      ROS_LU_K012_OSPCLAM_N_V1      1002  2000021
      ROS_LU_K025_OSPCLAM_N_V1      1003  2000021
      ROS_LU_K048_OSPCLAM_N_V1      1004  2000021
      ROS_LU_K098_OSPCLAM_N_V1      1005  2000021
      ROS_LU_K190_OSPCLAM_N_V1      1006  2000021
      ROS_LU_K240_OSPCLAM_N_V1      1007  2000021
      ROS_LU_K380_OSPCLAM_N_V1      1008  2000021
      ROS_LU_K780_OSPCLAM_N_V1      1009  2000021
      ROS_LU_M002_OSPCLAM_N_V1      1010  2000021
      ROS_LU_M003_OSPCLAM_N_V1      1011  2000021


   Name-ID Mapping keywords:

   \begindata

      NAIF_SURFACE_NAME += 'ROS_LU_K003_OSPCLAM_N_V1'
      NAIF_SURFACE_CODE += 1000
      NAIF_SURFACE_BODY += 2000021

      NAIF_SURFACE_NAME += 'ROS_LU_K006_OSPCLAM_N_V1'
      NAIF_SURFACE_CODE += 1001
      NAIF_SURFACE_BODY += 2000021

      NAIF_SURFACE_NAME += 'ROS_LU_K012_OSPCLAM_N_V1'
      NAIF_SURFACE_CODE += 1002
      NAIF_SURFACE_BODY += 2000021

      NAIF_SURFACE_NAME += 'ROS_LU_K025_OSPCLAM_N_V1'
      NAIF_SURFACE_CODE += 1003
      NAIF_SURFACE_BODY += 2000021

      NAIF_SURFACE_NAME += 'ROS_LU_K048_OSPCLAM_N_V1'
      NAIF_SURFACE_CODE += 1004
      NAIF_SURFACE_BODY += 2000021

      NAIF_SURFACE_NAME += 'ROS_LU_K098_OSPCLAM_N_V1'
      NAIF_SURFACE_CODE += 1005
      NAIF_SURFACE_BODY += 2000021

      NAIF_SURFACE_NAME += 'ROS_LU_K190_OSPCLAM_N_V1'
      NAIF_SURFACE_CODE += 1006
      NAIF_SURFACE_BODY += 2000021

      NAIF_SURFACE_NAME += 'ROS_LU_K240_OSPCLAM_N_V1'
      NAIF_SURFACE_CODE += 1007
      NAIF_SURFACE_BODY += 2000021

      NAIF_SURFACE_NAME += 'ROS_LU_K380_OSPCLAM_N_V1'
      NAIF_SURFACE_CODE += 1008
      NAIF_SURFACE_BODY += 2000021

      NAIF_SURFACE_NAME += 'ROS_LU_K780_OSPCLAM_N_V1'
      NAIF_SURFACE_CODE += 1009
      NAIF_SURFACE_BODY += 2000021

      NAIF_SURFACE_NAME += 'ROS_LU_M002_OSPCLAM_N_V1'
      NAIF_SURFACE_CODE += 1010
      NAIF_SURFACE_BODY += 2000021

      NAIF_SURFACE_NAME += 'ROS_LU_M003_OSPCLAM_N_V1'
      NAIF_SURFACE_CODE += 1011
      NAIF_SURFACE_BODY += 2000021

   \begintext


   Asteroid 2867 Steins Surface name/IDs:

          DSK Surface Name          ID    Body ID
      ===========================  =====  =======

      ROS_ST_K020_OSPCLAM_N_V1      1000  2002867

   Name-ID Mapping keywords:

   \begindata

      NAIF_SURFACE_NAME += 'ROS_ST_K020_OSPCLAM_N_V1'
      NAIF_SURFACE_CODE += 1000
      NAIF_SURFACE_BODY += 2002867

   \begintext

End of FK file.
