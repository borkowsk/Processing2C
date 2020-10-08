//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: ModelSteps.pde
#include "processing_templates.hpp"
//#include "processing_inlines.hpp" //is optional. Use when project is already compilable
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

//More alaborated functionalities are defined as stand-alone functions,
//not as methods, because of not enought flexible syntax of Processing
///////////////////////////////////////////////////////////////////////////
#include "processing_lists.hpp" //Sort array of Comparable<T>

void stepForAgent(pAgent agent,pWorld world)                                      //,int agentsCPUtics - not in simple_model
{
  if(agent->issues[0]->useableLinks==nullptr)                                        //Lazy initialisation   
  {
    agent->issues[0]->useableLinks=agent->getConns(allLinks);                      //In this version only possible type of link array is sarray<pRTSILink>
  }
                                                                                //print("!");//DEBUG
  float select=random(1.0);//Which acction?
  
  if(select<REAL_INFO_PROBABILITY)                                              //ACTION: Reality check!
  {                                                                             //assert( agent->sensors[0]->propertyIndex==0);	//
     float reliab=1.0;//It is reality! So 100% sure!                            if(TRACE_ACTIONS) print("R");//DEBUG 
     
     float currmes=0; //<>//
     int   REALITY=2; //Skąd bierzemy "realność"? 0-bierze pomiar spod nóg, 1-średni pomiar, 2-średnią opinie, 3-średnią realność
                      //Realność zawsze z poprzedniego kroku czyli weryfikacja post-factum
     if(REALITY==0)                                                             // MODEL IMPORTANT PART!
           currmes=agent->getReality(0,world);
     else if(REALITY==1)
           currmes=meanSensor;                   
           else if(REALITY==2)
                currmes=meanOpinion;
                else if(REALITY==3)
                     currmes=meanSRealt;
                     else
                     {
	 println("REALITY type UNKNOWN! Only 0,1,2,3 can be understand!"); exit(); 
	}
                
     checkCoherenceWithReality(currmes,agent->issues[0]->facts,agent);            // MODEL IMPORTANT PART!
     
     if(REMEMBER_REALITY_FACTS)                                                 //Remember this fact or not?
     {
       pInfo newFact=new Info(currmes,reliab,world->StepCounter,nullptr);            //"nullptr" because this info as arived from outside social network!
       agent->issues[0]->facts->add(newFact);
     }
  }
  else
  if(select<OWN_MEASURE_PROBABILITY+REAL_INFO_PROBABILITY)                      //ACTION: Use own sensor!
  {
     pSensor sens=agent->sensors[0];                                              assert( agent->sensors[0]->propertyIndex==0);	//<>//
                                                                                if(TRACE_ACTIONS) print("S");//DEBUG
     float reliab=sens->reliability->weight;                                      assert( reliab<=1);	//
     
     if(MIN_RELIABILITY<reliab)                                                 //Agent may not trust its own sensor
     {                                                                          assert(reliab<=1);	//Mamy zatem pomiar któremu choć trochę ufamy
       float currmes=agent->getSensor(0,world);                                  assert(0<=currmes && currmes<=1 );	//  String("agent.getSensor()==")+currmes;
       pInfo newFact=new Info(currmes,reliab,world->StepCounter,sens->reliability);
       
       //some changes in reliability of own sensor                              
       reliab=checkFactReliability(newFact,agent->issues[0]->facts,agent);        //(pInfo fact,sArrayList<Info> infos,pNode selfsource) - MODEL IMPORTANT PART!
       
       agent->issues[0]->facts->add(newFact);                                      //ZAPAMIĘTANIE NOWEGO FAKTU NA LIŚCIE DO WYDAWANIA OPINII
                                                                                //println(world->StepCounter,"\t",agent,currmes,reliab,"MEASURED FACT");//DEBUG
     }
  }
  else
  //if(select<ASK_FACT_PROBABILITY)                                             //ELSE ACTION: Ask other for facts!
  {
    //Sort of useableLinks by current weights                                   //PRZESORTOWANIE JEST POTRZEBNE TYLKO PRZY TAKIEJ AKCJI!                  
    Arrays->sort(agent->issues[0]->useableLinks);                                  //Zerowy powinien mieć maksymalną wagę - MODEL IMPORTANT PART! 
                                                                                //print(" ",agent->issues[0]->useableLinks[0]->weight);//DEBUG
                                                                                if(TRACE_ACTIONS) print("o");//DEBUG 
    int  index=(int)(random(1)*random(1)*random(1)*                             //Bardziej lub mniej...  - MODEL IMPORTANT PART! 
               random(1)*random(1)*random(1)*                                   //skośna dystrybucja     - MODEL IMPORTANT PART! 
               agent->issues[0]->useableLinks->length);                            //JEDNAK wciąż losowy index partnera interakcji 
               
    pRTSILink currlnk=(RTSILink)agent->issues[0]->useableLinks[index];             //Wybrany link do partnera interakcji
    float    reliab=currlnk->weight;                                             assert(0<=abs(reliab) && abs(reliab)<=1);	//     
    
    if(MIN_RELIABILITY<reliab)                                                  //Tylko jak partner wart uwagi to coś zapamiętamy
    {                                                                           assert(reliab<=1);	//
      pAgent    partner=(Agent)currlnk->target;                                   assert(partner!=nullptr);	//
      
      float    currmes=partner->getSensor(0,world);                              // MODEL IMPORTANT PART!
                                                                                //PYTAMY O JEGO SENSOR A NIE O OPINIE!!! - MODEL IMPORTANT PART!    
      if(currmes!=INF_NOT_EXIST)                                                //O ile coś odpowiedział
      {                                                                         assert(0<=currmes && currmes<=1 );	//  String("partner.getSensor()==")+currmes;
        pInfo newFact=new Info(currmes,reliab,world->StepCounter,currlnk);        //Mamy zatem fakt któremu choć trochę ufamy
            
        if(SELF_LINKED && partner==agent)                                       //... some changes in reliability?   
        {                                                                       //Tylko linki powyżej MIN_RELIABILITY podlegają uczeniu!!!
          reliab=checkFactReliability(newFact,agent->issues[0]->facts,agent);     //Ta sytuacja trochę nietypowa //<>//
        }
        else
          reliab=checkFactReliability(newFact,agent->issues[0]->facts,nullptr);      //(pInfo fact,sArrayList<Info> infos,pNode selfsource) - MODEL IMPORTANT PART! 
        
        agent->issues[0]->facts->add(newFact);                                     //ZAPAMIĘTANIE NOWEGO FAKTU NA LIŚCIE DO WYDAWANIA OPINII
                                                                                //println(world->StepCounter,"\t",agent,partner,currmes,reliab,"OTHER FACT");//DEBUG
      }   
    }
  }
                                                                                //print("a");//DEBUG //<>//
}
/* NO OPINIONS IN simple_model 
  else 
  if(select<0.75)//Ask other for facts about others! (Jak ICH samopoczucie?)
  {
     //TODO???
  }
  else //Ask for opinions?
  {
    int index=agent->issues[0]->useableLinks->length;
    index=(int)(random(1)*random(1)*random(1)*index);//Losowy index partnera - skośna dystrybucja
    
    pRTSILink currlnk=(RTSILink)agent->issues[0]->useableLinks[index];
    float    reliab=currlnk->weight;                                            assert(0<=abs(reliab) && abs(reliab)<=1);	//
    
    if(0.1<=reliab  && reliab<=1 )//Tylko jak partner wart uwagi
    {
      pAgent    partner=(Agent)currlnk->target;
      float    currmes=partner->getOpinion(0);
      if(currmes!=INF_NOT_EXIST)
      {                                                                        assert(0<=currmes && currmes<=1 );	//  String("partner.getOpinion()==")+currmes;
        //... some changes in reliability TODO
        agent->issues[0]->opinions->add(new Info(currmes,reliab,world->StepCounter,currlnk)); //float ival,float asses,int timem,pRTSILink sour)
        println(world->StepCounter,"\t",agent,partner,currmes,reliab,"OPINION");
      }  
    }
  }
*/

void modelStepOnAgents(smatrix<pAgent> agents)
{
  int side=agents->length;
  int size=side*agents[0]->length;                //print("{");//DEBUG
  for(int a=size;a>0;a--)//M C step
  {
   int i=(int)random(side);
   int j=(int)random(agents[i]->length);
   
   pAgent alias=agents[i][j];                     //print(".");
   if(alias==nullptr) continue;//Nothing to do
                                                 //print(i,j);//DEBUG
   stepForAgent(alias,theWorld);                 //print(";");//DEBUG
  }
                                                 //print("}");//DEBIL
}

//OR

void modelStepOnAgents(sarray<pAgent> agents)
{
  assert(false);	//  "Implementation out of date";
}/*
  int side=agents->length;
  for(int a=side;a>0;a--)//M C step
  {
    int i=(int)random(side);
    pAgent alias=agents[i];
    if(alias==nullptr) continue;//Nothing to do
    stepForAgent(alias,theWorld);
  }
}*/
///////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - RTSI model in Processing
///////////////////////////////////////////////////////////////////////////////////////////////////////
//../../scripts/procesing2cpp.sh did it

