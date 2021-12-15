//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: AgentDef.pde
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
/// ORIGINAL FILE: AgentDefinition->pde
/////////////////////////////////////////////////////////////////////////////////////////
// Agent is a one of two central class of each ABM model
///////////////////////////////////////////////////////////////
class Agent: public virtual Object{
  public:
  int   state;
  float immunity;//Zamiast PTransfer!
  
  Agent()//Konstruktor agenta. Inicjuje atrybuty
  {
    state=Susceptible;
    immunity=( random(1.0)+random(1.0)+random(1.0)
              +random(1.0)+random(1.0)+random(1.0) )/6.0;//Średnia 0.5
             //random(1.0);//Srednia taka sama, ale rozkład płaski
  }
};

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: AGENT FOR FILL UP
///////////////////////////////////////////////////////////////////////////////////////////
//../../scripts did it

