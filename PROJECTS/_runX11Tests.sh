#!/bin/bash
#Processing2C version 26.

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
    echo -e $COLOR2
    pwd
    echo -e $COLOR1
    ls *_x11
    echo -e $NORMCO
    ./*_x11
    popd > /dev/null
  elif [ -f "$f" ]; then
     echo "'$f' - file" >> /dev/null
  else
    echo -e "${COLOR4}WARNING${NORMCO}'$f' -${COLERR} unexpected entry type ${NORMCO}"
    echo "'$f' unexpected directory entry type" >> clean_list.txt
  fi
done
