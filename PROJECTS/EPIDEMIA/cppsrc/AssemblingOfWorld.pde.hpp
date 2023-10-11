/// ABM (Agent Base Modeling) minimum template test for Processing2C
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: AssemblingOfWorld->pde
//*///////////////////////////////////////////////////////////////////////////////////////
/// World is a one of two central class of each ABM model
//*/////////////////////////////////////////////////////////////
int StepCounter=0; //GLOBALNY LICZNIK KROKÓW SYMULACJI

class World: public virtual Object{
  public:
  //sarray<pAgent> agents; //JEDNOWYMIAROWA TABLICA AGENTÓW
  //OR
  smatrix<pAgent> agents; //DWUWYMIAROWA TABLICA AGENTÓW
  
  World(int side) //KONSTRUKTOR ŚWIATA
  {
    //agents=new array<pAgent>(side);
    //OR
    agents=new matrix<pAgent>(side,2*side);
  }
};

// BARDZIEJ ZŁOŻONE FUNKCJONALNOŚCI ZOSTAŁY ZDEFINIOWANE JAKO OSOBNE FUNKCJE
// A NIE METODY KLASY World ZE WZGLĘDU NA OGRANICZENIA SKŁADNI PROCESSINGU
// NIE POZWALAJĄCEJ SCHOWAĆ GDZIEŚ INDZIEJ MNIEJ ISTOTNYCH METOD KLASY
//*/////////////////////////////////////////////////////////////////////////

void initializeModel(pWorld world) ///< Zwyczajowa nazwa funkcji
{
  initializeAgents(world->agents); //TU NASTĄPI WYBÓR FUNKCJI PRZECIĄŻONEJ!
}

void visualizeModel(pWorld world) ///< Zwyczajowa nazwa funkcji
{
  visualizeAgents(world->agents); //TU NASTĄPI WYBÓR FUNKCJI PRZECIĄŻONEJ!
}

//void dummyChange(pWorld world) //FUKCJE MOŻNA USUNĄĆ GDY POJAWI SIĘ
//{                             //REALNY KOD MODELU
//  dummyChangeAgents(world->agents);//TU NASTĄPI WYBÓR FUNKCJI PRZECIĄŻONEJ!
//}

void modelStep(pWorld world) ///< Zwyczajowa nazwa funkcji
{
   //dummyChange(world); //TYMCZASOWE WYWOŁANIE TRYWIALNEJ DYNAMIKI
   //OR
   //REALNY KOD MODELU
   agentsChange(world->agents); //TU NASTĄPI WYBÓR FUNKCJI PRZECIĄŻONEJ!
   
   StepCounter++;
}

//*/////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: WORLD OF AGENTS FOR FILL UP
//*/////////////////////////////////////////////////////////////////////////////////////////////
//NOTE! ../../scripts did it 2023-10-11 14:12:40

