/// Agent Base Model of ant foraging adopted for Processing2C.
/// @author: Zofia Cieślińska
/// @date 2024-10-04 (last change)
//*////////////////////////////////////////////////////////////
/// ORIGINAL FILE: klasaAnt->pde
//*///////////////////////////////////////////

//++++++++++++ ZMIENNE ++++++++++++
class Ant: public virtual Object{
  public:
  float id, trailS; 
  //id - numerek w tablicy mrówek, trails - ile szlaku zostawia
  
  smatrix<int> memory = new matrix<int>(memo+3,2); 
  //pamięć z przegródkami: 
  //zerowa - jedzenie, pierwsza - wsp->gniazda, druga - wsp->jedzenia, rezszta - gdzie już była
  
  bool    czyCosNiosla = false;

  Ant(float idA, int xGnia, int yGnia) {  //inicjacja mrówki
    id = idA; //numerek w tablicy mrówek
    if(szlak) trailS = 0;  //początkowe wzmocnienie szlaku
    memory[0][0]=0;  //nie ma jedzenia na samym początku
    

    for (int i=1; i<memo+3; i++) {  //zainicjowane tylko gniazdem
      memory[i][0]=xGnia;
      memory[i][1]=yGnia;
    }
  }

  //++++++++++++ FUNKCJE WYKONAWCZE ++++++++++++

   /*virtual*/ void takeFood(int x, int y) {
    memory[0][0] +=1; //zbiera jedzenie do pamięci
    czyCosNiosla = true;
    if (trailS<0.95 && szlak) trailS+=ts;  //wzmacnia swój zostawiany szlak
    if (pamiec) pamieta(x, y);
  }

  void ifOnNestLeaveFood(int p, int r) {
      foodSupply+=memory[0][0];    //dodaje jedzenie do gniazda i zapomina
      memory[0][0] = 0;
      if(!pamiec) zapominanie();  //zapomina bardziej, jeżeli ma nie pamiętać
  }

  int memup = 0;  //dodawanie właśnie przeszłego pola do pamięci
  void memoryUpdate(int x, int y) {
    memory[memup+3][0]=x;
    memory[memup+3][1]=y;
    memup++;
    if (memup==memo) memup=0;
  }

  void pamieta(int x, int y) { //zapis lokalizacji jedzenia do pamięci
      memory[2][0] = x;
      memory[2][1] = y;
  }

  void slyszy1() { //inna wersja działania wibracji - wzmacnia swój szlak po usłyszeniu
    if (trailS<0.95 && szlak) trailS=0.94;
  }

  void zanikanie() {
    if (trailS>0 && memory[0][0]==0 && szlak) trailS-=distrail;
  }

  void zapominanie() {
    memory[2][0] = memory[1][0];
    memory[2][1] = memory[1][1];
  }

  bool    memoryCheck(int a, int b) { //sprawdzanie, czy dane pole jest w pamięci
    for (int i=3; i<memo; i++) {
      if (a==memory[i][0] && b==memory[i][1]) {
        return(false);  //fałsz, gdy jest
      }
    }
    return(true); //prawda, jeżeli nie ma i można się ruszyć
  }
};
//NOTE! ../../scripts did it 2024-10-04 13:54:21

