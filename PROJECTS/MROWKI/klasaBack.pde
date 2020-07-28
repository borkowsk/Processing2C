class Back
{
  float id;  //jaki rodzaj nawierzchni
  float p_follow;  //ile feromonu jest, jak chętnie będą iść
  float amountFood;  //ile jedzenia jest na miejscu
  float sound;
  int[] where = new int[2];

  Back(int idB) {  //tło inicjowane rodzajem powierzchi
    id = idB;
    sound = 0;
    if (id==2) { //jeżeli to jedzenie, zawsze je zabierze
      p_follow = 1;  
      amountFood = int(random(ileje));
    } else if (id==10) {
    } else { //inaczej idzie z takim samym p
      p_follow = pe;   
      amountFood=0;
    }
  }

  //++++++++++++ FUNKCJE WYKONAWCZE ++++++++++++


  void makeAsound(int x, int y){//dźwięk zadaje kolor tła i kierunek, skąd dobiega
    sound = 1;
    where[0] = x;
    where[1] = y;
  }

  void diss() {//poza bazowym prawdopodobieństwem, feromon zawsze się zmiejsza z czasem
    if (p_follow>pe) p_follow-=disp;
  }

  void dissound() {
    if (sound>0) sound-=quiet;
  }

  void trail(float amount) {//wzmocnienie następuje, gdy szlak nie jest już przepełniony
    if (p_follow<0.95) p_follow+=amount;
  }

  void takeFood() {//funkcja pokazująca zabranie jedzenia z miejsca przez mrówkę 
    if (id == 2) amountFood-=1;
    if (amountFood<=0) id = 0;
  }
}
