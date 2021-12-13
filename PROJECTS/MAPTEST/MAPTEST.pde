/// Test for HashMaps
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "MAPTEST.pde"
//////////////////////////////////////////////////////////////////////////////////
/// "file:///home/borkowsk/processing-3.5.4/modes/java/reference/HashMap.html"
import java.util.Map;//To wciąż potrzebne do for(Map.Entry me : <<AnyHashMap>>.entrySet()) 

HashMap<String,Integer>  mapString2Integer=new HashMap<String,Integer>();
HashMap<Integer,String>  mapInteger2String=new HashMap<Integer,String>();
HashMap<String,Float>    mapString2Float=new HashMap<String,Float>();
HashMap<String,String>   mapString2String=new HashMap<String,String>();
HashMap<String,myTest>   mapString2Object;

class myTest {
  int A;float B;
  myTest(int iA,float iB)
  {
    A=iA;B=iB;
  }
};

void adding(HashMap<String,myTest>   map)
{
  map.put("Daga",new myTest(-1,-0.99999));
  map.put("Elfaba",new myTest(0,0.0));
  map.put("Fasaba",new myTest(1,+0.99999));
}

void texting(HashMap<String,myTest>   map)
{
  int y=0;
  for(Map.Entry me:map.entrySet())
    text(me.getKey()+"!",width/2,y+=16);
}

void setup()
{
  size(200,200);
  // Putting key-value pairs in the HashMap
  mapString2Integer.put("Ava", 1);
  mapString2Integer.put("Cait", 35);
  mapString2Integer.put("Casey", 36);

  // Using an enhanced loop to iterate over each entry
  for(Map.Entry me : mapString2Integer.entrySet()) 
  {
    print(me.getKey() + " is ");
    println(me.getValue());
  }
  
  mapString2Integer.replace("Casey",10);
  // We can also access values by their key
  
  int val = mapString2Integer.get("Casey");
  println("Casey is now " + val);
  
  //More complicated
  println("\nUsing myObject");
  mapString2Object=new HashMap<String,myTest>();
  mapString2Object.put("Ataga",new myTest(-1,-0.99999));
  mapString2Object.put("Bulba",new myTest(0,0.0));
  mapString2Object.put("Cebas",new myTest(1,+0.99999));
  adding(mapString2Object);
  texting(mapString2Object);
  
  // Using an enhanced loop to iterate over each entry
  for(Map.Entry me : mapString2Object.entrySet()) 
  {
    print(me.getKey() + " is { ");
    myTest obj=/*_upcast*/(myTest)(me.getValue());//Second () required by C++ translation
    println(obj.A,obj.B,"}");
  }
  
  println("\nDefault print method:");
  println(mapString2Object);
}
