cmake_minimum_required(VERSION 2.8)

project(WBProcessing)

set(WBRTM "/data/wb/SCC/__working_copies/symShell2/WBRTM_Linux/" )
set(WBPROCDIR "/data/wb/SCC/__working_copies/Processing2C/" )
set(CONTRLIBS "${WBRTM}/CONTRLIBS")

include_directories( "${WBPROCDIR}/lib/include" "${WBRTM}" "${CONTRLIBS}")

if(true)
add_definitions( -DHAVE_X11 -DUSE_X11 )
add_library( wbprocess STATIC 
    "${WBPROCDIR}/lib/src/main.cpp"
    "${WBPROCDIR}/lib/src/pwindow.cpp"
    "${WBPROCDIR}/lib/src/plibrary.cpp"
    "${WBPROCDIR}/lib/src/pconsole.cpp"
    "${WBPROCDIR}/lib/src/max.cpp"
    "${WBPROCDIR}/lib/src/min.cpp"
    "${WBPROCDIR}/lib/src/window_exit.cpp"
    "${WBPROCDIR}/lib/src/mouseClicked.cpp"
)
endif()



#KONIEC
