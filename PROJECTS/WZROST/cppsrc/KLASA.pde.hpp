/// @file
/// Simple model of colony growth with mutations (test project for Processing2C).
/// @date 2024-10-15 (last change)
//*////////////////////////////////////////////////////


//*/////////////////////////
//  TAKA KLASA PRZYKŁADOWA
//*/////////////////////////

int KLASA_Counter=0; ///< Globalny licznik obiektów typu RGB.

/// Info: obiekt przykładowy z polami Red,Green,Blue.
class KLASA: public virtual Object{
  public:
  int R,G,B;
  
  KLASA() //!< Konstruktor
  { 
    R=G=B=0; 
    KLASA_Counter++;
  }
  
  void Set(int iR,int iG,int iB) //!< Setter.
  {
    R=iR;G=iG;B=iB;
  }
  
  bool    isEmpty()
  {
    return R<=0 && G<=0 && B<=0;
  }
  
  void Visualise(int X,int Y) //!< Method of visualisation.
  {
    if(!isEmpty())
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
  
  void finalize() //!< Finalizer->Wywoływany przez Javę gdy Garbage collector likwiduje objekt.
  {               //!< Teoretycznie - bo trudno to sprawdzić. http://stackoverflow->com/questions/2506488/when-is-the-finalize-method-called-in-java
    KLASA_Counter--; //Wygląda na to że w tym programie nie jest wołany nigdy.
    println("-");
    //super::finalize();//A na to Processing robi blup...
  }
};

//*//////////////////////////////////////////////////////////
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
//*//////////////////////////////////////////////////////////
//MADE NOTE: ../../scripts did it 2024-10-15 16:10:57 !

