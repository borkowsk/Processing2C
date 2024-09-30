/// @file
/// "TragedyOfCommons" AGENT BASE EVOLUTIONARY MODEL.
///  It utilizes 2D discrete geometry.
///  Implemented by @author Wojciech Borkowski
/// @date 2024-09-30 (last modification)
//*///////////////////////////////////////////////////////////////////////////////////////

/*_using_class Agent */
/*_using_class World */

// Model parameters
int side=200;                 ///< side of main table: 20,50,100,200,400 ...
String modelName="TOC1.0_";   ///< name of the model used for producing file names of outputs.

float treesDensity=0.250;     ///< ??? ...
float treesR=1.015;           ///< from 1..1.1 ...
float agentsDensity=0.005;    ///< Initial density of agents.

boolean usePunishment=true;   ///< Punishment swith off/on.
boolean enableKilling=false;  ///< ??? ...
//boolean symPunishment=true; ///< Punishment genes defines tolerance window for others behavior.
char   punishmentTime=20;     ///< How long punished agent is paralysed.

int   costOfStep=10;          ///< Metabolic cost for agent to live one step more.
float maxStock=costOfStep*50; ///< maximal stock per agent. The storage of unused energy is limited!
float maxInitialEnergyOfAgent=costOfStep*50;    ///<
float pOffspring=0.05;        ///< How often agent WANTs split into 2 agents.

World TheWorld=new World(side); ///< Made here, but also will be completed inside `setup()` .

// Parameters of visualisation etc...
int cwidth=8;                   ///< size of cell.
int STATUSHEIGH=40;             ///< ??? ...
int STEPSperVIS=usePunishment?100:10; ///< Jak nie ma punishment'u to mogą szybko wymrzeć.
int FRAMEFREQ=1000;             ///< ??? ...
boolean WITH_NEW_DEL_LOG=false; ///< ??? ...
/*_OnlyProcessingBlockBegin*/
boolean WITH_VIDEO=false;       ///< ??? ...
/*_OnlyProcessingBlockEnd*/
boolean simulationRun=true;     ///< Start/stop flag.

void setup()
{
  // Graphics
  size(850,840);
  noSmooth(); //Trochę szybciej
  background(0);
  strokeWeight(2);
  frameRate(FRAMEFREQ);
  
  // Model
  initializeModel(TheWorld);
  initializeStats();
  doStatistics(TheWorld);
  
  //Window 
  println("REQUIRED SIZE OF PAINTING AREA IS "+(cwidth*side)+"x"+(cwidth*side+STATUSHEIGH));
  cwidth= (height-STATUSHEIGH) / side;
    
  // Optionals:
  //setupMenu(); //ISSUE: Size of MenuBar is not counted by Processing!
  //...
  
  /*_OnlyProcessingBlockBegin*/
  if(WITH_VIDEO) 
  {
    initVideoExport(this,modelName+".mp4",FRAMEFREQ);
    FirstVideoFrame();
  }
  /*_OnlyProcessingBlockEnd*/
  
  // Finishing setup stage
  println("CURRENT SIZE OF PAINTING AREA IS "+width+"x"+height); // - myMenu.bounds.height???
  visualizeModel(TheWorld); //First time visualisation
  
  if(!simulationRun)
    println("PRESS 'r' or 'ESC' to start simulation");
  else
    println("PRESS 's' or 'ESC' to pause simulation");
    
/*_OnlyProcessingBlockBegin*/   
  NextVideoFrame(); //It utilise inside variable to check if is enabled
/*_OnlyProcessingBlockEnd*/  
}

void draw()
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
    
    // WARUNEK STOPU
    if(liveAgentsCount==0) 
            simulationRun=false; //stop when agents are extinct
/*_OnlyProcessingBlockBegin*/    
    NextVideoFrame(); //It utilise inside variable to check if is enabled
/*_OnlyProcessingBlockEnd*/  
  }

}

void writeStatusLine() ///< Wypełnia treścią obszar statusu aplikacji
{
  fill(255);rect(0,side*cwidth,width,STATUSHEIGH);
  fill(0);noStroke();
  textAlign(LEFT, TOP);
  text("NofAg:"+nf(liveAgentsCount,5)+" MnE:"+nf(meanAgentsEn,0,2),0,side*cwidth);
  text("NofC:"+nf(liveCellsCount,5)+" MnCv:"+meanCells,width/2,side*cwidth);
  textAlign(LEFT, BOTTOM);
  text(StepCounter+")  Fps:"+ nf(frameRate,3,0)+"  Born/st:"+bornsPerStep,0,side*cwidth+STATUSHEIGH-2);
  if(usePunishment)
  {
    textAlign(RIGHT, BOTTOM);
    text("NofPan./st: "+punPerStep+" ...",width,height);
  }
}

//*/////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - ABM TragedyOfCommons
//*/////////////////////////////////////////////////////////////////////////////////////////
