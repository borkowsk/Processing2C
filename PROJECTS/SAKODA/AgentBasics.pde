/// ABM model of segregation (test project for Processing2C)
/// ORIGINAL FILE: AgentSuplement.pde
/// @date 2024-10-14 (last change)
//*///////////////////////////////////////////////////////////////////////////////////////
/// Agent is a one of two central class of each ABM model.
//*///////////////////////////////////////////////////////////////////////////////////////

/*_import_class:Agent */

/// Agents need to be initialised & they need logic of change.
void initializeAgents(Agent[][] agents) ///< @note Need to be global!
{
   for(int a=0;a<agents.length;a++)
    for(int b=0;b<agents[a].length;b++)
    if(random(1)<density)
    {
      Agent curr=new Agent();
      agents[a][b]=curr;
    }
}
//OR
/// Agents need to be initialised & they need logic of change.
void initializeAgents(Agent[] agents) ///< @note Need to be global!
{ 
  for(int a=0;a<agents.length;a++)
  if(random(1)<density)
  {
    Agent curr=new Agent();
    agents[a]=curr;
  }
}

/// Agents need logic of change.
void  changeAgents(Agent[] agents) ///< @note Need to be global!
{
  int MC=agents.length;
  for(int i=0;i<MC;i++)
  {
    int a=(int)random(0,agents.length);
    if(agents[a]!= null )
    {
      //Sprawdzenie stresu
      int strangers=0;
      if(0<a-1 && agents[a-1]!=null 
      && agents[a-1].identity!=agents[a].identity)
        strangers++;
      if(a+1<agents.length && agents[a+1]!=null 
      && agents[a+1].identity!=agents[a].identity)
        strangers++;  
      agents[a].stress=strangers/2.0;  
      
      //Próba migracji gdy stres doskwiera
      if(agents[a].stress>0 
      && random(1)<agents[a].stress)
      {
        int target=(int)random(0,agents.length);
        if(agents[target]==null) //Jest miejsce
        {
          agents[target]=agents[a]; //Przeprowadzka
          agents[a]=null; //Wymeldowanie ze starego miejsca
        }
      }
    }
  }  
}
//OR
/// Agents need logic of change.
void  changeAgents(Agent[][] agents) ///< @note Need to be global!
{
  int MC=agents.length*agents[0].length;
  for(int i=0;i<MC;i++)
  {
    int a=(int)random(0,agents.length);
    int b=(int)random(0,agents[a].length);
    if(agents[a][b]!= null )
    {
      // Sprawdzenie stresu
      int strangers=0;
      if(0<a-1 && agents[a-1][b]!=null 
      && agents[a-1][b].identity!=agents[a][b].identity)
        strangers++;
        
      if(a+1<agents.length && agents[a+1][b]!=null 
      && agents[a+1][b].identity!=agents[a][b].identity)
        strangers++;  
        
      if(0<b-1 && agents[a][b-1]!=null 
      && agents[a][b-1].identity!=agents[a][b].identity)
        strangers++;
        
      if(b+1<agents.length && agents[a][b+1]!=null 
      && agents[a][b+1].identity!=agents[a][b].identity)
        strangers++;  
      
      agents[a][b].stress=strangers/4.0;  
      
      // Próba migracji gdy stres doskwiera
      if(agents[a][b].stress>0 
      && random(1)<agents[a][b].stress)
      {
        int tara=(int)random(0,agents.length);
        int tarb=(int)random(0,agents[a].length);
        
        if(agents[tara][tarb]==null) //Jest miejsce
        {
          agents[tara][tarb]=agents[a][b]; //Przeprowadzka
          agents[a][b]=null; //Wymeldowanie ze starego miejsca
        }
      }
    }
  }
}

//*//////////////////////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - ABM: BASIC INITIALISATION & EVERY STEP CHANGE
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
//*//////////////////////////////////////////////////////////////////////////////////////////////////////////
