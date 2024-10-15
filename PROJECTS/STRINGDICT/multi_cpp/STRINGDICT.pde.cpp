/// @file
/// @note Automatically made from _STRINGDICT.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
/// @date 2024-10-15 16:11:05 (translation)
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
#include "processing_StringDict.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

/// @file
/// STRINGDICT is a test for Processing2C++
/// @date 2024-09-30 (last change)
/// @class StringDict
/// @details
///   A simple class to use a `String` as a lookup for an `String` value.
///   `String` "keys" are associated with String values.
///   In Pr2C it is implemented as class used `std::map`
//*///////////////////////////////////////////////////////////////////////

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

//MADE NOTE: ../../scripts did it 2024-10-15 16:11:05 !

const char* Processing::_PROGRAMNAME="STRINGDICT";
