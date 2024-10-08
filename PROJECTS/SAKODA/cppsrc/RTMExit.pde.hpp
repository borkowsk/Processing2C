/// ABM model of segregation (test project for Processing2C)
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// @date 2024-10-04 (last change)
/// ORIGINAL NAME OF @file: RTMExit->pde
//*////////////////////////////////////////////////////////////////////////////////////////

void processing_window::exit()          //it is called whenever a window is closed. 
{
  noLoop();          //For to be sure...
  //write(world,modelName+String(".")+nf((float)StepCounter,5,5));//end state of the system
  delay(100);        //???
  
  if(outstat!=nullptr)
  {
    outstat->flush();  // Writes the remaining data to the file
    outstat->close();  // Finishes the file
  }
  
  //if(WITH_VIDEO) CloseVideo();    //Finalise of Video export
  
  save("exit.png");
  println(modelName,"said: Thank You!");
  processing_window_base::exit();       //What library superclass have to do at exit()
} 

//*/////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - EXIT TEMPLATE
//*/////////////////////////////////////////////////////////////////////////////////////////
//NOTE! ../../scripts did it 2024-10-04 13:54:21

