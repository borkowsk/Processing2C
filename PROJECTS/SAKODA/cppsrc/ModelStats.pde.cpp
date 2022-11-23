/// ABM model of segregation (test project for Processing2C)
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: ModelStatistics->pde
//*///////////////////////////////////////////////////////////////////////////////////////
// Simulation have to collect and write down statistics from every step
//*///////////////////////////////////////////////////////////////////////////////////////
PrintWriter outstat;

void initializeStats() { ///< Need to be global!
  String FileName=modelName+=String("_s")+side+String("d")+density+String("i")+Number_of_identities
                           +String("_")+year()+String('.')+nf(month(),2)+String('.')+nf(day(),2)+String('.')+nf(hour(),2)+String('.')+nf(minute(),2)+String('.')+nf(second(),2)+String('.')+millis();
  outstat=createWriter(FileName+ String(".out"));
  println(outstat,"$STEP\tAlive\tStress\t"); //<-- complete the header fields!
}

float meanStress=0;
int   liveCount=0;

void doStatistics(pWorld world) { ///< Need to be global!
  doStatisticsOnAgents(world->agents);
}

void doStatisticsOnAgents(sarray<pAgent> agents) {  ///< Need to be global!
  pAgent curra;
  double summ=0;
  liveCount=0;
  
  for(int a=0;a<agents->length;a++)
    if( (curra=agents[a]) != nullptr )
    {
      summ+=curra->stress;
     
      //Inne statystyki
      //TODO
       
      liveCount++;
    }
  
   if(outstat!=nullptr)
      println(outstat,StepCounter+String("\t")+liveCount+String("\t")+(summ/liveCount)+ String("\t"));
   
   meanStress=(float)(summ/liveCount);
   
   //outstat should be closed in exit() --> see Exit->pde
}

void doStatisticsOnAgents(smatrix<pAgent> agents) { ///< Need to be global!
  pAgent curra;
  double summ=0;
  liveCount=0;
  
  for(int a=0;a<agents->length;a++)
   for(int b=0;b<agents[a]->length;b++)
    if( (curra=agents[a][b]) != nullptr )
    {
      summ+=curra->stress;
     
      //Inne statystyki
      //TODO
      
      liveCount++;
    }
  
   if(outstat!=nullptr)
      println(outstat,StepCounter+String("\t")+liveCount+String("\t")+(summ/liveCount)+ String("\t"));
   
   meanStress=(float)(summ/liveCount);
   
   //outstat should be closed in exit() --> see Exit->pde
}

//*/////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: STATISTICS LOG TEMPLATE
//*/////////////////////////////////////////////////////////////////////////////////////////
//../../scripts did it

