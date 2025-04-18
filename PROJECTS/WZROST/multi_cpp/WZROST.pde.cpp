/// @file
/// @note Automatically made from _WZROST.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
/// @date 2024-10-15 16:11:06 (translation)
//
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
#ifndef _NO_INLINE
#include "processing_inlines.hpp" //...is optional.
#endif // _NO_INLINE
#include "processing_string.hpp"  //Processing::String class
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_files.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

/// @file
/// Simple model of colony growth with mutations (test project for Processing2C).
/// @date 2024-09-30 (last modification)
/// TODO Gpf in table in C++ version :-/
/// NOTE We use a user-defined CLASS called "KLASA" ;-)
//*////////////////////////////////////////////////////////////////////////////////

// PL: Wzrost losowo z punktu środkowego z mutacjami kolorów.
//     UWAGA! Używamy KLASY zdefiniowanej przez użytkownika o nazwie "KLASA" ;-)

#include "KLASA_class.pde.hpp"

// Parametry modelu:
//*////////////////
int JUMP=3;                 ///< skok pozycji "zarodnika". Nieparzysty!
int CJUMP=9;                ///< skok koloru->Tez lepiej nieparzysty.
int STARTG=128;             ///< W jakiej szarości pierwsza komórka.
bool    ScreenDumps=false;  ///< Zrzucanie obrazków co krok wcale.
int VIS_FRQ=100;            ///< co ile kroków zrzut ekranu.

// Ważne globalne zmienne, ale inicjowane w funkcji `s e t u p`:
//*/////////////////////////////////////////////////////////////
int          Side;          ///< Bok macierzy.
int          W;             ///< Mnożnik dla kwadracika.
smatrix<pKLASA>    World;         ///< TABLICA OBIEKTÓW - DLA TŁUMACZENIA C++ NAWIASY TABLICY MUSZĄ BYĆ PRZY TYPIE.

PrintWriter output;         ///< A tu używamy innej klasy, zdefiniowanej w bibliotece.

void processing_window::setup() //Window and model initialization
{
  size(900,900);
  W=3;
  Side=900/W;

  World = new matrix<pKLASA>(Side,Side);
  World[Side/2][Side/2]= new KLASA();

  World[Side/2][Side/2]->Set(STARTG,STARTG,STARTG); // Inicjalizacja.
  World[Side/2][Side/2]->Visualise(Side/2,Side/2);
  
  output = createWriter("Statistics.log"); // Create a new file in the sketch directory  
  println(output,"Step\tCounter");
  
  noSmooth(); // Fast visualization
  noStroke();
  setFrameRate(1000); // maximize speed
}

int Step=0;
bool    Stop=false;

/// Monte Carlo Step.
void processing_window::draw()
{
  //Zapis tego co jest
  println(output,Step+String("\t")+KLASA_Counter); // Write the statistics to the file
  output->flush(); //Upewnij się że bufor "poszedł na dysk"
  
  //Nowy stan
  if(!Stop)
  {
    int M=Side*Side;
    
    for(int i=0;i<M;i++)
    {
      int X=int(random(Side));
      int Y=int(random(Side));
      if(World[Y][X]!=nullptr)
      {
         int Xt=X+int(random(JUMP))-JUMP/2;
         int Yt=Y+int(random(JUMP))-JUMP/2;
         
         if(0<=Xt && Xt<Side && 0<=Yt && Yt<Side
            &&  World[Yt][Xt]==nullptr)
          {
            World[Yt][Xt]=new KLASA();
            int nR=World[Y][X]->R+int(random(CJUMP))-CJUMP/2;
            if(nR<0) nR=0; else if(nR>255) nR=255;
            
            int nG=World[Y][X]->G+int(random(CJUMP))-CJUMP/2;
            if(nG<0) nG=0; else if(nG>255) nG=255;
            
            int nB=World[Y][X]->B+int(random(CJUMP))-CJUMP/2;
            if(nB<0) nB=0; else if(nB>255) nB=255;
            
            World[Yt][Xt]->Set(nR,nG,nB);
            World[Yt][Xt]->Visualise(Xt,Yt);
            
            if(Xt==0 || Yt==0) //Doszło do brzegu z jednej z dwu stron - a rośnie w zasadzie symetrycznie
                  Stop=true; 
          }  
      }
    }
      
    if(Step % VIS_FRQ == 0) //Zrzucanie obrazków co VIS_FRQ krok lub wcale
    //if(ScreenDumps) //Zrzucanie obrazków co krok lub wcale
    {
       //saveFrame(String("wzrost_step")+Step+ String(".png")); //Wersja z niewygodną numeracją
       //saveFrame(String("wzrost_")+ String("f########.png")); //Wersja z numeracją ramek - będzie też zrzucać kolejne ramki jak właściwa symulacja stanie
       String sc = nf(Step, 8); //Jawne użycie KLASY String oraz funkcji formatującej numery (nUMBER fORMAT)
       if(ScreenDumps) saveFrame(String("wzrost_step")+sc+ String(".png")); //Wersja z wygodną numeracją
       println("Frame rate:",frameRate);
    }
    
    Step++;
  }
}

//*//////////////////////////////////////////////////////////
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
//*//////////////////////////////////////////////////////////
//MADE NOTE: ../../scripts did it 2024-10-15 16:11:06 !

const char* Processing::_PROGRAMNAME="WZROST";
