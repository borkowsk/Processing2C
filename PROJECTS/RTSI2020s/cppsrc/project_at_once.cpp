//All sources in one file 
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
#include "processing_inlines.hpp" //is optional. Use when project is already compilable
using namespace Processing;
#include "local.h"
#include "project.h" //This is for you. Could be deleted when not needed
//==================================================================================
const char* Processing::_PROGRAMNAME="RTSI2020s";
#include "A1Network.pde.cpp"
#include "Abstract.pde.cpp"
#include "Agent.pde.cpp"
#include "AssembOfWorld.pde.cpp"
#include "InfoCalc.pde.cpp"
#include "InitModel.pde.cpp"
#include "ModelStats.pde.cpp"
#include "ModelSteps.pde.cpp"
#include "ModelVisual.pde.cpp"
#include "NetLinkMani.pde.cpp"
#include "NetVisual.pde.cpp"
#include "PropOfWorld.pde.cpp"
#include "RTMEvents.pde.cpp"
#include "RTMExit.pde.cpp"
#include "RTMMoInsp.pde.cpp"
#include "RTSI2020s.pde.cpp"
#include "UtilCharts.pde.cpp"
#include "UtilsGraph.pde.cpp"
