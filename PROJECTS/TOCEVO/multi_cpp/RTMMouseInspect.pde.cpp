/// @file
/// @note Automatically made from _RTMMouseInspect.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
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

// @date 2024-09-30 (last modification)
// Obsługa wyszukiwania obiektu po kliknięciu myszy:
//*///////////////////////////////////////////////////

#include "Agent_class.pde.hpp"
#include "World_class.pde.hpp"

int searchedX=-1;       ///<???
int searchedY=-1;       ///<???
bool    Clicked=false;  ///<???
int selectedX=-1;       ///<???
int selectedY=-1;       ///<???
pAgent selected=nullptr;    ///<???

//double minDist2Selec=MAX_INT; ///???
//double maxTransSelec=-MAX_INT; ///???

/// Simple version of Pair returning a pair of Int.
#include "MousePairOfInt_class.pde.hpp"


pMousePairOfInt findCell(smatrix<pAgent> agents) ///< Używamy globalnych zmiennych mouseX i mouseY dla szybkości.
{ // Przeliczanie współrzędnych myszy na współrzędne komórki 
  // Parametr jest tylko do sprawdzenie typu i ROZMIARÓW
  // Działa o tyle o ile wizualizacja komórek startuje w punkcie 0,0
  int x=mouseX/cwidth;
  int y=mouseY/cwidth;
  if(0<=y && y<agents->length
  && 0<=x && x<agents[y]->length)
      return new MousePairOfInt(x,y);
  else
      return nullptr;
}

/// Support for searching for an object on mouse click.
void processing_window::onMouseClicked()
{
  println("Mouse clicked at ",mouseX,mouseY); //DEBUG
  Clicked=true;
  searchedX=mouseX;
  searchedY=mouseY; 
  
  pMousePairOfInt result=findCell(TheWorld->agents); //But 1D searching is belong to you!
  if(result!=nullptr) //Znaleziono
  {
    selectedX=result->a;
    selectedY=result->b;
    if((selected=TheWorld->agents[selectedY][selectedX])!=nullptr)
    {
      println("Cell",selectedX,selectedY,"belong to",TheWorld->agents[selectedY][selectedX]);
      println(TheWorld->agents[selectedY][selectedX]->info());
    }
    else
      println("Cell",selectedX,selectedY,"is empty");
  }
}

//*/////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM EVENTS TEMPLATE
//*/////////////////////////////////////////////////////////////////////////////////////////
//MADE NOTE: ../../scripts did it 2024-10-15 16:11:05 !

