///\file processing_library.hpp
/// Created by borkowsk
//
#pragma once
#ifndef PROCESSING_LIBRARY_H
#define PROCESSING_LIBRARY_H

#include <cassert>
#include <vector>
#include <algorithm>

#include "processing_string.hpp"

///\namespace Processing2C compatibility libraries
namespace Processing
{
    // Simple functions:
    // /////////////////

  /// Nonparametric, Processing like exit()
  /// ...
  void exit();

  /// String parsing
  /// The split() function breaks a String into pieces using a character or string as the delimiter.
  /// \param string : string to parse
  /// \param delim  : delimiter
  /// \return array of strings
  sarray<String> split(_string_param string,_string_param delim);

  /// WHOLE PROGRAM PARAMETERS!!!
  extern sarray<String> args;

  // Extended graphics: text() & attributes:
  // ///////////////////////////////////////

  /// Sets the current alignment for drawing text.
  /// The parameters are LEFT, CENTER, or RIGHT for horizontal
  /// The parameters are TOP, BOTTOM, CENTER, or BASELINE for vertical
  void textAlign(int,int);

  /// Sets the current alignment for drawing text. The parameters are LEFT, CENTER, or RIGHT for horizontal
  void textAlign(int);

  /// Sets the spacing between lines of text in units of pixels.
  void textLeading(int);

  /// Sets the way text draws to the screen, either as texture maps or as vector geometry (MODEL or SHAPE)
  void textMode(int);

  /// Sets the current font size, measured in units of pixels.
  void textSize(int);

  /// Calculates and returns the width of any character or text string.
  float textWidth(_string_param str);

  /// Print text on screen
  void text(_string_param str,float x,float y);

  /// Print text on screen TODO - IMPLEMENTATION!!!
  void text(_string_param str,float x1,float y1,float x2,float y2);

  /// Font handler
  typedef void* PFont; //ptr<???> TODO?

  /// Make font available for program - TODO - IMPLEMENTATION!!!
  PFont createFont(String fn,int s);
  /// Use previously created font - TODO - IMPLEMENTATION!!!
  void textFont(PFont f);

  // Extended graphics: Shapes:
  // //////////////////////////

  /// Using the beginShape() and endShape() functions allow creating more complex forms. beginShape() begins recording vertices for
  /// a shape and endShape() stops recording. The value of the kind parameter tells it which types of shapes to create from
  /// the provided vertices. With no mode specified, the shape can be any irregular polygon.
  /// kind int: Either POINTS, LINES, TRIANGLES, TRIANGLE_FAN, TRIANGLE_STRIP, QUADS, or QUAD_STRIP
  const int CLOSE=1;

  ///TODO - IMPLEMENTATION!!!
  void beginShape();
  ///TODO - IMPLEMENTATION!!!
  void beginShape(int kind);
  ///TODO - IMPLEMENTATION!!!
  void endShape();

  ///\param	mode 	int: use CLOSE to close the shape
  ///TODO - IMPLEMENTATION!!!
  void endShape(int mode);

  /// vertex() is used to specify the vertex coordinates for points, lines, triangles, quads, and polygons.
  /// It is used exclusively within the beginShape() and endShape() functions.
  /// TODO - IMPLEMENTATION!!!
  ///
  /// \param  v 	float[]: vertex parameters, as a float array of length VERTEX_FIELD_COUNT
  /// \param  x 	float: x-coordinate of the vertex
  /// \param  y 	float: y-coordinate of the vertex
  /// \param  z 	float: z-coordinate of the vertex
  /// \param  u 	float: horizontal coordinate for the texture mapping
  /// \param  v 	float: vertical coordinate for the texture mapping
  void vertex(float x,float y);
  void vertex(float x,float y,float z);
  void vertex(float v[]);
  void vertex(float x,float y,float u,float v);
  void vertex(float x,float y,float z,float u,float v);

  // Generates random numbers:
  // /////////////////////////

  /// Each time the random() function is called, it returns an unexpected value within the specified range.
  /// If only one parameter is passed to the function, it will return a float between zero and the value of the high parameter.
  /// For example, random(5) returns values between 0 and 5 (starting at zero, and up to, but not including, 5).
  /// If two parameters are specified, the function will return a float with a value between the two values.
  /// For example, random(-5, 10.2) returns values starting at -5 and up to (but not including) 10.2.
  /// To convert a floating-point random number to an integer, use the int() function.
  double random(double low,double hig);
  inline
  double random(double hig){return random(0,hig); }

  /// Sets the seed value for random(). By default, random() produces different results each time the program is run.
  void   randomSeed(int seed);

  /// NOISE functions calculate the Perlin noise value at specified coordinates.
  /// \param  x 	float: x-coordinate in noise space
  /// \param  y 	float: y-coordinate in noise space
  /// \param  z 	float: z-coordinate in noise space
  /// \note  Perlin noise is a random sequence generator producing a more natural,
  /// harmonic succession of numbers, than that of the standard random() function.
  float noise(float x,float  y,float  z);
  float noise(float x,float  y);
  float noise(float x);

