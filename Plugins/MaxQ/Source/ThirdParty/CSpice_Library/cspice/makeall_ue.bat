cd /D %1

if not exist "..\lib\win64\cspice.lib" (

echo Compiling CSpice Toolkit - this takes a while, please wait!

rem fix a canceled build that left zzsecprt.c renamed as zzsecprt.x
if not exist %1\src\cspice\zzsecprt.c (
    rename %1\src\cspice\zzsecprt.x zzsecprt.c
)

SET _CL_=/nologo /Z7
SET _LINK_=/NOLOGO /MD /DEBUG

pushd .

rem from makeall.bat
cd src
rem
rem Creating cspice
rem
cd cspice
call mkprodct.bat
cd ..

popd

if not exist "..\lib\win64" (
    mkdir "..\lib\win64"
)

copy .\lib\cspice.lib ..\lib\win64
copy .\src\cspice\*.pdb ..\lib\win64

) else (
    echo CSpice Toolkit - cspice.lib found
)

