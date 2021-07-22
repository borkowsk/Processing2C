//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: FILES.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
//#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h"
#include "project.h" //...is for you. Could be deleted when not needed.
//==================================================================================

//Używamy KLAS obsługi strumieni zdefiniowanych w bibliotece

PrintWriter    writer = nullptr;
BufferedReader reader = nullptr;

void processing_window::setup()
{
  size(200,200);
    
  // Create a new file in the sketch directory

  writer = createWriter("positions.txt");
 
  if(writer == nullptr )  exit();
  
  println("positions.txt is open");
  
  for(int i=0;i<100;i++)
  {
    float x = random(width);
    float y = random(height);
    println(x+String("\t")+y);
    println(writer,x+String("\t")+y);
  }

  writer->close();
  println("positions.txt is closed");
   
  delay(1000);
  reader = createReader("positions0.txt");
  
  if(reader == nullptr )   //<>//
                  exit(); //<>//
  
  println("\npositions.txt is open");
}

void processing_window::draw()
{
  String line = nullptr;
  try 
  {
    if((line = reader->readLine() )!= nullptr)
    {
      sarray<String> pieces = split(line,"\t");
      if(pieces->length<2) throw std::runtime_error("File format error");
      float x = std::stof(pieces[0]);
      float y = std::stof(pieces[1]);
      println(x+String("\t")+y);
      ellipse( x, y,10,10);
    }
  }
  catch (std::ifstream::failure e) 
  {
    println("IOerror:",e); //<>//
    //e->printStackTrace(); //<>//
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
       reader->close(); //<>//
       println("positions.txt is closed");
    }
  }
  catch (std::ifstream::failure e) 
  {
    println(e);
    //e->printStackTrace();
  }  
  
  processing_window_base::exit();
}
//../../scripts/procesing2cpp.sh did it

