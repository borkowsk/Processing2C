/// @file
/// @note Automatically made from _SYNCHRONIC1.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
/// @date 2024-10-15 16:11:05 (translation)
//
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
#ifndef _NO_INLINE
#include "processing_inlines.hpp" //...is optional.
#endif // _NO_INLINE
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

/// @file
/// Simple model of synchronization of couple, also class usage demonstration. (test project for Processing2C)
/// @date 2024-09-30 (last change)
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// @note Comments from lecture/Komentarze są notatkami z wykładu: Małgorzata Filon
/// ORIGINAL FILE: "synchronizacja1.pde" -> "SYNCHRONIC1->pde"
//*////////////////////////////////////////////////////////////////////////////////

#include "singiel_class.pde.hpp"

/// Potrzebna będzie wartość współczynnika spięcia, czyli synchronizacji systemów w klasach `singiel`:
const float DefaultAlfa=0.25;

int     Rozbieg=100;   //!< Ile kroków traktujemy jako rozbieg do zsynchronizowania

// Zdefiniowaliśmy klasę, teraz jej użyjemy.
psingiel First, Second; //!< Te nazwy to tylko uchwyty do obiektów, coś jak zwykła liczba `float` czy `integer`,
                       //!< ale to ze je zadeklarujemy nie oznacza ze istnieją te obiekty.
                       //!< Obiekty powstaną dalej za pomocą `new`, wiec za te dopiero uchwycą to co powstanie.
int Ws=400;

void processing_window::setup()
{
  size(1200,400);
  setFrameRate(300);
 // `First=new singiel()` // Tak tworzymy nowy obiekt, będzie typu "singiel". Używamy konstruktor singiel:
 First=new singiel(random(1.0), 3.5+random(0.5), DefaultAlfa);  // 3,5 do 5 bo patrzymy na synchronizacje w chaosie, wtedy jest najciekawsza
 Second=new singiel(random(1.0), 3.5+random(0.5), DefaultAlfa); // dwa systemy od siebie niezależne, wpływając na alfa możemy zwiększać ich wzajemna synchronizacje
 
 println("1st:",First->x1+
         String(" ")+First->r+
         String(" alfa:")+First->sync); // uchwyt do obiektu, robi za nazwę obiektu, kropka i nazwa pola wiec czytamy z pola (lub można też z funkcją)
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
    line(N-1,scaleY(First->x1),N,scaleY(First->x2)); //musimy napisac z ktorego obiektu bierzemy x1,x2
    
    
    stroke(0,0,Blu,25);
    line(N-1,scaleY(Second->x1),N,scaleY(Second->x2));
    
    stroke(0,Grn,0);
    point(N,scaleY(std::abs(First->x2-Second->x2)));
    point(2*Ws+First->x2*Ws,scaleY(Second->x2));
    
    if(N>Rozbieg) //to wyrzucić to będzie widać dojście do atraktora
    {
       stroke(0);
       ellipse(2*Ws+First->x2*Ws,scaleY(Second->x2),4.0,4.0);
    }
    
    N++; // tu kończymy dany krok
  }
  else
  {
    N=0; //Wystarczająco dużo już było, restartujemy systemy
    println("realFM:",frameRate,
            "\tX=",First->x1,Second->x2);
    First->x2=random(1.0);
    Second->x2=random(1.0);
    Grn=100+random(155);Blu=100+random(155);Red=100+random(155);
  }

}

//MADE NOTE: ../../scripts did it 2024-10-15 16:11:05 !

const char* Processing::_PROGRAMNAME="SYNCHRONIC1";
