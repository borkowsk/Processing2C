/// ABM (Agent Base Modeling) minimum template test for Processing2C
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: AgentSuplement->pde
//*///////////////////////////////////////////////////////////////////////////////////////
/// Agent is a one of two central class of each ABM model
/// Agent need to be initialised & they need logic of change 
//*///////////////////////////////////////////////////////////////////////////////////////

void initializeAgents(smatrix<pAgent> agents) /// Inicjalizacja wszystkich agentów w 2D
{
   for(int a=0;a<agents->length;a++)
    for(int b=0;b<agents[a]->length;b++)
      if(random(1)<density)
      {
        pAgent curr=new Agent();
        //DODATKOWY KOD INICJALIZACJI AGENTÓW, np->curr->initialise();
        liveCount++;
        agents[a][b]=curr;
      }
      
   //Inicjowanie infekcji od środka
   if(agents[agents->length/2][agents->length/2]==nullptr) //Gdyby go nie było
   {
      agents[agents->length/2][agents->length/2]=new Agent();
      liveCount++;
   }
   agents[agents->length/2][agents->length/2]->state=Infected;
}
//OR
void initializeAgents(sarray<pAgent> agents) /// Inicjalizacja wszystkich agentów  w 1D
{
  for(int a=0;a<agents->length;a++)
    if(random(1)<density)
    {
      pAgent curr=new Agent();
      //DODATKOWY KOD INICJALIZACJI AGENTÓW, np->curr->initialise();
      liveCount++;
      agents[a]=curr;
    }
   
   //Inicjowanie infekcji od środka
   if(agents[agents->length/2]==nullptr) //Gdyby go nie było
   {
      agents[agents->length/2]=new Agent();
      liveCount++;
   }
   agents[agents->length/2]->state=Infected;
}

void  agentsChange(sarray<pAgent> agents) /// Główna dynamika symulacji 1D - dummy! NIEZAIPLEMENTOWANA!
{
  int MC=agents->length;
  for(int i=0;i<MC;i++)
  {
    int a=(int)random(0,agents->length);
    if(agents[a]!= nullptr )
    {
      //agents[a]->dummy+=random(-0.1,0.1);//PRZYKŁADOWA ZMIANA 
    }
  }  
}

//OR

void  agentsChange(smatrix<pAgent> agents) /// Główna dynamika symulacji 2D
{
  //Zapamiętujemy stan przed krokiem
  int befInfected=sumInfected;
  int befRecovered=sumRecovered;
  int befDeath=sumDeath;
  
  int MC=agents->length*agents[0]->length;
  for(int i=0;i<MC;i++)
  {
    int a=(int)random(0,agents->length);    //agents[a]->lenght na wypadek gdyby nam przyszło do głowy zrobić prostokąt
    int b=(int)random(0,agents[a]->length); //print(a,b,' '); DEBUG
    if(agents[a][b]!= nullptr )
    {
       //Jesli pusty lub zdrowy to nic nie robimy
       if(agents[a][b]->state<Infected || Recovered<=agents[a][b]->state) continue;
       
       //Wyliczenie lokalizacji sąsiadów
       int dw=(a+1) % agents->length;   
       int up=(agents->length+a-1) % agents->length;
       int right = (b+1) % agents[a]->length;      
       int left  = (agents[a]->length+b-1) % agents[a]->length;

       if(agents[a][left]!=nullptr
       && agents[a][left]->state==Susceptible && random(1) < 1-agents[a][left]->immunity )
         {
	agents[a][left]->state=Infected; sumInfected++;
	}
        
       if(agents[a][right]!=nullptr
       && agents[a][right]->state==Susceptible && random(1) < 1-agents[a][right]->immunity )
         {
	agents[a][right]->state=Infected; sumInfected++;
	}
        
       if(agents[up][b]!=nullptr
       && agents[up][b]->state==Susceptible && random(1) < 1-agents[up][b]->immunity )
         {
	agents[up][b]->state=Infected; sumInfected++;
	}
        
       if(agents[dw][b]!=nullptr
       && agents[dw][b]->state==Susceptible && random(1) < 1-agents[dw][b]->immunity ) 
         {
	agents[dw][b]->state=Infected; sumInfected++;
	}

       float prob=random(1); //Los na dany dzień
       
       if(prob<PDeath) //Albo tego dnia umiera
        { 
          sumDeath++;liveCount--;
          agents[a][b]->state=Death; //Ale to trzeba też uwzglednić przy statystyce!
        }
        else
        {
          //Albo jest wyleczony
          if(++(agents[a][b]->state)==Recovered)
          {
              sumRecovered++;
              //agents[a][b]->immunity=1;//Dla sprawdzenia, ale demoluje ;-) wykres
          }
          //else //NADAL CIERPI!
        }
    }
  }
  //Zapamiętujemy zmianę w podstawowych statystykach 
  //jaka się dokonała w tym kroku symulacji
  deaths->append(sumDeath-befDeath);
  newcas->append(sumInfected-befInfected);
  cured->append(sumRecovered-befRecovered);
}

//*//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: BASIC INITIALISATION & EVERY STEP CHANGE
//*//////////////////////////////////////////////////////////////////////////////////////////////////////////
//../../scripts did it

