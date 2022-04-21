//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: EPIDEMIA.pde
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

/// ABM (Agent Base Modeling) minimum template test for Processing2C
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "EPIDEMIA.pde"
/////////////////////////////////////////////////////////////////////////////////////////
// Model of epidemic using template for AGENT BASE MODEL in 1D & 2D discrete geometry
// implemented by Wojciech Borkowski
/////////////////////////////////////////////////////////////////////////////////////////

//PARAMETRY MODELU
int side=200;/// DŁUGOŚĆ BOKU ŚWIATA
String modelName="ABMEpidemia";/// Nazwa modelu, np. dla plików wyjściowych
float density=0.66;/// główny MERYTORYCZNY parametr modelu

pWorld TheWorld=new World(side);//INICJALIZACJA JEST KONCZONA 
                               //W FUNKCJI setup( )

//Inne parametry symulacji jako const - coś w rodzaju stałych ;-)
const int Duration=7;/// Czas trwania infekcji!
//const int Empty=0;//NIEPOTRZEBNE. Zamiast tego jest nullptr w komórce tablicy uchwytów do agetów 
const int Susceptible=1;/// Oznaczenie podatnego
const int Infected=2;/// Oznaczenie zainfekowanego
const int Recovered=Infected+Duration;/// Oznaczenie wyleczonego
const int Death=100;/// Oznaczenie zmarłego
//const float PTransfer=???;  //Prawdopodobieństwo zarażenia agenta w pojedynczej interakcji
                              //teraz zależy od indywidualnej wartości immunity!
                              
const float PDeath=0.015;     /// Średnie prawdopodobieństwo śmierci w danym dniu choroby

//STATYSTYKI LICZONE W TRAKCIE SYMULACJI
int liveCount=0;/// Ile aktualnie żywych

int  sumInfected=0;///Zachorowanie
int sumRecovered=0;///Wyzdrowienia
int     sumDeath=0;///Ci co umarli

//HISTORIE DO WYŚWIETLANIA
pFloatList deaths=new FloatList();///Historia śmierci 
pFloatList newcas=new FloatList();///Historia nowych zachorowań
pFloatList  cured=new FloatList();///Historia wyleczeń

//PARAMETRY WIZUALIZACJI, STATYSTYKI ITP.
int cwidth=3;///DŁUGOŚĆ BOKU KOMÓRKI W WIZUALIZACJI
             //WARTOSC NADANA TU JEST TYLKO WSTĘPNA
int STATUSHEIGH=150;///WYSOKOŚĆ PASKA STATUSU NA DOLE OKNA

int STEPSperVIS=1;///JAK CZĘSTO URUCHAMIAMY WIZUALIZACJĘ
int FRAMEFREQ=30; ///ILE RAZY NA SEKUNDĘ URUCHAMIA SIĘ draw( )

//bool WITH_VIDEO=false;//CZY CHCEMY ZAPIS DO PLIKU FILMOWEGO (wymagany modu… RTMVideo->pde)
bool simulationRun=true;//FLAGA Start/stop DZIAŁANIA SYMULACJI

int fontHeight=16;

