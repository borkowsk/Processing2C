#!/bin/bash
# This script have to prepare cmake C++ project in directory containing Processing project
# One optional parameter is possible:  multisrc
# But it is still TODO!
#
# Processing2C version 22h.
# @date 2024-10-15 (last modif.)
#
Pr2CVERSION="0.22j"

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
echo -e $COLOR4"\nMaking PROCESSING2C project in "$COLOR1 `pwd` $NORMCO "\n"
echo -e $COLOR4"\nConfiguration directories:"$NORMCO

export SOURCES=`pwd`
export PROJECT=$(basename "$SOURCES")

source $SCRIPTS/config.dat

#echo -e WBRTM  $COLOR1"      $WBRTM"$NORMCO
echo -e PROC2DIR $COLOR1"    $PROC2DIR"$NORMCO
echo -e SCRIPTS $COLOR1"     $SCRIPTS"$NORMCO
echo -e WBSYMSHELL $COLOR1"  $SYMSHELL"$NORMCO

echo -e PROJECT $COLOR1"     $PROJECT"$NORMCO
echo -e SOURCES $COLOR1"     $SOURCES"$NORMCO

#SINGLE OR MULTISOURCE?
echo -e $COLOR4"\nChecking number of pde sources."$NORMCO
export NUMBER_OF_PDES=`ls -1 *.pde | grep -v exit | wc -l`

if [[ $NUMBER_OF_PDES == 0 ]]; then
  $ECHO $COLERR"No any '*.pde' files in this folder.\nNothing to do!!!"$NORMCO  \
  1>&2
  exit -1
else
  $ECHO $COLOR3'\nNumber of "*.pde" source files excluding "exit*.pde":'$COLOR2 \
          $NUMBER_OF_PDES  $NORMCO
fi

echo -e $COLOR4"\nChecking single/multi sources mode:\n"$NORMCO
export SOURCEMODE=$1

if [[ $SOURCEMODE != "multisrc" ]]; then
     SOURCEMODE="singlesrc"
fi

echo -e $COLOR3"Project will be translated in mode:$COLOR2 $SOURCEMODE"$NORMCO

#CHECK SOURCE
$ECHO $COLOR4"\nCHECKING IDENTIFIERS..."$NORMCO

$ECHO $COLOR2"\nAt least setup() or draw() function expected in *.pde files:"$NORMCO
egrep  -Hn --color=always '^void\s+(setup\(\)|draw\(\))' *.pde

$ECHO $COLOR2"\nOnly non parametrised event handlers are alloved. These are such ones in *.pde files:"$NORMCO
egrep  -Hn --color=always '^void\s+(keyPressed\(\)|keyReleased\(\)|mouseClicked\(\)|mousePressed\(\)|mouseReleased\(\)|mouseMoved\(\)|mouseDragged\(\))' *.pde

$ECHO $COLOR2"\nThe following lines may hide library symbols..."$NORMCO
#exclude pseudo declaration then check for any construct ::identifier::\s+(::one of library identifier::) 
grep -P -Hn  --color=always -f $SCRIPTS/symbols_pattern.grep *.pde

#$ECHO $COLOR4"\nCHECKING IDENTIFIERS FINISHED\n"$NORMCO

#GET GLOBAL SYMBOLS
$ECHO $COLOR4"\nSEARCHING GLOBAL SYMBOLS:"$NORMCO
$SCRIPTS/prepare_local_h.sh



if [[ $SOURCEMODE == "multisrc" ]] #==========================================================================================================================
then

# MULTI-SOURCE MODE BELOW:
#*########################

$ECHO $COLOR4"\nCHECKING DIRECTORIES FOR multisrc MODE...\n"$NORMCO

export SRCDIR="./multi_cpp/"    
if [ -d "${SRCDIR}" ]; then
  $ECHO $COLOR2"Directory ${COLOR1}${SRCDIR}${COLOR2} already exists."$NORMCO
else
  $ECHO $COLOR2"Folder ${COLOR1}${SRCDIR}${COLOR2} does not exist. Will be created"$NORMCO
  $ECHO $COLERR`mkdir -p $SRCDIR ` $NORMCO  # -p, --parents  no error if existing, make parent directories as needed
fi

export TOOLSOUTDIR="./multi_pde/"
if [ -d "${TOOLSOUTDIR}" ]; then
  $ECHO $COLOR2"Directory ${COLOR1}${TOOLSOUTDIR}${COLOR2} already exists."$NORMCO
else
  $ECHO $COLOR2"Folder ${COLOR1}${TOOLSOUTDIR}${COLOR2} does not exist. Will be created"$NORMCO
  $ECHO $COLERR `mkdir -p ${TOOLSOUTDIR} `$NORMCO
fi

if [ -d "${TOOLSOUTDIR}.bak_classes/" ]; then
  $ECHO $COLOR2"Directory ${COLOR1}${TOOLSOUTDIR}.bak_classes/${COLOR2} already exists."$NORMCO  
else
  $ECHO $COLERR `mkdir -p ${TOOLSOUTDIR}.bak_classes/ ` $NORMCO
