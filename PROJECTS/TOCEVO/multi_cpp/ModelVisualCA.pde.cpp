/// @file
/// @note Automatically made from _ModelVisualCA.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
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
#include "processing_files.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

// @date 2024-09-30 (last modification)
/// A world full of cells needs method of visualisation on screen/window.
//*//////////////////////////////////////////////////////////////////////

void visualizeCells(smatrix<int> cells)  ///< Need to be global!
{
  double maximum=std::log10(MAX_INT);
  for(int a=0;a<cells->length;a++)
   for(int b=0;b<cells[a]->length;b++)
   {
      // Colorisation
      double val=std::log10(cells[a][b]);
      
      fill(0,(int)(val/maximum*255),0);
    
      rect(b*cwidth,a*cwidth,cwidth,cwidth); //'a' is vertical!
   }
}

//*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - CA: BASIC VISUALISATION of CELLS FOR TragedyOfCommons
//*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MADE NOTE: ../../scripts did it 2024-10-15 16:11:05 !

