// processing_library.hpp
#pragma once
#ifndef PROCESSING_LIBRARY_H
#define PROCESSING_LIBRARY_H
#include <string>
#include <cassert>
#include <fstream>
#include <initializer_list>
///
///
///
namespace Processing
{
/// Classes
  class String:public std::string
  {
    public:
      String(const char*);
      String(const String&);
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

  template<class T>
  class ptr
  {
    public:
        ptr();
        ptr(T* ini);
        T* operator -> ();
        operator T& ();
        bool operator == (const ptr&) const;
        bool operator != (const ptr&)const;
        bool operator == (T*) const;
        bool operator != (T*) const;
  };

  class _string_param:public String
  {
    public:
    _string_param(String p):String(p){}
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
    public:
        virtual int compareTo(ptr<T> t)=0;
  };

  //https://en.cppreference.com/w/cpp/utility/initializer_list
  //https://en.cppreference.com/w/cpp/language/constructor

  template<class T>
  class array
  {
    public:
        size_t length;
        array(size_t N);
        array(array<T>* tab);//TEST IT! TODO
  };

  template<class T>
  class sarray
  {
    public:
        sarray();
        sarray(array<T>* tab);
        sarray(nullptr_t);//Empty sarray
        sarray(std::initializer_list<T> l);
        size_t length();
        array<T>* operator -> ();
        T& operator [] (size_t i);
  };

  template<class T>
  class matrix
  {
    public:
        size_t length;
        matrix(size_t N,size_t M);
        matrix(array<T>* tab);//??? TEST IT! TODO!!!
  };

  template<class T>
  class smatrix
  {
    public:
        smatrix();
        smatrix(matrix<T>* tab);
        smatrix(std::initializer_list<T> l);//??? TODO TEST IT!
        size_t length();
        matrix<T>* operator -> ();
        sarray<T>& operator [] (size_t i);
  };


/// Simple functions
  float random(double low,double hig);

  inline
  float random(double hig){return random(0,hig); }

  int       min(int,int);
  double    min(double,double);
  int       max(int,int);
  double    max(double,double);

  void loop();
  void noLoop();
  void saveFrame(const String& filename);
  void saveFrame(const std::string& filename);


/// File streams
  class PrintWriter
  {
      std::fstream* ptr;
   public:
      PrintWriter();
      PrintWriter(PrintWriter&);
      std::fstream* operator -> ();
      void flush();
  };

  PrintWriter& createWriter(const String&);
  PrintWriter& createWriter(const char* );

  //void print();//To bez sensu
  //void print(PrintWriter& o,_string_param _p1="");
  void print(PrintWriter& o,const String& );
  void print(PrintWriter& o,const std::string& );

  //void println(PrintWriter& o,_string_param _p1="");
  void println(PrintWriter& o,const String& );
  void println(PrintWriter& o,const std::string& );

}//END of namespace Processing
#endif
