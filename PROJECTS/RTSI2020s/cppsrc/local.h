//Automagically generated file
//Dont edit!
#pragma once
#ifndef LOCAL_H
#define LOCAL_H


//All global finals (consts) from Processing files
extern const float INF_NOT_EXIST;//=Float.MAX_VALUE;  ///visible autside this file!

//All global variables from Processing files
extern int debug_level;//=0;  ///visible autside this file!
extern float meanOpinion;//=0;  ///May be used also autside this file!
extern float stddOpinion;//=0;  ///visible autside this file!
extern float minOpinion;//=0;  ///visible autside this file!
extern float maxOpinion;//=0;  ///visible autside this file!
extern float meanSensor;//=0;  ///visible autside this file!
extern int   UsedSensors;//=0;  ///visible autside this file!
extern float meanSRealt;//=0;  ///visible autside this file!
extern float meanSRelia;//=0;  ///visible autside this file!
extern float meanError;//=0; ///Co jest błędem jest zależne od tego co jest realnością!
extern int    link_up;//=0;  ///When weight goes up
extern int    link_dw;//=0;  ///When weight goes down
extern int  sensor_up;//=0;  ///visible autside this file!
extern int  sensor_dw;//=0;  ///visible autside this file!
extern bool requestClean;//=false;  ///visible autside this file!
extern float histogram_width;//=HISTOGRAM_WIDTH;  /// Bars have integer width, so really histogram may be narrower than that
extern float XSPREAD;//=0.01;   /// how far is target point of link of type 1, from center of the cell
extern int   linkCounter;//=0;  /// number od=f links visualised last time
extern int searchedX;//=-1;  ///visible autside this file!
extern int searchedY;//=-1;  ///visible autside this file!
extern bool Clicked;//=false;  ///visible autside this file!
extern int selectedX;//=-1;  ///visible autside this file!
extern int selectedY;//=-1;  ///visible autside this file!
extern String  modelName;//="RTSI_Model_S3.1b";  /// MODEL NAME IS USED IN STATISTICS AND VISUALISATION
extern int     FRAMEFREQ;//=300;  /// Desired simulation speed per second
extern int   SIDE;//=6;  /// side of the 1 & 2D tables - not more than 20 when full_network  is used!!!
extern float NETWORK_DENSITY;//=1;   /// Not for all network types - in simple_model select between full & random network
extern int   NOISE_DETAILS;//=4; /// For 2D noiseDetail()
extern float NOISE_OFFS;//=0.5;  /// For 2D noiseDetail()
extern float NOISE_SCALE;//=0.25;/// For init noise properties. Until now was 0.233 - TODO disconnect properties area from SIDE!!!
extern float NOISE_DRIFT;//=0;   /// If different than 0 enable random walk on noise space instead of random change every MACRO_STEP
extern float AGENTS_DENSITY;//=0.95;/// Desired density of agents may not be realised strictly 
extern float MAX_ERROR_OF_SENSOR;//=0.2;/// For sensor initialisation. Warning! Flat distribution 0..MAX for particular sensors
extern float BIAS_MEAN;//=0.01;  /// Desired mean value of bias
extern float BIAS_DISP;//=0.02;  /// Desired dispersion, so each BIAS is inside range [mean-dispersion,mean+dispersion]
extern bool TRACE_ACTIONS;//=false;  /// If you want to see each particular action
extern float   REAL_INFO_PROBABILITY;//=0.01;    /// "R" - How offten agent has reality check - JAK 0 TO NIGDY NIE SPRAWDZA FAKTYCZNEGO STANU
extern int     REALITY;//=3;   /// Skąd bierzemy "realność"? 0-bierze REALNOSC spod nog, 1-średni pomiar, 2-średnią opinie, 3-średnią realność
extern bool REMEMBER_REALITY_FACTS;//=false;  /// Is reality fact remembered for opinion or not (ESPECIALLY NOT IN PREDICTION CHECK MODEL!)
extern float   OWN_MEASURE_PROBABILITY;//=0.0;   /// "S" - How offten agent use own sensor
extern bool SELF_LINKED;//=(OWN_MEASURE_PROBABILITY==0);  /// Alternatywnie używamy linku do własnego sensora jak do obcego
extern float   INTERACTION_PROBABILITY;//=1.0-OWN_MEASURE_PROBABILITY-REAL_INFO_PROBABILITY;/// "o" - other agent activities (ask for fact only in simple_model)
extern float MIN_RELIABILITY;//=0.001;   /// Minimal reliability for sensor and links. Maybe 0.5? TODO CHECK! 
extern float MAX_INI_RELIABILITY;//=0.90;/// Maximal initial weight and sensor reliability
extern float SQR_ERROR_TRESHOLD;//=0.01; /// Squared errors above treshold lead to lowering trust, below otherwise 
extern float UP_Q_LINK_TRUST;//=0.20; /// How much trust (weight of link) may go up in one interaction
extern float DOWN_LINK_TRUST;//=0.30; /// How much trust (weight of link) may go down in one interaction
extern float UP_Q_SELF_TRUST;//=0.20; /// How much reliability of sensor may go up in one measuiring SELF_TRUST
extern float DOWN_SELF_TRUST;//=0.30; /// How much reliability of sensor may go down in one measuiring
extern int   MACRO_STEP_MULT;//=3;  /// Multiplicating of social step lenght
extern int   MACRO_STEP;//=(int)((SIDE*SIDE)*INTERACTION_PROBABILITY*NETWORK_DENSITY)*MACRO_STEP_MULT;  /// 1/OWN_MEASURE_PROBABILITY may leads to DIV/0 error, 
extern int   MINIMAL_PROPERTY_INDEX;//=0;  /// ONLY ONE PROPERTY FOR SIMPLE MODEL
extern int   MAXIMAL_PROPERTY_INDEX;//=0;  /// ONLY ONE PROPERTY FOR SIMPLE MODEL
extern int   NUM_OF_PROPERTIES;//=MAXIMAL_PROPERTY_INDEX+1;  /// How many important properties of the simulation world?
extern int   NUM_OF_ISSUES;//=NUM_OF_PROPERTIES;  /// ONLY ONE PROPERTY FOR SIMPLE MODEL
extern int     WhichProperty;//=0;  ///Which property of the world is about to visualise?
extern int     STEPSperVIS;//=10;  ///Visualisation &  every 10 steps
extern int     STEPSperSTAT;//=1;  ///Statistics &  every 10 steps
extern bool VIS_NETWORK;//=false;   ///
extern float   linkWeightTresh;//=0.95;///Links filtering for visualisation
extern float   MAX_LINK_WEIGHT;//=2;   ///Maximal strokeWidth for links TODO - link stroke from 1-3, when 1 is for linkWeightTresh
extern float   LINK_INTENSITY;//=32;   ///For link transparency
extern bool VIS_AGENTS;//=false;    ///
extern float   AGENT_STROKE;//=2;      ///Stroke width for Agents
extern bool WITH_STROKE;//=true;    ///
extern bool WITH_MIN_MAX;//=false;  /// Wizualizacja minimalnej i maksymalnej opini
extern bool WITH_ERRORS;//=true;    /// Czy jest wykres średniego błędu?
extern bool ZERO_ONE_SCALE;//=false;///Dodanie zera i jedynki do wspólnych maksimów i minimów
extern bool visualiseReliabilities;//=true;  ///
extern int     FROM_END;//=(MACRO_STEP*10)/STEPSperSTAT;  ///How many MACRO_STEPS are visible on timelines?
extern bool WITH_VIDEO;//=false;    /// visible autside this file!
extern int     FONT_HEIGHT;//=10;       /// for fontSize 
extern int     STATUSHEIGH;//=100;      /// Bottom side STATUS area HEIGHT
extern float   WORLD_VIS_SIDE;//=0.5;   /// Side of a world visualisation area
extern float   HISTOGRAM_WIDTH;//=0.497;/// as part of a window width
extern float   HISTOGRAM_HEIGHT;//=0.55;/// as part of STATUSHEIGH
extern float   TIMELINES_WIDTH;//=0.4985;///as part of window width
extern float   TIMELINES_HIGTH;//=0.950;/// as part of window (height-STATUSHEIGH)
extern int     cwidth;//=15;///size of cell
extern bool simulationRun;//=true;///Start/stop flag

