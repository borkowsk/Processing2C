/// @file
/// Test dla problemu z użyciem "this" jako parametru funkcji oczekujących Processing::ptr<...>
/// @date 2024-09-30 (last change)
/// To powoduje GPF bo tworzy się nowy _shared_ptr<...> nie powiązany z tym trzymającym obiekt! 
//*//////////////////////////////////////////////////////////////////////////////////////////////

///Info: klasa testowa.
class C: public virtual Object{
  public:
  C(int ii){ i=ii;}
  int i;
  void call_inside(String msg)
  {
     call_outside(SAFE_THIS,msg);    
  }
};

int y=0; ///< Globalna zmienna powinna mieć w C++ deklaracje zapowiadającą.

void call_outside(pC obj,String msg) ///< dla C++ musi być deklaracja zapowiadająca.
{
  println(msg,obj->i);
  text(msg+String(" ")+obj->i,0,y+=16);
}

void processing_window::setup()
{
  size(200,200); //Musi być bo używamy funkcji graficznej (`text` )
  pC c=new C(5);
  c->call_inside("First time");
  c->i=10;
  c->call_inside("Second time");
  c->i=20;
  c->call_inside("Third time");
  saveFrame();
}

//NOTE! ../../scripts did it 2024-09-30 17:06:18

