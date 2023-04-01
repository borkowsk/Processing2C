/// Events example.
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// base on Processing examples
/// ORIGINAL FILE: "EVENTS.pde"
//*///////////////////////////////////////////////////
// * Click on the window to give it focus,
// * Or press the 'B' key.
// * Also click one of mouse buttons
// Both setup() and draw() are implemented, as well set of events handler.
//

void setup() {
  size(100,100);
  frameRate(100); // Apart this fraquency,
                  // events are get only 10 times per second! (?)
}

int test()
{
  int blue=1;     //It hides library symbol! But dont panic, this is a test only.
  return color(255,255,255);// 'Suspicious' warning here is also for test only.
}

void draw() {
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
      println("keyPressed &&","'"+key+"'","detected in draw function - fill(RED)");
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

void keyPressed() {
    println("keyPressed\t", 
    "'"+key+"'", keyCode,keyPressed);
}

// Method signature 2
//void keyPressed(KeyEvent event) { ///not implemented in P2C++
//  println("keyPressed EVENT " + event);
//}

void keyReleased() {
    println("keyReleased\t", 
    "'"+key+"'",int(key),keyCode,keyPressed); 
}

// Method signature 2
//void keyReleased(KeyEvent event) { ///not implemented in P2C++
//  println("keyReleased EVENT " + event);
//}

void mouseClicked() {
    println("mouseClicked\t",
    mouseX,mouseY,pmouseX,pmouseY,mousePressed,mouseButton);
}

// Method signature 2
//void mouseClicked(MouseEvent event) { ///not implemented in P2C++
//  println("mouseClicked EVENT " + event);
//}

void mousePressed() {
    println("mousePressed\t",
    mouseX,mouseY,pmouseX,pmouseY,mousePressed,mouseButton);
}

// Method signature 2
//void mousePressed(MouseEvent event) { ///not implemented in P2C++
//  println("mousePressed EVENT " + event);
//}

void mouseReleased() {
    println("mouseReleased\t",
    mouseX,mouseY,pmouseX,pmouseY,mousePressed,mouseButton);
}

// Method signature 2
//void mouseReleased(MouseEvent event) {
//  println("mouseReleased EVENT " + event);
//}

//void mouseMoved() {  ///not implemented in P2C++
//    println("mouseMoved\t",
//    mouseX,mouseY,pmouseX,pmouseY,mousePressed,mouseButton);
//}

//void mouseDragged() {  ///not implemented in P2C++
//    println("mouseDragged\t",
//    mouseX,mouseY,pmouseX,pmouseY,mousePressed,mouseButton);
//}

//void mouseWheel(MouseEvent event) { ///not implemented in P2C++
//  float e = event.getCount();
//  println("mouseWheel",e);
//}
