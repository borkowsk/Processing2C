/// \file processing_inlines.hpp
/// \brief Procedury graficzne w wersji inline, dla przyśpieszenia wykonania
/// \author 'borkowsk'
/// \ingroup graphics
///
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
#pragma once
#ifndef PROCESSING_INLINES_H
#define PROCESSING_INLINES_H
#include "symshell.h"
#include <cmath>
//using namespace std::math;

/// ???
#define OPTINLINE inline
///

///\namespace Processing \brief P2C compatibility libraries
namespace Processing
{
extern bool _filled;//=true;
extern int _LINE_WIDTH;//=1;
extern int _RECT_MODE;//=CORNER; /// either CENTER, RADIUS, CORNER, or CORNERS
extern int _ELLIPSE_MODE;//=CENTER; /// either CENTER, RADIUS, CORNER, or CORNERS

inline void strokeWeight(float Weight)
{
    _LINE_WIDTH=(int)Weight;
    line_width(_LINE_WIDTH);
}

inline void noStroke()
{
    _LINE_WIDTH=0;
    line_width(0);//??? TODO TEST?
}

inline void stroke(float Gray)
{
    if(_LINE_WIDTH<0) _LINE_WIDTH=1;
    int S=(int)Gray;
    set_pen_rgb(S,S,S,_LINE_WIDTH,1 /*style*/);
}

inline void stroke(float Red,float Green,float Blue)
{
    if(_LINE_WIDTH<0) _LINE_WIDTH=1;
    set_pen_rgb((int)Red,(int)Green,(int)Blue,_LINE_WIDTH,1 /*style*/);
}

inline void stroke(float Gray,float Alpha)
{
    if(_LINE_WIDTH<0) _LINE_WIDTH=1;
    int S=(int)Gray;
    set_pen_rgba(S,S,S,(int)Alpha,
                _LINE_WIDTH,1 /*style*/);
}

inline void noFill()
{
    _filled=false;
}

inline void fill(float Gray)
{
    int S=(int)Gray;
    set_brush_rgb(S,S,S);
    _filled=true;
}

inline void fill(float Red,float Green,float Blue)
{
    set_brush_rgb((int)Red,(int)Green,(int)Blue);
    _filled=true;
}

inline void fill(float Red,float Green,float Blue,float Alpha)
{
    set_brush_rgba((int)Red,(int)Green,(int)Blue,(int)Alpha);
    _filled=true;
}

inline void point(float x,float y)
{
    plot_d((int)x,(int)y);
}

inline void line(float  x1,float  y1,float  x2,float  y2)
{
    line_d((int)x1,(int)y1,(int)x2,(int)y2);
}

inline void rectMode(int mode)/// Parameter: mode 	int: either CORNER, CORNERS, CENTER, or RADIUS
{
    _RECT_MODE=mode;
}

inline void rect(float a,float  b,float  c,float  d)
{
    int x1,y1,x2,y2;
    switch(_RECT_MODE){
    case CORNERS:x1=a; y1=b; x2=c; y2=d;break;
    case CENTER:x1=a-c/2;x2=a+c/2;y1=b-d/2;y2=b+d/2;break;
    case RADIUS:x1=a-c;x2=a+c;y1=b-d;y2=b+d;break;
    default:
    case CORNER:
        if(d<0)//Procesing can handle that strange situation
        {x1=a; y1=b+d; x2=a+c; y2=b;}
        else
        {x1=a; y1=b; x2=a+c; y2=b+d;}
        break;
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
}

inline void ellipse(float a,float  b,float  c,float  d)
{
    int x1,y1,A,B;
    switch(_ELLIPSE_MODE){
    case RADIUS:x1=a; A=c; y1=b; B=d;break;
    case CORNERS:A=abs(c-a)/2;x1=a+A; B=abs(d-b)/2;y1=b+B;break;
    case CORNER:
         A=c/2;B=d/2;x1=a+A; y1=b+B;break;
    default:
    case CENTER:x1=a; A=c/2; y1=b; B=d/2;break;
    }

    if(_filled)
        fill_ellipse_d(x1,y1,A,B);

    if(get_line_width()>0 && A>1 && B>1)//TODO - eliminate it!!!
        ellipse_d(x1,y1,A,B);
}

/// map & lerp - nie graficzne, ale też często używane z grafiką
/// \ingroup math

/// \fn map
/// \param s
/// \param a1
/// \param a2
/// \param b1
/// \param b2
/// \return float
/// \see https://rosettacode.org/wiki/Map_range#C
/// \n TODO TEST & IMPROVE?
inline float map(float s,float a1,float a2,float b1,float b2)//float value,float start1,float stop1,float start2,float stop2)
{
    return b1 + (s-a1)*(b2-b1)/(a2-a1);
}

/// \fn lerp
/// \param v0
/// \param v1
/// \param t
/// \return float
/// \see \a https://en.wikipedia.org/wiki/Linear_interpolation
/// \n TODO TEST & IMPROVE?
inline float lerp(float v0, float v1, float t) // Precise method, which guarantees v = v1 when t = 1.
{
  return (1 - t) * v0 + t * v1;
}


}//END of namespace Processing
/* ****************************************************************** */
/*               PROCESSING2C  version 2021-12-23                     */
/* ****************************************************************** */
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                   */
/*            W O J C I E C H   B O R K O W S K I                     */
/*    Instytut Studiów Społecznych Uniwersytetu Warszawskiego         */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI    */
/*    RG : https://www.researchgate.net/profile/Wojciech-Borkowski    */
/*    GITHUB: https://github.com/borkowsk                             */
/*                                                                    */
/*                                 (Don't change or remove this note) */
/* ****************************************************************** */
#endif
