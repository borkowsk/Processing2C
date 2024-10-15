// @date 2024-10-15 (last modification)
// Obsługa wyszukiwania obiektu po kliknięciu myszy:
//*///////////////////////////////////////////////////

/*_import_class:Agent */
/*_import_class:World */

int searchedX=-1;       ///<???
int searchedY=-1;       ///<???
boolean Clicked=false;  ///<???
int selectedX=-1;       ///<???
int selectedY=-1;       ///<???
Agent selected=null;    ///<???

//double minDist2Selec=MAX_INT; ///???
//double maxTransSelec=-MAX_INT; ///???

/// Simple version of Pair returning a pair of Int.
/*_import_class:MousePairOfInt */


MousePairOfInt findCell(Agent[][] agents) ///< Używamy globalnych zmiennych mouseX i mouseY dla szybkości.
{ // Przeliczanie współrzędnych myszy na współrzędne komórki 
  // Parametr jest tylko do sprawdzenie typu i ROZMIARÓW
  // Działa o tyle o ile wizualizacja komórek startuje w punkcie 0,0
  int x=mouseX/cwidth;
  int y=mouseY/cwidth;
  if(0<=y && y<agents.length
  && 0<=x && x<agents[y].length)
      return new MousePairOfInt(x,y);
  else
      return null;
}

/// Support for searching for an object on mouse click.
void mouseClicked()
{
  println("Mouse clicked at ",mouseX,mouseY); //DEBUG
  Clicked=true;
  searchedX=mouseX;
  searchedY=mouseY; 
  
  MousePairOfInt result=findCell(TheWorld.agents); //But 1D searching is belong to you!
  if(result!=null) //Znaleziono
  {
    selectedX=result.a;
    selectedY=result.b;
    if((selected=TheWorld.agents[selectedY][selectedX])!=null)
    {
      println("Cell",selectedX,selectedY,"belong to",TheWorld.agents[selectedY][selectedX]);
      println(TheWorld.agents[selectedY][selectedX].info());
    }
    else
      println("Cell",selectedX,selectedY,"is empty");
  }
}

//*/////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - ABM EVENTS TEMPLATE
//*/////////////////////////////////////////////////////////////////////////////////////////
