/// ABM model of segregation (test project for Processing2C).
/// Agent is a one of two central class of each ABM model
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// @date 2024-10-04 (last change)
//*////////////////////////////////////////////////////
/// ORIGINAL FILE: AgentA->pde

int Number_of_identities=2; ///< Ile jest wykluczających się tożsamości

/// INFO: Agent class.
class Agent: public virtual Object{
  public: 

  float identity; //Tożsamość agenta: [1..Number_of_identities]
  float stress;   //Stress w aktualnej pozycji [0..1]
  
  Agent() //!< Constructor of the Agent
  {
    identity=round(random(1,Number_of_identities)); //Muszą bywać te same
    stress=0;
  }
};

//*/////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: AGENT OF SAKODA MODEL
//*/////////////////////////////////////////////////////////////////////////////////////////
//NOTE! ../../scripts did it 2024-10-04 13:54:21

