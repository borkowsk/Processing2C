/// @file
/// @note Automatically made from _Histogram.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
/// @date 2024-10-15 16:11:03 (translation)
//
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
#ifndef _NO_INLINE
#include "processing_inlines.hpp" //...is optional.
#endif // _NO_INLINE
#include "processing_string.hpp"  //Processing::String class
#include "processing_lists.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

/// ABM (Agent Base Modeling) minimum template test for Processing2C.
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// @date 2024-09-30 (last change)
/// ORIGINAL FILE:aSimpleHistogram->pde
//*//////////////////////////////////////////////////////////////////////////////////////
/// Bardzo prosty histogram agentów wg jednej właściwości
//*//////////////////////////////////////////////////////////////////////////////////////
int Max=0; //Max wspólny dla całej symulacji

void histogram(smatrix<pAgent> agents,float startx,float starty,float hight) ///Funkcja przechodzi po wszystkich agentach i zlicza wg->klas odpornosci.
{
  int NumOfBaskets=100;
  sarray<int> Basket=new array<int>(NumOfBaskets+1);
  int N=0; //Licznik żywych
  //int Max=0; //Albo Max resetowany dla każdego kroku
  pAgent curra; //Pomocniczy uchwyt agenta
  
  // Zliczanie 
  for(int a=0;a<agents->length;a++)
   for(int b=0;b<agents[a]->length;b++)
   {
    // KOLORYZACJA AGENTA
    if( (curra=agents[a][b]) != nullptr 
        && curra->state!=Death //Uwzględniamy zmarłych przy statystyce
    )
    {
      N++; //Ten jest żywy!
      int cl=round(curra->immunity*NumOfBaskets); //Z odporniością w klasie "cl"
      Basket[cl]++; //Doliczamy go
      if(Basket[cl]>Max) Max=Basket[cl]; //Sprawdzamy czy nie urosło "Max"
    }
   }
   
   // Rysowanie
   stroke(random(255),random(255),random(255));
   for(int i=0;i<=NumOfBaskets;i++)
   {
     float val=Basket[i];
     val/=Max;val*=hight;
     //map(val,0,Max,0,hight);
     line(startx+i,starty,startx+i,starty-val);
   }
   
   // Opis
   fill(random(255),random(255),random(255));
   text(String("N:")+N+String("\nMax:")+Max,startx+NumOfBaskets,starty);
}

//*//////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - TOOLS
//*//////////////////////////////////////////////////////////////////////////////////////////////////////
//MADE NOTE: ../../scripts did it 2024-10-15 16:11:03 !

