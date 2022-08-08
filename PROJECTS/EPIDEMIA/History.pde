/// ABM (Agent Base Modeling) minimum template test for Processing2C
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: aSimpleHistory.pde
//*///////////////////////////////////////////////////////////////////
/// Wykres zmian w czasie
//*///////////////////////////////////////////////////////////////////

//void timeline(FloatList data,             //dane do wykresu
//              float startX, float startY, //Położenie początku
//              float height,               //wysokość
//              boolean logaritm);          //czy logarytmować dane
              
void timeline(FloatList data,float startX, float startY, float height,boolean logaritm) /// Dla C++ ta deklaracja musi być umieszczona w HPP
{
  float   Max=-Float.MAX_VALUE;
  int     whMax=-1; //Gdzie jest maksimum
  float   Min=Float.MAX_VALUE;
  int     whMin=-1; //Gdzie jest minimum
  int     N=data.size(); //Ile pomiarów
  float  lenght=width-startX; //Ile miejsca na wykres
  
  // Szukanie minimum i maksimum
  for(int t=0;t<N;t++)
  {
    float val=data.get(t);
    if(val>Max) { Max=val; whMax=t;}
    if(val<Min) { Min=val; whMin=t;}
  }
  
  if(logaritm)
  {
    Max=(float)Math.log10(Max+1); //+1 to takie oszustwo 
    Min=(float)Math.log10(Min+1); //żeby 0 nie wywalało obliczeń
  }
  
  // Właściwe rysowanie
  float wid=lenght/N; //println(width,N,wid,min,max);DEBUG
  float oldy=-Float.MIN_VALUE;
  for(int t=0;t<N;t++)
  {
    float val=data.get(t);
    
    if(logaritm)
      val=map((float)Math.log10(val+1),Min,Max,0,height);    
    else 
      val=map(val,Min,Max,0,height);
    
    float x=t*wid;
    if(oldy!=-Float.MIN_VALUE)
    {
      line (startX+x-wid,startY-oldy,startX+x,startY-val);
    }
    else
      point(startX+x,startY-val);
    
    oldy=val;
    
    if(t==whMax || t==whMin)
    {
      textAlign(LEFT,BOTTOM);
      String out=""+data.get(t);
      text(out,startX,startY-val); //Na osi X
      text(out,startX+x,startY-val); //Przy danych
    }
  }
}

/// A jakby miało być więcej zmiennych? UWAGA!:  wspólna skala!!!
/// Wtedy np. tak jak poniżej, co jest wersją bardzo prymitywną, ale będzie działać :-D
void timeline(FloatList data_a,FloatList data_b,FloatList data_c,float startX,float startY,float height,boolean logaritm,color color_a,color color_b,color color_c) /// Dla C++ ta deklaracja musi być umieszczona w HPP
{
  float   Max=-Float.MAX_VALUE; //Tu będzie prawdziwa wartość
  float   gMax=0; //A tu przeliczona dla grafiki
  float   Min=Float.MAX_VALUE; //J.w.
  float   gMin=0; //Analogicznie j.w.
  int     N1=data_a.size(),N2=data_b.size(),N3=data_c.size(); //Ile pomiarów
  float   lenght=width-startX; //Ile miejsca na wykres
  
  //Szukanie minimum i maksimum
  for(int t=0;t<N1;t++)
  {
    float val=data_a.get(t);
    if(val>Max) Max=val;
    if(val<Min) Min=val;
  }
  
  for(int t=0;t<N2;t++)
  {
    float val=data_b.get(t);
    if(val>Max) Max=val;
    if(val<Min) Min=val;
  }
  
  for(int t=0;t<N3;t++)
  {
    float val=data_c.get(t);
    if(val>Max) Max=val; 
    if(val<Min) Min=val;
  }
  
  if(logaritm)
  {
    gMax=(float)Math.log10(Max+1); //+1 to takie oszustwo 
    gMin=(float)Math.log10(Min+1); //żeby 0 nie wywalało obliczeń
  }
  else
  {
    gMax=Max;
    gMin=Min;
  }
  
  // Właściwe rysowanie
  float wid=lenght/max(N1,N2,N3); //Najdłuższy decyduje
  float oldy=-Float.MIN_VALUE;
  stroke(color_a); //fill(color_a);
  for(int t=0;t<N1;t++)
  {
    float val=data_a.get(t);
    
    if(logaritm)
      val=map((float)Math.log10(val+1),gMin,gMax,0,height);    
    else 
      val=map(val,gMin,gMax,0,height);
    
    float x=t*wid;
    if(oldy!=-Float.MIN_VALUE)
      line (startX+x-wid,startY-oldy,startX+x,startY-val);
    else
      point(startX+x,startY-val);
    
    oldy=val;
  }

  oldy=-Float.MIN_VALUE;
  stroke(color_b); //fill(color_b);
  for(int t=0;t<N2;t++)
  {
    float val=data_b.get(t);
    
    if(logaritm)
      val=map((float)Math.log10(val+1),gMin,gMax,0,height);    
    else 
      val=map(val,gMin,gMax,0,height);
    
    float x=t*wid;
    if(oldy!=-Float.MIN_VALUE)
      dottedLine(startX+x-wid,startY-oldy,startX+x,startY-val,2);
    else
      point(startX+x,startY-val);
    
    oldy=val;
  }
  
  oldy=-Float.MIN_VALUE;
  stroke(color_c); //fill(color_c);
  for(int t=0;t<N3;t++)
  {
    float val=data_c.get(t);
    
    if(logaritm)
      val=map((float)Math.log10(val+1),gMin,gMax,0,height);    
    else 
      val=map(val,gMin,gMax,0,height);
    
    float x=t*wid;
    if(oldy!=-Float.MIN_VALUE)
      dottedLine(startX+x-wid,startY-oldy,startX+x,startY-val,3);
    else
      point(startX+x,startY-val);
    
    oldy=val;
  }
  
  // Min i max są wspólne
  textAlign(LEFT,BOTTOM);
  text(""+Max,startX,startY-height); //Na osi X
  text(""+Min,startX,startY); //Na osi X
}

/// https://processing.org/discourse/beta/num_1219255354.html
void dottedLine(float x1, float y1, float x2, float y2, float steps) ///< Potrzebna do wizualizacji
{
 for(int i=0; i<=steps; i++) {
   float x = lerp(x1, x2, i/steps); //funkcja lerp jest bardzo uzyteczna :-)
   float y = lerp(y1, y2, i/steps);
   //noStroke();ellipse(x, y,2,2); //Używanie elipsy zamiast punktu nie jest zbyt wydajne ;-)
   point(x,y);
 }
} 

//*//////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - TOOLS
//*//////////////////////////////////////////////////////////////////////////////////////////////////////
