#!/bin/bash
#GREPOPTIONS="--with-filename --color -E" #For DEBUG
GREPOPTIONS="-c -E"
if [ $# -lt 1 ];
then
   echo -e $COLOR2"$# is invalid number of parameters!"$NORMCO 1>&2
   exit -1
fi

echo -e $COLOR2"Is \"processing_string.hpp\" needed?"$NORMCO 1>&2
grep  $GREPOPTIONS "(String\s+|_string_param\s+)" $* 1>&2 \
&& echo "#include \"processing_string.hpp\"  //Processing::String class"

echo -e $COLOR2"Is \"processing_console.hpp\" needed?"$NORMCO 1>&2
grep $GREPOPTIONS "(nf\s*\(|print\s*\(|println\s*\()" $* 1>&2 \
&& echo "#include \"processing_console.hpp\"   //...is optional. Should be deleted when not needed."

echo -e $COLOR2"Is \"processing_alist.hpp\" needed?"$NORMCO 1>&2
grep $GREPOPTIONS "(ArrayList\s*<)" $* 1>&2 \
&& echo "#include \"processing_alist.hpp\" //...is optional. Should be deleted when not needed."

echo -e $COLOR2"Is \"processing_lists.hpp\" needed?"$NORMCO 1>&2
grep $GREPOPTIONS "(FloatList\s+|IntList\s+|StringList\s+)" $* 1>&2 \
&& echo "#include \"processing_lists.hpp\" //...is optional. Should be deleted when not needed."

echo -e $COLOR2"Is \"processing_map.hpp\" needed?"$NORMCO 1>&2
grep $GREPOPTIONS "(HashMap\s*<)" $* 1>&2 \
&& echo "#include \"processing_map.hpp\"   //...is optional. Should be deleted when not needed."

echo -e $COLOR2"Is \"processing_files.hpp\" needed?"$NORMCO 1>&2
grep $GREPOPTIONS "(BufferedReader\s+|PrintWriter\s+|createReader\s+\(|createWriter\s+\()" $* 1>&2 \
&& echo "#include \"processing_files.hpp\" //...is optional. Should be deleted when not needed."

echo -e $COLOR2"Is \"processing_StringDict.hpp\" needed?"$NORMCO 1>&2
grep $GREPOPTIONS "(StringDict\s+)" $* 1>&2 \
&& echo "#include \"processing_StringDict.hpp\" //...is optional. Should be deleted when not needed."

echo -e $COLOR2"Is \"processing_IntDict.hpp\" needed?"$NORMCO 1>&2
grep $GREPOPTIONS "(IntDict\s+)" $* 1>&2 \
&& echo "#include \"processing_IntDict.hpp\" //...is optional. Should be deleted when not needed."

echo -e $COLOR2"Is \"processing_FloatDict.hpp\" needed?"$NORMCO 1>&2
grep $GREPOPTIONS "(FloatDict\s+)" $* 1>&2 \
&& echo "#include \"processing_FloatDict.hpp\" //...is optional. Should be deleted when not needed."

echo -e ${NORMCO}"Searching includes finished for"$COLOR2 $* "\n"$NORMCO 1>&2

#/********************************************************************/
#/*               PROCESSING2C  version 2022-06-30                   */
#/********************************************************************/
#/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
#/*            W O J C I E C H   B O R K O W S K I                   */
#/*    Instytut Studów Społecznych Uniwersytetu Warszawskiego        */
#/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
#/*    GITHUB: https://github.com/borkowsk                           */
#/*                                                                  */
#/*                               (Don't change or remove this note) */
#/********************************************************************/
