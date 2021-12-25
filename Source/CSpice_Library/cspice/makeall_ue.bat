echo Compiling CSpice Toolkit - this takes a while, please wait!

rem fix a canceled build that left zzsecprt.c renamed as zzsecprt.x
if not exist "%1\src\cspice\zzsecprt.c" (
    rename "%1\src\cspice\zzsecprt.x" zzsecprt.c
)

SET _CL_=/nologo /Zi
SET _LINK_=/NOLOGO /MD /DEBUG
cd "%1"

echo push
pushd .

echo cd
rem from makeall.bat
cd src
rem
rem Creating cspice
rem
cd cspice
call mkprodct.bat

popd

if not exist "..\lib\win64" (
    mkdir "..\lib\win64"
)

copy .\lib\cspice.lib ..\lib\win64
copy .\src\cspice\*.pdb ..\lib\win64
