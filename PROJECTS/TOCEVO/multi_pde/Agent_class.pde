//_pragma once
//_ifndef HEADER_Agent_INCLUDED
//_define HEADER_Agent_INCLUDED

/// Agent is a one of two central class of each ABM model.

/// @note Automatically extracted definition of `class`: Agent
class Agent  {

  char  genEat;     //!< Gene for probability of eating.
  char  genPan;     //!< Gene for probability of punishment.
  char  punished=0; //!< NOT USED.
  float energy;     //!< Agent resources.
  
  /// Information for inspection or so...
  String info()
  {
    return "Energy:"+energy+" genEat:"+nf(genEat,3)+" genPan:"+nf(genPan,3)+" punished:"+punished;
  }
  
  /// This function sets attribute values ensuring they are correct.
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
  
  /// Default constructor of the Agent.
  Agent()
  {
    energy=(int)random(maxInitialEnergyOfAgent);
    genEat=(char)(random(255));
    genPan=usePunishment?(char)(random(255)):0; // A jeśli startujemy z małej skłonności?
  }
  
  /// Offspring constructor for Agent.
  Agent(float initEnergy,int igenEat,int igenPan)
  {
    set(initEnergy,igenEat,igenPan);
  }
  
};

/// Generated by Processing2C++ extraction Tools
//_endif //HEADER_Agent_INCLUDED
