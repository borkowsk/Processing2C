//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: ARRAYLIST.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
//#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h"
#include "project.h" //...is for you. Could be deleted when not needed.
//==================================================================================

/// IntList,FloatList,StringList & ArrayList test for Processing2C
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: ARRAYLIST->pde
////////////////////////////////////////////////////////////////////
sArrayList<String> testStr=nullptr;
pStringList inventory=new StringList();
pFloatList inventoryF;
pIntList inventoryI;

void processing_window::setup() {
  size(200, 200);
  
  testStr=new ArrayList<String>();
  bool    res=testStr->add("bulba?");
  res=testStr->add("buuulba!");
  println(testStr);
  
  inventory = new StringList();
  inventory->append("coffee");
  inventory->append("flour");
  inventory->append("tea");
  inventory->append("cocoa");
  println(inventory);
  
  inventoryF = new FloatList();
  inventoryF->append(108.6);
  inventoryF->append(5.8);
  inventoryF->append(8.2);
  println(inventoryF);
  
  inventoryI = new IntList();
  inventoryI->append(84);
  inventoryI->append(15);
  inventoryI->append(102);
  println(inventoryI);
  
  noLoop();// ONLY ONE CALL OF draw()
  fill(0);
  textAlign(CENTER);
}

void processing_window::draw() {
  //Called only once!
  String item = inventory->get(2);
  float flos = inventoryF->get(2);
  int nums = inventoryI->get(2);
  for(int i:inventoryI)
    println(i);
  for(String s:testStr)
    println(s);
  text(item+String(';')+nums+String(';')+flos, width/2, height/2);
  
}
//../../scripts/procesing2cpp.sh did it

