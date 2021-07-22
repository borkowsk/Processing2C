#!/bin/bash
# Processing2C installation script
#

EDIT=nano

set -e # https://intoli.com/blog/exit-on-errors-in-bash-scripts/

echo "Running" `realpath $0`
echo -e "\n\tThis script stops on any error\!\n\tWhen it stop, remove source of the error & run it again!\n" 

function pause(){ #https://www.cyberciti.biz/tips/linux-unix-pause-command.html
 read -s -n 1 -p "Press ^C to abort, any key to continue . . ."
 echo ""
}

#WBRTM="/home/Kowalski/WBRTM"
SYMSHELL=`realpath "../SymShellLight"`
PROC2DIR=`realpath "./"`

echo -e "$SYMSHELL\n$PROC2DIR"
echo -e "Are the paths correct?\n"
echo -e "If not, break script, edit it and run it again!"
pause

#prepare config.dat
cp scripts/config.dat.tmpl scripts/config.dat
echo SYMSHELL=${SYMSHELL} >> scripts/config.dat
echo PROC2DIR=${PROC2DIR} >> scripts/config.dat
echo "see scripts/config.dat !"

#prepare CMakeLists.txt
cat lib/CMakeLists.tmpl |\
sed "s|%%PROC2DIR%%|\"$PROC2DIR\"|" |\
sed "s|%%SYMSHELL%%|\"$SYMSHELL\"|" > lib/CMakeLists.txt
echo "see lib/CMakeLists.txt !"

echo "Ready to make library!"
pause

pushd lib/ 
cmake . 
make
popd

date > configured.txt #FINALLY SUCCESFULL

echo "Ready to make examples?"
echo "(You can skip this step just by Cntr-C at this moment)"
pause

rm -f configured.txt

pushd "PROJECTS/"
./_translateProjects.sh
echo "SELECT EXAMPLES by REMOVING 'EXCLUDE_FROM_ALL' CLAUSULES"
$EDIT CMakeLists.txt
cmake . 
make
popd

date > configured.txt #FINALLY SUCCESFULL
echo "With some examples" >> configured.txt
echo -e "\nSCRIPT" `realpath $0` "FINISHED"



