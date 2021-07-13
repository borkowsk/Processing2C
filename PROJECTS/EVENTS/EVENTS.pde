/// Events example.
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// base on Processing examples
/// ORIGINAL FILE: EVENTS.pde
/////////////////////////////////////////////////////
// Click on the window to give it focus,
// and press the 'B' key.
// Also click one of mouse buttons

void draw() {
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

void keyPressed() {
    println("keyPressed\t", 
    key, keyCode);
}

// Method signature 2
//void keyPressed(KeyEvent event) {
//  println("keyPressed EVENT " + event);
//}

void keyReleased() {
    println("keyReleased\t", 
    key, keyCode);
}

// Method signature 2
//void keyReleased(KeyEvent event) {
//  println("keyReleased EVENT " + event);
//}

void mouseClicked() {
    println("mouseClicked\t",
    mouseX,mouseY,pmouseX,pmouseY,mousePressed,mouseButton);
}

// Method signature 2
//void mouseClicked(MouseEvent event) {
//  println("mouseClicked EVENT " + event);
//}

void mousePressed() {
    println("mousePressed\t",
    mouseX,mouseY,pmouseX,pmouseY,mousePressed,mouseButton);
}

// Method signature 2
//void mousePressed(MouseEvent event) {
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
//  float e = event.getCount();
//  println("mouseWheel",e);
//}
