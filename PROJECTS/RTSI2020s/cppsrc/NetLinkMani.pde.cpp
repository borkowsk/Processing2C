//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: NetLinkMani.pde
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
#include "processing_inlines.hpp" //is optional. Use when project is already compilable
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

// Diferent filters of links and other link tols for a (social) network
///////////////////////////////////////////////////////////////////////////////////////////
// Available filters: 
//   AllLinks, AndFilter, OrFilter, TypeFilter,
//   LowPassFilter,   HighPassFilter,
//   AbsLowPassFilter, AbsHighPassFilter
//   TypeAndAbsHighPassFilter - special type for efficient visualisation

class AllLinks : public LinkFilter
// Simplest link filtering class which accepts all links
{
  bool meetsTheAssumptions(pLink l) {
	 return true;
	}
};

pAllLinks allLinks=new AllLinks();//Used very frequently

class TypeAndAbsHighPassFilter  : public LinkFilter {
  public:
  ///INFO: Special type for efficient visualisation
  int ltype;
  float treshold;
  TypeAndAbsHighPassFilter(){
	 ltype=-1;treshold=0;
	}
  TypeAndAbsHighPassFilter(int t,float tres) {
	 ltype=t;treshold=tres;
	}
  pTypeAndAbsHighPassFilter reset(int t,float tres) {
	 ltype=t;treshold=tres;
	return  this;
	}
  bool meetsTheAssumptions(pLink l) {
	 return l->ltype==ltype && abs(l->weight)>treshold;
	}
};

class AndFilter : public LinkFilter {
  public:
   ///INFO: Special class for the assembly of various filters
   pLinkFilter a;
   pLinkFilter b;
   AndFilter(pLinkFilter aa,pLinkFilter bb){
	a=aa;b=bb;
	}
   bool meetsTheAssumptions(pLink l) 
   { 
     return a->meetsTheAssumptions(l) && b->meetsTheAssumptions(l);
   }
};

class OrFilter : public LinkFilter {
  public:
   ///INFO: Another filters assembly class
   pLinkFilter a;
   pLinkFilter b;
   OrFilter(pLinkFilter aa,pLinkFilter bb){
	a=aa;b=bb;
	}
   bool meetsTheAssumptions(pLink l) 
   { 
     return a->meetsTheAssumptions(l) || b->meetsTheAssumptions(l);
   }
};

class TypeFilter : public LinkFilter {
  public:
  ///INFO: TypeFilter filtering links of specific "color"
  int ltype;
  TypeFilter(int t) {
	 ltype=t;
	}
  bool meetsTheAssumptions(pLink l) {
	 return l->ltype==ltype;
	}
};

class LowPassFilter : public LinkFilter {
  public:
  ///INFO: lowPassFilter filtering links with lower weights
  float treshold;
  LowPassFilter(float tres) {
	 treshold=tres;
	}
  bool meetsTheAssumptions(pLink l) {
	 return l->weight<treshold;
	}
};

class HighPassFilter : public LinkFilter {
  public:
  ///INFO: lowPassFilter filtering links with higher weights
  float treshold;
  HighPassFilter(float tres) {
	 treshold=tres;
	}
  bool meetsTheAssumptions(pLink l) {
	 return l->weight>treshold;
	}
};

class AbsLowPassFilter : public LinkFilter {
  public:
  ///INFO: lowPassFilter filtering links with lower absolute value of weight
  float treshold;
  AbsLowPassFilter(float tres) {
	 treshold=abs(tres);
	}
  bool meetsTheAssumptions(pLink l) {
	 return abs(l->weight)<treshold;
	}
};

class AbsHighPassFilter : public LinkFilter {
  public:
  ///INFO:  lowPassFilter filtering links with higher absolute value of weight
  float treshold;
  AbsHighPassFilter(float tres) {
	 treshold=abs(tres);
	}
  bool meetsTheAssumptions(pLink l) {
	 return abs(l->weight)>treshold;
	}
};

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate.net/profile/WOJCIECH_BORKOWSKI - SOCIAL NETWORK TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////
//../../scripts/procesing2cpp.sh did it

