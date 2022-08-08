///   Cell is a one of two central data of each CA model
//*/////////////////////////////////////////////////////////////

void initializeCells( int[][] cells )     ///< Need to be global!
{
   for(int a=0;a<cells.length;a++)
    for(int b=0;b<cells[a].length;b++)
      if(treesDensity>0 && random(1)<treesDensity)
        cells[a][b]=(int)(random(1.0)*random(1.0)*random(1.0)*MAX_INT*random(1.0)*random(1.0)*random(1.0));
      else
        cells[a][b]=0;
   
   if(treesDensity==0) 
       cells[cells.length/2][cells.length/2]=1;
}

// Implement rules
//*///////////////////////////////////////////////

void synchChangeCells( int[][] cells , int[][] newcells )   ///< Drugi parametr tłumaczony jest błędnie! TODO
{
  float R=treesR-1.0;
  int N=cells.length;
  for(int a=0;a<N;a++)
  for(int b=0;b<cells[a].length;b++)
  {
     int val=cells[a][b];
     
     if(val==0)
     {
       if(treesDensity>0 && random(1.0)<treesDensity)
          val=1;
     }
     else if(val*R<1)
     {
       if(random(1.0)<R) val++;
     }
     else
     {
        val+=(int)(R*val); //Ups, przekraczając max giną :-D (ze starości?)
     }
     
     if(val<0) val=MAX_INT; //Tak już nie giną
     
     newcells[a][b]=val;
  }  
}

//*//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - ABM: BASIC INITIALISATION & EVERY STEP CHANGE
//*//////////////////////////////////////////////////////////////////////////////////////////////////////////
