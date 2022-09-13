//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: ModelVisual.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

///   World full of agents need method of visualisation on screen/window
//*//////////////////////////////////////////////////////////////////////////

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
//../../scripts did it

