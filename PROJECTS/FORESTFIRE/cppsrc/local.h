//Automagically generated file
//Dont edit!
#pragma once
#ifndef LOCAL_H
#define LOCAL_H



//All classes from Processing files

//All global finals (consts) from Processing files

//All global variables from Processing files
extern int week;//=24*7;    ///how many steps is equivalential to one week?
extern float year;//=365.5*24;///how many steps is equivalential to one YEAR?
extern int N;//=300;        ///array side
extern int FireTimeDiv;//=50;///How long the tree is burning (divider for size)
extern float IgnitionP ;//= 0.10;///Probability of fire transfer
extern float InitT;//=  0.00; ///How many trees at start
extern float GrowS;//=  0.0005; ///Growt per step
extern float SeedP;//=  0.0005;///How often new ofspring emerging (per free cell)
extern float LightP;//= 0.000000005;///How often fire emerge (per tree)
extern int MatureT;//=220; ///Max size of tree. Then will stop to grow
extern PrintWriter Log;///For writing statistics into disk drive
extern int S;//=20;       ///cell width & height
extern int Step;//=0; ///!!!
extern float Burn;//=0;///Ile możliwości zapalenia na krok

//All global functions from Processing files
void doMonteCarloStep(); ///MAIN FUNCTION OF THE MODEL
void doVisualisation(); /// Must be predeclared
#endif
