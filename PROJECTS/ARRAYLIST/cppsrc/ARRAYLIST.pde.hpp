/// IntList,FloatList,StringList & ArrayList test for Processing2C
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "ARRAYLIST.pde"
// @date 2024-10-15 (last change)
//*//////////////////////////////////////////////////////////////////

pArrayList<String> testStrings=nullptr;
pStringList        inventory=new StringList();
pFloatList         inventoryF;
pIntList           inventoryI;

void processing_window::setup() // Preparing for draw() loop
{
  size(200, 200);
  
  testStrings=new ArrayList<String>();
  bool    res=testStrings->add("bulba?");
  res=testStrings->add("buuulba!");
  println(testStrings);
  
  inventory = new StringList();
  inventory->append("coffee");
  inventory->append("flour");
  inventory->append("tea");
  inventory->append("cocoa");
  println(inventory);
  inventory->sort();
  println("Sorted:",inventory);
  //inventory-->sortReverse(); // Still not implemented
  //println("Sorted rev.:",inventory);

  inventoryF = new FloatList();
  inventoryF->append(108.6);
  inventoryF->append(5.8);
  inventoryF->append(8.2);
  println(inventoryF);
  inventoryF->sort();
  println("Sorted:",inventoryF);
  
  inventoryI = new IntList();
  inventoryI->append(84);
  inventoryI->append(15);
  inventoryI->append(102);
  println(inventoryI);
  inventoryI->sort();
  println("Sorted:",inventoryI);

  //noLoop();// ONLY ONE CALL OF draw FUNCTION!
  //or
  setFrameRate(1);
  
  fill(0);
  textAlign(CENTER);
}


void processing_window::draw() // May be called only once, or many times
{ 
  println();
  println(testStrings);
  
  inventoryI->add(2,1);
  int nums = inventoryI->get(2);
  String item = inventory->get(2);
  float flos = inventoryF->get(2);

  background(255);
  text(item+String(';')+nums+String(';')+flos, width/2, height/2);
    
  println(inventoryI);
  user_print(inventoryI);
}

void user_print(pIntList intInv) ///< USED before definition!
{
  for(int i:intInv)
      println(Processing::hex(i));
}


//MADE NOTE: ../../scripts did it 2024-10-15 16:10:55 !

