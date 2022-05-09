#!/bin/bash
if [ $# -ne 0 ]; 
then
   echo "No parameters expected!" 1>&2
   exit -1
fi

echo "Cleaning cmake files!"
echo "Cleaning current directoryfrom cmake files!" `date` >> clean_list.txt

rm -f CMakeCache.txt
rm -f Makefile
rm -f cmake_install.cmake
rm -Rf CMakeFiles
rm -f build.ninja
rm -f rules.ninja
rm -f .ninja_log
rm -f .ninja_deps
rm -Rf cmake-build-*/

