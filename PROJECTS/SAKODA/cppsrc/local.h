//Automagically generated file
//Dont edit!
#pragma once
#ifndef LOCAL_H
#define LOCAL_H



//All classes from Processing files
class Agent; typedef Processing::ptr<Agent> pAgent; // { 
class World; typedef Processing::ptr<World> pWorld; // {

//All global finals (consts) from Processing files

//All global variables from Processing files
extern	int 		Number_of_identities;///< =2; Ile jest wykluczających się tożsamości
extern	int 		side;///< =100; side of main table
extern	String 		modelName;///< ="ABMSakoda";
extern	float 		density;///< =0.55;
extern	pWorld 		TheWorld;///< =new World(side); ... but also will be initialised inside setup function
extern	int 		cwidth;///< =8; size of cell
extern	int 		STATUSHEIGH;///< =40;
extern	int 		STEPSperVIS;///< =1;
extern	int 		FRAMEFREQ;///< =20;
extern	bool 		WITH_VIDEO;///< =false;
extern	bool 		simulationRun;///< =true;Start/stop flag

//All global arrays from Processing files

//All global matrices from Processing files

//All global functions from Processing files
void	initializeAgents(smatrix<pAgent> agents);  ///
void	initializeAgents(sarray<pAgent> agents);  ///
void	changeAgents(sarray<pAgent> agents);  ///
void	changeAgents(smatrix<pAgent> agents);  ///
void	initializeModel(pWorld world);  ///
void	visualizeModel(pWorld world);  ///
void	changeState(pWorld world);  ///
void	modelStep(pWorld world);  ///
void	initializeStats();  ///
void	doStatistics(pWorld world);  ///
void	doStatisticsOnAgents(sarray<pAgent> agents);  ///
void	doStatisticsOnAgents(smatrix<pAgent> agents);  ///
void	visualizeAgents(smatrix<pAgent> agents);  ///
void	visualizeAgents(sarray<pAgent> agents);  ///
void	writeStatusLine();  /// Used also for stats
#endif
