//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: NetVisual.pde
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
#include "processing_inlines.hpp" //is optional. Use when project is already compilable
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

// Generic visualisations of a (social) network
///////////////////////////////////////////////////////////
float XSPREAD=0.01;   /// how far is target point of link of type 1, from center of the cell
int   linkCounter=0;  /// number od=f links visualised last time

//FUNCTIONS:
////////////
//void visualiseLinks(sarray<piVisNode>   nodes,float defX,float defY,float cellside);
//void visualiseLinks(smatrix<piVisNode> nodes,float defX,float defY,float cellside);

// INTERFACES
///////////////////////////////////
//interface
class iVisNode : public iNode,iNamed,iColorable,iPositioned {
  public:
  ///INFO:
};

//interface
class  iVisLink : public iLink,iNamed,iColorable {
  public:
  ///INFO:
};

//interface
class iNamed {
  public:
    ///INFO: Forcing name for visualisation and mapping by names                
  String    name();
};

//interface
class iColorable {
  public:
  ///INFO: Forcing setFill & setStroke methods for visualisation
  void setFill(float intensity);
  void setStroke(float intensity);
};

//interface
class iPositioned {
  public:
  ///INFO: Forcing posX() & posY() & posZ() methods for visualisation and mapping                
  float    posX();
  float    posY();
  float    posZ();
};

// IMPLEMENTATIONS:
///////////////////

void visualiseLinks(sarray<piVisNode> nodes,pLinkFilter filter,float defX,float defY,float cellside)
{
  noFill();strokeCap(ROUND);
  linkCounter=0;
  ellipseMode(CENTER);
  int n=nodes->length;
  for(int i=0;i<n;i++)
  {
    piVisNode Source=nodes[i];
    
    if(Source!=nullptr)
    {
      float X=Source->posX();
      sarray<pLink> links=Source->getConns(filter);
      int m=links->length;
      for(int j=0;j<m;j++)
      {
        float Xt=links[j]->target->posX();
        //print(X,Xt,"; "); 
        float R=abs(Xt-X)*cellside;
        float C=(X+Xt)/2;
        
        if(X<Xt) {
	 Xt+=links[j]->ltype*XSPREAD;
	}
        else    {
	 Xt-=links[j]->ltype*XSPREAD;
	}
        C*=cellside;
        
        links[j]->setStroke(LINK_INTENSITY);
        
        arc(defX+C,defY,R,R,0,PI);
        stroke(255);
        point(defX+(Xt*cellside),defY);
        linkCounter++;
      }
    }
  }
}

void visualiseLinks(smatrix<piVisNode> nodes,pLinkFilter filter,float defX,float defY,float cellside)
{
  noFill();
  linkCounter=0;
  for(int i=0;i<nodes->length;i++)
  for(int j=0;j<nodes[i]->length;j++)
  {
    piVisNode Source=nodes[i][j];
    
    if(Source!=nullptr)
    {
      float X=Source->posX();
      float Y=Source->posY();
      sarray<pLink> links=Source->getConns(filter);
      int n=links->length;
      
      for(int k=0;k<n;k++)
      {
        float Xt=links[k]->target->posX();
        float Yt=links[k]->target->posY();

        if(X<Xt) {
	 Xt+=links[k]->ltype*XSPREAD;
	}
        else    {
	 Xt-=links[k]->ltype*XSPREAD;
	}
        
        links[k]->setStroke(LINK_INTENSITY);
        arrow(defX+(X*cellside),defY+(Y*cellside),defX+(Xt*cellside),defY+(Yt*cellside));
        /*
        float midX=defX+( X*cellside + Xt*cellside )/2.0;
        float midY=defY+( Y*cellside + Yt*cellside )/2.0;
        stroke(255,0,0);
        line(defX+(X*cellside),defY+(Y*cellside),midX,midY);
        links[k]->setStroke(LINK_INTENSITY*0.77);
        stroke(0,0,255);
        line(midY,midY,defX+(Xt*cellside),defY+(Yt*cellside));
        */
        
        stroke(255);point(defX+(Xt*cellside),defY+(Yt*cellside));
        
        linkCounter++;
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate.net/profile/WOJCIECH_BORKOWSKI - SOCIAL NETWORK TEMPLATE
///////////////////////////////////////////////////////////////////////////////////////////
//../../scripts/procesing2cpp.sh did it

