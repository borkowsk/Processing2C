//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: WZROST.pde
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
#include "processing_inlines.hpp" //is optional. Use when project is already compilable
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

//Wzrost losowo z punktu środkowego z mutacjami kolorów
//////////////////////////////////////////////////////////////////////////////////
//uzywamy KLASY zdefiniowanej przez użytkownika o nazwie RGB

//Parametry modelu  
int JUMP=3;//skok pozycji "zarodnika". Nieparzysty!
int CJUMP=9;//skok koloru. Tez lepiej nieparzysty.
int STARTG=128;//W jakiej szarości pierwsza komórka
bool ScreenDumps=true; //Zrzucanie obrazków co krok wcale
int VIS_FRQ=10; //co ile kroków zrzut ekranu

//Ważne globalne zmienne, ale inicjowane w setup()
int Side;  /// Bok macieży
int W;     /// Mnożnik dla kwadracika
smatrix<pRGB>    World;//TABLICA - NAWIASY MUSZĄ BYĆ PRZY TYPIE

PrintWriter output;//A tu używamy KLASY zdefiniowanej w bibliotece

void processing_window::setup() //Window and model initialization
{
  size(900,900);
  W=2;
  Side=900/2;

  World = new matrix<pRGB>(Side,Side); //<>//
  World[Side/2][Side/2]= new RGB();

  World[Side/2][Side/2]->Set(STARTG,STARTG,STARTG);//Inicjalize 
  World[Side/2][Side/2]->Visualise(Side/2,Side/2);

  output = createWriter("Statistics.log"); // Create a new file in the sketch directory
  println(output,"Step\tCounter");

  noSmooth(); //Fast visualization
  setFrameRate(30); //maximize speed
}

int Step=0;
bool Stop=false;
void processing_window::draw()
//Monte Carlo Step
{
  //Zapis tego co jest
  println(output, Step + String("\t") + RGB_Counter); // Write the statistics to the file
  output->flush();//Upewnij się że bufor "poszedł na dysk"
  
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
            World[Yt][Xt]=new RGB();
            int nR=World[Y][X]->R+int(random(CJUMP))-CJUMP/2;
            if(nR<0) nR=0; else if(nR>255) nR=255;
            
            int nG=World[Y][X]->G+int(random(CJUMP))-CJUMP/2;
            if(nG<0) nG=0; else if(nG>255) nG=255;
            
            int nB=World[Y][X]->B+int(random(CJUMP))-CJUMP/2;
            if(nB<0) nB=0; else if(nB>255) nB=255;
            
            World[Yt][Xt]->Set(nR,nG,nB);
            World[Yt][Xt]->Visualise(Xt,Yt);
            
            if(Xt==0 || Yt==0)//Doszło do brzegu z jednej z dwu stron - a rośnie w zasadzie symetrycznie
                  Stop=true; 
          }  
      }
    }
      
    if(ScreenDumps && Step % VIS_FRQ == 0)//Zrzucanie obrazków co VIS_FRQ krok lub wcale
    //if(ScreenDumps) //Zrzucanie obrazków co krok lub wcale
    {
       //saveFrame(String("wzrost_step")+Step+ String(".png"));//Wersja z niewygodną numeracją
       //saveFrame(String("wzrost_")+ String("f########.png"));//Wersja z numeracją ramek - będzie też zrzucać kolejne ramki jak właściwa symulacja stanie
       String sc = nf(Step, 8);//Jawne użycie KLASY String oraz funkcji formatującej numery (nUMBER fORMAT)
       String name= String("wzrost_step") + sc + String(".png");
       println(name);
       saveFrame(name);//Wersja z wygodną numeracją nazw plików
    }
    
    Step++;
  }
}
//../../scripts/procesing2cpp.sh did it

