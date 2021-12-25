/*

-Procedure eul2xf_c ( Euler angles and derivative to transformation)

-Abstract
 
   This routine computes a state transformation from an Euler angle 
   factorization of a rotation and the derivatives of those Euler 
   angles. 
 
-Disclaimer

   THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE
   CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S.
   GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE
   ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE
   PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS"
   TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY
   WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A
   PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC
   SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE
   SOFTWARE AND RELATED MATERIALS, HOWEVER USED.

   IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA
   BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT
   LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND,
   INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS,
   REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE
   REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY.

   RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF
   THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY
   CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE
   ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE.

-Required_Reading
 
   ROTATION
 
-Keywords
 
   ANGLES 
   STATE 
   DERIVATIVES 
 
*/

   #include "SpiceUsr.h"
   #include "SpiceZfc.h"
   #undef eul2xf_c
   

   void eul2xf_c ( ConstSpiceDouble    eulang[6],
                   SpiceInt            axisa,
                   SpiceInt            axisb,
                   SpiceInt            axisc,
                   SpiceDouble         xform [6][6] )
/*

-Brief_I/O
 
   VARIABLE  I/O  DESCRIPTION 
   --------  ---  -------------------------------------------------- 
   eulang     I   An array of Euler angles and their derivatives. 
   axisa      I   Axis A of the Euler angle factorization. 
   axisb      I   Axis B of the Euler angle factorization. 
   axisc      I   Axis C of the Euler angle factorization. 
   xform      O   A state transformation matrix. 
 
-Detailed_Input
 
 
   eulang      is the set of Euler angles corresponding to the 
               specified factorization. 
 
               If we represent r as shown here: 
 
                   r =  [ alpha ]     [ beta ]     [ gamma ] 
                                 axisa        axisb         axisc 
 
               then 
 
 
                  eulang[0] = alpha 
                  eulang[1] = beta 
                  eulang[2] = gamma 
                  eulang[3] = dalpha/dt 
                  eulang[4] = dbeta/dt 
                  eulang[5] = dgamma/dt 
 
 
   axisa       are the axes desired for the factorization of r. 
   axisb       All must be in the range from 1 to 3.  Moreover 
   axisc       it must be the case that axisa and axisb are distinct 
               and that axisb and axisc are distinct. 
 
               Every rotation matrix can be represented as a product 
               of three rotation matrices about the principal axes 
               of a reference frame. 
 
                   r =  [ alpha ]     [ beta ]     [ gamma ] 
                                 axisa        axisb         axisc 
 
               The value 1 corresponds to the X axis. 
               The value 2 corresponds to the Y axis. 
               The value 3 corresponds to the Z axis. 
               
 
-Detailed_Output
 
   xform       is the state transformation corresponding r and dr/dt 
               as described above.  Pictorially, 
 
                    [       |        ] 
                    |  r    |    0   | 
                    |       |        | 
                    |-------+--------| 
                    |       |        | 
                    | dr/dt |    r   | 
                    [       |        ] 
 
               where r is a rotation that varies with respect to time 
               and dr/dt is its time derivative. 
 
-Parameters
 
   None. 
 
-Exceptions
 
   All erroneous inputs are diagnosed by routines in the call 
   tree to this routine.  These include 
 
   1)   If any of axisa, axisb, or axisc do not have values in 
 
           { 1, 2, 3 }, 
 
        then the error SPICE(INPUTOUTOFRANGE) is signaled. 
 
-Files
 
   None. 
 
-Particulars
 
   This function is intended to provide an inverse for the function 
   xf2eul_c.    
 
 
   A word about notation:  the symbol 
 
      [ x ] 
           i 
 
   indicates a coordinate system rotation of x radians about the 
   ith coordinate axis.  To be specific, the symbol 
 
      [ x ] 
           1 
 
   indicates a coordinate system rotation of x radians about the 
   first, or x-, axis; the corresponding matrix is 
 
      +-                    -+ 
      |  1      0       0    | 
      |                      | 
      |  0    cos(x)  sin(x) |. 
      |                      | 
      |  0   -sin(x)  cos(x) | 
      +-                    -+ 
 
   Remember, this is a COORDINATE SYSTEM rotation by x radians; this 
   matrix, when applied to a vector, rotates the vector by -x 
   radians, not x radians.  Applying the matrix to a vector yields 
   the vector's representation relative to the rotated coordinate 
   system. 
 
   The analogous rotation about the second, or y-, axis is 
   represented by 
 
      [ x ] 
           2 
 
   which symbolizes the matrix 
 
      +-                    -+ 
      | cos(x)   0   -sin(x) | 
      |                      | 
      |  0       1      0    |, 
      |                      | 
      | sin(x)   0    cos(x) | 
      +-                    -+ 
 
   and the analogous rotation about the third, or z-, axis is 
   represented by 
 
      [ x ] 
           3 
 
   which symbolizes the matrix 
 
      +-                    -+ 
      |  cos(x)  sin(x)   0  | 
      |                      | 
      | -sin(x)  cos(x)   0  |. 
      |                      | 
      |  0        0       1  | 
      +-                    -+ 
 
 
   The input matrix is assumed to be the product of three 
   rotation matrices, each one of the form 
 
      +-                    -+ 
      |  1      0       0    | 
      |                      | 
      |  0    cos(r)  sin(r) |     (rotation of r radians about the 
      |                      |      x-axis), 
      |  0   -sin(r)  cos(r) | 
      +-                    -+ 
 
 
      +-                    -+ 
      | cos(s)   0   -sin(s) | 
      |                      | 
      |  0       1      0    |     (rotation of s radians about the 
      |                      |      y-axis), 
      | sin(s)   0    cos(s) | 
      +-                    -+ 
 
   or 
 
      +-                    -+ 
      |  cos(t)  sin(t)   0  | 
      |                      | 
      | -sin(t)  cos(t)   0  |     (rotation of t radians about the 
      |                      |      z-axis), 
      |  0        0       1  | 
      +-                    -+ 
 
   where the second rotation axis is not equal to the first or 
   third.  Any rotation matrix can be factored as a sequence of 
   three such rotations, provided that this last criterion is met. 
 
   This routine is related to the routine eul2xf_c which produces 
   a state transformation from an input set of axes, Euler angles 
   and derivatives. 
 
   The two function calls shown here will not change xform except for 
   round off errors. 
 
      xf2eul_c ( xform,  axisa, axisb, axisc, eulang, &unique );
      eul2xf_c ( eulang, axisa, axisb, axisc, xform           ); 
 
   On the other hand the two calls 
 
      eul2xf_c ( eulang, axisa, axisb, axisc, xform           ); 
      xf2eul_c ( xform,  axisa, axisb, axisc, eulang, &unique );
 
   will leave eulang unchanged only if the components of eulang 
   are in the range produced by xf2eul_c and the Euler representation 
   of the rotation component of xform is unique within that range. 

 
-Examples
 
   Suppose you have a set of Euler angles and their derivatives 
   for a 3 1 3 rotation, and that you would like to determine 
   the equivalent angles and derivatives for a 1 2 3 rotation. 
 
       r = [alpha]  [beta]  [gamma] 
                  3       1        3 
 
       r = [roll]  [pitch]  [yaw] 
                 1        2      3 
 
   The following code fragment will perform the desired computation. 
 
      abgang[0] = alpha; 
      abgang[1] = beta; 
      abgang[2] = gamma; 
      abgang[3] = dalpha; 
      abgang[4] = dbeta; 
      abgang[5] = dgamma; 
 
      eul2xf_c ( abgang, 3, 1, 3, xform  ); 
      xf2eul_c ( xform,  1, 2, 3, rpyang, &unique ); 
 
      roll     = rpyang[0]; 
      pitch    = rpyang[1]; 
      yaw      = rpyang[2]; 
      droll    = rpyang[3]; 
      dpitch   = rpyang[4]; 
      dyaw     = rpyang[5];
       
 
-Restrictions
 
   None. 
 
-Literature_References
 
   None. 
 
-Author_and_Institution
 
   N.J. Bachman    (JPL)
   W.L. Taber      (JPL) 
   
-Version

   -CSPICE Version 2.0.1, 25-APR-2007 (EDW)

      Corrected code in Examples section, example showed
      a xf2eul_c call:
      
            xf2eul_c( xform,  1, 2, 3, rpyang); 
       
      The proper form of the call:
      
            xf2eul_c( xform,  1, 2, 3, rpyang, &unique );

   -CSPICE Version 2.0.0, 31-OCT-2005 (NJB)

      Restriction that second axis must differ from the first
      and third was removed.

   -CSPICE Version 1.0.1, 03-JUN-2003 (EDW)

      Correct typo in Procedure line.
 
   -CSPICE Version 1.0.0, 18-MAY-1999 (WLT) (NJB)

-Index_Entries
 
   State transformation from Euler angles and derivatives 
 
-&
*/



{ /* Begin xf2eul_c */


   /*
   Participate in error tracing.
   */
   chkin_c ( "eul2xf_c" );
   
   
   eul2xf_ (  ( doublereal * ) eulang,
              ( integer    * ) &axisa,
              ( integer    * ) &axisb,
              ( integer    * ) &axisc,
              ( doublereal * ) xform   );
              
   /*
   Convert the output matrix to row-major order.
   */
   xpose6_c ( xform, xform );
   
   
   chkout_c ( "eul2xf_c" );
   
} /* End xf2eul_c */
   
