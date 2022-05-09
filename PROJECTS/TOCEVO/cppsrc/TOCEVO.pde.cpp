//Processing to C++ converter /data/wb/SCC/public/Processing2C/scripts/procesing2cpp.sh
//Source: TOCEVO.pde
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

//*   "TragedyOfCommons" AGENT BASE EVOLUTIONARY MODEL 
//*   utilized 2D discrete geometry
//*   implemented by Wojciech Borkowski
//*///////////////////////////////////////////////////////////////////////////////////////

//Model parameters
int side=200;                 ///< side of main table: 20,50,100,200,400
String modelName="TOC1.0_";   ///< name of the model used for producing file names of outputs

float treesDensity=0.250;     ///<
float treesR=1.015;           ///< from 1..1.1 !
float agentsDensity=0.005;    ///< Initial density of agents

bool usePunishment=true;   ///< Punishment swith off/on
bool enableKilling=false;  ///<
//bool symPunishment=true; ///< Punishment genes defines tolerance window for others behavior
char16_t   punishmentTime=20;     ///< How long punished agent is paralysed

int   costOfStep=10;          ///< Metabolic cost for agent to live one step more.
float maxStock=costOfStep*50; ///< maximal stock per agent. The storage of unused energy is limited!
float maxInitialEnergyOfAgent=costOfStep*50;    ///<
float pOffspring=0.05;        ///< How often agent WANTs split into 2 agents

pWorld TheWorld=new World(side Made here, but also will be completed inside setup()

//Parameters of visualisation etc...
int cwidth=8;                   ///<size of cell
int STATUSHEIGH=40;             ///<
int STEPSperVIS=usePunishment?100:10 Jak nie ma punishment'u to mogą szybko wymrzeć
int FRAMEFREQ=1000;             ///<
bool WITH_NEW_DEL_LOG=false; ///<
/*_OnlyProcessingBlockBegin

bool WITH_VIDEO=false;       ///<
_OnlyProcessingBlockEnd*/

bool simulationRun=true;     ///< Start/stop flag

void processing_window::setup()
{
  //Graphics
  size(850,840);
  noSmoothTrochę szybciej
  background(0);
  strokeWeight(2);
  setFrameRate(FRAMEFREQ);
  
  //Model
  initializeModel(TheWorld);
  initializeStats();
  doStatistics(TheWorld);
  
  //Window 
  println(String("REQUIRED SIZE OF PAINTING AREA IS ")+(cwidth*side)+String("x")+(cwidth*side+STATUSHEIGH));
  cwidth=(height-STATUSHEIGHside;
    
  //Optionals:
  //setupMenu();//ISSUE: Size of MenuBar is not counted by Processing!
  //...
  
  /*_OnlyProcessingBlockBegin

  if(WITH_VIDEO) 
  {
    initVideoExport(SAFE_THIS,modelName+ String(".mp4"),FRAMEFREQ);
    FirstVideoFrame();
  }
  _OnlyProcessingBlockEnd*/

  
  //Finishing setup stage
  println(String("CURRENT SIZE OF PAINTING AREA IS ")+width+String("x")+heightmyMenu->bounds->height???
  visualizeModel(TheWorldFirst time visualisation
  
  if(!simulationRun)
    println("PRESS 'r' or 'ESC' to start simulation");
  else
    println("PRESS 's' or 'ESC' to pause simulation");
    
/*_OnlyProcessingBlockBegin
   
  NextVideoFrameIt utilise inside variable to check if is enabled
_OnlyProcessingBlockEnd*/
  
}

void processing_window::draw()
{
  if(simulationRun)
  {
    modelStep(TheWorld);
  }
  
  if(!simulationRun //When simulation was stopped only visualisation should work
  || StepCounter % STEPSperVIS == 0 ) //But when model is running, visualisation should be done from time to time
  {
    doStatistics(TheWorld);
    visualizeModel(TheWorld);
    writeStatusLine();
    
    //WARUNEK STOPU
    if(liveAgentsCount==0) 
            simulationRun=falsestop when agents are extinct
/*_OnlyProcessingBlockBegin
    
    NextVideoFrameIt utilise inside variable to check if is enabled
_OnlyProcessingBlockEnd*/
  
  }

}

void writeStatusLine() ///< Wypełnia treścią obszar statusu aplikacji
{
  fill(255);rect(0,side*cwidth,width,STATUSHEIGH);
  fill(0);noStroke();
  textAlign(LEFT, TOP);
  text(String("NofAg:")+nf(liveAgentsCount,5)+String(" MnE:")+nf(meanAgentsEn,0,2),0,side*cwidth);
  text(String("NofC:")+nf(liveCellsCount,5)+String(" MnCv:")+meanCells,width/2,side*cwidth);
  textAlign(LEFT, BOTTOM);
  text(StepCounter+String(")  Fps:")+ nf(frameRate,3,0)+String("  Born/st:")+bornsPerStep,0,side*cwidth+STATUSHEIGH-2);
  if(usePunishment)
  {
    textAlign(RIGHT, BOTTOM);
    text(String("NofPanst: ")+punPerStep+ String(" ..."),width,height);
  }
}

//*/////////////////////////////////////////////////////////////////////////////////////////
//*  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM TragedyOfCommons
//*/////////////////////////////////////////////////////////////////////////////////////////
///data/wb/SCC/public/Processing2C/scripts did it

