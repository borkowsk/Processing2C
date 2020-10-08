//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: ModelStats.pde
#include "processing_templates.hpp"
//#include "processing_inlines.hpp" //is optional. Use when project is already compilable
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

//   Step by step statistics of RTSI model utilized cell geometry
////////////////////////////////////////////////////////////////////
PrintWriter outstat; ///May be used also autside this file! 

void initializeStats()
{
  String FileName=modelName+=String("_")+year()+String('.')+nf(month(),2)+String('.')+nf(day(),2)+String('.')+nf(hour(),2)+String('.')+nf(minute(),2)+String('.')+nf(second(),2)+String('.')+millis();
  outstat=createWriter(FileName+ String(".out"));
  print(outstat,"$STEP\tAlive\tMeanOp\t+StdDevOp\tMinOp\tMaxOp\tmeanABSError"
                + String("\tlink_up\tlink_dw\tsensor_up\tsensor_dw\tMeanSensor\tUsedSensors\tMeanSRelia\tMeanSReal\tmaxInfos\tmaxKnowl")
                  );//<-- complete the header line!
  println(outstat,"\tHistTooLow\tH0\tH1\tH2\tH3\tH4\tH5\tH6\tH7\tH8\tH9\tHistTooHig");//At the end of line is histogram of links weights               
  statisticsLogEnabled=true;
}

// Global statistics & their histories
int   liveCount=0;//Właściwie niepotrzebne w tym modelu bo nie giną TODO?

float meanOpinion=0;  ///May be used also autside this file!
pSample mnOpinions=new Sample("mnOpinions");

float stddOpinion=0;  ///visible autside this file!
pSample stdOpinionsPlus=new Sample("stdOpinionsPlus");
pSample stdOpinionsMinus=new Sample("stdOpinionsMinus");

float minOpinion=0;  ///visible autside this file!
pSample minOpinions=new Sample("minOpinions");

float maxOpinion=0;  ///visible autside this file!
pSample maxOpinions=new Sample("maxOpinions");
  
float meanSensor=0;  ///visible autside this file!
int   UsedSensors=0;  ///visible autside this file!
pSample mnSensors=new Sample("mnSensors");
pSample ratioOfSensors=new Sample("ratioOfSensors");//history od=f UsedSensors

float meanSRealt=0;  ///visible autside this file!
pSample mnRealities=new Sample("mnRealities");

float meanSRelia=0;  ///visible autside this file!
pSample mnReliabilities=new Sample("mnReliabilities");

//Historie błędów 
//int     REALITY=2; //Skąd bierzemy "realność"? 0-bierze pomiar spod nóg, 1-średni pomiar, 2-średnią opinie, 3-średnią realność TODO
float meanError=0; ///Co jest błędem jest zależne od tego co jest realnością!
pSample meanErrors=new Sample("mn(abs(Opinion[a,b]-Sensor[a,b]))");

pSample mnDiffOwnReal=new Sample("mnDiffOwnReal");  ///visible autside this file!
pSample mnDiffMnSensor=new Sample("mnDiffMnSensor");  ///visible autside this file!
pSample mnDiffMnOpinion=new Sample("mnDiffMnOpinion");  ///visible autside this file!
pSample mnDiffMnReal=new Sample("mnDiffMnReal");  ///visible autside this file!

// Global DYNAMICS
int    link_up=0;  ///When weight goes up
int    link_dw=0;  ///When weight goes down
int  sensor_up=0;  ///visible autside this file!
int  sensor_dw=0;  ///visible autside this file!

void doStatistics(pWorld world)
{
  doStatisticsOnAgents(world->agents);
  doStatisticsOnLinks(world->agents,allLinks);//USE ADDITIONAL STATISTICS 
}

