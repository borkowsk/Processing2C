// Obsługa wyszukiwania obiektu po kliknięciu myszy
///////////////////////////////////////////////////////////////////////
int searchedX=-1;  ///visible autside this file!
int searchedY=-1;  ///visible autside this file!
boolean Clicked=false;  ///visible autside this file!
int selectedX=-1;  ///visible autside this file!
int selectedY=-1;  ///visible autside this file!

Agent selected=null;

//double minDist2Selec=MAX_INT;//???
//double maxTransSelec=-MAX_INT;//???

class PairOfInt {
    ///INFO: Simple version of Pair returning a pair of Int
    //public 
    final int a;
    //public 
    final int b;

    //public 
    PairOfInt(int a,int b) 
    {
        this.a = a;
        this.b = b;
    }
};

void mouseClicked()
{
  //println("Mouse clicked at ",mouseX,mouseY);//DEBUG
  //Clicked=true;//To nie jest używane (na razie?)
  searchedX=mouseX;
  searchedY=mouseY; 
  
  PairOfInt result=findCell(theWorld.agents);//But 1D searching is belong to you!
  if(result!=null)//Znaleziono
  {
    selectedX=result.a;
    selectedY=result.b;
    if((selected=theWorld.agents[selectedY][selectedX])!=null)
    {
      println("Cell",selectedX,selectedY,"belong to",selected);
      println("Env. value:",theWorld.properties[0].get2D(selectedX,selectedY));//?TODO
      println(selected.fullInfo("\t"));
    }
    else
    {
      println("Cell",selectedX,selectedY,"is empty");
      println("Env. value:",theWorld.properties[0].get2D(selectedX,selectedY));//?TODO
    }
  }
}

PairOfInt findCell(Agent[][] agents)//Używamy globalnych zmiennych mouseX i mouseY dla szybkości
{ //Przeliczanie współrzędnych myszy na współrzędne komórki 
  //Parametr jest tylko do sprawdzenie typu i ROZMIARÓW
  //Działa o tyle o ile wizualizacja komórek startuje w punkcie 0,0
  int x=mouseX/cwidth;
  int y=mouseY/cwidth;
  if(0<=y && y<agents.length
  && 0<=x && x<agents[y].length)
      return new PairOfInt(x,y);
  else
      return null;
}


///////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - ABM EVENTS FROM TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////
