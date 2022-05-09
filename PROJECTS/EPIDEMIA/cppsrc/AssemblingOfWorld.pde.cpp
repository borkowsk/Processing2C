//Processing to C++ converter /data/wb/SCC/public/Processing2C/scripts/procesing2cpp.sh
//Source: AssemblingOfWorld.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

/// ABM (Agent Base Modeling) minimum template test for Processing2C
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: AssemblingOfWorld->pde
/////////////////////////////////////////////////////////////////////////////////////////
// World is a one of two central class of each ABM model
///////////////////////////////////////////////////////////////
int StepCounter=0GLOBALNY LICZNIK KROKÓW SYMULACJI

class World: public virtual Object{
  public:
  //sarray<pAgent> agents;//JEDNOWYMIAROWA TABLICA AGENTÓW
  //OR
  smatrix<pAgent> agentsDWUWYMIAROWA TABLICA AGENTÓW
  
  World(int sideKONSTRUKTOR ŚWIATA
  {
    //agents=new array<pAgent>(side);
    //OR
    agents=new matrix<pAgent>(side,2*side);
  }
};

//BARDZIEJ ZŁOŻONE FUNKCJONALNOŚCI ZOSTAŁY ZDEFINIOWANE JAKO OSOBNE FUNKCJE
//A NIE METODY KLASY World ZE WZGLĘDU NA OGRANICZENIA SKŁADNI PROCESSINGU
//NIE POZWALAJĄCEJ SCHOWAĆ GDZIEŚ INDZIEJ MNIEJ ISTOTNYCH METOD KLASY
///////////////////////////////////////////////////////////////////////////

void initializeModel(pWorld world) /// Zwyczajowa nazwa funkcji
{
  initializeAgents(world->agentsTU NASTĄPI WYBÓR FUNKCJI PRZECIĄŻONEJ!
}

void visualizeModel(pWorld world) /// Zwyczajowa nazwa funkcji
{
  visualizeAgents(world->agentsTU NASTĄPI WYBÓR FUNKCJI PRZECIĄŻONEJ!
}

//void dummyChange(pWorld world) //FUKCJE MOŻNA USUNĄĆ GDY POJAWI SIĘ
//{                             //REALNY KOD MODELU
//  dummyChangeAgents(world->agents);//TU NASTĄPI WYBÓR FUNKCJI PRZECIĄŻONEJ!
//}

void modelStep(pWorld world) /// Zwyczajowa nazwa funkcji
{
   //dummyChange(world);//TYMCZASOWE WYWOŁANIE TRYWIALNEJ DYNAMIKI
   //OR
   //REALNY KOD MODELU
   agentsChange(world->agentsTU NASTĄPI WYBÓR FUNKCJI PRZECIĄŻONEJ!
   
   StepCounter++;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: WORLD OF AGENTS FOR FILL UP
///////////////////////////////////////////////////////////////////////////////////////////////
///data/wb/SCC/public/Processing2C/scripts did it

