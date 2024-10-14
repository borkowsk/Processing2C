/// ABM model of segregation (test project for Processing2C). 
/// ORIGINAL FILE: AgentA->pde
/// Agent is a one of two central class of each ABM model.
/// @date 2024-10-14 (last change)
//*///////////////////////////////////////////////////////////

int Number_of_identities=2; ///< How many mutually exclusive identities are there?

/// @brief Agent with identity and stress.
class Agent: public virtual Object{
  public: 

  float identity; //!< pAgent Identity: [1..Number_of_identities]
  float stress;   //!< Stress felt in current position [0..1]
  
  Agent() //!< Constructor of the Agent
  {
    identity=round(random(1,Number_of_identities));
    stress=0;
  }
};

//*/////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: AGENT OF SAKODA MODEL
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
//*/////////////////////////////////////////////////////////////////////////////////////////
//MADE NOTE: /data/wb/SCC/public/Processing2C/scripts did it 2024-10-14 17:34:05 !

