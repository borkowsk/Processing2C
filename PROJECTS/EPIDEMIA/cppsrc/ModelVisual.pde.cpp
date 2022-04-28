//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: ModelVisual.pde
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
/// ORIGINAL FILE: ModelVisualisation->pde
/////////////////////////////////////////////////////////////////////////////////////////
// World full of agents need method of visualisation on screen/window
/////////////////////////////////////////////////////////////////////////////////////////

void visualizeAgents(smatrix<pAgent> agents) /// Wizualizacja wszystkich agentów 2D
{
  pAgent curra;
  for(int a=0;a<agents->length;a++)
   for(int b=0;b<agents[a]->length;b++)
   {
    //KOLORYZACJA AGENTA
    if( (curra=agents[a][b]) != nullptr )
    {
      float Green=curra->immunity*255;
      switch(curra->state){ //Instrukcja wyboru pozwala nam wybrać dowolny kolor
      case Recovered:  fill(0,255,0);break;//Wyleczony
      case Infected:   fill(255,Green,0);break;//Zachorował
      case Susceptible:fill(0,Green,255);break;//Podatny
      case Death:      fill(0);break;//Zmarły
      default:         fill(random(255),Green,random(255));//Chory
      break;
      } 
    }
    else
    {
      fill(128);
    }
    
    noStroke();
    rect(b*cwidth,a*cwidth,cwidth,cwidth);//WŁAŚCIWE RYSOWANIE 
   }
}
//OR
void visualizeAgents(sarray<pAgent> agents) /// Wizualizacja wszystkich agentów 2D
{
   pAgent curra;
   for(int a=0;a<agents->length;a++)
   {
    //KOLORYZACJA AGENTA  
    if( (curra=agents[a]) != nullptr )
    {
      switch(curra->state){ //Instrukcja wyboru pozwala nam wybrać dowolny kolor
      case Recovered:  fill(0,255,0);break;//Wyleczony
      case Infected:   fill(255,0,0);break;//Zachorował
      case Susceptible:fill(0,0,255);break;//Podatny
      default:         fill(random(255),0,random(255));//Chory
      break;
      } 
    }
    else
    {
      fill(128);
    }
    
    int t=StepCounter%side;
    noStroke();
    rect(a*cwidth,t*cwidth,cwidth,cwidth);//WŁAŚCIWE RYSOWANIE 
    
    stroke(255);
    line(0,(t+1)*cwidth+1,width,(t+1)*cwidth+1);//LINIA CZASU TERAŹNIEJSZEGO
   }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: BASIC VISUALISATION
////////////////////////////////////////////////////////////////////////////////////////////////////////
//../../scripts did it

