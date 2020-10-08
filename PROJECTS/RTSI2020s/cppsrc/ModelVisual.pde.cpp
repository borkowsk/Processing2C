//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: ModelVisual.pde
#include "processing_templates.hpp"
//#include "processing_inlines.hpp" //is optional. Use when project is already compilable
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

//   Basic visualisation of RTSI model utilized cell geometry
///////////////////////////////////////////////////////////////

bool    requestClean=false;  ///visible autside this file!
float histogram_width=HISTOGRAM_WIDTH;  /// Bars have integer width, so really histogram may be narrower than that

void processing_window::draw()
{
  if(theWorld->StepCounter>0 //Nie na początku!!!
  && theWorld->StepCounter%MACRO_STEP==0 //Otwarcie nowego MACRO_STEPu
  && simulationRun
  )
  {
    theWorld->resetModel();
    requestClean=true;
    doStatistics(theWorld);//Tu jest zapisywana statystyka zerowego kroku czyli po resecie)
    visualizeGraphs();
    theWorld->StepCounter++;
    return;//EMPTY STEP AFTER RESETING
  } 
  
  if(requestClean)
  {
    //delay(500); print("c");
    requestClean=false;
    //background(128,128,128);
    pixelizeProperties2D(theWorld->properties);
  }
    
  if(!simulationRun //When simulation was stopped only visualisation should work
  || theWorld->StepCounter % STEPSperVIS == 0 //But when model is running, visualisation shoud be done from time to time
  ) 
  {
    if(simulationRun && STEPSperVIS>=100) print("*");
    
    theWorld->visualizeModel();    
    visualizeGraphs();
    writeStatusLine();    
    //NextVideoFrame();//It utilise inside variable to check if is enabled
  }
  
  if(simulationRun)
  {
    theWorld->modelStep();                                                              //print("STEP");
    if(theWorld->StepCounter % STEPSperSTAT==0)
      doStatistics(theWorld);                                                          //print("?STAT");
  }   
  
}

void writeStatusLine()
{
  strokeWeight(1);noStroke();
  rectMode(CORNER);//Default rectMode CORNER is expected here
  fill(255);rect(0,WORLD_VIS_SIDE,width,STATUSHEIGH);
  textSize(FONT_HEIGHT);fill(0);
  textAlign(LEFT, TOP);
  text(String("Opinions [")+nf(minOpinion)+String("..(mean:")+nf(meanOpinion,1,5)
       +String(" stddev:")+nf(stddOpinion)+String(")..")+nf(maxOpinion)+ String("]"),
          0,WORLD_VIS_SIDE);
  fill(200,0,0);        
  text(String("mnError:")+meanError+String(" maxInfo:")+Info_maxInfos+String(" maxKnow.:")+Info_maxKnowl+ String(" mnSens.:")
       +nf(meanSensor,1,5)+String("(N:")+UsedSensors+String(") mnReliab:")+nf(meanSRelia,1,5),
          0,WORLD_VIS_SIDE+FONT_HEIGHT);
  fill(255,0,255);        
  if(VIS_NETWORK)
    text(String(" Visible links:")+linkCounter+String(" Link tres.:")+linkWeightTresh,
          0,WORLD_VIS_SIDE+FONT_HEIGHT*2);//For link filtering
  fill(0,0,200);
  text(String(" ")+theWorld->StepCounter+String(") Life:")+liveCount+String(" Fps.:")+frameRate,             //+String(" Prop.:")+WhichProperty, - in simple_model only ONE PROPERTY
          0,WORLD_VIS_SIDE+FONT_HEIGHT*3);
  stroke(64);
  viewFrame(WORLD_VIS_SIDE,WORLD_VIS_SIDE+HISTOGRAM_HEIGHT+FONT_HEIGHT+1,int(histogram_width),int(HISTOGRAM_HEIGHT));
  stroke(200);
  int index=forVis->higherBucketIndex;
  fill(5+index*2.5,0,5+index*2.5);
  histogram_width=viewAsColumns(forVis,WORLD_VIS_SIDE,WORLD_VIS_SIDE+HISTOGRAM_HEIGHT+FONT_HEIGHT+1,int(HISTOGRAM_WIDTH),int(HISTOGRAM_HEIGHT),true);
  if(selected!=nullptr)
  {
      String inspect=String("Cell ")+selectedX+String("x")+selectedY+String(" belong to ")+selected;
      inspect+=String(" Env. value:")+theWorld->properties[0]->get2D(selectedX,selectedY);
      inspect+=String("\n")+selected.fullInfo(";");
      selected->setFill();
      textAlign(LEFT,TOP);text(inspect,width/4,WORLD_VIS_SIDE);
  }
}

