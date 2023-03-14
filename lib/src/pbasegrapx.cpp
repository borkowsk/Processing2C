/// \file
/// \brief
/// \author 'borkowsk'
/// \date 2022-11-21 (last modification)
/// \details
///     podstawy obsługi okienka pseudo-processingowego
///
/// \ingroup PROCESSING_compatibility
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
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
        if(d<0) //Processing can (?) handle that strange situation.
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
/// @todo NOT IGNORE CORNERS ROUNDING WHERE POSSIBLE.
void rect(float a,float  b,float  c,float  d,float r)
{
    rect(a,b,c,d);
    FIRST_TIME_ERRMESSAGE( " !!! 'r' parameter is ignored in Processing2C!" );
}

/// \param tl 	float: radius for top-left corner
/// \param tr 	float: radius for top-right corner
/// \param br 	float: radius for bottom-right corner
/// \param bl 	float: radius for bottom-left corner
/// @todo NOT IGNORE CORNERS WHERE POSSIBLE.
void rect(float a,float b,float c,float d,float tl,float tr,float br,float bl)
{
    rect(a,b,c,d);
    FIRST_TIME_ERRMESSAGE( " !!! 'tl','tr','br','bl' parameters are ignored in Processing2C!" );
}

/// \note Meaning of parameters depends on rectMode() but in mode CORNERS
///       this particular function behave stupid in Processing 3.x at least.
void square(float a,float  b,float extent)
{
    rect(a,b,extent,extent);
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

/// @details
///         A triangle is a plane created by connecting three points.
///         ---------------------------------------------------------
///
///         The first two arguments specify the first point, the middle two arguments specify the second point,
///         and the last two arguments specify the third point.
///
/// \param x1 float: x-coordinate of the first vertex
/// \param y1 float: y-coordinate of the first vertex
/// \param x2 float: x-coordinate of the second vertex
/// \param y2 float: y-coordinate of the second vertex
/// \param x3 float: y-coordinate of the second vertex
/// \param y3 float: x-coordinate of the third vertex
//  WARNING:    Type 'float' cannot be narrowed to 'ssh_coordinate' (aka 'int') in initializer list
//  Explicit conversion needed.
void triangle(float     x1,float     y1,float     x2,float     y2,float     x3,float     y3)
{
    /* tablica wierzchołków wielokąta */
    const ssh_point points[]={{(int)x1,(int)y1},{(int)x2,(int)y2},{(int)x3,(int)y3}};

    /* Wypełnia wielokąt przesunięty o "vx","vy" kolorem domyślnym */
    fill_poly_d(0,                                   /* pozioma składowa wektora przesunięcia */
                0,                                   /* pionowa składowa wektora przesunięcia */
                points, 3                         /* tablica punktów i jej długość */
    );

    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

/// \brief
/// \details
///         A quad is a quadrilateral, a four sided polygon.
///         ------------------------------------------------
///
///         It is similar to a rectangle, but the angles between its edges are not constrained to ninety degrees.
///         The first pair of parameters (x1,y1) sets the first vertex and the subsequent pairs should proceed
///         clockwise or counter-clockwise around the defined shape.
///
/// \param x1 float: x-coordinate of the first corner
/// \param y1 float: y-coordinate of the first corner
/// \param x2 float: x-coordinate of the second corner
/// \param y2 float: y-coordinate of the second corner
/// \param x3 float: y-coordinate of the second corner
/// \param y3 float: x-coordinate of the third corner
/// \param x4 float: x-coordinate of the fourth corner
/// \param y4 float: y-coordinate of the fourth corner
//  WARNING:    Type 'float' cannot be narrowed to 'ssh_coordinate' (aka 'int') in initializer list
//  Explicit conversion needed.
void quad( float  x1,float y1,float x2, float y2,float x3,float y3,float x4,float y4)
{
    /* tablica wierzchołków wielokąta */
    const ssh_point points[]={{(int)x1,(int)y1},{(int)x2,(int)y2},
                              {(int)x3,(int)y3},{(int)x4,(int)y4}};

    /* Wypełnia wielokąt przesunięty o "vx","vy" kolorem domyślnym */
    fill_poly_d(0,                                   /* pozioma składowa wektora przesunięcia */
                0,                                   /* pionowa składowa wektora przesunięcia */
                points, 4                         /* tablica punktów i jej długość */
    );
    FIRST_TIME_ERRMESSAGE( " not inline called" );
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

///  \details Functions for driving elliptical arc.
///           =====================================
///  Draws an arc to the screen. Arcs are drawn along the outer edge of an ellipse defined by the a, b, c,
///  and d parameters. The origin of the arc's ellipse may be changed with the ellipseMode() function.
///  Use the start and stop parameters to specify the angles (in radians) at which to draw the arc.
///  The start/stop values must be in clockwise order.
///
///  There are three ways to draw an arc; the rendering technique used is defined by the optional seventh parameter.
///  The three options, depicted in the above examples, are PIE, OPEN, and CHORD. The default mode is the OPEN stroke with a PIE fill.
///
///  In some cases, the arc() function isn't accurate enough for smooth drawing. For example, the shape may jitter
///  on screen when rotating slowly. If you're having an issue with how arcs are rendered, you'll need to draw the
///  arc yourself with `beginShape()` - `endShape()` or a `PShape`.
///
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
    // FIRST_TIME_ERRMESSAGE( " not inline called" );
}

/// \details Simplified circle.
/// \todo Test, what about ellipse mode?!!!
/// \param x
/// \param y
/// \param r
void circle(float x,float y,float r)
{
    fill_circle_d((ssh_coordinate)x,(ssh_coordinate)y,(ssh_natural)r); //ssh_coordinate & ssh_natural
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

/// Extended graphics text() & Attributes
int _TEXT_HORIZONTAL_AL=LEFT;
int _TEXT_VERTICAL_AL=BOTTOM;

/// Sets the current alignment for drawing text. The parameters are LEFT, CENTER, or RIGHT for horizontal
void textAlign(int hor)
{
    _TEXT_HORIZONTAL_AL=hor;
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

/// and TOP, BOTTOM, CENTER, or BASELINE for vertical
void textAlign(int hor,int ver)
{
    _TEXT_HORIZONTAL_AL=hor;
    _TEXT_VERTICAL_AL=ver;
    FIRST_TIME_ERRMESSAGE( " not inline called" );
}

/// Calculates and returns the width of any character or text string.
float textWidth(_string_param str)
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
/* ******************************************************************
 *               PROCESSING2C  version 2023                         *
 ********************************************************************
 *           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 *
 *            W O J C I E C H   B O R K O W S K I                   *
 *          Robert Zajonc Institute for Social Studies,             *
 *                     UNIVERSITY OF WARSAW                         *
 *   (Instytut Studiów Społecznych Uniwersytetu Warszawskiego)      *
 *    WWW: http://iss.uw.edu.pl/en/ ; https://en.uw.edu.pl/         *
 *    RG : https://www.researchgate.net/profile/Wojciech-Borkowski  *
 *    GITHUB: https://github.com/borkowsk                           *
 *                                                                  *
 *                               (Don't change or remove this note) *
 ********************************************************************/
