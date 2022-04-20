//All sources in one file 
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
//#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_alist.hpp"     //...is optional. Should be deleted when not needed.
#include "processing_lists.hpp"     //...is optional. Should be deleted when not needed.
#include "processing_map.hpp"       //...is optional. Should be deleted when not needed.
#include "processing_files.hpp"     //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================
const char* Processing::_PROGRAMNAME="TOCEVO";
#include "Agent.pde.cpp"
#include "AgentBasics.pde.cpp"
#include "AssemblingOfWorld.pde.cpp"
#include "CABasics.pde.cpp"
#include "ModelStats.pde.cpp"
#include "ModelVisualCA.pde.cpp"
#include "ModelVisual.pde.cpp"
#include "RTMEvents.pde.cpp"
#include "RTMExit.pde.cpp"
#include "RTMMouseInspect.pde.cpp"
#include "RTMVideo.pde.cpp"
#include "TragedyOfCommons.pde.cpp"
