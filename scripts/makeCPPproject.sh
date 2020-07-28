#!/bin/bash
if [ $# -ne 0 ]; 
then
   echo "No parameters expected!" 1>&2
   exit -1
fi

BASEDIR=$(dirname "$0")
SOURCES=`pwd`
PROJECT=$(basename "$SOURCES")
echo "$BASEDIR" "$SOURCES" "$PROJECT"

source $BASEDIR/config.dat

$BASEDIR/prepare_local_h.sh

mv "$SOURCES/local.h" "$SOURCES/cppsrc/"

#Preparing files
mkdir cppsrc/
cat <<EOF > "./cppsrc/project_at_once.cpp"
//All sources in one file 
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

EOF

FILES=*.pde
for f in $FILES
do
  echo "File: $f "
  echo "#include \"$f.cpp\"" >> "$SOURCES/cppsrc/project_at_once.cpp"
  # take action on each file. $f store current file name
  $BASEDIR/procesing2cpp.sh "$f" > "./cppsrc/$f.cpp"
done

#Preparing CMakeLists.txt
#https://stackoverflow.com/questions/2500436/how-does-cat-eof-work-in-bash
echo "Creating CMakeLists.txt"
cat << EOF > CMakeLists.txt
cmake_minimum_required(VERSION 2.8)
set( CMAKE_VERBOSE_MAKEFILE off )

project($PROJECT)
set( VERSION_NUM 0.1 ) #MUST BE NUMERIC 

set( SRCPATH "$SOURCES/cppsrc/" )
set( WBRTM   "../../WBRTM_Linux/")
set( MYLIBS  "../../WBRTM_Linux/")

add_definitions(-DMULTITR -DDEF_MAXTHREADS=16 -DVERSION_NUM=\${VERSION_NUM})

include_directories(  "\${SRCPATH}" "$BASEDIR/../lib/include" "\${WBRTM}" )

add_executable("\${PROJECT_NAME}_\${VERSION_NUM}_once"
               "\${SRCPATH}project_at_once.cpp"
              )

#add_executable("\${PROJECT_NAME}_\${VERSION_NUM}"
EOF

#List of modules
pushd "./cppsrc/"
FILES=*.cpp
for f in $FILES
do
  echo -e "#\t\"\${SRCPATH}$f\"" >> ../CMakeLists.txt
done


popd

#Final part of CMakeLists.txt
cat << EOF >> CMakeLists.txt
#        )

target_compile_options( "\${PROJECT_NAME}_\${VERSION_NUM}_once" PRIVATE "\${CMAKE_CXX_FLAGS}" "-std=c++11" "-pthread" ) # -o3 ?

target_link_libraries( "\${PROJECT_NAME}_\${VERSION_NUM}_once"
     "-L\${MYLIBS}"
     wbrtm wbsyshX11 X11 Xpm
     \${CMAKE_THREAD_LIBS_INIT}
     pthread
     rt
     )

#target_compile_options( "\${PROJECT_NAME}_\${VERSION_NUM}"  PRIVATE "\${CMAKE_CXX_FLAGS}" "-std=c++11" "-pthread" ) # -v ?

#target_link_libraries( "\${PROJECT_NAME}_\${VERSION_NUM}"
#     "-L\${MYLIBS}"
#     wbprocessing wbrtm wbsyshX11 X11 Xpm
#     \${CMAKE_THREAD_LIBS_INIT}
#     pthread
#     rt
#     )
EOF
