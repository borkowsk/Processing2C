/// ABM model of segregation (test project for Processing2C)
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "SAKODA.pde"
//*///////////////////////////////////////////////////////////////////////////////////////
/// Sakoda inspired AGENT BASE MODEL utilized 1D or 2D dicrete geometry
/// implemented by Wojciech Borkowski
//*///////////////////////////////////////////////////////////////////////////////////////

// Model parameters
String modelName="ABMSakoda"; ///< Name of the model
int side=100; ///< side of main table
float density=0.55; ///<initial density of agents

pWorld TheWorld=new World(side); ///<  will be initialised inside setup function

// Parameters of visualisation etc...
int cwidth=8; ///< size of cell
int STATUSHEIGH=40; ///<???
int STEPSperVIS=1;  ///<???
int FRAMEFREQ=20;   ///<???

bool WITH_VIDEO=false;   ///< Is video stream enabled?
bool simulationRun=true; ///<Start/stop flag

void processing_window::setup()
{
  // Graphics
  size(800,840);
  setFrameRate(FRAMEFREQ);
  background(255,255,200);
  strokeWeight(2);
  
  // Model
  initializeModel(TheWorld);
  initializeStats(); //Wykomentowanie blokuje tworzenie pliku log
  doStatistics(TheWorld);
  
  // Window 
  println(String("REQUIRED SIZE OF PAINTING AREA IS ")+(cwidth*side)+String("x")+(cwidth*side+STATUSHEIGH));
  cwidth=(height-STATUSHEIGH) / side;
    
  if(WITH_VIDEO) 
  {
    //initVideoExport(SAFE_THIS,modelName+ String(".mp4"),FRAMEFREQ);
    //FirstVideoFrame();
  }
  
  //Finishing setup stage
  println(String("CURRENT SIZE OF PAINTING AREA IS ")+width+String("x")+height); //-myMenu->bounds->height???
  visualizeModel(TheWorld); //First time visualisation
  if(!simulationRun)
    println("PRESS 'r' or 'ESC' to start simulation");
  else
    println("PRESS 's' or 'ESC' to pause simulation");
  
  //NextVideoFrame(); //It utilise inside variable to check if is enabled
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
    //NextVideoFrame(); //It utilise inside variable to check if is enabled
  }

}

void writeStatusLine() ///< Used also for stats
{
  fill(255);rect(0,side*cwidth,width,STATUSHEIGH);
  fill(0);noStroke();
  textAlign(LEFT, TOP);
  text(meanStress+String("  ")+liveCount,0,side*cwidth);
  textAlign(LEFT, BOTTOM);
  text(StepCounter+String(")  Fps:")+ frameRate,0,side*cwidth+STATUSHEIGH-2);
}

//*/////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM SAKODA MAIN 
//*/////////////////////////////////////////////////////////////////////////////////////////
//../../scripts did it

