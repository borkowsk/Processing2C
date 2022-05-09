//Processing to C++ converter /data/wb/SCC/public/Processing2C/scripts/procesing2cpp.sh
//Source: SAKODA.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "processing_string.hpp"  //Processing::String class
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

/// ABM model of segregation (test project for Processing2C)
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "SAKODA.pde"
/////////////////////////////////////////////////////////////////////////////////////////
//   Sakoda inspired AGENT BASE MODEL utilized 1D or 2D dicrete geometry
//   implemented by Wojciech Borkowski
/////////////////////////////////////////////////////////////////////////////////////////

//Model parameters
int side=100 side of main table
String modelName="ABMSakoda
float density=0.55

pWorld TheWorld=new World(side); ///... but also will be initialised inside setup function

//Parameters of visualisation etc...
int cwidth=8 size of cell
int STATUSHEIGH=40
int STEPSperVIS=1
int FRAMEFREQ=20
bool WITH_VIDEO=false
bool simulationRun=trueStart/stop flag

void processing_window::setup()
{
  //Graphics
  size(800,840);
  setFrameRate(FRAMEFREQ);
  background(255,255,200);
  strokeWeight(2);
  
  //Model
  initializeModel(TheWorld);
  initializeStatsWykomentowanie blokuje tworzenie pliku log
  doStatistics(TheWorld);
  
  //Window 
  println(String("REQUIRED SIZE OF PAINTING AREA IS ")+(cwidth*side)+String("x")+(cwidth*side+STATUSHEIGH));
  cwidth=(height-STATUSHEIGHside;
    
  if(WITH_VIDEO) 
  {
    //initVideoExport(SAFE_THIS,modelName+ String(".mp4"),FRAMEFREQ);
    //FirstVideoFrame();
  }
  
  //Finishing setup stage
  println(String("CURRENT SIZE OF PAINTING AREA IS ")+width+String("x")+heightmyMenu->bounds->height???
  visualizeModel(TheWorldFirst time visualisation
  if(!simulationRun)
    println("PRESS 'r' or 'ESC' to start simulation");
  else
    println("PRESS 's' or 'ESC' to pause simulation");
  
  //NextVideoFrame();//It utilise inside variable to check if is enabled
}

void processing_window::draw()
{
  if(simulationRun)
  {
    modelStep(TheWorld);
    doStatistics(TheWorld);
  }
  
  writeStatusLine();
  
  if(!simulationRun //When simulation was stopped only visualisation should work
  || StepCounter % STEPSperVIS == 0 ) //But when model is running, visualisation shoud be done from time to time
  {
    visualizeModel(TheWorld);
    //NextVideoFrame();//It utilise inside variable to check if is enabled
  }

}

void writeStatusLine() /// Used also for stats
{
  fill(255);rect(0,side*cwidth,width,STATUSHEIGH);
  fill(0);noStroke();
  textAlign(LEFT, TOP);
  text(meanStress+String("  ")+liveCount,0,side*cwidth);
  textAlign(LEFT, BOTTOM);
  text(StepCounter+String(")  Fps:")+ frameRate,0,side*cwidth+STATUSHEIGH-2);
}

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM SAKODA MAIN 
///////////////////////////////////////////////////////////////////////////////////////////
///data/wb/SCC/public/Processing2C/scripts did it

