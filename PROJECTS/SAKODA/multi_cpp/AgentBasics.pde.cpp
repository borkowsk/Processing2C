/// @file
/// @note Automatically made from _AgentBasics.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
/// @date 2024-10-15 16:11:04 (translation)
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
/// ORIGINAL FILE: AgentSuplement->pde
/// @date 2024-10-14 (last change)
//*///////////////////////////////////////////////////////////////////////////////////////
/// Agent is a one of two central class of each ABM model.
//*///////////////////////////////////////////////////////////////////////////////////////

#include "Agent_class.pde.hpp"

/// Agents need to be initialised & they need logic of change.
void initializeAgents(smatrix<pAgent> agents) ///< @note Need to be global!
{
   for(int a=0;a<agents->length;a++)
    for(int b=0;b<agents[a]->length;b++)
    if(random(1)<density)
    {
      pAgent curr=new Agent();
      agents[a][b]=curr;
    }
}
//OR
/// Agents need to be initialised & they need logic of change.
void initializeAgents(sarray<pAgent> agents) ///< @note Need to be global!
{ 
  for(int a=0;a<agents->length;a++)
  if(random(1)<density)
  {
    pAgent curr=new Agent();
    agents[a]=curr;
  }
}

/// Agents need logic of change.
void  changeAgents(sarray<pAgent> agents) ///< @note Need to be global!
{
  int MC=agents->length;
  for(int i=0;i<MC;i++)
  {
    int a=(int)random(0,agents->length);
    if(agents[a]!= nullptr )
    {
      //Sprawdzenie stresu
      int strangers=0;
      if(0<a-1 && agents[a-1]!=nullptr 
      && agents[a-1]->identity!=agents[a]->identity)
        strangers++;
      if(a+1<agents->length && agents[a+1]!=nullptr 
      && agents[a+1]->identity!=agents[a]->identity)
        strangers++;  
      agents[a]->stress=strangers/2.0;  
      
      //Próba migracji gdy stres doskwiera
      if(agents[a]->stress>0 
      && random(1)<agents[a]->stress)
      {
        int target=(int)random(0,agents->length);
        if(agents[target]==nullptr) //Jest miejsce
        {
          agents[target]=agents[a]; //Przeprowadzka
          agents[a]=nullptr; //Wymeldowanie ze starego miejsca
        }
      }
    }
  }  
}
//OR
/// Agents need logic of change.
void  changeAgents(smatrix<pAgent> agents) ///< @note Need to be global!
{
  int MC=agents->length*agents[0]->length;
  for(int i=0;i<MC;i++)
  {
    int a=(int)random(0,agents->length);
    int b=(int)random(0,agents[a]->length);
    if(agents[a][b]!= nullptr )
    {
      // Sprawdzenie stresu
      int strangers=0;
      if(0<a-1 && agents[a-1][b]!=nullptr 
      && agents[a-1][b]->identity!=agents[a][b]->identity)
        strangers++;
        
      if(a+1<agents->length && agents[a+1][b]!=nullptr 
      && agents[a+1][b]->identity!=agents[a][b]->identity)
        strangers++;  
        
      if(0<b-1 && agents[a][b-1]!=nullptr 
      && agents[a][b-1]->identity!=agents[a][b]->identity)
        strangers++;
        
      if(b+1<agents->length && agents[a][b+1]!=nullptr 
      && agents[a][b+1]->identity!=agents[a][b]->identity)
        strangers++;  
      
      agents[a][b]->stress=strangers/4.0;  
      
      // Próba migracji gdy stres doskwiera
      if(agents[a][b]->stress>0 
      && random(1)<agents[a][b]->stress)
      {
        int tara=(int)random(0,agents->length);
        int tarb=(int)random(0,agents[a]->length);
        
        if(agents[tara][tarb]==nullptr) //Jest miejsce
        {
          agents[tara][tarb]=agents[a][b]; //Przeprowadzka
          agents[a][b]=nullptr; //Wymeldowanie ze starego miejsca
        }
      }
    }
  }
}

//*//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: BASIC INITIALISATION & EVERY STEP CHANGE
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
//*//////////////////////////////////////////////////////////////////////////////////////////////////////////
//MADE NOTE: ../../scripts did it 2024-10-15 16:11:04 !

