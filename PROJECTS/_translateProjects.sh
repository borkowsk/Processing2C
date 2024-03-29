#!/bin/bash
#Processing2C version 22.

source "../scripts/screen.ini"

if [ $# -ne 0 ]; 
then
   echo -e $COLERR"No parameters expected!"$NORMCO 1>&2
   exit -1
fi

#CONFIGURATION
source ../scripts/config.dat
#echo WBRTM in $WBRTM
echo SYMSHELL in $SYMSHELL
echo

rm -f trash.txt
cat <<EOF > "CMakeLists.txt"
# Examples for Processing2C
# Add or remove EXCLUDE_FROM_ALL, if you want (not) compile a particular example\n
cmake_minimum_required(VERSION 3.0)
project(PROCESSING2C_EXAMPLES)
#LIBRARIES
add_subdirectory( "${SYMSHELL}" 
                  "${SYMSHELL}" )
add_subdirectory( "../lib/" 
                  "../lib/" )
add_subdirectory( "../tools/" 
                  "../tools/" )
#EXAMPLES
EOF

echo "Preparing!" `date` "..." > translate_lst.txt

for f in *; do # * rozwija się do listy wszystkich plików/katalogów znajdujących się w bieżącym katalogu
  if [ -d "$f" ]; then
    pushd "$f" > /dev/null
    LST=`ls *.pde 2>> lista.txt`
    if [[ -n "$LST" ]]
    then
     echo "Processing projekt '$f'" 
     #echo $LST
     ../../scripts/makeCPPproject.sh
     echo -e "add_subdirectory( $f \t)" >> ../CMakeLists.txt
     git add *.sed
    fi
    popd > /dev/null
  elif [ -f "$f" ]; then
     echo "'$f' - file" >> lista.txt
  else
    echo -e "${COLOR4}WARNING${NORMCO}'$f' -${COLERR} unexpected entry type ${NORMCO}"
    echo "'$f' - unexpected entry type" >> translate_lst.txt
  fi
done

echo "DONE" >> translate_lst.txt


