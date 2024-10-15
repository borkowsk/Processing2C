/// @file
/// @note Automatically made from _ModelVisual.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
/// @date 2024-10-15 16:11:05 (translation)
//
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
#ifndef _NO_INLINE
#include "processing_inlines.hpp" //...is optional.
#endif // _NO_INLINE
#include "processing_string.hpp"  //Processing::String class
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_files.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

// @date 2024-10-10 (last modification)
/// A world full of agents needs method of visualisation on screen/window.
//*//////////////////////////////////////////////////////////////////////////

#include "Agent_class.pde.hpp"

void visualizeAgents(smatrix<pAgent> agents) ///< Need to be global!
{
  double maxSt=std::pow(maxStock,1/3.0); //println(maxSt);
  pAgent curra;
  
  noStroke();
  for(int a=0;a<agents->length;a++)
   for(int b=0;b<agents[a]->length;b++)
   {
    //Colorisation
    if( (curra=agents[a][b]) != nullptr )
    {
      if(curra->energy>0)
      {
        fill(curra->genEat,0,curra->genPan);
        
        if(curra->punished>0) 
            stroke(255);
        else 
            noStroke();
        
        float radius=(float)(cwidth*(std::pow(min(curra->energy,maxStock),1/3.0) / maxSt));  

        ellipse(b*cwidth+cwidth/2,a*cwidth+cwidth/2,radius,radius); //'a' is vertical! 
      }
      else
      {
        fill(255);stroke(255);
        point(b*cwidth+cwidth/2,a*cwidth-cwidth/2);
        noStroke();
      }  
        
    } 
   }
}

//*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: BASIC VISUALISATION OF agents FOR TragedyOfCommons
//*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MADE NOTE: ../../scripts did it 2024-10-15 16:11:05 !

