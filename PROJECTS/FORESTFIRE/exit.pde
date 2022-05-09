void exit() //it is called whenever a window is closed. 
{
  noLoop();    // For to be sure...
  delay(100);  // it is quite possible to close window when draw( ) is currently working!
  Log.flush(); // Writes the remaining data to the file
  Log.close(); // Finishes the file
  save("exit.png");
  println("Thank You");
  super.exit(); //What library superclass have to do at exit
} 
