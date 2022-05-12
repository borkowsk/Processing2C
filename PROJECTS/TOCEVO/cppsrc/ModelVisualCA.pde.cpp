//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: ModelVisualCA.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

//*   World full of cells need method of visualisation on screen/window
//*//////////////////////////////////////////////////////////////////////////

void visualizeCells(smatrix<int> cells)  ///<
{
  double maximum=std::log10(MAX_INT);
  for(int a=0;a<cells->length;a++)
   for(int b=0;b<cells[a]->length;b++)
   {
      //Colorisation
      double val=std::log10(cells[a][b]);
      
      fill(0,(int)(val/maximum*255),0);
    
      rect(b*cwidth,a*cwidth,cwidth,cwidth);//a is vertical!
   }
}

//*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - CA: BASIC VISUALISATION of CELLS FOR TragedyOfCommons
//*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//../../scripts did it

