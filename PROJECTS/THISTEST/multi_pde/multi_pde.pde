/// @file
/// Test dla problemu z użyciem "this" jako parametru funkcji oczekujących `Processing::ptr<...>`.
/// @date 2024-09-30 (last change)
//  PL: BEZ SPECJALNEJ OBSŁUGI to powoduje GPF bo tworzy się nowy `_shared_ptr<...>` nie powiązany 
//      z tym trzymającym obiekt! 
//*//////////////////////////////////////////////////////////////////////////////////////////////

/// Klasa testowa.
/*_import_class:C */
   
int y=0; ///< Globalna zmienna powinna mieć w C++ deklaracje zapowiadającą.

void call_outside(C obj,String msg) ///< dla C++ musi być deklaracja zapowiadająca.
{
  println(msg,obj.i);
  text(msg+" "+obj.i,0,y+=16);
}

void setup()
{
  size(200,200);
  C c=new C(5);
  c.call_inside("First time");
  c.i=10;
  c.call_inside("Second time");
  c.i=20;
  c.call_inside("Third time");
  saveFrame();
}
// multi_pde.pde
String PROJECT_NAME="THISTEST";

