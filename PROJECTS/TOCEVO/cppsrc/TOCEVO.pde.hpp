/// @file
/// "TragedyOfCommons" AGENT BASE EVOLUTIONARY MODEL.
///  It utilizes 2D discrete geometry.
///  Implemented by @author Wojciech Borkowski
/// @date 2024-10-15 (last modification)
//*///////////////////////////////////////////////////////////////////////////////////////

/*_import_class:Agent */
/*_import_class:World */

// Model parameters
int side=200;                 ///< side of main table: 20,50,100,200,400 ...
String modelName="TOC1.0_";   ///< name of the model used for producing file names of outputs.

float treesDensity=0.250;     ///< ??? ...
float treesR=1.015;           ///< from 1..1.1 ...
float agentsDensity=0.005;    ///< Initial density of agents.

bool    usePunishment=true;   ///< Punishment switch off/on.
bool    enableKilling=false;  ///< ??? ...
//bool    symPunishment=true; ///< Punishment genes defines tolerance window for others behavior.
char16_t   punishmentTime=20;     ///< How long punished agent is paralysed.

int   costOfStep=10;          ///< Metabolic cost for agent to live one step more.
float maxStock=costOfStep*50; ///< maximal stock per agent->The storage of unused energy is limited!
float maxInitialEnergyOfAgent=costOfStep*50;    ///<
float pOffspring=0.05;        ///< How often agent WANTs split into 2 agents.

pWorld TheWorld=new World(side); ///< Made here, but also will be completed inside `setup()` .

// Parameters of visualisation etc...
int cwidth=8;                   ///< size of cell.
int STATUSHEIGH=40;             ///< ??? ...
int STEPSperVIS=usePunishment?100:10; ///< Jak nie ma punishment'u to mogą szybko wymrzeć.
int FRAMEFREQ=1000;             ///< ??? ...
bool    WITH_NEW_DEL_LOG=false; ///< ??? ...
/*_OnlyProcessingBlockBegin
bool    WITH_VIDEO=false;       ///< ??? ...
_OnlyProcessingBlockEnd*/
bool    simulationRun=true;     ///< Start/stop flag.

void processing_window::setup()
{
  // Graphics
  size(850,840);
  noSmooth(); //Trochę szybciej
  background(0);
  strokeWeight(2);
  setFrameRate(FRAMEFREQ);
  
  // Model
  initializeModel(TheWorld);
  initializeStats();
  doStatistics(TheWorld);
  
  //Window 
  println(String("REQUIRED SIZE OF PAINTING AREA IS ")+(cwidth*side)+String("x")+(cwidth*side+STATUSHEIGH));
  cwidth= (height-STATUSHEIGH) / side;
    
  // Optionals:
  //setupMenu(); //ISSUE: Size of MenuBar is not counted by Processing!
  //...
  
  /*_OnlyProcessingBlockBegin
  if(WITH_VIDEO) 
  {
    initVideoExport(SAFE_THIS,modelName+ String(".mp4"),FRAMEFREQ);
    FirstVideoFrame();
  }
  _OnlyProcessingBlockEnd*/
  
  // Finishing setup stage
  println(String("CURRENT SIZE OF PAINTING AREA IS ")+width+String("x")+height); // - myMenu->bounds->height???
  visualizeModel(TheWorld); //First time visualisation
  
  if(!simulationRun)
    println("PRESS 'r' or 'ESC' to start simulation");
  else
    println("PRESS 's' or 'ESC' to pause simulation");
    
/*_OnlyProcessingBlockBegin   
  NextVideoFrame(); //It utilise inside variable to check if is enabled
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
    
    // WARUNEK STOPU
    if(liveAgentsCount==0) 
            simulationRun=false; //stop when agents are extinct
/*_OnlyProcessingBlockBegin    
    NextVideoFrame(); //It utilise inside variable to check if is enabled
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
    text(String("NofPan./st: ")+punPerStep+ String(" ..."),width,height);
  }
}

//*/////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM TragedyOfCommons
//*/////////////////////////////////////////////////////////////////////////////////////////
//MADE NOTE: ../../scripts did it 2024-10-15 16:10:56 !

