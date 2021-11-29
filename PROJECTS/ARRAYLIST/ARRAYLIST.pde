/// IntList,FloatList,StringList & ArrayList test for Processing2C
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "ARRAYLIST.pde"
////////////////////////////////////////////////////////////////////
ArrayList<String> testStrings=null;
StringList        inventory=new StringList();
FloatList         inventoryF;
IntList           inventoryI;

void setup() {
  size(200, 200);
  
  testStrings=new ArrayList<String>();
  boolean res=testStrings.add("bulba?");
  res=testStrings.add("buuulba!");
  println(testStrings);
  
  inventory = new StringList();
  inventory.append("coffee");
  inventory.append("flour");
  inventory.append("tea");
  inventory.append("cocoa");
  println(inventory);
  
  inventoryF = new FloatList();
  inventoryF.append(108.6);
  inventoryF.append(5.8);
  inventoryF.append(8.2);
  println(inventoryF);
  
  inventoryI = new IntList();
  inventoryI.append(84);
  inventoryI.append(15);
  inventoryI.append(102);
  println(inventoryI);
  
  //noLoop();// ONLY ONE CALL OF draw FUNCTION!
  //or
  frameRate(1);
  
  fill(0);
  textAlign(CENTER);
}


void user_print(IntList intInv)///
{
  for(int i:intInv)
      println(hex(i));
}


void draw() { //May be called only once, or many times
  println();
  println(testStrings);
  
  inventoryI.add(2,1);
  int nums = inventoryI.get(2);
  String item = inventory.get(2);
  float flos = inventoryF.get(2);

  background(255);
  text(item+';'+nums+';'+flos, width/2, height/2);
    
  println(inventoryI);
  user_print(inventoryI);
}
