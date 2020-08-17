//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: InfoCalc.pde
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
#include "processing_inlines.hpp" //is optional. Use when project is already compilable
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

// Class Info
///////////////////////////////////////////////////////////////////////
// Facts are represented by numbers between 0 and 1 (or between -1, +1) 
// and another number **(0-1) representing assessment of quality
// Opinions are also the same vectors of numbers.
///////////////////////////////////////////////////////////////////////

//float UP_Q_LINK_TRUST=0.10; // How much trust (weight of link) may go up in one interaction
//float DOWN_LINK_TRUST=0.30; // How much trust (weight of link) may go down in one interaction
//float UP_Q_RELIABILITY=0.10; // How much reliability of sensor may go up in one measuiring
//float DOWN_RELIABILITY=0.20; // How much reliability of sensor may go down in one measuiring

class Info {
  public: // MODEL IMPORTANT PART!
  ///INFO about class info: 
  float value;//[-1, +1]
  int   timemark;//Step = The time when this information was obtained
  float assessment;//[0-1] ??? Maybe should be get from current weight of the source of info link?
                   //Andrzej decided that this field is OK.
  pRTSILink sourceOfInfo;//You have to know from whom was the info obtained 
                        //May be NULL!!!
                        
  Info(float ival,float asses,int timem,pRTSILink sour)
  {
    value=ival;assessment=asses;timemark=timem;sourceOfInfo=sour;
  }
};

static int   Info_maxInfos=0;//Current max size of ArrayList<Info> in all existing objects of Issees class
static float Info_maxKnowl=0.001;//Current max knowledge from any ArrayList<Info> in all existing objects of Issees class

// IMPLEMENTATIONS:
///////////////////
float getSummOfKnowlegde(ArrayList<Info> infos)// NOW FOR VISUALISATION ONLY
{
    if(infos->size()<1) return INF_NOT_EXIST;// Checking and updating the variable maxInfos
    else if(infos->size()>Info_maxInfos) Info_maxInfos=infos->size();
    
    float know=0;
    
    for(Info inf:infos)
    {
      know+=inf->assessment;//Only level of assesment!
    }
    
    if(Info_maxKnowl<know) Info_maxKnowl=know;
    
    return know;
}

float getAssesedMeanOfKnowlegde(ArrayList<Info> infos)               // MODEL IMPORTANT PART!
{                                                                    // Ważona średnia z całej tablicy faktów
    if(infos->size()<1) return INF_NOT_EXIST;                         // Checking and updating the variable maxInfos
    else if(infos->size()>Info_maxInfos) Info_maxInfos=infos->size();
    
    float mean=0;
    float know=0;
    
    for(Info inf:infos)                                
    {
      mean+=inf->value*inf->assessment;
      know+=inf->assessment;
    }
    
    if(know>0)
    {
      if(Info_maxKnowl<know) Info_maxKnowl=know;
      return mean/know;
    }
    else
      return INF_NOT_EXIST;
}

float getAssesedMeanOfSource(ArrayList<Info> infos,pNode source)     //MODEL IMPORTANT PART!
{                                                                   //Ważona średnia z obecnych w tablicy faktów danego źródła
                                                                    assert(source!=nullptr);	//
                                                                    assert(infos!=nullptr);	//
    if(infos->size()<1) return INF_NOT_EXIST;                        // Checking and updating the variable maxInfos
    else if(infos->size()>Info_maxInfos) Info_maxInfos=infos->size();
    
    float mean=0;
    float know=0;//To musi być suma wszystkich wag!
    
    for(Info inf:infos)
    if(inf->sourceOfInfo!=nullptr 
    && inf->sourceOfInfo.target==source)                             //Filtrowanie jednego źródła
    {
      mean+=inf->value*inf->assessment;
      know+=inf->assessment;
    }
    
    if(know>0)
    {
      if(Info_maxKnowl<know) Info_maxKnowl=know;
      return mean/know;
    }
    else
      return INF_NOT_EXIST;
}

