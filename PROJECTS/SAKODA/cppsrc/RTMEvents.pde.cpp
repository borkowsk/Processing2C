//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: RTMEvents.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
//#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_alist.hpp" //...is optional. Should be deleted when not needed.
#include "processing_lists.hpp" //...is optional. Should be deleted when not needed.
#include "processing_map.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_files.hpp" //...is optional. Should be deleted when not needed.
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

/// ABM model of segregation (test project for Processing2C)
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: RTMEventHandling->pde
/////////////////////////////////////////////////////////////////////////////////////////
//  Dopasowana do modelu obsługa zdarzeń
/////////////////////////////////////////////////////////////////////////////////////////
int searchedX=-1;
int searchedY=-1;
bool    Clicked=false;
pAgent  theSelected=nullptr; 

double minDist2Selec=MAX_INT;
double maxTransSelec=-MAX_INT;

void processing_window::onMouseClicked()
{
  Clicked=true;
  theSelected=nullptr;
  searchedX=mouseX;
  searchedY=mouseY; //Searching should be implemented in visialisation!
  key=0;
}

void processing_window::onKeyPressed() 
{
  println("RECIVED:'",key,"\' CODE:",int(key)); 
  switch(key)
  {
  case '1': STEPSperVIS=1;background(255,255,200);text(String("StPerV: ")+STEPSperVIS,1,16);break;
  case '2': STEPSperVIS=2;background(255,255,200);text(String("StPerV: ")+STEPSperVIS,1,16);break;
  case '3': STEPSperVIS=5;background(255,255,200);text(String("StPerV: ")+STEPSperVIS,1,16);break;
  case '4': STEPSperVIS=10;background(255,255,200);text(String("StPerV: ")+STEPSperVIS,1,16);break;
  case '5': STEPSperVIS=25;background(255,255,200);text(String("StPerV: ")+STEPSperVIS,1,16);break;
  case '6': STEPSperVIS=50;background(255,255,200);text(String("StPerV: ")+STEPSperVIS,1,16);break;
  case '7': STEPSperVIS=100;background(255,255,200);text(String("StPerV: ")+STEPSperVIS,1,16);break;
  case '8': STEPSperVIS=150;background(255,255,200);text(String("StPerV: ")+STEPSperVIS,1,16);break;
  case '9': STEPSperVIS=200;background(255,255,200);text(String("StPerV: ")+STEPSperVIS,1,16);break;
//  case '0': STEPSperVIS=1;DeltaMC=0.2;text(String("DeltaMC: ")+DeltaMC,1,16);break;
  case ' ': saveFrame(modelName+String(".")+nf((float)StepCounter,6,5)+ String(".PNG"));
            //write(world,modelName+String(".")+nf((float)StepCounter,6,5));//Aktualny stan ekosystemu
            break;
  case ESC: simulationRun=!simulationRun; break;
  case 's': simulationRun=false; break;
  case 'r': simulationRun=true; break;
  default:println(String("Command '")+key+ String("' unknown"));
          println("USE:");
          println("1-9 for less frequent visualisation");
          println("  0 for most frequent visualisation");
          println("ESC,r,s for pause/run simulation");
          println("SPACE for dump the current screen\n"); 
  break;
  }
  
  if (key == ESC) 
  {
    key = 0;  // Fools! don't let them escape!
  }
}


///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM EVENTS TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////
//../../scripts/procesing2cpp.sh did it

