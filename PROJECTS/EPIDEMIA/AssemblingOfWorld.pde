/// ABM (Agent Base Modeling) minimum template test for Processing2C
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// @date 2024-09-30 (last change)
/// ORIGINAL FILE: AssemblingOfWorld.pde
//*///////////////////////////////////////////////////////////////////////////////////////
/// World is a one of two central class of each ABM model
//*/////////////////////////////////////////////////////////////
int StepCounter=0; //GLOBALNY LICZNIK KROKÓW SYMULACJI

class World {
  //Agent[] agents; //JEDNOWYMIAROWA TABLICA AGENTÓW
  //OR
  Agent[][] agents; //DWUWYMIAROWA TABLICA AGENTÓW
  
  World(int side) //KONSTRUKTOR ŚWIATA
  {
    //agents=new Agent[side];
    //OR
    agents=new Agent[side][2*side];
  }
};

// BARDZIEJ ZŁOŻONE FUNKCJONALNOŚCI ZOSTAŁY ZDEFINIOWANE JAKO OSOBNE FUNKCJE
// A NIE METODY KLASY World ZE WZGLĘDU NA OGRANICZENIA SKŁADNI PROCESSINGU
// NIE POZWALAJĄCEJ SCHOWAĆ GDZIEŚ INDZIEJ MNIEJ ISTOTNYCH METOD KLASY
//*/////////////////////////////////////////////////////////////////////////

void initializeModel(World world) ///< Zwyczajowa nazwa funkcji
{
  initializeAgents(world.agents); //TU NASTĄPI WYBÓR FUNKCJI PRZECIĄŻONEJ!
}

void visualizeModel(World world) ///< Zwyczajowa nazwa funkcji
{
  visualizeAgents(world.agents); //TU NASTĄPI WYBÓR FUNKCJI PRZECIĄŻONEJ!
}

//void dummyChange(World world) //FUKCJE MOŻNA USUNĄĆ GDY POJAWI SIĘ
//{                             //REALNY KOD MODELU
//  dummyChangeAgents(world.agents);//TU NASTĄPI WYBÓR FUNKCJI PRZECIĄŻONEJ!
//}

void modelStep(World world) ///< Zwyczajowa nazwa funkcji
{
   //dummyChange(world); //TYMCZASOWE WYWOŁANIE TRYWIALNEJ DYNAMIKI
   //OR
   //REALNY KOD MODELU
   agentsChange(world.agents); //TU NASTĄPI WYBÓR FUNKCJI PRZECIĄŻONEJ!
   
   StepCounter++;
}

//*/////////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - ABM: WORLD OF AGENTS FOR FILL UP
//*/////////////////////////////////////////////////////////////////////////////////////////////
