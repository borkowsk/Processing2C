//Automagically generated file
//Dont edit!
#pragma once
#ifndef LOCAL_H
#define LOCAL_H


//All global finals (consts) from Processing files

//All global variables from Processing files
extern int worozmiar ;//= sizew/ws;  ///ile pól jest na świecie
extern float density ;//= 0.005;  ///ewentualna gęstośc jedzenia rozłożena
extern int xNest ;//= int(worozmiar/7);  ///współrzędne gniazda i jego rozmiar
extern int yNest ;//= int(worozmiar/7);  ///
extern int siNest ;//= 3;                ///
extern int foodSupply;  /// początkowa ilość jedzenia w gnieździe
extern int ileWsumieMrowek ;//= sizew/10;  /// maksymalna dopuszczalna liczba mrówek
extern int ws ;//= 10;///
extern int sizew ;//= 900;///
extern float ts ;//= 0.5; ///wzmocnienie szlaku po zebraniu jedzenia
extern int memo ;//= 10; /// długość pamięci
extern float distrail ;//= 0.1; ///osłabienie szlaku, gdy nie ma jedzenia
extern float pLosowe ;//= 0.01;  ///prawdopodobieństwo odejścia od reguł, w klasieWorld
extern float disp ;//= 0.01; ///tempo zanikania szlaku 
extern float pe ;//= 0.1; ///normalne p przejścia, niby 0.125, bo 8 dróg, ale nie
extern int ileje ;//= 80; ///ile jest maksymalnie jedzenia na miejscu jedzenia
extern float quiet ;//= 0.5;   ///tempo uciszania dźwięku
extern bool vibrate;  ///
extern bool szlak;    ///
extern bool pamiec;  ///
extern bool losowo;  ///
extern int ileSymulacji ;//= 2; ///
extern int iteracja;  ///
extern int dra ;//= 0;   ///
extern int lpsym ;//= 1; /// do nazewnictwa

//All global functions from Processing files
void inicjacja(); /// Funkcja wymagająca deklaracji zapowiadającej
void pomocPetli(); /// Funkcja wymagająca deklaracji zapowiadającej
void petla(); /// Funkcja wymagająca deklaracji zapowiadającej


//All classes from Processing files
class Ant; typedef Processing::ptr<Ant> pAnt; // {
class Back; typedef Processing::ptr<Back> pBack; // {
class World; typedef Processing::ptr<World> pWorld; // {
#endif
