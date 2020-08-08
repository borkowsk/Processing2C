//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: klasaWorld.pde
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
//include "processing_inlines.hpp" //is optional. Use when project is already compilable
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

int worozmiar = sizew/ws;  ///ile pól jest na świecie

float density = 0.005;  ///ewentualna gęstośc jedzenia rozłożena

int xNest = int(worozmiar/7);  ///współrzędne gniazda i jego rozmiar
int yNest = int(worozmiar/7);  ///
int siNest = 3;                ///

int foodSupply;  /// początkowa ilość jedzenia w gnieździe
int ileWsumieMrowek = sizew/10;  /// maksymalna dopuszczalna liczba mrówek


class World {
  public:
    sarray<pAnt>    dumm1 { new array<pAnt>(10) };//OK
    //sarray<pAnt>    dummy2 = new array<pAnt>(10); //Compiler error?!?!?!
    smatrix<pAnt>   dummyWorld1 { new matrix<pAnt>(100,100) };//OK
    smatrix<pAnt>   dummyWorld2 = new matrix<pAnt>(100,100);//OK
    smatrix<int>    ants = new matrix<int>(50/*ileWsumieMrowek*/,2);// OK

    //tablica współrzędnych mrówek
    smatrix<pBack> backWorld;
    smatrix<pAnt>  antsWorld
    ;

  World() {  //świat składa się ze środowiska i z mrówek
    backWorld = new matrix<pBack>(worozmiar,worozmiar);
    antsWorld = new matrix<pAnt>(worozmiar,worozmiar);
  }

  //++++++++++++ FUNKCJE GŁÓWNE ++++++++++++

  void initWorld() { //początkowy stan świata
    if (losowo) {
      for (int u=0; u<3; u++) {
        int size = int(random(2, 4));
        int xowa = int(random(worozmiar/5, worozmiar-size));
        int ykowa = int(random(worozmiar/5, worozmiar-size));
        whoLetTheFoodOut(xowa, ykowa, size, 2);
      }
    }
    if (!losowo) {
      whoLetTheFoodOut(int(worozmiar*2/3), int(worozmiar*2/3), 3, 2);
      whoLetTheFoodOut(int(worozmiar/5), int(worozmiar*4/5), 3, 2);
      whoLetTheFoodOut(int(worozmiar*6/9), int(worozmiar*1/8), 3, 2);
    }
    whoLetTheFoodOut(xNest, yNest, siNest, 10); //gniazdo
    whoLetTheAntsOut();  //a z gniazda wychodzą mrówki
    for (int i=0; i<worozmiar; i++) {
      for (int j=0; j<worozmiar; j++) {
        if (backWorld[i][j]==nullptr) backWorld[i][j] = new Back(0);
      }
    }
  }

  int antsOut = 0;  //licznik, ile jest obecnie mrówek
  void whoLetTheAntsOut() {  //funkcja wypuszczająca mrówki z gniazda
    for (int i=xNest; i<=xNest+siNest; i++) {
      for (int j=yNest; j<=yNest+siNest; j++) {
        if (antsOut<ileWsumieMrowek) {  //jest limit na całkowitą liczbę mrówek
          if (antsWorld[i][j]==nullptr) {
            antsWorld[i][j] = new Ant(antsOut, i, j);
            //zapisują się współrzędne mrówki do przypisanego jej miejsca
            ants[antsOut][0] = i;  
            ants[antsOut][1] = j;
            antsOut++;
          }
        }
      }
    }
  }

  void whoLetTheFoodOut(int x, int y, int roz, int id) {
    //funkcja umieszczająca na planszy jedzenie i gniazdo
    for (int i=x; i<=x+roz; i++) {  
      for (int j=y; j<=y+roz; j++) {
        backWorld[i][j] = new Back(id);
      }
    }
  }

