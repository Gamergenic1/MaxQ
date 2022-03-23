
KPL/MK

File name: maxq_unit_test_metakernel.tm

This meta-kernel is intended to support operation unit-
texting MaxQ.  MaxQ is an integration of Spice with
Unreal Engine 5.

In order for an application to use this meta-kernel, the
kernels referenced here must be present in the user's
current working directory.

030201AP_SK_SM546_T45.bsp validity range:
2004 JUN 11 05:01 : 04 - 2004 JUN 12 12:01:04
CASSINI (-82)

020514_SE_SAT105.bsp validity range:
2004 JUN 11 05:01 : 04 - 2004 JUN 12 12:01:04
Bodies: MIMAS (601)      DIONE (604)      HYPERION (607)   SATURN (699)
ENCELADUS(602)  RHEA(605)       IAPETUS(608)
   TETHYS(603)     TITAN(606)      PHOEBE(609)

981005_PLTEPH-DE405S.bsp validity range:
2004 JUN 11 05:01:04 - 2004 JUN 12 12:01:04
Bodies: MERCURY BARYCENTER(1)  SATURN BARYCENTER(6)   MERCURY(199)
VENUS BARYCENTER(2)    URANUS BARYCENTER(7)   VENUS(299)
EARTH BARYCENTER(3)    NEPTUNE BARYCENTER(8)  MOON(301)
MARS BARYCENTER(4)     PLUTO BARYCENTER(9)    EARTH(399)
JUPITER BARYCENTER(5)  SUN(10)                MARS(499)


\begindata

KERNELS_TO_LOAD = ( 'naif0008.tls',
                    '020514_SE_SAT105.bsp',
                    '030201AP_SK_SM546_T45.bsp',
                    '981005_PLTEPH-DE405S.bsp' )

\begintext