//TAKA KLASA
////////////////////////
int RGB_Counter=0;/// Globalny licznik obiektów typu RGB

class RGB {
  ///Info: obiekt przykładowy z polami Red,Green,Blue
  int R,G,B;
  
  RGB() //Konstruktor
  { 
    R=G=B=0; 
    RGB_Counter++;
  }
  
  void Set(int iR,int iG,int iB) //Setter
  {
    R=iR;G=iG;B=iB;
  }
  
  boolean isEmpty()
  {
    return R<=0 && G<=0 && B<=0;
  }
  
  void Visualise(int X,int Y) //Method
  {
    if(!isEmpty()) //<>//
    {
      stroke(R,G,B);
      if(W>1)
      {
        fill(R,G,B);
        rect(X*W,Y*W,W,W);
      }
      else
      {
        stroke(R,G,B);
        point(X,Y);
      }
    }
  }
  
  void finalize() //Finalizer.  Wywoływany przez Javę gdy Garbage collector likwiduje objekt
  {               //Teoretycznie - bo trudno to sprawdzić. http://stackoverflow.com/questions/2506488/when-is-the-finalize-method-called-in-java
    RGB_Counter--;//Wygląda na to że tym programie nie jest wołany nigdy //<>//
    println("-");
    //super.finalize();//Ale na to Processing robi blup...
  }
};
