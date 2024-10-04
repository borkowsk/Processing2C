// @date 2024-10-04 (last modification)
//  Agent is a one of two central class of each ABM model
//*/////////////////////////////////////////////////////////////

/*_using_class Agent */

/// Agents need to be initialised & they need logic of change.
void initializeAgents(smatrix<pAgent> agents) ///< initialisation of all agents.
{
   for(int a=0;a<agents->length;a++)
    for(int b=0;b<agents[a]->length;b++)
    if(random(1)<agentsDensity)
    {
      pAgent curr=new Agent();
      agents[a][b]=curr;
    }
}

void cleanDeaths(smatrix<pAgent> agents)      ///< Cleaning world from death agents.
{
   for(int a=0;a<agents->length;a++)
    for(int b=0;b<agents[a]->length;b++)
    if(agents[a][b]!= nullptr) 
      if(agents[a][b]->energy<=0)
      {
        agents[a][b]=nullptr; //remove death agent from the world 
      }
}

//*  EVERY STEP CHANGE == MAIN DYNAMICS
//*//////////////////////////////////////

void  changeAgents(smatrix<pAgent> agents,smatrix<int> cells)  ///< Changing states of agents.
{
  int MC=agents->length*agents[0]->length;
  
  for(int i=0;i<MC;i++)
  {
    int a=(int)random(0,agents->length);
    int b=(int)random(0,agents[a]->length);
    
    if(agents[a][b]!= nullptr && agents[a][b]->energy>0 ) //Exists and not death
    {
      // Zużycie zasobów na koszty metaboliczne
      if(agents[a][b]->energy>costOfStep) 
          agents[a][b]->energy-=costOfStep; //Metabolic costs
      else
          agents[a][b]->energy=0; //Not enough!
          
      if(agents[a][b]->energy<=0) //Czy nie umarł od tego?
      {
          if(WITH_NEW_DEL_LOG) 
            println("Agent death",(int)agents[a][b]->genEat,(int)agents[a][b]->genPan);
          
          continue; //Now is death
      }
      
      if(agents[a][b]->punished>0) //Czy jest sparaliżowany?
      {
        agents[a][b]->punished--;
        continue; //Nic nie może zrobić poza zużywaniem zasobów
      }
      
      //CELL OF INTEREST
      int ma=(a+(int)random(-1.99,1.99)+agents->length)%agents->length;
      int mb=(b+(int)random(-1.99,1.99)+agents[a]->length)%agents[a]->length;
      
      //Is there something to eat?
      if(cells[ma][mb]!=0)
      {
        float rpOfEat=agents[a][b]->genEat/255.0;
        int consumption=(int)(cells[ma][mb]*rpOfEat);
        
        if(consumption<1 && random(1.0) < rpOfEat) //When too small resources
            consumption=1;
            
        if(consumption>0)
        {
          cells[ma][mb]-=consumption;
          agents[a][b]->energy+=consumption;
          // To jednak powinno być tu!
          if(agents[a][b]->energy>maxStock)
            agents[a][b]->energy=maxStock; //the storage of unused energy is limited
        }
      }
      
      // Jeżeli przypadkiem wylosowano własną komórkę, to dalsze akcje nie mają sensu
      if(a==ma && b==mb) continue;
      
      //Maybe offspring?
      if(agents[ma][mb]==nullptr     //Tylko gdy wolne miejsce
      && agents[a][b]->energy > 4 * costOfStep //Jest minimalny zapas
      && pOffspring > random(1.0) ) //I jest DECYZJA!
      {
          agents[ma][mb]=new Agent(agents[a][b]->energy/2,
                                  (agents[a][b]->genEat+(int)random(-1.5,1.5)), //With mutation possible
                                  (agents[a][b]->genPan+(int)random(-1.5,1.5))  //With mutation possible
                                  );
          if(WITH_NEW_DEL_LOG)
              println("New agent",(int)agents[ma][mb]->genEat,(int)agents[ma][mb]->genPan);                        
          agents[a][b]->energy/=2;
          numOfBorns++;
          continue;
      }
      
      // Maybe punishment
      if( agents[a][b]->genPan>0 //Czy ma skłonności do karania?
      && agents[ma][mb]!=nullptr                        //Czy to ktoś do ukarania?
      && agents[ma][mb]->punished==0                  //Czy nie jest już ukarany?
      && agents[ma][mb]->genEat > agents[a][b]->genEat //Czy jest za co go ukarać
      && (enableKilling || agents[ma][mb]->energy > (punishmentTime+1) * costOfStep)     //Czy chce go tak całkiem zabić!
      && (agents[a][b]->genPan/255.0) > random(1.0) ) //Czynnik losowy
      {
          if(WITH_NEW_DEL_LOG)
            println("Punishment at",ma,mb);
          numOfPunishments++;  
          agents[ma][mb]->punished=punishmentTime;
          continue;
      }
      
      //NON-BLOCKING RANDOM WALK
      pAgent tmp=agents[a][b];
      agents[a][b]=agents[ma][mb];
      agents[ma][mb]=tmp; //Agent ready at new position
    }
  }
  
  //println("numOfPanishments:",numOfPanishments);
}


//*//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: BASIC INITIALISATION & EVERY STEP CHANGE
//*//////////////////////////////////////////////////////////////////////////////////////////////////////////
//NOTE! ../../scripts did it 2024-10-04 13:54:22

