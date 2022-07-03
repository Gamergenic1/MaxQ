KPL/FK

File name: MaxQ-TRAPPIST_1-fk.fk
FRAMES KERNEL FILE
===========================================================================

MAXQ SAMPLE CONTENT ONLY - NOT FOR USE OR DISTRIBUTION FOR ANY OTHER PURPOSE.  

This SPICE kernel is intended as sample content for MaxQ Spaceflight
Toolkit.  MaxQ is an integration of Spice with Unreal Engine 5.


Define NAIF ID Code to NAIF Name mappings...
(obviously, these did not come from NAIF, but that's the terminology.)

        \begindata
        NAIF_BODY_CODE  += ( 5009010, 5009000 )
        NAIF_BODY_NAME  += ( 'TRAPPIST_1', 'TRAPPIST_1_BARYCENTER' )

        NAIF_BODY_CODE  += ( 5009199, 5009001 )
        NAIF_BODY_NAME  += ( 'TRAPPIST_1B', 'TRAPPIST_1B_BARYCENTER' )

        NAIF_BODY_CODE  += ( 5009299, 5009002 )
        NAIF_BODY_NAME  += ( 'TRAPPIST_1C', 'TRAPPIST_1C_BARYCENTER' )

        NAIF_BODY_CODE  += ( 5009399, 5009003 )
        NAIF_BODY_NAME  += ( 'TRAPPIST_1D', 'TRAPPIST_1D_BARYCENTER' )

        NAIF_BODY_CODE  += ( 5009499, 5009004 )
        NAIF_BODY_NAME  += ( 'TRAPPIST_1E', 'TRAPPIST_1E_BARYCENTER' )

        NAIF_BODY_CODE  += ( 5009599, 5009005 )
        NAIF_BODY_NAME  += ( 'TRAPPIST_1F', 'TRAPPIST_1F_BARYCENTER' )

        NAIF_BODY_CODE  += ( 5009699, 5009006 )
        NAIF_BODY_NAME  += ( 'TRAPPIST_1G', 'TRAPPIST_1G_BARYCENTER' )

        NAIF_BODY_CODE  += ( 5009799, 5009007 )
        NAIF_BODY_NAME  += ( 'TRAPPIST_1H', 'TRAPPIST_1H_BARYCENTER' )

        \begintext


Define Reference Frames...

        \begindata
        TRAPPIST_1_BARYCENTER_PCK = 1500000
        FRAME_1500000_NAME     = 'TRAPPIST_1_BARYCENTER_PCK'
        FRAME_1500000_CLASS    =  2
        FRAME_1500000_CENTER   = 5009000
        FRAME_1500000_CLASS_ID = 5009000

        FRAME_TRAPPIST_1_PA  =  1500002
        FRAME_1500002_NAME     = 'TRAPPIST_1_PA'
        FRAME_1500002_CLASS    =  2
        FRAME_1500002_CENTER   = 5009010
        FRAME_1500002_CLASS_ID = 5009010

        FRAME_IAU_TRAPPIST_1 = 1500003
        FRAME_1500003_NAME     = 'IAU_TRAPPIST_1'
        FRAME_1500003_CLASS    = 4
        FRAME_1500003_CLASS_ID = 1500003
        FRAME_1500003_CENTER   = 5009010

        TKFRAME_1500003_SPEC     = 'MATRIX'
        TKFRAME_1500003_RELATIVE = 'TRAPPIST_1_PA'
        TKFRAME_1500003_MATRIX   = ( 1 0 0
                                     0 1 0
                                     0 0 1 )

        FRAME_TRAPPIST_1B_PA  =  1500104
        FRAME_1500104_NAME     = 'TRAPPIST_1B_PA'
        FRAME_1500104_CLASS    =  2
        FRAME_1500104_CENTER   = 5009199
        FRAME_1500104_CLASS_ID = 5009199

        FRAME_IAU_TRAPPIST_1B = 1500105
        FRAME_1500105_NAME     = 'IAU_TRAPPIST_1B'
        FRAME_1500105_CLASS    = 4
        FRAME_1500105_CLASS_ID = 1500105
        FRAME_1500105_CENTER   = 5009199

        TKFRAME_1500105_SPEC     = 'MATRIX'
        TKFRAME_1500105_RELATIVE = 'TRAPPIST_1B_PA'
        TKFRAME_1500105_MATRIX   = ( 1 0 0
                                     0 1 0
                                     0 0 1 )

        FRAME_TRAPPIST_1C_PA  =  1500206
        FRAME_1500206_NAME     = 'TRAPPIST_1C_PA'
        FRAME_1500206_CLASS    =  2
        FRAME_1500206_CENTER   = 5009299
        FRAME_1500206_CLASS_ID = 5009299

        FRAME_IAU_TRAPPIST_1C = 1500207
        FRAME_1500207_NAME     = 'IAU_TRAPPIST_1C'
        FRAME_1500207_CLASS    = 4
        FRAME_1500207_CLASS_ID = 1500207
        FRAME_1500207_CENTER   = 5009299

        TKFRAME_1500207_SPEC     = 'MATRIX'
        TKFRAME_1500207_RELATIVE = 'TRAPPIST_1C_PA'
        TKFRAME_1500207_MATRIX   = ( 1 0 0
                                     0 1 0
                                     0 0 1 )

        FRAME_TRAPPIST_1D_PA  =  1500308
        FRAME_1500308_NAME     = 'TRAPPIST_1D_PA'
        FRAME_1500308_CLASS    =  2
        FRAME_1500308_CENTER   = 5009399
        FRAME_1500308_CLASS_ID = 5009399

        FRAME_IAU_TRAPPIST_1D = 1500309
        FRAME_1500309_NAME     = 'IAU_TRAPPIST_1D'
        FRAME_1500309_CLASS    = 4
        FRAME_1500309_CLASS_ID = 1500309
        FRAME_1500309_CENTER   = 5009399

        TKFRAME_1500309_SPEC     = 'MATRIX'
        TKFRAME_1500309_RELATIVE = 'TRAPPIST_1D_PA'
        TKFRAME_1500309_MATRIX   = ( 1 0 0
                                     0 1 0
                                     0 0 1 )

        FRAME_TRAPPIST_1E_PA  =  1500410
        FRAME_1500410_NAME     = 'TRAPPIST_1E_PA'
        FRAME_1500410_CLASS    =  2
        FRAME_1500410_CENTER   = 5009499
        FRAME_1500410_CLASS_ID = 5009499

        FRAME_IAU_TRAPPIST_1E = 1500411
        FRAME_1500411_NAME     = 'IAU_TRAPPIST_1E'
        FRAME_1500411_CLASS    = 4
        FRAME_1500411_CLASS_ID = 1500411
        FRAME_1500411_CENTER   = 5009499

        TKFRAME_1500411_SPEC     = 'MATRIX'
        TKFRAME_1500411_RELATIVE = 'TRAPPIST_1E_PA'
        TKFRAME_1500411_MATRIX   = ( 1 0 0
                                     0 1 0
                                     0 0 1 )

        FRAME_TRAPPIST_1F_PA  =  1500512
        FRAME_1500512_NAME     = 'TRAPPIST_1F_PA'
        FRAME_1500512_CLASS    =  2
        FRAME_1500512_CENTER   = 5009599
        FRAME_1500512_CLASS_ID = 5009599

        FRAME_IAU_TRAPPIST_1F = 1500513
        FRAME_1500513_NAME     = 'IAU_TRAPPIST_1F'
        FRAME_1500513_CLASS    = 4
        FRAME_1500513_CLASS_ID = 1500513
        FRAME_1500513_CENTER   = 5009599

        TKFRAME_1500513_SPEC     = 'MATRIX'
        TKFRAME_1500513_RELATIVE = 'TRAPPIST_1F_PA'
        TKFRAME_1500513_MATRIX   = ( 1 0 0
                                     0 1 0
                                     0 0 1 )

        FRAME_TRAPPIST_1G_PA  =  1500614
        FRAME_1500614_NAME     = 'TRAPPIST_1G_PA'
        FRAME_1500614_CLASS    =  2
        FRAME_1500614_CENTER   = 5009699
        FRAME_1500614_CLASS_ID = 5009699

        FRAME_IAU_TRAPPIST_1G = 1500615
        FRAME_1500615_NAME     = 'IAU_TRAPPIST_1G'
        FRAME_1500615_CLASS    = 4
        FRAME_1500615_CLASS_ID = 1500615
        FRAME_1500615_CENTER   = 5009699

        TKFRAME_1500615_SPEC     = 'MATRIX'
        TKFRAME_1500615_RELATIVE = 'TRAPPIST_1G_PA'
        TKFRAME_1500615_MATRIX   = ( 1 0 0
                                     0 1 0
                                     0 0 1 )

        FRAME_TRAPPIST_1H_PA  =  1500716
        FRAME_1500716_NAME     = 'TRAPPIST_1H_PA'
        FRAME_1500716_CLASS    =  2
        FRAME_1500716_CENTER   = 5009799
        FRAME_1500716_CLASS_ID = 5009799

        FRAME_IAU_TRAPPIST_1H = 1500717
        FRAME_1500717_NAME     = 'IAU_TRAPPIST_1H'
        FRAME_1500717_CLASS    = 4
        FRAME_1500717_CLASS_ID = 1500717
        FRAME_1500717_CENTER   = 5009799

        TKFRAME_1500717_SPEC     = 'MATRIX'
        TKFRAME_1500717_RELATIVE = 'TRAPPIST_1H_PA'
        TKFRAME_1500717_MATRIX   = ( 1 0 0
                                     0 1 0
                                     0 0 1 )


        \begintext


