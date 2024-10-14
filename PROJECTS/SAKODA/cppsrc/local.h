//Automagically generated file. @date 2024-10-14 17:34:05 
//Dont edit\!
#pragma once
#ifndef LOCAL_H
#define LOCAL_H



//All classes but not templates from Processing files
class Agent; typedef Processing::ptr<Agent> pAgent; // { 
class World; typedef Processing::ptr<World> pWorld; // {

//All global finals (consts) from Processing files

//All global variables from Processing files
extern	int 		Number_of_identities;	// ->  How many mutually exclusive identities are there?
extern	int 		StepCounter;	// ->  Global step counter.
extern	PrintWriter 		outstat;  // ->  Global statistic log stream (text file).
extern	float 		meanStress;	// ->  @note Should be globally visible!
extern	int   		liveCount;	// ->  @note Should be globally visible!
extern	String 		modelName;	// ->  Name of the model.
extern	int 		side;	// ->  side of main table.
extern	float 		density;	// ->  initial density of agents.
extern	pWorld 		TheWorld;	// ->   will be initialised inside setup function.
extern	int 		cwidth;	// ->  size of cell.
extern	int 		STATUSHEIGH;	// ->  ???
extern	int 		STEPSperVIS;	// ->  ???
extern	int 		FRAMEFREQ;	// ->  ???
extern	bool 		WITH_VIDEO;	// ->  Is video stream enabled?
extern	bool 		simulationRun;	// ->  Start/stop flag.

//All global arrays from Processing files

//All global matrices from Processing files

//All global functions from Processing files
void 	initializeAgents(smatrix<pAgent> agents);  // => @note Need to be global!
void 	initializeAgents(sarray<pAgent> agents);  // => @note Need to be global!
void  	changeAgents(sarray<pAgent> agents);  // => @note Need to be global!
void  	changeAgents(smatrix<pAgent> agents);  // => @note Need to be global!
void 	initializeModel(pWorld world);  // => Need to be global!
void 	visualizeModel(pWorld world);  // => Need to be global!
void 	changeState(pWorld world);  // => Need to be global!
void 	modelStep(pWorld world);  // => Need to be global!
void 	initializeStats();  // => @note Needs to be global!
void 	doStatistics(pWorld world);  // => @note Needs to be global!
void 	doStatisticsOnAgents(sarray<pAgent> agents);  // => @note Needs to be global!
void 	doStatisticsOnAgents(smatrix<pAgent> agents);  // => @note Needs to be global!
void 	visualizeAgents(smatrix<pAgent> agents);  // => Need to be global!
void 	visualizeAgents(sarray<pAgent> agents);  // => Need to be global!
void 	writeStatusLine();  // => Used also for stats
#endif