  /// Sets the seed value for noise()
  /// \param seed 	int: seed value
  /// \note By default, noise() produces different results each time the program is run. Set the seed parameter
  /// to a constant to return the same pseudo-random numbers each time the software is run.
  void  noiseSeed(long seed);

  /// Adjusts the character and level of detail produced by the Perlin noise function.
  /// \param  lod 	    int: number of octaves to be used by the noise
  /// \param  falloff float: falloff factor for each octave
  /// \note While any number between 0.0 and 1.0 is valid, note that values greater than 0.5 may result in noise()
  /// returning values greater than 1.0. By changing these parameters, the signal created by the noise()
  /// function can be adapted to fit very specific needs and characteristics.
  void noiseDetail(int lod,float falloff);
  void noiseDetail(int lod);

  // Min & Max functions:
  // /////////////////////

  /// max with 2 parameters template
  /// \tparam value
  /// \param a
  /// \param b
  /// \return max value
  template<class value> inline
  value max(value a,value b)
  {
     return (a>b?a:b);
  }

  /// max with 3 parameters template
  /// \tparam value
  /// \param a
  /// \param b
  /// \param c
  /// \return max value
  template<class value> inline
  value max(value a,value b,value c)
  {
     value d=(a>b?a:b);
     return (c>d?c:d);
  }

  /// min with 2 parameters template
  /// \tparam value
  /// \param a
  /// \param b
  /// \return min value
  template<class value> inline
  value min(value a,value b)
  {
     return (a<b?a:b);
  }

  /// min with 3 parameters template
  /// \tparam value
  /// \param a
  /// \param b
  /// \param c
  /// \return min value
  template<class value> inline
  value min(value a,value b,value c)
  {
     value d=(a<b?a:b);
     return (c<d?c:d);
  }

  /// Mixed type max & min is often used in Processing especially inside graphics functions
  float     min(int,float);
  float     min(float,int);
  float     max(int,float);
  float     max(float,int);

  ///\note More sophisticated std:: min & max is defined in header <algorithm>
  /// Use rather std::min & std::max instead of Processing like version!

  /// Mapping value from current range to target range
  /// \param value  float: the incoming value to be converted
  /// \param start1 float: lower bound of the value's current range
  /// \param stop1  float: upper bound of the value's current range
  /// \param start2 float: lower bound of the value's target range
  /// \param stop2  float: upper bound of the value's target range
  /// \return float - mapped value
  float map(float value,float start1,float stop1,float start2,float stop2);

  /// Normalise value considering range
  /// \param value 	float: the incoming value to be converted
  /// \param start 	float: lower bound of the value's current range
  /// \param stop 	float: upper bound of the value's current range
  /// \return	float
  float norm(float value,float start,float stop);

  /// \param start 	float: first value
  /// \param stop 	float: second value
  /// \param  amt 	float: float between 0.0 and 1.0
  /// \return	float
  float lerp(float start,float stop,float amt);

  /// Recalculating angles from degrees to radians
  ///\param degrees 	float: degree value to convert to radians
  ///\return	float
  float radians(float degrees);

  /// Recalculating angles from radians to degrees
  ///\param radians 	float: radian value to convert to degrees
  ///\return	float
  float degrees(float radians);

  // Functions for saving window/screen graphics to file:
  // /////////////////////////////////////////////////////

  /// Save window/screen graphics to file using default naming
  void saveFrame();

  /// Save window/screen graphics to file using filename
  void saveFrame(_string_param filename);

  /// Alias for \function saveFrame(filename)
  void save(_string_param filename);

  // Time counting and manipulating:
  // ////////////////////////////////

  /// Parameters: int napTime: milliseconds to pause before running draw() again
  void delay(int napTime);

  /// The year() function returns the current year as an integer (2003, 2004, 2005, etc).
  int year();
  /// The month() function returns the current month as a value from 1 - 12.
  int month();
  /// The day() function returns the current day as a value from 1 - 31.
  int day();
  /// The hour() function returns the current hour as a value from 0 - 23.
  int hour();
  /// The minute() function returns the current minute as a value from 0 - 59.
  int minute();
  /// The second() function returns the current second as a value from 0 - 59.
  int second();

  /// The millis() function returns the number of milliseconds (thousandths of a second) since starting the program.
  /// This information is often used for timing events and animation sequences.
  int millis();

  // Processing like string to value converters:
  // ////////////////////////////////////////////

  inline int     Int(const String& sval) { return std::stoi(sval.c_str());}
  inline float Float(const String& sval) { return std::stof(sval.c_str());}


}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2021-11-26                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiów Społecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
#endif
