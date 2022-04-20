//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: AgentAd.pde
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

//*   Agent is a one of two central class of each ABM model
//*/////////////////////////////////////////////////////////////

class Agent: public virtual Object{
  public:
  char  genEat; //< Gene for probability of eating
  char  genPan; //< Gene for probability of punishment
  char  punished=0; //< NOT USED
  float energy; //< Agent resources
  
  /// Information for inspection or so...
  String info()
  {
    return String("Energy:")+energy+String(" genEat:")+nf(genEat,3)+String(" genPan:")+nf(genPan,3)+String(" punished:")+punished;
  }
  
  /// This function sets attribute values ensuring they are correct
  void set(float initEnergy,int igenEat,int igenPan)
  {
    energy=min(initEnergy,maxInitialEnergyOfAgent);
    
    if(igenEat<0) igenEat=0;
    if(igenEat>255) igenEat=255;
    genEat=(char)igenEat;
    
    if(usePunishment)
    {
      if(igenPan<0) igenPan=0;
      if(igenPan>255) igenPan=255;
      genPan=(char)igenPan;
    }
    else genPan=0;
  }
  
  /// Default constructor of the Agent
  Agent()
  {
    energy=(int)random(maxInitialEnergyOfAgent);
    genEat=(char)(random(255));
    genPan=usePunishment?(char)(random(255)):0;//A jeśli startujemy z małej skłonności?
  }
  
  /// Offspring constructor for Agent
  Agent(float initEnergy,int igenEat,int igenPan)
  {
    set(initEnergy,igenEat,igenPan);
  }
};

//*////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: AGENT for TragedyOfCommons
//*////////////////////////////////////////////////////////////////////////////////////////////
//../../scripts did it

