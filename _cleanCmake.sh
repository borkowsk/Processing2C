#!/bin/bash
#Cleaning cmake files
#
# Processing2C version .22.
#
source scripts/screen.ini

pushd lib/ > /dev/null
$ECHO $COLOR1"Directory is"$COLOR2 `pwd` $NORMCO
./_cleanCmake.sh
$ECHO $COLOR1"Finished for"$COLOR2 `pwd` $NORMCO
popd > /dev/null

#Cleaning cmake files
pushd tools/ > /dev/null
$ECHO $COLOR1"Directory is"$COLOR2 `pwd` $NORMCO
./_cleanCmake.sh
$ECHO $COLOR1"Finished for"$COLOR2 `pwd` $NORMCO
popd > /dev/null

pushd PROJECTS/ > /dev/null
$ECHO $COLOR1"Directory is"$COLOR2 `pwd` $NORMCO
./_cleanProjects.sh
$ECHO $COLOR1"Finished for"$COLOR2 `pwd` $NORMCO
popd > /dev/null
$ECHO $COLOR1"THE END"
