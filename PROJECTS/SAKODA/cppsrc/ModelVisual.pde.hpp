/// ABM model of segregation (test project for Processing2C)
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// @date 2024-09-30 (last change)
/// ORIGINAL FILE: ModelVisualisation->pde
//*///////////////////////////////////////////////////////////////////////////////////////
/// World full of agents need method of visualisation on screen/window
//*//////////////////////////////////////////////////////////////////////////

void visualizeAgents(smatrix<pAgent> agents) { ///< Need to be global!
  pAgent curra;
  for(int a=0;a<agents->length;a++)
   for(int b=0;b<agents[a]->length;b++)
   {
      // Background
      noStroke();fill(200); //Lepiej dopasowa tło
      rect(b*cwidth,a*cwidth,cwidth,cwidth); //'a' is vertical!
      
      // Colorisation of agent
      if( (curra=agents[a][b]) != nullptr )
      {
        if(curra->stress>0)
          stroke(curra->stress*255,0,curra->stress*255);
        else
          noStroke();
           
        float forFill=(curra->identity*255.0) / Number_of_identities;
        fill(forFill,forFill,0);
        ellipse(b*cwidth,a*cwidth,cwidth,cwidth);
      }  
   }
}
//OR
void visualizeAgents(sarray<pAgent> agents) { ///< Need to be global!
   pAgent curra;
   for(int a=0;a<agents->length;a++)
   {
    //Colorisation    
    if( (curra=agents[a]) != nullptr )
    {
        if(curra->stress>0)
          stroke(curra->stress*255,0,curra->stress*255);
        else
          noStroke();
           
        float forFill=(curra->identity*255.0) / Number_of_identities;
        fill(forFill,forFill,0);
    }
    else
    {
      noStroke();
      fill(128);
    }
    
    int t=(StepCounter/STEPSperVIS)%side; //Uwzględniamy różne częstości wizualizacji
    rect(a*cwidth,t*cwidth,cwidth,cwidth);
    stroke(255);
    line(0,(t+1)*cwidth+1,width,(t+1)*cwidth+1);
   }
}

//*//////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: BASIC VISUALISATION
//*//////////////////////////////////////////////////////////////////////////////////////////////////////
//NOTE! ../../scripts did it 2024-09-30 17:06:17

