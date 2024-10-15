/// @file
/// @note Automatically made from _AssemblingOfWorld.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
/// @date 2024-10-15 16:11:05 (translation)
//
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
#ifndef _NO_INLINE
#include "processing_inlines.hpp" //...is optional.
#endif // _NO_INLINE
#include "processing_string.hpp"  //Processing::String class
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_files.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

/// @date 2024-10-10 (last modification)
/// World is a one of two central class of each ABM model.
//*///////////////////////////////////////////////////////

#include "Agent_class.pde.hpp"

/// @details 
///         We have two layer - environment resources cells and agents. 
///         
#include "World_class.pde.hpp"

// More elaborated functionalities are defined as stand-alone functions,
// not as methods because of not enough flexible syntax of Processing
//*/////////////////////////////////////////////////////////////////////////

int StepCounter=0; ///< Global step counter.

void initializeModel(pWorld world)   ///< Need to be global!
{
  initializeCells(world->cells);
  initializeAgents(world->agents);
}

void visualizeModel(pWorld world)    ///< Need to be global!
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
    float len=log(eatCounters[i]) / maxL*50.0; //println(len);
    stroke(i,0,128);
    line(side*cwidth,i,side*cwidth+len,i);
  }
  
  for(int i=0;i<punCounters->length;i++)
  if(punCounters[i]>0)
  {
    float len=log(punCounters[i]) / maxL*50.0; //println(len);
    stroke(128,0,128+i);
    line(side*cwidth,eatCounters->length+i,side*cwidth+len,eatCounters->length+i);
  }
  
}

void changes(pWorld world)   ///< Need to be global!
{
  cleanDeaths(world->agents);
  synchChangeCells(world->cells,world->cells); //No intercells interactions
  changeAgents(world->agents,world->cells); //Agents influence the resource layer
}

void modelStep(pWorld world) ///< Need to be global!
{
   changes(world);
   
   StepCounter++;
}

//*/////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: WORLD FOR TragedyOfCommons
//*/////////////////////////////////////////////////////////////////////////////////////////////
//MADE NOTE: ../../scripts did it 2024-10-15 16:11:05 !

