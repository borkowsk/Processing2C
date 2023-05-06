//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: TragedyOfCommons.pde
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

//*   "TragedyOfCommons" AGENT BASE EVOLUTIONARY MODEL 
//*   utilized 2D discrete geometry
//*   implemented by Wojciech Borkowski
//*///////////////////////////////////////////////////////////////////////////////////////

//Model parameters
int side=200;//side of main table: 20,50,100,200,400
String modelName="TOC1.0_";

float treesDensity=0.250;
float treesR=1.015;///from 1..1.1 !
float agentsDensity=0.005;///Initial density of agents

bool    usePanishment=true;///Panishment swith off/on
bool    enableKilling=false;
//bool    symPanishment=true;///Panishment genes defines tolerance window for others behavior
char   panishmentTime=20;///How long panished agent is paralised

int   costOfStep=10; /// Metabolic cost for agent to live one step more.
float maxStock=costOfStep*50;///maximal stock per agent. The storage of unused energy is limited!
float maxInitialEnergyOfAgent=costOfStep*50;
float pOffspring=0.05;///How offten agent WANTs split into 2 agents

pWorld TheWorld=new World(side);//... but also will be initialised inside setup()

//Parameters of visualisation etc...
int cwidth=8;//size of cell
int STATUSHEIGH=40;
int STEPSperVIS=usePanishment?100:10;//Jak nie ma panishmentu to mogą szybko wymrzeć
int FRAMEFREQ=1000;
bool    WITH_NEW_DEL_LOG=false;///
bool    WITH_VIDEO=false;///
bool    simulationRun=true;//Start/stop flag

void processing_window::setup()
{
  //Graphics
  size(850,840);
  noSmooth();//Trochę szybciej
  background(0);
  strokeWeight(2);
  setFrameRate(FRAMEFREQ);
  
  //Model
  initializeModel(TheWorld);
  initializeStats();
  doStatistics(TheWorld);
  
  //Window 
  println(String("REQUIRED SIZE OF PAINTING AREA IS ")+(cwidth*side)+String("x")+(cwidth*side+STATUSHEIGH));
  cwidth=(height-STATUSHEIGH)/side;
    
  //Optionals:
  //setupMenu();//ISSUE: Size of MenuBar is not counted by Processing!
  //...
  if(WITH_VIDEO) 
  {
    initVideoExport(SAFE_THIS,modelName+ String(".mp4"),FRAMEFREQ);
    FirstVideoFrame();
  }
  
  //Finishing setup stage
  println(String("CURRENT SIZE OF PAINTING AREA IS ")+width+String("x")+height);//-myMenu->bounds->height???
  visualizeModel(TheWorld);//First time visualisation
  
  if(!simulationRun)
    println("PRESS 'r' or 'ESC' to start simulation");
  else
    println("PRESS 's' or 'ESC' to pause simulation");
  NextVideoFrame();//It utilise inside variable to check if is enabled
}

void processing_window::draw()
{
  if(simulationRun)
  {
    modelStep(TheWorld);
  }
  
  if(!simulationRun //When simulation was stopped only visualisation should work
  || StepCounter % STEPSperVIS == 0 ) //But when model is running, visualisation shoud be done from time to time
  {
    doStatistics(TheWorld);
    visualizeModel(TheWorld);
    writeStatusLine();
    
    //WARUNEK STOPU
    if(liveAgentsCount==0) 
            simulationRun=false;//stop when agents are extinct
    
    NextVideoFrame();//It utilise inside variable to check if is enabled
  }

}

void writeStatusLine()
{
  fill(255);rect(0,side*cwidth,width,STATUSHEIGH);
  fill(0);noStroke();
  textAlign(LEFT, TOP);
  text(String("NofAg:")+nf(liveAgentsCount,5)+String(" MnE:")+nf(meanAgentsEn,0,2),0,side*cwidth);
  text(String("NofC:")+nf(liveCellsCount,5)+String(" MnCv:")+meanCells,width/2,side*cwidth);
  textAlign(LEFT, BOTTOM);
  text(StepCounter+String(")  Fps:")+ nf(frameRate,3,0)+String("  Born/st:")+bornsPerStep,0,side*cwidth+STATUSHEIGH-2);
  if(usePanishment)
  {
    textAlign(RIGHT, BOTTOM);
    text(String("NofPan./st: ")+panPerStep+ String(" ..."),width,height);
  }
}

//*/////////////////////////////////////////////////////////////////////////////////////////
//*  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM TragedyOfCommons
//*/////////////////////////////////////////////////////////////////////////////////////////
//../../scripts did it

