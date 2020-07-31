//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: InitModel.pde
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
//include "processing_inlines.hpp" //is optional. Use when project is already compilable
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

//   Initialisation of RTSI model utilized cell geometry
/////////////////////////////////////////////////////////

// This random link factory creates links with random weights
class RTSILinkFactory : public LinkFactory {
  public:
  ///INFO: 
  float min_weight,max_weight;
  int   default_type;
  
  RTSILinkFactory(float min_we,float max_we,int def_type)
  { 
    min_weight=min_we;max_weight=max_we;
    default_type=def_type;
  }
  
  pLink  makeLink(pNode Source,pNode Target)
  {
    return new RTSILink(Target,random(min_weight,max_weight),default_type);// MODEL IMPORTANT PART! LINK CREATION
  }
  
};

void resetAgents(smatrix<pAgent> agents)// MODEL IMPORTANT PART!
{
  int side=agents->length;
  pAgent curra=nullptr;
  for(int i=0;i<side;i++)
    for(int j=0;j<side;j++)
      if((curra=agents[i][j])!=nullptr)
      {
        curra->reset(); 
      }
  Info_maxInfos=0;
  Info_maxKnowl=0.001;
}
//OR
void resetAgents(sarray<pAgent> agents)
{
   assert(false);	//  "Implementation out of date";
}/*
  int side=agents->length;
  pAgent curra=nullptr;
  for(int i=0;i<side;i++)
    if((curra=agents[i])!=nullptr)
    {
      curra->reset();
    }
  Info_maxInfos=0;
  Info_maxKnowl=0.001;
}
*/
void initializeAgents(smatrix<pAgent> agents,// MODEL IMPORTANT PART!
                      pWorld     world)//Agents may need access into properties of the World, but not in simple_model
{
  int side=agents->length;
  for(int i=0;i<side;i++)
    for(int j=0;j<side;j++)
      if(random(1)<AGENTS_DENSITY)
      {
        pAgent curra=new Agent();
        curra->X=j+0.5;
        curra->Y=i+0.5;
        
        for (int k = 0; k < curra->sensors.length; k++)// MODEL IMPORTANT PART!
        {
             curra->sensors[k]->reliability=new RTSILink(curra,random(MIN_RELIABILITY,MAX_INI_RELIABILITY),k);//Some initial trust to own sensor - MODEL IMPORTANT PART!
             if(SELF_LINKED)
             {
               curra->addConn(curra->sensors[k]->reliability);                       //Dodaje self-link - czyli swój sensor traktuje jak sąsiadów
                                                                                  println(curra,"+ String(",curra->sensors[0]->reliability.fullInfo(");"));//DEBUG                                                      //DEBUG
             }
             //NOT USED simple_model
             //tmp->issues[k]->own_reliability=new RTSILink(tmp,random(0.5,1.0),k);  //Some initial trust to own "logic" 
    
             //float noise=tmp->sensors[k]->noise;//Noise of particular agent's sensor
             //TODO? Use noise as regulator of numbers of rules?
             //For now only one rule per agent per issue, fully random.
             //int nrules=world->rules[k]->size();
             //int index=(int)random(nrules);
             //float value=world->rules[k]->get(index);
             //tmp->issues[k]->rules->add(new Info(value,1,0,tmp->issues[k]->own_reliability));//Full assesment, time 0, source "my own".
        }
        
        agents[i][j]=curra;
      }
}
//OR
void initializeAgents(sarray<pAgent> agents,const pWorld world)//Agents need access into properties of the World
{
  assert(false);	//  "Implementation outr of date";
}/*
  int side=agents->length;
  for(int j=0;j<side;j++)
  if(random(1)<AGENTS_DENSITY)
  {
    pAgent tmp=new Agent();
    tmp->X=j+0.5;//???
    tmp->Y=0;//Why is different? Because of 1D?
    
    //for (int k = 0; k < tmp->sensors.length; k++)//Initial knowledge
    {
         //float noise=tmp->sensors[k]->noise;//Noise of particular agent's sensor
         //TODO? Use noise as regulator of numbers of rules?
         //For now only one rule per agent per issue, fully random.
         //int nrules=world->rules[k]->size();
         //int index=(int)random(nrules);
         //float value=world->rules[k]->get(index);
         //tmp->issues[k]->rules->add(new Info(value,1,0,nullptr));//Full assesment, time 0, source link unknown/autside the world.
    }
    
    agents[j]=tmp;
  }
}
*/
///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate.net/profile/WOJCIECH_BORKOWSKI - model initialisation
///////////////////////////////////////////////////////////////////////////////////////////
//../../scripts/procesing2cpp.sh did it

