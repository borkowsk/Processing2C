//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: SYNCHRONIC1.pde
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

/// Simple model of synchronization of couple (test project for Processing2C)
/// Also class demonstration
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// Comments from lecture: Małgorzata Filon
/// ORIGINAL FILE: "synchronizacja1.pde" -> "SYNCHRONIC1.pde"
//////////////////////////////////////////////////////////////////////////////////

class singiel: public virtual Object{
  public: //klasa czyli typ złożony
  //pola obiektu czyli dane 
  float x1,x2;
  float r;// np. wspolczynik kontroli
  float sync; //jedno z pól, zależne do czego używamy obiektu, tu jest to wartośc sychronizacji
  
  //Metody. Kazda klasa ma jedną metodę, ktora nazywa sie jak nazwa klasy
  singiel(float iX,float iR,float iSync)// konstruktor nie ma wart. zwracanej, nadaje stan obiektowi, 
  {                                     // wszystkie pola musza mieć wartość nie przypadkową
    x1=x2=iX; r=iR; sync=iSync;
  }
  
  //zwykła metoda, czyli zmienia wart. przynajmniej jednego pola
  void next()
  {
    x1=x2;
    x2=x1*r*(1-x1);
  }
};

//zdefiniowaliśmy klasę, teraz jej użyjemy. Potrzebna bedzie wartość wspólczynnika spięcia, czyli synchronizacji
const   float DefaultAlfa=0.25;

int     Rozbieg=100;//Ile kroków traktujemy jako rozbieg do zsynchronizowania

psingiel First, Second;//uchwyty do obiektow, coś jak zwykla liczbe float czy intiger, ale to ze je zadeklarujemy nie oznacza ze istnieją obiekty. 
                      //obiekty powstaną dalej, wiec te uchwycą to co powstanie. Wiecej niz jeden może chwytac
int Ws=400;

void processing_window::setup()
{
  size(1200,400);
  setFrameRate(300);
 // First=new singlel // tworzymy nowy obiekt, bedzie typu "singiel". Wpisujemy konstruktor singiel
 First=new singiel(random(1.0), 3.5+random(0.5), DefaultAlfa);// 3,5 do 5 bo patrzymy na synchronizacje w chaosie, wtedy jest najciekawsza
 Second=new singiel(random(1.0), 3.5+random(0.5), DefaultAlfa);//dwa systemy od siebie niezależne, wpływając na alfa możemy zwiekszac ich wzajemna synchronizacje
 
 println("1st:",First->x1+
         String(" ")+First->r+
         String(" alfa:")+First->sync);//uchwyt do biektu, robi za nazwe obiektu, kropka i nazwa pola wiec czytamy z pola (lub mozna też z funkcją)
 println("2st:",Second->x1+
         String(" ")+Second->r+
         String(" alfa:")+Second->sync);
}

int N=0;

float Grn=255;
float Blu=255;
float Red=255;

float scaleY(double X)
{
  return Ws-(float)X*Ws;
}

void processing_window::draw()
{
  First->next();
  Second->next();
  
  //println("1st:",First->x1,
  //        "\t2nd:",Second->x1);
  
  if(N<2*Ws)
  {
    stroke(Red,0,0,25);
    line(N-1,scaleY(First->x1),N,scaleY(First->x2));//musimy napisac z ktorego obiektu bierzemy x1,x2
    
    
    stroke(0,0,Blu,25);
    line(N-1,scaleY(Second->x1),N,scaleY(Second->x2));
    
    stroke(0,Grn,0);
    point(N,scaleY(abs(First->x2-Second->x2)));
    point(2*Ws+First->x2*Ws,scaleY(Second->x2));
    
    if(N>Rozbieg)//to wyrzucić to będzie widać dojście do atraktora
    {
       stroke(0);
       ellipse(2*Ws+First->x2*Ws,scaleY(Second->x2),4.0,4.0);
    }
    
    N++; // tu kończymy dany krok
  }
  else
  {
    N=0;//Wystarczająco dużo już było, restartujemy systemy
    println("realFM:",frameRate,
            "\tX=",First->x1,Second->x2);
    First->x2=random(1.0);
    Second->x2=random(1.0);
    Grn=100+random(155);Blu=100+random(155);Red=100+random(155);
  }

}
//../../scripts/procesing2cpp.sh did it

