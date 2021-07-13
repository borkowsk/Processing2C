//Processing to C++ converter /data/wb/SCC/__public_git/Processing2C/scripts/procesing2cpp.sh
//Source: EVENTS.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
//#include "processing_inlines.hpp" //is optional. Use when project is already compilable
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

/// Events example.
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// base on Processing examples
/// ORIGINAL FILE: EVENTS->pde
/////////////////////////////////////////////////////
// Click on the window to give it focus,
// and press the 'B' key.
// Also click one of mouse buttons

void processing_window::draw() {
  if (keyPressed) {
    if (key == 'b' || key == 'B') {
      fill(0);
    }
  } else {
    fill(255);
  }
  
  if (mousePressed && (mouseButton == LEFT)) {
    background(0);
  } else if (mousePressed && (mouseButton == RIGHT)) {
    background(255);
  } else if (mousePressed) {
    background(126);
  }
  
  rect(25, 25, 50, 50);
}

void processing_window::keyPressed() {
    println("keyPressed\t", 
    key, keyCode);
}

// Method signature 2
//void keyPressed(KeyEvent event) {
//  println(String("keyPressed EVENT ") + event);
//}

void keyReleased() {
    println("keyReleased\t", 
    key, keyCode);
}

// Method signature 2
//void keyReleased(KeyEvent event) {
//  println(String("keyReleased EVENT ") + event);
//}

void processing_window::mouseClicked() {
    println("mouseClicked\t",
    mouseX,mouseY,pmouseX,pmouseY,mousePressed,mouseButton);
}

// Method signature 2
//void mouseClicked(MouseEvent event) {
//  println(String("mouseClicked EVENT ") + event);
//}

void mousePressed() {
    println("mousePressed\t",
    mouseX,mouseY,pmouseX,pmouseY,mousePressed,mouseButton);
}

// Method signature 2
//void mousePressed(MouseEvent event) {
//  println(String("mousePressed EVENT ") + event);
//}

void mouseReleased() {
    println("mouseReleased\t",
    mouseX,mouseY,pmouseX,pmouseY,mousePressed,mouseButton);
}

// Method signature 2
//void mouseReleased(MouseEvent event) {
//  println(String("mouseReleased EVENT ") + event);
//}

void mouseMoved() {
    println("mouseMoved\t",
    mouseX,mouseY,pmouseX,pmouseY,mousePressed,mouseButton);
}

void mouseDragged() 
{
    println("mouseDragged\t",
    mouseX,mouseY,pmouseX,pmouseY,mousePressed,mouseButton);
}

//void mouseWheel(MouseEvent event) {
//  float e = event->getCount();
//  println("mouseWheel",e);
//}
///data/wb/SCC/__public_git/Processing2C/scripts/procesing2cpp.sh did it

