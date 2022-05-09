//Processing to C++ converter /data/wb/SCC/public/Processing2C/scripts/procesing2cpp.sh
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

/// ABM model of segregation (test project for Processing2C)
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: ModelVisualisation->pde
/////////////////////////////////////////////////////////////////////////////////////////
// World full of agents need method of visualisation on screen/window
////////////////////////////////////////////////////////////////////////////

void visualizeAgents(smatrix<pAgent> agents) { ///
  pAgent curra;
  for(int a=0;a<agents->length;a++)
   for(int b=0;b<agents[a]->length;b++)
   {
      //Background
      noStroke();fill(200Lepiej dopasowa tło
      rect(b*cwidth,a*cwidth,cwidth,cwidtha is vertical!
      
      //Colorisation of agent
      if( (curra=agents[a][b]) != nullptr )
      {
        if(curra->stress>0)
          stroke(curra->stress*255,0,curra->stress*255);
        else
          noStroke();
           
        float forFill=(curra->identity*255.0Number_of_identities;
        fill(forFill,forFill,0);
        ellipse(b*cwidth,a*cwidth,cwidth,cwidth);
      }  
   }
}
//OR
void visualizeAgents(sarray<pAgent> agents) { ///
   pAgent curra;
   for(int a=0;a<agents->length;a++)
   {
    //Colorisation    
    if( (curra=agents[a]) != nullptr )
    {
        if(curra->stress>0)
          stroke(curra->stress*255,0,curra->stress*255);
        else
          noStroke();
           
        float forFill=(curra->identity*255.0Number_of_identities;
        fill(forFill,forFill,0);
    }
    else
    {
      noStroke();
      fill(128);
    }
    
    int t=(StepCounter/STEPSperVIS)%sideUwzględniamy różne częstości wizualizacji
    rect(a*cwidth,t*cwidth,cwidth,cwidth);
    stroke(255);
    line(0,(t+1)*cwidth+1,width,(t+1)*cwidth+1);
   }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: BASIC VISUALISATION
////////////////////////////////////////////////////////////////////////////////////////////////////////
///data/wb/SCC/public/Processing2C/scripts did it

