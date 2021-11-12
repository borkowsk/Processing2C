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

/**
 * @brief The Object class
 * Base class for all Processing/JAVA like class but not pointers
 * see:
 * @link https://www.javatpoint.com/object-class
 */
class Object
{
  private: Object& operator = (const Object&);
  public:
    virtual ~Object(){}
    virtual long hashCode() const;///	returns the hashcode number for this object
    virtual bool equals(const Object& obj) const///	compares the given object to this object.
    { return this==&obj; }
};

/**
 * @brief The template class ptr<>
 * Proxy for standard shared_ptr but mimic Procesing "object references" behaviour
 */
template<class T>
class ptr:public std::shared_ptr<T>
{
  public:
      ~ptr(){}// Destruktor - zwalnianie zasobów

      //Konstruktory
      //^^^^^^^^^^^^
      ptr():std::shared_ptr<T>(nullptr){}     //empty

      ptr(nullptr_t p):std::shared_ptr<T>(p){}//visible empty

      ptr(T* ini):std::shared_ptr<T>(ini){}   //from raw pointer for new T

      template<class B>
      ptr(std::shared_ptr<B> ini):std::shared_ptr<T>(ini)//konwersja z gołych shared_ptr'ów potrzebna dla dynamic_ptr_cast<>
      {
          assert(ini.get()==nullptr || this->get()!=nullptr);//std::cerr<<ini.get()<<std::endl;
      }

      template<class B>
      ptr(ptr<B>& ini):std::shared_ptr<T>(ini)//Konwersja z ptr<> z typów akceptowalnych przez shared_ptr<T>
      {
          assert(ini.get()==nullptr || this->get()!=nullptr);
      }

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
      operator T* () { return this->get();}
};

/**
 * Representation of JAVA "Comparable" interface
 */
template<class T>
/*interface*/ class Comparable
{
  ///INFO:
  public:
      virtual int compareTo(ptr<T> o) = 0;
};

/**
 * @brief pObject is aliasing for ptr<Object>
 * Represents "object references" for object of basic class Object
 */
typedef ptr<Object> pObject;

/**
 * @brief The template class array
 * Array of T, sized when constructed
 */
template<class T>
class array
{
      T* _ptr;
  public:
      size_t length;//Processing ma to jako goły atrybut a nie akcessor

      ~array() { delete [] _ptr; } // Zwalnianie zasobów
      array(size_t N); //Jedyny konstruktor
      T& operator [] (size_t i) { return _ptr[i]; }
};

/**
 * @brief The template class ptr< array >
 * Represents "object references" for array of T
 * Implements Processing semantics for one dimensional array
 */
template<class T>
class sarray:public ptr< array<T> >
{
  public:
      ~sarray(){}// Odziedziczone zwalnianie zasobów
      sarray(){}
      sarray(array<T>* tab): ptr< array<T> >(tab){}
      sarray(std::initializer_list<T> lst);

      array<T>*   operator -> () { return this->get();}
      T&          operator [] (std::size_t i) { return (*this->get())[i]; }
      T*          begin() { return &(*this)[0]; }
      T*          end() { return &(*this)[ length() ]; }
      std::size_t length() { return this->get()->length; }
};

/**
 * @brief The template class matrix (2D array)
 * Matrix of T, sized when constructed
 * (Tablica dwuwymiarowa opiera się na jednowymiarowych (PL))
 */
template<class T>
class matrix:public array< sarray<T> >
{
  public:
      ~matrix(){}// Odziedziczone zwalnianie zasobów
       matrix(std::size_t N,std::size_t M);//Jedyny konstruktor
      //sarray<T>& operator [] (size_t j);//???
};

/**
 * @brief The template class ptr< matrix >
 * Represents "object references" for matrix of T
 * Implements Processing semantics for two dimensional array
 */
template<class T>
class smatrix:public ptr< matrix<T> >
{
  public:
      ~smatrix(){}// Odziedziczone zwalnianie zasobów
      smatrix(){}
      smatrix(matrix<T>* tab): ptr< matrix<T> > (tab) {}
      //smatrix(std::initializer_list<T> lst);//Na razie nigdzie nie używane. Potrzebne?

      matrix<T>* operator -> () { return this->get();}
      sarray<T>& operator [] (size_t j) { return (*this->get())[j]; }
      sarray<T>* begin() { return &(*this)[0]; }
      sarray<T>* end() { return &(*this)[ length() ]; }
      size_t     length() { return this->get()->length; }
};

// PODRĘCZNE IMPLEMETACJE INLINE
//**********************************

/**
 * @brief Function _free_ptr_to releases the raw pointer to A
 */
template<class A,class B>
inline
A* _free_ptr_to(ptr<B>& b)//TODO rename it into _raw_ptr_to
{
    return (A*)(B*)b;
}

/**
 * @brief JAVA like instanceof function
 * inspired by https://www.tutorialspoint.com/cplusplus-equivalent-of-instanceof
 */
template<typename Base, typename T>
inline
bool instanceof(ptr<T>& p)
{
   return dynamic_cast<Base*>(p.get()) != nullptr;
}

/**
 * @brief Template of sarray<> constructor with initialiser list
 */
template<class T>
inline
sarray<T>::sarray(std::initializer_list<T> l):ptr< array<T> >(new array<T>(l.size()))
{
    size_t i=0;
    for(auto e:l)
        (*this)[i++]=e;
}

/**
 * @brief The sole constructor of inside template array<T> class
 */
template<class T>
inline
array<T>::array(size_t N): length{N}
{
    _ptr = new T[N];
}

/**
 * @brief The sole constructor of inside template matrix<T> class
 */
template<class T>
inline
matrix<T>::matrix(size_t N,size_t M):array< sarray<T> >( N )
{
    for(size_t i=0;i<this->length;i++)
        (*this)[i]=new array<T>( M );
}

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
