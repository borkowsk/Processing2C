//Automagically generated file. @date 2024-10-15 16:11:04 
//Dont edit\!
#pragma once
#ifndef LOCAL_H
#define LOCAL_H



//All classes but not templates from Processing files
class Ant; typedef Processing::ptr<Ant> pAnt; // {
class Back; typedef Processing::ptr<Back> pBack; // {
class World; typedef Processing::ptr<World> pWorld; // {

//All global finals (consts) from Processing files

//All global variables from Processing files
extern	int 		worozmiar ;	// -> ile pól jest na świecie
extern	float 		density ;	// -> ewentualna gęstośc jedzenia rozłożena
extern	int 		xNest ;	// -> współrzędne gniazda i jego rozmiar
extern	int 		yNest ;	// -> ???
extern	int 		siNest ;	// -> ???
extern	int 		foodSupply;  // ->  początkowa ilość jedzenia w gnieździe
extern	int 		ileWsumieMrowek ;	// ->  maksymalna dopuszczalna liczba mrówek
extern	PrintWriter 		output;     // ->  Globalny output
extern	PrintWriter 		stan;       // ->  stany
extern	pWorld 		world;            // ->  ŚWIAT MRÓWEK
extern	int 		ws ;	// ->  ???
extern	int 		sizew ;	// ->  ???
extern	float 		ts ;	// ->  wzmocnienie szlaku po zebraniu jedzenia
extern	int 		memo ;	// ->  długość pamięci
extern	float 		distrail ;	// ->  osłabienie szlaku, gdy nie ma jedzenia
extern	float 		pLosowe ;	// ->  prawdopodobieństwo odejścia od reguł, w klasieWorld
extern	float 		disp ;	// ->  tempo zanikania szlaku 
extern	float 		pe ;	// ->  normalne p przejścia, niby 0.125, bo 8 dróg, ale nie
extern	int 		ileje ;	// ->  ile jest maksymalnie jedzenia na miejscu jedzenia
extern	float 		quiet ;	// ->  tempo uciszania dźwięku
extern	bool 		may_vibrate;    // ->  Globalna zmienna nie może nazywać się tak jak lokalne metody
extern	bool 		szlak;          // ->  ???
extern	bool 		pamiec;         // ->  ???
extern	bool 		losowo;         // ->  ???
extern	int 		ileSymulacji ;	// ->  ???
extern	int 		iteracja;          // ->  ???
extern	int 		dra ;	// ->  ???
extern	int 		lpsym ;	// ->  do nazewnictwa.

//All global arrays from Processing files

//All global matrices from Processing files

//All global functions from Processing files
void 	inicjacja();  // => Funkcja wymagająca w C++ deklaracji zapowiadającej.
void 	pomocPetli();  // => Funkcja wymagająca deklaracji zapowiadającej
void 	petla();  // => Funkcja wymagająca deklaracji zapowiadającej
#endif
