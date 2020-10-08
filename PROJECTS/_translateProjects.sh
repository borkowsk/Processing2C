#!/bin/bash
rm -f trash.txt
for f in *; do # * rozwija się do listy wszystkich plików/katalogów znajdujących się w bieżącym katalogu
  if [ -d "$f" ]; then
    pushd "$f" > /dev/null
    LST=`ls *.pde 2>> trash.txt`
    if [[ -n "$LST" ]]
    then
     echo "Processing projekt '$f'" 
     #echo $LST
     ../../scripts/makeCPPproject.sh
    fi
    popd > /dev/null
  elif [ -f "$f" ]; then
    echo "Plik '$f'" >> trash.txt
  else
    echo "Niespodziewany typ '$f'" >> trash.txt
  fi
done
