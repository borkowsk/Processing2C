// processing_library.hpp
#pragma once
#ifndef PROCESSING_LIBRARY_H
#define PROCESSING_LIBRARY_H
#include <string>
#include <cassert>
#include <cfloat>
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>
///
///
///
namespace Processing
{
/// MATH CONSTANTS
/// # define M_PI_2		1.57079632679489661923	/* pi/2 */
/// # define M_PI_4		0.78539816339744830962	/* pi/4 */
    const auto PI=M_PI;//3.6651914291881;
    const auto TWO_PI=2*M_PI;//6.2831855f
    const auto TAU=6.2831855f;
    const auto HALF_PI=M_PI_2;
    const auto QUARTER_PI=M_PI_4;
    const auto MAX_INT=INT_MAX;

/// Classes
/////////////////////////////////////////////////////////////

  class _string_param;//Zapowiadająca

  class String:public std::string
  {
    ///INFO:
    public:
      friend class Processing::_string_param;

      //virtual ???
      ~String();//??? Na pewno potrzebne?

      String(){}
      String(const char* str):std::string(str){}
      String(nullptr_t):String(){}
      explicit
      String(char  c);
      String(const std::string& str):std::string(str){}
      String(const String&);
      String(double v);//:String(){ operator+=(v);}
      String(const Object* p);//:String("@"){ operator+=( (long unsigned int)p.get() );}

      template<class T>
      String(const ptr<T> p);//:String("@"){ operator+=( (long unsigned int)p.get() );}

      String* operator -> () //Utożsamia operator -> z operatorem . dla tego typu!!!
      { return this; }//Sam z siebie robi pointer na siebie :-D HACK!!!

      bool  equals(const char* wz) { return this->compare(wz)==0;}
      //operator bool () { return this->c_str()!=nullptr; }
      bool  notEmpty() { return this->c_str()!=nullptr; }
      bool operator == (nullptr_t);
      bool operator != (nullptr_t);

      String& operator = (_string_param v);
      String& operator += (_string_param v);

      //template<class X>
      //String& operator += (const ptr<X>&);

      String operator  + (_string_param) const;

      //template<class X>
      //String operator  + (const ptr<X>& p) const;
  };

   //String operator  + (_string_param,float); //A lot of conflicts :-(
   //String operator  + (_string_param,int); //A lot of conflicts :-(
   String operator  + (_string_param,const String&);

   //template<class X>
   //String& operator + (const ptr<X>&,String&);

   extern 
   sarray<String> args; //WHOLE PROGRAM PARAMETERS!!!

   /*interface*/ class _self_printable
   {
     public:
       virtual String print() const=0;
   };

   //Processing like string -. value converters
   inline int     Int(const String& sval) { return std::stoi(sval);}
   inline float Float(const String& sval) { return std::stof(sval);}

   template<class T>
   class  self_printable_ptr:public ptr<T>,virtual public _self_printable
   {
     public:
       String print() const { return  this->get()->print(); }
       self_printable_ptr():ptr<T>(nullptr){}
       self_printable_ptr(T* ini):ptr<T>(ini){}
       //using ptr<T>::operator = ;
       self_printable_ptr<T>& operator = (T* other){ ptr<T>::operator = ((T*)other); return *this;}
       auto begin() { return this->get()->begin(); } //need C++14 !
       auto end()   { return this->get()->end(); } //need C++14 !
   };

  class _string_param:public String
  {
    ///INFO: class designed for automatic PARAMETER conversion into String
    public:
        virtual ~_string_param();// Zwalnianie zasobów
        _string_param(const String& p):String(p){}
        _string_param(const std::string& p):String(p){}
        _string_param(const char *p):String(p){}
        _string_param(const _self_printable& p):String(p.print()){}
        _string_param(char   p);
        _string_param(double p);
        _string_param(float  p);
        _string_param(int    p);
        _string_param(long unsigned int p);
        _string_param(std::exception &e);
        //explicit
        _string_param(const void*  p);

        _string_param operator  + (_string_param) const;

        template<class T>
        _string_param(ptr<T> p):_string_param(p.get()){}
        //operator String& () {return *(String*)this;}
        String& get() {return *(String*)this;}
  };

