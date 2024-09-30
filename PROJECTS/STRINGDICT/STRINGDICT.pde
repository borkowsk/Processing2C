/// @file
/// STRINGDICT is a test for Processing2C++
/// @date 2024-09-30 (last change)
/// @class StringDict
/// @details
///   A simple class to use a `String` as a lookup for an `String` value.
///   `String` "keys" are associated with String values.
///   In Pr2C it is implemented as class used `std::map`
//*///////////////////////////////////////////////////////////////////////

StringDict inventory;

void setup() 
{
  size(300, 300);
  inventory = new StringDict();
  inventory.set("coffee","black");
  inventory.set("flour","white");
  inventory.set("tea","green");
  println(inventory);

  textAlign(CENTER);
  frameRate(2);
  //noLoop();//W C++ program kończy się po mignięciu oknem! TODO
}

void draw() 
{
  background(random(255));
  fill(random(255),random(255),random(255));
  String s = inventory.get("tea");
  text(s, width/2, height/2);
}

