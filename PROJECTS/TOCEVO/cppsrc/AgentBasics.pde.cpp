//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: AgentBasics.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
//#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_alist.hpp" //...is optional. Should be deleted when not needed.
#include "processing_lists.hpp" //...is optional. Should be deleted when not needed.
#include "processing_map.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_files.hpp" //...is optional. Should be deleted when not needed.
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

//*  Agent is a one of two central class of each ABM model
//*  Agent need to be initialised & they need logic of change 
//*/////////////////////////////////////////////////////////////

void initializeAgents(smatrix<pAgent> agents)
{
   for(int a=0;a<agents->length;a++)
    for(int b=0;b<agents[a]->length;b++)
    if(random(1)<agentsDensity)
    {
      pAgent curr=new Agent();
      agents[a][b]=curr;
    }
}

void cleanDeaths(smatrix<pAgent> agents)
{
   for(int a=0;a<agents->length;a++)
    for(int b=0;b<agents[a]->length;b++)
    if(agents[a][b]!= nullptr) 
      if(agents[a][b]->energy<=0)
      {
        agents[a][b]=nullptr;//remove death agent from the world 
      }
}

//*  EVERY STEP CHANGE == MAIN DYNAMICS
//*//////////////////////////////////////

void  changeAgents(smatrix<pAgent> agents,smatrix<int> cells)
{
  int MC=agents->length*agents[0]->length;
  
  for(int i=0;i<MC;i++)
  {
    int a=(int)random(0,agents->length);
    int b=(int)random(0,agents[a]->length);
    
    if(agents[a][b]!= nullptr && agents[a][b]->energy>0 )//Exists and not death
    {
      //Zurzycie zasobów na koszty metaboliczne
      if(agents[a][b]->energy>costOfStep) 
          agents[a][b]->energy-=costOfStep; //Metabolic costs
      else
          agents[a][b]->energy=0;//Not enough!
          
      if(agents[a][b]->energy<=0) //Czy nie umarł od tego?
      {
          if(WITH_NEW_DEL_LOG) 
            println("Agent death",(int)agents[a][b]->genEat,(int)agents[a][b]->genPan);
          continue;//Now is death
      }
      
      if(agents[a][b]->panished>0)//Czy jest sparaliżowany?
      {
        agents[a][b]->panished--;
        continue;//Nic nie może zrobić poza zużywaniem zasobów
      }
      
      //CELL OF INTEREST
      int ma=(a+(int)random(-1.99,1.99)+agents->length)%agents->length;
      int mb=(b+(int)random(-1.99,1.99)+agents[a]->length)%agents[a]->length;
      
      //Is there something to eat?
      if(cells[ma][mb]!=0)
      {
        float rpOfEat=agents[a][b]->genEat/255.0;
        int consumption=(int)(cells[ma][mb]*rpOfEat);
        
        if(consumption<1 && random(1.0) < rpOfEat)//When too small resources
            consumption=1;
            
        if(consumption>0)
        {
          cells[ma][mb]-=consumption;
          agents[a][b]->energy+=consumption;
          //To jednak powinno być tu! TODO DONE
          if(agents[a][b]->energy>maxStock)
            agents[a][b]->energy=maxStock;//the storage of unused energy is limited
        }
      }
      
      //Jeżeli przypadkiem wylosowano własną komórkę, to dalsze akcje nie mają sensu
      if(a==ma && b==mb) continue;
      
      //Maybe offspring?
      if(agents[ma][mb]==nullptr     //Tylko gdy wolne miejsce
      && agents[a][b]->energy > 4 * costOfStep //Jest minimalny zapas
      && pOffspring > random(1.0) )//I jest DECYZJA!
      {
          agents[ma][mb]=new Agent(agents[a][b]->energy/2,
                                  (agents[a][b]->genEat+(int)random(-1.5,1.5)),//With mutation possible
                                  (agents[a][b]->genPan+(int)random(-1.5,1.5)) //With mutation possible
                                  );
          if(WITH_NEW_DEL_LOG)
              println("New agent",(int)agents[ma][mb]->genEat,(int)agents[ma][mb]->genPan);                        
          agents[a][b]->energy/=2;
          numOfBorns++;
          continue;
      }
      
      //Maybe panishment
      if( agents[a][b]->genPan>0 //Czy ma skłonnośc do karania?
      && agents[ma][mb]!=nullptr                        //Czy to ktoś do ukarania?
      && agents[ma][mb]->panished==0                  //Czy nie jest już ukarany?
      && agents[ma][mb]->genEat > agents[a][b]->genEat //Czy jest za co go ukarać
      && (enableKilling || agents[ma][mb]->energy > (panishmentTime+1) * costOfStep)     //Czy chce go tak całkiem zabić!
      && (agents[a][b]->genPan/255.0) > random(1.0) ) //Czynnik losowy
      {
          if(WITH_NEW_DEL_LOG)
            println("Panishment at",ma,mb);
          numOfPanishments++;  
          agents[ma][mb]->panished=panishmentTime;
          continue;
      }
      
      //NON-BLOCKING RANDOM WALK
      pAgent tmp=agents[a][b];
      agents[a][b]=agents[ma][mb];
      agents[ma][mb]=tmp;//Agent ready at new position
    }
  }
  
  //println("numOfPanishments:",numOfPanishments);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: BASIC INITIALISATION & EVERY STEP CHANGE
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//../../scripts did it

