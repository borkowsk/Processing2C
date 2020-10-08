//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: Agent.pde
#include "processing_templates.hpp"
//#include "processing_inlines.hpp" //is optional. Use when project is already compilable
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

// RTSI model - agent definition
///////////////////////////////////
static int   Agent_oldmaxInfos=1;  //Previous step max size of ArrayList<Info> in all existing objects of Issees class
static float Agent_oldmaxKnowl=1.0;//Previous step max knowledge from any ArrayList<Info> in all existing objects of Issees class        

class Agent : public NodeList , iVisNode {
  public:
   ///INFO: 
   float X,Y;//Position in real coordinates

   //float minOfcomfort;//Range of optimal 
   //float maxOfcomfort;//temperature for agent
   
   sarray<pSensor> sensors;
   sarray<pIssue>  issues;
      
   Agent()
   {
     //minOfcomfort=random(0.25,0.45);maxOfcomfort=random(0.55,0.75);//Each agent have different optimal range
     sensors=new array<pSensor>(NUM_OF_PROPERTIES);
     for (int i = 0; i < sensors->length; i++)
     {   //TODO - wyłączyć losowanie jak oba parametry równe 0.
         // BIAS_MEAN - mean value od BIAS, BIAS_DISP - dispersion. Each BIAS is inside range [mean-dispersion,mean+dispersion]
         float bias=random(BIAS_MEAN-BIAS_DISP,BIAS_MEAN+BIAS_DISP);     print(String("B=")+bias+ String(" "));// MODEL IMPORTANT PART! BIAS!!!
         float noise=random(MAX_ERROR_OF_SENSOR);                        print(String("N=")+noise+ String(" "));// MODEL IMPORTANT PART! NOISE!!!
         sensors[i] = new Sensor(i,noise,bias);                          // MODEL IMPORTANT PART! NOISE & BIAS
     }
         
     issues=new array<pIssue>(NUM_OF_ISSUES);
     for (int i = 0; i < issues->length; i++)
         issues[i] = new Issue(i);
   }
   
   String fullInfo(String fieldSeparator)
   {
      String res="";
      for (int i = 0; i < sensors->length; i++)
         res+=String("sensor[")+i+String("]:")+sensors[i].fullInfo(fieldSeparator)+ String("\n");
      for (int i = 0; i < issues->length; i++)
         res+=String("issues[")+i+String("]:")+issues[i].fullInfo(fieldSeparator)+ String("\n");
      return res;
   }
   
   void reset()
   {
     for (int i = 0; i < issues->length; i++)
         issues[i]->reset();
     for (int i = 0; i < sensors->length; i++)
         sensors[i]->reset();     
   }
   
   float getSensor(int index,pWorld world)
   {
     return sensors[index]->measure(X,Y,world->properties);
   }
   
   float getReality(int index,pWorld world)
   {
     return sensors[index]->reality(X,Y,world->properties);
   }
   
   float getReliability(int index)
   {
     return sensors[index]->getReliability();
   }
   
   float getOpinion(int index)
   {
     return issues[index]->getOpinion();
   }
   
   //Required for visualisation!
   float posX(){
	 return X;
	}
   float posY(){
	 return Y;
	}
   
   void setFill(/*float modifier=0 ?*/)
   {
      pIssue curr=issues[WhichProperty];
      float opinion=curr->getOpinion(); //print(opinion,"");
      if(opinion==INF_NOT_EXIST)
        fill(128,0,0);//Different than "the goby for two foretelled"
      else
      if(opinion>=0)  
        fill(opinion*255,opinion*255,0);
      else
        fill(0,-opinion*255,-opinion*255);
   }
   
   void setStroke(/*float modifier=0 ?*/)
   {
     if(AGENT_STROKE<=0) return; //Nothing to do!
     
     strokeWeight(AGENT_STROKE); //print("!");
     pIssue curr=issues[WhichProperty];
     float R=sensors[WhichProperty]->reliability->weight*255;//curr->getRulesKnowledge()/Agent_oldmaxKnowl;                  assert(0<=R);	//  String("R=")+R;
     float F=curr->getFactsKnowledge()/Agent_oldmaxKnowl;                  assert(0<=F);	//  String("F=")+F;
     float O=0;//curr->getOpinsKnowledge()/Agent_oldmaxKnowl;                  assert(0<=O);	//  String("O=")+O;
     
     stroke(O<=1?O*254:255,F<=1?F*254:255,R<=1?R*254:255);
   }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - RTSI model in Processing
///////////////////////////////////////////////////////////////////////////////////////////////////////
//../../scripts/procesing2cpp.sh did it

