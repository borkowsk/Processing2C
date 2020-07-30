#!/bin/bash
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

echo -e SCRIPTS "     $SCRIPTS"
echo -e PROJECT "     $PROJECT"
echo -e SOURCES "     $SOURCES"
echo -e WBRTM "       $WBRTM"
echo -e WBSYMSHELL "  $WBSYMSHELL"

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
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
//include "processing_inlines.hpp" //is optional. Use when project is already compilable
using namespace Processing;
#include "local.h"
#include "project.h" //This is for you. Could be deleted when not needed
//==================================================================================

EOF

FILES=*.pde
for f in $FILES
do # take action on each file. $f store current file name
  echo -e "File: $f \t-->\t./cppsrc/$f.cpp"
  echo "#include \"$f.cpp\"" >> "$SOURCES/cppsrc/project_at_once.cpp"
  $SCRIPTS/procesing2cpp.sh "$f" > "./cppsrc/$f.cpp"
done

#Preparing CMakeLists.txt
#https://stackoverflow.com/questions/2500436/how-does-cat-eof-work-in-bash
echo -e "\nCreating CMakeLists.txt"
cat << EOF > CMakeLists.txt
cmake_minimum_required(VERSION 2.8)
set( CMAKE_VERBOSE_MAKEFILE off )

project($PROJECT)
set( VERSION_NUM 0.1 ) #MUST BE NUMERIC 

set( SRCPATH "$SOURCES/cppsrc/" )
set( WBRTM   "$WBRTM")
set( MYLIBS  "$WBRTM")

add_definitions( -DMULTITR -DDEF_MAXTHREADS=16 -DVERSION_NUM=\${VERSION_NUM} )

include_directories(  "\${SRCPATH}" "$SCRIPTS/../lib/include" "\${WBRTM}" "\${WBRTM}/INCLUDE" )

add_executable("\${PROJECT_NAME}_\${VERSION_NUM}_once"
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

target_compile_options( "\${PROJECT_NAME}_\${VERSION_NUM}_once" PRIVATE "\${CMAKE_CXX_FLAGS}" "--verbose" "-std=c++11" "-pthread" ) # -o3 ?

target_link_libraries( "\${PROJECT_NAME}_\${VERSION_NUM}_once"
     "-L\${MYLIBS}"
     wbrtm wbsyshX11 X11 Xpm
     \${CMAKE_THREAD_LIBS_INIT}
     pthread
     rt
     )

#target_compile_options( "\${PROJECT_NAME}_\${VERSION_NUM}"  PRIVATE "\${CMAKE_CXX_FLAGS}" "-std=c++11" "-pthread" ) # --verbose ?

#target_link_libraries( "\${PROJECT_NAME}_\${VERSION_NUM}"
#     "-L\${MYLIBS}"
#     wbprocessing wbrtm wbsyshX11 X11 Xpm
#     \${CMAKE_THREAD_LIBS_INIT}
#     pthread
#     rt
#     )
EOF

echo -e "\nDONE\n"
