/// podstawy obsługo okienka pseudo-processingowego
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "SYMSHELL/symshell.h"
#include <iostream>

namespace Processing
{

void noSmooth()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void smooth()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void strokeCap(int cap)/// Parameters	cap 	int: either SQUARE, PROJECT, or ROUND
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void strokeJoin(int join)/// Parameters	join 	int: either MITER, BEVEL, ROUND
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

static int lineWidthMem=1;

void strokeWeight(float Weight)/// Parameters	weight 	float: the weight (in pixels) of the stroke
{
    line_width(lineWidthMem=(int)Weight);
}

void stroke(float Gray)
{
    int S=(int)Gray;
    set_pen_rgb(S,S,S,lineWidthMem,1 /*style*/);
}

void stroke(float Gray,float Alpha)
{
    int S=(int)Gray;
    set_pen_rgb(S,S,S,lineWidthMem,1 /*style*/);
    std::cerr<<__FUNCTION__<<" - Alpha ignored!"<<std::endl;
}

void stroke(float Red,float Green,float Blue)
{
    set_pen_rgb((int)Red,(int)Green,(int)Blue,lineWidthMem,1 /*style*/);
}

void stroke(float Red,float Green,float Blue,float Alpha)
{
    set_pen_rgb((int)Red,(int)Green,(int)Blue,lineWidthMem,1 /*style*/);
    std::cerr<<__FUNCTION__<<" - Alpha ignored!"<<std::endl;
}

void noStroke()
{
    line_width(0);//???
    //std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

static bool filled=true;

void fill(float Gray)
{
    int S=(int)Gray;
    set_brush_rgb(S,S,S);
    filled=true;
}

void fill(float Gray,float Alpha)
{
    int S=(int)Gray;
    set_brush_rgb(S,S,S);
    filled=true;
    std::cerr<<__FUNCTION__<<" - Alpha ignored!"<<std::endl;
}

void fill(float Red,float Green,float Blue)
{
    set_brush_rgb((int)Red,(int)Green,(int)Blue);
    filled=true;
}

void fill(float Red,float Green,float Blue,float Alpha)
{
    set_brush_rgb((int)Red,(int)Green,(int)Blue);
    filled=true;
    std::cerr<<__FUNCTION__<<" - Alpha ignored!"<<std::endl;
}

void noFill()
{
    filled=false;
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void point(float x,float y)
{
    plot_d((int)x,(int)y);
}

void line(float  x1,float  y1,float  x2,float  y2)
{
    line_d((int)x1,(int)y1,(int)x2,(int)y2);
}

void rect(float a,float  b,float  c,float  d)
{
    int x1=a;
    int y1=b;
    int x2=a+c;
    int y2=b+d;

    if(filled)
        fill_rect_d(x1,y1,x2,y2);

    if(get_line_width()>0)
    {
        line_d(x1,y1,x1,y2);
        line_d(x1,y1,x2,y1);
    }
}

void rect(float a,float  b,float  c,float  d,float r)
{
    rect(a,b,c,d);
    std::cerr<<__FUNCTION__<<" - r parameter is ignored!"<<std::endl;
}

/// Parameter: mode 	int: either CORNER, CORNERS, CENTER, or RADIUS
void rectMode(int mode)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

/// Parameters
///  a 	float: x-coordinate of the ellipse
///  b 	float: y-coordinate of the ellipse
///  c 	float: width of the ellipse by default
///  d 	float: height of the ellipse by default
///  start 	float: angle to start the arc, specified in radians
///  stop 	float: angle to stop the arc, specified in radians
void ellipse(float a,float  b,float  c,float  d)
{
    int x1=a;
    int y1=b;
    int A=c/2;
    int B=d/2;
    if(A==0) A=1;
    if(B==0) B=1;

    if(filled)
        fill_ellipse_d(x1,y1,A,B);

    if(get_line_width()>0 && A>1 && B>1)
        ellipse_d(x1,y1,A,B);
}

void arc(float a,float  b,float  c,float  d,float  start,float  stop)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void arc(float a,float  b,float  c,float  d,float  start,float  stop,int  mode)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

/// Parameters	mode 	int: either CENTER, RADIUS, CORNER, or CORNERS
void ellipseMode(int mode)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}
/*
void text(char c, float x,float y)
{
    print_d(x,y,"%c",c);
}

void text(const char* str,float x,float y)
{
    print_d(x,y,"%s",str);
}

void text(char chars[],int start,int stop,float x,float y)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void text(const char* str,float x1,float y1,float x2,float y2)
{
    print_d(x1,y1,"%s",str);
    std::cerr<<__FUNCTION__<<" - x2 & y2 ignored!"<<std::endl;
}

void text(float num,float x,float y)
{
     print_d(x,y,"%f",num);
}
*/
/// Extended graphix text()
void text(_string_param str,float x,float y)
{
    print_d(x,y-char_height('X'),"%s",str.c_str());
}

void text(_string_param str,float x1,float y1,float x2,float y2)
{
    print_d(x1,y1-char_height('X'),"%s",str.c_str());
    std::cerr<<__FUNCTION__<<" - x2 & y2 ignored!"<<std::endl;
}

//void text(const String& str,float x,float y);
//void text(const String& str,float x1,float y1,float x2,float y2);


void saveFrame(const String& filename)
{
    dump_screen(filename.c_str());
    if(filename.find_first_of('#')!=std::string::npos)
        std::cerr<<__FUNCTION__<<" - special meaning of # ignored!"<<std::endl;
}

void saveFrame(const std::string& filename)
{
    dump_screen(filename.c_str());
    if(filename.find_first_of('#')!=std::string::npos)
        std::cerr<<__FUNCTION__<<" - special meaning of # ignored!"<<std::endl;
}

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2020-09-02                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
