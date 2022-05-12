/*All sources in one file?*/
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "processing_string.hpp"  //Processing::String class
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_IntDict.hpp" //...is optional. Should be deleted when not needed.
#include "processing_FloatDict.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================
const char* Processing::_PROGRAMNAME="DICTSTEST";
#include "DICTSTEST.pde.cpp"
#include "exit.pde.cpp"