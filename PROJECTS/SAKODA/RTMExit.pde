/// ABM model of segregation (test project for Processing2C).
/// ORIGINAL NAME OF @file: RTMExit.pde
/// @date 2024-10-14 (last change)
//*/////////////////////////////////////////////////////////////////////////////////////

/// @brief it is called whenever a window is closed. 
void exit()          
{
  noLoop();          // For to be sure...
  //write(world,modelName+"."+nf((float)StepCounter,5,5)); //end state of the system
  delay(100);        // ???
  
  if(outstat!=null)
  {
    outstat.flush();  // Writes the remaining data to the file
    outstat.close();  // Finishes the file
  }
  
  //if(WITH_VIDEO) CloseVideo();    //Finalise of Video export
  
  save("exit.png");
  println(modelName,"said: Thank You!");
  super.exit();       //What library superclass have to do at exit()
} 

//*/////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - EXIT TEMPLATE
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
//*/////////////////////////////////////////////////////////////////////////////////////////
