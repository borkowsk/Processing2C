/// @date 2024-10-10 (last modification)
/// World is a one of two central class of each ABM model.
//*///////////////////////////////////////////////////////

/*_import_class:Agent */

/// @details 
///         We have two layer - environment resources cells and agents. 
///         
/*_import_class:World */

// More elaborated functionalities are defined as stand-alone functions,
// not as methods because of not enough flexible syntax of Processing
//*/////////////////////////////////////////////////////////////////////////

int StepCounter=0; ///< Global step counter.

void initializeModel(World world)   ///< Need to be global!
{
  initializeCells(world.cells);
  initializeAgents(world.agents);
}

void visualizeModel(World world)    ///< Need to be global!
{
  noStroke();
  visualizeCells(world.cells);
  visualizeAgents(world.agents);
  float maxL=log(side*side);
  
  fill(128);noStroke();rect(side*cwidth,0,50,eatCounters.length);
  fill(200);noStroke();rect(side*cwidth,eatCounters.length,50,punCounters.length);
  strokeWeight(1);
  
  for(int i=0;i<eatCounters.length;i++)
  if(eatCounters[i]>0)
  {
    float len=log(eatCounters[i]) / maxL*50.0; //println(len);
    stroke(i,0,128);
    line(side*cwidth,i,side*cwidth+len,i);
  }
  
  for(int i=0;i<punCounters.length;i++)
  if(punCounters[i]>0)
  {
    float len=log(punCounters[i]) / maxL*50.0; //println(len);
    stroke(128,0,128+i);
    line(side*cwidth,eatCounters.length+i,side*cwidth+len,eatCounters.length+i);
  }
  
}

void changes(World world)   ///< Need to be global!
{
  cleanDeaths(world.agents);
  synchChangeCells(world.cells,world.cells); //No intercells interactions
  changeAgents(world.agents,world.cells); //Agents influence the resource layer
}

void modelStep(World world) ///< Need to be global!
{
   changes(world);
   
   StepCounter++;
}

//*/////////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - ABM: WORLD FOR TragedyOfCommons
//*/////////////////////////////////////////////////////////////////////////////////////////////
