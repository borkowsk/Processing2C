/// @file
/// String operations tests.
/// ORIGINAL FILE: "STRINGTEST.PDE"
/// @author: Wojciech Borkowski wborkowski_uw_edu_pl
/// @date 2024-10-15 (last change)
/////////////////////////////////////////////////////////////////

String A;                     ///< declared globally.
String B=nullptr;                ///< declared globally.
String C="Ala ma kota!";      ///< declared globally.
String D="😜👍 😡 🤼‍♂️ 🧐";      ///< declared globally.
String E=String("Number")+1;          ///< declared globally.

sarray<String> SA={A,B,C,D,E};      ///< declared globally.

pStringList SL=new StringList(SA); ///< declared globally.

pArrayList<String> SAL=new ArrayList<String>(); ///< declared globally.

int y=0; ///< declared globally

void toScreen(pStringList lst)  ///< declared globally.
{
  for(String s:lst)
  if(s!=nullptr)
      text(s,1,y+=16);
}

void toScreen(pArrayList<String> lst)  ///< declared globally.
{
  for(String s:lst)
  if(s!=nullptr)
      text(s,1,y+=16);
}

void addStrings(pStringList lst1,pArrayList<String> lst2)  ///< declared globally.
{
  lst1->append(C+String("? & ")+E);
  for(String s:lst1)
    lst2->add(s);
}

void processing_window::setup()  // Must be->But should not be marked with `///`
{
  size(300,200);
  for(String s:SA)
    println(s);
    
  addStrings(SL,SAL);  
  toScreen(SL);
  toScreen(SAL);
}
//MADE NOTE: ../../scripts did it 2024-10-15 16:10:56 !

