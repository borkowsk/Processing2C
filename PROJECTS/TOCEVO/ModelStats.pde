//*   Simulation have to collect and write down statistics from every step
//*/////////////////////////////////////////////////////////////////////////////////////
PrintWriter outstat;

void initializeStats()
{
  String FileName="ToC_"+year()+'.'+nf(month(),2)+'.'+nf(day(),2)+'.'+nf(hour(),2)+'.'+nf(minute(),2)+'.'+nf(second(),2)+'.'+millis();
  outstat=createWriter("Results/"+FileName+".out");
  outstat.println("$STEP\tAlive\t.....");//<-- complete the header fields!
}

int   prevStep=0;
float meanAgentsEn=0;
float meanCells=0;
int   liveAgentsCount=0;
int   liveCellsCount=0;

int   numOfPanishments=0;
float panPerStep=0;///Panishment per step

int   numOfBorns=0;//number of newborns
float bornsPerStep=0;

int[] eatCounters=new int[256];   
int[] panCounters=new int[256];   

void doStatistics(World world)
{
  doStatisticsOnAgents(world.agents);
  doStatisticsOnCells(world.cells);
}

void doStatisticsOnAgents(Agent[][] agents)
{  
  Agent curra;
  
  double summ=0;
  liveAgentsCount=0;
    
  for(int i=0;i<eatCounters.length;i++) eatCounters[i]=0;//Zero counters!
  for(int i=0;i<panCounters.length;i++) panCounters[i]=0;//Zero counters!
  
  for(int a=0;a<agents.length;a++)
   for(int b=0;b<agents[a].length;b++)
    if( (curra=agents[a][b]) != null )
    {
      //Dummy statistic
      summ+=curra.energy;
     
      /*count genoms*/                //assert curra.genEat<256;
      eatCounters[curra.genEat]++;
      panCounters[curra.genPan]++;
      
      liveAgentsCount++;
    }
  
   panPerStep=(float)((numOfPanishments)/((double)StepCounter-prevStep)); // println(numOfPanishments,StepCounter-prevStep,panPerStep);
   bornsPerStep=(float)((numOfBorns)/((double)StepCounter-prevStep));
   meanAgentsEn=(float)(summ/liveAgentsCount);
   
   if(outstat!=null)
      outstat.print(StepCounter+"\t"+liveAgentsCount+"\t"+(summ/liveAgentsCount)+"\t"+panPerStep+"\t"+bornsPerStep);
   
   prevStep=StepCounter;
   
   numOfPanishments=0;//Liczone "on run"
   numOfBorns=0;//number of newborns
   //outstat should be closed in exit() --> see Exit.pde
}

void doStatisticsOnCells(int[][] cells)
{  
  long summ=0;
  int curr;
  
  liveCellsCount=0;
  
  for(int a=0;a<cells.length;a++)
   for(int b=0;b<cells[a].length;b++)
    if( (curr=cells[a][b]) != 0 )
    {
      //Dummy stat
      summ+=curr;
      
      //if(curr==1) 
      //.....THIS PART IS FOR YOU!
      
      liveCellsCount++;//Alive cells
    }
  
   if(liveCellsCount>0)
   {
      meanCells=summ/liveCellsCount;
      if(outstat!=null)
         outstat.println("\t"+StepCounter+"\t"+liveCellsCount+"\t"+meanCells);
   }
   else
   {
     simulationRun=false;
     if(outstat!=null)
        outstat.println("\t"+StepCounter+"\t"+liveCellsCount+"\tFINISHED");
   }
   //outstat should be closed in exit() --> see Exit.pde
}


//*///////////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - ABM: STATISTICS FOR TragedyOfCommons
//*///////////////////////////////////////////////////////////////////////////////////////////////////////////
