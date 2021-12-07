/// TEST KLAS obsługi strumieni
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "FILES.pde"
//////////////////////////////////////////////////////////////////////////////////

PrintWriter    writer = null;
BufferedReader reader = null;

void write_someting(PrintWriter wr)
{
  for(int i=0;i<100;i++)
  {
    float x = random(width);
    float y = random(height);
    println("Save line #",i,x+"\t"+y);
    wr.println(x+"\t"+y);
  }
}

void setup()
{
  size(200,216);
  background(0);
    
  // Create a new file in the sketch directory
  writer = createWriter("positions.txt");
 
  if(writer == null )  exit();
  
  println("positions.txt is open");
  
  write_someting(writer);// Reference semantic test
  
  writer.println("0\t0");

  writer.close();
  println("positions.txt is closed");
   
  delay(1000);
  reader = createReader("positions.txt");
  
  if(reader == null )   //<>//
                  exit(); //<>//
  
  println("\npositions.txt is open");
  
  //println(reader.hashCode());// :-D TODO!
}

int counter=0;
void draw()
{
  fill(random(256));
  String line = null;
  try 
  {
    if((line = reader.readLine() )!= null)
    {
      text(line,0,height);
      String[] pieces = split(line,"\t"); //println(pieces.length,pieces);
      if(pieces.length<2) //May appears eg. at the end of file!
        throw new Exception("Line "+counter+"th Two colums expected");
      float x = Float.parseFloat(pieces[0]);
      float y = Float.parseFloat(pieces[1]);
      println("Read line #",counter++,x+"\t"+y);
      ellipse( x, y,10,10);
    }
  }
  catch (IOException e) 
  {
    println("IOerror:",e); //<>//
    //e.printStackTrace(); //<>//
  }
  catch (Exception e)
  {
    println("ERROR:",e);
  }
}

void exit()
{ 
  noLoop();
  try 
  {
    if(reader!=null)
    {
       reader.close(); //<>//
       println("positions.txt is closed");
    }
  }
  catch (IOException e) 
  {
    println(e);
    //e.printStackTrace();
  }  
  
  save("exit.png");
  super.exit();
}