  inline String::String(double v):String()
  {
      operator+=(v);
  }

  inline String::String(const Object* p):String("@")
  {
      operator+=( (long unsigned int)p );
  }

  template<class T>
  inline String::String(const ptr<T> p):String("@")
  {
      operator+=( (long unsigned int)p.get() );
  }

/// Simple functions
/////////////////////////////////////////////////

  /// nonparametr exit()
  void exit();

  /// String parsing
  sarray<String> split(_string_param string,_string_param delim);///The split() function breaks a String into pieces
                                                                 ///using a character or string as the delimiter.

  /// Extended graphix text() & Attributes
  void textAlign(int); /// Sets the current alignment for drawing text. The parameters are LEFT, CENTER, or RIGHT for horizontal
  void textAlign(int,int);/// and TOP, BOTTOM, CENTER, or BASELINE for vertical
  void textLeading(int);/// Sets the spacing between lines of text in units of pixels.
  void textMode(int);/// Sets the way text draws to the screen, either as texture maps or as vector geometry (MODEL or SHAPE)
  void textSize(int);/// Sets the current font size, measured in units of pixels.
  float textWidth(_string_param str);/// Calculates and returns the width of any character or text string.
  void text(_string_param str,float x,float y);
  void text(_string_param str,float x1,float y1,float x2,float y2);

  typedef void* PFont;              /// Font handler
  PFont createFont(String fn,int s);/// Make font available for program
  void textFont(PFont f);           /// Use font

  /// Shapes:
  /// Using the beginShape() and endShape() functions allow creating more complex forms. beginShape() begins recording vertices for
  /// a shape and endShape() stops recording. The value of the kind parameter tells it which types of shapes to create from
  /// the provided vertices. With no mode specified, the shape can be any irregular polygon.
  /// 	kind int: Either POINTS, LINES, TRIANGLES, TRIANGLE_FAN, TRIANGLE_STRIP, QUADS, or QUAD_STRIP
  const int CLOSE=1;
  void beginShape();
  void beginShape(int kind);
  void endShape();
  void endShape(int mode);/// Parameters	mode 	int: use CLOSE to close the shape
  /// vertex() is used to specify the vertex coordinates for points, lines, triangles, quads, and polygons. It is used exclusively
  /// within the beginShape() and endShape() functions.
  /// Parameters
  /// v 	float[]: vertex parameters, as a float array of length VERTEX_FIELD_COUNT
  /// x 	float: x-coordinate of the vertex
  /// y 	float: y-coordinate of the vertex
  /// z 	float: z-coordinate of the vertex
  /// u 	float: horizontal coordinate for the texture mapping
  /// v 	float: vertical coordinate for the texture mapping
  void vertex(float x,float y);
  void vertex(float x,float y,float z);
  void vertex(float v[]);
  void vertex(float x,float y,float u,float v);
  void vertex(float x,float y,float z,float u,float v);

  /// Generates random numbers:
  /// Each time the random() function is called, it returns an unexpected value within the specified range.
  /// If only one parameter is passed to the function, it will return a float between zero and the value of the high parameter.
  /// For example, random(5) returns values between 0 and 5 (starting at zero, and up to, but not including, 5).
  /// If two parameters are specified, the function will return a float with a value between the two values.
  /// For example, random(-5, 10.2) returns values starting at -5 and up to (but not including) 10.2.
  /// To convert a floating-point random number to an integer, use the int() function.
  double random(double low,double hig);
  inline
  double random(double hig){return random(0,hig); }
  void   randomSeed(int seed);/// Sets the seed value for random(). By default, random() produces different results each time the program is run.

