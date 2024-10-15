/// @file
/// @note Automatically made from _ARRAYTEST.pde_ by __Processing to C++__ converter (../../scripts/procesing2cpp.sh).
/// @date 2024-10-15 16:11:03 (translation)
//
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
#ifndef _NO_INLINE
#include "processing_inlines.hpp" //...is optional.
#endif // _NO_INLINE
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
using namespace Processing;
#include "local.h" //???.
#include <iostream>
//================================================================

/// Array and matrix test for Processing2C
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "ARRAYTEST.pde"
// @date 2024-09-30 (last change)
//*//////////////////////////////////////////////////////////////////

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

//MADE NOTE: ../../scripts did it 2024-10-15 16:11:03 !

const char* Processing::_PROGRAMNAME="ARRAYTEST";
