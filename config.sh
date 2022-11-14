#!/bin/bash
# Processing2C version 0.13 installation script
#

EDIT=nano

set -e # https://intoli.com/blog/exit-on-errors-in-bash-scripts/

source screen.ini

echo -e $COLOR2"Running"$COLOR1 `realpath $0` $NORMCO
echo -e "\n\tThis script stops on any error!\n\tWhen it stop, remove source of the error & run it again!\n" 

function pause(){ #https://www.cyberciti.biz/tips/linux-unix-pause-command.html
 echo -e $COLOR1""
 read -s -n 1 -p "Press ^C to abort, any key to continue . . ."
 echo -e $NORMCO""
}

#WBRTM="/home/Kowalski/WBRTM"
SYMSHELL=`realpath "../SymShellLight"`
PROC2DIR=`realpath "./"`

echo -e $COLOR2"Are the paths correct?\n"$NORMCO
echo -e "PROC2DIR=$PROC2DIR  #This toolbox whole path"
echo -e "SYMSHELL=$SYMSHELL  #SymShellLight toolbox whole path"
ls -d $PROC2DIR
ls -d $SYMSHELL
echo -e $COLOR2"If something is wrong, break script, edit it and run it again!"$NORMCO
pause

if [[ ! -d $SYMSHELL ]]
then
echo 
echo -e "Are you sure, that SymShellLight is cloned into directory $COLOR1 $SYMSHELL $NORMCO?"
echo -e "I can't find this toolbox, which is strictly required!"
echo
echo -e "How to install?"
echo
echo -e "In parent directory use the following commands:"$COLOR2
echo
echo -e "$ git clone git clone https://github.com/borkowsk/SymShellLight.git"
echo -e "$ cd SymShellLight"
echo -e "$ $EDIT README.md"
echo
echo -e $NORMCO"Then follow the compilation instruction."
exit -1
fi


#prepare config.dat
echo
cp scripts/config.dat.tmpl scripts/config.dat
echo SYMSHELL=${SYMSHELL} >> scripts/config.dat
echo PROC2DIR=${PROC2DIR} >> scripts/config.dat
echo -e "see $COLOR1 scripts/config.dat !"$NORMCO

#set variable with path in .profile
set +e
grep -q "P2Cscr" $HOME/.profile

if [  $? != 0  ]
then
##TODO #Any insertion of such configuration variables need consider __LAST_EXPORT__ mark.
     P2Cscr="$PROC2DIR/scripts"
     echo -e "\nProcessing to C++ scripts are in" $P2Cscr
     echo -e "\nexport P2Cscr=\"${P2Cscr}\"" >> $HOME/.profile
fi

echo "In $HOME/.profile:"
grep --color "P2Cscr" $HOME/.profile

set -e
#make the tools app
pushd tools/
cmake .
make
cp tools* ../scripts/
popd

echo
echo -e $COLOR2"Prepare to make library?"$NORMCO
pause

#prepare CMakeLists.txt
echo
cat lib/CMakeLists.tmpl |\
sed "s|%%PROC2DIR%%|\"$PROC2DIR\"|" |\
sed "s|%%SYMSHELL%%|\"$SYMSHELL\"|" > lib/CMakeLists.txt
echo -e "see $COLOR1 lib/CMakeLists.txt !"$NORMCO

echo
echo -e $COLOR2"Ready to make library!"$NORMCO
pause

echo
pushd lib/ 
cmake . 
make
popd

date > configured.txt #FINALLY SUCCESFULL

echo
echo -e $COLOR2"Ready to make examples?"
echo -e "(You can skip this final step just by break script at this moment)"$NORMCO
pause

rm -f configured.txt

echo -e $COLOR1
pushd "PROJECTS/"
echo -e $NORMCO

./_translateProjects.sh

echo -e "$COLOR2\nNow You have to edit $COLOR1 'CMakeLists.txt' $COLOR2 using $COLOR1 $EDIT $COLOR2"  
echo -e "\nSELECT EXAMPLES by REMOVING 'EXCLUDE_FROM_ALL' CLAUSULES\n"$NORMCO
pause
$EDIT CMakeLists.txt
cmake . 
make
popd

date > configured.txt #FINALLY SUCCESFULL
echo -e "With some examples" >> configured.txt

echo -e $COLOR2"\nSCRIPT" `realpath $0` "FINISHED"$NORMCO



