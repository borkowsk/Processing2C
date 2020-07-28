// Functions & classes for chart making
///////////////////////////////////////////////////////////////////////////////////////////
//final float INF_NOT_EXIST=Float.MAX_VALUE;

class NamedData implements iNamed {
  ///INFO:
  String myName;
  NamedData(String Name){ myName=Name;}
  String name() {return myName;}
};

class Range extends NamedData {
  ///INFO: 
  float min=+Float.MAX_VALUE;
  float max=-Float.MAX_VALUE;
  
  Range(String Name){ super(Name);}
  
  void addValue(float value)
  {
    if(value==INF_NOT_EXIST) return;
    if(max<value)
    {
      max=value;
    }
    if(min>value)
    {
      min=value;
    }
  }
};

class Sample  extends NamedData {
  ///INFO:  For representing series of numbers
  FloatList data=null;
  
  float   min=+Float.MAX_VALUE;
  int   whmin=-1;
  float   max=-Float.MAX_VALUE;
  int   whmax=-1;
  double   sum=0;
  int    count=0;//Licznik REALNYCH wartości!
  
  Sample(String Name)
  {
    super(Name);
    data=new FloatList();
  }
  
  int  numOfElements() 
  { 
     return data.size();//Razem z pustymi czyli INF_NOT_EXIST
  }
  
  void reset()
  {
    data.clear();
    min=-Float.MAX_VALUE;
    whmin=-1;
    max=-Float.MAX_VALUE;
    whmax=-1;
    sum=0;  
    count=0;
  }
  
  float getMin()
  {
    if(count>0) return min;
    else return INF_NOT_EXIST;
  }
  
  float getMax()
  {
    if(count>0) return max;
    else return INF_NOT_EXIST;
  }
  
  float getMean()
  {
    if(count>0) return (float)(sum/count);
    else return INF_NOT_EXIST;
  }
  
  float getStdDev() //TODO
  {
    if(count==0) return INF_NOT_EXIST;
    int    N=0;
    double kwadraty=0;
    double mean=getMean();
    for(float val:data)
    if(val!=INF_NOT_EXIST)
    {
      kwadraty+=sqr(val-mean);
      N++;
    }
                              assert N==count;
    return (float)(kwadraty/N);
  }
  
  void addValue(float value)
  {        
    data.append(value);
    
    if(value==INF_NOT_EXIST) return;//Nic więcej do zrobienia
    
    sum+=value;
    count++;//Realna wartość a nie pusta!
    
    if(max<value)
    {
      max=value;
      whmax=data.size()-1; //print("^");
    }
    if(min>value)
    {
      min=value;
      whmin=data.size()-1; //print("v");
    }
  }
};

class Frequencies extends NamedData {
  ///INFO:  For representing frequencies 
  private int[]   buckets=null;
  float   sizeOfbucket=0;//(Max-Min)/N;
  float   lowerb=+Float.MAX_VALUE;
  float   upperb=-Float.MAX_VALUE;
  int     outsideLow=0;
  int     outsideHig=0;
  int     inside=0;
  int     higherBucket=0;
  int     higherBucketIndex=-1;

  Frequencies(int numberOfBuckets,float lowerBound, float upperBound,String Name)
  {
    super(Name);
    buckets=new int[numberOfBuckets];
    lowerb=lowerBound;
    upperb=upperBound;
    sizeOfbucket=(upperBound-lowerBound)/numberOfBuckets;
  }
  
  int  numOfElements() { return buckets.length;}
  
  void reset()
  {
    for(int i=0;i<buckets.length;i++)
            buckets[i]=0;
    outsideLow=0;
    outsideHig=0;
    inside=0;
    higherBucket=0;
    higherBucketIndex=-1;    
  }
  
  void addValue(float value)
  {
    if(value==INF_NOT_EXIST) return;
    
    if(value<lowerb)
      {outsideLow++;return;}
    
    if(value>upperb) 
      {outsideHig++;return;}    
    
    int index=(int)((value-lowerb)/sizeOfbucket);
         
    buckets[index]++;
    
    if(higherBucket<buckets[index])
      {higherBucket=buckets[index];higherBucketIndex=index;}
    
    inside++;
  }
};

void viewAxis(int startX,int startY,int width,int height)
{
  line(startX,startY,startX+width,startY);
  line(startX+width-5,startY-5,startX+width,startY);
  line(startX,startY,startX,startY-height);
  line(startX+5,startY-height+5,startX,startY-height);
  line(startX-5,startY-height+5,startX,startY-height);
}

void viewFrame(float startX,float startY,int width,int height)
{
  line(startX,startY,startX+width,startY);
  line(startX,startY,startX,startY-height);
  line(startX+width,startY,startX+width,startY-height);
  line(startX,startY-height,startX+width,startY-height);
}

