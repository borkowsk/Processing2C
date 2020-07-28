// Handling of exit from aplication - mainly closing open files!
/////////////////////////////////////////////////////////////////////
void exit()          //it is called whenever a window is closed. 
{
  noLoop();          //For to be sure...
  delay(100);        // it is possible to close window when draw() is still working!
  
  //write(world,modelName+"."+nf((float)StepCounter,5,5));//end state of the system
  if(statisticsLogEnabled)
        CloseStatistics();

  //if(videoExportEnabled) 
  //        CloseVideo();    //Finalise of Video export
          
  println("Thank You");
  super.exit();       //What library superclass have to do at exit
} 

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - EXIT from TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////
