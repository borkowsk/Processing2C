/// @file
/// @note Automatically made from _RTMEvents.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
/// @date 2024-10-15 16:11:05 (translation)
//
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
#ifndef _NO_INLINE
#include "processing_inlines.hpp" //...is optional.
#endif // _NO_INLINE
#include "processing_string.hpp"  //Processing::String class
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_files.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

// @date 2024-09-30 (last modification)
/// Model-tailored event handling.
//*/////////////////////////////////////////////////

void processing_window::onKeyPressed()
{
  //println("RECIVED:'",key,"\' CODE:",int(key)); //DEBUG
  switch(key)
  {
  case 'q': exit();
  case '1': STEPSperVIS=1;background(255,255,200);println(String("StPerV: ")+STEPSperVIS,1,16);break;
  case '2': STEPSperVIS=2;background(255,255,200);println(String("StPerV: ")+STEPSperVIS,1,16);break;
  case '3': STEPSperVIS=5;background(255,255,200);println(String("StPerV: ")+STEPSperVIS,1,16);break;
  case '4': STEPSperVIS=10;background(255,255,200);println(String("StPerV: ")+STEPSperVIS,1,16);break;
  case '5': STEPSperVIS=25;background(255,255,200);println(String("StPerV: ")+STEPSperVIS,1,16);break;
  case '6': STEPSperVIS=50;background(255,255,200);println(String("StPerV: ")+STEPSperVIS,1,16);break;
  case '7': STEPSperVIS=100;background(255,255,200);println(String("StPerV: ")+STEPSperVIS,1,16);break;
  case '8': STEPSperVIS=200;background(255,255,200);println(String("StPerV: ")+STEPSperVIS,1,16);break;
  case '9': STEPSperVIS=500;background(255,255,200);println(String("StPerV: ")+STEPSperVIS,1,16);break;
  case '0': STEPSperVIS=1000;background(255,255,200);println(String("StPerV: ")+STEPSperVIS,1,16);break;
//  case '0': STEPSperVIS=1;DeltaMC=0.2;text(String("DeltaMC: ")+DeltaMC,1,16);break;
  case ' ': save(modelName+String(".")+nf((float)StepCounter,6,5)+ String(".PNG"));
            //write(world,modelName+String(".")+nf((float)StepCounter,6,5));//Aktualny stan ekosystemu
            break;
  case ESC: simulationRun=!simulationRun; break;
  case 's': simulationRun=false; break;
  case 'r': simulationRun=true; break;
  default:println(String("Command '")+key+ String("' unknown"));
          println("USE:");
          println("1-9 for less frequent visualisation");
          //println("  0 for most frequent visualisation");
          println("ESC,r,s for pause/run simulation");
          println("SPACE for dump the current screen\n"); 
  break;
  }
  
  if (key == ESC) 
  {
    key = 0;  // Fools! don't let them escape!
  }
}


//*/////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM EVENTS TEMPLATE
//*/////////////////////////////////////////////////////////////////////////////////////////
//MADE NOTE: ../../scripts did it 2024-10-15 16:11:05 !
