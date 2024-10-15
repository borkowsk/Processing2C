/// @file
/// @note Automatically made from _AssemblingOfWorld.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
/// @date 2024-10-15 16:11:04 (translation)
//
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
#ifndef _NO_INLINE
#include "processing_inlines.hpp" //...is optional.
#endif // _NO_INLINE
#include "processing_string.hpp"  //Processing::String class
#include "processing_files.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

/// ABM model of segregation (test project for Processing2C)
/// ORIGINAL FILE: AssemblingOfWorld->pde
/// @date 2024-10-14 (last change)
//*///////////////////////////////////////////////////////////////////////////////////////

#include "Agent_class.pde.hpp"

int StepCounter=0;  ///< Global step counter.

/// @brief World is a one of two central class of each ABM model.
#include "World_class.pde.hpp"

// More alaborated functionalities are defined as stand-alone functions,
// not as methods because of not enought flexible syntax of Processing
//*/////////////////////////////////////////////////////////////////////////

void initializeModel(pWorld world) { ///< Need to be global!
  initializeAgents(world->agents);
}

void visualizeModel(pWorld world) { ///< Need to be global!
  visualizeAgents(world->agents);
}

void changeState(pWorld world) { ///< Need to be global!
  changeAgents(world->agents);
}

void modelStep(pWorld world) { ///< Need to be global!
   changeState(world);   
   StepCounter++;
}

//*/////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: WORLD OF SAKODA
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
//*/////////////////////////////////////////////////////////////////////////////////////////////
//MADE NOTE: ../../scripts did it 2024-10-15 16:11:04 !

