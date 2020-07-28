//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: RGB.pde
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

//TAKA KLASA
////////////////////////
class RGB
{
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
  
  void constize() //Finalizer.  Wywoływany przez Javę gdy Garbage collector likwiduje objekt
  {               //Teoretycznie - bo trudno to sprawdzić. http://stackoverflow.com/questions/2506488/when-is-the-constize-method-called-in-java
    RGB_Counter--; //<>//
    println("-");
    //super.constize();//Ale na to Processing robi blup...
  }
}

int RGB_Counter=0;//../../scripts/procesing2cpp.sh did it

