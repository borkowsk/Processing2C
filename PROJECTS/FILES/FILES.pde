//Używamy KLAS obsługi strumieni zdefiniowanych w bibliotece

PrintWriter    writer = null;
BufferedReader reader = null;

void setup()
{
  size(200,200);
    
  // Create a new file in the sketch directory

  writer = createWriter("positions.txt");
 
  if(writer == null )  exit();
  
  println("positions.txt is open");
  
  for(int i=0;i<100;i++)
  {
    float x = random(width);
    float y = random(height);
    println(x+"\t"+y);
    writer.println(x+"\t"+y);
  }

  writer.close();
  println("positions.txt is closed");
   
  delay(1000);
  reader = createReader("positions.txt");
  
  if(reader == null )  exit();
  
  println("\npositions.txt is open");
}

void draw()
{
  String line = null;
  try 
  {
    if((line = reader.readLine() )!= null)
    {
      String[] pieces = split(line,"\t");
      float x = float(pieces[0]);
      float y = float(pieces[1]);
      println(x+"\t"+y);
      ellipse( x, y,10,10);
    }
  }
  catch (IOException e) 
  {
    e.printStackTrace();
  }
}

void exit()
{ 
  noLoop();
  try 
  {
    reader.close();
    println("positions.txt is closed");
  }
  catch (IOException e) 
  {
    e.printStackTrace();
  }  
}
