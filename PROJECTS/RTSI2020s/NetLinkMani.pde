// Diferent filters of links and other link tols for a (social) network
///////////////////////////////////////////////////////////////////////////////////////////
// Available filters: 
//   AllLinks, AndFilter, OrFilter, TypeFilter,
//   LowPassFilter,   HighPassFilter,
//   AbsLowPassFilter, AbsHighPassFilter
//   TypeAndAbsHighPassFilter - special type for efficient visualisation

class AllLinks extends LinkFilter
// Simplest link filtering class which accepts all links
{
  boolean meetsTheAssumptions(Link l) { return true;}
};

AllLinks allLinks=new AllLinks();//Used very frequently

class TypeAndAbsHighPassFilter  extends LinkFilter {
  ///INFO: Special type for efficient visualisation
  int ltype;
  float treshold;
  TypeAndAbsHighPassFilter(){ ltype=-1;treshold=0;}
  TypeAndAbsHighPassFilter(int t,float tres) { ltype=t;treshold=tres;}
  TypeAndAbsHighPassFilter reset(int t,float tres) { ltype=t;treshold=tres;return this;}
  boolean meetsTheAssumptions(Link l) { return l.ltype==ltype && abs(l.weight)>treshold;}
};

class AndFilter extends LinkFilter {
   ///INFO: Special class for the assembly of various filters
   LinkFilter a;
   LinkFilter b;
   AndFilter(LinkFilter aa,LinkFilter bb){a=aa;b=bb;}
   boolean meetsTheAssumptions(Link l) 
   { 
     return a.meetsTheAssumptions(l) && b.meetsTheAssumptions(l);
   }
};

class OrFilter extends LinkFilter {
   ///INFO: Another filters assembly class
   LinkFilter a;
   LinkFilter b;
   OrFilter(LinkFilter aa,LinkFilter bb){a=aa;b=bb;}
   boolean meetsTheAssumptions(Link l) 
   { 
     return a.meetsTheAssumptions(l) || b.meetsTheAssumptions(l);
   }
};

class TypeFilter extends LinkFilter {
  ///INFO: TypeFilter filtering links of specific "color"
  int ltype;
  TypeFilter(int t) { ltype=t;}
  boolean meetsTheAssumptions(Link l) { return l.ltype==ltype;}
};

class LowPassFilter extends LinkFilter {
  ///INFO: lowPassFilter filtering links with lower weights
  float treshold;
  LowPassFilter(float tres) { treshold=tres;}
  boolean meetsTheAssumptions(Link l) { return l.weight<treshold;}
};

class HighPassFilter extends LinkFilter {
  ///INFO: lowPassFilter filtering links with higher weights
  float treshold;
  HighPassFilter(float tres) { treshold=tres;}
  boolean meetsTheAssumptions(Link l) { return l.weight>treshold;}
};

class AbsLowPassFilter extends LinkFilter {
  ///INFO: lowPassFilter filtering links with lower absolute value of weight
  float treshold;
  AbsLowPassFilter(float tres) { treshold=abs(tres);}
  boolean meetsTheAssumptions(Link l) { return abs(l.weight)<treshold;}
};

class AbsHighPassFilter extends LinkFilter {
  ///INFO:  lowPassFilter filtering links with higher absolute value of weight
  float treshold;
  AbsHighPassFilter(float tres) { treshold=abs(tres);}
  boolean meetsTheAssumptions(Link l) { return abs(l.weight)>treshold;}
};

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI - SOCIAL NETWORK TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////
