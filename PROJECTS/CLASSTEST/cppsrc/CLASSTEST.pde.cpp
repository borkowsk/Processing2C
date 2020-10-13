//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: CLASSTEST.pde
#include "processing_templates.hpp"
//#include "processing_inlines.hpp" //is optional. Use when project is already compilable
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

// EXAMPLE BORROWED from https://www->baeldung->com/java-type-casting
///////////////////////////////////////////////////////////////////////////

//interface
class Mew : virtual public Object {
  public:
    virtual void meow(int l)=0;
};

//interface
class Eat : virtual public Object {
  public:
    virtual void eat(int l)=0;
};

//abstract
 class Animal : virtual public Object{
   public:
    virtual void eat(int l) {
        println(l,"Animal eats"); 
    }
};

class Cat  : public Animal, public  Mew, public Eat  {
  public:
    void eat(int l) {
         println(l,"Cat eats");  
    }
 
    void meow(int l) {
         println(l,"Cat meows");  
    }
};

class Dog : public Animal {
  public:
    void eat(int l) {
         println(l,"Dog eats");  
    }
};

/*
class AnimalFeeder {
  public:
//    void feed(ArrayList<Animal> animals) {
//        for(pAnimal a:animals)
//            a->eat(0);
//        }
//};
*/

void processing_window::setup()
{
    size(150,100);
    //pObject object= new Animal(); //OK
    pCat cat= new Cat();//OK
    pMew mew= new Cat();
    pObject obj=new Cat();
    mew = cat;
    mew->meow(1);
    
    pAnimal animal= cat;//OK
    //animal = processing_cast<Cat>( mew );
    animal->eat(2);
    
    //animal = processing_cast<Animal>( cat );//OK
    
    animal->eat(3);
//  animal->meow(4); /// The method meow() is undefined for the type Animal
    //pCat ancat=processing_cast<Cat>( animal );
    //ancat->meow(4);
    //(processing_cast<Cat>( animal ) ).meow(5);// downcast is needed 
   
    

    //if (animal instanceof Cat) { //downcast with check
    //    (processing_cast<Cat>( animal ) ).meow(6);
    //}
    
    animal = new Dog();
    animal->eat(7);    
    
//    if (animal instanceof Cat) { //downcast with check
//        ((Cat) animal).meow(8); /// Does not happen
//    }

    //Polymorphism
    //sArrayList<Animal> animals = new ArrayList<Animal>();
    //animals->add(new Cat());
    //animals->add(new Dog());
    //pAnimalFeeder feeder=new AnimalFeeder();
    //feeder->feed(animals);
}
//../../scripts/procesing2cpp.sh did it

