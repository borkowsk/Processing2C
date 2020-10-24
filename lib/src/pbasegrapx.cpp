/// podstawy obsługo okienka pseudo-processingowego
#include "processing_consts.hpp"
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

int _LINE_WIDTH=1;

void strokeWeight(float Weight)/// Parameters	weight 	float: the weight (in pixels) of the stroke
{
    line_width(_LINE_WIDTH=(int)Weight);
}

void stroke(float Gray)
{
    int S=(int)Gray;
    set_pen_rgb(S,S,S,_LINE_WIDTH,1 /*style*/);
}

void stroke(float Gray,float Alpha)
{
    int S=(int)Gray;
    set_pen_rgb(S,S,S,_LINE_WIDTH,1 /*style*/);
    std::cerr<<__FUNCTION__<<" - Alpha ignored!"<<std::endl;
}

void stroke(float Red,float Green,float Blue)
{
    set_pen_rgb((int)Red,(int)Green,(int)Blue,_LINE_WIDTH,1 /*style*/);
}

void stroke(float Red,float Green,float Blue,float Alpha)
{
    set_pen_rgb((int)Red,(int)Green,(int)Blue,_LINE_WIDTH,1 /*style*/);
    std::cerr<<__FUNCTION__<<" - Alpha ignored!"<<std::endl;
}

//TEMPORARY IMPLEMENTATION OF stroke(color)
void stroke(const color& col)//Until update of symshell.h (TODO!)
{
    //std::cerr<<__FUNCTION__<<' '<<std::hex<<col.val<<std::endl;
    stroke(red(col),green(col),blue(col));
}

void noStroke()
{
    line_width(0);//??? TODO?
    _LINE_WIDTH=0;
    std::cerr<<__FUNCTION__<<" - not inline called"<<std::endl;
}

bool _filled=true;//TODO _FILLED !!!

void fill(float Gray)
{
    int S=(int)Gray;
    set_brush_rgb(S,S,S);
    _filled=true;
}

void fill(float Gray,float Alpha)
{
    int S=(int)Gray;
    set_brush_rgb(S,S,S);
    _filled=true;
    std::cerr<<__FUNCTION__<<" - Alpha ignored!"<<std::endl;
}

void fill(float Red,float Green,float Blue)
{
    set_brush_rgb((int)Red,(int)Green,(int)Blue);
    _filled=true;
}

void fill(float Red,float Green,float Blue,float Alpha)
{
    set_brush_rgb((int)Red,(int)Green,(int)Blue);
    _filled=true;
    std::cerr<<__FUNCTION__<<" - Alpha ignored!"<<std::endl;
}

//TEMPORARY IMPLEMENTATION OF fill(color)
void fill(const color& col)//Until update of symshell.h (TODO!)
{
    fill(red(col),green(col),blue(col));
}

void noFill()
{
    _filled=false;
    std::cerr<<__FUNCTION__<<" - not inline called"<<std::endl;
}

void point(float x,float y)
{
    plot_d((int)x,(int)y);
}

void line(float  x1,float  y1,float  x2,float  y2)
{
    line_d((int)x1,(int)y1,(int)x2,(int)y2);
}


int _RECT_MODE=CORNER; /// either CENTER, RADIUS, CORNER, or CORNERS
void rect(float a,float  b,float  c,float  d)
{
    int x1,y1,x2,y2;
    switch(_RECT_MODE){
    case CORNERS:x1=a; y1=b; x2=c; y2=d;break;
    case CENTER:x1=a-c/2;x2=a+c/2;y1=b-d/2;y2=b+d/2;break;
    case RADIUS:x1=a-c;x2=a+c;y1=b-d;y2=b+d;break;
    default: std::cerr<<__FUNCTION__<<" - undefined rect mode!"<<std::endl;
    case CORNER:
        x1=a; y1=b; x2=a+c; y2=b+d;break;
    }

    if(_filled)
        fill_rect_d(x1,y1,x2,y2);

    if(get_line_width()>0) //TODO - eliminate it!!!
    {
        ::line_d(x1,y1,x1,y2);
        ::line_d(x1,y1,x2,y1);
        ::line_d(x2,y1,x2,y2);
        ::line_d(x1,y2,x2,y2);
    }

    std::cerr<<__FUNCTION__<<" - not inline called"<<std::endl;
}

void rect(float a,float  b,float  c,float  d,float r)
{
    rect(a,b,c,d);
    std::cerr<<__FUNCTION__<<" - r parameter is ignored!"<<std::endl;
}