void doStatisticsOnAgents(smatrix<pAgent> agents)
{  
  pAgent curra;
  double sens=0;
  double reli=0;
  double real=0;
  double dsum=0;//Suma abs(różnic)
  int opinCount=0;//May be alive but have no opinion!
  int sensCount=0;//May be alive but have never used their sensor!
  int derrCount=0;//May have opinion, but not sensor!
  liveCount=0;
  pSample stepOpinions=new Sample("stepOpinions");
  
  for(int a=0;a<agents->length;a++)
   for(int b=0;b<agents[a]->length;b++)
    if( (curra=agents[a][b]) != nullptr )
    {
      //Simple statistic
      double val=curra->getOpinion(0); 
      
      if(val!=INF_NOT_EXIST)
      {
        stepOpinions->addValue((float)(val));
        opinCount++;
      }
      
      double vre=curra->sensors[0]->lastMeasurement;//from last usage of getSensor(0,theWorld);
      
      if(vre!=INF_NOT_EXIST)
      {
        sens+=vre;
        sensCount++;
      }
      
      if(val!=INF_NOT_EXIST && vre!=INF_NOT_EXIST)
      {
        dsum+=std::abs(vre-val);//MN(abs(Opinion[a,b]-Sensor[a,b]))
        derrCount++;
      }
      
      reli+=curra->getReliability(0);
      real+=curra->getReality(0,theWorld);
      
      liveCount++;
    }
                                                                    assert(opinCount==stepOpinions->numOfElements());	//
   meanOpinion=stepOpinions->getMean();
   stddOpinion=stepOpinions->getStdDev();
   minOpinion=stepOpinions->getMin();
   maxOpinion=stepOpinions->getMax();
        
   if(sensCount>0)
   {
     meanSensor=(float)(sens/sensCount);
     UsedSensors=sensCount;
   }
   else
   {
     meanSensor=INF_NOT_EXIST;
     UsedSensors=0;
   }     
   
   if(derrCount>0)
     meanError=(float)(dsum/derrCount);
   else
     meanError=INF_NOT_EXIST;
   
   if(liveCount>0)
   {
     meanSRelia=(float)(reli/liveCount);
     meanSRealt=(float)(real/liveCount);
   }
   else
   {
     meanSRelia=INF_NOT_EXIST;
     meanSRealt=INF_NOT_EXIST;
   }
   
   
   mnSensors->addValue(meanSensor);
   if(UsedSensors>0)
     ratioOfSensors->addValue( UsedSensors/(1.0*SIDE*SIDE));              
   else
     ratioOfSensors->addValue( INF_NOT_EXIST );                                      //println(UsedSensors/(1.0*SIDE*SIDE));
     
   mnReliabilities->addValue(meanSRelia);
   mnRealities->addValue(meanSRealt);
   mnOpinions->addValue(meanOpinion);
   minOpinions->addValue(minOpinion);
   maxOpinions->addValue(maxOpinion);
   
   meanErrors->addValue(meanError);
   
   if(meanOpinion!=INF_NOT_EXIST && stddOpinion!=INF_NOT_EXIST)
   {
     stdOpinionsPlus->addValue(meanOpinion+stddOpinion);
     stdOpinionsMinus->addValue(meanOpinion-stddOpinion);
   }
   else
   {
     stdOpinionsPlus->addValue(INF_NOT_EXIST);
     stdOpinionsMinus->addValue(INF_NOT_EXIST);     
   }
   
   if(statisticsLogEnabled)
   {
     print(outstat,theWorld->StepCounter+String("\t")+liveCount+String("\t")+meanOpinion+String("\t")+stddOpinion+String("\t")+minOpinion+String("\t")+maxOpinion+String("\t")+meanError
                       +String("\t")+link_up+String("\t")+link_dw+String("\t")+sensor_up+String("\t")+sensor_dw+ String("\t")
                       +sens/UsedSensors+String("\t")+UsedSensors+String("\t")+reli/liveCount+String("\t")+real/liveCount+String("\t")+Info_maxInfos+String("\t")+Info_maxKnowl+ String("\t"));
     print(outstat,forLog->outsideLow+ String("\t"));
     for(int i=0;i<forLog->buckets->length;i++)
            print(outstat,forLog->buckets[i]+ String("\t"));
     println(outstat,forLog->outsideHig);
   }
        
   link_up=0;//When weight goes up
   link_dw=0;//When weight goes down
   sensor_up=0;
   sensor_dw=0;
}

