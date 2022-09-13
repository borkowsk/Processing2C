//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: AgentAd.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "processing_string.hpp"  //Processing::String class
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

///   Agent is a one of two central class of each ABM model
//*/////////////////////////////////////////////////////////////

class Agent: public virtual Object{
  public:
  char16_t  genEat; //!< Gene for probability of eating
  char16_t  genPan; //!< Gene for probability of punishment
  char16_t  punished=0; //!< NOT USED
  float energy; //!< Agent resources
  
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
    genEat=(char16_t)igenEat;
    
    if(usePunishment)
    {
      if(igenPan<0) igenPan=0;
      if(igenPan>255) igenPan=255;
      genPan=(char16_t)igenPan;
    }
    else genPan=0;
  }
  
  /// Default constructor of the Agent
  Agent()
  {
    energy=(int)random(maxInitialEnergyOfAgent);
    genEat=(char16_t)(random(255));
    genPan=usePunishment?(char16_t)(random(255)):0; //A jeśli startujemy z małej skłonności?
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

