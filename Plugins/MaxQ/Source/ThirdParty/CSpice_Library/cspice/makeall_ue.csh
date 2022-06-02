echo This script builds the SPICE library
echo for the cspice package of the toolkit.
cd $2
if ( -f "../lib/Mac/cspice.a" ) then
cd src
echo
echo Creating cspice
echo
cd cspice
chmod u+x mkprodct.csh; ./mkprodct.csh
cd ..
cp ./lib/cspice.a ../lib/Mac
echo UE Toolkit Build Complete
else
echo CSpice Toolkit - cspice.a found
endif
