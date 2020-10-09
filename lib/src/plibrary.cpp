// most commonly used library functions
#include "processing_window.hpp"
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include <iostream>

namespace Processing
{

/// Simple functions

void  randomSeed(int seed)
{
    srand((unsigned)seed);
}

static double _denominator=RAND_MAX+1.0;
double random(double low,double hig)
{
    double tmp=low + (rand()/_denominator) * (hig-low);  //???
    if(tmp==hig)
            std::cout<<__FUNCTION__<<" - unexpected value "<<tmp<<std::endl;
    return tmp;
}

//inline float random(double hig){return random(0,hig); }

/// Parameters:
/// value 	float: the incoming value to be converted
/// start1 	float: lower bound of the value's current range
/// stop1 	float: upper bound of the value's current range
/// start2 	float: lower bound of the value's target range
/// stop2 	float: upper bound of the value's target range
float map(float s,float a1,float a2,float b1,float b2)//float value,float start1,float stop1,float start2,float stop2)
{
    return b1 + (s-a1)*(b2-b1)/(a2-a1);//https://rosettacode.org/wiki/Map_range#C
}

double map(double s,double a1,double a2,double b1,double b2)
{
    return b1 + (s-a1)*(b2-b1)/(a2-a1);//https://rosettacode.org/wiki/Map_range#C
}

/// Parameters:
/// value 	float: the incoming value to be converted
/// start 	float: lower bound of the value's current range
/// stop 	float: upper bound of the value's current range
float norm(float value,float start,float stop)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

/// Parameters:
/// start 	float: first value
/// stop 	float: second value
/// amt 	float: float between 0.0 and 1.0
/// float lerp(float start,float stop,float amt)
float lerp(float v0, float v1, float t) // Precise method, which guarantees v = v1 when t = 1.
{                                       // https://en.wikipedia.org/wiki/Linear_interpolation
  return (1 - t) * v0 + t * v1;
}

void saveFrame()
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
}

void saveFrame(const char* filename)
{
    std::cerr<<__FUNCTION__<<" not implemented!"<<std::endl;
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
