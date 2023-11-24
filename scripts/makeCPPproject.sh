#!/bin/bash
# This script have to prepare cmake C++ project in directory containing Processing project
# One optional parameter is possible:  multisrc
# But it is still TODO!
#
# Processing2C version 22g. (2023-11-15)
#
Pr2CVERSION="0.22g"

export TIMEMARK=`date "+%Y-%m-%d %H:%M:%S" `
export SCRIPTS=$(dirname "$0")
source $SCRIPTS/screen.ini

if [ $# -gt 1 ]; 
then
   echo $ERRCOL"Only one parameter allowed!"$NORMCO 1>&2
   echo "It may be 'singlesrc' or 'multisrc'" 1>&2
   exit -1
fi

#CONFIGURATION
echo -e $COLOR3"\nMaking PROCESSING2C project in "$COLOR1 `pwd` $NORMCO "\n"
echo -e $COLOR4"\nConfiguration directories:"$NORMCO

export SOURCES=`pwd`
export PROJECT=$(basename "$SOURCES")
source $SCRIPTS/config.dat

echo -e WBRTM  $COLOR1"      $WBRTM"$NORMCO
echo -e PROC2DIR $COLOR1"    $PROC2DIR"$NORMCO
echo -e SCRIPTS $COLOR1"     $SCRIPTS"$NORMCO
echo -e WBSYMSHELL $COLOR1"  $SYMSHELL"$NORMCO

echo -e PROJECT $COLOR1"     $PROJECT"$NORMCO
echo -e SOURCES $COLOR1"     $SOURCES"$NORMCO

#SINGLE OR MULTISOURCE?
echo -e $COLOR4"\nChecking single/multi sources mode:"$NORMCO
export NUMBER_OF_PDES=`ls -1 *.pde | grep -v exit | wc -l`

if [[ $NUMBER_OF_PDES == 0 ]];
then
	echo -e $COLERR"No any '*.pde' files in this folder.\nNothing to do!!!"$NORMCO
	exit -1
else
	echo -e $COLOR3'\nNumber of "*.pde" source files excluding "exit.pde":'$COLOR2 \
        $NUMBER_OF_PDES  $NORMCO
fi

export SOURCEMODE=$1
if [[ $SOURCEMODE != "multisrc" ]]
then
     SOURCEMODE="singlesrc"
fi

echo -e $COLOR3"Project will be translated in mode:$COLOR2 $SOURCEMODE"$NORMCO

#CHECK SOURCE
echo -e $COLOR4"\nCHECKING FUNCTION NAMES..."$NORMCO

echo -e $COLOR2"\nAt least setup() or draw() function expected in *.pde files:"$NORMCO
grep -E  --color=always -Hn '^void\s+(setup\(\)|draw\(\))' *.pde

echo -e $COLOR2"\nOnly non parametrised event handlers are alloved. These are such ones in *.pde files:"$NORMCO
egrep  -Hn  --color=always '^void\s+(keyPressed\(\)|keyReleased\(\)|mouseClicked\(\)|mousePressed\(\)|mouseReleased\(\)|mouseMoved\(\)|mouseDragged\(\))' *.pde

echo -e $COLOR2"\nThe following lines may hide library symbols..."$NORMCO
#exclude pseudo declaration then check for any construct ::identifier::\s+(::one of library identifier::) 
grep -P -Hn  --color=always -f $SCRIPTS/symbols_pattern.grep *.pde
#echo -e "\nCHECKING NAMES FINISHED\n"



#GET GLOBAL SYMBOLS
echo -e $COLOR4"\nSEARCHING GLOBAL SYMBOLS:"$NORMCO
$SCRIPTS/prepare_local_h.sh

#LETS CHECK OUTPUT DIRECTORIES!
echo -e $COLOR4"\nCHECKING OUTPUT DIRECTORIES:"$NORMCO
#https://stackoverflow.com/questions/18622907/only-mkdir-if-it-does-not-exist
export SRCDIR="./cppsrc/"    
if [ -d ${SRCDIR} ]; then
   echo -e $COLOR2"Directory ${COLOR1}${SRCDIR}${COLOR2} already exists."$NORMCO
else
   echo -e $COLOR2"Folder ${COLOR1}${SRCDIR}${COLOR1} does not exist. Will be created"$NORMCO
   echo -e $COLERR `mkdir -p $SRCDIR`$NORMCO  # -p, --parents     no error if existing, make parent directories as needed
fi

export TOOLSOUTDIR="${SRCDIR}toolsouts/"
if [ -d ${TOOLSOUTDIR} ]; then
   echo -e $COLOR2"Directory ${COLOR1}${TOOLSOUTDIR}${COLOR2} already exists."$NORMCO
   echo -e $COLERR `rm ${TOOLSOUTDIR}/*`$NORMCO
else
   echo -e $COLOR2"Folder ${COLOR1}${SRCDIR}${COLOR2} does not exist. Will be created"$NORMCO
   echo -e $COLERR `mkdir -p ${TOOLSOUTDIR} `$NORMCO
fi

echo -e $COLERR `mv "$SOURCES/local.h" "$SOURCES/cppsrc/"`$NORMCO


if [[ $SOURCEMODE == "multisrc" ]]
then
     echo -e $COLERR"$SOURCEMODE required but not implemented yet!"$NORMCO
     exit -2
fi

#OPTIONAL HEADERS
echo -e $COLOR4"PREPARING INCLUDES FOR $SOURCEMODE MODE:"$NORMCO

#Preparing C++ source files

echo "/*All sources in one file?*/"                                  > ./cppsrc/project_at_once.cpp

echo "#include \"processing_consts.hpp\""                            >> ./cppsrc/project_at_once.cpp
echo "#include \"processing_templates.hpp\""                         >> ./cppsrc/project_at_once.cpp
echo "#include \"processing_library.hpp\""                           >> ./cppsrc/project_at_once.cpp
echo "#include \"processing_inlines.hpp\" //...is optional. Use when project is already compilable!" >> ./cppsrc/project_at_once.cpp
echo "#include \"processing_window.hpp\""                            >> ./cppsrc/project_at_once.cpp
${SCRIPTS}/includeOptionals.sh *.pde                                 >> ./cppsrc/project_at_once.cpp
echo "using namespace Processing;"                                   >> ./cppsrc/project_at_once.cpp
[[ -f "./cppsrc/pre_local.h" ]] && echo "#include \"pre_local.h\""   >> ./cppsrc/project_at_once.cpp
echo "#include \"local.h\""                                          >> ./cppsrc/project_at_once.cpp
[[ -f "./cppsrc/post_local.h" ]] && echo "#include \"post_local.h\"" >> ./cppsrc/project_at_once.cpp
echo "#include <iostream>"                                           >> ./cppsrc/project_at_once.cpp
echo "//=================================================================================="          >> ./cppsrc/project_at_once.cpp
echo "const char* Processing::_PROGRAMNAME=\"$PROJECT\";" >> ./cppsrc/project_at_once.cpp

#REAL TRANSLATION
echo -e $COLOR4"DOING REAL TRANSLATION:"$NORMCO

FILES=*.pde
for f in $FILES
do # take action on each file. $f store current file name
  echo -e $COLOR3"Translating file:$COLOR1 $f $NORMCO\t-->\t$COLOR2./cppsrc/$f.hpp$NORMCO\n"
  echo "#include \"$f.hpp\"" >> "$SOURCES/cppsrc/project_at_once.cpp"
  $SCRIPTS/procesing2cpp.sh "$f" > "./cppsrc/$f.hpp"
done

#FINAL WORK
echo -e $COLOR4"FINALISING..."$NORMCO

#Preparing CMakeLists.txt    --> https://stackoverflow.com/questions/2500436/how-does-cat-eof-work-in-bash
echo -e  $COLOR3"\nCreating$COLOR1 CMakeLists.txt $NORMCO"
cat << EOF > CMakeLists.txt
# This file was made automagically. Do not edit!
#! @date $TIMEMARK (translation timemark)
cmake_minimum_required(VERSION 3.0)
set( CMAKE_VERBOSE_MAKEFILE off )

project($PROJECT)
set( VERSION_NUM $Pr2CVERSION ) #MUST BE NUMERIC 

IF (WIN32)
  # set stuff for windows
  message( \${PROJECT_NAME} ": MS Windows platform assumed.\n\tInside C/C++ code automatic _MSC_VER variable will be used!" )
  #set( WINDOWS_ONLY_SRC  "" )
ELSE()
  # set stuff for other systems
  message( \${PROJECT_NAME} ": Linux/unix platform assumed." )
  #set( X_ONLY_SRC  "" )
ENDIF()

set( SRCPATH  "$SOURCES/cppsrc/" )
set( PROC2C   "$PROC2DIR" )
set( SYMSHELL "$SYMSHELL" )
set( WBRTM    "$WBRTM" )

set( MYLIBS   "$WBRTM/lib" )

# THESE LINES BELOW COULD BE UNCOMMENTED WHEN LIBRARIES SEEMS TO BE NOT COMPILED.
#add_subdirectory( "\${SYMSHELL}"
#                  "\${SYMSHELL}" )
#add_subdirectory( "\${PROC2C}/lib/"
#                  "\${PROC2C}/lib/" )

add_definitions( -DVERSION_NUM=\${VERSION_NUM} ) # -DMULTITR -DDEF_MAXTHREADS=16 

include_directories(  "\${SRCPATH}" "\${PROC2C}/lib/include" "\${SYMSHELL}" "\${WBRTM}/INCLUDE" )

add_executable("\${PROJECT_NAME}_\${VERSION_NUM}_x11"
               "\${SRCPATH}project_at_once.cpp"
              )

add_executable("\${PROJECT_NAME}_\${VERSION_NUM}_svg"
               "\${SRCPATH}project_at_once.cpp"
              )

#add_executable("\${PROJECT_NAME}_\${VERSION_NUM}"

EOF

#List of modules
pushd "./cppsrc/" >> /dev/null

FILES=*.cpp
for f in $FILES
do
  echo -e "#\t\"\${SRCPATH}$f\"" >> ../CMakeLists.txt
done

popd >> /dev/null

#Final part of CMakeLists.txt
cat << EOF >> CMakeLists.txt
#        )

target_compile_options( "\${PROJECT_NAME}_\${VERSION_NUM}_x11" PRIVATE "\${CMAKE_CXX_FLAGS}" "-w" "-std=c++14" "-pthread" )
target_link_libraries( "\${PROJECT_NAME}_\${VERSION_NUM}_x11"  
     "-L\${PROC2C}/lib"
     "-L\${SYMSHELL}"
     wbprocess wbsyshLight X11 Xpm
     \${CMAKE_THREAD_LIBS_INIT}
     pthread
     rt
     )

target_compile_options( "\${PROJECT_NAME}_\${VERSION_NUM}_svg" PRIVATE "\${CMAKE_CXX_FLAGS}" "-w" "-std=c++14" "-pthread" "-O3" )
target_link_libraries( "\${PROJECT_NAME}_\${VERSION_NUM}_svg"  
     "-L\${PROC2C}/lib"
     "-L\${SYMSHELL}"
     wbprocess wbsyshLightSVG
     \${CMAKE_THREAD_LIBS_INIT}
     pthread
     rt
     )

#target_compile_options( "\${PROJECT_NAME}_\${VERSION_NUM}"  PRIVATE "\${CMAKE_CXX_FLAGS}" "-std=c++14" "-pthread" ) # --verbose ?

#target_link_libraries( "\${PROJECT_NAME}_\${VERSION_NUM}"
#     #"-L\${PROC2C}/lib/;\${SYMSHELL};\${MYLIBS}"
#     wbprocess wbrtm wbsyshLight X11 Xpm
#     \${CMAKE_THREAD_LIBS_INIT}
#     pthread
#     rt
#     )

EOF

echo -e $COLOR4"\nProject$COLOR1 ${PROJECT}$COLOR4 DONE\n\n"$NORMCO

#/********************************************************************/
#/*                 PROCESSING2C  release 2023                       */
#/********************************************************************/
#/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
#/*            W O J C I E C H   B O R K O W S K I                   */
#/*    Instytut Studiów Społecznych Uniwersytetu Warszawskiego       */
#/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
#/*    GITHUB: https://github.com/borkowsk                           */
#/*                                                                  */
#/*                               (Don't change or remove this note) */
#/********************************************************************/

