//Automagically generated file. @date 2024-10-15 16:11:05 
//Dont edit\!
#pragma once
#ifndef LOCAL_H
#define LOCAL_H



//All classes but not templates from Processing files
class Agent; typedef Processing::ptr<Agent> pAgent; // 
class MousePairOfInt; typedef Processing::ptr<MousePairOfInt> pMousePairOfInt; // {
class World; typedef Processing::ptr<World> pWorld; // {

//All global finals (consts) from Processing files

//All global variables from Processing files
extern	int 		StepCounter;	// ->  Global step counter.
extern	PrintWriter 		outstat;    // ->  The main statistics output file.
extern	int   		prevStep;	// ->  ...
extern	float 		meanAgentsEn;	// ->  ...
extern	float 		meanCells;	// ->  ...
extern	int   		liveAgentsCount;	// ->  ...
extern	int   		liveCellsCount;	// ->  ...
extern	int   		numOfPunishments;	// ->  ...
extern	float 		punPerStep;	// ->  Punishment per step
extern	int   		numOfBorns;	// ->  number of newborns
extern	float 		bornsPerStep;	// ->  ...
extern	int 		searchedX;	// -> ???
extern	int 		searchedY;	// -> ???
extern	bool 		Clicked;	// -> ???
extern	int 		selectedX;	// -> ???
extern	int 		selectedY;	// -> ???
extern	pAgent 		selected;	// -> ???
extern	int 		side;	// ->  side of main table: 20,50,100,200,400 ...
extern	String 		modelName;	// ->  name of the model used for producing file names of outputs.
extern	float 		treesDensity;	// ->  ??? ...
extern	float 		treesR;	// ->  from 1..1.1 ...
extern	float 		agentsDensity;	// ->  Initial density of agents.
extern	bool 		usePunishment;	// ->  Punishment switch off/on.
extern	bool 		enableKilling;	// ->  ??? ...
extern	char16_t   		punishmentTime;	// ->  How long punished agent is paralysed.
extern	int   		costOfStep;	// ->  Metabolic cost for agent to live one step more.
extern	float 		maxStock;	// ->  maximal stock per agent. The storage of unused energy is limited!
extern	float 		maxInitialEnergyOfAgent;	// -> 
extern	float 		pOffspring;	// ->  How often agent WANTs split into 2 agents.
extern	pWorld 		TheWorld;	// ->  Made here, but also will be completed inside `setup()` .
extern	int 		cwidth;	// ->  size of cell.
extern	int 		STATUSHEIGH;	// ->  ??? ...
extern	int 		STEPSperVIS;	// ->  Jak nie ma punishment'u to mogą szybko wymrzeć.
extern	int 		FRAMEFREQ;	// ->  ??? ...
extern	bool 		WITH_NEW_DEL_LOG;	// ->  ??? ...
extern	bool 		WITH_VIDEO;	// ->  ??? ...
extern	bool 		simulationRun;	// ->  Start/stop flag.

//All global arrays from Processing files
extern	sarray<int> eatCounters;	// ->  TU JEST PROBLEM
extern	sarray<int> punCounters;	// ->  Chyba tablica nie jest akceptowana. TODO???

//All global matrices from Processing files

//All global functions from Processing files
void 	initializeAgents(smatrix<pAgent> agents);  // => initialisation of all agents.
void 	cleanDeaths(smatrix<pAgent> agents);  // => Cleaning world from death agents.
void  	changeAgents(smatrix<pAgent> agents,smatrix<int> cells);  // => Changing states of agents.
void 	initializeModel(pWorld world);  // => Need to be global!
void 	visualizeModel(pWorld world);  // => Need to be global!
void 	changes(pWorld world);  // => Need to be global!
void 	modelStep(pWorld world);  // => Need to be global!
void 	initializeCells( smatrix<int> cells );  // => Need to be global!
void 	synchChangeCells( smatrix<int> cells , smatrix<int> newcells );  // => Drugi parametr tłumaczony jest błędnie? TODO???
void 	initializeStats();  // => Needs to be global!
void 	doStatistics(pWorld world);  // => Need to be global!
void 	doStatisticsOnAgents(smatrix<pAgent> agents);  // => Need to be global!
void 	doStatisticsOnCells(smatrix<int> cells);  // => Need to be global!
void 	visualizeCells(smatrix<int> cells);  // => Need to be global!
void 	visualizeAgents(smatrix<pAgent> agents);  // => Need to be global!
pMousePairOfInt 	findCell(smatrix<pAgent> agents);  // => Używamy globalnych zmiennych mouseX i mouseY dla szybkości.
void 	writeStatusLine();  // => Wypełnia treścią obszar statusu aplikacji
#endif