  void drawWorld() {
    for (int i=0; i<worozmiar; i++) {
      for (int j=0; j<worozmiar; j++) {
        if (antsWorld[i][j]!=nullptr) { 
          //najważniejsze mrówki 
          fill(antsWorld[i][j]->memory[0][0]*100, 0, 0);
        } else if (backWorld[i][j]->id==10) { 
          //potem gniazdo jest brązowe
          fill(150, 90, 0);
        } else if (backWorld[i][j]->id==2) { 
          //jedzenia jest niebieskie, intensywność zależy od ilośći
          fill(0, 200, backWorld[i][j]->amountFood*70);
        } else if (backWorld[i][j]->sound>0) {
          //wibracja jest czerwona i się wycisza
          fill(200*backWorld[i][j]->sound, 100, 0);    
          backWorld[i][j]->dissound();  
        } else if (backWorld[i][j]->p_follow>pe) {
          //szlak jest żółty, intensywność zależy od ilości
          fill(300*backWorld[i][j]->p_follow, 200, 0);    
          backWorld[i][j]->diss();  //i zanika z czasem
        } else if (backWorld[i][j]->p_follow==pe || antsWorld[i][j]==nullptr) 
          //przestrzeń jest zielona, albo domyślnie, albo gaśnie
          fill(50, 200, 20);

        rect(i*ws, j*ws, worozmiar, worozmiar);  //dyskretny świat
      }
    }
  }

  void antsMove() {
    int N = antsOut;  //chodzimy po dotychczasowych mrówkach
    for (int a=0; a<N*3; a++) {
      int ktora = int(random(N));
      int i = ants[ktora][0];
      int j = ants[ktora][1];

      if (a%12==0) czyOtoczona(i, j);

      sarray<int> ite = {
	i-1, i, i+1
	};
      sarray<int> jte = {
	j-1, j, j+1
	};

      for (int o=0; o<8; o++) {  //idziemy po jej sąsiadach, losowo
        int p=(ite[int(random(3))]+worozmiar)%worozmiar;
        int r=(jte[int(random(3))]+worozmiar)%worozmiar;

        if (czyChce(i, j, p, r)) { //sprawdzamy, czy chce się tam ruszyć  
          if (czyMoze(i, j, p, r)) { //czy może się tam ruszyć
            move(i, j, p, r, ktora);
            break;
          }
        }
      }
    }
  };

  //++++++++++++ FUNKCJE POMOCNICZE ++++++++++++


  bool czyWstroneZpamieci(int i, int j, int p, int r, int mem) { 
    //idzie za danymi współrzędnymi w pamięci
    sarray<int> polePamieci = antsWorld[i][j]->memory[mem];
    p = abs(p - polePamieci[0]);  //zawinięcie w torus
    p = min(p, worozmiar-p);
    i = abs(i - polePamieci[0]);
    i = min(i, worozmiar-i);
    r = abs(r - polePamieci[1]);
    r = min(r, worozmiar-r);
    j = abs(j - polePamieci[1]);
    j = min(j, worozmiar-j);
    return (p<=i && r<=j) || random(1)<pLosowe; 
    //albo bliżej gniazda/jedzenia w którymkolwiek kierunku, albo małe p, że jednak skręci
  }  

  bool czyCosWie(int i, int j) {  //jeżeli wie, że gdzieś jest jedzenie
    return antsWorld[i][j]->memory[1][0]!=antsWorld[i][j]->memory[2][0] 
            || antsWorld[i][j]->memory[1][1]!=antsWorld[i][j]->memory[2][1];
  }  


  bool czyMoze(int i, int j, int p, int r) {//nie może iść na swoje obecne miejsce lub na czyjeś
    return (p!=i || r!=j) && antsWorld[p][r]==nullptr;
  }


  bool czyChce(int i, int j, int p, int r) {  
    if (antsWorld[i][j]->memory[0][0]>0) {  
      //jeżeli już coś zebrała, chce tylko do gniazda
      return czyWstroneZpamieci(i, j, p, r, 1);
    } else if (czyCosWie(i, j)) { 
      //jeżeli nic nie ma, ale wie, gdzie mieć 
      return czyWstroneZpamieci(i, j, p, r, 2);
    } else { 
      return (antsWorld[i][j]->memoryCheck(p, r) && random(1)<backWorld[p][r]->p_follow)  
              || backWorld[p][r]->id==2 || random(1)<pLosowe;
    }
  }