void checkCoherenceWithReality(float reality,ArrayList<Info> infos,pAgent self)//very mild version - MODEL IMPORTANT PART!
{
    for(Info inf:infos)
    {                                     
      if(inf->sourceOfInfo!=nullptr)//When link is available to change
      {
        float errsqr=sqr(reality-inf->value);//squared error                   // MODEL IMPORTANT PART!
                                                                              //print("SQRE=",errsqr);//DEBUG
        if(errsqr>SQR_ERROR_TRESHOLD)
        {
              inf->sourceOfInfo.weight*=(1-DOWN_LINK_TRUST);                   // MODEL IMPORTANT PART!
              link_dw++;//Count when weight goes down!
                                                                              //print("l-");//DEBUG   
        }
        else
        {
              inf->sourceOfInfo.weight+=                                       // MODEL IMPORTANT PART!
                          (1-inf->sourceOfInfo.weight)*UP_Q_LINK_TRUST;        // MODEL IMPORTANT PART!
              link_up++;//Count when weight goes up
                                                                              //print("l+");//DEBUG
        } 
      }
    }
} //<>//

float checkFactReliability(pInfo fact,ArrayList<Info> infos,pAgent self)// MODEL IMPORTANT PART!!!
{                                                
    float val=getAssesedMeanOfKnowlegde(infos);                               //Mean result - MODEL IMPORTANT PART! //<>//
                                                                              //Ważona średnia z całej tablicy faktów
    if(val!=INF_NOT_EXIST)
    {
      float errsqr=sqr(val-fact->value);//squared error                        // MODEL IMPORTANT PART! //<>//
                                                                              assert(fact->sourceOfInfo.weight>=0);	//
      if(errsqr>SQR_ERROR_TRESHOLD)
      {
            fact->assessment/=2;//TODO WHY as much?!                           //Lowering trust for this fact  - MODEL IMPORTANT PART!!!
            fact->sourceOfInfo.weight*=(1-DOWN_LINK_TRUST);                    //Lowering trust for this source! -  MODEL IMPORTANT PART!
            link_dw++;                                                        //Count when weight goes down!
                                                                              //print("l-");//DEBUG   
      }
      else
      {
            fact->sourceOfInfo.weight+=                                        // MODEL IMPORTANT PART!
                        (1-fact->sourceOfInfo.weight)*UP_Q_LINK_TRUST;         //More trust for this source! - MODEL IMPORTANT PART!
            link_up++;                                                        //Count when weight goes up!
                                                                              //print("l+");//DEBUG
      }
                                                                              assert(fact->sourceOfInfo.weight<=1);	//
      float myres=0;//For own result      
      if(self!=nullptr                                                           //only if self is known 
      && (myres=getAssesedMeanOfSource(infos,self))!=INF_NOT_EXIST)           //If has it own results and mean result, then is able to check own sensor
      {                                                                       assert(self->sensors[0]->reliability->weight>=0);	//
        errsqr=sqr(val-myres);//squared error                                 // MODEL IMPORTANT PART! 
        if(errsqr>SQR_ERROR_TRESHOLD)
        {
           self->sensors[0]->reliability->weight*=(1-DOWN_SELF_TRUST);          //Lowering trust of sensor - MODEL IMPORTANT PART!          
           sensor_dw++;//Count!                                               //print("s-");//DEBUG
        }
        else
        {
           self->sensors[0]->reliability->weight+=                               // MODEL IMPORTANT PART!
                   (1-self->sensors[0]->reliability->weight)*UP_Q_SELF_TRUST;   //More trust for my own sensor - MODEL IMPORTANT PART!
           sensor_up++;//Count!                                               //print("s+");//DEBUG
        }
                                                                              assert(self->sensors[0]->reliability->weight<=1);	//
                                            
                                                                              //println("\t",
        //self,"Sensor assesment:",self->sensors[0]->reliability->weight,self->sensors[0]->reliability->weight<0.01? //DEBUG
                                                                              //"!!!!!!!!!":"");
      }
    }
                                                                              //print("r");//DEBUG
    return fact->assessment;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate.net/profile/WOJCIECH_BORKOWSKI - RTSI model in Processing
///////////////////////////////////////////////////////////////////////////////////////////////////////
//../../scripts/procesing2cpp.sh did it

