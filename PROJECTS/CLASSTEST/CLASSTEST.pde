/// Class hierarchy test for Processing2C.
/// ORIGINAL FILE: "CLASSTEST.pde"
/// @date 2024-10-15 (last change)
//*/////////////////////////////////////////////////////////////////////////
/// INSPIRED BY EXAMPLE from https://www.baeldung.com/java-type-casting
//*/////////////////////////////////////////////////////////////////////////
interface Face 
{
     /*_interfunc*/ String face() /*_forcebody*/ ;
} //_endOfclass

interface Mew 
{
    /*_interfunc*/ void meow(int l) /*_forcebody*/ ;
} //_endOfclass

interface Eat 
{
    /*_interfunc*/ void eat(int l) /*_forcebody*/ ;
} //_endOfclass

abstract class Animal implements Face
{
    float mass;
    /*_interfunc*/ void eat(int l) {
        println(l,"Animal eats"); 
        mass+=l;
    }
    
    String face() { return "👾" ;}

} //_endOfclass

class Cat extends Animal implements Face,/*_pubext*/ Mew, /*_pubext*/ Eat
{
    void eat(int l) {
         println(l,"Cat eats");  
    }
 
    void meow(int l) {
         println(l,"Cat meows");  
    }
    
    String face() { return "🐱"; }
} //_endOfclass

class Dog extends Animal 
{
    void eat(int l) {
         println(l,"Dog eats");  
    }
    
    String face() { return "🐶"; }
} //_endOfclass

class AnimalFeeder 
{
    void feed(ArrayList<Animal> animals) {
        for(Animal a:animals)
            a.eat(10);
        }
} //_endOfclass

void setup()
{
    size(150,150);
    Object object = new Cat();
    Cat cat = /*_downcast*/(Cat)(object); //Second parentheses required
    cat.meow(0);
    //object = cat;//Work in processing, DOES NOT IN C++ :-/ :-(
                 //error: ambiguous overload for ‘operator=’ 
    object = /*_upcast*/(Object)(cat); //works using static_cast in C++
    object = /*_downcast*/(Object)(cat); //works using dynamic_cast in C++
    
    Mew mew = new Cat();
    mew.meow(1);
    //mew = cat;//Work in processing, DOES NOT IN C++ :-/ :-(
              //error: ambiguous overload for ‘operator=’ 
    mew = /*_upcast*/(Mew)(cat); //works using COMPILE TIME static_cast in C++
    mew = /*_downcast*/(Mew)(cat); //dynamic_cast is usually resolved at RUN TIME
    
    mew.meow(2);
    
    Animal animal = cat; //OK
    //animal = cat;//Work in processing, DOES NOT IN C++ :-/ :-(
    animal = /*_upcast*/(Animal)( cat ); //use static_cast in C++
    animal.eat(3);
    
    //animal = mew; //Not work in Processing, also in C++ does not
    //animal = (Cat) mew; //Work in Processing, in C++ does not
    //animal = (Animal) mew; //Work in Processing, in C++ does not
    //animal = /*_upcast*/(Animal)( mew ); //in Processing same as below, but not in C++
    animal = /*_downcast*/(Animal)( mew ); //With _downcast work always
    animal.eat(4);
    
//  animal.meow(4); ///Error: The method meow() is undefined for the type Animal
    
    Cat ancat = /*_downcast*/(Cat)( animal );
    ancat.meow(5);
    ( /*_downcast*/(Cat)( animal ) ).meow(6); //Second parentheses in cast required
   
    if (animal instanceof Cat) { //downcast with check
      println("This animal is a cat");
      ( /*_downcast*/(Cat)( animal ) ).meow(7); //Second parentheses in cast required
    }
    
    animal = new Dog();
    animal.eat(8);    
    
    if (animal instanceof Cat) { //downcast with check
      println("This animal is a cat");
      ( /*_downcast*/(Cat)(animal) ).meow(9); /// Does not happen
    }
    
    if ( animal instanceof Dog ) { //Type check
      println("This animal is a dog");
    }
    
    //if ( Dog instanceof Animal ) //Does not work both in Processing & in C++
    //  println("Any dog is an animal");

    //Polymorphism
    ArrayList<Animal> animals = new ArrayList<Animal>();
    animals.add(new Cat());
    animals.add(new Dog());
    AnimalFeeder feeder=new AnimalFeeder();
    feeder.feed(animals);

    print_animals(animals);  
    println(animals);
    
    String as="";
    for(Animal a:animals)
        as+=a.face();
    as+="...";
    text(as,10,height/2);    println(as);
        
    print_animals(animals); //Sprawdzenie czy wywołanie function z parametrem obiektowym nie niszczy pamięci!
}

void print_animals(ArrayList<Animal> anim) /// Drukowanie własną metodą
{
      for(Animal a:anim)
        println(a,"",a.face());
}

//*/////////////////////////////////////////////////////////////////
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
//*/////////////////////////////////////////////////////////////////
