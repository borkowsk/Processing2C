#!/bin/bash
if [ $# -ne 0 ]; 
then
   echo "No parameters expected!" 1>&2
   exit -1
fi

#CONFIGURATION
source ../scripts/config.dat
echo WBRTM in $WBRTM
echo

rm -f trash.txt
cat <<EOF > "CMakeLists.txt"
# Examples for Processing2C
# Remove EXCLUDE_FROM_ALL if you want compile all in one build\n"
cmake_minimum_required(VERSION 3.0)

#LIBRARIES
add_subdirectory( "${WBSYMSHELL}" 
                  "${WBSYMSHELL}" ) 
add_subdirectory( "../lib/" 
                  "../lib/" )

#EXAMPLES
EOF


for f in *; do # * rozwija się do listy wszystkich plików/katalogów znajdujących się w bieżącym katalogu
  if [ -d "$f" ]; then
    pushd "$f" > /dev/null
    LST=`ls *.pde 2>> lista.txt`
    if [[ -n "$LST" ]]
    then
     echo "Processing projekt '$f'" 
     #echo $LST
     ../../scripts/makeCPPproject.sh
     echo -e "add_subdirectory( $f \t EXCLUDE_FROM_ALL )" >> ../CMakeLists.txt
     git add *.sed
    fi
    popd > /dev/null
  elif [ -f "$f" ]; then
    echo "'$f' plik">> lista.txt
  else
    echo "'$f' niespodziewany typ pliku" >> lista.txt
  fi
done
