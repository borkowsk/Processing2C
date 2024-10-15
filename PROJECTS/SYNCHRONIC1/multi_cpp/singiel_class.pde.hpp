/// @file
#pragma once
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
#ifndef HEADER_singiel_INCLUDED
#define HEADER_singiel_INCLUDED

/// @file
/// Simple model of synchronization of couple, also class usage demonstration. (test project for Processing2C)
/// @note Comments from lecture/Komentarze są notatkami z wykładu: Małgorzata Filon
/// ORIGINAL FILE: "synchronizacja1.pde" -> "SYNCHRONIC1->pde"

/// @note Automatically extracted definition of `class`: singiel
class singiel: public virtual Object{
  public:
 //klasa czyli typ złożony
  //pola obiektu czyli dane 
  float x1,x2;
  float r;    //!<  np->współczynnik kontroli.
  float sync; //!<  jedno z pól, zależne do czego używamy obiektu, tu jest to wartość synchronizacji.
  
  //Metody:
  // KONSTRUKTOR: Każda klasa ma jedną metodę, która nazywa sie jak nazwa klasy.
  singiel(float iX,float iR,float iSync) //!< Konstruktor nie ma wartości zwracanej, nadaje stan obiektowi,
  {                                      //!< wszystkie pola muszą otrzymać nieprzypadkową wartość.
    x1=x2=iX; r=iR; sync=iSync;
  }
  
  /// Zwykła metoda, zazwyczaj zmienia wartość przynajmniej jednego pola.
  void next()
  {
    x1=x2;
    x2=x1*r*(1-x1);
  }

} ;/*_endOfClass*/

/// Generated by Processing2C++ extraction Tools
#endif //HEADER_singiel_INCLUDED

//MADE NOTE: ../../scripts did it 2024-10-15 16:11:05 !

