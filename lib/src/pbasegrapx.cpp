/// \file ***.cpp
/// \brief
/// \author 'borkowsk'
///
/// podstawy obsługi okienka pseudo-processingowego
#include "processing_consts.hpp"
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include "symshell.h"
#include "_impl_errors.h"

namespace Processing
{

void noSmooth()
{
    FIRST_TIME_ERRMESSAGE( " is default and only possible for X11!" );
}

void smooth()
{
    FIRST_TIME_ERRMESSAGE( " not available under X11! Sorry." );
}

void strokeCap(int cap)/// Parameters	cap 	int: either SQUARE, PROJECT, or ROUND
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}

void strokeJoin(int join)/// Parameters	join 	int: either MITER, BEVEL, ROUND
{
    FIRST_TIME_ERRMESSAGE( " not implemented!" );
}

int _LINE_WIDTH=1;

void strokeWeight(float Weight)/// Parameters	weight 	float: the weight (in pixels) of the stroke
{
    line_width(_LINE_WIDTH=(int)Weight);
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

void stroke(float Gray)
{
    if(_LINE_WIDTH<0) _LINE_WIDTH=1;
    int S=(int)Gray;
    set_pen_rgb(S,S,S,_LINE_WIDTH,1 /*style*/);
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

void stroke(float Gray,float Alpha)
{
    if(_LINE_WIDTH<0) _LINE_WIDTH=1;
    int S=(int)Gray;
    set_pen_rgba(S,S,S,(int)Alpha,
                _LINE_WIDTH,1 /*style*/);
    FIRST_TIME_ERRMESSAGE( "!!! Alpha not tested!" );
}

void stroke(float Red,float Green,float Blue)
{
    if(_LINE_WIDTH<0) _LINE_WIDTH=1;
    set_pen_rgb((int)Red,(int)Green,(int)Blue,_LINE_WIDTH,1 /*style*/);
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

void stroke(float Red,float Green,float Blue,float Alpha)
{
    set_pen_rgba((int)Red,(int)Green,(int)Blue,(int)Alpha,
                 _LINE_WIDTH,1 /*style*/);
    FIRST_TIME_ERRMESSAGE( "!!! Alpha not tested!" );
}

//TEMPORARY IMPLEMENTATION OF stroke(color)
void stroke(const color& col)//Until update of symshell.h (TODO!)
{
    if(_LINE_WIDTH<0) _LINE_WIDTH=1;
    stroke(red(col),green(col),blue(col));
    //FIRST_TIME_ERRMESSAGE( ' '<<std::hex<<col.val );
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

void noStroke()
{
    line_width(0);//??? TODO?
    _LINE_WIDTH=0;
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

bool _filled=true;//TODO _FILLED !!!???

void fill(float Gray)
{
    int S=(int)Gray;
    set_brush_rgb(S,S,S);
    _filled=true;
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

void fill(float Gray,float Alpha)
{
    int S=(int)Gray;
    set_brush_rgba(S,S,S,(int)Alpha);
    _filled=true;
    FIRST_TIME_ERRMESSAGE( "!!! Alpha not tested!" );
}

void fill(float Red,float Green,float Blue)
{
    set_brush_rgb((int)Red,(int)Green,(int)Blue);
    _filled=true;
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

void fill(float Red,float Green,float Blue,float Alpha)
{
    set_brush_rgba((int)Red,(int)Green,(int)Blue,(int)Alpha);
    _filled=true;
    FIRST_TIME_ERRMESSAGE( "!!! Alpha not tested!" );
}

//TEMPORARY IMPLEMENTATION OF fill(color)
void fill(const color& col)//Until update of symshell.h (TODO!)
{
    fill(red(col),green(col),blue(col));
}

void noFill()
{
    _filled=false;
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

void point(float x,float y)
{
    plot_d((int)x,(int)y);
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

void line(float  x1,float  y1,float  x2,float  y2)
{
    line_d((int)x1,(int)y1,(int)x2,(int)y2);
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

/// Set driving mode for rects. Either CENTER, RADIUS, CORNER, or CORNERS
int _RECT_MODE=CORNER;

/// Set driving mode for rects
/// Parameter: mode 	int: either CORNER, CORNERS, CENTER, or RADIUS
void rectMode(int mode)
{
    _RECT_MODE=mode;
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

/// Driving a filled (by default) rectangle
/// \param a : meaning depend of mode
/// \param b : meaning depend of mode
/// \param c : meaning depend of mode
/// \param d : meaning depend of mode
void rect(float a,float  b,float  c,float  d)
{
    int x1,y1,x2,y2;
    switch(_RECT_MODE){
    case CORNERS:
        x1=a; y1=b; x2=c; y2=d;
        break;
    case CENTER:
        x1=a-c/2;x2=a+c/2;y1=b-d/2;y2=b+d/2;
        break;
    case RADIUS:
        x1=a-c;x2=a+c;y1=b-d;y2=b+d;
        break;
    default: ALWAYS_ERRMESSAGE( " - undefined rect mode!" );
    case CORNER:
        if(d<0)//Procesing can handle that strange situation
        {x1=a; y1=b+d; x2=a+c; y2=b;}
        else
        {x1=a; y1=b; x2=a+c; y2=b+d;}
        break;
    }

    if(_filled)
        fill_rect_d(x1,y1,x2,y2);

    if(get_line_width()>0) //TODO - eliminate it!!!???
    {
        ::line_d(x1,y1,x1,y2);
        ::line_d(x1,y1,x2,y1);
        ::line_d(x2,y1,x2,y2);
        ::line_d(x1,y2,x2,y2);
    }

    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

/// Driving a filled (by default) rectangle, witch rounded corners
/// \param a  : meaning depend of mode
/// \param b  : meaning depend of mode
/// \param c  : meaning depend of mode
/// \param d  : meaning depend of mode
/// \param r : radius for rounding corners (CURRENTLY IGNORED)
void rect(float a,float  b,float  c,float  d,float r)
{
    rect(a,b,c,d);
    FIRST_TIME_ERRMESSAGE( " !!! 'r' parameter is ignored here!" );
}

/// Current mode for driving ellipses. Either CENTER, RADIUS, CORNER, or CORNERS
int  _ELLIPSE_MODE=CENTER;

/// Set driving mode for ellipses and elliptical arcs
/// \param	mode 	int: either CENTER, RADIUS, CORNER, or CORNERS
void ellipseMode(int mode)
{
    _ELLIPSE_MODE=mode;
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

///  Functions for driving ellipse
///  \param a 	float: x-coordinate of the ellipse
///  \param b 	float: y-coordinate of the ellipse
///  \param c 	float: width of the ellipse by default
///  \param d 	float: height of the ellipse by default
void ellipse(float a,float  b,float  c,float  d)
{
    int x1,y1,A,B;
    switch(_ELLIPSE_MODE){
    case RADIUS:x1=a; A=c; y1=b; B=d;break;
    case CORNERS:A=abs(c-a)/2;x1=a+A; B=abs(d-b)/2;y1=b+B;break;
    case CORNER:
         A=c/2;B=d/2;x1=a+A; y1=b+B;break;
    default: ALWAYS_ERRMESSAGE( " - undefined ellipse mode!" );
    case CENTER:x1=a; A=c/2; y1=b; B=d/2;break;
    }

    if(_filled)
        fill_ellipse_d(x1,y1,A,B);

    if(get_line_width()>0 && A>1 && B>1)//TODO - eliminate it!!!
        ellipse_d(x1,y1,A,B);

    FIRST_TIME_ERRMESSAGE( "!!! not inline called" );
}

///  Functions for driving elliptical arc
///  \param a 	float: x-coordinate of the ellipse
///  \param b 	float: y-coordinate of the ellipse
///  \param c 	float: width of the ellipse by default
///  \param d 	float: height of the ellipse by default
///  \param start 	float: angle to start the arc, specified in radians
///  \param stop 	float: angle to stop the arc, specified in radians
///  \param mode arc connecting mode (STILL IGNORED?)
void arc(float a,float  b,float  c,float  d,float  start,float  stop,int  mode/*=0*/)
{
    int x1,y1,A,B;
    switch(_ELLIPSE_MODE){
    case RADIUS:x1=a; A=c; y1=b; B=d;break;
    case CORNERS:A=abs(c-a)/2;x1=a+A; B=abs(d-b)/2;y1=b+B;break;
    case CORNER:
         A=c/2;B=d/2;x1=a+A; y1=b+B;break;
    default: ALWAYS_ERRMESSAGE( " - undefined ellipse mode!" );
    case CENTER:x1=a; A=c/2; y1=b; B=d/2;break;
    }

    if(_filled)
    {
        fill_earc_d(x1,y1,A,B,start,stop,mode & 0x1);
    }

    if(get_line_width()>0 && A>1 && B>1)//TODO - eliminate it!!!
        earc_d(x1,y1,A,B,start,stop);

    if(mode!=0)
        FIRST_TIME_ERRMESSAGE( " mode ignored!!" );
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

/// Extended graphics text() & Attributes
int _TEXT_HORIZONTAL_AL=LEFT;
int _TEXT_VERTICAL_AL=BOTTOM;

void textAlign(int hor)
// Sets the current alignment for drawing text. The parameters are LEFT, CENTER, or RIGHT for horizontal
{
    _TEXT_HORIZONTAL_AL=hor;
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

void textAlign(int hor,int ver)
// and TOP, BOTTOM, CENTER, or BASELINE for vertical
{
    _TEXT_HORIZONTAL_AL=hor;
    _TEXT_VERTICAL_AL=ver;
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

float textWidth(_string_param str)
// Calculates and returns the width of any character or text string.
{
    FIRST_TIME_ERRMESSAGE( " not inline called" );
    return string_width(str.c_str());
}

void text(_string_param str,float x,float y)
{
    switch(_TEXT_HORIZONTAL_AL){
    default:ALWAYS_ERRMESSAGE( " - invalid horizontal alignment!" );
    case LEFT:break;
    case CENTER:x-=string_width(str.c_str())/2;break;
    case RIGHT:x-=string_width(str.c_str());break;
    }
    switch(_TEXT_VERTICAL_AL){
    default:ALWAYS_ERRMESSAGE( " - invalid vertical alignment!" );
    case BASELINE:
    case TOP: break;
    case BOTTOM:y-=char_height('X');break;
    case CENTER: y-=char_height('X')/2;break;
    }
    print_d(x,y,"%s",str.c_str());//Kolor wypełnienia nie działa! TODO!
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

void text(_string_param str,float x1,float y1,float x2,float y2)
{
    print_d(x1,y1-char_height('X'),"%s",str.c_str());//Kolor wypełnienia nie działa! TODO!
    FIRST_TIME_ERRMESSAGE( " - x2 & y2 ignored!" );//ale w SYMSHELL X11
}

void save(_string_param filename)
{
    dump_screen(filename.c_str());
}

void saveFrame(_string_param filename)
{
    dump_screen(filename.c_str());
    if(filename.find_first_of('#')!=std::string::npos)
        FIRST_TIME_ERRMESSAGE( " - special meaning of # ignored!" );
}


void saveFrame()//PROCESSING: If saveFrame() is used without parameters, it will save files as screen-0000.tif, screen-0001.tif,
{
    extern String nf(double num,int digits);//Tylko tu potrzeba, szkoda wołać cały nagłówek
    String name="screen-";
    name+=nf(frameCount,4);
    dump_screen(name.c_str());
    FIRST_TIME_ERRMESSAGE( ": files numbering not implemented!" );
}

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2021-12-17                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiów Społecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
