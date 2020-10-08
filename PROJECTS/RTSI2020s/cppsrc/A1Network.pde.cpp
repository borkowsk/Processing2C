//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: A1Network.pde
#include "processing_templates.hpp"
//#include "processing_inlines.hpp" //is optional. Use when project is already compilable
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

// Generic (social) network
//////////////////////////////////////////////////////////////
// Classes:
///////////
// class Link : public Colorable //USER CAN MODIFY FOR THE SAKE OF EFFICIENCY
// class NodeList : public Node
// class NodeMap : public Node
//
// Abstractions:
////////////////
// abstract class Node : public Positioned 
//
// abstract class LinkFilter
// abstract class LinkFactory
//
// abstract class Named : public iNamed
// abstract class Colorable : public Named : public iColorable
// abstract class Positioned : public Colorable : public iPositioned
//
// INTERFACES:
//////////////
// interface iLink //Is it really needed?
// interface iNode //using class Link not interface iLink because of efficiency!
//
// Network generators: 
//////////////////////
// void makeRingNet(sarray<pNode> nodes,pLinkFactory links,int neighborhood);
// void makeTorusNet(sarray<pNode> nodes,pLinkFactory links,int neighborhood);
// void makeTorusNet(smatrix<pNode> nodes,pLinkFactory links,int neighborhood);
// 
// void makeFullNet(sarray<pNode> nodes,pLinkFactory links);
// void makeFullNet(smatrix<pNode> nodes,pLinkFactory links);
// 
// void makeRandomNet(sarray<pNode> nodes,pLinkFactory links,float probability);
// void makeRandomNet(smatrix<pNode> nodes,pLinkFactory links,float probability);
// 
// void makeSmWorldNet(sarray<pNode> nodes,pLinkFactory links,int neighborhood,float probability);
// void makeImSmWorldNet(sarray<pNode> nodes,pLinkFactory links,int neighborhood,float probability);
// 
//
#include "processing_map.hpp"

int debug_level=0;  ///visible autside this file!

// INTERFACES:
//////////////

//interface
class iLink {
  public: 
  ///INFO: Is iLink interface really needed?
  float getWeight();
};

//interface
class iNode {
  public: 
  ///INFO: "Conn" below is a shortage from Connection.
  //using class Link not interface iLink because of efficiency!
  int     addConn(pLink   l);
  int     delConn(pLink   l);
  int     numOfConn()      ;
  pLink    getConn(int    i);
  pLink    getConn(pNode   n);
  pLink    getConn(String k);
  sarray<pLink>  getConns(pLinkFilter f);
};

// ABSTRACT BASE CLASSES
///////////////////////////////////

//abstract
 class LinkFilter {
   public:
  ///INFO: 
  bool    meetsTheAssumptions(pLink l)
                  {
	assert(false );	//  "Pure interface meetsTheAssumptions(Link) called";
 	return  false;
	}
};

//abstract
 class LinkFactory {
   public:
  ///INFO: 
  pLink  makeLink(pNode Source,pNode Target)
                  {
	assert(false );	//  "Pure interface make(Node,Node) called";
 	return  nullptr;
	}
};

//abstract
 class Named : public iNamed {
   public: 
  ///INFO: Forcing name() method for visualisation and mapping                
  String    name(){
	assert(false );	//  "Pure interface name() called";
 	return  nullptr;
	}
};

//abstract
 class Colorable : public Named , iColorable {
   public:
  ///INFO: For visualisation
  void setFill(float modifier){
	assert(false );	//  "Pure interface setFill() called";
	}
  void setStroke(float modifier){
	assert(false );	//  "Pure interface setStroke() called";
	}
};

//abstract
 class Positioned : public Colorable , iPositioned {
   public:
  ///INFO: Forcing posX() & posY() & posZ() methods for visualisation and mapping                
  float    posX(){
	assert(false );	//  "Pure interface posX() called";
 	return  0;
	}
  float    posY(){
	assert(false );	//  "Pure interface posY() called";
 	return  0;
	}
  float    posZ(){
	assert(false );	//  "Pure interface posZ() called";
 	return  0;
	}
};