  /// NOISE:
  /// Returns the Perlin noise value at specified coordinates. Perlin noise is a random sequence generator
  /// producing a more natural, harmonic succession of numbers than that of the standard random() function.
  /// Parameters:
  /// x 	float: x-coordinate in noise space
  /// y 	float: y-coordinate in noise space
  /// z 	float: z-coordinate in noise space
  /// By default, noise() produces different results each time the program is run. Set the seed parameter
  /// to a constant to return the same pseudo-random numbers each time the software is run.
  float noise(float x);
  float noise(float x,float  y);
  float noise(float x,float  y,float  z);
  void  noiseSeed(long seed);/// Parameters	seed 	int: seed value
  /// Adjusts the character and level of detail produced by the Perlin noise function.
  /// While any number between 0.0 and 1.0 is valid, note that values greater than 0.5 may result in noise()
  /// returning values greater than 1.0. By changing these parameters, the signal created by the noise()
  /// function can be adapted to fit very specific needs and characteristics.
  /// Parameters:
  /// lod 	int: number of octaves to be used by the noise
  /// falloff 	float: falloff factor for each octave
  void noiseDetail(int lod);
  void noiseDetail(int lod,float falloff);

  /// Min & Max functions:
  /// More sophisticated min & max is defined in header <algorithm>
  /// Use std::min & std::max instead of Processing like version!
  template<class value>
  inline 
  value max(value a,value b)
  {
     return (a>b?a:b);
  }

  template<class value>
  inline 
  value max(value a,value b,value c)
  {
     value d=(a>b?a:b);
     return (c>d?c:d);
  }

  template<class value>
  inline 
  value min(value a,value b)
  {
     return (a<b?a:b);
  }

  template<class value>
  inline 
  value min(value a,value b,value c)
  {
     value d=(a<b?a:b);
     return (c<d?c:d);
  }

  /// Mixed type max & min is often used in Processing
  /// especially inside graphix functions
  float     min(int,float);
  float     min(float,int);
  float     max(int,float);
  float     max(float,int);

  /// Mapping and normalising values:
  float map(float value,float start1,float stop1,float start2,float stop2);
  /// Parameters:
  /// value 	float: the incoming value to be converted
  /// start1 	float: lower bound of the value's current range
  /// stop1 	float: upper bound of the value's current range
  /// start2 	float: lower bound of the value's target range
  /// stop2 	float: upper bound of the value's target range

  float norm(float value,float start,float stop);
  /// Parameters:
  /// value 	float: the incoming value to be converted
  /// start 	float: lower bound of the value's current range
  /// stop 	float: upper bound of the value's current range

  float lerp(float start,float stop,float amt);
  /// Parameters:
  /// start 	float: first value
  /// stop 	float: second value
  /// amt 	float: float between 0.0 and 1.0

  /// Recalculating angles
  float radians(float degrees);
  float degrees(float radians);
  /// degrees 	float: degree value to convert to radians
  /// radians 	float: radian value to convert to degrees
  /// Returns	float

  /// Graphics saving to file
  void saveFrame();
  void saveFrame(_string_param filename);
  void save(_string_param filename);

  /// Time counting and manipulatring
  void delay(int napTime); /// Parameters: int napTime: milliseconds to pause before running draw() again
  int year();   /// The year() function returns the current year as an integer (2003, 2004, 2005, etc).
  int month();  /// The month() function returns the current month as a value from 1 - 12.
  int day();    /// The day() function returns the current day as a value from 1 - 31.
  int hour();   /// The hour() function returns the current hour as a value from 0 - 23.
  int minute(); /// The minute() function returns the current minute as a value from 0 - 59.
  int second(); /// The second() function returns the current second as a value from 0 - 59.
  int millis(); /// Returns the number of milliseconds (thousandths of a second) since starting the program.
                /// This information is often used for timing events and animation sequences.

/// File streams
////////////////////////////////////////////////////////////////////////

  class BufferedReader
  {
   ///INFO:
      std::ifstream* ptr;
   public:
      virtual ~BufferedReader();// zamknięcie i zwalnianie zasobów

      //Konstruktory
      BufferedReader(){ptr=nullptr;}
      BufferedReader(const std::nullptr_t& p): BufferedReader(){}
      BufferedReader(std::ifstream* p) { ptr=p;}
      BufferedReader(BufferedReader& );
      BufferedReader(const BufferedReader& );//need for nullptr initialisation  BUT NOT USED?

      void _set(std::ifstream* p)  { ptr=p;} //for createReader ONLY
      std::ifstream* _get() const;
      bool _ok() const { return ptr!=nullptr && ptr->is_open();}

