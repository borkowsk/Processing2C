// Agent is a one of two central class of each ABM model
///////////////////////////////////////////////////////////////
class Agent
{
  int   state;
  float immunity;//Zamiast PTransfer!
  
  Agent()//Konstruktor agenta. Inicjuje atrybuty
  {
    state=Susceptible;
    immunity=( random(1.0)+random(1.0)+random(1.0)
              +random(1.0)+random(1.0)+random(1.0) )/6.0;//Średnia 0.5
             //random(1.0);//Srednia taka sama, ale rozkład płaski
  }
}

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - ABM: AGENT FOR FILL UP
///////////////////////////////////////////////////////////////////////////////////////////
