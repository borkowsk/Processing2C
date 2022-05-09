//Processing to C++ converter /data/wb/SCC/public/Processing2C/scripts/procesing2cpp.sh
//Source: STRINGTEST.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "processing_string.hpp"  //Processing::String class
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_alist.hpp" //...is optional. Should be deleted when not needed.
#include "processing_lists.hpp" //...is optional. Should be deleted when not needed.
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

/// String operations tests
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "STRINGTEST.PDE"
/////////////////////////////////////////////////////////////////

String A;                     ///< declared globally
String B=nullptr;                ///< declared globally
String C="Ala ma kota!";      ///< declared globally
String D="😜👍 😡 🤼‍♂️ 🧐";   ///< declared globally
String E=String("Number")+1;          ///< declared globally

sarray<String> SA={
	A,B,C,D,E
	};      ///< declared globally

pStringList SL=new StringList(SA); ///< declared globally

pArrayList<String> SAL=new ArrayList<String>(); ///< declared globally

int y=0; ///< declared globally

void toScreen(pStringList lst)  ///< declared globally
{
  for(String s:lst)
  if(s!=nullptr)
      text(s,1,y+=16);
}

void toScreen(pArrayList<String> lst)  ///< declared globally
{
  for(String s:lst)
  if(s!=nullptr)
      text(s,1,y+=16);
}

void addStrings(pStringList lst1,pArrayList<String> lst2)  ///< declared globally
{
  lst1->append(C+String("? & ")+E);
  for(String s:lst1)
    lst2->add(s);
}

void processing_window::setup()  // Must be
{
  size(300,200);
  for(String s:SA)
    println(s);
    
  addStrings(SL,SAL);  
  toScreen(SL);
  toScreen(SAL);
}
///data/wb/SCC/public/Processing2C/scripts did it

