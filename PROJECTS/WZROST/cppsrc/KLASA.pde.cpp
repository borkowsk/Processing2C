//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: KLASA.pde
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

/// Simple model of colony growth with mutations (test project for Processing2C)
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "klasaRGB.pde"
//////////////////////////////////////////////////////////////////////////////////
// TAKA KLASA PRZYKLADOWA
//////////////////////////////////////////////////////////
int KLASA_Counter=0;/// Globalny licznik obiektów typu RGB

class KLASA: public virtual Object{
  public:
  ///Info: obiekt przykładowy z polami Red,Green,Blue
  int R,G,B;
  
  KLASA() //Konstruktor
  { 
    R=G=B=0; 
    KLASA_Counter++;
  }
  
  void Set(int iR,int iG,int iB) //Setter
  {
    R=iR;G=iG;B=iB;
  }
  
  bool    isEmpty()
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
      {
        stroke(R,G,B);
        point(X,Y);
      }
    }
  }
  
  void finalize() //Finalizer.  Wywoływany przez Javę gdy Garbage collector likwiduje objekt
  {               //Teoretycznie - bo trudno to sprawdzić. http://stackoverflow->com/questions/2506488/when-is-the-finalize-method-called-in-java
    KLASA_Counter--;//Wygląda na to że tym programie nie jest wołany nigdy //<>//
    println("-");
    //super::finalize();//Ale na to Processing robi blup...
  }
};
//../../scripts/procesing2cpp.sh did it

