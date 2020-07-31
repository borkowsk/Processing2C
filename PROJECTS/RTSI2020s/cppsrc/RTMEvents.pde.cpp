//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: RTMEvents.pde
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
//include "processing_inlines.hpp" //is optional. Use when project is already compilable
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

//  Obsługa zdarzeń klawiatury i myszy
//  Keyboard Event Handling 
///////////////////////////////////////////////////

pTypeAndAbsHighPassFilter comboVisFilter=new TypeAndAbsHighPassFilter();
//pTypeAndAbsHighPassFilter moralVisFilter=new TypeAndAbsHighPassFilter(MORALITY_MARKER,linkWeightTresh);

void keyPressed() 
{
  fill(128);
  if(key!=CODED) println("Key:'",key,'\''); else println("Key coded:'",keyCode,'\'');
  switch(key)
  {
  case 'q':
  case 'Q': exit();break;
  //case '￿': //println(int('￿'));//Do nothing - WHAT DOES IT MEANS?
  //          break;
  case '+': linkWeightTresh+=0.10;if(linkWeightTresh>0.9) linkWeightTresh=0.9;
            println("pLink treshhold=",linkWeightTresh);
            pixelizeProperties2D(theWorld->properties);
            theWorld->currFilter=comboVisFilter->reset(WhichProperty,linkWeightTresh);
            break;
  case '-': linkWeightTresh-=0.10;if(linkWeightTresh<0) linkWeightTresh=0;
            println("pLink treshhold=",linkWeightTresh);
            pixelizeProperties2D(theWorld->properties);
            theWorld->currFilter=comboVisFilter->reset(WhichProperty,linkWeightTresh);
            break;
  case 'O': FRAMEFREQ/=2;setFrameRate(FRAMEFREQ);println("Requested",FRAMEFREQ,"frames/sec");break;
  case '0': FRAMEFREQ*=2;setFrameRate(FRAMEFREQ);println("Requested",FRAMEFREQ,"frames/sec");break;
  case '1': STEPSperVIS=1;println(STEPSperVIS,"step/frame");text(String("StPerV: ")+STEPSperVIS,0,height-16);break;
  case '2': STEPSperVIS=2;println(STEPSperVIS,"step/frame");text(String("StPerV: ")+STEPSperVIS,0,height-16);break;
  case '3': STEPSperVIS=5;println(STEPSperVIS,"step/frame");text(String("StPerV: ")+STEPSperVIS,0,height-16);break;
  case '4': STEPSperVIS=10;println(STEPSperVIS,"step/frame");text(String("StPerV: ")+STEPSperVIS,0,height-16);break;
  case '5': STEPSperVIS=25;println(STEPSperVIS,"step/frame");text(String("StPerV: ")+STEPSperVIS,0,height-16);break;
  case '6': STEPSperVIS=50;println(STEPSperVIS,"step/frame");text(String("StPerV: ")+STEPSperVIS,0,height-16);break;
  case '7': STEPSperVIS=100;println(STEPSperVIS,"step/frame");text(String("StPerV: ")+STEPSperVIS,0,height-16);break;
  case '8': STEPSperVIS=150;println(STEPSperVIS,"step/frame");text(String("StPerV: ")+STEPSperVIS,0,height-16);break;
  case '9': STEPSperVIS=200;println(STEPSperVIS,"step/frame");text(String("StPerV: ")+STEPSperVIS,0,height-16);break;
  case ' ': save(modelName+String(".")+nf((float)theWorld->StepCounter,6,5)+ String(".PNG"));
            println(modelName+String(".")+nf((float)theWorld->StepCounter,6,5)+ String(".PNG"),"SAVED!");
            break;
  case ESC: simulationRun=!simulationRun; break;
  case 's': simulationRun=false; break;
  case 'r': simulationRun=true; break;
  case 'a': VIS_AGENTS=!VIS_AGENTS;
            if(!VIS_AGENTS)
              pixelizeProperties2D(theWorld->properties);
            break;
  case 'e': WITH_ERRORS=!WITH_ERRORS;break;
  case 'I':
  case 'i': WITH_STROKE=!WITH_STROKE;
            pixelizeProperties2D(theWorld->properties);
            break;
  case 'm': WITH_MIN_MAX=!WITH_MIN_MAX;break;
  case 'n': VIS_NETWORK=!VIS_NETWORK;
            if(!VIS_NETWORK)
              pixelizeProperties2D(theWorld->properties);
            break;
  case 'o': ZERO_ONE_SCALE=!ZERO_ONE_SCALE;break;
  // Morality network is not present in simple_model
  //case 'M':  theWorld->currFilter=new OrFilter(comboVisFilter->reset(WhichProperty,linkWeightTresh),moralVisFilter->reset(MORALITY_MARKER,linkWeightTresh));
  //           break;
  //case 'N':  linkWeightTresh=0;println("pLink treshhold=",linkWeightTresh);
  //           pixelizeProperties2D(theWorld->properties);
  //           theWorld->currFilter=comboVisFilter->reset(WhichProperty,linkWeightTresh);
  //           break;
  // Many properties are also not present in simple_model
  //case '\t': WhichProperty++;
  //           WhichProperty%=NUM_OF_PROPERTIES;
  //           println(String("Visualise property #")+WhichProperty);
  //           pixelizeProperties2D(theWorld->properties);
  //           theWorld->currFilter=comboVisFilter->reset(WhichProperty,linkWeightTresh);
  //           break;
  default:println(String("Command '")+key+ String("' unknown"));
  case 'h':
          println("USE:");
          println("q - exit");
          println("\u2423 \tfor dump the current screen"); 
 //       println("\u21E5 \tfor change properties to be visualised");
          println("e \tfor visualise mean errors");
          println("i \tfor visualise information level of agents");
          println("m \tfor visualisation min & max opinions");
          println("n \tfor swith on/off networks visualisation");
          println("o \tfor 0..1 scaling of histories graphs");
          println("1-9 \tfor less frequent visualisation");
          println("0 \tfor more frequent frames");
          println("+- \tfor more or less links");
          println("\u241B,s,r \tfor pause/stop/run simulation");
          println("\n");//http://blog->elliottcable.name/posts/useful_unicode->xhtml
  break;
  }
  
  if (key == ESC) 
  {
    key = 0;  // Fools! don't let them escape!
  }
}

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate.net/profile/WOJCIECH_BORKOWSKI - EVENTS from TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////
//../../scripts/procesing2cpp.sh did it

