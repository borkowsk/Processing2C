//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: SYNCHRONIC1.pde
#include "processing_templates.hpp"
//#include "processing_inlines.hpp" //is optional. Use when project is already compilable
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

/// Simple model of synchronization of couple (test project for Processing2C)
/// Also class demonstration
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// Comments from lecture: Małgorzata Filon
/// ORIGINAL FILE: synchronizacja1->pde -> SYNCHRONIC1->pde
//////////////////////////////////////////////////////////////////////////////////

class singiel: public virtual Object{
  public: //typ złożony
  //pola obiektu czyli dane 
  float x1,x2;
  float r;// wspolczynik kontroli
  float alfa; //jedno z pól, zależne do czego używamy obiektu, tu wartośc sychronizacji
  
  //metody   kazda klasa ma jedna metode ktora nazywa sie jak nazwa klasy
  singiel(float iX,float iR,float iAlfa)// konstruktor nie ma wart zwracanej, nadaje stan obiektowi, 
  {                                     // wszystkie pola musza miec wartosc nie przypadkową
    x1=x2=iX; r=iR; alfa=iAlfa;
  }
  //zwykła metoda, czyli zmienia wart przynajmniej jednego pola
  void next()
  {
    x1=x2;
    x2=x1*r*(1-x1);
  }
};

//zdefiniowaliśmy klasę, teraz jej użyjemy, wspólczynnik spięcia, synchronizacji
const  float DefaultAlfa=0.0;
int Rozbieg=100;
psingiel First, Second;// uchwyty do obiektow, zwykla liczbe float czy intriger, to ze je zadeklarujemy nie oznacza ze istnieja. obiekty powstana dalej, wiec ten uchwyci ta co powstanie, wiecej niz jeden moze chwytac
int Ws=400;

void processing_window::setup()
{
  size(1200,400);
  setFrameRate(300);
 // First=new singlel // tworzymy nowy obiekt, bedzie typu singiel wpisujem konstrukt singiel
 First=new singiel(random(1.0), 3.5+random(0.5), DefaultAlfa);// 3,5 do 5 bo patrzymy na synchronnizacje w chaosie, wtedy jest najciekawsza
 Second=new singiel(random(1.0), 3.5+random(0.5), DefaultAlfa);//dwaa systey od siebie niezależne, wpływając na alfa możemy zwiekszac ich wzajmna synchronizacje
 
 println("1st:",First->x1+
         String(" ")+First->r+
         String(" alfa:")+First->alfa);//uchwyt do biektu, robi za nazwe obiektu, kropka i nazwa pola wiec czytamy nazew pola lub mozna z funkcja
 println("2st:",Second->x1+
         String(" ")+Second->r+
         String(" alfa:")+Second->alfa);
}

int N=0;

float G=0;
float B=255;
float Red=255;

float scaleY(double X)
{
  return Ws-(float)X*Ws;
}

void processing_window::draw()///
{
  First->next();
  Second->next();
  println("1st:",First->x1,
          "\t2nd:",Second->x1);
  if(N<2*Ws)
  {
    stroke(Red,0,0,25);
    line(N-1,scaleY(First->x1),N,scaleY(First->x2));//musimy napisac z ktorego obiektu bierzemy x1,x2
    
    stroke(Red,0,0,25);
    line(N-1,scaleY(Second->x1),N,scaleY(Second->x2));
    stroke(0,0,25);
  
    point(N,scaleY(abs(First->x2-Second->x2)));
    point(2*Ws+First->x2*Ws,scaleY(Second->x2));
    
    if(N>Rozbieg)//to wyrzucić to będzie widać dojście do atraktora
    {
       ellipse(2*Ws+First->x2*Ws,scaleY(Second->x2),4.0,4.0);
    }
    
    N++; // tu kończymy wyrzucanie
  }
  else
  {
    N=0;
    println("realFM:",frameRate,
            "\tX=",First->x1,Second->x2);
    First->x2=random(1.0);
    Second->x2=random(1.0);
    G=random(255);B=random(255);Red=random(255);
  }

}
//../../scripts/procesing2cpp.sh did it

