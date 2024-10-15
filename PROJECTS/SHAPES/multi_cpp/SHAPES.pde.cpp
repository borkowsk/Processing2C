/// @file
/// @note Automatically made from _SHAPES.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
/// @date 2024-10-15 16:11:05 (translation)
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

/// @file
/// Shape example.
/// @date 2024-09-30 (last change)
//*/////////////////////////

const int iniWidth=500;
const int iniHeight=500;
const int NUMBER_OF_SHAPES=7;

int   FREQUENCY=25;

void processing_window::settings()
{
   size(iniWidth,iniHeight);
}

void processing_window::setup()
{
  setFrameRate(FREQUENCY);
  background(0);
  fill(random(255));
  stroke(random(255));
  strokeWeight(2);
  circle(width/2,height/2, min(width,height) / 10 );
  //rectMode(CORNERS); - its brake a lot!
}

void processing_window::draw()
{
  random_shape();
  if(frameCount % FREQUENCY == 0)
          println("\t",frameRate,"fr/s");
}

void random_shape() ///< Global namespace!
{
   switch(int(random(NUMBER_OF_SHAPES))){
   case 0:  fill(random(255)); stroke(random(255));  //noStroke(); ?
            circle(random(width),random(height), random(min(width,height) / 10 )); 
            break;
   case 1:  fill(random(255)); stroke(random(255),random(255),random(255));
            square(random(width),random(height), random(min(width,height) / 10 ));
            break;         
   case 2:  fill(random(255),random(255),random(255));
            stroke(random(255),random(255),random(255));
            circle(random(width),random(height), random(min(width,height) / 7 )); 
            break;
   case 3:  fill(random(255),random(255),random(255));
            stroke(random(255),random(255),random(255));
           {float x=random(width); float y=random(height);
            triangle(x,y,x-20,y+50,x+20,y+50);}
            break;
   case 4: fill(random(255),random(255),random(255));
           stroke(random(255),random(255),random(255));
           {float x=random(width); float y=random(height);
            quad(x,y,x-15,y+15,x,y+30,x+15,y+15);}
            break;
   case 5:  rect(30, 20, 55, 55, 3, 6, 12, 18);
            break;
   case 6:  rect(width/2+random(30),height/2+random(20),10+random(55),10+random(77), 7);
            break;
   case 7:  rectMode(CENTER);break;
   case 8:  rectMode(CORNER);break;
   case 9:  rectMode(RADIUS);break;
   //case 10: break;
   default: println("Not so many shapes!"); break;
   }
}
//MADE NOTE: ../../scripts did it 2024-10-15 16:11:05 !

const char* Processing::_PROGRAMNAME="SHAPES";
