//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: RTMExit.pde
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
//include "processing_inlines.hpp" //is optional. Use when project is already compilable
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

// Handling of exit from aplication - mainly closing open files!
/////////////////////////////////////////////////////////////////////
void processing_window::exit()          //it is called whenever a window is closed. 
{
  noLoop();          //For to be sure...
  delay(100);        // it is possible to close window when draw() is still working!
  
  //write(world,modelName+String(".")+nf((float)StepCounter,5,5));//end state of the system
  if(statisticsLogEnabled)
        CloseStatistics();

  //if(videoExportEnabled) 
  //        CloseVideo();    //Finalise of Video export
          
  println("Thank You");
  processing_window_base::exit();       //What library superclass have to do at exit
} 

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate.net/profile/WOJCIECH_BORKOWSKI - EXIT from TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////
//../../scripts/procesing2cpp.sh did it