  void move(int i, int j, int p, int r, int ktora) { 
    //funkcja robiąca wszystko, co potrzebne do ruchu
    if (backWorld[p][r]->id==10 && antsWorld[i][j]->memory[0][0]>0) {
      antsWorld[i][j]->ifOnNestLeaveFood(p, r); 
      //jeżeli rusza się na gniazdo, zrzuca tam jedzenie
      print(antsWorld[i][j]->trailS+ String("  "));
    }
    if (p==antsWorld[i][j]->memory[2][0] && r==antsWorld[i][j]->memory[2][1] && backWorld[p][r]->id==0) { 
      //jeżeli rusza się na jedzenie, a go tam nie ma, zapomina
      antsWorld[i][j]->zapominanie();
    }
    if (szlak) { 
      //jeżeli jest taka opcja, to zostawia szlak
      backWorld[i][j]->trail(antsWorld[i][j]->trailS);
    }
    if (backWorld[p][r]->sound>0 && may_vibrate) {  
      //jeżeli jest na wibracji, to wibruje
      antsWorld[i][j]->pamieta(backWorld[p][r]->where[0], backWorld[p][r]->where[1]);
    }
    if (backWorld[p][r]->id==2) {
      //jeżeli ruszyła się na jedzenie, bierze i wibruje
      backWorld[p][r]->takeFood();
      antsWorld[i][j]->takeFood(p, r);
      if (may_vibrate) vibrate(p, r);
    }
    //rusza się, wpisuje to do pamięci i uzupełnia się w tabliczce
    antsWorld[p][r] = antsWorld[i][j];  
    antsWorld[p][r]->memoryUpdate(p, r); 
    antsWorld[p][r]->zanikanie();
    ants[ktora][0] = p;
    ants[ktora][1] = r;
    antsWorld[i][j] = nullptr;  //i się teleportuje
  }

  int wwib = 10;
  void vibrate(int i, int j) { //rozchodzenie się wibracji w przestrzeni
    for (int k=i-wwib; k<=i+wwib; k++) {
      for (int l=j-wwib; l<=j+wwib; l++) {
        if ((k-i)*(k-i)+(l-j)*(l-j)<=wwib*wwib) {
          backWorld[(k+worozmiar)%worozmiar][(l+worozmiar)%worozmiar]->makeAsound(i, j);
        }
      }
    }
  }

  int ileMrowekNiosloCokolwiek() {
    int ile = 0;
    for (int i = 0; i<ileWsumieMrowek; i++) {
      int x = ants[i][0];
      int y = ants[i][1];
      if (antsWorld[x][y]->czyCosNiosla) ile++;
    }
    return ile;
  }

  void czyOtoczona(int i, int j) {
    int a=0;
    for (int k=i-2; k<=i+2; k++) {
      for (int l=j-2; l<=j+2; l++) {
        if ((k-i)*(k-i)+(l-j)*(l-j)<=4) {
          if (antsWorld[(k+worozmiar)%worozmiar][(l+worozmiar)%worozmiar]!=nullptr) a++;
        }
      }
    }
    if (a>4) bombaZapomnienia(i, j);
  }


  void bombaZapomnienia(int i, int j) {
    for (int k=i-wwib/2; k<=i+wwib/2; k++) {
      for (int l=j-wwib/2; l<=j+wwib/2; l++) {
        if ((k-i)*(k-i)+(l-j)*(l-j)<=wwib*wwib/4) {
          if (antsWorld[i][j]!=nullptr && random(1)<0.75) antsWorld[i][j]->zapominanie();
        }
      }
    }
  }
};
//../../scripts/procesing2cpp.sh did it

