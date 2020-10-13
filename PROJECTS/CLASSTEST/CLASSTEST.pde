// EXAMPLE BORROWED from https://www.baeldung.com/java-type-casting
///////////////////////////////////////////////////////////////////////////

interface Mew {
    /*_interfunc*/ void meow(int l)/*_forcebody*/;
};

interface Eat {
    /*_interfunc*/ void eat(int l)/*_forcebody*/;
};

abstract class Animal {
    /*_interfunc*/ void eat(int l) {
        println(l,"Animal eats"); 
    }
};

class Cat extends Animal implements Mew, /*_pubext*/ Eat {
    void eat(int l) {
         println(l,"Cat eats");  
    }
 
    void meow(int l) {
         println(l,"Cat meows");  
    }
};

class Dog extends Animal {
    void eat(int l) {
         println(l,"Dog eats");  
    }
};

/*
class AnimalFeeder {
//    void feed(ArrayList<Animal> animals) {
//        for(Animal a:animals)
//            a.eat(0);
//        }
//};
*/

void setup()
{
    size(150,100);
    //Object object = new Animal(); //OK
    Cat cat = new Cat();//OK
    Mew mew = new Cat();
    Object obj=new Cat();
    mew = cat;
    mew.meow(1);
    
    Animal animal = cat;//OK
    animal = /*_downcast*/(Cat)( mew );
    animal.eat(2);
    
    animal = /*_downcast*/(Animal)( cat );//OK
    
    animal.eat(3);
//  animal.meow(4); /// The method meow() is undefined for the type Animal
    Cat ancat=/*_downcast*/(Cat)( animal );
    ancat.meow(4);
    (/*_downcast*/(Cat)( animal ) ).meow(5);// downcast is needed 
   
    

    //if (animal instanceof Cat) { //downcast with check
    //    (/*_downcast*/(Cat)( animal ) ).meow(6);
    //}
    
    animal = new Dog();
    animal.eat(7);    
    
//    if (animal instanceof Cat) { //downcast with check
//        ((Cat) animal).meow(8); /// Does not happen
//    }

    //Polymorphism
    //ArrayList<Animal> animals = new ArrayList<Animal>();
    //animals.add(new Cat());
    //animals.add(new Dog());
    //AnimalFeeder feeder=new AnimalFeeder();
    //feeder.feed(animals);
}
