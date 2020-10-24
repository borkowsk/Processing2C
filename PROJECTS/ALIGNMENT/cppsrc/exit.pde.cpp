//Processing to C++ converter /data/wb/SCC/__working_copies/Processing2C/scripts/procesing2cpp.sh
//Source: exit.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
//#include "processing_inlines.hpp" //is optional. Use when project is already compilable
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

void processing_window::exit()
{
  save("exit.png");//Without extension in Processing it produce TIFF, in C++ file format depend on implementation
  processing_window_base::exit();//What shoud be done by default!
}
///data/wb/SCC/__working_copies/Processing2C/scripts/procesing2cpp.sh did it

