//All sources in one file 
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_inlines.hpp" //is optional. Use when project is already compilable
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed!
#include "processing_lists.hpp"   //is optional. Should be deleted when not needed!
#include "processing_map.hpp"     //is optional. Should be deleted when not needed!

using namespace Processing;
#include "local.h"
#include "project.h" //This is for you. Could be deleted when not needed
//==================================================================================
const char* Processing::_PROGRAMNAME="ARRAYLIST";
#include "ARRAYLIST.pde.cpp"
