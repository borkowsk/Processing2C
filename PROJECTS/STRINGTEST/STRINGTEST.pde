/// String operations tests
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "STRINGTEST.PDE"
/////////////////////////////////////////////////////////////////

String A;                     ///< declared globally
String B=null;                ///< declared globally
String C="Ala ma kota!";      ///< declared globally
String D="😜👍 😡 🤼‍♂️ 🧐";   ///< declared globally
String E="Number"+1;          ///< declared globally

String[] SA={A,B,C,D,E};      ///< declared globally

StringList SL=new StringList(SA); ///< declared globally

ArrayList<String> SAL=new ArrayList<String>(); ///< declared globally

int y=0; ///< declared globally

void toScreen(StringList lst)  ///< declared globally
{
  for(String s:lst)
  if(s!=null)
      text(s,1,y+=16);
}

void toScreen(ArrayList<String> lst)  ///< declared globally
{
  for(String s:lst)
  if(s!=null)
      text(s,1,y+=16);
}

void addStrings(StringList lst1,ArrayList<String> lst2)  ///< declared globally
{
  lst1.append(C+"? & "+E);
  for(String s:lst1)
    lst2.add(s);
}

void setup()  // Must be
{
  size(300,200);
  for(String s:SA)
    println(s);
    
  addStrings(SL,SAL);  
  toScreen(SL);
  toScreen(SAL);
}
