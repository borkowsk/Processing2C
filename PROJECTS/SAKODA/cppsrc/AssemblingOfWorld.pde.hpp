/// ABM model of segregation (test project for Processing2C)
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: AssemblingOfWorld->pde
//*///////////////////////////////////////////////////////////////////////////////////////
/// World is a one of two central class of each ABM model
//*///////////////////////////////////////////////////////////////////////////////////////
int StepCounter=0;

class World: public virtual Object{
  public:
  //sarray<pAgent> agents; //One dimensional array of agents
  //OR
  smatrix<pAgent> agents; //Two dimensional array of agents
  
  World(int side) //Constructor of the World
  {
    //agents=new array<pAgent>(side);
    //OR
    agents=new matrix<pAgent>(side,side);
  }
};

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
//*/////////////////////////////////////////////////////////////////////////////////////////////
//NOTE! ../../scripts did it 2023-10-11 14:12:42

