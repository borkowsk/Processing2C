/// String operations tests
/// Author: Wojciech Borkowski wborkowski_uw_edu_pl
/// ORIGINAL FILE: "STRINGTEST.PDE"
/////////////////////////////////////////////////////////////////

String A;                     ///
String B=null;                ///
String C="Ala ma kota!";      ///
String D="😜👍 😡 🤼‍♂️ 🧐";///
String E="Number"+1;          ///

String[] SA={A,B,C,D,E};      ///

StringList SL=new StringList(SA);///

ArrayList<String> SAL=new ArrayList<String>();///

int y=0;///

void toScreen(StringList lst)  ///
{
  for(String s:lst)
  if(s!=null)
      text(s,1,y+=16);
}

void toScreen(ArrayList<String> lst)  ///
{
  for(String s:lst)
  if(s!=null)
      text(s,1,y+=16);
}

void addStrings(StringList lst1,ArrayList<String> lst2)  ///
{
  lst1.append(C+"? & "+E);
  for(String s:lst1)
    lst2.add(s);
}

void setup()  ///
{
  size(300,200);
  for(String s:SA)
    println(s);
    
  addStrings(SL,SAL);  
  toScreen(SL);
  toScreen(SAL);
}
