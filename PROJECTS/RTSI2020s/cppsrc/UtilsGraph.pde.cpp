//Processing to C++ converter ../../scripts/procesing2cpp.sh
//Source: UtilsGraph.pde
#include "processing_templates.hpp"
//#include "processing_inlines.hpp" //is optional. Use when project is already compilable
#include "processing_window.hpp"
#include "processing_library.hpp"
#include "processing_console.hpp" //is optional. Should be deleted when not needed
using namespace Processing;
#include "local.h"
#include "project.h" //Is's for you. Could be deleted when not needed
//==================================================================================

// Różne pomocne procedury rysujące
////////////////////////////////////////////////////////////////

void dottedline(int x1,int y1,int x2,int y2,float dens)
{
  for (int i = 0; i <= dens; i++) 
  {
    float x = lerp(x1, x2, i/dens);
    float y = lerp(y1, y2, i/dens);
    point(x, y);
  }
}

void dashedline(float x0, float y0, float x1, float y1,float dens)
{
  dashedline(x0,y0,x1,y1,new sarray<float>{
	dens,dens
	});
}

void surround(int x1,int y1,int x2,int y2)//Ramka domyslną linią
{
  line(x1,y1,x2,y1);//--->
  line(x2,y1,x2,y2);//vvv
  line(x1,y2,x2,y2);//<---
  line(x1,y1,x1,y2);//^^^
}

void cross(float x,float y,float cross_width)//Krzyzyk domyslną linią
{
  line(x-cross_width,y,x+cross_width,y);
  line(x,y-cross_width,x,y+cross_width);
}

void cross(int x,int y,int cross_width)//Krzyzyk domyslną linią
{
  line(x-cross_width,y,x+cross_width,y);
  line(x,y-cross_width,x,y+cross_width);
}

void baldhead(int x,int y,int r,float direction)
{
  float D=2*r;
  float xn=x+r*cos(direction);
  float yn=y+r*sin(direction);
  ellipse(xn,yn,D/5,D/5);  //Nos
  xn=x+0.95*r*cos(direction+PI/2);
  yn=y+0.95*r*sin(direction+PI/2);
  ellipse(xn,yn,D/4,D/4);  //Ucho  1
  xn=x+0.95*r*cos(direction-PI/2);
  yn=y+0.95*r*sin(direction-PI/2);
  ellipse(xn,yn,D/4,D/4);  //Ucho  2
  //Glówny blok
  ellipse(x,y,D,D);
}

void regularpoly(float x, float y, float radius, int npoints) 
{
  float angle = TWO_PI / npoints;
  beginShape();
  for (float a = 0; a < TWO_PI; a += angle) 
  {
    float sx = x + cos(a) * radius;
    float sy = y + sin(a) * radius;
    vertex(sx, sy);
  }
  endShape(CLOSE);
}

//POLYGON

class pointxy {
  public:
  float x;
  float y;
  
  pointxy()
  {
    x=y=0;
  }
  
  pointxy(float ix,float iy)
  {
    x=ix;y=iy;
  }
  
};

void polygon(sarray<ppointxy> lst/*+1*/,int N)
{
  beginShape();
  for (int a = 0; a < N; a ++) 
  {
    vertex(lst[a]->x,lst[a]->y);
  }
  endShape(CLOSE);
}
/*
Pair<pointxy,pointxy> nearestPoints(const sarray<ppointxy> listA,const sarray<ppointxy> listB)
//Najbliższe punkty dwóch wielokątów
{                                    assert(listA->length>0);assert(listB->length>0);
  float mindist=MAX_FLOAT;
  int   minA=-1;
  int   minB=-1;
  for(int i=0;i<listA->length;i++)
    for(int j=0;j<listB->length;j++) //Pętla nadmiarowa
    {
      float x2=(listA[i]->x-listB[j]->x)*(listA[i]->x-listB[j]->x);
      float y2=(listA[i]->y-listB[j]->y)*(listA[i]->y-listB[j]->y);
      if(x2+y2 < mindist)
      {
        mindist=x2+y2;
        minA=i; minB=j;
      }
    }
  return new Pair<pointxy,pointxy>(listA[minA],listB[minB]);
}
*/
//BAR3D 
class settings_bar3d {
  public:
  int a=10;
  int b=6;
  int c=6;
  color wire=color(255,255,255); //Kolor ramek
  color back=color(0,0,0); //Informacja o kolorze tla
};

