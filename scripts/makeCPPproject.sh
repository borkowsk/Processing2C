#!/bin/bash
# This script have to prepare cmake C++ project in directory containing Processing project
# No parameters are expected!  

if [ $# -ne 0 ]; 
then
   echo "No parameters expected!" 1>&2
   exit -1
fi

#CONFIGURATION
SCRIPTS=$(dirname "$0")
SOURCES=`pwd`
PROJECT=$(basename "$SOURCES")
source $SCRIPTS/config.dat

echo "Directories:"
echo -e SCRIPTS "     $SCRIPTS"
echo -e PROJECT "     $PROJECT"
echo -e SOURCES "     $SOURCES"
echo -e PROC2C "      $PROC2C"
echo -e WBRTM "       $WBRTM"
echo -e WBSYMSHELL "  $SYMSHELL"

#CHECK SOURCE
echo -e "\nAt least setup() or draw() function expected in *.pde files:"
egrep --color -Hn '(setup\(\)|draw\(\))' *.pde

echo -e "\nOnly non parametrised event handlers are alloved. These are such ones in *.pde files:"
egrep --color -Hn '(keyPressed\(\)|keyReleased\(\)|mouseClicked\(\)|mousePressed\(\)|mouseReleased\(\)|mouseMoved\(\)|mouseDragged\(\))' *.pde

echo -e "\nThe following lines may hide library symbols..."
egrep --color -Hn -f $SCRIPTS/symbols_pattern.grep *.pde
echo -e "... END\n"

echo "Translating project..."
#GET GLOBAL SYMBOLS
$SCRIPTS/prepare_local_h.sh

#https://stackoverflow.com/questions/18622907/only-mkdir-if-it-does-not-exist
SRCDIR="./cppsrc/"    
if [ -d $SRCDIR ]; then
   echo #"Directory $SRCDIR already exists."
else
   echo "Folder $SRCDIR does not exist. Will be created"
   mkdir -p $SRCDIR  # -p, --parents     no error if existing, make parent directories as needed
fi

mv "$SOURCES/local.h" "$SOURCES/cppsrc/"

#Preparing C++ source files
cat <<EOF > "./cppsrc/project_at_once.cpp"
//All sources in one file 
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //...is optional. Should be deleted when not needed!
#include "processing_lists.hpp"   //...is optional. Should be deleted when not needed!
#include "processing_map.hpp"     //...is optional. Should be deleted when not needed!
#include "project.h"              //...is for you. Could be deleted when not needed!
using namespace Processing;
#include "local.h"
//==================================================================================
const char* Processing::_PROGRAMNAME="$PROJECT";
EOF

FILES=*.pde
for f in $FILES
do # take action on each file. $f store current file name
  echo -e "File: $f \t-->\t./cppsrc/$f.cpp"
  echo "#include \"$f.cpp\"" >> "$SOURCES/cppsrc/project_at_once.cpp"
  $SCRIPTS/procesing2cpp.sh "$f" > "./cppsrc/$f.cpp"
done

#Preparing CMakeLists.txt    --> https://stackoverflow.com/questions/2500436/how-does-cat-eof-work-in-bash
echo -e "\nCreating CMakeLists.txt"
cat << EOF > CMakeLists.txt
cmake_minimum_required(VERSION 2.8)
set( CMAKE_VERBOSE_MAKEFILE off )

project($PROJECT)
set( VERSION_NUM 0.13 ) #MUST BE NUMERIC 

set( SRCPATH  "$SOURCES/cppsrc/" )
set( PROC2C   "$PROC2DIR" )
set( SYMSHELL "$SYMSHELL" )
set( WBRTM    "$WBRTM" )

set( MYLIBS   "$WBRTM/lib" )

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
     wbprocess wbsyshX11 X11 Xpm
     \${CMAKE_THREAD_LIBS_INIT}
     pthread
     rt
     )

target_compile_options( "\${PROJECT_NAME}_\${VERSION_NUM}_svg" PRIVATE "\${CMAKE_CXX_FLAGS}" "-w" "-std=c++14" "-pthread" "-O3" )
target_link_libraries( "\${PROJECT_NAME}_\${VERSION_NUM}_svg"  
     "-L\${PROC2C}/lib"
     "-L\${SYMSHELL}"
     wbprocess wbsyshSVG
     \${CMAKE_THREAD_LIBS_INIT}
     pthread
     rt
     )

#target_compile_options( "\${PROJECT_NAME}_\${VERSION_NUM}"  PRIVATE "\${CMAKE_CXX_FLAGS}" "-std=c++14" "-pthread" ) # --verbose ?

#target_link_libraries( "\${PROJECT_NAME}_\${VERSION_NUM}"
#     #"-L\${PROC2C}/lib/;\${SYMSHELL};\${MYLIBS}"
#     wbprocess wbrtm wbsyshX11 X11 Xpm
#     \${CMAKE_THREAD_LIBS_INIT}
#     pthread
#     rt
#     )
EOF

echo -e "\nProject ${PROJECT} DONE\n\n"

#/********************************************************************/
#/*               PROCESSING2C  version 2021-10-13                   */
#/********************************************************************/
#/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
#/*            W O J C I E C H   B O R K O W S K I                   */
#/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
#/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
#/*    GITHUB: https://github.com/borkowsk                           */
#/*                                                                  */
#/*                               (Don't change or remove this note) */
#/********************************************************************/

