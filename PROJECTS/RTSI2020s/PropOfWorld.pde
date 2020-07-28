// Basic properties of the world
////////////////////////////////////////////////////////////////////////////////

final float INF_NOT_EXIST=Float.MAX_VALUE;  ///visible autside this file!

class PropertyBase {
  ///INFO: 
  //local property of world (e.g. temperature, availability of some information etc.) 
  //There are up to 10 topics of information which is a number between 0 and 1. 
  //Information also may have a value of DOES NOT EXIST (e.g, represented by INF_NOT_EXIST). 
  //May varies over time.  Probably by randomly drawing new random clusters (???).
  String getName(){ return "BASE_OF_PROPERTY";}
  float get0D(){return INF_NOT_EXIST;}
  float get1D(float x){return INF_NOT_EXIST;}
  float get2D(float x,float y){return INF_NOT_EXIST;}
  float getMin(){ return -Float.MAX_VALUE;}//MIN_RANGE_VALUE?
  float getMax(){ return +Float.MAX_VALUE;}//Always must be different!
  void  reset(){}//May but not must change values
};

class MultProperty extends PropertyBase {
  ///INFO: 
  String getName(){ return "Multiplicative";}
  float get0D(){return 1;}
  float get1D(float x){return x*x;}
  float get2D(float x,float y){return x*y;}
  float getMin(){ return -Float.MAX_VALUE;}
  float getMax(){ return Float.MAX_VALUE;}//Must be different!
};

class SinMultProperty extends PropertyBase {
  ///INFO: 
  String getName(){ return "Sinus multiplicative";}
  float get0D(){return 1;}
  float get1D(float x){return sin(x);}
  float get2D(float x,float y){return sin(x)*sin(y);}
  float getMin(){ return -1.0;}
  float getMax(){ return +1.0;}//Must be different!
};

class CosMultProperty extends PropertyBase {
  ///INFO: 
  String getName(){ return "Cosinus multiplicative";}
  float get0D(){return 1;}
  float get1D(float x){return cos(x);}
  float get2D(float x,float y){return cos(x)*cos(y);}
  float getMin(){ return -1.0;}
  float getMax(){ return +1.0;}//Must be different!
};

class DefPerlinProperty extends PropertyBase { // MODEL IMPORTANT PART!
  ///INFO: 
  float multx,multy;
  float offsx,offsy;
  int   ndet;
  float noffs;
  String getName(){ return "Perlin noise {"+ndet+","+noffs+"}["+multx+","+multy+","+offsx+","+offsy+"]";}
  DefPerlinProperty(float mx,float my){ multx=mx;multy=my;offsx=offsy=0;noffs=NOISE_OFFS;ndet=NOISE_DETAILS;noiseDetail(NOISE_DETAILS,NOISE_OFFS);}
  DefPerlinProperty(float mx,float my,float offx,float offy){ multx=mx;multy=my;offsx=offx;offsy=offy;noffs=NOISE_OFFS;ndet=NOISE_DETAILS;noiseDetail(NOISE_DETAILS,NOISE_OFFS);}
  
  float get0D(){return 0;}
  float get1D(float x){return noise((offsx+x)*multx);}
  float get2D(float x,float y){return noise((offsx+x)*multx,(offsy+y)*multy);}// MODEL IMPORTANT PART!
  float getMin(){ return -0.0;}
  float getMax(){ return +1.0;}//Must be different!
  
  void  reset() // MODEL IMPORTANT PART!
  {
    //println("Properties reseting");//DEBUG
    
    ndet+=(random(1)<0.5?-1:1);// MODEL IMPORTANT PART!
    if(ndet<=2) ndet=2;
    if(ndet>10) ndet=10;
    
    noffs+=random(-0.02,0.02);
    //if(noffs<0.01) noffs=0.01;
    //if(ndet*noffs>0.9) noffs=0.9/ndet;
    if(noffs<0.1) noffs=0.1;//DEBUG?
    if(noffs>0.5) noffs=0.5;//DEBUG?
    
    noiseDetail(ndet,noffs);
    
    /*if(NOISE_DRIFT==0)// MODEL IMPORTANT PART!
    {
      offsx+=random(1000);//Just use random?
      offsy+=random(1000);//TODO CHECK!
    }
    else
    {
      offsx+=random(-NOISE_DRIFT,NOISE_DRIFT);// MODEL IMPORTANT PART!
      offsy+=random(-NOISE_DRIFT,NOISE_DRIFT);// MODEL IMPORTANT PART!      
    }*/
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - RTSI model in Processing
///////////////////////////////////////////////////////////////////////////////////////////////////////