      operator std::ifstream& () {*_get();}
      BufferedReader& operator = (std::ifstream* p) { ptr=p;}
      BufferedReader& operator = (BufferedReader& );
      BufferedReader* operator -> () { return this; }

      bool operator == (std::nullptr_t p) const { return ptr==nullptr; }
      bool operator != (std::nullptr_t p) const { return ptr!=nullptr; }

      String readLine();

      void close() { if(ptr!=nullptr) ptr->close(); }
  };

  BufferedReader& createReader(_string_param _name);

  inline
  String BufferedReader::readLine()
  {
      if(ptr!=nullptr)
      {
          String line;
          std::getline(*ptr, line);
          return line;
      }
      else return nullptr;
  }

  class PrintWriter
  {
   ///INFO:
      std::ofstream* ptr;
   public:
      virtual ~PrintWriter();// zamknięcie i zwalnianie zasobów

      //Konstruktory
      PrintWriter() {ptr=nullptr;}
      PrintWriter(const std::nullptr_t& p): PrintWriter(){}
      PrintWriter(std::ofstream* p) { ptr=p;}
      PrintWriter(PrintWriter& );
      PrintWriter(const PrintWriter& );//need for nullptr initialisation BUT NOT USED?

      void _set(std::ofstream* p)  { ptr=p;} //for createWriter ONLY
      std::ofstream* _get() const;
      bool _ok() const { return ptr!=nullptr && ptr->is_open();}

      operator std::ofstream& () {*_get();}
      PrintWriter&   operator = (std::ofstream* p) { ptr=p;}
      PrintWriter&   operator = (PrintWriter& );
      PrintWriter*   operator -> () { return this; }

      bool operator == (std::nullptr_t p) const { return ptr==nullptr; }
      bool operator != (std::nullptr_t p) const { return ptr!=nullptr; }

      void flush() { if(ptr!=nullptr) ptr->flush(); }
      void close() { if(ptr!=nullptr) ptr->close(); }
  };

  PrintWriter& createWriter(_string_param _name);

  //void print();//To bez sensu
  void print(PrintWriter& o,_string_param _p1="");
  //void print(PrintWriter& o,const String& );
  //void print(PrintWriter& o,const std::string& );

  void println(PrintWriter& o,_string_param _p1="");
  //void println(PrintWriter& o,const String& );
  //void println(PrintWriter& o,const std::string& );

/// Processing specialised lists
///////////////////////////////////////////////////////

  class FloatList:private std::vector<float>,virtual public _self_printable
  {
     public:
      using     std::vector<float>::begin;
      using     std::vector<float>::end;
      FloatList(){}
      FloatList(int initialSize):std::vector<float>(initialSize){}
      int       size() const;// 	Get the length of the list
      void      clear();// 	Remove all entries from the list
      float     get(int index);// 	Get an entry at a particular index
      void      append(float what);// 	Add a new entry to the list (.append(values) .append(list) )
      void      set(int index,float what);// 	Set the entry at a particular index

      float     remove(int index);// 	Remove an element from the specified index
      bool      hasValue(float what);// 	Check if a number is a part of the list
      void      add(int index,float amount);// 	Add to a value
      void      sub(int index,float amount);// 	Subtract from a value
      void      mult(int index,float amount);// 	Multiply a value
      void      div(int index,float amount);// 	Divide a value
      float     min();// 	Return the smallest value
      float     max();// 	Return the largest value
      void      sort();// 	Sorts an array, lowest to highest
      void      sortReverse();// 	Reverse sort, orders values from highest to lowest
      void      reverse();// 	Reverse the order of the list elements
      void      shuffle();// 	Randomize the order of the list elements
      sarray<float>     array();// 	Create a new array with a copy of all the values
      String print() const;
  };

  class IntList:private std::vector<int>,virtual public _self_printable
  {
     public:
       using     std::vector<int>::begin;
       using     std::vector<int>::end;
       int      size() const;// 	Get the length of the list
       void     clear();// 	Remove all entries from the list
       int      get(int index);// 	Get an entry at a particular index
       void     append(int   what);// 	Add a new entry to the list (.append(values) .append(list) )
       void     set(int index,int   what);// 	Set the entry at a particular index

