/** 
 * \brief Most commonly used library functions.
 * \file processing_library.hpp
 * \author borkowsk
 * \date 2023-03-17 (last modification)
 */
// //////////////////////////////////////////////////////////////////////
// This file is part of the Processing2C++ Library. See bottom lines.
// //////////////////////////////////////////////////////////////////////
#pragma once
#ifndef PROCESSING_LIBRARY_H
#define PROCESSING_LIBRARY_H

#include <cassert>
#include <vector>
#include <algorithm>

#include "processing_string.hpp"

///\namespace Processing \brief P2C compatibility libraries
namespace Processing
{
  // Simple functions:
  // /////////////////

  /// \brief Nonparametric, Processing like exit()
  /// \ingroup rtm
  void exit();

  /// \brief WHOLE PROGRAM PARAMETERS!!!
  /// \ingroup rtm
  extern sarray<String> args;

  /// String parsing
  /// The split() function breaks a String into pieces using a character or string as the delimiter.
  /// \param string : string to parse
  /// \param delim  : delimiter
  /// \return array of strings
  /// \ingroup strings
  sarray<String> split(_string_param string,_string_param delim);

  // text() & attributes:
  // ///////////////////////////////////////

  /// \brief Sets the current alignment for drawing text.
  /// \param h may be LEFT, CENTER, or RIGHT for horizontal
  /// \param v may be TOP, BOTTOM, CENTER, or BASELINE for vertical
  /// \ingroup drawing
  void textAlign(int h,int v);

  /// \brief Sets the current alignment for drawing text. The parameters are LEFT, CENTER, or RIGHT for horizontal
  /// \ingroup drawing
  void textAlign(int);

  /// \brief Sets the spacing between lines of text in units of pixels.
  /// \ingroup drawing
  void textLeading(int);

  /// \brief Sets the way text draws to the screen, either as texture maps or as vector geometry (MODEL or SHAPE)
  /// \ingroup drawing
  void textMode(int);

  /// \brief Sets the current font size, measured in units of pixels.
  /// \ingroup drawing
  void textSize(int);

  /// \brief Calculates and returns the width of any character or text string.
  /// \ingroup drawing
  float textWidth(_string_param str);

  /// \brief Print text on screen
  /// \ingroup strings
  void text(_string_param str,float x,float y);

  /// \brief Print text on screen TODO - IMPLEMENTATION!!!
  /// \ingroup strings
  void text(_string_param str,float x1,float y1,float x2,float y2);

  /// \brief Type for font handler
  /// \ingroup drawing
  typedef void* PFont; //ptr<???> TODO?

  /// Make font available for program - TODO - IMPLEMENTATION!!!
  /// \ingroup drawing
  PFont createFont(String fn,int s);

  /// \brief Use previously created font - TODO - IMPLEMENTATION!!!
  /// \ingroup drawing
  void textFont(PFont f);

  /// \note About Shapes
  /// ==================
  /// Using the beginShape() and endShape() functions allow creating more complex forms. beginShape() begins recording vertices for
  /// a shape and endShape() stops recording. The value of the kind parameter tells it which types of shapes to create from
  /// the provided vertices. With no mode specified, the shape can be any irregular polygon.
  /// kind int: Either POINTS, LINES, TRIANGLES, TRIANGLE_FAN, TRIANGLE_STRIP, QUADS, or QUAD_STRIP
  /// TODO - IMPLEMENTATION!!!
  const int CLOSE=1;

  /// \brief Using the beginShape() and endShape() functions allow creating more complex forms.
  /// TODO - IMPLEMENTATION!!!
  /// \ingroup drawing
  void beginShape();

  /// \brief Using the beginShape() and endShape() functions allow creating more complex forms.
  /// \param kind
  /// TODO - IMPLEMENTATION!!!
  /// \ingroup drawing
  void beginShape(int kind);

  /// \brief Using the beginShape() and endShape() functions allow creating more complex forms.
  /// TODO - IMPLEMENTATION!!!
  /// \ingroup drawing
  void endShape();

  /// Using the beginShape() and endShape() functions allow creating more complex forms.
  /// \param	mode 	int: use CLOSE to close the shape
  /// TODO - IMPLEMENTATION!!!
  /// \ingroup drawing
  void endShape(int mode);

