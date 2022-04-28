/// @file STRINGDICT.pde is a test for Processing2C++
/// @class StringDict:
///   A simple class to use a String as a lookup for an String value. 
///   String "keys" are associated with String values.
///   In Pr2C it is implemented as class used std::map
//*///////////////////////////////////////////////////////////////////
StringDict inventory;

void setup() {
  size(200, 200);
  inventory = new StringDict();
  inventory.set("coffee","black");
  inventory.set("flour","white");
  inventory.set("tea","green");
  println(inventory);
  noLoop();
  fill(0);
  textAlign(CENTER);
}

void draw() 
{
  String s = inventory.get("tea");
  text(s, width/2, height/2);
}
