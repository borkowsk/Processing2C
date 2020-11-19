// Obligatoryjne szablony dla obiektów i tablic
#pragma once
#ifndef PROCESSING_TEMPLATES_H
#define PROCESSING_TEMPLATES_H
#include <cassert>
#include <memory>
#include <initializer_list>
/// https://en.cppreference.com/w/cpp/utility/initializer_list
/// https://en.cppreference.com/w/cpp/language/constructor
/// https://stackoverflow.com/questions/31874669/c11-reference-count-smart-pointer-design
namespace Processing
{

class Object
{
  ///INFO: see https://www.javatpoint.com/object-class
  private: Object& operator = (const Object&);
  public:
    virtual ~Object(){}
    virtual long hashCode() const;///	returns the hashcode number for this object
    virtual bool equals(const Object& obj) const///	compares the given object to this object.
    { return this==&obj; }
};

template<class T>
class ptr:public std::shared_ptr<T>
{
  ///INFO: Proxy for standard shared_ptr for mimic Procesing "object references" behaviour
  public:
      ~ptr(){}// Destruktor - zwalnianie zasobów

      //Konstruktory
      //^^^^^^^^^^^^
      ptr():std::shared_ptr<T>(nullptr){}     //empty

      ptr(nullptr_t p):std::shared_ptr<T>(p){}//visible empty

      ptr(T* ini):std::shared_ptr<T>(ini){}   //from raw pointer for new T

      template<class B>
      ptr(std::shared_ptr<B> ini):std::shared_ptr<T>(ini)//konwersja z gołych shared_ptr'ów (potrzebna?)
      {assert(ini.get()==nullptr || this->get()!=nullptr);}

      template<class B>
      ptr(ptr<B>& ini):std::shared_ptr<T>(ini)//Konwersja z ptr<> z typów akceptowalnych przez shared_ptr<T>
      {assert(ini.get()==nullptr || this->get()!=nullptr);}

      //Przypisania  //using std::shared_ptr<T>::operator = ;//kipisz!!! :-(
      //^^^^^^^^^^^
      ptr<T>& operator = (nullptr_t p){ std::shared_ptr<T>::operator = (p); return *this; }
      ptr<T>& operator = (std::shared_ptr<T> p){ std::shared_ptr<T>::operator = (p); return *this;}
      ptr<T>& operator = (ptr<T> p){ std::shared_ptr<T>::operator = (p); return *this; }

      //Porównania
      //^^^^^^^^^^
      template<class B>
      bool equals(const ptr<B>& p) const //Same object pointed
      {
          Object* tmp1=this->get();
          Object* tmp2=p.get();
          return tmp1==tmp2;
      }

      template<class B>
      bool operator == (const ptr<B>& p) const { return this->equals(p);}

      template<class B>
      bool operator != (const ptr<B>& p) const { return !(this->equals(p));}

      bool operator == (T* p) const { return this->get()==p;}
      bool operator != (T* p) const { return this->get()!=p;}

      bool operator == (std::nullptr_t p) const { return this->get()==p;}
      bool operator != (std::nullptr_t p) const { return this->get()!=p;}

      //Dostęp do wskaźnika przechowywanego
      //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
      T* operator -> () { return this->get();}
      //operator T& () { return *(this->get());}
      operator T* () { return this->get();}
};

typedef ptr<Object> pObject;

template<class A,class B>
inline A*
_free_ptr_to(ptr<B>& b)//release the pointer to A
{
    return (A*)(B*)b;
}

template<typename Base, typename T> //inspired by https://www.tutorialspoint.com/cplusplus-equivalent-of-instanceof
inline 
bool instanceof(ptr<T>& p)
{
   return dynamic_cast<Base*>(p.get()) != nullptr;
}

template<class T>
/*interface*/ class Comparable
{
  ///INFO:
  public:
      virtual int compareTo(ptr<T> o) = 0;
};

template<class T>
class array
{
  ///INFO: Array of T, sized when constructed
  T* _ptr;
  public:
      size_t length;

      ~array() { delete [] _ptr; } // Zwalnianie zasobów
      array(size_t N): length{N} { _ptr = new T[N]; }
      T& operator [] (size_t i) { return _ptr[i]; }
};

template<class T>
class sarray:public ptr< array<T> >
{
      ///INFO: Processing semantics for one dimensional array
  public:
      ~sarray(){}// Zwalnianie zasobów
      sarray(){}
      sarray(std::initializer_list<T> lst);
      sarray(array<T>* tab): ptr< array<T> >(tab){}

      array<T>* operator -> () { return this->get();}
      T&        operator [] (size_t i) { return (*this->get())[i]; }
      T*        begin() { return &(*this)[0]; }
      T*        end() { return &(*this)[ length() ]; }
      size_t    length() { return this->get()->length; }
};

template<class T>
inline  
sarray<T>::sarray(std::initializer_list<T> l):ptr< array<T> >(new array<T>(l.size()))
{ //NOT TESTED YET? TODO?
    size_t i=0;
    for(auto e:l)
        (*this)[i++]=e;
}

template<class T>
class matrix:public array< sarray<T> >
{
  ///INFO: tablica dwuwymiarowa opiera się na jednowymiarowych
  public:
      ~matrix(){}// Zwalnianie zasobów
       matrix(size_t N,size_t M);
      //sarray<T>& operator [] (size_t j);//Potrzebne?
};

template<class T>
inline 
matrix<T>::matrix(size_t N,size_t M):array< sarray<T> >( N )
{ //NOT TESTED YET! TODO!
    for(size_t i=0;i<this->length;i++)
        (*this)[i]=new array<T>( M );
}

template<class T>
class smatrix:public ptr< matrix<T> >
{
  ///INFO:Processing semantics for two dimensional array
  public:
      ~smatrix(){}// Zwalnianie zasobów
      smatrix(){}
      smatrix(matrix<T>* tab): ptr< matrix<T> > (tab) {}
      //smatrix(std::initializer_list<T> lst);//Potrzebne?

      matrix<T>* operator -> () { return this->get();}
      sarray<T>& operator [] (size_t j) { return (*this->get())[j]; }
      sarray<T>* begin() { return &(*this)[0]; }
      sarray<T>* end() { return &(*this)[ length() ]; }
      size_t     length() { return this->get()->length; }
};

}//END of namespace Processing
/********************************************************************/
/*               PROCESSING2C  version 2020-11-18                   */
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
