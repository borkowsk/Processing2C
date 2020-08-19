//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: ARRAYTEST.pde
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
#include "processing_inlines.hpp" //is optional. Use when project is already compilable
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================


void processing_window::setup()
{
  sarray<int> a=new array<int>(10);
  for(int v:a)
    print(v,' ');
  
  println();
  
  smatrix<int> b=new matrix<int>(10,2);
  for(sarray<int> v:b)
    print(v,' ');
    
  println();
  for(sarray<int> v:b)
  {
    for(int w:v)
      print(w,' ');
    
    println();
  }

}
//../../scripts/procesing2cpp.sh did it

