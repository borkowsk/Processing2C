//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: CLASSTEST.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

/// Class hierarchy test for Processing2C
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "CLASSTEST.pde"
///////////////////////////////////////////////////////////////////////////
// INSPIRED BY EXAMPLE from https://www->baeldung->com/java-type-casting
///////////////////////////////////////////////////////////////////////////

//interface
class Mew: public virtual Object{
  public:
    virtual void meow(int l)=0;
};

//interface
class Eat: public virtual Object{
  public:
    virtual void eat(int l)=0;
};

//abstract
class Animal: public virtual Object{
  public:
    float mass;
    virtual void eat(int l) {
        println(l,"Animal eats"); 
        mass+=l;
    }
};

class Cat : public  Animal, public virtual Mew, public virtual Eat , public virtual Object{
  public:
    void eat(int l) {
         println(l,"Cat eats");  
    }
 
    void meow(int l) {
         println(l,"Cat meows");  
    }
};

class Dog : public  Animal , public virtual Object{
  public:
    void eat(int l) {
         println(l,"Dog eats");  
    }
};

class AnimalFeeder: public virtual Object{
  public:
    void feed(pArrayList<pAnimal> animals) {
        for(pAnimal a:animals)
            a->eat(10);
        }
};

void processing_window::setup()
{
    size(150,100);
    pObject object= new Cat();
    pCat cat= std::dynamic_pointer_cast<Cat>(object);//Second parentheses required
    cat->meow(0);
    //object = cat;//Work in processing, DOES NOT IN C++ :-/ :-(
                 //error: ambiguous overload for ‘operator=’ 
    object = static_cast<pObject>(cat);//works using static_cast in C++
    object = std::dynamic_pointer_cast<Object>(cat);//works using dynamic_cast in C++
    
    pMew mew= new Cat();
    mew->meow(1);
    //mew = cat;//Work in processing, DOES NOT IN C++ :-/ :-(
              //error: ambiguous overload for ‘operator=’ 
    mew = static_cast<pMew>(cat);//works using COMPILE TIME static_cast in C++
    mew = std::dynamic_pointer_cast<Mew>(cat);//dynamic_cast is usualy resolved at RUN TIME
    
    mew->meow(2);
    
    pAnimal animal= cat;//OK
    //animal = cat;//Work in processing, DOES NOT IN C++ :-/ :-(
    animal = static_cast<pAnimal>( cat );//use static_cast in C++
    animal->eat(3);
    
    //animal = mew;//Not work in Processing, also in C++ does not
    //animal = (Cat) mew;//Work in Processing, in C++ does not
    //animal = (Animal) mew;//Work in Processing, in C++ does not
    //animal = static_cast<pAnimal>( mew );//in Processing same as below, but not in C++
    animal = std::dynamic_pointer_cast<Animal>( mew );//With _downcast work always
    animal->eat(4);
    
//  animal->meow(4); ///Error: The method meow() is undefined for the type Animal
    
    pCat ancat=std::dynamic_pointer_cast<Cat>( animal );
    ancat->meow(5);
    (std::dynamic_pointer_cast<Cat>( animal ) )->meow(6);//Second parentheses in cast required
   
    if (instanceof< Cat >( animal )) { //downcast with check
      println("This animal is a cat");
      (std::dynamic_pointer_cast<Cat>( animal ) )->meow(7);//Second parentheses in cast required
    }
    
    animal = new Dog();
    animal->eat(8);    
    
    if (instanceof< Cat >( animal )) { //downcast with check
      println("This animal is a cat");
      (std::dynamic_pointer_cast<Cat>(animal) )->meow(9); /// Does not happen
    }
    
    if ( instanceof< Dog >( animal ) ) { //Type check
      println("This animal is a dog");
    }
    
    //if ( instanceof< Animal >( Dog ) ) //Does not work both in Processing & in C++
    //  println("Any dog is an animal");

    //Polymorphism
    pArrayList<pAnimal> animals= new ArrayList<pAnimal>();
    animals->add(new Cat());
    animals->add(new Dog());
    pAnimalFeeder feeder=new AnimalFeeder();
    feeder->feed(animals);

    print_animals(animals);  
    println(animals);  
    print_animals(animals); //Sprawdzenie czy wywołanie funcji z parametrem obiektowym nie niszczy pamięci!
}

void print_animals(pArrayList<pAnimal> anim) /// Drukowanie własną metodą
{
      for(pAnimal a:anim)
        println(a);
}
//../../scripts did it

