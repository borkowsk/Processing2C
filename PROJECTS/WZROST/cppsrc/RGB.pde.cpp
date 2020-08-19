//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: RGB.pde
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
#include "processing_inlines.hpp" //is optional. Use when project is already compilable
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

//TAKA KLASA
////////////////////////
int RGB_Counter=0;/// Globalny licznik obiektów typu RGB

class RGB {
  public:
  ///Info: obiekt przykładowy z polami Red,Green,Blue
  int R,G,B;
  
  RGB() //Konstruktor
  { 
    R=G=B=0; 
    RGB_Counter++;
  }
  
  void Set(int iR,int iG,int iB) //Setter
  {
    R=iR;G=iG;B=iB;
  }
  
  bool isEmpty()
  {
    return R<=0 && G<=0 && B<=0;
  }
  
  void Visualise(int X,int Y) //Method
  {
    if(!isEmpty()) //<>//
    {
      stroke(R,G,B);
      if(W>1)
      {
        fill(R,G,B);
        rect(X*W,Y*W,W,W);
      }
      else
      point(X,Y);
    }
  }
  
  void finalize() //Finalizer.  Wywoływany przez Javę gdy Garbage collector likwiduje objekt
  {               //Teoretycznie - bo trudno to sprawdzić. http://stackoverflow->com/questions/2506488/when-is-the-finalize-method-called-in-java
    RGB_Counter--;//Wygląda na to że tym programie nie jest wołany nigdy //<>//
    println("-");
    //super->finalize();//Ale na to Processing robi blup...
  }
};
//../../scripts/procesing2cpp.sh did it

