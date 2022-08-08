/// ABM model of segregation (test project for Processing2C)
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: AssemblingOfWorld.pde
//*///////////////////////////////////////////////////////////////////////////////////////
/// World is a one of two central class of each ABM model
//*///////////////////////////////////////////////////////////////////////////////////////
int StepCounter=0;

class World {
  //Agent[] agents; //One dimensional array of agents
  //OR
  Agent[][] agents; //Two dimensional array of agents
  
  World(int side) //Constructor of the World
  {
    //agents=new Agent[side];
    //OR
    agents=new Agent[side][side];
  }
};

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
//*/////////////////////////////////////////////////////////////////////////////////////////////
