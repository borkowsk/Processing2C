//Processing to C++ converter /data/wb/SCC/__working_copies/Processing2C/scripts/procesing2cpp.sh
//Source: ELIPSY.pde
#include "processing_templates.hpp"
//#include "processing_inlines.hpp" //is optional. Use when project is already compilable
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

//Control parameters
int W=600;

int radius()
{
  return int(random(W/10));
}

//Initialisation
void processing_window::setup()
{
  size(600,600);
  setFrameRate(1000);//Nie za dużo bo Xorg zablokuje kompa!
}

//Running - visualisation and dynamics (about 30 times per sec.)
void processing_window::draw()
{
  fill(random(255),random(255),random(255),random(255));
  float r=radius();
  ellipse(random(W),random(W),r,r);
  println(frameRate);
}
///data/wb/SCC/__working_copies/Processing2C/scripts/procesing2cpp.sh did it

