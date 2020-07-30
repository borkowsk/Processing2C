//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: RTSI2020s.pde
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
//include "processing_inlines.hpp" //is optional. Use when project is already compilable
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

//   RTSI model utilized cell geometry
//   implemented by Wojciech Borkowski, Andrzej Nowak, ...
/////////////////////////////////////////////////////////////////////////////////////////

String  modelName="RTSI_Model_S3.1b";  /// MODEL NAME IS USED IN STATISTICS AND VISUALISATION
int     FRAMEFREQ=300;  /// Desired simulation speed per second

// Model parameters ( MODEL IMPORTANT PART! )
//========================================================================================
int   SIDE=6;  /// side of the 1 & 2D tables - not more than 20 when full_network  is used!!!
float NETWORK_DENSITY=1;   /// Not for all network types - in simple_model select between full & random network
//int   MOORE=1;/// Moore distance of basic lattice - currenty not used in simple_model

int   NOISE_DETAILS=4; /// For 2D noiseDetail()
float NOISE_OFFS=0.5;  /// For 2D noiseDetail()
float NOISE_SCALE=0.25;/// For init noise properties. Until now was 0.233 - TODO disconnect properties area from SIDE!!!
float NOISE_DRIFT=0;   /// If different than 0 enable random walk on noise space instead of random change every MACRO_STEP

float AGENTS_DENSITY=0.95;/// Desired density of agents may not be realised strictly 
float MAX_ERROR_OF_SENSOR=0.2;/// For sensor initialisation. Warning! Flat distribution 0..MAX for particular sensors
float BIAS_MEAN=0.01;  /// Desired mean value of bias
float BIAS_DISP=0.02;  /// Desired dispersion, so each BIAS is inside range [mean-dispersion,mean+dispersion]

//Wybieranie mieszanki zachowań!!!
bool TRACE_ACTIONS=false;  /// If you want to see each particular action

float   REAL_INFO_PROBABILITY=0.01;    /// "R" - How offten agent has reality check - JAK 0 TO NIGDY NIE SPRAWDZA FAKTYCZNEGO STANU
int     REALITY=3;   /// Skąd bierzemy "realność"? 0-bierze REALNOSC spod nog, 1-średni pomiar, 2-średnią opinie, 3-średnią realność
bool REMEMBER_REALITY_FACTS=false;  /// Is reality fact remembered for opinion or not (ESPECIALLY NOT IN PREDICTION CHECK MODEL!)

float   OWN_MEASURE_PROBABILITY=0.0;   /// "S" - How offten agent use own sensor
bool SELF_LINKED=(OWN_MEASURE_PROBABILITY==0);  /// Alternatywnie używamy linku do własnego sensora jak do obcego
float   INTERACTION_PROBABILITY=1.0-OWN_MEASURE_PROBABILITY-REAL_INFO_PROBABILITY;/// "o" - other agent activities (ask for fact only in simple_model)

//Parametry startu i zmiany zaufania czyli wagi połączeń
float MIN_RELIABILITY=0.001;   /// Minimal reliability for sensor and links. Maybe 0.5? TODO CHECK! 
float MAX_INI_RELIABILITY=0.90;/// Maximal initial weight and sensor reliability
float SQR_ERROR_TRESHOLD=0.01; /// Squared errors above treshold lead to lowering trust, below otherwise 

float UP_Q_LINK_TRUST=0.20; /// How much trust (weight of link) may go up in one interaction
float DOWN_LINK_TRUST=0.30; /// How much trust (weight of link) may go down in one interaction
float UP_Q_SELF_TRUST=0.20; /// How much reliability of sensor may go up in one measuiring SELF_TRUST
float DOWN_SELF_TRUST=0.30; /// How much reliability of sensor may go down in one measuiring

//SOCIAL STEP
int   MACRO_STEP_MULT=3;  /// Multiplicating of social step lenght
int   MACRO_STEP=(int)((SIDE*SIDE)*INTERACTION_PROBABILITY*NETWORK_DENSITY)*MACRO_STEP_MULT;  /// 1/OWN_MEASURE_PROBABILITY may leads to DIV/0 error, 
                                                                                              /// which is may not be detected!!!

// ENVIROMENT PROPERTIES. ONLY ONE PROPERTY FOR SIMPLE MODEL
//==============================================================
int   MINIMAL_PROPERTY_INDEX=0;  /// ONLY ONE PROPERTY FOR SIMPLE MODEL
int   MAXIMAL_PROPERTY_INDEX=0;  /// ONLY ONE PROPERTY FOR SIMPLE MODEL
//int   MORALITY_MARKER=MINIMAL_PROPERTY_INDEX;  /// THE SAME NETWORK!!!
//int   MORALITY_MARKER=MINIMAL_PROPERTY_INDEX-1; ///
int   NUM_OF_PROPERTIES=MAXIMAL_PROPERTY_INDEX+1;  /// How many important properties of the simulation world?
int   NUM_OF_ISSUES=NUM_OF_PROPERTIES;  /// ONLY ONE PROPERTY FOR SIMPLE MODEL

//Parameters of visualisation etc...
//=======================================
//bool SCREEN_FULL=true;//To nie działa bo "size() and fullScreen() cannot be used in the same sketch"
int     WhichProperty=0;  ///Which property of the world is about to visualise?

int     STEPSperVIS=10;  ///Visualisation &  every 10 steps
int     STEPSperSTAT=1;  ///Statistics &  every 10 steps

bool VIS_NETWORK=false;   ///
float   linkWeightTresh=0.95;///Links filtering for visualisation
float   MAX_LINK_WEIGHT=2;   ///Maximal strokeWidth for links TODO - link stroke from 1-3, when 1 is for linkWeightTresh
float   LINK_INTENSITY=32;   ///For link transparency
bool VIS_AGENTS=false;    ///
float   AGENT_STROKE=2;      ///Stroke width for Agents
bool WITH_STROKE=true;    ///

