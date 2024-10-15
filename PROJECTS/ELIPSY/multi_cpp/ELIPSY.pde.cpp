/// @file
/// @note Automatically made from _ELIPSY.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
/// @date 2024-10-15 16:11:03 (translation)
//
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
#ifndef _NO_INLINE
#include "processing_inlines.hpp" //...is optional.
#endif // _NO_INLINE
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

/// Simple graphics test for Processing2C
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "ELIPSY.pde"
// @date 2024-09-30 (last change)
//*//////////////////////////////////////////////////////////////////

int W=600; /// Control parameter

int radius() ///< Example of the user declared function
{
  return int(random(W/10));
}

/// Initialisation
void processing_window::setup()
{
  size(600,600);
  background(255);
  setFrameRate(500); // draw( ) about 500 times per sec.(if possible!)
                  //Nie za dużo bo Xorg zablokuje kompa!
}

/// Running - visualisation and dynamics
void processing_window::draw()
{
  fill(random(255),random(255),random(255),random(255));
  float r=radius();
  float x=random(W);
  float y=random(W);
  ellipse(x,y,r,r);
  
  noStroke();
  //stroke(255);
  point(x,y);
  
  println(frameRate);
}
//MADE NOTE: ../../scripts did it 2024-10-15 16:11:03 !

const char* Processing::_PROGRAMNAME="ELIPSY";
