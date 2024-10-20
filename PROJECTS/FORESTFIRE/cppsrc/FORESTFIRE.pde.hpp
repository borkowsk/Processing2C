/// Sophisticated :-) PCA (Probabilistic Cellular Automaton) model test for Processing2C.
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// @date 2024-10-15 (last change)
/// ORIGINAL FILE: "FORESTFIRE.pde"
//*///////////////////////////////////////////////////////////////////////////////////////
/// Model "pożaru lasu" jest bardzo klasyczny, choć tu mamy wersję autorską
/// z próbą urealnienia stosunków czasowych
//*/////////////////////////////////////////////////////////////////////////

// One step is equivalential to one hour
int Week=24*7;    ///< how many steps is equivalential to one week?
float Year=365.5*24; ///< how many steps is equivalential to one YEAR?

//Model parameters
int N=100;        ///<array side

int FireTimeDiv=50; ///<How long the tree is burning (divider for size)
float IgnitionP = 0.10; ///<Probability of fire transfer
float InitT=  0.00; ///<How many trees at start
float GrowS=  0.0005; ///<Growt per step
float SeedP=  0.0005; ///<How often new ofspring emerging (per free cell)
float LightP= 0.000000005; ///<How often fire emerge (per tree)
int MatureT=220; ///<Max size of tree->Then will stop to grow

// 2D "World" of trees
smatrix<float> World = new matrix<float>(N,N); ///<!!!
PrintWriter Log; ///<For writing statistics into disk drive

// For visualisation
int S=20;       ///cell width & height
bool    is_burning=false;

// For statistics
int Step=0; ///<!!!

// Simple statistics
int empty=0;
int alives=0;
int burning=0;
double meanSize=0; ///<Sredni rozmiar drzewa (albo wiek bo to wychodzi na to samo chyba)

// Initialisation
void processing_window::setup()
{
  size(900,936);
  S=width/N; //cell side size

  for(int i=0;i<N;i++)
   for(int j=0;j<N;j++)
   if(random(0,1)<InitT)
    //World[i][j]=(int)random(MatureT); //FLAT DISTRIBUTION? RATHER NOT REALISTIC!
    World[i][j]=MatureT/2;
    else
    World[i][j]=0;
   
  //setFrameRate(4*Week);
  setFrameRate(10001);
  
  noSmooth();
  noStroke();
  
  String LogName=String("FF") + IgnitionP + String("_") + GrowS + String("_") + LightP +  String(".log");
  Log = createWriter(LogName); // Create a new file in the sketch directory
  println(Log,"step\t alives\t burning\t empty\t meanSize"); //Header
}

void processing_window::draw()
{
  if(is_burning ||
     Step % (4*Week) == 0)
      doVisualisation();
  
  is_burning=false; //We will check it in a moment
  
  doMonteCarloStep();
}

float Burn=0; ///Ile możliwości zapalenia na krok
void doMonteCarloStep() ///MAIN FUNCTION OF THE MODEL
{
  // Bardzo rzadkie zapalanie - trochę oszukujemy, ale unikamy wywołań random na każdą niemal komórkę!
  Burn+=N*N*LightP; //Prawdopodobieństwo jest na komórkę na krok->Z czasem licznik rośnie
  for(;Burn>1;) //Spontanic fireing
      {
        int i=(int)random(N);
        int j=(int)random(N);
        if(World[i][j]>0)
        {
          World[i][j]=(int)(-World[i][j] /FireTimeDiv - 1); //At least one step 
          Burn--;
          is_burning=true; //At least one! DO VISUALISATION!
        }
      }
      
  // Reszta akcji
  int M=N*N;
  for(int m=0;m<M;m++) //Processing is CASE SENSITIVE. 
  {
    int i=(int)random(N);
    int j=(int)random(N);
    if(World[i][j]==0) //Free or burned cell
    {
      if(random(0,1)<SeedP)
          World[i][j]=1; //New seedling
    }
    else
    if(World[i][j]>0) //TREE
    {
      if(World[i][j]<MatureT)
            World[i][j]+=GrowS;
    }
    else //Negative means still burning!
    {
       // Ignite neighbors!
       for(int l=-1;l<2;l++) //Moore neighborhood
        for(int k=-1;k<2;k++)        
        {
            int a=(N+i+l)%N;
            int b=(N+j+k)%N;
            if(World[a][b]>0 //If is still not burning
            && random(0,1)<IgnitionP) //May ignite
             {
               World[a][b]=(int)(-World[a][b] /FireTimeDiv - 1); //At least one step
               //println(World[a][b],"!");
               is_burning=true; //At least one! DO VISUALISATION!
             }
        }
       //Burn more
       World[i][j]++; //Until 0
    }
  }
  // Step completed
  Step++;
}

void doVisualisation() ///< Must be predeclared
{
  empty=0;alives=0;burning=0; //Simple counting will be done during visualisation
  meanSize=0;
  
 for(int i=0;i<N;i++) //visualisation
  for(int j=0;j<N;j++)
  {
    if(World[i][j]==0) //Free or burned cell
    {
      fill(20,20,20);
      empty++;
    }
    else
    if(World[i][j]>0) //TREE
    {
      int col=30+(int)World[i][j];
      if(col>255) col=255;
      fill(0,col,0);
      alives++;
      meanSize+=World[i][j];
    }
    else //Burning!
    {
      fill(50+random(205),random(255),0);
      burning++;
    }  
    rect(i*S,j*S,S,S);
  } 
  
  //Printing statistics:
  fill(0);
  rect(0,height,width,-32);
  
  if(!is_burning)
    fill(255);
  else
    fill(50+random(205),random(255),0);
  meanSize/=alives;
  textAlign(LEFT);
  text(String(" T:")+alives+String(" B:")+burning,0,height-16);
  fill(0,255,0);
  textAlign(RIGHT);
  text(String("Growing:")+GrowS+String(" Fire transfer p.:")+IgnitionP+ String(" Fire p.:")
       +LightP+ String(" (per step and per tree)"), width, height-16);
  fill(255,255,0); 
  textAlign(LEFT);
  text(Step/Year +  String(" years  = ") 
     + Step/Week +  String(" weeks & ") 
     + (Step%Week) / 24 +  String(" days = ") 
     + Step +  String(" h") 
     + String(" Speed:") + frameRate +  String(" fr/sec") ,0,height);
  fill(0,255,255);
  textAlign(RIGHT);
  text(String(" Mean: ")+meanSize+ String(" "),width,height);
  
  println(Log,Step+String("\t ")+alives+String("\t ")+burning+String("\t ")+empty+String("\t ")+meanSize);
  if(Step % 5000==0) Log->flush(); //Sometimes writes the buffer to the file
}

//*///////////////////////////////////////////////////////////////////////////////////////
/// "Forest fire with regeneration" - my private version 
//*///////////////////////////////////////////////////////////////////////////////////////
//MADE NOTE: ../../scripts did it 2024-10-15 16:10:55 !

