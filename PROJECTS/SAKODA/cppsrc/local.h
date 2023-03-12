//Automagically generated file
//Dont edit!
#pragma once
#ifndef LOCAL_H
#define LOCAL_H



//All classes but not templates from Processing files
class Agent; typedef Processing::ptr<Agent> pAgent; // { 
class World; typedef Processing::ptr<World> pWorld; // {

//All global finals (consts) from Processing files

//All global variables from Processing files
extern	int 		Number_of_identities;	///< =2;  - Ile jest wykluczających się tożsamości
extern	String 		modelName;	///< ="ABMSakoda";  - Name of the model
extern	int 		side;	///< =100;  - side of main table
extern	float 		density;	///< =0.55;  -initial density of agents
extern	pWorld 		TheWorld;	///< =new World(side);  -  will be initialised inside setup function
extern	int 		cwidth;	///< =8;  - size of cell
extern	int 		STATUSHEIGH;	///< =40;  -???
extern	int 		STEPSperVIS;	///< =1;   -???
extern	int 		FRAMEFREQ;	///< =20;    -???
extern	bool 		WITH_VIDEO;	///< =false;    - Is video stream enabled?
extern	bool 		simulationRun;	///< =true;  -Start/stop flag

//All global arrays from Processing files

//All global matrices from Processing files

//All global functions from Processing files
void	initializeAgents(smatrix<pAgent> agents);  ///< Need to be global!
void	initializeAgents(sarray<pAgent> agents);  ///< Need to be global!
void	changeAgents(sarray<pAgent> agents);  ///< Need to be global!
void	changeAgents(smatrix<pAgent> agents);  ///< Need to be global!
void	initializeModel(pWorld world);  ///< Need to be global!
void	visualizeModel(pWorld world);  ///< Need to be global!
void	changeState(pWorld world);  ///< Need to be global!
void	modelStep(pWorld world);  ///< Need to be global!
void	initializeStats();  ///< Need to be global!
void	doStatistics(pWorld world);  ///< Need to be global!
void	doStatisticsOnAgents(sarray<pAgent> agents);  ///< Need to be global!
void	doStatisticsOnAgents(smatrix<pAgent> agents);  ///< Need to be global!
void	visualizeAgents(smatrix<pAgent> agents);  ///< Need to be global!
void	visualizeAgents(sarray<pAgent> agents);  ///< Need to be global!
void	writeStatusLine();  ///< Used also for stats
#endif
