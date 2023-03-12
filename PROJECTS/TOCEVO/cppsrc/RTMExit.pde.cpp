void processing_window::exit()          //it is called whenever a window is closed. 
{
  noLoop();          //For to be sure...
  delay(100);        // it is possible to close window when draw() is still working!
  //write(world,modelName+String(".")+nf((float)StepCounter,5,5));//end state of the system
  
  if(outstat!=nullptr)
  {
    outstat->flush();  // Writes the remaining data to the file
    outstat->close();  // Finishes the file
  }
  
/*_OnlyProcessingBlockBegin
  if(WITH_VIDEO) CloseVideo();    //Finalise of Video export
_OnlyProcessingBlockEnd*/

  println(modelName,"said: Thank You!");
  processing_window_base::exit();       //What library superclass have to do at exit()
} 

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - EXIT TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////
//NOTE! ../../scripts did it

