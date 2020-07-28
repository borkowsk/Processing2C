//   Step by step statistics of RTSI model utilized cell geometry
////////////////////////////////////////////////////////////////////
PrintWriter outstat; ///May be used also autside this file! 

void initializeStats()
{
  String FileName=modelName+="_"+year()+'.'+nf(month(),2)+'.'+nf(day(),2)+'.'+nf(hour(),2)+'.'+nf(minute(),2)+'.'+nf(second(),2)+'.'+millis();
  outstat=createWriter(FileName+".out");
  outstat.print("$STEP\tAlive\tMeanOp\t+StdDevOp\tMinOp\tMaxOp\tmeanABSError"
                +"\tlink_up\tlink_dw\tsensor_up\tsensor_dw\tMeanSensor\tUsedSensors\tMeanSRelia\tMeanSReal\tmaxInfos\tmaxKnowl"
                  );//<-- complete the header line!
  outstat.println("\tHistTooLow\tH0\tH1\tH2\tH3\tH4\tH5\tH6\tH7\tH8\tH9\tHistTooHig");//At the end of line is histogram of links weights               
  statisticsLogEnabled=true;
}

// Global statistics & their histories
int   liveCount=0;//Właściwie niepotrzebne w tym modelu bo nie giną TODO?

float meanOpinion=0;  ///May be used also autside this file!
Sample mnOpinions=new Sample("mnOpinions");

float stddOpinion=0;  ///visible autside this file!
Sample stdOpinionsPlus=new Sample("stdOpinionsPlus");
Sample stdOpinionsMinus=new Sample("stdOpinionsMinus");

float minOpinion=0;  ///visible autside this file!
Sample minOpinions=new Sample("minOpinions");

float maxOpinion=0;  ///visible autside this file!
Sample maxOpinions=new Sample("maxOpinions");
  
float meanSensor=0;  ///visible autside this file!
int   UsedSensors=0;  ///visible autside this file!
Sample mnSensors=new Sample("mnSensors");
Sample ratioOfSensors=new Sample("ratioOfSensors");//history od=f UsedSensors

float meanSRealt=0;  ///visible autside this file!
Sample mnRealities=new Sample("mnRealities");

float meanSRelia=0;  ///visible autside this file!
Sample mnReliabilities=new Sample("mnReliabilities");

//Historie błędów 
//int     REALITY=2; //Skąd bierzemy "realność"? 0-bierze pomiar spod nóg, 1-średni pomiar, 2-średnią opinie, 3-średnią realność TODO
float meanError=0; ///Co jest błędem jest zależne od tego co jest realnością!
Sample meanErrors=new Sample("mn(abs(Opinion[a,b]-Sensor[a,b]))");

Sample mnDiffOwnReal=new Sample("mnDiffOwnReal");  ///visible autside this file!
Sample mnDiffMnSensor=new Sample("mnDiffMnSensor");  ///visible autside this file!
Sample mnDiffMnOpinion=new Sample("mnDiffMnOpinion");  ///visible autside this file!
Sample mnDiffMnReal=new Sample("mnDiffMnReal");  ///visible autside this file!

// Global DYNAMICS
int    link_up=0;  ///When weight goes up
int    link_dw=0;  ///When weight goes down
int  sensor_up=0;  ///visible autside this file!
int  sensor_dw=0;  ///visible autside this file!

void doStatistics(World world)
{
  doStatisticsOnAgents(world.agents);
  doStatisticsOnLinks(world.agents,allLinks);//USE ADDITIONAL STATISTICS 
}

void doStatisticsOnAgents(Agent[][] agents)
{  
  Agent curra;
  double sens=0;
  double reli=0;
  double real=0;
  double dsum=0;//Suma abs(różnic)
  int opinCount=0;//May be alive but have no opinion!
  int sensCount=0;//May be alive but have never used their sensor!
  int derrCount=0;//May have opinion, but not sensor!
  liveCount=0;
  Sample stepOpinions=new Sample("stepOpinions");
  
  for(int a=0;a<agents.length;a++)
   for(int b=0;b<agents[a].length;b++)
    if( (curra=agents[a][b]) != null )
    {
      //Simple statistic
      double val=curra.getOpinion(0); 
      
      if(val!=INF_NOT_EXIST)
      {
        stepOpinions.addValue((float)(val));
        opinCount++;
      }
      
      double vre=curra.sensors[0].lastMeasurement;//from last usage of getSensor(0,theWorld);
      
      if(vre!=INF_NOT_EXIST)
      {
        sens+=vre;
        sensCount++;
      }
      
      if(val!=INF_NOT_EXIST && vre!=INF_NOT_EXIST)
      {
        dsum+=Math.abs(vre-val);//MN(abs(Opinion[a,b]-Sensor[a,b]))
        derrCount++;
      }
      
      reli+=curra.getReliability(0);
      real+=curra.getReality(0,theWorld);
      
      liveCount++;
    }
                                                                    assert opinCount==stepOpinions.numOfElements();
   meanOpinion=stepOpinions.getMean();
   stddOpinion=stepOpinions.getStdDev();
   minOpinion=stepOpinions.getMin();
   maxOpinion=stepOpinions.getMax();
        
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
   
   
   mnSensors.addValue(meanSensor);
   if(UsedSensors>0)
     ratioOfSensors.addValue( UsedSensors/(1.0*SIDE*SIDE));              
   else
     ratioOfSensors.addValue( INF_NOT_EXIST );                                      //println(UsedSensors/(1.0*SIDE*SIDE));
     
   mnReliabilities.addValue(meanSRelia);
   mnRealities.addValue(meanSRealt);
   mnOpinions.addValue(meanOpinion);
   minOpinions.addValue(minOpinion);
   maxOpinions.addValue(maxOpinion);
   
   meanErrors.addValue(meanError);
   
   if(meanOpinion!=INF_NOT_EXIST && stddOpinion!=INF_NOT_EXIST)
   {
     stdOpinionsPlus.addValue(meanOpinion+stddOpinion);
     stdOpinionsMinus.addValue(meanOpinion-stddOpinion);
   }
   else
   {
     stdOpinionsPlus.addValue(INF_NOT_EXIST);
     stdOpinionsMinus.addValue(INF_NOT_EXIST);     
   }
   
   if(statisticsLogEnabled)
   {
     outstat.print(theWorld.StepCounter+"\t"+liveCount+"\t"+meanOpinion+"\t"+stddOpinion+"\t"+minOpinion+"\t"+maxOpinion+"\t"+meanError
                       +"\t"+link_up+"\t"+link_dw+"\t"+sensor_up+"\t"+sensor_dw+"\t"
                       +sens/UsedSensors+"\t"+UsedSensors+"\t"+reli/liveCount+"\t"+real/liveCount+"\t"+Info_maxInfos+"\t"+Info_maxKnowl+"\t");
     outstat.print(forLog.outsideLow+"\t");
     for(int i=0;i<forLog.buckets.length;i++)
            outstat.print(forLog.buckets[i]+"\t");
     outstat.println(forLog.outsideHig);
   }
        
   link_up=0;//When weight goes up
   link_dw=0;//When weight goes down
   sensor_up=0;
   sensor_dw=0;
}

