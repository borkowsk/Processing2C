// processing_alist.hpp - IMPLEMENTATION OF JAVA LIKE ArrayList
#pragma once
#ifndef PROCESSING_ALIST_H
#define PROCESSING_ALIST_H
///
///
///
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include <vector>

namespace Processing
{
/// JAVA like ArrayList
//////////////////////////


/// \brief Template for ArrayLists of objects
///
/// \link https://en.cppreference.com/w/cpp/container/vector
template<class T>
class ArrayList:public std::vector<T>, virtual public _self_printable
{
  public:
    using std::vector<T>::begin;
    using std::vector<T>::end;
    using std::vector<T>::operator[];

    ArrayList()
    {
        this->reserve(4);   assert(this->size()==0);
    }

    ArrayList(int initialSize):std::vector<T>(initialSize)
    {
        assert(this->size()==initialSize);
    }

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

/// \brief Template for interface for ArrayLists of objects
///
///
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
      //T&        operator [] (size_t i) { return (*this->get())[i]; }
      //size_t    length() { return this->get()->length; }
      ArrayList<T>* operator -> ()
      {
          auto ret=this->get();//Potrzebne dla debugingu
          return ret;
      }

      auto  begin()
      {
          auto ret=this->get()->begin();
          return ret;
      } //need C++14 !

      auto  end()
      {
          auto ret=this->get()->end();
          return ret;
      } //need C++14 !

      int   size() const //Returns the number of elements in this list.
      {
          int ret=this->get()->size();//Potrzebne dla debugingu
          return ret;
      }
};


}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2021-11-12                   */
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
