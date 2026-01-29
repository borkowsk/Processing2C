#!/bin/bash
# Processing2C installation script
# @version 0.26.01
# @date 2026-01-29 (last change)
#
if [[ -f /usr/bin/gedit ]]
then 
	EDIT=/usr/bin/gedit
else
	EDIT=nano
	if [[ -f /bin/nano/ ]]
	then
	echo "nano detected"
    else
    echo "nano required:"
    sudo apt install nano
    fi
fi

source scripts/screen.ini

set -e # https://intoli.com/blog/exit-on-errors-in-bash-scripts/


echo -e $COLOR2"Running"$COLOR1 `realpath $0` $NORMCO
echo -e "\n\tThis script stops on any error!\n"$COLOR3"\tWhen it stop, remove source of the error & run it again!\n"$NORMCO 

function pause(){ #https://www.cyberciti.biz/tips/linux-unix-pause-command.html
 echo -e $COLOR1""
 read -s -n 1 -p "Press ^C to abort, any key to continue . . ."
 echo -e $NORMCO""
}

#WBRTM="/home/Kowalski/WBRTM"
SYMSHELL=`realpath "./SYMSHELL"`
PROC2DIR=`realpath "./"`

echo -e $COLOR2"Are the paths correct?\n"$NORMCO
echo -e "PROC2DIR=$COLOR1"$PROC2DIR"$NORMCO  #This toolbox whole path"
echo -e "SYMSHELL=$COLOR1"$SYMSHELL"$NORMCO  #SymShellLight toolbox whole path"
if [[ ! -d $SYMSHELL ]]
then
  echo -e $COLERR"Directory"$COLOR1 $SYMSHELL $COLERR"is not found!" $NORMCO
  echo -e $COLERR"This toolbox is strictly required!"$NORMCO
  exit -1  
fi
echo -e $COLOR2"If it seems wrong, break script, edit it and run it again!"$NORMCO
pause
echo

if [[ ! -d "$SYMSHELL/SVG/" ]]
then
echo 
echo -e $COLERR"Are you sure, that SymShellLight toolbox is in directory"$COLOR1 $SYMSHELL $NORMCO"?"
echo -e $COLERR"I can't find this toolbox, which is strictly required!"
echo
echo -e $NORMCO"How to get this?"
echo
echo -e $NORMCO"In directory"$COLOR1 $PROC2DIR $NORMCO"use the following git command:"$COLOR2
echo
echo -e "$ git submodule update --remote --recursive"$NORMCO
echo
echo -e "Alternatively..."
echo 
echo -e $NORMCO"Go to the parent directory and use the following command:"$COLOR2
echo
echo -e "$ git clone https://github.com/borkowsk/symShellLight.git SymShellLight"
echo -e "$ ln -s ../SymShellLight/ $PROC2DIR/SYMSHELL"$NORMCO
echo
exit -1
else
 echo -e "SymShellLight toolbox is located in...\n"$COLOR1"$SYMSHELL"$NORMCO
 echo
fi

echo -e "Finally, p2c working directory is ..."$COLOR1 
ls -d $PROC2DIR
echo -e $NORMCO

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
##TODO: Any insertion of such configuration variables need consider __LAST_EXPORT__ mark!
     P2Cscr="$PROC2DIR/scripts"
     echo -e "\nProcessing to C++ scripts are in" $P2Cscr
     echo -e "\nexport P2Cscr=\"${P2Cscr}\"" >> $HOME/.profile
     $EDIT $HOME/.profile
fi

echo -e $COLOR2"In"$COLOR3 $HOME/.profile $NORMCO":"
grep --color=always "P2Cscr" $HOME/.profile

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

pushd lib/ 
echo -e $COLOR3"CMAKE..."$NORMCO
cmake . 
echo -e $COLOR3"MAKE..."$NORMCO
make
echo -e $COLOR3"DONE"$NORMCO
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

./_cleanProjects.sh
./_translateProjects.sh

echo -e "$COLOR2\nNow You have to edit $COLOR1 'CMakeLists.txt' $COLOR2 using $COLOR1 $EDIT $COLOR2"  
echo -e "\nSELECT EXAMPLES by ADDING/REMOVING $COLOR3'EXCLUDE_FROM_ALL'$COLOR2 CLAUSULES\n"$NORMCO

$EDIT CMakeLists.txt
pause

echo -e $COLOR3"CMAKE..."$NORMCO
#mkdir -p build_examples/ 
#cmake -B build_examples/ -S ./
cmake .
echo -e $COLOR3"MAKE..."$NORMCO
#pushd build_examples/
make
echo -e $COLOR3"DONE"$NORMCO
#popd
popd

date > configured.txt          #FINALLY SUCCESFULL
echo -e "With some examples" >> configured.txt

echo -e $COLOR2"\nSCRIPT"$COLOR1 `realpath $0` $COLOR2"FINISHED"$NORMCO


#/********************************************************************/
#/*               PROCESSING2C  version 2026                         */
#/********************************************************************/
#/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
#/*            W O J C I E C H   B O R K O W S K I                   */
#/*    Instytut Studów Społecznych Uniwersytetu Warszawskiego        */
#/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
#/*    GITHUB: https://github.com/borkowsk                           */
#/*                                                                  */
#/*                               (Don't change or remove this note) */
#/********************************************************************/