//abstract
 class Node : public Positioned , iNode {
   public:
  ///INFO: 
  int     addConn(pLink   l){
	assert(false );	//  String("Pure interface addConn(Link ")+l+ String(") called");
 	return    -1;
	}
  int     delConn(pLink   l){
	assert(false );	//  String("Pure interface delConn(Link ")+l+ String(") called");
 	return    -1;
	}
  int     numOfConn()      {
	assert(false );	//  "Pure interface numOfConn() called";
 	return    -1;
	}
  pLink    getConn(int    i){
	assert(false );	//  String("Pure interface getConn(int ")+i+ String(")  called");
 	return  nullptr;
	}
  pLink    getConn(pNode   n){
	assert(false );	//  String("Pure interface getConn(Node ")+n+ String(") called");
 	return  nullptr;
	}
  pLink    getConn(String k){
	assert(false );	//  String("Pure method  getConn(String '")+k+ String("') called");
 	return  nullptr;
	}
  sarray<pLink>  getConns(pLinkFilter f)
                  {
	assert(false );	//  String("Pure interface getConns(LinkFilter ")+f+ String(") called");
 	return  nullptr;
	}
};

// CLASS FOR MODIFICATION:
//////////////////////////

class Link : public Colorable , iLink,iVisLink,Comparable<pLink> {
  public:
  ///INFO: This class is available for user modifications
  pNode  target;
  float weight;//importance/trust
  int   ltype;//"color"
  //... add something, if you need in derived classes
  
  //Constructor (may vary)
  Link(pNode targ,float we,int ty){
	 target=targ;weight=we;ltype=ty;
	}
  
  String fullInfo(String fieldSeparator)
  {
    return String("W:")+weight+fieldSeparator+String("Tp:")+ltype+fieldSeparator+String("->")+target;
  }
  
  //For sorting. Much weighted link should be at the begining of the array!
  int  compareTo(pLink o)//Compares this object with the specified object for order.
  {
     if(o==this || o->weight==weight) return 0;
     else
     if(o->weight>weight) return 1;
     else return -1;
  }
  
  //For visualisation and mapping  
  String name(){
	 return target->name(); 
	}
  
  float getWeight() {
	 return weight;
	}
  
  void setStroke(float Intensity)
  {
     strokeWeight(abs(weight)*MAX_LINK_WEIGHT);
     switch ( ltype )
     {
     case 0: if(weight<=0) stroke(0,-weight*255,0,Intensity);else stroke(weight*255,0,weight*255,Intensity);break;
     case 1: if(weight<=0) stroke(-weight*255,0,0,Intensity);else stroke(0,weight*255,weight*255,Intensity);break;
     case 2: if(weight<=0) stroke(0,0,-weight*255,Intensity);else stroke(weight*255,weight*255,0,Intensity);break;
     default://Wszystkie inne 
             if(weight>=0) stroke(128,0,weight*255,Intensity);else stroke(-weight*255,-weight*255,128,Intensity);
             break;
     }
  }
};


// IMPLEMENTATIONS:
///////////////////

void makeRingNet(sarray<pNode> nodes,pLinkFactory linkfac,int neighborhood)
{
  int n=nodes->length;
  for(int i=0;i<n;i++)
  {
    pNode Source=nodes[i];
    
    if(Source!=nullptr)
    {
      if(debug_level>2) println(i,Source,' ');
      for(int j=1;j<=neighborhood;j++)
      {
        int g=(i-j+n)%n;//left index
        int h=(i+j+n)%n;//right index
        
        if(nodes[g]!=nullptr)
        {
          if(debug_level>2) print(i,g,' ');
          Source->addConn( linkfac->makeLink(Source,nodes[g]) );
        }
        
        if(nodes[h]!=nullptr)
        {
          if(debug_level>2) print(i,h,' ');
          Source->addConn( linkfac->makeLink(Source,nodes[h]) );
        }    
        
        if(debug_level>2) println();
      }
    }
  }
}

void makeTorusNet(sarray<pNode> nodes,pLinkFactory links,int neighborhood)//It is alias only
{
   makeRingNet(nodes,links,neighborhood);
}

void makeTorusNet(smatrix<pNode> nodes,pLinkFactory linkfac,int neighborhood)
{
  int s=nodes->length;   
  for(int i=0;i<s;i++)
  {
    int z=nodes[i]->length;
    for(int k=0;k<z;k++)
    {
      pNode Source=nodes[i][k];
      
      if(Source!=nullptr)
      {
        if(debug_level>2) println(i,k,Source,' ');
        
        for(int j=-neighborhood;j<=neighborhood;j++)
        {
          int vert=(s+i+j)%s;//up index
          
          for(int m=-neighborhood;m<=neighborhood;m++)
          {
            int hor=(z+k+m)%z;//right index
            
            pNode Target;
            
            if((Target=nodes[vert][hor])!=nullptr && Target!=Source)
            {
              if(debug_level>2) print(vert,hor,' ');
              Source->addConn( linkfac->makeLink(Source,Target) );
            }
  
            if(debug_level>2) println();
          }
        }
      }
    }
  }
}