bool WITH_MIN_MAX=false;  /// Wizualizacja minimalnej i maksymalnej opini
bool WITH_ERRORS=true;    /// Czy jest wykres średniego błędu?
bool ZERO_ONE_SCALE=false;///Dodanie zera i jedynki do wspólnych maksimów i minimów
bool visualiseReliabilities=true;  ///
int     FROM_END=(MACRO_STEP*10)/STEPSperSTAT;  ///How many MACRO_STEPS are visible on timelines?
bool WITH_VIDEO=false;    /// visible autside this file!

int     FONT_HEIGHT=10;       /// for fontSize 
int     STATUSHEIGH=100;      /// Bottom side STATUS area HEIGHT
float   WORLD_VIS_SIDE=0.5;   /// Side of a world visualisation area
float   HISTOGRAM_WIDTH=0.497;/// as part of a window width
float   HISTOGRAM_HEIGHT=0.55;/// as part of STATUSHEIGH
float   TIMELINES_WIDTH=0.4985;///as part of window width
float   TIMELINES_HIGTH=0.950;/// as part of window (height-STATUSHEIGH)

int     cwidth=15;///size of cell
bool simulationRun=true;///Start/stop flag

// MAIN OBJECT
//========================================================
pWorld theWorld=nullptr;//Created & initialised inside setup()

void processing_window::setup()
{
  //Graphics size(N,N/2+STATUSHEIGH);
  pixelDensity(1);//1 or 2, expecially for "Retina" HERE?
  fullScreen();
  //else
  //size(800,600);//(480,340);<--minimal window size
  pixelDensity(1);//1 or 2, expecially for "Retina" or HERE?
  println("WINDOW:","Width=",width,"Height=",height,"displayDensity=",displayDensity());
  
  frameRate(FRAMEFREQ);
  noSmooth();
  background(255,255,200);
  strokeWeight(1);
  textSize(FONT_HEIGHT);
  
  //Window size calculation
  println(String("\nREQUIRED MINIMAL SIZE OF PAINTING AREA IS ")+(cwidth*SIDE)*2+String("x")+(cwidth*SIDE+STATUSHEIGH));
  WORLD_VIS_SIDE=min(height-STATUSHEIGH,width/2);
  cwidth=int(WORLD_VIS_SIDE/SIDE);
  HISTOGRAM_WIDTH*=width;
  HISTOGRAM_HEIGHT*=STATUSHEIGH;
  TIMELINES_WIDTH*=width; //println("TIMELINES_WIDTH:",TIMELINES_WIDTH);
  TIMELINES_HIGTH*=WORLD_VIS_SIDE;
  
  //Set randomizers for known seeds,
  //but for development only!q
  //noiseSeed(10);
  //randomSeed(10);
                                                                          assert(MACRO_STEP>1);	// String("MACRO_STEP==")+MACRO_STEP;
                                                                          assert(FROM_END>1);	// String("FROM_END==")+FROM_END;
  //Model creation and initialisation
  theWorld=new World(SIDE);//Created here, but also need to be initialised
  theWorld->initializeModel();
  
  //initializeStats();//There would be no log file, if this line is commented out
  doStatistics(theWorld);
  
  if(WITH_VIDEO) 
  {
    //initVideoExport(this,modelName+".mp4",FRAMEFREQ);
    //FirstVideoFrame();
  }
  
  //Finishing setup stage
  //println(String("\nCURRENT SIZE OF PAINTING AREA IS ")+width+String("x")+height);//-myMenu->bounds.height???
  XSPREAD=0.30/NUM_OF_PROPERTIES;
  theWorld->visualizeModel();//First time visualisation
  println("\nMacro step is",MACRO_STEP);
  if(!simulationRun)
    println("PRESS 'r' or 'ESC' to start simulation");
  else
    println("PRESS 's' or 'ESC' to pause simulation");
  //NextVideoFrame();//It utilise inside variable to check if is enabled
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate.net/profile/WOJCIECH_BORKOWSKI - SETUP SOURCE FROM TEMPLATE, BUT CHANGED!!!
///////////////////////////////////////////////////////////////////////////////////////////////////////

//ABSTRACT RULES FOR MODEL A
//float RULE_DETAILER=0.75;//(0.50..1] - smaller numbers generate more rules - not used in simple_model
//float SMALL_RULE_LIMIT=0.01;//When remain knowledge is less than that, rules generation will stop - not used in simple_model

//COSTS FOR MODEL A - not used in simple_model
//int   VIRT_CPU_TICKS=10; //Number od virtual "CPU" tics per agent per MC step.
//int   OP_QUESTION_COST=1;//Question for opinion cost
//int   FA_QUESTION_COST=2;//Question for fact cost
//int   RU_QUESTION_COST=5;//Question for rule cost
//int   CHECK_COHER_COST=VIRT_CPU_TICKS/2;//Cost for checking coherence in facts
//int   MEASURMENT_COST=VIRT_CPU_TICKS;

// SKOPIOWANE Z INNEGO PLIKU DLA ZMNIEJSZENIA LICZBY ZAKŁADEK W IDE:
//
// Do łatwego i CZYTELNEGO w wyrażeniach podnoszenia do kwadratu
//////////////////////////////////////////////////////////////////////
int sqr(int a)
{
  return a*a;
}

float sqr(float a)
{
  return a*a;
}

double sqr(double a)
{
  return a*a;
}

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate.net/profile/WOJCIECH_BORKOWSKI - HANDY FUNCTIONS & CLASSES
///////////////////////////////////////////////////////////////////////////////////////////
//../../scripts/procesing2cpp.sh did it

