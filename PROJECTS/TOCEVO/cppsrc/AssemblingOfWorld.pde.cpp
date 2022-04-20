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

//*   World is a one of two central class of each ABM model
//*/////////////////////////////////////////////////////////////
int StepCounter=0; ///< globalny licznik kroków

class World: public virtual Object{
  public:
  int smatrix<pcells>;//Two dimensional array of resources
  Agent smatrix<pagents>;//Two dimensional array of agents
  
  World(int side)//Constructor of the World
  {
    cells=new matrix<int>(side,side);
    agents=new matrix<pAgent>(side,side);
  }
};

// More elaborated functionalities are defined as stand-alone functions,
// not as methods because of not enough flexible syntax of Processing
//*/////////////////////////////////////////////////////////////////////////

void initializeModel(pWorld world)   ///<
{
  initializeCells(world->cells);
  initializeAgents(world->agents);
}

void visualizeModel(pWorld world)    ///<
{
  noStroke();
  visualizeCells(world->cells);
  visualizeAgents(world->agents);
  float maxL=log(side*side);
  
  fill(128);noStroke();rect(side*cwidth,0,50,eatCounters->length);
  fill(200);noStroke();rect(side*cwidth,eatCounters->length,50,punCounters->length);
  strokeWeight(1);
  
  for(int i=0;i<eatCounters->length;i++)
  if(eatCounters[i]>0)
  {
    float len=log(eatCounters[i])/maxL*50.0; //println(len);
    stroke(i,0,128);
    line(side*cwidth,i,side*cwidth+len,i);
  }
  
  for(int i=0;i<punCounters->length;i++)
  if(punCounters[i]>0)
  {
    float len=log(punCounters[i])/maxL*50.0; //println(len);
    stroke(128,0,128+i);
    line(side*cwidth,eatCounters->length+i,side*cwidth+len,eatCounters->length+i);
  }
  
}

void changes(pWorld world)   ///<
{
  cleanDeaths(world->agents);
  synchChangeCells(world->cells,world->cells);//No intercells interactions
  changeAgents(world->agents,world->cells);//Agents influence the resource layer
}

void modelStep(pWorld world) ///<
{
   changes(world);
   
   StepCounter++;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: WORLD FOR TragedyOfCommons
///////////////////////////////////////////////////////////////////////////////////////////////
//../../scripts did it