void rewireLinksRandomly(smatrix<pNode> nodes,float probability)
{
  for(int i=0;i<nodes->length;i++)
  for(int g=0;g<nodes[i]->length;g++)
  {
    pNode Source=nodes[i][g];
    if(Source==nullptr) 
                  continue;
                  
    int j=(int)random(nodes->length);
    int h=(int)random(nodes[j]->length);
    pNode Target=nodes[j][h];
    if(Target==nullptr || Source==Target)
                  continue;    
    
    if(random(1.0)<probability)
    {
       //if(debug_level>2) 
       print(i,g,j,h);
       
       int index=(int)random(Source->numOfConn());
       assert(index<Source->numOfConn());	//
       pLink l=Source->getConn(index);
       
       l->target=Target;//Replacing target!
          
       //if(debug_level>2) 
       println();
    }  
  }
}

void makeSmWorldNet(smatrix<pNode> nodes,pLinkFactory links,int neighborhood,float probability)
{
  makeTorusNet(nodes,links,neighborhood);
  rewireLinksRandomly(nodes,probability);
}

void makeImSmWorldNet(smatrix<pNode> nodes,pLinkFactory links,int neighborhood,float probability)
{
  makeTorusNet(nodes,links,neighborhood);
  makeRandomNet(nodes,links,probability);
}

void makeFullNet(sarray<pNode> nodes,pLinkFactory linkfac)
{
  int n=nodes->length;
  for(int i=0;i<n;i++)
  {
    pNode Source=nodes[i];
    if(Source!=nullptr)
      for(int j=0;j<n;j++)
        if(i!=j && nodes[j]!=nullptr )
        {
          if(debug_level>2) print(i,j);
          
          Source->addConn( linkfac->makeLink(Source,nodes[j]) );
          
          if(debug_level>2) println();
        }
  }
}

void makeRandomNet(sarray<pNode> nodes,pLinkFactory linkfac,float probability)
{
  int n=nodes->length;
  for(int i=0;i<n;i++)
  {
    pNode Source=nodes[i];
    if(Source!=nullptr)
      for(int j=0;j<n;j++)
        if(i!=j && nodes[j]!=nullptr && random(1)<probability)
        {
          if(debug_level>2) print(i,j);
          
          Source->addConn( linkfac->makeLink(Source,nodes[j]) );
          
          if(debug_level>2) println();
        }
  }
}

void makeFullNet(smatrix<pNode> nodes,pLinkFactory linkfac)
{
  for(int i=0;i<nodes->length;i++)
  for(int g=0;g<nodes[i]->length;g++)
  {
    pNode Source=nodes[i][g];
    
    if(Source!=nullptr)
      for(int j=0;j<nodes->length;j++)
      for(int h=0;h<nodes[j]->length;h++)
      {
        pNode Target=nodes[j][h];
        
        if(Target!=nullptr && Source!=Target)
        {
          if(debug_level>2) print(i,g,j,h);
          
          Source->addConn( linkfac->makeLink(Source,Target) );
          
          if(debug_level>2) println();
        }
      }
  }
}

void makeRandomNet(smatrix<pNode> nodes,pLinkFactory linkfac,float probability)
{
  for(int i=0;i<nodes->length;i++)
  for(int g=0;g<nodes[i]->length;g++)
  {
    pNode Source=nodes[i][g];
    
    if(Source!=nullptr)
      for(int j=0;j<nodes->length;j++)
      for(int h=0;h<nodes[j]->length;h++)
      {
        pNode Target=nodes[j][h];
        
        if(Target!=nullptr && Source!=Target && random(1)<probability)
        {
          if(debug_level>2) print(i,g,j,h);
          
          Source->addConn( linkfac->makeLink(Source,Target) );
          
          if(debug_level>2) println();
        }
      }
  }
}

class NodeList : public Node {
  public:
  ///INFO: 
  sArrayList<pLink> connections;//https://docs->oracle->com/javase/8/docs/api/java/util/ArrayList->html
  
  NodeList()
  {
    connections=new ArrayList<pLink>();
  }
  
