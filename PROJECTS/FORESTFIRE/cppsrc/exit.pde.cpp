//Processing to C++ converter /data/wb/SCC/public/Processing2C/scripts/procesing2cpp.sh
//Source: exit.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

void processing_window::exit() //it is called whenever a window is closed. 
{
  noLoop();   // For to be sure...
  delay(100); // it is quite possible to close window when draw( ) is currently working!
  Log->flush Writes the remaining data to the file
  Log->close Finishes the file
  save("exit.png");
  println("Thank You");
  processing_window_base::exit(); //What library superclass have to do at exit
} 
///data/wb/SCC/public/Processing2C/scripts did it

