KPL/FK

Frame (FK) kernel file for Hera Didymos-Nadir Power Optimized
===============================================================================

   This frames kernel overwrites the Hera spacecraft frame (HERA_SPACECRAFT)
   definition from [3] and maps it to the Hera Didymos power optimized
   frame (HERA_DIDYMOS_NPO) defined in [4].

   This allows the user to use the existing alignments and instrument frame
   definitions in the Hera frames kernel (see ref [3]) to perform instrument
   specific mission analysis and attitude dependent science opportunity
   identification. Please refer to the section ``Using this frame'' for further
   details.

   NOTE THAT BY USING THIS KERNEL, THE HERA_SPACECRAFT FRAME WILL BE
   MAPPED TO THE HERA_DIDYMOS_NPO FRAME, AND ANY CK PROVIDING ORIENTATION FOR
   THE HERA_SPACECRAFT FRAME WILL NOT BE USED BY THE APPLICATION SOFTWARE,
   EVEN IF IT IS LOADED IN THE KERNEL POOL.


Version and Date
-------------------------------------------------------------------------------

   Version 0.0 -- July 30, 2020 -- Marc Costa Sitja, ESAC/ESA

      Initial version. Based on hera_sc_didymain_npo_v01.tf


References
-------------------------------------------------------------------------------

   [1]   "Frames Required Reading"

   [2]   "Kernel Pool Required Reading"

   [3]   Hera Frames Definition Kernel (FK), latest version.


Contact Information
-------------------------------------------------------------------------------

   If you have any questions regarding this file contact SPICE support at
   ESAC:

           Marc Costa Sitja
           (+34) 91-8131-457
           marc.costa@esa.int, esa_spice@sciops.esa.int


Implementation Notes
-------------------------------------------------------------------------------

   This file is used by the SPICE system as follows: programs that make
   use of this frame kernel must "load" the kernel normally during
   program initialization. Loading the kernel associates the data items
   with their names in a data structure called the "kernel pool". The
   routine that loads a kernel into the pool is shown below:

      FORTRAN: (SPICELIB)

         CALL FURNSH ( frame_kernel_name )

      C: (CSPICE)

         furnsh_c ( frame_kernel_name );

      IDL: (ICY)

         cspice_furnsh, frame_kernel_name

      MATLAB: (MICE)

         cspice_furnsh ( 'frame_kernel_name' )

   This file was created and may be updated with a text editor or word
   processor.


Using this frame
-------------------------------------------------------------------------------

   This frames have been implemented to overwrite the HERA_SPACECRAFT
   frame definition provided in the Hera Frames Definitions kernel
   ([3]) and map it to the HERA_DIDYMOS_NPO frame defined in the Hera Frames
   Definitions kernel.

   In order to make use of this frames kernel, this file MUST BE LOADED
   AFTER the Hera frames definition kernel and the TGO Science
   Operations Frames Definition kernel.

   A metakernel defined to use this file should look like this:

         ...

              $DATA/fk/hera_v00.tf
              $DATA/fk/hera_sc_didymos_npo_v00.tf

         ...


   NOTE THAT BY USING THIS KERNEL, THE HERA_SPACECRAFT FRAME WILL BE
   MAPPED TO THE HERA_DIDYMOS_NPO FRAME, AND ANY CK PROVIDING ORIENTATION FOR
   THE HERA_SPACECRAFT FRAME WILL NOT BE USED BY THE APPLICATION SOFTWARE,
   EVEN IF IT IS LOADED IN THE KERNEL POOL.


  \begindata

      FRAME_-999000_CLASS       = 4
      TKFRAME_-999000_RELATIVE  = 'HERA_DIDYMOS_NPO'
      TKFRAME_-999000_SPEC      = 'MATRIX'
      TKFRAME_-999000_MATRIX    = ( 1   0   0
                                    0   1   0
                                    0   0   1 )

  \begintext


End of FK file.