void visualizeGraphs()
{                                                                                   //print("VI: ");//DEBUG
  strokeWeight(1);noStroke();
  fill(250,250,255);
  rect(width/2,0,int(TIMELINES_WIDTH)+2,int(TIMELINES_HIGTH)+FONT_HEIGHT*2);
  stroke(0);
  viewFrame(width/2+2,int(TIMELINES_HIGTH),int(TIMELINES_WIDTH),int(TIMELINES_HIGTH));
  
  float tick_sizeV=10;
  //viewTicsV(width/2+2,TIMELINES_HIGTH,-3,TIMELINES_HIGTH,tick_sizeV);
 
  float minim=min(mnReliabilities->numOfElements(),FROM_END);                        //print(FROM_END,'?',minim,"");          
  float tick_sizeH=TIMELINES_WIDTH/minim;                                           //print(tick_sizeH,'=',TIMELINES_WIDTH,'/',minim,"");
  
  int expo=0;
  for(;tick_sizeH<2.0;expo++)
      tick_sizeH*=10;                                                               
                                                                                    //println(tick_sizeH,' ',expo);  
  if(tick_sizeH>=1)
    viewTicsH(width/2+2,TIMELINES_HIGTH,TIMELINES_WIDTH,3,tick_sizeH);
                                                                                    //print("VI?");//DEBUG  
  textSize(FONT_HEIGHT);textAlign(LEFT,BOTTOM);fill(0);
  
  line(width/2+2+tick_sizeH,TIMELINES_HIGTH,width/2+2+tick_sizeH,TIMELINES_HIGTH-6);
  text(String("")+pow(10,expo)*STEPSperSTAT,width/2+2+tick_sizeH,TIMELINES_HIGTH);
  
  pRange commonMinMax=new Range("commonMinMax");
  if(ZERO_ONE_SCALE)
  {
    commonMinMax->addValue(0.0);
    commonMinMax->addValue(1.0);    
  }
  commonMinMax->addValue(mnRealities->min);commonMinMax->addValue(mnRealities->max);
  commonMinMax->addValue(mnSensors->min);commonMinMax->addValue(mnSensors->max);
  commonMinMax->addValue(mnOpinions->min);commonMinMax->addValue(mnOpinions->max);
  commonMinMax->addValue(stdOpinionsPlus->max);
  commonMinMax->addValue(stdOpinionsMinus->min);
  if(WITH_ERRORS)
  { //int     REALITY=0; //Skąd bierzemy "realność"? 0-bierze pomiar spod nóg, 1-średni pomiar, 2-średnią opinie TODO
    commonMinMax->addValue(meanErrors->min);
    commonMinMax->addValue(meanErrors->min);
  }
  if(WITH_MIN_MAX)
  {
    commonMinMax->addValue(minOpinions->min);
    commonMinMax->addValue(maxOpinions->max);
  }
  if(visualiseReliabilities && WITH_STROKE)
  {
    commonMinMax->addValue(mnReliabilities->min);
    commonMinMax->addValue(mnReliabilities->max);
  }
 
  stroke(0,0,255,64);fill(0,0,255,128);
  viewAsPoints(mnSensors, -FROM_END,  width/2+2,int(TIMELINES_HIGTH),int(TIMELINES_WIDTH),int(TIMELINES_HIGTH),false,commonMinMax,false);
  stroke(0,0,255,128);
  if(ZERO_ONE_SCALE)
  {
    viewAsPoints(ratioOfSensors, -FROM_END,  width/2+2,int(TIMELINES_HIGTH),int(TIMELINES_WIDTH),int(TIMELINES_HIGTH),false,commonMinMax,true);
    textAlign(LEFT,BOTTOM);text("mn&ratio of Sensors",width/2+10,TIMELINES_HIGTH+FONT_HEIGHT*2);
  }
  else 
  {
    textAlign(LEFT,BOTTOM);text(mnSensors->name(),width/2+10,TIMELINES_HIGTH+FONT_HEIGHT*2);
  }
  
  
  stroke(0,128,0,128);fill(0,128,0);
  viewAsPoints(mnRealities, -FROM_END,width/2+2,int(TIMELINES_HIGTH),int(TIMELINES_WIDTH),int(TIMELINES_HIGTH),false,commonMinMax,true);
  textAlign(LEFT,BOTTOM);text(mnRealities->name(),width/2+width/10+10,TIMELINES_HIGTH+FONT_HEIGHT*2);
   
  stroke(255,0,0,128);fill(255,0,0,128);
  viewAsPoints(stdOpinionsMinus, -FROM_END, width/2+2,int(TIMELINES_HIGTH),int(TIMELINES_WIDTH),int(TIMELINES_HIGTH),false,commonMinMax,true);
  viewAsPoints(stdOpinionsPlus,  -FROM_END, width/2+2,int(TIMELINES_HIGTH),int(TIMELINES_WIDTH),int(TIMELINES_HIGTH),false,commonMinMax,true);
  stroke(200,0,0);fill(200,0,0);
  viewAsPoints(mnOpinions, -FROM_END, width/2+2,int(TIMELINES_HIGTH),int(TIMELINES_WIDTH),int(TIMELINES_HIGTH),false,commonMinMax,true);
  if(WITH_MIN_MAX)
  {
    viewAsPoints(minOpinions, -FROM_END, width/2+2,int(TIMELINES_HIGTH),int(TIMELINES_WIDTH),int(TIMELINES_HIGTH),false,commonMinMax,false);
    viewAsPoints(maxOpinions, -FROM_END, width/2+2,int(TIMELINES_HIGTH),int(TIMELINES_WIDTH),int(TIMELINES_HIGTH),false,commonMinMax,false);
    textAlign(LEFT,BOTTOM);text("minMnStdDevMaxOpinions",width/2+width/10*2+10,TIMELINES_HIGTH+FONT_HEIGHT*2);
  }
  else
  {
    textAlign(LEFT,BOTTOM);text("mnStdDevOpinions",width/2+width/10*2+10,TIMELINES_HIGTH+FONT_HEIGHT*2);
  }
  
  if(WITH_ERRORS)
  {
    //int     REALITY=0; //Skąd bierzemy "realność"? 0-bierze pomiar spod nóg, 1-średni pomiar, 2-średnią opinie TODO
    stroke(255,0,255);fill(255,0,255);
    viewAsPoints(meanErrors, -FROM_END,width/2+2,int(TIMELINES_HIGTH),int(TIMELINES_WIDTH),int(TIMELINES_HIGTH),false,commonMinMax,true);
    textAlign(LEFT,BOTTOM);text(meanErrors->name(),width/2+width/10*3+10,TIMELINES_HIGTH+FONT_HEIGHT*2);    
  }
  
  if(visualiseReliabilities && WITH_STROKE)
  {
    stroke(0,255,255);fill(0,255,255);
    viewAsPoints(mnReliabilities, -FROM_END,width/2+2,int(TIMELINES_HIGTH),int(TIMELINES_WIDTH),int(TIMELINES_HIGTH),false,commonMinMax,true);
    textAlign(LEFT,BOTTOM);text(mnReliabilities->name(),width/2+width/10*4+10,TIMELINES_HIGTH+FONT_HEIGHT*2);
  }
  
  fill(0);
  viewScaleV(commonMinMax,width/2+2,int(TIMELINES_HIGTH),0,int(TIMELINES_HIGTH));
  textSize(FONT_HEIGHT);
}