//All global functions from Processing files


//All classes from Processing files
/*abstract*/class Colorable; typedef Processing::ptr<Colorable> pColorable; // extends Named implements iColorable {
/*abstract*/class LinkFactory; typedef Processing::ptr<LinkFactory> pLinkFactory; // {
/*abstract*/class LinkFilter; typedef Processing::ptr<LinkFilter> pLinkFilter; // {
/*abstract*/class Named; typedef Processing::ptr<Named> pNamed; // implements iNamed { 
/*abstract*/class Node; typedef Processing::ptr<Node> pNode; // extends Positioned implements iNode {
/*abstract*/class Positioned; typedef Processing::ptr<Positioned> pPositioned; // extends Colorable implements iPositioned {
/*interface*/class iColorable; typedef Processing::ptr<iColorable> piColorable; // {
/*interface*/class iLink; typedef Processing::ptr<iLink> piLink; // { 
/*interface*/class iNamed; typedef Processing::ptr<iNamed> piNamed; // {
/*interface*/class iNode; typedef Processing::ptr<iNode> piNode; // { 
/*interface*/class iPositioned; typedef Processing::ptr<iPositioned> piPositioned; // {
/*interface*/class iVisLink; typedef Processing::ptr<iVisLink> piVisLink; // extends iLink,iNamed,iColorable {
/*interface*/class iVisNode; typedef Processing::ptr<iVisNode> piVisNode; // extends iNode,iNamed,iColorable,iPositioned {
class AbsHighPassFilter; typedef Processing::ptr<AbsHighPassFilter> pAbsHighPassFilter; // extends LinkFilter {
class AbsLowPassFilter; typedef Processing::ptr<AbsLowPassFilter> pAbsLowPassFilter; // extends LinkFilter {
class Agent; typedef Processing::ptr<Agent> pAgent; // extends NodeList implements iVisNode {
class AllLinks; typedef Processing::ptr<AllLinks> pAllLinks; // extends LinkFilter
class AndFilter; typedef Processing::ptr<AndFilter> pAndFilter; // extends LinkFilter {
class CosMultProperty; typedef Processing::ptr<CosMultProperty> pCosMultProperty; // extends PropertyBase {
class DefPerlinProperty; typedef Processing::ptr<DefPerlinProperty> pDefPerlinProperty; // extends PropertyBase { // MODEL IMPORTANT PART!
class Frequencies; typedef Processing::ptr<Frequencies> pFrequencies; // extends NamedData {
class HighPassFilter; typedef Processing::ptr<HighPassFilter> pHighPassFilter; // extends LinkFilter {
class Info; typedef Processing::ptr<Info> pInfo; // { // MODEL IMPORTANT PART!
class Issue; typedef Processing::ptr<Issue> pIssue; // { 
class Link; typedef Processing::ptr<Link> pLink; // extends Colorable implements iLink,iVisLink,Comparable<Link> {
class LowPassFilter; typedef Processing::ptr<LowPassFilter> pLowPassFilter; // extends LinkFilter {
class MultProperty; typedef Processing::ptr<MultProperty> pMultProperty; // extends PropertyBase {
class NamedData; typedef Processing::ptr<NamedData> pNamedData; // implements iNamed {
class NodeList; typedef Processing::ptr<NodeList> pNodeList; // extends Node {
class NodeMap; typedef Processing::ptr<NodeMap> pNodeMap; // extends Node {
class OrFilter; typedef Processing::ptr<OrFilter> pOrFilter; // extends LinkFilter {
class PairOfInt; typedef Processing::ptr<PairOfInt> pPairOfInt; // {
class PropertyBase; typedef Processing::ptr<PropertyBase> pPropertyBase; // {
class RTSILink; typedef Processing::ptr<RTSILink> pRTSILink; // extends Link {
class RTSILinkFactory; typedef Processing::ptr<RTSILinkFactory> pRTSILinkFactory; // extends LinkFactory {
class Range; typedef Processing::ptr<Range> pRange; // extends NamedData {
class Sample; typedef Processing::ptr<Sample> pSample; // extends NamedData {
class Sensor; typedef Processing::ptr<Sensor> pSensor; // {
class SinMultProperty; typedef Processing::ptr<SinMultProperty> pSinMultProperty; // extends PropertyBase {
class TypeAndAbsHighPassFilter; typedef Processing::ptr<TypeAndAbsHighPassFilter> pTypeAndAbsHighPassFilter; // extends LinkFilter {
class TypeFilter; typedef Processing::ptr<TypeFilter> pTypeFilter; // extends LinkFilter {
class World; typedef Processing::ptr<World> pWorld; // {
class pointxy; typedef Processing::ptr<pointxy> ppointxy; // {
class settings_bar3d; typedef Processing::ptr<settings_bar3d> psettings_bar3d; // {
#endif
