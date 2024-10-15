/// @file
/// Test dla problemu z użyciem "this" jako parametru funkcji oczekujących `Processing::ptr<...>`.
/// @date 2024-10-15 (last change)
//  PL: BEZ SPECJALNEJ OBSŁUGI to powoduje GPF bo tworzy się nowy `_shared_ptr<...>` nie powiązany 
//      z tym trzymającym obiekt! 
//*//////////////////////////////////////////////////////////////////////////////////////////////

/// Klasa testowa.
class C {
  C(int ii){ i=ii;}
  int i;
  /// Metoda ma dostęp do `this`.
  void call_inside(String msg)
  {
     call_outside(this,msg);    /// @internal Wołanie mietody zewnętrznej, która wymaga podania `this`.
  }
};
   
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
