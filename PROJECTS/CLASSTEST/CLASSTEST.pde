// EXAMPLE BORROWED from https://www.baeldung.com/java-type-casting
///////////////////////////////////////////////////////////////////////////

interface Mew {
    void meow();
};

interface Eat {
    void eat();
};

class Animal {
    void eat() {
        println("Animal eats"); 
    }
};

class Cat extends Animal implements Mew, Eat {
    void eat() {
         println("Cat eats");  
    }
 
    void meow() {
         println("Cat meows");  
    }
};

class Dog extends Animal {
    void eat() {
         println("Dog eats");  
    }
};

class AnimalFeeder {
    void feed(ArrayList<Animal> animals) {
        for(Animal a:animals)
            a.eat();
        }
};

Mew mew = new Cat();

void setup()
{
    Object object = new Animal(); //OK
    Cat cat = new Cat();//OK
    Animal animal = cat;//OK
    animal =(Animal)cat;//OK
    
    animal.eat();
//  animal.meow(); /// The method meow() is undefined for the type Animal
  	((Cat) animal).meow();// downcast is needed 

    if (animal instanceof Cat) { //downcast with check
        ((Cat) animal).meow();
    }
    
    animal = new Dog();
    
    if (animal instanceof Cat) { //downcast with check
        ((Cat) animal).meow(); /// Does not happen
    }

    //Polymorphism
    ArrayList<Animal> animals = new ArrayList<Animal>();
    animals.add(new Cat());
    animals.add(new Dog());
    AnimalFeeder feeder=new AnimalFeeder();
    feeder.feed(animals);
}
