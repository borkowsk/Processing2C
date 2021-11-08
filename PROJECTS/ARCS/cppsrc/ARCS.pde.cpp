//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: ARCS.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
//#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //...is optional. Should be deleted when not needed.
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

//Division of the ellipse into sectors
//The coordinate system is treated as rotated!
void processing_window::setup()
{
  
size(500,500);

ellipseMode(CENTER);
arc(0,0,200,200,radians(1),PI/2.0,OPEN);//or PIE or CHORD

ellipse(250, 250, 200, 200);
fill(0);
arc(250, 250, 190, 190, PI/2.0,PI);
fill(128);
arc(250, 250, 190, 190, PI,PI*2-PI/10);
fill(255);

ellipseMode(CORNER);
arc(400,400,100,100,radians(10),radians(180),PIE);


//http://processingwedukacji->blogspot->com
saveFrame();//If saveFrame function is used without parameters, it will save files as "screen-0000.tif", "screen-0001.tif" etc.
}
//../../scripts/procesing2cpp.sh did it

