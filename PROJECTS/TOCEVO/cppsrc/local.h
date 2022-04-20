//Automagically generated file
//Dont edit!
#pragma once
#ifndef LOCAL_H
#define LOCAL_H



//All classes from Processing files
class Agent; typedef Processing::ptr<Agent> pAgent; //
class PairOfInt; typedef Processing::ptr<PairOfInt> pPairOfInt; //
class World; typedef Processing::ptr<World> pWorld; // 

//All global finals (consts) from Processing files

//All global variables from Processing files
extern float panPerStep;//=0;///Panishment per step
extern float treesR;//=1.015;///from 1..1.1 !
extern float agentsDensity;//=0.005;///Initial density of agents
extern bool usePanishment;//=true;///Panishment swith off/on
extern char   panishmentTime;//=20;///How long panished agent is paralised
extern int   costOfStep;//=10; /// Metabolic cost for agent to live one step more.
extern float maxStock;//=costOfStep*50;///maximal stock per agent. The storage of unused energy is limited!
extern float pOffspring;//=0.05;///How offten agent WANTs split into 2 agents
extern bool WITH_NEW_DEL_LOG;//=false;///
extern bool WITH_VIDEO;//=false;///

//All global functions from Processing files
#endif
