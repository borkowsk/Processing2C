//Automagically generated file
//Dont edit!
#pragma once
#ifndef LOCAL_H
#define LOCAL_H



//All classes from Processing files
class Agent; typedef Processing::ptr<Agent> pAgent; // {
class PairOfInt; typedef Processing::ptr<PairOfInt> pPairOfInt; // {
class World; typedef Processing::ptr<World> pWorld; // {

//All global finals (consts) from Processing files

//All global variables from Processing files
extern	int 		StepCounter;///< =0; < globalny licznik kroków
extern	PrintWriter 		outstat;    ///< główny plik wynikowy
extern	int   		prevStep;///< =0;           <
extern	float 		meanAgentsEn;///< =0;       <
extern	float 		meanCells;///< =0;          <
extern	int   		liveAgentsCount;///< =0;    <
extern	int   		liveCellsCount;///< =0;     <
extern	int   		numOfPunishments;///< =0;   <
extern	float 		punPerStep;///< =0;         < Punishment per step
extern	int   		numOfBorns;///< =0;         < number of newborns
extern	float 		bornsPerStep;///< =0;       <
extern	int 		searchedX;///< =-1;   <???
extern	int 		searchedY;///< =-1;   <???
extern	bool 		Clicked;///< =false; <???
extern	int 		selectedX;///< =-1;   <???
extern	int 		selectedY;///< =-1;   <???
extern	pAgent 		selected;///< =null; <???
extern	int 		side;///< =200;                 < side of main table: 20,50,100,200,400
extern	String 		modelName;///< ="TOC1.0_";   < name of the model used for producing file names of outputs
extern	float 		treesDensity;///< =0.250;     < ???
extern	float 		treesR;///< =1.015;           < from 1..1.1 !
extern	float 		agentsDensity;///< =0.005;    < Initial density of agents
extern	bool 		usePunishment;///< =true;   < Punishment swith off/on
extern	bool 		enableKilling;///< =false;  < ???
extern	char16_t   		punishmentTime;///< =20;     < How long punished agent is paralysed
extern	int   		costOfStep;///< =10;          < Metabolic cost for agent to live one step more.
extern	float 		maxStock;///< =costOfStep*50; < maximal stock per agent. The storage of unused energy is limited!
extern	float 		maxInitialEnergyOfAgent;///< =costOfStep*50;    <
extern	float 		pOffspring;///< =0.05;        < How often agent WANTs split into 2 agents
extern	pWorld 		TheWorld;///< =new World(side); < Made here, but also will be completed inside setup()
extern	int 		cwidth;///< =8;                   < size of cell
extern	int 		STATUSHEIGH;///< =40;             < ???
extern	int 		STEPSperVIS;///< =usePunishment?100:10;< Jak nie ma punishment'u to mogą szybko wymrzeć
extern	int 		FRAMEFREQ;///< =1000;             < ???
extern	bool 		WITH_NEW_DEL_LOG;///< =false; < ???
extern	bool 		WITH_VIDEO;///< =false;       < ???
extern	bool 		simulationRun;///< =true;     < Start/stop flag

//All global arrays from Processing files
extern	sarray<int> eatCounters;///< =null; < TU JEST PROBLEM
extern	sarray<int> punCounters;///< =null; < Chyba tablica nie jest akceptowana. TODO!!!

//All global matrices from Processing files

//All global functions from Processing files
void	initializeAgents(smatrix<pAgent> agents);  ///< initialisation of all agents
void	cleanDeaths(smatrix<pAgent> agents);  ///< ???
void	changeAgents(smatrix<pAgent> agents,smatrix<int> cells);  ///< ???
void	initializeModel(pWorld world);  ///< Need to be global!
void	visualizeModel(pWorld world);  ///< Need to be global!
void	changes(pWorld world);  ///< Need to be global!
void	modelStep(pWorld world);  ///< Need to be global!
void	initializeCells( smatrix<int> cells );  ///< Need to be global!
void	synchChangeCells( smatrix<int> cells , smatrix<int> newcells );  ///< Drugi parametr tłumaczony jest błędnie! TODO
void	initializeStats();  ///< Need to be global!
void	doStatistics(pWorld world);  ///< Need to be global!
void	doStatisticsOnAgents(smatrix<pAgent> agents);  ///< Need to be global!
void	doStatisticsOnCells(smatrix<int> cells);  ///< Need to be global!
void	visualizeCells(smatrix<int> cells);  ///< Need to be global!
void	visualizeAgents(smatrix<pAgent> agents);  ///< Need to be global!
void	writeStatusLine();  ///< Wypełnia treścią obszar statusu aplikacji
#endif
