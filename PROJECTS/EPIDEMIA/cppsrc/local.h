//Automagically generated file. @date 2024-10-15 16:10:55 
//Dont edit\!
#pragma once
#ifndef LOCAL_H
#define LOCAL_H



//All classes but not templates from Processing files
class Agent; typedef Processing::ptr<Agent> pAgent; // 
class World; typedef Processing::ptr<World> pWorld; // {

//All global finals (consts) from Processing files
static 	const int Duration=7;   // -> Czas trwania infekcji!
static 	const int Susceptible=1; // -> Oznaczenie podatnego
static 	const int Infected=2;	// -> Oznaczenie zainfekowanego
static 	const int Recovered=Infected+Duration; // -> Oznaczenie wyleczonego
static 	const int Death=100;	// -> Oznaczenie zmarłego
static 	const float PDeath=0.015;	// -> Średnie prawdopodobieństwo śmierci w danym dniu choroby

//All global variables from Processing files
extern	int 		side;	// ->  DŁUGOŚĆ BOKU ŚWIATA
extern	String 		modelName;	// ->  Nazwa modelu, np. dla plików wyjściowych
extern	float 		density;	// ->  główny MERYTORYCZNY parametr modelu
extern	pWorld 		TheWorld;	// ->  INICJALIZACJA JEST KONCZONA W FUNKCJI setup( )
extern	int 		liveCount;	// ->  Ile aktualnie żywych
extern	int  		sumInfected;	// ->  Zachorowanie
extern	int 		sumRecovered;	// ->  Wyzdrowienia
extern	int     		sumDeath;	// ->  Ci co umarli
extern	pFloatList 		deaths;	// ->  Historia śmierci 
extern	pFloatList 		newcas;	// ->  Historia nowych zachorowań
extern	pFloatList  		cured;	// ->  Historia wyleczeń
extern	int 		cwidth;	// ->  DŁUGOŚĆ BOKU KOMÓRKI W WIZUALIZACJI
extern	int 		STATUSHEIGH;	// ->  WYSOKOŚĆ PASKA STATUSU NA DOLE OKNA
extern	int 		STEPSperVIS;	// ->  JAK CZĘSTO URUCHAMIAMY WIZUALIZACJĘ
extern	int 		FRAMEFREQ;	// ->  ILE RAZY NA SEKUNDĘ URUCHAMIA SIĘ draw( )
extern	bool 		simulationRun;	// ->  FLAGA Start/stop DZIAŁANIA SYMULACJI
extern	int 		fontHeight;	// ->  Wysokość napisów (działa tylko w Processingu, ale 16 to domyslne w X11

//All global arrays from Processing files

//All global matrices from Processing files

//All global functions from Processing files
void 	initializeAgents(smatrix<pAgent> agents);  // =>  Inicjalizacja wszystkich agentów w 2D
void 	initializeAgents(sarray<pAgent> agents);  // =>  Inicjalizacja wszystkich agentów  w 1D
void  	agentsChange(sarray<pAgent> agents);  // =>  Główna dynamika symulacji 1D - dummy! NIEZAIPLEMENTOWANA!
void  	agentsChange(smatrix<pAgent> agents);  // =>  Główna dynamika symulacji 2D
void 	initializeModel(pWorld world);  // => Zwyczajowa nazwa funkcji
void 	visualizeModel(pWorld world);  // => Zwyczajowa nazwa funkcji
void 	modelStep(pWorld world);  // => Zwyczajowa nazwa funkcji
void 	writeStatusLine();  // => Ta nazwa musi być znana globalnie
void 	histogram(smatrix<pAgent> agents,float startx,float starty,float hight);  // => Funkcja przechodzi po wszystkich agentach i zlicza wg. klas odpornosci.
void 	timeline(pFloatList data,float startX, float startY, float height,bool logaritm);  // =>  Dla C++ ta deklaracja musi być umieszczona w HPP
void 	timeline(pFloatList data_a,pFloatList data_b,pFloatList data_c,float startX,float startY,float height,bool logaritm,color color_a,color color_b,color color_c);  // =>  Dla C++ ta deklaracja musi być umieszczona w HPP
void 	dottedLine(float x1, float y1, float x2, float y2, float steps);  // => Potrzebna do wizualizacji
void 	visualizeAgents(smatrix<pAgent> agents);  // => Wizualizacja wszystkich agentów 2D
void 	visualizeAgents(sarray<pAgent> agents);  // =>  Wizualizacja wszystkich agentów 2D
#endif
