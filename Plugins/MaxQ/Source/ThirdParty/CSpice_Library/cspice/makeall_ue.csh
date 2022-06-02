echo This script builds the SPICE delivery
echo for the cspice package of the toolkit.
cd $1
if test -f "../lib/Mac/cspice.a"; then
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
fi
