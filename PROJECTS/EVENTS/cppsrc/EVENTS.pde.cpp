//Processing to C++ converter /data/wb/SCC/__public_git/Processing2C/scripts/procesing2cpp.sh
//Source: EVENTS.pde
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

/// Events example.
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// base on Processing examples
/// ORIGINAL FILE: EVENTS->pde
/////////////////////////////////////////////////////
// Click on the window to give it focus,
// and press the 'B' key.
// Also click one of mouse buttons

void processing_window::setup() {
  size(100,100);
  setFrameRate(10);//Apart this fraquency,
                // message are get only 10 times per second!
}

void processing_window::draw() {
  if (keyPressed) {
    if (key == 'b' || key == 'B') {
      fill(0);    
      println("keyPressed && 'B' detected in draw() - fill(BLACK)");
    }
    else
    if (key == ' ') {
      fill(255,0,0);    
      println("keyPressed && ' ' detected in draw() - fill(RED)");
    }
    else 
    {
      fill(255);
      println("keyPressed &&",String("'")+key+ String("'"),"detected in draw() - fill(WHITE)");
    }
    //keyPressed=false;//NOW IS PROCESSED.
  } else {
    fill(255);
    //println("keyPressed not detected in draw() - fill(WHITE)");
  }
  
  if (mousePressed && (mouseButton == LEFT)) {
    background(0); println("mousePressed && LEFT detected in draw()");
  } else if (mousePressed && (mouseButton == RIGHT)) {
    background(255);  println("mousePressed && RIGHT detected in draw()");
  } else if (mousePressed && (mouseButton == 3)) {
    background(255,0,0); println("mousePressed && MIDLE detected in draw()");
  } else if (mousePressed) {
    background(126); println("mousePressed &&",mouseButton,"detected in draw()");
  }

  if(mousePressed){
      println("mousePressed detected in draw()");
      //mousePressed=false;//NOW IS PROCESSED.
  }
  
  rect(25, 25, 50, 50);
}

void processing_window::onKeyPressed() {
    println("keyPressed\t", 
    String("'")+key+ String("'"), keyCode,keyPressed);
}

// Method signature 2
//void keyPressed(KeyEvent event) { ///not implemented in P2C++
//  println(String("keyPressed EVENT ") + event);
//}

void processing_window::onKeyReleased() {
    println("keyReleased\t", 
    String("'")+key+ String("'"),int(key),keyCode,keyPressed); 
}

// Method signature 2
//void keyReleased(KeyEvent event) { ///not implemented in P2C++
//  println(String("keyReleased EVENT ") + event);
//}

void processing_window::onMouseClicked() {
    println("mouseClicked\t",
    mouseX,mouseY,pmouseX,pmouseY,mousePressed,mouseButton);
}

// Method signature 2
//void mouseClicked(MouseEvent event) { ///not implemented in P2C++
//  println(String("mouseClicked EVENT ") + event);
//}

void processing_window::onMousePressed() {
    println("mousePressed\t",
    mouseX,mouseY,pmouseX,pmouseY,mousePressed,mouseButton);
}

// Method signature 2
//void mousePressed(MouseEvent event) { ///not implemented in P2C++
//  println(String("mousePressed EVENT ") + event);
//}

void processing_window::onMouseReleased() {
    println("mouseReleased\t",
    mouseX,mouseY,pmouseX,pmouseY,mousePressed,mouseButton);
}

// Method signature 2
//void mouseReleased(MouseEvent event) {
//  println(String("mouseReleased EVENT ") + event);
//}

//void processing_window::onMouseMoved() {  ///not implemented in P2C++
//    println("mouseMoved\t",
//    mouseX,mouseY,pmouseX,pmouseY,mousePressed,mouseButton);
//}

//void processing_window::onMouseDragged() {  ///not implemented in P2C++
//    println("mouseDragged\t",
//    mouseX,mouseY,pmouseX,pmouseY,mousePressed,mouseButton);
//}

//void mouseWheel(MouseEvent event) { ///not implemented in P2C++
//  float e = event->getCount();
//  println("mouseWheel",e);
//}
///data/wb/SCC/__public_git/Processing2C/scripts/procesing2cpp.sh did it

