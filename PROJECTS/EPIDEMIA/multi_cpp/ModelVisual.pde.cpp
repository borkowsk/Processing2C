/// @file
/// @note Automatically made from _ModelVisual.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
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

/// ABM (Agent Base Modeling) minimum template test for Processing2C
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// @date 2024-09-30 (last change)
/// ORIGINAL FILE: ModelVisualisation->pde
//*///////////////////////////////////////////////////////////////////////////////////////
/// World full of agents need method of visualisation on screen/window
//*///////////////////////////////////////////////////////////////////////////////////////

void visualizeAgents(smatrix<pAgent> agents) ///< Wizualizacja wszystkich agentów 2D
{
  pAgent curra;
  for(int a=0;a<agents->length;a++)
   for(int b=0;b<agents[a]->length;b++)
   {
    // KOLORYZACJA AGENTA
    if( (curra=agents[a][b]) != nullptr )
    {
      float Green=curra->immunity*255;
      switch(curra->state){ //Instrukcja wyboru pozwala nam wybrać dowolny kolor
      case Recovered:  fill(0,255,0);break; //Wyleczony
      case Infected:   fill(255,Green,0);break; //Zachorował
      case Susceptible:fill(0,Green,255);break; //Podatny
      case Death:      fill(0);break; //Zmarły
      default:         fill(random(255),Green,random(255)); //Chory
      break;
      } 
    }
    else
    {
      fill(128);
    }
    
    noStroke();
    rect(b*cwidth,a*cwidth,cwidth,cwidth); //WŁAŚCIWE RYSOWANIE 
   }
}
//OR
void visualizeAgents(sarray<pAgent> agents) /// Wizualizacja wszystkich agentów 2D
{
   pAgent curra;
   for(int a=0;a<agents->length;a++)
   {
    // KOLORYZACJA AGENTA  
    if( (curra=agents[a]) != nullptr )
    {
      switch(curra->state){ //Instrukcja wyboru pozwala nam wybrać dowolny kolor
      case Recovered:  fill(0,255,0);break; //Wyleczony
      case Infected:   fill(255,0,0);break; //Zachorował
      case Susceptible:fill(0,0,255);break; //Podatny
      default:         fill(random(255),0,random(255)); //Chory
      break;
      } 
    }
    else
    {
      fill(128);
    }
    
    int t=StepCounter%side;
    noStroke();
    rect(a*cwidth,t*cwidth,cwidth,cwidth); //WŁAŚCIWE RYSOWANIE 
    
    stroke(255);
    line(0,(t+1)*cwidth+1,width,(t+1)*cwidth+1); //LINIA CZASU TERAŹNIEJSZEGO
   }
}

//*//////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: BASIC VISUALISATION
//*//////////////////////////////////////////////////////////////////////////////////////////////////////
//MADE NOTE: ../../scripts did it 2024-10-15 16:11:03 !

