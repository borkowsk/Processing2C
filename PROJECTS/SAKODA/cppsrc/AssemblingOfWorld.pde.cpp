//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: AssemblingOfWorld.pde
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

/// ABM model of segregation (test project for Processing2C)
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: AssemblingOfWorld->pde
/////////////////////////////////////////////////////////////////////////////////////////
// World is a one of two central class of each ABM model
/////////////////////////////////////////////////////////////////////////////////////////
int StepCounter=0;

class World: public virtual Object{
  public:
  //sarray<pAgent> agents;//One dimensional array of agents
  //OR
  smatrix<pAgent> agents;//Two dimensional array of agents
  
  World(int side)//Constructor of the World
  {
    //agents=new array<pAgent>(side);
    //OR
    agents=new matrix<pAgent>(side,side);
  }
};

//More alaborated functionalities are defined as stand-alone functions,
//not as methods because of not enought flexible syntax of Processing
///////////////////////////////////////////////////////////////////////////

void initializeModel(pWorld world) { ///
  initializeAgents(world->agents);
}

void visualizeModel(pWorld world) { ///
  visualizeAgents(world->agents);
}

void changeState(pWorld world) { ///
  changeAgents(world->agents);
}

void modelStep(pWorld world) { ///
   changeState(world);   
   StepCounter++;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: WORLD OF SAKODA
///////////////////////////////////////////////////////////////////////////////////////////////
//../../scripts did it

