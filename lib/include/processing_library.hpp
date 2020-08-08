// processing_library.hpp
#pragma once
#ifndef PROCESSING_LIBRARY_H
#define PROCESSING_LIBRARY_H
#include <string>
#include <cassert>
#include <fstream>
///
///
///
namespace Processing
{
/// Classes
  class String:public std::string
  {
    ///INFO:
    public:
      virtual ~String();//??? Na pewno potrzebne?
      String(const char*);
      String(const String&);
      String();
      bool operator == (nullptr_t);
      bool operator != (nullptr_t);
      String& operator += (const String&);
      String& operator += (int);
      String& operator += (float);
      String& operator += (double);
      String& operator += (bool);
      String& operator  + (const String&) const;
      String& operator  + (int) const;
      String& operator  + (float) const;
      String& operator  + (double) const;
      String& operator  + (bool) const;
  };

   String& operator  + (int,const String&);
   String& operator  + (float,const String&);
   String& operator  + (double,const String&);
   String& operator  + (bool,const String&);


  class _string_param:public String
  {
    ///INFO: class designed for automatic PARAMETER conversion into String
    public:
        virtual ~_string_param();// Zwalnianie zasobów
        _string_param(const String& p):String(p){}
        _string_param(const char *p):String(p){}
        _string_param(double p);
        _string_param(float  p);
        _string_param(int    p);
        _string_param(void*  p);
        template<class T>
        _string_param(ptr<T> p);
  };

  template<class X>
  String& operator + (String&,ptr<X>);

  template<class X>
  String& operator += (String&,ptr<X>);

  template<class T>
  /*interface*/ class Comparable
  {
    ///INFO:
    public:
        virtual int compareTo(ptr<T> t)=0;
  };

/// Simple functions
  float random(double low,double hig);
  inline float random(double hig){return random(0,hig); }

  int       min(int,int);
  double    min(double,double);
  int       max(int,int);
  double    max(double,double);


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

  void delay(int napTime); /// Parameters:	napTime 	int: milliseconds to pause before running draw() again

  void saveFrame(const String& filename);
  void saveFrame(const std::string& filename);

/// Extended graphix text()
  void text(_string_param str,float x,float y);
  void text(_string_param str,float x1,float y1,float x2,float y2);
  //void text(const String& str,float x,float y);
  //void text(const String& str,float x1,float y1,float x2,float y2);

/// File streams
  class PrintWriter
  {
   ///INFO:
      std::fstream* ptr;
   public:
      virtual ~PrintWriter();// Zwalnianie zasobów
      PrintWriter();
      PrintWriter(PrintWriter&);
      std::fstream* operator -> ();
      void flush();
  };

  PrintWriter& createWriter(const String&);
  PrintWriter& createWriter(const char* );

  //void print();//To bez sensu
  void print(PrintWriter& o,_string_param _p1="");
  //void print(PrintWriter& o,const String& );
  //void print(PrintWriter& o,const std::string& );

  void println(PrintWriter& o,_string_param _p1="");
  //void println(PrintWriter& o,const String& );
  //void println(PrintWriter& o,const std::string& );

  void saveFrame();
  void saveFrame(const char* filename);

}//END of namespace Processing
#endif
