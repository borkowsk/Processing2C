/// ABM model of segregation (test project for Processing2C)
/// ORIGINAL FILE: AssemblingOfWorld.pde
/// @date 2024-10-14 (last change)
//*///////////////////////////////////////////////////////////////////////////////////////

/*_import_class:Agent */

int StepCounter=0;  ///< Global step counter.

/// @brief World is a one of two central class of each ABM model.
/*_import_class:World */

// More alaborated functionalities are defined as stand-alone functions,
// not as methods because of not enought flexible syntax of Processing
//*/////////////////////////////////////////////////////////////////////////

void initializeModel(World world) { ///< Need to be global!
  initializeAgents(world.agents);
}

void visualizeModel(World world) { ///< Need to be global!
  visualizeAgents(world.agents);
}

void changeState(World world) { ///< Need to be global!
  changeAgents(world.agents);
}

void modelStep(World world) { ///< Need to be global!
   changeState(world);   
   StepCounter++;
}

//*/////////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - ABM: WORLD OF SAKODA
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
//*/////////////////////////////////////////////////////////////////////////////////////////////