  /// \brief vertex() is used to specify the vertex coordinates for points, lines, triangles, quads, and polygons.
  /// \note It is used exclusively within the beginShape() and endShape() functions.
  /// \param  x 	float: x-coordinate of the vertex
  /// \param  y 	float: y-coordinate of the vertex \ingroup drawing
  void vertex(float x,float y);
  
  /// \param  z 	float: z-coordinate of the vertex \ingroup drawing
  void vertex(float x,float y,float z);
  
  /// \param  v 	float[]: vertex parameters, as a float array of length VERTEX_FIELD_COUNT, TODO - IMPLEMENTATION!!!
  void vertex(float v[]);
  
  /// \param  u 	float: horizontal coordinate for the texture mapping
  /// \param  v 	float: vertical coordinate for the texture mapping \ingroup drawing
  void vertex(float x,float y,float u,float v);
  
  /// \param  z 	float: z-coordinate of the vertex  \ingroup drawing
  void vertex(float x,float y,float z,float u,float v);

  /// \note Generates random numbers:
  /// ===================================
  /// Each time the random() function is called, it returns an unexpected value within the specified range.
  /// If only one parameter is passed to the function, it will return a float between zero and the value of the high parameter.
  /// For example, random(5) returns values between 0 and 5 (starting at zero, and up to, but not including, 5).
  /// If two parameters are specified, the function will return a float with a value between the two values.
  /// For example, random(-5, 10.2) returns values starting at -5 and up to (but not including) 10.2.
  /// To convert a floating-point random number to an integer, use the int() function.

  /// \brief It produces an "unpredictable" value within the specified range.
  /// \param low
  /// \param hig
  /// \return random value from low..hig range
  /// \ingroup etc
  double random(double low,double hig);

  /// \brief It produces an "unpredictable" value within the specified range.
  /// \param hig
  /// \return random value from 0..hig range
  /// \ingroup etc
  inline
  double random(double hig){return random(0,hig); }

  /// \brief Sets the seed value for random().
  /// By default, random() produces different results each time the program is run,
  /// bit with specific seed you have same sequence of values everytime
  /// \param seed 	int: seed value
  /// \ingroup etc
  void   randomSeed(int seed);

  /// \brief NOISE functions calculate the Perlin noise value at specified coordinates.
  /// \param  x 	float: x-coordinate in noise space
  /// \param  y 	float: y-coordinate in noise space
  /// \param  z 	float: z-coordinate in noise space
  /// \note  Perlin noise is a random sequence generator producing a more natural,
  /// harmonic succession of numbers, than that of the standard random() function.
  /// \ingroup etc
  float noise(float x,float  y,float  z);
  float noise(float x,float  y);
  float noise(float x);

  /// \brief Sets the seed value for noise()
  /// \param seed 	int: seed value
  /// By default, noise() produces different results each time the program is run. Set the seed parameter
  /// to a constant to return the same pseudo-random numbers each time the software is run.
  /// \ingroup etc
  void  noiseSeed(long seed);

  /// \brief Adjusts the character and level of detail produced by the Perlin noise function.
  /// \param  lod 	    int: number of octaves to be used by the noise
  /// \param  falloff float: falloff factor for each octave
  /// \note While any number between 0.0 and 1.0 is valid, note that values greater than 0.5 may result in noise()
  /// returning values greater than 1.0. By changing these parameters, the signal created by the noise()
  /// function can be adapted to fit very specific needs and characteristics.
  /// \ingroup etc
  void noiseDetail(int lod,float falloff);

  /// \brief Adjusts the number of octaves to be used by the Perlin noise function.
  /// \param lod   int: number of octaves to be used by the noise
  /// \ingroup etc
  void noiseDetail(int lod);

  // Min & Max functions:
  // /////////////////////

  /// \brief 'max' as 2 parameters template
  /// \tparam value
  /// \param a
  /// \param b
  /// \return max value
  /// \ingroup etc
  template<class value> inline
  value max(value a,value b)
  {
     return (a>b?a:b);
  }

  /// \brief 'max' as 3 parameters template
  /// \tparam value
  /// \param a
  /// \param b
  /// \param c
  /// \return max value
  /// \ingroup etc
  template<class value> inline
  value max(value a,value b,value c)
  {
     value d=(a>b?a:b);
     return (c>d?c:d);
  }

