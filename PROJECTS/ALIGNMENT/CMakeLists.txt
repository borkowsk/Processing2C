# This file was made automagically. Do not edit!
#! @date 2024-10-15 16:10:55 (translation timemark)
cmake_minimum_required(VERSION 3.5)
set( CMAKE_VERBOSE_MAKEFILE off )

project( ALIGNMENT_S )
set( VERSION_NUM 0.22j ) #MUST BE NUMERIC 

IF (WIN32)
  # set stuff for windows
  message( ${PROJECT_NAME} ": MS Windows platform assumed.\n\tInside C/C++ code automatic _MSC_VER variable will be used!" )
  #set( WINDOWS_ONLY_SRC  "" )
ELSE()
  # set stuff for other systems
  message( ${PROJECT_NAME} ": Linux/unix platform assumed." )
  #set( X_ONLY_SRC  "" )
ENDIF()

set( SRCPATH  "/data/wb/SCC/public/Processing2C/PROJECTS/ALIGNMENT/cppsrc/" )
set( PROC2C   "/data/wb/SCC/public/Processing2C" )
set( SYMSHELL "/data/wb/SCC/public/SymShellLight" )
set( WBRTM    "" )

set( MYLIBS   "/lib" )

# THESE LINES BELOW COULD BE UNCOMMENTED WHEN LIBRARIES SEEMS TO BE NOT COMPILED.
#add_subdirectory( "${SYMSHELL}"
#                  "${SYMSHELL}" )
#add_subdirectory( "${PROC2C}/lib/"
#                  "${PROC2C}/lib/" )

add_definitions( -DVERSION_NUM=${VERSION_NUM} ) # -DMULTITR -DDEF_MAXTHREADS=16 

include_directories(  "${SRCPATH}" "${PROC2C}/lib/include" "${SYMSHELL}" "${WBRTM}/INCLUDE" )

add_executable("${PROJECT_NAME}_${VERSION_NUM}_x11"
               "${SRCPATH}project_at_once.cpp"
              )

add_executable("${PROJECT_NAME}_${VERSION_NUM}_svg"
               "${SRCPATH}project_at_once.cpp"
              )

#add_executable("${PROJECT_NAME}_${VERSION_NUM}"

#	"${SRCPATH}project_at_once.cpp"
#        )

target_compile_options( "${PROJECT_NAME}_${VERSION_NUM}_x11" PRIVATE "${CMAKE_CXX_FLAGS}" "-w" "-std=c++14" "-pthread" )
target_link_libraries( "${PROJECT_NAME}_${VERSION_NUM}_x11"  
     "-L${PROC2C}/lib"
     "-L${SYMSHELL}"
     wbprocess wbsyshLight X11 Xpm
     ${CMAKE_THREAD_LIBS_INIT}
     pthread
     rt
     )

target_compile_options( "${PROJECT_NAME}_${VERSION_NUM}_svg" PRIVATE "${CMAKE_CXX_FLAGS}" "-w" "-std=c++14" "-pthread" "-O3" )
target_link_libraries( "${PROJECT_NAME}_${VERSION_NUM}_svg"  
     "-L${PROC2C}/lib"
     "-L${SYMSHELL}"
     wbprocess wbsyshLightSVG
     ${CMAKE_THREAD_LIBS_INIT}
     pthread
     rt
     )

