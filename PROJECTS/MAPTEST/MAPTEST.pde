//Test obiektow mapowych
//file:///home/borkowsk/processing-3.5.4/modes/java/reference/HashMap.html
import java.util.Map;

HashMap<String,Integer>  mapString2Integer=new HashMap<String,Integer>();
HashMap<Integer,String>  mapInteger2String=new HashMap<Integer,String>();
HashMap<String,Float>    mapString2Float=new HashMap<String,Float>();
HashMap<String,String>   mapString2String=new HashMap<String,String>();

class myObject {
  int A;float B;
  myObject(int iA,float iB)
  {
    A=iA;B=iB;
  }
};

HashMap<String,myObject> mapString2Object;

void setup()
{
  // Putting key-value pairs in the HashMap
  mapString2Integer.put("Ava", 1);
  mapString2Integer.put("Cait", 35);
  mapString2Integer.put("Casey", 36);
  
  // Using an enhanced loop to iterate over each entry
  for (Map.Entry me : mapString2Integer.entrySet()) {
    print(me.getKey() + " is ");
    println(me.getValue());
  }
  
  mapString2Integer.replace("Casey",10);
  // We can also access values by their key
  
  int val = mapString2Integer.get("Casey");
  println("Casey is now " + val);
  
  //More complicated
  println("\nUsing myObject");
  mapString2Object=new HashMap<String,myObject>();
  mapString2Object.put("Ataga",new myObject(-1,-0.99999));
  mapString2Object.put("Bulba",new myObject(0,0.0));
  mapString2Object.put("Cebas",new myObject(1,+0.99999));
  
  // Using an enhanced loop to iterate over each entry
  for (Map.Entry me : mapString2Object.entrySet()) {
    print(me.getKey() + " is { ");
    myObject obj=(myObject)me.getValue();
    println(obj.A,obj.B,"}");
  }
}