/// Parameter: mode 	int: either CORNER, CORNERS, CENTER, or RADIUS
void rectMode(int mode)
{
    _RECT_MODE=mode;
    //std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

/// Parameters
///  a 	float: x-coordinate of the ellipse
///  b 	float: y-coordinate of the ellipse
///  c 	float: width of the ellipse by default
///  d 	float: height of the ellipse by default
///  start 	float: angle to start the arc, specified in radians
///  stop 	float: angle to stop the arc, specified in radians
int  _ELLIPSE_MODE=CENTER; /// either CENTER, RADIUS, CORNER, or CORNERS
void ellipse(float a,float  b,float  c,float  d)
{
    int x1,y1,A,B;
    switch(_ELLIPSE_MODE){
    case RADIUS:x1=a; A=c; y1=b; B=d;break;
    case CORNERS:A=abs(c-a)/2;x1=a+A; B=abs(d-b)/2;y1=b+B;break;
    case CORNER:
         A=c/2;B=d/2;x1=a+A; y1=b+B;break;
    default: std::cerr<<__FUNCTION__<<" - undefined ellipse mode!"<<std::endl;
    case CENTER:x1=a; A=c/2; y1=b; B=d/2;break;
    }

    if(_filled)
        fill_ellipse_d(x1,y1,A,B);

    if(get_line_width()>0 && A>1 && B>1)//TODO - eliminate it!!!
        ellipse_d(x1,y1,A,B);

    std::cerr<<__FUNCTION__<<" - not inline called"<<std::endl;
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
    _ELLIPSE_MODE=mode;
    //std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

/// Extended graphix text() & Attributes
int _TEXT_HORIZONTAL_AL=LEFT;
int _TEXT_VERTICAL_AL=BOTTOM;

void textAlign(int hor)
// Sets the current alignment for drawing text. The parameters are LEFT, CENTER, or RIGHT for horizontal
{
    _TEXT_HORIZONTAL_AL=hor;
}

void textAlign(int hor,int ver)
// and TOP, BOTTOM, CENTER, or BASELINE for vertical
{
    _TEXT_HORIZONTAL_AL=hor;
    _TEXT_VERTICAL_AL=ver;
}

void textLeading(int)
// Sets the spacing between lines of text in units of pixels.
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void textMode(int)
// Sets the way text draws to the screen, either as texture maps or as vector geometry (MODEL or SHAPE)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void textSize(int)
// Sets the current font size, measured in units of pixels.
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

float textWidth(_string_param str)
// Calculates and returns the width of any character or text string.
{
    return string_width(str.c_str());
}

void text(_string_param str,float x,float y)
{
    switch(_TEXT_HORIZONTAL_AL){
    default:std::cerr<<__FUNCTION__<<" - invalid horizontal alignment!"<<std::endl;
    case LEFT:break;
    case CENTER:x-=string_width(str.c_str())/2;break;
    case RIGHT:x-=string_width(str.c_str());break;
    }
    switch(_TEXT_VERTICAL_AL){
    default:std::cerr<<__FUNCTION__<<" - invalid vertical alignment!"<<std::endl;
    case BASELINE:
    case TOP: break;
    case BOTTOM:y-=char_height('X');break;
    case CENTER: y-=char_height('X')/2;break;
    }
    print_d(x,y,"%s",str.c_str());//Kolor wypełnienia nie działa! TODO!
}

void text(_string_param str,float x1,float y1,float x2,float y2)
{
    print_d(x1,y1-char_height('X'),"%s",str.c_str());//Kolor wypełnienia nie działa! TODO!
    std::cerr<<__FUNCTION__<<" - x2 & y2 ignored!"<<std::endl;//ale w SYMSHELL X11
}

void saveFrame(_string_param filename)
{
    dump_screen(filename.c_str());
    if(filename.find_first_of('#')!=std::string::npos)
        std::cerr<<__FUNCTION__<<" - special meaning of # ignored!"<<std::endl;
}

void save(_string_param filename)
{
    dump_screen(filename.c_str());
}

void beginShape()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void beginShape(int kind)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void endShape()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void endShape(int mode)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void vertex(float x,float y)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void vertex(float x,float y,float z)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void vertex(float v[])
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void vertex(float x,float y,float u,float v)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void vertex(float x,float y,float z,float u,float v)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}


}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2020-09-29                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/

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
