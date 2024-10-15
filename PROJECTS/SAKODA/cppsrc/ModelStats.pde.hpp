/// ABM model of segregation (test project for Processing2C).
/// ORIGINAL FILE: ModelStatistics->pde
/// @date 2024-10-15 (last change)
//*///////////////////////////////////////////////////////////////////////////////////////
// Simulation have to collect and write down statistics from every step.
//*///////////////////////////////////////////////////////////////////////////////////////

/*_import_class:Agent */
/*_import_class:World */

PrintWriter outstat;  ///< Global statistic log stream (text file).

void initializeStats() { ///< @note Needs to be global!
  String FileName=modelName+=String("_s")+side+String("d")+density+String("i")+Number_of_identities
                           +String("_")+year()+String('.')+nf(month(),2)+String('.')+nf(day(),2)+String('.')+nf(hour(),2)+String('.')+nf(minute(),2)+String('.')+nf(second(),2)+String('.')+millis();
  outstat=createWriter(FileName+ String(".out"));
  println(outstat,"$STEP\tAlive\tStress\t"); //<-- complete the header fields!
}

float meanStress=0;  ///< @note Should be globally visible!
int   liveCount=0;   ///< @note Should be globally visible!

void doStatistics(pWorld world) { ///< @note Needs to be global!
  doStatisticsOnAgents(world->agents);
}

void doStatisticsOnAgents(sarray<pAgent> agents) {  ///< @note Needs to be global!
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

void doStatisticsOnAgents(smatrix<pAgent> agents) { ///< @note Needs to be global!
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
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
//*/////////////////////////////////////////////////////////////////////////////////////////
//MADE NOTE: ../../scripts did it 2024-10-15 16:10:56 !

