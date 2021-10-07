#!/bin/bash
if [ $# -ne 0 ]; 
then
   echo "No parameters expected!" 1>&2
   exit -1
fi

echo "Cleaning cmake files!"
echo "Cleaning cmake files" `date` >> clean_list.txt

for f in *; do # * rozwija się do listy wszystkich plików/katalogów znajdujących się w bieżącym katalogu
  if [ -d "$f" ]; then
    pushd "$f"
    #rm -f lista.txt
    rm -f CMakeCache.txt
    rm -f Makefile
    rm -f cmake_install.cmake
    rm -Rf CMakeFiles
    rm -f headers.tmp
    popd > /dev/null
  elif [ -f "$f" ]; then
    echo "'$f' plik" >> /dev/null
  else
    echo "'$f' unexpected directory entry type" >> lista.txt
  fi
done

rm -f build.ninja
rm -f rules.ninja
rm -f .ninja_log
rm -f .ninja_deps
rm -f CMakeCache.txt
rm -f Makefile
rm -f cmake_install.cmake
rm -Rf CMakeFiles
