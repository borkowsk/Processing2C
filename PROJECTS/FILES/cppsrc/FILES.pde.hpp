/// TEST KLAS obsługi strumieni.
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "FILES.pde"
// @date 2024-10-15 (last change)
//////////////////////////////////////////////////////////////////////////////////

PrintWriter    writer = nullptr;
BufferedReader reader = nullptr;

void write_someting(PrintWriter wr)
{
  for(int i=0;i<100;i++)
  {
    float x = random(width);
    float y = random(height);
    println("Save line #",i,x+String("\t")+y);
    println(wr,x+String("\t")+y);
  }
}

void processing_window::setup()
{
  size(200,216);
  background(0);
    
  // Create a new file in the sketch directory
  writer = createWriter("positions.txt");
 
  if(writer == nullptr )  exit();
  
  println("positions.txt is open");
  
  write_someting(writer); // Reference semantic test
  
  println(writer,"0\t0");

  writer->close();
  println("positions.txt is closed");
   
  delay(1000);
  reader = createReader("positions.txt");
  
  if(reader == nullptr )
                  exit();
  
  println("\npositions.txt is open");
  
  //println(reader->hashCode());// :-D TODO!
}

int counter=0;
void processing_window::draw()
{
  fill(random(256));
  String line = nullptr;
  try 
  {
    if((line = reader->readLine() )!= nullptr)
    {
      text(line,0,height);
      sarray<String> pieces = split(line,"\t"); //println(pieces->length,pieces);
      if(pieces->length<2) //May appears eg->at the end of file!
        throw std::runtime_error(String("Line ")+counter+ String("th Two colums expected"));
      float x = std::stof(pieces[0]);
      float y = std::stof(pieces[1]);
      println("Read line #",counter++,x+String("\t")+y);
      ellipse( x, y,10,10);
    }
  }
  catch (std::ifstream::failure e) 
  {
    println("IOerror:",e);
    //e->printStackTrace();
  }
  catch (std::runtime_error e)
  {
    println("ERROR:",e);
  }
}

void processing_window::exit()
{ 
  noLoop();
  try 
  {
    if(reader!=nullptr)
    {
       reader->close();
       println("positions.txt is closed");
    }
  }
  catch (std::ifstream::failure e) 
  {
    println(e);
    //e->printStackTrace();
  }  
  
  save("exit.png");
  processing_window_base::exit();
}

//MADE NOTE: ../../scripts did it 2024-10-15 16:10:55 !