psettings_bar3d bar3dsett=new settings_bar3d();

pointxy sarray<pbar3dromb>={
	new pointxy(),new pointxy(),new pointxy(),new pointxy(),new pointxy(),new pointxy()
	};

void bar3dRGB(float x,float y,float h,int R,int G,int B,int Shad)
{
                                                    /*      6 ------ 5    */
  bar3dromb[0]->x= x;                                /*     /        / |   */
  bar3dromb[0]->y= y - h;                            /*    1 ------ 2  |   */
  bar3dromb[1]->x= x + bar3dsett->a;                  /*    |        |  |   */
  bar3dromb[1]->y= bar3dromb[1-1]->y;                 /*    |        |  |   */
  bar3dromb[2]->x= bar3dromb[2-1]->x;                 /*    |        |  |   */
  bar3dromb[2]->y= y;                                /*    |        |  4   */
  bar3dromb[3]->x= x + bar3dsett->a + bar3dsett->b;    /*    |        | /  c */
  bar3dromb[3]->y= y - bar3dsett->c;                  /*  x,y ------ 3      */
  bar3dromb[4]->x= bar3dromb[4-1]->x;                 /*         a      b   */
  bar3dromb[4]->y= y - h - bar3dsett->c;
  bar3dromb[5]->x= x + bar3dsett->b;
  bar3dromb[5]->y= bar3dromb[5-1]->y;

  fill(R,G,B);
  rect(x,y-h,bar3dsett->a,h+1);               //front

  fill(R/Shad,G/Shad,B/Shad);
  polygon(bar3dromb/*+1*/,6);              //bok i gora

  stroke(bar3dsett->wire);
  //rect(bar3dromb[1-1]->x,bar3dromb[1-1]->y,bar3dromb[2-1]->x+1,bar3dromb[2-1]->y+1);//gorny poziom
  //rect(x,y,bar3dromb[3-1]->x+1,bar3dromb[3-1]->y+1);       //dolny poziom

  line(bar3dromb[2-1]->x,bar3dromb[2-1]->y,bar3dromb[5-1]->x,bar3dromb[5-1]->y); //blik?

  //point(bar3dromb[5]->x,bar3dromb[5]->y,wire_col-1);
  line(bar3dromb[1-1]->x,bar3dromb[1-1]->y,bar3dromb[6-1]->x,bar3dromb[6-1]->y);//lewy ukos
  line(bar3dromb[2-1]->x,bar3dromb[2-1]->y,bar3dromb[3-1]->x,bar3dromb[3-1]->y);//prawy ukos
  line(bar3dromb[3-1]->x,bar3dromb[3-1]->y,bar3dromb[4-1]->x,bar3dromb[4-1]->y);//dolny ukos
  line(bar3dromb[4-1]->x,bar3dromb[4-1]->y,bar3dromb[5-1]->x,bar3dromb[5-1]->y);//tyl bok
  line(bar3dromb[5-1]->x,bar3dromb[5-1]->y,bar3dromb[6-1]->x,bar3dromb[6-1]->y);//tyl bok

 // rect(x,y-h,1,h+1,wire_col);       //lewy pion
}/* end slupek RGB */

/* https://processing->org/discourse/beta/num_1202486379->html 
 * Draw a dashed line with given set of dashes and gap lengths. 
 * x0 starting x-coordinate of line. 
 * y0 starting y-coordinate of line. 
 * x1 ending x-coordinate of line. 
 * y1 ending y-coordinate of line. 
 * spacing array giving lengths of dashes and gaps in pixels; 
 *  an array with values {
	5, 3, 9, 4
	} will draw a line with a 
 *  5-pixel dash, 3-pixel gap, 9-pixel dash, and 4-pixel gap. 
 *  if the array has an odd number of entries, the values are 
 *  recycled, so an array of {
	5, 3, 2
	} will draw a line with a 
 *  5-pixel dash, 3-pixel gap, 2-pixel dash, 5-pixel gap, 
 *  3-pixel dash, and 2-pixel gap, then repeat. 
 */ 
 
