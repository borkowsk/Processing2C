//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: AgentA.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

/// ABM model of segregation (test project for Processing2C)
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: AgentA->pde
/////////////////////////////////////////////////////////////////////////////////////////
// Agent is a one of two central class of each ABM model
//////////////////////////////////////////////////////////////////
int Number_of_identities=2;/// Ile jest wykluczających się tożsamości

class Agent: public virtual Object{
  public: 
  ///INFO: Agent class
  float identity;//Tożsamość agenta: [1..Number_of_identities]
  float stress;//Stress w aktualnej pozycji [0..1]
  
  Agent()//Constructor of the Agent
  {
    identity=round(random(1,Number_of_identities));//Muszą bywać te same
    stress=0;
  }
};

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: AGENT OF SAKODA MODEL
///////////////////////////////////////////////////////////////////////////////////////////
//../../scripts did it

