/// \file processing_alist.hpp
/// IMPLEMENTATION OF JAVA LIKE ArrayList
/// \link https://en.cppreference.com/w/cpp/container/vector
#pragma once
#ifndef PROCESSING_ArrayLIST_H
#define PROCESSING_ArrayLIST_H
///
///
///
#include "processing_templates.hpp"
#include "processing_library.hpp"
#include <vector>

///\namespace Processing2C compatibility libraries
namespace Processing
{
/// Template for ArrayLists of objects
template<class T>
class ArrayList:public/*private?*/ std::vector<T>, virtual public _self_printable
{
public:
    /// Default constructor
    ArrayList()
    {
        this->reserve(4);   assert(this->size()==0);
    }

    /// Initial size constructor
    ArrayList(int initialSize):std::vector<T>(initialSize)
    {
        assert(this->size()==initialSize);
    }

    /// NULL init constructor
    ArrayList(nullptr_t p)
    { this->reserve(4); }

    //int 	size() const //Returns the number of elements in this list.
    //{ return std::vector<T>::size(); } // Is available in vector<>

    /// Method for adding an item to the list
    bool add(const T& o)
    {
      this->push_back(o);
      return true;
    }

    /// A method of accessing a specific item
    T& get(int index)
    {
        return this->at(index);// []?
    }

    /// Index Specific Item Removal Method (NOT YET IMPLEMENTED)
    void remove(int index)
    {
       assert("NOT IMPLEMENTED"==nullptr);
       // this->erase(index);//TODO CHECK
    }

    /// A method for removing a specific item based on the comparison.
    /// It uses the one with the index.
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

    /// \brief A method that creates an array from a list (RATHER EXPENSIVE!)
    /// \in_Processing Returns an array containing all of the elements in this list in proper sequence
    /// (from first to last element); the runtime type of the returned array is that of
    /// the specified array. If the list fits in the specified array, it is returned therein.
    /// Otherwise, a new array is allocated with the runtime type of the specified array and the size of this list.
    /// If the list fits in the specified array with room to spare (i.e., the array has more elements than the list),
    /// the element in the array immediately following the end of the collection is set to null.
    ///(This is useful in determining the length of the list only if the caller knows that the list does not contain any null elements.)
    sarray<T> toArray(sarray<T>& a)
    {
        if(a.length()!=this->size())
            a=new array<T>(this->size());

        int i=0;
        for(T& e:(*this))
            a[i++]=e;

        return a;
    }

    /// Method creating a text representation of a list required by _self_printable
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

    /// DIRECT IMPORTS FROM BASIC CLASS, even if will be made private
    using std::vector<T>::begin;
    using std::vector<T>::end;
    using std::vector<T>::size;
    using std::vector<T>::operator[];
};

/// \brief Template for interface for ArrayLists of objects
/// Processing/JAVA handle semantics for list
template<class T>
class sArrayList:public self_printable_ptr< ArrayList<T> >
{
public:
    ///Default (Empty) constructor
    sArrayList()
    {}

    ///RAW POINTER constructor
    sArrayList(ArrayList<T>* lst): self_printable_ptr< ArrayList<T> >(lst)
    {}

    /// Initializer list constructor
    sArrayList(std::initializer_list<T> lst);

    /// Destructor
    ~sArrayList(){}// Dziedziczone zwalnianie zasobów

    /// Most important operator
    ArrayList<T>* operator -> ()
    {
        auto ret=this->get();//Linia potrzebna dla debuggingu
        return ret;
    }

    /// Return size of pointed list
    int   size() const //Returns the number of elements in this list.
    {
        int ret=this->get()->size();//TODO: Po co? Potrzebne chyba tylko do DEBUG
        return ret;
    }

    /// Method expected by C++
    auto  begin() //For auto return need C++14 !
    {
          auto ret=this->get()->begin();
          return ret;
    }

    /// Method expected by C++
    auto  end() //For auto return need C++14 !
    {
          auto ret=this->get()->end();
          return ret;
    }

    // DIRECT IMPORTS FROM basic class, even if will be made private
    //using self_printable_ptr< ArrayList<T> >::operator [];// NIE NO TAKIEGO TO NIE MA :-D
    //using self_printable_ptr< ArrayList<T> >::operator =;
    //using self_printable_ptr< ArrayList<T> >::operator ->;
    //T&        operator [] (size_t i) { return (*this->get())[i]; }
    //size_t    length() { return this->get()->length; }
};


}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2021-11-29                   */
/********************************************************************/
/*           THIS CODE IS DESIGNED & COPYRIGHT  BY:                 */
/*            W O J C I E C H   B O R K O W S K I                   */
/*    Instytut Studiów Społecznych Uniwersytetu Warszawskiego       */
/*    WWW: https://www.researchgate.net/profile/WOJCIECH_BORKOWSKI  */
/*    GITHUB: https://github.com/borkowsk                           */
/*                                                                  */
/*                               (Don't change or remove this note) */
/********************************************************************/
#endif //PROCESSING_ArrayLIST_H
