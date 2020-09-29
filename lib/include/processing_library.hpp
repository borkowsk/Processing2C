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

  class String:public std::string
  {
    ///INFO:
    public:
      //virtual ???
      ~String();//??? Na pewno potrzebne?
      String(){}
      String(const char* str):std::string(str){}
      String(char  c);
      String(const std::string& str):std::string(str){}
      String(const String&);

      String* operator -> () //Utożsamia operator -> z operatorem . dla tego typu!!!
      { return this; }//Sam z siebie robi pointer na siebie :-D HACK!!!

      bool  equals(const char* wz) { return this->compare(wz)==0;}
      operator bool () { return this->c_str()!=nullptr; }
      bool operator == (nullptr_t);
      bool operator != (nullptr_t);
      String& operator += (const String&);
      String& operator += (int);
      String& operator += (float);
      String& operator += (double);
      String& operator += (bool);
      String& operator += (void*);
      String operator  + (const String&) const;
      String operator  + (int) const;
      String operator  + (float) const;
      String operator  + (double) const;
      String operator  + (bool) const;
      String operator  + (void*) const;
      template<class X>
      String operator  + (ptr<X>& p) const;
  };

   String operator  + (int,const String&);
   String operator  + (float,const String&);
   String operator  + (double,const String&);
   String operator  + (bool,const String&);

   template<class X>
   String& operator + (String&,ptr<X>);

   template<class X>
   String& operator += (String&,ptr<X>);

   /*interface*/ class _self_printable
   {
     public:
       virtual String print() const=0;
   };

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
        _string_param(char p);
        _string_param(double p);
        _string_param(float  p);
        _string_param(int    p);
        _string_param(const void*  p);
        template<class T>
        _string_param(ptr<T> p):_string_param(p.get()){}
        //operator String& () {return *(String*)this;}
  };

/// Simple functions
/////////////////////////////////////////////////

  /// Extended graphix text() & Attributes
  void textAlign(int); /// Sets the current alignment for drawing text. The parameters are LEFT, CENTER, or RIGHT for horizontal
  void textAlign(int,int);/// and TOP, BOTTOM, CENTER, or BASELINE for vertical
  void textLeading(int);/// Sets the spacing between lines of text in units of pixels.
  void textMode(int);/// Sets the way text draws to the screen, either as texture maps or as vector geometry (MODEL or SHAPE)
  void textSize(int);/// Sets the current font size, measured in units of pixels.
  float textWidth(_string_param str);/// Calculates and returns the width of any character or text string.
  void text(_string_param str,float x,float y);
  void text(_string_param str,float x1,float y1,float x2,float y2);

  void  randomSeed(int seed);
  double random(double low,double hig);
  inline double random(double hig){return random(0,hig); }


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

  void saveFrame();
  void saveFrame(const String& filename);
  void saveFrame(const std::string& filename);
  void saveFrame(const char* filename);

/// File streams
////////////////////////////////////////////////////////////////////////

  class PrintWriter
  {
   ///INFO:
      std::fstream* ptr;
   public:
      virtual ~PrintWriter();// Zwalnianie zasobów
      PrintWriter(std::fstream* p);
      PrintWriter& operator = (std::fstream* p);

      PrintWriter();
      PrintWriter(PrintWriter& );

      void set(std::fstream*);
      operator std::fstream& () {return *ptr;}

      PrintWriter& operator = (PrintWriter& );
      std::fstream* operator -> ();
      bool operator == (std::nullptr_t p) const;
      bool operator != (std::nullptr_t p) const;

      void flush();
      //Nie działa jako "friend"
      //error: undefined reference to `Processing::PrintWriter::PrintWriter(std::basic_fstream<char, std::char_traits<char> >*)'
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

/// Processing specialised lists
///////////////////////////////////////////////////////

  class FloatList:private std::vector<float>,virtual public _self_printable
  {
     public:
      using     std::vector<float>::begin;
      using     std::vector<float>::end;
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
  inline void StringList::append(Processing::String& what){std::vector<Processing::String>::push_back(what);}

  inline float   FloatList::get(int index){ return (*this)[index];}
  inline int       IntList::get(int index){ return (*this)[index];}
  inline String StringList::get(int index){ return (*this)[index];}

  inline void  FloatList::set(int index,float what){ (*this)[index]=what;}
  inline void    IntList::set(int index,int what){ (*this)[index]=what;}
  inline void StringList::set(int index,_string_param what){ (*this)[index]=what;}

  inline String FloatList::print() const
  {
      String ret=String("Size:")+size()+String(" [");
      for(float val:*this)
          ret+=val+String(" ");
      ret+=String("]");
      return ret;
  }

  inline String IntList::print() const
  {
      String ret=String("Size:")+size()+String(" [");
      for(int val:*this)
          ret+=val+String(" ");
      ret+=String("]");
      return ret;
  }

  inline String StringList::print() const
  {
      String ret=String("Size:")+size()+String(" [");
      for(String val:*this)
          ret+=String('"')+val+String("\" ");
      ret+=String("]");
      return ret;
  }

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2020-09-29                   */
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
