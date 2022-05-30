echo This script builds the SPICE delivery
echo for the cspice package of the toolkit.
echo
echo The script must be executed from the
echo cspice directory.
echo
cd src
echo
echo Creating cspice
echo
cd cspice
chmod u+x mkprodct.csh; ./mkprodct.csh
cd ..
echo UE Toolkit Build Complete
