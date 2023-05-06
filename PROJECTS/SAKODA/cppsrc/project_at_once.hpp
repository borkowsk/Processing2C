/*All sources in one file?*/
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "processing_string.hpp"  //Processing::String class
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_files.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================
const char* Processing::_PROGRAMNAME="SAKODA";
#include "AgentA.pde.hpp"
#include "AgentBasics.pde.hpp"
#include "AssemblingOfWorld.pde.hpp"
#include "ModelStats.pde.hpp"
#include "ModelVisual.pde.hpp"
#include "RTMEvents.pde.hpp"
#include "RTMExit.pde.hpp"
#include "SAKODA.pde.hpp"
