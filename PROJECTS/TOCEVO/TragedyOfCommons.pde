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

boolean usePanishment=true;///Panishment swith off/on
boolean enableKilling=false;
//boolean symPanishment=true;///Panishment genes defines tolerance window for others behavior
char   panishmentTime=20;///How long panished agent is paralised

int   costOfStep=10; /// Metabolic cost for agent to live one step more.
float maxStock=costOfStep*50;///maximal stock per agent. The storage of unused energy is limited!
float maxInitialEnergyOfAgent=costOfStep*50;
float pOffspring=0.05;///How offten agent WANTs split into 2 agents

World TheWorld=new World(side);//... but also will be initialised inside setup()

//Parameters of visualisation etc...
int cwidth=8;//size of cell
int STATUSHEIGH=40;
int STEPSperVIS=usePanishment?100:10;//Jak nie ma panishmentu to mogą szybko wymrzeć
int FRAMEFREQ=1000;
boolean WITH_NEW_DEL_LOG=false;///
boolean WITH_VIDEO=false;///
boolean simulationRun=true;//Start/stop flag

void setup()
{
  //Graphics
  size(850,840);
  noSmooth();//Trochę szybciej
  background(0);
  strokeWeight(2);
  frameRate(FRAMEFREQ);
  
  //Model
  initializeModel(TheWorld);
  initializeStats();
  doStatistics(TheWorld);
  
  //Window 
  println("REQUIRED SIZE OF PAINTING AREA IS "+(cwidth*side)+"x"+(cwidth*side+STATUSHEIGH));
  cwidth=(height-STATUSHEIGH)/side;
    
  //Optionals:
  //setupMenu();//ISSUE: Size of MenuBar is not counted by Processing!
  //...
  if(WITH_VIDEO) 
  {
    initVideoExport(this,modelName+".mp4",FRAMEFREQ);
    FirstVideoFrame();
  }
  
  //Finishing setup stage
  println("CURRENT SIZE OF PAINTING AREA IS "+width+"x"+height);//-myMenu.bounds.height???
  visualizeModel(TheWorld);//First time visualisation
  
  if(!simulationRun)
    println("PRESS 'r' or 'ESC' to start simulation");
  else
    println("PRESS 's' or 'ESC' to pause simulation");
  NextVideoFrame();//It utilise inside variable to check if is enabled
}

void draw()
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
  text("NofAg:"+nf(liveAgentsCount,5)+" MnE:"+nf(meanAgentsEn,0,2),0,side*cwidth);
  text("NofC:"+nf(liveCellsCount,5)+" MnCv:"+meanCells,width/2,side*cwidth);
  textAlign(LEFT, BOTTOM);
  text(StepCounter+")  Fps:"+ nf(frameRate,3,0)+"  Born/st:"+bornsPerStep,0,side*cwidth+STATUSHEIGH-2);
  if(usePanishment)
  {
    textAlign(RIGHT, BOTTOM);
    text("NofPan./st: "+panPerStep+" ...",width,height);
  }
}

//*/////////////////////////////////////////////////////////////////////////////////////////
//*  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - ABM TragedyOfCommons
//*/////////////////////////////////////////////////////////////////////////////////////////
