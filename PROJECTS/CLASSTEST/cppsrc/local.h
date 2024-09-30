//Automagically generated file. @date 2024-09-30 17:06:16 
//Dont edit\!
#pragma once
#ifndef LOCAL_H
#define LOCAL_H



//All classes but not templates from Processing files
/*abstract*/class Animal; typedef Processing::ptr<Animal> pAnimal; // 
/*interface*/class Eat; typedef Processing::ptr<Eat> pEat; // 
/*interface*/class Mew; typedef Processing::ptr<Mew> pMew; // 
class AnimalFeeder; typedef Processing::ptr<AnimalFeeder> pAnimalFeeder; // 
class Cat; typedef Processing::ptr<Cat> pCat; // extends Animal implements Mew, /*_pubext*/ Eat 
class Dog; typedef Processing::ptr<Dog> pDog; // extends Animal 

//All global finals (consts) from Processing files

//All global variables from Processing files

//All global arrays from Processing files

//All global matrices from Processing files

//All global functions from Processing files
void 	print_animals(pArrayList<pAnimal> anim);  // =>  Drukowanie własną metodą
#endif
