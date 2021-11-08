/// IntList,FloatList,StringList & ArrayList test for Processing2C
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: ARRAYLIST.pde
////////////////////////////////////////////////////////////////////
ArrayList<String> testStr=null;
StringList        inventory=new StringList();
FloatList         inventoryF;
IntList           inventoryI;

void setup() {
  size(200, 200);
  
  testStr=new ArrayList<String>();
  boolean res=testStr.add("bulba?");
  res=testStr.add("buuulba!");
  println(testStr);
  
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
  
  noLoop();// ONLY ONE CALL OF draw FUNCTION!
  fill(0);
  textAlign(CENTER);
}

void draw() {
  //Called only once!
  String item = inventory.get(2);
  float flos = inventoryF.get(2);
  int nums = inventoryI.get(2);
  for(int i:inventoryI)
    println(i);
  for(String s:testStr)
    println(s);
  text(item+';'+nums+';'+flos, width/2, height/2);
}
