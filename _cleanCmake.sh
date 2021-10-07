#!/bin/bash
#Cleaning cmake files
pushd lib/ > /dev/null
echo "Directory is" `pwd`
./_cleanCmake.sh
echo "Finished for" `pwd`
popd > /dev/null
pushd PROJECTS/ > /dev/null
echo "Directory is" `pwd`
./_cleanProjects.sh
echo "Finished for" `pwd`
popd > /dev/null