// STATYSTYKI SIECI
/////////////////////////////////////////////////////////////
pFrequencies forLog=new Frequencies( 10,0.0,1.0,"frequenciesForLog");
pFrequencies forVis=new Frequencies(100,0.0,1.0,"frequenciesForVis");

int doStatisticsOnLinks(smatrix<piVisNode> nodes,pLinkFilter filter)
{
  int counter=0;
  forLog->reset();
  forVis->reset();
  
  for(int i=0;i<nodes->length;i++)
    for(int j=0;j<nodes[i]->length;j++)
    {
      piVisNode Source=nodes[i][j];
      
      if(Source!=nullptr)
      {
        //float X=Source->posX();
        //float Y=Source->posY();
        sarray<pLink> links=Source->getConns(filter);
        int n=links->length;
        
        for(int k=0;k<n;k++)
        {
          //float Xt=links[k]->target->posX();
          //float Yt=links[k]->target->posY();//For counting distances
          
          float value=links[k]->weight;
          forLog->addValue(value);
          forVis->addValue(value);
          
          counter++;
        }
      }
    }
  
  return counter;
}


void CloseStatistics()
//outstat should be closed in exit() --> see RTMExit->pde
{
  if(outstat!=nullptr && statisticsLogEnabled)
  {
    outstat->flush();  // Writes the remaining data to the file
    outstat->close();  // Finishes the file
    statisticsLogEnabled=false;
    outstat=nullptr;
  }
}

static bool        statisticsLogEnabled=false;//initializeStats() will set up it for true

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - STATISTICS LOG from TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////

void doStatisticsOnAgents(sarray<pAgent> agents)
{  
   assert(false);	//  "Implementation out of date";
}/*
  pAgent curra;
  double summ=0;
  double sens=0;
  double reli=0;
  double real=0;
  liveCount=0;
  int opinCount=0;//May be alive but have no opinion!
  int sensCount=0;//May be alive but have never used their sensor!
  
  for(int a=0;a<agents->length;a++)
    if( (curra=agents[a]) != nullptr )
    {
      //Simple statistic
      double val=curra->getOpinion(0); 
      if(val!=INF_NOT_EXIST)
      {
        summ+=val;
        opinCount++;
      }
      
      val=curra->sensors[0]->lastMeasurement;//from last usage of getSensor(0,theWorld);
      
      if(val!=INF_NOT_EXIST)
      {
        sens+=val;
        sensCount++;
      }
      
      reli+=curra->getReliability(0);
      real+=curra->getReality(0,theWorld);
      
      liveCount++;
    }
   
   //doStatisticsOnLinks(agents,allLinks);
    
   if(statisticsLogEnabled)
       println(outstat,theWorld->StepCounter+String("\t")+liveCount+String("\t")+(summ/opinCount)
                       +String("\t")+link_up+String("\t")+link_dw+String("\t")+sensor_up+String("\t")+sensor_dw+ String("\t")
                       +sens/liveCount+String("\t")+reli/liveCount+String("\t")+real/liveCount+String("\t")+Info_maxInfos+String("\t")+Info_maxKnowl);
       
   meanOpinion=(float)(summ/liveCount);
   meanSensor=(float)(sens/sensCount);
   meanSRelia=(float)(reli/liveCount);
   meanSRealt=(float)(real/liveCount);
   
   mnReliabilities->addValue(meanSRelia);
   mnRealities->addValue(meanSRealt);
   mnSensors->addValue(meanSensor);
   mnOpinions->addValue(meanOpinion);
   
   link_up=0;//When weight goes up
   link_dw=0;//When weight goes down
   sensor_up=0;
   sensor_dw=0;
} */
//../../scripts/procesing2cpp.sh did it

