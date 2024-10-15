//Automagically generated file. @date 2024-10-15 16:11:06 
//Dont edit\!
#pragma once
#ifndef LOCAL_H
#define LOCAL_H



//All classes but not templates from Processing files
class KLASA; typedef Processing::ptr<KLASA> pKLASA; // 

//All global finals (consts) from Processing files

//All global variables from Processing files
extern	int 		KLASA_Counter;	// ->  Globalny licznik obiektów typu RGB.
extern	int 		JUMP;	// ->  skok pozycji "zarodnika". Nieparzysty!
extern	int 		CJUMP;	// ->  skok koloru. Tez lepiej nieparzysty.
extern	int 		STARTG;	// ->  W jakiej szarości pierwsza komórka.
extern	bool 		ScreenDumps;	// ->  Zrzucanie obrazków co krok wcale.
extern	int 		VIS_FRQ;	// ->  co ile kroków zrzut ekranu.
extern	int          		Side;          // ->  Bok macierzy.
extern	int          		W;             // ->  Mnożnik dla kwadracika.
extern	PrintWriter 		output;         // ->  A tu używamy innej klasy, zdefiniowanej w bibliotece.

//All global arrays from Processing files

//All global matrices from Processing files

//All global functions from Processing files
#endif