fi

$ECHO $COLERR `rm ${TOOLSOUTDIR}/* `$NORMCO
$ECHO $COLERR `mv "$SOURCES/local.h" "$SRCDIR" `$NORMCO

#REAL TRANSLATION
$ECHO $COLOR4"DOING REAL TRANSLATION:"$NORMCO

# W trybie multi trzeba tłumaczyć dyrektywy _import_class
echo 's|\/\*_import_class:\s*(\w+)\s*\*\/|#include "\1_class@@@pde@@@hpp"|' >> userclasses.sed

FILES="*.pde"
for f in $FILES
do # take action on each file. $f store current source file name
  $ECHO $COLOR3"Translating file:$COLOR1 $f $NORMCO\t-->\t${COLOR2}${SRCDIR}${f}.cpp$NORMCO\n"
  #$ECHO $SCRIPTS/procesing2cpp.sh "$f" "${TOOLSOUTDIR}" -CLSS '>' "${SRCDIR}$f.cpp"
  $ECHO "/// @file" > "${SRCDIR}$f.cpp"
  $SCRIPTS/procesing2cpp.sh "$f" "${TOOLSOUTDIR}" "-ECLL" >> "${SRCDIR}$f.cpp"
done

echo "const char* Processing::_PROGRAMNAME=\"$PROJECT\";"            >> ${SRCDIR}$PROJECT.pde.cpp

CLASSFILES="${TOOLSOUTDIR}*_class.pde"
for f in $CLASSFILES
do # take action on each file. $f store current class file name
  if [ -f "$f" ]; then 
	  FBASE=$(basename "$f")
	  #echo STAGE1 1>&2
	  $ECHO $COLOR3"Translating file:$COLOR1 $f $NORMCO\t-->\t${COLOR2}${SRCDIR}${FBASE}.hpp$NORMCO\n"
	  #echo STAGE2 1>&2
	  #$ECHO $SCRIPTS/procesing2cpp.sh "$f" "${TOOLSOUTDIR}.bak_classes/" '>' "${SRCDIR}${FBASE}.hpp"
	  #echo STAGE3 1>&2
	  $ECHO "/// @file" > "${SRCDIR}${FBASE}.hpp"
	  #echo STAGE4 1>&2
	  $SCRIPTS/procesing2cpp.sh "$f" "${TOOLSOUTDIR}.bak_classes/" >> "${SRCDIR}${FBASE}.hpp" 
  else
      $ECHO $COLERR "File $f not found!" $NORMCO
  fi
done


cat ${TOOLSOUTDIR}/${PROJECT}.pde_imp.pde > ${TOOLSOUTDIR}/multi_pde.pde
echo -e "// multi_pde.pde\nString PROJECT_NAME=\"$PROJECT\";\n" >> ${TOOLSOUTDIR}/multi_pde.pde
mv ${TOOLSOUTDIR}/${PROJECT}.pde_imp.pde ${TOOLSOUTDIR}/${PROJECT}.pde_imp.bak


#exit 1

#FINAL WORK
$ECHO $COLOR4"FINALISING..."$NORMCO

#Preparing CMakeLists.txt    --> https://stackoverflow.com/questions/2500436/how-does-cat-eof-work-in-bash
$ECHO $COLOR3"\nCreating$COLOR1 ${SRCDIR}CMakeLists.txt $NORMCO"

cat << EOF > ${SRCDIR}CMakeLists.txt
# This file was made automagically. Do not edit!
#! @date $TIMEMARK (translation timemark)
cmake_minimum_required(VERSION 3.5)
set( CMAKE_VERBOSE_MAKEFILE off )

project( ${PROJECT}_M )
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

set( SRCPATH  "./" )
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

set(  SRCCODESLIST 
EOF

#List of modules
pushd "${SRCDIR}" >> /dev/null

FILES="*.pde.???"
for f in $FILES
do
  echo -e "\t\"$f\"" >> CMakeLists.txt
done

popd >> /dev/null

#Final part of CMakeLists.txt
cat << EOF >> ${SRCDIR}CMakeLists.txt
        )
        
add_executable("\${PROJECT_NAME}_\${VERSION_NUM}_x11"
               "\${SRCCODESLIST}"
              )

add_executable("\${PROJECT_NAME}_\${VERSION_NUM}_svg"
               "\${SRCCODESLIST}"
              )

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

EOF

else #singlesrc below #========================================================================================================================================

# SINGLE-SOURCE MODE BELOW:
#*#########################

#LETS CHECK OUTPUT DIRECTORIES!
$ECHO $COLOR4"\nCHECKING OUTPUT DIRECTORIES:"$NORMCO

#https://stackoverflow.com/questions/18622907/only-mkdir-if-it-does-not-exist
export SRCDIR="./cppsrc/"    
if [ -d ${SRCDIR} ]; then
  $ECHO $COLOR2"Directory ${COLOR1}${SRCDIR}${COLOR2} already exists."$NORMCO
