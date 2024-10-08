// @file
/// @date 2024-10-10 (last modification)
/// Support for exiting the program when something needs to be cleaned up before doing so.
//*///////////////////////////////////////////////////////////////////////////////////////

void exit()   // It is called whenever a window is closed. 
{
  save("exit.png");
  noLoop();   // For to be sure... (but no more screen update so!!!)

  delay(100); // it is possible to close window when draw() is still working!
  
  //write(world,modelName+"."+nf((float)StepCounter,5,5));//end state of the system
  
  if(outstat!=null)
  {
    outstat.flush();  // Writes the remaining data to the file
    outstat.close();  // Finishes the file
  }
  
/*_OnlyProcessingBlockBegin*/
  if(WITH_VIDEO) CloseVideo();    //Finalise of Video export (may take a time)
/*_OnlyProcessingBlockEnd*/

  println(modelName,"said: Thank You!");
  super.exit();       //What library superclass have to do at exit()
} 

//*//////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - EXIT TEMPLATE
//*//////////////////////////////////////////////////////////////////////////////
