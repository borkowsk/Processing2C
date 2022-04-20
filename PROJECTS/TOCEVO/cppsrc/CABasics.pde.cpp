//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: CABasics.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
//#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_alist.hpp" //...is optional. Should be deleted when not needed.
#include "processing_lists.hpp" //...is optional. Should be deleted when not needed.
#include "processing_map.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_files.hpp" //...is optional. Should be deleted when not needed.
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

//*   Agent is a one of two central class of each ABM model
//*   Agent need to be initialised & they need logic of change 
//*/////////////////////////////////////////////////////////////

void initializeCells(smatrix<int> cells)
{
   for(int a=0;a<cells->length;a++)
    for(int b=0;b<cells[a]->length;b++)
      if(treesDensity>0 && random(1)<treesDensity)
        cells[a][b]=(int)(random(1.0)*random(1.0)*random(1.0)*MAX_INT*random(1.0)*random(1.0)*random(1.0));
      else
        cells[a][b]=0;
   
   if(treesDensity==0) 
       cells[cells->length/2][cells->length/2]=1;
}

//Implement rules
/////////////////////////////////////////////////

void synchChangeCells(smatrix<int> cells,sarray<int>[] newcells)
{
  float R=treesR-1.0;
  int N=cells->length;
  for(int a=0;a<N;a++)
  for(int b=0;b<cells[a]->length;b++)
  {
     int val=cells[a][b];
     
     if(val==0)
     {
       if(treesDensity>0 && random(1.0)<treesDensity)
          val=1;
     }
     else if(val*R<1)
     {
       if(random(1.0)<R) val++;
     }
     else
     {
        val+=(int)(R*val);//Ups, przekraczając max giną :-D (ze starości?)
     }
     
     if(val<0) val=MAX_INT;//Tak już nie giną
     
     newcells[a][b]=val;
  }  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: BASIC INITIALISATION & EVERY STEP CHANGE
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//../../scripts did it

