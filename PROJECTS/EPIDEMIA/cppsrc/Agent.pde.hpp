//Processing to C++ converter /data/wb/SCC/__working_copies/Processing2C/scripts/procesing2cpp.sh
//Source: Agent.pde
#include "processing_templates.hpp"
//#include "processing_inlines.hpp" //is optional. Use when project is already compilable
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

// Agent is a one of two central class of each ABM model
///////////////////////////////////////////////////////////////
class Agent
{
  int   state;
  float immunity;//Zamiast PTransfer!
  
  Agent()//Konstruktor agenta. Inicjuje atrybuty
  {
    state=Susceptible;
    immunity=( random(1.0)+random(1.0)+random(1.0)
              +random(1.0)+random(1.0)+random(1.0) )/6.0;//Średnia 0.5
             //random(1.0);//Srednia taka sama, ale rozkład płaski
  }
}

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: AGENT FOR FILL UP
///////////////////////////////////////////////////////////////////////////////////////////
///data/wb/SCC/__working_copies/Processing2C/scripts/procesing2cpp.sh did it

