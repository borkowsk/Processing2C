/// @file
/// @note Automatically made from _ModelVisual.pde_ by __Processing to C++__ converter (/data/wb/SCC/public/Processing2C/scripts/procesing2cpp.sh).
/// @date 2024-10-14 17:32:20 (translation)
//
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
#ifndef _NO_INLINE
#include "processing_inlines.hpp" //...is optional.
#endif // _NO_INLINE
#include "processing_string.hpp"  //Processing::String class
#include "processing_files.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

/// ABM model of segregation (test project for Processing2C)
/// ORIGINAL FILE: ModelVisualisation->pde
/// @date 2024-09-30 (last change)
//*//////////////////////////////////////////////////////////////////////////
/// World full of agents need method of visualisation on screen/window.
//*//////////////////////////////////////////////////////////////////////////

#include "Agent_class.pde.hpp"
#include "World_class.pde.hpp"

/// @brief Procedure for visualizing a two-dimensional array of agents
void visualizeAgents(smatrix<pAgent> agents) { ///< Need to be global!
  pAgent curra;
  for(int a=0;a<agents->length;a++)
   for(int b=0;b<agents[a]->length;b++)
   {
      // Background
      noStroke();fill(200); // Lepiej dopasowa tło
      rect(b*cwidth,a*cwidth,cwidth,cwidth); //'a' is vertical!
      
      // Colorisation of agent
      if( (curra=agents[a][b]) != nullptr )
      {
        if(curra->stress>0)
          stroke(curra->stress*255,0,curra->stress*255);
        else
          noStroke();
           
        float forFill=(curra->identity*255.0) / Number_of_identities;
        fill(forFill,forFill,0);
        ellipse(b*cwidth,a*cwidth,cwidth,cwidth);
      }  
   }
}
//OR
/// @brief Procedure for visualizing a one-dimensional array of agents
void visualizeAgents(sarray<pAgent> agents) { ///< Need to be global!
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
           
        float forFill=(curra->identity*255.0) / Number_of_identities;
        fill(forFill,forFill,0);
    }
    else
    {
      noStroke();
      fill(128);
    }
    
    int t=(StepCounter/STEPSperVIS)%side; // @internal We take into account different visualization frequencies.
    rect(a*cwidth,t*cwidth,cwidth,cwidth);
    stroke(255);
    line(0,(t+1)*cwidth+1,width,(t+1)*cwidth+1);
   }
}

//*//////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: BASIC VISUALISATION
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
//*//////////////////////////////////////////////////////////////////////////////////////////////////////
//MADE NOTE: /data/wb/SCC/public/Processing2C/scripts did it 2024-10-14 17:32:20 !

