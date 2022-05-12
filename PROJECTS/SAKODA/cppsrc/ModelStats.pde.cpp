//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: ModelStats.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "processing_string.hpp"  //Processing::String class
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_files.hpp" //...is optional. Should be deleted when not needed.
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

/// ABM model of segregation (test project for Processing2C)
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: ModelStatistics->pde
/////////////////////////////////////////////////////////////////////////////////////////
// Simulation have to collect and write down statistics from every step
/////////////////////////////////////////////////////////////////////////////////////////
PrintWriter outstat;

void initializeStats() { ///
  String FileName=modelName+=String("_s")+side+String("d")+density+String("i")+Number_of_identities
                           +String("_")+year()+String('.')+nf(month(),2)+String('.')+nf(day(),2)+String('.')+nf(hour(),2)+String('.')+nf(minute(),2)+String('.')+nf(second(),2)+String('.')+millis();
  outstat=createWriter(FileName+ String(".out"));
  println(outstat,"$STEP\tAlive\tStress\t");//<-- complete the header fields!
}

float meanStress=0;
int   liveCount=0;

void doStatistics(pWorld world) { ///
  doStatisticsOnAgents(world->agents);
}

void doStatisticsOnAgents(sarray<pAgent> agents) {  ///
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

void doStatisticsOnAgents(smatrix<pAgent> agents) {  ///
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

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: STATISTICS LOG TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////
//../../scripts did it