void visualizeProperties1D(sarray<pPropertyBase> props)
{
  noStroke();
  rectMode(CENTER);  // Set rectMode to CENTER
  pPropertyBase property=props[WhichProperty];
  
  int t=theWorld->StepCounter%SIDE;
  
  float min=property->getMin();
  float max=property->getMax();
  float dist=max-min;          assert(dist>0);	//
  for(float i=0.5;i<SIDE;i++)
   {
     float val=property->get1D(i);
     float intensity=map(val,min,max,0,255);                                       //((val-min)*255)/(dist);//ALT?
     fill(intensity);
     rect(i*cwidth,(t+0.5)*cwidth,cwidth,cwidth);
   }
}

void visualizeProperties2D(sarray<pPropertyBase> props)
{
  noStroke();
  rectMode(CENTER);                                                                //Set rectMode to CENTER
  pPropertyBase property=props[WhichProperty];
  float min=property->getMin();
  float max=property->getMax();
  //float dist=max-min;          assert(dist>0);	//
  for(float i=0.5;i<SIDE;i++)
   for(float j=0.5;j<SIDE;j++)
   {
     float val=property->get2D(j,i);
     float intensity=map(val,min,max,0,255);                                       //((val-min)*255)/(dist);//ALT?
     fill(intensity);
     rect(j*cwidth,i*cwidth,cwidth,cwidth);
   }
}

