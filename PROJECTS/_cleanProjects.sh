#!/bin/bash
if [ $# -ne 0 ]; 
then
   echo "No parameters expected!" 1>&2
   exit -1
fi

echo "Cleaning!" `date` >> lista.txt

for f in *; do # * rozwija się do listy wszystkich plików/katalogów znajdujących się w bieżącym katalogu
  if [ -d "$f" ]; then
    pushd "$f"
    #rm -f lista.txt
    rm -f Makefile
    rm -f cmake_install.cmake
    rm -f headers.tmp
    rm -Rf CMakeFiles
    popd > /dev/null
  elif [ -f "$f" ]; then
    echo "'$f' plik" >> /dev/null
  else
    echo "'$f' unexpected directory entry type" >> lista.txt
  fi
done
