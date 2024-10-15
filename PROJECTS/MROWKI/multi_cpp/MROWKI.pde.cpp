/// @file
/// @note Automatically made from _MROWKI.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
/// @date 2024-10-15 16:11:04 (translation)
//
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
#ifndef _NO_INLINE
#include "processing_inlines.hpp" //...is optional.
#endif // _NO_INLINE
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_files.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

/// @file
/// Agent Base Model of ant foraging adopted for Processing2C.
/// ORIGINAL FILE: "MRÓWKI.pde"
/// @author: Zofia Cieślińska
/// @date 2024-09-30 (last change)
//*///////////////////////////////////////////

//++++++++++++ ZMIENNE ++++++++++++

//świat
PrintWriter output;     ///< Globalny output
PrintWriter stan;       ///< stany
pWorld world;            ///< ŚWIAT MRÓWEK

int ws = 10;            ///< ???
int sizew = 900;        ///< ???

//mrówka
float ts = 0.5;         ///< wzmocnienie szlaku po zebraniu jedzenia
int memo = 10;          ///< długość pamięci
float distrail = 0.1;   ///< osłabienie szlaku, gdy nie ma jedzenia
float pLosowe = 0.01;   ///< prawdopodobieństwo odejścia od reguł, w klasieWorld

//tło
float disp = 0.01;      ///< tempo zanikania szlaku 
float pe = 0.1;         ///< normalne p przejścia, niby 0.125, bo 8 dróg, ale nie
int ileje = 80;         ///< ile jest maksymalnie jedzenia na miejscu jedzenia
float quiet = 0.5;      ///< tempo uciszania dźwięku

//manipulowalne
bool    may_vibrate;    ///< Globalna zmienna nie może nazywać się tak jak lokalne metody
bool    szlak;          ///< ???
bool    pamiec;         ///< ???
bool    losowo;         ///< ???
int ileSymulacji = 2;   ///< ???


//++++++++++++ ZBIERANIE DANYCH ++++++++++++

void processing_window::setup() {
  size(900, 900);
  setFrameRate(2000); //Maximize speed
  output = createWriter("Symulacja kolejna.txt");
  inicjacja();
  pomocPetli();
  petla();
}

int iteracja;          ///< ???
int dra = 0;           ///< ???
int lpsym = 1;         ///< do nazewnictwa.

void processing_window::draw() {
  if (foodSupply<400) {  //dra - ile razy wykona tę samą symulację
    if (world->antsOut<ileWsumieMrowek) world->whoLetTheAntsOut(); 
    //do pewnego poziomu wypuszcza nowe

    world->antsMove();
    iteracja++;
    
    if (iteracja%50==0) {
      world->drawWorld();
    }
    
    if(iteracja%50==0)
          println("\nStep:",iteracja,"Frame:",frameCount,"Frame rate:",frameRate);
    
  } else {  //po osiągnięciu pewnego poziomu jedzenia spisuje dane
    println(output,dra + String(" \t ") + iteracja + String(" \t ") + world->ileMrowekNiosloCokolwiek());
    output->flush(); 
    print("Koniec!");
    dra++;  //zmienia nazwę nowego i znowu inicjuje świat
    if (dra<ileSymulacji) {
      inicjacja();
    } else {
      noLoop();
      petla();
    }
  }
}

void inicjacja()  ///< Funkcja wymagająca w C++ deklaracji zapowiadającej.
{
  foodSupply = 0;
  iteracja = 0;
  world = new World();
  world->initWorld();
}




//++++++++++++ FUNKCJE DO SPRAWNEGO SYMULOWANIA ++++++++++++

smatrix<bool   > permutacje = new matrix<bool   >(16,4);
sarray<bool   > doIteracji = new array<bool   >(2);
int pet = 0;

void pomocPetli() { ///< Funkcja wymagająca deklaracji zapowiadającej
  doIteracji[0]=false;
  doIteracji[1]=true;
  for (int d=2; d>0; d--) {
    for (int a=2; a>0; a--) {
      for (int b=2; b>0; b--) {
        for (int c=2; c>0; c--) {
          permutacje[pet][0] = doIteracji[a-1];
          permutacje[pet][1] = doIteracji[b-1];
          permutacje[pet][2] = doIteracji[c-1];
          permutacje[pet][3] = doIteracji[d-1];
          pet++;
        }
      }
    }
  }
  pet = 0;
}

void petla() { ///< Funkcja wymagająca deklaracji zapowiadającej
  may_vibrate = permutacje[pet][0]; //Tu się wywala po wydrukowaniu KONIEC!
  szlak = permutacje[pet][1];
  pamiec = permutacje[pet][2];
  losowo = permutacje[pet][3];
  println(output,lpsym+String(") Kod symulacji: wspl ")+ int(may_vibrate)+int(szlak)+int(pamiec)+int(losowo)); //? czy z tego nie wyjdzie liczba zamiast ciągu zer i jedynej? TODO check it!
  println(output,"lp\tczas\tpracowało"); //Usuwamy zbędne konkatenacje!
  lpsym++;
  pet++;
  if (pet<=16) {
    dra = 0;
    inicjacja();
    loop();
  }
}
//MADE NOTE: ../../scripts did it 2024-10-15 16:11:04 !

const char* Processing::_PROGRAMNAME="MROWKI";
