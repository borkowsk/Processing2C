//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: AssembOfWorld.pde
#include "processing_templates.hpp"
//#include "processing_inlines.hpp" //is optional. Use when project is already compilable
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

//   World for RTSI model utilized cell geometry
///////////////////////////////////////////////////////////////

class World {
  public:
  ///INFO: 
  int StepCounter=0;
  sarray<pPropertyBase>  properties;//All properties of the world
  //sarray<pFloatList>     rules; //not in simple_model? TODO?
  pLinkFilter      currFilter=nullptr;
  //sarray<pAgent>       agents;//One dimensional array of inhabitants - assert(false);	//  "Implementation out of date";
  //OR
  smatrix<pAgent>       agents;//Two dimensional array of inhabitants
  
  World(int side)//Constructor of the World
  {
    properties=new array<pPropertyBase>(NUM_OF_PROPERTIES);
    //rules=new array<pFloatList>(NUM_OF_PROPERTIES);//not in simple_model? TODO?
    //agents=new array<pAgent>(side); assert(false);	//  "Implementation out of date";
    //OR
    agents=new matrix<pAgent>(side,side);
  }
  
  void initializeProperties()
  {    
    for(int p=0;p<NUM_OF_PROPERTIES;p++)
    {
        print("Property[",p,"]: "); 
        properties[p]=new DefPerlinProperty((p+1)*NOISE_SCALE,(p+1)*NOISE_SCALE,random(100),random(100));// MODEL IMPORTANT PART! ENVIRONMENT
        println(properties[p]->getName());
        //print(" Rules:");
        //rules[p]=new FloatList();        
        //float limit=1.0;         // NOT IN simple_model
        //float knsum=0;
        /*
        while(limit>SMALL_RULE_LIMIT)
        {
          float rule=random(limit*RULE_DETAILER);
          rules[p]->append(rule);
          limit-=rule;
          knsum+=rule;
          print(rule,"");
        }
        println(" number of rules:",rules[p].size()," Maximal knowledge:",knsum);
        */
    }
    //properties[0]=new SinMultProperty();  
  }
  
  void initializeModel()
  {
    initializeProperties(); 
    pixelizeProperties2D(this->properties);
    
    initializeAgents(this->agents,this);//First parameter is important because of function selection
    
    if(NETWORK_DENSITY==1)// MODEL IMPORTANT PART! NETWORK INITIALISATION
      makeFullNet(this->agents,new RTSILinkFactory(MIN_RELIABILITY,MAX_INI_RELIABILITY,MINIMAL_PROPERTY_INDEX));// MODEL IMPORTANT PART!
    else                                                                                                       // MODEL IMPORTANT PART!
      makeRandomNet(this->agents,new RTSILinkFactory(MIN_RELIABILITY,MAX_INI_RELIABILITY,MINIMAL_PROPERTY_INDEX),NETWORK_DENSITY);// MODEL IMPORTANT PART!
  }

  void visualizeModel()
  {
    if(currFilter==nullptr) //int   WhichProperty=0;//Which property of the world is about to visualise? 
          currFilter=comboVisFilter->reset(WhichProperty,linkWeightTresh);//float linkWeightTresh=0;//For link filtering
    //visualizeProperties2D(this->properties);//DEBUG. Now used only after reseting of properties
    if(VIS_AGENTS || WITH_STROKE)
      visualizeAgents(this->agents);
    if(VIS_NETWORK) 
      visualiseLinks(this->agents,currFilter,0,0,cwidth);
    //visualizeAgents(this->agents);
  }
  
  void modelStep() // MODEL IMPORTANT PART!
  {                                                        //print(String("<")+StepCounter+ String(" "));//DEBUG
    modelStepOnAgents(this->agents);                        //... do simulation on agents - IMPORTANT PART!
    Agent_oldmaxKnowl=Info_maxKnowl;
    Agent_oldmaxInfos=Info_maxInfos;
    StepCounter++;                                         //print(">");//DEBUG 
  }
  
  void resetModel() // MODEL IMPORTANT PART!
  {
    for(int p=0;p<NUM_OF_PROPERTIES;p++)
    {
        print("Property[",p,"]: "); 
        properties[p]->reset();// IMPORTANT PART!
        println(properties[p]->getName());//DEBUG
    }
    
    resetAgents(agents);// IMPORTANT PART!
  }
};

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - WORLD FOR FILL UP
///////////////////////////////////////////////////////////////////////////////////////////
//../../scripts/procesing2cpp.sh did it

