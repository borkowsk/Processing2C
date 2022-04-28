//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: ELIPSY.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

/// Simple graphics test for Processing2C
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "ELIPSY.pde"
////////////////////////////////////////////////////////////////////

int W=600;//Control parameter

int radius()
{
  return int(random(W/10));
}

//Initialisation
void processing_window::setup()
{
  size(600,600);
  setFrameRate(500); // draw( ) about 500 times per sec.(if possible!)
                  //Nie za dużo bo Xorg zablokuje kompa!
}

//Running - visualisation and dynamics
void processing_window::draw()
{
  fill(random(255),random(255),random(255),random(255));
  float r=radius();
  float x=random(W);
  float y=random(W);
  ellipse(x,y,r,r);
  stroke(255);
  point(x,y);
  println(frameRate);
}
//../../scripts did it

