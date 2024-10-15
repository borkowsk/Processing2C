/// @file 
/* All sources included in one file. */
/// @date 2024-10-15 (0.22j)
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
#ifdef _NDEBUG
#include "processing_inlines.hpp" //...is optional.
#endif // _NDEBUG
#include "processing_string.hpp"  //Processing::String class
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_files.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h"
#include <iostream>
//==============================================================================
const char* Processing::_PROGRAMNAME="SAKODA";
#include "AgentA.pde.hpp"
#include "AgentBasics.pde.hpp"
#include "AssemblingOfWorld.pde.hpp"
#include "ModelStats.pde.hpp"
#include "ModelVisual.pde.hpp"
#include "RTMEvents.pde.hpp"
#include "RTMExit.pde.hpp"
#include "SAKODA.pde.hpp"
