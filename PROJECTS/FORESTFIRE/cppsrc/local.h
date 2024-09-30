//Automagically generated file. @date 2024-09-30 17:06:17 
//Dont edit\!
#pragma once
#ifndef LOCAL_H
#define LOCAL_H



//All classes but not templates from Processing files

//All global finals (consts) from Processing files

//All global variables from Processing files
extern	int 		Week;	// ->  how many steps is equivalential to one week?
extern	float 		Year;	// ->  how many steps is equivalential to one YEAR?
extern	int 		N;	// -> array side
extern	int 		FireTimeDiv;	// -> How long the tree is burning (divider for size)
extern	float 		IgnitionP ;	// -> Probability of fire transfer
extern	float 		InitT;	// -> How many trees at start
extern	float 		GrowS;	// -> Growt per step
extern	float 		SeedP;	// -> How often new ofspring emerging (per free cell)
extern	float 		LightP;	// -> How often fire emerge (per tree)
extern	int 		MatureT;	// -> Max size of tree. Then will stop to grow
extern	PrintWriter 		Log; // -> For writing statistics into disk drive
extern	int 		S;	// -> cell width & height
extern	int 		Step;	// -> !!!
extern	double 		meanSize;	// -> Sredni rozmiar drzewa (albo wiek bo to wychodzi na to samo chyba)
extern	float 		Burn;	// -> Ile możliwości zapalenia na krok

//All global arrays from Processing files

//All global matrices from Processing files

//All global functions from Processing files
void 	doMonteCarloStep();  // => MAIN FUNCTION OF THE MODEL
void 	doVisualisation();  // => Must be predeclared
#endif
