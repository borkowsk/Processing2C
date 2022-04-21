//Automagically generated file
//Dont edit!
#pragma once
#ifndef LOCAL_H
#define LOCAL_H



//All classes from Processing files
class Agent; typedef Processing::ptr<Agent> pAgent; // {
class World; typedef Processing::ptr<World> pWorld; // {

//All global finals (consts) from Processing files
extern const int Duration;//=7;/// Czas trwania infekcji!
extern const int Susceptible;//=1;/// Oznaczenie podatnego
extern const int Infected;//=2;/// Oznaczenie zainfekowanego
extern const int Recovered;//=Infected+Duration;/// Oznaczenie wyleczonego
extern const int Death;//=100;/// Oznaczenie zmarłego
extern const float PDeath;//=0.015;     /// Średnie prawdopodobieństwo śmierci w danym dniu choroby

//All global variables from Processing files
extern	int 		side;///< =200; DŁUGOŚĆ BOKU ŚWIATA
extern	String 		modelName;///< ="ABMEpidemia"; Nazwa modelu, np. dla plików wyjściowych
extern	float 		density;///< =0.66; główny MERYTORYCZNY parametr modelu
extern	int 		liveCount;///< =0; Ile aktualnie żywych
extern	int  		sumInfected;///< =0;Zachorowanie
extern	int 		sumRecovered;///< =0;Wyzdrowienia
extern	int     		sumDeath;///< =0;Ci co umarli
extern	pFloatList 		deaths;///< =new FloatList();Historia śmierci 
extern	pFloatList 		newcas;///< =new FloatList();Historia nowych zachorowań
extern	pFloatList  		cured;///< =new FloatList();Historia wyleczeń
extern	int 		cwidth;///< =3;DŁUGOŚĆ BOKU KOMÓRKI W WIZUALIZACJI
extern	int 		STATUSHEIGH;///< =150;WYSOKOŚĆ PASKA STATUSU NA DOLE OKNA
extern	int 		STEPSperVIS;///< =1;JAK CZĘSTO URUCHAMIAMY WIZUALIZACJĘ
extern	int 		FRAMEFREQ;///< =30; ILE RAZY NA SEKUNDĘ URUCHAMIA SIĘ draw( )

//All global arrays from Processing files

//All global matrices from Processing files

//All global functions from Processing files
void	initializeAgents(smatrix<pAgent> agents);  /// Inicjalizacja wszystkich agentów w 2D
void	initializeAgents(sarray<pAgent> agents);  /// Inicjalizacja wszystkich agentów  w 1D
void	agentsChange(sarray<pAgent> agents);  /// Główna dynamika symulacji 1D - dummy! NIEZAIPLEMENTOWANA!
void	agentsChange(smatrix<pAgent> agents);  /// Główna dynamika symulacji 2D
void	initializeModel(pWorld world);  /// Zwyczajowa nazwa funkcji
void	visualizeModel(pWorld world);  /// Zwyczajowa nazwa funkcji
void	modelStep(pWorld world);  /// Zwyczajowa nazwa funkcji
void	writeStatusLine();  ///Ta nazwa musi być znana globalnie
void	histogram(smatrix<pAgent> agents,float startx,float starty,float hight);  ///Funkcja przechodzi po wszystkich agentach i zlicza wg. klas odpornosci.
void	timeline(pFloatList data,float startX, float startY, float height,bool logaritm); /// Dla C++ ta deklaracja musi być umieszczona w HPP
void	timeline(pFloatList data_a,pFloatList data_b,pFloatList data_c,float startX,float startY,float height,bool logaritm,color color_a,color color_b,color color_c); /// Dla C++ ta deklaracja musi być umieszczona w HPP
void	dottedLine(float x1, float y1, float x2, float y2, float steps);  ///Potrzebna do wizualizacji
void	visualizeAgents(smatrix<pAgent> agents);  /// Wizualizacja wszystkich agentów 2D
void	visualizeAgents(sarray<pAgent> agents);  /// Wizualizacja wszystkich agentów 2D
#endif
