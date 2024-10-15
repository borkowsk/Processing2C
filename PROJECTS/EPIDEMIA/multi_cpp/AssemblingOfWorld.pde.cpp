/// @file
/// @note Automatically made from _AssemblingOfWorld.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
/// @date 2024-10-15 16:11:03 (translation)
//
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
#ifndef _NO_INLINE
#include "processing_inlines.hpp" //...is optional.
#endif // _NO_INLINE
#include "processing_string.hpp"  //Processing::String class
#include "processing_lists.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

/// ABM (Agent Base Modeling) minimum template test for Processing2C
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// @date 2024-09-30 (last change)
/// ORIGINAL FILE: AssemblingOfWorld->pde
//*///////////////////////////////////////////////////////////////////////////////////////
/// World is a one of two central class of each ABM model
//*/////////////////////////////////////////////////////////////
int StepCounter=0; //GLOBALNY LICZNIK KROKÓW SYMULACJI

#include "World_class.pde.hpp"

// BARDZIEJ ZŁOŻONE FUNKCJONALNOŚCI ZOSTAŁY ZDEFINIOWANE JAKO OSOBNE FUNKCJE
// A NIE METODY KLASY World ZE WZGLĘDU NA OGRANICZENIA SKŁADNI PROCESSINGU
// NIE POZWALAJĄCEJ SCHOWAĆ GDZIEŚ INDZIEJ MNIEJ ISTOTNYCH METOD KLASY
//*/////////////////////////////////////////////////////////////////////////

void initializeModel(pWorld world) ///< Zwyczajowa nazwa funkcji
{
  initializeAgents(world->agents); //TU NASTĄPI WYBÓR FUNKCJI PRZECIĄŻONEJ!
}

void visualizeModel(pWorld world) ///< Zwyczajowa nazwa funkcji
{
  visualizeAgents(world->agents); //TU NASTĄPI WYBÓR FUNKCJI PRZECIĄŻONEJ!
}

//void dummyChange(pWorld world) //FUKCJE MOŻNA USUNĄĆ GDY POJAWI SIĘ
//{                             //REALNY KOD MODELU
//  dummyChangeAgents(world->agents);//TU NASTĄPI WYBÓR FUNKCJI PRZECIĄŻONEJ!
//}

void modelStep(pWorld world) ///< Zwyczajowa nazwa funkcji
{
   //dummyChange(world); //TYMCZASOWE WYWOŁANIE TRYWIALNEJ DYNAMIKI
   //OR
   //REALNY KOD MODELU
   agentsChange(world->agents); //TU NASTĄPI WYBÓR FUNKCJI PRZECIĄŻONEJ!
   
   StepCounter++;
}

//*/////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: WORLD OF AGENTS FOR FILL UP
//*/////////////////////////////////////////////////////////////////////////////////////////////
//MADE NOTE: ../../scripts did it 2024-10-15 16:11:03 !

