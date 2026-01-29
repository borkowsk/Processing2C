#!/bin/bash
#Processing2C version 22.
export TIMEMARK=`date "+%Y-%m-%d %H:%M:%S" `
source "../scripts/screen.ini"

if [ $# -g 1 ]; 
then
   echo -e $COLERR"One or zero parameters expected!"$NORMCO 1>&2
   exit -1
fi

#CONFIGURATION
source ../scripts/config.dat
#echo WBRTM in $WBRTM
echo SYMSHELL in $SYMSHELL
echo

rm -f trash.txt
cat <<EOF > "CMakeLists.txt"
# Examples for Processing2C translated $TIMEMARK
# Add or remove EXCLUDE_FROM_ALL, if you want (not) compile a particular example\n

cmake_minimum_required(VERSION 3.5)
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

echo "Preparing!" $TIMEMARK "..." > translate_lst.txt

for f in *; do # * rozwija się do listy wszystkich plików/katalogów znajdujących się w bieżącym katalogu
  if [ -d "$f" ]; then
    pushd "$f" > /dev/null
    LST=`ls *.pde 2>> lista.txt`
    if [[ -n "$LST" ]]
    then
     echo "Processing projekt '$f'" 
     #echo $LST
     ../../scripts/makeCPPproject.sh $*
     
     if [ -f "CMakeLists.txt" ];then
     	echo -e "add_subdirectory( $f \t)" >> ../CMakeLists.txt
     fi
     
     if [ -f "multi_cpp/CMakeLists.txt" ]; then
      	echo -e "add_subdirectory( $f/multi_cpp/ EXCLUDE_FROM_ALL \t)" >> ../CMakeLists.txt
     fi
     
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


