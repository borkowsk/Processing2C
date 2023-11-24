/// @file STRINGDICT->pde is a test for Processing2C++
/// @class StringDict:
///   A simple class to use a String as a lookup for an String value. 
///   String "keys" are associated with String values.
///   In Pr2C it is implemented as class used std::map
//*///////////////////////////////////////////////////////////////////
pStringDict inventory;

void processing_window::setup() 
{
  size(300, 300);
  inventory = new StringDict();
  inventory->set("coffee","black");
  inventory->set("flour","white");
  inventory->set("tea","green");
  println(inventory);

  textAlign(CENTER);
  setFrameRate(2);
  //noLoop();//W C++ program kończy się po mignięciu oknem! TODO
}

void processing_window::draw() 
{
  background(random(255));
  fill(random(255),random(255),random(255));
  String s = inventory->get("tea");
  text(s, width/2, height/2);
}

//NOTE! ../../scripts did it 2023-10-11 14:12:43