else
  $ECHO $COLOR2"Folder ${COLOR1}${SRCDIR}${COLOR1} does not exist. Will be created"$NORMCO
  $ECHO $COLERR`mkdir -p $SRCDIR` $NORMCO  # -p, --parents  no error if existing, make parent directories as needed
fi

export TOOLSOUTDIR="${SRCDIR}toolsouts/"
if [ -d ${TOOLSOUTDIR} ]; then
  $ECHO $COLOR2"Directory ${COLOR1}${TOOLSOUTDIR}${COLOR2} already exists."$NORMCO
  $ECHO $COLERR `rm ${TOOLSOUTDIR}/*`$NORMCO
else
  $ECHO $COLOR2"Folder ${COLOR1}${SRCDIR}${COLOR2} does not exist. Will be created"$NORMCO
  $ECHO $COLERR `mkdir -p ${TOOLSOUTDIR} `$NORMCO
fi

$ECHO $COLERR `mv "$SOURCES/local.h" "$SOURCES/cppsrc/"`$NORMCO


#OPTIONAL HEADERS
$ECHO $COLOR4"PREPARING INCLUDES FOR $SOURCEMODE MODE:"$NORMCO

#Preparing C++ source files

echo -e "/// @file \n/* All sources included in one file. */"         > ./cppsrc/project_at_once.cpp
echo "/// @date 2024-10-15 ($Pr2CVERSION)"                           >> ./cppsrc/project_at_once.cpp
echo "#include \"processing_consts.hpp\""                            >> ./cppsrc/project_at_once.cpp
echo "#include \"processing_templates.hpp\""                         >> ./cppsrc/project_at_once.cpp
echo "#include \"processing_library.hpp\""                           >> ./cppsrc/project_at_once.cpp
echo "#include \"processing_window.hpp\""                            >> ./cppsrc/project_at_once.cpp
echo "#ifdef _NDEBUG"                                                >> ./cppsrc/project_at_once.cpp
echo "#include \"processing_inlines.hpp\" //...is optional."         >> ./cppsrc/project_at_once.cpp
echo "#endif // _NDEBUG"                                             >> ./cppsrc/project_at_once.cpp
${SCRIPTS}/includeOptionals.sh *.pde                                 >> ./cppsrc/project_at_once.cpp
echo "using namespace Processing;"                                   >> ./cppsrc/project_at_once.cpp
[[ -f "./cppsrc/pre_local.h" ]] && echo "#include \"pre_local.h\""   >> ./cppsrc/project_at_once.cpp
echo "#include \"local.h\""                                          >> ./cppsrc/project_at_once.cpp
[[ -f "./cppsrc/post_local.h" ]] && echo "#include \"post_local.h\"" >> ./cppsrc/project_at_once.cpp
echo "#include <iostream>"                                           >> ./cppsrc/project_at_once.cpp
echo "//==============================================================================" >> ./cppsrc/project_at_once.cpp
echo "const char* Processing::_PROGRAMNAME=\"$PROJECT\";"            >> ./cppsrc/project_at_once.cpp

#REAL TRANSLATION
$ECHO $COLOR4"DOING REAL TRANSLATION:"$NORMCO

FILES=*.pde
for f in $FILES
do # take action on each file. $f store current file name
  $ECHO $COLOR3"Translating file:$COLOR1 $f $NORMCO\t-->\t$COLOR2./cppsrc/$f.hpp$NORMCO\n"
  $SCRIPTS/procesing2cpp.sh "$f" "${TOOLSOUTDIR}" > "./cppsrc/$f.hpp"

  if [[ "$f" != "$PROJECT.pde" ]]; then # Why? See below...
  	echo "#include \"$f.hpp\"" >> "$SOURCES/cppsrc/project_at_once.cpp"
  fi

done

# Most problems with undeclared types were because the main file includes itself 
# in random places depending on the name! Now it will be always the last one.
echo "#include \"$PROJECT.pde.hpp\"" >> "$SOURCES/cppsrc/project_at_once.cpp"

#FINAL WORK
$ECHO $COLOR4"FINALISING..."$NORMCO

#Preparing CMakeLists.txt    --> https://stackoverflow.com/questions/2500436/how-does-cat-eof-work-in-bash
$ECHO $COLOR3"\nCreating$COLOR1 CMakeLists.txt $NORMCO"
cat << EOF > CMakeLists.txt
# This file was made automagically. Do not edit!
#! @date $TIMEMARK (translation timemark)
cmake_minimum_required(VERSION 3.5)
set( CMAKE_VERBOSE_MAKEFILE off )

project( ${PROJECT}_S )
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

EOF

fi  #multisrc else singlesrc


$ECHO $COLOR4"\nProject$COLOR1 ${PROJECT}$COLOR4 DONE\n\n"$NORMCO

#/********************************************************************/
#/*                 PROCESSING2C  release 2024                       */
#/********************************************************************/
#/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
#/*            W O J C I E C H   B O R K O W S K I                   */
#/*    Instytut Studiów Społecznych Uniwersytetu Warszawskiego       */
#/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
#/*    GITHUB: https://github.com/borkowsk                           */
#/*                                                                  */
#/*                               (Don't change or remove this note) */
#/********************************************************************/

