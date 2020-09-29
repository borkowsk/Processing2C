//Processing to C++ converter /data/wb/SCC/__working_copies/Processing2C/scripts/procesing2cpp.sh
//Source: ARRAYTEST.pde
#include "processing_templates.hpp"
//#include "processing_inlines.hpp" //is optional. Use when project is already compilable
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================


smatrix<int> c;
smatrix<String> s;

void processing_window::setup()
{
  size(100,100);
  setFrameRate(10);
  randomSeed(4);
  
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
  
  c=new matrix<int>(2,3);
  s=new matrix<String>(2,3);
  
  for(int i=0;i<2;i++)
  for(int j=0;j<3;j++)
  {
    c[i][j]=i*j;
    s[i][j]=nf(c[i][j]);
  } 
}

void processing_window::draw()
{
  int a=(int)random(2);
  int b=(int)random(3);
  c[a][b]+=1;
  s[a][b]=nf(c[a][b]);
  println(a,b,c[a][b],String("'")+s[a][b]+ String("'"));
}
///data/wb/SCC/__working_copies/Processing2C/scripts/procesing2cpp.sh did it

