#!/bin/bash

function pause(){ #https://www.cyberciti.biz/tips/linux-unix-pause-command.html
 read -s -n 1 -p "Press ^C to abort, any key to continue . . ."
 echo ""
}

#WBRTM="/home/Kowalski/WBRTM"
SYMSHELL=`realpath "../SymShellLight"`
PROC2DIR=`realpath "./"`

echo -e "$SYMSHELL\n$PROC2DIR"
echo -e "Are the paths correct?\n"
pause

#prepare config.dat
cp scripts/config.dat.tmpl scripts/config.dat
echo SYMSHELL=${SYMSHELL} >> scripts/config.dat
echo PROC2DIR=${PROC2DIR} >> scripts/config.dat
echo "see scripts/config.dat"

#prepare CMakeLists.txt
cat lib/CMakeLists.tmpl |\
sed "s|%%PROC2DIR%%|\"$PROC2DIR\"|" |\
sed "s|%%SYMSHELL%%|\"$SYMSHELL\"|" > lib/CMakeLists.txt
echo "see lib/CMakeLists.txt"

echo "Ready to make library!"
pause

pushd lib/ 
cmake . && make
popd

echo "Ready to make examples!"
pause

pushd "PROJECTS/"
./_translateProjects.sh
cmake . && make
popd
