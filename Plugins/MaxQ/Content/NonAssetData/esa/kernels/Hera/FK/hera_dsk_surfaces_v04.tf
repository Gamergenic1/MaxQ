KPL/FK

Hera Target Body DSK Surface ID Codes
========================================================================

   This frame kernel contains a set of Hera Target Body DSK Surface ID
   Codes for the Didymos system.


Version and Date
------------------------------------------------------------------------

   Version 0.4 -- June 17, 2021 -- Alfredo Escalante Lopez, ESAC/ESA

      Added HERA_DIMORPHOS_K001_V02 and HERA_DIMORPHOS_K003_V01 surfaces
      ID associations.

   Version 0.3 -- July 30, 2020 -- Marc Costa Sitja, ESAC/ESA

      Updated NAIF Surface Names and IDs for the binary asteroid system:
      HERA_DIDYMOS_K001_V01, HERA_DIMORPHOS_K001_V01.

   Version 0.2 -- September 9, 2019 -- Marc Costa Sitja, ESAC/ESA

      Updated Hera ID according to standard ESOC provisional numbering:
      from -667 to -999. Changed DIDYMOS to DIDYMAIN and added the IDs.

   Version 0.1 -- March 1, 2019 -- Marc Costa Sitja, ESAC/ESA

      Added draft version of Didymoon surfaces.

   Version 0.0 -- March 1, 2019 -- Marc Costa Sitja, ESAC/ESA

      First version.


References
------------------------------------------------------------------------

   1. ``Frames Required Reading''

   2. ``Kernel Pool Required Reading''

   3. ``DS-Kernel Required Reading''

   4. Hera Frames Kernel


Contact Information
------------------------------------------------------------------------

   If you have any questions regarding this file contact SPICE support at
   ESAC:

           Marc Costa Sitja
           (+34) 91-8131-457
           marc.costa@esa.int, esa_spice@sciops.esa.int


Implementation Notes
------------------------------------------------------------------------

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


Definition Section
------------------------------------------------------------------------

   This section contains name to ID mappings for the Hera target
   body DSK surfaces. These mappings are supported by all SPICE
   toolkits with integrated DSK capabilities (version N0066 or later).

   Didymos Surface name/IDs:

          DSK Surface Name          ID        Body ID
      ===========================  =========  =======

      HERA_DIDYMOS_K001_V01        658030001  -658030
      HERA_DIMORPHOS_K001_V01      658031001  -658031


   Name-ID Mapping keywords:

   \begindata

      NAIF_SURFACE_NAME   += 'HERA_DIDYMOS_K001_V01'
      NAIF_SURFACE_CODE   += 658030001
      NAIF_SURFACE_BODY   += -658030

      NAIF_SURFACE_NAME   += 'HERA_DIMORPHOS_K001_V01'
      NAIF_SURFACE_CODE   += 658031001
      NAIF_SURFACE_BODY   += -658031

      NAIF_SURFACE_NAME   += 'HERA_DIMORPHOS_K001_V02'
      NAIF_SURFACE_CODE   += 658031002
      NAIF_SURFACE_BODY   += -658031

      NAIF_SURFACE_NAME   += 'HERA_DIMORPHOS_K003_V01'
      NAIF_SURFACE_CODE   += 658031003
      NAIF_SURFACE_BODY   += -658031

   \begintext


End of FK file.