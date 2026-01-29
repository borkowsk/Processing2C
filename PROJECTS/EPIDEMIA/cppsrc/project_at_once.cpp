/// @file 
/* All sources included in one file. */
/// @date 2026-01-29 (0.26.01)
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
#ifdef _NDEBUG
#include "processing_inlines.hpp" //...is optional.
#endif // _NDEBUG
#include "processing_string.hpp"  //Processing::String class
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_lists.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h"
#include <iostream>
//==============================================================================
const char* Processing::_PROGRAMNAME="EPIDEMIA";
#include "AgentDef.pde.hpp"
#include "AgentSupl.pde.hpp"
#include "AssemblingOfWorld.pde.hpp"
#include "exit_common.pde.hpp"
#include "Histogram.pde.hpp"
#include "History.pde.hpp"
#include "ModelVisual.pde.hpp"
#include "EPIDEMIA.pde.hpp"
