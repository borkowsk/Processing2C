/// @file
/// @note Automatically made from _DICTSTEST.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
/// @date 2024-10-15 16:11:03 (translation)
//
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
#ifndef _NO_INLINE
#include "processing_inlines.hpp" //...is optional.
#endif // _NO_INLINE
#include "processing_string.hpp"  //Processing::String class
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_IntDict.hpp" //...is optional. Should be deleted when not needed.
#include "processing_FloatDict.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

/// Dictionary is a simple class to use a String as a lookup for an value. 
/// String "keys" are associated with integer or float values.
/// In Pr2C it is implemented as class derived from std::map
// @date 2024-09-30 (last change)
//*/////////////////////////////////////////////////////////////////////////

pFloatDict inventoryF;
pIntDict   inventoryI;

void processing_window::setup() 
{
  size(300, 300);
  
  inventoryF = new FloatDict();
  inventoryF->set("coffee",108.6);
  inventoryF->set("flour",5.8);
  inventoryF->set("tea",8.2);
  println(inventoryF);  // There is 8.2 of tea
  
  inventoryF->mult("tea", 4);
  println(inventoryF);  // There is 32.8 of tea
  
  inventoryF->remove("tea");
  println(inventoryF);
  
  inventoryI = new IntDict();
  inventoryI->set("cd", 84);
  inventoryI->set("tapes", 15);
  inventoryI->set("records", 102);
  println(inventoryI);
  inventoryI->div("records",2);
  
  fill(0);
  textAlign(CENTER);
  
  setFrameRate(3);
  //noLoop();
}

void processing_window::draw() 
{
  background(128);
  fill(random(255),random(255),random(255));
  int numRecords = inventoryI->get("records");
  text(numRecords, width/2, height/2);
}
//MADE NOTE: ../../scripts did it 2024-10-15 16:11:03 !

const char* Processing::_PROGRAMNAME="DICTSTEST";
