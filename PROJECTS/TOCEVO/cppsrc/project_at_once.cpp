/* All sources in one file? */
// @date 2024-10-10 (0.22i)
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
#include <iostream>
//==================================================================================
const char* Processing::_PROGRAMNAME="TOCEVO";
#include "AgentAd.pde.hpp"
#include "AgentBasics.pde.hpp"
#include "AssemblingOfWorld.pde.hpp"
#include "CABasics.pde.hpp"
#include "ModelStats.pde.hpp"
#include "ModelVisualCA.pde.hpp"
#include "ModelVisual.pde.hpp"
#include "RTMEvents.pde.hpp"
#include "RTMExit.pde.hpp"
#include "RTMMouseInspect.pde.hpp"
#include "RTMVideo.pde.hpp"
#include "TOCEVO.pde.hpp"
