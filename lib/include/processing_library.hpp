// processing_library.hpp
#pragma once
#ifndef PROCESSING_LIBRARY_H
#define PROCESSING_LIBRARY_H
#include <string>
#include <cassert>
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

  template<class T>
  class array
  {
    public:
        size_t length;
        array(size_t N);
  };

  template<class T>
  class sarray
  {
    public:
        sarray();
        sarray(array<T>* tab);
        sarray(nullptr_t);//Empty sarray
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
  };

  template<class T>
  class smatrix
  {
    public:
        smatrix();
        smatrix(matrix<T>* tab);
        size_t length();
        matrix<T>* operator -> ();
        sarray<T>& operator [] (size_t i);
  };


/// Simple functions
  float random(double low,double hig);

  inline
  float random(double hig){return random(0,hig); }

}//END of namespace Processing
#endif