void viewTicsV(int startX,int startY,int width,int height,float space)
{
  for(int y=startY;y>startY-height;y-=space)
     line(startX,y,startX+width,y);
}

void viewTicsH(float startX,float startY,float width,float height,float space)
{
  for(int x=int(startX);x<startX+width;x+=space)
     line(x,startY,x,startY-height);
}

void viewScaleV(Range MinMax,int startX,int startY,int width,int height)//,boolean logaritm)//Na razie tu nie rysujemy kresek (tics)
{
   //float min=(logaritm?(float)Math.log10(MinMax.min+1):MinMax.min);//+1 wizualnie niewiele zmienia a gwarantuje obliczalność
   //float max=(logaritm?(float)Math.log10(MinMax.max+1):MinMax.max);//+1 wizualnie niewiele zmienia a gwarantuje obliczalność
   textAlign(LEFT,TOP);
   text(""+MinMax.min,startX+width,startY);
   text(""+MinMax.max,startX+width,startY-height);
}

void viewAsPoints(Sample data,//Źródło danych
                  int startD, //Punkt startowy wyświetlania, albo liczba od końca  - gdy wartość ujemna
                  float startX,float startY,int width,int height,boolean logaritm,Range commMinMax,boolean connect)
{
  float min,max;
  if(commMinMax!=null)
  {
    min=(logaritm?(float)Math.log10(commMinMax.min+1):commMinMax.min);//+1 wizualnie niewiele zmienia a gwarantuje obliczalność
    max=(logaritm?(float)Math.log10(commMinMax.max+1):commMinMax.max);//+1 wizualnie niewiele zmienia a gwarantuje obliczalność    
  }
  else
  {
    min=(logaritm?(float)Math.log10(data.min+1):data.min);//+1 wizualnie niewiele zmienia a gwarantuje obliczalność
    max=(logaritm?(float)Math.log10(data.max+1):data.max);//+1 wizualnie niewiele zmienia a gwarantuje obliczalność
  }
  
  int     N=data.numOfElements();       assert startD<N-1;
  if(startD<0)
  {
      startD=-startD;//Ujemne było tylko umownie!!!
      startD=N-startD;//Ileś od końca
  }
  if(startD<0) //Nadal ujemne!?
  {
      startD=0;//Czyli zabrakło danych
      //print("?");
  }
  float wid=float(width)/(N-startD);  //println(width,N,startD,wid,min,max);
  float oldy=-Float.MIN_VALUE;
  
  for(int t=startD;t<N;t++)
  {
    float val=data.data.get(t);
    if(val==INF_NOT_EXIST) 
    {
      oldy=-Float.MIN_VALUE;
      continue;
    }
    
    if(logaritm)
      val=map((float)Math.log10(val+1),min,max,0,height);    
    else 
      val=map(val,min,max,0,height);
    
    float x=(t-startD)*wid;
    if(connect && oldy!=-Float.MIN_VALUE)
    {
      line (startX+x-wid,startY-oldy,startX+x,startY-val);//println(wid,x-wid,oldy,x,val);
    }
    else
    {
                                                          //println(startX+x,startY-val);
      line(startX+x+2,startY-val,startX+x-1,startY-val); 
      line(startX+x,startY-val+2,startX+x,startY-val-1); 
    }
    
    if(connect) oldy=val;
    
    if(t==data.whmax || t==data.whmin)
    {
      textAlign(LEFT,TOP);
      text(""+data.data.get(t),startX+x,startY-val);
    }
  }
}

float viewAsColumns(Frequencies hist,float startX,float startY,int width,int height,boolean logaritm)
{
  float max=(logaritm?(float)Math.log10(hist.higherBucket+1):hist.higherBucket);//+1 wizualnie niewiele zmienia a gwarantuje obliczalność
  int wid=width/hist.buckets.length; //println(width,wid);
  if(wid<1) wid=1;
  
  for(int i=0;i<hist.buckets.length;i++)
  {
    float hei;
    if(logaritm)
      hei=map((float)Math.log10(hist.buckets[i]+1),0,max,0,height);    
    else 
      hei=map(hist.buckets[i],0,max,0,height);
    
    rect(startX+i*wid,startY,wid,-hei);
  }
  
  textAlign(LEFT,BOTTOM);
  text(""+max+(logaritm?"<="+hist.higherBucket+" @ "+hist.higherBucketIndex:" @ "+hist.higherBucketIndex),startX,startY-height);
  //Real width of histogram
  float realwidth=(hist.buckets.length)*wid;//println(realwidth);noLoop();
  return realwidth;
}

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - HANDY FUNCTIONS & CLASSES
///////////////////////////////////////////////////////////////////////////////////////////
