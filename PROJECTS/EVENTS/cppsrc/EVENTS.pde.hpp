/// Events example.
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// base on Processing examples
/// ORIGINAL FILE: "EVENTS.pde"
// @date 2024-10-15 (last change)
//*///////////////////////////////////////////////////
// * Click on the window to give it focus,
// * Or press the 'B' key.
// * Also click one of mouse buttons
// Both setup() and draw() are implemented, as well set of events handler.
//

void processing_window::setup() {
  size(100,100);
  setFrameRate(100); // Apart this fraquency,
                  // events are get only 10 times per second! (?)
}

int test()
{
  int blue=1;     //It hides library symbol! But dont panic, this is a test only.
  return color(255,255,255);// 'Suspicious' warning here is also for test only.
}

void processing_window::draw() {
  if (keyPressed) {
    if (key == 'b' || key == 'B') {
      fill(0);    
      println("keyPressed && 'B' detected in draw function - fill(BLACK)");
    }
    else
    if (key == ' ') {
      fill(255,0,0);    
      println("keyPressed && ' ' detected in draw function - fill(RED)");
    }
    else 
    {
      fill(255);
      println("keyPressed &&",String("'")+key+ String("'"),"detected in draw function - fill(RED)");
    }
    //keyPressed=false;//NOW IS PROCESSED.
  } 
  else fill(255);    //println("keyPressed not detected in draw function - fill(WHITE)");

  
  if (mousePressed && (mouseButton == LEFT)) {
    background(0); println("mousePressed && LEFT detected in draw function");
  } else if (mousePressed && (mouseButton == RIGHT)) {
    background(255);  println("mousePressed && RIGHT detected in draw function");
  } else if (mousePressed && (mouseButton == 3)) {
    background(255,0,0); println("mousePressed && MIDLE detected in draw function");
  } else if (mousePressed) {
    background(126); println("mousePressed &&",mouseButton,"detected in draw function");
  }

  if(mousePressed){
      println("mousePressed detected in draw function");
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
//MADE NOTE: ../../scripts did it 2024-10-15 16:10:55 !

