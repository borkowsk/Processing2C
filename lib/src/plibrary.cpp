/// \file ***.cpp
/// \brief most commonly used library functions
/// \author 'borkowsk'
/// \date 2023-03-21 (last modification)
/// \details
///             ...
///
/// \ingroup PROCESSING_compatibility
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////

#include "processing_consts.hpp"
#include "processing_templates.hpp"
#include "processing_window.hpp"
#include "processing_library.hpp"

#include <iostream>

namespace Processing
{

// Simple functions
// /////////////////

/// @details Uses standard C `srand()`!
void  randomSeed(int seed)
{
    srand((unsigned)seed);
}

static double _denominator=RAND_MAX+1.0; ///< Denominator for random function (STATIC, so invisible for linker)

/// @details Uses standard C `rand()`!
double random(double low,double hig)
{
    double tmp=low + (rand()/_denominator) * (hig-low);  //???TODO BETTER
    if( tmp<low )
    {
            std::cerr<<__FUNCTION__<<"("<<low<<","<<hig<<") - unexpected value "<<tmp<<std::endl;
            return low;
    }
    if( hig<=tmp )
    {
            std::cerr<<__FUNCTION__<<"("<<low<<","<<hig<<") - unexpected value "<<tmp<<std::endl;
            return hig-0.00000000001;//????TODO BETTER
    }
    return tmp;
}

//inline float random(double hig){return random(0,hig); }

/// \details Implementation of proportions mapping
/// \param value 	float: the incoming value to be converted
/// \param start1 	float: lower bound of the value's current range
/// \param stop1 	float: upper bound of the value's current range
/// \param start2 	float: lower bound of the value's target range
/// \param stop2 	float: upper bound of the value's target range
float map(float s,float a1,float a2,float b1,float b2) //float value,float start1,float stop1,float start2,float stop2)
{
    return b1 + (s-a1)*(b2-b1)/(a2-a1);//https://rosettacode.org/wiki/Map_range#C
}

/// \details Implementation of proportions mapping
/// \param value 	double: the incoming value to be converted
/// \param start1 	double: lower bound of the value's current range
/// \param stop1 	double: upper bound of the value's current range
/// \param start2 	double: lower bound of the value's target range
/// \param stop2 	double: upper bound of the value's target range
double map(double s,double a1,double a2,double b1,double b2)
{
    return b1 + (s-a1)*(b2-b1)/(a2-a1);//https://rosettacode.org/wiki/Map_range#C
}

/// Parameters:
/// \param value 	float: the incoming value to be converted
/// \param start 	float: lower bound of the value's current range
/// \param stop 	float: upper bound of the value's current range
float norm(float value,float start,float stop)
{
    return (value-start)/(stop-start);
}

/// Parameters:
/// \param start 	float: first value
/// \param stop 	float: second value
/// \param amt 	    float: float between 0.0 and 1.0
/// float lerp(float start,float stop,float amt)
///
float lerp(float v0, float v1, float t) // Precise method, which guarantees v = v1 when t = 1.
{                                       // https://en.wikipedia.org/wiki/Linear_interpolation
  return (1 - t) * v0 + t * v1;
}


/// \details Recalculating angles
/// \param degrees 	float: degree value to convert to radians
/// \return	float
float radians(float degrees)
{
    const double mult = M_PI/180;
    return degrees * mult;
    //return ( degrees * M_PI ) / 180 ;
}

/// \details Recalculating angles
/// \param radians 	float: radian value to convert to degrees
/// \return	float
float degrees(float radians)
{
    const double mult = 180/M_PI;
    return radians * mult;
    //return ( radians * 180 ) / M_PI ;
}


}//END of namespace Processing
/* ******************************************************************
 *               PROCESSING2C  version 2022                         *
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


