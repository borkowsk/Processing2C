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
//////////////////////////////////////////////////////////////////
int Number_of_identities=2;//Ile jest wykluczających się tożsamości

class Agent
{
  float identity;//Tożsamość agenta: [1..Number_of_identities]
  float stress;//Stress w aktualnej pozycji [0..1]
  
  Agent()//Constructor of the Agent
  {
    identity=round(random(1,Number_of_identities));//Muszą bywać te same
    stress=0;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: AGENT OF SAKODA MODEL
///////////////////////////////////////////////////////////////////////////////////////////
///data/wb/SCC/__working_copies/Processing2C/scripts/procesing2cpp.sh did it

