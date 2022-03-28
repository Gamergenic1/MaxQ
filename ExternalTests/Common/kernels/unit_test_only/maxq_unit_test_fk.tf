KPL/FK

File name: maxq_unit_test_fk.fk
FRAMES KERNEL FILE
===========================================================================

MAXQ UNIT TESTS ONLY - NOT FOR USE OR DISTRIBUTION FOR ANY OTHER PURPOSE.  

This SPICE kernel is intended to support operation unit-
texting MaxQ.  MaxQ is an integration of Spice with
Unreal Engine 5.


        \begindata
        NAIF_BODY_CODE  += ( 9995, 9994, 9993, 9899 )
        NAIF_BODY_NAME  += ( 'FAKEBODY9995', 'FAKEBODY9994', 'FAKEBODY9993', 'FAKEBODY9899' )

        FRAME_FAKEBODY9995_PCK =  1400000
        FRAME_1400000_NAME     = 'FAKEBODY9995_PCK'
        FRAME_1400000_CLASS    =  2
        FRAME_1400000_CENTER   = 9995
        FRAME_1400000_CLASS_ID = 9995

        FRAME_IAU_FAKEBODY9995 = 1400001
        FRAME_1400001_NAME     = 'IAU_FAKEBODY9995'
        FRAME_1400001_CLASS    = 4
        FRAME_1400001_CLASS_ID = 1400001
        FRAME_1400001_CENTER   = 9995

        TKFRAME_1400001_RELATIVE = 'FAKEBODY9995_PCK'
        TKFRAME_1400001_SPEC     = 'MATRIX'
        TKFRAME_1400001_MATRIX   = ( 1 0 0
                                     0 1 0
                                     0 0 1 )

        FRAME_FAKEBODY9994_PA  =  1400002
        FRAME_1400002_NAME     = 'FAKEBODY9994_PA'
        FRAME_1400002_CLASS    =  2
        FRAME_1400002_CENTER   = 9994
        FRAME_1400002_CLASS_ID = 9994

        FRAME_IAU_FAKEBODY9994 = 1400003
        FRAME_1400003_NAME     = 'IAU_FAKEBODY9994'
        FRAME_1400003_CLASS    = 4
        FRAME_1400003_CLASS_ID = 1400003
        FRAME_1400003_CENTER   = 9994

        TKFRAME_1400003_SPEC     = 'MATRIX'
        TKFRAME_1400003_RELATIVE = 'FAKEBODY9994_PA'
        TKFRAME_1400003_MATRIX   = ( 1 0 0
                                     0 1 0
                                     0 0 1 )

        FRAME_FAKEBODY9993_PA  =  1400200
        FRAME_1400200_NAME     = 'FAKEBODY9993_PA'
        FRAME_1400200_CLASS    =  2
        FRAME_1400200_CENTER   = 9993
        FRAME_1400200_CLASS_ID = 9993

        FRAME_IAU_FAKEBODY9899 =  1400201
        FRAME_1400201_NAME     = 'IAU_FAKEBODY9899'
        FRAME_1400201_CLASS    =  2
        FRAME_1400201_CENTER   = 9899
        FRAME_1400201_CLASS_ID = 1400201

        \begintext


