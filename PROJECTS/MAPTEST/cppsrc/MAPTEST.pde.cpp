//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: MAPTEST.pde
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

//Test for HashMaps
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "MAPTEST.pde"
//////////////////////////////////////////////////////////////////////////////////
/// "file:///home/borkowsk/processing-3.5.4/modes/java/reference/HashMap.html"
//HashMap is used here//To wciąż potrzebne do for(auto me : <<AnyHashMap>>->entrySet()) 

sHashMap<String,int>  mapString2Integer=new HashMap<String,int>();
sHashMap<int,String>  mapInteger2String=new HashMap<int,String>();
sHashMap<String,float>    mapString2Float=new HashMap<String,float>();
sHashMap<String,String>   mapString2String=new HashMap<String,String>();

class myObject: public virtual Object{
  public:
  int A;float B;
  myObject(int iA,float iB)
  {
    A=iA;B=iB;
  }
};

sHashMap<String,pmyObject> mapString2Object;

void processing_window::setup()
{
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
  mapString2Object=new HashMap<String,pmyObject>();
  mapString2Object->put("Ataga",new myObject(-1,-0.99999));
  mapString2Object->put("Bulba",new myObject(0,0.0));
  mapString2Object->put("Cebas",new myObject(1,+0.99999));
  
  // Using an enhanced loop to iterate over each entry
  for(auto me : mapString2Object->entrySet()) 
  {
    print(me->getKey() +  String(" is { "));
    pmyObject obj=static_cast<pmyObject>(me->getValue());//Second () required by C++ translation
    println(obj->A,obj->B,"}");
  }
  
  println("\nDefault print method:");
  println(mapString2Object);
}
//../../scripts/procesing2cpp.sh did it

