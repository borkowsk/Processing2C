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

template<class T>
class ArrayList:public std::vector<T>, virtual public _self_printable
{
  public:
    using std::vector<T>::begin;
    using std::vector<T>::end;

    bool add(const T& o)
    {
      this->push_back(o);
      return true;
    }

    T& get(int index)
    {
        return this->at(index);// []?
    }

    void remove(int index)
    {
       assert("NOT IMPLEMENTED"==nullptr);
       // this->erase(index);//TODO CHECK
    }

    bool remove(const T& o)
    {
       for (auto it = begin(); it != end(); )
         if(it->equals(o))
         {
           this->erase(it);
           return true;
         }
      return false;
    }

    sarray<T> toArray(sarray<T>& a)
    //Returns an array containing all of the elements in this list in proper sequence
    //(from first to last element); the runtime type of the returned array is that of
    //the specified array. If the list fits in the specified array, it is returned therein.
    //Otherwise, a new array is allocated with the runtime type of the specified array and the size of this list.
    //If the list fits in the specified array with room to spare (i.e., the array has more elements than the list),
    //the element in the array immediately following the end of the collection is set to null.
    //(This is useful in determining the length of the list only if the caller knows that the list does not contain any null elements.)
    {
        if(a.length()!=this->size())
            a=new array<T>(this->size());

        int i=0;
        for(T& e:(*this))
            a[i++]=e;

        return a;
    }

    String print() const
    {
        String ret=String("Size:");
        ret+=nf(this->size(),3);
        ret+=String(" [");
        for(const T& val:*this)
        {
            ret+=val;
            ret+=" ";
        }
        ret+=String("]");
        return ret;
    }
    
    //int 	size() const //Returns the number of elements in this list.
    //{ return this->size(); }
};

template<class T>
class sArrayList:public self_printable_ptr< ArrayList<T> >
{
      ///INFO: Processing semantics for one dimensional array
  public:
      ~sArrayList(){}// Zwalnianie zasobów
      sArrayList(){}
      sArrayList(std::initializer_list<T> lst);
      sArrayList(ArrayList<T>* tab): self_printable_ptr< ArrayList<T> >(tab){}
      //using self_printable_ptr< ArrayList<T> >::operator =;
      //using self_printable_ptr< ArrayList<T> >::operator ->;
      ArrayList<T>* operator -> () { return this->get();}
      auto  begin() { return this->get()->begin(); } //need C++14 !
      auto  end() { return this->get()->end(); } //need C++14 !
      //T&        operator [] (size_t i) { return (*this->get())[i]; }
      //size_t    length() { return this->get()->length; }
      int 	size() const //Returns the number of elements in this list.
      { return this->get()->size(); }
};

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2021-10-26                   */
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
