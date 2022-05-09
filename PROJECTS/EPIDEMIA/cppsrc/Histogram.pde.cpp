//Processing to C++ converter /data/wb/SCC/public/Processing2C/scripts/procesing2cpp.sh
//Source: Histogram.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

/// ABM (Agent Base Modeling) minimum template test for Processing2C
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE:aSimpleHistogram->pde
/////////////////////////////////////////////////////////////////////////////////////////
// Bardzo prosty histogram agentów wg jednej właściwości
/////////////////////////////////////////////////////////////////////////////////////////
int Max=0Max wspólny dla całej symulacji

void histogram(smatrix<pAgent> agents,float startx,float starty,float hight) ///Funkcja przechodzi po wszystkich agentach i zlicza wg. klas odpornosci.
{
  int NumOfBaskets=100;
  sarray<int> Basket=new array<int>(NumOfBaskets+1);
  int N=0; //Licznik żywych
  //int Max=0;//Albo Max resetowany dla każdego kroku
  Agent curraPomocniczy uchwyt agenta
  
  //Zliczanie 
  for(int a=0;a<agents->length;a++)
   for(int b=0;b<agents[a]->length;b++)
   {
    //KOLORYZACJA AGENTA
    if( (curra=agents[a][b]) != nullptr 
        && curra->state!=Death //Uwzględniamy zmarłych przy statystyce
    )
    {
      NŻywy
      int cl=round(curra->immunity*NumOfBasketsZ odporniością w klasie "cl"
      Basket[clDoliczamy go
      if(Basket[cl]>Max) Max=Basket[clSprawdzamy czy nie urosło "Max"
    }
   }
   
   //Rysowanie
   stroke(random(255),random(255),random(255));
   for(int i=0;i<=NumOfBaskets;i++)
   {
     float val=Basket[i];
     val/=Max;val*=hight;
     //map(val,0,Max,0,hight);
     line(startx+i,starty,startx+i,starty-val);
   }
   
   //Opis
   fill(random(255),random(255),random(255));
   text(String("N:")+N+String("\nMax:")+Max,startx+NumOfBaskets,starty);
}
///data/wb/SCC/public/Processing2C/scripts did it

