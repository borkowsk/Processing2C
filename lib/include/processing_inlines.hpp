// processing_inlines.hpp
#pragma once
#ifndef PROCESSING_INLINES_H
#define PROCESSING_INLINES_H
#include "SYMSHELL/symshell.h"
#include <cmath>
//using namespace std::math;
///
/// ???
#define OPTINLINE inline
namespace Processing
{
extern bool _filled;//=true;
extern int _LINE_WIDTH;//=1;

inline void strokeWeight(float Weight)
{
    line_width(_LINE_WIDTH=(int)Weight);
}

inline void noStroke()
{
    //line_width(0);//??? TODO?
    _LINE_WIDTH=0;
}

inline void stroke(float Gray)
{
    int S=(int)Gray;
    set_pen_rgb(S,S,S,_LINE_WIDTH,1 /*style*/);
}

inline void stroke(float Red,float Green,float Blue)
{
    set_pen_rgb((int)Red,(int)Green,(int)Blue,_LINE_WIDTH,1 /*style*/);
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

inline void point(float x,float y)
{
    plot_d((int)x,(int)y);
}

inline void line(float  x1,float  y1,float  x2,float  y2)
{
    line_d((int)x1,(int)y1,(int)x2,(int)y2);
}

inline void rect(float a,float  b,float  c,float  d)
{
    int x1=a;
    int y1=b;
    int x2=a+c;
    int y2=b+d;

    if(_filled)
        fill_rect_d(x1,y1,x2,y2);

    if(get_line_width()>0)
    {
        line_d(x1,y1,x1,y2);
        line_d(x1,y1,x2,y1);
    }
}

inline void ellipse(float a,float  b,float  c,float  d)
{
    int x1=a;
    int y1=b;
    int A=c/2;
    int B=d/2;
    if(A==0) A=1;
    if(B==0) B=1;

    if(_filled)
        fill_ellipse_d(x1,y1,A,B);

    if(get_line_width()>0 && A>1 && B>1)
        ellipse_d(x1,y1,A,B);
}

/// map & lerp - nie graficzne ale też czesto używane
//////////////////////////////////////////////////////////////
inline float map(float s,float a1,float a2,float b1,float b2)//float value,float start1,float stop1,float start2,float stop2)
{
    return b1 + (s-a1)*(b2-b1)/(a2-a1);//https://rosettacode.org/wiki/Map_range#C
}

inline float lerp(float v0, float v1, float t) // Precise method, which guarantees v = v1 when t = 1.
{                                       // https://en.wikipedia.org/wiki/Linear_interpolation
  return (1 - t) * v0 + t * v1;
}


}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2020-08-19                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiow Spolecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
#endif