// STATYSTYKI SIECI
/////////////////////////////////////////////////////////////
Frequencies forLog=new Frequencies( 10,0.0,1.0,"frequenciesForLog");
Frequencies forVis=new Frequencies(100,0.0,1.0,"frequenciesForVis");

int doStatisticsOnLinks(iVisNode[][] nodes,LinkFilter filter)
{
  int counter=0;
  forLog.reset();
  forVis.reset();
  
  for(int i=0;i<nodes.length;i++)
    for(int j=0;j<nodes[i].length;j++)
    {
      iVisNode Source=nodes[i][j];
      
      if(Source!=null)
      {
        //float X=Source.posX();
        //float Y=Source.posY();
        Link[] links=Source.getConns(filter);
        int n=links.length;
        
        for(int k=0;k<n;k++)
        {
          //float Xt=links[k].target.posX();
          //float Yt=links[k].target.posY();//For counting distances
          
          float value=links[k].weight;
          forLog.addValue(value);
          forVis.addValue(value);
          
          counter++;
        }
      }
    }
  
  return counter;
}


void CloseStatistics()
//outstat should be closed in exit() --> see RTMExit.pde
{
  if(outstat!=null && statisticsLogEnabled)
  {
    outstat.flush();  // Writes the remaining data to the file
    outstat.close();  // Finishes the file
    statisticsLogEnabled=false;
    outstat=null;
  }
}

static boolean     statisticsLogEnabled=false;//initializeStats() will set up it for true

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - STATISTICS LOG from TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////

void doStatisticsOnAgents(Agent[] agents)
{  
   assert false: "Implementation out of date";
}/*
  Agent curra;
  double summ=0;
  double sens=0;
  double reli=0;
  double real=0;
  liveCount=0;
  int opinCount=0;//May be alive but have no opinion!
  int sensCount=0;//May be alive but have never used their sensor!
  
  for(int a=0;a<agents.length;a++)
    if( (curra=agents[a]) != null )
    {
      //Simple statistic
      double val=curra.getOpinion(0); 
      if(val!=INF_NOT_EXIST)
      {
        summ+=val;
        opinCount++;
      }
      
      val=curra.sensors[0].lastMeasurement;//from last usage of getSensor(0,theWorld);
      
      if(val!=INF_NOT_EXIST)
      {
        sens+=val;
        sensCount++;
      }
      
      reli+=curra.getReliability(0);
      real+=curra.getReality(0,theWorld);
      
      liveCount++;
    }
   
   //doStatisticsOnLinks(agents,allLinks);
    
   if(statisticsLogEnabled)
       outstat.println(theWorld.StepCounter+"\t"+liveCount+"\t"+(summ/opinCount)
                       +"\t"+link_up+"\t"+link_dw+"\t"+sensor_up+"\t"+sensor_dw+"\t"
                       +sens/liveCount+"\t"+reli/liveCount+"\t"+real/liveCount+"\t"+Info_maxInfos+"\t"+Info_maxKnowl);
       
   meanOpinion=(float)(summ/liveCount);
   meanSensor=(float)(sens/sensCount);
   meanSRelia=(float)(reli/liveCount);
   meanSRealt=(float)(real/liveCount);
   
   mnReliabilities.addValue(meanSRelia);
   mnRealities.addValue(meanSRealt);
   mnSensors.addValue(meanSensor);
   mnOpinions.addValue(meanOpinion);
   
   link_up=0;//When weight goes up
   link_dw=0;//When weight goes down
   sensor_up=0;
   sensor_dw=0;
} */
