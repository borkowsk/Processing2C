/// ABM (Agent Base Modeling) minimum template test for Processing2C
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: AgentDefinition->pde
//*//////////////////////////////////////////////////////////////////
/// Agent is a one of two central class of each ABM model
//*/////////////////////////////////////////////////////////////

class Agent: public virtual Object{
  public:
  int   state;
  float immunity; //Zamiast PTransfer!
  
  Agent() //Konstruktor agenta->Inicjuje atrybuty
  {
    state=Susceptible;
    immunity=( random(1.0)+random(1.0)+random(1.0)
              +random(1.0)+random(1.0)+random(1.0) ) / 6.0; //Średnia 0.5
             //random(1.0); //Srednia taka sama, ale rozkład płaski
  }
};

//*/////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: AGENT FOR FILL UP
//*/////////////////////////////////////////////////////////////////////////////////////////
//NOTE! ../../scripts did it 2023-10-11 14:12:40

