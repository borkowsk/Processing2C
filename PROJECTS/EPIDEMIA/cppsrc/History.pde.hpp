/// ABM (Agent Base Modeling) minimum template test for Processing2C
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// @date 2024-09-30 (last change)
/// ORIGINAL FILE: aSimpleHistory->pde
//*///////////////////////////////////////////////////////////////////
/// Wykres zmian w czasie
//*///////////////////////////////////////////////////////////////////

//void timeline(pFloatList data,             //dane do wykresu
//              float startX, float startY, //Położenie początku
//              float height,               //wysokość
//              bool    logaritm);          //czy logarytmować dane
              
void timeline(pFloatList data,float startX, float startY, float height,bool    logaritm) /// Dla C++ ta deklaracja musi być umieszczona w HPP
{
  float   Max=-FLT_MAX;
  int     whMax=-1; //Gdzie jest maksimum
  float   Min=FLT_MAX;
  int     whMin=-1; //Gdzie jest minimum
  int     N=data->size(); //Ile pomiarów
  float  lenght=width-startX; //Ile miejsca na wykres
  
  // Szukanie minimum i maksimum
  for(int t=0;t<N;t++)
  {
    float val=data->get(t);
    if(val>Max) {
	 Max=val; whMax=t;
	}
    if(val<Min) {
	 Min=val; whMin=t;
	}
  }
  
  if(logaritm)
  {
    Max=(float)std::log10(Max+1); //+1 to takie oszustwo 
    Min=(float)std::log10(Min+1); //żeby 0 nie wywalało obliczeń
  }
  
  // Właściwe rysowanie
  float wid=lenght/N; //println(width,N,wid,min,max);DEBUG
  float oldy=-FLT_MIN;
  for(int t=0;t<N;t++)
  {
    float val=data->get(t);
    
    if(logaritm)
      val=map((float)std::log10(val+1),Min,Max,0,height);    
    else 
      val=map(val,Min,Max,0,height);
    
    float x=t*wid;
    if(oldy!=-FLT_MIN)
    {
      line (startX+x-wid,startY-oldy,startX+x,startY-val);
    }
    else
      point(startX+x,startY-val);
    
    oldy=val;
    
    if(t==whMax || t==whMin)
    {
      textAlign(LEFT,BOTTOM);
      String out=String("")+data->get(t);
      text(out,startX,startY-val); //Na osi X
      text(out,startX+x,startY-val); //Przy danych
    }
  }
}

/// A jakby miało być więcej zmiennych? UWAGA!:  wspólna skala!!!
/// Wtedy np->tak jak poniżej, co jest wersją bardzo prymitywną, ale będzie działać :-D
void timeline(pFloatList data_a,pFloatList data_b,pFloatList data_c,float startX,float startY,float height,bool    logaritm,color color_a,color color_b,color color_c) /// Dla C++ ta deklaracja musi być umieszczona w HPP
{
  float   Max=-FLT_MAX; //Tu będzie prawdziwa wartość
  float   gMax=0; //A tu przeliczona dla grafiki
  float   Min=FLT_MAX; //J->w.
  float   gMin=0; //Analogicznie j->w.
  int     N1=data_a->size(),N2=data_b->size(),N3=data_c->size(); //Ile pomiarów
  float   lenght=width-startX; //Ile miejsca na wykres
  
  //Szukanie minimum i maksimum
  for(int t=0;t<N1;t++)
  {
    float val=data_a->get(t);
    if(val>Max) Max=val;
    if(val<Min) Min=val;
  }
  
  for(int t=0;t<N2;t++)
  {
    float val=data_b->get(t);
    if(val>Max) Max=val;
    if(val<Min) Min=val;
  }
  
  for(int t=0;t<N3;t++)
  {
    float val=data_c->get(t);
    if(val>Max) Max=val; 
    if(val<Min) Min=val;
  }
  
  if(logaritm)
  {
    gMax=(float)std::log10(Max+1); //+1 to takie oszustwo 
    gMin=(float)std::log10(Min+1); //żeby 0 nie wywalało obliczeń
  }
  else
  {
    gMax=Max;
    gMin=Min;
  }
  
  // Właściwe rysowanie
  float wid=lenght/max(N1,N2,N3); //Najdłuższy decyduje
  float oldy=-FLT_MIN;
  stroke(color_a); //fill(color_a);
  for(int t=0;t<N1;t++)
  {
    float val=data_a->get(t);
    
    if(logaritm)
      val=map((float)std::log10(val+1),gMin,gMax,0,height);    
    else 
      val=map(val,gMin,gMax,0,height);
    
    float x=t*wid;
    if(oldy!=-FLT_MIN)
      line (startX+x-wid,startY-oldy,startX+x,startY-val);
    else
      point(startX+x,startY-val);
    
    oldy=val;
  }

  oldy=-FLT_MIN;
  stroke(color_b); //fill(color_b);
  for(int t=0;t<N2;t++)
  {
    float val=data_b->get(t);
    
    if(logaritm)
      val=map((float)std::log10(val+1),gMin,gMax,0,height);    
    else 
      val=map(val,gMin,gMax,0,height);
    
    float x=t*wid;
    if(oldy!=-FLT_MIN)
      dottedLine(startX+x-wid,startY-oldy,startX+x,startY-val,2);
    else
      point(startX+x,startY-val);
    
    oldy=val;
  }
  
  oldy=-FLT_MIN;
  stroke(color_c); //fill(color_c);
  for(int t=0;t<N3;t++)
  {
    float val=data_c->get(t);
    
    if(logaritm)
      val=map((float)std::log10(val+1),gMin,gMax,0,height);    
    else 
      val=map(val,gMin,gMax,0,height);
    
    float x=t*wid;
    if(oldy!=-FLT_MIN)
      dottedLine(startX+x-wid,startY-oldy,startX+x,startY-val,3);
    else
      point(startX+x,startY-val);
    
    oldy=val;
  }
  
  // Min i max są wspólne
  textAlign(LEFT,BOTTOM);
  text(String("")+Max,startX,startY-height); //Na osi X
  text(String("")+Min,startX,startY); //Na osi X
}

/// https://processing->org/discourse/beta/num_1219255354->html
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
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - TOOLS
//*//////////////////////////////////////////////////////////////////////////////////////////////////////
//NOTE! ../../scripts did it 2024-09-30 17:06:17

