cmake_minimum_required(VERSION 2.9)

project(WBProcessing)

set(PROC2CDIR "/data/wb/SCC/public/Processing2C" )
set(SYMSHELL  "/data/wb/SCC/public/SymShellLight" )

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories( "${PROC2CDIR}/lib/include" "${SYMSHELL}" )

if(true)
add_definitions( -DHAVE_X11 -DUSE_X11 )
add_library( wbprocess STATIC
    "${PROC2CDIR}/lib/src/_errMessage.cpp"
    "${PROC2CDIR}/lib/src/main.cpp"
    "${PROC2CDIR}/lib/src/delay.cpp"
    "${PROC2CDIR}/lib/src/pwindow.cpp"
    "${PROC2CDIR}/lib/src/pobject.cpp"
    "${PROC2CDIR}/lib/src/pstrings.cpp"
    "${PROC2CDIR}/lib/src/pbasegrapx.cpp"
    "${PROC2CDIR}/lib/src/pshape.cpp"
    "${PROC2CDIR}/lib/src/pfont.cpp"
    "${PROC2CDIR}/lib/src/pimage.cpp"
    "${PROC2CDIR}/lib/src/pconsole.cpp"
    "${PROC2CDIR}/lib/src/pnumberformat.cpp"
    "${PROC2CDIR}/lib/src/parrayformat.cpp"
    "${PROC2CDIR}/lib/src/pprintwriter.cpp"
    "${PROC2CDIR}/lib/src/plibrary.cpp"
    "${PROC2CDIR}/lib/src/plists.cpp"
    "${PROC2CDIR}/lib/src/psplit.cpp"
    "${PROC2CDIR}/lib/src/pdatetime.cpp"
    "${PROC2CDIR}/lib/src/processing_exit.cpp"
    "${PROC2CDIR}/lib/src/max.cpp"
    "${PROC2CDIR}/lib/src/min.cpp"
    "${PROC2CDIR}/lib/src/pnoise.cpp"
    "${PROC2CDIR}/lib/src/mouseClicked.cpp"
    "${PROC2CDIR}/lib/src/mousePressed.cpp"
    "${PROC2CDIR}/lib/src/mouseReleased.cpp"
    "${PROC2CDIR}/lib/src/mouseMoved.cpp"
    "${PROC2CDIR}/lib/src/mouseDragged.cpp"
    "${PROC2CDIR}/lib/src/keyPressed.cpp"
    "${PROC2CDIR}/lib/src/keyReleased.cpp"
    "${PROC2CDIR}/lib/src/window_exit.cpp"
    "${PROC2CDIR}/lib/src/window_draw.cpp"
    "${PROC2CDIR}/lib/src/window_setup.cpp"
    "${PROC2CDIR}/lib/src/window_settings.cpp"
    "${PROC2CDIR}/lib/src/pwindow_destructor.cpp"
    "${PROC2CDIR}/lib/src/pwindow_exit.cpp"
        )


target_compile_options( wbprocess PRIVATE "${CMAKE_CXX_FLAGS}" "-fPIC" "-w"  "-pthread" )

endif()



#KONIEC
