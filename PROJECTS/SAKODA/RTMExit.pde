/// ABM model of segregation (test project for Processing2C)
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: RTMExit.pde
//////////////////////////////////////////////////////////////////////////////////////////
void exit()          //it is called whenever a window is closed. 
{
  noLoop();          //For to be sure...
  delay(100);        // it is possible to close window when draw() is still working!
  //write(world,modelName+"."+nf((float)StepCounter,5,5));//end state of the system
  
  if(outstat!=null)
  {
    outstat.flush();  // Writes the remaining data to the file
    outstat.close();  // Finishes the file
  }
  
  //if(WITH_VIDEO) CloseVideo();    //Finalise of Video export
  
  println(modelName,"said: Thank You!");
  super.exit();       //What library superclass have to do at exit()
} 

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - EXIT TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////