void pixelizeProperties2D(sarray<pPropertyBase> props)
{
  strokeWeight(1);
  pPropertyBase property=props[WhichProperty];
  float min=property->getMin();
  float max=property->getMax();
  float dist=max-min;                                                              assert(dist>0);	//
  float side=SIDE*cwidth;
  for(float i=0;i<side;i++)
   for(float j=0;j<side;j++)
   {
     float val=property->get2D(i/cwidth,j/cwidth);
     float intensity=((val-min)*255)/(dist);                                       //map(val,min,max,0,255);
     stroke(intensity);
     point(i,j);
   }
  fill(255,255,0,64);
  textAlign(RIGHT,BOTTOM);
  text(property->getName(),side,side);
}


void visualizeAgents(smatrix<pAgent> agents)
{
  noStroke();strokeCap(SQUARE);
  noFill();
  ellipseMode(CENTER);
  
  for(int i=0;i<agents->length;i++)
   for(int j=0;j<agents[i]->length;j++)
   {
    pAgent curra; 
    
    if( (curra=agents[i][j]) != nullptr )
    {
      if(WITH_STROKE) curra->setStroke();//Border colorisation
      if(VIS_AGENTS)  curra->setFill();//Inside colorisation
      ellipse(curra->X*cwidth,curra->Y*cwidth,cwidth/2,cwidth/2);
      if(!VIS_AGENTS)//Alternatywnie słupki
      {
        float opinion=curra->getOpinion(WhichProperty);                            
        float reality=curra->getReality(WhichProperty,theWorld);                   //!!!theWorld jest globalne
        float sensor=curra->sensors[0]->lastMeasurement;                            //from last usage of getSensor(0,theWorld);//alt curra->getSensor(WhichProperty,theWorld);
        strokeWeight(3);
        if(opinion!=INF_NOT_EXIST)
        {                                                                         assert(-1<=opinion && opinion<=1);	//
          stroke(255,255,0);
          line(curra->X*cwidth,curra->Y*cwidth,curra->X*cwidth,curra->Y*cwidth-opinion*cwidth/4);
        }
        if(reality!=INF_NOT_EXIST)
        {                                                                         assert(-1<=reality && reality<=1);	//
          stroke(0,255,0);
          line(curra->X*cwidth-3,curra->Y*cwidth,curra->X*cwidth-3,curra->Y*cwidth-reality*cwidth/4);
        }
        if(sensor!=INF_NOT_EXIST)
        {                                                                         assert(-1<=sensor && sensor<=1);	//
          stroke(0,0,255);
          line(curra->X*cwidth+3,curra->Y*cwidth,curra->X*cwidth+3,curra->Y*cwidth-sensor*cwidth/4);
        }
        strokeWeight(AGENT_STROKE);
        noStroke();
      }
    }//Valid if moving not available
  }
}
//OR
void visualizeAgents(sarray<pAgent> agents)
{
   assert(false);	//  "Implementation out of date";
}/*
   noStroke();
   ellipseMode(CENTER);

   int t=theWorld->StepCounter%SIDE;
   
   for(int a=0;a<agents->length;a++)
   {
    pAgent curra;
    
    if( (curra=agents[a]) != nullptr )
    {
      if(WITH_STROKE) curra->setStroke();
      curra->setFill();//Colorisation      
      ellipse(curra->X*cwidth,(t+0.5)*cwidth,cwidth*0.75,cwidth*0.75);
    }//Valid if moving not available
   }
   
   stroke(255);// CURRENT TIME MARKER
   strokeWeight(2);
   line(0,(t+1)*cwidth+1,width,(t+1)*cwidth+1);
   strokeWeight(0);
}
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - BASIC VISUALISATION from TEMPLATE
////////////////////////////////////////////////////////////////////////////////////////////////////////
//../../scripts/procesing2cpp.sh did it

