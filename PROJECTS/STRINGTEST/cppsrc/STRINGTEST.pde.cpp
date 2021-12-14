//Processing to C++ converter /home/data/SCC/__public_git/Processing2C/scripts/procesing2cpp.sh
//Source: STRINGTEST.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_window.hpp"
//#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_alist.hpp" //...is optional. Should be deleted when not needed.
#include "processing_lists.hpp" //...is optional. Should be deleted when not needed.
#include "processing_map.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_files.hpp" //...is optional. Should be deleted when not needed.
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

/// String operations tests
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "STRINGTEST.PDE"
/////////////////////////////////////////////////////////////////

String A;                     ///
String B=nullptr;                ///
String C="Ala ma kota!";      ///
String D="😜👍 😡 🤼‍♂️ 🧐";///
String E=String("Number")+1;          ///

sarray<String> SA={
	A,B,C,D,E
	};      ///

pStringList SL=new StringList(SA);///

pArrayList<String> SAL=new ArrayList<String>();///

int y=0;///

void toScreen(pStringList lst)  ///
{
  for(String s:lst)
  if(s!=nullptr)
      text(s,1,y+=16);
}

void toScreen(pArrayList<String> lst)  ///
{
  for(String s:lst)
  if(s!=nullptr)
      text(s,1,y+=16);
}

void addStrings(pStringList lst1,pArrayList<String> lst2)  ///
{
  lst1->append(C+String("? & ")+E);
  for(String s:lst1)
    lst2->add(s);
}

void processing_window::setup()  ///
{
  size(300,200);
  for(String s:SA)
    println(s);
    
  addStrings(SL,SAL);  
  toScreen(SL);
  toScreen(SAL);
}
///home/data/SCC/__public_git/Processing2C/scripts/procesing2cpp.sh did it

