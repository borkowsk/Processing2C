//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: RTMExit.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
//#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h"
#include "project.h" //...is for you. Could be deleted when not needed.
//==================================================================================

/// ABM model of segregation (test project for Processing2C)
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: RTMExit->pde
//////////////////////////////////////////////////////////////////////////////////////////
void processing_window::exit()          //it is called whenever a window is closed. 
{
  noLoop();          //For to be sure...
  delay(100);        // it is possible to close window when draw() is still working!
  //write(world,modelName+String(".")+nf((float)StepCounter,5,5));//end state of the system
  
  if(outstat!=nullptr)
  {
    outstat->flush();  // Writes the remaining data to the file
    outstat->close();  // Finishes the file
  }
  
  //if(WITH_VIDEO) CloseVideo();    //Finalise of Video export
  
  println(modelName,"said: Thank You!");
  processing_window_base::exit();       //What library superclass have to do at exit()
} 

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - EXIT TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////
//../../scripts/procesing2cpp.sh did it

