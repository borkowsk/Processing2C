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
World world;            ///< ŚWIAT MRÓWEK

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
boolean may_vibrate;    ///< Globalna zmienna nie może nazywać się tak jak lokalne metody
boolean szlak;          ///< ???
boolean pamiec;         ///< ???
boolean losowo;         ///< ???
int ileSymulacji = 2;   ///< ???


//++++++++++++ ZBIERANIE DANYCH ++++++++++++

void setup() {
  size(900, 900);
  frameRate(2000); //Maximize speed
  output = createWriter("Symulacja kolejna.txt");
  inicjacja();
  pomocPetli();
  petla();
}

int iteracja;          ///< ???
int dra = 0;           ///< ???
int lpsym = 1;         ///< do nazewnictwa.

void draw() {
  if (foodSupply<400) {  //dra - ile razy wykona tę samą symulację
    if (world.antsOut<ileWsumieMrowek) world.whoLetTheAntsOut(); 
    //do pewnego poziomu wypuszcza nowe

    world.antsMove();
    iteracja++;
    
    if (iteracja%50==0) {
      world.drawWorld();
    }
    
    if(iteracja%50==0)
          println("\nStep:",iteracja,"Frame:",frameCount,"Frame rate:",frameRate);
    
  } else {  //po osiągnięciu pewnego poziomu jedzenia spisuje dane
    output.println(dra + " \t " + iteracja + " \t " + world.ileMrowekNiosloCokolwiek());
    output.flush(); 
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
  world.initWorld();
}




//++++++++++++ FUNKCJE DO SPRAWNEGO SYMULOWANIA ++++++++++++

boolean[][] permutacje = new boolean[16][4];
boolean[] doIteracji = new boolean[2];
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
  output.println(lpsym+") Kod symulacji: wspl "+ int(may_vibrate)+int(szlak)+int(pamiec)+int(losowo)); //? czy z tego nie wyjdzie liczba zamiast ciągu zer i jedynej? TODO check it!
  output.println("lp\tczas\tpracowało"); //Usuwamy zbędne konkatenacje!
  lpsym++;
  pet++;
  if (pet<=16) {
    dra = 0;
    inicjacja();
    loop();
  }
}
