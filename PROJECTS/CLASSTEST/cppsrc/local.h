//Automagically generated file
//Dont edit!
#pragma once
#ifndef LOCAL_H
#define LOCAL_H



//All classes from Processing files
/*abstract*/class Animal; typedef Processing::ptr<Animal> pAnimal; // {
/*interface*/class Eat; typedef Processing::ptr<Eat> pEat; // {
/*interface*/class Mew; typedef Processing::ptr<Mew> pMew; // {
class AnimalFeeder; typedef Processing::ptr<AnimalFeeder> pAnimalFeeder; // {
class Cat; typedef Processing::ptr<Cat> pCat; // extends Animal implements Mew, /*_pubext*/ Eat {
class Dog; typedef Processing::ptr<Dog> pDog; // extends Animal {

//All global finals (consts) from Processing files

//All global variables from Processing files

//All global functions from Processing files
void print_animals(ArrayList<pAnimal> anim); /// Drukowanie własną metodą
#endif
