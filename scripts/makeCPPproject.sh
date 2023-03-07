#!/bin/bash
# This script have to prepare cmake C++ project in directory containing Processing project
# One optional parameter is possible:  multisrc
# But it is still TODO!
#
# Processing2C version 22b.
#
Pr2CVERSION="0.22b"

export SCRIPTS=$(dirname "$0")
source $SCRIPTS/screen.ini

if [ $# -gt 1 ]; 
then
   echo $ERRCOL"Only one parameter allowed!"$NORMCO 1>&2
   echo "It may be 'singlesrc' or 'multisrc'" 1>&2
   exit -1
fi

#CONFIGURATION
echo -e $COLOR3"\nMaking PROCESSING2C project in "$COLOR2 `pwd` $NORMCO "\n"
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

echo -e $COLOR1"\nAt least setup() or draw() function expected in *.pde files:"$NORMCO
grep -E  --color=always -Hn '(setup\(\)|draw\(\))' *.pde

echo -e $COLOR1"\nOnly non parametrised event handlers are alloved. These are such ones in *.pde files:"$NORMCO
egrep  -Hn  --color=always '(keyPressed\(\)|keyReleased\(\)|mouseClicked\(\)|mousePressed\(\)|mouseReleased\(\)|mouseMoved\(\)|mouseDragged\(\))' *.pde

echo -e $COLOR1"\nThe following lines may hide library symbols..."$NORMCO
egrep  -Hn  --color=always -f $SCRIPTS/symbols_pattern.grep *.pde
#echo -e "\nCHECKING NAMES FINISHED\n"



#GET GLOBAL SYMBOLS
echo -e $COLOR4"\nSERCHING GLOBAL SYMBOLS:"$NORMCO
$SCRIPTS/prepare_local_h.sh

#CHECK OUTPUT DIRECTORIES
echo -e $COLOR4"\nCHECKING OUTPUT DIRECTORIES:"$NORMCO
#https://stackoverflow.com/questions/18622907/only-mkdir-if-it-does-not-exist
export SRCDIR="./cppsrc/"    
if [ -d $SRCDIR ]; then
   echo -e $COLOR1"Directory$COLOR2 $SRCDIR $COLOR1 already exists."$NORMCO
else
   echo -e $COLOR1"Folder$COLOR2 $SRCDIR $COLOR1 does not exist. Will be created"$NORMCO
   echo -e $COLERR `mkdir -p $SRCDIR`$NORMCO  # -p, --parents     no error if existing, make parent directories as needed
fi

if [ -d "${SRCDIR}toolsouts/" ]; then
   echo -e $COLOR1"Directory$COLOR2 $SRCDIR/toolsouts/$COLOR1 already exists."$COLOR2
   echo -e $COLERR `rm   ${SRCDIR}toolsouts/*`$NORMCO
else
   echo -e $COLOR1"Folder$COLOR2 ${SRCDIR}toolsouts/$COLOR1 does not exist. Will be created"$COLOR2
   echo -e $COLERR `mkdir -p "${SRCDIR}toolsouts/" `$NORMCO
fi

echo -e $COLERR `mv "$SOURCES/local.h" "$SOURCES/cppsrc/"`$NORMCO

#REAL TRANSLATION
echo -e $COLOR4"DOING REAL TRANSLATION:"$NORMCO

#Preparing C++ source files

if [[ $SOURCEMODE == "multisrc" ]]
then
     echo -e $COLERR"$SOURCEMODE required but not implemented yet!"$NORMCO
     exit -2
fi

echo "/*All sources in one file?*/" > ./cppsrc/project_at_once.cpp

echo "#include \"processing_consts.hpp\"" >> ./cppsrc/project_at_once.cpp
echo "#include \"processing_templates.hpp\"" >> ./cppsrc/project_at_once.cpp
echo "#include \"processing_library.hpp\"" >> ./cppsrc/project_at_once.cpp
echo "#include \"processing_inlines.hpp\" //...is optional. Use when project is already compilable!" >> ./cppsrc/project_at_once.cpp
echo "#include \"processing_window.hpp\"" >> ./cppsrc/project_at_once.cpp
${SCRIPTS}/includeOptionals.sh *.pde >> ./cppsrc/project_at_once.cpp
echo "using namespace Processing;" >> ./cppsrc/project_at_once.cpp
echo "#include \"local.h\"" >> ./cppsrc/project_at_once.cpp
echo "//==================================================================================" >> ./cppsrc/project_at_once.cpp
echo "const char* Processing::_PROGRAMNAME=\"$PROJECT\";" >> ./cppsrc/project_at_once.cpp

FILES=*.pde
for f in $FILES
do # take action on each file. $f store current file name
  echo -e "File:$COLOR2 $f $NORMCO\t-->\t$COLOR2./cppsrc/$f.cpp$NORMCO\n"
  echo "#include \"$f.cpp\"" >> "$SOURCES/cppsrc/project_at_once.cpp"
  $SCRIPTS/procesing2cpp.sh "$f" > "./cppsrc/$f.cpp"
done

#Preparing CMakeLists.txt    --> https://stackoverflow.com/questions/2500436/how-does-cat-eof-work-in-bash
echo -e "\nCreating$COLOR1 CMakeLists.txt $NORMCO"
cat << EOF > CMakeLists.txt
# This file was made automagically. Do not edit!
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
#/*               PROCESSING2C  version 2022-11-23                   */
#/********************************************************************/
#/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
#/*            W O J C I E C H   B O R K O W S K I                   */
#/*    Instytut Studiów Społecznych Uniwersytetu Warszawskiego       */
#/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
#/*    GITHUB: https://github.com/borkowsk                           */
#/*                                                                  */
#/*                               (Don't change or remove this note) */
#/********************************************************************/