  int     numOfConn()      {
	 return connections->size();
	}
  
  int     addConn(pLink   l)
  {
    assert(l!=nullptr );	//  String("Empty link in ")+this->getClass().getName()+ String(".addConn(Link)?"); 
    bool    res=connections->add(l); 
    if(res)
      return   1;
    else
      return   0;
  }
  
  int     delConn(pLink   l)
  {
    assert(false );	//  String("Not implemented ")+this->getClass().getName()+String(".delConn(Link ")+l+ String(") called"); 
    return   -1;
  }
  
  pLink    getConn(int    i)
  {
    assert(i<connections->size());	//  String("Index '")+i+String("' out of bound '")+connections->size()+String("' in ")+this->getClass().getName()+ String(".getConn(int)"); 
    return connections->get(i);
  }
  
  pLink    getConn(pNode   n)
  {
    assert(n!=nullptr );	//  String("Empty node in ")+this->getClass().getName()+ String(".getConn(Node)"); 
    for(pLink l:connections)
    {
      if(l->target==n) 
            return l;
    }
    return nullptr;
  }
  
  pLink    getConn(String k)
  {
    assert(k==nullptr || k=="" );	//  String("Empty string in ")+this->getClass().getName()+ String(".getConn(String)"); 
    for(pLink l:connections)
    {
      if(l->target->name()==k) 
            return l;
    }
    return nullptr;
  }
  
  sarray<pLink>  getConns(pLinkFilter f)
  {
    assert(f!=nullptr );	//  String("Empty LinkFilter in ")+this->getClass().getName()+ String(".getConns(LinkFilter)"); 
    sArrayList<pLink> selected=new ArrayList<pLink>();
    for(pLink l:connections)
    {
      if(f->meetsTheAssumptions(l)) 
            selected->add(l);
    }
    
    sarray<pLink> ret=new array<pLink>(selected->size());
    selected->toArray(ret);
    return ret;
  }
};

class NodeMap : public Node {
  public:
  ///INFO: 
  HashMap<String,Link> connections;//https://docs->oracle->com/javase/6/docs/api/java/util/HashMap->html
  
  NodeMap()
  {
    connections=new HashMap<String,Link>(); 
  }
  
  int     numOfConn()      {
	 return connections->size();
	}
  
  int     addConn(pLink   l)
  {
    assert(l!=nullptr );	//  String("Empty link in ")+this->getClass().getName()+ String(".addConn(Link)?"); 
    String key=l->target->name();
    pLink old=connections->put(key,l); 
    if(old==nullptr)
      return   1;
    else
      return 0;
  }
  
  int     delConn(pLink   l)
  {
    assert(false );	//  String("Not implemented ")+this->getClass().getName()+String(".delConn(Link ")+l+ String(") called"); 
    return   -1;
  }
  
  pLink    getConn(int    i)
  {
    assert(i>=connections->size());	// String("Index '")+i+String("' out of bound '")+connections->size()+String("' in ")+this->getClass().getName()+ String(".getConn(int)"); 
    assert(false);	//  "Non optimal use of NodeMap in getConn(int)";
    int counter=0;
    for(Map->Entry<String,Link> ent:connections->entrySet())
    {
      if(i==counter) 
          return ent->getValue();
      counter++;
    }
    return nullptr;
  }
  
  pLink    getConn(pNode   n)
  {
    assert(n!=nullptr );	//  String("Empty node in ")+this->getClass().getName()+ String(".getConn(Node)"); 
    String key=n->name();
    return connections->get(key);
  }
  
  pLink    getConn(String k)
  {
    assert(k==nullptr || k=="" );	//  String("Empty string in ")+this->getClass().getName()+ String(".getConn(String)"); 
    return connections->get(k);
  }
  
  sarray<pLink>  getConns(pLinkFilter f)
  {
    assert(f!=nullptr );	//  String("Empty LinkFilter in ")+this->getClass().getName()+ String(".getConns(LinkFilter)"); 
    sArrayList<pLink> selected=new ArrayList<pLink>();
    for(Map->Entry<String,Link> ent:connections->entrySet())
    {
      if(f->meetsTheAssumptions(ent->getValue())) 
            selected->add(ent->getValue());
    }
    sarray<pLink> ret=new array<pLink>(selected->size());
    selected->toArray(ret);
    return ret;
  }
};

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - SOCIAL NETWORK TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////
//../../scripts/procesing2cpp.sh did it

