
void setup()
{
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

}
