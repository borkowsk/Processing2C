#!/bin/bash
# Processing2C version 0.2c installation script
#

EDIT=nano
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
SYMSHELL=`realpath "../symShellLight"`
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
echo -e $COLERR"Are you sure, that SymShellLight is cloned into directory"$COLOR1 $SYMSHELL $NORMCO"?"
echo -e $COLERR"I can't find this toolbox, which is strictly required!"$NORMCO
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

./_translateProjects.sh

echo -e "$COLOR2\nNow You have to edit $COLOR1 'CMakeLists.txt' $COLOR2 using $COLOR1 $EDIT $COLOR2"  
echo -e "\nSELECT EXAMPLES by ADDING/REMOVING $COLOR3'EXCLUDE_FROM_ALL'$COLOR2 CLAUSULES\n"$NORMCO
pause
$EDIT CMakeLists.txt
echo -e $COLOR3"CMAKE..."$NORMCO
cmake . 
echo -e $COLOR3"MAKE..."$NORMCO
make
echo -e $COLOR3"DONE"$NORMCO
popd

date > configured.txt #FINALLY SUCCESFULL
echo -e "With some examples" >> configured.txt

echo -e $COLOR2"\nSCRIPT"$COLOR1 `realpath $0` $COLOR2"FINISHED"$NORMCO


#/********************************************************************/
#/*               PROCESSING2C  version 2022-11-23                   */
#/********************************************************************/
#/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
#/*            W O J C I E C H   B O R K O W S K I                   */
#/*    Instytut Studów Społecznych Uniwersytetu Warszawskiego        */
#/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
#/*    GITHUB: https://github.com/borkowsk                           */
#/*                                                                  */
#/*                               (Don't change or remove this note) */
#/********************************************************************/

