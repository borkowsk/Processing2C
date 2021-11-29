/// Array and matrix test for Processing2C
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "ARRAYTEST.pde"
////////////////////////////////////////////////////////////////////

int[][] c;
String[][] s;

void setup()
{
  size(100,100);
  frameRate(10);
  randomSeed(4);
  
  int[] a=new int[10];
  for(int v:a)
    print(v,' ');
  
  println();
  
  int[][] b=new int[10][2];
  for(int[] v:b)
    print(v,' ');
    
  println();
  for(int[] v:b)
  {
    for(int w:v)
      print(w,' ');
    
    println();
  }
  
  c=new int[2][3];
  s=new String[2][3];
  
  for(int i=0;i<2;i++)
  for(int j=0;j<3;j++)
  {
    c[i][j]=i*j;
    s[i][j]=nf(c[i][j]);
  } 
}

void draw()
{
  int a=(int)random(2);
  int b=(int)random(3);
  c[a][b]+=1;
  s[a][b]=nf(c[a][b]);
  println(a,b,c[a][b],"'"+s[a][b]+"'");
}
