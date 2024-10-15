/// @file
/// @note Automatically made from _THISTEST.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
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
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

/// @file
/// Test dla problemu z użyciem "this" jako parametru funkcji oczekujących `Processing::ptr<...>`.
/// @date 2024-09-30 (last change)
//  PL: BEZ SPECJALNEJ OBSŁUGI to powoduje GPF bo tworzy się nowy `_shared_ptr<...>` nie powiązany 
//      z tym trzymającym obiekt! 
//*//////////////////////////////////////////////////////////////////////////////////////////////

/// Klasa testowa.
#include "C_class.pde.hpp"
   
int y=0; ///< Globalna zmienna powinna mieć w C++ deklaracje zapowiadającą.

void call_outside(pC obj,String msg) ///< dla C++ musi być deklaracja zapowiadająca.
{
  println(msg,obj->i);
  text(msg+String(" ")+obj->i,0,y+=16);
}

void processing_window::setup()
{
  size(200,200);
  pC c=new C(5);
  c->call_inside("First time");
  c->i=10;
  c->call_inside("Second time");
  c->i=20;
  c->call_inside("Third time");
  saveFrame();
}
//MADE NOTE: ../../scripts did it 2024-10-15 16:11:05 !

const char* Processing::_PROGRAMNAME="THISTEST";
