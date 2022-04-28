//Processing to C++ converter /data/wb/SCC/public/Processing2C/scripts/procesing2cpp.sh
//Source: STRINGDICT.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "processing_string.hpp"  //Processing::String class
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_StringDict.hpp" //...is optional. Should be deleted when not needed.
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

/// @file STRINGDICT->pde is a test for Processing2C++
/// @class StringDict:
///   A simple class to use a String as a lookup for an String value. 
///   String "keys" are associated with String values.
///   In Pr2C it is implemented as class used std::map
//*///////////////////////////////////////////////////////////////////
StringDict inventory;

void processing_window::setup() {
  size(200, 200);
  inventory = new StringDict();
  inventory->set("coffee","black");
  inventory->set("flour","white");
  inventory->set("tea","green");
  println(inventory);
  noLoop();
  fill(0);
  textAlign(CENTER);
}

void processing_window::draw() 
{
  String s = inventory->get("tea");
  text(s, width/2, height/2);
}
///data/wb/SCC/public/Processing2C/scripts did it

