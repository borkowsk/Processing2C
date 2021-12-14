// processing_lists.hpp
#pragma once
#ifndef PROCESSING_LISTS_H
#define PROCESSING_LISTS_H
///
///
///
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include <vector>

namespace Processing
{
/// Processing specialised lists
/////////////////////////////////////

  ///
  /// \brief The FloatList class
  ///
  /// \link \a https://en.cppreference.com/w/cpp/container/vector
  /// \link \a https://en.cppreference.com/w/cpp/language/list_initialization
  class FloatList:private std::vector<float>,virtual public _self_printable
  {
     public:
      using     std::vector<float>::begin;
      using     std::vector<float>::end;
      using     std::vector<float>::operator[];

      ~FloatList()=default;
      FloatList()=default;
      FloatList(FloatList const&) = default;  // copy-constructor (not aggregate initialization)
      FloatList(std::initializer_list<int>);// initializer-list constructor (not copy constructor)
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

  ///
  /// \brief The IntList class
  ///
  /// \link \a https://en.cppreference.com/w/cpp/container/vector
  /// \link \a https://en.cppreference.com/w/cpp/language/list_initialization
  class IntList:private std::vector<int>,virtual public _self_printable
  {
     public:
       using     std::vector<int>::begin;
       using     std::vector<int>::end;
       using     std::vector<int>::operator[];

       ~IntList()=default;
       IntList()=default;
       IntList(IntList const&) = default;  // copy-constructor (not aggregate initialization)
       IntList(std::initializer_list<int>);// initializer-list constructor (not copy constructor)
       IntList(int initialSize):std::vector<int>(initialSize){}

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

  ///
  /// \brief The StringList class
  ///
  /// \link \a https://en.cppreference.com/w/cpp/container/vector
  /// \link \a https://en.cppreference.com/w/cpp/language/list_initialization
  class StringList:private std::vector<Processing::String>, virtual public _self_printable
  {
     public:
       using     std::vector<Processing::String>::begin;
       using     std::vector<Processing::String>::end;
       using     std::vector<Processing::String>::operator[];

       ~StringList() = default;
       StringList() = default;
       StringList(StringList const&) = default;  // copy-constructor (not aggregate initialization)
       StringList(std::initializer_list<String> lst);// initializer-list constructor (not copy constructor)
       StringList(sarray<String> const& arr);
       StringList(int initialSize):std::vector<Processing::String>(initialSize){}

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


//  Implementation part
// ///////////////////////
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
    String ret{"Size:"};
    ret+=_string_param(size());
    ret+=String(" [");
    for(float val:*this)
    {
        ret+=_string_param(val);
        ret+=String(" ");
    }
    ret+=String("]");//TODO +=char ?
    return ret;
}

inline String IntList::print() const
{
    String ret{"Size:"};
    ret+=_string_param(size());
    ret+=String(" [");
    for(int val:*this)
    {
        ret+=_string_param(val);
        ret+=String(" ");
    }
    ret+=String("]");//TODO +=char ?
    return ret;
}

inline String StringList::print() const
{
    String ret{"Size:"};
    ret+=_string_param(size());
    ret+=String(" [");
    for(String val:*this)
    {
        ret+=String('"');
        ret+=_string_param(val);
        ret+=String("\" ");
    }
    ret+=String("]");//TODO +=char ?
    return ret;
}

inline void StringList::append(String &what)
{
    assert("Not implemented"== nullptr);
}

inline StringList::StringList(const sarray<String> &arr):
        std::vector<Processing::String>(arr.length())
{
    int i=0;
    for(String const& s:arr)
        (*this)[i++]=s;
}


}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2021-12-14                   */
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