  /// \brief 'min' as 2 parameters template
  /// \tparam value
  /// \param a
  /// \param b
  /// \return min value
  /// \ingroup etc
  template<class value> inline
  value min(value a,value b)
  {
     return (a<b?a:b);
  }

  /// \brief 'min' as 3 parameters template
  /// \tparam value
  /// \param a
  /// \param b
  /// \param c
  /// \return min value
  /// \ingroup etc
  template<class value> inline
  value min(value a,value b,value c)
  {
     value d=(a<b?a:b);
     return (c<d?c:d);
  }

  /// \brief Mixed type max & min is often used in Processing especially inside graphics functions
  /// \note More sophisticated std:: min & max is defined in header <algorithm>
  /// Use rather std::min & std::max instead of Processing like version!
  /// \ingroup etc
  float     min(int,float);
  float     min(float,int);
  float     max(int,float);
  float     max(float,int);

  /// \brief Mapping value from current range to target range
  /// \param value  float: the incoming value to be converted
  /// \param start1 float: lower bound of the value's current range
  /// \param stop1  float: upper bound of the value's current range
  /// \param start2 float: lower bound of the value's target range
  /// \param stop2  float: upper bound of the value's target range
  /// \return float - mapped value
  /// \ingroup etc
  float map(float value,float start1,float stop1,float start2,float stop2);

  /// \brief Normalise value considering range
  /// \param value 	float: the incoming value to be converted
  /// \param start 	float: lower bound of the value's current range
  /// \param stop 	float: upper bound of the value's current range
  /// \ingroup etc
  float norm(float value,float start,float stop);

  /// \brief lerp is a linear interpolation
  /// \param start 	float: first value
  /// \param stop 	float: second value
  /// \param  amt 	float: float between 0.0 and 1.0
  /// \ingroup etc
  float lerp(float start,float stop,float amt);

  /// \brief Recalculating angles from degrees to radians
  /// \param degrees 	float: degree value to convert to radians
  /// \return radians as float
  /// \ingroup etc
  float radians(float degrees);

  /// \brief Recalculating angles from radians to degrees
  /// \param radians 	float: radian value to convert to degrees
  /// \return degrees as float
  /// \ingroup etc
  float degrees(float radians);

  // Functions for saving window/screen graphics to file:
  // /////////////////////////////////////////////////////

  /// \brief Save window/screen graphics to file using default naming
  /// \ingroup file_output
  void saveFrame();

  /// \brief Save window/screen graphics to file using filename
  /// \param filename : any representation of file name
  /// \ingroup file_output
  void saveFrame(_string_param filename);

  /// \brief Alias for \function saveFrame(filename)
  /// \param filename : any representation of file name
  /// \ingroup file_output
  void save(_string_param filename);

  // Time counting and manipulating:
  // ////////////////////////////////

  /// \brief Stop program for same time (in  milliseconds)
  /// \param napTime: milliseconds to pause before running draw() again \ingroup etc
  void delay(int napTime);

  ///  \brief The year() function returns the current year as an integer (2003, 2004, 2005, etc). \ingroup etc
  int year();
  /// \brief  The month() function returns the current month as a value from 1 - 12. \ingroup etc
  int month();
  /// \brief  The day() function returns the current day as a value from 1 - 31. \ingroup etc
  int day();
  /// \brief  The hour() function returns the current hour as a value from 0 - 23. \ingroup etc
  int hour();
  /// \brief  The minute() function returns the current minute as a value from 0 - 59. \ingroup etc
  int minute();
  /// \brief  The second() function returns the current second as a value from 0 - 59. \ingroup etc
  int second();

  ///  \brief The millis() function returns the number of milliseconds
  /// (thousandths of a second) since starting the program.
  /// This information is often used for timing events and animation sequences. \ingroup etc
  int millis();

  // Processing like string to value converters:
  // ////////////////////////////////////////////

  /// \brief Converts string into integer
  /// \param sval : string representation of integer value
  /// \return integer
  /// \ingroup strings
  inline int     Int(const String& sval) { return std::stoi(sval.c_str());}

  /// \brief Converts string into float
  /// \param sval : string representation of float value
  /// \return float
  /// \ingroup strings
  inline float Float(const String& sval) { return std::stof(sval.c_str());}


}//END of namespace Processing
/* ******************************************************************
 *                     PROCESSING2C  2023                           *
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
#endif
