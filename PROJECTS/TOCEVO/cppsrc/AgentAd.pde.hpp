// @date 2026-01-29 (last modification)
/// Agent is a one of two central class of each ABM model.
//*/////////////////////////////////////////////////////////////

class Agent: public virtual Object{
  public:
  char16_t  genEat;     //!< Gene for probability of eating.
  char16_t  genPan;     //!< Gene for probability of punishment.
  char16_t  punished=0; //!< NOT USED.
  float energy;     //!< Agent resources.
  
  /// Information for inspection or so...
  String info()
  {
    return String("Energy:")+energy+String(" genEat:")+nf(genEat,3)+String(" genPan:")+nf(genPan,3)+String(" punished:")+punished;
  }
  
  /// This function sets attribute values ensuring they are correct.
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
  
  /// Default constructor of the Agent.
  Agent()
  {
    energy=(int)random(maxInitialEnergyOfAgent);
    genEat=(char16_t)(random(255));
    genPan=usePunishment?(char16_t)(random(255)):0; // A jeśli startujemy z małej skłonności?
  }
  
  /// Offspring constructor for Agent.
  Agent(float initEnergy,int igenEat,int igenPan)
  {
    set(initEnergy,igenEat,igenPan);
  }
  
};

//*////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: AGENT for TragedyOfCommons
//*////////////////////////////////////////////////////////////////////////////////////////////
//MADE NOTE: ../../scripts did it 2026-01-29 16:31:16 !