       int      remove(int index);// 	Remove an element from the specified index
       bool     hasValue(int   what);// 	Check if a number is a part of the list
       void     add(int index,int   amount);// 	Add to a value
       void     sub(int index,int   amount);// 	Subtract from a value
       void     mult(int index,int   amount);// 	Multiply a value
       void     div(int index,int   amount);// 	Divide a value
       int      min();// 	Return the smallest value
       int      max();// 	Return the largest value
       void     sort();// 	Sorts an array, lowest to highest
       void     sortReverse();// 	Reverse sort, orders values from highest to lowest
       void     reverse();// 	Reverse the order of the list elements
       void     shuffle();// 	Randomize the order of the list elements
       sarray<int>  array();// 	Create a new array with a copy of all the values
       String print() const;
  };

  class StringList:private std::vector<Processing::String>, virtual public _self_printable
  {
     public:
       using     std::vector<Processing::String>::begin;
       using     std::vector<Processing::String>::end;
       int      size() const;// 	Get the length of the list
       void     clear();// 	Remove all entries from the list
       String   get(int index);// 	Get an entry at a particular index
       void     append(_string_param   what);// Add a new entry to the list (.append(values) .append(list) )
       void     append(String& what);
       void     set(int index,_string_param   what);// 	Set the entry at a particular index

       String   remove(int index);// 	Remove an element from the specified index
       bool     hasValue(_string_param   what);// Check if a number is a part of the list
       void     sort();// 	Sorts an array, lowest to highest
       void     sortReverse();// 	Reverse sort, orders values from highest to lowest
       void     reverse();// 	Reverse the order of the list elements
       void     shuffle();// 	Randomize the order of the list elements
       void     lower();// 	Make the entire list lower case
       void     upper();// 	Make the entire list upper case
       sarray<int>  array();// 	Create a new array with a copy of all the values
       String print() const;
  };

  typedef Processing::self_printable_ptr<FloatList>  pFloatList;
  typedef Processing::self_printable_ptr<IntList>    pIntList;
  typedef Processing::self_printable_ptr<StringList> pStringList;

  inline int  FloatList::size() const { return std::vector<float>::size();}
  inline int    IntList::size() const { return std::vector<int>::size();}
  inline int StringList::size() const { return std::vector<Processing::String>::size();}

  inline void  FloatList::clear() { return std::vector<float>::clear();}
  inline void    IntList::clear() { return std::vector<int>::clear();}
  inline void StringList::clear() { return std::vector<Processing::String>::clear();}

  inline void  FloatList::append(float what){std::vector<float>::push_back(what);}
  inline void    IntList::append(int what){std::vector<int>::push_back(what);}
  inline void StringList::append(_string_param what){std::vector<Processing::String>::push_back((String)what);}
  //inline void StringList::append(Processing::String& what){std::vector<Processing::String>::push_back(what);}

  inline float   FloatList::get(int index){ return (*this)[index];}
  inline int       IntList::get(int index){ return (*this)[index];}
  inline String StringList::get(int index){ return (*this)[index];}

  inline void  FloatList::set(int index,float what){ (*this)[index]=what;}
  inline void    IntList::set(int index,int what){ (*this)[index]=what;}
  inline void StringList::set(int index,_string_param what){ (*this)[index]=what;}

  inline String FloatList::print() const
  {
      String ret=_string_param("Size:")+_string_param(size());
      ret+=String(" [");
      for(float val:*this)
          ret+=_string_param(val)+_string_param(" ");
      ret+=String("]");
      return ret;
  }

  inline String IntList::print() const
  {
      String ret=_string_param("Size:")+_string_param(size())+_string_param(" [");
      for(int val:*this)
          ret+=_string_param(val)+_string_param(" ");
      ret+=String("]");
      return ret;
  }

  inline String StringList::print() const
  {
      String ret=_string_param("Size:")+_string_param(size())+_string_param(" [");
      for(String val:*this)
          ret+=_string_param('"')+_string_param(val)+_string_param("\" ");
      ret+=String("]");
      return ret;
  }

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2021-07-12                   */
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
