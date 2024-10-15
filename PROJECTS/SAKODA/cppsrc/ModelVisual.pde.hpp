/// ABM model of segregation (test project for Processing2C)
/// ORIGINAL FILE: ModelVisualisation->pde
/// @date 2024-10-15 (last change)
//*//////////////////////////////////////////////////////////////////////////
/// World full of agents need method of visualisation on screen/window.
//*//////////////////////////////////////////////////////////////////////////

/*_import_class:Agent */
/*_import_class:World */

/// @brief Procedure for visualizing a two-dimensional array of agents
void visualizeAgents(smatrix<pAgent> agents) { ///< Need to be global!
  pAgent curra;
  for(int a=0;a<agents->length;a++)
   for(int b=0;b<agents[a]->length;b++)
   {
      // Background
      noStroke();fill(200); // Lepiej dopasowa tło
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
/// @brief Procedure for visualizing a one-dimensional array of agents
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
    
    int t=(StepCounter/STEPSperVIS)%side; // @internal We take into account different visualization frequencies.
    rect(a*cwidth,t*cwidth,cwidth,cwidth);
    stroke(255);
    line(0,(t+1)*cwidth+1,width,(t+1)*cwidth+1);
   }
}

//*//////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - ABM: BASIC VISUALISATION
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
//*//////////////////////////////////////////////////////////////////////////////////////////////////////
//MADE NOTE: ../../scripts did it 2024-10-15 16:10:56 !

