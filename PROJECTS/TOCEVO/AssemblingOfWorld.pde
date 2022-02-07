//*   World is a one of two central class of each ABM model
//*/////////////////////////////////////////////////////////////
int StepCounter=0;

class World 
{
  int cells[][];//Two dimensional array of resources
  Agent agents[][];//Two dimensional array of agents
  
  World(int side)//Constructor of the World
  {
    cells=new int[side][side];
    agents=new Agent[side][side];
  }
}

//More alaborated functionalities are defined as stand-alone functions,
//not as methods because of not enought flexible syntax of Processing
///////////////////////////////////////////////////////////////////////////

void initializeModel(World world)
{
  initializeCells(world.cells);
  initializeAgents(world.agents);
}

void visualizeModel(World world)
{
  noStroke();
  visualizeCells(world.cells);
  visualizeAgents(world.agents);
  float maxL=log(side*side);
  
  fill(128);noStroke();rect(side*cwidth,0,50,eatCounters.length);
  fill(200);noStroke();rect(side*cwidth,eatCounters.length,50,panCounters.length);
  strokeWeight(1);
  
  for(int i=0;i<eatCounters.length;i++)
  if(eatCounters[i]>0)
  {
    float len=log(eatCounters[i])/maxL*50.0; //println(len);
    stroke(i,0,128);
    line(side*cwidth,i,side*cwidth+len,i);
  }
  
  for(int i=0;i<panCounters.length;i++)
  if(panCounters[i]>0)
  {
    float len=log(panCounters[i])/maxL*50.0; //println(len);
    stroke(128,0,128+i);
    line(side*cwidth,eatCounters.length+i,side*cwidth+len,eatCounters.length+i);
  }
  
}

void changes(World world)
{
  cleanDeaths(world.agents);
  synchChangeCells(world.cells,world.cells);//No intercells interactions
  changeAgents(world.agents,world.cells);//Agents influence the resource layer
}

void modelStep(World world)
{
   changes(world);
   
   StepCounter++;
}

///////////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - ABM: WORLD FOR TragedyOfCommons
///////////////////////////////////////////////////////////////////////////////////////////////
