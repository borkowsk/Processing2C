// RTSI model - model specific abstract classes definitions
////////////////////////////////////////////////////////////////

class RTSILink extends Link {
   ///INFO: 
   //Colored link rather
   //The network is multi-layered. 
   //A separate network exists for each issue and connections strength corresponds to the perceived 
   //competence of the partner. 
   //One network is common to all the issues and it corresponds to perceived intention (good-bad) 
   //or morality(type MORALITY_MARKER). 
   //Connection strength is updated in each MC step. 
   //New connections may be created and old connections broken (DELETION NOT IMPLEMENTED YET!)
   int timemark;//Step, when this link is used last time. 
   //int social;//social debt on this link (How much does the Source owe the Target)
   RTSILink cross;//cross connection for similar links, eg. morality_link of same target or reverse link (some kind of link cache)
   RTSILink(Node targ,float we,int ty) { super(targ,we,ty); timemark=0;cross=null;/*social=0;*/}
   
   String fullInfo(String fieldSeparator)
   {
    return super.fullInfo(fieldSeparator)+fieldSeparator+"TM:"+timemark;
   }
}; //; after class is not a problem for Processing

class Sensor {
  ///INFO: Each agent has its own sensors
  float   lastMeasurement;
  int     propertyIndex;//Capacity(?) to measure a signal from the environment
  float   noise;//+-noise added to each measurement (maybe not for all types of sensors?)
  float   bias;//Stable part of sensor error
  RTSILink reliability;//=0; Indication of accuracy of sensor - agent have to  
                       //calculate it during simulation 
                       //Link is used because of common interface to the Info
  
  Sensor(int index,float nn,float bia){propertyIndex=index;noise=nn;reliability=null;bias=bia;lastMeasurement=INF_NOT_EXIST;}
  
  String fullInfo(String fieldSeparator)
  {
    return "Ns:"+noise+fieldSeparator+"Bi:"+bias+fieldSeparator+"rel:"+reliability.fullInfo(fieldSeparator);
  }
  
  void  reset(){lastMeasurement=INF_NOT_EXIST;}
  
  float getReliability() { return reliability.weight; }
  
  float measure(float x,float y,PropertyBase[] props)
  {
    PropertyBase p=props[propertyIndex];
    float min=p.getMin();
    float max=p.getMax();
    float val=p.get2D(x,y);
    
    val+=random(-noise,noise)+bias;//BIAS USED!!! MODEL IMPORTANT PART!
    
    if(val<min) val=min;//TODO TEST ???
    if(val>max) val=max;//It is needed or map() do the same?
    
    if(min==0 && max==1)
      return lastMeasurement=val;
    else
      return lastMeasurement=map(val,min,max,0,1);
  }
  
  float reality(float x,float y,PropertyBase[] props)
  {
    PropertyBase p=props[propertyIndex];
    return p.get2D(x,y);
  }
};

enum StateOfIssue { NOT_NEED,NEED_OPINION,HAVE_OPINION,HAVE_DECISION }
                                                            
//NOTE:
//Cannot be inside Issue because in processing all classes are inside classes of the Applet! 
//https://stackoverflow.com/questions/37509919/field-cannot-be-declared-static-in-a-non-static-inner-type-unless-initialized-wi

class Issue { 
  ///INFO: Issue === Topic ??
  StateOfIssue   flag;//  0) have decision! a) have an opinion, b) do not have an opinion and do not need it, c) do not have an opinion and need it.  
  //float importance;//~ urgency? Should be different attribute? Treshold for HAVE_DECISION, 2/3*importance for HAVE_OPINION
  int     properties;//index of related properties
  float   currentop;//current opinion
  
  ArrayList<Info> facts;
  //ArrayList<Info> opinions;
  ArrayList<Info> rules;
  
  //This own_reliability is probably not used in this version of simple_model.
  //Reliability of sensor is used instead
  //RTSILink own_reliability=null;// Indication mean accuracy of agent knowlegde.  
                           //It will be calculated during simulation 
                           //Link is used because of common interface to the Info
                           
  /*RTSI*/Link[] useableLinks=null;
  
  Issue(int index)
  {
    flag=StateOfIssue.NOT_NEED;
    properties=index;
    //importance=random(1);//not used in simple_model
    currentop=INF_NOT_EXIST;
    
    facts=new ArrayList<Info>();
    //opinions=new ArrayList<Info>();
    rules=new ArrayList<Info>();
  }
  
  String fullInfo(String fieldSeparator)
  {
    return "Op:"+currentop+fieldSeparator+"NofFacts:"+facts.size();
  }
  
  void reset()
  {
    useableLinks=null;
    flag=StateOfIssue.NOT_NEED;
    currentop=INF_NOT_EXIST;
    facts.clear();
    //opinions.clear();//not used in simple_model
    rules.clear();//may be used in simple_model
  }
  
  //float getRulesKnowledge(){return getSummOfKnowlegde(rules);} //Currently for visualisation only
  
  float getFactsKnowledge(){return getSummOfKnowlegde(facts);} //Currently for visualisation only
  
  //float getOpinsKnowledge(){return getSummOfKnowlegde(opinions);} //not used in simple_model
  
  float getOpinion() //Should be between 0 to 1. MODEL IMPORTANT PART! //<>//
  {
     float val=getAssesedMeanOfKnowlegde(facts);//0.5*getAssesedMeanOfKnowlegde(facts)+0.5*getAssesedMeanOfKnowlegde(opinions);
     if(val==INF_NOT_EXIST) return INF_NOT_EXIST;
     
     if(val>1) 
     {
         println(this,val);//DEBUG
         val=1;
     }
     return currentop=val;
  }
  
};
///////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - RTSI model in Processing
///////////////////////////////////////////////////////////////////////////////////////////////////////
