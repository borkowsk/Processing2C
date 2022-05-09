//Processing to C++ converter /data/wb/SCC/public/Processing2C/scripts/procesing2cpp.sh
//Source: THISTEST.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "processing_string.hpp"  //Processing::String class
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

/// Test dla problemu z użyciem "this" jako parametru funkcji oczekujących Processing::ptr<...>
/// To powoduje GPF bo tworzy się nowy _shared_ptr<...> nie powiązany z tym trzymającym obiekt! 
//*//////////////////////////////////////////////////////////////////////////////////////////////

///Info: klasa testowa
class C: public virtual Object{
  public:
  C(int ii){
	 i=ii;
	}
  int i;
  void call_inside(String msg)
  {
     call_outside(SAFE_THIS,msg);    
  }
};

int y=0; ///< Globalna zmienna powinna mieć w C++ deklaracje zapowiadającą

void call_outside(pC obj,String msg) ///< dla C++ musi być deklaracja zapowiadająca
{
  println(msg,obj->i);
  text(msg+String(" ")+obj->i,0,y+=16);
}

void processing_window::setup()
{
  size(200,200); //Musi być bo pośrednio używamy w setupie funkcji graficznych (text)
  pC c=new C(5);
  c->call_inside("First time");
  c->i=10;
  c->call_inside("Second time");
  c->i=20;
  c->call_inside("Third time");
  saveFrame();
}

///data/wb/SCC/public/Processing2C/scripts did it

