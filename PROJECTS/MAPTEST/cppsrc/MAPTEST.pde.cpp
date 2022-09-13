//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: MAPTEST.pde
#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_inlines.hpp" //...is optional. Use when project is already compilable!
#include "processing_window.hpp"
#include "processing_console.hpp"   //...is optional. Should be deleted when not needed.
#include "processing_map.hpp"   //...is optional. Should be deleted when not needed.
#include "project.h" //...is for you. Could be deleted when not needed.
using namespace Processing;
#include "local.h"
//==================================================================================

/// Test for HashMaps
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "MAPTEST.pde"
//*////////////////////////////////////////////////////////////////////////////////
/// "file:///home/borkowsk/processing-3.5.4/modes/java/reference/HashMap.html"

//HashMap is used here // To wciąż potrzebne (?) do for(auto me : <<AnyHashMap>>->entrySet()) 

pHashMap<String,int>  mapString2Integer=new HashMap<String,int>();
pHashMap<int,String>  mapInteger2String=new HashMap<int,String>();
pHashMap<String,float>    mapString2Float=new HashMap<String,float>();
pHashMap<String,String>   mapString2String=new HashMap<String,String>();

class myTest: public virtual Object{
  public:
  int A;float B;
  myTest(int iA,float iB)
  {
    A=iA;B=iB;
  }
};

pHashMap<String,pmyTest>   mapString2Object=nullptr;

void adding(pHashMap<String,pmyTest>   map)
{
  map->put("Daga",new myTest(-1,-0.99999));
  map->put("Elfaba",new myTest(0,0.0));
  map->put("Fasaba",new myTest(1,+0.99999));
}

void texting(pHashMap<String,pmyTest>   map)
{
  int y=0;
  for(auto me:map->entrySet())
    text(me->getKey()+ String("!"),width/2,y+=16);
}

void processing_window::setup()
{
  size(200,200);
  // Putting key-value pairs in the HashMap
  mapString2Integer->put("Ava", 1);
  mapString2Integer->put("Cait", 35);
  mapString2Integer->put("Casey", 36);

  // Using an enhanced loop to iterate over each entry
  for(auto me : mapString2Integer->entrySet()) 
  {
    print(me->getKey() +  String(" is "));
    println(me->getValue());
  }
  
  mapString2Integer->replace("Casey",10);
  // We can also access values by their key
  
  int val = mapString2Integer->get("Casey");
  println(String("Casey is now ") + val);
  
  //More complicated
  println("\nUsing myObject");
  mapString2Object=new HashMap<String,pmyTest>();
  mapString2Object->put("Ataga",new myTest(-1,-0.99999));
  mapString2Object->put("Bulba",new myTest(0,0.0));
  mapString2Object->put("Cebas",new myTest(1,+0.99999));
  adding(mapString2Object);
  texting(mapString2Object);
  
  // Using an enhanced loop to iterate over each entry
  for(auto me : mapString2Object->entrySet()) 
  {
    print(me->getKey() +  String(" is { "));
    pmyTest obj= static_cast<pmyTest>(me->getValue()); // Second () required by C++ translation
    println(obj->A,obj->B,"}");
  }
  
  println("\nDefault print method:");
  println(mapString2Object);
}
//../../scripts did it