void processing_window::setup()
{
  //GRAFIKA
  textSize(fontHeight); //Same size as default for Processing2C, where textSize function does not work.
  size(1200,750);//NIESTETY TU MOGĄ BYĆ TYLKO WARTOŚCI PODANE LITERALNIE CZYLI "LITERAŁY"!!!
  noSmooth();   //Znacząco przyśpiesza wizualizacje
  setFrameRate(FRAMEFREQ);
  background(255,255,200);
  strokeWeight(2);
  //randomSeed(-1013);//Zasianie generatora gdy chcemy mieć powtarzalny przebieg np. 107 albo 1013
  
  //INICJALIZACJA MODELU I (ewentualnie) STATYSTYK
  initializeModel(TheWorld);//DOKONCZENIE INICJALIZACJI ŚWIATA
  //initializeStats();      //ODKOMENTOWAĆ JEŚLI UŻYWAMY STATYSTYK
  //doStatistics(TheWorld); //J->W.
  
  //OBLICZAMY WYMAGANY ROZMIAR OKNA DLA funkcji size 
  println(modelName+ String(": REQUIRED SIZE OF PAINTING AREA IS ")
          +(cwidth*side)+String("x")+(cwidth*side+STATUSHEIGH));
  cwidth=(height-STATUSHEIGH)/side;//DOPASOWUJEMY ROZMIAR KOMÓREK DO OKNA JAKIE JEST
  
  //INICJALIZACJA ZAPISU FILMU  (jeśli używamy RTMVideo->pde)
  //if(WITH_VIDEO) 
  //{ 
  //  initVideoExport(SAFE_THIS,modelName+ String(".mp4"),FRAMEFREQ);
  //  FirstVideoFrame();
  //}
  
  //INFORMACJE KONSOLOWE NA KONIEC FUNKCJI setup( )
  println(String("CURRENT SIZE OF PAINTING AREA IS ")+width+String("x")+height);//-myMenu->bounds->height???
  visualizeModel(TheWorld);//PIERWSZA PO INICJALIZACJI WIZUALIZACJA ŚWIATA
  
  //if(!simulationRun) //WYMAGA MODUŁU RTMEvents->pde
  //  println("PRESS 'r' or 'ESC' to start simulation");
  //else
  //  println("PRESS 's' or 'ESC' to pause simulation");
  
  //NextVideoFrame();//PIERWSZA REALNA KLATKA FILMU (o ile używamy RTMVideo->pde)
}

void processing_window::draw()
{
  if(simulationRun)
  {
    modelStep(TheWorld);
    //doStatistics(TheWorld);//ODKOMENTOWAĆ JEŚLI UŻYWAMY STATYSTYK
  }                          //Używa wewnętrznej flagi określajacej czy log został otwarty
  
  writeStatusLine();
  
  if(!simulationRun //When simulation was stopped only visualisation should work
  || StepCounter % STEPSperVIS == 0 ) //But when model is running, visualisation should be done from time to time
  {
    visualizeModel(TheWorld);
    //NextVideoFrame();//FUNKCJA ZAPISU KLATKI FILMU. 
  }                    //Używa wewnętrznej flagi określajacej czy film został otwarty

}

void writeStatusLine() ///Ta nazwa musi być znana globalnie
{
  fill(64);rect(0,side*cwidth,width,STATUSHEIGH);fill(128);
  histogram(TheWorld->agents,0,height-fontHeight-fontHeight/2,STATUSHEIGH-fontHeight-fontHeight/2);//Histogram wg. odporności  
   
  //Legenda i historie trzech zmiennych dziennych każda w swojej skali
  stroke(0,0,255);fill(0,0,200);text("newly infected",300,height-fontHeight);
  //timeline(newcas,200,height,STATUSHEIGH-fontHeight,false);
  stroke(255,0,0);fill(200,0,0);text("newly died",300,height-fontHeight*2);
  //timeline(deaths,200,height,STATUSHEIGH-fontHeight,false);
  stroke(0,255,0);fill(0,200,0);text("newly healed",300,height-fontHeight*3);
  //timeline(cured, 200,height,STATUSHEIGH-fontHeight,false);
  
  //Historie trzech zmiennych we wspólnej skali
  fill(0,128,255);//Tylko kolor napisów tu możemy ustalić
  timeline(newcas,deaths,cured, 200,height,STATUSHEIGH-fontHeight,false,
           color(0,0,255),color(255,0,0),color(0,255,0));
  
  fill(128);noStroke();
  textAlign(CENTER, TOP);
  text(String("Still Alive:")+liveCount+String(" Sum of infected:")+sumInfected+String(" sum of healed:")+sumRecovered+String(" sum of dead:")+sumDeath+ String("     "),width/2,side*cwidth);//Miejce dla NAJWAŻNIEJSZYCH STATYSTYK
  println(String("ST:")+StepCounter+String("\tZ\t")+sumInfected+String("\t")+newcas->get(newcas->size()-1)
                           +String("\tW\t")+sumRecovered+String("\t")+cured->get(cured->size()-1)
                           +String("\tU\t")+sumDeath+String("\t")+deaths->get(deaths->size()-1)
                           + String("\t"));
  textAlign(LEFT, BOTTOM);
  text(StepCounter+String(")  Fps:")+ frameRate,0,side*cwidth+STATUSHEIGH);
}

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM MAIN TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////
//../../scripts did it

