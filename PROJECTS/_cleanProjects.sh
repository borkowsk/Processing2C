#!/bin/bash
#Processing2C version 22.

source "../scripts/screen.ini"

if [ $# -ne 0 ]; 
then
   echo -e $COLERR"No parameters expected!"$NORMCO 1>&2
   exit -1
fi

echo -e ${COLOR1}"Cleaning cmake files!"${NORMCO}
echo "Cleaning cmake files" `date` >> clean_list.txt

for f in *; do # * rozwija się do listy wszystkich plików/katalogów znajdujących się w bieżącym katalogu
  if [ -d "$f" ]; then
    pushd "$f"
    #rm -f lista.txt
    rm -f build.ninja
    rm -f rules.ninja
    rm -f .ninja_log
    rm -f .ninja_deps
    rm -f cmake_install.cmake

    rm -f CMakeCache.txt
    rm -f CMakeLists.txt.user
    rm -f Makefile
    rm -Rf cmake/
    rm -Rf CMakeFiles/
    rm -Rf cmake-build-*/
    rm -f headers.tmp
    rm -f *~
    popd > /dev/null
  elif [ -f "$f" ]; then
     echo "'$f' - file" >> /dev/null
  else
    echo -e "${COLOR4}WARNING${NORMCO}'$f' -${COLERR} unexpected entry type ${NORMCO}"
    echo "'$f' unexpected directory entry type" >> clean_list.txt
  fi
done


rm -f build.ninja
rm -f rules.ninja
rm -f .ninja_log
rm -f .ninja_deps
rm -f cmake_install.cmake

rm -f CMakeCache.txt
rm -f CMakeLists.txt.user
rm -f Makefile
rm -Rf cmake/
rm -Rf CMakeFiles/
rm -Rf cmake-build-*/

rm -f *~