void dashedline(float x0, float y0, float x1, float y1, sarray<float> spacing) 
{ 
  float distance = dist(x0, y0, x1, y1); 
  sarray<float> xSpacing = new array<float>(spacing->length); 
  sarray<float> ySpacing = new array<float>(spacing->length); 
  float drawn = 0.0;  // amount of distance drawn 
 
  if (distance > 0) 
  { 
    int i; 
    bool    drawLine = true; // alternate between dashes and gaps 
 
    /* 
      Figure out x and y distances for each of the spacing values 
      I decided to trade memory for time; I'd rather allocate 
      a few dozen bytes than have to do a calculation every time 
      I draw. 
    */ 
    for (i = 0; i < spacing->length; i++) 
    { 
      xSpacing[i] = lerp(0, (x1 - x0), spacing[i] / distance); 
      ySpacing[i] = lerp(0, (y1 - y0), spacing[i] / distance); 
    } 
 
    i = 0; 
    while (drawn < distance) 
    { 
      if (drawLine) 
      { 
        line(x0, y0, x0 + xSpacing[i], y0 + ySpacing[i]); 
      } 
      x0 += xSpacing[i]; 
      y0 += ySpacing[i]; 
      /* Add distance "drawn" by this line or gap */ 
      drawn = drawn + mag(xSpacing[i], ySpacing[i]); 
      i = (i + 1) % spacing->length;  // cycle through array 
      drawLine = !drawLine;  // switch between dash and gap 
    } 
  } 
} 
 
//STRZAŁKA W DOWOLNYM KIERUNKU
float def_arrow_size=15;
float def_arrow_theta=PI/6.0+PI;//3.6651914291881

void arrow(float x1,float y1,float x2,float y2)
{
  arrow_d(int(x1),int(y1),int(x2),int(y2),def_arrow_size,def_arrow_theta);
}

void arrow_d(int x1,int y1,int x2,int y2,float size,float theta)
{
  //METODA LICZENIA Z OBRACANIA OSI STRZALKI
  float A=(size>=1 ? size : size * sqrt( sqr(x1-x2)+sqr(y1-y2) ));
  float poY=float(y2-y1);
  float poX=float(x2-x1);

  if(poY==0 && poX==0)
  {
    //Rzadki błąd, ale duży problem
    float cross_width=def_arrow_size/2;
    //line(x1-cross_width,y1,x1+cross_width,y1);
    //line(x1,y1-cross_width,x1,y1+cross_width);
    ellipse(x1+def_arrow_size/*/sqrt(2.0)*/,y1/*-def_arrow_size/sqrt(2.0)+1*/,
            def_arrow_size*2,def_arrow_size*2);
    return;
  }
                                        assert(!(poY==0 && poX==0));
  float alfa=atan2(poY,poX);            if(abs(alfa)>PI+0.0000001)
                                             println("Alfa=%e\n",alfa);
                                      //assert(fabs(alfa)<=M_PI);//cerr<<alfa<<endl;
  float xo1=A*cos(theta+alfa);
  float yo1=A*sin(theta+alfa);
  float xo2=A*cos(alfa-theta);
  float yo2=A*sin(alfa-theta); //cross(x2,y2,128);DEBUG!

  line(int(x2+xo1),int(y2+yo1),x2,y2);
  line(int(x2+xo2),int(y2+yo2),x2,y2);
  line(x1,y1,x2,y2);
}

///////////////////////////////////////////////////////////////////////////////////////////
//  https://www->researchgate->net/profile/WOJCIECH_BORKOWSKI - HANDY FUNCTIONS & CLASSES
///////////////////////////////////////////////////////////////////////////////////////////
//../../scripts/procesing2cpp.sh did it

