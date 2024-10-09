// @date 2024-10-10 (last modification)
///   Simulation have to collect and write down statistics from every step.
//*////////////////////////////////////////////////////////////////////////

/*_import_class:Agent */
/*_import_class:World */

PrintWriter outstat;    ///< The main statistics output file.

void initializeStats()  ///< Needs to be global!
{
  String FileName=String("ToC_")+year()+String('.')+nf(month(),2)+String('.')+nf(day(),2)+String('.')+nf(hour(),2)+String('.')+nf(minute(),2)+String('.')+nf(second(),2)+String('.')+millis();
  outstat=createWriter(String("Results/")+FileName+ String(".out"));
  println(outstat,"$STEP\tAlive\t....."); //<-- complete the header fields!
}

int   prevStep=0;           ///< ...
float meanAgentsEn=0;       ///< ...
float meanCells=0;          ///< ...
int   liveAgentsCount=0;    ///< ...
int   liveCellsCount=0;     ///< ...

int   numOfPunishments=0;   ///< ...
float punPerStep=0;         ///< Punishment per step

int   numOfBorns=0;         ///< number of newborns
float bornsPerStep=0;       ///< ...

sarray<int> eatCounters=nullptr;     ///< TU JEST PROBLEM
sarray<int> punCounters=nullptr;     ///< Chyba tablica nie jest akceptowana->TODO???

/// Every(?) step statistics.
void doStatistics(pWorld world)  ///< Need to be global!
{
  if(eatCounters==nullptr) eatCounters=new array<int>(256);
  if(punCounters==nullptr) punCounters=new array<int>(256);
  doStatisticsOnAgents(world->agents);
  doStatisticsOnCells(world->cells);
}

/// Agents statistics after step.
void doStatisticsOnAgents(smatrix<pAgent> agents) ///< Need to be global!
{  
  pAgent curra;
  
  double summ=0;
  liveAgentsCount=0;
    
  for(int i=0;i<eatCounters->length;i++) eatCounters[i]=0; //Zero counters!
  for(int i=0;i<punCounters->length;i++) punCounters[i]=0; //Zero counters!
  
  for(int a=0;a<agents->length;a++)
   for(int b=0;b<agents[a]->length;b++)
    if( (curra=agents[a][b]) != nullptr )
    {
      // Dummy statistic
      summ+=curra->energy;
     
      /*count genoms*/                //assert(curra->genEat<256);	//
      eatCounters[curra->genEat]++;
      punCounters[curra->genPan]++;
      
      liveAgentsCount++;
    }
  
   punPerStep=(float)((numOfPunishments) / ((double)StepCounter-prevStep)); // println(numOfPanishments,StepCounter-prevStep,panPerStep);
   bornsPerStep=(float)((numOfBorns) / ((double)StepCounter-prevStep));
   meanAgentsEn=(float)(summ/liveAgentsCount);
   
   if(outstat!=nullptr)
      print(outstat,StepCounter+String("\t")+liveAgentsCount+String("\t")+(summ/liveAgentsCount)+String("\t")+punPerStep+String("\t")+bornsPerStep);
   
   prevStep=StepCounter;
   
   numOfPunishments=0; //Liczone "on run"
   numOfBorns=0; //number of newborns
   // outstat should be closed in exit() --> see Exit->pde
}

/// Cells statistics after step. 
void doStatisticsOnCells(smatrix<int> cells) ///< Need to be global!
{  
  long summ=0;
  int curr;
  
  liveCellsCount=0;
  
  for(int a=0;a<cells->length;a++)
   for(int b=0;b<cells[a]->length;b++)
    if( (curr=cells[a][b]) != 0 )
    {
      // Dummy stat
      summ+=curr;
      
      //if(curr==1) 
      //.....THIS PART IS FOR YOU!
      
      liveCellsCount++; //Alive cells
    }
  
   if(liveCellsCount>0)
   {
      meanCells=summ/liveCellsCount;
      if(outstat!=nullptr)
         println(outstat,String("\t")+StepCounter+String("\t")+liveCellsCount+String("\t")+meanCells);
   }
   else
   {
     simulationRun=false;
     if(outstat!=nullptr)
        println(outstat,String("\t")+StepCounter+String("\t")+liveCellsCount+ String("\tFINISHED"));
   }
   // outstat should be closed in exit() --> see Exit->pde
}


//*///////////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: STATISTICS FOR TragedyOfCommons
//*///////////////////////////////////////////////////////////////////////////////////////////////////////////
//NOTE! /data/wb/SCC/public/Processing2C/scripts did it 2024-10-09 23:57:26

